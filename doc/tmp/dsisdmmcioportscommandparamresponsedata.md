# DSi SD/MMC I/O Ports: Command/Param/Response/Data


### 4004800h/4004A00h - SD_CMD - Command and Response/Data Type (R/W)

```
+-------------------------------------------------------------------------------------+
|       15    undoc   Unknown/undoc  (read/write-able)                                |
|       14    undoc   Security Cmd?  (0=Normal, 1=Whatever/Security?) (sdio?)         |
|       13    undoc   Data Length    (0=Single Block, 1=Multiple Blocks)              |
|       12    undoc   Data Direction (0=Write, 1=Read)                                |
|       11    NTDT    Data Transfer  (0=No data, 1=With data)                         |
|       10-8  REP2-0  Response Type  (0=Auto, 1..2=Unknown/Reserved, 3=None, 4=48bit, |
|                                     5=48bit+Busy, 6=136bit, 7=48bitOcrWithoutCRC7)  |
|       7-6   CMD1-0  Command Type   (0=CMD, 1=ACMD, 2..3=unknown, maybe GEN WR/RD?)  |
|       5-0   CIX     Command Index  (0..3Fh, command index)                          |
+-------------------------------------------------------------------------------------+
```

Setting Command Type to \"ACMD\" does NOT automatically send the APP_CMD prefix prior to the command number.
For Multiple Blocks, the hardware supports automatically sending STOP_TRANSMISSION after the last block.
DSi software is usually setting Response Type to \"Auto\", which is causing the hardware to use the correct response/data type for standard SD/MMC commands (bit11-13 are ignored/should be zero when using \"Auto\"; and maybe same for bit14-15?).
One exception is that the DSi firmware isn\'t using \"Auto\" for SDIO commands (maybe the hardware isn\'t aware of them; or it\'s unable to distinguish between read/write direction of CMD53, which would require examining the command\'s PARAM bits).
There are some differences between some SD and MMC commands, unknown if/how \"Auto\" is working in that cases; unknown if there\'s a SD-or-MMC mode select bit for that purpose in some configuration register (note: The DSi firmware uses manual config instead of Auto for CMD8, which differs for SD vs MMC).
Invalid values can cause ILA error (particulary on setting NTDT for CMD12, or for CMD\'s Response=None). ILA error will also occur if an old CMD is still busy.

### 4004804h/4004A04h - SD_CMD_PARAM0-1 - Argument (32bit, 2 halfwords) (R/W)

```
+-----------------------------------------------------------------------+
|       31-0  Parameter value for CMD                                   |
+-----------------------------------------------------------------------+
```

The parameter value should be written \<before\> sending the command via SD_CMD/SDIO_CMD.

### 400480Ch/4004A0Ch - SD_RESPONSE0-7 - Response (128bit, 8 halfwords) (R)
After sending a command, wait for the CMDRESPEND bit (IRQ_STATUS.bit0) to get set, then read the RESPONSE (if the command does have any response).
For normal 32bit responses:

```
+-----------------------------------------------------------------------+
|       31-0      Response                                              |
|       127-32    Older Responses                                       |
+-----------------------------------------------------------------------+
```

For CID/CSD responses:

```
+-----------------------------------------------------------------------+
|       119-0     120bit Response                                       |
|       127-120   Zero (always?)                                        |
+-----------------------------------------------------------------------+
```

The above stuff is left-shifted when receiving new response bits (hence moving older responses to MSBs).

### DATA16 vs DATA32
Data can be transferred in 16bit or 32bit units (as selected in DATA_CTL.bit1 and DATA32_IRQ.bit1). There are separate data, block len, and block count registers for 16bit and 32bit mode. 16bit mode uses two FIFOs (each with 200h-byte capactity). 32bit adds another FIFO (also with 200h-byte capacity):

```
+------------------------------------------------------------------------------+
|                       .----------.                                  CPU      |
|                    o--| FIFO16_A |--o             o---------------- 4004830h |
|       serial          '----------'   \                              16bit    
|       SD/MMC  ---o                    o---------o                            |
|       bus         \   .----------.               \    .--------.    CPU/NDMA 
|                    o--| FIFO16_B |--o             o---| FIFO32 |--- 400490Ch |
|                       '----------'                    '--------'    32bit    |
+------------------------------------------------------------------------------+
```

The 32bit mode is some odd patchwork, apparently Nintendo/Toshiba considered it easier to add an extra 32bit FIFO (rather than to figure out how to add native 32bit access to Toshiba\'s original 16bit chip design).
The DSi firmware does use both 32bit and 16bit mode once and then; 32bit mode can be faster, and it\'s required for NDMA transfers (which don\'t support 16bit).

### 40048D8h/4004AD8h - SD_DATA_CTL

```
+------------------------------------------------------------------------------------+
|       15-13  Always zero                                                           |
|       12     Unknown (usually 1)                                             (R?)  |
|       11-6   Always zero                                                           |
|       5      Unknown (read/write-able) (usually 0)                           (R/W) |
|       4      Unknown (usually 1)                                             (R?)  |
|       3-2    Always zero                                                           |
|       1      Select 16bit/32bit Data Mode (0=DATA16, 1=DATA32, see 4004900h) (R/W) |
|       0      Always zero                                                           |
+------------------------------------------------------------------------------------+
```

DATA32 mode requires setting both 40048D8h.bit1 and 4004900h.bit1. For DATA16 mode, both bits should be zero (though DATA16 seems to be also working the same way when only either of the bits is zero).

### 400480Ah/4004A0Ah - SD_DATA16_BLK_COUNT - NumBlocks for 16/32 bit Modes (R/W)
### 4004908h/4004B08h - SD_DATA32_BLK_COUNT - NumBlocks for 32 bit Mode (R/W)

```
+--------------------------------------------------------------------------------+
|       15-0   Number of Data Blocks for multiple read/write commands (0..FFFFh) |
+--------------------------------------------------------------------------------+
```

SD_DATA16_BLK_COUNT needs to be initialized in both 16bit and 32bit mode, the written value is copied to a internal register, which gets decremented after each block, and (when enabled in STOP_INTERNAL_ACTION.bit8) the hardware will automatically send STOP_TRANSMISSION (CMD12) after the last block (otherwise the hardware would keep transferring blocks infinitely).
For Data32 mode, DATA32_BLK_COUNT should be set to the same value (it doesn\'t really affect the transfer though, the register is intended only for watching the transfer progress: DATA32_BLK_COUNT is decremented after each block (when FIFO32 gets empty); except when it would become zero, in that case it stays stuck at 0001h).

### 4004826h/4004A26h - SD_DATA16_BLK_LEN - FIFO16 Size for 16/32 bit Modes (R/W)
### 4004904h/4004B04h - SD_DATA32_BLK_LEN - FIFO32 Size for 32 bit Mode (R/W)

```
+----------------------------------------------------------------------------------+
|       15-10  Always zero                                                         |
|       9-0    Data Block Length in bytes (for DATA16: clipped to max 0200h by hw) |
+----------------------------------------------------------------------------------+
```

SD_DATA16_BLK_LEN needs to be initialized in both 16bit and 32bit mode. For 32bit mode, SD_DATA32_BLK_LEN should be also set to the same value (otherwise odd effects might occur when forwarding FIFO16 to/from FIFO32).
The block length should be usually 0200h (for 512-byte SD/MMC memory blocks). Other values may be needed for SDIO functions, or when accessing SSR/SCR/PWD registers via data transfers.
DATA32_BLK_LEN can be set to max=3FFh (unlike DATA16_BLK_LEN which is clipped to max=200h by hardware), though settings bigger than 200h won\'t work in practice (since the FIFOs are only 200h bytes in size).

### 4004830h/4004A30h - SD_DATA16_FIFO - Data FIFO for 16bit Mode (R/W)
### 400490Ch/4004B0Ch - SD_DATA32_FIFO - Data FIFO for 32bit Mode (R/W)
For Data16:

```
+-----------------------------------------------------------------------------------+
|       15-0   Data (Read/Write one block (usually 100h halfwords) upon RXRDY/TXRQ) |
+-----------------------------------------------------------------------------------+
```

For Data32:

```
+----------------------------------------------------------------------------------+
|       31-0   Data (Read/Write one block (usually 80h words) upon RX32RDY/TX32RQ) |
+----------------------------------------------------------------------------------+
```

See the RXRDY/TXRQ and RX32RDY/TX32RQ interrupt flags for details.
The first Data32 block may be written even before sending the command (the DSi firmware is actually doing that, although, performance-wise, it would make sense only when writing multiple clusters, ie. sending the first block of the next cluster while the previous write is still in progress).
Observe that RX32RDY/TX32RQ are actually FIFO full/empty flags (getting triggered any time when FIFO is full/empty, so you must know for yourself if you want to transfer data in that situations; eg. FIFO empty will trigger even after having written all data blocks, or when not intending to write any data at all).



