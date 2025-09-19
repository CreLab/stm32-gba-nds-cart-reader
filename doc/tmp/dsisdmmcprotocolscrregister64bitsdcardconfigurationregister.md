# DSi SD/MMC Protocol: SCR Register (64bit SD Card Configuration Register)


### ACMD51 - SD - SPI - GET_SCR (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       63-0  SCR Register (8bytes, aka 64bit)                          |
+-----------------------------------------------------------------------+
```


### SD Configuration Register (SCR)
In addition to the CSD register, there is another configuration register named SD CARD Configuration Register (SCR). SCR provides information on the SD Memory Card\'s special features that were configured into the given card. The size of SCR register is 64 bits. This register shall be set in the factory by the SD Memory Card manufacturer.

```
+-------------------------------------------------------------------------------------+
|       Bit  Siz  Typ Description                      Field                 ;common  |
|       63-60  4  R   SCR Structure                    SCR_STRUCTURE         ;\00h or 
|       59-56  4  R   SD Memory Card - Spec. Version   SD_SPEC               ;/01h    |
|       55     1  R   data_status_after erases         DATA_STAT_AFTER_ERASE ;\       
|       54-52  3  R   CPRM Security Support            SD_SECURITY           ; A5h    |
|       51-48  4  R   DAT Bus widths supported         SD_BUS_WIDTHS         ;/       |
|       47     1  R   Spec. Version 3.00 or higher     SD_SPEC3              ;\       
|       46-43  4  R   Extended Security Support        EX_SECURITY           ; 0000h  |
|       42     1  R   Spec. Version 4.00 or higher     SD_SPEC4              ;        |
|       41-36  6  R   Reserved                         -                     ;        |
|       35-32  4  R   Command Support bits             CMD_SUPPORT           ;/       |
|       31-0  32  R   reserved for manufacturer usage  -                     ;-var    |
+-------------------------------------------------------------------------------------+
```


### SCR Register Structure Version

```
+-------------------------------------------------------------------------------------+
|       SCR_STRUCTURE  SCR Structure Version  SD Physical Layer Specification Version |
|       00h            SCR version 1.0        Version 1.01-4.00                       |
|       01h..0Fh       reserved                                                       |
+-------------------------------------------------------------------------------------+
```

Note: SD_SPEC is used to indicate SCR Structure Version instead of this field.

### SD_SPEC, SD_SPEC3, SD_SPEC4
The Physical Layer Specification Version is indicated in combination with SD_SPEC, SD_SPEC3 and SD_SPEC4 as described Table 5-19.

```
+---------------------------------------------------------------------------------+
|       SD_SPEC  SD_SPEC3  SD_SPEC4   Physical Layer Specification Version Number |
|       0        0         0          Version 1.0 and 1.01                        |
|       1        0         0          Version 1.10                                |
|       2        0         0          Version 2.00                                |
|       2        1         0          Version 3.0X                                |
|       2        1         1          Version 4.XX                                |
|              Others                 Reserved                                    |
+---------------------------------------------------------------------------------+
```

\(1\) Version 2.00 hosts do not recognize SD_SPEC3 and SD_SPEC4.
(2) Version 3.00 hosts do not recognize SD_SPEC4.
Hosts recognize Physical Layer Specification Version shall also recognize including future version. Next version will be defined in SD_SPEC field.

The card manufacturer determines SD_SPEC value by conditions indicated below. All conditions shall be satisfied for each version. The other combination of conditions is not allowed.

Essential conditions to indicate Version 1.01 Card (SD_SPEC=0, SD_SPEC3=0 and SD_SPEC4=0):

```
+-----------------------------------------------------------------------+
|       (1) The card does not support CMD6                              |
|       (2) The card does not support CMD8                              |
|       (3) User area capacity shall be up to 2GB                       |
+-----------------------------------------------------------------------+
```

Essential conditions to indicate Version 1.10 Card (SD_SPEC=1, SD_SPEC3=0 and SD_SPEC4=0):

```
+-----------------------------------------------------------------------+
|       (1) The card shall support CMD6                                 |
|       (2) The card does not support CMD8                              |
|       (3) User area capacity shall be up to 2GB                       |
+-----------------------------------------------------------------------+
```

Essential conditions to indicate Version 2.00 Card (SD_SPEC=2, SD_SPEC3=0 and SD_SPEC4=0):

```
+-----------------------------------------------------------------------+
|       (1) The card shall support CMD6                                 |
|       (2) The card shall support CMD8                                 |
|       (3) The card shall support CMD42                                |
|       (4) User area capacity shall be up to 2GB (SDSC) or 32GB (SDHC) |
|       (5) Speed Class shall be supported (SDHC)                       |
+-----------------------------------------------------------------------+
```

Essential conditions to indicate Version 3.00 Card (SD_SPEC=2, SD_SPEC3=1 and SD_SPEC4=0):

```
+-------------------------------------------------------------------------------------+
|       (1) The card shall support CMD6                                               |
|       (2) The card shall support CMD8                                               |
|       (3) The card shall support CMD42                                              |
|       (4) User area capacity shall be up to 2GB (SDSC) or 32GB (SDHC)               |
|         User area capacity shall be more than or equal to 32GB and up to 2TB (SDXC) |
|       (5) Speed Class shall be supported (SDHC or SDXC)                             |
+-------------------------------------------------------------------------------------+
```

Optional conditions to indicate Version 3.00 Card:

```
+------------------------------------------------------------------------------+
|       A card supports any of following functions shall satisfy essential     |
|       conditions of Version 3.00 Card                                        |
|       (1) Speed Class supported under the conditions defined in Version 3.00 |
|       (2) UHS-I supported card                                               |
|       (3) CMD23 supported card                                               |
+------------------------------------------------------------------------------+
```

Essential conditions to indicate Version 4.XX Card (SD_SPEC=2, SD_SPEC3=1 and SD_SPEC4=1):

```
+------------------------------------------------------------------------+
|       (1) Same as the essential conditions of Version 3.00 device      |
|       (2) Support any of additional functions defined by Version 4.XX: |
|           Followings functions (a) to (c) are defined by Version 4.00. |
|             (a) Support of CMD48 and CMD49                             |
|             (b) Support of UHS-II mode                                 |
|             (c) Support of DPS (Data Protection System)                |
|           Followings functions (d) to (f) are defined by Version 4.10. |
|             (d) Support of CMD58 and CMD59                             |
|             (e) Support of Power Management Functions                  |
|             (f) Support of Speed Grade 1 for UHS-II mode               |
+------------------------------------------------------------------------+
```

The requirements of supporting commands mentioned above are for the optional commands, the support of which depends on versions (SD_SPEC, SD_SPEC3 and SD_SPEC4). Refer to Table 4-21 (and Notes below the table) about the mandatory and optional commands in the card.

### DATA_STAT_AFTER_ERASE
Defines the data status after erase, whether it is 0 or 1 (the status is card vendor dependent).

### SD_SECURITY
This field indicates CPRM Security Specification Version for each capacity card. The definition of Protected Area is different in each capacity card.

```
+-----------------------------------------------------------------------+
|       00h           No Security                                       |
|       01h           Not Used                                          |
|       02h           SDSC Card (CPRM Security Version 1.01)            |
|       03h           SDHC Card (CPRM Security Version 2.00)            |
|       04h           SDXC Card (CPRM Security Version 3.xx)            |
|       05h-07h       Reserved                                          |
+-----------------------------------------------------------------------+
```

The basic rule of setting this field:

```
+-----------------------------------------------------------------------+
|       SDSC Card sets this field to 2 (Version 1.01).                  |
|       SDHC Card sets this field to 3 (Version 2.00).                  |
|       SDXC Card sets this field to 4 (Version 3.xx).                  |
+-----------------------------------------------------------------------+
```

Note that it is mandatory for a regular writable SD Memory Card to support Security Protocol. For ROM (Read Only) and OTP (One Time Programmable) types of the SD Memory Card, the security feature is optional.

### SD_BUS_WIDTHS
Describes all the DAT bus widths that are supported by this card.

```
+-----------------------------------------------------------------------+
|       Bit 3          Reserved                                         |
|       Bit 2          4 bit (DAT0-3)                                   |
|       Bit 1          Reserved                                         |
|       Bit 0          1 bit (DAT0)                                     |
+-----------------------------------------------------------------------+
```

Since the SD Memory Card shall support at least the two bus modes 1-bit or 4-bit width, then any SD Card shall set at least bits 0 and 2 (SD_BUS_WIDTH=\"0101\").

### EX_SECURITY
This field indicates Extended Security which is defined by the Part A4 Data Protection System Specification Version 1.00 or will be defined by a later version of the Part 3 Security Specification Version 3.00.

```
+----------------------------------------------------------------------------------+
|       00h          Extended Security is not supported.                           |
|       01h..0Fh     Extended Security is supported. SCR[44-43] is defined by the  |
|                      Part A4 Data Protection System Specification. SCR[46-45] is |
|                      reserved for future extension.                              |
+----------------------------------------------------------------------------------+
```


### CMD_SUPPORT
Support bit of new commands are defined to Bit 33-32 (uh, 35-32?) of SCR.

```
+-----------------------------------------------------------------------------------+
|       Bit Supported Command               Command  CCC  Remark                    |
|       35  Extension Register Multi-Block  CMD58/59 11   Optional.                 |
|       34  Extension Register Single Block CMD48/49 11   Optional.                 |
|       33  Set Block Count                 CMD23    2,4  Mandatory for UHS104 card |
|       32  Speed Class Control             CMD20    2,4  Mandatory for SDXC card   |
+-----------------------------------------------------------------------------------+
```

If CMD58/59 is supported, then CMD48/49 shall be also supported.



