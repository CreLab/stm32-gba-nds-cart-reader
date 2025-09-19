# BIOS RSA Functions (DSi only)


RSA_Init_crypto_heap(heap_nfo,heap_start,heap_size)
RSA_Decrypt(heap_nfo,struct,dest4)
RSA_Decrypt_Unpad(heap_nfo,dst,src,key)
RSA_Decrypt_Unpad_OpenPGP_SHA1(heap_nfo,dst,src,key)

RSA is important because the DSi cartridge header and system files do contain RSA signatures. Which makes it impossible to create unlicensed software (without knowing Nintendo\'s private key).
- [BIOS RSA Basics](./biosrsabasics.md)
- [BIOS RSA Pseudo Code](./biosrsapseudocode.md)

### SWI 20h (DSi9/DSi7) - RSA_Init_crypto_heap(heap_nfo,heap_start,heap_size)
Initializes the heap for use with SWI 21h..23h. heap_nfo is a 0Ch-byte structure, which gets set to:

```
+-------------------------------------------------------------------------------+
|       [heap_nfo+0] = heap_start (rounded-up to 4-byte boundary)               |
|       [heap_nfo+4] = heap_end   (start+size, rounded-down to 4-byte boundary) |
|       [heap_nfo+8] = heap_size  (matched to above rounded values)             |
+-------------------------------------------------------------------------------+
```

heap_start should point to a free memory block which will be used as heap, heap_size should be usually 1000h.

### SWI 21h (DSi9/DSi7) - RSA_Decrypt(heap_nfo,ptr_nfo,len_dest)

```
+-----------------------------------------------------------------------+
|       [ptr_nfo+0] = dst (usually 7Fh bytes, max 80h bytes)            |
|       [ptr_nfo+4] = src (80h bytes)                                   |
|       [ptr_nfo+8] = key (80h bytes)                                   |
+-----------------------------------------------------------------------+
```

This is a subfunction for SWI 22h/23h. It\'s returning raw decrypted data without unpadding (aside from stripping leading 00h bytes; most (or all) signatures are containing one leading 00h byte, so the returned \[len_dest\] value will be usually 7Fh).
Return value (r0) is: 0=failed, 1=okay. The length of the decrypted data is returned at \[len_dest\].

### SWI 22h (DSi9/DSi7) - RSA_Decrypt_Unpad(heap_nfo,dst,src,key)
Same as SWI 21h, and additionally removes the \"01h,min eight FFh,00h\" padding. src,dst,key should be 80h-bytes. The output at dst can be theoretically max 80h-bytes (or shorter due to removed padding). In practice, the DSi is often using only the first 14h-bytes at dst (aka the last 14h-bytes from src) as SHA1 or SHA1-HMAC value (RSA-SHA1). Return value (r0) is: 0=failed, 1=okay.

### SWI 23h (DSi9/DSi7) - RSA_Decrypt_Unpad_OpenPGP_SHA1(heap_nfo,dst,src,key)
Same as SWI 22h, but with some extra processing for extracting a SHA1 value from an OpenPGP header: The data must consist of five ASN.1 (DER) chunks (with Tag IDs 30h,30h,06h,05h,04h), the last chunk (with ID=04h) must be 14h bytes in size, and the 14h-byte chunk data is then copied to dst. The other four chunks must exist, but their content is just skipped.

```
+----------------------------------------------------------------------------------+
|       00h 1    Leading zero       (00h)                           ;\             
|       01h 1    Block type         (01h)                           ; padding      |
|       02h 5Ah  Padding Bytes      (FFh-filled)                    ;              |
|       5Ch 1    Padding End        (00h)                           ;/             |
|       5Dh 2    30h,junk(1)        (30h,21h)                       ;-sequence     |
|       5Fh 2    30h,junk(1)        (30h,09h)                       ;-sequence     |
|       61h 7    06h,len,junk(len)  (06h,05h, 2Bh,0Eh,03h,02h,1Ah)  ;-OID for SHA1 |
|       68h 2    05h,junk(1)        (05h,00h)                       ;-null         |
|       6Ah 16h  04h,len,sha1(len)  (04h,14h, sha1[14h bytes])      ;-SHA1         |
+----------------------------------------------------------------------------------+
```

The \"junk\" bytes aren\'t actually used/verified by the DSi. Handling chunks with len\>7Fh looks quite weird/bugged. The DSi firmware contains some functions where it could optionally use SWI 22h or SWI 23h for RSA signatures (although, there aren\'t any known cases where it would actually use SWI 23h). Note: The DSi\'s Flipnote \".ppm\" files are using the SWI 23h style SHA1 format (but Flipnote contains it\'s own RSA functions instead of using the BIOS SWI functions). DS Download Play (and equivalent code in NDS Firmware) is SWI 23h style, too (but also uses its own RSA function instead of the BIOS SWI).
Note: The format is based on the OpenPGP Message Format (RFC 4880), that format allows to use similar headers for MD5, SHA256, etc. (the DSi supports only SHA1 though).

### Unencrypted Signatures
Emulators can hook the RSA BIOS functions to copy unencrypted signatures as-is (instead of trying to decrypt them). That allows to create \"authentic\" files that are fully compatible with the DSi firmware, and which would be actually working on real hardware (when knowing the private key).
Unencrypted 80h-byte signatures should be stored in following format (as defined in RFC 2313):

```
+-------------------------------------------------------------------------------------+
|       00h   1      "00" Leading zero (00h)                                          |
|       01h   1      "BT" Block type (always 01h on DSi)                              |
|       02h   8+n    "PS" Padding (FFh-filled, min 8 bytes, usually 69h bytes on DSi) |
|       0Ah+n 1      "00" Padding end (00h)                                           |
|       0Bh+n 75h-n  "D"  Data (max 75h bytes, usually a 14h-byte SHA1 value on DSi)  |
+-------------------------------------------------------------------------------------+
```

If the hooked BIOS function sees a RSA source to contain \"00h, 01h, at least eight FFh, followed by 00h\", then it could treat it as unencrypted data (it\'s nearly impossible that an encrypted signature could contain those values).

### Key.Bit0
The DSi BIOS contains two different RSA core modes (either one of them is used, depending on whether BIT0 of the FIRST BYTE of the \"key\" is set or cleared). The purpose & difference between those two modes is unknown. Also, dunno if that BIT0 thing is something common in the RSA world?

### DSi Public RSA Keys (for verifying signatures)

```
+-------------------------------------------------------------------------------------+
|       TWL_FIRM       (F1,F5,1A,FF..) eMMC Boot Info (same key for retail+debug)     |
|       BIOS:FFFF87F4h (C3,02,93,DE..) Key0: System Menu (Launcher) of Retail version |
|       BIOS:FFFF8874h (B6,18,D8,61..) Key1: System Fun Tools and Wifi Firmware       |
|       BIOS:FFFF88F4h (DA,94,09,01..) Key2: System Base Tools (Settings, Shop)       |
|       BIOS:FFFF8974h (95,6F,79,0D..) Key3: DSiWare and DSi ROM Cartridges           |
|       BIOS:FFFF89F4h (D4,30,E3,7D..) Key4: Unknown ;\probably more/unused RSA keys  
|       BIOS:FFFF8A74h (BD,29,02,38..) Key5: Unknown ; (DSi only)                     |
|       BIOS:FFFF8AF4h (CF,8A,4B,15..) Key6: Unknown ; (doesn't exist on 3DS)         |
|       BIOS:FFFF8B74h (A3,BC,C1,7C..) Key7: Unknown ;/                               |
|       BIOS:FFFF9920h (30,33,26,D5..) Unknown (probably NOT a RSA key)               |
|       Launcher       (BA,F1,98,A4..) HWINFO_S.dat (with RSA-SHA1-HMAC)              |
|       Launcher       (9F,80,BC,5F..) Version Data and TWLFontTable.dat              |
|       Launcher       (C7,F4,1D,27..) DS Cart Whitelist (missing RSA in v1.4E)       |
|       Launcher+NDS   (9E,C1,CC,C0..) For wifi-booted NDS titles (DsDownloadPlay)    |
|       Flipnote       (C2,3C,BC,13..) Public key for Flipnote .ppm files             |
|       Unknown        (?)             HWID.sgn                                       |
|       Unknown        (?)             Newer NDS ROM Cartridges (have RSA, too?)      |
|       DSi Shop       (9D,69,36,28..) Unknown, seems to be RSA        (100h bytes)   |
|       Launcher       (F8,24,6C,58..) Root key for cert.sys CA00000001(200h bytes)   |
|       cert.sys       (B2,79,C9,E2..) CA00000001 key for cert.sys keys(100h bytes)   |
|       cert.sys       (93,BC,0D,1F..) CP00000007 key for tmd's        (100h bytes)   |
|       cert.sys       (AD,07,A9,37..) XS00000003 key for shop-tickets (100h bytes)   |
|       cert.sys       (92,FF,96,40..) XS00000006 key for free-tickets (100h bytes)   |
|       cert.sys       (01,93,6D,08..) MS00000008 key for dev.kp       (ECC, non-RSA) |
|       dev.kp         (per-console)   TWxxxxxxxx... key for tad files (ECC, non-RSA) |
|       *.bin          (random?)       AP00030015484e42gg in tad files (ECC, non-RSA) |
|       Launcher+Boot  (BC,FD,A1,FF..) Debug0: System Menu (Launcher, Debug version)  |
|       Launcher       (E9,9E,A7,9F..) Debug1:                                        |
|       Launcher       (A7,9F,54,A0..) Debug2:                                        |
|       Launcher       (AC,93,BB,3C..) Debug3: Public key for Debug DSiware/ROMs      |
|       Debug Updater  (E5,1C,BF,C7..) Debug Public key for HWInfo                    |
|       Debug Updater  (C8,4B,38,2C..) Debug Public key for HWID.sgn    (100h bytes)  |
|       Launcher       (D0,1F,E1,00..) Debug Root key for CA00000002 key(200h bytes)  |
|       debug cert.sys (...)           Debug CA00000002 key for cert.sys(100h bytes)  |
|       debug cert.sys (...)           Debug CP00000005 key for ...?    (100h bytes)  |
|       debug cert.sys (...)           Debug CP00000007 key for ...     (100h bytes)  |
|       debug cert.sys (...)           Debug XS00000006 key for ...     (100h bytes)  |
|       verdata        (...)           Public keys in Version Data file?              |
|       Unknown        (?)             further keys...?                               |
+-------------------------------------------------------------------------------------+
```


### DSi Private RSA Keys (for creating signatures)
Nintendo\'s private keys should be known only by Nintendo. However, the console does have a few \"own\" private keys (for sending signed data to Nintendo (verdata), for storing signed data on SD card (flipnote), plus some more keys for the developer\'s debug version).

```
+-------------------------------------------------------------------------------------+
|       Flipnote       (26,A7,53,7E..) Private key for Flipnote .ppm files            |
|       dev.kp         (per-console)   TWxxxxxxxx... key for tad files (ECC, non-RSA) |
|       (temp/unsaved?)(random?)       AP00030015484e42gg    tad files (ECC, non-RSA) |
|       verdata        (...)           Private keys in Version Data file?             |
|       Debug Updater  (77,FC,77,9E..) Private key for Debug HWID.sgn (100h bytes)    |
|       Debug Updater  (B5,7C,C2,85..) Private key for Debug HWInfo                   |
|       Debug SDK      (95,DC,C8,18..) Private key for Debug DSiware/ROMs (Debug3)    |
|       Unknown        (?)             further keys...?                               |
+-------------------------------------------------------------------------------------+
```

The private keys are usually stored in DER format; that\'s including entries for the public key/exponent, and the original prime numbers that the key was generated from, plus some numbers that were temporarily used during key creation, and with all entries preceeded by tag/length values, whereas values with MSB set are preceeded by a 00h byte to make them \"unsigned\" (eg. most 80h-byte keys will occupy 81h bytes in DER format).



