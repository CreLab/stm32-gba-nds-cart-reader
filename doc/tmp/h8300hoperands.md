# H8/300H Operands


### CPU Registers

```
+--------------------------------------------------------------------------+
|       R0..R6  32bit General Purpose   ;\can be alternately used as       
|       R7 (SP) 32bit Stack Pointer     ;/8bit/16bit registers (see below) |
|       PC      24bit Program Counter                                      |
|       CCR     8bit  Flags (occupies 16bit when pushed/stored in memory)  |
+--------------------------------------------------------------------------+
```

Registers R0..R7 can be split into 8bit/16bit registers (alike 80x86 registers):

```
+-----------------------------------------------------------------------+
|       .-----------------------.                                       |
|       | ERx                   | 32bit  (ERx)                          |
|       |-----------+-----------|                                       |
|       | Ex        | Rx        | 16bit  (Rx)                           |
|       '-----------+-----+-----|                                       |
|                   ' RxH | RxL | 8bit   (RxB)                          |
|                   '-----'-----'                                       |
+-----------------------------------------------------------------------+
```

There are no opcodes for splitting upper 16bit in Ex into 8bit ExL,ExH (except, the sign/zero-extend opcodes seem to allow to extend ExL to Ex).

### Normal and Extended Mode
The CPU can be wired to two different addressing modes:

```
+-----------------------------------------------------------------------+
|       Normal Mode   --> 16bit addressing (default)                    |
|       Extended Mode --> 24bit addressing                              |
+-----------------------------------------------------------------------+
```

Normal mode is usually used (the CPU has less than 64K ROM/RAM anyways), the opcodes with \[er0..er7\] memory addressing are then actually accessing \[r0..r7\], ie. the upper 16bit in e0..e7 are ignored (and can be used for general purpose data).
Extended mode, if it were ever used, uses the lower 24bit of er0..er7 for \[er0..er7\] addressing, and CALL/RET and indirect JMP opcodes are a bit slower, and exception vectors are 32bit wide.

### Memory Addressing
Data is stored in Big-Endian. 16bit/32bit values must be stored at even addresses (with bit0 cleared) (there is no need to clear bit1 for 32bit values, namely, push/pop work regardless of bit1).

```
+--------------------------------------------------------------------------------+
|       Native        Nocash                                                     |
|       @aa:8         [FFaa]        Memory at FF00h..FFFFh (upper RAM and SFR's) |
|       @aa:16        [nnnn]                                                     |
|       @aa:24        [nnnnnn]                                                   |
|       @Erm          [Erm]                                                      |
|       @(d:16,ERm)   [ERm+nnnn]                                                 |
|       @(d:24,ERm)   [ERm+nnnnnn]                                               |
|       @ERm+         [ERm+]          Memory access with post-increment          |
|       @-ERm         [ERm-]          Memory access with pre-decrement           |
|       (implied)     [ER6+],[ER5+]   Memory block transfer (EEPMOV)             |
+--------------------------------------------------------------------------------+
```


### Bit Addressing

```
+-----------------------------------------------------------------------+
|       Native        Nocash                                            |
|       #nn:8,@aa:8   [FFaa].n                                          |
|       RnB,@aa:8     [FFaa].RnB                                        |
|       #nn:8,RdB     RdB.n                                             |
|       RnB,RdB       RdB.RnB                                           |
+-----------------------------------------------------------------------+
```

Note: The \"#nn:8\" suggests native syntax to use \"#0x80\" to select bit7, however, the existing disassembler does instead use \"#7\".



