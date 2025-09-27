# DS Cartridge Icon/Title


The ROM offset of the Icon/Title is defined in CartHdr\[68h\]. The size was originally implied by the size of the original Icon/Title structure rounded to 200h-byte sector boundary (ie. A00h bytes for Version 1 or 2), however, later DSi carts (with CartHdr\[1Ch\].bit0=1) are having a size entry at CartHdr\[208h\] (usually 23C0h).
If present (ie. if CartHdr\[68h\]=nonzero), then Icon/Title are displayed in the bootmenu.

```
+-------------------------------------------------------------------------------------+
|       0000h 2     Version (0001h, 0002h, 0003h, or 0103h)                           |
|       0002h 2     CRC16 across entries 0020h..083Fh (all versions)                  |
|       0004h 2     CRC16 across entries 0020h..093Fh (Version 0002h and up)          |
|       0006h 2     CRC16 across entries 0020h..0A3Fh (Version 0003h and up)          |
|       0008h 2     CRC16 across entries 1240h..23BFh (Version 0103h and up)          |
|       000Ah 16h   Reserved (zero-filled)                                            |
|       0020h 200h  Icon Bitmap  (32x32 pix) (4x4 tiles, 4bit depth) (4x8 bytes/tile) |
|       0220h 20h   Icon Palette (16 colors, 16bit, range 0000h-7FFFh)                |
|                   (Color 0 is transparent, so the 1st palette entry is ignored)     |
|       0240h 100h  Title 0 Japanese  (128 characters, 16bit Unicode)                 |
|       0340h 100h  Title 1 English   ("")                                            |
|       0440h 100h  Title 2 French    ("")                                            |
|       0540h 100h  Title 3 German    ("")                                            |
|       0640h 100h  Title 4 Italian   ("")                                            |
|       0740h 100h  Title 5 Spanish   ("")                                            |
|       0840h 100h  Title 6 Chinese   ("")                 (Version 0002h and up)     |
|       0940h 100h  Title 7 Korean    ("")                 (Version 0003h and up)     |
|       0A40h 800h  Zerofilled (probably reserved for Title 8..15)                    |
+-------------------------------------------------------------------------------------+
```

Below for animated DSi icons only (Version 0103h and up):

```
+---------------------------------------------------------------------------------+
|       1240h 1000h Icon Animation Bitmap 0..7 (200h bytes each, format as above) |
|       2240h 100h  Icon Animation Palette 0..7 (20h bytes each, format as above) |
|       2340h 80h   Icon Animation Sequence (16bit tokens)                        |
+---------------------------------------------------------------------------------+
```

Unused/padding bytes:

```
+-----------------------------------------------------------------------+
|       0840h 1C0h  Unused/padding (FFh-filled) in Version 0001h        |
|       0940h C0h   Unused/padding (FFh-filled) in Version 0002h        |
|       23C0h 40h   Unused/padding (FFh-filled) in Version 0103h        |
+-----------------------------------------------------------------------+
```


### Versions

```
+-----------------------------------------------------------------------+
|       0001h = Original                                                |
|       0002h = With Chinese Title                                      |
|       0003h = With Chinese+Korean Titles                              |
|       0103h = With Chinese+Korean Titles and animated DSi icon        |
+-----------------------------------------------------------------------+
```


### Title Strings
Usually, for non-multilanguage games, the same (english) title is stored in all title entries. The title may consist of ASCII characters 0020h-007Fh, character 000Ah (linefeed), and should be terminated/padded by 0000h.
The whole text should not exceed the dimensions of the DS cart field in the bootmenu (the maximum number of characters differs due to proportional font).
The title is usually split into a primary title, optional sub-title, and manufacturer, each separated by 000Ah character(s). For example: \"America\", 000Ah, \"The Axis of War\", 000Ah, \"Cynicware\", 0000h.

### Icon Animation Sequence (DSi)
The sequence is represented by 16bit tokens, in the following format:

```
+-----------------------------------------------------------------------+
|       15    Flip Vertically   (0=No, 1=Yes)                           |
|       14    Flip Horizontally (0=No, 1=Yes)                           |
|       13-11 Palette Index     (0..7)                                  |
|       10-8  Bitmap Index      (0..7)                                  |
|       7-0   Frame Duration    (01h..FFh) (in 60Hz units)              |
+-----------------------------------------------------------------------+
```

Value 0000h indicates the end of the sequence. If the first token is 0000h, then the non-animated default image is shown.
Uh, actually, a non-animated icon uses values 01h,00h,00h,01h, followed by 7Ch zerofilled bytes (ie. 0001h, 0100h, 3Eh x 0000h)?

### FAT16:\\title\\000300tt\\4ggggggg\\data\\banner.sav ;if carthdr\[1BFh\].bit2=1
Some DSi games are having a separate \"banner.sav\" file stored in the eMMC filesystem, enabled via carthdr\[1BFh\].bit2 (allowing to indicate the game progress by overriding the default icon). The banner files are 4000h bytes in size, the animation data is same as above, but without title strings and without non-animated icon.

```
+----------------------------------------------------------------------------------+
|       0000h 2     Version (0103h)                                                |
|       0002h 6     Reserved (zero-filled)                                         |
|       0008h 2     CRC16 across entries 0020h..119Fh (with initial value FFFFh)   |
|       000Ah 16h   Reserved (zero-filled)                                         |
|       0020h 1000h Icon Animation Bitmap 0..7 (200h bytes each)  ;\same format as 
|       1020h 100h  Icon Animation Palette 0..7 (20h bytes each)  ; in Icon/Title  |
|       1120h 80h   Icon Animation Sequence (16bit tokens)        ;/               |
|       11A0h 2E60h Garbage (random values, maybe due to eMMC decryption)          |
+----------------------------------------------------------------------------------+
```

The feature is used by some Brain Age Express games (for example, Brain Age Express Sudoku: \'title\\00030004\\4b4e3945\\data\\banner.sav\').
The feature does probably work only for DSiware titles (unless there are any DSi carts with SD/MMC access enabled; or unless there is a feature for storing similar data in cartridge memory).



