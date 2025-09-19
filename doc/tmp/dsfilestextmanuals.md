# DS Files - Text Manuals


Manual files are common in DSiware download titles, unknown if DS/DSi cartridges did also use that files (or if they did stick with print manuals).
Used in DSi Flipnote, Sudoku, Paper Plane, Deep Psyche, Dr. Mario, DSi-to-3DS Transfer Tool.
Usually found in \"rom:\\..\\manpages_narc.blz\" (with two folders in the .blz file, \"arc\" for the manual, and \"gpArc\" with a quick reference on how to read the manual; the latter containing only two \"pages\", without \"content\" file).

### NTLI File (manual language info) (in \"ntli\" folder)

```
+-----------------------------------------------------------------------+
|       000h 4     ID "NTLI"                                            |
|       004h 2     Byte Order  (FEFFh)                                  |
|       006h 2     Version     (can be 0200h)                           |
|       008h 4     Total Filesize                                       |
|       00Ch 2     Header Size (10h)                                    |
|       00Eh 4     Number of Chunks (usually 1 = mtl1)                  |
+-----------------------------------------------------------------------+
```

### mtl1 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "mtl1"                                      |
|       004h 4     Chunk Size                                           |
|       008h 4     Number of supported languages                        |
|       00Ch 2*N   Language IDs (two-letter ASCII spelled backwards)    |
+-----------------------------------------------------------------------+
```

Known IDs are ne=English, rf=French, se=Spanish, ti=Italian, ed=German.
EUR games do usually support 5 languages (Deep Psyche supports less).
IDs for Japanese/Chinese/Korean are unknown (also unknown if US has different IDs for english/spanish etc, and if portugese or so do exist on DSi).
Note: The two-letters do directly translate to the \"ntmc\\xx\\\" and \"ntpg\\xx\\\" folder names.

### NTMC File (manual contents) (in \"ntmc\\xx\\\" folders)
The content contains \"hyperlinks\" to the actual chapters. A chapter can be divided into subsections (with the subsections being shown at the right of the main chapter name).

```
+-----------------------------------------------------------------------+
|       000h 4     ID "NTMC"                                            |
|       004h 2     Byte Order  (FEFFh)                                  |
|       006h 2     Version     (can be 0200h)                           |
|       008h 4     Total Filesize                                       |
|       00Ch 2     Header Size (10h)                                    |
|       00Eh 4     Number of Chunks (usually 3 = nap1+txp1+mtc1)        |
+-----------------------------------------------------------------------+
```

### nap1 Chunk

```
+-------------------------------------------------------------------------+
|       000h 4     Chunk ID "nap1"                                        |
|       004h 4     Chunk Size                                             |
|       008h 4     Number of chapters (aka pages) minus 1?  (eg. 18h=19h) |
|       00Ch 4*N   Offsets to filenames (from nap+0Ch)                    |
|       ...  ..    Filenames (ASCII, terminated by 00h)                   |
+-------------------------------------------------------------------------+
```

### txp1 Chunk

```
+---------------------------------------------------------------------------------+
|       000h 4     Chunk ID "txp1"                                                |
|       004h 4     Chunk Size                                                     |
|       008h 4     Number of something?? minus 1            (eg. 25h=26h)         |
|       00Ch 4*N   Offsets to something?? (from txp1+0Ch)                         |
|       ...  ..    Somewhat corrupt UTF-16 strings (many aborted with char 20xxh) |
+---------------------------------------------------------------------------------+
```

### mtc1 Chunk

```
+-----------------------------------------------------------------------------+
|       000h 4     Chunk ID "mtc1"                                            |
|       004h 4     Chunk Size                                                 |
|       008h 4     Number of dunno what                  (eg. 0Dh=Much more?) |
|       00Ch 2*?   16bit Indices in txp1? (eg. 0000h..0025h)                  |
+-----------------------------------------------------------------------------+
```


### NTPG File (manual pages) (or rather chapters?) (in \"ntpg\\xx\\\" folders)
The pages can contain text, tables, and symbols/images/screenshots (there appears to be no support for hyperlinks inside of the pages; probably because they default to be displayed on upper screen, without touchscreen support).

```
+------------------------------------------------------------------------------------+
|       000h 4     ID "NTPC"                                                         |
|       004h 2     Byte Order  (FEFFh)                                               |
|       006h 2     Version     (can be 0200h)                                        |
|       008h 4     Total Filesize                                                    |
|       00Ch 2     Header Size (10h)                                                 |
|       00Eh 4     Number of Chunks (usually 7 = nap1+txp1+pag1+pan1+pas1+txt1+pae1) |
+------------------------------------------------------------------------------------+
```

### nap1 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "nap1"                                      |
|       004h 4     Chunk Size (10h)                                     |
|       008h 4     Zero (unlike as in NTMC file)                        |
|       00Ch 4     Unknown (4)                                          |
+-----------------------------------------------------------------------+
```

### txp1 Chunk

```
+-------------------------------------------------------------------------+
|       000h 4     Chunk ID "txp1"                                        |
|       004h 4     Chunk Size                                             |
|       008h 4     Number of something?? minus 1            (eg. 02h=03h) |
|       00Ch 4*N   Offsets to something?? (from txp1+0Ch)                 |
|       ...  ..    UTF-16 strings (Headline, Body, Footer?)               |
+-------------------------------------------------------------------------+
```

### pag1 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "pag1"                                      |
|       004h 4     Chunk Size (10h)                                     |
|       008h 2?    0000h text color black?                              |
|       00Ah 2?    0160h link color or so?                              |
|       00Ch 2?    7FFFh bg color white?                                |
|       00Eh 2?    0000h                                                |
+-----------------------------------------------------------------------+
```

### pan1 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "pan1"                                      |
|       004h 4     Chunk Size (10h)                                     |
|       008h 2?    0000h                                                |
|       00Ah 2?    0000h                                                |
|       00Ch 2?    0100h                                                |
|       00Eh 2?    0160h link color or so?                              |
+-----------------------------------------------------------------------+
```

### pas1 Chunk (start?)

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "pan1"                                      |
|       004h 4     Chunk Size (0Ch)                                     |
|       008h 4?    00000001h                                            |
+-----------------------------------------------------------------------+
```

### txt1 Chunk

```
+---------------------------------------------------------------------------------+
|       000h 4     Chunk ID "txt1"                                                |
|       004h 4     Chunk Size                                                     |
|       008h 2?    0008h                                                          |
|       00Ah 2?    0008h                                                          |
|       00Ch 2?    00F0h                                                          |
|       00Eh 2?    0150h                                                          |
|       010h 2?    0001h                                                          |
|       012h 2?    0015h  Number of 8-byte entries? start/end line-wrapping list? |
|       014h 2?    000Dh                                                          |
|       016h 2?    0010h                                                          |
|       018h 4?    00000000h                                                      |
|       01Ch 4?    00001CE7h                                                      |
|       020h 4?    00000000h                                                      |
|       024h 4?    00000000h                                                      |
|       028h N*8   Unknown 8-byte entries? (00xxh,0010h,0000h,00yyh)              |
|                  Or maybe positioning for symbols/images/tables?                |
+---------------------------------------------------------------------------------+
```

### pae1 Chunk (end?)

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "pae1"                                      |
|       004h 4     Chunk Size (08h)                                     |
+-----------------------------------------------------------------------+
```


### NTTF File (manual graphics/symbols) (in \"nttf\" folder)

```
+----------------------------------------------------------------------------------+
|       000h 2  Bitmap Width in bytes (eg. 0Fh, 10h, 14h, 40h, 60h)                |
|       002h 2  Bitmap Height         (eg. 12h, 0Eh, 14h, 30h, 47h)                |
|       004h 1  Unknown, maybe Texture Format? (always 04h=256-Color?)             |
|       005h 1  Unknown, maybe Color0.alpha?   (00h or 01h) (often same as [007h]) |
|       006h 2  Number of Palette entries (usually 10h, 80h, or 100h)              |
|       008h 8  Zerofilled                                                         |
|       010h .. Palette data (with 16bit values in range 0000h..7FFFh)             |
|       ...  .. Bitmap data (seems to be always 8bpp)                              |
+----------------------------------------------------------------------------------+
```

Width/height can be odd (the bitmap doesn\'t contain any padding to even width/height\... except, maybe padding to bytesize in case color depths other than 8bpp should exist?).

### Notes
DSi manuals are using the TWLFontTable.dat system font (Flipnote, at least).
3DS manuals consist of CLYT and CLIM files (inside of a manual BCMA darc archive in a NCCH file).



