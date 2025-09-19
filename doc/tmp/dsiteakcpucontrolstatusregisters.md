# DSi Teak CPU Control/Status Registers


There are two sets of Control/Status registers

```
+-------------------------------------------------------------------------------+
|       Old registers (for TeakLite):   st0/st1/st2, and icr                    |
|       New registers (for TeakLiteII): stt0/stt1/stt2, and mod0/mod1/mod2/mod3 |
+-------------------------------------------------------------------------------+
```

The new registers do contain only a few new bits, apart from that they are basically same as the old registers (with the old bits rearranged to different locations in the new registers).
The old registers do still exist on TeakLiteII, so one could use either old or new registers (all reads/writes will be mirrored to both register sets).
However, there are a few cases where writing the old registers may smash bits in new registers (writing the old \"limit\" bit will change BOTH of the new \"limit\" bits, changing \"ps\" versus \"ps01\" may also involve strange effects, and\... changing \"a0e/a1e\" bits seems to have \"weird\" effects on a0l/a0h/a1l/a1h, or maybe that\'s some \"wanted\" saturation effect?).

### CPU Flags (for Cond opcodes)
CPU Flags are stored in st0 register (with mirrors in stt0/stt1). The flags can be used for conditional opcodes (with \"Cond\" operand). According to TeakLite datasheet, the flags are affected somewhat like this:

```
+-------------------------------------------------------------------------------------+
|       ZMNVCEL- add, addh, addl, cmp, cmpu, sub, subh, subl, inc, dec, neg           |
|       ZMNVCEL- maa, maasu, mac, macsu, macus, macuu, msu, sqra, rnd, pacr, movr     |
|       ZMN-C--- or                                                                   |
|       ZM--C--- addv, cmpv, subv, and                                                |
|       ZMN--E-- clr, clrr, copy, divs, swap, not, xor                                |
|       ZMN--0L- lim                                                                  |
|       ZMNVCELR norm                                                                 |
|       ZMN-CE-- rol, ror                                                             |
|       ZMN-CE-- movs, movsi, shfc, shfi, shl, shl4, shr, shr4  ;for logical shift    |
|       ZMNVCEL- movs, movsi, shfc, shfi, shl, shl4, shr, shr4  ;for arithmetic shift |
|       ZMN--E-- mov, movp, pop        ;when dst=ac,bc (whut?)         ;\             
|       xxxxxxxx mov, movp, pop        ;when dst=st0                   ; mov etc.     |
|       ------L- mov, push             ;when src=aXL,aXH,bXL,bXH       ;              |
|       -------- mov, movp, pop, push  ;when src/dst neither of above  ;/             |
|       ZMN--E-- cntx s  ;store shadows (new flags for a1)             ;\cntx         
|       ZMNVCELR cntx r  ;restore shadows (old flags)                  ;/             |
|       ZM------ set, rst, chng                                                       |
|       Z------- tst0, tst1, tstb                                                     |
|       -M------ max, maxd, min                                                       |
|       -------R modr                                                                 |
|       -------- mpy, mpyi, mpysu, sqr, exp                                           |
|       -------- banke, dint, eint, load, nop, bkrep, rep, break, trap, movd          |
|       -------- br, brr, call, calla, callr, ret, retd, reti, retid, rets            |
+-------------------------------------------------------------------------------------+
```

Flags for new TL2 opcodes aren\'t officially documented; some might follow the above rules (eg. the new \"r6\" register should act as old \"r0-r5\"), but other new opcodes might do this or that.


```
+-------------------------------------------------------------------------------------+
|      __________________________ Old registers (TeakLite) __________________________ |
+-------------------------------------------------------------------------------------+
```


### st0 - Old TL1 Status/Control Register st0

```
+----------------------------------------------------------------------------------+
|       0     SAT  R/W Saturation Mode  (0=Off, 1=Saturate "Ax to data") ;mod0.0   |
|       1     IE   R/W Interrupt Enable (0=Disable, 1=Enable) ;dint/eint ;mod3.7   |
|       2     IM0  R/W Interrupt INT0 Mask (0=Disable, 1=Enable if IE=1) ;mod3.8   |
|       3     IM1  R/W Interrupt INT1 Mask (0=Disable, 1=Enable if IE=1) ;mod3.9   |
|       4     R    R/W Flag: rN is Zero   ;see Cond nr                   ;stt1.4   |
|       5     L    R/W Flag: Limit        ;see Cond l      ;L=(LM or VL) ;stt0.0+1 |
|       6     E    R/W Flag: Extension    ;see Cond e                    ;stt0.2   |
|       7     C    R/W Flag: Carry        ;see Cond c                    ;stt0.3   |
|       8     V    R/W Flag: Overflow     ;see Cond v                    ;stt0.4   |
|       9     N    R/W Flag: Normalized   ;see Cond nn                   ;stt0.5   |
|       10    M    R/W Flag: Minus        ;see Cond gt,ge,lt,le          ;stt0.6   |
|       11    Z    R/W Flag: Zero         ;see Cond eq,neq,gt,le         ;stt0.7   |
|       12-15 a0e  R/W Accumulator 0 Extension Bits                      ;a0.32-35 |
+----------------------------------------------------------------------------------+
```


### st1 - Old TL1 Status/Control Register st1

```
+------------------------------------------------------------------------------------+
|       0-7   PAGE R/W Data Memory Page (for MemImm8) (see "load page")  ;mod1.0-7   |
|       8-9   -    -   Reserved (read: always set)                       ;-          |
|       10-11 PS   R/W Product Shifter for P0 (see "load ps")(multiply?) ;mod0.10-11 |
|                        (0=No Shift, 1=SHR1, 2=SHL1, 3=SHL2)                        |
|       12-15 a1e  R/W Accumulator 1 Extension Bits                      ;a1.32-35   |
+------------------------------------------------------------------------------------+
```


### st2 - Old TL1 Status/Control Register st2

```
+----------------------------------------------------------------------------------+
|       0-3   MDn  R/W Enable cfgi.modi modulo for R0..R3 (0=Off, 1=On)  ;mod2.0-3 |
|       4-5   MDn  R/W Enable cfgj.modj modulo for R4..R5 (0=Off, 1=On)  ;mod2.4-5 |
|       6     IM2  R/W Interrupt INT2 Mask (0=Disable, 1=Enable if IE=1) ;mod3.10  |
|       7     S    R/W Shift Mode (0=Arithmetic, 1=Logic)                ;mod0.7   |
|       8     OU0  R/W OUSER0 User Output Pin                            ;mod0.8   |
|       9     OU1  R/W OUSER1 User Output Pin                            ;mod0.9   |
|       10    IU0  R   IUSER0 User Input Pin (zero)  ;see Cond iu0,niu0  ;stt1.??  |
|       11    IU1  R   IUSER1 User Input Pin (zero)  ;see Cond iu1       ;stt1.??  |
|       12    -    -   Reserved (read: always set)                       ;-        |
|       13    IP2  R   Interrupt Pending INT2 (0=No, 1=IRQ)              ;stt2.2   |
|       14    IP0  R   Interrupt Pending INT0 (0=No, 1=IRQ)              ;stt2.0   |
|       15    IP1  R   Interrupt Pending INT1 (0=No, 1=IRQ)              ;stt2.1   |
+----------------------------------------------------------------------------------+
```


### icr - Old TL1 Interrupt Context and Repeat Nesting

```
+------------------------------------------------------------------------------------+
|       0     NMIC R/W NMI Context switching enable  (0=Off, 1=On)       ;mod3.0     |
|       1     IC0  R/W INT0 Context switching enable (0=Off, 1=On)       ;mod3.1     |
|       2     IC1  R/W INT1 Context switching enable (0=Off, 1=On)       ;mod3.2     |
|       3     IC2  R/W INT2 Context switching enable (0=Off, 1=On)       ;mod3.3     |
|       4     LP   R   InLoop (when inside one or more "bkrep" loops)    ;stt2.15    |
|       5-7   BCn  R   Block repeat nest. counter ;see "bkrep"           ;stt2.12-14 |
|       8-15  -    -   Reserved (read: always set)                       ;-          |
+------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________________ New registers (TeakLiteII) _________________________ |
+-------------------------------------------------------------------------------------+
```


### stt0 - New TL2 Status/Control Register stt0 (CPU Flags)

```
+------------------------------------------------------------------------------------+
|       0     LM   R/W Flag: Limit, set if saturation has/had occured    ;st0.5      |
|       1     VL   R/W Flag: LatchedV, set if overflow has/had occurred  ;st0.5, too |
|       2     E    R/W Flag: Extension    ;see Cond e                    ;st0.6      |
|       3     C    R/W Flag: Carry        ;see Cond c                    ;st0.7      |
|       4     V    R/W Flag: Overflow     ;see Cond v                    ;st0.8      |
|       5     N    R/W Flag: Normalized   ;see Cond nn                   ;st0.9      |
|       6     M    R/W Flag: Minus        ;see Cond gt,ge,lt,le          ;st0.10     |
|       7     Z    R/W Flag: Zero         ;see Cond eq,neq,gt,le         ;st0.11     |
|       8-10  -    -   Unknown (reads as zero)                                       |
|       11    C1   R/W Flag: Carry1 (2nd carry, for dual-operation opcodes)          |
|       12-15 -    -   Unknown (reads as zero)                                       |
+------------------------------------------------------------------------------------+
```


### stt1 - New TL2 Status/Control Register stt1 (whatever)

```
+------------------------------------------------------------------------------------+
|       0-3   -    -   Unknown (reads as zero)                                       |
|       4     R    R/W Flag: rN is Zero   ;see Cond nr                   ;st0.4      |
|       5-13  -    -   Unknown (reads as zero)  (IU1 and IU0 should be here!)        |
|       14    P0E  R/W Upper bit of 33bit P0 register  ;\shifted-in on        ;p0.32 
|       15    P1E  R/W Upper bit of 33bit P1 register  ;/arith right shifts   ;p1.32 |
+------------------------------------------------------------------------------------+
```

Note: bit14/bit15 are automatically sign-expanded when moving data to p0/p0h/p1.

### stt2 - New TL2 Status/Control Register stt2 (Interrupt/ProgBank/Bkrep)

```
+------------------------------------------------------------------------------------+
|       0     IP0  R   Interrupt Pending INT0 (0=No, 1=IRQ)              ;st2.14     |
|       1     IP1  R   Interrupt Pending INT1 (0=No, 1=IRQ)              ;st2.15     |
|       2     IP2  R   Interrupt Pending INT2 (0=No, 1=IRQ)              ;st2.13     |
|       3     IPV  R   Interrupt Pending VINT                            ;-          |
|       4-5   -    -   Unknown (reads as zero)                           ;-          |
|       6-7  PCMhi R/W Program Memory Bank (for ProgMemRn/ProgMemAxl) ("load movpd") |
|       8-11  -    -   Unknown (reads as zero)                           ;-          |
|       12-14 BCn  R   Block repeat nest. counter ;see "bkrep"           ;icr.5-7    |
|       15    LP   R   InLoop (when inside one or more "bkrep" loops)    ;icr.4      |
+------------------------------------------------------------------------------------+
```


### mod0 - New TL2 Status/Control Register mod0 (Misc)

```
+-----------------------------------------------------------------------------------+
|       0     SAT  R/W Saturation Mode (0=Off, 1=Saturate "Ax to data"?) ;st0.0     |
|       1     SATA R/W Saturation Mode on store (0=Off, 1="(Ax op data) to Ax"?)    |
|       2     ?    R   Unknown (reads as one)                                       |
|       3     -    -   Unknown (reads as zero)                                      |
|       4     -    -   Unknown (reads as zero)                                      |
|       5-6   HWM  R/W Halfword Multiply    ... Modify y0 (and y1?)                 |
|                       0=read y0/y1 directly (full 16bit words)                    |
|                       1=Takes y0>>8 and y1>>8 (logic shift)                       |
|                       2=Takes y0&0xFF and y1&0xFF                                 |
|                       3=Takes y0>>8 and y1&&0xFF                                  |
|       7     S    R/W Shift Mode (0=Arithmetic, 1=Logic)                ;st2.7     |
|       8     OU0  R/W OUSER0 User Output Pin                            ;st2.8     |
|       9     OU1  R/W OUSER1 User Output Pin                            ;st2.9     |
|       10-11 PS0  R/W Product Shifter for P0 (see "load ps")(multiply?) ;st1.10-11 |
|       12    -    -   Unknown (reads as zero)                                      |
|       13-14 PS1  R/W Product Shifter for P1 (see "load ps")(multiply?)            |
|       15    -    -   Unknown (reads as zero)                                      |
+-----------------------------------------------------------------------------------+
```


### mod1 - New TL2 Status/Control Register mod1 (Data Page)

```
+-------------------------------------------------------------------------------------+
|       0-7   PAGE R/W Data Memory Page (for MemImm8) (see "load page")  ;st1.0-7     |
|       8-11  -    -   Unknown (reads as zero)                                        |
|       12   STP16 R/W banke opcode (0=exchange cfgi/cfgj, 1=cfgi/cfgj+stepi0/stepj0) |
|                       1=use stepi0/j0 instead of stepi/j for stepping Rn registers  |
|       13    CMD  R/W Change Modulo mode (0=New TL2 style, 1=TL1 style)              |
|       14    EPI  R/W Unknown (1=Set R3=0 after any "modr R3" or "access[R3]"?)      |
|       15    EPJ  R/W Unknown (1=Set R7=0 after any "modr R7" or "access[R7]"?)      |
+-------------------------------------------------------------------------------------+
```


### mod2 - New TL2 Status/Control Register mod2 (Modulo Enable)

```
+---------------------------------------------------------------------------------+
|       0-3   MDn  R/W Enable cfgi.modi modulo for R0..R3 (0=Off, 1=On)  ;st2.0-3 |
|       4-5   MDn  R/W Enable cfgj.modj modulo for R4..R5 (0=Off, 1=On)  ;st2.4-5 |
|       6-7   MDn  R/W Enable cfgj.modj modulo for R6..R7 (0=Off, 1=On) ;TL2 only |
|       8-11  BRn  R/W Step +s for R0..R3 (0=cfgi.stepi, 1=stepi0)                |
|       12-15 BRn  R/W Step +s for R4..R7 (0=cfgj.stepi, 1=stepj0)                |
+---------------------------------------------------------------------------------+
```

XXX\... bit8-9 seem to mess up my code (that uses r0/r1, but only with +0 step).
\"When BRn=1, memory access through Rn will use the bit-reversed value of Rn as the address. Note that this also implies that stepi0/j0 will be used, regardless of what STP16 says.\"

### mod3 - New TL2 Status/Control Register mod3 (Interrupt Control)

```
+---------------------------------------------------------------------------------+
|       0     NMIC R/W NMI Context switching enable  (0=Off, 1=On)       ;icr.0   |
|       1     IC0  R/W INT0 Context switching enable (0=Off, 1=On)       ;icr.1   |
|       2     IC1  R/W INT1 Context switching enable (0=Off, 1=On)       ;icr.2   |
|       3     IC2  R/W INT2 Context switching enable (0=Off, 1=On)       ;icr.3   |
|       4     OU2  R/W Unknown (R/W)                                              |
|       5     OU3  R/W Unknown (R/W)                                              |
|       6     OU4  ?   ---DANGER BIT--- (1=hangs/crashes when set)                |
|       7     IE   R/W Interrupt Enable (0=Disable, 1=Enable) ;dint/eint ;st0.1   |
|       8     IM0  R/W Interrupt INT0 Mask (0=Disable, 1=Enable if IE=1) ;st0.2   |
|       9     IM1  R/W Interrupt INT1 Mask (0=Disable, 1=Enable if IE=1) ;st0.3   |
|       10    IM2  R/W Interrupt INT2 Mask (0=Disable, 1=Enable if IE=1) ;st2.6   |
|       11    IMV  R/W Interrupt VINT Mask (0=Disable, 1=Enable if IE=1?)         |
|       12    -    -   Unknown (reads as zero)                                    |
|       13   CCNTA R/W Unknown (R/W)                                              |
|       14    CPC  R/W Stack word order for PC on call/ret (0=Normal, 1=Reversed) |
|       15    CREP R/W Unknown (R/W)                                              |
+---------------------------------------------------------------------------------+
```

Bit14=0: push lowword then push highword on call; pop highword then pop lowword on ret.



