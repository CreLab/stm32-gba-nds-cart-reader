# DSi Teak MMIO\[8000h\] - Misc Registers (JAM/GLUE)


### MMIO\[8004h\] - JAM Unknown (R/W)

```
+-----------------------------------------------------------------------+
|       0-10  Unknown (R/W) (0..7FFh=?)                                 |
|       11-14 Unused (0)                                                |
|       15    Unknown (R/W) (0..1=?)                                    |
+-----------------------------------------------------------------------+
```

Maybe this is for the 11bit \"Host-to-Core JAM protocol\"?

### MMIO\[8006h\] - JAM Unknown/Crash, DANGER (crashes on read)
Crashes on read.

### MMIO\[8010h\] - GLUE CFG0 (R/W)
GLUE_CFG0 - Number of wait-states for Z-space transactions in predefined zones
Uh, the above name does not match up with below descriptions?

```
+-----------------------------------------------------------------------+
|       0     Timer 1 clock source (0=107MHz/Core, 1=Timer0_TOUT)       |
|       1     Timer 0 force restart upon Timer 1 output (0=No, 1=Yes)   |
|       2-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```


### MMIO\[8012h\] - GLUE Unknown 2bit (R/W)

```
+-----------------------------------------------------------------------+
|       0-1   Unknown (R/W) (0..3=?)                                    |
|       2-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```


### MMIO\[8014h\] - GLUE Unknown 16bit (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Unknown (R/W) (0..FFFFh=?)                                |
+-----------------------------------------------------------------------+
```


### MMIO\[8016h\] - GLUE Unknown, DSi=0000h or New3DS=00BAh (R)

```
+-----------------------------------------------------------------------+
|       0-15  Unknown (DSi: always 0000h, New3DS: always 00BAh)         |
+-----------------------------------------------------------------------+
```


### MMIO\[8018h\] - GLUE Whatever Parity/Shuffle (R/W)

```
+-----------------------------------------------------------------------+
|       0-3   Value A                                         (R/W)     |
|       4     All four bits in Value A XORed together         (R)       |
|       5-8   Value B                                         (R/W)     |
|       9     All four bits in Value B XORed together         (R)       |
|       10-13 Value C                                         (R/W)     |
|       14    All four bits in Value C XORed together         (R)       |
|       15    Value D                                         (R/W)     |
+-----------------------------------------------------------------------+
```

Unknown purpose, might be a randomizer/maths feature, or an interactive chip-detection feature, or something completely different, like memory-control function, or whatever.

### MMIO\[801Ah\] - GLUE Chip config ID (R)

```
+-----------------------------------------------------------------------+
|       0-15  Fixed, always C902h on DSi and New3DS                     |
+-----------------------------------------------------------------------+
```

Used for chip detect (for xpert_offsets_tbl).

### More Unknown Registers
XpertTeak was announced to support GPIO, unknown where those registers are located. Probably consist of 16bit direction and 16bit data registers (if it\'s similar as in older Oak chips). A few GPIO-style bits seem to be in st2/mod0/mod3 CPU registers.

Unknown what below is\... maybe MMIO\[8800h..8807h\] or maybe 11bit values for JAM registers at MMIO\[8004h..8006h\]\... and/or Input-only direction GPIO?

### \[dbg:800h\] - H2C Host-to-Core JAM protocol h2c_0

```
+---------------------------------------------------------------------------+
|       0     Reset                                           (0=No, 1=Yes) |
|       1     Boot                                            (0=No, 1=Yes) |
|       2     Debug                                           (0=No, 1=Yes) |
|       4     URST (user reset)                               (0=No, 1=Yes) |
|       5     -                                                             |
|       6     Internal Program (Load code to on-chip memory)  (0=No, 1=Yes) |
|       7-10  -                                                             |
+---------------------------------------------------------------------------+
```


### \[dbg:801h\] - H2C Host-to-Core JAM protocol h2c_1

```
+---------------------------------------------------------------------------+
|       0-6   -                                                             |
|       7     Continue core's clock after stopped by software (0=No, 1=Yes) |
|       8     Stop (Stop core's clock)                        (0=No, 1=Yes) |
|       9     NMI                                             (0=No, 1=Yes) |
|       10    Abort                                           (0=No, 1=Yes) |
+---------------------------------------------------------------------------+
```


### \[dbg:802h\] - H2C Host-to-Core JAM protocol h2c_2

```
+---------------------------------------------------------------------------+
|       0-10  Interrupt 0..10                                 (0=No, 1=Yes) |
+---------------------------------------------------------------------------+
```


### \[dbg:803h\] - H2C Host-to-Core JAM protocol h2c_3

```
+-----------------------------------------------------------------------------+
|       0-10  GPI (General Purpose Input) 0..10               (0=Low, 1=High) |
+-----------------------------------------------------------------------------+
```


### \[dbg:804h\] - H2C Host-to-Core JAM protocol h2c_4

```
+-----------------------------------------------------------------------------+
|       0-4   GPI (General Purpose Input) 11..15              (0=Low, 1=High) |
|       5-8   -                                                               |
|       9-10  UI (User Input) 0..1                            (0=Low, 1=High) |
+-----------------------------------------------------------------------------+
```


### \[dbg:805h\] - H2C Host-to-Core JAM protocol h2c_5

```
+----------------------------------------------------------------------------+
|       0-10  Interrupt external/internal control 0..10       (0=Ext, 1=Int) |
+----------------------------------------------------------------------------+
```


### \[dbg:806h\] - H2C Host-to-Core JAM protocol h2c_6

```
+-----------------------------------------------------------------------------------+
|       0-10  GPI Enable Control 0..10                        (0=Disable, 1=Enable) |
+-----------------------------------------------------------------------------------+
```


### \[dbg:807h\] - H2C Host-to-Core JAM protocol h2c_7

```
+-----------------------------------------------------------------------------------+
|       0-4   GPI Enable Control 11..15                       (0=Disable, 1=Enable) |
|       5-8                                                                         |
|       9-10  User Input Enable Control 0..1                  (0=Disable, 1=Enable) |
+-----------------------------------------------------------------------------------+
```




