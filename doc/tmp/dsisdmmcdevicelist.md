# DSi SD/MMC Device List


The Device List is automatically copied to ARM7 RAM address defined in cartheader\[1D4h\] by firmware. The 400h-byte list is mainly used for DSiware/firmware titles (DSi ROM titles will usually just receive an empty zerofilled 400h-byte list; unless maybe if they are flagged to use SD/MMC hardware in cartheader?). There appears to be no range check for the cartheader\[1D4h\] entry (setting it to zero causes the list to be \'written\' to ARM7 ROM area).

### Device List, 400h-bytes, loaded to ARM7/RAM address from cartheader\[1D4h\]

```
+-------------------------------------------------------------------------------------+
|       000h 54h*11 Device List (max 11 entries)                                      |
|       39Ch 24h    Zerofilled                                                        |
|       3C0h 40h    Name 'nand:/title/000300tt/4ggggggg/content/000000vv.app' + 00h's |
+-------------------------------------------------------------------------------------+
```

Format of the 54h-byte device list entries:

```
+-----------------------------------------------------------------------+
|       00h  1    Drive Letter ("A".."I")                               |
|       01h  1    Flags (see below)                                     |
|       02h  1    Access Rights (bit1=Write, bit2=Read)                 |
|       03h  1    Zero                                                  |
|       04h  10h  Device Name (eg. "nand" or "dataPub") (zeropadded)    |
|       14h  40h  Path        (eg. "/" or "nand:/shared1") (zeropadded) |
+-----------------------------------------------------------------------+
```

Bits in Flags byte:

```
+-----------------------------------------------------------------------------------+
|       0    Physical Drive (0=External SD/MMC Slot, 1=Internal eMMC)               |
|       1-2  Zero (maybe MSBs of Drive)                                             |
|       3-4  Device Type (0=Physical, 1=Virtual/File, 2=Virtual/Folder, 3=Reserved) |
|       5    Partition (0=1st, 1=2nd)                                               |
|       6    Zero (maybe MSB of Partition)                                          |
|       7    Encrypt? (set for eMMC physical devices; not for virtual, not for SD)  |
+-----------------------------------------------------------------------------------+
```

The DSi has 9 default devices (\"A\"-\"I\"):

```
+------------------------------------------------------------------------------------+
|       Letter/Flags     Name       Path                   ;Notes                    |
|       'A',81h,06h,00h  'nand'     '/'                    ;eMMC Cart Partition 1    |
|       'B',A1h,06h,00h  'nand2'    '/'                    ;eMMC Cart Partition 2    |
|       'C',11h,04h,00h  'content'  'nand:/title/000300tt/4ggggggg/content'          |
|       'D',11h,04h,00h  'shared1'  'nand:/shared1'        ;TWLCFGn.dat              |
|       'E',11h,06h,00h  'shared2'  'nand:/shared2'        ;Sound and wrap.bin       |
|       'F',31h,06h,00h  'photo'    'nand2:/photo'         ;Camera photos/frames     |
|       'G',09h,06h,00h  'dataPrv'  'nand:/title/000300tt/4ggggggg/data/private.sav' |
|       'H',09h,06h,00h  'dataPub'  'nand:/title/000300tt/4ggggggg/data/public.sav'  |
|       'I',00h,06h,00h  'sdmc'     '/'                    ;SD Cart Partition 1      |
+------------------------------------------------------------------------------------+
```

Depending on the cartheader, usually only 5-8 of that 9 devices are copied to the device list in RAM, and Access Rights for some devices can be crippled in the RAM list entries.
Caution: The list may not contain forward references (eg. one can redirect \"dataPub\" to \"sdmc:/flipnote.pub\", but that works only if \"sdmc\" was already defined in one of the previous entries).
A and B: These physical eMMC partitions are always included in the list (because they are needed as parent entries for Virtual devices), however, their Access Rights are usually set to 00h (unless Title ID indicates a system file; with cartheader\[234h\].bit4=1).
C and E: These virtual devices are passed ONLY to System Menu (Launcher)\... hmmm, or actually, the Launcher doesn\'t receive ANY device list at all?
G and H: Present only if Title ID indicates DSiware/firmware; with cartheader\[234h\].bit2=1 (ie. not ROM carts), and only if public/private.sav sizes are nonzero in carthdr\[238h/23Ch\].
A-H: removed from list if carthdr\[1B4h\].4=0 (no eMMC access).
I: removed from list if carthdr\[1B4h\].3=0 (no SD card access).
Some games may adjust the Device List AFTER booting. For example, Flipnote changes the \"photo\" (F) Access Rights to 04h, and appends an extra device at the end of the list, using a spare drive letter (C):

```
+-----------------------------------------------------------------------+
|       'C',09h,06h,00h  'share'    'nand:/shared2/0000'   ;Sound file  |
+-----------------------------------------------------------------------+
```

Other device names that have been spotted here or there:

```
+-----------------------------------------------------------------------+
|       'verdata'   for Version Data NARC file                          |
|       'rom'       for executable's NitroROM filesystem                |
|       'otherPub'                                                      |
|       'otherPrv'                                                      |
+-----------------------------------------------------------------------+
```

Apart from Virtual Devices, there are also some Virtual Filename Placeholders:

```
+------------------------------------------------------------------------------------+
|       'nand:/<tmpjump>'     --> 'nand:/tmp/jump.app'                               |
|       'nand:/<sharedFont>'  --> 'nand:/sys/TWLFontTable.dat'                       |
|       'nand:/<verdata>'     --> 'nand:/title/0003000f/484e4c%02x/content/%08x.app' |
|       'nand:/<banner>'      --> ..... '/data/banner.sav'                           |
|       ':<srl>'              --> .....                                              |
+------------------------------------------------------------------------------------+
```


### public & private savedata
If the file is in a folder named \"CONTENT\", then savedata is stored in a separata \"DATA\" folder (this is as how Nintendo is doing it officially):

```
+-----------------------------------------------------------------------+
|       "nand:/../CONTENT/title.tmd"                                    |
|       "nand:/../CONTENT/00000002.app"                                 |
|       "nand:/../DATA/public.sav"                                      |
|       "nand:/../DATA/private.sav"                                     |
+-----------------------------------------------------------------------+
```

If the file is anywhere else (not in a CONTENT folder), then savedata should be stored in the same folder & same name, with extension changed to .pub or .prv (this homebrew convention allows to use more descriptive non-numeric filenames, and doesn\'t require \"title.tmd\"):

```
+-----------------------------------------------------------------------+
|       "sdmc:/../My Folder Name/Filpnote Studio (EUR.AUS).dsi"         |
|       "sdmc:/../My Folder Name/Filpnote Studio (EUR.AUS).pub"         |
|       "sdmc:/../My Folder Name/Filpnote Studio (EUR.AUS).prv"         |
+-----------------------------------------------------------------------+
```

As seen above, names can exceed the 8.3 character shortfilename limit (and can use 16bit unicode), however, using such long filenames can quickly exceed the 64 character limit of the DSi\'s Device List (or it\'s 8bit character space), as a workaround, unlaunch is converting the above names to 8.3 character format before storing them in the Device List:

```
+-----------------------------------------------------------------------+
|       "sdmc:/../MYFOLD~1/FLIPN~12.DSI"                                |
|       "sdmc:/../MYFOLD~1/FLIPN~10.PUB"                                |
|       "sdmc:/../MYFOLD~1/FLIPNO~2.PRV"                                |
+-----------------------------------------------------------------------+
```

With those short 8-character folder names, one can have up to five folders nested (or only three folders with extension alike \"MYFOLD\~1.EXT\", or more than five folders if folder/filename are shorter than 8 characters).
As shown in the above examples, the longname (\"Filpnote Studio (EUR.AUS)\") is same for all three files, but the \~NN suffix may vary for shortnames.



