# DS 3D Display Control


### 4000060h - DISP3DCNT - 3D Display Control Register (R/W)

```
+------------------------------------------------------------------------------------+
|       0     Texture Mapping      (0=Disable, 1=Enable)                             |
|       1     PolygonAttr Shading  (0=Toon Shading, 1=Highlight Shading)             |
|       2     Alpha-Test           (0=Disable, 1=Enable) (see ALPHA_TEST_REF)        |
|       3     Alpha-Blending       (0=Disable, 1=Enable) (see various Alpha values)  |
|       4     Anti-Aliasing        (0=Disable, 1=Enable)                             |
|       5     Edge-Marking         (0=Disable, 1=Enable) (see EDGE_COLOR)            |
|       6     Fog Color/Alpha Mode (0=Alpha and Color, 1=Only Alpha) (see FOG_COLOR) |
|       7     Fog Master Enable    (0=Disable, 1=Enable)                             |
|       8-11  Fog Depth Shift      (FOG_STEP=400h shr FOG_SHIFT) (see FOG_OFFSET)    |
|       12    Color Buffer RDLINES Underflow (0=None, 1=Underflow/Acknowledge)       |
|       13    Polygon/Vertex RAM Overflow    (0=None, 1=Overflow/Acknowledge)        |
|       14    Rear-Plane Mode                (0=Blank, 1=Bitmap)                     |
|       15-31 Not used                                                               |
+------------------------------------------------------------------------------------+
```


### 4000540h - Cmd 50h - SWAP_BUFFERS - Swap Rendering Engine Buffer (W)
SwapBuffers exchanges the two sets of Polygon/Vertex RAM buffers, that is, the newly defined polygons/vertices are passed to the rendering engine (and will be displayed in following frame(s)). The other buffer is emptied, and passed to the Geometry Engine (to be filled with new polygons/vertices by Geometry Commands).

```
+-----------------------------------------------------------------------------+
|       0     Translucent polygon Y-sorting (0=Auto-sort, 1=Manual-sort)      |
|       1     Depth Buffering  (0=With Z-value, 1=With W-value)               |
|             (mode 1 does not function properly with orthogonal projections) |
|       2-31  Not used                                                        |
+-----------------------------------------------------------------------------+
```

SwapBuffers isn\'t executed until next VBlank (Scanline 192) (the Geometry Engine is halted for that duration). SwapBuffers should not be issued within Begin/End. The two parameter bits of the SwapBuffers command are used for the following gxcommands (ie. not for the old gxcommands prior to SwapBuffers).
SwapBuffers does lock-up the 3D hardware if an incomplete polygon list has been defined (eg. a triangle with only 2 vertices). On lock-up, only 2D video is kept working, any wait-loops for GXSTAT.27 will hang the program. Once lock-up has occured, there seems to be no way to recover by software, not by sending the missing veric(es), and not even by pulsing POWCNT1.Bit2-3.

### 4000580h - Cmd 60h - VIEWPORT - Set Viewport (W)

```
+--------------------------------------------------------------------------------+
|       0-7   Screen/BG0 Coordinate X1 (0..255) (For Fullscreen: 0=Left-most)    |
|       8-15  Screen/BG0 Coordinate Y1 (0..191) (For Fullscreen: 0=Bottom-most)  |
|       16-23 Screen/BG0 Coordinate X2 (0..255) (For Fullscreen: 255=Right-most) |
|       24-31 Screen/BG0 Coordinate Y2 (0..191) (For Fullscreen: 191=Top-most)   |
+--------------------------------------------------------------------------------+
```

Coordinate 0,0 is the lower-left (unlike for 2D where it\'d be upper-left).
The 3D view-volume (size as defined by the Projection Matrix) is automatically scaled to match into the Viewport area. Although polygon vertices are clipped to the view-volume, some vertices may still exceed to X2,Y1 (lower-right) boundary by one pixel, due to some sort of rounding errors. The Viewport settings don\'t affect the size or position of the 3D Rear-Plane. Viewport should not be issued within Begin/End.

### 4000610h - DISP_1DOT_DEPTH - 1-Dot Polygon Display Boundary Depth (W)
1-Dot Polygons are very small, or very distant polygons, which would be rendered as a single pixel on screen. Polygons with a depth value greater (more distant) than DISP_1DOT_DEPTH can be automatically hidden; in order to reduce memory consumption, or to reduce dirt on the screen.

```
+--------------------------------------------------------------------------+
|       0-14  W-Coordinate (Unsigned, 12bit integer, 3bit fractional part) |
|       15-31 Not used                 (0000h=Closest, 7FFFh=Most Distant) |
+--------------------------------------------------------------------------+
```

The DISP_1DOT_DEPTH comparision can be enabled/disabled per polygon (via POLYGON_ATTR.Bit13), so \"important\" polygons can be displayed regardless of their size and distance.
Note: The comparision is always using the W-coordinate of the vertex (not the Z-coordinate) (ie. no matter if using Z-buffering, or W-buffering). The polygon is rendered if at least one of its vertices is having a w-coordinate less or equal than DISP_1DOT_DEPTH. NB. despite of checking the w-coords of ALL vertices, the polygon is rendered using the color/depth/texture of its FIRST vertex.
Note: The hardware does round-up the width and height of all polygons to at least 1, so polygons of 0x0, 1x0, 0x1, and 1x1 dots will be all rounded-up to a size of 1x1. Of which, the so-called \"1dot\" depth check is applied only to the 0x0 dot variant (so \"0dot\" depth check would be a better name for it).
Caution: Although DISP_1DOT_DEPTH is a Geometry Engine parameter, it is NOT routed through GXFIFO, ie. changes will take place immediately, and will affect all following polygons, including such that are still in GXFIFO. Workaround: ensure that GXFIFO is empty before changing this parameter.

### 4000340h - ALPHA_TEST_REF - Alpha-Test Comparision Value (W)
Alpha Test can be enabled in DISP3DCNT.Bit2. When enabled, pixels are rendered only if their Alpha value is GREATER than ALPHA_TEST_REF. Otherwise, when disabled, pixels are rendered only if their Alpha value is GREATER than zero. Alpha Test is performed on the final polygon pixels (ie. after texture blending).

```
+----------------------------------------------------------------------------------+
|       0-4   Alpha-Test Comparision Value (0..31) (Draw pixels if Alpha>AlphaRef) |
|       5-31  Not used                                                             |
+----------------------------------------------------------------------------------+
```

Value 00h is effectively the same as when Alpha Test is disabled. Value 1Fh hides all polygons, including opaque ones.



