# 78K/0 Opcode List


### Move Byte

```
+---------------------------------------------------------------------------+
|       85/87/AB/AA/AE              MOV  A, [DE]/[HL]/[HL+B]/[HL+C]/[HL+nn] |
|       F0/F4/8E                    MOV  A, [FExx]/[FFxx]/[nnnn]            |
|       60/--/62/63/64/65/66/67     MOV  A, X/-/C/B/E/D/L/H                 |
|       70/--/72/73/74/75/76/77     MOV  X/-/C/B/E/D/L/H, A                 |
|       A0/A1/A2/A3/A4/A5/A6/A7     MOV  X/A/C/B/E/D/L/H, nn                |
|       95/97/BB/BA/BE              MOV  [DE]/[HL]/[HL+B]/[HL+C]/[HL+nn], A |
|       F2/F6/9E                    MOV  [FExx]/[FFxx]/[nnnn], A            |
|       11/13                       MOV  [FExx]/[FFxx], nn                  |
|       30/--/32/33/34/35/36/37     XCH  A, X/-/C/B/E/D/L/H                 |
|       05/07/318B/318A/DE          XCH  A, [DE]/[HL]/[HL+B]/[HL+C]/[HL+nn] |
|       83/93/CE                    XCH  A, [FExx]/[FFxx]/[nnnn]            |
+---------------------------------------------------------------------------+
```


### Move Word

```
+-----------------------------------------------------------------------------+
|       C2/C4/C6/10                 MOVW AX, BC/DE/HL/nnnn                    |
|       89/A9/02                    MOVW AX, [FExx]/[FFxx]/[nnnn]             |
|       D2/D4/D6                    MOVW BC/DE/HL, AX                         |
|       12/14/16                    MOVW BC/DE/HL, nnnn                       |
|       99/B9/03                    MOVW [FExx]/[FFxx]/[nnnn], AX             |
|       EE/FE                       MOVW [FExx]/[FFxx], nnnn                  |
|       E2/E4/E6                    XCHW AX,BC/DE/HL                          |
|       B1/B3/B5/B7/22              PUSH AX/BC/DE/HL/PSW  ;PSW=[FF1Eh] (8bit) |
|       B0/B2/B4/B6/23              POP  AX/BC/DE/HL/PSW  ;PSW=[FF1Eh] (8bit) |
+-----------------------------------------------------------------------------+
```


### ALU Byte

```
+-------------------------------------------------------------------------------------+
|       6100/6101/6102/6103/6104/6105/6106/6107  ADD  X/A/C/B/E/D/L/H, A              |
|       6120/6121/6122/6123/6124/6125/6126/6127  ADDC X/A/C/B/E/D/L/H, A              |
|       6110/6111/6112/6113/6114/6115/6116/6117  SUB  X/A/C/B/E/D/L/H, A              |
|       6130/6131/6132/6133/6134/6135/6136/6137  SUBC X/A/C/B/E/D/L/H, A              |
|       6140/6141/6142/6143/6144/6145/6146/6147  CMP  X/A/C/B/E/D/L/H, A              |
|       6150/6151/6152/6153/6154/6155/6156/6157  AND  X/A/C/B/E/D/L/H, A              |
|       6160/6161/6162/6163/6164/6165/6166/6167  OR   X/A/C/B/E/D/L/H, A              |
|       6170/6171/6172/6173/6174/6175/6176/6177  XOR  X/A/C/B/E/D/L/H, A              |
|       6108/----/610A/610B/610C/610D/610E/610F  ADD  A, X/-/C/B/E/D/L/H              |
|       6128/----/612A/612B/612C/612D/612E/612F  ADDC A, X/-/C/B/E/D/L/H              |
|       6118/----/611A/611B/611C/611D/611E/611F  SUB  A, X/-/C/B/E/D/L/H              |
|       6138/----/613A/613B/613C/613D/613E/613F  SUBC A, X/-/C/B/E/D/L/H              |
|       6148/----/614A/614B/614C/614D/614E/614F  CMP  A, X/-/C/B/E/D/L/H              |
|       6158/----/615A/615B/615C/615D/615E/615F  AND  A, X/-/C/B/E/D/L/H              |
|       6168/----/616A/616B/616C/616D/616E/616F  OR   A, X/-/C/B/E/D/L/H              |
|       6178/----/617A/617B/617C/617D/617E/617F  XOR  A, X/-/C/B/E/D/L/H              |
|       0D/0F/310B/310A/09/0E/08   ADD  A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       2D/2F/312B/312A/29/2E/28   ADDC A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       1D/1F/311B/311A/19/1E/18   SUB  A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       3D/3F/313B/313A/39/3E/38   SUBC A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       4D/4F/314B/314A/49/4E/48   CMP  A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       5D/5F/315B/315A/59/5E/58   AND  A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       6D/6F/316B/316A/69/6E/68   OR   A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       7D/7F/317B/317A/79/7E/78   XOR  A,nn/[HL]/[HL+B]/[HL+C]/[HL+nn]/[FExx]/[nnnn] |
|       88                         ADD  [FExx], nn                                    |
|       A8                         ADDC [FExx], nn                                    |
|       98                         SUB  [FExx], nn                                    |
|       B8                         SUBC [FExx], nn                                    |
|       C8                         CMP  [FExx], nn                                    |
|       D8                         AND  [FExx], nn                                    |
|       E8                         OR   [FExx], nn                                    |
|       F8                         XOR  [FExx], nn                                    |
|       40/41/42/43/44/45/46/47/81 INC  X/A/C/B/E/D/L/H/[FExx]                        |
|       50/51/52/53/54/55/56/57/91 DEC  X/A/C/B/E/D/L/H/[FExx]                        |
+-------------------------------------------------------------------------------------+
```


### ALU Word

```
+-----------------------------------------------------------------------+
|       CA/DA/EA                   ADDW/SUBW/CMPW AX,nnnn               |
|       80/82/84/86                INCW AX/BC/DE/HL                     |
|       90/92/94/96                DECW AX/BC/DE/HL                     |
+-----------------------------------------------------------------------+
```


### Rotate/Shift

```
+-------------------------------------------------------------------------------------+
|       26                         ROL  A,1                                           |
|       24                         ROR  A,1                                           |
|       27                         ROLC A,1                                           |
|       25                         RORC A,1                                           |
|       3180                       ROL4 A,[HL] ;12bit A.lsb:[HL],4 ;native: ROL4 [HL] |
|       3190                       ROR4 A,[HL] ;12bit A.lsb:[HL],4 ;native: ROR4 [HL] |
+-------------------------------------------------------------------------------------+
```


### Jump/Call

```
+--------------------------------------------------------------------------------+
|       3198                       JMP  AX                    ;native: BR AX     |
|       9B                         JMP  absolute addr         ;native: BR        |
|       FA                         JMP  relative short addr   ;native: BR        |
|       9A                         CALL absolute addr         ;native: CALL      |
|       C1+(nn AND 3Eh)            CALL [40h..7Eh]            ;native: CALLT     |
|       0C/1C/2C/3C/4C/5C/6C/7C    CALLF 08nn/09nn/0Ann/0Bnn/0Cnn/0Dnn/0Enn/0Fnn |
+--------------------------------------------------------------------------------+
```


### Conditional Relative Jumps

```
+-------------------------------------------------------------------------------------+
|       8D                         JC  aka JB  rel  ;carry/below        ;native: BC   |
|       AD                         JZ  aka JE  rel  ;zero/equal         ;native: BZ   |
|       9D                         JNC aka JAE rel  ;not carry/below    ;native: BNC  |
|       BD                         JNZ aka JNE rel  ;not zero/equal     ;native: BNZ  |
|       04/8B/8A                   DJNZ [FExx]/B/C, rel  ;decrement+jnz ;native: DBNZ |
+-------------------------------------------------------------------------------------+
```


### Test (and Clear) and Conditional Relative Jump

```
+-----------------------------------------------------------------------+
|       3101/3105/3185/310D+n*10   BTCLR [FExx]/[FFxx]/[HL]/A.n, rel    |
|       8C/3106/3186/310E+n*10     BT    [FExx]/[FFxx]/[HL]/A.n, rel    |
|       3103/3107/3187/310F+n*10   BF    [FExx]/[FFxx]/[HL]/A.n, rel    |
+-----------------------------------------------------------------------+
```


### Bit Manipulation

```
+-----------------------------------------------------------------------+
|       7101/7109/7181/6189+n*10   MOV1 [FExx]/[FFxx]/[HL]/A.n, CY      |
|       7104/710C/7184/618C+n*10   MOV1 CY, [FExx]/[FFxx]/[HL]/A.n      |
|       7105/710D/7185/618D+n*10   AND1 CY, [FExx]/[FFxx]/[HL]/A.n      |
|       7106/710E/7186/618E+n*10   OR1  CY, [FExx]/[FFxx]/[HL]/A.n      |
|       7107/710F/7187/618F+n*10   XOR1 CY, [FExx]/[FFxx]/[HL]/A.n      |
|       20/0A/710A/7182/618A+n*10  SET1 CY/[FExx]/[FFxx]/[HL]/A.n       |
|       21/0B/710B/7183/618B+n*10  CLR1 CY/[FExx]/[FFxx]/[HL]/A.n       |
|       01                         NOT1 CY                              |
+-----------------------------------------------------------------------+
```


### Misc

```
+------------------------------------------------------------------------------------+
|       00                         NOP                                               |
|       BF/7110/7100               BRK/HALT/STOP                                     |
|       AF/9F/8F                   RET/RETB/RETI                                     |
|       61D0/61D8/61F0/61F8        SEL RB0/1/2/3                                     |
|       3188                       MULU AX,A,X   ;unsigned AX=A*X    ;native: MULU X |
|       3182                       DIVUW AX,C    ;unsigned AX=AX/C, C=remainder   ;X |
|       6180/6190                  ADJBA/ADJBS   ;decimal BCD adjust A after Add/Sub |
|       7A1E/7B1E                  EI/DI         ;pseudo SET1/CLR1 PSW.7             |
|       FA                         JR addr       ;pseudo jmp short relative addr     |
+------------------------------------------------------------------------------------+
```


### Note
Operand \[FExx\] can he in range FE20h..FF1Fh, of which FE20h..FEFFh is encoded as 20..FF, and FF00h..FF1Fh is encoded as 00..1F (the latter overlaps with operand \[FFxx\]) (for the overlapping addresses, \[FExx\] is preferred because BT/SET1/CLR1 have smaller encoding for \[FExx\] than \[FFxx\], and DJNZ/ALU support only \[FExx\]) (all opcodes that support \[FFxx\] do also support \[FExx\], so \[FFxx\] should be NEVER used for \[FF00..FF1F\]).



