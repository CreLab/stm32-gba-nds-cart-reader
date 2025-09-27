# DSi Teak MMIO\[80C0h\] - Host Port Interface (APBP aka HPI)


The APBP (aka HPI Host Port Interface) registers are used to communicate between ARM and DSP.

### MMIO\[80C0h/80C4h/80C8h\] - APBP DSP-to-ARM Reply 0/1/2 (R/W)
### MMIO\[80C2h/80C6h/80CAh\] - APBP ARM-to-DSP Command 0/1/2 (R)

```
+-----------------------------------------------------------------------+
|       0-15   Command/Reply Data                                       |
+-----------------------------------------------------------------------+
```


### MMIO\[80CCh\] - APBP DSP-to-ARM Semaphore Set Flags (0=Clear, 1=Set) (R/W)
### MMIO\[80CEh\] - APBP ARM-to-DSP Semaphore Interrupt Mask (?=On/Off) (R/W)
### MMIO\[80D0h\] - APBP ARM-to-DSP Semaphore Ack Flags (0=No change, 1=Clear) (W?)
### MMIO\[80D2h\] - APBP ARM-to-DSP Semaphore Get Flags (R)

```
+-----------------------------------------------------------------------+
|       0-15   Semaphore Flag 0..15                                     |
+-----------------------------------------------------------------------+
```


### MMIO\[80D4h\] - APBP Control (R/W)

```
+---------------------------------------------------------------------------+
|       0-1    Unused (0)                                                   |
|       2      ARM-side register endianness (0=Normal, 1=Big-Endian/DANGER) |
|       3-7    Unused (0)                                                   |
|       8      Interrupt when CMD0 is written by ARM (0=Enable, 1=Disable)  |
|       9-11   Unused (0)                                                   |
|       12     Interrupt when CMD1 is written by ARM (0=Enable, 1=Disable)  |
|       13     Interrupt when CMD2 is written by ARM (0=Enable, 1=Disable)  |
|       14-15  Unused (0)                                                   |
+---------------------------------------------------------------------------+
```


### MMIO\[80D6h\] - APBP DSP-side Status (R)

```
+-------------------------------------------------------------------------------+
|       0-4    Unused? (usually 0)                                              |
|       5      Reply Register 0 Read Flag     (0=Was Read by ARM?, 1=No)        |
|       6      Reply Register 1 Read Flag     (0=Was Read by ARM?, 1=No)        |
|       7      Reply Register 2 Read Flag     (0=Was Read by ARM?, 1=No)        |
|       8      Command Register 0 Update Flag (0=Was Written by ARM?, 1=No)     |
|       9      Semaphore IRQ Flag             (0=No, 1=[80D2h] AND NOT [80CEh]) |
|       10-11  Unused? (usually 0)                                              |
|       12     Command Register 1 Update Flag (0=Was Written by ARM?, 1=No)     |
|       13     Command Register 2 Update Flag (0=Was Written by ARM?, 1=No)     |
|       14-15  Unused? (usually 0)                                              |
+-------------------------------------------------------------------------------+
```


### MMIO\[80D8h\] - APBP ARM-side Status (mirror of ARM9 Port 400430Ch) (R)

```
+--------------------------------------------------------------------------------+
|       0      Read Transfer Underway Flag    (0=No, 1=Yes/From DSP Memory)      |
|       1      Write Transfer Underway Flag   (0=No, 1=Yes/To DSP Memory)        |
|       2      Peripheral Reset Flag          (0=No/Ready, 1=Reset/Busy)         |
|       3-4    Unused (0)                                                        |
|       5      Read FIFO Full Flag            (0=No, 1=Yes/Full)                 |
|       6      Read FIFO Not-Empty Flag       (0=No, 1=Yes, ARM9 may read PDATA) |
|       7      Write FIFO Full Flag           (0=No, 1=Yes/Full)                 |
|       8      Write FIFO Empty Flag          (0=No, 1=Yes/Empty)                |
|       9      Semaphore IRQ Flag             (0=None, 1=IRQ)                    |
|       10     Reply Register 0 Update Flag   (0=Was Written by DSP, 1=No)       |
|       11     Reply Register 1 Update Flag   (0=Was Written by DSP, 1=No)       |
|       12     Reply Register 2 Update Flag   (0=Was Written by DSP, 1=No)       |
|       13     Command Register 0 Read Flag   (0=Was Read by DSP, 1=No)          |
|       14     Command Register 1 Read Flag   (0=Was Read by DSP, 1=No)          |
|       15     Command Register 2 Read Flag   (0=Was Read by DSP, 1=No)          |
+--------------------------------------------------------------------------------+
```




