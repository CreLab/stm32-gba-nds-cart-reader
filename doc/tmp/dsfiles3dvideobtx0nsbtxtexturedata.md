# DS Files - 3D Video BTX0 (.NSBTX Texture Data)


Contains Texture bitmaps and Palettes. The TEX0 Chunk can exist in .NSBTX Texture files, or in .NSBMD Model files.

### BTX0 Header (in .NSBTX files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BTX0" (Basic Texture)                             |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (1)                                           |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=TEX0)                             |
|       010h 4     Offset from BTX0 to TEX0 Chunk                        |
+------------------------------------------------------------------------+
```


### TEX0 Chunk (can occur in .NSBTX and .NSBMD files)

```
+-----------------------------------------------------------------------------------+
|       000h  4       Chunk ID "TEX0" (Texture Block)                               |
|       004h  4       Chunk Size                                                    |
|       008h  4       Padding (0)                                                   |
|       00Ch  2       Texture Data Size/8                            ;\Texture      
|       00Eh  2       Texture Dict Offset (03Ch)                     ; (Format 1..4 |
|       010h  4       Padding (0)                                    ; and 6..7)    |
|       014h  4       Texture Data Offset                            ;/             |
|       018h  4       Padding (0)                                                   |
|       01Ch  2       Compressed Texture Data Size/12 (often 0=none) ;\             
|       01Eh  2       Compressed Texture Dict Offset (03Ch, too)     ; Compressed   |
|       020h  4       Padding (0)                                    ; Texture      |
|       024h  4       Compressed Texture Offset for 4x4-Texel Data   ; (Format 5)   |
|       028h  4       Compressed Texture Offset for 4x4-Texel Attr   ;/             |
|       02Ch  4       Padding (0)                                                   |
|       030h  4       Palette Data Size/8                            ;\             
|       034h  4       Palette Dict Offset                            ; Palette      |
|       038h  4       Palette Data Offset                            ;/             |
|       [0Eh] ..      Texture Dict (with 8-byte entries, see below)  ;\Dict's       
|       [34h] ..      Palette Dict (with 4-byte entries, see below)  ;/             |
|       [14h] [0Ch]*8 Texture Data                                   ;\             
|       [24h] [1Ch]*8 Compressed Texture 4x4-Texel Data (2bpp)       ; VRAM Data    |
|       [28h] [1Ch]*4 Compressed Texture 4x4-Texel Attr (1bpp)       ;              |
|       [38h] [30h]*8 Palette Data Section                           ;/             |
+-----------------------------------------------------------------------------------+
```


### 8-byte entries in Texture Dict:
This Dict is shared for Textures and Compressed Textures (ie. TEX0 entries \[00Eh\] and \[01Eh\] do both point to the same Dict).

```
+-------------------------------------------------------------------------------------+
|       000h 4   Value for TEXIMAGE_PARAM register                                    |
|                  0-15   Texture Data       (Offset/8, in File Data / VRAM Data)     |
|                  16-19  Zero in TEX0       (instead, derived from Model's Material) |
|                  20-22  Texture S-Size (W) (for W=0..7: Width=(8 SHL W)             |
|                  23-25  Texture T-Size (H) (for H=0..7: Height=(8 SHL H)            |
|                  26-28  Texture Format     (0..7)                                   |
|                  29     Palette Color 0    (0=Displayed, 1=Made Transparent)        |
|                  30-31  Zero in TEX0       (instead, derived from Model's Material) |
|       004h 4   Width/Height (contains the above 3bit W/H values decoded to 11bit)   |
|                  0-10   Width in pixels    (8 shl W) (8..1024)                      |
|                  11-21  Height in pixels   (8 shl H) (8..1024)                      |
|                  22-30  Unknown            (0)                                      |
|                  31     Unknown            (1)                                      |
+-------------------------------------------------------------------------------------+
```


### 4-byte entries in Palette Dict:

```
+---------------------------------------------------------------------------------+
|       000h 2   Value for PLTT_BASE register                                     |
|                  0-12   Palette Base       (Offset/8, in File Data / VRAM Data) |
|                  13-15  Unused             (0)                                  |
|       002h 2   Unknown (usually 0, sometimes 1)  ;unrelated to number of colors |
+---------------------------------------------------------------------------------+
```


### Note
The offsets in LSBs of TEXIMAGE_PARAM and PLTT_BASE are relative the begin of the corresponding Data block (and need to be adjusted depending on where the data is stored in VRAM).

### Texture/Palette Names
TEX0 has Textures and Palettes are stored in separate Dict\'s. One could usually guess which Texture belongs to which Palette, but there is no clear naming scheme.
For example, MarioKart DS \"rom:\\data\\Course\\mini_stage1Tex.carc\\\*.nsbtx\":

```
+-----------------------------------------------------------------------------------+
|       Texture Name: "MS_ttl_1_2"      ;\both SAME name                            
|       Palette Name: "MS_ttl_1_2"      ;/                                          |
|       Texture Name: "MS_ttl_3"        ;\palette with extra "_pl" suffix (or "_p") 
|       Palette Name: "MS_ttl_3_pl"     ;/                                          |
|       Texture Name: "MS1_11_2"        ;\palette without suffix                    
|       Palette Name: "MS1_11"          ;/                                          |
|       Texture Name: "nr_space3_2"     ;\palette without prefix                    
|       Palette Name: "space3_2"        ;/                                          |
+-----------------------------------------------------------------------------------+
```




