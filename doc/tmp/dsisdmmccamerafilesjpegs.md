# DSi SD/MMC Camera Files - JPEG\'s


### Overall JPEG Format (big-endian)

```
+------------------------------------------------------------------------------------+
|       Offs   ID    Len   Data                                                      |
|       0000h  FFD8h                                      ;(start of image)    ;SOI  |
|       0002h  FFE1h,10C4h,"Exif",00h,00h,<Exif Body>     ;(extra "Exif" data) ;APP1 |
|       10C8h  FFC0h,0011h,08h,01E0h,0280h,03h,012100h,021101h,031101h         ;SOF0 |
|       10DBh  FFDBh,0084h, 00 06 04 05 06 05 04 06 06 05 06 07 07 .. 28 28 28 ;DQT  |
|       1161h  FFC4h,01A2h, 00 00 01 05 01 01 01 .. .. F8 F9 FA                ;DHT  |
|       1305h  FFDAh,000Ch,03h,010002h,110311h,003F00h    ;(start of scan)     ;SOS  |
|       1313h  E6 76 F4 DD 4F 0A 3B 60 0F 4C D7 9E 9A 93 3D 4B EE 98 B8 .. ..        |
|       AB4Fh  FFD9h                                      ;(end of image)      ;EOI  |
+------------------------------------------------------------------------------------+
```


### Exif Body for Nintendo DSi Photos
The Exif data consists of several headers/footers and data blocks, mixed with several \"IFD\" tables.

```
+-------------------------------------------------------------------------------+
|       Offs  Siz  ExID  Type  Length    Offset    ;<-- Format for "IFD" Tables |
|       0000h 4    "MM",002Ah                      ;Big-Endian (aka Motorola)   |
|       0004h 4    00000008h                       ;first IFD offset (IFD0)     |
+-------------------------------------------------------------------------------+
```

IFD0 (Main Image):

```
+---------------------------------------------------------------------------------+
|       0008h 2    0009h                           ;number of IFD0 entries        |
|       000Ah 12   010Fh,0002h,00000009h,0000007Ah ;Maker ("Nintendo",0)          |
|       0016h 12   0110h,0002h,0000000Bh,00000084h ;Model ("NintendoDS",0)        |
|       0022h 12   011Ah,0005h,00000001h,00000090h ;Resolution X (72 dpi)         |
|       002Eh 12   011Bh,0005h,00000001h,00000098h ;Resolution Y (72 dpi)         |
|       003Ah 12   0128h,0003h,00000001h,00020000h ;Resolution Unit (2=Inches)    |
|       0046h 12   0131h,0002h,00000005h,000000A0h ;Firmware (Gamecode backwards) |
|       0052h 12   0132h,0002h,00000014h,000000A6h ;Date/Time Modified            |
|       005Eh 12   0213h,0003h,00000001h,00020000h ;Subsampling (2=datum point)   |
|       006Ah 12   8769h,0004h,00000001h,000000BAh ;Exif SubIFD offset            |
|       0076h 4    000001DEh                       ;next IFD offset (IFD1)        |
|       007Ah 9+1  "Nintendo",00h,00h              ;Maker ("Nintendo",0,0)        |
|       0084h 11+1 "NintendoDS",00h,00h            ;Model ("NintendoDS",0,0)      |
|       0090h      00000048h,00000001h             ;Resolution X (72 dpi)         |
|       0098h      00000048h,00000001h             ;Resolution Y (72 dpi)         |
|       00A0h 5+1  "PINH",00h,00h   ;aka HNIP      ;Firmware (Gamecode backwards) |
|       00A6h 20   "YYYY:MM:DD HH:MM:SS",00h       ;Date/Time Modified            |
+---------------------------------------------------------------------------------+
```

Sub IFD:

```
+---------------------------------------------------------------------------------+
|       00BAh 2    000Ah                           ;number of Sub IFD entries     |
|       00BCh 12   9000h,0007h,00000004h,30323230h ;Exif Version ("0220")         |
|       00C8h 12   9003h,0002h,00000014h,00000138h ;Date/Time Original            |
|       00D4h 12   9004h,0002h,00000014h,0000014Ch ;Date/Time Digitized           |
|       00E0h 12   9101h,0007h,00000004h,01020300h ;Components (Y,Cb,Cr)          |
|       00ECh 12   927Ch,0007h,00000042h,00000160h ;Maker dependent internal data |
|       00F8h 12   A000h,0007h,00000004h,30313030h ;Flashpix Version ("0100")     |
|       0104h 12   A001h,0003h,00000001h,00010000h ;Color Space (1=Normal=sRGB)   |
|       0110h 12   A002h,0004h,00000001h,00000280h ;Pixel Dimension X (640)       |
|       011Ch 12   A003h,0004h,00000001h,000001E0h ;Pixel Dimension Y (480)       |
|       0128h 12   A005h,0004h,00000001h,000001A2h ;Interoperability IFD (R98)    |
|       0134h 4    00000000h                       ;next IFD offset (none)        |
|       0138h 20   "YYYY:MM:DD HH:MM:SS",00h       ;Date/Time Original            |
|       014Ch 20   "YYYY:MM:DD HH:MM:SS",00h       ;Date/Time Digitized           |
+---------------------------------------------------------------------------------+
```

Maker dependent IFD (DSi specific):

```
+-----------------------------------------------------------------------------------+
|       0160h 2    0002h                           ;number of IFD entries           |
|       0162h 12   1000h,0007h,0000001Ch,0000017Eh ;DSi Signature (IV+MAC)          |
|       016Eh 12   1001h,0007h,00000008h,0000019Ah ;DSi Whatever Zero (Frame info?) |
|       017Ah 4    00000000h                       ;next IFD offset (none)          |
|       017Eh 12   2E AB A5 D1 FD A8 .. ..         ;DSi Signature (IV)  ;\          
|       018Ah 16   xx xx xx xx xx xx .. ..         ;DSi Signature (MAC) ;/          |
|       019Ah 8    0000000000000000h               ;<-- different for Frames        |
+-----------------------------------------------------------------------------------+
```

Interoperability IFD (R98) (some common/useless stuff for JPEGs):

```
+-----------------------------------------------------------------------------------+
|       01A2h 2    0003h                           ;number of IFD entries           |
|       01A4h 12   0001h,0002h,00000004h,52393800h ;Stipulated File ("R98",0)       |
|       01B0h 12   0002h,0007h,00000004h,30313030h ;Whatever ("0100")               |
|       01BCh 12   1000h,0002h,00000012h,000001CCh ;Whatever (JPEG Exif Ver 2.2",0) |
|       01C8h 4    00000000h                       ;next IFD offset (none)          |
|       01CCh 18   "JPEG Exif Ver 2.2",00h         ;Whatever (JPEG Exif Ver 2.2",0) |
+-----------------------------------------------------------------------------------+
```

IFD1 (Thumbnail Image):

```
+------------------------------------------------------------------------------+
|       01DEh 2    0006h                           ;number of IFD1 entries     |
|       01E0h 12   0103h,0003h,00000001h,00060000h ;Compression (1=JPEG)       |
|       01ECh 12   011Ah,0005h,00000001h,0000022Ch ;Resolution X (72 dpi)      |
|       01F8h 12   011Bh,0005h,00000001h,00000234h ;Resolution Y (72 dpi)      |
|       0204h 12   0128h,0003h,00000001h,00020000h ;Resolution Unit (2=Inches) |
|       0210h 12   0201h,0004h,00000001h,0000023Ch ;Jpeg Offset                |
|       021Ch 12   0202h,0004h,00000001h,00000xxxh ;Jpeg Size (eg. E80h)       |
|       0228h 4    00000000h                       ;next IFD offset (none)     |
|       022Ch 8    00000048h,00000001h             ;Resolution X (72 dpi)      |
|       0234h 8    00000048h,00000001h             ;Resolution Y (72 dpi)      |
+------------------------------------------------------------------------------+
```

Thumbnail Data (160x120pix, in JPEG Format):

```
+------------------------------------------------------------------------------------+
|       023Ch 2    FFD8h                           ;(start of thumbnail/image) ;SOI  |
|       023Eh 13h  FFC0h,0011h,08h,0078h,00A0h,03h,012100h,021101h,031101h     ;SOF0 |
|       0251h 86h  FFDBh,0084h, 00 0A 07 07 08 07 .. ..                        ;DQT  |
|       02D7h 1A4h FFC4h,01A2h, 00 00 01 05 01 .. .. F8 F9 FA                  ;DHT  |
|       047Bh 0Eh  FFDAh,000Ch,03h,010002h,110311h,003F00h   ;(start of scan)  ;SOS  |
|       0489h ...  CC 55 14 F0 3D 2B 8B 4B 9D C2 E3 BD 18 A5 B0 09 B6 .. ..          |
|       10xxh 2    FFD9h                           ;(end of thumbnail/image)   ;EOI  |
+------------------------------------------------------------------------------------+
```

The above european gamecode entry differs for other regions. Above offsets are usually as so for DSi jpeg\'s, but they might change if Nintendo adds/removes some entries, or changes size of some entries (for example, the Model string is said to be different for 3DS, and \"Frames\" are including a bigger entry, as described below).

### DSi Signature (IV+MAC)
The 1Ch-byte Signature is split into a 0Ch-byte IV value (this might be just a random number?), and a 10h-byte MAC value. The MAC is computed via AES-CCM:

```
+------------------------------------------------------------------------------------+
|       IV[00h..0Bh]  = First 0Ch-bytes of signature                                 |
|       KEY[00h..0Fh] = Constant (70,88,52,06,...)   ;from BIOS ROM                  |
|       Zerofill the 1Ch-byte signature area in the JPEG file                        |
|       Probably zeropad(?) the JPEG file (if filesize isn't a multiple of 16 bytes) |
|       Pass the whole JPEG as "extra associated data" to the AES-CCM hardware       |
|       Copy the IV value and computed MAC value back to the JPEG's signature area   |
+------------------------------------------------------------------------------------+
```

Unknown if the IV value is just random, and unknown if there are further requirements (such like using same Maker/Model strings or same resolution as in original DSi files).
Locating \"ldr rx,=927Ch\" opcodes at various locations in Nintendo DSi Camera is easy; but the stuff is handled via numerous sub-functions, including IPC stuff with both ARM7 and ARM9 envolved; which isn\'t too easy to disassemble.

### Exif Body for Nintendo DSi Frames
Frames are using same format above, but with the 8-byte zero entry at \[019Ah\] replaced by a bigger 8FCh-byte entry (accordingly, the size in IFD entry \[016Eh\] is also adjusted, and offsets for entries \[01A2h..10xxh\] are moved up).
The actual change is that 0000000000000000h is changed from 8 byte size to 8FCh-byte size, containing 0000000000000001h, followed by 8F4h extra bytes (with unknown content; maybe the frame mask for transparent pixels; the data doesn\'t really look like a mask though, unless it\'s compressed, but then the fixed size would be strange).

### IFD Type Values (and Length/Offset)

```
+---------------------------------------------------------------------------------+
|       0001h = 8bit Unsigned                                                     |
|       0002h = 7bit ASCII                                                        |
|       0003h = 16bit Unsigned                                                    |
|       0004h = 32bit Unsigned                                                    |
|       0005h = 64bit Unsigned Rational (32bit numerator, plus 32bit denominator) |
|       0006h = Reserved                                                          |
|       0007h = 8bit General Purpose                                              |
|       0009h = 32bit Signed                                                      |
|       000Ah = 64bit Signed Rational (32bit numerator, plus 32bit denominator)   |
|       000Bh..FFFFh = Reserved                                                   |
+---------------------------------------------------------------------------------+
```

The \"Length\" value indicates the number of type units, eg. type=16bit, length=3 would mean 6 bytes. If the information fits into 4 bytes then it\'s stored directly in the 4-byte \"Offset\" field, otherwise \"Offset\" is a pointer to the actual information.



