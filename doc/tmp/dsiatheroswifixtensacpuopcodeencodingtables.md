# DSi Atheros Wifi - Xtensa CPU Opcode Encoding Tables


### Xtensa Opcodes
Xtensa opcodes are 24bit wide (or 16bit for \"narrow\" opcodes), the opcodes consist of several 4bit fields (or 2bit, 8bit, 12bit, 16bit, 18bit fields in some cases):

```
+------------------------------------------------------------------------+
|       23-20  19-16  15-12  11-8  7-4   3-0   Type                      |
|       op2    op1    r      s     t     op0   RRR                       |
|       imm4   op1    r      s     t     op0   RRI4                      |
|       imm8--------> r      s     t     op0   RRI8                      |
|       imm16------------------->  t     op0   RRI16                     |
|       op2    op1    rs-------->  t     op0   RSR                       |
|       offset----------------------> n  op0   CALL                      |
|       op2    op1    r      s     m  n  op0   CALLX                     |
|       imm8--------> r      s     m  n  op0   BRI8                      |
|       imm12------------->  s     m  n  op0   BRI8                      |
|                     r      s     t     op0   RRRN                      |
|                     imm.l  s     imm.h op0   RI7  (bit7="i")           |
|                     imm.l  s     imm.h op0   RI6  (bit7="i", bit6="z") |
+------------------------------------------------------------------------+
```


### Xtensa Opcode Root- and Subtables (Summary)
Opcode decoding can be done in 4bit units, starting at the \"op0\" field, and then decoding further 4bit field(s) depending on the opcode. Decoding speed could be improved by grouping two 4bit fields into a 8bit field (eg. op2 and op1; that won\'t work out perfectly for all opcodes though).

```
+-------------------------------------------------------------------------------+
|       ROOT\                        op0                                        
|       ROOT\QRST                    op0=0, op1                                 
|       ROOT\QRST\RST0               op0=0, op1=0, op2                          
|       ROOT\QRST\RST0\ST0           op0=0, op1=0, op2=0, r                     
|       ROOT\QRST\RST0\ST0\SNM0      op0=0, op1=0, op2=0, r=0, mn               
|       ROOT\QRST\RST0\ST0\SYNC      op0=0, op1=0, op2=0, r=2, t                
|       ROOT\QRST\RST0\ST0\RFEI      op0=0, op1=0, op2=0, r=3, t                
|       ROOT\QRST\RST0\ST0\RFEI\RFET op0=0, op1=0, op2=0, r=3, t=0, s           
|       ROOT\QRST\RST0\ST1           op0=0, op1=0, op2=4, r                     
|       ROOT\QRST\RST0\TLB           op0=0, op1=0, op2=5, r                     
|       ROOT\QRST\RST0\RT0           op0=0, op1=0, op2=6, s                     
|       ROOT\QRST\RST1               op0=0, op1=1, op2                          
|       ROOT\QRST\RST1\IMP           op0=0, op1=1, op2=F, r                     
|       ROOT\QRST\RST1\IMP\RFDX      op0=0, op1=1, op2=F, r=E, t                
|       ROOT\QRST\RST2               op0=0, op1=2, op2                          
|       ROOT\QRST\RST3               op0=0, op1=3, op2                          
|       ROOT\QRST\LSCX               op0=0, op1=8, op2                          
|       ROOT\QRST\LSC4               op0=0, op1=9, op2                          
|       ROOT\QRST\FP0                op0=0, op1=A, op2                          
|       ROOT\QRST\FP0\FP1OP          op0=0, op1=A, op2=F, t                     
|       ROOT\QRST\FP1                op0=0, op1=B, op2                          
|       ROOT\LSAI                    op0=2, r                                   
|       ROOT\LSAI\CACHE              op0=2, r=7, t                              
|       ROOT\LSAI\CACHE\DCE          op0=2, r=7, t=8, op1                       
|       ROOT\LSAI\CACHE\ICE          op0=2, r=7, t=D, op1                       
|       ROOT\LSCI                    op0=3, r                                   
|       ROOT\MAC16                   op0=4, op2                                 
|       ROOT\MAC16\MACID             op0=4, op2=0, op1                          
|       ROOT\MAC16\MACCD             op0=4, op2=1, op1                          
|       ROOT\MAC16\MACDD             op0=4, op2=2, op1                          
|       ROOT\MAC16\MACAD             op0=4, op2=3, op1                          
|       ROOT\MAC16\MACIA             op0=4, op2=4, op1                          
|       ROOT\MAC16\MACCA             op0=4, op2=5, op1                          
|       ROOT\MAC16\MACDA             op0=4, op2=6, op1                          
|       ROOT\MAC16\MACAA             op0=4, op2=7, op1                          
|       ROOT\MAC16\MACI              op0=4, op2=8, op1                          
|       ROOT\MAC16\MACC              op0=4, op2=9, op1                          
|       ROOT\CALLN                   op0=5, mn                                  
|       ROOT\SI                      op0=6, mn   (and \SI\BZ, \SI\BI0, \SI\BI1) 
|       ROOT\SI\BI1\B1               op0=6, mn=7, r                             
|       ROOT\B                       op0=7, r                                   
|       ROOT\ST2                     op0=C, t                                   
|       ROOT\ST3                     op0=D, r                                   
|       ROOT\ST3\S3                  op0=D, r=F, t                              
+-------------------------------------------------------------------------------+
```


### Xtensa Opcode Root- and Subtables (Complete)
Below is showing the whole opcode \"tree\", starting with the root table (indexed via op0). Entries with \"\--\>\" are referencing to child tables, the other entries are indicating the actual opcodes (or reserved opcodes). The lower-case suffices are somewhat indicating optional opcodes.

```
+----------------------------------------------------------------------------------+
|         ROOT\             ROOT\QRST         ROOT\QRST\RS      ROOT\QRST\RST0\ST0 
|         op0               op1               op2               r                  |
|       0 --> QRST          --> RST0          --> ST0           --> SNM0           |
|       1 L32R              --> RST1          AND               MOVSP              |
|       2 --> LSAI          --> RST2          OR                --> SYNC           |
|       3 --> LSCIp         --> RST3          XOR               --> RFEIx          |
|       4 --> MAC16d        EXTUI ;\          --> ST1           BREAKx             
|       5 --> CALLN         EXTUI ;/          --> TLB           SYSCALLx           |
|       6 --> SI            CUST0 ;\          --> RT0           RSILx              
|       7 --> B             CUST1 ;/          reserved          WAITIx (t=0)       |
|       8 L32I.Nn  ;\       --> LSCXp         ADD               ANY4p              
|       9 S32I.Nn  ;        --> LSC4          ADDX2             ALL4p              |
|       A ADD.Nn   ; narrow --> FP0f          ADDX4             ANY8p              |
|       B ADDI.Nn  ; 16bit  --> FP1f          ADDX8             ALL8p              |
|       C --> ST2n ;        reserved          SUB               reserved           |
|       D --> ST3n ;/       reserved          SUBX2             reserved           |
|       E reserved          reserved          SUBX4             reserved           |
|       F reserved          reserved          SUBX8             reserved           |
+----------------------------------------------------------------------------------+
```



```
+--------------------------------------------------------------------------------+
|         ..\RST0\ST0\SNM0  ..\RST0\ST0\SYNC  ..\RST0\ST0\RFEI  ..\ST0\RFEI\RFET 
|         mn                t                 t                 s                |
|       0 ILL      ;\       ISYNC             --> RFETx         RFEx             
|       1 reserved ; ILL    RSYNC             RFIx              RFUEx            |
|       2 reserved ;        ESYNC             RFME (s=0)        RFDEx            |
|       3 reserved ;/       DSYNC             reserved          reserved         |
|       4 reserved ;\       reserved          reserved          RFWOw            
|       5 reserved ; N/A    reserved          reserved          RFWUw            |
|       6 reserved ;        reserved          reserved          reserved         |
|       7 reserved ;/       reserved          reserved          reserved         |
|       8 RET      ;\       EXCW              reserved          reserved         
|       9 RETWw    ; JR     reserved          reserved          reserved         |
|       A JX       ;        reserved          reserved          reserved         |
|       B reserved ;/       reserved          reserved          reserved         |
|       C CALLX0   ;\       MEMW              reserved          reserved         
|       D CALLX4w  ; CALLX  EXTW              reserved          reserved         |
|       E CALLX8w  ;        reserved          reserved          reserved         |
|       F CALLX12w ;/       NOP/reserved      reserved          reserved         |
+--------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------+
|         ..\RST0\ST1       ..\RST0\TLB       ..\RST0\RT0       ROOT\QRST\RST1 
|         r                 r                 s                 op2            |
|       0 SSR (t=0)         reserved          NEG               SLLI ;\        
|       1 SSL (t=0)         reserved          ABS               SLLI ;/        |
|       2 SSA8L (t=0)       reserved          reserved          SRAI ;\        
|       3 SSA8B (t=0)       RITLB0            reserved          SRAI ;/        |
|       4 SSAI (t=0)        IITLB (t=0)       reserved          SRLI ;-        |
|       5 reserved          PITLB             reserved          reserved       |
|       6 RER               WITLB             reserved          XSR            |
|       7 WER               RITLB1            reserved          --> ACCER (?)  |
|       8 ROTWw (s=0)       reserved          reserved          SRC            |
|       9 reserved          reserved          reserved          SRL (s=0)      |
|       A reserved          reserved          reserved          SLL (t=0)      |
|       B reserved          RDTLB0            reserved          SRA (s=0)      |
|       C reserved          IDTLB (t=0)       reserved          MUL16U         |
|       D reserved          PDTLB             reserved          MUL16S         |
|       E NSAu              WDTLB             reserved          reserved       |
|       F NSAUu             RDTLB1            reserved          --> IMP        |
+------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------+
|         ..\RST1\IMP       ..\RST1\IMP\RFDX  ROOT\QRST\RST2    ROOT\QRST\RST3 
|         r                 t                 op2               op2            |
|       0 LICT              RFDO (s=0)        ABDBp             RSR            |
|       1 SICT              RFDD (s=0,1)      ANDBCp            WSR            |
|       2 LICW              reserved          ORBp              SEXTu          |
|       3 SICW              reserved          ORBCp             CLAMPSu        |
|       4 reserved          reserved          XORBp             MINu           |
|       5 reserved          reserved          reserved          MAXu           |
|       6 reserved          reserved          reserved          MINUu          |
|       7 reserved          reserved          reserved          MAXUu          |
|       8 LDCT              reserved          MULLi             MOVEQZ         |
|       9 SDCT              reserved          reserved          MOVNEZ         |
|       A reserved          reserved          MULUHi            MOVLTZ         |
|       B reserved          reserved          MULSHi            MOVGEZ         |
|       C reserved          reserved          QUOUi             MOVFp          |
|       D reserved          reserved          QUOSi             MOVTp          |
|       E --> RFDX          reserved          REMUi             RUR            |
|       F reserved          reserved          REMSi             WUR            |
+------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|         ROOT\QRST\LSCX    ROOT\QRST\LSC4    ROOT\QRST\FP0     ROOT\QRST\FP0\FP1OP 
|         op2               op2               op2               t                   |
|       0 LSXf              L32E              ADD.Sf            MOV.Sf              |
|       1 LSXUf             reserved          SUB.Sf            ABS.Sf              |
|       2 reserved          reserved          MUL.Sf            reserved            |
|       3 reserved          reserved          reserved          reserved            |
|       4 SSXf              S32E              MADD.Sf           RFRf                |
|       5 SSXUf             reserved          MSUB.Sf           WFRf                |
|       6 reserved          reserved          reserved          NEG.Sf              |
|       7 reserved          reserved          reserved          reserved            |
|       8 reserved          reserved          ROUND.Sf          reserved            |
|       9 reserved          reserved          TRUNC.Sf          reserved            |
|       A reserved          reserved          FLOOR.Sf          reserved            |
|       B reserved          reserved          CEIL.Sf           reserved            |
|       C reserved          reserved          FLOAT.Sf          reserved            |
|       D reserved          reserved          UFLOAT.Sf         reserved            |
|       E reserved          reserved          UTRUNC.Sf         reserved            |
|       F reserved          reserved          --> FP1OPf        reserved            |
+-----------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------+
|         ROOT\QRST\FP1     ROOT\LSAI         ROOT\LSAI\CACHE   ..\CACHE\DCE 
|         op2               r                 t                 op1          |
|       0 reserved          L8UI              DPFRc             DPFLl        |
|       1 UN.Sf             L16UI             DPFWc             reserved     |
|       2 OEQ.Sf            L32I              DPFROc            DHUl         |
|       3 UEQ.Sf            reserved          DPFWOc            DIUl         |
|       4 OLT.Sf            S8I               DHWBc             DIWBc        |
|       5 ULT.Sf            S16I              DHWBIc            DIWBIc       |
|       6 OLE.Sf            S32I              DHIc              reserved     |
|       7 ULE.Sf            --> CACHEc        DIIc              reserved     |
|       8 MOVEQZ.Sf         reserved          --> DCEc          reserved     |
|       9 MOVNEZ.Sf         L16SI             reserved          reserved     |
|       A MOVLTZ.Sf         MOVI              reserved          reserved     |
|       B MOVGEZ.Sf         L32AIy            reserved          reserved     |
|       C MOVF.Sf           ADDI              IPFc              reserved     |
|       D MOVT.Sf           ADDMI             --> ICEc          reserved     |
|       E reserved          S32C1Iy           IHIc              reserved     |
|       F reserved          S32RIy            IIIc              reserved     |
+----------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|         ..\CACHE\ICE      ROOT\LSCI         ROOT\CALLN        ROOT\SI 
|         op1               r                 mn                mn      |
|       0 IPFLl             LSIf              CALL0  ;\         J       
|       1 reserved          reserved          CALL4  ;          BEQZ    |
|       2 IHUl              reserved          CALL8  ;          BEQI    |
|       3 IIUl              reserved          CALL12 ;/         ENTRYw  |
|       4 reserved          SSIf              CALL0  ;\         J       
|       5 reserved          reserved          CALL4  ;          BNEZ    |
|       6 reserved          reserved          CALL8  ;          BNEI    |
|       7 reserved          reserved          CALL12 ;/         --> B1  |
|       8 reserved          LSIUf             CALL0  ;\         J       
|       9 reserved          reserved          CALL4  ;          BLTZ    |
|       A reserved          reserved          CALL8  ;          BLTI    |
|       B reserved          reserved          CALL12 ;/         BLTUI   |
|       C reserved          SSIUf             CALL0  ;\         J       
|       D reserved          reserved          CALL4  ;          BGEZ    |
|       E reserved          reserved          CALL8  ;          BGEI    |
|       F reserved          reserved          CALL12 ;/         BGEUI   |
+-----------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------+
|         ROOT\SI\BI1\B1    ROOT\B            ROOT\ST2          ROOT\ST3 
|         r                 r                 t                 r        |
|       0 BFp               BNONE             MOVI.Nn ;\        MOV.Nn   
|       1 BTp               BEQ               MOVI.Nn ;         reserved |
|       2 reserved          BLT               MOVI.Nn ;         reserved |
|       3 reserved          BLTU              MOVI.Nn ;         reserved |
|       4 reserved          BALL              MOVI.Nn ;         reserved |
|       5 reserved          BBC               MOVI.Nn ;         reserved |
|       6 reserved          BBCI ;\           MOVI.Nn ;         reserved 
|       7 reserved          BBCI ;/           MOVI.Nn ;/        reserved |
|       8 LOOP              BANY              BEQZ.Nn ;\        reserved 
|       9 LOOPNEZ           BNE               BEQZ.Nn ;         reserved |
|       A LOOPGTZ           BGE               BEQZ.Nn ;         reserved |
|       B reserved          BGEU              BEQZ.Nn ;/        reserved |
|       C reserved          BNALL             BNEZ.Nn ;\        reserved 
|       D reserved          BBS               BNEZ.Nn ;         reserved |
|       E reserved          BBSI ;\           BNEZ.Nn ;         reserved 
|       F reserved          BBSI ;/           BNEZ.Nn ;/        --> S3   |
+------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------+
|         ROOT\ST3\S3       ROOT\MAC16        ROOT\MAC16\MACI   ROOT\MAC16\MACC 
|         t                 op2               op1               op1             |
|       0 RET.Nn            --> MACID         LDINC             LDDEC           |
|       1 RETW.Nwn          --> MACCD         reserved          reserved        |
|       2 BREAK.Nn          --> MACDD         reserved          reserved        |
|       3 NOP.Nn            --> MACAD         reserved          reserved        |
|       4 reserved          --> MACIA         reserved          reserved        |
|       5 reserved          --> MACCA         reserved          reserved        |
|       6 ILL.Nn            --> MACDA         reserved          reserved        |
|       7 reserved          --> MACAA         reserved          reserved        |
|       8 reserved          --> MACI          reserved          reserved        |
|       9 reserved          --> MACC          reserved          reserved        |
|       A reserved          reserved          reserved          reserved        |
|       B reserved          reserved          reserved          reserved        |
|       C reserved          reserved          reserved          reserved        |
|       D reserved          reserved          reserved          reserved        |
|       E reserved          reserved          reserved          reserved        |
|       F reserved          reserved          reserved          reserved        |
+-------------------------------------------------------------------------------+
```



```
+--------------------------------------------------------------------------------+
|         ROOT\MAC16\MACID  ROOT\MAC16\MACCD  ROOT\MAC16\MACIA  ROOT\MAC16\MACCA 
|         op1               op1               op1               op1              |
|       0 reserved          reserved          reserved          reserved         |
|       1 reserved          reserved          reserved          reserved         |
|       2 reserved          reserved          reserved          reserved         |
|       3 reserved          reserved          reserved          reserved         |
|       4 reserved          reserved          reserved          reserved         |
|       5 reserved          reserved          reserved          reserved         |
|       6 reserved          reserved          reserved          reserved         |
|       7 reserved          reserved          reserved          reserved         |
|       8 MULA.DD.LL.LDINC  MULA.DD.LL.LDDEC  MULA.DA.LL.LDINC  MULA.DA.LL.LDDEC |
|       9 MULA.DD.HL.LDINC  MULA.DD.HL.LDDEC  MULA.DA.HL.LDINC  MULA.DA.HL.LDDEC |
|       A MULA.DD.LH.LDINC  MULA.DD.LH.LDDEC  MULA.DA.LH.LDINC  MULA.DA.LH.LDDEC |
|       B MULA.DD.HH.LDINC  MULA.DD.HH.LDDEC  MULA.DA.HH.LDINC  MULA.DA.HH.LDDEC |
|       C reserved          reserved          reserved          reserved         |
|       D reserved          reserved          reserved          reserved         |
|       E reserved          reserved          reserved          reserved         |
|       F reserved          reserved          reserved          reserved         |
+--------------------------------------------------------------------------------+
```



```
+--------------------------------------------------------------------------------+
|         ROOT\MAC16\MACDD  ROOT\MAC16\MACAD  ROOT\MAC16\MACDA  ROOT\MAC16\MACAA 
|         op1               op1               op1               op1              |
|       0 reserved          reserved          reserved          UMUL.AA.LL       |
|       1 reserved          reserved          reserved          UMUL.AA.HL       |
|       2 reserved          reserved          reserved          UMUL.AA.LH       |
|       3 reserved          reserved          reserved          UMUL.AA.HH       |
|       4 MUL.DD.LL         MUL.AD.LL         MUL.DA.LL         MUL.AA.LL        |
|       5 MUL.DD.HL         MUL.AD.HL         MUL.DA.HL         MUL.AA.HL        |
|       6 MUL.DD.LH         MUL.AD.LH         MUL.DA.LH         MUL.AA.LH        |
|       7 MUL.DD.HH         MUL.AD.HH         MUL.DA.HH         MUL.AA.HH        |
|       8 MULA.DD.LL        MULA.AD.LL        MULA.DA.LL        MULA.AA.LL       |
|       9 MULA.DD.HL        MULA.AD.HL        MULA.DA.HL        MULA.AA.HL       |
|       A MULA.DD.LH        MULA.AD.LH        MULA.DA.LH        MULA.AA.LH       |
|       B MULA.DD.HH        MULA.AD.HH        MULA.DA.HH        MULA.AA.HH       |
|       C MULS.DD.LL        MULS.AD.LL        MULS.DA.LL        MULS.AA.LL       |
|       D MULS.DD.HL        MULS.AD.HL        MULS.DA.HL        MULS.AA.HL       |
|       E MULS.DD.LH        MULS.AD.LH        MULS.DA.LH        MULS.AA.LH       |
|       F MULS.DD.HH        MULS.AD.HH        MULS.DA.HH        MULS.AA.HH       |
+--------------------------------------------------------------------------------+
```




