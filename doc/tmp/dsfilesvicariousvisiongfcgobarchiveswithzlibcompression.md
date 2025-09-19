# DS Files - Vicarious Vision GFC/GOB Archives with ZLIB compression


NDS Over the Hedge, rom:\\vvobj\\generated\\gob\\main.gfc and main.gob
NDS Tony Hawks Skateland, rom:\\vvobj\\generated\\gob\\main.gfc and main.gob
NDS Tony Hawks Downhill Jam, rom:\\vvobj\\generated\\gob\\main.gfc and main.gob
NDS Ultimate Spiderman, rom:\\vvobj2\\generated\\gob\\main.gfc and main.gob

```
+-----------------------------------------------------------------------+
|       .GFC - directory                                                |
|       .GOB - zlib compressed data cluster                             |
+-----------------------------------------------------------------------+
```


### GFC File (BIG ENDIAN)

```
+-------------------------------------------------------------------------------------+
|       000h   4       File ID (always 8008h)                                         |
|       004h   4       Size of the .GOB data file   (eg. 01735224h)                   |
|       008h   4       Number of Clusters (C)       (eg. 2468h)                       |
|       00Ch   4       Number of Files    (F)       (eg. 1AF4h, 6900 decimal)         |
|       010h   C*10h   Cluster Table                                                  |
|       24690h C*4     Cluster Checksums (ADLER32 checksums on compressed clusters)   |
|       2D830h F*0Ch   Basic File Table                                               |
|       41BA0h (F*68h) Extended File Table          ;-NOT included in retail version! |
+-------------------------------------------------------------------------------------+
```


### Cluster Table Entries (FAT-like allocation table)

```
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
|       000h 4     Compressed size in bytes                                                                                                                      |
|       004h 4     Offset in .GOB data file (usually PrevOffs+PrevSize+4byteAlign)                                                                               |
|       008h 4     Next Cluster (0..NumClusters-1, usually Curr+1, or 7FFFh=None)                                                                                |
|       00Ch (1)   Compression (30h="0"=None, 7Ah="z"=zlib)  ;\exists in NDS games,   00Dh (3)   Zerofilled                                ;/NOT in other games? 
+----------------------------------------------------------------------------------------------------------------------------------------------------------------+
```

Larger files can consist of several compressed and/or uncompressed clusters, that allows random-access to compressed files (without needing to decompress the preceeding clusters; provided that the decompressor knows maximum size of the the uncompressed cluster; that is 2000h on NDS?).
Small files (and last cluster of larger files) may be left uncompressed (if they are considered to be small enough without compression).

### Cluster Checksums
The Cluster Checksums (in .GFC) contain ADLER32 checksums on the compressed data. The zlib compressed data (.in GOB) additionally includes a ADLER32 on the uncompressed data.
Caution: ADLER32 is usally computed with InitialValue=00000001h (aka 2x16bit 0001h,0000h). However, the .GFC and .GOB are using InitialValue=00000000h, this is incompatible with unmodified zlib functions.

### Basic File Table (sorted by filename CRC32s)
Files are accessed via filename CRCs (that can be faster than string compare, but fails if two filenames have the same CRCs; the dev tool has error checking for that, and the developer must then rename one of the files).

```
+--------------------------------------------------------------------------+
|       000h 4    CRC32 on lowercase filename, excluding ending zero       |
|       004h 4    Filesize (of uncompressed file)                          |
|       008h 4    First Cluster Number in Cluster Table (0..NumClusters-1) |
+--------------------------------------------------------------------------+
```

Examples names found in the NDS Over the Hedge executable:

```
+-------------------------------------------------------------------------------------+
|       ".\strm\LA_BG.hwas"   --> CRC32=522AFF5Dh (with name converted to lowercase)  
|       ".\strm\boy_tv2.hwas" --> CRC32=F047AA4Eh (with name already being lowercase) 
+-------------------------------------------------------------------------------------+
```


### Extended File Table (if any, not included in NDS retail titles)
This contains a list of all filenames, but does apparently exist in dev version only. The retail version does have filenames in the executable (but they may be scattered around at various locations, or even generated on the fly, eg. path+filename+index+ext).

```
+-------------------------------------------------------------------------+
|       000h 60h  Filename in lowercase ASCII (eg. ".\path\name.ext",00h) 
|       060h 4    CRC32 on uncompressed file data                         |
|       064h 4    Timestamp                                               |
+-------------------------------------------------------------------------+
```


### Compressed .GOB file
Compression=NONE stores uncompressed clusters, except: if the remaining file size (in last cluster of the file) is smaller than ClusterSize then it stores only that many bytes in the .GOB file.
Compression=ZLIB stores 2-byte ZLIB header, deflated data, and 4-byte checksum, except: the initial checksum value is different as in standard zlib functions (see above notes on ADLER32).

### Variants
The GFC/GOP format is used in different games on different consoles. Some hardcoded parameters may differ (and, unfortunately, the file header doesn\'t contain that info):

```
+-------------------------------------------------------------------------------------+
|      - The Extended File Table (with filenames) doesn't exist in all GFC files.     |
|      - Use "if Next>=NumClusters then End" (instead hardcoded "if Next=7FFFh").     |
|      - Offsets in GOP may be matched to DMA alignment or CDROM sector (sector       |
|        align might help on 1st cluster of file, without hurting continous loading). |
|      - ClusterSize is important only for random access (if needed, one could detect |
|        the biggest (uncompressed) ClusterSize and use that as filepos divider).     |
|      - Source code seems to use 0Ch-byte Cluster Entries (without compression flag, |
|        it seems to have compression "codec" type byte at begin compressed data?).   |
|      - FilenameSize=60h might vary (if the Extended File Table is present at all).  |
+-------------------------------------------------------------------------------------+
```


### References
<https://github.com/jedis/jediacademy/tree/master/code/goblib> - source code



