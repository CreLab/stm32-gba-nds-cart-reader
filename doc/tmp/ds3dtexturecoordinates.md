# DS 3D Texture Coordinates


For textured polygons, a texture coordinate must be associated with each vertex of the polygon. The coordinates (S,T) are defined by TEXCOORD command (typically issued prior to each VTX command), and can be optionally automatically transformed, by the Transformation Mode selected in TEXIMAGE_PARAM register.

### Texture Matrix
Although the texture matrix is 4x4, with values m\[0..15\], only the left two columns of this matrix are actually used. In Mode 2 and 3, the bottom row of the matrix is replaced by S and T values from most recent TEXCOORD command.

### Texture Coordinates Transformation Mode 0 - No Transform
The values are set upon executing the TEXCOORD command,

```
+-----------------------------------------------------------------------+
|       ( S' T' )  =  ( S  T )                                          |
+-----------------------------------------------------------------------+
```

Simple coordinate association, without using the Texture Matrix at all.

### Texture Coordinates Transformation Mode 1 - TexCoord source
The values are calculated upon executing the TEXCOORD command,

```
+-----------------------------------------------------------------------+
|                                          | m[0]  m[1]  |              |
|       ( S' T' )  =  ( S  T 1/16 1/16 ) * | m[4]  m[5]  |              |
|                                          | m[8]  m[9]  |              |
|                                          | m[12] m[13] |              |
+-----------------------------------------------------------------------+
```

Can be used to produce a simple texture scrolling, rotation, or scaling, by setting a translate, rotate, or scale matrix for the texture matrix.

### Texture Coordinates Transformation Mode 2 - Normal source
The values are calculated upon executing the NORMAL command,

```
+-----------------------------------------------------------------------+
|                                          | m[0]  m[1]  |              |
|       ( S' T' )  =  ( Nx  Ny  Nz 1.0 ) * | m[4]  m[5]  |              |
|                                          | m[8]  m[9]  |              |
|                                          | S     T     |              |
+-----------------------------------------------------------------------+
```

Can be used to produce spherical reflection mapping by setting the texture matrix to the current directional vector matrix, multiplied by a scaling matrix that expands the directional vector space from -1.0..+1.0 to one half of the texture size. For that purpose, translate the origin of the texture coordinate to the center of the spherical texture by using TexCoord command (spherical texture means a bitmap that contains some circle-shaped image).

### Texture Coordinates Transformation Mode 3 - Vertex source
The values are calculated upon executing any VTX commands,

```
+-----------------------------------------------------------------------+
|                                          | m[0]  m[1]  |              |
|       ( S' T' )  =  ( Vx  Vy  Vz 1.0 ) * | m[4]  m[5]  |              |
|                                          | m[8]  m[9]  |              |
|                                          | S     T     |              |
+-----------------------------------------------------------------------+
```

Can be used to produce texture scrolls dependent on the View coordinates by copying the current position coordinate matrix into the texture matrix. For example, the PositionMatrix can be obtained via CLIPMTX_RESULT (see there for details), and that values can be then manually copied to the TextureMatrix.

### Sign+Integer+Fractional Parts used in above Formulas

```
+----------------------------------------------------------------------------+
|       Matrix    m[..]     1+19+12 (32bit)                                  |
|       Vertex    Vx,Vy,Vz  1+3+12  (16bit)                                  |
|       Normal    Nx,Ny,Nz  1+0+9   (10bit)                                  |
|       Constant  1.0       0+1+0   (1bit)                                   |
|       Constant  1/16      0+0+4   (4bit)                                   |
|       TexCoord  S,T       1+11+4  (16bit)                                  |
|       Result    S',T'     1+11+4  (16bit) <-------- clipped to that size ! |
+----------------------------------------------------------------------------+
```

Observe that the S\',T\' values are clipped to 16bit size. Ie. after the Vector\*Matrix calaction, the result is shifted right (to make it having a 4bit fraction), and the value is then masked to 16bit size.



