# DSi SD/MMC Protocol: SSR Register (512bit SD Status Register)


### ACMD13 - SD - SPI - SD_STATUS (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-0   stuff bits                                               |
+-----------------------------------------------------------------------+
```

SD Mode Response: R1 (32bit Card Status)
SPI Mode Response: R2 (16bit Card Status) (same as for CMD13, see there)
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       511-0  SSR Register (512bit)                                    |
+-----------------------------------------------------------------------+
```

Send the SD Status. The status fields are given in Table 4-43.

### SD Status (transferred on DATA line after ACMD13)
The size of the SD Status is one data block of 512 bit. The content of this register is transmitted to the Host over the DAT bus along with a 16-bit CRC.
ACMD13 can be sent to a card only in \'tran_state\' (card is selected).

```
+-------------------------------------------------------------------------------------+
|       Bits   Type Clr Identifier                                                    |
|       511-510  SR A   DAT_BUS_WIDTH (0..3, see below)                               |
|       509      SR A   SECURED_MODE  (0=Normal, 1=Secured) (Part 3 Security Specs)   |
|       508-502  -  -   Reserved for Security Functions     (Part 3 Security Specs)   |
|       501-496  -  -   Reserved                                                      |
|       495-480  SR A   SD_CARD_TYPE  (0..FFFFh, see below)                           |
|       479-448  SR A   SIZE_OF_PROTECTED_AREA   Size of protected area (see below)   |
|       447-440  SR A   SPEED_CLASS      Speed Class of the card (see below)          |
|       439-432  SR A   PERFORMANCE_MOVE Performance of move indicated by 1 MB/s step |
|       431-428  SR A   AU_SIZE          Size of AU (see below)                       |
|       427-424  -  -   Reserved                                                      |
|       423-408  SR A   ERASE_SIZE       Number of AUs to be erased at a time         |
|       407-402  SR A   ERASE_TIMEOUT    Timeout value for erasing areas              |
|                                        specified by UNIT_OF_ERASE_AU (see below)    |
|       401-400  SR A   ERASE_OFFSET     Fixed offset value added to erase time       |
|       399-396  SR A   UHS_SPEED_GRADE  Speed Grade for UHS mode  (see below)        |
|       395-392  SR A   UHS_AU_SIZE      Size of AU  for UHS mode  (see below)        |
|       391-312  -  -   Reserved                                                      |
|       311-0    -  -   Reserved for manufacturer                                     |
+-------------------------------------------------------------------------------------+
```


### Values for DAT_BUS_WIDTH (as set via SET_BUS_WIDTH command):

```
+-----------------------------------------------------------------------+
|       00h = 1 bit width (default)                                     |
|       01h = reserved                                                  |
|       02h = 4 bit width                                               |
|       03h = reserved                                                  |
+-----------------------------------------------------------------------+
```


### Values for SD_CARD_TYPE

```
+-----------------------------------------------------------------------------------+
|       0000h = Regular SD RD/WR Card                                               |
|       0001h = SD ROM Card                                                         |
|       0002h = OTP                                                                 |
|       0004h,0008h,0010h,0020h,0040h,0080h = Reserved for future variations        |
|       01xxh..FFxxh = Reserved for Cards that don't comply to Physical Layer Specs |
+-----------------------------------------------------------------------------------+
```


### Values for SIZE_OF_PROTECTED_AREA
Setting this field differs between SDSC and SDHC/SDXC.
In case of SDSC Card, the capacity of protected area is calculated as follows:

```
+--------------------------------------------------------------------------+
|       Protected Area = SIZE_OF_PROTECTED_AREA_* MULT * BLOCK_LEN.        |
|       SIZE_OF_PROTECTED_AREA is specified by the unit in MULT*BLOCK_LEN. |
+--------------------------------------------------------------------------+
```

In case of SDHC and SDXC Cards, the capacity of protected area is calculated as follows:

```
+-----------------------------------------------------------------------+
|       Protected Area = SIZE_OF_PROTECTED_AREA                         |
|       SIZE_OF_PROTECTED_AREA is specified by the unit in byte.        |
+-----------------------------------------------------------------------+
```


### Values for SPEED_CLASS
This 8-bit field indicates the Speed Class. Classes lower than indicated by this field are also effective.

```
+-----------------------------------------------------------------------+
|       00h      Speed Class 0                                          |
|       01h      Speed Class 2                                          |
|       02h      Speed Class 4                                          |
|       03h      Speed Class 6                                          |
|       04h      Speed Class 10                                         |
|       05h-FFh  Reserved for future/faster classes                     |
+-----------------------------------------------------------------------+
```

Application Note:
If a Class value indicated in SD Status (including reserved value) is larger than that of host supported, the host should read as any Class can be used with the card.
For example, Class 10 is indicated, host should consider Class 2 to 6 is also effective.

### Values for PERFORMANCE_MOVE
This 8-bit field indicates Pm and the value can be set by 1 \[MB/sec\] step.
If the card does not move used RUs, Pm should be considered as infinity.
Setting to FFh means infinity.
Pm is defined for Class 2 to 6 in Default Speed Mode. When host uses Class 10, Pm indicated in SD Status shall be ignored and treated as 0.

```
+-----------------------------------------------------------------------+
|       00h    Sequential Write                                         |
|       01h    1 [MB/sec]                                               |
|       02h    2 [MB/sec]                                               |
|       ...    ...                                                      |
|       FEh    254 [MB/sec]                                             |
|       FFh    Infinity                                                 |
+-----------------------------------------------------------------------+
```


### Values for AU_SIZE
This 4-bit field indicates AU Size and the value can be selected from 16 KB.

```
+-----------------------------------------------------------------------+
|       00h    Not Defined                                              |
|       01h    16 KB                                                    |
|       02h    32 KB                                                    |
|       03h    64 KB                                                    |
|       04h    128 KB                                                   |
|       05h    256 KB                                                   |
|       06h    512 KB                                                   |
|       07h    1 MB                                                     |
|       08h    2 MB                                                     |
|       09h    4 MB                                                     |
|       0Ah    8 MB                                                     |
|       0Bh    12 MB (!)                                                |
|       0Ch    16 MB                                                    |
|       0Dh    24 MB (!)                                                |
|       0Eh    32 MB                                                    |
|       0Fh    64 MB                                                    |
+-----------------------------------------------------------------------+
```

Maximum AU size (depending on card capacity):

```
+-------------------------------------------------------------------------------------+
|       Card Capacity     up to 64MB  up to 256MB  up to 512MB  up to 32GB  up to 2TB |
|       Maximum AU Size   512 KB      1 MB         2 MB         4 MB1       64MB      |
+-------------------------------------------------------------------------------------+
```

The card can set any AU size (up to above maximum AU size values).
The card should set smaller AU size as much as possible.
Application Notes:
The host should determine host buffer size based on total busy time of 4MB and the card supported class. The host can treat multiple AUs combined as one unit.

### Values for ERASE_SIZE
This 16-bit field indicates NERASE. When NERASE numbers of AUs are erased, the timeout value is specified by ERASE_TIMEOUT (Refer to ERASE_TIMEOUT).
The host should determine proper number of AUs to be erased in one operation so that the host can indicate progress of erase operation.

```
+-----------------------------------------------------------------------+
|       0000h    Erase Time-out Calculation is not supported.           |
|       0001h    1 AU                                                   |
|       0002h    2 AU                                                   |
|       0003h    3 AU                                                   |
|       ...      ...                                                    |
|       FFFFh    65535 AU                                               |
+-----------------------------------------------------------------------+
```


### Values for ERASE_TIMEOUT
This 6-bit field indicates the TERASE and the value indicates erase timeout from offset when multiple AUs are erased as specified by ERASE_SIZE. The range of ERASE_TIMEOUT can be defined as up to 63 seconds and the card manufacturer can choose any combination of ERASE_SIZE and ERASE_TIMEOUT depending on the implementation. Once ERASE_TIMEOUT is determined, it determines the ERASE_SIZE. The host can determine timeout for any number of AU erase by the Equation (6). Refer to 4.14 for the concept of calculating erase timeout. If ERASE_SIZE field is set to 0, this field shall be set to 0.

```
+-----------------------------------------------------------------------+
|       00h      Erase Time-out Calculation is not supported.           |
|       01h      1 [sec]                                                |
|       02h      2 [sec]                                                |
|       03h      3 [sec]                                                |
|       ...      ...                                                    |
|       3Fh      63 [sec]                                               |
+-----------------------------------------------------------------------+
```


### Values for ERASE_OFFSET
This 2-bit field indicates the TOFFSET and one of four values can be selected. The erase offset adjusts the line by moving in parallel on the upper side. Refer to Figure 4-57 and Equation (6) in 4.14. This field is meaningless if ERASE_SIZE and ERASE_TIMEOUT fields are set to 0.

```
+-----------------------------------------------------------------------+
|       00h      0 [sec]                                                |
|       01h      1 [sec]                                                |
|       02h      2 [sec]                                                |
|       03h      3 [sec]                                                |
+-----------------------------------------------------------------------+
```


### Values for UHS_SPEED_GRADE
This 4-bit field indicates the UHS mode Speed Grade. Reserved values are for future speed grades larger than the highest defined value. Host shall treat reserved values (undefined) as highest grade defined.

```
+-----------------------------------------------------------------------+
|       00h      Less than 10MB/sec                                     |
|       01h      10MB/sec and above                                     |
|       02h-0Fh  Reserved                                               |
+-----------------------------------------------------------------------+
```


### Values for UHS_AU_SIZE
This 4-bit field indicates AU Size for UHS-I and UHS-II cards. Card should set smaller value as much as possible. Host shall refer to UHS_AU_SIZE instead of AU_SIZE when the card is operating in UHS-I or UHS-II bus speed modes.

```
+-----------------------------------------------------------------------+
|       00h      Not Defined                                            |
|       01h-06h  Not Used                                               |
|       07h      1 MB                                                   |
|       08h      2 MB                                                   |
|       09h      4 MB                                                   |
|       0Ah      8 MB                                                   |
|       0Bh      12 MB (!)                                              |
|       0Ch      16 MB                                                  |
|       0Dh      24 MB (!)                                              |
|       0Eh      32 MB                                                  |
|       0Fh      64 MB                                                  |
+-----------------------------------------------------------------------+
```




