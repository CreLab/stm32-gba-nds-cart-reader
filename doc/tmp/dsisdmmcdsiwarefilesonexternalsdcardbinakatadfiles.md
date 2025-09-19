# DSi SD/MMC DSiware Files on External SD Card (.bin aka Tad Files)


The DSi can export applications from NAND to SD (via System Settings \--\> Data Managment). The \".bin\" files created on SD are using the \"Tad file structure\", and alongsides, there\'s a \"HNB\_.lst\" file containing a list of game codes.

### SD:\\private\\ds\\title\\HNB\_.lst (list of gamecodes) (1208 bytes)

```
+-------------------------------------------------------------------------------------+
|       000h 1200  List of 300 gamecodes, spelled backwards (or zero = unused entry)  |
|       4B0h 1     Language (0=Jap, 1=Eng, 2=Fre, 3=Ger, 4=Ita, 5=Spa, 6=Chi, 7=Kor?) |
|       4B1h 3     Zero                                                               |
|       4B4h 2     CRC16 on entries [000h..4B3h] (with initial value FFFFh)           |
|       4B6h 2     Zero                                                               |
+-------------------------------------------------------------------------------------+
```

For example, \"VUGK\" in HNB\_.lst would indicate gamecode KGUV aka \"Flipnote Studio\" for EUR/AUS regions. And the corresponding SD Card file would be \"SD:\\private\\ds\\title\\4B475556.bin\" (with the 4-letter gamecode encoded as 8-digit uppercase HEX number). The full 16-digit on eMMC storage would be \"00030004\\4b475556\" (in lowercase, and with the \"00030004\" implied for the DSiWare folder; files from system folders cannot be exported to SD Card).
The Language byte reflects the System Settings\'s language selection at time when the HNB\_.lst was created or modified (unknown why that info is stored in the file).

### SD:\\private\\ds\\title\\4GGGGGGG.bin (encrypted executable/data in one file)

```
+------------------------------------------------------------------------------------+
|       Offset   Size       Key  Description                                         |
|       000000h  4000h+20h  FIX  Icon/Title                                          |
|       004020h  B4h+20h    FIX  Header                                              |
|       0040F4h  440h+20h   FIX  Cert (certificates/hashes)                          |
|       004554h  208h+20h   VAR  title.tmd (usually 208h bytes; but could be bigger) |
|       00477Ch  size+N*20h VAR  000000vv.app                                        |
|       ...      0          ?    seven N/A parts (unknown if/when they are used)     |
|       ...      size+N*20h FIX  public.sav  (if any)                                |
|       ...      ?          ?    banner.sav  (if any)                                |
+------------------------------------------------------------------------------------+
```

ES Block Encryption is used to encrypt the header block, cert block, and the 11 content parts. Each are their own seperate ES blocks.
- [DSi ES Block Encryption](./dsiesblockencryption.md)
Some of the above blocks use fixed keys (FIX):

```
+-----------------------------------------------------------------------------------+
|       KEY_X[00h..0Fh] = Constant ("Nintendo DS",...)                              |
|       KEY_Y[00h..0Fh] = Constant (66,82,32,04,...)  ;from ARM7BIOS                |
|       since above X/Y are constant, that gives a fixed normal key:                |
|       KEY[00h..0Fh]   = Constant (3D,A3,EA,33,...)  ;as used in "dsi srl extract" |
+-----------------------------------------------------------------------------------+
```

Other blocks use variable per-console keys (VAR):

```
+----------------------------------------------------------------------------------+
|       KEY_X[00h..03h] = 4E00004Ah                           ;\                   
|       KEY_X[04h..07h] = 4A00004Eh                           ; same as for dev.kp |
|       KEY_X[08h..0Bh] = Port[4004D00h+4] xor C80C4B72h      ;                    |
|       KEY_X[0Ch..0Fh] = Port[4004D00h+0]                    ;/                   |
|       KEY_Y[00h..0Fh] = Constant (CC,FC,A7,03,...)  ;from ARM7BIOS               |
+----------------------------------------------------------------------------------+
```

Without knowing the console-specifc Port\[4004D00h\] value, the data could be decrypted only by the DSi console that has originally exported the file to SD card.
However, Nintendo has somehow (maybe accidently) managed to store the Port\[4004D00h\] value as 16-digit ASCII string in the \"TW cert\"; which can be decrypted right from the SD card file (as done by the homebrew \"dsi srl extract\" utility).

### Decrypted Icon/Title (at 0000h, size 4000h)

```
+-----------------------------------------------------------------------------+
|       0000h 23C0h  Icon/Title (usually 23C0h bytes) ;see carthdr[068h,208h] |
|       23C0h 1C40h  Zerofilled (padding to get 4000h byte size)              |
+-----------------------------------------------------------------------------+
```


### Decrypted Header block (at 4020h, size B4h)

```
+-------------------------------------------------------------------------------------+
|       000h  4      Fixed ID "4ANT" (aka TNA4, spelled backwards)                    |
|       004h  2      Maker Code, spelled backwards ("10"=Nintendo) ;carthdr[010h]     |
|       006h  1      Zero                                                             |
|       007h  1      Title version (vv)                            ;carthdr[01Eh]     |
|       008h  6      DSi MAC Address, spelled backwards            ;wifi_flash[036h]  |
|       00Eh  2      Zero                                                             |
|       010h  16     Some console ID from HWINFO_N.dat             ;datfile[8Ch..9Bh] |
|       020h  8      Title ID (gg gg gg gg 04 00 03 00)            ;carthdr[230h]     |
|       028h  4      Size of title.tmd    (usually 208h+20h)                          |
|       02Ch  4      Size of 000000vv.app (size+N*20h)             ;carthdr[210h]     |
|       030h  4*7    Size of seven N/A parts (0)                                      |
|       04Ch  4      Size of public.sav   (size+N*20h)             ;carthdr[238h]     |
|       050h  4      Size of banner.sav?  (usually 0)       ;carthdr[1BFh].bit2=1     |
|       054h  4*8    List of eight Content IDs in same order as title.tmd             |
|       074h  3Eh    Reserved section per tmds, uh? (mostly zero, plus garbage?)      |
|       0B2h  2      Unknown (zero)                                                   |
+-------------------------------------------------------------------------------------+
```


### Decrypted Cert block (at 40F4h, size 460h)

```
+------------------------------------------------------------------------------+
|       000h  20     SHA1 of Icon/Title                                        |
|       014h  20     SHA1 of TNA4                                              |
|       028h  20     SHA1 of title.tmd                                         |
|       03Ch  20     SHA1 of 000000vv.app                                      |
|       040h  20*7   SHA1 of seven N/A parts (unused, can be whatever garbage) |
|       0DCh  20     SHA1 of public.sav                                        |
|       0F0h  20     SHA1 of banner.sav                                        |
|       104h  3Ch    ECC signature of [000h..103h] with AP cert                |
|       140h  180h   AP cert, signed by TW cert                                |
|       2C0h  180h   TW cert, specific to a console (see dev.kp)               |
+------------------------------------------------------------------------------+
```

More in depth, the above two cert\'s look as so:

```
+-------------------------------------------------------------------------------------+
|       140h 4    Signature Type (00,01,00,02) (ECC, sect233r1, non-RSA)  ;\          
|       144h 3Ch  Signature Hex numbers... across... below?               ; AP cert   |
|       180h 40h  Signature padding/alignment (zerofilled)                ; 180h-byte |
|       1C0h 40h  Signature Name "Root-CA..-MS..-TW..-08..", 00h-padded   ;           |
|                 "Root-CA00000001-MS00000008-TWxxxxxxxx-08nnnnnnnnnnn1nn";           |
|       200h 4    Key Type (00,00,00,02)       (ECC, sect233r1, non-RSA)  ;           |
|       204h 40h  Key Name "AP00030015484e42gg", 00h-padded ;sys.settings ;           |
|       244h 4    Key Random/time/type/flags/chksum?   ;<-- ZERO here     ;           |
|       248h 3Ch  Key Public ECC Key (point X,Y) (random/per game?)       ;           |
|       284h 3Ch  Key padding/alignment (zerofilled)                      ;/          |
|       2C0h 4    Signature Type (00,01,00,02) (ECC, sect233r1, non-RSA)  ;\          
|       2C4h 3Ch  Signature Hex numbers... across... below?               ; TW cert   |
|       300h 40h  Signature padding/alignment (zerofilled)                ; 180h-byte |
|       340h 40h  Signature Name "Root-CA00000001-MS00000008", 00h-padded ; (same as  |
|       380h 4    Key Type (00,00,00,02)       (ECC, sect233r1, non-RSA)  ; dev.kp,   |
|       384h 40h  Key Name "TWxxxxxxxx-08nnnnnnnnnnn1nn", 00h-padded      ; excluding |
|       3C4h 4    Key Random/time/type/flags/chksum?                      ; private   |
|       3C8h 3Ch  Key Public ECC Key (point X,Y)                          ; key)      |
|       404h 3Ch  Key padding/alignment (zerofilled)                      ;/          |
+-------------------------------------------------------------------------------------+
```


Much like the Wii, the DSi carries with it a private ECC key that it can use to sign things, and a certificate signed by Nintendo that attests to the fact that the public ECC key belongs to a genuine DSi.



