# DSi SD/MMC Images


### Filesystem Viewer
no\$gba debug version is allowing to view the filesystem tree from encrypted eMMC images (via menubar: Window, Filesystem), the filesystem viewer is also able to export single files from eMMC and SD images (by double-clicking separate files).

### Emulation
No\$gba emulates read/write-accesses to eMMC images.
Another idea for future would be using files & folders on the PC filesystem instead of a single image file (that might be easier to deal with in some cases, but for the reverse-engineering stage it\'s better to stick with original authentic images).

### Encrypted eMMC Images
no\$gba can emulate up to 12 consoles simultaneously, and expects the eMMC images having following filename(s), in no\$gba folder:

```
+-----------------------------------------------------------------------+
|       DSi-#.mmc             ;eMMC for machine 1..12 (# = 1..C hex)    |
+-----------------------------------------------------------------------+
```

the eMMC images are encrypted with per-console keys, so decryption won\'t work without knowing the console ID values. no\$gba expects that info to be stored in a 40h-byte Footer at the end of the file:

```
+-------------------------------------------------------------------------------------+
|       00000000h .. Encrypted eMMC image (usually 240Mbyte for DSi)                  |
|       0F000000h 16 Footer ID      ("DSi eMMC CID/CPU")                              |
|       0F000010h 16 eMMC CID       (dd ss ss ss ss 03 4D 30 30 46 50 41 00 00 15 00) |
|       0F000020h 8  CPU/Console ID (nn n1 nn nn nn nn xn 08)                         |
|       0F000028h 24 Reserved       (zerofilled)                                      |
+-------------------------------------------------------------------------------------+
```

Alternately, the \"footer\" can be stored in the zerofilled area at eMMC offset 000FF800h..000FF83Fh (using that area, the data can be kept in place even when using other tools; that were getting confused by the data appended at end of file).

### SD Card Images
no\$gba supports SD Card images in similar fashion as above eMMC images, but without needing any footer since there\'s encryption on SD cards. The image should contain a pre-formatted MBR and FAT (as real SD cards do).

```
+-----------------------------------------------------------------------+
|       DSi-#.sd              ;SD Card for machine 1..12 (# = 1..C hex) |
+-----------------------------------------------------------------------+
```

note: no\$gba does currently support only 128MB SDSC images (the CID, CSD, OCR, SCR, SSR registers are hardcoded for images with 125698048 byte size), there is a .zip file with an empty pre-formatted SD image in the no\$gba package (if you want to use that image: unzip it to the no\$gba folder).

### Dumping eMMC Images
DSiware exploits like sudokuhax are allowing to access SD/MMC hardware (so one could simply copy all eMMC sectors to a file on SD Card).
Unfortunately, most/other exploits don\'t have SD/MMC access, so dumping would work only when the eMMC chip to a SD/MMC card reader. For details, see:
- [AUX DSi SD/MMC Pin-Outs](./auxdsisdmmcpinouts.md)
For obtaining the Console IDs, see:
- [DSi Console IDs](./dsiconsoleids.md)



