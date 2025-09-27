# ARM VFP Floating Point Maths Opcodes


### VFP data-processing primary opcodes

```
+---------------------------------------------------------------------------------+
|       pqrs cp10/cp11                  Instruction functionality                 |
|       0000 FMAC{S|D}{cond} Fd,Fn,Fm   Fd = +(Fn*Fm)+Fd   ;Multiply, Add         |
|       0001 FNMAC{S|D}{cond} Fd,Fn,Fm  Fd = -(Fn*Fm)+Fd   ;Multiply, Negate, Add |
|       0010 FMSC{S|D}{cond} Fd,Fn,Fm   Fd = +(Fn*Fm)-Fd   ;Multiply, Subtract    |
|       0011 FNMSC{S|D}{cond} Fd,Fn,Fm  Fd = -(Fn*Fm)-Fd   ;Multiply, Negate, Sub |
|       0100 FMUL{S|D}{cond} Fd,Fn,Fm   Fd = +(Fn*Fm)      ;Multiply              |
|       0101 FNMUL{S|D}{cond} Fd,Fn,Fm  Fd = -(Fn*Fm)      ;Multiply, Negate      |
|       0110 FADD{S|D}{cond} Fd,Fn,Fm   Fd = Fn+Fm         ;Add                   |
|       0111 FSUB{S|D}{cond} Fd,Fn,Fm   Fd = Fn-Fm         ;Sub                   |
|       1000 FDIV{S|D}{cond} Fd,Fn,Fm   Fd = Fn/Fm         ;Divide                |
|       1001 -Undefined-                                                          |
|       1010 -Undefined-                                                          |
|       1011 -Undefined-                                                          |
|       1100 -Undefined-                                                          |
|       1101 -Undefined-                                                          |
|       1110 -Undefined-                                                          |
|       1111 -Extension instructions-                                             |
+---------------------------------------------------------------------------------+
```


### VFP data-processing extension opcodes

```
+-------------------------------------------------------------------------------------+
|       Fn   N cp10/cp11                  Instruction functionality                   |
|       0000 0 FCPY{S|D}{cond} Fd,Fm      Fd = Fm        ;Copy                        |
|       0000 1 FABS{S|D}{cond} Fd,Fm      Fd = abs(Fm)   ;Absolute                    |
|       0001 0 FNEG{S|D}{cond} Fd,Fm      Fd = -Fm       ;Negate                      |
|       0001 1 FSQRT{S|D}{cond} Fd,Fm     Fd = sqrt(Fm)  ;Square root                 |
|       001x x -Undefined-                                                            |
|       0100 0 FCMP{S|D}{cond} Fd,Fm      Fd-Fm     ;Compare                          |
|       0100 1 FCMPE{S|D}{cond} Fd,Fm     Fd-Fm     ;Compare, exception on quiet NaNs |
|       0101 0 FCMPZ{S|D}{cond} Fd        Fd-0      ;Compare                          |
|       0101 1 FCMPEZ{S|D}{cond} Fd       Fd-0      ;Compare, exception on quiet NaNs |
|       0110 x -Undefined-                                                            |
|       0111 0 -Undefined-                                                            |
|       0111 1 FCVT{DS|SD}{cond} Fd,Fm    Single <--> Double-precision conversion     |
|       1000 0 FUITO{S|D}{cond} Fd,Im     Unsigned integer --> float                  |
|       1000 1 FSITO{S|D}{cond} Fd,Im     Signed integer --> float                    |
|       1001 x -Undefined-                                                            |
|       101x x -Undefined-                                                            |
|       1100 0 FTOUI{S|D}{cond} Id,Fm     Float --> unsigned integer                  |
|       1100 1 FTOUIZ{S|D}{cond} Id,Fm    Float --> unsigned integer, round to zero   |
|       1101 0 FTOSI{S|D}{cond} Id,Fm     Float --> signed integer                    |
|       1101 1 FTOSIZ{S|D}{cond} Id,Fm    Float --> signed integer, round to zero     |
|       111x x -Undefined-                                                            |
+-------------------------------------------------------------------------------------+
```

cp10: FCVTDS Dd,Sm ;Double \<\-- Single
cp11: FCVTSD Sd,Dm ;Single \<\-- Double

### Nocash syntax
The useless {S\|D} and {DS\|SD} suffixes are ommitted. FCVT is renamed to FMOV. F{UI\|SI}TO{UI\|SI}{Z} is renamed to FMOV{UI\|SI}{Z}, with operand I0..I31 for the integer register.



