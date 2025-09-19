# DSi SD/MMC Protocol: Block Read/Write Commands


### CMD16 - SD/MMC - SPI - SET_BLOCKLEN (type=ac)

```
+---------------------------------------------------------------------------+
|       31-0  Block length (for Block Read, Block Write, Lock, and GEN_CMD) |
+---------------------------------------------------------------------------+
```

Response: R1
In the case of SDSC Card, this command sets the block length (in bytes) for all following block commands (read, write, lock). Default block length is fixed to 512 Bytes. Set length is valid for memory access commands only if partial block read operation are allowed in CSD.
In the case of SDHC/SDXC Cards, block length set by CMD16 command does not affect memory read and write commands. Always 512 Bytes fixed block length is used. This command is effective for LOCK_UNLOCK command.
In both cases, if block length is set larger than 512 Bytes, the card sets the BLOCK_LEN_ERROR bit.
In DDR50 mode, block length must be even (because data is sampled on both clock edges).

### CMD20 - SD (optional, see SCR.Bit32) - SPEED_CLASS_CONTROL (type=ac)

```
+-----------------------------------------------------------------------------+
|       31-28  Speed Class Control (for Block Read, and Block Write commands) |
|       27-0   Reserved (0)                                                   |
+-----------------------------------------------------------------------------+
```

Response: R1b
Additional Data Transfer (from card): Busy signal for \"R1b\" response
Speed Class control command. Refer to Section 4.13.2.8.

### CMD23 - SD/MMC - SPI (but only on MMC) - SET_BLOCK_COUNT (type=ac)
Supported by SD and MMC Cards. However, in SPI-mode it\'s supported only for MMC? And, for SD it\'s optional (see SCR.Bit33).

```
+----------------------------------------------------------------------------+
|       31-0  Block Count (MMC: only lower 16bit used, upper 16bit=reserved) |
+----------------------------------------------------------------------------+
```

Response: R1
Specify block count for CMD18 and CMD25.


```
+-------------------------------------------------------------------------------------+
|      ________________________ Block-Oriented READ Commands ________________________ |
+-------------------------------------------------------------------------------------+
```


### CMD17 - SD/MMC - SPI - READ_SINGLE_BLOCK (type=adtc)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       data                                                            |
+-----------------------------------------------------------------------+
```

In the case of SDSC Card, this command reads a block of the size selected by the SET_BLOCKLEN command. The data transferred shall not cross a physical block boundary unless READ_BLK_MISALIGN is set in the CSD.
In case of SDHC and SDXC Cards, block length is fixed 512 Bytes regardless of the SET_BLOCKLEN command.

### CMD18 - SD/MMC - SPI - READ_MULTIPLE_BLOCK (type=adtc)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       data                                                            |
+-----------------------------------------------------------------------+
```

Continuously transfers data blocks from card to host until interrupted by a STOP_TRANSMISSION command.
Block length is specified the same as READ_SINGLE_BLOCK command.

### CMD19 - SD - SET_TUNING_BLOCK (type=adtc) (SD only, BUSTEST_W on MMC)

```
+-----------------------------------------------------------------------+
|       31-0  reserved bits (0)                                         |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to card):

```
+-----------------------------------------------------------------------+
|       64 bytes (512bit) tuning pattern is sent for SDR50 and SDR104.  |
+-----------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      _______________________ Block-Oriented WRITE Commands _______________________ |
+------------------------------------------------------------------------------------+
```


### CMD24 - SD/MMC - SPI - WRITE_BLOCK (type=adtc)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to card):

```
+-----------------------------------------------------------------------+
|       data                                                            |
+-----------------------------------------------------------------------+
```

In case of SDSC Card, block length is set by the SET_BLOCKLEN command. The data transferred shall not cross a physical block boundary unless WRITE_BLK_MISALIGN is set in the CSD. In the case that write partial blocks is not supported, then the block length=default block length (given in CSD).
In case of SDHC and SDXC Cards, block length is fixed 512 Bytes regardless of the SET_BLOCKLEN command.

### CMD25 - SD/MMC - SPI - WRITE_MULTIPLE_BLOCK (type=adtc)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to card):

```
+-----------------------------------------------------------------------+
|       data                                                            |
+-----------------------------------------------------------------------+
```

Continuously writes blocks of data until a STOP_TRANSMISSION follows.
Block length is specified the same as WRITE_BLOCK command.

### ACMD22 - SD - SPI - GET_NUM_WR_BLOCKS (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-------------------------------------------------------------------------+
|       31-0  Number of the written (without errors) write blocks (32bit) |
+-------------------------------------------------------------------------+
```

Responds with 32bit+CRC data block.
If WRITE_BL_PARTIAL=\'0\', the unit of ACMD22 is always 512 byte.
If WRITE_BL_PARTIAL=\'1\', the unit of ACMD22 is a block length which was used when the write command was executed.

### ACMD23 - SD - SPI - SET_WR_BLK_ERASE_COUNT (type=ac)

```
+-----------------------------------------------------------------------+
|       31-23  stuff bits                                               |
|       22-0   Number of blocks                                         |
+-----------------------------------------------------------------------+
```

Response: R1
Set the number of write blocks to be pre-erased before writing (to be used for faster Multiple Block WR command). \"1\"=default (one wr block).
Command STOP_TRAN (CMD12) shall be used to stop the transmission in Write Multiple Block whether or not the pre-erase (ACMD23) feature is used.


```
+-------------------------------------------------------------------------------------+
|      _____________________ Byte-Streaming READ/WRITE Commands _____________________ |
+-------------------------------------------------------------------------------------+
```


### CMD11 - MMC - READ_DAT_UNTIL_STOP (class 1) (type=adtc)
### CMD20 - MMC - WRITE_DAT_UNTIL_STOP (class 3) (type=adtc)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to/from card):

```
+-----------------------------------------------------------------------+
|       data                                                            |
+-----------------------------------------------------------------------+
```

Similar to read/write multiple blocks, but transferring the data as an endless byte stream (instead of splitting it into separate blocks). Transfer is terminated by sending STOP_TRANSMISSION.



