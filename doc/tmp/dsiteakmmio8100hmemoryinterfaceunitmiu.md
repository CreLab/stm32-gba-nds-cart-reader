# DSi Teak MMIO\[8100h\] - Memory Interface Unit (MIU)


### MMIO\[8100h\] - MIU Waitstate Settings, bit0-15 (R/W)
### MMIO\[8102h\] - MIU Waitstate Settings, bit16-31 (R/W)

```
+------------------------------------------------------------------------------+
|       0-3    Number of wait-states for off-chip Z0 block                     |
|       4-7    Number of wait-states for off-chip Z1 block                     |
|       8-11   Number of wait-states for off-chip Z2 block                     |
|       12-15  Number of wait-states for off-chip Z3 block                     |
|       16-19  Number of wait-states for off-chip Z blocks outside Z0/Z1/Z2/Z3 |
|       20-23  Number of wait-states for off-chip X/Y memory transactions      |
|       24-27  Number of wait-states for off-chip Program-memory transactions  |
|       28-31  Unused (0)                                                      |
+------------------------------------------------------------------------------+
```

Uh, what means \"off-chip\" exactly, what kind of memory, on what \"chip\"?

### MMIO\[8104h\] - MIU Waitstate Area Z0 (R/W)
### MMIO\[8106h\] - MIU Waitstate Area Z1 (R/W)
### MMIO\[8108h\] - MIU Waitstate Area Z2 (R/W)
### MMIO\[810Ah\] - MIU Waitstate Area Z3 (R/W)

```
+-----------------------------------------------------------------------+
|       0-5    Wait-state block Start address in 1K-word units          |
|       6-11   Wait-state block End address in 1K-word units            |
|       12-15  Wait-state block Page (lower 4bit of page)               |
+-----------------------------------------------------------------------+
```


### MMIO\[810Eh\] - MIU X Page (or unused) (16bit) (R/W)
### MMIO\[8110h\] - MIU Y Page (or unused) (8bit) (R/W)
### MMIO\[8112h\] - MIU Z Page (or \"absolute\" page) (16bit) (R/W)
The X/Z pages are 16bit wide:

```
+-----------------------------------------------------------------------+
|       0-15   Memory Page (...base or so, in WHAT-units?)              |
+-----------------------------------------------------------------------+
```

The Y page is only 8bit wide:

```
+-----------------------------------------------------------------------+
|       0-7    Memory Page (...base or so, in WHAT-units?)              |
|       8-15   Unused (0)                                               |
+-----------------------------------------------------------------------+
```

The register meaning depends on the PGM paging mode:

```
+-----------------------------------------------------------------------+
|       When PGM=0 --> MMIO[8112h] is the "absolute" data memory page   |
|       When PGM=1 --> MMIO[810Eh/8110h/8112h] are the X/Y/Z pages      |
+-----------------------------------------------------------------------+
```


### MMIO\[8114h\] - MIU X/Y Page Size for Page 0 (or all pages) (R/W)
### MMIO\[8116h\] - MIU X/Y Page Size for Page 1 (or unused) (R/W)
### MMIO\[8118h\] - MIU X/Y Page Size for Off-chip Pages (or unused) (R/W)

```
+-----------------------------------------------------------------------+
|       0-5    X memory size (0..3Fh)                                   |
|       6-7    Unused (0)                                               |
|       8-14   Y memory size (1..40h)                                   |
|       15     Unused (0)                                               |
+-----------------------------------------------------------------------+
```

The register meaning depends on the PGM paging mode:

```
+-------------------------------------------------------------------------------------+
|       When PGM=0?--> MMIO[8114h,8116h,8118h] used for Page 0, 1, and Off-chip pages |
|       When PGM=1?--> MMIO[8114h] used for all pages                                 |
+-------------------------------------------------------------------------------------+
```

For Y memory size, the hardware does automatically replace the written value by min=01h or max=40h when trying to to write 00h or 41h-7Fh.

### MMIO\[811Ah\] - MIU Config for Misc stuff (R/W)

```
+------------------------------------------------------------------------------------+
|       0      Program protection mechanism, uh, what is that? (0=Disable, 1=Enable) |
|       1      Program page for entire program space (from Test pin) (1=offchip)     |
|       2      Program page for breakpoint handler (0=Page1/offchip, 1=Page0/onchip) |
|       3      Unknown (R/W)  (0..1=?)                                               |
|       4      Core/DMA data use only Z-even address bus (single? PGM=0?) (1=Enable) |
|       5      Unknown (R/W)  (0..1=?)                                               |
|       6      Paging mode (PGM) (for X/Y/Z pages)  (0=Normal, 1=DANGER)             |
|       7-15   Unused (0)                                                            |
+------------------------------------------------------------------------------------+
```

Power-on default is 0014h. Bit1-2 are read-only (always bit1=0, bit2=1).

### MMIO\[811Ch\] - MIU Config for Program Page and Download Memory (R/W)

```
+----------------------------------------------------------------------------------+
|       0      Select Z-space data memory (0=Regular Memory, 1=Download memory)    |
|       1      Download mem is/was selected (bit1 can be cleared during Trap only) |
|       2-5    Alternative Program Page for movd/movp opcodes (PDLPAGE) (4bit)     |
|       6      Select program page for movd/movp (0=2bit/movpd, 1=4bit/PDLPAGE)    |
|       7-15   Unused (0)                                                          |
+----------------------------------------------------------------------------------+
```

Bit1 gets set when setting bit0=1 (bit1 is usually readonly, except, trap handler may clear bit1 by writing to it). Unknown what Download means, maybe off-chip data memory?

### MMIO\[811Eh\] - MIU Base Address for MMIO Registers (R/W)

```
+-----------------------------------------------------------------------+
|       0-9    Unused (0)                                               |
|       10-15  MMIO Base Address (in 400h-word units)                   |
+-----------------------------------------------------------------------+
```

Power-on default is 8000h, ie. mapping MMIO\[8000h..87FFh\] to 8000h..87FFh.

### MMIO\[8120h\] - MIU Observability Mode (R/W)

```
+-----------------------------------------------------------------------+
|       0      Observability Enable (0=Disable, 1=Enable)               |
|       1-3    Observability Mode   (0..4=Mode, see below)              |
|       4-15   Unused (0)                                               |
+-----------------------------------------------------------------------+
```

Observability modes (defines which Core/DMA address/data buses are reflected on the off-chip XZ buses):

```
+-----------------------------------------------------------------------+
|       00h: Core XZ address/data buses                                 |
|       01h: Core Y address/data buses                                  |
|       02h: Core P address/data buses                                  |
|       03h: DMA DST address/data buses                                 |
|       04h: DMA SRC address/data buses                                 |
+-----------------------------------------------------------------------+
```


### MMIO\[8122h\] - MIU Pin Config? (R/W)

```
+-----------------------------------------------------------------------+
|       0     Z Read Polarity Bit   - for DRZON/DRZEN                   |
|       1     Z Write Polarity Bit  - for DWZON/DWZEN                   |
|       2     Z Strobe Polarity Bit - for ZSTRB                         |
|       3     X Strobe Polarity Bit - for XSTRB                         |
|       4     X Select Polarity Bit - for XS                            |
|       5     Z Select Polarity Bit - for ZS                            |
|       6     Signal Polarity Bit   - for RD_WR                         |
|       7-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```




