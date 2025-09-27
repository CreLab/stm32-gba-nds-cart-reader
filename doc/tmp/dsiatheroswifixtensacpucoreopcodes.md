# DSi Atheros Wifi - Xtensa CPU Core Opcodes


### Core Opcodes - Move/Load/Store

```
+-------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Expl.                   |
|       ii0st2h  L8UI   at,as,imm     movb   at,[as+imm8]     Load 8bit Unsigned      |
|       ii1st2h  L16UI  at,as,imm*2   movh   at,[as+imm8*2]   Load 16bit Unsigned     |
|       ii9st2h  L16SI  at,as,imm*2   movsh  at,[as+imm8*2]   Load 16bit Signed       |
|       ii2st2h  L32I   at,as,imm*4   mov    at,[as+imm8*4]   Load 32bit              |
|       ii4st2h  S8I    at,as,imm     movb   [as+imm8],at     Store 8bit              |
|       ii5st2h  S16I   at,as,imm*2   movh   [as+imm8*2],at   Store 16bit             |
|       ii6st2h  S32I   at,as,imm*4   mov    [as+imm8*4],at   Store 32bit             |
|       iiiit1h  L32R   at,adr        movp   at,literal       Load 32bit literal pool |
|       iiAit2h  MOVI   at,imm12      mov    at,+/-imm12      Move Immediate(signed)  |
|       83rst0h  MOVEQZ ar,as,at      movz   at,ar,as         Move if at=0  ;zero     |
|       93rst0h  MOVNEZ ar,as,at      movnz  at,ar,as         Move if at<>0 ;nonzero  |
|       A3rst0h  MOVLTZ ar,as,at      movs   at,ar,as         Move if at<0  ;negative |
|       B3rst0h  MOVGEZ ar,as,at      movns  at,ar,as         Move if at>=0 ;positive |
+-------------------------------------------------------------------------------------+
```


### Core Opcodes - ALU

```
+------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Expl.                  |
|       iiCst2h  ADDI   at,as,imm8    add  at,as,+/-imm8      Add Immediate (signed) |
|       iiDst2h  ADDMI  at,as,imm     add  at,as,+/-imm8*256  Add Immediate*100h     |
|       80rst0h  ADD    ar,as,at      add  ar,as,at           Add        (as+at)     |
|       90rst0h  ADDX2  ar,as,at      add  ar,at,as*2         Add shift1 (as*2+at)   |
|       A0rst0h  ADDX4  ar,as,at      add  ar,at,as*4         Add shift2 (as*4+at)   |
|       B0rst0h  ADDX8  ar,as,at      add  ar,at,as*8         Add shift3 (as*8+at)   |
|       C0rst0h  SUB    ar,as,at      sub  ar,as,at           Subtract   (as-at)     |
|       D0rst0h  SUBX2  ar,as,at      sub  ar,as*2,at         Sub shift1 (as*2-at)   |
|       E0rst0h  SUBX4  ar,as,at      sub  ar,as*4,at         Sub shift2 (as*4-at)   |
|       F0rst0h  SUBX8  ar,as,at      sub  ar,as*8,at         Sub shift3 (as*8-at)   |
|       60r0t0h  NEG    ar,at         neg  ar,at              Negate                 |
|       60r1t0h  ABS    ar,at         abs  ar,at              Absolute Value         |
|       10rst0h  AND    ar,as,at      and  ar,as,at           Bitwise Logical And    |
|       20rst0h  OR     ar,as,at      or   ar,as,at  ;akaMOV  Bitwise Logical Or     |
|       30rst0h  XOR    ar,as,at      xor  ar,as,at           Bitwise Logical Xor    |
+------------------------------------------------------------------------------------+
```


### Core Opcodes - Shift

```
+------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Expl.                  |
|       01rsi0h  SLLI   ar,as,32-imm5 shl  ar,as,32-imm5      Shift Left Logical     |
|       21rit0h  SRAI   ar,at,imm5    sar  ar,at,imm5         Shift Right Arithmetic |
|       41rit0h  SRLI   ar,at,imm4    shr  ar,at,imm4         Shift Right Logical    |
|       m4rst0h  EXTUI  ar,at,s,m     shrmask ar,at,imm5,mask ExtractUnsignedImm     |
|       81rst0h  SRC    ar,as,at      shr  ar,as,at,shiftreg  Shift Right Combined   |
|       91r0t0h  SRL    ar,at         shr  ar,at,shiftreg     Shift Right Logical    |
|       A1rs00h  SLL    ar,as         shl  ar,as,shiftreg ??  Shift Left Logical     |
|       B1r0t0h  SRA    ar,at         sar  ar,at,shiftreg     Shift Right Arithmetic |
|       400s00h  SSR    as            mov  shiftreg,as        SetShiftAm for RightSh |
|       401s00h  SSL    as            sub  shiftreg,32,as     SetShiftAm for LeftSh  |
|       402s00h  SSA8L  as            mov  shiftreg,as*8      SetShiftAmFor LE shift |
|       403s00h  SSA8B  as            sub  shiftreg,32,as*8   SetShiftAmFor BE shift |
|       404i.0h  SSAI   imm5          mov  shiftreg,imm5sar   SetShiftAm Immediate   |
+------------------------------------------------------------------------------------+
```


### Core Opcodes - Jump/Call

```
+------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Expl.                  |
|       iiii06h  J      adr           jmp    rel18            Unconditional Jump     |
|       000sA0h  JX     as            jmp    as               Unconditional Jump Reg |
|       iiii05h  CALL0  adr           call0  rel18x4          Non-windowed Call      |
|       000sC0h  CALLX0 as            call0  as               Non-windowed Call Reg  |
|       000080h  RET        ;(jx a0)  ret          ;(jx a0)   Non-Windowed Return    |
+------------------------------------------------------------------------------------+
```


### Core Opcodes - Conditional Jump

```
+-------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Branch if...            |
|       iiis16h  BEQZ   as,adr        jz     as,rel12         as=0                    |
|       iiis56h  BNEZ   as,adr        jnz    as,rel12         as<>0                   |
|       iiis96h  BLTZ   as,adr        js     as,rel12         as<0         (signed)   |
|       iiisD6h  BGEZ   as,adr        jns    as,rel12         as>=0        (signed)   |
|       iics26h  BEQI   as,c,adr      je     as,const4,rel8   as=Imm4(c)              |
|       iics66h  BNEI   as,c,adr      jne    as,const4,rel8   as<>Imm4(c)             |
|       iicsA6h  BLTI   as,c,adr      jl     as,const4,rel8   as<Imm4(c)   (signed)   |
|       iicsE6h  BGEI   as,c,adr      jge    as,const4,rel8   as>=Imm4(c)  (signed)   |
|       iicsB6h  BLTUI  as,c,adr      jb     as,const4u,rel8  as<UnsiImm4  (unsigned) |
|       iicsF6h  BGEUI  as,c,adr      jae    as,const4u,rel8  as>=UnsiImm4 (unsigned) |
|       ii1st7h  BEQ    as,at,adr     je     as,at,rel8       as=at  equal            |
|       ii9st7h  BNE    as,at,adr     jne    as,at,rel8       as<>at not equal        |
|       ii2st7h  BLT    as,at,adr     jl     as,at,rel8       as<at  less  (signed)   |
|       iiAst7h  BGE    as,at,adr     jge    as,at,rel8       as>=at gt/eq (signed)   |
|       ii3st7h  BLTU   as,at,adr     jb     as,at,rel8       as<at  less  (unsigned) |
|       iiBst7h  BGEU   as,at,adr     jae    as,at,rel8       as>=at gt/eq (unsigned) |
|       ii0st7h  BNONE  as,at,adr     tstjz  as,at,rel8       (as AND at)=0  ;none    |
|       ii8st7h  BANY   as,at,adr     tstjnz as,at,rel8       (as AND at)<>0 ;any set |
|       ii4st7h  BALL   as,at,adr     tstje  as,at,rel8       (as AND at)=at ;all set |
|       iiCst7h  BNALL  as,at,adr     tstjne as,at,rel8       (as AND at)<>at;not all |
|       ii5st7h  BBC    as,at,adr     tstjz  as,1 shl at,rel8 (as AND (1 shl at))=0   |
|       ii6sb7h  BBCI   as,b,adr      tstjz  as,1 shl imm5,r8 (as AND (1 shl imm))=0  |
|       iiDst7h  BBS    as,at,adr     tstjnz as,1 shl at,rel8 (as AND (1 shl at))<>0  |
|       iiEsb7h  BBSI   as,b,adr      tstjnz as,1 shl imm5,r8 (as AND (1 shl imm))<>0 |
+-------------------------------------------------------------------------------------+
```


### Core Opcodes - Misc

```
+-------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                  Expl.                   |
|       406st0h  RER    at,as         mov  at,ext[as]         ReadExternal Register   |
|       407st0h  WER    at,as         mov  ext[as],at         WriteExternalRegister   |
|       03iit0h  RSR    at,imm8       mov  at,special[imm8]   ReadSpecial Register    |
|       13iit0h  WSR    at,imm8       mov  special[imm8],at   WriteSpecialRegister    |
|       61iit0h  XSR    at,imm8       xchg at,special[imm8]   ExchangeSpecialRegister |
|       002000h  ISYNC                isync                   Instruction Fetch Sync  |
|       002010h  RSYNC                rsync                   Register Read Sync      |
|       002020h  ESYNC                esync                   Execute Synchronize     |
|       002030h  DSYNC                dsync                   Load/Store Synchronize  |
|       0020C0h  MEMW                 memwait                 Memory Wait             |
|       0020D0h  EXTW                 extwait                 External Wait           |
|       0020F0h  NOP                  nop                     No-Operation            |
+-------------------------------------------------------------------------------------+
```


### Pseudo Opcodes

```
+----------------------------------------------------------------------------------+
|       MOV    ar,as       Macro (=OR ar,as,as)                                    |
|       NOP                Alias for "OR An,An,An" (alternate, instead of 0020F0h) |
|       J.L    adr,as      Macro (J or LiteralLoad+JX)                             |
|       BBCI.L as,b,adr    Macro Branch Bit Clear Imm5 LE                          |
|       BBSI.L as,b,adr    Macro Branch Bit Set Imm5 LE                            |
|       SRLI ar,at,imm5    Alias for "SRLI ar,at,imm4" or EXTUI (when imm5>=16)    |
+----------------------------------------------------------------------------------+
```

More (inofficial) pseudos\...

```
+-----------------------------------------------------------------------+
|       mov    br,bs       or  br,bs,bs                                 |
|       mov    br,0        and br,bs,not bs                             |
|       mov    br,1        or  br,bs,not bs                             |
|       sub    at,as,imm   add at,as,-imm                               |
|       mov    sfr_xxx     mov special[imm8]                            |
|       alu    ax,...      alu ax,ax,...                                |
+-----------------------------------------------------------------------+
```




