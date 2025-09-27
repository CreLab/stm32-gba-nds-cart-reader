# DSi TeakLite II Operand Encoding


### Syntax Notes
The official Teak syntax specifies all operands in \"source,dest\" order, that\'s opposite of most other ASM languages which use \"dest,source\" order (except 68000 processors, which the Teak is apparently inspired on). One exception are instructions tagged \"NoReverse\" in the opcode list: These ones do have the operands ordered as how one would usually expect them.
Operands tagged as \"Implied xx\" are effectively used by the hardware, although the official syntax doesn\'t specify them in source code. On the other hand, operands tagged as \"Bogus xx\" are specified in official source code syntax, although the hardware doesn\'t actually use that operands in that form.
The nocash (dis-)assembler syntax reverses the operand order (except those flagged as NoReverse), removes Bogus operands, and inserts Implied operands. Moreover, immediates and memory operands are specified differently\...

### Memory Operands

```
+-----------------------------------------------------------------------+
|       name          native                  nocash                    |
|       MemRn         (Rn)                    [Rn]                      |
|       MemSp         (sp)                    [sp]                      |
|       ProgMemRn     (Rn)                    [code:movpd:Rn]           |
|       ProgMemAxl    (Axl)                   [code:movpd:Axl]          |
|       ProgMemAx     (Ax)                    [code:Ax]                 |
|       ProgMemAx_..  (Ax),(Ax+)              [code:Ax]:[code:Ax+]      |
|       MemImm8       0xNN                    [page:NNh]                |
|       MemImm16      [##0xNNNN]              [NNNNh]                   |
|       MemR7Imm7s    (r7+#0xNN), (r7+#-NNN)  [r7+/-NNh]                |
|       MemR7Imm16    (r7+##0xNNNN)           [r7+NNNNh]                |
+-----------------------------------------------------------------------+
```


### Immediates/Addresses

```
+-------------------------------------------------------------------------------+
|       Address18     0xNNNNN                 NNNNNh         ;for bkrep/br/call |
|       Address16     0xNNNN                  NNNNh          ;for bkrep         |
|       RelAddr7      0xNNNN                  NNNNh          ;for jmp           |
|       ImmN:         #0xNNNN                 NNNNh                             |
|       ImmNs:        #0xNN, #-NNN            +/-NNh                            |
|       Imm16:        ##0xNNNN                NNNNh                             |
|       Imm4bitno:    ...                     1 shl N                           |
|       ConstZero     <implied>               0000h                             |
|       Const1        <implied>               0001h                             |
|       Const4        <implied>               0004h                             |
|       Const8000h    <implied>               8000h                             |
+-------------------------------------------------------------------------------+
```


### Operand Encoding
Below shows the binary encoding for registers/conditions. For example, \"Ab@10\" in the opcode list can be \"b0,b1,a0,a1\" encoded in bit10-11. Some instructions re-use the same bitfield for multiple operands (eg. when performing two operations on the SAME operand, or when expecting DIFFERENT operands: for \"Ax@12,Ax@not12\" one of the registers must \"a0\", and the other must be \"a1\").


```
+--------------------------------------------------------------------------------+
|       Register:  RegisterP0:  Ax:     Axl:    Axh:            Px:              |
|       00: r0     00: r0       0: a0   0: a0l  0: a0h          0: p0            |
|       01: r1     01: r1       1: a1   1: a1l  1: a1h          1: p1            |
|       02: r2     02: r2                                                        |
|       03: r3     03: r3       Bx:     Bxl:    Bxh:            Ablh:            |
|       04: r4     04: r4       0: b0   0: b0l  0: b0h          0: b0l           |
|       05: r5     05: r5       1: b1   1: b1l  1: b1h          1: b0h           |
|       06: r7     06: r7                                       2: b1l           |
|       07: y0     07: y0       Ab:     Abl:    Abh:    Abe:    3: b1h           |
|       08: st0    08: st0      0: b0   0: b0l  0: b0h  0: b0e  4: a0l           |
|       09: st1    09: st1      1: b1   1: b1l  1: b1h  1: b1e  5: a0h           |
|       0A: st2    0A: st2      2: a0   2: a0l  2: a0h  2: a0e  6: a1l           |
|       0B: p0h !! 0B: p0 !!    3: a1   3: a1l  3: a1h  3: a1e  7: a1h           |
|       0C: pc     0C: pc                                                        |
|       0D: sp     0D: sp       Cond:                                            |
|       0E: cfgi   0E: cfgi     0: true  ;Always                    ;always      |
|       0F: cfgj   0F: cfgj     1: eq    ;Equal to zero             ;Z=1         |
|       10: b0h    10: b0h      2: neq   ;Not equal to zero         ;Z=0         |
|       11: b1h    11: b1h      3: gt    ;Greater than zero         ;M=0 and Z=0 |
|       12: b0l    12: b0l      4: ge    ;Greater or equal to zero  ;M=0         |
|       13: b1l    13: b1l      5: lt    ;Less than zero            ;M=1         |
|       14: ext0   14: ext0     6: le    ;Less or equal to zero     ;M=1 or Z=1  |
|       15: ext1   15: ext1     7: nn    ;Normalize flag is cleared ;N=0         |
|       16: ext2   16: ext2     8: c     ;Carry flag is set         ;C=1         |
|       17: ext3   17: ext3     9: v     ;Overflow flag is set      ;V=1         |
|       18: a0     18: a0       A: e     ;Extension flag is set     ;E=1         |
|       19: a1     19: a1       B: l     ;Limit flag is set         ;L=1         |
|       1A: a0l    1A: a0l      C: nr    ;R flag is cleared         ;R=0         |
|       1B: a1l    1B: a1l      D: niu0  ;Input user pin 0 cleared  ;IUSER0=0    |
|       1C: a0h    1C: a0h      E: iu0   ;Input user pin 0 set      ;IUSER0=1    |
|       1D: a1h    1D: a1h      F: iu1   ;Input user pin 1 set      ;IUSER1=1    |
|       1E: lc     1E: lc                                                        |
|       1F: sv     1F: sv                                                        |
+--------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|       R0123457y0:       Rn:                 ArArpSttMod:  ArArp:       SttMod:     |
|       0: r0             0: r0               0: ar0        0: ar0       0: stt0     |
|       1: r1             1: r1               1: ar1        1: ar1       1: stt1     |
|       2: r2             2: r2               2: arp0       2: arp0      2: stt2     |
|       3: r3             3: r3               3: arp1       3: arp1      3: reserved |
|       4: r4             4: r4               4: arp2       4: arp2      4: mod0     |
|       5: r5             5: r5               5: arp3       5: arp3      5: mod1     |
|       6: r7  ;aka rb    6: r6 ;TL2 only     6: reserved   6: reserved  6: mod2     |
|       7: y0  ;aka y     7: r7 ;TL2 only     7: reserved   7: reserved  7: mod3     |
|                                             8: stt0                                |
|       R01:     R04:     R45:                9: stt1       Ar:       BankFlags:     |
|       0: r0    0: r0    0:r4                A: stt2       0: ar0    01h: cfgi      |
|       1: r1    1: r4    1:r5                B: reserved   1: ar1    02h: r4        |
|                                             C: mod0                 04h: r1        |
|       R0123:   R0425:   R4567:              D: mod1       Arp:      08h: r0        |
|       0: r0    0: r0    0: r4               E: mod2       0: arp0   10h: r7   ;TL2 |
|       1: r1    1: r4    1: r5               F: mod3       1: arp1   20h: cfgj ;TL2 |
|       2: r2    2: r2    2: r6                             2: arp2                  |
|       3: r3    3: r5    3: r7                             3: arp3                  |
+------------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|       SwapTypes:                                                                 |
|       val native           nocash         ;meaning                               |
|       0:  (a0,b0)          a0,b0          ;a0 <--> b0                ;flags(a0)  |
|       1:  (a0,b1)          a0,b1          ;a0 <--> b1                ;flags(a0)  |
|       2:  (a1,b0)          a1,b0          ;a1 <--> b0                ;flags(a1)  |
|       3:  (a1,b1)          a1,b1          ;a1 <--> b1                ;flags(a1)  |
|       4:  (a0,b0),(a1,b1)  a0:a1,b0:b1    ;a0 <--> b0 and a1 <--> b1 ;flags(a0)  |
|       5:  (a0,b1),(a1,b0)  a0:a1,b1:b0    ;a0 <--> b1 and a1 <--> b0 ;flags(a0)  |
|       6:  (a0,b0,a1)       a1,b0,a0       ;a0 --> b0 --> a1          ;flags(a1)  |
|       7:  (a0,b1,a1)       a1,b1,a0       ;a0 --> b1 --> a1          ;flags(a1)  |
|       8:  (a1,b0,a0)       a0,b0,a1       ;a1 --> b0 --> a0          ;flags(a0)  |
|       9:  (a1,b1,a0)       a0,b1,a1       ;a1 --> b1 --> a0          ;flags(a0)  |
|       A:  (b0,a0,b1)       b1,a0,b0       ;b0 --> a0 --> b1          ;flags(a0)! |
|       B:  (b0,a1,b1)       b1,a1,b0       ;b0 --> a1 --> b1          ;flags(a1)! |
|       C:  (b1,a0,b0)       b0,a0,b1       ;b1 --> a0 --> b0          ;flags(a0)! |
|       D:  (b1,a1,b0)       b0,a1,b1       ;b1 --> a1 --> b0          ;flags(a1)! |
|       E:  reserved         reserved       ;-                         ;-          |
|       F:  reserved         reserved       ;-                         ;-          |
+----------------------------------------------------------------------------------+
```


### offs and step
Memory operands with \"offs\" allow to read from \[Rn\], \[Rn+1\], or \[Rn-1\]. Operands with \"step\" allow to increment/decrement registers (for old TL opcodes this is usually specified alongsides with memory operands, for new TL2 opcodes it\'s typically specified as separate \"\|\|\" instruction (eg. \"\|\| Rn@0stepZIDS@3\"; which can be omitted if the step is zero).
The official syntax wants \"+1,-1\" abbreviated to \"+,-\" in some cases (but not abbreviated in other cases). step \"+s\" does probably refer to \"stepi or stepj\", but it\'s rather unclear which one, maybe stepi is used for r0..r3, and stepj for r4..r7, or vice versa\... or maybe it depends on each opcode (particulary opcodes that allow to use \"Rn\" (r0..r7) might use the same step in ALL cases).

```
+---------------------------------------------------------------------------------+
|      offsZI:                           ;maybe offsAr01 ?                        |
|       0: ''         ;Z  (zero)                                                  |
|       1: '+'        ;I  (increment)                                             |
|      offsI:                                                                     |
|       0: '+'        ;I  (increment)                                             |
|      offsZIDZ:                         ;aka offsAr0123                          |
|       0: ''         ;Z  (zero)                                                  |
|       1: '+'        ;I  (increment)                                             |
|       2: '-'        ;D  (decrement)                                             |
|       3: ''         ;Z  (zero)                                                  |
|      stepZIDS:                                                                  |
|       0: ''         ;Z  (zero)                                                  |
|       1: '+1'       ;I  (increment)                                             |
|       2: '-1'       ;D  (decrement)                                             |
|       3: '+s'       ;S  (add step)           ;XXX ?   see "stepi" and "stepj"   |
|      modrstepZIDS:                                                              |
|       0: ''         ;Z  (zero)                                                  |
|       1: '+'        ;I  (increment)                                             |
|       2: '-'        ;D  (decrement)                                             |
|       3: '+s'       ;S  (add step)           ;XXX ?   see "stepi" and "stepj"   |
|      stepII2D2S:                      ;aka stepAr0123@                          |
|       0: '+1'       ;I  (increment)                                             |
|       1: '+2'       ;I2 (increment twice)                                       |
|       2: '-2'       ;D2 (decrement twice)                                       |
|       3: '+s'       ;S  (add step)           ;XXX ?   see "stepi" and "stepj"   |
|      stepD2S:                                                                   |
|       0: '-2'       ;D2 (decrement twice)                                       |
|       1: '+s'     ' ;S  (add step)           ;XXX ?   see "stepi" and "stepj"   |
|      modrstepII2D2S0:                                                           |
|       0: '+'        ;I  (increment)                                             |
|       1: '+2'       ;I2 (increment twice)                                       |
|       2: '-2'       ;D2 (decrement twice)                                       |
|       3: '+s0'      ;S0 (add step0 ?)        ;XXX ??  see "stepi0" and "stepj0" |
|      stepII2:                                                                   |
|       0: '+1'       ;I  (increment)                                             |
|       1: '+2'       ;I2 (increment twice)                                       |
|      modrstepI2:                                                                |
|       0: '+2'       ;I2 (increment twice)                                       |
|      modrstepD2:                                                                |
|       0: '-2'       ;D2 (decrement twice)                                       |
+---------------------------------------------------------------------------------+
```


Note: The \"modr\" opcodes are probably just incrementing/decrementing registers (with optional \"modulo\"), although the official syntax specifies their operands in brackets, ie. as if they were doing memory accesses.



