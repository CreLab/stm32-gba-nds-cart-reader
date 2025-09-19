# ARM VFP Floating Point Opcode Encoding


### Comparision of normal ARM copro opcodes and VFP opcodes

```
+-------------------------------------------------------------------------------------+
|       |..3 ..................2 ..................1 ..................0|             |
|       |1_0_9_8_7_6_5_4_3_2_1_0_9_8_7_6_5_4_3_2_1_0_9_8_7_6_5_4_3_2_1_0|             |
|       |_Cond__|1_1_0_0_0_1_0|L|__Rn___|__Rd___|__CP#__|_CPopc_|__CRm__| 2reg normal |
|       |_Cond__|1_1_0_0_0_1_0|L|__Rn___|__Rd___|__CP#__|0|0|M|1|__Fm___| 2reg on VFP |
|       |_Cond__|1_1_0|P|U|N|W|L|__Rn___|__CRd__|__CP#__|____Offset_____| Mem normal  |
|       |_Cond__|1_1_0|P|U|D|W|L|__Rn___|__Fd___|__CP#__|____Offset_____| Mem on VFP  |
|       |_Cond__|1_1_1_0|_CPopc_|__CRn__|__CRd__|__CP#__|_CP__|0|__CRm__| CDP normal  |
|       |_Cond__|1_1_1_0|p|D|q|r|__Fn___|__Fd___|__CP#__|N|s|M|0|__Fm___| CDP on VFP  |
|       |_Cond__|1_1_1_0|CPopc|L|__CRn__|__Rd___|__CP#__|_CP__|1|__CRm__| 1reg normal |
|       |_Cond__|1_1_1_0|CPopc|L|__Fn___|__Rd___|__CP#__|N|0_0|1|0_0_0_0| 1reg on VFP |
+-------------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|       Cond             = Condition                                               |
|       L                = Load/Store direction for memory/register transfers      |
|       Fm:M, Fn:N, Fd:D = Float Registers S0..S31 (or D0..D15, with LSB=0)        |
|       Rd, Rn           = ARM Registers                                           |
|       PUW, pqrs, CPopc = Opcode bits                                             |
|       CP#              = Coprocessor number (0Ah=Single-, 0Bh=Double-Precision)  |
|       Offset           = Address step, implies number of registers for FLDM/FSTM |
+----------------------------------------------------------------------------------+
```




