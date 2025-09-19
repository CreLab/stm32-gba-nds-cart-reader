# DSi SD/MMC Protocol: EXT_CSD Register (4096bit Extended CSD Register) (MMC)


### CMD8 - MMC - SPI - GET_EXT_CSD (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       4095-0  EXT_CSD Register (4096bit)                              |
+-----------------------------------------------------------------------+
```

MMC only.

### CMD6 - MMC - SPI - SWITCH (type=ac)

```
+------------------------------------------------------------------------------------+
|       31-26  6bit  Reserved (0)                                                    |
|       25-24  2bit  Access                                                          |
|                      00h  Change Command Set (EXT_CSD[191] = parameter bit2-0)     |
|                      01h  Set bits (EXT_CSD[index] = EXT_CSD[index] OR value)      |
|                      02h  Clr bits (EXT_CSD[index] = EXT_CSD[index] AND NOT value) |
|                      03h  Write    (EXT_CSD[index] = value)                        |
|       23-16  8bit  Index (0..191)   ;\used only if "Access=1..3"                   
|       15-8   8bit  Value (0..255)   ;/                                             |
|       7-3    5bit  Reserved (0)                                                    |
|       2-0    3bit  Cmd Set (0..7)   ;-used only if "Access=0"                      |
+------------------------------------------------------------------------------------+
```

Response: R1b
Additional Data Transfer (from card): Busy signal for \"R1b\" response
MMC only.

### Extended CSD Register (MMC only)
The Extended CSD register defines the card properties and selected modes. It is 512 bytes (4096 bits) long.
The most significant 320 bytes are the Properties segment, which defines the card capabilities and cannot be modified by the host. The lower 192 bytes are the Modes segment, which defines the configuration the card is working in. These modes can be changed by the host by means of the SWITCH command.

```
+-------------------------------------------------------------------------------------+
|       Properties Segment                                                            |
|       Byte    Siz  Type  Name                                  Field                |
|       511-505   7  -     Reserved(1)                           -                    |
|       504       1  R     Supported Command Sets                S_CMD_SET            |
|       503-216 288  -     Reserved(1)                           -                    |
|       215-212   4  R     moviNAND only: Sector Count           SEC_COUNT            |
|       211       1  -     Reserved                              -                    |
|       210       1  R     Min Write Performance for 8bit @52MHz MIN_PERF_W_8_52      |
|       209       1  R     Min Read Performance for 8bit @52MHz  MIN_PERF_R_8_52      |
|       208       1  R     Min Write Perf. for 8/4bit @26/52MHz  MIN_PERF_W_8_26_4_52 |
|       207       1  R     Min Read Perf. for 8/4bit @26/52MHz   MIN_PERF_R_8_26_4_52 |
|       206       1  R     Min Write Performance for 4bit @26MHz MIN_PERF_W_4_26      |
|       205       1  R     Min Read Performance for 4bit @26MHz  MIN_PERF_R_4_26      |
|       204       1  -     Reserved(1)                           -                    |
|       203       1  R     Power Class for 26MHz @ 3.6V          PWR_CL_26_360        |
|       202       1  R     Power Class for 52MHz @ 3.6V          PWR_CL_52_360        |
|       201       1  R     Power Class for 26MHz @ 1.95V         PWR_CL_26_195        |
|       200       1  R     Power Class for 52MHz @ 1.95V         PWR_CL_52_195        |
|       199-197   3  -     Reserved(1)                           -                    |
|       196       1  R     Card Type                             CARD_TYPE            |
|       195       1  -     Reserved(1)                           -                    |
|       194       1  R     CSD Structure Version                 CSD_STRUCTURE        |
|       193       1  -     Reserved(1)                           -                    |
|       192 C0h   1  R     Extended CSD Revision                 EXT_CSD_REV          |
|       Modes Segment                                                                 |
|       191 BFh   1  R/W   Command Set                           CMD_SET              |
|       190 BEh   1  -     Reserved(1)                           -                    |
|       189 BDh   1  RO    Command Set Revision                  CMD_SET_REV          |
|       188 BCh   1  -     Reserved(1)                           -                    |
|       187 BBh   1  R/W   Power Class                           POWER_CLASS          |
|       186 BAh   1  -     Reserved(1)                           -                    |
|       185 B9h   1  R/W   High Speed Interface Timing           HS_TIMING            |
|       184 B8h   1  -     Reserved(1)                           -                    |
|       183 B7h   1  WO    Bus Width Mode                        BUS_WIDTH            |
|       182 B6h      ?     ?                                                          |
|       181 B5h   1  -     Reserved                              -                    |
|       180 B4h   1  RO    moviNAND only: Erased Memory Content  ERASED_MEM_CONT      |
|       180-0   181  -     Reserved(a)                           -                    |
+-------------------------------------------------------------------------------------+
```

\(a\) Reserved(a) bits should read as \'0\'.
(1) Reserved(1) bits should be probably ZERO, too.
The above table is transferred \"most significant first\", which does probably mean that it starts with BYTE 0, not with byte 511. ALTHOUGH, the 4-byte SEC_COUNT appears to be LITTLE-ENDIAN?
Note: JEDEC Standard No. 84-A44 contains MANY additional fields in EXT_CSD.

### S_CMD_SET
This field defines which command sets are supported by the card.

```
+-----------------------------------------------------------------------+
|       Bit   Command Set                                               |
|       7-5   Reserved                                                  |
|       4     moviNAND only: ATA on MMC                                 |
|       3     moviNAND only: SecureMCC 2.0                              |
|       2     Content Protection SecureMMC                              |
|       1     SecureMMC                                                 |
|       0     Standard MMC                                              |
+-----------------------------------------------------------------------+
```


### SEC_COUNT (moviNAND and newer JEDEC specs only)
The device density is calculated from the register by multiplying the value of the register (sector count) by 512B/sector. The maximum density possible to be indicated is thus 2 Tera bytes (minus 512 bytes) (4,294,967,295 x 512B). The least significant byte (LSB) of the sector count value is the byte \[212\].

### MIN_PERF_a_b_ff
These fields defines the overall minimum performance value for the read and write access with different bus width and max clock frequency modes. The value in the register is coded as follows. Other than defined values are illegal.

```
+------------------------------------------------------------------------------------+
|       Value Performance                                                            |
|       0x00  For Cards not reaching the 2.4MB/s minimum value                       |
|       0x08  Class A: 2.4MB/s and is the lowest allowed value for MMCplus and       |
|              MMCmobile(16x150kB/s)                                                 |
|       0x0A  Class B: 3.0MB/s and is the next allowed value (20x150kB/s)            |
|       0x0F  Class C: 4.5MB/s and is the next allowed value (30x150kB/s)            |
|       0x14  Class D: 6.0MB/s and is the next allowed value (40x150kB/s)            |
|       0x1E  Class E: 9.0MB/s and is the next allowed value (60x150kB/s)            |
|              This is also the highest class which any MMCplus or MMCmobile card    |
|              is needed to support in low bus category operation mode (26MHz with   |
|              4bit data bus).                                                       |
|              A MMCplus or MMCmobile card supporting any higher class than this     |
|              have to support this class also (in low category bus operation mode). |
|       0x28  Class F: Equals 12.0MB/s and is the next allowed value (80x150kB/s)    |
|       0x32  Class G: Equals 15.0MB/s and is the next allowed value (100x150kB/s)   |
|       0x3C  Class H: Equals 18.0MB/s and is the next allowed value (120x150kB/s)   |
|       0x46  Class J: Equals 21.0MB/s and is the next allowed value (140x150kB/s)   |
|              This is also the highest class which any MMCplus or MMCmobile card    |
|              is needed to support in mid bus category operation mode (26MHz with   |
|              8bit data bus or 52MHz with 4bit data bus).                           |
|              A MMCplus or MMCmobile card supporting any higher class than this     |
|              have to support this Class (in mid category bus operation mode) and   |
|              Class E also (in low category bus operation mode).                    |
|       0x50  Class K: Equals 24.0MB/s and is the next allowed value (160x150kB/s)   |
|       0x64  Class M: Equals 30.0MB/s and is the next allowed value (200x150kB/s)   |
|       0x78  Class O: Equals 36.0MB/s and is the next allowed value (240x150kB/s)   |
|       0x8C  Class R: Equals 42.0MB/s and is the next allowed value (280x150kB/s)   |
|       0xA0  Class T: Equals 48.0MB/s and is the last defined value (320x150kB/s)   |
+------------------------------------------------------------------------------------+
```


### PWR_CL_ff_vvv
These fields define the supported power classes by the card. By default, the card has to operate at maximum frequency using 1 bit bus configuration, within the default max current consumption, as stated in the table below. If 4 bit/8 bits bus configurations, require increased current consumption, it has to be stated in these registers.
By reading these registers the host can determine the power consumption of the card in different bus modes. Bits \[7:4\] code the current consumption for the 8 bit bus configuration. Bits \[3:0\] code the current consumption for the 4 bit bus configuration.
The PWR_52_vvv registers are not defined for 26MHz MultiMediaCards.

```
+---------------------------------------------------------------------------------+
|       Voltage Value Max RMS Current   Max Peak Current   Remarks                |
|       3.6V    0     100 mA            200 mA             Default current        |
|               1     120 mA            220 mA             consumption for        |
|               2     150 mA            250 mA             high voltage cards     |
|               3     180 mA            280 mA                                    |
|               4     200 mA            300 mA                                    |
|               5     220 mA            320 mA                                    |
|               6     250 mA            350 mA                                    |
|               7     300 mA            400 mA                                    |
|               8     350 mA            450 mA                                    |
|               9     400 mA            500 mA                                    |
|               10    450 mA            550 mA                                    |
|               11-15 Reserved for future use                                     |
|       1.95V   0     65 mA             130 mA             Default current        |
|               1     70 mA             140 mA             consumption for        |
|               2     80 mA             160 mA             Dual voltage cards     |
|               3     90 mA             180 mA             (if any, not moviNAND) |
|               4     100 mA            200 mA                                    |
|               5     120 mA            220 mA                                    |
|               6     140 mA            240 mA                                    |
|               7     160 mA            260 mA                                    |
|               8     180 mA            280 mA                                    |
|               9     200 mA            300 mA                                    |
|               10    250 mA            350 mA                                    |
|               6-15  Reserved for future use                                     |
+---------------------------------------------------------------------------------+
```

The measurement for max RMS current is done as average RMS current consumption over a period of 100ms.
Max peak current is defined as absolute max value not to be exceeded at all.
The conditions under which the power classes are defined are:

```
+-----------------------------------------------------------------------+
|       - Maximum bus frequency                                         |
|       - Maximum operating voltage                                     |
|       - Worst case functional operation                               |
|       - Worst case environmental parameters (temperature,...)         |
+-----------------------------------------------------------------------+
```

These registers define the maximum power consumption for any protocol operation in data transfer mode, Ready state and Identification state.

### CARD_TYPE
This field defines the type of the card. The only currently valid values for this field are 0x01 and 0x03.

```
+-----------------------------------------------------------------------+
|       Bit Card Type                                                   |
|       7-2 Reserved                                                    |
|       1   High Speed MultiMediaCard @ 52MHz                           |
|       0   High Speed MultiMediaCard @ 26MHz                           |
+-----------------------------------------------------------------------+
```


### CSD_STRUCTURE
This field is a continuation of the CSD_STRUCTURE field in the CSD register.

```
+------------------------------------------------------------------------------------+
|       CSD_STRUCTURE CSD structure version   Valid for System Specification Version |
|       0             CSD version No. 1.0     Version 1.0 - 1.2                      |
|       1             CSD version No. 1.1     Version 1.4 - 2.2                      |
|       2             CSD version No. 1.2     Version 3.1-3.2-3.31-4.0-4.1-4.2       |
|       3             Reserved for future use                                        |
|       4-255         Reserved for future use                                        |
+------------------------------------------------------------------------------------+
```


### EXT_CSD_REV
Defines the fixed parameters. related to the EXT_CSD, according to its revision.

```
+-----------------------------------------------------------------------+
|       EXT_CSD_REV   Extended CSD Revision                             |
|       0             Revision 1.0                                      |
|       1             Revision 1.1                                      |
|       2             Revision 1.2 (moviNAND)                           |
|       3-255         Reserved                                          |
+-----------------------------------------------------------------------+
```


### CMD_SET
Contains the binary code of the command set that is currently active in the card. It is set to \'0\' (Standard MMC) after power up and can be changed by a SWITCH command.

### CMD_SET_REV
Contains a binary number reflecting the revision of the currently active command set. For Standard MMC command set it is:

```
+-----------------------------------------------------------------------+
|       Code    MMC Revisions                                           |
|       0       v4.0                                                    |
|       1-255   Reserved                                                |
+-----------------------------------------------------------------------+
```

This field, though in the Modes segment of the EXT_CSD, is read only.

### POWER_CLASS
This field contains the 4 bit value of the selected power class for the card. The power classes are defined in Table. The host should be responsible of properly writing this field with the maximum power class it allows the card to use. The card uses this information to, internally, manage the power budget and deliver an optimized performance.
This field is 0 after power-on or software reset.

```
+-----------------------------------------------------------------------+
|       Bits    Description                                             |
|       7-4     Reserved                                                |
|       3-0     Card power class code (See Table 5-29)                  |
+-----------------------------------------------------------------------+
```


### HS_TIMING
This field is 0 after power-on, or software reset, thus selecting the backwards compatibility interface timing for the card. If the host writes 1 to this field, the card changes its timing to high speed interface timing (refer to Chapter 5.4.8).

### BUS_WIDTH
It is set to \'0\' (1 bit data bus) after power up and can be changed by a SWITCH command.

```
+--------------------------------------------------------------------------------+
|       Value   Bus Mode                                                         |
|       0       1 bit data bus (MMC, with old 7pin connector)                    |
|       1       4 bit data bus (MMCplus, with SD-card-compatible 9pin connector) |
|       2       8 bit data bus (MMCplus, with special 13pin connector)           |
|       3-255   Reserved                                                         |
+--------------------------------------------------------------------------------+
```

For detecting cards with 4bit/8bit data bus support: Switch the SD/MMC controller to 4bit/8bit modes, and use BUSTEST_W and BUSTEST_R to test if the card sends a proper response, see <https://www.mikrocontroller.net/attachment/101561/AN_MMCA050419.pdf>
Note: The SD/MMC controller in the DSi supports 1bit/4bit modes only (no 8bit mode). For the DSi\'s onboard eMMC it\'s safe to assume 4bit being supported, however, external MMC cards do require detecting 4bit support.

### ERASED_MEM_CONT (moviNAND) (but, RESERVED in newer JEDEC specs!)
This Field defines the content of an explicitly erased memory range.

```
+-----------------------------------------------------------------------+
|       Value   Erased Memory content                                   |
|       00h     Erased memory range shall be '0'                        |
|       01h     Erased memory range shall be '1'                        |
|       02h-FFh Reserved                                                |
+-----------------------------------------------------------------------+
```

Looks like a mis-definition, since value 00h should have been kept reserved for cards that do not specify whether they set erased bits to 0 or 1.



