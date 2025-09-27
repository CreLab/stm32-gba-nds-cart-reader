# Non-DS Files - RARC Archives


RARC archives are used in Wii and GameCube games like Super Mario Galaxy 1 & 2 and Supermario Sunshine. The RARC format is unique in terms of storing duplicated folder data in both Folder List and Directory Entries.

### RARC Header (\...probably bug-endian?)

```
+------------------------------------------------------------------------------------+
|       000h 4   ID "RARC"                                                           |
|       004h 4   Total Filesize                                                      |
|       008h 4   Size of RARC Header (always 20h)                                    |
|       00Ch 4   Size of Info Block (plus Folder List, Directory List, String Table) |
|       010h 4   Size of File Data area                                              |
|       014h 4   Size of File Data again? (always same as the previous value)        |
|       018h 8   Unknown (zerofilled)                                                |
|       020h ..  Info Block (plus Folder List, Directory List, String Table)         |
|       ...  ..  File Data                                                           |
+------------------------------------------------------------------------------------+
```


### Info Block (20h-bytes, plus Folder List, Directory List, String Table)

```
+------------------------------------------------------------------------------+
|       000h 4   Folder List Size/10h    (number of folders)                   |
|       004h 4   Folder List Offset      (relative to the start of Info block) |
|       008h 4   Directory List Size/14h (number of files+folders)             |
|       00Ch 4   Directory List Offset   (relative to the start of Info block) |
|       010h 4   String Table Size/1     (in bytes)                            |
|       014h 4   String Table Offset     (relative to the start of Info block) |
|       018h 2   Number of directory entries that are Files (number of files)  |
|       01Ah 6   Unknown (zerofilled)                                          |
|       020h ..  Folder List (10h bytes per entry)                             |
|       ...  ..  Directory List (14h bytes per entry)                          |
|       ...  ..  String Table                                                  |
+------------------------------------------------------------------------------+
```


### Folder List Entries (10h-bytes each) (first entry is root folder)

```
+------------------------------------------------------------------------------------+
|       000h 4   Short name (first 4 chars of name, uppercase, spc-padded, eg. ROOT) |
|       004h 4   Name Offset (relative to start of string table)                     |
|       008h 2   Name Checksum                                                       |
|       00Ah 2   Number of Directory entries in this folder                          |
|       00Ch 4   Index of first Directory entry for this folder                      |
+------------------------------------------------------------------------------------+
```


### Directory Entries (14h-bytes each) (contains both Files and Folders)

```
+------------------------------------------------------------------------------------+
|       000h 2   Index of this directory entry (aka File ID or so) (or FFFFh=Folder) |
|       002h 2   Name Checksum                                                       |
|       004h 2   Type/Attributes? (1100h=File, 0200h=Folder)                         |
|       006h 2   Name Offset (relative to start of string table)                     |
|       008h 4   File Data Offset   (or, for folders: Index in Folder List)          |
|       00Ch 4   File Size in bytes (or, for folders: unused)                        |
|       010h 4   Unknown (zerofilled)                                                |
+------------------------------------------------------------------------------------+
```


### String Table & Name Checksums
The string table consists of null-terminated ASCII(?) strings. The Name Checksums (in Folder List and Directory Entries) are calculated as so:

```
+--------------------------------------------------------------------------------+
|       sum=0, i=0, while name[i]<>00h do sum=((sum*3)+name[i]) AND FFFFh, i=i+1 |
+--------------------------------------------------------------------------------+
```




