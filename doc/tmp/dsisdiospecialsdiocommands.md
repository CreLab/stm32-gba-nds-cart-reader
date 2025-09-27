# DSi SDIO Special SDIO Commands


### CMD52 - SDIO: IO_RW_DIRECT
Read/write single byte. Mostly used for detection/configuration via SDIO Function 0 commands.

```
+--------------------------------------------------------------------------+
|       31     R/W Flag               (0=Read, 1=Write)                    |
|       30-28  Function Number (3bit)                                      |
|       27     Read-after-write (RAW) Flag (if Bit31=1=Write, and Bit27=1) |
|       26     Stuff (unspecified, should be probably 0, but is 1 on DSi)  |
|       25-9   Register Address (17bit)                                    |
|       8      Stuff (unspecified, should be probably 0, but is 1 on DSi)  |
|       7-0    Write Data (8bit), or Stuff bits (for read)                 |
+--------------------------------------------------------------------------+
```

SD Mode Response: R5:

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-24   Stuff Bits                                    ;-2nd..3rd byte |
|       23-16   Response Flags                                ;-4th byte      |
|                7   COM_CRC_ERROR                                            |
|                6   ILLEGAL_COMMAND                                          |
|                5-4 IO_CURRENT STATE (0=dis, 1=cmd, 2=trn(cmd53), 3=rfu)     |
|                3   ERROR                                                    |
|                2   RFU (reserved for future use)                            |
|                1   INVALID_FUNCTION_NUMBER                                  |
|                0   OUT_OF_RANGE                                             |
|       15-8    Read or Write Data (8bit)                     ;-5th byte      |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```

SPI Mode Response: R5:

```
+-----------------------------------------------------------------------+
|       8bit  modified R1 response                                      |
|                7  start bit (0)                                       |
|                6  parameter error       (0=okay, 1=error)             |
|                5  RFU (0)                                             |
|                4  function number error (0=okay, 1=error)             |
|                3  COM CRC error         (0=okay, 1=error)             |
|                2  illegal command       (0=okay, 1=error)             |
|                1  RFU (0)                                             |
|                0  in idle state         (0=no, 1=idle)                |
|       8bit  Read or Write Data                                        |
+-----------------------------------------------------------------------+
```


### CMD53 - SDIO: IO_RW_EXTENDED
Mostly used for actual command/data transfers via SDIO Function 1 commands.

```
+-----------------------------------------------------------------------------------+
|       31     R/W Flag               (0=Read, 1=Write)                             |
|       30-28  Function Number (3bit) (0=CIA)                                       |
|       27     Block Mode             (0=Bytes, 1=Blocks/optional)                  |
|       26     OP Code                (0=Fixed Address, 1=Incrementing Address)     |
|       25-9   Register Address (17bit)                                             |
|       8-0    Byte/Block Count (9bit) (1..511) (0=512 Bytes, or 0=Infinite Blocks) |
+-----------------------------------------------------------------------------------+
```

Response: R5: Same as for CMD52 (with 8bit data = 00h)
Data Transfer:

```
+-------------------------------------------------------------------------------------+
|       For Byte Mode: Similar to CMD17/CMD24 (single block)                          |
|       For Block Mode: Similar to CMD18/CMD25 (multiple block)                       |
|       For Block Mode: CMD52:STOP_TRANSMISSION only needed if using "InfiniteBlocks" |
+-------------------------------------------------------------------------------------+
```


### CMD5 - SPI - SDIO: IO_SEND_OP_COND
Similar to SD Memory Card\'s ACMD41.

```
+-----------------------------------------------------------------------+
|       31-25  stuff bits (0)                                           |
|       24     Switching to 1.8V Request (S18R)                         |
|       23     I/O OCR VDD Voltage Window 3.5V-3.6V                     |
|       22     I/O OCR VDD Voltage Window 3.4V-3.5V                     |
|       21     I/O OCR VDD Voltage Window 3.3V-3.4V                     |
|       20     I/O OCR VDD Voltage Window 3.2V-3.3V                     |
|       19     I/O OCR VDD Voltage Window 3.1V-3.2V                     |
|       18     I/O OCR VDD Voltage Window 3.0V-3.1V                     |
|       17     I/O OCR VDD Voltage Window 2.9V-3.0V                     |
|       16     I/O OCR VDD Voltage Window 2.8V-2.9V                     |
|       15     I/O OCR VDD Voltage Window 2.7V-2.8V                     |
|       14     I/O OCR VDD Voltage Window 2.6V-2.7V                     |
|       13     I/O OCR VDD Voltage Window 2.5V-2.6V                     |
|       12     I/O OCR VDD Voltage Window 2.4V-2.5V                     |
|       11     I/O OCR VDD Voltage Window 2.3V-2.4V                     |
|       10     I/O OCR VDD Voltage Window 2.2V-2.3V                     |
|       9      I/O OCR VDD Voltage Window 2.1V-2.2V                     |
|       8      I/O OCR VDD Voltage Window 2.0V-2.1V                     |
|       7-4    I/O OCR VDD Voltage Window Reserved                      |
|       3-0    I/O OCR VDD Voltage Window Reserved                      |
+-----------------------------------------------------------------------+
```

SD Mode Response: R4:

```
+----------------------------------------------------------------------------+
|       47     Start Bit (0)                                 ;\              
|       46     Transmission To Host (0)                      ; 1st byte      |
|       45-40  Reserved (111111) (instead of Command value)  ;/              |
|       39     Card is ready to operate after init           ;\              
|       38-36  Number of I/O Functions                       ;               |
|       35     Memory Present                                ; 2nd byte      |
|       34-33  Stuff bits (0)                                ;               |
|       32     Switching to 1.8V Accepted (S18R) (not SPI)   ;/              |
|       31-8   I/O OCR (24bit)                               ;-3rd..5th byte |
|       7-1    Reserved (111111) (instead of CRC7)           ;\6th byte      
|       0      End Bit (1)                                   ;/              |
+----------------------------------------------------------------------------+
```

SPI Mode Response: R4:

```
+-----------------------------------------------------------------------+
|       8bit   modified R1 Response                                     |
|                7  start bit (0)                                       |
|                6  parameter error       (0=okay, 1=error)             |
|                5  RFU (0)                                             |
|                4  function number error (0=okay, 1=error)             |
|                3  COM CRC error         (0=okay, 1=error)             |
|                2  illegal command       (0=okay, 1=error)             |
|                1  RFU (0)                                             |
|                0  in idle state         (0=no, 1=idle)                |
|       32bit  same as SD Response bit39-8 (but without S18R bit)       |
+-----------------------------------------------------------------------+
```


### DSi SDIO Wifi Init
Related required registers/bits are:

```
+-------------------------------------------------------------------------------------+
|      - SCFG_EXT7.bit19 needed for SDIO controller (else 4004Axxh-4004Bxxh disabled) |
|      - SCFG_CLK7 seems to be NOT needed for SDIO clock enable (unlike SDMMC)        |
|      - SCFG_WL.bit0 seems to be wifi-related (but effect is unknown)                |
|      - GPIO_WIFI.bit8 needed for AR6013G chips (else SDIO Function 1 fails)         |
|      - BPTWL[30h] needed for LED and SDIO (else SDIO fails badly)                   |
|      - RTC.FOUT pin as configured by firmware (else WMI commands/events fail)       |
+-------------------------------------------------------------------------------------+
```

DSi init sequence is trying to send one CMD52 command first; if that fails, then the DSi is sending several CMD5\'s, followed by CMD3+CMD7.

### SDIO State

```
+-----------------------------------------------------------------------+
|       Command                 ini  stb  cmd  trn  ina                 |
|       CMD3  SET_RELATIVE_ADDR stb  ok   ---  ---  ---                 |
|       CMD5  IO_SEND_OP_COND   ok   ---  ---  ---  ---                 |
|              ocr bad          ina  ---  ---  ---  ---                 |
|       CMD7  SELECT_CARD       ---  cmd  ok   ---  ---                 |
|             DESELECT_CARD     ---  ok   stb  ---  ---                 |
|       CMD15 GO_INACTIVE_STATE ina  ina  ina  ---  ---                 |
|       CMD52 IO_RW_DIRECT      ---  ---  ok   (cmd)---                 |
|       CMD53 IO_RW_EXTENDED    ---  ---  trn  ---  ---                 |
+-----------------------------------------------------------------------+
```

Note: In CMD52, state \"dis\" can mean state \"ini\",\"stb\",\"ina\" (though, theoretically CMD52 cannot be used in that states, so one should never see the \"dis\" state at all).

### More SD commands that are (occassionally) used for SDIO

```
+------------------------------------------------------------------------------------+
|       CMD0  GO_IDLE_STATE     for entering SPI mode only (but does NOT reset SDIO) |
|       CMD8  SEND_IF_COND      optional for SDHC/SDXC                               |
|       CMD11 VOLTAGE_SWITCH    optional for UHS-I                                   |
|       CMD19 SEND_TUNING_BLOCK optional for UHS-I                                   |
|       CMD59 CRC_ON_OFF        spi-only                                             |
+------------------------------------------------------------------------------------+
```

Moreover a combo card (a SDIO device with built-in SD memory card) may implement various SD commands; these commands will affect only the SD memory card side, not the SDIO device).
SDIO doesn\'t have CID or CSD registers, nor commands for STOP_TRANSMISSION, SET_BUSWIDTH, or SET_BLOCKLEN (but CMD52 can do equivalent stuff via SDIO Function 0 registers).


```
+------------------------------------------------------------------------------------+
|      ____________________________ I/O Commands for MMC____________________________ |
+------------------------------------------------------------------------------------+
```


### CMD39 - MMCIO: FAST_IO (type=ac)

```
+-----------------------------------------------------------------------+
|       31-16  RCA                                                      |
|       15     Register Write Flag                                      |
|       14-8   Register Address                                         |
|       7-0    Register Data                                            |
+-----------------------------------------------------------------------+
```

MMC Response: R4:

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-24   RCA                                           ;-2nd..3rd byte |
|       23      Status (0=Bad, 1=Successful)                  ;\4th byte      
|       22-16   Register Address                              ;/              |
|       15-8    Read Register Contents                        ;-5th byte      |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```


### CMD40 - MMCIO: GO_IRQ_STATE (type=bcr)

```
+-----------------------------------------------------------------------+
|       31-0   Stuff Bits                                               |
+-----------------------------------------------------------------------+
```

MMC Response: R5:

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-24   RCA                                           ;-2nd..3rd byte |
|       23-8    Not defined (may be used for IRQ data)        ;-4th..5th byte |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```




