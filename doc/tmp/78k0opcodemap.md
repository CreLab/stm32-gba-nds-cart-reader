# 78K/0 Opcode Map


### 78K/0 Primary Opcode Map

```
+--------------------------------------------------------------------------------+
|           00                10                20                30             |
|       00  NOP               MOVW AX,nnnn      SET1 CY           XCH  A,X       |
|       01  NOT1 CY           MOV  [FExx],nn    CLR1 CY           <prefix>       |
|       02  MOVW AX,[nnnn]    MOVW BC,nnnn      PUSH PSW ;[FF1Eh] XCH  A,C       |
|       03  MOVW [nnnn],AX    MOV  [FFxx],nn    POP  PSW ;[FF1Eh] XCH  A,B       |
|       04  DBNZ [FExx],rel   MOVW DE,nnnn      ROR  A,1          XCH  A,E       |
|       05  XCH  A,[DE]       <undef>           RORC A,1          XCH  A,D       |
|       06  <undef>           MOVW HL,nnnn      ROL  A,1          XCH  A,L       |
|       07  XCH  A,[HL]       <undef>           ROLC A,1          XCH  A,H       |
|       08  ADD  A,[nnnn]     SUB  A,[nnnn]     ADDC A,[nnnn]     SUBC A,[nnnn]  |
|       09  ADD  A,[HL+nn]    SUB  A,[HL+nn]    ADDC A,[HL+nn]    SUBC A,[HL+nn] |
|       0A  SET1 [FExx].0     SET1 [FExx].1     SET1 [FExx].2     SET1 [FExx].3  |
|       0B  CLR1 [FExx].0     CLR1 [FExx].1     CLR1 [FExx].2     CLR1 [FExx].3  |
|       0C  CALLF 08nn        CALLF 09nn        CALLF 0Ann        CALLF 0Bnn     |
|       0D  ADD  A,nn         SUB  A,nn         ADDC A,nn         SUBC A,nn      |
|       0E  ADD  A,[FExx]     SUB  A,[FExx]     ADDC A,[FExx]     SUBC A,[FExx]  |
|       0F  ADD  A,[HL]       SUB  A,[HL]       ADDC A,[HL]       SUBC A,[HL]    |
+--------------------------------------------------------------------------------+
```



```
+--------------------------------------------------------------------------------+
|           40                50                60                70             |
|       40  INC  X            DEC  X            MOV  A,X          MOV  X,A       |
|       41  INC  A            DEC  A            <prefix>          <prefix>       |
|       42  INC  C            DEC  C            MOV  A,C          MOV  C,A       |
|       43  INC  B            DEC  B            MOV  A,B          MOV  B,A       |
|       44  INC  E            DEC  E            MOV  A,E          MOV  E,A       |
|       45  INC  D            DEC  D            MOV  A,D          MOV  D,A       |
|       46  INC  L            DEC  L            MOV  A,L          MOV  L,A       |
|       47  INC  H            DEC  H            MOV  A,H          MOV  H,A       |
|       48  CMP  A,[nnnn]     AND  A,[nnnn]     OR   A,[nnnn]     XOR  A,[nnnn]  |
|       49  CMP  A,[HL+nn]    AND  A,[HL+nn]    OR   A,[HL+nn]    XOR  A,[HL+nn] |
|       4A  SET1 [FExx].4     SET1 [FExx].5     SET1 [FExx].6     SET1 [FExx].7  |
|       4B  CLR1 [FExx].4     CLR1 [FExx].5     CLR1 [FExx].6     CLR1 [FExx].7  |
|       4C  CALLF 0Cnn        CALLF 0Dnn        CALLF 0Enn        CALLF 0Fnn     |
|       4D  CMP  A,nn         AND  A,nn         OR   A,nn         XOR  A,nn      |
|       4E  CMP  A,[FExx]     AND  A,[FExx]     OR   A,[FExx]     XOR  A,[FExx]  |
|       4F  CMP  A,[HL]       AND  A,[HL]       OR   A,[HL]       XOR  A,[HL]    |
+--------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|           80                90                A0                B0                |
|       80  INCW AX           DECW AX           MOV  X,nn         POP  AX           |
|       81  INC  [FExx]       DEC  [FExx]       MOV  A,nn         PUSH AX           |
|       82  INCW BC           DECW BC           MOV  C,nn         POP  BC           |
|       83  XCH  A,[FExx]     XCH  A,[FFxx]     MOV  B,nn         PUSH BC           |
|       84  INCW DE           DECW DE           MOV  E,nn         POP  DE           |
|       85  MOV  A,[DE]       MOV  [DE],A       MOV  D,nn         PUSH DE           |
|       86  INCW HL           DECW HL           MOV  L,nn         POP  HL           |
|       87  MOV  A,[HL]       MOV  [HL],A       MOV  H,nn         PUSH HL           |
|       88  ADD  [FExx],nn    SUB  [FExx],nn    ADDC [FExx],nn    SUBC [FExx],nn    |
|       89  MOVW AX,[FExx]    MOVW [FExx],AX    MOVW AX,[FFxx]    MOVW [FFxx],AX    |
|       8A  DBNZ C,rel        CALL nnnn         MOV  A,[HL+C]     MOV  [HL+C],A     |
|       8B  DBNZ B,rel        BR   nnnn         MOV  A,[HL+B]     MOV  [HL+B],A     |
|       8C  BT   [FExx].0,rel BT   [FExx].1,rel BT   [FExx].2,rel BT   [FExx].3,rel |
|       8D  BC   rel          BNC  rel          BZ   rel          BNZ  rel          |
|       8E  MOV  A,[nnnn]     MOV  [nnnn],A     MOV  A,[HL+nn]    MOV  [HL+nn],A    |
|       8F  RETI              RETB              RET               BRK               |
+-----------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|           C0                D0                E0                F0                |
|       C0  <undef>           <undef>           <undef>           MOV  A,[FExx]     |
|       C1  CALLT [40]        CALLT [50]        CALLT [60]        CALLT [70]        |
|       C2  MOVW AX,BC        MOVW BC,AX        XCHW AX,BC        MOV  [FExx],A     |
|       C3  CALLT [42]        CALLT [52]        CALLT [62]        CALLT [72]        |
|       C4  MOVW AX,DE        MOVW DE,AX        XCHW AX,DE        MOV  A,[FFxx]     |
|       C5  CALLT [44]        CALLT [54]        CALLT [64]        CALLT [74]        |
|       C6  MOVW AX,HL        MOVW HL,AX        XCHW AX,HL        MOV  [FFxx],A     |
|       C7  CALLT [46]        CALLT [56]        CALLT [66]        CALLT [76]        |
|       C8  CMP  [FExx],nn    AND  [FExx],nn    OR   [FExx],nn    XOR  [FExx],nn    |
|       C9  CALLT [48]        CALLT [58]        CALLT [68]        CALLT [78]        |
|       CA  ADDW AX,nnnn      SUBW AX,nnnn      CMPW AX,nnnn      BR   rel          |
|       CB  CALLT [4A]        CALLT [5A]        CALLT [6A]        CALLT [7A]        |
|       CC  BT   [FExx].4,rel BT   [FExx].5,rel BT   [FExx].6,rel BT   [FExx].7,rel |
|       CD  CALLT [4C]        CALLT [5C]        CALLT [6C]        CALLT [7C]        |
|       CE  XCH  A,[nnnn]     XCH  A,[HL+nn]    MOVW [FExx],nnnn  MOVW [FFxx],nnnn  |
|       CF  CALLT [4E]        CALLT [5E]        CALLT [6E]        CALLT [7E]        |
+-----------------------------------------------------------------------------------+
```


### 78K/0 Opcodes with Prefix 31

```
+-------------------------------------------------------------------------------------+
|       3100+xxx*10  -                                                                |
|       3180+xxx*10  - (unless below ROL/ROR)                                         |
|       3101+bbb*10  BTCLR   [FExx].n,rel    ;n=0..7                                  |
|       3181+xxx*10  -                                                                |
|       3102+xxx*10  -                                                                |
|       3182+xxx*10  - (unless below DIV)                                             |
|       3103+bbb*10  BF      [FExx].n,rel    ;n=0..7                                  |
|       3183+xxx*10  -                                                                |
|       3104+xxx*10  -                                                                |
|       3184+xxx*10  -                                                                |
|       3105+bbb*10  BTCLR   [FFxx].n,rel    ;n=0..7                                  |
|       3185+bbb*10  BTCLR   [HL].n,rel      ;n=0..7                                  |
|       3106+bbb*10  BT      [FFxx].n,rel    ;n=0..7                                  |
|       3186+bbb*10  BT      [HL].n,rel      ;n=0..7                                  |
|       3107+bbb*10  BF      [FFxx].n,rel    ;n=0..7                                  |
|       3187+bbb*10  BF      [HL].n,rel      ;n=0..7                                  |
|       3108+xxx*10  -                                                                |
|       3188+xxx*10  - (unless below MUL/BR)                                          |
|       3109+xxx*10  -                                                                |
|       3189+xxx*10  -                                                                |
|       310A+xxx*10  <see below ADD/SUB/ADDC/SUBC/CMP/AND/OR/XOR)                     |
|       318A+xxx*10  - (unless below XCH)                                             |
|       310B+xxx*10  <see below ADD/SUB/ADDC/SUBC/CMP/AND/OR/XOR)                     |
|       318B+xxx*10  - (unless below XCH)                                             |
|       310C+xxx*10  -                                                                |
|       318C+xxx*10  -                                                                |
|       310D+bbb*10  BTCLR   A.n,rel         ;n=0..7                                  |
|       318D+xxx*10  -                                                                |
|       310E+bbb*10  BT      A.n,rel         ;n=0..7                                  |
|       318E+xxx*10  -                                                                |
|       310F+bbb*10  BF      A.n,rel         ;n=0..7                                  |
|       318F+xxx*10  -                                                                |
|       310A         ADD     A,[HL+C]                                                 |
|       310B         ADD     A,[HL+B]                                                 |
|       311A         SUB     A,[HL+C]                                                 |
|       311B         SUB     A,[HL+B]                                                 |
|       312A         ADDC    A,[HL+C]                                                 |
|       312B         ADDC    A,[HL+B]                                                 |
|       313A         SUBC    A,[HL+C]                                                 |
|       313B         SUBC    A,[HL+B]                                                 |
|       314A         CMP     A,[HL+C]                                                 |
|       314B         CMP     A,[HL+B]                                                 |
|       315A         AND     A,[HL+C]                                                 |
|       315B         AND     A,[HL+B]                                                 |
|       316A         OR      A,[HL+C]                                                 |
|       316B         OR      A,[HL+B]                                                 |
|       317A         XOR     A,[HL+C]                                                 |
|       317B         XOR     A,[HL+B]                                                 |
|       318A         XCH     A,[HL+C]                                                 |
|       318B         XCH     A,[HL+B]                                                 |
|       3180         ROL4    A,[HL]   ;rol 12bit A.lsb:[HL],4      ;native: ROL4 [HL] |
|       3190         ROR4    A,[HL]   ;ror 12bit A.lsb:[HL],4      ;native: ROR4 [HL] |
|       3182         DIVUW   AX,C     ;unsigned AX=AX/C, C=remainder ;native: DIVWU C |
|       3188         MULU    AX,A,X   ;unsigned AX=A*X               ;native: MULU X  |
|       3198         BR      AX                                                       |
+-------------------------------------------------------------------------------------+
```


### 78K/0 Opcodes with Prefix 61

```
+---------------------------------------------------------------------------------+
|       6100+rrr     ADD     r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6108+rrr     ADD     A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6110+rrr     SUB     r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6118+rrr     SUB     A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6120+rrr     ADDC    r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6128+rrr     ADDC    A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6130+rrr     SUBC    r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6138+rrr     SUBC    A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6140+rrr     CMP     r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6148+rrr     CMP     A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6150+rrr     AND     r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6158+rrr     AND     A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6160+rrr     OR      r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6168+rrr     OR      A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6170+rrr     XOR     r,A            ;r=X,A,C,B,E,D,L,H                    |
|       6178+rrr     XOR     A,r            ;r=X,-,C,B,E,D,L,H                    |
|       6180+xxx*10  - (unless below ADJ/SEL)                                     |
|       6181+xxx*10  -                                                            |
|       6182+xxx*10  -                                                            |
|       6183+xxx*10  -                                                            |
|       6184+xxx*10  -                                                            |
|       6185+xxx*10  -                                                            |
|       6186+xxx*10  -                                                            |
|       6187+xxx*10  -                                                            |
|       6188+xxx*10  - (unless below ADJ/SEL)                                     |
|       6189+bbb*10  MOV1    A.n,CY         ;n=0..7                               |
|       618A+bbb*10  SET1    A.n            ;n=0..7                               |
|       618B+bbb*10  CLR1    A.n            ;n=0..7                               |
|       618C+bbb*10  MOV1    CY,A.n         ;n=0..7                               |
|       618D+bbb*10  AND1    CY,A.n         ;n=0..7                               |
|       618E+bbb*10  OR1     CY,A.n         ;n=0..7                               |
|       618F+bbb*10  XOR1    CY,A.n         ;n=0..7                               |
|       6180         ADJBA                ;Decimal BCD adjust A after Addition    |
|       6190         ADJBS                ;Decimal BCD adjust A after Subtraction |
|       61D0         SEL     RB0                                                  |
|       61D8         SEL     RB1                                                  |
|       61F0         SEL     RB2                                                  |
|       61F8         SEL     RB3                                                  |
+---------------------------------------------------------------------------------+
```


### 78K/0 Opcodes with Prefix 71

```
+-----------------------------------------------------------------------+
|       7100+xxx*10  - (unless below STOP/HALT)                         |
|       7180+xxx*10  -                                                  |
|       7101+bbb*10  MOV1    [FExx].n,CY    ;n=0..7                     |
|       7181+bbb*10  MOV1    [HL].n,CY      ;n=0..7                     |
|       7102+xxx*10  -                                                  |
|       7182+bbb*10  SET1    [HL].n         ;n=0..7                     |
|       7103+xxx*10  -                                                  |
|       7183+bbb*10  CLR1    [HL].n         ;n=0..7                     |
|       7104+bbb*10  MOV1    CY,[FExx].n    ;n=0..7                     |
|       7184+bbb*10  MOV1    CY,[HL].n      ;n=0..7                     |
|       7105+bbb*10  AND1    CY,[FExx].n    ;n=0..7                     |
|       7185+bbb*10  AND1    CY,[HL].n      ;n=0..7                     |
|       7106+bbb*10  OR1     CY,[FExx].n    ;n=0..7                     |
|       7186+bbb*10  OR1     CY,[HL].n      ;n=0..7                     |
|       7107+bbb*10  XOR1    CY,[FExx].n    ;n=0..7                     |
|       7187+bbb*10  XOR1    CY,[HL].n      ;n=0..7                     |
|       7108+xxx*10  -                                                  |
|       7188+xxx*10  -                                                  |
|       7109+bbb*10  MOV1    [FFxx].n,CY    ;n=0..7                     |
|       7189+xxx*10  -                                                  |
|       710A+bbb*10  SET1    [FFxx].n       ;n=0..7                     |
|       718A+xxx*10  -                                                  |
|       710B+bbb*10  CLR1    [FFxx].n       ;n=0..7                     |
|       718B+xxx*10  -                                                  |
|       710C+bbb*10  MOV1    CY,[FFxx].n    ;n=0..7                     |
|       718C+xxx*10  -                                                  |
|       710D+bbb*10  AND1    CY,[FFxx].n    ;n=0..7                     |
|       718D+xxx*10  -                                                  |
|       710E+bbb*10  OR1     CY,[FFxx].n    ;n=0..7                     |
|       718E+xxx*10  -                                                  |
|       710F+bbb*10  XOR1    CY,[FFxx].n    ;n=0..7                     |
|       718F+xxx*10  -                                                  |
|       7100         STOP                                               |
|       7110         HALT                                               |
+-----------------------------------------------------------------------+
```




