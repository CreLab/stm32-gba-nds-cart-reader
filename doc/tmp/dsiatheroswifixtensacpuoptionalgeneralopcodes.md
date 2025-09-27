# DSi Atheros Wifi - Xtensa CPU Optional General Opcodes


### Boolean Option

```
+-------------------------------------------------------------------------------------+
|       Opcode   Native               Nocash                                          |
|       008st0h  ANY4  bt,bs          or     bt,bs..bs+3      Any 4 Booleans True     |
|       009st0h  ALL4  bt,bs          and    bt,bs..bs+3      All 4 Booleans True     |
|       00Ast0h  ANY8  bt,bs          or     bt,bs..bs+7      Any 8 Booleans True     |
|       00Bst0h  ALL8  bt,bs          and    bt,bs..bs+7      All 8 Booleans True     |
|       02rst0h  ANDB  br,bs,bt       and    br,bs,bt         BooleanAnd              |
|       12rst0h  ANDBC br,bs,bt       and    br,bs,not bt     BooleanAndComplement(t) |
|       22rst0h  ORB   br,bs,bt       or     br,bs,bt         BooleanOr               |
|       32rst0h  ORBC  br,bs,bt       or     br,bs,not bt     BooleanOrComplement(t)  |
|       42rst0h  XORB  br,bs,bt       xor    br,bs,bt         Boolean Xor             |
|       C3rst0h  MOVF  ar,as,bt       movz   bt,ar,as         Move if False           |
|       D3rst0h  MOVT  ar,as,bt       movnz  bt,ar,as         Move if True            |
|       ii0s76h  BF    bs,adr         jz     bs,rel8          Branch if False         |
|       ii1s76h  BT    bs,adr         jnz    bs,rel8          Branch if True          |
+-------------------------------------------------------------------------------------+
```


### Misc Option

```
+------------------------------------------------------------------------------------+
|       40Est0h  NSA    at,as         nsa    at,as            Normaliz.ShiftAmount   |
|       40Fst0h  NSAU   at,as         nsau   at,as            Norma.ShiftAmUnsigned  |
|       23rsi0h  SEXT   ar,as,imm     sext   ar,as,imm4+7     Sign Extend 7..22      |
|       33rsi0h  CLAMPS ar,as,imm     clamps ar,as,imm4+7     Signed Clamp minmax    |
|       43rst0h  MIN    ar,as,at      min    ar,as,at         Minimum Value Signed   |
|       53rst0h  MAX    ar,as,at      max    ar,as,at         Maximum Value Signed   |
|       63rst0h  MINU   ar,as,at      minu   ar,as,at         Minimum Value Unsigned |
|       73rst0h  MAXU   ar,as,at      maxu   ar,as,at         Maximum Value Unsigned |
+------------------------------------------------------------------------------------+
```


### Loop Option

```
+-----------------------------------------------------------------------------------+
|       ii8s76h  LOOP    as,adr       loop    as,rel8abs      Loop                  |
|       ii9s76h  LOOPNEZ as,adr       loopnz  as,rel8abs      Loop if NotEqual zero |
|       iiAs76h  LOOPGTZ as,adr       loopgtz as,rel8abs      Loop if Greater zero  |
+-----------------------------------------------------------------------------------+
```


### Windowed Code Option

```
+----------------------------------------------------------------------------------+
|       iiii15h  CALL4   adr          call4   rel18x4         Call RotateWinBy4    |
|       iiii25h  CALL8   adr          call8   rel18x4         Call RotateWinBy8    |
|       iiii35h  CALL12  adr          call12  rel18x4         Call RotateWinBy12   |
|       000sD0h  CALLX4  as           call4   as              Call RegRotateBy4    |
|       000sE0h  CALLX8  as           call8   as              Call RegRotateBy8    |
|       000sF0h  CALLX12 as           call12  as              Call RegRotateBy12   |
|       iiis36h  ENTRY   as,imm*8     entry   as,imm12*8      Subroutine Entry     |
|       000090h  RETW                 retw                    Windowed-Return      |
|       003400h  RFWO                 ret_wo                  RetFromWinOverflow   |
|       003500h  RFWU                 ret_wu                  RetFromWinUnderflw   |
|       001st0h  MOVSP   at,as        movsp   at,as           Move to Stack Ptr    |
|       4080i0h  ROTW    imm4         rotw    imm4            Rotate Window -8..+7 |
|       09ist0h  L32E    at,as,imm    mov_e   at,[as-imm*4]   Load32bitException   |
|       49ist0h  S32E    at,as,imm    mov_e   [as-imm*4],at   StrWinForExcepts     |
+----------------------------------------------------------------------------------+
```


### Narrow Code Option

```
+-------------------------------------------------------------------------------------+
|       --ist8h  L32I.N at,as,imm4*4  mov  at,[as+imm4*4]     Load 32bit              |
|       --ist9h  S32I.N at,as,imm4*4  mov  [as+imm4*4],at     Store 32bit             |
|       --rstAh  ADD.N  ar,as,at      add  ar,as,at           Add                     |
|       --rsiBh  ADDI.N ar,as,imm4    add  ar,as,imm4         Add Imm (0=-1 or 1..15) |
|       --is0Ch  MOVI.N as,imm        mov  as,imm7            Move Imm (-32..95)      |
|       --is8Ch  BEQZ.N as,adr        jz   as,rel6abs         Branch if as=0          |
|       --isCCh  BNEZ.N as,adr        jnz  as,rel6abs         Branch if as<>0         |
|       --0stDh  MOV.N  at,as         mov  at,as              Move                    |
|       --F00Dh  RET.N     ;(jx a0)   ret        ;jx a0       Non-Windowed Return     |
|       --F01Dh  RETW.N               retw                    Windowed Return         |
|       --F06Dh  ILL.N                ill                     Xcept Illegal Instr.    |
|       --Fi2Dh  BREAK.N imm4         break imm4              Debug Breakpoint        |
|       --F03Dh  NOP.N                nop                     No-Operation            |
+-------------------------------------------------------------------------------------+
```


### Mul16 Option

```
+-----------------------------------------------------------------------------------+
|       C1rst0h  MUL16U ar,as,at      umul16  ar,as,at        Multiply16bitUnsigned |
|       D1rst0h  MUL16S ar,as,at      smul16  ar,as,at        Multiply16bitSigned   |
+-----------------------------------------------------------------------------------+
```


### Mul32 Option

```
+----------------------------------------------------------------------------------+
|       82rst0h  MULL  ar,as,at       mul     ar,as,at        Multiply Low         |
|       A2rst0h  MULUH ar,as,at       umulhi  ar,as,at        MultiplyUnsignedHigh |
|       B2rst0h  MULSH ar,as,at       smulhi  ar,as,at        MultiplySignedHigh   |
+----------------------------------------------------------------------------------+
```


### Div32 Option

```
+--------------------------------------------------------------------------------+
|       C2rst0h  QUOU ar,as,at        udiv    ar,as,at        Quotient Unsigned  |
|       D2rst0h  QUOS ar,as,at        sdiv    ar,as,at        Quotient Signed    |
|       E2rst0h  REMU ar,as,at        udivrem ar,as,at        Remainder Unsigned |
|       F2rst0h  REMS ar,as,at        sdivrem ar,as,at        Remainder Signed   |
+--------------------------------------------------------------------------------+
```




