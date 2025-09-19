# DSi SD/MMC Summary of SD/MMC Files/Folders


### File/folder names
The DSi is using weird numeric strings as file/folder names:

```
+----------------------------------------------------------------------------------+
|       000000vv Title Version (lowercase hex32bit) from tmd[1E4h] as carthdr[1Eh] |
|       4ggggggg Title ID Gamecode (hex) as carthdr[230h..233h]                    |
|       000300tt Title ID Filetype (hex) as carthdr[234h..237h]                    |
|       HNI_nnnn Camera photo/frame files (nnnn = 0001..0100 decimal)              |
|       nnnNIN02 Camera photo/frame folders (nnn = 100..999 decimal)               |
+----------------------------------------------------------------------------------+
```

The \"000300tt\" can be:

```
+------------------------------------------------------------------------------------+
|       00030000 ROM Cartridges (as so for ROMs, doesn't appear in SD/MMC files)     |
|       00030004 DSiware (browser, flipnote, and games) (if any installed)           |
|       00030005 System Fun Tools (camera, sound, zone, pictochat, ds download play) |
|       0003000f System Data (non-executable, without carthdr)                       |
|       00030015 System Base Tools (system settings, dsi shop, 3ds transfer tool)    |
|       00030017 System Menu (launcher)                                              |
+------------------------------------------------------------------------------------+
```

The \"4ggggggg\" can be (last two digits are region(s), or \"41\" for all regions):

```
+-----------------------------------------------------------------------------------+
|       484e41gg System Menu (Launcher)                                             |
|       484e42gg System Settings                                                    |
|       484e4341 Wifi Firmware (non-executable datafile) (all regions)              |
|       484e4441 DS Download Play (all regions)                                     |
|       484e4541 Pictochat (all regions) (no update available)                      |
|       484e46gg Nintendo DSi Shop                                                  |
|       484e47gg Nintendo DSi Browser                                               |
|       484e4841 Nintendo DS Cart Whitelist (non-executable datafile) (all regions) |
|       484e49gg Nintendo DSi Camera                                                |
|       484e4agg Nintendo Zone (doesn't exist in Korea)                             |
|       484e4bgg Nintendo DSi Sound                                                 |
|       484e4cgg Version Data (non-executable datafile)                             |
|       484e4fgg Nintendo 3DS Transfer Tool                                         |
|       484E494A Nintendo DSi Camera Data (uppercase) ("japan") (aka all regions)   |
|       4b44474a Dokodemo Wii no Ma (japan only)                                    |
|       4b4755gg Flipnote Studio (doesn't exist in Korea/China)                     |
|       42383841 DS Internet settings (a new DSi tool on 3DS consoles)              |
|       4bgggggg DSiware games... (whatever games you have purchased, if any)       |
+-----------------------------------------------------------------------------------+
```

These files can be stored in Internal eMMC, or on external SD card, and can be downloaded from Nintendo\'s server (when buying games, or updating system files).

### DSi Internal eMMC
Internal eMMC can contain System files and any purchased DSiware games:

```
+-------------------------------------------------------------------------------------+
|       FAT16:\ticket\000300tt\4ggggggg.tik (encrypted)      ;ticket (708 bytes)      
|       FAT16:\title\000300tt\4ggggggg\content\title.tmd     ;tmd (520 bytes)         
|       FAT16:\title\000300tt\4ggggggg\content\000000vv.app  ;executable (decrypted)  
|       FAT16:\title\000300tt\4ggggggg\data\public.sav       ;size as carthdr[238h]   
|       FAT16:\title\000300tt\4ggggggg\data\private.sav      ;size as carthdr[23Ch]   
|       FAT16:\title\000300tt\4ggggggg\data\ec.cfg           ;dsi shop only           
|       FAT16:\title\000300tt\4ggggggg\data\banner.sav       ;if carthdr[1BFh].bit2=1 
+-------------------------------------------------------------------------------------+
```

Note that some of the above files are containing their own virtual filesystem inside of the eMMC\'s FAT16 filesystem (NitroROM filesystems in \"000000vv.app\" files, and FAT12 filesystems in \"public.sav\" and \"private.sav\" files).
The System tools (menu, settings, and shop) are also storing further data on FAT16 (outside of the ticket and title folders):

```
+----------------------------------------------------------------------------------+
|       FAT16:\shared1\TWLCFG0.dat            ;16K                                 
|       FAT16:\shared1\TWLCFG1.dat            ;16K                                 
|       FAT16:\shared2\launcher\wrap.bin      ;16K                                 
|       FAT16:\shared2\0000                   ;2048K (sound recorder)              
|       FAT16:\sys\log\product.log            ;573 bytes                           
|       FAT16:\sys\log\sysmenu.log            ;16K                                 
|       FAT16:\sys\log\shop.log               ;32 bytes                            
|       FAT16:\sys\HWINFO_S.dat               ;16K                                 
|       FAT16:\sys\HWINFO_N.dat               ;16K                                 
|       FAT16:\sys\cert.sys                   ;3904 bytes (or 2560 bytes)          
|       FAT16:\sys\HWID.sgn                   ;256 bytes (unknown purpose/content) 
|       FAT16:\sys\TWLFontTable.dat           ;843.1K (D2C40h bytes) (compressed)  
|       FAT16:\sys\dev.kp                     ;446 bytes (encrypted)               
|       FAT16:\import\                        ;empty folder                        
|       FAT16:\progress\                      ;empty folder                        
|       FAT16:\tmp\es\write\                  ;empty folder                        
+----------------------------------------------------------------------------------+
```

The Camera is storing further data on the eMMC FAT12 partition:

```
+-------------------------------------------------------------------------------------+
|       FAT12:\photo\DCIM\100NIN02\HNI_nnnn.JPG                        ;camera photos 
|       FAT12:\photo\private\ds\app\484E494A\pit.bin                   ;camera info   
|       FAT12:\photo\private\ds\app\484E494A\DCIM\100NIN02\HNI_nnnn.JPG;camera frames 
+-------------------------------------------------------------------------------------+
```

And, there\'s a small 3rd eMMC partition in MBR, but it\'s left unformatted (the VBR and FAT and everything is left zero-filled).

### DSi External SD Card
DSiware games (and browser and flipnote) can be copied to SD card (via System Menu, Data Managment) (however, the DSi doesn\'t seem to allow to execute files on SD card, so they can be used only if they are copied back to the DSi):

```
+-------------------------------------------------------------------------------------+
|       SD:\private\ds\title\4GGGGGGG.bin    ;executable/data in one file (encrypted) 
|       SD:\private\ds\title\HNB_.lst        ;list of gamecodes                       
+-------------------------------------------------------------------------------------+
```

Camera data can be copied to SD card (via Nintendo DSi Camera, Options, Copy):

```
+--------------------------------------------------------------------------------+
|       SD:\DCIM\nnnNIN02\HNI_nnnn.JPG                            ;camera photos 
|       SD:\private\ds\app\484E494A\pit.bin                       ;camera info   
|       SD:\private\ds\app\484E494A\DCIM\nnnNIN02\HNI_nnnn.JPG    ;camera frames 
+--------------------------------------------------------------------------------+
```

Flipnote \"movies\" can be also saved on SD card:

```
+-------------------------------------------------------------------------------------+
|       SD:\private\ds\app\4B4755GG\recent10.pls     ;Recently saved path/filenames   
|       SD:\private\ds\app\4B4755GG\mark0.pls        ;Heart sticker path/filenames    
|       SD:\private\ds\app\4B4755GG\mark1.pls        ;Crown sticker path/filenames    
|       SD:\private\ds\app\4B4755GG\mark2.pls        ;Music sticker path/filenames    
|       SD:\private\ds\app\4B4755GG\mark3.pls        ;Skull sticker path/filenames    
|       SD:\private\ds\app\4B4755GG\001\dirmemo2.lst ;List of all files in folder     
|       SD:\private\ds\app\4B4755GG\001\XNNNNN_NNNNNNNNNNNNN_NNN.ppm          ;normal 
|       SD:\private\ds\app\4B4755GG\YYYYMMDD\NNN\XNNNNN_NNNNNNNNNNNNN_NNN.ppm ;backup 
|       SD:\private\ds\app\4B4755GG\gif\XNNNNN_NNNNNNNNNNNNN_NNN.gif          ;gif    
+-------------------------------------------------------------------------------------+
```

The Nintendo DSi Sound utility can read .AAC (and .M4A) files from SD card (though it doesn\'t seem to allow to save your own recordings to SD card?). There appears to be no special folder location, ie. the AAC/M4A files can be anywhere:

```
+-----------------------------------------------------------------------+
|       SD:\...\*.aac                                                   
|       SD:\...\*.m4a                                                   
+-----------------------------------------------------------------------+
```


### DSi Shop and System Update Download URLs

```
+-------------------------------------------------------------------------------------+
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/tmd      |
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/cetk     |
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/000000vv |
+-------------------------------------------------------------------------------------+
```

The \"cetk\" file contains the encrypted ticket. The \"cetk\" file is available only for freeware downloads (eg. system updates). Commercial DSi Shop titles can be downloaded the same way, except that the ticket must be somehow purchased/downloaded separetely.
Nintendo does keep hosting older \"00000vv\" versions (except, the original version, \"00000000\" isn\'t available in all cases; namely if the title was pre-installed on all DSi\'s then it would be pointless to provide it as update).

### NUS Downloader Notation
The homebrew NUS Downloader utility for PCs comes up with its own renaming scheme:

```
+--------------------------------------------------------------------------------+
|       d:\...\TITLES\000300tt4ggggggg\ddd\000000vv      ;executable (encrypted) 
|       d:\...\TITLES\000300tt4ggggggg\ddd\000000vv.APP  ;executable (decrypted) 
|       d:\...\TITLES\000300tt4ggggggg\ddd\CETK          ;cetk (2468 bytes)      
|       d:\...\TITLES\000300tt4ggggggg\ddd\TMD           ;tmd (520 bytes)        
+--------------------------------------------------------------------------------+
```

Whereas, \"ddd\" is same as \"000000vv\" multiplied by 256 decimal (which is nonsense and redundant). The decrypted \".APP\" file is generated only if the \"common key\" is found in 16-byte file \"dsikey.bin\".



