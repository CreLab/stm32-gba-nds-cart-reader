# ARM Opcodes: Memory: Block Data Transfer (LDM, STM)


**Opcode Format**

```
+-----------------------------------------------------------------------+
|       Bit    Expl.                                                    |
|       31-28  Condition                                                |
|       27-25  Must be 100b for this instruction                        |
|       24     P                                                        |
|  - Pre/Post (0=post; add offset after transfer, 1=pre; before trans.) |
|       23     U                                                        |
|  - Up/Down Bit (0=down; subtract offset from base, 1=up; add to base) |
|                                                                       |
| 22     S - PSR & force user bit (0=No, 1=load PSR or force user mode) |
|       2                                                               |
| 1     W - Write-back bit (0=no write-back, 1=write address into base) |
|                                                                       |
|     20     L - Load/Store bit (0=Store to memory, 1=Load from memory) |
|               0: STM{cond}{amod} Rn{!},<Rlist>{^}  ;Store (Push)      |
|               1: LDM{cond}{amod} Rn{!},<Rlist>{^}  ;Load  (Pop)       |
|               Whereas, {!}=Write-Back (W), and {^}=PSR/User Mode (S)  |
|                                                                       |
| 19-16  Rn - Base register                (R0-R14) (not including R15) |
|       15-0   Rlist - Register List                                    |
|       (A                                                              |
| bove 'offset' is meant to be the number of words specified in Rlist.) |
+-----------------------------------------------------------------------+
```

Return: No Flags affected.
Execution Time: For normal LDM, nS+1N+1I. For LDM PC, (n+1)S+2N+1I. For
STM (n-1)S+2N. Where n is the number of words transferred.

**Addressing Modes {amod}**
The IB,IA,DB,DA suffixes directly specify the desired U and P bits:

```
+-----------------------------------------------------------------------+
|       IB  increment before          ;P=1, U=1                         |
|       IA  increment after           ;P=0, U=1                         |
|       DB  decrement before          ;P=1, U=0                         |
|       DA  decrement after           ;P=0, U=0                         |
+-----------------------------------------------------------------------+
```

Alternately, FD,ED,FA,EA could be used, mostly to simplify mnemonics for
stack transfers.

```
+-----------------------------------------------------------------------+
|       ED  empty stack, descending   ;LDM: P=1, U=1  ;STM: P=0, U=0    |
|       FD  full stack,  descending   ;     P=0, U=1  ;     P=1, U=0    |
|       EA  empty stack, ascending    ;     P=1, U=0  ;     P=0, U=1    |
|       FA  full stack,  ascending    ;     P=0, U=0  ;     P=1, U=1    |
+-----------------------------------------------------------------------+
```

Ie. the following expressions are aliases for each other:

```
+-----------------------------------------------------------------------+
|       STMFD=STMDB=PUSH   STMED=STMDA   STMFA=STMIB   STMEA=STMIA      |
|       LDMFD=LDMIA=POP    LDMED=LDMIB   LDMFA=LDMDA   LDMEA=LDMDB      |
+-----------------------------------------------------------------------+
```

Note: The equivalent THUMB functions use fixed organization:

```
+-----------------------------------------------------------------------+
|       PUSH/POP: full descending     ;base register SP (R13)           |
|       LDM/STM:  increment after     ;base register R0..R7             |
+-----------------------------------------------------------------------+
```

Descending is common stack organization as used in 80x86 and Z80 CPUs,
SP is decremented when pushing/storing data, and incremented when
popping/loading data.

**When S Bit is set (S=1)**
If instruction is LDM and R15 is in the list: (Mode Changes)

```
+-----------------------------------------------------------------------+
|       While R15 loaded, additionally: CPSR=SPSR_<current mode>        |
+-----------------------------------------------------------------------+
```

Otherwise: (User bank transfer)

```
+-----------------------------------------------------------------------+
|       Rlist is referring to User Bank Registers, R0-R15 (rather than  |
|       register related to the current mode, such like R14_svc etc.)   |
|       Base write-back should not be used for User bank transfer.      |
|       Caution - When instruction is LDM:                              |
|       If                                                              |
| the following instruction reads from a banked register (eg. R14_svc), |
|       th                                                              |
| en CPU might still read R14 instead; if necessary insert a dummy NOP. |
+-----------------------------------------------------------------------+
```


**Notes**
The base address should be usually word-aligned.
LDM Rn,\...,PC on ARMv4 leaves CPSR.T unchanged.
LDR Rn,\...,PC on ARMv5 sets CPSR.T to \<op\> Bit0, (1=Switch t
Thumb).

**Transfer Order**
The lowest Register in Rlist (R0 if its in the list) will be
loaded/stored to/from the lowest memory address.
Internally, the rlist register are always processed with INCREASING
addresses (ie. for DECREASING addressing modes, the CPU does first
calculate the lowest address, and does then process rlist with
increasing addresses; this detail can be important when accessing memory
mapped I/O ports).

**Strange Effects on Invalid Rlist\'s**
Empty Rlist: R15 loaded/stored (ARMv4 only), and Rb=Rb+/-40h
(ARMv4-v5).
Writeback with Rb included in Rlist: Store OLD base if Rb is FIRST entry
in Rlist, otherwise store NEW base (STM/ARMv4), always store OLD base
(STM/ARMv5), no writeback (LDM/ARMv4), writeback if Rb is \"the ONL
register, or NOT the LAST register\" in Rlist (LDM/ARMv5).



