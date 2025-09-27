# Non-DS Files - U8 Archives


U8 archives are used in Mario Kart Wii and maybe other games (something called Wii discs is reportedly using a similar format, too).

### U8 Format (big endian)

```
+---------------------------------------------------------------------------------+
|       000h 4     ID (55AA382Dh) (appears as U.8- in hex editors) (nicknamed U8) |
|       004h 4     Offset to Directory (aka 20h?)                                 |
|       008h 4     Size of Directory including String Table                       |
|       00Ch 4     Offset to File Data                                            |
|       010h 10h   Reserved                                                       |
|       020h N*0Ch Directory Entries (0Ch-bytes each)                             |
|       ...  ..    String Table (ASCII strings, terminated by 00h)                |
|       ...  ..    File Data                                                      |
+---------------------------------------------------------------------------------+
```


### Directory Entries (starting with root entry)

```
+-----------------------------------------------------------------------------+
|       000h 1    Type (00h=File, 01h=Directory) (other values never seen)    |
|       001h 3    24bit Filename Offset (relative to begin of String Table)   |
|       004h 4    File: Offset to data                                        |
|                 Directory: Index of the parent directory                    |
|       008h 4    File: Size of data                                          |
|                 Directory: Index of the first node that is not part of this |
|                   directory (skip to node)                                  |
+-----------------------------------------------------------------------------+
```


Note: The U8 format is about same as 3DS \"darc\" format (with different header, different byte-order, and ASCII instead of UTF-16 names).
- [3DS Files - Archive DARC](./3dsfilesarchivedarc.md)



