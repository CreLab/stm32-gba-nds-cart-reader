# DSi SDIO Card Information Structures (CIS)


The CIS used by SDIO is based directly upon the metaformat specification used by PCMCIA and Compact Flash. For details on the metaformat, refer to:

```
+-----------------------------------------------------------------------+
|       PC Card Standard, Volume 4, Metaformat Specification            |
+-----------------------------------------------------------------------+
```

Published by: PCMCIA (Personal Computer Memory Card International Association)

### Basic Format

```
+-----------------------------------------------------------------------+
|       00h           CISTPL_code                                       |
|       01h           Offset to next tuple (n) (aka size of body)       |
|       02h+(0..n-1)  Body (n bytes)                                    |
+-----------------------------------------------------------------------+
```


### Summary

```
+-----------------------------------------------------------------------+
|       00h = CISTPL_NULL          Null Tuple                           |
|       10h = CISTPL_CHECKSUM      Checksum Control                     |
|       15h = CISTPL_VERS_1        Level 1 Version/Product Information  |
|       16h = CISTPL_ALTSTR        Alternate Language String            |
|       20h = CISTPL_MANFID        Manufacturer ID                      |
|       21h = CISTPL_FUNCID        Function ID                          |
|       22h = CISTPL_FUNCE         Function Extensions                  |
|       80h-8Fh = Vendor specific  Vendor specific                      |
|       91h = CISTPL_SDIO_STD      Info for Standard SDIO Functions     |
|       92h = CISTPL_SDIO_EXT      Reserved for future SDIO stuff       |
|       FFh = CISTPL_END           End-of-chain                         |
+-----------------------------------------------------------------------+
```


### Tuple 00h - Null Tuple (meaningless, unknown purpose)

```
+-----------------------------------------------------------------------+
|       00h Tuple ID   (00h)                                            |
|       01h Tuple Size (00h)                                            |
+-----------------------------------------------------------------------+
```

Unspecified in SDIO reference\... but maybe defined in PCMIA specs?)

### Tuple 10h - Checksum Control

```
+-----------------------------------------------------------------------+
|       00h Tuple ID   (10h)                                            |
|       01h Tuple Size (?)                                              |
|       ... Unknown                                                     |
+-----------------------------------------------------------------------+
```

Unspecified in SDIO reference\... but maybe defined in PCMIA specs?)

### Tuple 15h - Level 1 Version/Product Information

```
+-----------------------------------------------------------------------+
|       00h Tuple ID   (15h)                                            |
|       01h Tuple Size (?)                                              |
|       ... Unknown                                                     |
+-----------------------------------------------------------------------+
```

Unspecified in SDIO reference\... but maybe defined in PCMIA specs?)


### Tuple 20h - Manufacturer ID

```
+-----------------------------------------------------------------------+
|       00h      Tuple ID   (20h)                                       |
|       01h      Tuple Size (at least 4)                                |
|       02h-03h  Manufacturer ID (assigned by JEIDA or PCMCIA)          |
|       04h-05h  Part Number/Revision (manufacturer specific)           |
+-----------------------------------------------------------------------+
```


### Tuple 21h - Function ID

```
+-----------------------------------------------------------------------+
|       00h      Tuple ID   (21h)                                       |
|       01h      Tuple Size (2)                                         |
|       02h      Card Function Code (0Ch for SDIO)                      |
|       03h      System initialization bit mask (Not used, 00h)         |
+-----------------------------------------------------------------------+
```


### Tuple 22h - Function Extension

```
+-----------------------------------------------------------------------+
|       00h      Tuple ID   (22h)                                       |
|       01h      Tuple Size (..)                                        |
|       02h      Type of extended data                                  |
|       03h..xxh Function information                                   |
+-----------------------------------------------------------------------+
```


### Tuple 22h - Function Extension, Type 00h, for Function 0

```
+-------------------------------------------------------------------------------------+
|       00h      Tuple ID   (22h)                                                     |
|       01h      Tuple Size (04h+2*N)                                                 |
|       02h      Type of extended data (00h=Type 00h)                                 |
|       03h-04h  Max Block Size for Function 0 (0001h or higher)                      |
|       05h      Max Transfer Speed for Function 0-7 (specified as Value*Unit bits/s) |
|                bit0-2: Unit  (0=0.1M, 1=1M, 2=10M, 3=100M, 4..7=Reserved)           |
|                bit3-6: Value (0=Reserved, 1=1, 2=1.2, 3=1.3, 4=1.5, 5=2, 6=2.5,     |
|                        7=3, 8=3.5, 9=4, 10=4.5, 11=5, 12=5.5, 13=6, 14=7, 15=8)     |
|                bit7:   Reserved                                                     |
|       06h...   N two-byte pairs (TC,CP) for 1..N   ;(N=([01h]-4)/2)                 |
+-------------------------------------------------------------------------------------+
```


### Tuple 22h - Function Extension, Type 01h, for Function 1-7

```
+------------------------------------------------------------------------------------+
|       00h      Tuple ID   (22h)                                                    |
|       01h      Tuple Size (2Ah)                                                    |
|       02h      Type of extended data (01h=Type 01h)                                |
|       03h      Function Info (bit0=WakeUpSupport, bit1..7=Reserved)                |
|       04h      Standard SDIO Function version (2x4bit maj.min, or 00h=Nonstandard) |
|       05h-08h  Card Product Serial Number PSN (32bit) (unique value, or 0=None)    |
|       09h-0Ch  CSA Size in bytes available for this Function (32bit)               |
|       0Dh      CSA Property (bit0=WriteProtected/ReadOnly, bit1=NoReformatting)    |
|       0Eh-0Fh  Max Block Size for this Function (0001h or higher)                  |
|       10h-13h  Operation Condition OCR (same as in ACMD41 for SD Memory devices)   |
|       14h-16h  3x8bit Operation Power (Min/Average/Max) (0..254mA, or 255=more)    |
|       17h-19h  3x8bit Standby Power   (Min/Average/Max) (0..254mA, or 255=more)    |
|       1Ah-1Dh  2x16bit Bandwidth      (Min/Optimal) (1..65535 KB/sec, or 0=None)   |
|       1Eh-1Fh  Timeout for Enable-till-Ready in 10ms units (max 655.35 seconds)    |
|       20h-23h  2x16bit Operation 3.3V         (Average/Max) (1..65535mA, or 0=?)   |
|       24h-25h  2x16bit High-Current-Mode 3.3V (Average/Max) (1..65535mA, or 0=?)   |
|       28h-2Bh  2x16bit Low-Current-Mode 3.3V  (Average/Max) (1..65535mA, or 0=?)   |
+------------------------------------------------------------------------------------+
```


### Tuple 22h - Function Extension, Type 02h, for Function 1-7 (Power State)

```
+--------------------------------------------------------------------------+
|       00h      Tuple ID   (22h)                                          |
|       01h      Tuple Size (02h+N*2) (N=1..15, for up to 15 power states) |
|       02h      Type of extended data (02h=Type 02h)                      |
|       03h      Fixed value (00h)                                         |
|       04h..xxh Nx16bit Max consumption in Power State 1..N (0..65535mW)  |
+--------------------------------------------------------------------------+
```


### Tuple 91h - SDIO_STD - Info about Standard SDIO Functions

```
+-------------------------------------------------------------------------------------+
|       00h      Tuple ID   (91h)                                                     |
|       01h      Tuple Size (02h..FFh)                                                |
|       02h      SDIO STD ID (the 4+8bit Interface Type in FBR, squeezed into 8bits?) |
|       03h      SDIO STD Type           ;\depends on Interface Type                  
|       04h...   SDIO STD Data (if any)  ;/                                           |
+-------------------------------------------------------------------------------------+
```


### Tuple 92h - SDIO_EXT

```
+-----------------------------------------------------------------------+
|       00h      Tuple ID   (92h)                                       |
|       01h      Tuple Size (?)                                         |
|       02h...   Reserved (if any)                                      |
+-----------------------------------------------------------------------+
```


### Tuple FFh - END

```
+-----------------------------------------------------------------------+
|       00h      Tuple ID   (FFh)                                       |
+-----------------------------------------------------------------------+
```

Indicates the end of tuple\'s list. Unlike all other tuple\'s, this is only a single FFh-byte (without \"Tuple Size\" entry).

01 CISTPL_DEVICE
14 CISTPL_NO_LINK
1A CISTPL_CONFIG
1B CISTPL_CFTABLE_ENTRY



