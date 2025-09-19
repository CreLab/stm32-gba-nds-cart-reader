# DS Cartridge Nitro Font Resource Format


**Nitro Font Resource File formats (compressed & uncompressed)**
Nitro Fonts are often found as .NFTR or .ZFTR files (within NitroROM
filesystems). The DSi firmware does additionally contain Nitro Fonts in
a .dat file (in the eMMC FAT16 filesystem).

```
+-----------------------------------------------------------------------+
|       .NFTR  Raw uncompressed Nitro Font Resource                     |
|       .ZFTR  LZ11-compressed Nitro Font Resource                      |
|       .dat   A                                                        |
| rchive with three LZrev-compressed Nitro Font Resources (used on DSi) |
+-----------------------------------------------------------------------+
```

The .ZFTR files are containing a 4-byte compression header, followed by
the compressed data (starting with the first compression flag byte,
following by the first chunk header). For details, see:
- [LZ Decompression Functions](./lzdecompressionfunctions.md)
The DSi\'s \"\\sys\\TWLFontTable.dat\" contains three fonts, using 
special LZ compression variant (with the data decompressed backwards,
starting at highest memory address). For details, see:
- [DSi SD/MMC Firmware Font File](./dsisdmmcfirmwarefontfile.md)
Either way, the decompressed fonts are looking as follows:

**Nitro Font Resource Header Chunk**

```
+-----------------------------------------------------------------------+
|                                                                       |
|    00h 4    Chunk ID "RTFN" (aka NFTR backwards, Nitro Font Resource) |
|       04h 2                                                           |
|  Byte Order    (FEFFh) (indicates that above is to be read backwards) |
|       06h 2    Version       (0100h..0102h) (usually 0101h or 0102h)  |
|       08h 4                                                           |
|    Decompressed Resource Size (000A3278h) (including the NFTR header) |
|                                                                       |
|     0Ch 2    Offset to "FNIF" Chunk, aka Size of "RTFN" Chunk (0010h) |
|                                                                       |
| 0Eh 2    Total number of following Chunks (0003h+NumCharMaps) (0018h) |
+-----------------------------------------------------------------------+
```


**Font Info Chunk**

```
+-----------------------------------------------------------------------+
|       00h      4    Chunk ID "FNIF" (aka FINF backwards, Font Info)   |
|       04h      4    Chunk Size (1Ch or 20h)                           |
|       08h      1    Unknown/unused (zero)                             |
|       09h xxx  1    Height                       ;or Height+/-1       |
|       0Ah xxx                                                         |
|   1    Unknown (usually 00h, or sometimes 1Fh maybe for chr(3Fh)="?") |
|       0Bh      2    Unknown/unused (zero)                             |
|       0Dh xxx  1    Width           ;\or Width+1                      
|       0Eh xxx  1    Width_bis (?)   ;/                                |
|       0Fh                                                             |
|       1    Encoding (0=UTF8, 1=Unicode, 2=SJIS, 3=CP1252) (usually 1) |
|       10h      4    Offset to Character Glyph chunk, plus 8           |
|       14h      4    Offset to Character Width chunk, plus 8           |
|       18h      4    Offset to first Character Map chunk, plus 8       |
|       1C                                                              |
| h      (1)  Tile Height                                ;\present only 
|                                                                       |
| 1Dh xxx  (1)  Max Width or so +/-?                       ; when above |
|       1Eh                                                             |
|    (1)  Underline location                         ; Chunk Size = 20h |
|       1Fh                                                             |
|     (1)  Unknown/unused (zero)                      ;/(version 0102h) |
+-----------------------------------------------------------------------+
```


**Character Glyph Chunk (Tile Bitmaps)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|   00h      4    Chunk ID "PLGC" (aka CGLP backwards, Character Glyph) |
|       04h      4    Chunk Size (10h+NumTiles*siz+padding)             |
|       08h      1    Tile Width in pixels                              |
|       09h      1    Tile Height in pixels                             |
|       0Ah      2    Tile Size in bytes (siz=width*height*bpp+7)/8)    |
|       0Ch      1    Underline location                                |
|                                                                       |
|     0Dh      1    Max proportional Width including left/right spacing |
|       0E                                                              |
| h      1    Tile Depth (bits per pixel) (usually 1 or 2, sometimes 3) |
|       0Fh      1    Tile Rotation (0=None/normal, other=see below)    |
|       10h      ...  Tile Bitmaps                                      |
|       ...      ...  Padding to 4-byte boundary (zerofilled)           |
+-----------------------------------------------------------------------+
```

All tiles are starting on a byte boundary. However, the separate
scanlines aren\'t necessarily byte-aligned (for example, at 10pix width
a byte may contain rightmost pixels of one line, followed by leftmost
pixels of next line).
Bit7 of the first byte of a bitmap is the MSB of the upper-left pixel,
bit6..0 are then containing the LSB(s) of the pixel (if bpp\>1)
followed by the next pixels of the scanline, followed by further
scanlines; the data is arranged as straight Width\*Height bitma
(without splitting into 8x8 sub-tiles).
Colors are ranging from Zero (transparent/background color) to all
bit(s) set (solid/text color).
The meaning of the Tile Rotation entry is unclear (one source claims
0=0\', 1=90\', 2=270\', 3=180\', and another source claims 0=0\'
2=90\', 4=180\', 6=270\', and for both sources, it\'s unclear if th
rotation is meant to be clockwise or anti-clockwise).

**Character Width Chunk**

```
+-----------------------------------------------------------------------+
|                                                                       |
|   00h      4    Chunk ID "HDWC" (aka CWDH backwards, Character Width) |
|       04h      4    Chunk Size (10h+NumTiles*3+padding)               |
|       08h      2    First Tile Number (should be 0000h)               |
|       0Ah      2    Last Tile Number  (should be NumTiles-1)          |
|       0Ch      4    Unknown/unused (zero)                             |
|                                                                       |
|  10h+N*3  1    Left Spacing (to be inserted left of character bitmap) |
|       1                                                               |
| 1h+N*3  1    Width of Character Bitmap (excluding left/right spacing) |
|                                                                       |
| 12h+N*3  1    Total Width of Character (including left/right spacing) |
|       ...      ...  Padding to 4-byte boundary (zerofilled)           |
+-----------------------------------------------------------------------+
```

Defines the proportional character width for each tile. Entry
- \[11h+N\*3\] defines the width of the non-transparent character are
(which left-aligned in the Tile Bitmap; any further pixels in the Bitmap
are unused/zero). The other two entries define the left/right spacing
that is needed to be added to the character.

**Character Map(s) - Translation Tables for ASCII/JIS/etc to Tile
Numbers?**

```
+-----------------------------------------------------------------------+
|                                                                       |
|     00h      4    Chunk ID "PAMC" (aka CMAP backwards, Character Map) |
|       04h      4    Chunk Size (14h+...+padding)                      |
|       08h      2    First Character (eg. 0020h=First ASCII Char)      |
|       0Ah      2    Last Character  (eg. 007Eh=Last ASCII Char)       |
|       0Ch      4    Map Type (0..2, for entry 14h and up, see there)  |
|       10h                                                             |
|      4    Offset to next Character Map, plus 8   (0=None, no further) |
+-----------------------------------------------------------------------+
```

For Map Type0, Increasing TileNo\'s assigned to increasing CharNo\'s:

```
+-----------------------------------------------------------------------+
|       1                                                               |
| 4h      2    TileNo for First Char (and increasing for further chars) |
|       16h      2    Padding to 4-byte boundary (zerofilled)           |
+-----------------------------------------------------------------------+
```

For Map Type1, Custom TileNo\'s assigned to increasing CharNo\'s:

```
+-----------------------------------------------------------------------+
|       14h+N                                                           |
| *2  2    TileNo's for First..Last Char (FFFFh=None; no tile assigned) |
|       ...      0/2  Padding to 4-byte boundary (zerofilled)           |
+-----------------------------------------------------------------------+
```

For Map Type2, Custom TileNo\'s assigned to custom CharNo\'s:

```
+-----------------------------------------------------------------------+
|       14h      2    Number of following Char=Tile groups...           |
|       16h+N*4  2    Character Number                                  |
|       18h+N*4  2    Tile Number                                       |
|       ...      2    Padding to 4-byte boundary (zerofilled)           |
+-----------------------------------------------------------------------+
```

These chunks are containing tables for translating character numbers
(eg. Unicode numbers, or whatever format is selected in the Font Info
chunk) to actual Tile Numbers (ie. the way how tiles are ordered in the
Glyph and Width chunks).
Font files can contain several Character Map chunks (eg. some Type0
chunks for Char 0020h..007Eh and Char 00A0h..00FFh, plus some Type1
chunks for areas like Char 037Eh..0451h, plus one large Type2 chunk for
everything that wasn\'t defined in the other chunks; the First/Las
Character entries are don\'t care for Type2, they are usually set t
First=0000h and Last=FFFFh in that case). Characters that are NOT
included in any of the tables should be treated as undefined (as so for
any characters that are assigned as Tile=FFFFh in Type1 chunks).
Unicode character numbers are stored as 16bit values. Unknown how other
character numbers like UTF8 or SJIS are stored.



