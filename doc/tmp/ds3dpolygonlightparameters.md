# DS 3D Polygon Light Parameters


The lighting operation is performed by executing the Normal command (which sets the VertexColor based on the Light/Material parameters) (to the rest of the hardware it doesn\'t matter if the VertexColor was set by Color command or by Normal command). Light is calculated only for the Front side of the polygon (assuming that the Normal is matched to that side), so the Back side will be (incorrectly) using the same color.

### 40004C8h - Cmd 32h - LIGHT_VECTOR - Set Light\'s Directional Vector (W)
Sets direction of the specified light (ie. the light selected in Bit30-31).

```
+---------------------------------------------------------------------------------+
|       0-9   Directional Vector's X component (1bit sign + 9bit fractional part) |
|       10-19 Directional Vector's Y component (1bit sign + 9bit fractional part) |
|       20-29 Directional Vector's Z component (1bit sign + 9bit fractional part) |
|       30-31 Light Number                     (0..3)                             |
+---------------------------------------------------------------------------------+
```

Upon executing this command, the incoming vector is multiplied by the current Directional Matrix, the result is then applied as LightVector. This allows to rotate the light direction. However, normally, to keep the light unrotated, be sure to use LoadIdentity (in MtxMode=2) before setting the LightVector.

### 40004CCh - Cmd 33h - LIGHT_COLOR - Set Light Color (W)
Sets the color of the specified light (ie. the light selected in Bit30-31).

```
+---------------------------------------------------------------------------------+
|       0-4   Red          (0..1Fh)      ;\light color this will be combined with 
|       5-9   Green        (0..1Fh)      ; diffuse, specular, and ambient colors  |
|       10-14 Blue         (0..1Fh)      ;/upon execution of the normal command   |
|       15-29 Not used                                                            |
|       30-31 Light Number (0..3)                                                 |
+---------------------------------------------------------------------------------+
```


### 40004C0h - Cmd 30h - DIF_AMB - MaterialColor0 - Diffuse/Ambient Reflect. (W)

```
+-------------------------------------------------------------------------------------+
|       0-4   Diffuse Reflection Red     ;\light(s) that directly hits the polygon,   
|       5-9   Diffuse Reflection Green   ; ie. max when NormalVector has opposite     |
|       10-14 Diffuse Reflection Blue    ;/direction of LightVector                   |
|       15    Set Vertex Color (0=No, 1=Set Diffuse Reflection Color as Vertex Color) |
|       16-20 Ambient Reflection Red     ;\light(s) that indirectly hits the polygon, 
|       21-25 Ambient Reflection Green   ; ie. assuming that light is reflected by    |
|       26-30 Ambient Reflection Blue    ;/walls/floor, regardless of LightVector     |
|       31    Not used                                                                |
+-------------------------------------------------------------------------------------+
```

With Bit15 set, the lower 15bits are applied as VertexColor (exactly as when when executing the Color command), the purpose is to use it as default color (eg. when outcommenting the Normal command), normally, when using lighting, the color setting gets overwritten (as soon as executing the Normal command).

### 40004C4h - Cmd 31h - SPE_EMI - MaterialColor1 - Specular Ref. & Emission (W)

```
+------------------------------------------------------------------------------------+
|       0-4   Specular Reflection Red    ;\light(s) reflected towards the camera,    
|       5-9   Specular Reflection Green  ; ie. max when NormalVector is in middle of |
|       10-14 Specular Reflection Blue   ;/LightVector and ViewDirection             |
|       15    Specular Reflection Shininess Table (0=Disable, 1=Enable)              |
|       16-20 Emission Red               ;\light emitted by the polygon itself,      
|       21-25 Emission Green             ; ie. regardless of light colors/vectors,   |
|       26-30 Emission Blue              ;/and no matter if any lights are enabled   |
|       31    Not used                                                               |
+------------------------------------------------------------------------------------+
```

Caution: Specular Reflection WON\'T WORK when the ProjectionMatrix is rotated.

### 40004D0h - Cmd 34h - SHININESS - Specular Reflection Shininess Table (W)
Write 32 parameter words (each 32bit word containing four 8bit entries), entries 0..3 in the first word, through entries 124..127 in the last word:

```
+------------------------------------------------------------------------------------+
|       0-7   Shininess 0 (unsigned fixed-point, 0bit integer, 8bit fractional part) |
|       8-15  Shininess 1 ("")                                                       |
|       16-23 Shininess 2 ("")                                                       |
|       24-31 Shininess 3 ("")                                                       |
+------------------------------------------------------------------------------------+
```

If the table is disabled (by MaterialColor1.Bit15), then reflection will act as if the table would be filled with linear increasing numbers.

### 4000484h - Cmd 21h - NORMAL - Set Normal Vector (W)
In short, this command does calculate the VertexColor, based on the various light-parameters.
In detail, upon executing this command, the incoming vector is multiplied by the current Directional Matrix, the result is then applied as NormalVector (giving it the same rotation as used for the following polygon vertices).

```
+-----------------------------------------------------------------------------+
|       0-9   X-Component of Normal Vector (1bit sign + 9bit fractional part) |
|       10-19 Y-Component of Normal Vector (1bit sign + 9bit fractional part) |
|       20-29 Z-Component of Normal Vector (1bit sign + 9bit fractional part) |
|       30-31 Not used                                                        |
+-----------------------------------------------------------------------------+
```

Defines the Polygon\'s Normal. And, does then update the Vertex Color; by recursing the View Direction, the NormalVector, the LightVector(s), and Light/Material Colors. The execution time of the Normal command varies depending on the number of enabled light(s).

### Additional Light Registers
Additionally to above registers, light(s) must be enabled in PolygonAttr (mind that changes to PolygonAttr aren\'t applied until next Begin command). And, the Directional Matrix must be set up correctly (in MtxMode=2) for the LightVector and NormalVector commands.

### Normal Vector
The Normal vector must point \"away from the polygon surface\" (eg. for the floor, the Normal should point upwards). That direction is implied by the polygon vertices, however, the hardware cannot automatically calculate it, so it must be set manually with the Normal command (prior to the VTX-commands).
When using lighting, the Normal command must be re-executed after switching Lighting on/off, or after changing light/material parameters. And, of course, also before defining polygons with different orientation. Polygons with same orientation (eg. horizontal polygon surfaces) and same material color can use the same Normal. Changing the Normal per polygon gives differently colored polygons with flat surfaces, changing the Normal per vertex gives the illusion of curved surfaces.

### Light Vector
Each light consists of parallel beams; similar to sunlight, which appears to us (due to the great distance) to consist of parallel beams, all emmitted into the same direction; towards Earth.
In reality, light is emitted into ALL directions, originated from the light source (eg. a candle), the hardware doesn\'t support that type of non-parallel light. However, the light vectors can be changed per polygon, so a polygon that is located north of the light source may use different light direction than a polygon that is east of the light source.
And, of course, Light 0..3 may (and should) have different directions.

### Normalized Vectors
The Normal Vector and the Light Vectors should be normalized (ie. their length should be 1.0) (in practice: something like 0.99, since the registers have only fractional parts) (a length of 1.0 can cause overflows).

### Lighting Limitations
The functionality of the light feature is limited to reflecting light to the camera (light is not reflected to other polygons, nor does it cast shadows on other polygons). However, independently of the lighting feature, the DS hardware does allow to create shadows, see:
- [DS 3D Shadow Polygons](./ds3dshadowpolygons.md)

### Internal Operation on Normal Command

```
+-----------------------------------------------------------------------------------+
|       IF TexCoordTransformMode=2 THEN TexCoord=NormalVector*Matrix (see TexCoord) |
|       NormalVector=NormalVector*DirectionalMatrix                                 |
|       VertexColor = EmissionColor                                                 |
|       FOR i=0 to 3                                                                |
|        IF PolygonAttrLight[i]=enabled THEN                                        |
|         DiffuseLevel = max(0,-(LightVector[i]*NormalVector))                      |
|         ShininessLevel = max(0,(-HalfVector[i])*(NormalVector))^2                 |
|         IF TableEnabled THEN ShininessLevel = ShininessTable[ShininessLevel]      |
|         ;note: below processed separately for the R,G,B color components...       |
|         VertexColor = VertexColor + SpecularColor*LightColor[i]*ShininessLevel    |
|         VertexColor = VertexColor + DiffuseColor*LightColor[i]*DiffuseLevel       |
|         VertexColor = VertexColor + AmbientColor*LightColor[i]                    |
|        ENDIF                                                                      |
|       NEXT i                                                                      |
+-----------------------------------------------------------------------------------+
```


### Internal Operation on Light_Vector Command (for Light i)

```
+-----------------------------------------------------------------------+
|       LightVector[i] = (LightVector*DirectionalMatrix)                |
|       HalfVector[i] = (LightVector[i]+LineOfSightVector)/2            |
+-----------------------------------------------------------------------+
```


### LineOfSightVector (how it SHOULD work)
Ideally, the LineOfSightVector should point from the camera to the vertic(es), however, the vertic(es) are still unknown at time of normal command, so it is just pointing from the camera to the screen, ie.

```
+-----------------------------------------------------------------------+
|       LineOfSightVector = (0,0,-1.0)                                  |
+-----------------------------------------------------------------------+
```

Moreover, the LineOfSightVector should be multiplied by the Projection Matrix (so the vector would get rotated accordingly when the camera gets rotated), and, after multiplication by a scaled matrix, it\'d be required to normalize the resulting vector.

### LineOfSightVector (how it DOES actually work)
However, the NDS cannot normalize vectors by hardware, and therefore, it does completely leave out the LineOfSightVector\*ProjectionMatrix multiplication. So, the LineOfSightVector is always (0,0,-1.0), no matter of any camera rotation. That means,

```
+-------------------------------------------------------------------------------+
|       Specular Reflection WON'T WORK when the ProjectionMatrix is rotated (!) |
+-------------------------------------------------------------------------------+
```

So, if you want to rotate the \"camera\" (in MTX_MODE=0), then you must instead rotate the \"world\" in the opposite direction (in MTX_MODE=2).
That problem applies only to Specular Reflection, ie. only if Lighting is used, and only if the Specular Material Color is nonzero.

### Maths Notes
Note on Vector\*Vector multiplication: Processed as LineVector\*RowVector, so the result is a number (aka scalar) (aka a matrix with only 1x1 elements), multiplying two (normalized) vectors results in: \"cos(angle)=vec1\*vec2\", ie. the cosine of the angle between the two vectors.
The various Normal/Light/Half/Sight vectors are only 3-dimensional (x,y,z), ie. only the upper-left 3x3 matrix elements are used on multiplications with the 4x4 DirectionalMatrix.



