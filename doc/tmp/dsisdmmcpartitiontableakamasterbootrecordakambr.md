# DSi SD/MMC Partition Table (aka Master Boot Record aka MBR)


### DSi eMMC Partition table
The decrypted DSi MBR contains (for 240MB chips; 3rd part differs for 245.5MB):

```
+-------------------------------------------------------------------------------------+
|       0000  00 00 00 00 00 00 00 00 .. .. .. .. 00 00        ;bootcode (zero)       |
|       01BE  00 03 18 04 06 0F E0 3B 77 08 00 00 89 6F 06 00  ;1st partition (main)  |
|       01CE  00 02 CE 3C 06 0F E0 BE 4D 78 06 00 B3 05 01 00  ;2nd partition (photo) |
|       01DE  00 02 DE BF 01 0F E0 BF 5D 7E 07 00 A3 01 00 00  ;3rd partition (extra) |
|       01EE  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ;4th partition (none)  |
|       01FE  55 AA                                            ;mbr id (55h,AAh)      |
+-------------------------------------------------------------------------------------+
```

Above values are following the classical standard MBR format:

```
+----------------------------------------------------------------------------------+
|       000h      446  bootcode (zerofilled on DSi)                   ;-bootcode   |
|       1BEh+n*10h  1  status (00h)                                   ;\           
|       1BFh+n*10h  3  chsFirst                                       ; four       |
|       1C2h+n*10h  1  type (00h=unused, 01h=FAT12, 06h=FAT16B)       ; partitions |
|       1C3h+n*10h  3  chsLast                                        ; (n=0..3)   |
|       1C6h+n*10h  4  lbaFirst  ;\logical block addresses/sizes      ;            
|       1CAh+n*10h  4  lbaSize   ;/counted in 200h-byte sectors       ;/           |
|       1FEh        2  mbrsig (55h,AAh)                               ;-MBR ID     |
+----------------------------------------------------------------------------------+
```

The CHS and LBA values are essentially containing the same information (CHS being an older standard, and LBA being invented in 1996). The 24bit CHS values are encoded as:

```
+-----------------------------------------------------------------------+
|       0-7    Head Bit0-7     (00h..FEh) (or less common, 00h..FFh)    |
|       8-13   Sector Bit0-5   (01h..3Fh)                               |
|       14-15  Cylinder Bit8-9                                          |
|       16-23  Cylinder Bit0-7 (000h..3FFh, with above bit8-7)          |
+-----------------------------------------------------------------------+
```

To convert CHS to LBA, one must know the number of (logical) heads and sectors per cylinder (that info isn\'t stored in the MBR). The DSi\'s eMMC uses 32 sectors, 16 heads, 1024 cylinders:

```
+-----------------------------------------------------------------------+
|       LBA = (Cylinder*32*16) + (Head*32) + (Sector-1)                 |
+-----------------------------------------------------------------------+
```

Anyways, it\'s better/easier to use the LBA values directly, and ignore the CHS values.

### 3DS eMMC Partition table
The 3DS does have a DSi compatible MBR (with main & photo partitions, as shown above). The additional 3DS partitions are accessed via a separate \"NCSD\" header (with 3DS specific encryption keys, which aren\'t available in DSi mode).

### SD/MMC Card Partition table
SD/MMC Cards are shipped with pre-formatted filesystem, so they should stick to some standarized MBR variant, with only a single partition used, possibly with additional date/id fields(?).
Note that SD/MMC Cards may or may not use partition tables (see CSD Register, FILE_FORMAT entry).

### Formatting and Reformatting
SD/MMC cards are usually pre-formatted with empty filesystems. Reformatting should be avoided, or should be done only with tools that are aware of some memory card specific requirements:
The cluster size should not be less than the physical sector size (otherwise, when writing smaller clusters, sectors may get erased multiple times, which would result in slower writing and reduced lifetime).
Many devices do support only the standard FAT filesystems (for example, cameras or mp3-players may be unable to access memory cards with NTFS filesystem).

### More info
For more info on MBR variants (and on the Partition Type value at 1C2h+n\*10h), see:

```
+--------------------------------------------------------------------------+
|       http://en.wikipedia.org/wiki/Master_Boot_Record                    |
|       http://en.wikipedia.org/wiki/Partition_type <-- rather meaningless |
+--------------------------------------------------------------------------+
```




