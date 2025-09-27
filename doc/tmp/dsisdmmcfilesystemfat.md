# DSi SD/MMC Filesystem (FAT)


### Volume Boot Record (VBR) (FAT12/FAT16) (DOS 4.0 EBPB)

```
+---------------------------------------------------------------------------+
|       000h 3   80x86 jump opcode       (DSi: E9h,00h,00h)                 |
|       003h 8   ascii disk name         (DSi: "TWL     ")                  |
|       00Bh 2   bytes / sector          (DSi: 0200h)                       |
|       00Dh 1   sectors / cluster       (DSi: 20h)                         |
|       00Eh 2   sectors / boot-record   (DSi: 0001h)                       |
|       010h 1   number of FAT-copys     (DSi: 02h)                         |
|       011h 2   entrys / root-directory (DSi: 0200h)                       |
|       013h 2   sectors / disk          (DSi: 0000h)                       |
|       015h 1   ID                      (DSi: F8h=HDD)                     |
|       016h 2   sectors / FAT           (DSi: A:0034h, B:0009h)            |
|       018h 2   sectors / track         (DSi: 0020h)                       |
|       01Ah 2   heads / disk            (DSi: 0010h)                       |
|       01Ch 2   number of reserved sectors    (DSi: None such entry!)      |
|       01Ch 4   LBA First "hidden"      (DSi: A:00000877h, B:0006784Dh)    |
|       020h 4   LBA Size (total sectors)(DSi: A:00066F89h, B:000105B3h)    |
|       024h 1   Drive Number            (DSi: A:00h, B:01h)                |
|       025h 1   Flags (reserved)        (DSi: 00h)                         |
|       026h 1   EBPB Version            (DSi: 29h) (that is, DOS 4.0 EBPB) |
|       027h 4   Volume Serial Number    (DSi: 12345678h)                   |
|       02Bh 11  Volume Label            (DSi: "           ")               |
|       036h 8   Filesystem Type         (DSi: 00h-filled)                  |
|       03Eh 448 Bootcode                (DSi: 00h-filled)                  |
|       1FEh 2   Signature               (DSi: 55h,AAh)                     |
+---------------------------------------------------------------------------+
```

SDHC carts use FAT32, which differs in entries 011h, 016h and 024h-059h:

```
+-------------------------------------------------------------------------------------+
|       011h 2   Must be 0 (number of root entries, is variable-length FAT chain)     |
|       016h 2   Must be 0 (sectors per fat, instead use 32bit value at 024h)         |
|       024h 4   sectors / FAT  (new 32bit value instead of old entry 016h)           |
|       028h 2   ExtFlags (related to "active" FAT copy)                              |
|       02Ah 2   Version of FAT32 filesystem (minor, major) (should be 0.0)           |
|       02Ch 4   Cluster number of first Root directory cluster (usually/often 2)     |
|       030h 2   Sector number of FSINFO in reserved area (usually 0001h)             |
|       032h 2   Sector number of VBR backup copy in reserved area (usually 0006h)    |
|       034h 12  Reserved for future   ;Should be zerofilled                          |
|       040h 1   Drive Number                                               ;\        
|       041h 1   Flags (reserved)                                           ; as old  |
|       042h 1   EBPB Version          ;Must be 29h (that is, DOS 4.0 EBPB) ; entries |
|       043h 4   Volume Serial Number                                       ; at 024h |
|       047h 11  Volume Label                                               ;         |
|       052h 8   Filesystem Type       ;Must be "FAT32   "                  ;/        |
+-------------------------------------------------------------------------------------+
```

Moreover, FAT32 has the \"FSINFO\" at sector number VBR\[30h\]:

```
+-------------------------------------------------------------------------+
|       000h 4   Value 41615252h (aka "RRaA")                             |
|       004h 480 Reserved (should be 0)                                   |
|       1E4h 4   Value 61417272h (aka "rrAa")                             |
|       1E8h 4   Hint on number of free clusters   (or FFFFFFFFh=unknown) |
|       1ECh 4   Hint on first free cluster number (or FFFFFFFFh=unknown) |
|       1F0h 12  Reserved (should be 0)                                   |
|       1FCh 4   Value AA550000h                                          |
+-------------------------------------------------------------------------+
```

For more info see <http://en.wikipedia.org/wiki/BIOS_Parameter_Block> and fatgen103.pdf (official specs from microsoft).

### File Allocation Table - FAT and FAT copy(s)
The following sectors are occupied by the File Allocation Table (FAT), which contains 12bit, 16bit, or 32bit entries (for FAT12/16/32) for each cluster:

```
+-------------------------------------------------------------------------+
|       (x000)(0)000      unused, free                                    |
|       (x000)(0)001      ???                                             |
|       (x000)(0)002...   pointer to next cluster in chain (0)002..(F)FEF |
|       (xFFF)(F)FF0-6    reserved (no part of chain, not free)           |
|       (xFFF)(F)FF7      defect cluster, don't use                       |
|       (xFFF)(F)FF8-F    last cluster of chain                           |
+-------------------------------------------------------------------------+
```

The \"x\" in MSB of FAT32 entries is reserved (ie. FAT32 is restricted to 28bit cluster numbers).
Number and size of FATs can be calculated by the information in the boot sector.
Note on The first two FAT entries:
\"The first cluster of the data area is cluster #2. That leaves the first two entries of the FAT unused. In the first byte of the first entry a copy of the media descriptor is stored. The remaining bits of this entry are 1. In the second entry the end-of-file marker is stored. The high order two bits of the second entry are sometimes, in the case of FAT16 and FAT32, used for dirty volume management: high order bit 1: last shutdown was clean; next highest bit 1: during the previous mount no disk I/O errors were detected.
(Historically this description has things backwards: DOS 1.0 did not have a BIOS Parameter Block, and the distinction between single-sided and double-sided 5.25\" 360K floppies was indicated by the first byte in the FAT. DOS 2.0 introduced the BPB with media descriptor byte.)\"

### Root directory
The following sectors are the Root directory, again, size depends on the info in bootsector (on FAT32 is it\'s a normal cluster chain with variable size). Each entry consists of 32 bytes:

```
+----------------------------------------------------------------------------------+
|       00-07  8    Filename (first byte: 00=free entry, 2E=dir, E5=deleted entry) |
|       08-0A  3    Filename extension                                             |
|       0B     1    Fileattribute                                                  |
|                     bit0 read only                                               |
|                     bit1 hidden                                                  |
|                     bit2 system                                                  |
|                     bit3 volume label                                            |
|                     bit4 subdirectory                                            |
|                     bit5 archive-flag                                            |
|                     bit6 reserved                                                |
|                     bit7 reserved                                                |
|       0C-0D  2    Reserved, or stuff                                             |
|       0E-0F  2    Reserved, or Creation Timestamp                                |
|       10-11  2    Reserved, or Creation Datestamp                                |
|       12-13  2    Reserved, or Last Access Datestamp                             |
|       14-15  2    Reserved, or MSBs of Cluster (for FAT32)                       |
|       16-17  2    Last Modify Timestamp: HHHHHMMM, MMMSSSSS                      |
|       18-19  2    Last Modify Datestamp: YYYYYYYM, MMMDDDDD                      |
|       1A-1B  2    Pointer to first Cluster of file                               |
|       1C-1F  4    Filesize in bytes (always 0 for directories)                   |
+----------------------------------------------------------------------------------+
```

The \'cluster\' entry points to the first used cluster of the file. The FAT entry for that cluster points to the next used cluster (if any), the FAT entry for that cluster points to the next cluster, and so on.

### Long File Names (LFNs)
Long File Names (LFNs) are occupying multiple continous directory entries, consisting of a normal short filename entry, preceeded by one or more LFN prefix entries (with Attribute=0Fh). Each LFN prefix can hold 13 characters, the total length should not exceed 255 characters. The name should be terminated by 0000h, and any remaining unused characters should be padded by FFFFh. The LFN prefix entries are using the following format:

```
+-------------------------------------------------------------------------------------+
|       00h  1  Sequence Number (bit6: last logical, first physical LFN entry,        |
|               bit5: 0, bit4-0: number 01h..14h (1Fh)) (or E5h=deleted entry)        |
|       01h  10 Long Filename characters (five UCS-2 characters)                      |
|       0Bh  1  Attributes (always 0Fh for LFN prefix)                                |
|       0Ch  1  Type (always 00h)                                                     |
|       0Dh  1  Short Filename Checksum                                               |
|               sum=00h, for i=0 to 10, sum = (sum ROR 1) + shortname_char[i], next i |
|       0Eh  12 Long Filename characters (six UCS-2 characters)                       |
|       1Ah  2  First cluster (always 0000h)                                          |
|       1Ch  4  Long Filename characters (two UCS-2 characters)                       |
+-------------------------------------------------------------------------------------+
```

For example, \"File with very long filename.ext\" would be formatted as so:

```
+-----------------------------------------------------------------------+
|       Entry 1: LFN Prefix (43h) "me.ext", 0000h, 6xFFFFh              |
|       Entry 2: LFN Prefix (02h) "y long filena"                       |
|       Entry 3: LFN Prefix (01h) "File with ver"                       |
|       Entry 4: Normal 8.3 short filename entry "FILEWI~1.EXT"         |
+-----------------------------------------------------------------------+
```

<http://en.wikipedia.org/wiki/Design_of_the_FAT_file_system#VFAT_long_file_names>

### Reserved Sectors (if any)
Usually the number of reserved sectors is zero. If it is non-zero, then the following sector(s) are reserved (and could be used by the boot procedure for whatever purposes).

### Data Clusters 0002..nnnn
Finally all following sectors are data clusters. The first cluster is called cluster number (000)(0)002, followed by number (000)(0)003, (000)(0)004, and so on.

<http://en.wikipedia.org/wiki/Design_of_the_FAT_file_system>



