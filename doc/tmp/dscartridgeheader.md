# DS Cartridge Header


### Header Overview (loaded from ROM Addr 0 to Main RAM 27FFE00h on Power-up)

```
+-------------------------------------------------------------------------------------+
|       Address Bytes Expl.                                                           |
|       000h    12    Game Title  (Uppercase ASCII, padded with 00h)                  |
|       00Ch    4     Gamecode    (Uppercase ASCII, NTR-<code>)        (0=homebrew)   |
|       010h    2     Makercode   (Uppercase ASCII, eg. "01"=Nintendo) (0=homebrew)   |
|       012h    1     Unitcode    (00h=NDS, 02h=NDS+DSi, 03h=DSi) (bit1=DSi)          |
|       013h    1     Encryption Seed Select (00..07h, usually 00h)                   |
|       014h    1     Devicecapacity         (Chipsize = 128KB SHL nn) (eg. 7 = 16MB) |
|       015h    7     Reserved    (zero filled)                                       |
|       01Ch    1     Reserved    (zero)                      (except, used on DSi)   |
|       01Dh    1     NDS Region  (00h=Normal, 80h=China, 40h=Korea) (other on DSi)   |
|       01Eh    1     ROM Version (usually 00h)                                       |
|       01Fh    1     Autostart (Bit2: Skip "Press Button" after Health and Safety)   |
|                     (Also skips bootmenu, even in Manual mode & even Start pressed) |
|       020h    4     ARM9 rom_offset    (4000h and up, align 1000h)                  |
|       024h    4     ARM9 entry_address (2000000h..23BFE00h)                         |
|       028h    4     ARM9 ram_address   (2000000h..23BFE00h)                         |
|       02Ch    4     ARM9 size          (max 3BFE00h) (3839.5KB)                     |
|       030h    4     ARM7 rom_offset    (8000h and up)                               |
|       034h    4     ARM7 entry_address (2000000h..23BFE00h, or 37F8000h..3807E00h)  |
|       038h    4     ARM7 ram_address   (2000000h..23BFE00h, or 37F8000h..3807E00h)  |
|       03Ch    4     ARM7 size          (max 3BFE00h, or FE00h) (3839.5KB, 63.5KB)   |
|       040h    4     File Name Table (FNT) offset                                    |
|       044h    4     File Name Table (FNT) size                                      |
|       048h    4     File Allocation Table (FAT) offset                              |
|       04Ch    4     File Allocation Table (FAT) size                                |
|       050h    4     File ARM9 overlay_offset                                        |
|       054h    4     File ARM9 overlay_size                                          |
|       058h    4     File ARM7 overlay_offset                                        |
|       05Ch    4     File ARM7 overlay_size                                          |
|       060h    4     Port 40001A4h setting for normal commands (usually 00586000h)   |
|       064h    4     Port 40001A4h setting for KEY1 commands   (usually 001808F8h)   |
|       068h    4     Icon/Title offset (0=None) (8000h and up)                       |
|       06Ch    2     Secure Area Checksum, CRC-16 of [[020h]..00007FFFh]             |
|       06Eh    2     Secure Area Delay (in 131kHz units) (051Eh=10ms or 0D7Eh=26ms)  |
|       070h    4     ARM9 Auto Load List Hook RAM Address (?) ;\endaddr of auto-load 
|       074h    4     ARM7 Auto Load List Hook RAM Address (?) ;/functions            |
|       078h    8     Secure Area Disable (by encrypted "NmMdOnly") (usually zero)    |
|       080h    4     Total Used ROM size (remaining/unused bytes usually FFh-padded) |
|       084h    4     ROM Header Size (4000h)                                         |
|       088h    4     Unknown, some rom_offset, or zero? (DSi: slightly different)    |
|       08Ch    8     Reserved (zero filled; except, [88h..93h] used on DSi)          |
|       094h    2     NAND end of ROM area  ;\in 20000h-byte units (DSi: 80000h-byte) 
|       096h    2     NAND start of RW area ;/usually both same address (0=None)      |
|       098h    18h   Reserved (zero filled)                                          |
|       0B0h    10h   Reserved (zero filled; or "DoNotZeroFillMem"=unlaunch fastboot) |
|       0C0h    9Ch   Nintendo Logo (compressed bitmap, same as in GBA Headers)       |
|       15Ch    2     Nintendo Logo Checksum, CRC-16 of [0C0h-15Bh], fixed CF56h      |
|       15Eh    2     Header Checksum, CRC-16 of [000h-15Dh]                          |
|       160h    4     Debug rom_offset   (0=none) (8000h and up)       ;only if debug |
|       164h    4     Debug size         (0=none) (max 3BFE00h)        ;version with  |
|       168h    4     Debug ram_address  (0=none) (2400000h..27BFE00h) ;SIO and 8MB   |
|       16Ch    4     Reserved (zero filled) (transferred, and stored, but not used)  |
|       170h    90h   Reserved (zero filled) (transferred, but not stored in RAM)     |
|       200h    E00h  Reserved (zero filled) (usually not transferred)                |
+-------------------------------------------------------------------------------------+
```

DSi Cartridges are using an extended cartridge header,
- [DSi Cartridge Header](./dsicartridgeheader.md)
Some of that new/changed DSi header entries are important even in NDS mode:
- On DSi, ARM9/ARM7 areas are restricted to 2.75MB (instead 3.8MB on real NDS)
- New NDS titles must have RSA signatures (and old titles must be in whitelist)

For more info about CRC-16, see description of GetCRC16 BIOS function,
- [BIOS Misc Functions](./biosmiscfunctions.md)
For the Logo checksum, the BIOS verifies only \[15Ch\]=CF56h, it does NOT verify the actual data at \[0C0h-15Bh\] (nor it\'s checksum), however, the data is verified by the firmware.

### Secure Area Delay
The Secure Area Delay at header\[06Eh\] is counted in 130.912kHz units (which can be clocked via one of the hardware timers with prescaler=F/256 and reload=(10000h-((X AND 3FFFh)+2)); for some weird reason, in case of Header checksum it\'s ANDed with 1FFFh instead of 3FFFh). Commonly used values are X=051Eh (10ms), and X=0D7Eh (26ms).
The delay is used for all Blowfish encrypted commands, the actual usage/purpose differs depending on bit31 of the ROM Chip ID:
When ChipID.Bit31=0 (commands are sent ONCE): The delay is issued BEFORE sending the command:

```
+-----------------------------------------------------------------------+
|       Delay,Cmd                                                       |
+-----------------------------------------------------------------------+
```

Older/newer games are using delays of 10ms/26ms (although all known existing cartridges with Bit31=0 would actually work WITHOUT delays).
When ChipID.Bit31=1 (commands are repeated MULTIPLE times): The delay is issued AFTER sending the command for the FIRST time:

```
+-----------------------------------------------------------------------+
|       Cmd,Delay,Cmd                                ;for 2x repeat     |
|       Cmd,Delay,Cmd,Cmd,Cmd,Cmd,Cmd,Cmd,Cmd,Cmd    ;for 9x repeat     |
+-----------------------------------------------------------------------+
```

Known games are using delays of 26ms (although all known existing cartridges (=Cooking Coach) with Bit31=1 would actually work with shorter delays of ca. 7ms (but, better use 8ms for safety)).

### NDS Gamecodes
This is the same code as the NTR-UTTD (NDS) or TWL-UTTD (DSi) code which is printed on the package and sticker on (commercial) cartridges (excluding the leading \"NTR-\" or \"TWL-\" part).

```
+--------------------------------------------------------------------------------+
|       U  Unique Code          (usually "A", "B", "C", or special meaning)      |
|       TT Short Title          (eg. "PM" for Pac Man)                           |
|       D  Destination/Language (usually "J" or "E" or "P" or specific language) |
+--------------------------------------------------------------------------------+
```

The first character (U) is usually \"A\" or \"B\", in detail:

```
+-----------------------------------------------------------------------------------+
|       A NDS common games                                                          |
|       B NDS common games                                                          |
|       C NDS common games                                                          |
|       D DSi-exclusive games                                                       |
|       H DSiWare (system utilities and browser) (eg. HNGP=browser)                 |
|       I NDS and DSi-enhanced games with built-in Infrared port                    |
|       K DSiWare (dsiware games and flipnote) (eg. KGUV=flipnote)                  |
|       N NDS nintendo channel demo's japan (NTR-NTRJ-JPN)                          |
|       T NDS many games                                                            |
|       U NDS and DSi uncommon extra hardware (eg. NAND, ram, microSD, TV, azimuth) |
|       V DSi-enhanced games                                                        |
|       Y NDS many games                                                            |
+-----------------------------------------------------------------------------------+
```

The second/third characters (TT) are:

```
+----------------------------------------------------------------------------------+
|       Usually an abbreviation of the game title (eg. "PM" for "Pac Man") (unless |
|       that gamecode was already used for another game, then TT is just random)   |
+----------------------------------------------------------------------------------+
```

The fourth character (D) indicates Destination/Language:

```
+-------------------------------------------------------------------------------------+
|       A Asian    E English/USA  I Italian   M Swedish  Q Danish   U Australian      |
|       B N/A      F French       J Japanese  N Nor      R Russian  V EUR+AUS         |
|       C Chinese  G N/A          K Korean    O Int      S Spanish  W..Z Europe #3..5 |
|       D German   H Dutch        L USA #2    P Europe   T USA+AUS                    |
+-------------------------------------------------------------------------------------+
```




