# DSi SD/MMC Firmware dev.kp and cert.sys Certificate Files


### FAT16:\\sys\\cert.sys ;3904 bytes (or 2560 bytes before DSi-Shop connection)
Data in this file is same on all retail DSi consoles (even for different regions like US and EUR and KOR).

```
+--------------------------------------------------------------------------+
|       000h 300h  Public RSA Key "XS00000006" signed by "Root-CA00000001" |
|       300h 400h  Public RSA Key "CA00000001" signed by "Root"            |
|       700h 300h  Public RSA Key "CP00000007" signed by "Root-CA00000001" |
|      Below NOT in Korea? Or NOT when notyet connected to DSi Shop?       |
|       A00h 240h  Public ECC Key "MS00000008" signed by "Root-CA00000001" |
|       C40h 300h  Public RSA Key "XS00000003" signed by "Root-CA00000001" |
+--------------------------------------------------------------------------+
```

The cert.sys for DSi debug version is different:

```
+--------------------------------------------------------------------------+
|       000h 300h  Public RSA Key "CP00000005" signed by "Root-CA00000002" |
|       300h 300h  Public RSA Key "XS00000006" signed by "Root-CA00000002" |
|       600h 400h  Public RSA Key "CA00000002" signed by "Root"            |
|       A00h 300h  Public RSA Key "CP00000007" signed by "Root-CA00000002" |
+--------------------------------------------------------------------------+
```

More detailed, the retail version of cert.sys looks as so:

```
+------------------------------------------------------------------------+
|       000h 4    Signature Type (00,01,00,01) (100h-byte RSA)        ;\ 
|       004h 100h Signature RSA-OpenPGP-SHA1 across 140h..2FFh        ;  |
|       104h 3Ch  Signature padding/alignment (zerofilled)            ;  |
|       140h 40h  Signature Name "Root-CA00000001", 00h-padded        ;  |
|       180h 4    Key Type (00,00,00,01) (100h-byte RSA)              ;  |
|       184h 40h  Key Name "XS00000006", 00h-padded                   ;  |
|       1C4h 4    Key Random/time/type/flags/chksum?                  ;  |
|       1C8h 100h Key Public RSA Key (92,FF,96,40..)                  ;  |
|       2C8h 4    Key Public RSA Exponent? (00,01,00,01)              ;  |
|       2CCh 34h  Key padding/alignment (zerofilled)                  ;/ |
|       300h 4    Signature Type (00,01,00,00) (200h-byte RSA) (!)    ;\ 
|       304h 200h Signature RSA-OpenPGP-SHA1 across 540h..6FFh        ;  |
|       504h 3Ch  Signature padding/alignment (zerofilled)            ;  |
|       540h 40h  Signature Name "Root", 00h-padded                   ;  |
|       580h 4    Key Type (00,00,00,01) (100h-byte RSA)              ;  |
|       584h 40h  Key Name "CA00000001", 00h-padded                   ;  |
|       5C4h 4    Key Random/time/type/flags/chksum?                  ;  |
|       5C8h 100h Key Public RSA Key (B2,79,C9,E2..)                  ;  |
|       6C8h 4    Key Public RSA Exponent? (00,01,00,01)              ;  |
|       6CCh 34h  Key padding/alignment (zerofilled)                  ;/ |
|       700h 4    Signature Type (00,01,00,00) (100h-byte RSA)        ;\ 
|       704h 100h Signature RSA-OpenPGP-SHA1 across 840h..9FFh        ;  |
|       804h 3Ch  Signature padding/alignment (zerofilled)            ;  |
|       840h 40h  Signature Name "Root-CA00000001", 00h-padded        ;  |
|       880h 4    Key Type (00,00,00,01) (100h-byte RSA)              ;  |
|       884h 40h  Key Name "CP00000007", 00h-padded                   ;  |
|       8C4h 4    Key Random/time/type/flags/chksum?                  ;  |
|       8C8h 100h Key Public RSA Key (93,BC,0D,1F..)                  ;  |
|       9C8h 4    Key Public RSA Exponent? (00,01,00,01)              ;  |
|       9CCh 34h  Key padding/alignment (zerofilled)                  ;/ |
|      Below NOT when notyet connected to DSi Shop:                      |
|       A00h 4    Signature Type (00,01,00,01) (100h-byte RSA)        ;\ 
|       A04h 100h Signature RSA-OpenPGP-SHA1 across B40h..C3Fh        ;  |
|       B04h 3Ch  Signature padding/alignment (zerofilled)            ;  |
|       B40h 40h  Signature Name "Root-CA00000001", 00h-padded        ;  |
|       B80h 4    Key Type (00,00,00,02)   (ECC, sect233r1, non-RSA)  ;  |
|       B84h 40h  Key Name "MS00000008", 00h-padded                   ;  |
|       BC4h 4    Key Random/time/type/flags/chksum?                  ;  |
|       BC8h 3Ch  Key Public ECC Key (point X,Y) (01,93,6D,08..)      ;  |
|       C04h 3Ch  Key padding/alignment (zerofilled)                  ;/ |
|       C40h 4    Signature Type (00,01,00,01) (100h-byte RSA)        ;\ 
|       C44h 100h Signature RSA-OpenPGP-SHA1 across D80h..F3Fh        ;  |
|       D44h 3Ch  Signature padding/alignment (zerofilled)            ;  |
|       D80h 40h  Signature Name "Root-CA00000001", 00h-padded        ;  |
|       DC0h 4    Key Type (00,00,00,01) (100h-byte RSA)              ;  |
|       DC4h 40h  Key Name "XS00000003", 00h-padded                   ;  |
|       E04h 4    Key Random/time/type/flags/chksum?                  ;  |
|       E08h 100h Key Public RSA Key (AD,07,A9,37..)                  ;  |
|       F08h 4    Key Public RSA Exponent? (00,01,00,01)              ;  |
|       F0Ch 34h  Key padding/alignment (zerofilled)                  ;/ |
+------------------------------------------------------------------------+
```

Cert chain for the DSi. Contains certificates with signed keys:

```
+-------------------------------------------------------------------------------------+
|       Root-CA00000001:            used for signing the four certificates below      |
|       Root-CA00000001-CP00000007: used for signing TMDs ("Content Protection"?)     |
|       Root-CA00000001-MS00000008: used for signing per-console ECC keys ("Master"?) |
|       Root-CA00000001-XS00000003: used for signing tickets from the DSiWare Shop    |
|       Root-CA00000001-XS00000006: used for signing (common) tickets ("access"?)     |
+-------------------------------------------------------------------------------------+
```

A similar file with the same name exists on the Wii.

### FAT16:\\sys\\dev.kp ;446 bytes (encrypted), 414 bytes (when decrypted)
The dev.kp file is encrypted with ES Block Encryption (using same key X/Y as for .tik files):

```
+-------------------------------------------------------------------------------+
|       KEY_X[00h..03h] = 4E00004Ah                           ;\                
|       KEY_X[04h..07h] = 4A00004Eh                           ; same as for Tad |
|       KEY_X[08h..0Bh] = Port[4004D00h+4] xor C80C4B72h      ;                 |
|       KEY_X[0Ch..0Fh] = Port[4004D00h+0]                    ;/                |
|       KEY_Y[00h..0Fh] = Constant (E5,CC,5A,8B,...)  ;from ARM7BIOS            |
+-------------------------------------------------------------------------------+
```

- [DSi ES Block Encryption](./dsiesblockencryption.md)
The decrypted dev.kp contains following entries:

```
+----------------------------------------------------------------------------+
|       000h 4    Signature Type (00,01,00,02) (ECC, sect233r1, non-RSA)  ;\ 
|       004h 3Ch  Signature Hex numbers... across... below?               ;  |
|       040h 40h  Signature padding/alignment (zerofilled)                ;  |
|       080h 40h  Signature Name "Root-CA00000001-MS00000008", 00h-padded ;  |
|       0C0h 4    Key Type (00,00,00,02)       (ECC, sect233r1, non-RSA)  ;  |
|       0C4h 40h  Key Name "TWxxxxxxxx-08nnnnnnnnnnn1nn", 00h-padded      ;  |
|       104h 4    Key Random/time/type/flags/chksum?                      ;  |
|       108h 3Ch  Key Public ECC Key (point X,Y)       ;<-- public key    ;  |
|       144h 3Ch  Key padding/alignment (zerofilled)                      ;  |
|       180h 1Eh  Key Private ECC Key                  ;<-- private key   ;/ |
+----------------------------------------------------------------------------+
```

The \"TWxxxxxxxx-08nnnnnnnnnnn1nn\" string may vary:

```
+----------------------------------------------------------------------------------+
|       "TW" might be for DSi only (ie. it might be different on DSi XL or 3DS?)   |
|       "xxxxxxxx" is 8-digit lower-case hex number (unknown where from; for .tik) |
|       "08nnnnnnnnnnn1nn" is 16-digit lower-case hex number (from Port 4004D00h)  |
+----------------------------------------------------------------------------------+
```

Example:

```
+-----------------------------------------------------------------------+
|       Signature across rest of block -- type = 0x00010002, ECC        |
|       0000000: 00 01 00 02 00 db da 21 3b e1 f1 bf bb 4d dc 1d        |
|       0000010: 60 29 da 19 42 1e 66 4f a8 e5 27 a1 d4 ea 46 7d        |
|       0000020: 9b b4 00 95 c5 0d e8 fa ef a7 8d e9 bc 54 da c1        |
|       0000030: 24 94 0b 7c ad a8 61 d5 05 97 c2 64 38 ad 18 f9        |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|       0000040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000060: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|       Key used to sign this cert (Root-CA00000001-MS00000008)                    |
|       0000080: 52 6f 6f 74 2d 43 41 30 30 30 30 30 30 30 31 2d  Root-CA00000001- |
|       0000090: 4d 53 30 30 30 30 30 30 30 38 00 00 00 00 00 00  MS00000008       |
|       00000a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00                   |
|       00000b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00                   |
+----------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|       Console ID string                                                          |
|       00000c0: 00 00 00 02 54 57 63 37 39 64 63 65 63 39 2d 30  ....TWc79dcec9-0 |
|       00000d0: 38 61 32 30 32 38 37 30 31 30 38 34 31 31 38 00  8a2028701084118. |
|       00000e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00                   |
|       00000f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00                   |
+----------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|       Public ECC key (30 bytes, starting at 0x108)                    |
|       0000100: 00 00 00 00 6f dd de 42 01 e0 34 a3 19 bc a9 af        |
|       0000110: 50 fe 8a ac 75 08 07 a9 3a 2c 21 51 93 ae 4a 90        |
|       0000120: 6e 62 41 f1 a2 fe 00 00 3d 0a 13 97 da 53 17 98        |
|       0000130: 69 38 65 67 ca f4 9c 87 ec 44 b7 eb d0 ec b8 3d        |
|       0000140: 23 cf 7a 35 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000150: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000160: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
|       0000170: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00        |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|       Private per-console ECC key, used for signing files on SD       |
|       0000180: 01 12 9d e0 77 82 44 d3 ee 99 ad ce e5 fa fa ed        |
|       0000190: c9 ab 8e a1 f9 b5 c8 14 3c 74 74 f8 19 3a              |
+-----------------------------------------------------------------------+
```

Note that the console id itself is burned in an OTP area of the TWL CPU, and changing the contents of this file will not actually change the console id.
This file contains the unique per-console ECC private-public key pair, along with a certificate issued by Nintendo.
This file is created by the DSi Shop, with data from a SOAP reply. The SOAP request data includes the hw console id, and the 0x100-byte RSA signature stored in NAND file \"HWID.sgn\". Trying to send that request would require a NAND dump, but when you have a NAND dump already sending that request is pointless since you can grab dev.kp from NAND.
Sending that request is pointless anyway since the dev.kp data from the server is random. The returned dev.kp data from the server for the EC private/public keys are random, the ticket consoleID immediately following TW before - in the twcert keyid is random as well. DSi Shop and System Settings don\'t contain any code for deleting dev.kp. If you try to delete/rename dev.kp manually from NAND a new dev.kp will be generated by the shop, but then the server will return an error since the server account public dev.kp cert won\'t match.

Data management can\'t be accessed when dev.kp doesn\'t exist since you\'d have no twcert to sign/verify tads with, like when you never connected the DSi Shop server.



