# DS Cart DLDI Driver


DLDI (Dynamically Linked Device Interface for libfat) is a popular yet undocumented flashcart driver for homebrew NDS software dating back to 2006. Below was reverse-engineered 11/2018.

file.dldi \--\> driver file (can be small like 1.5Kbyte, or max 32Kbyte)
file.nds \--\> ROM image (must contain 32Kbyte space with DLDI ID for patching)

### Driver patch file standard header

```
+-------------------------------------------------------------------------------------+
|       00h 4  DLDI ID       (EDh,A5h,8Dh,BFh) (aka BF8DA5EDh)  ;\patching tools will 
|       04h 8  DLDI String   (20h,"Chishm",00h)                 ; refuse any other    |
|       0Ch 1  DLDI Version  (01h in .dldi, don't care in .nds) ;/values              |
|       0Dh 1  Size of .dldi+BSS (rounded up to 1 SHL N bytes) (max 0Fh=32Kbytes)     |
|       0Eh 1  Sections to fix/destroy (see FIX_xxx)                                  |
|       0Fh 1  Space in .nds file (1 SHL N) (0Eh..0Fh in .nds, can be 0 in .dldi)     |
|       10h 48 ASCII Full Driver Name (max 47 chars, plus zero padding)               |
|       40h 4  Address of ALL start (text) ;-base address (BF800000h in .dldi)        |
|       44h 4  Address of ALL end   (data) ;-for highly-unstable FIX_ALL addr.adjusts |
|       48h 4  Address of GLUE start       ;\for semi-stable FIX_GLUE addr.adjusts    
|       4Ch 4  Address of GLUE end         ;/  ("Interworking glue" for ARM-vs-THUMB) |
|       50h 4  Address of GOT start        ;\for semi-stable FIX_GOT addr.adjusts     
|       54h 4  Address of GOT end          ;/  ("Global Offset Table")                |
|       58h 4  Address of BSS start        ;\for zerofilling "BSS" via FIX_BSS        
|       5Ch 4  Address of BSS end          ;/  ("Block Started by Symbol")            |
|       60h 4  ASCII Short Driver/Device Name (4 chars, eg. "MYHW" for MyHardware)    |
|       64h 4  Flags 2 (see FEATURE_xxx) (usually 13h=GbaSlot, or 23h=NdsSlot)        |
|       68h 4  Address of Function startup() ;<-- must be at offset +80h !! ;\        
|       6Ch 4  Address of Function isInserted() ;out: 0=no/fail, 1=yes/okay ; all     |
|       70h 4  Address of Function readSectors(sector,numSectors,buf)       ; return  |
|       74h 4  Address of Function writeSectors(sector,numSectors,buf)      ; 0=fail, |
|       78h 4  Address of Function clearStatus()                            ; 1=okay  |
|       7Ch 4  Address of Function shutdown()                               ;/        |
|       80h .. Driver Code (can/must begin with "startup()")            ;\max 7F80h   
|       ..  .. Glue section (usually a small snippet within above code) ; bytes (when |
|       ..  .. GOT section (usually after above code) (pointer table)   ; having 32K  |
|       ..  .. BSS section (usually at end, may exceed .dldi filesize)  ; allocated)  |
|       ..  .. Optional two garbage NOPs at end of default.dldi         ;/            |
+-------------------------------------------------------------------------------------+
```

hdr\[0Eh\] - Sections to fix/destroy (FIX_xxx):

```
+-----------------------------------------------------------------------------------+
|       0    FIX_ALL   ;-installer uses highly-unstable guessing in whole dldi file |
|       1    FIX_GLUE  ;-installer uses semi-stable address guessing in GLUE area   |
|       2    FIX_GOT   ;-installer uses semi-stable address guessing in GOT area    |
|       3    FIX_BSS   ;-installer will zerofill BSS area                           |
|       4-7  Reserved (0)                                                           |
+-----------------------------------------------------------------------------------+
```

hdr\[64h\] - Flags 2 (FEATURE_xxx) (usually 13h=GbaSlot, or 23h=NdsSlot):

```
+-------------------------------------------------------------------------------------+
|       0    FEATURE_MEDIUM_CANREAD          00000001h (usually set)                  |
|       1    FEATURE_MEDIUM_CANWRITE         00000002h (a few carts can't write)      |
|       2-3  Reserved (0)                                                             |
|       4    FEATURE_SLOT_GBA                00000010h (need EXMEMCNT bit7 adjusted)  |
|       5    FEATURE_SLOT_NDS                00000020h (need EXMEMCNT bit11 adjusted) |
|       6-31 Reserved (0)                                                             |
+-------------------------------------------------------------------------------------+
```

Note: The allocated driver size in hdr\[0Fh\] was 0Fh=32Kbytes between 2006 and 2016, however, libnds has changed that to 0Eh=16Kbytes in January 2017 (maybe intending to free more RAM, especially when using ARM7 WRAM).
However, there\'s at least one driver exceeding 16K (rpg_nand.dldi in AKAIO package; the driver disguises itself as 8K driver in hdr\[0Dh\], but its BSS area actually needs ways MORE than 16K).

### Required entries in .nds file
Officially, dldi could be at any 4-byte aligned location, however, for faster lookup, better use this locations:

```
+-------------------------------------------------------------------------------+
|       dldi area should be located at a 40h-byte aligned address in ROM image. |
|       dldi area should be located in ARM9 (or ARM7) bootcode area.            |
+-------------------------------------------------------------------------------+
```

An \"empty\" driver needs to contain:

```
+---------------------------------------------------------------------------------+
|       dldi[00h..0Bh] must contain DLDI ID word/string                           |
|       dldi[0Fh]      must contain allocated size (0Eh=16Kbyte or 0Fh=32Kbyte)   |
|       dldi[40h..43h] must contain RAM base address of DLDI block                |
|       and other entries should contain valid dummy strings and dummy functions. |
+---------------------------------------------------------------------------------+
```

An installed driver should contain a copy of the .dldi file, with addresses adjusted to RAM locations, and BSS area zerofilled (if FIX_BSS was set)

```
+-----------------------------------------------------------------------------+
|       dldi[0Fh] must be kept as in the old .nds file (not as in .dldi file) |
+-----------------------------------------------------------------------------+
```

Some installers might try to detect homebrew by looking at nds carthdr for deciding whether or not to try to install dldi (unknown if/which ones are doing such things and looking at which carthdr entries).

### Functions
startup, isInserted, clearStatus, shutdown can be dummy functions that do nothing (other than returning r0=1=okay).
Alternately startup/shutdown can initialize or power down the hardware, clearStatus is meant to be some sort of soft reset, and isInserted is allowing to test if the SD card is inserted & working.
read/write sectors are reading/writing one or more sectors. Sector size is 200h bytes, sector numbers is 0=First 200h bytes, 1=Next 200h bytes, and so on.
buf should be usually 4-byte aligned, however, some drivers do also support unaligned buffers using slower transfer code (better implement that when making .dldi drivers, but better don\'t rely on it being supported when making .nds files).
The driver functions can support SD and SDHC (or the flashcart manufacturer might release driver updates if SDHC wasn\'t supported).
Higher level FAT functions must be contained in the .nds file (so a driver update won\'t help if the .nds file lacks FAT32) (and ExFAT most unlikely to be supported).
Functions should be ARM7 compatible, ie. don\'t use BLX or POP r15 for mode switching, so the driver can be used on both ARM9 and ARM7 (or even on GBA).

### SLOT_GBA/NDS
SLOT_GBA/NDS seem to relate to GBA and NDS slots, the driver can probably have only one of the SLOT bits set (the functions don\'t allow to select which slot to use).
Purpose is unclear to me, maybe just telling the .nds file that the flashcart is in the given slot (and thereby shouldn\'t expect other hardware in that slot). Or maybe telling telling the installer which hardware the driver is supposed for.

FIX_xxx does maybe relate to address adjustments made by the dldi installer. Unknown if/how that\'s working.
- [DS Cart DLDI Driver - Guessed Address-Adjustments](./dscartdldidriverguessedaddressadjustments.md)

Some DLDI flashcarts support extra features like Rumble. However, that extra hardware is accessed via direct I/O, not via DLDI driver. Unknown which I/O ports are used for that stuff - probably something compatible with official GBA/NDS rumble cart(s).



