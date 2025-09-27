# DS 3D Polygon Attributes


### 40004A4h - Cmd 29h - POLYGON_ATTR - Set Polygon Attributes (W)

```
+------------------------------------------------------------------------------------+
|       0-3   Light 0..3 Enable Flags (each bit: 0=Disable, 1=Enable)                |
|       4-5   Polygon Mode  (0=Modulation,1=Decal,2=Toon/Highlight Shading,3=Shadow) |
|       6     Polygon Back Surface   (0=Hide, 1=Render)  ;Line-segments are always   |
|       7     Polygon Front Surface  (0=Hide, 1=Render)  ;rendered (no front/back)   |
|       8-10  Not used                                                               |
|       11    Depth-value for Translucent Pixels    (0=Keep Old, 1=Set New Depth)    |
|       12    Far-plane intersecting polygons       (0=Hide, 1=Render/clipped)       |
|       13    1-Dot polygons behind DISP_1DOT_DEPTH (0=Hide, 1=Render)               |
|       14    Depth Test, Draw Pixels with Depth    (0=Less, 1=Equal) (usually 0)    |
|       15    Fog Enable                            (0=Disable, 1=Enable)            |
|       16-20 Alpha      (0=Wire-Frame, 1..30=Translucent, 31=Solid)                 |
|       21-23 Not used                                                               |
|       24-29 Polygon ID (00h..3Fh, used for translucent, shadow, and edge-marking)  |
|       30-31 Not used                                                               |
+------------------------------------------------------------------------------------+
```

Writes to POLYGON_ATTR have no effect until next BEGIN_VTXS command.
Changes to the Light bits have no effect until lighting is re-calculated by Normal command. The interior of Wire-frame polygons is transparent (Alpha=0), and only the lines at the polygon edges are rendered, using a fixed Alpha value of 31.

### 4000480h - Cmd 20h - COLOR - Directly Set Vertex Color (W)

```
+-----------------------------------------------------------------------+
|       Parameter 1, Bit 0-4    Red                                     |
|       Parameter 1, Bit 5-9    Green                                   |
|       Parameter 1, Bit 10-14  Blue                                    |
|       Parameter 1, Bit 15-31  Not used                                |
+-----------------------------------------------------------------------+
```

The 5bit RGB values are internally expanded to 6bit RGB as follows: X=X\*2+(X+31)/32, ie. zero remains zero, all other values are X=X\*2+1.
Aside from by using the Color command, the color can be also changed by MaterialColor0 command (if MaterialColor0.Bit15 is set, it acts identical as the Color Command), and by the Normal command (which calculates the color based on light/material parameters).

### Depth Test
The Depth Test compares the depth of the pixels of the polygon with the depth of previously rendered polygons (or of the rear plane if there have been none rendered yet). The new pixels are drawn if the new depth is Less (closer to the camera), or if it is Equal, as selected by POLYGON_ATTR.Bit14.
Normally, Depth Equal would work only exact matches (ie. if the overlapping polygons have exactly the same coordinates; and thus have the same rounding errors), however, the NDS hardware is allowing \"Equal\" to have a tolerance of +/-200h (within the 24bit depth range of 0..FFFFFFh), that may bypass rounding errors, but it may also cause nearby polygons to be accidently treated to have equal depth.



