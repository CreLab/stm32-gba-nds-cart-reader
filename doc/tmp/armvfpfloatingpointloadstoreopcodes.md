# ARM VFP Floating Point Load/Store Opcodes


### VFP single register transfer instructions

```
+-------------------------------------------------------------------------------------+
|       cp   opcode L Instruction name   Instruction functionality                    |
|       cp10 000    0 FMSR{cond} Sn,Rd   Sn = Rd        ;\Single-Precision or Integer 
|       cp10 000    1 FMRS{cond} Rd,Sn   Rd = Sn        ;/                            |
|       cp10 111    0 FMXR{cond} sys,Rd  Reg(Fn,N) = Rd ;\SystemReg (FPSID, etc.)     
|       cp10 111    1 FMRX{cond} Rd,sys  Rd = Reg(Fn,N) ;/  ;<-- or FMSTAT{cond}      |
|       cp11 000    0 FMDLR{cond} Dn,Rd  Dn.31-0 = Rd   ;\LSW of Double-Precision     
|       cp11 000    1 FMRDL{cond} Rd,Dn  Rd = Dn.31-0   ;/                            |
|       cp11 001    0 FMDHR{cond} Dn,Rd  Dn.63-32 = Rd  ;\MSW of Double-Precision     
|       cp11 001    1 FMRDH{cond} Rd,Dn  Rd = Dn.63-32  ;/                            |
|       other's       -Undefined-                                                     |
+-------------------------------------------------------------------------------------+
```

System Register encodings:

```
+----------------------------------------------------------------------------------+
|       Fn   N  System register                                                    |
|       0000 0  FPSID (New3DS: 410120b4h = VFPv2 with single AND double precision) |
|       0001 0  FPSCR      ;(FMSTAT opcode encodes as FMRX R15,FPSCR)              |
|       0110 0? MVFR1                       ;\mpcore only                          
|       0111 0? MVFR0                       ;/                                     |
|       1000 0  FPEXC                                                              |
|       1001 0? FPINST                      ;\mpcore only                          
|       1010 0? FPINST2                     ;/                                     |
+----------------------------------------------------------------------------------+
```


### VFP two register transfer instructions (VFPv2 and above)

```
+-----------------------------------------------------------------------------------+
|       cp   L Instruction name               Instruction functionality             |
|       cp10 0 FMSRR{cond} {Sm,Sm+1},Rd,Rn    Fm = Rn, (Fm+1) = Rd    ;XXX swapped? |
|       cp10 1 FMRRS{cond} Rd,Rn,{Sm,Sm+1}    Rn = Fm, Rd = (Fm+1)    ;XXX swapped? |
|       cp11 0 FMDRR{cond} Dm,Rd,Rn           Fm[31:0] = Rd, Fm[63:32] = Rn         |
|       cp11 1 FMRRD{cond} Rd,Rn,Dm           Rd = Fm[31:0], Rn = Fm[63:32]         |
+-----------------------------------------------------------------------------------+
```


### VFP load and store instructions

```
+-------------------------------------------------------------------------------------+
|       PUW  L=0/1,cp10/cp11                             Registers transferred        |
|       000  -Two-register transfer instructions-        -                            |
|       001  -Undefined-                                 -                            |
|       010  FSTM|FLDMIA{S|D|X}{<cond>} Rn,{Fd,Fd+1,..}  Multiple Registers           |
|       011  FSTM|FLDMIA{S|D|X}{<cond>} Rn!,{Fd,Fd+1,..} Multiple Registers Increment |
|       100  FST|FLD{S|D}{<cond>} Fd, [Rn{,-offs*4}]     One register, -offs          |
|       101  FSTM|FLDMDB{S|D|X}{<cond>} Rn!,{Fd,Fd+1,..} Multiple Registers Decrement |
|       110  FST|FLD{S|D}{<cond>} Fd, [Rn{,+offs*4}]     One register, +offs          |
|       111  -Undefined-                                 -                            |
+-------------------------------------------------------------------------------------+
```

FSTM/FLDM do transfer multiple words (with offs containing the number of words to be transferred, 1..32 for {S}, or an even number 2..32 for {D}.
VFP load/store multiple addressing modes

```
+-----------------------------------------------------------------------+
|       Non-stacking mnemonic   Stacking mnemonic                       |
|       FLDMIA{S|D|X}           FLDMFD{S|D|X}     FPOP{S|D|X}           |
|       FLDMDB{S|D|X}           FLDMEA{S|D|X}                           |
|       FSTMIA{S|D|X}           FSTMEA{S|D|X}                           |
|       FSTMDB{S|D|X}           FSTMFD{S|D|X}     FPUSH{S|D|X}          |
+-----------------------------------------------------------------------+
```


### Nocash syntax
The useless {S\|D} suffixes are ommitted, the weird {X} suffix is kept used to preserve weirdness.
Fancy {} brackets are omitted, LDM/STM must use square \[Rn\] brackets, the register list in LDM/STM is specified as Fx-Fz (rather than Fx,Fy,Fz).
All FMxxxx opcodes are renamed to FMOV{LSW\|MSW}.

### Weird STM/LDM{X} - for registers with unknown precision
The weird {X} mode is same as {D}, but with offset.bit0=1 (ie. with offs=3..33 instead of 2..32; and thereby actually transferring an unused dummy word; that extra word might be intended to contain datatype flags).
The weird {X} mode is/was intended for registers with unknown content (eg. when pushing/popping registers without knowing if they contain integer/single/double precision values; which might be a problem with internal accumulators in the VFP unit).
The weird {X} mode was declared as \"deprecated in ARMv6\" in DDI 0100I, but later re-declared as required for \"compatibility with future VFP implementations\" in DDI 360F. However, unknown if there are/were/will be any such implementations that do require it.
For now, it should be best to use {D} mode instead of weird {X}. Probably even {S} should also work the same (if the endianess-based word-order doesn\'t matter).



