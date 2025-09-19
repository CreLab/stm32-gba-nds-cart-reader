# DS Sound Files - SDAT (Sound Data Archive)


### SDAT Header

```
+------------------------------------------------------------------------------------+
|       000h 4     ID "SDAT"           ;alike "CSAR" on 3DS                          |
|       004h 2     Byte Order    (FEFFh)                                             |
|       006h 2     Version       (0100h)                                             |
|       008h 4     Total Filesize                                                    |
|       00Ch 2     Header Size (usually 40h)                                         |
|       00Eh 2     Number of Blocks (usually 4 = SYMB+INFO+FAT+FILE) (or 3=no SYMB)  |
|       010h 4+4   SYMB Block (Offset from SDAT+0, Size) ;=0,0 if above is 3=no SYMB |
|       018h 4+4   INFO Block (Offset from SDAT+0, Size) ;\                          
|       020h 4+4   FAT  Block (Offset from SDAT+0, Size) ; always present            |
|       028h 4+4   FILE Block (Offset from SDAT+0, Size) ;/                          |
|       030h 10h   Padding to 20h-byte boundary (0)                                  |
+------------------------------------------------------------------------------------+
```

The SYMB block exists in most SDAT files (except in some titles like Downhill Jam and Over the Hedge).


```
+-------------------------------------------------------------------------------------+
|      _________________________________ SYMB Block _________________________________ |
+-------------------------------------------------------------------------------------+
```


### Symbol Block (if present) (names for the corresponding items in INFO block)

```
+-------------------------------------------------------------------------------------+
|       000h 4     ID "SYMB"                                                          |
|       004h 4     SYMB Block Size (rounded up to 4-byte boundary, unlike as in SDAT) |
|       008h 4     File List SSEQ    (Offset from SYMB+0) Sequences (songs)           |
|       00Ch 4     Folder List SSAR  (Offset from SYMB+0) Sequence Archives (fx)      |
|       010h 4     File List BANK    (Offset from SYMB+0) Banks                       |
|       014h 4     File List SWAR    (Offset from SYMB+0) Wave Archives (samples)     |
|       018h 4     File List Player  (Offset from SYMB+0) Player (Group-related)      |
|       01Ch 4     File List Group   (Offset from SYMB+0) Group (SSEQ+SSAR+BANK+SWAR) |
|       020h 4     File List Player2 (Offset from SYMB+0) Player2 (Stream-related)    |
|       024h 4     File List STRM    (Offset from SYMB+0) Wave Stream                 |
|       028h 18h   Reserved (0)                                                       |
|       040h ..    File/Folder Lists (see below)                                      |
|       ..   ..    File/Folder Name Strings (ASCII, terminated by 0)                  |
|       ..   ..    Padding to 4-byte boundary (0)                                     |
+-------------------------------------------------------------------------------------+
```

File List\'s are having following format:

```
+-----------------------------------------------------------------------+
|       000h 4       Number of entries in this list (can be 0=None)     |
|       004h N*4     File Name (Offset from SYMB+0)                     |
+-----------------------------------------------------------------------+
```

Folder List (for SSAR):

```
+-----------------------------------------------------------------------------------+
|       000h 4       Number of entries in this list (can be 0=None)                 |
|       004h N*(4+4) SSAR "Folder Name" and SSEQ "File List" (Offset's from SYMB+0) |
+-----------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________________________ INFO Block _________________________________ |
+-------------------------------------------------------------------------------------+
```


### Info Block

```
+-------------------------------------------------------------------------------------+
|       000h 4     ID "INFO"                                                          |
|       004h 4     INFO Block Size (same as in SDAT header)                           |
|       008h 4     Info List SSEQ    (Offset from INFO+0) Sequences (songs)           |
|       00Ch 4     Info List SSAR    (Offset from INFO+0) Sequence Archives (fx)      |
|       010h 4     Info List BANK    (Offset from INFO+0) Banks                       |
|       014h 4     Info List SWAR    (Offset from INFO+0) Wave Archives (samples)     |
|       018h 4     Info List Player  (Offset from INFO+0) Player (Group-related)      |
|       01Ch 4     Info List Group   (Offset from INFO+0) Group (SSEQ+SSAR+BANK+SWAR) |
|       020h 4     Info List Player2 (Offset from INFO+0) Player2 (Stream-related)    |
|       024h 4     Info List STRM    (Offset from INFO+0) Wave Stream                 |
|       028h 18h   Reserved (0)                                                       |
|       ..   ..    Info Lists (see below)                                             |
|       ..   ..    Info Entries (see below)                                           |
|       ..   ..    Padding to 4-byte boundary (0)                                     |
+-------------------------------------------------------------------------------------+
```

Info List\'s are having following format:

```
+-----------------------------------------------------------------------+
|       000h 4     Number of entries in this list (can be 0=None)       |
|       004h N*4   Info Entries (Offset from INFO+0)                    |
+-----------------------------------------------------------------------+
```


### SSEQ Info Entry (Sequences, eg. songs)

```
+-----------------------------------------------------------------------+
|       000h 2   FAT fileID of SSEQ file      ;for accessing this file  |
|       002h 2   Unknown                                                |
|       004h 2   bnk         ;Associated BANK                           |
|       006h 1   vol         ;Volume                                    |
|       007h 1   cpr                                                    |
|       008h 1   ppr                                                    |
|       009h 1   ply                                                    |
|       00Ah 2   Unknown (0)                                            |
+-----------------------------------------------------------------------+
```


### SSAR Info Entry (Sequence Archives, eg. collections of sound effects)

```
+-----------------------------------------------------------------------+
|       000h 2   FAT fileID of SSAR file                                |
|       002h 2   unknown                                                |
+-----------------------------------------------------------------------+
```

Note: bnk/vol/cpr/ppr/ply is stored in the SSAR file (instead of in Info). The actual sequences are also in SSAR? Or does the SSAR contain pointers to SSEQ files?

### BANK Info Entry (Banks)

```
+---------------------------------------------------------------------------+
|       000h 2   FAT fileID of SBNK file                                    |
|       002h 2   unknown                                                    |
|       004h 2   1st SWAR   ;\                                              
|       006h 2   2nd SWAR   ; Associated Wave Archives (FFFFh=Unused entry) |
|       008h 2   3rd SWAR   ;                                               |
|       00Ah 2   4th SWAR   ;/                                              |
+---------------------------------------------------------------------------+
```


### SWAR Info Entry (Wave Archives, eg. collections of instruments or effects)

```
+-----------------------------------------------------------------------+
|       000h 2   FAT fileID of SWAR file                                |
|       002h 2   unknown                                                |
+-----------------------------------------------------------------------+
```


### Player Info Entry (whatever)

```
+-----------------------------------------------------------------------+
|       000h 1   Unknown                                                |
|       001h 3   Padding                                                |
|       004h 4   Unknown                                                |
+-----------------------------------------------------------------------+
```


### Group Info Entry (whatever, list of files that must be loaded to memory?)

```
+-----------------------------------------------------------------------+
|       000h 4       Number of items in this group                      |
|       004h N*(4+4) Array (with ID+Index pairs)                        |
+-----------------------------------------------------------------------+
```

ID values: 700h=SSEQ, 803h=SSAR, 601h=BANK, 402h=SWAR.
Index: Entry number in the corresponding SSEQ/SSAR/BANK/SWAR list.

### Player2 Info Entry (whatever, Stream related?)

```
+---------------------------------------------------------------------------------+
|       000h 1   nCount             ;number of USED entries in below array        |
|       001h 16  v[16]              ;unknown array (UNUSED entries are set to FFh |
|       011h 7   Reserved (0)                                                     |
+---------------------------------------------------------------------------------+
```


### STRM Info Entry

```
+-----------------------------------------------------------------------+
|       000h 2   FAT fileID of STRM file    ;for accessing the file     |
|       002h 2   Unknown                                                |
|       004h 1   vol            ;volume                                 |
|       005h 1   pri            ;priority?                              |
|       006h 1   ply            ;play?                                  |
|       007h 5   Reserved (0)                                           |
+-----------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ____________________________ FAT and FILE Blocks _____________________________ |
+-------------------------------------------------------------------------------------+
```


### FAT Block

```
+--------------------------------------------------------------------------+
|       000h 4         ID "FAT "                                           |
|       004h 4         FAT Block Size (same as in SDAT header) (0Ch+N*10h) |
|       008h 4         Number of files                                     |
|       00Ch N*(4+4+8) File Entries (Offset from SDAT+0, Size, Zero)       |
+--------------------------------------------------------------------------+
```

The 8-byte Zero entries can be used for storing data at runtime.

### File Block

```
+-------------------------------------------------------------------------------------+
|       000h 4         ID "FILE"                                                      |
|       004h 4         FILE Block Size (same as in SDAT header)                       |
|       008h 4         Number of files (same as in FAT block)                         |
|       00Ch 4         Reserved (0)                                                   |
|       010h ..        Files (SSEQ,SSAR,SBNK,SWAR,STRM) (at offsets specified in FAT) |
+-------------------------------------------------------------------------------------+
```




