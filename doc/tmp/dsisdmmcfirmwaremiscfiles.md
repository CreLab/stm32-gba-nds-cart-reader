# DSi SD/MMC Firmware Misc Files


### FAT16:\\sys\\HWINFO_S.dat (aka Serial/Barcode) (16Kbytes)

```
+------------------------------------------------------------------------------------+
|       0000h 80h   RSA-SHA1-HMAC across entries [0088h..00A3h]                      |
|                   (with RSA key from Bootsectors, and also from Launcher)          |
|                   (with SHA1-HMAC key = SHA1([4004D00h..4004D07h], aka Console ID) |
|       0080h 4     Header, Version or so (00000001h)                                |
|       0084h 4     Header, Size of entries at [0088h..00A3h] (0000001Ch)            |
|       0088h 4     Bitmask for Supported Languages (3Eh for Europe) (as wifi_flash) |
|       008Ch 4     Unknown (00,00,00,00)  (bit0=flag for 4004020h.bit0=wifi ?)      |
|       0090h 1     Console Region (0=JPN, 1=USA, 2=EUR, 3=AUS, 4=CHN, 5=KOR)        |
|       0091h 12    Serial/Barcode (ASCII, 11-12 characters; see console sticker)    |
|       009Dh 3     Unknown (00,00,3C)                     ;"<"                      |
|       00A0h 4     Title ID LSBs for Launcher ("PANH", aka HNAP spelled backwards)  |
|       00A4h 3F5Ch Unused (FFh-filled)                                              |
+------------------------------------------------------------------------------------+
```

Entries \[0088h..009Fh\] are copied to \[2FFFD68h..2FFFD7Fh\]. Entry \[00A0h\] is used to construct the region-specific filename of the Launcher (System Menu).
The RSA with Console ID means that one cannot change the region/language stuff.
The 3DS has similar data stored in file SecureInfo_A on 3DS partition.

### FAT16:\\sys\\HWINFO_N.dat (16Kbytes)

```
+-------------------------------------------------------------------------+
|       0000h 14h   SHA1 on entries [088h..09Bh]                          |
|       0014h 6Ch   Zerofilled                                            |
|       0080h 4     Header, Version or so (00000001h)                     |
|       0084h 4     Header, Size of entries at [0088h..009Bh] (00000014h) |
|       0088h 4     Some per-console ID (used what for?)                  |
|       008Ch 10h   Some per-console ID (used in "Tad Files")             |
|       009Ch 3F64h Unused (FFh-filled)                                   |
+-------------------------------------------------------------------------+
```

Entries \[0088h..009Bh\] are copied to \[2000600h..2000613h\].

### FAT16:\\sys\\HWID.sgn (256 bytes)

```
+-----------------------------------------------------------------------+
|       0000h 100h  RSA-OpenPGP-SHA1 across... whatever?                |
+-----------------------------------------------------------------------+
```

Seems to be used only by DSi Shop. The RSA keys are unknown for retail version. Also unknown WHAT the SHA1 is computed on (probably some console and/or region IDs).
The System Updater tool (for debug version) contains both public and private RSA keys for the file; the keys don\'t work for retail version though.
The OpenPGP bytes are same as for SWI 23h (but with more FFh padding bytes due to the 100h-byte RSA size).

### FAT16:\\shared2\\0000 (2048K) (sound recorder)
Huge 2Mbyte file with several used areas (and many zerofilled areas).
Contains a FAT12 filesystem with several voice .dat files for the Sound Recorder of the Nintendo DSi Sound utility. Unused clusters seem to contain garbage (maybe un-encrypted eMMC sectors).

```
+-----------------------------------------------------------------------+
|       voice18111008215651000010001.dat  ;14402h bytes                 |
|       voice20131018211242000010001.dat  ;14402h bytes                 |
|       voice19111008215708000010001.dat  ;14402h bytes                 |
|       voice00131018211411003110001.dat  ;14402h bytes                 |
|       voice01150418144405002110001.dat  ;14402h bytes                 |
|       voiceNNYYMMDDHHMMSS00NN10001.dat  ;14402h bytes                 |
+-----------------------------------------------------------------------+
```

Note: The DSi Sound utility is additionally having a 512Kbyte private.sav file (also containing a FAT12 filesystem; although it seems to contain only a MBR, FATs, and an empty Root directory - plus garbage in unused clusters).

### FAT16:\\import\\
### FAT16:\\progress\\
### FAT16:\\tmp\\es\\write\\
Empty folders.



