# DS Cartridge NAND


SLC-NAND is used in at least three NDS/DSi games. The ROM Chip ID has bit3 in 4th byte set.

```
+---------------------------------------------------------------------------------+
|       ECh,7Fh,00h,88h NDS Samsung  128MB NAND (eg. Warioware D.I.Y., NTR-UORE)  |
|       ECh,7Fh,01h,88h NDS Samsung  128MB NAND (eg. Jam with the Band, NTR-UXBP) |
|       ECh,7Fh,00h,E8h DSi Samsung  128MB NAND (eg. Face Training, TWL-USKV)     |
+---------------------------------------------------------------------------------+
```

In the cart header, the 1st byte of the Gamecode is \"U\" (that \"U\" is also used for a few other carts with \"uncommon\" hardware), and header entries \[094h,096h\] indicate the end of the ROM region and start of RW region (in 128Kbyte units for NDS, or 512Kbyte units for DSi; exception: the oldest NAND title (japanese version of Jam with the Band) did have \[094h,096h\] set to all zeroes). The chips are all 128MByte (122MByte usable), with memory map as so:

```
+-------------------------------------------------------------------------------------+
|       00000000h  ROM region (one large region)                                  (R) |
|       0xxx0000h  RW region (split into several 128KByte blocks)               (R/W) |
|       07A00000h  Reserved region                                                (R) |
+-------------------------------------------------------------------------------------+
```

The RW space is 8MB for Jam with the Band, 16MB for WarioWare DIY, and 82MB in Face Training. Unknown if some of the cart memory is reserved for broken sector handling.

### DS Cartridges with NAND memory
NAND memory contains both the game and save memory (normal NDS games contain separate ROM and SPI FLASH/EEPROM chips for that purposes). The advantage is that NAND allows more storage than the usual FLASH chips. Nintendo also claims SLC-NAND to be very fast, but that\'s only half true (it\'s much slower than MROM, but might be slightly faster than SPI FLASH).

### Command Summary
For whatever reason, random access is slightly restricted: One must use command 8Bh/B2h to select ROM region or a 128KByte RW window before reading/writing the selected area. Writing is done in 2Kbyte units (4x200h bytes).

```
+------------------------------------------------------------------------------------+
|      In ROM access mode:                                                           |
|       9400000000000000h Len=200h  NAND Read ID                                     |
|       B2aaaaaaaa000000h Len=0     NAND Select 128Kbyte RW access mode              |
|       B300000000000000h Len=04h   Unknown (returns 00000000h)                      |
|       BB00000000000000h Len=200h  Unknown (returns 1X 04 09 20 04, plus zeroes)    |
|      In RW access mode (on DSi carts, this works ONLY in DSi mode):                |
|       81aaaaaaaa000000h Len=200h  NAND Write to Write Buffer (must be issued 4x)   |
|       8200000000000000h Len=0     NAND Forward Write Buffer to NAND                |
|       8400000000000000h Len=0     NAND Discard Write Buffer                        |
|       8500000000000000h Len=0     NAND Write Enable                                |
|       8600000000000000h Len=0     Unknown                                          |
|       8700000000000000h Len=0     NAND Write Disable                               |
|       8B00000000000000h Len=0     NAND Select ROM access mode                      |
|      In either mode:                                                               |
|       0B00000000000000h Len=200h  Returns cart header[000h..1FFh]                  |
|       0C00000000000000h Len=200h  Returns corrupted cart header[1F8h..3F7h] ??     |
|       58h..5Fh          Len=0     Unknown (looks same/similar as in 1T-ROM carts)  |
|       60h..68h          Len=800h  Unknown (looks same/similar as in 1T-ROM carts)  |
|       B000000000000000h Len=04h   Unknown (returns 01010101h)                      |
|       B500000000000000h Len=0     Unknown (looks same/similar as in SanDisk carts) |
|       B7aaaaaaaa000000h Len=200h  NAND Read from ROM or RW area                    |
|       B800000000000000h Len=04h   Read Chip ID                                     |
|       D600000000000000h Len=04h   NAND Read Status                                 |
|      Further command(s) spotted in Face Training disassembly:                      |
|       8800000000000000h Len=0     Unknown (is in disassembly, but fails on HW?)    |
+------------------------------------------------------------------------------------+
```


### 81aaaaaaaa000000h - NAND Write to Write Buffer + Data\[200h\]
The command must be issued 4 times with the same address (seems to use the address from the first command), a full write is 800h bytes (4x200h), the chip won\'t respond to other commands until all 4 commands are sent. Unknown what happens when trying to send more than 4 commands.
This command doesn\'t directly write to NAND, instead it stores the incoming data in a 800h-byte write buffer (latter committed using command 82h).
The provided address needs to be within the access window specified by command B2h.

### 8200000000000000h - NAND Forward Write Buffer to NAND
The data in the 800h-byte write buffer is written to the actual NAND, and the write-enable bit in the status register is cleared.

### 8400000000000000h - NAND Discard Write Buffer
The data in the write buffer is discarded (a subsequent command 82h would have no effect).
Games seem to always use this after command 82h, so maybe it\'s required even after a write.

### 8500000000000000h - NAND Write Enable
The write-enable bit in the status register is set.
Only works in RW access mode.

### 8B00000000000000h - NAND Select ROM access mode
Switch to ROM access mode.

### B2aaaaaaaa000000h - NAND Select 128Kbyte RW access mode
The provided address defines an accessible 128K window in RW address space, reads and writes may only take place within that window, the lower 17 bits of the address are ignored.
Addresses below start of RW area are ignored (the cart stays in ROM mode, and the cart does then reportedly get stuck permanently busy).
Addresses that go past the end of the RW address space will just read all FF\'s.

### B7aaaaaaaa000000h - NAND Read from ROM or RW area + Data\[200h\]
This command is used for reading data under both ROM and RW modes.
In ROM mode: returns data from the ROM space, pretty much like the \'regular\' B7 command, trying to read from RW space in this mode will return all FF\'s.
In RW mode: returns data from the RW space, the provided address needs to be within the access window specified by command B2h.

### D600000000000000h - NAND Read Status + Data\[4\]
Status register bits:

```
+-----------------------------------------------------------------------------------+
|       0-1   Unknown (usually zero)                                                |
|       2-3   Unknown (usually zero, but tested by DSi Launcher, not NAND related?) |
|       4     NAND write enable                                                     |
|       5     NAND status (0=busy, 1=ready)                                         |
|       6     Unknown (usually zero, but set by DeSmuME)                            |
|       7     Unknown (possible error flag?)                                        |
|       8-15  Same as bit0-7                                                        |
|       16-23 Same as bit0-7                                                        |
|       24-31 Same as bit0-7                                                        |
+-----------------------------------------------------------------------------------+
```

Value on startup is 20h (aka 20202020h when reading 4 bytes).

### BB00000000000000h Len=200h Unknown (returns 1X 04 09 20 04, plus zeroes)

```
+-----------------------------------------------------------------------------------+
|       Values in Jam with the Band (nocash dump): 17 04 09 20 04, plus 1FBh zeroes |
|       Values in Face Training (nocash dump):     10 04 09 20 04, plus 1FBh zeroes |
+-----------------------------------------------------------------------------------+
```


### 9400000000000000h - NAND Read ID + Data\[200h\]
Returns NAND ID data of sorts.

```
+-------------------------------------------------------------------------------+
|      Values in Jam with the Band (arisotura dump):                            |
|       000h  EC F1 00 95 40 00 00 00 00 00 00 00 00 00 00 00  ....@........... |
|       010h  00 00 00 00 00 00 00 00 EC 00 9E A1 51 65 34 35  ............Qe45 |
|       020h  30 35 30 31 19 19 02 0A 00 00 00 00 00 00 00 00  0501............ |
|       030h  FF FF FF .. (1D0h bytes) (why not 00h's ???)     ................ |
|      Values in Jam with the Band (nocash dump):                               |
|       000h  EC F1 00 95 40 00 00 00 00 00 00 00 00 00 00 00  ....@........... |
|       010h  00 00 00 00 00 00 00 00 EC 00 3B 5A 32 9B 32 30  ..........;Z2.20 |
|       020h  35 35 30 30 19 19 02 0A 00 00 00 00 00 00 00 00  5500............ |
|       030h  00 00 00 .. (1D0h bytes)                         ................ |
|      Values in Face Training (nocash dump):                                   |
|       000h  EC F1 00 95 40 00 00 00 00 00 00 00 00 00 00 00  ....@........... |
|       010h  00 00 00 00 00 00 00 00 EC 00 5A 36 5C 14 35 35  ..........Z6\.55 
|       020h  32 36 30 36 04 04 08 0A 00 00 00 00 00 00 00 00  2606............ |
|       030h  00 00 00 .. (1D0h bytes)                         ................ |
+-------------------------------------------------------------------------------+
```

For Jam with Band, the 16 bytes at 018h are also found in the last 800h bytes of the RW space (see below). The bytes with value ECh might be related to the Maker ID in Chip ID.

### Last 128Kbyte in RW region (at 079E0000h..079FFFFFh)
The last 128Kbyte of RW area is normal write-able memory in Face Training without special content. However, in Jam with the Band, the last 128KByte are readonly, they can be read like normal RW blocks (select via command B2h, then read via B7h), but writing isn\'t supported (although NAND Status bit5 gets cleared for a moment upon write attempts to this 128Kbyte area; unlike as for when trying to write 7A00000h and up).

```
+-----------------------------------------------------------------------------------+
|      Values in Jam with the Band (arisotura dump):                                |
|       079E0000h  FF FF FF .. (1F800h bytes)                      ................ |
|       079FF800h  EC 00 9E A1 51 65 34 35 30 35 30 31 19 19 02 0A ....Qe450501.... |
|       079FF810h  00 00 00 00 6D D6 DA 9B B0 24 22 88 79 3B BF EA ....m....$".y;.. |
|       079FF820h  E6 AC 5E FA 69 12 0D 52 5D 5B F5 80 FF FF FF FF ..^.i..R][...... |
|       079FF830h  FF FF FF .. (7D0h bytes)                        ................ |
|      Values in Jam with the Band (nocash dump):                                   |
|       079E0000h  FF FF FF .. (1F800h bytes)                      ................ |
|       079FF800h  EC 00 3B 5A 32 9B 32 30 35 35 30 30 19 19 02 0A ..;Z2.205500.... |
|       079FF810h  00 00 00 00 DD 58 84 07 F9 72 19 04 96 8C FF 67 .....X...r.....g |
|       079FF820h  7F 66 B9 E5 FD F7 3F 1A AE 60 60 00 FF FF FF FF .f....?..``..... |
|       079FF830h  FF FF FF .. (7D0h bytes)                        ................ |
+-----------------------------------------------------------------------------------+
```

Jam with the Band checks the bytes at 079FF800h (unknown what it does with them, or what it does when they are missing).

### Reserved Area (at 07A00000h and up) (including 08000000h and up)
This memory isn\'t intended to be used, in Jam with the Band it just returns FFh\'s. However, in Face Training it does return some interesting internal data (in RW mode):
The DSi Blowfish key (with the gamecode pre-applied), some NDS ARM code (for the secure area or so), and most interestingly some more ARM+THUMB code (apparently containing the firmware running on an ARM CPU inside of the game cartridge itself).
Unfortunately, that internal memory is returned as \"raw\" data with faulty bits, and it seems to be required to apply error correction to convert it to actual intact data (the \"raw\" stuff consists of 1E8h-byte data snippets, usually followed by 8-byte ECC info, or sometimes 16-byte or 20-byte ECC, or no ECC at all). There are several \"backup\" copies of the blowfish/firmware blocks.

### Write Example

```
+----------------------------------------------------------------------------+
|       B2aaaaaaaa000000h - Select 128Kbyte RW access mode (unlesss already) |
|       8500000000000000h - NAND Write Enable                                |
|       81aaaaaaaa000000h - NAND Write to Write Buffer        + Data[200h]   |
|       81aaaaaaaa000000h - NAND Write to Write Buffer        + Data[200h]   |
|       81aaaaaaaa000000h - NAND Write to Write Buffer        + Data[200h]   |
|       81aaaaaaaa000000h - NAND Write to Write Buffer        + Data[200h]   |
|       8200000000000000h - NAND Forward Write Buffer to NAND                |
|       D600000000000000h - NAND Read Status                  + Data[4]      |
|       (...repeat reading status until bit5=1=ready...)                     |
|       8400000000000000h - NAND Discard SRAM write                          |
|       8B00000000000000h - NAND Select ROM access mode (if desired)         |
+----------------------------------------------------------------------------+
```


### Chipsets
Warioware D.I.Y., NTR-UORE:

```
+-----------------------------------------------------------------------+
|       PCB "DI X-7 C17-01"                                             |
|       Chip "SAMSUNG 004, KLC2811ANB-P204, NTR-UORE-0"                 |
+-----------------------------------------------------------------------+
```

Jam with the Band, NTR-UXBP:

```
+-----------------------------------------------------------------------+
|       PCB (Unknown)                                                   |
|       Chip "SAMSUNG 013, KLC2811UOC-P30A, NTR-UXBP-0, WKA069J2"       |
+-----------------------------------------------------------------------+
```

Face Training, TWL-USKV:

```
+-----------------------------------------------------------------------+
|       PCB "DI X-8 C17-01"                                             |
|       U1 "SAMSUNG 031, KLC2811UOC-P309, TWL-USKV-0, WKE114(80?)"      |
|       (this chip must be slightly different, for DSi mode support)    |
+-----------------------------------------------------------------------+
```

There are also a bunch of 3DS games with similar chips (with the RW area being called \"CARD2\" area on 3DS, and, the 3DS is using 16-byte commands, so the protocol is different).

### Notes
Unlike ROM carts, the NAND cart does crash upon invalid commands (and stops to respond to further commands). That is, upon invalid command numbers, upon ROM mode commands in RW mode (or vice-versa), upon any data lengths other than listed above.



