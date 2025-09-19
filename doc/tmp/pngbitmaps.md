# PNG Bitmaps


Used by DSi Browser (rom:\\\*.png)

### File Header

```
+-----------------------------------------------------------------------+
|       000h 8    ID (89h,'PNG',0Dh,0Ah,1Ah,0Ah)                        |
|       008h ..   Chunks                                                |
+-----------------------------------------------------------------------+
```


### Chunk Format

```
+-----------------------------------------------------------------------+
|       000h 4    Chunk Size (LEN)                  ;big-endian         |
|       004h 4    Chunk ID (4-letter ASCII) ("A..Z" and "a..z")         |
|       008h LEN  Chunk Data                                            |
|       ...  4    Chunk CRC32 on [004h+(0..LEN+3)]  ;big-endian         |
+-----------------------------------------------------------------------+
```

The Chunk ID is 4-letter ASCII, with upper/lowercase having special meanings:

```
+------------------------------------------------------------------------------------+
|       1st char  Uppercase=Critical (Basic)   Lowercase=Ancillary (Optional extras) |
|       2nd char  Uppercase=Public (Official)  Lowercase=Private (Custom extensions) |
|       3rd char  Uppercase=Normal             Lowercase=Reserved                    |
|       4th char  Uppercase=Unsafe to copy     Lowercase=Safe to copy                |
+------------------------------------------------------------------------------------+
```

PNG Chunks

```
+------------------------------------------------------------------------------------+
|       IHDR v1.0  Image header (first chunk)                ;\                      
|       PLTE v1.0  Palette (if any)                          ; Critical chunks       |
|       IDAT v1.0  Image data (can be multiple IDAT chunks!) ; (aka the bitmap data) |
|       IEND v1.0  Image trailer (last chunk)                ;/                      |
|       tRNS v1.0  Transparency                              ;-Transparency          |
|       cHRM v1.0  Primary chromaticities and white point    ;\                      
|       gAMA v1.0  Image gamma                               ;                       |
|       iCCP v1.1  Embedded ICC profile                      ; Colour space info     |
|       sBIT v1.0  Significant bits                          ;                       |
|       sRGB v1.1  Standard RGB colour space                 ;                       |
|       cICP v3rd  Coding-independent code points            ;/                      |
|       bKGD v1.0  Background colour                         ;\                      
|       hIST v1.0  Image histogram                           ;                       |
|       pHYs v1.0  Physical pixel dimensions                 ; Miscellaneous info    |
|       sPLT v1.1  Suggested palette                         ;                       |
|       eXIf v3rd  EXIF chunk (starts with "MM"=byteorder)   ;/                      |
|       tEXt v1.0  Textual data                              ;\Textual information   
|       zTXt v1.0  Compressed textual data                   ; (aka comments)        |
|       iTXt v1.2  International textual data                ;/                      |
|       tIME v1.0  Image last-modification time              ;-Time stamp            |
|       acTL v3rd  Animation Control Chunk                   ;\                      
|       fcTL v3rd  Frame Control Chunk                       ; Animation (APNG)      |
|       fdAT v3rd  Frame Data Chunk                          ;/                      |
+------------------------------------------------------------------------------------+
```

Note: There are some rules for the chunk ordering, see PNG specs for details.

### IHDR Chunk (first chunk)

```
+-------------------------------------------------------------------------------------+
|       000h 4    Chunk Size (always 0Dh)       ;big-endian                           |
|       004h 4    Chunk ID   ("IHDR")                                                 |
|       008h 4    Width in pixels  (0=invalid)  ;big-endian                           |
|       00Ch 4    Height in pixels (0=invalid)  ;big-endian                           |
|       010h 1    Bits per sample  (1,2,4,8,16) (allowed values depend on Color Type) |
|       011h 1    Color Type       (0,2,3,4,6)                                        |
|       012h 1    Compression method  (always 0=Zlib-Deflate)                         |
|       013h 1    Filter method       (always 0=Adaptive; with subtype per line)      |
|       014h 1    Interlace method    (0=None, 1=Adam7)                               |
|       015h 4    Chunk CRC32 on [004h..]       ;big-endian                           |
+-------------------------------------------------------------------------------------+
```

The valid Color types and bits per sample are:

```
+-----------------------------------------------------------------------+
|       Color type             (Samples)  Bits/sample     Bits/pixel    |
|       0=Grayscale            (I)        1,2,4,8,16  --> 1,2,4,8,16    |
|       2=Truecolor            (RGB)      8,16        --> 24,48         |
|       3=Palette indices      (I)        1,2,4,8     --> 1,2,4,8       |
|       4=Grayscale with alpha (IA)       8,16        --> 16,32         |
|       6=Truecolor with alpha (RGBA)     8,16        --> 32,64         |
+-----------------------------------------------------------------------+
```


### PLTE Chunk (required for Color type 3)

```
+-------------------------------------------------------------------------------+
|       000h 4    Chunk Size (LEN=NumColors*3) (3..300h)            ;big-endian |
|       004h 4    Chunk ID ("PLTE")                                             |
|       008h LEN  Palette Data (three bytes per color, ordered R,G,B)           |
|       ...  4    Chunk CRC32 on [004h+(0..LEN+3)]  ;big-endian                 |
+-------------------------------------------------------------------------------+
```

Additional Alpha values for each palette entry can be defined in tRNS chunk.

### IDAT Chunk(s)

```
+-----------------------------------------------------------------------+
|       000h 4    Chunk Size (LEN)                      ;big-endian     |
|       004h 4    Chunk ID ("IDAT")                                     |
|       008h LEN  Zlib-Deflate compressed image data                    |
|       ...  4    Chunk CRC32 on [004h+(0..LEN+3)]  ;big-endian         |
+-----------------------------------------------------------------------+
```

There may be multiple IDAT chunks; if so, they shall appear consecutively with no other \"intervening\" chunks. The compressed datastream is then the \"concatenation\" of the contents of the data fields of all the IDAT chunks.

### IEND Chunk (last chunk)

```
+----------------------------------------------------------------------------+
|       000h 4    Chunk Size (0)                    ;big-endian              |
|       004h 4    Chunk ID ("IEND")                                          |
|       008h 4    Chunk CRC32 on [004h..007h] (always AE426082h) ;big-endian |
+----------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________ Decompression, Unfiltering, Deinterlacing __________________ |
+-------------------------------------------------------------------------------------+
```


### Overall image decoding flowchart
- merge SDAT chunk(s) into a continous bitstream (remove Chunk Headers/CRCs)
- decompress via Zlib-Inflate
- unfilter
- convert to desired color depth and RGBA bit-order
- deinterlace

### Decompression
The merged IDAT chunks contain:

```
+--------------------------------------------------------------------------+
|       000h 1   zlib compression method/flags code (usually 78h)          |
|       001h 1   Additional flags/check bits        (usually 9Ch) (or DAh) |
|       002h ..  Compressed data blocks (deflate)                          |
|       ...  4   Adler32 checksum on decompressed data   ;big-endian       |
+--------------------------------------------------------------------------+
```

- [ZIP Decompression](./zipdecompression.md)
\"tinf_zlib_uncompress\"
All scanlines are padded to 1-byte boundary, and all scanlines include a leading filter bytes. That is, the decompressed size is:

```
+-----------------------------------------------------------------------+
|       decompressed_size = ((width*bpp+7)/8+1)*height                  |
+-----------------------------------------------------------------------+
```

For interlaced images, compute the width & height for each pass, then compute the sum of the decompressed_size\'s.

### Unfiltering
Pixels can have 1..64 bpp, but unfiltering is always done in BYTE units.

```
+------------------------------------------------------------------------------+
|       for pass=1 to num_passes   ;for 7-pass interlacing                     |
|         calc width/height for current pass                                   |
|         for x=1 to (bpp+7)/8 + (width*bpp+7)/8                               |
|           byte[dst]=00h, dst=dst+1            ;-pad topmost for unfiltering  |
|         for y=1 to height                                                    |
|           filter = byte[src], src=src+1                                      |
|           for x=1 to (bpp+7)/8                                               |
|             byte[dst]=00h, dst=dst+1          ;-pad leftmost for unfiltering |
|           for x=1 to (width*bpp+7)/8                                         |
|             left      = byte[dst-(bpp+7)/8]                                  |
|             upper     = byte[dst-bytes_per_scanline]                         |
|             upperleft = byte[dst-bytes_per_scanline-(bpp+7)/8]               |
|             if filter=0 then byte[dst]=byte[src]                             |
|             if filter=1 then byte[dst]=byte[src]+left                        |
|             if filter=2 then byte[dst]=byte[src]+upper                       |
|             if filter=3 then byte[dst]=byte[src]+(left+upper)/2              |
|             if filter=4 then                                                 |
|               pa=abs(upper-upperleft)                                        |
|               pb=abs(left-upperleft)                                         |
|               pc=abs(left+upper-(upperleft*2))                               |
|               if pa<=pb AND pa<=pc then byte[dst]=byte[src]+left             |
|               elseif pb<=pc then        byte[dst]=byte[src]+upper            |
|               else                      byte[dst]=byte[src]+upperleft        |
|             if filter>4 then error                                           |
|             src=src+1, dst=dst+1                                             |
|           next x                                                             |
|         next y                                                               |
|       next pass                                                              |
+------------------------------------------------------------------------------+
```

Note: The dst buffer may be as small as two scanlines (when directly forwarding the unfiltered data to the color conversion & deinterlacing steps).

### Color Depth conversion and RGBA bit-order
The MSB of first pixel is in bit7 of first byte (ie. 16bit samples are big-endian, and 2bpp would have 1st pixel in bit7-6). Pixels with multiple samples are ordered R,G,B or R,G,B,A or Luminance,A.
The data should be converted to a format supported by the OS/hardware. Also, deinterlacing will be easier when converting to at least 8bpp (or simply convert everything to 32bpp).

### Deinterlacing (if enabled in IHDR chunk)
Interlace allows to display a low-resolution preview during slow network downloads. The image is divided into 8x8 pixel blocks.

```
+-------------------------------------------------------------------------------------------------------------------------------------------------------------+
|       Pass Numbers per 8x8:      Width/Height per pass:                                                                                                     |
|       1 6 4 6 2 6 4 6            Pass 1   (width+7)/8, (height+7)/8  ;\                                                                                     
|       7 7 7 7 7 7 7 7            Pass 2   (width+3)/8, (height+7)/8  ;                                                                                      |
|       5 6 5 6 5 6 5 6            Pass 3   (width+3)/4, (height+3)/8  ; seven-pass   7 7 7 7 7 7 7 7            Pass 4   (width+1)/4, (height+3)/4  ; (Adam7 |
|       3 6 4 6 3 6 4 6            Pass 5   (width+1)/2, (height+1)/4  ; interlace)                                                                           |
|       7 7 7 7 7 7 7 7            Pass 6   (width+0)/2, (height+1)/2  ;                                                                                      |
|       5 6 5 6 5 6 5 6            Pass 7   (width+0)/1, (height+0)/2  ;/                                                                                     |
|       7 7 7 7 7 7 7 7            Single   (width+0)/1, (height+0)/1  ;-single-pass                                                                          |
+-------------------------------------------------------------------------------------------------------------------------------------------------------------+
```

For example, a 12x2 pixel image would be interlaced as so:

```
+------------------------------------------------------------------------------------+
|       1 6 4 6 2 6 4 6 1 6 4 6      ;\Pass1=2x1, Pass2=1x1, Pass3=Empty, Pass4=4x1, 
|       7 7 7 7 7 7 7 7 7 7 7 7      ;/Pass5=Empty, Pass6=6x1, Pass7=12x1.           |
+------------------------------------------------------------------------------------+
```

All seven passes are stored in a single Zlib-bitstream (for low-res preview, one must pause the Zlib decompression every once and then to display the yet downloaded pixels).


```
+-------------------------------------------------------------------------------------+
|      ____________________________________ Misc ____________________________________ |
+-------------------------------------------------------------------------------------+
```


### tRNS Chuunk
Colour type 0 Grayscale

```
+-------------------------------------------------------------------------------+
|       Grey sample value              2 bytes   (big-endian) (0..SampleSize-1) |
+-------------------------------------------------------------------------------+
```

Colour type 2 RGB

```
+-------------------------------------------------------------------------------+
|       Red sample value               2 bytes   (big-endian) (0..SampleSize-1) |
|       Blue sample value              2 bytes   (big-endian)                   |
|       Green sample value             2 bytes   (big-endian)                   |
+-------------------------------------------------------------------------------+
```

Colour type 3 Color-indexed

```
+--------------------------------------------------------------------------------+
|       Alpha for palette index 0      1 byte (alpha value, 00h..FFh; FFh=Solid) |
|       Alpha for palette index 1      1 byte                                    |
|       ...etc...                      1 byte                                    |
+--------------------------------------------------------------------------------+
```


### References
Official PNG specs are filled with overhelming details (without actually getting to the point).

```
+--------------------------------------------------------------------------------+
|       http://www.libpng.org/pub/png/spec/1.0/ (gzip)      PNG v1.0             |
|       http://www.libpng.org/pub/png/spec/1.1/ (html/txt)  PNG v1.1             |
|       http://www.libpng.org/pub/png/spec/1.2/ (html/txt)  PNG v1.2             |
|       http://www.w3.org/TR/2003/REC-PNG-20031110/#minitoc PNG "second edition" |
|       http://w3c.github.io/PNG-spec/ (corrupted html)     PNG "third edition"  |
+--------------------------------------------------------------------------------+
```

To figure out \"how to decode the damn bitmap\", there is this valuable resource:

```
+--------------------------------------------------------------------------------+
|       http://pyokagan.name/blog/2019-10-14-png/ Writing a (simple) PNG decoder |
+--------------------------------------------------------------------------------+
```

For testing different color depths and interlacing:

```
+-------------------------------------------------------------------------------------+
|       http://www.schaik.com/pngsuite/ PNG test images (color types, interlace, etc) |
+-------------------------------------------------------------------------------------+
```




