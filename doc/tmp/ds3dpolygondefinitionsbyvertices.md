# DS 3D Polygon Definitions by Vertices


The DS supports polygons with 3 or 4 edges, triangles and quadliterals.
The position of the edges is defined by vertices, each consisting of (x,y,z) values.

For Line Segments, use Triangles with twice the same vertex, Line Segments are rendered always because they do not have any front and back sides.
The Prohibited Quad shapes may produce unintended results, namely, that are Quads with crossed sides, and quads with angles greater than 180 degrees.


```
+-----------------------------------------------------------------------+
|       Separate Tri.     Triangle Strips   Line Segment                |
|       v0                 v2___v4____v6                                |
|       |\      v3         /|\  |\    /\     v0    v1                   
|       | \     /\      v0( | \ | \  /  \     ------                    
|       |__\   /__\        \|__\|__\/____\         v2                   
|       v1 v2 v4  v5       v1   v3  v5   v7                             |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------+
|       Separate Quads          Quadliteral Strips         Prohibited Quads  |
|         v0__v3                 v0__v2____v4     v10__    v0__v3     v4     |
|          /  \   v4____v7        /  \     |\ _____ / /v11   \/       |\     
|         /    \   |    \        /    \    | |v6 v8| /       /\     v5| \    
|        /______\  |_____\      /______\___|_|_____|/       /__\     /___\   
|        v1    v2  v5    v6     v1    v3  v5 v7   v9       v2   v1   v6   v7 |
+----------------------------------------------------------------------------+
```


The vertices are normally arranged anti-clockwise, except that: in triangle-strips each second polygon uses clockwise arranged vertices, and quad-strips are sorts of \"up-down\" arranged (whereas \"up\" and \"down\" may be anywhere due to rotation). Other arrangements may result in quads with crossed lines, or may swap the front and back sides of the polygon (above examples are showing the front sides).

### 4000500h - Cmd 40h - BEGIN_VTXS - Start of Vertex List (W)

```
+-----------------------------------------------------------------------+
|       Parameter 1, Bit 0-1    Primitive Type (0..3, see below)        |
|       Parameter 1, Bit 2-31   Not used                                |
+-----------------------------------------------------------------------+
```

Indicates the Start of a Vertex List, and its Primitive Type:

```
+-----------------------------------------------------------------------+
|       0  Separate Triangle(s)    ;3*N vertices per N triangles        |
|       1  Separate Quadliteral(s) ;4*N vertices per N quads            |
|       2  Triangle Strips         ;3+(N-1) vertices per N triangles    |
|       3  Quadliteral Strips      ;4+(N-1)*2 vertices per N quads      |
+-----------------------------------------------------------------------+
```

The BEGIN_VTX command should be followed by VTX\_-commands to define the Vertices of the list, and should be then terminated by END_VTX command.
BEGIN_VTX additionally applies changes to POLYGON_ATTR.

### 4000504h - Cmd 41h - END_VTXS - End of Vertex List (W)
Parameters: None. This is a Dummy command for OpenGL compatibility. It should be used to terminate a BEGIN_VTX, VTX\_\<values\> sequence. END_VTXS is possibly required for Nintendo\'s software emulator? On real NDS consoles (and in no\$gba) it does have no effect, it can be left out, or can be issued multiple times inside of a vertex list, without disturbing the display.

### 400048Ch - Cmd 23h - VTX_16 - Set Vertex XYZ Coordinates (W)

```
+---------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-15   X-Coordinate (signed, with 12bit fractional part) |
|       Parameter 1, Bit 16-31  Y-Coordinate (signed, with 12bit fractional part) |
|       Parameter 2, Bit 0-15   Z-Coordinate (signed, with 12bit fractional part) |
|       Parameter 2, Bit 16-31  Not used                                          |
+---------------------------------------------------------------------------------+
```


### 4000490h - Cmd 24h - VTX_10 - Set Vertex XYZ Coordinates (W)

```
+--------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-9    X-Coordinate (signed, with 6bit fractional part) |
|       Parameter 1, Bit 10-19  Y-Coordinate (signed, with 6bit fractional part) |
|       Parameter 1, Bit 20-29  Z-Coordinate (signed, with 6bit fractional part) |
|       Parameter 1, Bit 30-31  Not used                                         |
+--------------------------------------------------------------------------------+
```

Same as VTX_16, with only one parameter, with smaller fractional part.

### 4000494h - Cmd 25h - VTX_XY - Set Vertex XY Coordinates (W)

```
+---------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-15   X-Coordinate (signed, with 12bit fractional part) |
|       Parameter 1, Bit 16-31  Y-Coordinate (signed, with 12bit fractional part) |
+---------------------------------------------------------------------------------+
```

The Z-Coordinate is kept unchanged, and re-uses the value from previous VTX.

### 4000498h - Cmd 26h - VTX_XZ - Set Vertex XZ Coordinates (W)

```
+---------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-15   X-Coordinate (signed, with 12bit fractional part) |
|       Parameter 1, Bit 16-31  Z-Coordinate (signed, with 12bit fractional part) |
+---------------------------------------------------------------------------------+
```

The Y-Coordinate is kept unchanged, and re-uses the value from previous VTX.

### 400049Ch - Cmd 27h - VTX_YZ - Set Vertex YZ Coordinates (W)

```
+---------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-15   Y-Coordinate (signed, with 12bit fractional part) |
|       Parameter 1, Bit 16-31  Z-Coordinate (signed, with 12bit fractional part) |
+---------------------------------------------------------------------------------+
```

The X-Coordinate is kept unchanged, and re-uses the value from previous VTX.

### 40004A0h - Cmd 28h - VTX_DIFF - Set Relative Vertex Coordinates (W)

```
+-----------------------------------------------------------------------------------+
|       Parameter 1, Bit 0-9    X-Difference (signed, with 9/12bit fractional part) |
|       Parameter 1, Bit 10-19  Y-Difference (signed, with 9/12bit fractional part) |
|       Parameter 1, Bit 20-29  Z-Difference (signed, with 9/12bit fractional part) |
|       Parameter 1, Bit 30-31  Not used                                            |
+-----------------------------------------------------------------------------------+
```

Sets XYZ-Coordinate relative to the XYZ-Coordinates from previous VTX. In detail: The 9bit fractional values are divided by 8 (sign expanded to 12bit fractions, in range +/-0.125), and that 12bit fraction is then added to the old vtx coordinates. The result of the addition should not overflow 16bit vertex coordinate range (1bit sign, 3bit integer, 12bit fraction).

### Notes on VTX commands
On each VTX command, the viewport coordinates of the vertex are calculated and stored in Vertex RAM,

```
+-----------------------------------------------------------------------+
|       ( xx, yy, zz, ww ) = ( x, y, z, 1.0 ) * ClipMatrix              |
+-----------------------------------------------------------------------+
```

The actual screen position (in pixels) is then,

```
+-----------------------------------------------------------------------+
|       screen_x = (xx+ww)*viewport_width / (2*ww) + viewport_x1        |
|       screen_y = (yy+ww)*viewport_height / (2*ww) + viewport_y1       |
+-----------------------------------------------------------------------+
```

Each VTX command that completes the definition of a polygon (ie. each 3rd for Separate Trangles) does additionally store data in Polygon List RAM.
VTX commands may be issued only between Begin and End commands.

### Clipping
Polygons are clipped to the 6 sides of the view volume (ie. to the left, right, top, bottom, near, and far edges). If one or more vertic(es) exceed one of these sides, then these vertic(es) are replaced by two newly created vertices (which are located on the intersections of the polygon edges and the view volume edge).
Depending on the number of clipped vertic(es), this may increase or decrease the number of entries in Vertex RAM (ie. minus N clipped vertices, plus 2 new vertices). Also, clipped polygons which are part of polygon strips are converted to separate polygons (which does increase number of entries in Vertex RAM). Polygons that are fully outside of the View Volume aren\'t stored in Vertex RAM, nor in Polygon RAM (the only exception are polygons that are located exactly one pixel below of, or right of lower/right edges, which appear to be accidently stored in memory).



