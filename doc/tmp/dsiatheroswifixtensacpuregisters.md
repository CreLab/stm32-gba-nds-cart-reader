# DSi Atheros Wifi - Xtensa CPU Registers


### Xtensa Core Registers

```
+------------------------------------------------------------------------------------+
|       -              AR      Address registers A0..A15 (general purpose registers) |
|       -              PC      Program Counter                                       |
+------------------------------------------------------------------------------------+
```

The AR registers are used as so:

```
+--------------------------------------------------------------------------+
|       A0       general purpose (and return address for CALL/RET opcodes) |
|       A1       general purpose (commonly used as stack pointer)          |
|       A2..A15  general purpose                                           |
+--------------------------------------------------------------------------+
```

Chips with Windowed Code option are actually having more than sixteen AR registers, and the register window is rotated by CALL4/CALL8/CALL12/RETW opcodes (allowing to save/restore registers without needing to push/pop them in memory):

```
+-------------------------------------------------------------------------------------+
|       CALL4   saves A0..A3 and moves A4..A15 to A0..A11  ;\and, probably copies     
|       CALL8   saves A0..A7 and moves A8..A15 to A0..A7   ; old A1 to new A1 (?),    |
|       CALL12  saves A0..A11 and moves A12..A15 to A0..A3 ;/and new A0=ret_addr      |
|       ENTRY   used at begin of sub-functions (allocate local variables on stack)    |
|       RETW    windowed return (deallocate locals, and undo the CALL4/8/12 rotation) |
+-------------------------------------------------------------------------------------+
```

The sub-functions will have retaddr/stack in A0/A1, and incoming parameters in A2 and up, and return value in A2. However, due to the rotation, the caller will see parameters/return value elsewhere (eg. for CALL8, parameters in A10 and up, and return value in A10).
The ENTRY opcode is used to allocate local variables on stack. For some weird reason ENTRY is usually also allocating \"N\*4 bytes\" dummy space for the \"N\" saved words (as if they were intended to be pushed on stack, rather than being saved via rotation, maybe some exception handler is actually USING that dummy space when the register window gets full(?), the AR6002 BIOS contains a few functions that aren\'t allocating enough dummy words though, eg. 8EDE44h uses \"entry a1,10h\" although being called via CALL8).

### Xtensa Special Registers

```
+------------------------------------------------------------------------------------+
|       0        00h   LBEG    Loop Begin                  ;\                        
|       1        01h   LEND    Loop End                    ; Loop option             |
|       2        02h   LCOUNT  Loop Count                  ;/                        |
|       3        03h   SAR     Shift-Amount Register       ;-Core                    |
|       4        04h   BR      Boolean Registers (16x1bit) ;-Boolean option          |
|       5        05h   LITBASE Literal Base                ;-Literal base option     |
|       12       0Ch   SCOMPARE1                      ;-Multiprocessor... vs S32C1I  |
|       16       10h   ACCLO   Accumulator low (32bit)     ;\                        
|       17       11h   ACCHI   Accumulator high (8bit)     ;                         |
|       32       20h   MR0     MAC16 register m0 (32bit)   ; MAC16 option            |
|       33       21h   MR1     MAC16 register m1 (32bit)   ;                         |
|       34       22h   MR2     MAC16 register m2 (32bit)   ;                         |
|       35       23h   MR3     MAC16 register m3 (32bit)   ;/                        |
|       177      B1h   EPC[1]  Exception Program Counter   ;\                        
|       232      E8h   EXCAUSE Cause of last Exception     ;                         |
|       209      D1h   EXCSAVE[1]                          ;                         |
|       230      E6h   PS                                  ; Exception option        |
|       230      E6h   PS.EXCM                             ;                         |
|       238      EEH   EXCVADDR                            ;                         |
|       192      C0h   DEPC                                ;/                        |
|       see            PS.INTLEVEL                         ;-Interrupt option        |
|       178..183 B2h.. EPC[2..7]                    ;\                               
|       194..199 C2h.. EPS[2..7]                    ; High-Priority Interrupt option |
|       210..215 D2h.. EXCSAVE[2..7]                ;/                               |
|       234      EAh   CCOUNT                       ;\Timer Interrupt option         
|       240-242  F0h   CCOMPARE                     ;/                               |
|       -              AR[NAREG]                    ;\                               
|       72       48h   WindowBase                   ; Windowed Register option       |
|       73       49h   WindowStart                  ;                                |
|       230      E6h   PS.CALLINC                   ;                                |
|       230      E6h   PS.OWB                       ;                                |
|       230      E6h   PS.WOE                       ;/                               |
|       244-247  F4h.. MISC                         ;-Misc Special Register option   |
|       236      ECh   ICOUNT                       ;\                               
|       237      EDh   ICOUNTLEVEL                  ;                                |
|       128-129  80h.. IBREAKA                      ;                                |
|       96       60h   IBREAKENABLE                 ; Debug option                   |
|       144-145  90h.. DBREAKA                      ;                                |
|       160-161  A0h.. DBREAKC                      ;                                |
|       233      E9h   DEBUGCAUSE                   ;                                |
|       104      68h   DDR                          ;/                               |
|       230      E6h   PS.RING                      ;\                               
|       83       53h   PTEVADDR                     ;                                |
|       90       5Ah   RASID                        ; MMU option                     |
|       91       5Bh   ITLBCFG                      ;                                |
|       92       5Ch   DTLBCFG                      ;                                |
|       see            ITLB                         ;                                |
|       see            DTLB                         ;/                               |
|       98       62h   CACHEATTR    ;-                                               |
|       99       63h   ATOMCTL      ;-                                               |
|       224      E0h   CPENABLE     ;-                                               |
|       226      E2h   INTERRUPT (R);\                                               
|       226      E2h   INTSET    (W); Interrupt                                      |
|       227      E3h   INTCLEAR     ;                                                |
|       228      E4h   INTENABLE    ;/                                               |
|       106      6Ah   MEPC         ;\                                               
|       107      6Bh   MEPS         ;                                                |
|       108      6Ch   MESAVE       ; Memory ECC/Parity                              |
|       109      6Dh   MESR         ;                                                |
|       110      6Eh   MECR         ;                                                |
|       111      6Fh   MEVADDR      ;/                                               |
|       89       59h   MMID         ;-Trace Port                                     |
|       231      E7h   VECBASE      ;-                                               |
|       235      EBh   PRID         ;-Processor ID                                   |
+------------------------------------------------------------------------------------+
```


XSR with \>=64 is privileged.

### Xtensa User Registers

```
+-------------------------------------------------------------------------------------+
|       0-223    0-DFh Available for designer extensions                              |
|       192-255  C0h.. Reserved by Tensilica (conflicts with above "available" info?) |
|       231      E7h   THREADPTR                      ;-Thread Pointer                |
|       232      E8h   FCR        (float control)     ;\                              
|       233      E9h   FSR        (float status)      ; Float                         |
|       -              FR         (f0..f15?)          ;/                              |
+-------------------------------------------------------------------------------------+
```




