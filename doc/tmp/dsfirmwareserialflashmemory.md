# DS Firmware Serial Flash Memory


### ST Microelectronics SPI Bus Compatible Serial FLASH Memory

```
+-------------------------------------------------------------------------------------+
|      Chips used as wifi-flash:                                                      |
|       ID 20h,40h,12h - ST M45PE20 - 256 KBytes (Nintendo DS) (in my old DS)         |
|       ID 20h,50h,12h - ST M35PE20 - 256 KBytes (Nintendo DS) (in my DS-Lite)        |
|       ID 20h,80h,13h - ST M25PE40 - 512 KBytes (iQue DS, with chinese charset)      |
|       ID 20h,40h,11h - ST 45PE10V6 - 128 Kbytes (Nintendo DSi) (in my DSi)          |
|       ID 20h,58h,0Ch?- 5A32        - 4 Kbytes (Nintendo DSi, newer models)          |
|       ID ?           - 26FV032T    - (Nintendo DSi, J27H020) (this has big package) |
|       ID ?           - 5K32        - (3DS?)                                         |
|       ID 62h,62h,0Ch - 32B, 3XH    - 4 Kbytes (New3DS)                              |
|      Other similar chips (used in game cartridges):                                 |
|       ID 20h,40h,13h - ST 45PE40V6 - 512 KBytes (DS Zelda, NTR-AZEP-0)              |
|       ID 20h,40h,14h - ST 45PE80V6 - 1024 Kbytes (eg. Spirit Tracks, NTR-BKIP)      |
|      +ID 62h,11h,00h - Sanyo ?          - 512 Kbytes (P-Letter Diamond, ADAE)       |
|       ID 62h,16h,00h - Sanyo LE25FW203T - 256 KBytes (Mariokart backup)             |
|      +ID 62h,26h,11h - Sanyo ?          - ? Kbytes (3DS: CTR-P-AXXJ)                |
|      +ID 62h,26h,13h - Sanyo ?          - ? Kbytes (3DS: CTR-P-APDJ)                |
|       ID C2h,22h,11h - Macronix MX25L1021E? 128 Kbytes (eg. 3DS Starfox)            |
|       ID C2h,22h,13h - Macronix ...? 512 Kbytes (eg. 3DS Kid Icarus, 3DS Sims 3)    |
|       ID C2h,20h,17h - Macronix MX25L6445EZNI-10G 8192 Kbytes (DSi Art Academy)     |
|       ID 01h,F0h,00h - Garbage/Infrared on SPI-bus? (eg. P-Letter White)            |
|       ID 03h,F8h,00h - Garbage/Infrared on SPI-bus? (eg. P-Letter White 2)          |
+-------------------------------------------------------------------------------------+
```

FLASH has more than 100,000 Write Cycles, more than 20 Year Data Retention
The Firmware Flash Memory is accessed via SPI bus,
- [DS Serial Peripheral Interface Bus (SPI)](./dsserialperipheralinterfacebusspi.md)

### Instruction Codes

```
+------------------------------------------------------------------------------------+
|       06h  WREN Write Enable (No Parameters)                                       |
|       04h  WRDI Write Disable (No Parameters)                                      |
|       9Fh  RDID Read JEDEC Identification (Read 1..3 ID Bytes)                     |
|                  (Manufacturer, Device Type, Capacity)                             |
|       05h  RDSR Read Status Register (Read Status Register, endless repeated)      |
|                  Bit7-2  Not used (zero)                                           |
|                  Bit1    WEL Write Enable Latch             (0=No, 1=Enable)       |
|                  Bit0    WIP Write/Program/Erase in Progess (0=No, 1=Busy)         |
|       03h  READ Read Data Bytes (Write 3-Byte-Address, read endless data stream)   |
|       0Bh  FAST Read Data Bytes at Higher Speed (Write 3-Byte-Address, write 1     |
|                  dummy-byte, read endless data stream) (max 25Mbit/s)              |
|       0Ah  PW   Page Write (Write 3-Byte-Address, write 1..256 data bytes)         |
|                  (changing bits to 0 or 1) (reads unchanged data, erases the page, |
|                  then writes new & unchanged data) (11ms typ, 25ms max)            |
|       02h  PP   Page Program (Write 3-Byte-Address, write 1..256 data bytes)       |
|                  (changing bits from 1 to 0) (1.2ms typ, 5ms max)                  |
|       DBh  PE   Page Erase 100h bytes (Write 3-Byte-Address) (10ms typ, 20ms max)  |
|       D8h  SE   Sector Erase 10000h bytes (Write 3-Byte-Address) (1s typ, 5s max)  |
|       B9h  DP   Deep Power-down (No Parameters) (consumption 1uA typ, 10uA max)    |
|                  (3us) (ignores all further instructions, except RDP)              |
|       ABh  RDP  Release from Deep Power-down (No Parameters) (30us)                |
+------------------------------------------------------------------------------------+
```

Write/Program may not cross page-boundaries. Write/Program/Erase are rejected during first 1..10ms after power up. The WEL bit is automatically cleared on Power-Up, on /Reset, and on completion of WRDI/PW/PP/PE/SE instructions. WEL is set by WREN instruction (which must be issued before any write/program/erase instructions). Don\'t know how RDSR behaves when trying to write to the write-protected region?

### Communication Protocol

```
+-----------------------------------------------------------------------+
|       Set Chip Select LOW to invoke the command                       |
|       Transmit the instruction byte                                   |
|       Transmit any parameter bytes                                    |
|       Transmit/receive any data bytes                                 |
|       Set Chip Select HIGH to finish the command                      |
+-----------------------------------------------------------------------+
```

All bytes (and 3-byte addresses) transferred most significant bit/byte first.

### DSi \"5A32\" chip (32Kit aka 4Kbyte)
Early DSi DWM-W015 boards did have 128Kbyte FLASH, but later boards have custum 4Kbyte FLASH chips (these 4K chips are found on later DSi DWM-W015 boards, and DSi DWM-W024 boards, and 3DS DWM-W028 boards). The chips are having a 24bit address bus (needed for NDS compatibility), and, a weird non-writeable gap within a 128Kbyte memory are:

```
+-----------------------------------------------------------------------------------+
|       000000h..0002FFh  Writeable only if /WP=HIGH (otherwise writes are ignored) |
|       000300h..01F2FFh  Not writeable (FFh-filled, writes are ignored)            |
|       01F300h..01FFFFh  Writeable                                                 |
|       020000h and up    Mirrors of 0..01FFFFh (same read/write-ability as above)  |
+-----------------------------------------------------------------------------------+
```

There are several part numbers: \"5A32\" (DSi), \"5K32\" (3DS), \"32B, 3XH\" (3DS), and \"26FV032T\" (DSi), that chips are probably all the same size & functionally same; most of those 4Kbyte chips have tiny packages (except \"26FV032T\" which comes in classic large package).

### Pin-Outs (Large Package, in NDS, and early DSi boards)

```
+-------------------------------------------------------------------------------------+
|       1   D    Serial Data In (latched at rising clock edge)          _________     |
|       2   C    Serial Clock (max 25MHz)                             /|o        |    |
|       3   /RES Reset                                            1 -| |         |- 8 |
|       4   /S   Chip Select (instructions start at falling edge) 2 -| |         |- 7 |
|       5   /W   Write Protect (makes first 256 pages read-only)  3 -| |_________|- 6 |
|       6   VCC  Supply (2.7V..3.6V typ) (4V max) (DS:VDD3.3)     4 -|/          |- 5 |
|       7   VSS  Ground                                              |___________|    |
|       8   Q    Serial Data Out (changes at falling clock edge)                      |
+-------------------------------------------------------------------------------------+
```


### Pin-Outs (Tiny Package, in newer DSi boards, and 3DS)

```
+-------------------------------------------------------------------------------------+
|       1   /S   Chip Select (instructions start at falling edge)     ___________     |
|       2   Q    Serial Data Out (changes at falling clock edge)  1 -| o         |- 8 |
|       3   /W   Write Protect (makes first pages read-only)      2 -|           |- 7 |
|       4   VSS  Ground                                           3 -|           |- 6 |
|       5   D    Serial Data In (latched at rising clock edge)    4 -|___________|- 5 |
|       6   C    Serial Clock                                                         |
|       7   /RES Reset                                                                |
|       8   VCC  Supply (2.7V..3.6V typ) (DSi: VDD33)                                 |
+-------------------------------------------------------------------------------------+
```




