# DS 3D Texture Formats


### Format 2: 4-Color Palette Texture
Each Texel occupies 2bit, the first Texel is located in LSBs of 1st byte.
In this format, the Palette Base is specified in 8-byte steps; all other formats use 16-byte steps (see PLTT_BASE register).

### Format 3: 16-Color Palette Texture
Each Texel occupies 4bit, the 1st Texel is located in LSBs of 1st byte.

### Format 4: 256-Color Palette Texture
Each Texel occupies 8bit, the 1st Texel is located in 1st byte.

### Format 7: Direct Color Texture
Each Texel occupies 16bit, the 1st Texel is located in 1st halfword.
Bit0-4: Red, Bit5-9: Green, Bit10-14: Blue, Bit15: Alpha

### Format 1: A3I5 Translucent Texture (3bit Alpha, 5bit Color Index)
Each Texel occupies 8bit, the 1st Texel is located in 1st byte.

```
+-----------------------------------------------------------------------+
|       Bit0-4: Color Index (0..31) of a 32-color Palette               |
|       Bit5-7: Alpha       (0..7; 0=Transparent, 7=Solid)              |
+-----------------------------------------------------------------------+
```

The 3bit Alpha value (0..7) is internally expanded into a 5bit Alpha value (0..31) as follows: Alpha=(Alpha\*4)+(Alpha/2).

### Format 6: A5I3 Translucent Texture (5bit Alpha, 3bit Color Index)
Each Texel occupies 8bit, the 1st Texel is located in 1st byte.

```
+-----------------------------------------------------------------------+
|       Bit0-2: Color Index (0..7) of a 8-color Palette                 |
|       Bit3-7: Alpha       (0..31; 0=Transparent, 31=Solid)            |
+-----------------------------------------------------------------------+
```


### Format 5: 4x4-Texel Compressed Texture
Consists of 4x4 Texel blocks in Slot 0 or 2, 32bit per block, 2bit per Texel,

```
+-----------------------------------------------------------------------+
|       Bit0-7   Upper 4-Texel row (LSB=first/left-most Texel)          |
|       Bit8-15  Next  4-Texel row ("")                                 |
|       Bit16-23 Next  4-Texel row ("")                                 |
|       Bit24-31 Lower 4-Texel row ("")                                 |
+-----------------------------------------------------------------------+
```

Additional Palette Index Data for each 4x4 Texel Block is located in Slot 1,

```
+--------------------------------------------------------------------------------+
|       Bit0-13  Palette Offset in 4-byte steps; Addr=(PLTT_BASE*10h)+(Offset*4) |
|       Bit14-15 Transparent/Interpolation Mode (0..3, see below)                |
+--------------------------------------------------------------------------------+
```

whereas, the Slot 1 offset is related to above Slot 0 or 2 offset,

```
+--------------------------------------------------------------------------------+
|       slot1_addr = slot0_addr / 2           ;lower 64K of Slot1 assoc to Slot0 |
|       slot1_addr = slot2_addr / 2 + 10000h  ;upper 64K of Slot1 assoc to Slot2 |
+--------------------------------------------------------------------------------+
```

The 2bit Texel values (0..3) are intepreted depending on the Mode (0..3),

```
+-----------------------------------------------------------------------------------+
|       Texel  Mode 0       Mode 1             Mode 2         Mode 3                |
|       0      Color 0      Color0             Color 0        Color 0               |
|       1      Color 1      Color1             Color 1        Color 1               |
|       2      Color 2      (Color0+Color1)/2  Color 2        (Color0*5+Color1*3)/8 |
|       3      Transparent  Transparent        Color 3        (Color0*3+Color1*5)/8 |
+-----------------------------------------------------------------------------------+
```

Mode 1 and 3 are using only 2 Palette Colors (which requires only half as much Palette memory), the 3rd (and 4th) Texel Colors are automatically set to above values (eg. to gray-shades if color 0 and 1 are black and white).
Note: The maximum size for 4x4-Texel Compressed Textures is 1024x512 or 512x1024 (which are both occupying the whole 128K in slot 0 or 2, plus 64K in slot1), a larger size of 1024x1024 cannot be used because of the gap between slot 0 and 2.



