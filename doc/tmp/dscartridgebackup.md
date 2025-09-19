# DS Cartridge Backup


### SPI Bus Backup Memory

```
+-------------------------------------------------------------------------------------+
|       Type   Total Size  Page Size  Chip/Example      Game/Example                  |
|       EEPROM 0.5K bytes   16 bytes  ST M95040-W       (eg. Metroid Demo)            |
|       EEPROM   8K bytes   32 bytes  ST M95640-W       (eg. Super Mario DS)          |
|       EEPROM  64K bytes  128 bytes  ST M95512-W       (eg. Downhill Jam)            |
|       EEPROM 128K bytes    ? bytes  ?                 (eg. Explorers of Sky)        |
|       FLASH  256K bytes  256 bytes  ST M45PE20        (eg. Skateland)               |
|       FLASH  256K bytes             Sanyo LE25FW203T  (eg. Mariokart)               |
|       FLASH  512K bytes  256 bytes  ST M25PE40?       (eg. which/any games?)        |
|       FLASH  512K bytes             ST 45PE40V6       (eg. DS Zelda, NTR-AZEP-0)    |
|       FLASH 1024K bytes             ST 45PE80V6       (eg. Spirit Tracks, NTR-BKIP) |
|       FLASH 8192K bytes             MX25L6445EZNI-10G (Art Academy only, TWL-VAAV)  |
|       FRAM     8K bytes   No limit  ?                 (eg. which/any games?)        |
|       FRAM    32K bytes   No limit  Ramtron FM25L256? (eg. which/any games?)        |
+-------------------------------------------------------------------------------------+
```


### Lifetime Stats (might vary per manufacturer)

```
+-----------------------------------------------------------------------+
|       Type      Max Writes per Page    Data Retention                 |
|       EEPROM    100,000                40 years                       |
|       FLASH     100,000                20 years                       |
|       FRAM      No limit               10 years                       |
+-----------------------------------------------------------------------+
```


SPI Bus Backup Memory is accessed via Ports 40001A0h and 40001A2h, see
- [DS Cartridge I/O Ports](./dscartridgeioports.md)

### Commands
For all EEPROM and FRAM types:

```
+----------------------------------------------------------------------------------+
|       06h WREN  Write Enable                Cmd, no parameters                   |
|       04h WRDI  Write Disable               Cmd, no parameters                   |
|       05h RDSR  Read Status Register        Cmd, read repeated status value(s)   |
|       01h WRSR  Write Status Register       Cmd, write one-byte value            |
|       9Fh RDID  Read JEDEC ID (not supported on EEPROM/FLASH, returns FFh-bytes) |
+----------------------------------------------------------------------------------+
```

For 0.5K EEPROM (8+1bit Address):

```
+---------------------------------------------------------------------------------+
|       03h RDLO  Read from Memory 000h-0FFh  Cmd, addr lsb, read byte(s)         |
|       0Bh RDHI  Read from Memory 100h-1FFh  Cmd, addr lsb, read byte(s)         |
|       02h WRLO  Write to Memory 000h-0FFh   Cmd, addr lsb, write 1..MAX byte(s) |
|       0Ah WRHI  Write to Memory 100h-1FFh   Cmd, addr lsb, write 1..MAX byte(s) |
+---------------------------------------------------------------------------------+
```

For 8K..64K EEPROM and for FRAM (16bit Address):

```
+-------------------------------------------------------------------------------------+
|       03h RD    Read from Memory            Cmd, addr msb,lsb, read byte(s)         |
|       02h WR    Write to Memory             Cmd, addr msb,lsb, write 1..MAX byte(s) |
+-------------------------------------------------------------------------------------+
```

For 128K EEPROM (24bit Address):

```
+-----------------------------------------------------------------------+
|       As above, but with 24bit addr msb,mid,lsb ?                     |
+-----------------------------------------------------------------------+
```

Note: MAX = Page Size (see above chip list) (no limit for FRAM).

For FLASH backup, commands should be same as for Firmware FLASH memory:
- [DS Firmware Serial Flash Memory](./dsfirmwareserialflashmemory.md)
A few NDS/DSi carts are sharing the SPI bus for FLASH and Infrared, this requires a 00h-prefix byte for FLASH access, with slower 1MHz SPI clock and delays, see:
- [DS Cart Infrared/Pedometers](./dscartinfraredpedometers.md)

### Status Register

```
+------------------------------------------------------------------------------------+
|       0   WIP  Write in Progress (1=Busy) (Read only) (always 0 for FRAM chips)    |
|       1   WEL  Write Enable Latch (1=Enable) (Read only, except by WREN,WRDI)      |
|       2-3 WP   Write Protect (0=None, 1=Upper quarter, 2=Upper Half, 3=All memory) |
+------------------------------------------------------------------------------------+
```

For 0.5K EEPROM:

```
+-----------------------------------------------------------------------+
|       4-7 ONEs Not used (all four bits are always set to "1" each)    |
+-----------------------------------------------------------------------+
```

For 8K..64K EEPROM and for FRAM:

```
+----------------------------------------------------------------------------------+
|       4-6 ZERO Not used (all three bits are always set to "0" each)              |
|       7   SRWD Status Register Write Disable (0=Normal, 1=Lock) (Only if /W=LOW) |
+----------------------------------------------------------------------------------+
```

WEL gets reset on Power-up, WRDI, WRSR, WRITE/LO/HI, and on /W=LOW.
The WRSR command allows to change ONLY the two WP bits, and the SRWD bit (if any), these bits are non-volatile (remain intact during power-down), respectively, the WIP bit must be checked to sense WRSR completion.

### Detection (by examining hardware responses)
The overall memory type and bus-width can be detected by RDSR/RDID commands:

```
+-------------------------------------------------------------------------+
|       RDSR  RDID          Type         (bus-width)                      |
|       FFh,  FFh,FFh,FFh   None         (none)                           |
|       F0h,  FFh,FFh,FFh   EEPROM       (with 8+1bit address bus)        |
|       00h,  FFh,FFh,FFh   EEPROM/FRAM  (with 16bit address bus)         |
|       ?     ?,?,?         EEPROM       (with 24bit address bus)         |
|       00h,  xxh,xxh,xxh   FLASH        (usually with 24bit address bus) |
+-------------------------------------------------------------------------+
```

And, the RD commands can be used to detect the memory size/mirrors (though that won\'t work if the memory is empty).

### Detection (in emulators)
Nintendo is using different functions for sending cmd+addr and data. The bus-width can be detected by counting the bytes transferred with same program counter after chip selection. One could also try to examine code/data in the ROM-image (but that may envolve self-decompressing code and other obstacles).
Special cases:
Over the Hedge does initially try to access 8Kbyte EEPROM, but does actually use 0.5Kbyte EEPROM (as workaround: re-detect the bus-width on each transfer).
Rune Factory - A Fantasy Harvest Moon seems to be also difficult to detect (as workaround: force 64Kbyte EEPROM on gamecode ARFx).
FLASH has same 24bit bus-width as 128Kbyte EEPROM, but isn\'t compatible on writing. EEPROM does use 02h=Write+Erase. FLASH does use 0Ah=Write+Erase (or D8h/DBh=Erase and 02h=Write separatly).

### Pin-Outs for EEPROM and FRAM chips

```
+-----------------------------------------------------------------------+
|       Pin Name Expl.                                                  |
|       1  /S    Chip Select                                            |
|       2  Q     Data Out                                               |
|       3  /W    Write-Protect (not used in NDS, wired to VCC)          |
|       4  VSS   Ground                                                 |
|       5  D     Data In                                                |
|       6  C     Clock                                                  |
|       7  /HOLD Transfer-pause (not used in NDS, wired to VCC)         |
|       8  VCC   Supply 2.5 to 5.5V for M95xx0-W                        |
+-----------------------------------------------------------------------+
```


FRAM (Ferroelectric Nonvolatile RAM) is fully backwards compatible with normal EEPROMs, but comes up with faster write/erase time (no delays), and with lower power consumption, and unlimited number of write/erase cycles. Unlike as for normal RAM, as far as I understand, the data remains intact without needing any battery.

### Other special save memory

```
+--------------------------------------------------------------------------------+
|       DS Vision (NDS cart with microSD slot... and maybe ALSO with EEPROM?)    |
|       NAND carts can store data in a read/write-able portion of the "ROM" chip |
|       Typing Adventure does have SPI FLASH (but not directly wired to SPI bus) |
+--------------------------------------------------------------------------------+
```


### DSi Internal eMMC and External SD Card
DSi cartridges are usually (maybe always) having SD/MMC access disabled, so they must stick using EEPROM/FLASH chips inside of the cartridges (which is required for NDS compatibility anyways).
However, DSiware games (downloaded from DSi Shop) are allowed to save data on eMMC, using \"private.sav\" or \"public.sav\" files in their data folder. The size of that files is preset in cartridge header.



