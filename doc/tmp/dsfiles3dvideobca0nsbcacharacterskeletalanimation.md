# DS Files - 3D Video BCA0 (.NSBCA Character Skeletal Animation)


An Animation is a skeletal animation of a Model. It changes the values of the BoneMatrices in a Model over time. All animations are frame-based, so \"time\" always means \"frame number\".

An Animation contains a collection of Tracks. A Track targets one of the BoneMatrices in a Model and tells you what its value should be at each time.

### BCA0 Header (in .NSBCA files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BCA0" (Basic Character Animation)                 |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (1)                                           |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=JNT0)                             |
|       010h 4     Offset from BCA0 to JNT0 Chunk                        |
+------------------------------------------------------------------------+
```


### JNT0 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "JNT0" (Joint Block)                        |
|       004h 4     Chunk Size                                           |
|       008h ..    Joint Dict (with 32bit offsets from JNT0 to J.AC)    |
+-----------------------------------------------------------------------+
```


### Joint Animations

```
+--------------------------------------------------------------------------------+
|       000h 4    ID "J",00h,"AC" (nicknamed "J.AC") (Joint Animation Content ?) |
|       004h 2    Number of Frames                                               |
|       006h 2    Number of Tracks (T)                                           |
|       008h 4    Unknown (3)                                                    |
|       00Ch 4    Offset from J.AC to PivotMatrices                              |
|       010h 4    Offset from J.AC to BasisMatrices                              |
|       014h 2*T  Offsets from J.AC to AnimationTrack(s)                         |
|       ...  ..   Padding to 4-byte boundary (if needed)                         |
|       ...  ..   AnimationTrack(s)                                              |
|       ...  ..   PivotMatrices (06h-bytes each)   ;\used for Rotations          
|       ...  ..   BasisMatrices (0Ah-bytes each)   ;/(see "Curve" entries)       |
+--------------------------------------------------------------------------------+
```


### AnimationTrack

```
+-----------------------------------------------------------------------------------+
|       000h 2    Flags (eg. 3028h)                                                 |
|                   0     No Channel                                                |
|                   1-2   No Translation channels    ;why 2bit?                     |
|                   3     Translation X is constant                                 |
|                   4     Translation Y is constant                                 |
|                   5     Translation Z is constant                                 |
|                   6-7   No Rotation channel        ;why 2bit?                     |
|                   8     Rotation is constant                                      |
|                   9-10  No Scale channels          ;why 2bit?                     |
|                   11    Scale X is constant                                       |
|                   12    Scale Y is constant                                       |
|                   13    Scale Z is constant                                       |
|                   14-15 Unknown (0) (unused?)                                     |
|       002h 1    Dummy (00h)                                                       |
|       003h 1    target_index (the index of the BoneMatrix this track targets?)    |
|       ...  ..   Curve, Translation X   ;\                                         
|       ...  ..   Curve, Translation Y   ; only if Flags.bit0=0 and Flags.bit1-2=0  |
|       ...  ..   Curve, Translation Z   ;/                                         |
|       ...  ..   Curve, Rotation        ;-only if Flags.bit0=0 and Flags.bit6-7=0  |
|       ...  ..   Curve, Scale X         ;\                                         
|       ...  ..   Curve, Scale Y         ; only if Flags.bit0=0 and Flags.bit9-10=0 |
|       ...  ..   Curve, Scale Z         ;/                                         |
+-----------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ___________________________________ Curves ___________________________________ |
+-------------------------------------------------------------------------------------+
```


### Curve
The format of the Curve entries varies for Translation, Rotation, Scaling, and depends on whether the above Flags entry has Constant=1 (ie. using the same value for all frames).

```
+---------------------------------------------------------------------------------+
|       When Constant=1 and Translation X/Y/Z:                                    |
|         000h 4  Translation value (fixed point, 1.19.12)                        |
|       When Constant=1 and Rotation:                                             |
|         000h 2  Matrix Index/Type (bit0-14=Index, bit15=Type: 0=Basis, 1=Pivot) |
|         002h 2  Unused            (padding for alignment, probably)             |
|       When Constant=1 and Scaling X/Y/Z:                                        |
|         000h 4  Scaling Value     (fixed point, 1.19.12)                        |
|         004h 4  Unknown           (fixed point, 1.19.12)                        |
|       When Constant=0:                                                          |
|         000h 4  Frame Info                                                      |
|                   bit0-15   Start_frame (start on this frame, step=samplerate)  |
|                   bit16-27  End_frame   (up to excluding this frame)            |
|                   bit28-29  Width for Scale/Translate (0=32bit, 1=16bit)        |
|                   bit30-31  Samplerate (0,1,2,3 = Each 1,2,4,8 frames)          |
|         004h 4  Offset from J.AC to SampledCurve                                |
+---------------------------------------------------------------------------------+
```


### SampledCurve (when Constant=0)
A sampled curve is always sampled at a fixed rate between two endpoints: one sample is stored at each of the frames

```
+---------------------------------------------------------------------------------+
|         num_samples=(end_frame-start_frame)/samplerate                          |
|       When Translation X/Y/Z, and Width=0:                                      |
|         000h 4  Sample            (fixed point, 1.19.12)                        |
|       When Translation X/Y/Z, and Width=1:                                      |
|         000h 2  Sample            (fixed point, 1.3.12)                         |
|       When Rotation:                                                            |
|         000h 2  Matrix Index/Type (bit0-14=Index, bit15=Type: 0=Basis, 1=Pivot) |
|       Whan Scaling X/Y/Z, and Width=0:                                          |
|         000h 4  Sample            (fixed point, 1.19.12)                        |
|         004h 4  Unknown           (fixed point, 1.19.12)                        |
|       Whan Scaling X/Y/Z, and Width=1:                                          |
|         000h 2  Sample            (fixed point, 1.3.12)                         |
|         002h 2  Unknown           (fixed point, 1.3.12)                         |
+---------------------------------------------------------------------------------+
```

The rotation Matrix Index/Type points to a rotation matrix stored in the PivotMatrices or BasisMatrices arrays for this Animation. The highest bit tells you which array it\'s in, and the low bits give the index into that array.


```
+-------------------------------------------------------------------------------------+
|      ________________________________ PivotMatrix _________________________________ |
+-------------------------------------------------------------------------------------+
```


A PivotMatrix encodes a rotation matrix for X, Y, or Z-axis in 6 bytes.

```
+------------------------------------------------------------------------------------+
|       000h 2  Flags (bit0-3=Form, bit4=NegI, bit5=NegC, bit6=NegD, bit7-15=Unused) |
|       002h 2  Value A (fixed point, 1.3.12)   ;\usually cos/sin values             
|       003h 2  Value B (fixed point, 1.3.12)   ;/                                   |
+------------------------------------------------------------------------------------+
```

To get the whole matrix, set C=A, D=B, I=1.0, negate them if NegC, NegD, NegI are set, then arrange A,B,C,D,I depending on the Form bits:

```
+-----------------------------------------------------------------------+
|               [ i 0 0 ]            [ 0 a c ]            [ 0 a c ]     |
|       Form0 = [ 0 a c ]    Form1 = [ i 0 0 ]    Form2 = [ 0 b d ]     |
|       (X)     [ 0 b d ]            [ 0 b d ]            [ i 0 0 ]     |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|               [ 0 i 0 ]            [ a 0 c ]            [ a 0 c ]     |
|       Form3 = [ a 0 c ]    Form4 = [ 0 i 0 ]    Form5 = [ b 0 d ]     |
|               [ b 0 d ]    (Y)     [ b 0 d ]            [ 0 i 0 ]     |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|               [ 0 0 i ]            [ a c 0 ]            [ a c 0 ]     |
|       Form6 = [ a c 0 ]    Form7 = [ 0 0 i ]    Form8 = [ b d 0 ]     |
|               [ b d 0 ]            [ b d 0 ]    (Z)     [ 0 0 i ]     |
+-----------------------------------------------------------------------+
```

XXX shouldn\'t that use C=B and D=A for usual sine/cosine rotations?
XXX or does that have rows/columns swapped, to match gbatek notation?
XXX what is the practical use of nine formats? three are for x/y/z axis\...
XXX what is the default for NegC, NegD, NegI


```
+-------------------------------------------------------------------------------------+
|      ________________________________ BasisMatrix _________________________________ |
+-------------------------------------------------------------------------------------+
```


A BasisMatrix encodes an arbitrary rotation matrix as six 13bit fixed point 1.0.12 values in 10 bytes.

```
+--------------------------------------------------------------------------+
|       000h 2  bit3-15=a0.bit0-12, and bit0-2=b2.bit9-11                  |
|       002h 2  bit3-15=a1.bit0-12, and bit0-2=b2.bit6-8                   |
|       004h 2  bit3-15=a2.bit0-12, and bit0-2=b2.bit3-5                   |
|       006h 2  bit3-15=b0.bit0-12, and bit0-2=b2.bit0-2                   |
|       008h 2  bit3-15=b1.bit0-12, and bit0=b2.bit12, and bit1-2=unknown? |
+--------------------------------------------------------------------------+
```

The remaining three matrix elements are computed as:

```
+-----------------------------------------------------------------------+
|       (c0,c1,c2) = (a0,a1,a2) x (b0,b1,b2)  ;cross product            |
+-----------------------------------------------------------------------+
```

And the rotation matrix is then:

```
+-----------------------------------------------------------------------+
|       [ a0  b0  c0 ]                                                  |
|       [ a1  b1  c1 ]                                                  |
|       [ a2  b2  c2 ]                                                  |
+-----------------------------------------------------------------------+
```

XXX or does that have rows/columns swapped, to match gbatek notation?



