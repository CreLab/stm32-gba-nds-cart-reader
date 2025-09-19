# DS Files - 3D Video BMD0 (.NSBMD Model Data)


### BMD0 Header (in .NSBMD files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BMD0" (Basic Model Data)                          |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (2) (unknown if version 1 did also exist)     |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=MDL0 or 2=MDL0+TEX0)              |
|       010h 4     Offset from BMD0 to MDL0 Chunk                        |
|       014h 4     Offset from BMD0 to TEX0 Chunk (if any)               |
+------------------------------------------------------------------------+
```


### TEX0 Chunk (if any)
Same as in BTX0 files, see there for details.
- [DS Files - 3D Video BTX0 (.NSBTX Texture Data)](./dsfiles3dvideobtx0nsbtxtexturedata.md)

### MDL0 Chunk

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "MDL0" (Model Block)                        |
|       004h 4     Chunk Size                                           |
|       008h ..    Model Dict (with 32bit offsets from MDL0 to Models)  |
|       ...  ..    Models                                               |
+-----------------------------------------------------------------------+
```


### Model
A Model is 3D model. The process of drawing a Model consists of executing a list of RenderCommands, which calculate skinning matrices, set material properties, and draw the individual pieces of the Model (the Meshes).

```
+-------------------------------------------------------------------------------------+
|       000h 4   Size of Model in bytes                                               |
|       004h 4   Offset from Model to RenderCommandList                               |
|       008h 4   Offset from Model to Material info                                   |
|       00Ch 4   Offset from Model to Dict for Meshes                                 |
|       010h 4   Offset from Model to InvBindMatrices                                 |
|       014h 1   Unknown (00h)                                                        |
|       015h 1   Unknown (00h or 01h)                                                 |
|       016h 1   Unknown (00h)                                                        |
|       017h 1   Number of BoneMatrices                                               |
|       018h 1   Number of Materials                                                  |
|       019h 1   Number of Meshes                                                     |
|       01Ah 2   Unknown (can be ZERO, or same as Number of BoneMatrices?)            |
|       01Ch 4   Scaling Factor for Up Scale command   (fixed point, 1.19.12)         |
|       020h 4   Scaling Factor for Down Scale command (fixed point, 1.19.12)         |
|       024h 2   Number of Vertices                                                   |
|       026h 2   Number of Polygons (Triangles+Quads)                                 |
|       028h 2   Number of Triangles                                                  |
|       02Ah 2   Number of Quads                                                      |
|       02Ch 2   Bounding Box X-Coordinate   (fixed point, 1.3.12) ;\                 
|       02Eh 2   Bounding Box Y-Coordinate   (fixed point, 1.3.12) ;                  |
|       030h 2   Bounding Box Z-Coordinate   (fixed point, 1.3.12) ; for BOX_TEST     |
|       032h 2   Bounding Box X-Size, Width  (fixed point, 1.3.12) ; command          |
|       034h 2   Bounding Box Y-Size, Height (fixed point, 1.3.12) ;                  |
|       036h 2   Bounding Box T-Size, Depth  (fixed point, 1.3.12) ;/                 |
|       038h 4   Unknown (1000h)  ;\maybe fixed point value 1.0 ?                     
|       03Ch 4   Unknown (1000h)  ;/                                                  |
|       040h ..  Dict for BoneMatrices (with 32bit offsets from 040h to BoneMatrices) |
|       [04h]   .. RenderCommandList                                                  |
|       [08h]+0 2  Offset from [08h] to Dict for Material-to-Texture Pairings      ;\ 
|       [08h]+2 2  Offset from [08h] to Dict for Material-to-Palette Pairings      ;  |
|       [08h]+4 .. Dict for Materials (with 32bit offsets from [08h] to Materials) ;  |
|       ...     .. Dict for Material-to-Texture Pairings (with 4-byte entries)     ;  |
|       ...     .. Dict for Material-to-Palette Pairings (with 4-byte entries)     ;/ |
|       [0Ch]   .. Dict for Meshes    (with 32bit offsets from [0Ch] to VertexMeshes) |
|       [10h]   .. InvBindMatrices (54h-byte each)                                    |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _____________________________ RenderCommandList ______________________________ |
+-------------------------------------------------------------------------------------+
```


### RenderCommandList
The RenderCommandList is a software script for drawing the Model. The list consists of command bytes and parameter bytes, the list is terminated by command 01h.
The commands must be processed by software (they aren\'t GPU commands). Apart from the commands bytes, the upper 3bit of the command number do contain some parameter bits that affect the behaviour of the command.

```
+-------------------------------------------------------------------------------------+
|       Cmd  Params Description                                                       |
|       00h  0      Nop (no operation?)                                               |
|       40h  0      Nop (same as above?)                                              |
|       80h  0      Nop (same as above?)                                              |
|       01h  0      End of RenderCommandList                                          |
|       02h  2      Unknown   ;reportedly, params: Node ID, Visibility                |
|       03h  1      Load Matrix from Stack (param=StackIndex)                         |
|       04h  1      Bind Material for subsequent Draw command (param=MaterialIndex)   |
|       24h  1      Bind Material (same as above?)                                    |
|       44h  1      Bind Material (same as above?)                                    |
|       05h  1      Draw VertexMesh (param=VertexMeshIndex)                           |
|       06h  3      Multiply Matrix by BoneMatrix (see below)                         |
|       26h  4      Multiply Matrix by BoneMatrix and Store Matrix to Stack           |
|       46h  4      Multiply Matrix by BoneMatrix and Load Matrix from Stack          |
|       66h  5      Multiply Matrix by BoneMatrix and Load/Store Matrix from/to Stack |
|       07h  1      Unknown                                                           |
|       47h  2?     Unknown (as above? but with 2 params?)                            |
|       08h  1      Unknown                                                           |
|       09h  var    Calculate Skinning Equation (see below)                           |
|       0Ah  -      Unused?                                                           |
|       0Bh  0      Scale Up   (using the scale factor in Model[01Ch])  ;or "BEGIN"?  |
|       2Bh  0      Scale Down (using the scale factor in Model[020h](  ;or "END"?    |
|       0Ch  2      Unknown                                                           |
|       0Dh  2      Unknown                                                           |
|       0Eh  -      Unused?                                                           |
|       0Fh  -      Unused?                                                           |
|       1xh  -      Unused?                                                           |
+-------------------------------------------------------------------------------------+
```


### Multiply Current Matrix with Bone Matrix (cmd 06h, 26h, 46h, 66h)
Multiplies the current matrix by a BoneMatrix. This is used to build the local-to-world matrices out of the BoneMatrices.

```
+-----------------------------------------------------------------------------------+
|       bone_idx = next_param     ;index of BoneMatrix         ;1st param           |
|       parent_idx = next_param   ;Parent of the Bone          ;2nd param           |
|       unknown = next_param      ;?                           ;3rd param           |
|       if cmd.bit6 then CurrMatrix = MatrixStack[next_param]  ;4th param (if any)  |
|       CurrMatrix *= BoneMatrices[bone_idx]                                        |
|       if cmd.bit5 then MatrixStack[next_param] = CurrMatrix  ;Last param (if any) |
+-----------------------------------------------------------------------------------+
```

Note: If bone_idx is the index of bone B, then parent_idx will be the index of the parent of B. \"I don\'t think it\'s used at all at runtime.\"

### Calculate Skinning Equation (cmd 09h, with 2+N\*3 parameters)
This (the \"Equation\"?) is the matrix applied to a vertex influenced by multiple bones. The inverse bind matrices bring the vertex into the local space of each bone and the local-to-world transforms send it to its world space position.

```
+--------------------------------------------------------------------------------+
|       CurrMatrix = 0                                                           |
|       store_index = next_param                                     ;1st param  |
|       num_terms = next_param                                       ;2nd param  |
|       loop num_terms times:                                                    |
|         term = MatrixStack[next_param]    ;local-to-world matrix   ;3rd,6th,.. |
|         term *= InvBindMatrices[next_param]                        ;4th,7th,.. |
|         term *= next_param / 256          ;weight                  ;5th,8th,.. |
|         CurrMatrix += term                                                     |
|       MatrixStack[store_index] = CurrMatrix                                    |
+--------------------------------------------------------------------------------+
```

This command is only used when there are vertices influenced by multiple bones (if a vertex is only influenced by a single bone, then its position will just be stored (in the Mesh) in the space of that bone, so there\'s no need for an InvBindMatrix to bring it into the correct space).


```
+-------------------------------------------------------------------------------------+
|      _______________________________ InvBindMatrix ________________________________ |
+-------------------------------------------------------------------------------------+
```


### InvBindMatrix entries
InvBindMatrices are used for computing the skinning matrix via render command 09h.

```
+-------------------------------------------------------------------------------------+
|       000h 30h  Position Matrix (3x4, fixed point 1.19.12) (rotate,scale,translate) |
|       030h 24h  Vector Matrix   (3x3, fixed point 1.19.12) (rotate only, for light) |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________________________ VertexMesh _________________________________ |
+-------------------------------------------------------------------------------------+
```


### VertexMesh
A Mesh contains actual vertex data in the form of a blob of GPU commands/parameters. To draw a Mesh, you just submit the blob of commands to the GPU\'s Geometry Command FIFO (GXFIFO).

```
+-----------------------------------------------------------------------+
|       000h 2   Dummy                                                  |
|       002h 2   Unknown (0010h, possibly the size of VertexMesh?)      |
|       004h 4   Unknown                                                |
|       008h 4   Offset from VertexMesh to GXFIFO Command List          |
|       00Ch 4   Size of GXFIFO Command List in bytes                   |
+-----------------------------------------------------------------------+
```

Only certain GPU commands appear in a Mesh. Here is a list:

```
+-------------------------------------------------------------------------------+
|       00h=NOP, 14h=MTX_RESTORE, 1Bh=MTX_SCALE, 40h=BEGIN_VTXS, 41h=END_VTXS   |
|       20h=COLOR, 21h=NORMAL, 22h=TEXCOORD                                     |
|       23h=VTX_16, 24h=VTX_10,25h=VTX_XY, 26h=VTX_XZ, 27h=VTX_YZ, 28h=VTX_DIFF |
+-------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________________________ Materials __________________________________ |
+-------------------------------------------------------------------------------------+
```


### Material
A Material is a bunch of GPU state (eg. colors, whether backface culling is enabled, etc.) to be set when the Material is bound. It also determines the texture/palette to use, though that isn\'t stored in this Material object itself.

```
+------------------------------------------------------------------------------------+
|       000h 2  Dummy (0)                                                            |
|       002h 2  Size of this Material in bytes (002Ch)                               |
|       004h 4  Value for DIF_AMB register                                           |
|       008h 4  Value for SPE_EMI register                                           |
|       00Ch 4  Value for POLYGON_ATTR register               ;<-- OR value?         |
|       010h 4  Mask for POLYGON_ATTR register (1F3FF8FFh) ?  ;<-- AND value?        |
|       014h 4  Value for TEXIMAGE_PARAMS register (bit16-19 and 30-31, see below)   |
|       018h 4  Unknown (FFFFFFFFh)                                                  |
|       01Ch 4  Unknown (1FCE0000h)                                                  |
|       020h 2  Texture_width                                                        |
|       022h 2  Texture_height                                                       |
|       024h 4  Unknown (00001000h)                                                  |
|       028h 4  Unknown (00001000h)                                                  |
|         XXX above is 2Ch-bytes (other source says "Usually 48 bytes" aka 30h-byte) |
|         XXX unknown if above can have optionaly extra entries                      |
|         XXX reportedly above can optionally contain a texcoord transform matrix?   |
|         XXX unknown if above contains 16bit COLOR (eg. for texture-less polygons)  |
+------------------------------------------------------------------------------------+
```

Only some TEXIMAGE_PARAMS bits are stored here; the others are zeroed out. They are stored in the teximage_params in the Texture object. These two teximage_param u32s are or-ed together to give the final argument to TEXIMAGE_PARAMS. The fields stored here are:

```
+-------------------------------------------------------------------------------------+
|       0-15  Zero in Model/Material (instead, derived from TEX0)                     |
|       16    Repeat in S Direction  (0=Clamp Texture, 1=Repeat Texture)              |
|       17    Repeat in T Direction  (0=Clamp Texture, 1=Repeat Texture)              |
|       18    Flip in S Direction    (0=No, 1=Flip each 2nd Texture; requires Repeat) |
|       19    Flip in T Direction    (0=No, 1=Flip each 2nd Texture; requires Repeat) |
|       20-29 Zero in Model          (instead, derived from TEX0)                     |
|       30-31 Texture Coordinates Transformation Mode (0..3)                          |
+-------------------------------------------------------------------------------------+
```


### 4-byte entries in Dict for Material-to-Texture/Palette Pairings

```
+-----------------------------------------------------------------------------+
|       000h 2  Offset from Model[008h] (?) to List of 8bit Materials Indices |
|       002h 1  Number of entries in the List of 8bit Materials Indices       |
|       003h 1  Dummy (0)                                                     |
+-----------------------------------------------------------------------------+
```

The Texture/Palette names for different Materials are stored in Dict\'s with the above 4-byte entries. The assignement is somewhat reversed (normally one would define \"Material 5 uses Texture Name 8\", but the Dict\'s are instead defining \"Texture Name 8 is used by Material Name 2, 5 and 6\").


```
+-------------------------------------------------------------------------------------+
|      ________________________________ BoneMatrices ________________________________ |
+-------------------------------------------------------------------------------------+
```


### BoneMatrix
A BoneMatrix stores the local-to-parent transform of some bone.
When a Model is animated by an Skeletal Animation, the only thing that changes are its BoneMatrices.
Note: A Model doesn\'t contain any actual bones or skeleton information (but see the parent_idx parameter to render command 06h); that has all been compiled down to an imperative list of rendering commands that build up all the necessary skinning matrices directly. The BoneMatrices just store the data from the bones that are needed by these rendering commands.

```
+-------------------------------------------------------------------------------------+
|       00h 2   Flags                                                                 |
|                 0     Disable Translation      (0=Enable, 1=Disable)                |
|                 1     Disable Rotation         (0=Enable, 1=Disable)                |
|                 2     Disable Scale            (0=Enable, 1=Disable)                |
|                 3     Matrix Type for Rotation (0=3x3 Matrix, 1=Pivot Matrix)       |
|                 4-7   Rotation Pivot Form    ;\                                     
|                 8     Rotation Pivot NegI    ; for Pivot Matrix Rotation            |
|                 9     Rotation Pivot NegC    ;                                      |
|                 10    Rotation Pivot NegD    ;/                                     |
|                 11-15 Unused (0)                                                    |
|       02h 2   Rotation Matrix m0 (fixed point, 1.3.12) ;-here for alignment reasons |
|       ... 4   Translation X      (fixed point, 1.19.12) ;\                          
|       ... 4   Translation Y      (fixed point, 1.19.12) ; only if flags.bit0=0      |
|       ... 4   Translation Z      (fixed point, 1.19.12) ;/                          |
|       ... 2   Rotation Matrix m1 (fixed point, 1.3.12) ;\                           
|       ... 2   Rotation Matrix m2 (fixed point, 1.3.12) ; only if Flags.bit3=0=3x3   |
|       ... 2   Rotation Matrix m3 (fixed point, 1.3.12) ; and Flags.bit1=0           |
|       ... 2   Rotation Matrix m4 (fixed point, 1.3.12) ;   [ m0 m3 m6 ]             |
|       ... 2   Rotation Matrix m5 (fixed point, 1.3.12) ;   [ m1 m4 m7 ]             |
|       ... 2   Rotation Matrix m6 (fixed point, 1.3.12) ;   [ m2 m5 m8 ]             |
|       ... 2   Rotation Matrix m7 (fixed point, 1.3.12) ;                            |
|       ... 2   Rotation Matrix m8 (fixed point, 1.3.12) ;/                           |
|       ... 2   Rotation Pivot A   (fixed point, 1.3.12) ;\only if Flags.bit3=1=Pivot 
|       ... 2   Rotation Pivot B   (fixed point, 1.3.12) ;/ (and Flags.bit1=0?)       |
|       ... 4   Scale X            (fixed point, 1.19.12) ;\                          
|       ... 4   Scale Y            (fixed point, 1.19.12) ; only if Flags.bit2=0      |
|       ... 4   Scale Z            (fixed point, 1.19.12) ;/                          |
+-------------------------------------------------------------------------------------+
```

The Pivot Matrix can be used for simple rotation around X, Y, or Z axis; see the Skeletal Animation chapter for info on how to convert the Pivot parameters (A, B, Form, NegI, NegC, NegD) into a 3x3 matrix.



