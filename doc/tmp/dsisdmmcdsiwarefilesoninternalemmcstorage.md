# DSi SD/MMC DSiware Files on Internal eMMC Storage


DSiware games (downloaded from DSi Shop), and pre-installed System Tools are consisting of following files:

### FAT16:\\title\\000300tt\\4ggggggg\\content\\000000vv.app ;executable (decrypted)
Contains the executable, with same header as used in Cartridge ROM images, and usually with a NitroROM File System (ie. a second virtual filesystem inside of the FAT16 filesystem).
- [DSi Cartridge Header](./dsicartridgeheader.md)
- [DS Cartridge NitroROM and NitroARC File Systems](./dscartridgenitroromandnitroarcfilesystems.md)
Note: There are also three non-executable \".app\" files without cartridge headers (Wifi Firmware, Version Data, and DS Cart Whitelist).

### FAT16:\\title\\000300tt\\4ggggggg\\data\\public.sav ;size as carthdr\[238h\]
### FAT16:\\title\\000300tt\\4ggggggg\\data\\private.sav ;size as carthdr\[23Ch\]
These files can contain whatever save data. The .sav files are usually containing a FAT12 with its own VBR, FAT, and Directories (so they use some virtual FAT12 inside of the real FAT16).
When exporting a game to SD Card (via System Settings, Data Managment), then public.sav (eg. used by Flipnote) will be included in the exported image, whilst private.sav (eg. used by DSi Browser) won\'t be included.

### FAT16:\\title\\000300tt\\4ggggggg\\data\\ec.cfg ;dsi shop only
Whatever extra file, encrypted, 134h bytes, used by DSi Shop only.

### FAT16:\\title\\000300tt\\4ggggggg\\data\\banner.sav ;if carthdr\[1BFh\].bit2=1
Custom icon, used by some games to indicate the game progress. Format is similar as Icon/Title, but containing only animated icon data (without title). For details, see:
- [DS Cartridge Icon/Title](./dscartridgeicontitle.md)

### FAT16:\\title\\000300tt\\4ggggggg\\content\\title.tmd ;tmd (520 bytes)
### FAT16:\\ticket\\000300tt\\4ggggggg.tik (encrypted) ;ticket (708 bytes)
### FAT16:\\ticket\\000300tt\\00000000.tik (encrypted) ;multi-tik? (N\*708 bytes?)
These files do contain title metadata (.tmd) and tickets (.tik).
- [DSi SD/MMC DSiware Tickets and Title metadata](./dsisdmmcdsiwareticketsandtitlemetadata.md)
The .tik files are encrypted with ES Block Encryption (using same key X/Y as for dev.kp):

```
+-------------------------------------------------------------------------------+
|       KEY_X[00h..03h] = 4E00004Ah                           ;\                
|       KEY_X[04h..07h] = 4A00004Eh                           ; same as for Tad |
|       KEY_X[08h..0Bh] = Port[4004D00h+4] xor C80C4B72h      ;                 |
|       KEY_X[0Ch..0Fh] = Port[4004D00h+0]                    ;/                |
|       KEY_Y[00h..0Fh] = Constant (E5,CC,5A,8B,...)  ;from ARM7BIOS            |
+-------------------------------------------------------------------------------+
```

- [DSi ES Block Encryption](./dsiesblockencryption.md)
Caution: There are some ways to modify .tmd files, but that can cause the whole title to be deleted when starting one of the following three tools:

```
+-----------------------------------------------------------------------------+
|       Data Management (in System Settings), DSi Shop, and 3DS transfer tool |
+-----------------------------------------------------------------------------+
```

These tools will delete the titles \"content\" folder (with .app and .tmd files) and the \"data\" folder (with .sav files). As a workaroung: Set read-only attribute for .tmd and .app files (the deletion aborts once when hitting a read-only file; with the files being processed as ordered in the directory).
Note: Tickets are kept stored in eMMC even after deleting titles (that\'s allowing to redownload the titles for free; at least that\'s been the case when the DSi shop was still online).

Below \"wrap.bin\" and \"menusave.dat\" files are containing lists of installed titles, however, it isn\'t neccessary to edit those files when manually installing .tmd/.app/.tik files.

### FAT16:\\shared2\\launcher\\wrap.bin (16Kbytes)
Contains a list of installed DSiware Title IDs (in no specific order).

```
+----------------------------------------------------------------------------------+
|       0000h 14h   SHA1 on entries [014h..03Fh]                                   |
|       0014h 14h   SHA1 on entries [040h..177h]                                   |
|       0028h 4     ID ("APWR") (aka 'WRAP' with mis-ordered letters)              |
|       002Ch 4     Size of entries at [040h..177h] (00000138h, aka 39*8)          |
|       0030h 10h   Zerofilled                                                     |
|       0040h 138h  Space for 39 Title IDs (as at cart[230h]) (8x00h=unused entry) |
|       0178h 3E88h Unknown (looks like random/garbage, or encrypted junk)         |
+----------------------------------------------------------------------------------+
```


### FAT16:\\title\\00030017\\484e41gg\\data\\private.sav:\\menusave.dat (System Menu)
This private.sav file contains a 4000h-byte FAT12 image. The FAT12 contains only one file: menusave.dat (154h bytes), containing a list of Title IDs (and their sort-order how they are arranged in System Menu; users can drag the icons to rearrange their ordering):

```
+------------------------------------------------------------------------------------+
|       0000h 4     ID ("TSSV")                                                      |
|       0004h 4     Zerofilled (used somehow, can be nonzero?)                       |
|       0008h 2     CRC16 on [000h..0153h], initial value 5356h, assume [008h]=0000h |
|       000Ah 6     Zerofilled                                                       |
|       0010h 39x8  Title IDs (gg,gg,gg,gg,tt,00,03,00) (0=NDS CartSlot or Unused)   |
|       0148h 8     Zerofilled                                                       |
|       0150h 4     Index of NDS CartSlot Entry (0..39)                              |
+------------------------------------------------------------------------------------+
```

The current selection isn\'t stored in this file (instead, the Title ID of the most recently selected title is stored in the TWLCFGn.dat files).
Note that the \"Nintendo Zone\" utility isn\'t included in this list (even though it\'s present in title & ticket folders, and listed in wrap.bin).
The System Menu works even if data\\private.sav doesn\'t exist (however, the sort-order is stored only if data\\private.sav does exist).



