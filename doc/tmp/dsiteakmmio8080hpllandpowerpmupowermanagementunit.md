# DSi Teak MMIO\[8080h\] - PLL and Power (PMU, Power Management Unit)


### MMIO\[8080h\] - PMU PLL Multiplier (R/W)

```
+----------------------------------------------------------------------------+
|       0-15  Configuration of the PLL clock multiplication (0..FFFFh=what?) |
+----------------------------------------------------------------------------+
```

Power-up: C00Eh. Unknown what that does\... multiplying clock by 16bit seems unlikely. Maybe alike CCR2 register in files peroak.per and pertklc.per?
Or maybe 0Ch and 0Eh translate to (14+1):12 ratio (ie. the 134MHz/1.25 divider; though changing this register doesn\'t seem to affect that)?

### MMIO\[8082h\] - PMU PLL Power-on config (R/W)

```
+-----------------------------------------------------------------------+
|       0     PLL power-on configuration value for PLL use (0..1=what)  |
|       1-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```

Power-up: 0001h. Unknown what that is. Default value for PLB bit in next register? Or maybe something needed for powering-up the PLL (when clearing bypass flag)?

### MMIO\[8084h\] - PMU PLL Divider/Bypass (R/W?)

```
+-----------------------------------------------------------------------------+
|       0-6   Clock Divider (0 or 1=Div1) (2..7Fh=Crashes?)                   |
|       7-14  Unused (0)                                                      |
|       15    Bypass PLL    (0=Use PLL/Crashes, 1=Bypass; works only if Div1) |
+-----------------------------------------------------------------------------+
```

Power-up: 8000h. Ie. PLL bypassed, and using 134MHz clock from DSi as is.
Unknown how to change/enable the PLL without crashing.

### MMIO\[8086h,809Ah\] - PMU Wake/Shutdown module(s) (0=Wake-up, 1=Shutdown) (R/W)
### MMIO\[8088h,809Ch\] - PMU Recover module(s) on interrupt 0 (R/W)
### MMIO\[808Ah,809Eh\] - PMU Recover module(s) on interrupt 1 (R/W)
### MMIO\[808Ch,80A0h\] - PMU Recover module(s) on interrupt 2 (R/W)
### MMIO\[808Eh,80A2h\] - PMU Recover module(s) on vectored interrupt (R/W)
### MMIO\[8090h,80A4h\] - PMU Recover module(s) on Timer 0 (except bit8) (R/W)
### MMIO\[8092h,80A6h\] - PMU Recover module(s) on Timer 1 (except bit9) (R/W)
### MMIO\[8094h,80A8h\] - PMU Recover module(s) on non-maskable interrupt (R/W)
### MMIO\[8096h\] - PMU Recover DMA module on external signal (bit1 only) (R/W)

```
+-----------------------------------------------------------------------+
|      For registers MMIO[8086h..8096h]:                                |
|       0     Core     ;aka cpu?                                        |
|       1     DMA                                                       |
|       2     SIO                                                       |
|       3     GLUE                                                      |
|       4     APBP/HPI                                                  |
|       5     AHBM                                                      |
|       6     Unused (0)                                                |
|       7     OCEM                                                      |
|       8     Timer 0                                                   |
|       9     Timer 1                                                   |
|       10    JAM                                                       |
|       11-15 Unused (0)                                                |
|      For registers MMIO[809Ah..80A8h]:                                |
|       0     BTDMP 0                                                   |
|       1     BTDMP 1                                                   |
|       2-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```

Register 8090h.bit8 and 8092h.bit9 are unused, always 0 (ie. a disabled timer cannot wakeup itself).
Register 8096h supports bit1 only (DMA), all other bits are unused, always 0.

### MMIO\[8098h\] - BM: PMU Breakpoint mask module(s) (bit1,8,9 only) (R/W)

```
+-----------------------------------------------------------------------+
|       0     Unused (0)                                                |
|       1     DMA                                                       |
|       2-7   Unused (0)                                                |
|       8     Timer 0                                                   |
|       9     Timer 1                                                   |
|       10-15 Unused (0)                                                |
+-----------------------------------------------------------------------+
```

Unknown what this does. It looks similar to the \"Recover\" registers, but, going by the description, it is \"breakpoink masking\" something instead of \"recovering\".

### MMIO\[80AAh\] - 16bit R/W ?
### MMIO\[80ACh\] - 16bit R/W ?
### MMIO\[80AEh\] - 16bit R/W ?



