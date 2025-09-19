# DSi SD/MMC Camera Files - Overview


**Photos/Frames**
Photos can be taken via Nintendo DSi Camera utitilty (or alternately,
directly via hotkeys in System Menu; which will be automatically
flagging the photos with \"Star\" stickers, which will cause them to b
shown as System Menu background image).
Frames are masks (with transparent pixels) that can be put onto photos.
The Frames can be created via Nintendo DSi Camera utility (Camera,
select Frame (upper-right Lens option), accept that Lens, then click
Create Frame; the procedure then is to take a photo, and to rub-out
pixels on touchscreen to make them transparent).

**Internal/External Storage**
The Camera is storing further data on the eMMC FAT12 partition:

```
+-----------------------------------------------------------------------+
|       FAT12:\p                                                        
| hoto\DCIM\100NIN02\HNI_nnnn.JPG                        ;camera photos 
|       FAT12:                                                          |
| \photo\private\ds\app\484E494A\pit.bin                   ;camera info 
|       FAT12:\p                                                        
| hoto\private\ds\app\484E494A\DCIM\100NIN02\HNI_nnnn.JPG;camera frames 
+-----------------------------------------------------------------------+
```

Camera data can be copied to SD card (via Nintendo DSi Camera, Options,
Copy):

```
+-----------------------------------------------------------------------+
|       SD:                                                             |
| \DCIM\nnnNIN02\HNI_nnnn.JPG                            ;camera photos 
|       S                                                               |
| D:\private\ds\app\484E494A\pit.bin                       ;camera info 
|       SD:                                                             |
| \private\ds\app\484E494A\DCIM\nnnNIN02\HNI_nnnn.JPG    ;camera frames 
+-----------------------------------------------------------------------+
```

And, in internal eMMC only (not on SD), the DSi is somewhere storing
Calendar entries (some sort of bitmaps with optional handwritten
comments drawn via touchscreen).

**File/Folder Numbers**
The \"nnnNIN02\" folders are numbered \"100NIN02\" through \"999NIN02\"
The first folder is usually 100NIN02, unless another \"100xxxxx\" folde
did already exist (eg. if the SD card contains a \"100CANON\" folder
then DSi would start at 101NIN02 or higher).
The trailing \"02\" of the \"nnnNIN02\" folders appears to be fixed fo
DSi photos (folder name \"nnnNIN01\" is reserved for Wii screenshots).
The \"HNI_nnnn.JPG\" filenames are numbered \"HNI_0001.JPG\" throug
\"HNI_0100.JPG\", thereafter, the DSi will switch to next higher folde
number, and wrap to using \"HNI_0001.JPG\" as first filename in tha
folder.
The weird \"484E494A\" folder name is based on the japanese Nintendo DS
Camera\'s gamecode (HNIJ) converted to an 8-digit uppercase HEX strin
(this appears to be always the japanese gamecode, even on european DSi
consoles).



