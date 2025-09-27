# DSi Atheros Wifi - Internal Memory Map


### Overall Memory Map (Internal Xtensa memory)
Internal Memory contains I/O Ports, ROM, and RAM. Arranged as so:

```
+---------------------------------------------------------------------------+
|       00000000h  I/O Ports                                                |
|       000E0000h  ROM        ;\as so on AR6002 (other AR60xx chips may use 
|       00100000h  RAM        ;/slightly different addresses).              |
+---------------------------------------------------------------------------+
```

The whole memory is repeated every 400000h bytes (4MByte), this is just dumb mirroring (although Atheros is referring to it as \"virtual memory\"). The first three mirrors (in first 12Mbytes) are commonly used as so:

```
+----------------------------------------------------------------------------------+
|       00000000h..003FFFFh  used for I/O Port read/write             ;1st mirror  |
|       00400000h..007FFFFh  used for ROM and RAM data read/write     ;2nd mirror  |
|       00800000h..00BFFFFh  used for ROM and RAM opcode read         ;3rd mirror  |
|       00C00000h..FFFFFFFh  normally unused                          ;4th..1024th |
+----------------------------------------------------------------------------------+
```

Unknown how far it is really required to use the mirrors that way. The different areas might be related to different access rights, or caching (although the AR6002/AR6003/AR6004 chips don\'t have any cache at all).
The AR6002 BIOS does usually read ROM data from 4E0000h..4F3FFFh, however, in one case it\'s accidently reading ROM data from 8EEFF8h..8EF73Bh, so that\'s apparently possible & working, too.
Using WINDOW_DATA to read memory works well for address 00000000h..FFFFFFFFh (apart from some dangerous read-locations in the I/O area; as well as mirrors of those I/O locations).

### RAM/ROM address/size, IDs, and various stuff for different chips

```
+------------------------------------------------------------------------------+
|       AR60xx chip name    AR6002    AR6003    AR6004    AR6013    AR6014     |
|       AR6002_rev alias    REV2      REV4      REV6      REV2      REV2       |
|       hw name             hw2       hw4       hw6       hw2       hw2        |
|       Nintendo DSi/3DS    Old DSi   N/A       N/A       New DSi   3DS/New3DS |
|       Wifi Board          DWM-W015  N/A       N/A       DWM-W024  DWM-W028   |
|       SPI FLASH ID Byte   01h       N/A       N/A       02h       03h        |
|       SPI FLASH Size      4 or 128K N/A       N/A       4K        4K         |
|       I2C EEPROM SizeUsed 300h      ?         ?         300h      300h       |
|       ROM Size (Kbyte)    80K       256K      512K      256K      256K       |
|       RAM Size (Kbyte)    184K      256K      256-288K? 128K      128K       |
|       IRAM Size (Kbyte)   N/A       N/A       160K?     N/A       N/A        |
|       ROM Date            23nov2007 ?         ?         18jul2008 25jun2009  |
|       ROM ID version      2.0.0.392 ?         ?         2.3.0.36  2.3.0.111  |
|       Firmware version    2.1.0.123 ?         ?         2.3.0.108 2.3.0.179+ |
|       ROM Base            0E0000h   0E0000h   100000h   0E0000h   0E0000h    |
|       ROM Reset Entry     8E0000h   ?         ?         8E0000h   8E0000h    |
|       RAM Base            100000h   140000h?  000000h?? 120000h   120000h    |
|       RAM Host Interest   500400h   540600h   400600h?? 520000h   520000h    |
|       RAM Start of Free   502400h   ?         ?         524C00h   524C00h    |
|       RAM BMI_DONE Entry  915000h   ?         ?         927000h   927000h    |
|       CPU Litbase         52F000h+1 ?         ?         54C000h+1 54C000h+1  |
|       IRAM Base           N/A       N/A       998000h   N/A       N/A        |
|       ROM Size (hex)      14000h    40000h    80000h    40000h    40000h     |
|       RAM Size (hex)      2E000h    40000h    4xxxxh?   20000h    20000h     |
|       ROM ID hex          20000188h ?         ?         23000024h 2300006Fh  |
|       Firm ID hex         2100007Bh ?         ?         2300006Ch 230000B3h+ |
|       CHIP_ID used        02000001h ?         ?         0D000000h 0D000001h  |
|       CHIP_ID alternate?  02010001h ?         ?         0D00000xh ?          |
|       BB_D2_CHIP_ID       has any?  ?         ?         has any?  has any?   |
|       SDIO MANFID         02000271h ?         ?         02010271h 02010271h  |
|       OSC                 26MHz     ?         ?         40MHz     40MHz      |
+------------------------------------------------------------------------------+
```


### Special ROM Addresses
There are only a few ROM locations with fixed/standarized addresses:

```
+------------------------------------------------------------------------------------+
|       Entrypoint:        ROM_Base+0                                                |
|       Exception Vectors: ROM_Base+xxx ?                                            |
|       DataSet Address:   ROM_Base+ROM_Size-8                                       |
|       MBIST Cksum:       ROM_Base+ROM_Size-4  ;MBIST = memory built-in-self-test ? |
+------------------------------------------------------------------------------------+
```

The firmware may call ROM functions, but the firmware code must be matched to specific ROM versions: There is some call table in RAM, allowing to call (or change) function vectors, but the table\'s location/indices vary for different ROM versions. The RAM table doesn\'t contain entries for all ROM functions though, so the firmware must use hardcoded addresses (like \"8E35A0h\") for functions that aren\'t in the table.
Note that it\'s possible to patch ROM via TCAM/BCAM registers.

### Special RAM Addresses
The first some kilobytes of RAM contain stuff like stack, call table, variables, and host interest area (but the exact addresses of that regions depend on the ROM version).
The remaining RAM could be more or less freely used by the firmware (whereas, one should probably use ROM\'s memory allocation function for that purpose).
The CPU\'s \"litbase\" is dictacted by the ROM, so the firmware must adapt its literal pool offsets to that value. The default BMI_DONE entrypoint is also dictated by the ROM (although one could override it if neccessary).

### Hardware I/O Addresses
The hardware I/O addresses are defined in source code folder \"include\\AR6002\\hw\*\". Whereas, the folder is called \"AR6002\", but it does also contain defintions for AR6003 and AR6004. In a similar fashion, the source code does also contain definitions like AR6002_REVn, whereas some of that \"AR6002 revisions\" are actually referring to AR6003 and AR6004. The naming scheme appears to be as so:

```
+-----------------------------------------------------------------------+
|       AR6002 = AR6002_REV2 = include\AR6002\hw2.0                     
|       AR6003 = AR6002_REV4 = include\AR6002\hw4.0                     
|       AR6004 = AR6002_REV6 = include\AR6002\hw6.0                     
+-----------------------------------------------------------------------+
```

The above folders are included in all source code versions (newer atheros code from 2010 is definetly no longer compatible with the DSi\'s AR6002 firmware, however, concerning the hardware definitions, the \"hw2.0\" folder appears to have stayed intact and should be still compatible with real hardware, even in newer source code versions).
However, there are at least two different \"hw4.0\" versions, the newer one containing some additional registers, and some changed register addresses. There\'s also some AR6002_REV42 definition in some files, which might be related to that \"hw4.0\" variant. Current theory would be that \"hw4.0\" means AR6003, and the newer \"hw4.0\" should be actually \"hw4.2\" and means some different chip with unknown name. Or whatever.
There\'s also a \"include\\AR6002\\hw\" folder, this is just some useless dupe, containing the exact same files as \"include\\AR6002\\hw2.0\".
There\'s also something called \"MCKINLEY\", which seems to same (or similar) as \"AR6004\".
The actual files in the above folders are containing some very ugly bloated auto-generated definitions, definetly not suitable for human reading (except by using some software parser for extracting relevant definitions).



