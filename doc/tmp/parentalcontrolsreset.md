# Parental Controls Reset


### Parental Controls Reset
Click \"I Forgot\" when getting prompted to enter the PIN and Secret Question, the console will then display an 8-digit Enquiry Number (or 10-digit with region/version RV/RVV in upper digits), the customer service hotline uses that number (and the current month/day, MMDD) to compute a 5-digit Master Key for resetting Parental Controls.
### DSi/Wii version

```
+------------------------------------------------------------------------------------+
|       This uses a standard CRC32 with polynomial EDB88320h.                        |
|       Enquiry = "XXXXNNNN" (8-digit, based on MAC but only last 4-digits are used) |
|       MasterKey = ((StandardCRC32("MMDDNNNN") XOR 0000AAAAh)+14C1h mod 100000      |
|       The XOR 0000AAAAh is replacing the standard crc32's final XOR FFFFFFFFh?     |
+------------------------------------------------------------------------------------+
```

### 3DS firmware version 1.0.0-X through 6.3.0-X

```
+------------------------------------------------------------------------------------+
|       Same as DSi/Wii, but using a nonstandard CRC32 (with polynomial EDBA6320h    |
|       instead of EDB88320h, and adding 1657h instead of 14C1h to the final result. |
|       Enquiry = "XXXXNNNN" (8-digit, based on MAC but only last 4-digits are used) |
|       MasterKey = ((NonStandardCRC32("MMDDNNNN") XOR 0000AAAAh)+1657h mod 100000   |
|       "This had a minor refactor in 6.0.0-X but is functionally identical."        |
+------------------------------------------------------------------------------------+
```

### 3DS firmware version7.0.0-X through 7.1.0-X (with version V=0)

```
+----------------------------------------------------------------------------------+
|       Similar as above, using a 10-digit Enquiry, and SHA256-HMAC instead CRC32. |
|       Enquiry = "RVNNNNNNNN" (10-digit, based on MAC?, upper digits=region/ver?) |
|       HmacKey = from mset .rodata, differs between regions.                      |
|       MasterKey = (FirstWordOf(SHA256HMAC("MMDDR0NNNNNNNN",HmacKey)) mod 100000  |
+----------------------------------------------------------------------------------+
```

### 3DS firmware versio n7.2.0-X and up (with version VV=10 and up)

```
+---------------------------------------------------------------------------------+
|       As above, but with HmacKey stored in a separate encrypted file.           |
|       AesIv,RVV = from masterkey.bin (found in System Data Archives 2, CVer)    |
|       AesKey = from mset .rodata, using RVV as decrypt key number               |
|       Enquiry = "RVVNNNNNNN" (10-digit, based on MAC?, upper digits=region/ver) |
|       HmacKey = from masterkey.bin (decrypt via AES-CTR with AesIv and AesKey)  |
|       MasterKey = (FirstWordOf(SHA256HMAC("MMDDR0NNNNNNNN",HmacKey)) mod 100000 |
+---------------------------------------------------------------------------------+
```

Newer(?) firmwares are using R=9 for japan (instead of R=0, maybe because people did tend to omit leading zeroes when specifying the Enquiry Number).
Alternately, an easier way to reset parental controls is to dump the PIN from \"config\" (3DS) or TWLCFG (DSi).




