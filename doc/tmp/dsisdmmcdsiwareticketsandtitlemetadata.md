# DSi SD/MMC DSiware Tickets and Title metadata


Below describes the \"raw\" ticket+tmd formats. For more info on the data being stored/encrypted in various locations, see these chapters:
- [DSi SD/MMC DSiware Files on Internal eMMC Storage](./dsisdmmcdsiwarefilesoninternalemmcstorage.md)
- [DSi SD/MMC DSiware Files on External SD Card (.bin aka Tad Files)](./dsisdmmcdsiwarefilesonexternalsdcardbinakatadfiles.md)
- [DSi SD/MMC DSiware Files from Nintendo\'s Server](./dsisdmmcdsiwarefilesfromnintendosserver.md)

### Ticket (cetk aka .tik)
Tickets exist as \"cetk\" files (as found on Nintendo\'s server), and as \".tik\" files (as found in nand/ticket folder):

```
+------------------------------------------------------------------------------------+
|       Server:  "cetk"         unencrypted, 2468 bytes (2A4h+700h), tik+certificate |
|       eMMC:    "gggggggg.tik" encrypted,   708 bytes  (2A4h+20h),  tik+es_block    |
|       SD Card: N/A            N/A, tickets aren't exported to SD card              |
+------------------------------------------------------------------------------------+
```

Tickets are used for decrypting downloads from DSi shop. They are essentially containing a 16-byte AES-CBC decryption key, plus signatures and some other stuff.

```
+-------------------------------------------------------------------------------------+
|       000h  4    Signature Type (00h,01h,00h,01h) (100h-byte RSA)                   |
|       004h  100h Signature RSA-OpenPGP-SHA1 across 140h..2A3h                       |
|       104h  3Ch  Signature padding/alignment (zerofilled)                           |
|       140h  40h  Signature Name "Root-CA00000001-XS00000006", 00h-padded            |
|       180h  3Ch  ECDH data for one-time installation keys?   ;zero for free tik's   |
|       1BCh  1    Zero (3DS: Ticket Version=1)                                       |
|       1BDh  1    Zero (3DS: CaCrl Version=0)                                        |
|       1BEh  1    Zero (3DS: SignerCrl Version=0)                                    |
|       1BFh  10h  Encrypted AES-CBC Title Key                                        |
|       1CFh  1    Zero                                                               |
|       1D0h  8    Ticket ID  (00,03,xx,xx,xx,xx,xx,xx) ?                             |
|       1D8h  4    Console ID (see dev.kp "TWxxxxxxxx", zero for free system updates) |
|       1DCh  8    Title ID       (00,03,00,17,"HNAP")                   ;cart[230h]  |
|       1E4h  2    Zero (Wii: mostly FFFFh)                                           |
|       1E6h  2    Title Version (vv,00) (LITTLE-ENDIAN!?)       ;NEWEST ;cart[01Eh]  |
|       1E8h  4    Zero (Wii: Permitted Titles Mask)                                  |
|       1ECh  4    Zero (Wii: Permit mask)                                            |
|       1F0h  1    Zero (Wii: Allow Title Export using PRNG key, 0=No, 1=Yes)         |
|       1F1h  1    Zero (Wii: Common Key Index, 0=Normal, 1=Korea) (DSi: Always 0)    |
|       1F2h  2Ah  Zero                                                               |
|       21Ch  4    Zero (3DS: eShop Account ID?)                                      |
|       220h  1    Zero                                                               |
|       221h  1    Unknown (01h) (Wii: Unknown, 00h=Non-VC, 01h=VC=VirtualConsole?)   |
|       222h  20h  FFh-filled (Wii: Content access permissions, 1 bit per content)    |
|       242h  20h  00h-filled (Wii: Content access permissions, 1 bit per content)    |
|       262h  2    Zero                                                               |
|       264h  4    Zero   ;Wii: Time Limit Enable  (0=Disable, 1=Enable)              |
|       268h  4    Zero   ;Wii: Time Limit Seconds (uh, seconds since/till when?)     |
|       26Ch  38h  Zero   ;Wii: Seven more Time Limits (Enable, Seconds)              |
|       2A4h  700h Certificates (see below) (only in "cetk", not in ".tik)            |
+-------------------------------------------------------------------------------------+
```

The Launcher checks some of the permission entries, but it doesn\'t check RSA for tickets, so one can create own/dummy tickets. The Console ID and Title ID might be also unchecked, so one could possibly simply copy/rename existing tickets (from the same console), or decrypt/copy/re-encrypt tickets (from other consoles).
Note: It seems to be possible to store multiple tickets in one .tik file (in that case each ticket is separately encrypted in 2A4h+20h bytes).

### Title metadata (tmd aka .tmd)
Title metadata exists as \"tmd\" file (as found on Nintendo\'s server), and as \".tmd\" file (as found in eMMC title folders), and it\'s also included in \".bin\" files (in files exported to SD cards):

```
+-------------------------------------------------------------------------------------+
|       Server:  "tmd"          unencrypted, 2312 bytes (208h+700h), tmd+certificate  |
|       Server:  "tmd.nn"       as above, OLDER tmd versions (nn=0,1,256,257,512,etc) |
|       eMMC:    "title.tmd"    unencrypted, 520 bytes  (208h+0),    tmd              |
|       SD Card: "GGGGGGGG.bin" encrypted, huge file, contains .app+tmd+sav files     |
+-------------------------------------------------------------------------------------+
```

Title metadata contains signatures and other useless stuff. One possibly useful feature is that it allows to define more than one \"content\" per title, however, that feature appears to be only used on Wii. DSi titles are usually having only one content (the \".app\" file).

```
+------------------------------------------------------------------------------------+
|       000h        4    Signature Type (00h,01h,00h,01h) (100h-byte RSA)            |
|       004h        100h Signature RSA-OpenPGP-SHA1 across 140h..207h                |
|       104h        3Ch  Signature padding/alignment (zerofilled)                    |
|       140h        40h  Signature Name "Root-CA00000001-CP00000007", 00h-padded     |
|       180h        1    TMD Version           (00h) (unlike 3DS)                    |
|       181h        1    ca_crl_version        (00h)                                 |
|       182h        1    signer_crl_version    (00h)                                 |
|       183h        1    Zero       (padding/align 4h)                               |
|       184h        8    System Version (0)                                          |
|       18Ch        8    Title ID       (00,03,00,17,"HNAP")             ;cart[230h] |
|       194h        4    Title Type     (0)                                          |
|       198h        2    Group ID       (eg. "01"=Nintendo)              ;cart[010h] |
|       19Ah        4    SD/MMC "public.sav" filesize in bytes  (0=none) ;cart[238h] |
|       19Eh        4    SD/MMC "private.sav" filesize in bytes (0=none) ;cart[23Ch] |
|       1A2h        4    Zero                                                        |
|       1A6h        1    Zero (3DS: SRL Flag)                                        |
|       1A7h        3    Zero                                                        |
|       1AAh        10h  Parental Control Age Ratings                    ;cart[2F0h] |
|       1BAh        1Eh  Zerofilled                                                  |
|       1D8h        4    Access rights (0)                                           |
|       1DCh        2    Title Version (vv,00) (LITTLE-ENDIAN!?) ;NEWEST ;cart[01Eh] |
|       1DEh        2    Number of contents (at 1E4h and up) (usually 00h,01h)       |
|       1E0h        2    boot content index (0)                                      |
|       1E2h        2    Zerofilled (padding/align 4h)                               |
|       1E4h+N*24h  4    Content ID    (00,00,00,vv) ;lowercase/hex ;"0000000vv.app" |
|       1E8h+N*24h  2    Content Index (00,00)                                       |
|       1EAh+N*24h  2    Content Type  (00,01)  ;aka DSi .app                        |
|       1ECh+N*24h  8    Content Size  (00,00,00,00,00,19,E4,00) ;NEWEST ;cart[210h] |
|       1F4h+N*24h  14h  Content SHA1  (on decrypted ".app" file);NEWEST             |
|       208h+..     700h Certificates (see below) (only in "tmd", not in ".tmd)      |
+------------------------------------------------------------------------------------+
```

The Launcher does verify the .tmd\'s RSA signature, and uses the Title/Content IDs to create the path/filename for the .app file. The Version, Size, SHA1 entries are not verified, so one could use any .tmd version with any .app version (when renaming the .app to match the .tmd\'s Content ID, but that\'d be a messy solution, and it\'s better to use the correct .tmd per .app).
Note: title.tmd is usually/always 208h bytes (one content), max permitted size is 49E4h (200h contents), a larger filesize can crash the firmware (used by Unlaunch.dsi exploit).

### Certificates (at end of \"cetk\" and \"tmd) (not in \".tik\" or \".tmd)

```
+-------------------------------------------------------------------------------------+
|       cert cetk tmd  siz  content                                                   |
|       000h 2A4h 208h 4    Signature Type (00h,01h,00h,01h)             ;\           
|       004h 2A8h 20Ch 100h Signature                                    ;            |
|       104h 3A8h 30Ch 3Ch  Signature padding/alignment (zerofilled)     ;            |
|       140h 3E4h 348h 40h  Signature Name "Root-CA00000001", 00h-padded ; 300h bytes |
|       180h 424h 388h 4    Key Type (00,00,00,01) (100h-byte RSA)       ;            |
|       184h 428h 38Ch 40h  Key Name "XS00000006", 00h-padded            ;            |
|       1C4h 468h 3CCh 4    Key Random/time/type/flags/chksum?           ;            |
|       1C8h 46Ch 3D0h 100h Key Public RSA Key                           ;            |
|       2C8h 56Ch 4D0h 4    Key Public RSA Exponent? (00,01,00,01)       ;            |
|       2CCh 570h 4D4h 34h  Key padding/alignment (zerofilled)           ;/           |
|       300h 5A4h 508h 4    Signature Type (00h,01h,00h,00h)             ;\           
|       304h 5A8h 50Ch 200h Signature                                    ;            |
|       504h 7A8h 70Ch 3Ch  Signature padding/alignment (zerofilled)     ;            |
|       540h 7E4h 748h 40h  Signature Name "Root" (padded with 00h)      ; 400h bytes |
|       580h 824h 788h 4    Key Type (00,00,00,01) (100h-byte RSA)       ;            |
|       584h 828h 78Ch 40h  Key Name "CA00000001", 00h-padded            ;            |
|       5C4h 868h 7CCh 4    Key Random/time/type/flags/chksum?           ;            |
|       5C8h 86Ch 7D0h 100h Key Public RSA Key                           ;            |
|       6C8h 86Ch 8D0h 4    Key Public RSA Exponent? (00,01,00,01)       ;            |
|       6CCh 970h 8D4h 34h  Key padding/alignment (zerofilled)           ;/           |
+-------------------------------------------------------------------------------------+
```

Note: Above certificates should be just a 1:1 copy of the entries in cert.sys.
Note: \"XS00000006\" or \"XS00000003\" is found in cetk/tik\'s, in tmd\'s it\'s called \"CP00000007\".

### Notes
The Title Version and Content Size/SHA1 entries are reflecting the NEWEST \".app\" version (but the AES-CBC key should usually/always also work for older versions).
The homebrew NUS Downloader utility is saving TMD (520 bytes; with REMOVED certificate) and CETK (2468 bytes; with included certificate).



