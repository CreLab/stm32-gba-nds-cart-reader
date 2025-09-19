# DS Cartridge NitroROM and NitroARC File Systems


The DS hardware, BIOS, and Firmware do NOT contain any built-in filesystem functions. The ARM9/ARM7 boot code (together max 3903KB), and Icon/Title information are automatically loaded on power-up.
Programs that require to load additional data from cartridge ROM may do that either by implementing whatever functions to translate filenames to ROM addresses, or by reading from ROM directly.

### NitroROM
The NitroROM Filesystem is used by many NDS games (at least those that have been developed with Nintendo\'s tools). It\'s used for ROM Cartridges, and, on the DSi, it\'s also used for DSiWare games (in the latter case, NitroROM acts as a 2nd virtual filesystem inside of the DSi\'s FAT16 filesystem).

```
+----------------------------------------------------------------------------+
|       FNT = cart_hdr[040h]     ;\origin as defined in ROM cartridge header 
|       FAT = cart_hdr[048h]     ;/                                          |
|       IMG = 00000000h          ;-origin at begin of ROM                    |
+----------------------------------------------------------------------------+
```

Aside from using filenames, NitroROM files can be alternately accessed via Overlay IDs (see later on below).

### NitroARC (Nitro Archive)
NARC Files are often found inside of NitroROM Filesystems (ie. NARC is a second virtual filesystem, nested inside of the actual filesystem). The NARC Format is very similar to the NitroROM Format, but with additional Chunk Headers (instead of the Cartridge ROM Header).

```
+----------------------------------------------------------------------------------+
|       ...  ...  Optional Header (eg. compression header, or RSA signature)       |
|       000h 4    Chunk Name "NARC" (Nitro Archive)                   ;\           
|       004h 2    Byte Order (FFFEh) (unlike usually, not FEFFh)      ;            |
|       006h 2    Version (0100h)                                     ; NARC       |
|       008h 4    File Size (from "NARC" ID to end of file)           ; Header     |
|       00Ch 2    Chunk Size (0010h)                                  ;            |
|       00Eh 2    Number of following chunks (0003h)                  ;/           |
|       010h 4    Chunk Name "BTAF" (File Allocation Table Block)     ;\           
|       014h 4    Chunk Size (including above chunk name)             ; File       |
|       018h 2    Number of Files                                     ; Allocation |
|       01Ah 2    Reserved (0000h)                                    ; Table      |
|       01Ch ...  FAT (see below)                                     ;/           |
|       ...  4    Chunk Name "BTNF" (File Name Table Block)           ;\           
|       ...  4    Chunk Size (including above chunk name)             ; File Name  |
|       ...  ...  FNT (see below)                                     ; Table      |
|       ...  ..   Padding for 4-byte alignment (FFh-filled, if any)   ;/           |
|       ...  4    Chunk Name "GMIF" (File Image Block)                ;\           
|       ...  4    Chunk Size (including above chunk name)             ; File Data  |
|       ...  ...  IMG (File Data)                                     ;/           |
+----------------------------------------------------------------------------------+
```


### NARCless variant
There are a few NARC archives with crippled header, without \"NARC\" string (eg. rom:\\dwc\\utility.bin in Over the Hedge, Downhill Jam, and Tony Hawk\'s Skateland).

```
+--------------------------------------------------------------------------+
|       000h 4   FNT Filename Table Offset (always at 10h)                 |
|       004h 4   FNT Filename Table Size                                   |
|       008h 4   FAT Allocaton Table Offset (at above Offset+Size+Padding) |
|       00Ch 4   FAT Allocaton Table Size                                  |
|       010h ..  FNT Filename Table Data                                   |
|       ...  ..  FAT Allocaton Table Data                                  |
|       ...  ..  IMG File Data                                             |
+--------------------------------------------------------------------------+
```

The offsets in FAT are relative to IMG=0 (as if IMG would start at begin of file).

### File Allocation Table (FAT) (base/size defined in cart header)
Contains ROM addresses for up to 61440 files (File IDs 0000h and up).

```
+-------------------------------------------------------------------------+
|       Addr Size Expl.                                                   |
|       00h  4    Start address (originated at IMG base) (0=Unused Entry) |
|       04h  4    End address   (Start+Len)              (0=Unused Entry) |
+-------------------------------------------------------------------------+
```

For NitroROM, addresses must be after Secure Area (at 8000h and up).
For NitroARC, addresses can be anywhere in the IMG area (at 0 and up).
Directories are fully defined in FNT area, and do not require FAT entries.

### File Name Table (FNT) (base/size defined in cart header)
Consists of the FNT Directory Table, followed by one or more FNT Sub-Tables.
To interprete the directory tree: Start at the 1st Main-Table entry, which is referencing to a Sub-Table, any directories in the Sub-Table are referencing to Main-Table entries, which are referencing to further Sub-Tables, and so on.

### FNT Directory Main-Table (base=FNT+0, size=\[FNT+06h\]\*8)
Consists of a list of up to 4096 directories (Directory IDs F000h and up).

```
+--------------------------------------------------------------------------+
|       Addr Size Expl.                                                    |
|       00h  4    Offset to Sub-table             (originated at FNT base) |
|       04h  2    ID of first file in Sub-table   (0000h..EFFFh)           |
+--------------------------------------------------------------------------+
```

For first entry (ID F000h, root directory):

```
+-----------------------------------------------------------------------+
|       06h  2    Total Number of directories     (1..4096)             |
+-----------------------------------------------------------------------+
```

Further entries (ID F001h..FFFFh, sub-directories):

```
+-----------------------------------------------------------------------+
|       06h  2    ID of parent directory (F000h..FFFEh)                 |
+-----------------------------------------------------------------------+
```


### FNT Sub-tables (base=FNT+offset, ends at Type/Length=00h)
Contains ASCII names for all files and sub-directories within a directory.

```
+----------------------------------------------------------------------------------+
|       Addr Size Expl.                                                            |
|       00h  1    Type/Length                                                      |
|                   01h..7Fh File Entry          (Length=1..127, without ID field) |
|                   81h..FFh Sub-Directory Entry (Length=1..127, plus ID field)    |
|                   00h      End of Sub-Table                                      |
|                   80h      Reserved                                              |
|       01h  LEN  File or Sub-Directory Name, case-sensitive, without any ending   |
|                   zero, ASCII 20h..7Eh, except for characters \/?"<>*:;|         
+----------------------------------------------------------------------------------+
```

Below for Sub-Directory Entries only:

```
+---------------------------------------------------------------------------+
|       LEN+1 2    Sub-Directory ID (F001h..FFFFh) ;see FNT+(ID AND FFFh)*8 |
+---------------------------------------------------------------------------+
```

File Entries do not have above ID field. Instead, File IDs are assigned in incrementing order (starting at the \"First ID\" value specified in the Directory Table).

### ARM9 and ARM7 Overlay Tables (OVT) (base/size defined in cart header)
Somehow related to Nintendo\'s compiler, allows to assign compiler Overlay IDs to filesystem File IDs, and to define additional information such like load addresses.

```
+-----------------------------------------------------------------------+
|       Addr Size Expl.                                                 |
|       00h  4    Overlay ID                                            |
|       04h  4    RAM Address ;Point at which to load                   |
|       08h  4    RAM Size    ;Amount to load                           |
|       0Ch  4    BSS Size    ;Size of BSS data region                  |
|       10h  4    Static initialiser start address                      |
|       14h  4    Static initialiser end address                        |
|       18h  4    File ID  (0000h..EFFFh)                               |
|       1Ch  4    Reserved (zero)                                       |
+-----------------------------------------------------------------------+
```


### Cartridge Header
The base/size of FAT, FNT, OVT areas is defined in cartridge header,
- [DS Cartridge Header](./dscartridgeheader.md)



