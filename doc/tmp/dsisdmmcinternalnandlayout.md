# DSi SD/MMC Internal NAND Layout


The DSi uses a 256MB Samsung eMMC moviNAND(?) flash chip, which is a NAND flash chip with a built-in controller that implements a MMC (SDIO?) interface. In many ways, it\'s like an SD card (or actually: MMC card) in BGA packaging, and some people have successfully read it with modified(why/how?) SD(/MMC?) card readers (is there any standard software that can be used for doing that?). The last 16MB is used for wear-leveling purposes (such as replacing bad blocks), while the first 240MB is used for storing actual data.

Addressing is done in terms of 512-bytes sectors. All wear-levelling and bad-block-mapping is handled transparently inside the chip by the controller. Most sectors are encrypted with a per-console key.

### Overall eMMC Layout

```
+-------------------------------------------------------------------------------------+
|       Offset     Size     Description                                               |
|       00000000h  200h     PC-style MBR, encrypted with a per-console key            |
|       00000200h  200h     Stage 2 Boot Info Block 1 (used)                          |
|       00000400h  200h     Stage 2 Boot Info Block 2 (unused, same as above)         |
|       00000600h  200h     Stage 2 Boot Info Block 3 (unused, nonsense NAND offsets) |
|       00000800h  26600h   Stage 2 ARM9 Bootcode (encrypted with universal key)      |
|       00026E00h  27600h   Stage 2 ARM7 Bootcode (encrypted with universal key)      |
|       0004E400h  400h     Stage 2 Footer -- unknown format, but first 10 bytes      |
|                             are (unencrypted) build number of Stage 2 bootloader    |
|       0004E800h  B1000h   Unused (all 00h)                                          |
|       000FF800h  200h     Unused (all 00h) (or No$gba Footer with CID & Console ID) |
|       000FFA00h  400h     Diagnostic area. (often contains build date of            |
|                             device in plaintext) Blank in never-before-booted       |
|                             DSi. Might be written to during firmware updates.       |
|       000FFE00h  200h     Unused (all FFh)                                          |
|       00100000h  EE00h    Unused (all 00h)                                          |
|       0010EE00h  CDF1200h 1st partition (205.9Mbyte) (main, encrypted, FAT16)       |
|       0CF00000h  9A00h    Unused (all 00h)                                          |
|       0CF09A00h  20B6600h 2nd partition (32.7Mbyte)  (photo, encrypted, FAT12)      |
|      For 240.0MB chips (Samsung KMAPF0000M-S998 or KLM5617EFW-B301):                |
|       0EFC0000h  BA00h    Unused (all 00h)                                          |
|       0EFCBA00h  34600h   3rd partition (0.2Mbyte)   (extra, unformatted)           |
|       0F000000h  -        End of 240MByte Address Space                             |
|      For 245.5MB chips (ST NAND02GAH0LZC5, both rev30 and rev31):                   |
|       0EFC0000h  B600h    Unused (all 00h?) (smaller unused area as in 240MB chip)  |
|       0EFCB600h  5B4A00h  3rd partition (5.7Mbyte)   (extra, unformatted)           |
|       0F580000h  -        End of 245.5MByte Address Space                           |
+-------------------------------------------------------------------------------------+
```


### Stage 2 Boot Info Blocks 1, 2, 3 (unencrypted, aside from the RSA block)

```
+-------------------------------------------------------------------------------------+
|       000h 20h Zerofilled                                                           |
|       020h 4   ARM9 Bootcode NAND Offset         (800h)      (Info Block 3: 80400h) |
|       024h 4   ARM9 Bootcode Size actual         (26410h)                           |
|       028h 4   ARM9 Bootcode RAM Address / Entry (37B8000h)                         |
|       02Ch 4   ARM9 Bootcode Size rounded-up     (26600h)                           |
|       030h 4   ARM7 Bootcode NAND Offset         (26E00h)    (Info Block 3: A6A00h) |
|       034h 4   ARM7 Bootcode Size actual         (27588h)                           |
|       038h 4   ARM7 Bootcode RAM Address / Entry (37B8000h)                         |
|       03Ch 4   ARM7 Bootcode Size rounded-up     (27600h)                           |
|       040h BFh Zerofilled                                                           |
|       0FFh 1   ARM Loadmode Flags               (0Ch)                               |
|       100h 80h RSA Block (B3,FF,EC,E5,..)       (Boot Info Block 3: 5B,E1,7A,9F,..) |
|       180h 14h Global MBK1..MBK5 Slot Settings                                      |
|       194h 0Ch Local MBK6..MBK8 Settings, WRAM Areas for ARM9                       |
|       1A0h 0Ch Local MBK6..MBK8 Settings, WRAM Areas for ARM7                       |
|       1ACh 4   Global MBK9 Setting, WRAM Slot Write Protect (FF000000h)             |
|       1B0h 50h Zerofilled                                                           |
+-------------------------------------------------------------------------------------+
```

The ARM Loadmode Flags are (usually 0Ch):

```
+-------------------------------------------------------------------------+
|       0    ARM9 Loadmode    (0=Normal to memory, 1=Special via bit3)    |
|       1    ARM7 Loadmode    (0=Normal to memory, 1=Special via bit3)    |
|       2    Unused, set      (usually 1)                                 |
|       3    Special Loadmode (0=LZSS to memory, 1=Transfer via IPC FIFO) |
|       4-7  Unused, cleared  (usually 0)                                 |
+-------------------------------------------------------------------------+
```

BUG: If bit3 is set, then parts of bootrom behaves as if both bit0 & bit1 are also set. Hmmm, but bit3 is actually set, so it\'s default behaviour\...?
The above RSA Block contains 74h bytes of information (plus 0Bh bytes padding):

```
+-------------------------------------------------------------------------------------+
|       Pre  0Bh  Leading RSA Padding (01,FF,FF,FF,FF,FF,FF,FF,FF,FF,00)              |
|       00h  10h  AES_Engine Key Y for ARM9/ARM7 Bootcode (EC,07,00,00,...)           |
|       10h  14h  SHA1 on WifiFlash[00h..27h] and eMMCBootInfo[00h..FFh,180h..1FFh]   |
|                 3DS: reportedly NAND/MBR[00h..27h] instead of WifiFlash[00h..27h]?? |
|       24h  14h  SHA1 on decrypted ARM9 Bootcode, with the actual binary size        |
|       38h  14h  SHA1 on decrypted ARM7 Bootcode, with the actual binary size        |
|       4Ch  14h  Zerofilled                                                          |
|       60h  14h  SHA1 on above 60h-byte area at [00h..5Fh] (63,D2,FC,6E,...)         |
+-------------------------------------------------------------------------------------+
```


### eMMC Encryption for Boot Sectors (AES-CTR, with fixed key; from RSA block)
The ARM9/ARM7 bootcode is encrypted via AES-CTR:

```
+-------------------------------------------------------------------------------------+
|       RSA_KEY  = F1,F5,1A,FF,...         ;-from 3DS TWL_FIRM (for RSA Block)        |
|       IV[0..3] = +size                   ;\                                         
|       IV[4..7] = -size                   ; size rounded up to 200h boundary, ie.    |
|       IV[8..B] = -size-1                 ; from Boot Info Block entries [02Ch,03Ch] |
|       IV[C..F] = 00000000h               ;/                                         |
|       KEY_X[0..F] = "Nintendo DS",...    ;-same as Key X for "Tad Files"            |
|       KEY_Y[0..F] = EC,07,00,00,...      ;-from RSA Block (see above)               |
+-------------------------------------------------------------------------------------+
```

The RSA_KEY key is stored in some non-dumpable area of the DSi BIOS, making it impossible to obtain that key without chip decapping. However, Nintendo has included the same RSA_KEY in the \"TWL_FIRM\" firmware update for 3DS.

### eMMC Encryption for MBR/Partitions (AES-CTR, with console-specific key)
The MBR and both partitions are encrypted via AES-CTR:

```
+-------------------------------------------------------------------------------------+
|       IV[0..F]:    SHA1(CID)+Address/10h                    ;-eMMC Chip ID          |
|       KEY_X[0..3]: [4004D00h]                               ;\                      
|       KEY_X[4..7]: [4004D00h] XOR 24EE6906h                 ; CPU/Console ID, for   |
|       KEY_X[8..B]: [4004D04h] XOR E65B601Dh                 ; DSi partitions on DSi |
|       KEY_X[C..F]: [4004D04h]                               ;/                      |
|       KEY_X[0..3]: [4004D00h]                               ;\CPU/Console ID, for   
|       KEY_X[4..B]: "NINTENDO"                               ; DSi partitions on 3DS |
|       KEY_X[C..F]: [4004D04h]                               ;/                      |
|       KEY_Y[0..F]: 0AB9DC76h,BD4DC4D3h,202DDD1Dh,E1A00005h  ;-Constant              |
+-------------------------------------------------------------------------------------+
```

The CID value (eMMC Chip ID) should be in same format as stored in RAM at 2FFD7BCh: little-endian 120bit (without crc7), padded to 128bit (with MSB=00h), ie. it should look like this (dd/ss being date/serial numbers):

```
+--------------------------------------------------------------------------+
|       CID = [2FFD7BCh] = dd,ss,ss,ss,ss,03,4D,30,30,46,50,41,00,00,15,00 |
|       SHA1(CID) = SWI_27h(SHA1value,2FFD7BCh,10h)                        |
+--------------------------------------------------------------------------+
```

The resulting SHA1value is 14h-bytes, the first 10h-bytes are used as IV value, whereas the DSi doesn\'t adjust the endianness (it does just use the SWI\'s \"big-endian\" SHA1value as \"little-endian\" AES/IV value).
The CTR gets incremented after each 10h bytes (ie. to access a random address: \"IV=SHA1value+(address/10h)\".
For more info on obtaining the CID and Port \[4004D00h\] values, see:
- [DSi Console IDs](./dsiconsoleids.md)
See also:
- [DSi SD/MMC Images](./dsisdmmcimages.md)

### Related Decryption Tools

```
+----------------------------------------------------------------------------------+
|       "NUS Downloader" allows to download and decrypt system updates             |
|       "DSi SRL Extract" allows to decrypt DSiware files (when copied to SD card) |
|       "TWLTool" decrypt/encrypt eMMC images (firmware downgrading, dsiware-hax)  |
|       "TWLbf" and "bfCL" bruteforce Console ID or CID (or both) from eMMC images |
+----------------------------------------------------------------------------------+
```




