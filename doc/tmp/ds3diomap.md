# DS 3D I/O Map


### 3D I/O Map

```
+---------------------------------------------------------------------------------+
|       Address  Siz Name            Expl.                                        |
|       Rendering Engine (per Frame settings)                                     |
|       4000060h 2   DISP3DCNT       3D Display Control Register (R/W)            |
|       4000320h 1   RDLINES_COUNT   Rendered Line Count Register (R)             |
|       4000330h 10h EDGE_COLOR      Edge Colors 0..7 (W)                         |
|       4000340h 1   ALPHA_TEST_REF  Alpha-Test Comparision Value (W)             |
|       4000350h 4   CLEAR_COLOR     Clear Color Attribute Register (W)           |
|       4000354h 2   CLEAR_DEPTH     Clear Depth Register (W)                     |
|       4000356h 2   CLRIMAGE_OFFSET Rear-plane Bitmap Scroll Offsets (W)         |
|       4000358h 4   FOG_COLOR       Fog Color (W)                                |
|       400035Ch 2   FOG_OFFSET      Fog Depth Offset (W)                         |
|       4000360h 20h FOG_TABLE       Fog Density Table, 32 entries (W)            |
|       4000380h 40h TOON_TABLE      Toon Table, 32 colors (W)                    |
|       Geometry Engine (per Polygon/Vertex settings)                             |
|       4000400h 40h GXFIFO          Geometry Command FIFO (W)                    |
|       4000440h ... ...             Geometry Command Ports (see below)           |
|       4000600h 4   GXSTAT          Geometry Engine Status Register (R and R/W)  |
|       4000604h 4   RAM_COUNT       Polygon List & Vertex RAM Count Register (R) |
|       4000610h 2   DISP_1DOT_DEPTH 1-Dot Polygon Display Boundary Depth (W)     |
|       4000620h 10h POS_RESULT      Position Test Results (R)                    |
|       4000630h 6   VEC_RESULT      Vector Test Results (R)                      |
|       4000640h 40h CLIPMTX_RESULT  Read Current Clip Coordinates Matrix (R)     |
|       4000680h 24h VECMTX_RESULT   Read Current Directional Vector Matrix (R)   |
+---------------------------------------------------------------------------------+
```


### Geometry Commands (can be invoked by Port Address, or by Command ID)
Table shows Port Address, Command ID, Number of Parameters, and Clock Cycles.

```
+------------------------------------------------------------------------------------+
|       Address  Cmd Pa.Cy.                                                          |
|       N/A      00h -  -   NOP - No Operation (for padding packed GXFIFO commands)  |
|       4000440h 10h 1  1   MTX_MODE - Set Matrix Mode (W)                           |
|       4000444h 11h -  17  MTX_PUSH - Push Current Matrix on Stack (W)              |
|       4000448h 12h 1  36  MTX_POP - Pop Current Matrix from Stack (W)              |
|       400044Ch 13h 1  17  MTX_STORE - Store Current Matrix on Stack (W)            |
|       4000450h 14h 1  36  MTX_RESTORE - Restore Current Matrix from Stack (W)      |
|       4000454h 15h -  19  MTX_IDENTITY - Load Unit Matrix to Current Matrix (W)    |
|       4000458h 16h 16 34  MTX_LOAD_4x4 - Load 4x4 Matrix to Current Matrix (W)     |
|       400045Ch 17h 12 30  MTX_LOAD_4x3 - Load 4x3 Matrix to Current Matrix (W)     |
|       4000460h 18h 16 35* MTX_MULT_4x4 - Multiply Current Matrix by 4x4 Matrix (W) |
|       4000464h 19h 12 31* MTX_MULT_4x3 - Multiply Current Matrix by 4x3 Matrix (W) |
|       4000468h 1Ah 9  28* MTX_MULT_3x3 - Multiply Current Matrix by 3x3 Matrix (W) |
|       400046Ch 1Bh 3  22  MTX_SCALE - Multiply Current Matrix by Scale Matrix (W)  |
|       4000470h 1Ch 3  22* MTX_TRANS - Mult. Curr. Matrix by Translation Matrix (W) |
|       4000480h 20h 1  1   COLOR - Directly Set Vertex Color (W)                    |
|       4000484h 21h 1  9*  NORMAL - Set Normal Vector (W)                           |
|       4000488h 22h 1  1   TEXCOORD - Set Texture Coordinates (W)                   |
|       400048Ch 23h 2  9   VTX_16 - Set Vertex XYZ Coordinates (W)                  |
|       4000490h 24h 1  8   VTX_10 - Set Vertex XYZ Coordinates (W)                  |
|       4000494h 25h 1  8   VTX_XY - Set Vertex XY Coordinates (W)                   |
|       4000498h 26h 1  8   VTX_XZ - Set Vertex XZ Coordinates (W)                   |
|       400049Ch 27h 1  8   VTX_YZ - Set Vertex YZ Coordinates (W)                   |
|       40004A0h 28h 1  8   VTX_DIFF - Set Relative Vertex Coordinates (W)           |
|       40004A4h 29h 1  1   POLYGON_ATTR - Set Polygon Attributes (W)                |
|       40004A8h 2Ah 1  1   TEXIMAGE_PARAM - Set Texture Parameters (W)              |
|       40004ACh 2Bh 1  1   PLTT_BASE - Set Texture Palette Base Address (W)         |
|       40004C0h 30h 1  4   DIF_AMB - MaterialColor0 - Diffuse/Ambient Reflect. (W)  |
|       40004C4h 31h 1  4   SPE_EMI - MaterialColor1 - Specular Ref. & Emission (W)  |
|       40004C8h 32h 1  6   LIGHT_VECTOR - Set Light's Directional Vector (W)        |
|       40004CCh 33h 1  1   LIGHT_COLOR - Set Light Color (W)                        |
|       40004D0h 34h 32 32  SHININESS - Specular Reflection Shininess Table (W)      |
|       4000500h 40h 1  1   BEGIN_VTXS - Start of Vertex List (W)                    |
|       4000504h 41h -  1   END_VTXS - End of Vertex List (W)                        |
|       4000540h 50h 1  392 SWAP_BUFFERS - Swap Rendering Engine Buffer (W)          |
|       4000580h 60h 1  1   VIEWPORT - Set Viewport (W)                              |
|       40005C0h 70h 3  103 BOX_TEST - Test if Cuboid Sits inside View Volume (W)    |
|       40005C4h 71h 2  9   POS_TEST - Set Position Coordinates for Test (W)         |
|       40005C8h 72h 1  5   VEC_TEST - Set Directional Vector for Test (W)           |
+------------------------------------------------------------------------------------+
```

All cycle timings are counted in 33.51MHz units. NORMAL commands takes 9..12 cycles, depending on the number of enabled lights in PolyAttr (Huh, 9..12 (four timings) cycles for 0..4 (five settings) lights?) Total execution time of SwapBuffers is Duration until VBlank, plus 392 cycles.
In MTX_MODE=2 (Simultanous Set), MTX_MULT/TRANS take additional 30 cycles.



