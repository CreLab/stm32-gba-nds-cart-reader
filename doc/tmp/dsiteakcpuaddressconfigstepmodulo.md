# DSi Teak CPU Address Config/Step/Modulo



```
+-------------------------------------------------------------------------------------+
|      _______________________________ Address Config _______________________________ |
+-------------------------------------------------------------------------------------+
```


These registers allow to reconfigure opcodes. For example, opcodes with operand MemR45 can normally use only R4/R5 operands; if desired that can be changed to anything else like R3/R0. The selection if Offset/Step operands can be changed in similar way.

```
+-----------------------------------------------------------------------+
|       Unknown which settings affect which opcodes exactly.            |
+-----------------------------------------------------------------------+
```

The DSi Sound code is using a default configuration for most of its code, but it does also have some functions with alternate configurations.

### ar0/ar1

```
+------------------------------------------------------------------------------+
|       0-2   R/W PM1/PM3 Post Modify Step    (0..7 = +0,+1,-1,+s,+2,-2,+2,-2) |
|       3-4   R/W CS1/CS3 Offset              (0..3 = +0,+1,-1,-1)             |
|       5-7   R/W PM0/PM2 Post Modify Step    (0..7 = +0,+1,-1,+s,+2,-2,+2,-2) |
|       8-9   R/W CS0/CS2 Offset              (0..3 = +0,+1,-1,-1)             |
|       10-12 R/W RN1/RN3 Register            (0..7 = R0..R7)                  |
|       13-15 R/W RN0/RN2 Register            (0..7 = R0..R7)                  |
+------------------------------------------------------------------------------+
```


### arp0/arp1/arp2/arp3

```
+------------------------------------------------------------------------------+
|       0-2   R/W PIn     Post Modify Step I  (0..7 = +0,+1,-1,+s,+2,-2,+2,-2) |
|       3-4   R/W CIn     Offset I            (0..3 = +0,+1,-1,-1)             |
|       5-7   R/W PJn     Post Modify Step J  (0..7 = +0,+1,-1,+s,+2,-2,+2,-2) |
|       8-9   R/W CJn     Offset J            (0..3 = +0,+1,-1,-1)             |
|       10-11 R/W RIn     Register I          (0..3 = R0..R3)                  |
|       12    -   -       Unused              (always zero)                    |
|       13-14 R/W RJn     Register J          (0..3 = R4..R7)                  |
|       15    -   -       Unused              (always zero)                    |
+------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      ________________________________ Step/Modulo ________________________________ |
+------------------------------------------------------------------------------------+
```


### cfgi - Step and Mod I (for R0..R3)
### cfgj - Step and Mod J (for R4..R7)

```
+--------------------------------------------------------------------------+
|       0-6   stepi/stepj  (7bit) (see "load stepi/stepj")  ;step "Rn+s" ? |
|       7-15  modi/modj    (9bit) (see "load modi/modj")                   |
+--------------------------------------------------------------------------+
```

The modulos can be enabled in Control/Status registers. Some opcodes do also allow to disable modulos via \"dmod\" suffix.
On TL2, the above 7bit stepi/stepj can be optionally replaced by new 16bit stepi0/stepj0 registers (via flags in mod2 register).

### stepi0 ;TL2 16bit
### stepj0 ;TL2 16bit

```
+-----------------------------------------------------------------------+
|       0-16  stepi0/stepj0                                             |
+-----------------------------------------------------------------------+
```

more steps, probably for \"modr\" with \"+s0\" (stepII2D2S0)
and for STP16 and BRn?



