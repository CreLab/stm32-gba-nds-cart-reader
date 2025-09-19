# 3DS GPU Internal Register List Summary


**3DS GPU Internal Registers - Finalize Interrupt registers**

```
+-----------------------------------------------------------------------+
|       10401000h+i   - PICA(N/A)       - GPUREG_IRQ_ACK(0..63) (R/W)   |
|       10401040h+i   - PICA(0010h+i/4) - GPUREG_IRQ_REQ(0..63) (R/W)   |
|       10401080h+i   - PICA(N/A)       - GPUREG_IRQ_CMP(0..63) (R/W)   |
|       104010C0h     - PICA(N/A)       - GPUREG_IRQ_MASK_LOW (R/W)     |
|       104010C4h     - PICA(N/A)       - GPUREG_IRQ_MASK_HIGH (R/W)    |
|       104010C8h     - PICA(N/A)       - GPUREG_IRQ_STAT_LOW (R)       |
|       104010CCh     - PICA(N/A)       - GPUREG_IRQ_STAT_HIGH (R)      |
|       104010D0h     - PICA(N/A)       - GPUREG_IRQ_AUTOSTOP (R/W)     |
|       104010D4h     - PICA(N/A)       - GPUREG_FIXED_00010002h (R)    |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Rasterizer registers**

```
+-----------------------------------------------------------------------+
|       10401100h     - PICA(0040h)   - GPUREG_FACECULLING_CONFIG (R/W) |
|       10401104h     - PICA(0041h)   - GPUREG_VIEWPORT_V_SCALE (R/W)   |
|       10401108h     - PICA(0042h)   - GPUREG_VIEWPORT_V_STEP (R/W)    |
|       1040110Ch     - PICA(0043h)   - GPUREG_VIEWPORT_H_SCALE (R/W)   |
|       10401110h     - PICA(0044h)   - GPUREG_VIEWPORT_H_STEP (R/W)    |
|       1                                                               |
| 0401114h     - PICA(0045h)   - GPUREG_undoc_10401114h (R/W=00FFFFFFh) |
|       1                                                               |
| 0401118h     - PICA(0046h)   - GPUREG_undoc_10401118h (R/W=00FFFFFFh) |
|       1040111Ch     - PICA(0047h)   - GPUREG_FRAGOP_CLIP (R/W)        |
|       10                                                              |
| 401120h+i*4 - PICA(0048h+i) - GPUREG_FRAGOP_CLIP_DATAi (i=0..3) (R/W) |
|       1                                                               |
| 0401130h     - PICA(004Ch)   - GPUREG_undoc_10401130h (R/W=00000001h) |
|       10401134h     - PICA(004Dh)   - GPUREG_DEPTHMAP_SCALE (R/W)     |
|       10401138h     - PICA(004Eh)   - GPUREG_DEPTHMAP_OFFSET (R/W)    |
|       1040113Ch     - PICA(004Fh)   - GPUREG_SH_OUTMAP_TOTAL (R/W)    |
|                                                                       |
|    10401140h+i*4 - PICA(0050h+i) - GPUREG_SH_OUTMAP_Oi (i=0..6) (R/W) |
|       1                                                               |
| 0401160h     - PICA(0058h)   - GPUREG_undoc_10401160h (R/W=00000101h) |
|       1                                                               |
| 0401164h     - PICA(0059h)   - GPUREG_undoc_10401164h (R/W=00000001h) |
|                                                                       |
| 10401168h     - PICA(005Ah)   - GPUREG_STAT_NUM_VERTICES_RECEIVED (R) |
|       1                                                               |
| 040116Ch     - PICA(005Bh)   - GPUREG_STAT_NUM_TRIANGLES_RECEIVED (R) |
|       10                                                              |
| 401170h     - PICA(005Ch)   - GPUREG_STAT_NUM_TRIANGLES_DISPLAYED (R) |
|       1                                                               |
| 0401180h     - PICA(0060h)   - GPUREG_undoc_10401180h (R/W=00000301h) |
|       10401184h     - PICA(0061h)   - GPUREG_EARLYDEPTH_FUNC (R/W)    |
|       10401188h     - PICA(0062h)   - GPUREG_EARLYDEPTH_TEST1 (R/W)   |
|       1040118Ch     - PICA(0063h)   - GPUREG_EARLYDEPTH_CLEAR (W)     |
|       10401190h     - PICA(0064h)   - GPUREG_SH_OUTATTR_MODE (R/W)    |
|       10401194h     - PICA(0065h)   - GPUREG_SCISSORTEST_MODE (R/W)   |
|       10401198h     - PICA(0066h)   - GPUREG_SCISSORTEST_POS1 (R/W)   |
|       1040119Ch     - PICA(0067h)   - GPUREG_SCISSORTEST_POS2 (R/W)   |
|       104011A0h     - PICA(0068h)   - GPUREG_VIEWPORT_XY (R/W)        |
|       1                                                               |
| 04011A4h     - PICA(0069h)   - GPUREG_undoc_104011A4h (R/W=FFFF0001h) |
|       104011A8h     - PICA(006Ah)   - GPUREG_EARLYDEPTH_DATA (R/W)    |
|       1                                                               |
| 04011ACh     - PICA(006Bh)   - GPUREG_undoc_104011ACh (R/W=00000FFFh) |
|       104011                                                          |
| B0h     - PICA(006Ch)   - GPUREG_undoc_104011B0h (hangs when reading) |
|       104011B4h     - PICA(006Dh)   - GPUREG_DEPTHMAP_ENABLE (R/W)    |
|       104011B8h     - PICA(006Eh)   - GPUREG_RENDERBUFFER_DIM_1 (R/W) |
|       104011BCh     - PICA(006Fh)   - GPUREG_SH_OUTATTR_CLOCK (R/W)   |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Texturing registers (Generic Textures)**

```
+-----------------------------------------------------------------------+
|       104012                                                          |
| 00h     - PICA(0080h)   - GPUREG_TEXUNIT_CONFIG (R/W)        ;-CONFIG |
|                                                                       |
| 10401204h     - PICA(0081h)   - GPUREG_TEXUNIT0_BORDER_COLOR (R/W) ;\ 
|                                                                       |
|  10401208h     - PICA(0082h)   - GPUREG_TEXUNIT0_DIM (R/W)          ; |
|       10401                                                           |
| 20Ch     - PICA(0083h)   - GPUREG_TEXUNIT0_PARAM (R/W)        ; UNIT0 |
|                                                                       |
|  10401210h     - PICA(0084h)   - GPUREG_TEXUNIT0_LOD (R/W)          ; |
|                                                                       |
|  10401214h     - PICA(0085h)   - GPUREG_TEXUNIT0_ADDR1 (R/W)        ; |
|                                                                       |
|  10401218h     - PICA(0086h)   - GPUREG_TEXUNIT0_ADDR2 (R/W)        ; |
|                                                                       |
|  1040121Ch     - PICA(0087h)   - GPUREG_TEXUNIT0_ADDR3 (R/W)        ; |
|                                                                       |
|  10401220h     - PICA(0088h)   - GPUREG_TEXUNIT0_ADDR4 (R/W)        ; |
|                                                                       |
|  10401224h     - PICA(0089h)   - GPUREG_TEXUNIT0_ADDR5 (R/W)        ; |
|                                                                       |
|  10401228h     - PICA(008Ah)   - GPUREG_TEXUNIT0_ADDR6 (R/W)        ; |
|                                                                       |
|  1040122Ch     - PICA(008Bh)   - GPUREG_TEXUNIT0_SHADOW (R/W)       ; |
|       1                                                               |
| 0401230h     - PICA(008Ch)   - GPUREG_undoc_10401230h (R/W=FFFF00FFh) |
|       1                                                               |
| 0401234h     - PICA(008Dh)   - GPUREG_undoc_10401234h (R/W=000000FFh) |
|                                                                       |
| 10401238h     - PICA(008Eh)   - GPUREG_TEXUNIT0_TYPE (R/W)         ;/ |
|                                                                       |
| 1040123Ch     - PICA(008Fh)   - GPUREG_LIGHTING_ENABLE (R/W)       ;- |
|                                                                       |
| 10401244h     - PICA(0091h)   - GPUREG_TEXUNIT1_BORDER_COLOR (R/W) ;\ 
|                                                                       |
|  10401248h     - PICA(0092h)   - GPUREG_TEXUNIT1_DIM (R/W)          ; |
|       10401                                                           |
| 24Ch     - PICA(0093h)   - GPUREG_TEXUNIT1_PARAM (R/W)        ; UNIT1 |
|                                                                       |
|  10401250h     - PICA(0094h)   - GPUREG_TEXUNIT1_LOD (R/W)          ; |
|                                                                       |
|  10401254h     - PICA(0095h)   - GPUREG_TEXUNIT1_ADDR (R/W)         ; |
|                                                                       |
| 10401258h     - PICA(0096h)   - GPUREG_TEXUNIT1_TYPE (R/W)         ;/ |
|                                                                       |
| 10401264h     - PICA(0099h)   - GPUREG_TEXUNIT2_BORDER_COLOR (R/W) ;\ 
|                                                                       |
|  10401268h     - PICA(009Ah)   - GPUREG_TEXUNIT2_DIM (R/W)          ; |
|       10401                                                           |
| 26Ch     - PICA(009Bh)   - GPUREG_TEXUNIT2_PARAM (R/W)        ; UNIT2 |
|                                                                       |
|  10401270h     - PICA(009Ch)   - GPUREG_TEXUNIT2_LOD (R/W)          ; |
|                                                                       |
|  10401274h     - PICA(009Dh)   - GPUREG_TEXUNIT2_ADDR (R/W)         ; |
|                                                                       |
| 10401278h     - PICA(009Eh)   - GPUREG_TEXUNIT2_TYPE (R/W)         ;/ |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Texturing registers (Procedural
Texture)**

```
+-----------------------------------------------------------------------+
|       104012A0h     - PICA(00A8h)   - GPUREG_TEXUNIT3_PROCTEX0 (R/W)  |
|       104012A4h     - PICA(00A9h)   - GPUREG_TEXUNIT3_PROCTEX1 (R/W)  |
|       104012A8h     - PICA(00AAh)   - GPUREG_TEXUNIT3_PROCTEX2 (R/W)  |
|       104012ACh     - PICA(00ABh)   - GPUREG_TEXUNIT3_PROCTEX3 (R/W)  |
|       104012B0h     - PICA(00ACh)   - GPUREG_TEXUNIT3_PROCTEX4 (R/W)  |
|                                                                       |
|    104012B4h     - PICA(00ADh)   - GPUREG_TEXUNIT3_PROCTEX5_LOW (R/W) |
|                                                                       |
|   104012B8h     - PICA(00AEh)   - GPUREG_TEXUNIT3_PROCTEX5_HIGH (R/W) |
|       104012BCh     - PICA(00AFh)   - GPUREG_PROCTEX_LUT_INDEX (R/W)  |
|                                                                       |
|   104012C0h+i*4 - PICA(00B0h+i) - GPUREG_PROCTEX_LUT_DATA(0..7) (R/W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Texturing registers (Environment)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|  10401300h     - PICA(00C0h)   - GPUREG_TEXENV0_SOURCE (R/W)       ;\ 
|                                                                       |
|   10401304h     - PICA(00C1h)   - GPUREG_TEXENV0_OPERAND (R/W)      ; |
|       104                                                             |
| 01308h     - PICA(00C2h)   - GPUREG_TEXENV0_COMBINER (R/W)     ; ENV0 |
|                                                                       |
|   1040130Ch     - PICA(00C3h)   - GPUREG_TEXENV0_COLOR (R/W)        ; |
|                                                                       |
|  10401310h     - PICA(00C4h)   - GPUREG_TEXENV0_SCALE (R/W)        ;/ |
|       1                                                               |
| 040131Ch     - PICA(00C7h)   - GPUREG_undoc_1040131Ch (R/W=00000007h) |
|                                                                       |
|  10401320h     - PICA(00C8h)   - GPUREG_TEXENV1_SOURCE (R/W)       ;\ 
|                                                                       |
|   10401324h     - PICA(00C9h)   - GPUREG_TEXENV1_OPERAND (R/W)      ; |
|       104                                                             |
| 01328h     - PICA(00CAh)   - GPUREG_TEXENV1_COMBINER (R/W)     ; ENV1 |
|                                                                       |
|   1040132Ch     - PICA(00CBh)   - GPUREG_TEXENV1_COLOR (R/W)        ; |
|                                                                       |
|  10401330h     - PICA(00CCh)   - GPUREG_TEXENV1_SCALE (R/W)        ;/ |
|                                                                       |
|  10401340h     - PICA(00D0h)   - GPUREG_TEXENV2_SOURCE (R/W)       ;\ 
|                                                                       |
|   10401344h     - PICA(00D1h)   - GPUREG_TEXENV2_OPERAND (R/W)      ; |
|       104                                                             |
| 01348h     - PICA(00D2h)   - GPUREG_TEXENV2_COMBINER (R/W)     ; ENV2 |
|                                                                       |
|   1040134Ch     - PICA(00D3h)   - GPUREG_TEXENV2_COLOR (R/W)        ; |
|                                                                       |
|  10401350h     - PICA(00D4h)   - GPUREG_TEXENV2_SCALE (R/W)        ;/ |
|                                                                       |
|  10401360h     - PICA(00D8h)   - GPUREG_TEXENV3_SOURCE (R/W)       ;\ 
|                                                                       |
|   10401364h     - PICA(00D9h)   - GPUREG_TEXENV3_OPERAND (R/W)      ; |
|       104                                                             |
| 01368h     - PICA(00DAh)   - GPUREG_TEXENV3_COMBINER (R/W)     ; ENV3 |
|                                                                       |
|   1040136Ch     - PICA(00DBh)   - GPUREG_TEXENV3_COLOR (R/W)        ; |
|                                                                       |
|  10401370h     - PICA(00DCh)   - GPUREG_TEXENV3_SCALE (R/W)        ;/ |
|                                                                       |
|     10401380h     - PICA(00E0h)   - GPUREG_TEXENV_UPDATE_BUFFER (R/W) |
|       10401384h     - PICA(00E1h)   - GPUREG_FOG_COLOR (R/W)          |
|       1                                                               |
| 0401388h     - PICA(00E2h)   - GPUREG_undoc_10401388h (R/W=0000FFFFh) |
|       1                                                               |
| 040138Ch     - PICA(00E3h)   - GPUREG_undoc_1040138Ch (R/W=0000FFFFh) |
|       10401390h     - PICA(00E4h)   - GPUREG_GAS_ATTENUATION (R/W)    |
|       10401394h     - PICA(00E5h)   - GPUREG_GAS_ACCMAX (R/W)         |
|       10401398h     - PICA(00E6h)   - GPUREG_FOG_LUT_INDEX (R/W)      |
|       104013A0h+i*4 - PICA(00E8h+i) - GPUREG_FOG_LUT_DATA(0..7) (R/W) |
|                                                                       |
|  104013C0h     - PICA(00F0h)   - GPUREG_TEXENV4_SOURCE (R/W)       ;\ 
|                                                                       |
|   104013C4h     - PICA(00F1h)   - GPUREG_TEXENV4_OPERAND (R/W)      ; |
|       104                                                             |
| 013C8h     - PICA(00F2h)   - GPUREG_TEXENV4_COMBINER (R/W)     ; ENV4 |
|                                                                       |
|   104013CCh     - PICA(00F3h)   - GPUREG_TEXENV4_COLOR (R/W)        ; |
|                                                                       |
|  104013D0h     - PICA(00F4h)   - GPUREG_TEXENV4_SCALE (R/W)        ;/ |
|                                                                       |
|  104013E0h     - PICA(00F8h)   - GPUREG_TEXENV5_SOURCE (R/W)       ;\ 
|                                                                       |
|   104013E4h     - PICA(00F9h)   - GPUREG_TEXENV5_OPERAND (R/W)      ; |
|       104                                                             |
| 013E8h     - PICA(00FAh)   - GPUREG_TEXENV5_COMBINER (R/W)     ; ENV5 |
|                                                                       |
|   104013ECh     - PICA(00FBh)   - GPUREG_TEXENV5_COLOR (R/W)        ; |
|                                                                       |
|  104013F0h     - PICA(00FCh)   - GPUREG_TEXENV5_SCALE (R/W)        ;/ |
|                                                                       |
|  104013F4h     - PICA(00FDh)   - GPUREG_TEXENV_BUFFER_COLOR (R/W)  ;- |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Framebuffer registers**

```
+-----------------------------------------------------------------------+
|       10401400h     - PICA(0100h)   - GPUREG_COLOR_OPERATION (R/W)    |
|       10401404h     - PICA(0101h)   - GPUREG_BLEND_FUNC (R/W)         |
|       10401408h     - PICA(0102h)   - GPUREG_LOGIC_OP (R/W)           |
|       1040140Ch     - PICA(0103h)   - GPUREG_BLEND_COLOR (R/W)        |
|       10401410h     - PICA(0104h)   - GPUREG_FRAGOP_ALPHA_TEST (R/W)  |
|       10401414h     - PICA(0105h)   - GPUREG_STENCIL_TEST (R/W)       |
|       10401418h     - PICA(0106h)   - GPUREG_STENCIL_OP (R/W)         |
|       1040141Ch     - PICA(0107h)   - GPUREG_DEPTH_COLOR_MASK (R/W)   |
|       1                                                               |
| 0401434h     - PICA(010Dh)   - GPUREG_undoc_10401434h (R/W=00000001h) |
|       1                                                               |
| 0401438h     - PICA(010Eh)   - GPUREG_undoc_10401438h (R/W=FFFFFFFFh) |
|       1                                                               |
| 040143Ch     - PICA(010Fh)   - GPUREG_undoc_1040143Ch (R/W=FFFFFFFFh) |
|       104014                                                          |
| 40h     - PICA(0110h)   - GPUREG_RENDERBUFFER_INVALIDATE (forget) (W) |
|       1040                                                            |
| 1444h     - PICA(0111h)   - GPUREG_RENDERBUFFER_FLUSH (writeback) (W) |
|                                                                       |
|      10401448h     - PICA(0112h)   - GPUREG_COLORBUFFER_READING (R/W) |
|                                                                       |
|      1040144Ch     - PICA(0113h)   - GPUREG_COLORBUFFER_WRITING (R/W) |
|                                                                       |
|      10401450h     - PICA(0114h)   - GPUREG_DEPTHBUFFER_READING (R/W) |
|                                                                       |
|      10401454h     - PICA(0115h)   - GPUREG_DEPTHBUFFER_WRITING (R/W) |
|       10401458h     - PICA(0116h)   - GPUREG_DEPTHBUFFER_FORMAT (R/W) |
|       1040145Ch     - PICA(0117h)   - GPUREG_COLORBUFFER_FORMAT (R/W) |
|       10401460h     - PICA(0118h)   - GPUREG_EARLYDEPTH_TEST2 (R/W)   |
|       1                                                               |
| 0401464h     - PICA(0119h)   - GPUREG_undoc_10401464h (R/W=FFFFFFFFh) |
|       1                                                               |
| 0401468h     - PICA(011Ah)   - GPUREG_undoc_10401468h (R/W=FFFFFFFFh) |
|                                                                       |
|     1040146Ch     - PICA(011Bh)   - GPUREG_RENDERBUFFER_BLOCK32 (R/W) |
|       10401470h     - PICA(011Ch)   - GPUREG_DEPTHBUFFER_LOC (R/W)    |
|       10401474h     - PICA(011Dh)   - GPUREG_COLORBUFFER_LOC (R/W)    |
|       10401478h     - PICA(011Eh)   - GPUREG_RENDERBUFFER_DIM_0 (R/W) |
|       1                                                               |
| 040147Ch     - PICA(011Fh)   - GPUREG_undoc_1040147Ch (R/W=7FFFFFFFh) |
|       10401                                                           |
| 480h     - PICA(0120h)   - GPUREG_GAS_LIGHT_XY - Planar Shading (R/W) |
|       10                                                              |
| 401484h     - PICA(0121h)   - GPUREG_GAS_LIGHT_Z - View Shading (R/W) |
|       10401488h     - PICA(0122h)   - GPUREG_GAS_LIGHT_Z_COLOR (R/W)  |
|       1040148Ch     - PICA(0123h)   - GPUREG_GAS_LUT_INDEX (W)        |
|       10401490h     - PICA(0124h)   - GPUREG_GAS_LUT_DATA (R/W)       |
|       1                                                               |
| 0401494h     - PICA(0125h)   - GPUREG_undoc_10401494h (R/W=0000FFFFh) |
|       10401498h     - PICA(0126h)   - GPUREG_GAS_DELTAZ_DEPTH (R/W)   |
|       104014C0h     - PICA(0130h)   - GPUREG_FRAGOP_SHADOW (R/W)      |
|       1                                                               |
| 04014FCh     - PICA(013Fh)   - GPUREG_undoc_104014FCh (R/W=0000000Fh) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Fragment Lighting registers**

```
+-----------------------------------------------------------------------+
|       104                                                             |
| 01500h+i*40h - PICA(0140h+10h*(0..7)) - GPUREG_LIGHTi_SPECULAR0 (R/W) |
|       104                                                             |
| 01504h+i*40h - PICA(0141h+10h*(0..7)) - GPUREG_LIGHTi_SPECULAR1 (R/W) |
|       1                                                               |
| 0401508h+i*40h - PICA(0142h+10h*(0..7)) - GPUREG_LIGHTi_DIFFUSE (R/W) |
|       1                                                               |
| 040150Ch+i*40h - PICA(0143h+10h*(0..7)) - GPUREG_LIGHTi_AMBIENT (R/W) |
|       1040                                                            |
| 1510h+i*40h - PICA(0144h+10h*(0..7)) - GPUREG_LIGHTi_VECTOR_LOW (R/W) |
|       10401                                                           |
| 514h+i*40h - PICA(0145h+10h*(0..7)) - GPUREG_LIGHTi_VECTOR_HIGH (R/W) |
|       10401                                                           |
| 518h+i*40h - PICA(0146h+10h*(0..7)) - GPUREG_LIGHTi_SPOTDIR_LOW (R/W) |
|       104015                                                          |
| 1Ch+i*40h - PICA(0147h+10h*(0..7)) - GPUREG_LIGHTi_SPOTDIR_HIGH (R/W) |
|                                                                       |
| 10401524h+i*40h - PICA(0149h+10h*(0..7)) - GPUREG_LIGHTi_CONFIG (R/W) |
|       1040                                                            |
| 1528h+i*40h - PICA(014Ah+10h*(0..7)) - GPUREG_LIGHTi_ATTENUATION_BIAS |
|       10401                                                           |
| 52Ch+i*40h - PICA(014Bh+10h*(0..7)) - GPUREG_LIGHTi_ATTENUATION_SCALE |
|       10401700h       - PICA(01C0h)   - GPUREG_LIGHTING_AMBIENT (R/W) |
|                                                                       |
|    10401708h       - PICA(01C2h)   - GPUREG_LIGHTING_NUM_LIGHTS (R/W) |
|       1040170Ch       - PICA(01C3h)   - GPUREG_LIGHTING_CONFIG0 (R/W) |
|       10401710h       - PICA(01C4h)   - GPUREG_LIGHTING_CONFIG1 (R/W) |
|                                                                       |
|     10401714h       - PICA(01C5h)   - GPUREG_LIGHTING_LUT_INDEX (R/W) |
|       10401718h       - PICA(01C6h)   - GPUREG_LIGHTING_DISABLE (R/W) |
|       1                                                               |
| 0401720h+i*4   - PICA(01C8h+i) - GPUREG_LIGHTING_LUT_DATA(0..7) (R/W) |
|                                                                       |
|  10401740h       - PICA(01D0h)   - GPUREG_LIGHTING_LUTINPUT_ABS (R/W) |
|       10                                                              |
| 401744h       - PICA(01D1h)   - GPUREG_LIGHTING_LUTINPUT_SELECT (R/W) |
|       1                                                               |
| 0401748h       - PICA(01D2h)   - GPUREG_LIGHTING_LUTINPUT_SCALE (R/W) |
|       1040                                                            |
| 1764h       - PICA(01D9h)   - GPUREG_LIGHTING_LIGHT_PERMUTATION (R/W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Geometry Pipeline registers**

```
+-----------------------------------------------------------------------+
|       10401800h       - PICA(0200h)   - GPUREG_ATTR_BUF_BASE (R/W)    |
|                                                                       |
|    10401804h       - PICA(0201h)   - GPUREG_ATTR_BUF_FORMAT_LOW (R/W) |
|                                                                       |
|   10401808h       - PICA(0202h)   - GPUREG_ATTR_BUF_FORMAT_HIGH (R/W) |
|       10                                                              |
| 40180Ch+i*0Ch - PICA(0203h+3*(0..11)) - GPUREG_ATTR_BUFi_OFFSET (R/W) |
|       104018                                                          |
| 10h+i*0Ch - PICA(0204h+3*(0..11)) - GPUREG_ATTR_BUFi_CONFIG_LOW (R/W) |
|       1040181                                                         |
| 4h+i*0Ch - PICA(0205h+3*(0..11)) - GPUREG_ATTR_BUFi_CONFIG_HIGH (R/W) |
|                                                                       |
|    1040189Ch       - PICA(0227h)   - GPUREG_ATTR_BUF_INDEX_LIST (R/W) |
|                                                                       |
|   104018A0h       - PICA(0228h)   - GPUREG_ATTR_BUF_NUMVERTICES (R/W) |
|       104018A4h       - PICA(0229h)   - GPUREG_GEOSTAGE_CONFIG (R/W)  |
|                                                                       |
|   104018A8h       - PICA(022Ah)   - GPUREG_ATTR_BUF_FIRST_INDEX (R/W) |
|                                                                       |
|  104018B4h       - PICA(022Dh)   - GPUREG_POST_VERTEX_CACHE_NUM (R/W) |
|                                                                       |
|      104018B8h       - PICA(022Eh)   - GPUREG_ATTR_BUF_DRAWARRAYS (W) |
|                                                                       |
|    104018BCh       - PICA(022Fh)   - GPUREG_ATTR_BUF_DRAWELEMENTS (W) |
|       104018C4h       - PICA(0231h)   - GPUREG_VTX_FUNC (W)           |
|       104018C8h       - PICA(0232h)   - GPUREG_FIXEDATTRIB_INDEX (W)  |
|                                                                       |
|   104018CCh+i*4   - PICA(0233h+i) - GPUREG_FIXEDATTRIB_DATA(0..2) (W) |
|       104018E0h       - PICA(0238h)   - GPUREG_CMDBUF_SIZE0 (R/W)     |
|       104018E4h       - PICA(0239h)   - GPUREG_CMDBUF_SIZE1 (R/W)     |
|       104018E                                                         |
| 8h       - PICA(023Ah)   - GPUREG_CMDBUF_ADDR0 (aka entrypoint) (R/W) |
|       104018E                                                         |
| Ch       - PICA(023Bh)   - GPUREG_CMDBUF_ADDR1 (aka entrypoint) (R/W) |
|       1040                                                            |
| 18F0h       - PICA(023Ch)   - GPUREG_CMDBUF_JUMP0 (jump to ADDR0) (W) |
|       1040                                                            |
| 18F4h       - PICA(023Dh)   - GPUREG_CMDBUF_JUMP1 (jump to ADDR1) (W) |
|       10401908h       - PICA(0242h)   - GPUREG_VSH_NUM_ATTR (R/W)     |
|       104                                                             |
| 0190Ch       - PICA(0243h)   - GPUREG_undoc_1040190Ch (R/W=00000037h) |
|       10401910h       - PICA(0244h)   - GPUREG_VSH_COM_MODE (R/W)     |
|       10401914h       - PICA(0245h)   - GPUREG_START_DRAW_FUNC0 (R/W) |
|                                                                       |
|      10401928h       - PICA(024Ah)   - GPUREG_VSH_OUTMAP_TOTAL1 (R/W) |
|                                                                       |
|      10401944h       - PICA(0251h)   - GPUREG_VSH_OUTMAP_TOTAL2 (R/W) |
|       10401948h       - PICA(0252h)   - GPUREG_GSH_MISC0 (R/W)        |
|       1040194Ch       - PICA(0253h)   - GPUREG_GEOSTAGE_CONFIG2 (R/W) |
|       10401950h       - PICA(0254h)   - GPUREG_GSH_MISC1 (R/W)        |
|       104                                                             |
| 01954h       - PICA(0255h)   - GPUREG_undoc_10401954h (R/W=00000001h) |
|       10401978h       - PICA(025Eh)   - GPUREG_PRIMITIVE_CONFIG (R/W) |
|                                                                       |
|      1040197Ch       - PICA(025Fh)   - GPUREG_RESTART_PRIMITIVE (R/W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Shader 0 (Geometry Shader)**

```
+-----------------------------------------------------------------------+
|       10401A00h       - PICA(0280h)   - GPUREG_GSH_BOOLUNIFORM (R/W)  |
|                                                                       |
|  10401A04h+i*4   - PICA(0281h+i) - GPUREG_GSH_INTUNIFORM_I0..I3 (R/W) |
|                                                                       |
| 10401A24h       - PICA(0289h)   - GPUREG_GSH_INPUTBUFFER_CONFIG (R/W) |
|       10401A28h       - PICA(028Ah)   - GPUREG_GSH_ENTRYPOINT (R/W)   |
|       10                                                              |
| 401A2Ch       - PICA(028Bh)   - GPUREG_GSH_ATTR_PERMUTATION_LOW (R/W) |
|       104                                                             |
| 01A30h       - PICA(028Ch)   - GPUREG_GSH_ATTR_PERMUTATION_HIGH (R/W) |
|       10401A34h       - PICA(028Dh)   - GPUREG_GSH_OUTMAP_MASK (R/W)  |
|                                                                       |
|     10401A3Ch       - PICA(028Fh)   - GPUREG_GSH_CODETRANSFER_END (W) |
|                                                                       |
|   10401A40h       - PICA(0290h)   - GPUREG_GSH_FLOATUNIFORM_INDEX (W) |
|       104                                                             |
| 01A44h+i*4   - PICA(0291h+i) - GPUREG_GSH_FLOATUNIFORM_DATA(0..7) (W) |
|                                                                       |
|   10401A6Ch       - PICA(029Bh)   - GPUREG_GSH_CODETRANSFER_INDEX (W) |
|       104                                                             |
| 01A70h+i*4   - PICA(029Ch+i) - GPUREG_GSH_CODETRANSFER_DATA(0..7) (W) |
|       10401A94h       - PICA(02A5h)   - GPUREG_GSH_OPDESCS_INDEX (W)  |
|                                                                       |
|   10401A98h+i*4   - PICA(02A6h+i) - GPUREG_GSH_OPDESCS_DATA(0..7) (W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Shader 1 (Vertex Shader)**

```
+-----------------------------------------------------------------------+
|       10401AC0h       - PICA(02B0h)   - GPUREG_VSH_BOOLUNIFORM (R/W)  |
|                                                                       |
|  10401AC4h+i*4   - PICA(02B1h+i) - GPUREG_VSH_INTUNIFORM_I0..I3 (R/W) |
|                                                                       |
| 10401AE4h       - PICA(02B9h)   - GPUREG_VSH_INPUTBUFFER_CONFIG (R/W) |
|       10401AE8h       - PICA(02BAh)   - GPUREG_VSH_ENTRYPOINT (R/W)   |
|       10                                                              |
| 401AECh       - PICA(02BBh)   - GPUREG_VSH_ATTR_PERMUTATION_LOW (R/W) |
|       104                                                             |
| 01AF0h       - PICA(02BCh)   - GPUREG_VSH_ATTR_PERMUTATION_HIGH (R/W) |
|       10401AF4h       - PICA(02BDh)   - GPUREG_VSH_OUTMAP_MASK (R/W)  |
|                                                                       |
|     10401AFCh       - PICA(02BFh)   - GPUREG_VSH_CODETRANSFER_END (W) |
|                                                                       |
|   10401B00h       - PICA(02C0h)   - GPUREG_VSH_FLOATUNIFORM_INDEX (W) |
|       104                                                             |
| 01B04h+i*4   - PICA(02C1h+i) - GPUREG_VSH_FLOATUNIFORM_DATA(0..7) (W) |
|                                                                       |
|   10401B2Ch       - PICA(02CBh)   - GPUREG_VSH_CODETRANSFER_INDEX (W) |
|       104                                                             |
| 01B30h+i*4   - PICA(02CCh+i) - GPUREG_VSH_CODETRANSFER_DATA(0..7) (W) |
|       10401B54h       - PICA(02D5h)   - GPUREG_VSH_OPDESCS_INDEX (W)  |
|                                                                       |
|   10401B58h+i*4   - PICA(02D6h+i) - GPUREG_VSH_OPDESCS_DATA(0..7) (W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Shader 2 (Unknown purpose)**

```
+-----------------------------------------------------------------------+
|       10401B80h       - PICA(02E0h)   - GPUREG_VSH2_BOOLUNIFORM (R/W) |
|                                                                       |
| 10401B84h+i*4   - PICA(02E1h+i) - GPUREG_VSH2_INTUNIFORM_I0..I3 (R/W) |
|       1                                                               |
| 0401BA4h       - PICA(02E9h)   - GPUREG_VSH2_INPUTBUFFER_CONFIG (R/W) |
|       10401BA8h       - PICA(02EAh)   - GPUREG_VSH2_ENTRYPOINT (R/W)  |
|       104                                                             |
| 01BACh       - PICA(02EBh)   - GPUREG_VSH2_ATTR_PERMUTATION_LOW (R/W) |
|       1040                                                            |
| 1BB0h       - PICA(02ECh)   - GPUREG_VSH2_ATTR_PERMUTATION_HIGH (R/W) |
|       10401BB4h       - PICA(02EDh)   - GPUREG_VSH2_OUTMAP_MASK (R/W) |
|                                                                       |
|    10401BBCh       - PICA(02EFh)   - GPUREG_VSH2_CODETRANSFER_END (W) |
|                                                                       |
|  10401BC0h       - PICA(02F0h)   - GPUREG_VSH2_FLOATUNIFORM_INDEX (W) |
|       1040                                                            |
| 1BC4h+i*4   - PICA(02F1h+i) - GPUREG_VSH2_FLOATUNIFORM_DATA(0..7) (W) |
|                                                                       |
|  10401BECh       - PICA(02FBh)   - GPUREG_VSH2_CODETRANSFER_INDEX (W) |
|       1040                                                            |
| 1BF0h+i*4   - PICA(02FCh+i) - GPUREG_VSH2_CODETRANSFER_DATA(0..7) (W) |
|       10401C14h       - PICA(0305h)   - GPUREG_VSH2_OPDESCS_INDEX (W) |
|                                                                       |
|  10401C18h+i*4   - PICA(0306h+i) - GPUREG_VSH2_OPDESCS_DATA(0..7) (W) |
+-----------------------------------------------------------------------+
```

**3DS GPU Internal Registers - Shader 3 (Unknown purpose)**

```
+-----------------------------------------------------------------------+
|       10401C40h       - PICA(0310h)   - GPUREG_VSH3_BOOLUNIFORM (R/W) |
|                                                                       |
| 10401C44h+i*4   - PICA(0311h+i) - GPUREG_VSH3_INTUNIFORM_I0..I3 (R/W) |
|       1                                                               |
| 0401C64h       - PICA(0319h)   - GPUREG_VSH3_INPUTBUFFER_CONFIG (R/W) |
|       10401C68h       - PICA(031Ah)   - GPUREG_VSH3_ENTRYPOINT (R/W)  |
|       104                                                             |
| 01C6Ch       - PICA(031Bh)   - GPUREG_VSH3_ATTR_PERMUTATION_LOW (R/W) |
|       1040                                                            |
| 1C70h       - PICA(031Ch)   - GPUREG_VSH3_ATTR_PERMUTATION_HIGH (R/W) |
|       10401C74h       - PICA(031Dh)   - GPUREG_VSH3_OUTMAP_MASK (R/W) |
|                                                                       |
|    10401C7Ch       - PICA(031Fh)   - GPUREG_VSH3_CODETRANSFER_END (W) |
|                                                                       |
|  10401C80h       - PICA(0320h)   - GPUREG_VSH3_FLOATUNIFORM_INDEX (W) |
|       1040                                                            |
| 1C84h+i*4   - PICA(0321h+i) - GPUREG_VSH3_FLOATUNIFORM_DATA(0..7) (W) |
|                                                                       |
|  10401CACh       - PICA(032Bh)   - GPUREG_VSH3_CODETRANSFER_INDEX (W) |
|       1040                                                            |
| 1CB0h+i*4   - PICA(032Ch+i) - GPUREG_VSH3_CODETRANSFER_DATA(0..7) (W) |
|       10401CD4h       - PICA(0335h)   - GPUREG_VSH3_OPDESCS_INDEX (W) |
|                                                                       |
|  10401CD8h+i*4   - PICA(0336h+i) - GPUREG_VSH3_OPDESCS_DATA(0..7) (W) |
+-----------------------------------------------------------------------+
```




