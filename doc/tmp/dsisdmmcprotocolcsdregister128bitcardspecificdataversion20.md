# DSi SD/MMC Protocol: CSD Register (128bit Card-Specific Data) Version 2.0


### CSD Register (CSD Version 2.0) (SDHC/SDXC)
The field name in parenthesis is set to fixed value and indicates that the host is not necessary to refer these fields. The fixed values enables host, which refers to these fields, to keep compatibility to CSD Version 1.0.
The Cell Type field is coded as follows: R=readable, W(1)=writable once, W=multiple writable.

```
+-------------------------------------------------------------------------------------+
|       Bit   Siz Type   Name                        Field          Value             |
|       127-126 2 R      CSD structure               CSD_STRUCTURE  01b               |
|       125-120 6 R      reserved                    -              000000b           |
|       119-112 8 R      data read access-time-1     (TAAC)         0Eh               |
|       111-104 8 R      data read access-time-2     (NSAC)         00h               |
|       103-96  8 R      max data transfer rate      (TRAN_SPEED)   32h,5Ah,0Bh,2Bh   |
|       95-84  12 R      card command classes        CCC            x1x110110101b     |
|       83-80   4 R      max read data block length       (READ_BL_LEN)        9      |
|       79      1 R      partial blocks for read allowed  (READ_BL_PARTIAL)    0      |
|       78      1 R      write block misalignment         (WRITE_BLK_MISALIGN) 0      |
|       77      1 R      read block misalignment          (READ_BLK_MISALIGN)  0      |
|       76      1 R      DSR implemented                  DSR_IMP              x      |
|       75-70   6 R      reserved                         -                   000000b |
|       69-48  22 R      device size                      C_SIZE              xxxxxxh |
|       47      1 R      reserved                         -                    0      |
|       46      1 R      erase single block enable        (ERASE_BLK_EN)       1      |
|       45-39   7 R      erase sector size                (SECTOR_SIZE)        7Fh    |
|       38-32   7 R      write protect group size         (WP_GRP_SIZE)        00h    |
|       31      1 R      write protect group enable       (WP_GRP_ENABLE)      0      |
|       30-29   2 R      reserved                         -                    00b    |
|       28-26   3 R      write speed factor               (R2W_FACTOR)         010b   |
|       25-22   4 R      max write data block length      (WRITE_BL_LEN)       9      |
|       21      1 R      partial blocks for write allowed (WRITE_BL_PARTIAL)   0      |
|       20-16   5 R      reserved                         -                    00000b |
|       15      1 R      File format group                (FILE_FORMAT_GRP)    0      |
|       14      1 R/W(1) copy flag                        COPY                 x      |
|       13      1 R/W(1) permanent write protection       PERM_WRITE_PROTECT   x      |
|       12      1 R/W    temporary write protection       TMP_WRITE_PROTECT    x      |
|       11-10   2 R      File format                      (FILE_FORMAT)        00b    |
|       9-8     2 R      reserved                         -                    00b    |
|       7-1     7 R/W    CRC                              CRC                  xxh    |
|       0       1 -      not used, always '1'             -                    1      |
+-------------------------------------------------------------------------------------+
```


### C_SIZE
This field is expanded to 22 bits and can indicate up to 2 TBytes (that is the same as the maximum memory space specified by a 32-bit block address.)
This parameter is used to calculate the user data area capacity in the SD memory card (not include the protected area). The user data area capacity is calculated from C_SIZE as follows:

```
+-----------------------------------------------------------------------+
|       memory capacity = (C_SIZE+1) * 512KByte                         |
+-----------------------------------------------------------------------+
```

The Minimum user area size of SDHC Card is 4,211,712 sectors (2GB + 8.5MB).
The Minimum value of C_SIZE for SDHC in CSD Version 2.0 is 001010h (4112).
The Maximum user area size of SDHC Card is (32GB - 80MB).
The Maximum value of C_SIZE for SDHC in CSD Version 2.0 is 00FF5Fh (65375).
The Minimum user area size of SDXC Card is 67,108,864 sectors (32GB).
The Minimum value of C_SIZE for SDXC in CSD Version 2.0 is 00FFFFh (65535).

### TRAN_SPEED
TRAN_SPEED is variable depends on bus speed mode of SD Interface.
When CMD0 is received, this field is reset to 32h.
On SDSC (but not SDHC/SDXC), CMD6 does the same reset stuff?

```
+-----------------------------------------------------------------------+
|       32h   SDSC/SDHC/SDXC in Default Speed mode (25MHz)              |
|       5Ah   SDSC/SDHC/SDXC in High Speed mode    (50MHz)              |
|       0Bh   SDHC/SDXC in SDR50 or DDR50 mode     (100Mbit/sec)        |
|       2Bh   SDHC/SDXC in SDR104 mode             (200Mbit/sec)        |
+-----------------------------------------------------------------------+
```

UHS-II mode is not related to this field.

### CCC, DSR_IMP, COPY, PERM_WRITE_PROTECT, TMP_WRITE_PROTECT
Definition of these fields is same as in CSD Version 1.0.

### TAAC, NSAC, R2W_FACTOR
In SDHC/SDXC, these fields should be fixed to TAAC=0Eh (1 ms), NSAC=00h, and R2W_FACTOR=02h (mul4).
The host should not use TAAC, NSAC, and R2W_FACTOR to calculate timeout and should uses fixed timeout values for read and write operations (See 4.6.2).

### READ_BL_LEN, WRITE_BL_LEN
These two fields are fixed to 9h (which indicates 512 Bytes).

### READ_BL_PARTIAL, WRITE_BL_PARTIAL, READ_BLK_MISALIGN, WRITE_BLK_MISALIGN
These four fields are fixed to 0 (partial block read and physical page crossing prohibited for block read/write).

### SECTOR_SIZE
This field is fixed to 7Fh, which indicates 64 KBytes. This value is not related to erase operation. SDHC and SDXC Cards indicate memory boundary by AU size and this field should not be used.

### ERASE_BLK_EN
This field is fixed to 1, which means the host can erase one or multiple units of 512 bytes.

### WP_GRP_SIZE, WP_GRP_ENABLE
These field are fixed to WP_GRP_SIZE=00h, and WP_GRP_ENABLE=0.
SDHC and SDXC Cards do not support write protected groups.

### FILE_FORMAT_GRP
### FILE_FORMAT
These fields are set to 0. Host should not use these fields.



