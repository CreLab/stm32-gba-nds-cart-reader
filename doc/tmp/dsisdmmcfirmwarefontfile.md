# DSi SD/MMC Firmware Font File


### FAT16:\\sys\\TWLFontTable.dat ;843.1K (D2C40h bytes) (compressed) (Normal)
### FAT16:\\sys\\TWLFontTable.dat ;568.1K (8E020h bytes) (compressed) (China)
### FAT16:\\sys\\TWLFontTable.dat ;158.9K (27B80h bytes) (compressed) (Korea)
This file contains LZrev-compressed fonts in the NFTR (Nitro font) format.
This is the only real long filename that exceeds the 8.3 limit on the DSi (alternate short name is TWLFON\~1.DAT). DSi software is often using a virtual filename \"nand:/\<sharedFont\>\" on ARM9 side, which is then replaced by \"nand:/sys/TWLFontTable.dat\" on ARM7 side.
The font can be used by DSiware titles (DSi ROM cartridges usually don\'t have eMMC access, and thus cannot use the font).

```
+------------------------------------------------------------------------------------+
|       0000h       80h  RSA-SHA1 on entries [0080h..009Fh] (23h,8Bh,F9h,08h,...)    |
|       0080h       4    Date? (00h,31h,07h,08h=Normal, 00h,27h,05h,09h=China/Korea) |
|       0084h       1    Number of NFTR resources (NUM) (3=Normal, 9=China/Korea)    |
|       0085h       1    Zerofilled                                                  |
|       0086h       1    Unknown (0=Normal, 4=China, 5=Korea)                        |
|       0087h       5    Zerofilled                                                  |
|       008Ch       14h  SHA1 on below resource headers at [00A0h+(0..NUM*40h-1)]    |
|       00A0h+N*40h 20h  Resource Name in ASCII, padded with 00h                     |
|       00C0h+N*40h 4    Compressed Resource Size in .dat file   ;\compressed        
|       00C4h+N*40h 4    Compressed Resource Start in .dat file  ;/                  |
|       00C8h+N*40h 4    Decompressed Resource Size              ;-decompressed      |
|       00CCh+N*40h 14h  SHA1 on Compressed Resource at [Start+0..Size-1]            |
|       ...         ..   Compressed Font Resources (with 16-byte alignment padding)  |
+------------------------------------------------------------------------------------+
```

The resources are containing the same font thrice (at three different sizes), normal consoles have only three resources (0,1,2), chinese/korean consoles have nine resources (six zerofilled 40h-byte entries, and three actually used entries: 3,4,5 for china, or 6,7,8 for korea). The name strings of the resources are:

```
+-------------------------------------------------------------------------------------+
|       "TBF1_l.NFTR"     ;0 Large  16x21 pixels ;\Normal (blurry: 4 colors used)     
|       "TBF1_m.NFTR"     ;1 Medium 12x16 pixels ; 2bpp, 7365 characters, Unicode     |
|       "TBF1_s.NFTR"     ;2 Small  10x12 pixels ;/                                   |
|       "TBF1-cn_l.NFTR"  ;3 Large  16x21 pixels ;\China (crisp-clear: 2 colors used) 
|       "TBF1-cn_m.NFTR"  ;4 Medium 12x16 pixels ; 2bpp, 7848 characters, Unicode     |
|       "TBF1-cn_s.NFTR"  ;5 Small  12x13 pixels ;/                                   |
|       "TBF1-kr_l.NFTR"  ;6 Large  16x21 pixels ;\Korea (crisp-clear: 2 colors used) 
|       "TBF1-kr_m.NFTR"  ;7 Medium 12x16 pixels ; 2bpp, 3679 characters, Unicode     |
|       "TBF1-kr_s.NFTR"  ;8 Small  12x12 pixels ;/                                   |
+-------------------------------------------------------------------------------------+
```

All characters have proportional width (as defined in the Character Width chunk), eg. the width of the 16x21 font can be max 16 pixels (plus spacing), but most of the characters are less than 16 pixels wide.
The character numbers in the Char Map chunks are 16bit Unicode, supporting ASCII, plus extra punctuation marks, european letters with accent marks, greek, cyrillic, math symbols, and thousands of japanese letters. There are also some custom nintendo-specific symbols (like buttons and Wii symbols).

### Notes
The blurry japanese letters aren\'t actually legible (especially for the smaller font sizes). Also note that the size of small font varies for the three regions (ie. 10x12, 12x13, or 12x12).

### LZrev Compressed Font Resource Format

```
+---------------------------------------------------------------------------------+
|       ..   uncompressed area (usually 15h bytes)                                |
|       ...  compressed area (decompressed backwards)                             |
|       ..   footer: padding (to 4-byte boundary)                                 |
|       3    footer: size of footer+compressed area (offset to compressed.bottom) |
|       1    footer: size of footer (offset to compressed.top)                    |
|       4    footer: extra DEST size (offset to decompressed.top)                 |
|       ..   zeropadding to 10h-byte boundary                                     |
+---------------------------------------------------------------------------------+
```

- [LZ Decompression Functions](./lzdecompressionfunctions.md)
The original decompression function can be found in Flipnote (EUR) at address 20BF8E4h (which is mainly doing error checking, and then calling the actual decompression function at 20BF938h) (Flipnote does also contain several custom fonts, the TWLFontTable.dat file is used only for Flipnote\'s \"Help\" function).

### Nitro Font Resources
The format of the decompressed data is Nintendo\'s standard Nitro Font format:
- [DS Cartridge Nitro Font Resource Format](./dscartridgenitrofontresourceformat.md)



