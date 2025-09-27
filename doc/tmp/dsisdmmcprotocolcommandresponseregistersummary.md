# DSi SD/MMC Protocol: Command/Response/Register Summary


### Basic Commands (class 0)

```
+-------------------------------------------------------------------------------------+
|       CMD0     sd/mmc spi GO_IDLE_STATE (CMD0 with arg=stuff) (type=bc)             |
|       CMD0     mmc        GO_PRE_IDLE_STATE (CMD0 with arg=F0F0F0F0h) (type=bc)     |
|       CMD0     mmc        BOOT_INITIATION (CMD0 with arg=FFFFFFFAh, type=N/A)       |
|       CMD1     sd/mmc spi SEND_OP_COND (On SD Cards: SPI only)                      |
|       CMD2     sd/mmc     ALL_GET_CID (type=bcr)                                    |
|       CMD3     sd         GET_RELATIVE_ADDR (type=bcr)                              |
|       CMD3     mmc        SET_RELATIVE_ADDR (type=ac)                               |
|       CMD4     sd/mmc     SET_DSR (type=bc)                                         |
|       CMD5     sd     spi Reserved for I/O cards (see "SDIO Card Specification")    |
|       CMD5     mmc    ?   SLEEP_AWAKE (type=ac) (MMC only, IO_SEND_OP_COND on SDIO) |
|       CMD7     sd/mmc     SELECT_DESELECT_CARD (type=ac) ;actually: (type=bcr)      |
|       CMD8     sd     spi SET_IF_COND (type=bcr)                                    |
|       CMD8     mmc    spi GET_EXT_CSD (type=adtc)                                   |
|       CMD9     sd/mmc spi GET_CSD (type=ac) (SPI: type=adtc)                        |
|       CMD10    sd/mmc spi GET_CID (type=ac) (SPI: type=adtc)                        |
|       CMD11    sd         VOLTAGE_SWITCH (type=ac)                                  |
|       CMD12    sd/mmc spi STOP_TRANSMISSION (type=ac)                               |
|       CMD13    sd/mmc spi GET_STATUS (type=ac) (sends 16bit status in SPI Mode)     |
|       CMD14    mmc        BUSTEST_R (type=adtc) (MMC only, Reserved on SD)          |
|       CMD19    mmc        BUSTEST_W (type=adtc) (MMC only, SET_TUNING_BLOCK on SD)  |
|       CMD15    sd/mmc     GO_INACTIVE_STATE (type=ac)                               |
+-------------------------------------------------------------------------------------+
```


### Block-Oriented Read Commands (class 2)

```
+----------------------------------------------------------------------------------+
|       CMD16    sd/mmc spi SET_BLOCKLEN (type=ac)                                 |
|       CMD17    sd/mmc spi READ_SINGLE_BLOCK (type=adtc)                          |
|       CMD18    sd/mmc spi READ_MULTIPLE_BLOCK (type=adtc)                        |
|       CMD19    sd         SET_TUNING_BLOCK (type=adtc)                           |
|       CMD20    sd         SPEED_CLASS_CONTROL (type=ac)                          |
|       CMD22    sd         Reserved                                               |
|       CMD23    sd/mmc-spi SET_BLOCK_COUNT (type=ac) (SPI supported ONLY on MMC?) |
+----------------------------------------------------------------------------------+
```


### Block-Oriented Write Commands (class 4)

```
+----------------------------------------------------------------------------------+
|       CMD16    sd/mmc spi SET_BLOCKLEN (type=ac)                                 |
|       CMD20    sd         SPEED_CLASS_CONTROL (type=ac)                          |
|       CMD23    sd/mmc-spi SET_BLOCK_COUNT (type=ac) (SPI supported ONLY on MMC?) |
|       CMD24    sd/mmc spi WRITE_BLOCK (type=adtc)                                |
|       CMD25    sd/mmc spi WRITE_MULTIPLE_BLOCK (type=adtc)                       |
|       CMD26    sd/mmc     Reserved For Manufacturer (MMC: PROGRAM_CID)           |
|       CMD27    sd/mmc spi PROGRAM_CSD (type=adtc)                                |
+----------------------------------------------------------------------------------+
```


### Block-Oriented Write-Protection Commands (class 6)

```
+-----------------------------------------------------------------------+
|       CMD28    sd/mmc spi SET_WRITE_PROT (type=ac)                    |
|       CMD29    sd/mmc spi CLR_WRITE_PROT (type=ac)                    |
|       CMD30    sd/mmc spi GET_WRITE_PROT (type=adtc)                  |
|       CMD31    -          SD: Reserved                                |
|       CMD31    mmc        MMC: SEND_WRITE_PROT_TYPE (type=adtc)       |
+-----------------------------------------------------------------------+
```


### Erase Commands (class 5)

```
+---------------------------------------------------------------------------------+
|       CMD32    sd     spi ERASE_WR_BLK_START (type=ac)                          |
|       CMD33    sd     spi ERASE_WR_BLK_END (type=ac)                            |
|       CMD32-34 mmc    spi Reserved for compatibility with older MMC cards (uh?) |
|       CMD35    mmc    spi ERASE_GROUP_START (type=ac)                           |
|       CMD36    mmc    spi ERASE_GROUP_END (type=ac)                             |
|       CMD37    mmc    spi Reserved for compatibility with older MMC cards (uh?) |
|       CMD38    sd/mmc spi ERASE (type=ac)                                       |
|       CMD39    -          Reserved                                              |
|       CMD41    -          Reserved                                              |
+---------------------------------------------------------------------------------+
```


### Lock Card (class 7)

```
+------------------------------------------------------------------------------------+
|       CMD16    sd/mmc spi SET_BLOCKLEN (type=ac)                                   |
|       CMD40    sd         Defined by DPS Spec (Data Protection System) (type=adtc) |
|       CMD42    sd/mmc spi LOCK_UNLOCK (type=adtc)                                  |
|       CMD43-47 -          Reserved                                                 |
|       CMD51    -          Reserved                                                 |
+------------------------------------------------------------------------------------+
```


### Application-Specific Commands (class 8)

```
+----------------------------------------------------------------------------+
|       CMD39-40 mmc        MMCA Optional Command, currently not supported   |
|       CMD55-56 mmc        MMCA Optional Command, currently not supported   |
|       CMD55    sd     spi APP_CMD (type=ac)    ;\also defined for MMC,     
|       CMD56    sd     spi GEN_CMD (type=adtc)  ;/but ONLY in SPI mode !!?? |
|       CMD60-63 sd/mmc spi Reserved for manufacturer                        |
+----------------------------------------------------------------------------+
```


### I/O Mode Commands (class 9) (Refer to \"SDIO Card Specification\")

```
+-----------------------------------------------------------------------+
|       CMD5     sdio   spi SDIO: IO_SEND_OP_COND                       |
|       CMD52    sdio   spi SDIO: IO_RW_DIRECT                          |
|       CMD53    sdio   spi SDIO: IO_RW_EXTENDED                        |
|       CMD54    -          SDIO: Reserved                              |
|       CMD39    mmcio      MMCIO: FAST_IO (type=ac)                    |
|       CMD40    mmcio      MMCIO: GO_IRQ_STATE (type=bcr)              |
+-----------------------------------------------------------------------+
```


### Switch Function Commands (class 10) (version 1.10+)

```
+--------------------------------------------------------------------------------+
|       CMD6     mmc    spi SWITCH      (type=ac)   ;related to EXT_CSD register |
|       CMD6     sd     spi SWITCH_FUNC (type=adtc)                              |
|       CMD34-37 sd+spi     Reserved for Command Systems from CMD6  ;\SPI        
|       CMD50,57 sd+spi     Reserved for Command Systems from CMD6  ;/           |
|       CMD34-35 sd         Reserved                                ;\           
|       CMD36-37 sd         Undoc (description field is held blank) ; Non-SPI    |
|       CMD50,57 sd         Undoc (description field is held blank) ;/           |
+--------------------------------------------------------------------------------+
```


### Function Extension Commands (class 11)

```
+-----------------------------------------------------------------------------------+
|       CMD21    sd         Reserved for DPS Specification (Data Protection System) |
|       CMD48    sd         READ_EXTR_SINGLE (type=adtc)                            |
|       CMD49    sd         WRITE_EXTR_SINGLE (type=adtc)                           |
|       CMD58    sd         READ_EXTR_MULTI (type=adtc)   ;SPI: READ_OCR            |
|       CMD59    sd         WRITE_EXTR_MULTI (type=adtc)  ;SPI: CRC_ON_OFF          |
+-----------------------------------------------------------------------------------+
```


### MMC Data Streaming Commands (class 1/class 3)

```
+-----------------------------------------------------------------------+
|       CMD11    mmc        READ_DAT_UNTIL_STOP (class 1) (type=adtc)   |
|       CMD20    mmc        WRITE_DAT_UNTIL_STOP (class 3) (type=adtc)  |
+-----------------------------------------------------------------------+
```


### Below CMD58-59 SPI-only (in Non-SPI mode: MMC=Reserved, SD=EXTR_MULTI)

```
+-----------------------------------------------------------------------------+
|       CMD58    sd/mmc+spi READ_OCR     ;SPI-only ;SD Mode: READ_EXTR_MULTI  |
|       CMD59    sd/mmc+spi CRC_ON_OFF   ;SPI-only ;SD Mode: WRITE_EXTR_MULTI |
+-----------------------------------------------------------------------------+
```

Above two commands are supported in SPI mode only, and are supported for both SD and MMC (though newer MMC docs are no longer mentioning them since JEDEC dropped SPI support).

### Application Specific Commands (prefixed by CMD55 aka APP_CMD)

```
+-----------------------------------------------------------------------------------+
|       ACMD6     sd        SET_BUS_WIDTH (type=ac)                                 |
|       ACMD13    sd    spi SD_STATUS (type=adtc) (get 512bit SSR)                  |
|       ACMD22    sd    spi GET_NUM_WR_BLOCKS (type=adtc)                           |
|       ACMD23    sd    spi SET_WR_BLK_ERASE_COUNT (type=ac)                        |
|       ACMD41    sd    spi SD_SEND_OP_COND (type=bcr)  ;SPI: reduced functionality |
|       ACMD42    sd    spi SET_CLR_CARD_DETECT (type=ac)                           |
|       ACMD51    sd    spi GET_SCR (type=adtc)                                     |
|       ACMD1-5   -         Reserved                                                |
|       ACMD7-12  -         Reserved                                                |
|       ACMD14-16 sd        Reserved for DPS Specification (Data Protection System) |
|       ACMD17    -         Reserved                                                |
|       ACMD18    sd    spi Reserved for SD security applications                   |
|       ACMD19-21 -         Reserved                                                |
|       ACMD24    -         Reserved                                                |
|       ACMD25    sd    spi Reserved for SD security applications                   |
|       ACMD26    sd    spi Reserved for SD security applications                   |
|       ACMD27    -         Shall not use this command                              |
|       ACMD28    sd        Reserved for DPS Specification (Data Protection System) |
|       ACMD29    -         Reserved                                                |
|       ACMD30-35 sd        Reserved for Security Specification                     |
|       ACMD36-37 -         Reserved                                                |
|       ACMD38    sd    spi Reserved for SD security applications                   |
|       ACMD39-40 -         Reserved                                                |
|       ACMD43-49 sd    spi Reserved for SD security applications                   |
|       ACMD52-54 sd        Reserved for Security Specification                     |
|       ACMD55    -         Not exist (equivalent to CMD55)                         |
|       ACMD56-59 sd        Reserved for Security Specification                     |
|       ACMD0     -         Unknown/Unused/Undocumented                             |
|       ACMD50    -         Unknown/Unused/Undocumented                             |
|       ACMD60-63 -         Unknown/Unused/Undocumented                             |
+-----------------------------------------------------------------------------------+
```


### Card Registers

```
+----------------------------------------------------------------------------------+
|       CSR       32bit  sd/mmc spi Card Status: command error & state information |
|       OCR       32bit  sd/mmc spi Operation Conditions Register                  |
|       CID      128bit  sd/mmc spi Card Identification                            |
|       CSD      128bit  sd/mmc spi Card-Specific Data (CSD Version 1.0 and 2.0)   |
|       RCA       16bit  sd/mmc     Relative Card Address (not used in SPI mode)   |
|       DSR       16bit  sd/mmc spi Driver Stage Register (optional)               |
|       SSR      512bit  sd     spi SD Card Status Register: Extended status field |
|       SCR       64bit  sd     spi SD Card Configuration Register                 |
|       EXT_CSD 4096bit  mmc    spi MMC Extended CSD Register (status & config)    |
|       PWD      128bit  sd/mmc spi Password (Card Lock) (max 16 bytes)            |
|       PWD_LEN    8bit  sd/mmc spi Password Length (0..16 max) (0=no password)    |
+----------------------------------------------------------------------------------+
```


### SD Mode Response Types

```
+------------------------------------------------------------------------------+
|       N/A    0bit  CMD0, CMD4, CMD15   No response                           |
|       R1    48bit  Normal CMDs/ACMDs   32bit CSR Card Status                 |
|       R1b   48bit  Busy CMDs/ACMDs     32bit CSR Card Status (and DATA=busy) |
|       R2   136bit  CMD9                120bit CSD Card-Specific Data         |
|       R2   136bit  CMD2, CMD10         120bit CID Card Identification        |
|       R3    48bit  ACMD41, MMC:CMD1    32bit OCR Register (without crc7)     |
|       R4        -  -                   Reserved for SDIO                     |
|       R5        -  -                   Reserved for SDIO                     |
|       R6    48bit  CMD3                16bit RCA and cut-down 16bit CSR      |
|       R7    48bit  CMD8                32bit Card interface condition        |
+------------------------------------------------------------------------------+
```


### SPI Mode Response Types

```
+------------------------------------------------------------------------------------+
|       R1     8bit  Normal CMDs/ACMDs   8bit CSR Card Status                        |
|       R1b    8bit  Busy CMDs/ACMDs     8bit CSR Card Status (and DATA=busy)        |
|       R2    16bit  CMD13, ACMD13       16bit CSR Card Status                       |
|       R3    40bit  CMD58               8bit CSR and 32bit OCR                      |
|       R4        -  -                   Reserved for SDIO                           |
|       R5        -  -                   Reserved for SDIO                           |
|       R6        -  -                   Reserved                                    |
|       R7    40bit  CMD8                8bit CSR and 32bit Card interface condition |
|       ERROR  8bit  Only first 8bit sent upon Illegal Command or Command CRC Error  |
+------------------------------------------------------------------------------------+
```


### Commands with Data Transfers (additionally to command/response) (type=adtc)

```
+------------------------------------------------------------------------------------+
|       CMD17,18 R   sd/mmc spi READ_SINGLE_BLOCK, READ_MULTIPLE_BLOCK               |
|       CMD24,25 W   sd/mmc spi WRITE_BLOCK, WRITE_MULTIPLE_BLOCK                    |
|       CMD8     R   mmc    spi GET_EXT_CSD (4096bit)                                |
|       CMD9     R   sd/mmc spi GET_CSD (128bit)  ;\in SPI Mode only (Non-SPI mode   
|       CMD10    R   sd/mmc spi GET_CID (128bit)  ;/sends that info as CMD response) |
|       ACMD13   R   sd     spi SD_STATUS (512bit SSR register)                      |
|       ACMD22   R   sd     spi GET_NUM_WR_BLOCKS (32bit counter)                    |
|       ACMD51   R   sd     spi GET_SCR (64bit SCR register)                         |
|       CMD14,19 R/W mmc        BUSTEST_R, BUSTEST_W                                 |
|       CMD19    W?  sd         SET_TUNING_BLOCK (512bit tuning pattern)             |
|       CMD27    W   sd/mmc spi PROGRAM_CSD (128bit CSD register)                    |
|       CMD30    R   sd/mmc spi GET_WRITE_PROT (32bit write-protect flags)           |
|       CMD31    R   mmc        GET_WRITE_PROT_TYPE (32x2bit write-protect types)    |
|       CMD42    W   sd/mmc spi LOCK_UNLOCK (password header/data)                   |
|       CMD6     ??  sd     spi SWITCH_FUNC                                          |
|       CMD40    ?   sd         Defined by DPS Spec (Data Protection System)         |
|       CMD48,49 R/W sd         READ_EXTR_SINGLE, WRITE_EXTR_SINGLE                  |
|       CMD58,59 R/W sd         READ_EXTR_MULTI, WRITE_EXTR_MULTI                    |
|       CMD56    R/W sd     spi GEN_CMD                                              |
|       CMD11    R   mmc        READ_DAT_UNTIL_STOP (class 1) (type=adtc)            |
|       CMD20    W   mmc        WRITE_DAT_UNTIL_STOP (class 3) (type=adtc)           |
|      xR1b      R   sd/mmc spi Busy signal for commands with "R1b" response         |
+------------------------------------------------------------------------------------+
```


### Misnamed Commands
Official command names include various SEND_xxx commands, which are misleading because they don\'t indicate if they \"send\" information \<to\> or \<from\> the card (or both). Better naming would be GET_xxx, SET_xxx, or GET_SET_xxx.

```
+-----------------------------------------------------------------------+
|       Official Name         Renamed                                   |
|       ALL_SEND_CID          ALL_GET_CID                               |
|       SEND_CID              GET_CID                                   |
|       SEND_CSD              GET_CSD                                   |
|       SEND_STATUS           GET_STATUS                                |
|       SEND_RELATIVE_ADDR    GET_RELATIVE_ADDR                         |
|       SEND_SCR              GET_SCR                                   |
|       SEND_EXT_CSD          GET_EXT_CSD                               |
|       SEND_WRITE_PROT       GET_WRITE_PROT                            |
|       SEND_WRITE_PROT_TYPE  GET_WRITE_PROT_TYPE                       |
|       SEND_NUM_WR_BLOCKS    GET_NUM_WR_BLOCKS                         |
|       SEND_IF_COND          SET_IF_COND             ;-to card         |
|       SEND_TUNING_BLOCK     SET_TUNING_BLOCK        ;-to card         |
|       SEND_OP_COND          ...                                       |
|       SD_SEND_OP_COND       ...                                       |
+-----------------------------------------------------------------------+
```

Other misnamed commands include SET_BLOCKLEN occassionally spelled SET_BLOCK_LEN in SD specs. SELECT_DESELECT_CARD is officially spelled SELECT/DESELECT_CARD.

### Difference of SD Commands Definition in UHS-II
SD-TRAN driver of host should manage the difference of SD commands functions. Not supported commands should not issue to UHS-II card. CMD13 shall not be issued during data transfer. Normally, data transfer should be stopped by setting TLEN instead of using CMD12.
CMD23 and CMD55 functions are included in UHS-II packet functions.

```
+-------------------------------------------------------------------------------------+
|      CMD0   Terminate SD transaction and reset SD-TRAN state.                       |
|      CMD3   Returns Device ID in the response instead of RCA                        |
|      CMD4   Illegal                                                                 |
|      CMD6   Function Group 1 and 3 are not used.                                    |
|      CMD7   Device ID is set to the argument instead of RCA                         |
|      CMD13  Device operation is up to implementation during data transfer (eg. CTS) |
|      CMD11  Illegal                                                                 |
|      CMD12  Normally, TLEN (data length) in UHS-II packet is used to stop data      |
|             transfer.                                                               |
|      CMD12  Should be used to abort an operation when illegal situation occurs.     |
|      CMD15  Illegal                                                                 |
|      CMD19  Illegal                                                                 |
|      CMD23  Not Affected. TLEN in UHS-II packet is used to specify data length.     |
|      CMD55  Not Affected. ACMD is set by APP field in UHS-II packet.                |
|      ACMD6  Illegal                                                                 |
|      ACMD42 Illegal                                                                 |
+-------------------------------------------------------------------------------------+
```

Not Affected means that the command is not executed in any card state, and response is returned (response type is up to implementation).
Illegal means that card returns response with NACK=1.
As SDHC/SDXC Cards do not support CMD28, 29 and 30, these commands are also illegal in UHS-II mode.

### Note
All future reserved commands shall have a codeword length of 48 bits, as well as their responses (if there are any).



