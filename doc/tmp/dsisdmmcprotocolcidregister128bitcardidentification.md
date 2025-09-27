# DSi SD/MMC Protocol: CID Register (128bit Card Identification)


### CMD2 - SD/MMC - ALL_GET_CID (type=bcr)
CMD2 is/was intended for multiple MMC cards on the same SD/MMC bus, the connected card(s) should compare the CMD2 response bits seen on the bus, and the card with the smallest CID number is switched to \"ident\" state (and any other cards stay in \"ready\" state until sending further CMD2\'s).
CMD2 is still required for both SD and MMC during initialization, although actually sharing the same bus for multiple cards is rather uncommon/depracted (and might envolve various problems: Like conflicting OCR responses, conflicting pull-ups on DAT3 pin, signal noise/spikes on insertion/removal of a second card while accessing another card, problems with (shared) Write Protect and Card Detect switches, and so on).
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

SD Mode Response: R2 (same 136bit response as for CMD10, see there)
Asks any card to send the CID numbers on the CMD line (any card that is connected to the host will respond - until it sees a \"0\" bit from another card while itself outputting a \"1\" bit).
Observe that CMD2 (and other card detection/initialization commands) should be done at lower CLK rate than usually (MMC specifies max 400kHz - this is actually required - the DSi\'s onboard Samsung KMAPF0000M-S998 eMMC chip won\'t respond to ALL_GET_CID when trying to use 16MHz CLK), higher CLK can be used once when detecting max speed (TRAN_SPEED in CSD register).

### CMD10 - SD/MMC - SPI - GET_CID (type=ac)
This command should be used for actually READING the CID (as opposed to ALL_GET_CID which is primarily intended for the connected card(s) to COMPARE their CIDs with each other).
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA (SPI Mode: stuff bits)                                |
|       15-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

SD Mode Response: R2:

```
+------------------------------------------------------------------------------+
|       135     Start Bit (0)                                 ;\               
|       134     Transmission To Host (0)                      ; 1st byte       |
|       133-128 Reserved (111111) (instead of Command value)  ;/               |
|       127-8   CID (120bit) (15 bytes)     ;\aka 128bit      ;-2nd..16th byte 
|       7-1     CRC7                        ; when including  ;\17th byte      
|       0       End Bit (1)                 ;/CRC7+EndBit     ;/               |
+------------------------------------------------------------------------------+
```

SPI Mode Response: R1, plus DATA line,
SPI Mode Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       127-0   CID (128bit) ... or 120bit ?                            |
+-----------------------------------------------------------------------+
```

Addressed card sends its card identification (CID).

### CID register
The Card IDentification (CID) register is 128 bits wide. It contains the card identification information used during the card identification phase. Every individual Read/Write (RW) card shall have a unique identification number.
For SD Cards (short product name, but bigger date field, 2000..2255?):

```
+----------------------------------------------------------------------------------+
|       Bit     Siz  Field  Name                                                   |
|       127-120   8  MID    Manufacturer ID    (binary) ;\assigned by SD-3C, LLC   
|       119-104  16  OID    OEM/Application ID (ASCII)  ;/                         |
|       103-64   40  PNM    Product name       (ASCII)                             |
|       63-56     8  PRV    Product revision   (BCD, 00h-99h) (eg 62h = rev 6.2)   |
|       55-24    32  PSN    Product serial number (32bit)                          |
|       23-20     4  -      Reserved (zero)                                        |
|       19-8     12  MDT    Manufacturing date (yymh) (m=1..12, yy=0..255?; +2000) |
|       7-1       7  CRC    CRC7 checksum                                          |
|       0         1  1      Stop bit (always 1)                                    |
+----------------------------------------------------------------------------------+
```

For MMC Cards (smaller date field, range 1997..2012 only):

```
+----------------------------------------------------------------------------------+
|       Bit     Siz  Field  Name                                                   |
|       127-120   8  MID    Manufacturer ID    (binary)   ;\assigned by MMCA       
|       119-104  16  OID    OEM/Application ID (binary)   ;/  ... or ...           |
|       127-120   8  MID    Manufacturer ID    (binary)   ;\assigned by MMCA/JEDEC 
|       119-114   6  -      Reserved (0)                  ;                        |
|       113-112   2  CBX    Device (0=Card, 1=BGA, 2=POP) ;                        |
|       119-104   8  OID    OEM/Application ID (binary)   ;/                       |
|       103-56   48  PNM    Product name       (ASCII)                             |
|       55-48     8  PRV    Product revision   (BCD, 00h-99h) (eg 62h = rev 6.2)   |
|       47-16    32  PSN    Product serial number (32bit)                          |
|       15-8      8  MDT    Manufacturing date (myh) (m=1..12, y=0..15; +1997)     |
|       7-1       7  CRC    CRC7 checksum                                          |
|       0         1  1      Stop bit (always 1)                                    |
+----------------------------------------------------------------------------------+
```


### Known CID\'s for DSi eMMC chips (excluding CRC in LSB, padded 00 in MSB)

```
+-------------------------------------------------------------------------------------+
|       MY ss ss ss ss 03 4D 30 30 46 50 41 00 00 15 00  ;DSi Samsung KMAPF0000M-S998 |
|       MY ss ss ss ss 32 57 37 31 36 35 4D 00 01 15 00  ;DSi Samsung KLM5617EFW-B301 |
|       MY ss ss ss ss 30 36 35 32 43 4D 4D 4E 01 FE 00  ;DSi ST NAND02GAH0LZC5 rev30 |
|       MY ss ss ss ss 31 36 35 32 43 4D 4D 4E 01 FE 00  ;DSi ST NAND02GAH0LZC5 rev31 |
|       MY ss ss ss ss 03 47 31 30 43 4D 4D 00 01 11 00  ;3DS whatever chiptype?      |
|       MY ss ss ss ss 07 43 59 31 47 34 4D 00 01 15 00  ;3DS Samsung KLM4G1YE0C-B301 |
+-------------------------------------------------------------------------------------+
```


See also:
- [DSi Console IDs](./dsiconsoleids.md)



