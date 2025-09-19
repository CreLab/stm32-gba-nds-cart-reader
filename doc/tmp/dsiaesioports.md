# DSi AES I/O Ports


### 4004400h - DSi7 - AES_CNT (parts R/W)

```
+-------------------------------------------------------------------------------------+
|       0-4   Write FIFO Count    (00h..10h words) (00h=Empty, 10h=Full)          (R) |
|       5-9   Read FIFO Count     (00h..10h words) (00h=Empty, 10h=Full)          (R) |
|       10    Write FIFO Flush    (0=No change, 1=Flush)                   (N/A or W) |
|       11    Read FIFO Flush     (0=No change, 1=Flush)                   (N/A or W) |
|       12-13 Write FIFO DMA Size (0..3 = 16,12,8,4 words) (2=Normal=8)    (R or R/W) |
|       14-15 Read FIFO DMA Size  (0..3 = 4,8,12,16 words) (1=Normal=8)    (R or R/W) |
|       16-18 CCM MAC Size, max(4,(N*2+2)) bytes, usually 7=16 bytes       (R or R/W) |
|       19    CCM Pass Associated Data to RDFIFO (0=No/Normal, 1=Yes)      (R or R/W) |
|               Bit19=1 is a bit glitchy: The data should theoretically arrive in     |
|               RDFIFO immediately after writing 4 words to WRFIFO, but actually,     |
|               Bit19=1 seems to cause 4 words held hidden in neither FIFO, until     |
|               the first Payload block is written (at that point, the hidden         |
|               associated words are suddenly appearing in RDFIFO)                    |
|       20    CCM MAC Verify Source (0=From AES_WRFIFO, 1=From AES_MAC)    (R or R/W) |
|       21    CCM MAC Verify Result (0=Invalid/Busy, 1=Verified/Okay)             (R) |
|       22-23 Unknown/Unused (0)                                                  (0) |
|       24    Key Select        (0=No change, 1=Apply key selected in Bit26-27)   (W) |
|       25    Key Schedule Busy (uh, always 0=ready?) (rather sth else busy?)     (R) |
|       26-27 Key Slot          (0..3=KEY0..KEY3, applied via Bit24)       (R or R/W) |
|       28-29 Mode (0=CCM/decrypt, 1=CCM/encrypt, 2=CTR, 3=Same as 2)      (R or R/W) |
|       30    Interrupt Enable  (0=Disable, 1=Enable IRQ on Transfer End)  (R or R/W) |
|       31    Start/Enable      (0=Disable/Ready, 1=Enable/Busy)                (R/W) |
+-------------------------------------------------------------------------------------+
```

Bit31 gets cleared automatically shortly after all data (as indicated in AES_BLKCNT) is written to WRFIFO, and the IRQ is generated alongsides; the transfer isn\'t fully completed at that point since there may be still data (and CCM/encrypt MAC result) in RDFIFO.

### 4004404h - DSi7 - AES_BLKCNT (W)
Specifies the transfer length, counted in 16-byte blocks.

```
+-------------------------------------------------------------------------------------+
|       0-15  Number of Extra associated data blocks for AES-CCM (unused for AES-CTR) |
|       16-31 Number of Payload data blocks (0..FFFFh = 0..FFFF0h bytes)              |
+-------------------------------------------------------------------------------------+
```

The length values are copied to internal counter registers on transfer start (the value in AES_BLKCNT is left unchanged during/after transfer).

### 4004408h - DSi7 - AES_WRFIFO (W)
### 400440Ch - DSi7 - AES_RDFIFO (R)

```
+-----------------------------------------------------------------------+
|       0-31  Data                                                      |
+-----------------------------------------------------------------------+
```

Writing to WRFIFO works even when AES_CNT.bit31=0 (the data does then stay in WRFIFO though, and doesn\'t arrive in RDFIFO).

### 4004420h - DSi7 - AES_IV (16 bytes) (W)
This contains the Initialization Vector (aka IV aka Nonce). The hardware does use that value to automatically initialize the internal CTR/CBC registers when starting encryption/decryption:

```
+---------------------------------------------------------------------------+
|       For AES-CTR mode:  CTR[00h..0Fh] = AES_IV[00h..0Fh]                 |
|                          CBC[00h..0Fh] = not used by AES-CTR mode         |
|       For AES-CCM mode:  CTR[00h..0Fh] = 00h,00h,00h,AES_IV[00h..0Bh],02h |
|                          CBC[00h..0Fh] = x0h,xxh,0xh,AES_IV[00h..0Bh],flg |
+---------------------------------------------------------------------------+
```

The initial CTR/CBC values for AES-CCM mode are following the CCM specifications, but WITHOUT encoding the \"extra associated data size\" in upper bytes of first block (see CCM pseudo code chapter for details).
The CTR/CBC registers are manipulated during transfer, however, the AES_IV content is kept unchanged during/after transfer.

### 4004430h - DSi7 - AES_MAC (16 bytes) (W)
The MAC (Message Authentication Code) is an encrypted checksum, computed alongsides with the actual data encryption/decryption, and used only in AES-CCM mode. There are three ways how the DSi deals with MAC values:

```
+----------------------------------------------------------------------------------+
|       AES-CCM Encryption: MAC is returned in AES_RDFIFO after transfer           |
|       AES-CCM Decryption, AES_CNT.20=0: MAC written to AES_WRFIFO after transfer |
|       AES-CCM Decryption, AES_CNT.20=1: MAC written to AES_MAC before transfer   |
+----------------------------------------------------------------------------------+
```

The AES_MAC register and the RDFIFO/WRFIFO blocks are always 16-byte wide; when selecting a smaller MAC size in AES_CNT, then the lower bytes of that 16-byte value are 00h-padded (eg. a 6-byte MAC would appear as 00000000h, 00000000h, xxxx0000h, xxxxxxxxh), for ENCRYPT those 00h-bytes are returned in RDFIFO, for DECRYPT those padding bytes MUST be 00h (else the verification will fail).
The minimum MAC size is 4 bytes (trying to use 2 byte by setting AES_CNT.16-18 to 00h is producing the exact same result as when setting it to 01h, ie. 4-bytes)

### 4004440h - DSi7 - AES_KEY0 (48 bytes) (W)
### 4004470h - DSi7 - AES_KEY1 (48 bytes) (W)
### 40044A0h - DSi7 - AES_KEY2 (48 bytes) (W)
### 40044D0h - DSi7 - AES_KEY3 (48 bytes) (W)

```
+-----------------------------------------------------------------------+
|       Byte 00h-0Fh  Normal 128bit Key      ;\use either normal key,   
|       Byte 10h-1Fh  Special 128bit Key_X   ; or special key_x/y       |
|       Byte 20h-2Fh  Special 128bit Key_Y   ;/                         |
+-----------------------------------------------------------------------+
```

Writing the last word of \"Key_Y\" (or any of its last four bytes, ie. byte(s) 2Ch..2Fh) causes the Normal Key to be overwritten by following values:

```
+----------------------------------------------------------------------------+
|       Key = ((Key_X XOR Key_Y) + FFFEFB4E295902582A680F5F1A4F3E79h) ROL 42 |
+----------------------------------------------------------------------------+
```

After changing a key, one must (re-)apply it via AES_CNT.Bits 24,26-27.

### DMA
The AES data would be usually transferred via two NDMA channels, one for WRFIFO, one for RDFIFO. The NDMAs should be started BEFORE setting AES_CNT.31 (else the DMA will miss the first WRFIFO data request; and DMA won\'t start). The DMAs \'Logical Block\' sizes should match up with the block sizes selected in AES_CNT (a bigger logical block size would cause FIFO overruns/underruns, a smaller logical block size could work theoretically, but it practice it causes the DMA to hang after the first data request; apparently data requests are somewhat generated upon \"empty-not-empty\" transitions, rather than upon \"enough data/space\" status).

### Reading Write-Only Values
The AES_IV register and the AES_KEY registers are fully write-able, including 8bit STRB writes; this allows to \'read\' the write-only values via brute-force without any noticeable delay (ie. encrypt 16 bytes with original values, then change one byte to values 00h..FFh, and check which of those values gives same encryption result). AES_BLKCNT can be also dumped by simple counting.

### Cartheader Key Request Byte
The firmware is usually destroying the AES_KEY registers before starting DSi programs. However, bits in CartHeader\[1B4h\] allow to \"request\" certain keys to be left intact.

### DSi BIOS & Firmware Keys
The DSi BIOS contains several AES keys in the non-dumpable upper 32K halves; most of that keys are relocated to RAM/TCM, so they can be dumped via main memory hacks (there might be some further keys that cannot be dumped, in case they exist only in early boot stages).



