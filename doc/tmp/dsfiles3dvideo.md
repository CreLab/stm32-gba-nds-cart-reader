# DS Files - 3D Video


Some NDS games are using the following set of files for 3D Models:
- [DS Files - 3D Video BMD0 (.NSBMD Model Data)](./dsfiles3dvideobmd0nsbmdmodeldata.md)
- [DS Files - 3D Video BTX0 (.NSBTX Texture Data)](./dsfiles3dvideobtx0nsbtxtexturedata.md)
- [DS Files - 3D Video BCA0 (.NSBCA Character Skeletal Animation)](./dsfiles3dvideobca0nsbcacharacterskeletalanimation.md)
- [DS Files - 3D Video BTA0 (.NSBTA Texture Coordinate Animation)](./dsfiles3dvideobta0nsbtatexturecoordinateanimation.md)
- [DS Files - 3D Video BTP0 (.NSBTP Texture Pattern Animation)](./dsfiles3dvideobtp0nsbtptexturepatternanimation.md)
- [DS Files - 3D Video BMA0 (.NSBMA Material Animation)](./dsfiles3dvideobma0nsbmamaterialanimation.md)
- [DS Files - 3D Video NVA0 (.NSBVA Unknown Vis Animation)](./dsfiles3dvideonva0nsbvaunknownvisanimation.md)
The format was used in Nintendo\'s own titles somewhere between 2005 and 2009 (older launch titles did use an older .bin or .bxx format instead of .nsbxx format, and later mini-games often don\'t support 3D video at all, and third-party games tend to use their own formats). Some known titles that do use .nsbxx are:

```
+-------------------------------------------------------------------------+
|       type BMD0/BCA0/BTA0/BTX0/BTP0/BMA0 is used by Mariokart DS (2005) |
|       type BMD0/BCA0/BTA0 is used by Walk with Me (2008-2009)           |
|       type BVA0 is used by what... if it was ever used?                 |
+-------------------------------------------------------------------------+
```

Note: The format resembles the later CGFX format used on 3DS.

### Dict - Directory with Name/Data (used in various places in 3D video files)

```
+-------------------------------------------------------------------------------------+
|       000h 1     Dummy (00h)                                                        |
|       001h 1     Number of entries (N)                                              |
|       002h 2     Size of whole Dict (Hdr(8)+Tree(4+X*4)+Data(4+N*siz)+Name(N*10h))  |
|       004h 2     Offset to Tree Section (always 08h)                                |
|       006h 2     Offset to Data Section (0Ch+X*4)                                   |
|       008h 4     Tree entry 0    (Patricia Tree Root entry)                 ;\Tree  
|       00Ch X*4   Tree entry 1..X (Patricia Tree and actual Names/Data)      ;/      |
|       ...  2     Size of each Data entry (siz) (usually 4 or 8)             ;\      
|       ...  2     Size of this Data Info Section (4+N*siz)                   ; Data  |
|       ...  N*siz Data (siz bytes, for each entry)                           ;/      |
|       ...  N*10h Name Strings (10h-byte ASCII, zeropadded, for each entry)  ;-Names |
+-------------------------------------------------------------------------------------+
```

Patricia Tree Root entry:

```
+-------------------------------------------------------------------------------------+
|       000h 1     Patricia Tree First Bit-number (always 7Fh=Last=char[0Fh].bit7)    |
|       001h 1     Patricia Tree First entry (1..X) (usually points to rightmost bit) |
|       002h 2     Patricia Tree Unused (zerofilled)                                  |
+-------------------------------------------------------------------------------------+
```

Patricia Tree entry 1..X format:

```
+-----------------------------------------------------------------------------------+
|       000h 1     Patricia Tree Bit-number to be tested (0=Bit0 of 1st char)       |
|       001h 1     Patricia Tree Next entry when test=0  ;\upon match: Next=Curr    
|       002h 1     Patricia Tree Next entry when test=1  ;/upon error: Next=0       |
|       003h 1     Entry number in Data and Name tables (used when Next=Curr entry) |
+-----------------------------------------------------------------------------------+
```

The Patricia Tree is intended for searching Symbols by testing a few bits (without comparing all characters).
The Data content depends on what the Dict is used for. Each name can have a small amount of data stored inside of the Dict (and, that Data may contain offsets to larger data stored elsewhere).

### References
<https://github.com/scurest/nsbmd_docs/blob/master/nsbmd_docs.txt>
Errata:

```
+------------------------------------------------------------------------------------+
|       3D Video Container/Headers have version=1 (except: BMD0 has version=2)       |
|       BoundingBox seems to have "origin/size" values (not "min/max" values)        |
|       SHININESS is a 128-byte array, that's definietly not encoded in 4-byte entry |
|       Material seems to contain OR-mask and AND-mask values for POLYGON_ATTR ?     |
|       Material can have further parameters, in the TODO part?                      |
|       MaterialIdxList offsets are relative to Model[008h], not to MaterialIdxList  |
|       Pivot should use C=B and D=A (not C=A and D=B) for sine/cosine rotations?    |
|       BasisMatrix description could be simplified, and are the unknown 2bit used?  |
|       Animations have IDs "J.AC","M.AT", "M.PT", "M.AM" (with "."=00h)             |
|       Dict's (aka NameList's) contain Patricia Trees for fast lookup (alike 3DS)   |
|       SRT0 does "Texture Coordinate Animation" (not "Material Animation")          |
|       SRT0 probably supports texture Scale/Rotate/Translate (not just Translate)   |
|       TEX0[04h]=Size of TEX0                                                       |
|       TEX0[18h]=Padding32bit (is MISSING in .txt, insert this after "block1_off")  |
|       TEX0[1Eh]=CompressedTextureDictOffs (alias for TEX[0Eh]=TextureDictOffs)     |
|       Texture[004h] is 11bit width, 11bit height (from TEXIMAGE bits), and bit31=1 |
|       NSBMA files do exists (eg. in Mariokart DS), and could/should be described   |
|       NSBVA files... would be nice to know if they are used by any games?          |
+------------------------------------------------------------------------------------+
```




