# DSi Atheros Wifi - Xtensa CPU Optional MAC16 Opcodes


### MAC16 Option

```
+-------------------------------------------------------------------------------------+
|       mw = m0..m3                                                                   |
|       mx = m0..m1                                                                   |
|       my = m2..m3                                                                   |
|       as,at = a0..a15                                                               |
|       acc = special register acchi(8bit):acclo(32bit)                               |
|       700st4h  UMUL.AA.LL as,at             umul    acc,as_l,at_l   ;\              
|       710st4h  UMUL.AA.HL as,at             umul    acc,as_h,at_l   ; Unsigned Mul  |
|       720st4h  UMUL.AA.LH as,at             umul    acc,as_l,at_h   ; acc=as*at     |
|       730st4h  UMUL.AA.HH as,at             umul    acc,as_h,at_h   ;/              |
|       24x0y4h  MUL.DD.LL  mx,my             smul    acc,mx_l,my_l   ;\              
|       25x0y4h  MUL.DD.HL  mx,my             smul    acc,mx_h,my_l   ; Signed Mul    |
|       26x0y4h  MUL.DD.LH  mx,my             smul    acc,mx_l,my_h   ; acc=mx*my     |
|       27x0y4h  MUL.DD.HH  mx,my             smul    acc,mx_h,my_h   ;/              |
|       340sy4h  MUL.AD.LL  as,my             smul    acc,as_l,my_l   ;\              
|       350sy4h  MUL.AD.HL  as,my             smul    acc,as_h,my_l   ; Signed Mul    |
|       360sy4h  MUL.AD.LH  as,my             smul    acc,as_l,my_h   ; acc=as*my     |
|       370sy4h  MUL.AD.HH  as,my             smul    acc,as_h,my_h   ;/              |
|       64x0t4h  MUL.DA.LL  mx,at             smul    acc,mx_l,at_l   ;\              
|       65x0t4h  MUL.DA.HL  mx,at             smul    acc,mx_h,at_l   ; Signed Mul    |
|       66x0t4h  MUL.DA.LH  mx,at             smul    acc,mx_l,at_h   ; acc=mx*at     |
|       67x0t4h  MUL.DA.HH  mx,at             smul    acc,mx_h,at_h   ;/              |
|       740st4h  MUL.AA.LL  as,at             smul    acc,as_l,at_l   ;\              
|       750st4h  MUL.AA.HL  as,at             smul    acc,as_h,at_l   ; Signed Mul    |
|       760st4h  MUL.AA.LH  as,at             smul    acc,as_l,at_h   ; acc=as*at     |
|       770st4h  MUL.AA.HH  as,at             smul    acc,as_h,at_h   ;/              |
|       28x0y4h  MULA.DD.LL mx,my             smuladd acc,mx_l,my_l   ;\              
|       29x0y4h  MULA.DD.HL mx,my             smuladd acc,mx_h,my_l   ; Signed MulAdd |
|       2Ax0y4h  MULA.DD.LH mx,my             smuladd acc,mx_l,my_h   ; acc=acc+mx*my |
|       2Bx0y4h  MULA.DD.HH mx,my             smuladd acc,mx_h,my_h   ;/              |
|       380sy4h  MULA.AD.LL as,my             smuladd acc,as_l,my_l   ;\              
|       390sy4h  MULA.AD.HL as,my             smuladd acc,as_h,my_l   ; Signed MulAdd |
|       3A0sy4h  MULA.AD.LH as,my             smuladd acc,as_l,my_h   ; acc=acc+as*my |
|       3B0sy4h  MULA.AD.HH as,my             smuladd acc,as_h,my_h   ;/              |
|       68x0t4h  MULA.DA.LL mx,at             smuladd acc,mx_l,at_l   ;\              
|       69x0t4h  MULA.DA.HL mx,at             smuladd acc,mx_h,at_l   ; Signed MulAdd |
|       6Ax0t4h  MULA.DA.LH mx,at             smuladd acc,mx_l,at_h   ; acc=acc+mx*at |
|       6Bx0t4h  MULA.DA.HH mx,at             smuladd acc,mx_h,at_h   ;/              |
|       780st4h  MULA.AA.LL as,at             smuladd acc,as_l,at_l   ;\              
|       790st4h  MULA.AA.HL as,at             smuladd acc,as_h,at_l   ; Signed MulAdd |
|       7A0st4h  MULA.AA.LH as,at             smuladd acc,as_l,at_h   ; acc=acc+as*at |
|       7B0st4h  MULA.AA.HH as,at             smuladd acc,as_h,at_h   ;/              |
|       2Cx0y4h  MULS.DD.LL mx,my             smulsub acc,mx_l,my_l   ;\              
|       2Dx0y4h  MULS.DD.HL mx,my             smulsub acc,mx_h,my_l   ; Signed MulSub |
|       2Ex0y4h  MULS.DD.LH mx,my             smulsub acc,mx_l,my_h   ; acc=acc-mx*my |
|       2Fx0y4h  MULS.DD.HH mx,my             smulsub acc,mx_h,my_h   ;/              |
|       3C0sy4h  MULS.AD.LL as,my             smulsub acc,as_l,my_l   ;\              
|       3D0sy4h  MULS.AD.HL as,my             smulsub acc,as_h,my_l   ; Signed MulSub |
|       3E0sy4h  MULS.AD.LH as,my             smulsub acc,as_l,my_h   ; acc=acc-as*my |
|       3F0sy4h  MULS.AD.HH as,my             smulsub acc,as_h,my_h   ;/              |
|       6Cx0t4h  MULS.DA.LL mx,at             smulsub acc,mx_l,at_l   ;\              
|       6Dx0t4h  MULS.DA.HL mx,at             smulsub acc,mx_h,at_l   ; Signed MulSub |
|       6Ex0t4h  MULS.DA.LH mx,at             smulsub acc,mx_l,at_h   ; acc=acc-mx*at |
|       6Fx0t4h  MULS.DA.HH mx,at             smulsub acc,mx_h,at_h   ;/              |
|       7C0st4h  MULS.AA.LL as,at             smulsub acc,as_l,at_l   ;\              
|       7D0st4h  MULS.AA.HL as,at             smulsub acc,as_h,at_l   ; Signed MulSub |
|       7E0st4h  MULS.AA.LH as,at             smulsub acc,as_l,at_h   ; acc=acc-as*at |
|       7F0st4h  MULS.AA.HH as,at             smulsub acc,as_h,at_h   ;/              |
|       80ws04h  LDINC      mw,as             movupd  mw,[as+4]       ;Load+AutoInc   |
|       90ws04h  LDDEC      mw,as             movupd  mw,[as-4]       ;Load+AutoDec   |
+-------------------------------------------------------------------------------------+
```

Below opcodes are doing two separate things:
1. acc=acc+x\*y ;Signed MulAdd
2. as=as+/-4, mw=\[as\] ;Load mw from memory (for use by NEXT opcode)

```
+------------------------------------------------------------------------------------+
|       08wsy4h  MULA.DD.LL.LDINC mw,as,mx,my smuladd_movupd acc,mx_l,my_l,mw,[as+4] |
|       09wsy4h  MULA.DD.HL.LDINC mw,as,mx,my smuladd_movupd acc,mx_h,my_l,mw,[as+4] |
|       0Awsy4h  MULA.DD.LH.LDINC mw,as,mx,my smuladd_movupd acc,mx_l,my_h,mw,[as+4] |
|       0Bwsy4h  MULA.DD.HH.LDINC mw,as,mx,my smuladd_movupd acc,mx_h,my_h,mw,[as+4] |
|       18wsy4h  MULA.DD.LL.LDDEC mw,as,mx,my smuladd_movupd acc,mx_l,my_l,mw,[as-4] |
|       19wsy4h  MULA.DD.HL.LDDEC mw,as,mx,my smuladd_movupd acc,mx_h,my_l,mw,[as-4] |
|       1Awsy4h  MULA.DD.LH.LDDEC mw,as,mx,my smuladd_movupd acc,mx_l,my_h,mw,[as-4] |
|       1Bwsy4h  MULA.DD.HH.LDDEC mw,as,mx,my smuladd_movupd acc,mx_h,my_h,mw,[as-4] |
|       48wst4h  MULA.DA.LL.LDINC mw,as,mx,at smuladd_movupd acc,mx_l,at_l,mw,[as+4] |
|       49wst4h  MULA.DA.HL.LDINC mw,as,mx,at smuladd_movupd acc,mx_h,at_l,mw,[as+4] |
|       4Awst4h  MULA.DA.LH.LDINC mw,as,mx,at smuladd_movupd acc,mx_l,at_h,mw,[as+4] |
|       4Bwst4h  MULA.DA.HH.LDINC mw,as,mx,at smuladd_movupd acc,mx_h,at_h,mw,[as+4] |
|       58wst4h  MULA.DA.LL.LDDEC mw,as,mx,at smuladd_movupd acc,mx_l,at_l,mw,[as-4] |
|       59wst4h  MULA.DA.HL.LDDEC mw,as,mx,at smuladd_movupd acc,mx_h,at_l,mw,[as-4] |
|       5Awst4h  MULA.DA.LH.LDDEC mw,as,mx,at smuladd_movupd acc,mx_l,at_h,mw,[as-4] |
|       5Bwst4h  MULA.DA.HH.LDDEC mw,as,mx,at smuladd_movupd acc,mx_h,at_h,mw,[as-4] |
+------------------------------------------------------------------------------------+
```




