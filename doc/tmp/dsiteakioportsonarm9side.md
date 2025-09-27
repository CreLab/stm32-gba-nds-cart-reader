# DSi Teak I/O Ports (on ARM9 Side)


### 4004300h - DSi9 - DSP_PDATA - DSP Transfer Data Read FIFO (R)

```
+-----------------------------------------------------------------------+
|       0-15  Data (one stage of the 16-stage Read FIFO)                |
+-----------------------------------------------------------------------+
```


### 4004300h - DSi9 - DSP_PDATA - DSP Transfer Data Write FIFO (W)

```
+-----------------------------------------------------------------------+
|       0-15  Data (one stage of the 16-stage Write FIFO)               |
+-----------------------------------------------------------------------+
```


### 4004304h - DSi9 - DSP_PADR - DSP Transfer Address (W)

```
+-----------------------------------------------------------------------+
|       0-15  Lower 16bit of Address in DSP Memory (in 16bit units)     |
+-----------------------------------------------------------------------+
```

For MMIO, only lower 10bit are used (ie. MMIO\[8000h-87FFh\] can be accessed via 8000h-87FFh or 0000h-07FFh or other mirrors).
For Data, the 16bit address allows to access 64K-words.
For Code, the 16bit address allows to access 64K-words, but Code works only in write-direction?
For Data/Code, the upper 16bit of Address must be configured on DSP side, in DMA channel 0 registers:

```
+--------------------------------------------------------------------------------+
|       MMIO[81BEh]   - DMA Select Channel (must be 0 for below DMA 0 regisrers) |
|       MMIO[81C2h:0] - DMA Channel 0: Source Address, bit16-31 (R/W)            |
|       MMIO[81C6h:0] - DMA Channel 0: Destination Address, bit16-31 (R/W)       |
+--------------------------------------------------------------------------------+
```

The Auto-increment flag in DSP_PCFG.bit1 will increment the 16bit address after each DSP_PDATA unit (but doesn\'t seem to increment the upper bits after address xxFFFFh).

### 4004308h - DSi9 - DSP_PCFG - DSP Configuration (R/W)

```
+----------------------------------------------------------------------------------+
|       0     DSP Reset (0=Release, 1=Reset) ;should be held "1" for 8 DSP clks    |
|       1     DSP Transfer Address Auto-Increment  (0=Off, 1=On)                   |
|       2-3   DSP Read Data Length (0=1 word, 1=8 words, 2=16 words, 3=FreeRun)    |
|       4     DSP Read Start Flag (mem transfer via Read FIFO) (1=Start)           |
|       5     Interrupt Enable Read FIFO Full      (0=Off, 1=On)                   |
|       6     Interrupt Enable Read FIFO Not-Empty (0=Off, 1=On)                   |
|       7     Interrupt Enable Write FIFO Full     (0=Off, 1=On)                   |
|       8     Interrupt Enable Write FIFO Empty    (0=Off, 1=On)                   |
|       9     Interrupt Enable Reply Register 0    (0=Off, 1=On)                   |
|       10    Interrupt Enable Reply Register 1    (0=Off, 1=On)                   |
|       11    Interrupt Enable Reply Register 2    (0=Off, 1=On)                   |
|       12-15 DSP Memory Transfer (0=DSP/Data, 1=DSP/MMIO, 5=DSP/Code, 7=ARM/AHBM) |
+----------------------------------------------------------------------------------+
```


### 400430Ch - DSi9 - DSP_PSTS - DSP Status (R)

```
+-------------------------------------------------------------------------------+
|       0     Read Transfer Underway Flag    (0=No, 1=Yes/From DSP Memory)      |
|       1     Write Transfer Underway Flag   (0=No, 1=Yes/To DSP Memory)        |
|       2     Peripheral Reset Flag          (0=No/Ready, 1=Reset/Busy)         |
|       3-4   Unused (0)                                                        |
|       5     Read FIFO Full Flag            (0=No, 1=Yes/Full)                 |
|       6     Read FIFO Not-Empty Flag       (0=No, 1=Yes, ARM9 may read PDATA) |
|       7     Write FIFO Full Flag           (0=No, 1=Yes/Full)                 |
|       8     Write FIFO Empty Flag          (0=No, 1=Yes/Empty)                |
|       9     Semaphore IRQ Flag             (0=None, 1=IRQ)                    |
|       10    Reply Register 0 Update Flag   (0=Was Written by DSP, 1=No)       |
|       11    Reply Register 1 Update Flag   (0=Was Written by DSP, 1=No)       |
|       12    Reply Register 2 Update Flag   (0=Was Written by DSP, 1=No)       |
|       13    Command Register 0 Read Flag   (0=Was Read by DSP, 1=No)          |
|       14    Command Register 1 Read Flag   (0=Was Read by DSP, 1=No)          |
|       15    Command Register 2 Read Flag   (0=Was Read by DSP, 1=No)          |
+-------------------------------------------------------------------------------+
```

Unknown if/when bit10-15 get reset\... maybe after reading the status\... or when reading a reply or writing a new command?

### 4004310h - DSi9 - DSP_PSEM - ARM9-to-DSP Semaphore (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  ARM9-to-DSP Semaphore 0..15 Flags (0=Off, 1=On)           |
+-----------------------------------------------------------------------+
```

Reportedly these flags are sent in ARM9-to-DSP direction (=seems correct).
Confusingly, the other DSP_Pxxx registers are for opposite direction?

### 4004314h - DSi9 - DSP_PMASK - DSP-to-ARM9 Semaphore Mask (R/W)

```
+---------------------------------------------------------------------------------+
|       0-15  DSP-to-ARM9 Semaphore 0..15 Interrupt Disable (0=Enable, 1=Disable) |
+---------------------------------------------------------------------------------+
```


### 4004318h - DSi9 - DSP_PCLEAR - DSP-to-ARM9 Semaphore Clear (W)

```
+--------------------------------------------------------------------------+
|       0-15  DSP-to-ARM9 Semaphore 0..15 Clear (0=No Change, 1=Clear/Ack) |
+--------------------------------------------------------------------------+
```

Reportedly clears bits in DSP_PSEM/4004310h. \[that\'s probably nonsense, clearing bits in DSP_SEM/400431Ch would make more sense?\]

### 400431Ch - DSi9 - DSP_SEM - DSP-to-ARM9 Semaphore Data (R)

```
+-----------------------------------------------------------------------+
|       0-15  DSP-to-ARM9 Semaphore 0..15 Flags (0=Off, 1=On)           |
+-----------------------------------------------------------------------+
```

Reportedly these flags are received in DSP-to-ARM9 direction.

### 4004320h - DSi9 - DSP_CMD0 - DSP Command Register 0 (R/W) (ARM9 to DSP)
### 4004328h - DSi9 - DSP_CMD1 - DSP Command Register 1 (R/W) (ARM9 to DSP)
### 4004330h - DSi9 - DSP_CMD2 - DSP Command Register 2 (R/W) (ARM9 to DSP)

```
+-----------------------------------------------------------------------+
|       0-15  Command/Data to DSP                                       |
+-----------------------------------------------------------------------+
```


### 4004324h - DSi9 - DSP_REP0 - DSP Reply Register 0 (R) (DSP to ARM9)
### 400432Ch - DSi9 - DSP_REP1 - DSP Reply Register 1 (R) (DSP to ARM9)
### 4004334h - DSi9 - DSP_REP2 - DSP Reply Register 2 (R) (DSP to ARM9)

```
+-----------------------------------------------------------------------+
|       0-15  Reply/Data from DSP                                       |
+-----------------------------------------------------------------------+
```


### Further Teak related registers
SCFG_CLK, SCFG_RST, SCFG_EXT registers, MBK registers, and SNDEXCNT register.
- [DSi Control Registers (SCFG)](./dsicontrolregistersscfg.md)
- [DSi New Shared WRAM (for ARM7, ARM9, DSP)](./dsinewsharedwramforarm7arm9dsp.md)
- [DSi Microphone and SoundExt](./dsimicrophoneandsoundext.md)
And, for the final audio output and microphone input,
- [DSi Touchscreen/Sound Controller](./dsitouchscreensoundcontroller.md)



