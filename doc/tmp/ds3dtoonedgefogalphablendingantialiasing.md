# DS 3D Toon, Edge, Fog, Alpha-Blending, Anti-Aliasing


### 4000380h..3BFh - TOON_TABLE - Toon Table (W)
This 64-byte region contains the 32 toon colors (16bit per color), used for both Toon and Highlight Shading. In both modes, the Red (R) component of the RGBA vertex color is mis-used as index to obtain the new RGB value from the toon table, vertex Alpha (A) is kept used as is.

```
+-----------------------------------------------------------------------+
|       Bit0-4: Red, Bit5-9: Green, Bit10-14: Blue, Bit15: Not Used     |
+-----------------------------------------------------------------------+
```

Shading can be enabled (per polygon) in Polygon_Attr, whether it is Toon or Highlight Shading is set (per frame) in DISP3DCNT. For more info on shading, see:
- [DS 3D Texture Blending](./ds3dtextureblending.md)

### 4000330h..33Fh - EDGE_COLOR - Edge Colors 0..7 (W)
This 16-byte region contains the 8 edge colors (16bit per color), Edge Color 0 is used for Polygon ID 00h..07h, Color 1 for ID 08h..0Fh, and so on.

```
+-----------------------------------------------------------------------+
|       Bit0-4: Red, Bit5-9: Green, Bit10-14: Blue, Bit15: Not Used     |
+-----------------------------------------------------------------------+
```

Edge Marking allows to mark the edges of an object (whose polygons all have the same ID) in a wire-frame style. Edge Marking can be enabled (per frame) in DISP3DCNT. When enabled, the polygon edges are drawn at the edge color, but only if the old ID value in the Attribute Buffer is different than the Polygon ID of the new polygon, so no edges are drawn between connected or overlapping polygons with same ID values.
Edge Marking is applied ONLY to opaque polygons (including wire-frames).
Edge Marking increases the size of opaque polygons (see notes below).
Edge Marking doesn\'t work very well with Anti-Aliasing (see Anti-Aliasing).
Technically, when rendering a polygon, it\'s edges (ie. the wire-frame region) are flagged as possible-edges (but it\'s still rendered normally, without using the edge-color). Once when all opaque polygons (\*) have been rendered, the edge color is applied to these flagged pixels, under following conditions: At least one of the four surrounding pixels (up, down, left, right) must have different polygon_id than the edge, and, the edge depth must be LESS than the depth of that surrounding pixel (ie. no edges are rendered if the depth is GREATER or EQUAL, even if the polygon_id differs). At the screen borders, edges seem to be rendered in respect to the rear-plane\'s polygon_id entry (see Port 4000350h).
(\*) Actually, edge-marking is reportedly performed not until all opaque AND translucent polygons have been rendered. That brings up some effects/problems when edges are covered by translucent polys: The edge-color is probably drawn as is (ie. it\'ll overwrite the translucent color, rather than being blended with the translucent color). And, any translucent polygons that do update the depth buffer will cause total edge-marking malfunction (since edge-marking involves the comparision of the current/surrounding pixel\'s depth values).

### 4000358h - FOG_COLOR - Fog Color (W)
Fog can be used to let more distant polygons to disappear in foggy grayness (or in darkness, or other color). This is particulary useful to \"hide\" the far clip plane. Fog can be enabled in DISP3DCNT.Bit7, moreover, when enabled, it can be activated or deactivated per polygon (POLYGON_ATTR.Bit15), and per Rear-plane (see there).

```
+-------------------------------------------------------------------------+
|       0-4    Fog Color, Red     ;\                                      
|       5-9    Fog Color, Green   ; used only when DISP3DCNT.Bit6 is zero |
|       10-14  Fog Color, Blue    ;/                                      |
|       15     Not used                                                   |
|       16-20  Fog Alpha          ;-used no matter of DISP3DCNT.Bit6      |
|       21-31  Not used                                                   |
+-------------------------------------------------------------------------+
```

Whether or not fog is applied to a pixel depends on the Fog flag in the framebuffer, the initial value of that flag can be defined in the rear-plane. When rendering opaque pixels, the framebuffer\'s fog flag gets replaced by PolygonAttr.Bit15. When rendering translucent pixels, the old flag in the framebuffer gets ANDed with PolygonAttr.Bit15.

### 400035Ch - FOG_OFFSET - Fog Depth Offset (W)

```
+-----------------------------------------------------------------------+
|       0-14   Fog Offset (Unsigned) (0..7FFFh)                         |
|       15-31  Not used                                                 |
+-----------------------------------------------------------------------+
```

FogDepthBoundary\[0..31\] (for FogDensity\[0..31\]) are defined as:

```
+---------------------------------------------------------------------------+
|       FogDepthBoundary[n] = FOG_OFFSET + FOG_STEP*(n+1)   ;with n = 0..31 |
+---------------------------------------------------------------------------+
```

Whereas FOG_STEP is derived from the FOG_SHIFT value in DISP3DCNT.Bit8-11 (FOG_STEP=400h shr FOG_SHIFT) (normally FOG_SHIFT should be 0..10 (bigger shift amounts of 11..15 would cause FOG_STEP to become zero, so only Density\[0\] and Density\[31\] would be used).
The meaning of the depth values depends on whether z-values or w-values are stored in the framebuffer (see SwapBuffers.Bit1).
For translucent polygons, the depth value (and therefore: the amount of fog) depends on the depth update bit (see PolygonAttr.Bit11).

### 4000360h..37Fh - FOG_TABLE - Fog Density Table (W)
This 32-byte region contains FogDensity\[0..31\] (used at FogDepthBoundary\[n\]),

```
+------------------------------------------------------------------------------+
|       0-6    Fog Density (00h..7Fh = None..Full) (usually increasing values) |
|       7      Not used                                                        |
+------------------------------------------------------------------------------+
```

FogDensity\[0\] is used for all pixels closer than FogDepthBoundary\[0\], FogDensity\[31\] is used for all pixels more distant than FogDepthBoundary\[0\].
Density is linear interpolated for pixels that are between two Density depth boundaries. The formula for Fog Blending is:

```
+-----------------------------------------------------------------------------------+
|       FrameBuffer[R] = (FogColor[R]*Density + FrameBuffer[R]*(128-Density)) / 128 |
|       FrameBuffer[G] = (FogColor[G]*Density + FrameBuffer[G]*(128-Density)) / 128 |
|       FrameBuffer[B] = (FogColor[B]*Density + FrameBuffer[B]*(128-Density)) / 128 |
|       FrameBuffer[A] = (FogColor[A]*Density + FrameBuffer[A]*(128-Density)) / 128 |
+-----------------------------------------------------------------------------------+
```

If DISP3DCNT.Bit6 is set (=Alpha Only), then only FrameBuffer\[A\] is updated, and FrameBuffer\[RGB\] are kepth unchanged. Density=127 is handled as if Density=128.
Fog Glitch: The fog_alpha value appears to be ignored (treated as fog_alpha=1Fh) in the region up to the first density boundary. However, normally that value will be multiplied by zero (assumung that density\[0\] is usually zero), so you won\'t ever notice that hardware glitch.

### Alpha-Blending (Polygon vs FrameBuffer)
Alpha-Blending occurs for pixels of translucent polygons,

```
+----------------------------------------------------------------------------+
|       FrameBuf[R] = (Poly[R]*(Poly[A]+1) + FrameBuf[R]*(31-(Poly[A])) / 32 |
|       FrameBuf[G] = (Poly[G]*(Poly[A]+1) + FrameBuf[G]*(31-(Poly[A])) / 32 |
|       FrameBuf[B] = (Poly[B]*(Poly[A]+1) + FrameBuf[B]*(31-(Poly[A])) / 32 |
|       FrameBuf[A] = max(Poly[A],FrameBuf[A])                               |
+----------------------------------------------------------------------------+
```

There are three situations in which Alpha-Blending is bypassed (the old Framebuf\[R,G,B,A\] value is then simply overwritten by Poly\[R,G,B,A\]):

```
+------------------------------------------------------------------------------+
|       1) Alpha-Blending is disabled                       (DISP3DCNT.Bit3=0) |
|       2) The polygon pixel is opaque                      (Poly[A]=31)       |
|       3) The old framebuffer value is totally transparent (FrameBuf[A]=0)    |
+------------------------------------------------------------------------------+
```

The third case can happen if the rear-plane was initialized with Alpha=0, which causes the polygon not to be blended with the rear-plane (which may give better results when subsequently blending the 3D layer with the 2D engine).
Note: Totally transparent pixels (with Poly\[A\]=0) are not rendered (ie. neither FrameBuf\[R,G,B,A\] nor FrameBuf\[Depth,Fog,PolyID,etc.\] are updated.

### Anti-Aliasing
Anti-Aliasing can be enabled in DISP3DCNT, when enabled, the edges of opaque polygons will be anti-aliased (ie. the pixels at the edges may become translucent).
Anti-Aliasing is not applied on translucent polygons. And, Anti-Aliasing is not applied on the interiors of the poylgons (eg. an 8x8 chessboard texture will be anti-aliased only at the board edges, not at the edges of the 64 fields).
Anti-Aliasing is (accidently) applied to opaque 1dot polygongs, line-segments and wire-frames (which results in dirty lines with missing pixels, 1dot polys become totally invisible), workaround is to use translucent dots, lines and wires (eg. with alpha=30).
Anti-Aliasing is (correctly) not applied to edges of Edge-Marked polygons, in that special case even opaque line-segments and wire-frames are working even if anti-aliasing is enabled (provided that they are edge-marked, ie. if their polygon ID differs from the framebuffer\'s ID).
Anti-Aliasing is (accidently) making the edges of Edge-Marked polygons translucent (with alpha=16 or so?), that reduces the contrast of the edge colors. Moreover, if two of these translucent edges do overlap, then they are blended twice (even if they have the same polygon_id, and even if the depth_update bit in polygon_attr is set; both should normally prevent double-blending), that scatters the brightness of such edges.

### Polygon Size
In some cases, the NDS hardware doesn\'t render the lower/right edges of certain polygons. That feature reduces rendering load, and, when rendering connected polygons (eg. strips), then it\'d be unnecessary to render that edges (since they\'d overlap with the upper/left edges of the other polygon). On the contrary, if there\'s no connected polygon displayed, then the polygon may appear smaller than expected. Small polygons with excluded edges are:

```
+------------------------------------------------------------------------------------+
|       Opaque polygons (except wire-frames) without Edge-Marking and Anti-Aliasing, |
|       and, all polygons with vertical right-edges (except line-segments).          |
|       Plus, Translucent Polys when Alpha-Blending is disabled in DISP3DCNT.Bit3.   |
+------------------------------------------------------------------------------------+
```

All other polygons are rendered at full size with all edges included (except vertical right edges). Note: To disable the small-polygon feature, you can enable edge-marking (which does increase the polygon size, even if no edges are drawn, ie. even if all polys do have the same ID).



