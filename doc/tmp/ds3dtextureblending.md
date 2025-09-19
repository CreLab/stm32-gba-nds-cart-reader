# DS 3D Texture Blending


Polygon pixels consist of a Vertex Color, and of Texture Colors.
These colors can be blended as described below. Or, to use only either one:
To use only the Vertex Color: Select No Texture in TEXIMAGE_PARAM.
To use only the Texture Color: Select Modulation Mode and Alpha=31 in POLYGON_ATTR, and set COLOR to 7FFFh (white), or to gray values (to decrease brightness of the texture color).

### Vertex Color (Rv,Gv,Bv,Av)
The Vertex Color (Rv,Gv,Bv) can be changed per Vertex (either by Color, Normal, or Material0 command), pixels between vertices are shaded to medium values of the surrounding vertices. The Vertex Alpha (Av), can be changed only per polygon (by PolygonAttr command).

### Texture Colors (Rt,Gt,Bt,At)
The Texture Colors (Rt,Gt,Bt), and Alpha value (At), are defined by the Texture Bitmap. For formats without Alpha value, assume At=31 (solid), and for formats with 1bit Alpha assume At=A\*31.

### Shading Table Colors (Rs,Gs,Bs)
In Toon/Highlight Shading Mode, the red component of the Vertex Color (Rv) is mis-used as an index in the Shading Table, ie. Rv is used to read Shading Colors (Rs,Gs,Bs) from the table; the green and blue components of the Vertex Color (Gv,Bv) are unused in this mode. The Vertex Alpha (Av) is kept used.
Shading is used in Polygon Mode 2, whether it is Toon or Highlight Shading is selected in DISP3DCNT; this is a per-frame selection, so only either one can be used.

### Texture Blending - Modulation Mode (Polygon Attr Mode 0)

```
+-----------------------------------------------------------------------+
|       R = ((Rt+1)*(Rv+1)-1)/64                                        |
|       G = ((Gt+1)*(Gv+1)-1)/64                                        |
|       B = ((Bt+1)*(Bv+1)-1)/64                                        |
|       A = ((At+1)*(Av+1)-1)/64                                        |
+-----------------------------------------------------------------------+
```

The multiplication result is decreased intensity (unless both factors are 63).

### Texture Blending - Decal Mode (Polygon Attr Mode 1)

```
+-------------------------------------------------------------------------------+
|       R = (Rt*At + Rv*(63-At))/64  ;except, when At=0: R=Rv, when At=31: R=Rt |
|       G = (Gt*At + Gv*(63-At))/64  ;except, when At=0: G=Gv, when At=31: G=Gt |
|       B = (Bt*At + Bv*(63-At))/64  ;except, when At=0: B=Bv, when At=31: B=Bt |
|       A = Av                                                                  |
+-------------------------------------------------------------------------------+
```

The At value is used (only) as ratio for Texture color vs Vertex Color.

### Texture Blending - Toon Shading (Polygon Mode 2, DISP3DCNT=Toon)
The vertex color Red component (Rv) is used as an index in the toon table.

```
+-----------------------------------------------------------------------+
|       R = ((Rt+1)*(Rs+1)-1)/64   ;Rs=ToonTableRed[Rv]                 |
|       G = ((Gt+1)*(Gs+1)-1)/64   ;Gs=ToonTableGreen[Rv]               |
|       B = ((Bt+1)*(Bs+1)-1)/64   ;Bs=ToonTableBlue[Rv]                |
|       A = ((At+1)*(Av+1)-1)/64                                        |
+-----------------------------------------------------------------------+
```

This is same as Modulation Mode, but using Rs,Gs,Bs instead Rv,Gv,Bv.

### Texture Blending - Highlight Shading (Polygon Mode 2, DISP3DCNT=Highlight)

```
+-----------------------------------------------------------------------+
|       R = ((Rt+1)*(Rs+1)-1)/64+Rs ;truncated to MAX=63                |
|       G = ((Gt+1)*(Gs+1)-1)/64+Gs ;truncated to MAX=63                |
|       B = ((Bt+1)*(Bs+1)-1)/64+Bs ;truncated to MAX=63                |
|       A = ((At+1)*(Av+1)-1)/64                                        |
+-----------------------------------------------------------------------+
```

Same as Toon Shading, with additional addition offset, the addition may increase the intensity, however, it may also change the hue of the color.

Above formulas are for 6bit RGBA values, ie. 5bit values internally expanded to 6bit as such: IF X\>0 THEN X=X\*2+1.

### Uni-Colored Textures
Although textures are normally containing \"pictures\", in some cases it makes sense to use \"blank\" textures that are filled with a single color:
Wire-frame polygons are always having Av=31, however, they can be made transparent by using Translucent Textures (ie. A5I3 or A3I5 formats) with At\<31.
In Toon/Highlight shading modes, the Vertex Color is mis-used as table index, however, Toon/Highlight shading can be used on uni-colored textures, which is more or less the same as using Toon/Highlight shading on uni-colored Vertex-colors.



