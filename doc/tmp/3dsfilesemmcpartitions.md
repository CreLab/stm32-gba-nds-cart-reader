# 3DS Files - eMMC Partitions


The 3DS can have up to eight primary NCSD partitions, some of these
partitions point to secondary MBR partition tables, each of those MBRs
could have up to four child partitions (with FAT filesystems).

**NAND structure**

```
+-----------------------------------------------------------------------+
|       Offset    Size      Name  _NCSD_partition_  AES Description     |
|                                 FS   crypt index  key                 |
|                                 type type                             |
|       00000000h 200h                                  NCSD header     |
|       00000000h 0B100000h       0x01 0x01  0x00   03h DSi MBR         |
|       00004                                                           |
| 000h 200h?             -    -     -    -   Some Consoles: Dummy FAT16 |
|                                                                       |
|      00012C00h 200h              -    -     -    11h New3DS FIRM keys |
|       00012E                                                          |
| 00h 08FB5200h twln                    03h DSi FAT16 File System, main |
|       09011A0                                                         |
| 0h 020B6600h twlp                    03h DSi FAT12 File System, photo |
|                                                                       |
| 0B100000h 00030000h       0x04 0x02  0x01   07h AGB_FIRM GBA savegame |
|                                                                       |
|    0B130000h 00400000h firm0 0x03 0x02  0x02   06h Firmware partition |
|       0B5300                                                          |
| 00h 00400000h firm1 0x03 0x02  0x03   06h Firmware partition (backup) |
|       0B930000h 2F5D0000h       0x01 0x02  0x04   04h Old3DS: MBR     |
|       0B95                                                            |
| CA00h 2F3E3600h nand                    04h Old3DS: FAT16 File System |
|       0B930000h 41ED0000h       0x01 0x03  0x04   05h New3DS: MBR     |
|       0B95                                                            |
| AE00h 41D2D200h nand                    05h New3DS: FAT16 File System |
+-----------------------------------------------------------------------+
```


**Physical Size**

```
+-----------------------------------------------------------------------+
|       Device  eMMC Chip                Size                           |
|                                                                       |
| 2DS     Toshiba ?                3AF00000h ;\943MB   ;uh, all unknown 
|       Old3                                                            |
| DS  Toshiba ?                3AF00000h ;/        ;CID and chip names? |
|       2DS                                                             |
|  ?                        3B000000h ;<-- 3AF00000h and up E3h-filled? |
|       2DS     Samsung ?                3BA00000h ;\954MB              
|       Old3DS  Samsung ?                3BA00000h ;/                   |
|       2DS     Samsung ?                4D800000h ;\1240MB             
|       New3DS  Samsung KLM4G1YE0C-B301  4D800000h ;/                   |
|       New3DS  Samsung ?                74800000h ;-1864MB             |
|       2DS     Toshiba ?                76000000h ;\1888MB             
|       New3DS  Toshiba ?                76000000h ;/                   |
+-----------------------------------------------------------------------+
```


**Encryption**
The NAND file system is encrypted using AES-CTR. The keyslot used for
each partition is determined by the NCSD partition FS type and
encryption type.

NAND sectors which were never written to contain plaintext 00h or FFh
bytes.

None of the NAND partitions are normally accessible from the ARM11,
except for twlp. CTR/TWL NAND FS can only be accessed when the exheader
access control descriptor for those are enabled. Normally the CTR/TWL
NAND descriptors are never enabled for retail ARM11 CXI processes. The
ARM11 can only access \"nand:/rw/\" mounted as the nandrw archive, an
\"nand:/ro/\" mounted as the nandro archive below.

**eMMC 4000h (on some consoles) (empty 00h-filled on others)**
On some 3DS systems (such as 3DS XL), there\'s a plaintext FAT16 boo
record located at NAND offset 0x4000. This block does not exist for
launch-day 3DS systems. This is the only plaintext block for this
\"partition\".
That is, a 200h-byte VBR sector with string FAT16 (the actual FAT, Root,
and Data sectors don\'t exist\... and the Data clusters would probabl
overlap other partitions).

**eMMC 12C00h (aka Sector 96h) (New3DS only) (empty FFh-filled on
Old3DS)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|   000h 10h   Used for generating Key X values for keyslot 15h and 18h |
|       010h 10h                                                        |
|    Used for generating Key X values for keyslot 16h and 19h-1Fh ;v9.6 |
|       020h 1E0h  Further constants (unused)                           |
+-----------------------------------------------------------------------+
```

This 200h-byte sector contains New3DS keys, this entire sector is
encrypted via AES-ECB with a console-unique keyX+keyY. The keyX+keyY for
this is generated by the New3DS arm9bin-loader. Once the arm9bin-loader
finishes decrypting this data, the keyX+keyY in the keyslot are then
cleared, then the memory used for generating the keydata is disabled
(after it finishes using it for TWL key init).
The decrypted sector is same on all New3DS consoles (except,
retail-vs-debug are different):

```
+-----------------------------------------------------------------------+
|                                                                       |
| Decrypted 200h-bytes on Retail: 07h,29h,44h,38h, ..., 13h,63h,CFh,8Fh |
|       Decrypted 200h-bytes on Dev:    Unknown...                      |
+-----------------------------------------------------------------------+
```


**3DS CTR partition**
The structure of nand/title appears to be exactly the same as SD, except
savegames are stored under the nand/data/\<ID0\>/sysdata director
instead. The sub-directory name under nand/data is the SHA256 hash over
the movable.sed keyY. This nand/data/\<ID0\> directory is the NAN
equivalent of the \"sdmc/Nintendo 3DS/\<ID0\>/\<ID1\>\" directory
however the data contained here is stored in cleartext. The movable.sed
keyY is only used for AES MACs for nand/data/\<ID0\>. Th
nand/data/\<ID0\>/extdata directory contains the shared extdata, and i
structured exactly the same way as SD extdata.

**DSi TWL partition**
The structure of these TWL partitions is mostly the same as DSi, except
tickets are stored in the CTR FAT FS. The twlp partition is exactly the
same as DSi. The structure of twln/title is exactly the same as CTR
NAND/SD, except the .cmd file is a cleartext file (this is likely a
dummy file). The data directory under system titles\' /title director
does not exist, this likely only exists for DSiWare. The directory names
titleID-High used under twln/title is from DSi.

**3ds:\\\_\_journal.nn\_ (with system attribute)**

```
+-----------------------------------------------------------------------+
|       00000h 12    ID "LIAFEFAS1",0,0,0  (aka 1SAFEFAIL backwards)    |
|                                                                       |
|    0000Ch 4     Total Filesize/200h (can be C0h=18000h or E0h=1C000h) |
|       000                                                             |
| 10h 4     Bytes 83h,3Eh,5Ch,89h or 86h,03h,0Fh,D7h (timestamp or so?) |
|       00014h 4     Value 01h (whatever)                               |
|       00018h ..    Zero                                               |
|       001DCh 4     Value 03h (whatever)                               |
|       0                                                               |
| 01E0h 20h   Whatever (maybe SHA256 on something) (3Fh,5Ch,AEh,20h,..) |
|       00200h 4     Value 06h (whatever)                               |
|       00204h 1F4h  Zero                                               |
|       00400h 200h  Some FAT Directory sector with short filenames     |
|       00600h 200h  Some FAT Allocation sector with FAT16 entries      |
|       00800h 7C00h Zero                                               |
|                                                                       |
|     Below can be at 08400h..17FFFh, or alternately at 04400h..1BFFFh: |
|       08400h 200h  Some FAT Directory sector with short filenames     |
|       08600h 200h  Some FAT Allocation sector with FAT16 entries      |
|       08800h F800h Random garbage, or encrypted sectors, or whatever  |
+-----------------------------------------------------------------------+
```

Unknown purpose, might be some debug log, or undo-info for handling
incomplete FAT writes to the 3DS partition? If so, unknown if it\'
important to update/delete the journal file after manually changing FAT
contents (to prevent the OS from corrupting/undoing the manual
changes).
Unknown if there is a list of sector numbers for the 200h-byte sectors
(maybe that list exists, but gets zerofilled after completion?), unknown
why there are only short filenames (normally there should be also
long/lowercase names).



