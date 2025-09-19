# DSi SD/MMC Camera Files - pit.bin


### FAT12:\\photo\\private\\ds\\app\\484E494A\\pit.bin (8K) (camera info)
### SD:\\private\\ds\\app\\484E494A\\pit.bin (47K) (camera info)

```
+----------------------------------------------------------------------------------+
|       0000h       8  ID ("0TIP00_1") (maybe meant to read as PIT01_00 or so)     |
|       0008h       2  Number of pit.bin entries (3000 for SD Card) (500 for eMMC) |
|       000Ah       2  Unknown (0001h)                                             |
|       000Ch       2  Next Photo Folder-Number minus 100  (xxxNIN02)              |
|       000Eh       2  Next Photo File-Number minus 1      (HNB_0xxx.JPG)          |
|       0010h       2  Next Frame Folder-Number minus 100  (xxxNIN02)              |
|       0012h       2  Next Frame File-Number minus 1      (HNB_0xxx.JPG)          |
|       0014h       2  CRC16 of whole file (with initial value 0000h, and with     |
|                      entry [0014h] being treated as 0000h for calculation)       |
|       0016h       2  Size of Header (0018h)                                      |
|       0018h+N*10h 4  Entry N, Time/Date (seconds since 01 Jan 2000)              |
|       001Ch+N*10h 8  Entry N, Unknown (zerofilled)                               |
|       0024h+N*10h 4  Entry N, Flags (see below)                                  |
|                       0     Used Entry Flag (0=Unused/Deleted, 1=Used)           |
|                       1-10  Folder-Number minus 100 (xxxNIN02)                   |
|                       11-17 File-Number minus 1     (0..99 = HNB_0001..0100.JPG) |
|                       18-19 Sticker (0=None, 1=Star, 2=Clover, 3=Heart)          |
|                       20-21 Type (0,3=Photo, 1=Frame, 2=?)                       |
|                       22-23 Unknown (0,2=Normal?, 1=?, 3=Error)                  |
|                       24-31 Unused (zero)                                        |
|       xxx8h       8  Padding for 16-byte filesize alignment (zerofilled)         |
+----------------------------------------------------------------------------------+
```

The \"Next Photo/Frame\" entries contain File/Folder Numbers where the next images will be saved; that file numbers increase after saving, and do eventually wrap to next higher folder number.
The Nintendo DSi Camera utility shows only photos listed in \"pit.bin\", when manually copying jpg\'s to SD Card one could:

```
+------------------------------------------------------------------------------------+
|      - Delete "pit.bin" (it'll be recreated with ALL jpgs, sticker flags are lost) |
|      - Replace an existing 'listed' file by a new file with same filename          |
|      - Manually edit "pit.bin" and adjust its CRC16 checksum                       |
+------------------------------------------------------------------------------------+
```

Photos are region free, can be viewed from any other DSi\'s (as long as they are listed in pit.bin). However, they do require some signature in Exif header, so in general, the DSi accepts only images that come from DSi consoles; not images from other sources.

### Stickers
Photos with \"Star\" sticker are shown as background picture in System Menu; this works only for images stored in internal eMMC memory (images on SD Card can have stickers, too, but they are ignored by System Menu).



