# DSi Teak MMIO\[8180h\] - Direct Memory Access (DMA)



```
+-------------------------------------------------------------------------------------+
|      _____________________________ DMA Control/Status _____________________________ |
+-------------------------------------------------------------------------------------+
```


### MMIO\[8184h\] - DMA Channel Start Flags (0=Stop/Done, 1=Start/Busy) (R/W)
### MMIO\[8186h\] - DMA Channel Pause Flags (0=Normal, 1=Pause) (R/W)

```
+-----------------------------------------------------------------------+
|       0-7    Channel 0..7 flags                                       |
|       8-15   Unused (0)                                               |
+-----------------------------------------------------------------------+
```

Transfer start/stop should be done via \[81DEh\].bit14/15 (using RMW to change \[8184h\] directly could mess up other channels; if they finish during the RMW).
Channel 0 is automatically enabled on power up, because it is used for ARM-side data transfers via DSP_PDATA (Port 4004300h).

### MMIO\[8188h\] - DMA Channel End Flags for Size0 (R)
### MMIO\[818Ah\] - DMA Channel End Flags for Size1 (R)
### MMIO\[818Ch\] - DMA Channel End Flags for Size2 (R) (all done)

```
+-----------------------------------------------------------------------+
|       0-7    Channel 0..7 end flags (0=No, 1=End)                     |
|       8-15   Unused (0)                                               |
+-----------------------------------------------------------------------+
```

The COFF labels refer to these three registers as \"seox\", whatever that means.
The 3rd register can be used to check for transfer completion (transfer end does also clear the Start/Enable bit in MMIO\[8184h\]).

### MMIO\[818Eh\] - DMA Whatever Slot Config, bit0-15 (R/W)
### MMIO\[8190h\] - DMA Whatever Slot Config, bit16-31 (R/W)

```
+-----------------------------------------------------------------------+
|       0-2    Whatever (0..7) (initially 0 on reset)                   |
|       4-6    Whatever (0..7) (initially 1 on reset)                   |
|       8-10   Whatever (0..7) (initially 2 on reset)                   |
|       12-14  Whatever (0..7) (initially 3 on reset)                   |
|       16-18  Whatever (0..7) (initially 4 on reset)                   |
|       20-22  Whatever (0..7) (initially 5 on reset)                   |
|       24-24  Whatever (0..7) (initially 6 on reset)                   |
|       28-30  Whatever (0..7) (initially 7 on reset)                   |
|       Bit3,7,11,15,19,23,25,31 are unused (always 0)                  |
+-----------------------------------------------------------------------+
```

Reportedly \"some sort of slots for channel 0..7\" maybe priority for DMA 0..7?
transfer can hang (eg. when changing 1st word to 4444h or higher)?


```
+-------------------------------------------------------------------------------------+
|      ________________________________ DMA Channels ________________________________ |
+-------------------------------------------------------------------------------------+
```


### MMIO\[81BEh\] - DMA Select Channel (R/W)

```
+---------------------------------------------------------------------------+
|       0-2    Select the channel to be mapped to MMIO[81C0h..81Exh] (0..7) |
|       3-15   Unused (0)                                                   |
+---------------------------------------------------------------------------+
```


### MMIO\[81C0h:0..7\] - DMA Channel: Source Address, bit0-15 (R/W)
### MMIO\[81C2h:0..7\] - DMA Channel: Source Address, bit16-31 (R/W)
### MMIO\[81C4h:0..7\] - DMA Channel: Destination Address, bit0-15 (R/W)
### MMIO\[81C6h:0..7\] - DMA Channel: Destination Address, bit16-31 (R/W)

```
+-------------------------------------------------------------------------+
|       0-31   Address (within the selected memory area, see MMIO[81DAh]) |
+-------------------------------------------------------------------------+
```

Unknown how/what works exactly\...
DSP/data probably uses only lower 18bit & probably ignores X/Y/Z and MMIOBASE
DSP/code probably uses only lower 18bit & probably ignores prpage/movpd
DSP/mmio probably uses only lower 11bit & probably ignores MMIOBASE
ARM/ahbm uses full 32bit address, counted in BYTE-units (not 16bit-units)

### MMIO\[81C8h:0..7\] - DMA Channel: Size0 (inner dimension) (R/W)
### MMIO\[81CAh:0..7\] - DMA Channel: Size1 (middle dimension) (R/W)
### MMIO\[81CCh:0..7\] - DMA Channel: Size2 (outer dimension) (R/W)

```
+-----------------------------------------------------------------------+
|       0-15   Length (for each array dimension)   (0001h..FFFFh)       |
+-----------------------------------------------------------------------+
```

Trying to write size=0000h is automatically replaced by size=0001h.
Total transfer length is Size0\*Size1\*Size2 (that is always counted in 16bit units; Size0 should contain an even number when using 32bit mode).
Normal 1-dimensional transfer would use Size0=Len, Size1=Size2=1. Size1 can be useful for 2-dimensional arrays. Size2 was announced to be useful for re-ordering things like RGB values (uh, but that may require 8bit-addressing, and negative step values, or separate step-direction flags?).

### MMIO\[81CEh:0..7\] - DMA Channel: Source Step0 (R/W)
### MMIO\[81D0h:0..7\] - DMA Channel: Source Step1 (R/W)
### MMIO\[81D2h:0..7\] - DMA Channel: Source Step2 (R/W)
### MMIO\[81D4h:0..7\] - DMA Channel: Destination Step0 (R/W)
### MMIO\[81D6h:0..7\] - DMA Channel: Destination Step1 (R/W)
### MMIO\[81D8h:0..7\] - DMA Channel: Destination Step2 (R/W)

```
+--------------------------------------------------------------------------+
|       0-15   Step (... in 8bit/16bit/32bit units?) (signed or unsigned?) |
+--------------------------------------------------------------------------+
```


### MMIO\[81DAh:0..7\] - DMA Channel: Memory Area Config (R/W)

```
+------------------------------------------------------------------------------------+
|       0-3    Source Memory Area      (0..0Fh, see below)                           |
|       4-7    Destination Memory Area (0..0Fh, see below)                           |
|       8      Unknown?                (0=Normal, 1=No Irq, No end, maybe repeat?)   |
|       9      Different Memory Areas  (0=No/Slow, 1=Yes/Simultaneous Read+Write)    |
|       10     Transfer Unit size      (0=16bit/Slow, 1=32bit/Fast)                  |
|       11     Unused (0)                                                            |
|       12-13  Unknown?                (0..3=?)                                      |
|       12-15  Transfer Speed          (0=Slow, 1/2=Medium, 3=Fast) (or burst size?) |
+------------------------------------------------------------------------------------+
```

Source/Destination Memory Areas can be:

```
+---------------------------------------------------------------------------------+
|       00h DSP/Data memory                                 ;\                    
|       01h DSP/MMIO registers                              ; 16bit-address units |
|       05h DSP/Code memory (only for DST_SPACE) (untested) ;/                    |
|       07h ARM/AHBM external memory (via AHBM registers)   ;-8bit-address units  |
+---------------------------------------------------------------------------------+
```

Used values: 670h,607h,400h,250h. Reset value is F200h (and kept so for channel 0).

### MMIO\[81DCh:0..7\] - DMA Channel: Unknown, usually set to 0300h? (R/W)

```
+-----------------------------------------------------------------------+
|       0-2    Unknown (R/W)  (0..07h=?) (usually 0)                    |
|       3      Unused (0)                                               |
|       4-7    Unknown (R/W)  (0..0Fh=?) (usually 0h)                   |
|       8-9    Unknown (R/W)  (0/1/2=Hangs?, 3=Normal)                  |
|       10-12  Unknown (R/W)  (0..07h=?) (usually 0h)                   |
|       13-15  Unused (0)                                               |
+-----------------------------------------------------------------------+
```

Usually set to 0300h or 0700h (or, set to 0011h for DSP_PDATA transfer for channel 0, though that does also work with reset value 0000h).

### MMIO\[81DEh:0..7\] - DMA Channel: Start/Stop/Control (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-2   Interrupt upon Size 0..2 End (0=Disable, 1=Enable)                (R/W) |
|       3-5   Never set Size2 End flag? (0=Normal, 1=No end, maybe repeat?)     (R/W) |
|       6-7   Unknown (0..3)                                                    (R/W) |
|       8-13  Unused? (0)                                                             |
|       14-15 Start/Stop Transfer (0=No change, 1=Start, 2=Stop, 3=Same as 1)     (W) |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ______________________ DMA Unknown/Internal Registers ________________________ |
+-------------------------------------------------------------------------------------+
```


### MMIO\[8192h\] - Unknown, one register with RW-mask 7C03h (R/W)
Unknown/internal stuff. Writing 0000h, 0001h, 0002h, 0800h, 1000h, 4000h, FFFFh passes okay, however, writing 0400h or 2000h causes TRAP exception. Note: Don\'t remember how that had happened; it might have been caused indirectly by dvm data matches.

### MMIO\[81B6h..81BCh\] - Unknown, four registers with RW-mask FFFFh (R/W)
Unknown/internal stuff. The four 16bit R/W registers might be general purpose fill values (if they have no other purpose)?

### MMIO\[8180h\] - DMA Internal: Channel Size0 Busy or so? (R)
### MMIO\[8182h\] - DMA Internal: Channel Size1 Busy or so? (R)
Unknown, can contain similar busy flags as in \[8184h\], although in read-only form, and not exactly the same value (eg. bit0 tends to be zero despite of channel being enabled for DSP_PATA transfers). Maybe related to Size0/1, or maybe indicating which channel is RIGHT NOW transferring data (if so, only one bit should be seen set at a time; or maybe bits go off one after another during processing of multiple channels).

### MMIO\[8194h\] - DMA Internal: initially 0, contains SRC_ADDR_L after DMA (R)
### MMIO\[8196h\] - DMA Internal: initially 0, contains DST_ADDR_L after DMA (R)
### MMIO\[8198h..81B4h\] - Unknown, fixed 0 (R)
### MMIO\[81E0h:0..7\] - DMA Internal: initially 0, but SRC_ADDR_L(n) after DMA (R)
### MMIO\[81E2h:0..7\] - DMA Internal: initially 0, but DST_ADDR_L(n) after DMA (R)
### MMIO\[81E4h:0..7\] - DMA Internal: initially 0, but SRC_ADDR_H(n) after DMA (R)
### MMIO\[81E6h:0..7\] - DMA Internal: initially 0, but DST_ADDR_H(n) after DMA (R)
### MMIO\[81E8h..81FEh\] - Unknown, fixed 0 (R)
Unknown/internal stuff.


```
+------------------------------------------------------------------------------------+
|      _________________________________ DMA Notes _________________________________ |
+------------------------------------------------------------------------------------+
```


STEP0, STEP1 and STEP2 specify the address stepping between elements for each dimension. Below is an example showing how it works.
With the source address configuration:

```
+-----------------------------------------------------------------------+
|       SRC_ADDR = 0                                                    |
|       SIZE0 = 3                                                       |
|       SIZE1 = 5                                                       |
|       SIZE2 = 2                                                       |
|       SRC_STEP0 = 2                                                   |
|       SRC_STEP1 = 1                                                   |
|       SRC_STEP2 = 7                                                   |
+-----------------------------------------------------------------------+
```

The data transfer copies data from the following addresses:

```
+-----------------------------------------------------------------------------------+
|       <--------------------------size1-------------------------->                 |
|       <--size0--> <--size0--> <--size0--> <--size0--> <--size0-->                 |
|        0,  2,  4,  5,  7,  9, 10, 12, 14, 15, 17, 19, 20, 22, 24  <-- size2 (1st) |
|       31, 33, 35, 36, 38, 40, 41, 43, 45, 46, 48, 50, 51, 53, 55  <-- size2 (2nd) |
+-----------------------------------------------------------------------------------+
```


The 32bit double word mode also automatically aligns down the addresses to 32bit boundaries.

When the memory space is specified as 7 (AHBM), it performs data transfer from/to external ARM memory.
The external memory has 8-bit addressing. Keep in mind that the STEP value is also added to the address as-is, so STEP = 1 means stepping 8-bit for FCRAM, while stepping 16-bit for DSP memory.
There are also more alignment requirement on the external memory address, but it is handled by AHBM.



