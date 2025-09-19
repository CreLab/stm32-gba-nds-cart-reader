# DSi Atheros Wifi - Xtensa CPU Optional Floating-Point Opcodes


**Float Option**

```
+-----------------------------------------------------------------------+
|       08                                                              |
- | rst0h  LSX      fr,as,at    f_mov    fr,[as+at]     LoadSingleIndexed |
|       ii0s                                                            |
- | t3h  LSI      ft,as,imm*4 f_mov    ft,[as+imm8*4] LoadSingleImmediate |
|       48rst                                                           |
- | 0h  SSX      fr,as,at    f_mov    [as+at],fr     Store Single Indexed |
|       ii4st3                                                          |
- | h  SSI      ft,as,imm*4 f_mov    [as+imm8*4],ft Store Single Immedia. |
|       18rst0                                                          |
- | h  LSXU     fr,as,at    f_movupd fr,[as+at]     LoadSingleIndexed+Upd |
|       ii8st                                                           |
- | 3h  LSIU     ft,as,imm*4 f_movupd ft,[as+imm8*4] LoadSingleImm+Update |
|       58rst0                                                          |
- | h  SSXU     fr,as,at    f_movupd [as+at],fr     Store Single Indx+Upd |
|       iiCst3                                                          |
- | h  SSIU     ft,as,imm*4 f_movupd [as+imm8*4],ft Store Single Imm+Upd. |
|                                                                       |
|      0Arst0h  ADD.S    fr,fs,ft    f_add      fr,fs,ft     Add Single |
|                                                                       |
| 1Arst0h  SUB.S    fr,fs,ft    f_sub      fr,fs,ft     Subtract Single |
|                                                                       |
|  2Arst0h  MUL.S    fr,fs,ft    f_mul      fr,fs,ft     Multipy Single |
|       4Ars                                                            |
| t0h  MADD.S   fr,fs,ft    f_muladd   fr,fs,ft     Multiply+Add Single |
|       5Ars                                                            |
| t0h  MSUB.S   fr,fs,ft    f_mulsub   fr,fs,ft     Multiply+Sub Single |
|       8Arsi0                                                          |
| h  ROUND.S  ar,fs,imm4  f_round    ar,fs,pow4   Round Single to Fixed |
|       9Arsi0                                                          |
| h  TRUNC.S  ar,fs,imm4  f_trunc    ar,fs,pow4   TruncateSingleToFixed |
|       EArsi0                                                          |
| h  UTRUNC.S ar,fs,imm4  f_utrunc   ar,fs,pow4   UnsignedTruncatetoFix |
|       AAr                                                             |
| si0h  FLOOR.S  ar,fs,imm4  f_floor    ar,fs,pow4   FloorSingleToFixed |
|       BArsi0                                                          |
| h  CEIL.S   ar,fs,imm4  f_ceil     ar,fs,pow4   Ceiling SingleToFixed |
|       CArsi                                                           |
| 0h  FLOAT.S  fr,as,imm4  f_float    fr,as,frac4  ConvertFixedToSingle |
|       DArsi0                                                          |
| h  UFLOAT.S fr,as,imm4  f_ufloat   fr,as,frac4  UnsignedFixedToSingle |
|                                                                       |
|     FArs00h  MOV.S    fr,fs       f_mov      fr,fs        Move Single |
|       FArs10                                                          |
| h  ABS.S    fr,fs       f_abs      fr,fs        Absolute Value Single |
|                                                                       |
|   FArs40h  RFR      ar,fs       f_mov      ar,fs        Move FR to AR |
|                                                                       |
|   FArs50h  WFR      fr,as       f_mov      fr,as        Move AR to FR |
|                                                                       |
|   FArs60h  NEG.S    fr,fs       f_neg      fr,fs        Negate Single |
|       1Brs                                                            |
| t0h  UN.S     br,fs,ft    f_cmp_un   br,fs,ft     CompareSingle Unord |
|       2Brs                                                            |
| t0h  OEQ.S    br,fs,ft    f_cmp_oeq  br,fs,ft     CompareSingle Equal |
|       3Brst0                                                          |
| h  UEQ.S    br,fs,ft    f_cmp_ueq  br,fs,ft     CompareSingle UnordEq |
|       4Brs                                                            |
| t0h  OLT.S    br,fs,ft    f_cmp_olt  br,fs,ft     CompareSingle OrdLt |
|       5Brst                                                           |
| 0h  ULT.S    br,fs,ft    f_cmp_ult  br,fs,ft     CompareSingle UnorLt |
|       6Brst0h                                                         |
|   OLE.S    br,fs,ft    f_cmp_ole  br,fs,ft     CompareSingle OrdLt/Eq |
|       7Brst0h                                                         |
|   ULE.S    br,fs,ft    f_cmp_ule  br,fs,ft     CompareSingle UnorLtEq |
|       8Brs                                                            |
| t0h  MOVEQZ.S fr,fs,at    f_movz     at,fr,fs     Move Single if at=0 |
|       9Brst                                                           |
| 0h  MOVNEZ.S fr,fs,at    f_movnz    at,fr,fs     Move Single if at<>0 |
|       ABrs                                                            |
| t0h  MOVLTZ.S fr,fs,at    f_movs     at,fr,fs     Move Single if at<0 |
|       BBrst                                                           |
| 0h  MOVGEZ.S fr,fs,at    f_movns    at,fr,fs     Move Single if at>=0 |
|       CBrs                                                            |
| t0h  MOVF.S   fr,fs,bt    f_movz     bt,fr,fs     Move Single if bt=0 |
|       DBrs                                                            |
| t0h  MOVT.S   fr,fs,bt    f_movnz    bt,fr,fs     Move Single if bt=1 |
+-----------------------------------------------------------------------+
```

pow4: (imm: opcode.bit7..4 = 0..15 aka (1 shl 0..15) aka 1..8000h)
frac4: (imm: opcode.bit7..4 = 0..15 aka (1 shr 0..15) aka 1..1/8000h)



