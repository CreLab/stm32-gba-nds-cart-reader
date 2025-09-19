# DSi SD/MMC Flipnote Files


### FAT16:\\title\\00030004\\4b4755gg\\data\\public.sav
This .sav file contains a FAT12 filesystem with following files:

```
+----------------------------------------------------------------------------------+
|       Flipnote(public.sav):\eula.txt     ;128 Kbytes, 20000h - zerofilled        
|       Flipnote(public.sav):\option.bin   ;256 bytes, 100h    - options           
|       Flipnote(public.sav):\mark0.pls    ;8000 bytes, 1F40h  - Heart sticker     
|       Flipnote(public.sav):\mark1.pls    ;8000 bytes, 1F40h  - Crown sticker     
|       Flipnote(public.sav):\mark2.pls    ;8000 bytes, 1F40h  - Music sticker     
|       Flipnote(public.sav):\mark3.pls    ;8000 bytes, 1F40h  - Skull sticker     
|       Flipnote(public.sav):\recent10.pls ;4000 bytes, FA0h   - Recently saved    
|       Flipnote(public.sav):\friend.pls   ;28800 bytes, 7080h - F7,A0,CD,zeroes.. 
|       Flipnote(public.sav):\remind.pls   ;10240 bytes, 2800h - F7,A0,CD,zeroes.. 
|       Flipnote(public.sav):\latest1.pls  ;256 bytes, 100h    - xxxxxxxx,zeroes.. 
|       Flipnote(public.sav):\nand.pls     ;160000 bytes, 27100h - All files       
|       Flipnote(public.sav):\ugo\0NN\XNNNNN_NNNNNNNNNNNNN_NNN.ppm - flipnotes     
+----------------------------------------------------------------------------------+
```


### Flipnote(public.sav):\\option.bin (256 bytes, 100h)

```
+-----------------------------------------------------------------------+
|       0000h 1   Unknown (02h)        (?)                              |
|       0001h 1   Stylus               (00h=Right Hand, 01h=Left Hand)  |
|       0002h 1   Sound Effects        (00h=On, 01h=Off)                |
|       0003h 1   Unknown (01h)        (?)                              |
|       0004h 1   Unknown (00h)        (?)                              |
|       0005h 1   Unknown (01h)        (?)                              |
|       0006h 1   Unknown (01h)        (?)                              |
|       0007h 1   Unknown (03h)        (?)                              |
|       0008h 1   Unknown (02h)        (?)                              |
|       0009h 1   Unknown (01h)        (?)                              |
|       000Ah 1   Unknown (00h)        (?)                              |
|       000Bh 1   Unknown (01h)        (?)                              |
|       000Ch 1   Advanced Tools       (00h=Off, 01h=On)                |
|       000Dh 1   Pages to Trace       (01h..04h=1..4)                  |
|       000Eh 1   Frog Display         (01h=Off, 01h=On)                |
|       000Fh 1   Start on Calendar    (00h=Off, 01h=On)                |
|       0010h 8   Flipnote Studio ID   (64bit User ID) (fixed)          |
|       0018h 2   Checksum             (see below)                      |
|       001Ah 2   Date of Birth, Year  (076Ch..0840h=1900..2112)        |
|       001Bh 1   Date of Birth, Month (01h..0Ch=1..12)                 |
|       001Ch 1   Date of Birth, Day   (01h..1Fh=1..31)                 |
|       001Eh E2h Unknown/unused       (zerofilled)                     |
+-----------------------------------------------------------------------+
```

Checksum is computed as \"chk=0000h, halfword\[18h\]=0000h, for i=0 to FFh, chk=chk+(byte\[i\] xor i), next i, halfword\[18h\]=chk\".

### SD:\\private\\ds\\app\\4B4755GG\\mark0.pls (Heart sticker), 8000 bytes (1F40h)
### SD:\\private\\ds\\app\\4B4755GG\\mark1.pls (Crown sticker), 8000 bytes (1F40h)
### SD:\\private\\ds\\app\\4B4755GG\\mark2.pls (Music sticker), 8000 bytes (1F40h)
### SD:\\private\\ds\\app\\4B4755GG\\mark3.pls (Skull sticker), 8000 bytes (1F40h)
### SD:\\private\\ds\\app\\4B4755GG\\recent10.pls (Recently saved), 4000 bytes (FA0h)
Recently saved files list, and four files with flipnotes that have \"stickers\" assigned to them (which can be done when clicking \"Details\" in the flipnote file menu).

```
+----------------------------------------------------------------------------------+
|       0000h   N*3Fh       List of filenames (if any)               ;\encrypted   
|       N*3Fh+0 1           End of filename list (00h)               ;/            |
|       N*3Fh+1 2           Crippled MD5 checksum bytes [6,8]        ;\unencrypted 
|       N*3Fh+3 SIZ-N*3Fh-3 Padding to end of file (zerofilled)      ;/            |
+----------------------------------------------------------------------------------+
```

The filenames are formatted as so (consisting of device, path, and name):

```
+----------------------------------------------------------------------------+
|       "sdmc:/private/ds/app/4B4755GG/001/XNNNNN_NNNNNNNNNNNNN_NNN.ppm",0Ah |
+----------------------------------------------------------------------------+
```

The files are encrypted using a fixed XOR pattern (repeated every 40h bytes):

```
+-----------------------------------------------------------------------+
|       F7h,4Ch,6Ah,3Ah,FBh,82h,A6h,37h,6Eh,11h,38h,CFh,A0h,DDh,85h,C0h |
|       C7h,9Bh,C4h,D8h,DDh,28h,8Ah,87h,53h,20h,EEh,E0h,0Bh,EBh,43h,A0h |
|       DBh,55h,0Fh,75h,36h,37h,EBh,35h,6Ah,34h,7Fh,B5h,0Fh,99h,F7h,EFh |
|       43h,25h,CEh,A0h,29h,46h,D9h,D4h,4Dh,BBh,04h,66h,68h,08h,F1h,F8h |
+-----------------------------------------------------------------------+
```

The checksum is derived by computing the MD5 checksum across the data bytes (in unencrypted form), and then crippling the 16-byte MD5 value to 2 bytes.
For example, an empty file contains only three bytes: F7h,A0h,CDh (plus zero padding).

### SD:\\private\\ds\\app\\4B4755GG\\001\\dirmemo2.lst (files), 160000 bytes (27100h)

```
+----------------------------------------------------------------------------------+
|       0000h   N*1Dh       List of filenames (if any)               ;\encrypted   
|       N*1Dh+0 1           End of filename list (00h)               ;/            |
|       N*1Dh+1 2           MD5 checksum bytes [6,8]                 ;\unencrypted 
|       N*1Dh+3 SIZ-N*1Dh-3 Padding to end of file (zerofilled)      ;/            |
+----------------------------------------------------------------------------------+
```

The filenames are formatted as so (raw names, without path):

```
+-----------------------------------------------------------------------+
|       "XNNNNN_NNNNNNNNNNNNN_NNN.ppm",0Ah                              |
+-----------------------------------------------------------------------+
```

Checksum and encryption is same as for the \".pls\" files, however, the \".lst\" file contains only raw filenames (without path\'s).

### SD:\\private\\ds\\app\\4B4755GG\\gif\\XNNNNN_NNNNNNNNNNNNN_NNN.gif
Flipnotes exported to GIF format. Supported are animated GIFs, and separate GIFs for each frame. There appears to be no way to view GIFs, or to convert them back to PPM format.

### SD:\\private\\ds\\app\\4B4755GG\\001\\XNNNNN_NNNNNNNNNNNNN_NNN.ppm ;normal
### SD:\\private\\ds\\app\\4B4755GG\\YYYYMMDD\\NNN\\XNNNNN_NNNNNNNNNNNNN_NNN.ppm ;backup
Flipnotes animation files.

```
+-------------------------------------------------------------------------------------+
|       0000h  4       File ID ("PARA")                                               |
|       0004h  4       Size of Animation Data (vid)                                   |
|       0008h  4       Size of Audio Data     (aud) (0=none)                          |
|       000Ch  2       Number of Frames minus 1    (NF-1)                             |
|       000Eh  2       Unknown (always 24h,00h)                                       |
|       0010h  2       Lock Flag (0=Open, 1=Locked, prevent editing)                  |
|       0012h  2       Preview frame number                                           |
|       0014h  22      Nickname of Original Author (UCS-2)  ;\max 10 characters       
|       002Ah  22      Nickname of Last Editor     (UCS-2)  ; (plus ending zero)      |
|       0040h  22      Nickname of User (?)        (UCS-2)  ;/                        |
|       0056h  8       User ID of Original Author  (Flipnote Studio ID)               |
|       005Eh  8       User ID of Last Editor      (Flipnote Studio ID)               |
|       0066h  18      Filename of Original File   (3xHEX, 13xASCII, 2xVER)           |
|       0078h  18      Filename of Current File    (3xHEX, 13xASCII, 2xVER)           |
|       008Ah  8       User ID of Previous Editor  (Flipnote Studio ID)               |
|       0092h  8       Filename Fragment           (3xHEX, 5xHEX)                     |
|       009Ah  4       Time/Date (seconds since 1st Jan 2000)                         |
|       009Eh  2       Zerofilled                                                     |
|       00A0h  600h    Preview Bitmap (8x6 tiles, aka 64x48 pixels, 4bpp)             |
|       06A0h  2       Size of Animation Table (4*NF)                                 |
|       06A2h  4       Zerofilled                                                     |
|       06A6h  2       Flags (bit0=Can be set?, bit1=Loop/Repeat, bit6=Set?)          |
|       06A8h  4*NF    Animation Table (offsets in Animation Data for each frame)     |
|       ...    (vid)   Animation Data Frame(s)                                        |
|       ...    1*NF    Audio Flags for each Frame (bit0-2: Effect 1-3, bit3-7: Zero)  |
|       ...    ..      Padding (0..3 bytes zerofilled, for alignment of next entry)   |
|       ...    4       Size of Background music in bytes (0=not used/empty)           |
|       ...    4       Size of Sound effect #1 in bytes (0=not used/empty, max 2000h) |
|       ...    4       Size of Sound effect #2 in bytes (0=not used/empty, max 2000h) |
|       ...    4       Size of Sound effect #3 in bytes (0=not used/empty, max 2000h) |
|       ...    1       Framespeed for playback          (1..8) aka "8 minus N"        |
|       ...    1       Framespeed when BGM was recorded (1..8) aka "8-decimal"        |
|       ...    14      Zerofilled                                                     |
|       ...    (aud)   Audio Data (BGM, followed by Effects 1, 2, 3) (if any)         |
|       ...    80h     RSA-OpenPGP-SHA1 across all preceeding bytes                   |
|       ...    10h     Zerofilled                                                     |
+-------------------------------------------------------------------------------------+
```

The RSA signature is in OpenPGP SHA1 format (as used by SWI 23h, however Flipnote is using it\'s own RSA functions instead of the BIOS SWIs). The RSA public/private keys are contained in the Flipnote executable (in the modcrypted area).

### Animation Data Frame(s)

```
+----------------------------------------------------------------------------+
|       Start  Length  Description                                           |
|       0000h  1       Pen and Paper information                             |
|       0001h  48      Layer 1 Line Encoding (48 bytes = 2bit per 192 lines) |
|       0031h  48      Layer 2 Line Encoding (48 bytes = 2bit per 192 lines) |
|       0061h  ...     Frame Data for Layer 1                                |
|       ...    ...     Frame Data for Layer 2                                |
+----------------------------------------------------------------------------+
```

The pen and paper byte at the start is encoded as follows:

```
+-------------------------------------------------------------------------+
|       0    Paper     (0=Black, 1=White)                                 |
|       1-2  Layer 1   (0=None, 1=Inverse of Paper, 2=Red, 3=Blue)        |
|       3-4  Layer 2   (0=None, 1=Inverse of Paper, 2=Red, 3=Blue)        |
|       5-6  Unknown                                                      |
|       7    New Frame (0=Change between last frame, 1=Totally new frame) |
+-------------------------------------------------------------------------+
```

The Line Encoding contains 2bit values for all 192 scanlines (starting with bit0-1 of the first byte; for the top-most(?) scanline). The meaning of the 2bit values is:

```
+----------------------------------------------------------------------------+
|       0 = Skip Line    (0 bytes)   (0 pixels)                              |
|       1 = Packed Line  (4+N bytes) (32bit flags, plus Nx8 pixels)          |
|       2 = Inverse Line (4+N bytes) (32bit flags, plus Nx8 inverted pixels) |
|       3 = Raw Line     (32 bytes)  (256 pixels)                            |
+----------------------------------------------------------------------------+
```

The packed lines contain a 32bit header (with flags for each 8-pixel fragment of the line, bit31 being the left-most fragment), followed by data bytes for each flagged fragment (with 8 pixels per fragment, bit0 being the left-most pixel). The Inverse lines have the same 32bit flags, but for whatever reason, the following data byte(s) are to be XORed with FFh.

### Audio Data

```
+-----------------------------------------------------------------------+
|       First comes the BGM (if used)                                   |
|       Then comes sound effect #1 (if used)                            |
|       Then comes sound effect #2 (if used)                            |
|       Then comes sound effect #3 (if used)                            |
+-----------------------------------------------------------------------+
```

The sound data seems to be a variant of VOX ADPCM at around 8KHz.

### IDs and Filenames
Half of the Flipnote Studio ID is same as the last 4 bytes of the wifi MAC address. The filenames are also containing the last 3 bytes of the MAC address. The \"XNNNNN_NNNNNNNNNNNNN_NNN.ppm\" filename is also encoded in three header entries:

```
+-------------------------------------------------------------------------------------+
|       Header  = Filename      = Meaning                                             |
|       3xHEX   = XNNNNN        = Based on MAC address (the "X" in "XNNNNN" is what?) |
|       13xASCII= NNNNNNNNNNNNN = Some 13-digit random number or so as ASCII string   |
|       5xHEX   = NNNNNNNNNN    = First 10-digits of above 13-digit string            |
|       2xVER   = NNN.ppm       = Trailing version(?) number (hex, decimal?)          |
+-------------------------------------------------------------------------------------+
```

For the file name \"G35B20_0909841CDBEB1_002.ppm\":

```
+------------------------------------------------------------------------------+
|                        <-hex--> <-----ascii-----------------> <-asc--> <-n-> |
|       Filename (ori)   D3 5B 20 30 39 30 39 38 34 31 43 44 42 45 42 31 00 00 |
|       Filename (curr)  D3 5B 20 30 39 30 39 38 34 31 43 44 42 45 42 31 02 00 |
|                        <-hex--> <--hex------->                               |
|       Filename (frag)  D3 5B 20 09 09 84 1C DB                               |
+------------------------------------------------------------------------------+
```


### Preview Palette (fixed)
Fullscreen flipnotes can have only four colors: Black, White, Red, Blue). Additional shades like gray, magenta, or dark/light colors exist only in resampled preview images. The Preview List uses pale colors, with higher contrast for the Selected icon.

```
+-----------------------------------------------------------------------+
|       Color  Purpose    (appearance)  Preview   Selected              |
|       00h    N/A       (transparent)  1F-1F-1F  1F-1F-1F              |
|       01h    Black       (dark grey)  13-13-13  0A-0A-0A              |
|       02h    White           (white)  1F-1F-1F  1F-1F-1F              |
|       03h    White+Black      (grey)  19-19-19  13-13-13              |
|       04h    Red               (red)  1F-12-12  1F-09-09              |
|       05h    Red+Black    (dark red)  1B-13-13  18-0A-0A              |
|       06h    Red+White        (pink)  1F-19-19  1F-15-15              |
|       07h    N/A             (green)  0E-1F-0E  02-1F-02              |
|       08h    Blue             (blue)  12-12-1F  09-09-1F              |
|       09h    Blue+Black  (dark blue)  13-13-1A  0A-0A-16              |
|       0Ah    Blue+White (light blue)  19-19-1F  15-15-1F              |
|       0Bh    N/A             (green)  0E-1F-0E  02-1F-02              |
|       0Ch    Red+Blue      (magenta)  1A-13-1A  16-0B-16              |
|       0Dh    N/A             (green)  0E-1F-0E  02-1F-02              |
|       0Eh    N/A             (green)  0E-1F-0E  02-1F-02              |
|       0Fh    N/A             (green)  0E-1F-0E  02-1F-02              |
+-----------------------------------------------------------------------+
```


### FAT12:\\photo\\DCIM\\100NIN02\\HNI_nnnn.JPG ;camera photos
Flipnote doesn\'t contain an own camera function. However, the drawing utility does allow to import JPGs from the camera partition (ie. images that have been previously taken via the DSi Camera utility).



