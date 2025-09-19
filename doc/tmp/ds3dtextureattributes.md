# DS 3D Texture Attributes


### 4000488h - Cmd 22h - TEXCOORD - Set Texture Coordinates (W)
Specifies the texture source coordinates within the texture bitmap which are to be associated with the next vertex.

```
+-----------------------------------------------------------------------------+
|       Parameter 1, Bit 0-15   S-Coordinate (X-Coordinate in Texture Source) |
|       Parameter 1, Bit 16-31  T-Coordinate (Y-Coordinate in Texture Source) |
|       Both values are 1bit sign + 11bit integer + 4bit fractional part.     |
|       A value of 1.0 (=1 SHL 4) equals to one Texel.                        |
+-----------------------------------------------------------------------------+
```

With Position 0.0 , 0.0 drawing starts from upperleft of the Texture.
With positive offsets, drawing origin starts more \"within\" the texture.
With negative offsets, drawing starts \"before\" the texture.
\"When texture mapping, the Geometry Engine works faster if you issue commands in the order TexCoord -\> Normal -\> Vertex.\"

### 40004A8h - Cmd 2Ah - TEXIMAGE_PARAM - Set Texture Parameters (W)

```
+-------------------------------------------------------------------------------------+
|       0-15  Texture VRAM Offset div 8 (0..FFFFh -> 512K RAM in Slot 0,1,2,3)        |
|             (VRAM must be allocated as Texture data, see Memory Control chapter)    |
|       16    Repeat in S Direction (0=Clamp Texture, 1=Repeat Texture)               |
|       17    Repeat in T Direction (0=Clamp Texture, 1=Repeat Texture)               |
|       18    Flip in S Direction   (0=No, 1=Flip each 2nd Texture) (requires Repeat) |
|       19    Flip in T Direction   (0=No, 1=Flip each 2nd Texture) (requires Repeat) |
|       20-22 Texture S-Size        (for N=0..7: Size=(8 SHL N); ie. 8..1024 texels)  |
|       23-25 Texture T-Size        (for N=0..7: Size=(8 SHL N); ie. 8..1024 texels)  |
|       26-28 Texture Format        (0..7, see below)                                 |
|       29    Color 0 of 4/16/256-Color Palettes (0=Displayed, 1=Made Transparent)    |
|       30-31 Texture Coordinates Transformation Mode (0..3, see below)               |
+-------------------------------------------------------------------------------------+
```

Texture Formats:

```
+-----------------------------------------------------------------------+
|       0  No Texture                     -                             |
|       1  A3I5 Translucent Texture       8bpp                          |
|       2  4-Color Palette Texture        2bpp                          |
|       3  16-Color Palette Texture       4bpp                          |
|       4  256-Color Palette Texture      8bpp                          |
|       5  4x4-Texel Compressed Texture   3bpp                          |
|       6  A5I3 Translucent Texture       8bpp                          |
|       7  Direct Texture                 16bpp                         |
+-----------------------------------------------------------------------+
```

Texture Coordinates Transformation Modes:

```
+-----------------------------------------------------------------------+
|       0  Do not Transform texture coordinates                         |
|       1  TexCoord source                                              |
|       2  Normal source                                                |
|       3  Vertex source                                                |
+-----------------------------------------------------------------------+
```

The S-Direction equals to the horizontal direction of the source bitmap.
The T-Direction, T-repeat, and T-flip are the same in vertical direction.
For a \"/\" shaped texture, the S-clamp, S-repeat, and S-flip look like so:

```
+-----------------------------------------------------------------------+
|       Clamp _____  Repeat       Repeat+Flip                           |
|       _____/       ///////////  /\/\/\/\/\/                           
+-----------------------------------------------------------------------+
```

With \"Clamp\", the texture coordinates are clipped to MinMax(0,Size-1), so the texels at the edges of the texture bitmap are repeated (to avoid that effect, fill the bitmap edges by texels with alpha=0, so they become invisible).

### 40004ACh - Cmd 2Bh - PLTT_BASE - Set Texture Palette Base Address (W)

```
+-----------------------------------------------------------------------------+
|       0-12   Palette Base Address (div8 or div10h, see below)               |
|              (Not used for Texture Format 7: Direct Color Texture)          |
|              (0..FFF8h/8 for Texture Format 2: ie. 4-color-palette Texture) |
|              (0..17FF0h/10h for all other Texture formats)                  |
|       13-31  Not used                                                       |
+-----------------------------------------------------------------------------+
```

The palette data occupies 16bit per color:

```
+-----------------------------------------------------------------------+
|       Bit0-4:   Red                                                   |
|       Bit5-9:   Green                                                 |
|       Bit10-14: Blue                                                  |
|       Bit15:    Not used                                              |
+-----------------------------------------------------------------------+
```

VRAM must be allocated as Texture Palette, there can be up to 6 Slots allocated, ie. the addressable 18000h bytes, see Memory Control chapter.

### TexImageParam and TexPlttBase
Can be issued per polygon (except within polygon strips).



