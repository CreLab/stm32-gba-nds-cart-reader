# DSi Teak MMIO\[80E0h\] - AHBM - Advanced High Performance Bus Master


AHBM does allow the Teak CPU to access the ARM-side memory (in combination with DMA interface at MMIO\[8180h\]).

### Supported ARM-side memory areas
DSi allows to access most of the ARM9 address space:

```
+------------------------------------------------------------------------------------+
|       02000000h/Main RAM     --> works                                             |
|       03000000h/Shared RAM   --> works (maybe also New Shared RAM, if any mapped?) |
|       04000000h/ARM9 I/O     --> works                                             |
|       05000000h/Palette      --> works                                             |
|       06000000h/VRAM         --> works                                             |
|       07000000h/OAM          --> works                                             |
|       08000000h/GBA SLOT ROM --> works (with dummy FFFFFFFFh values)               |
|       0A000000h/GBA SLOT RAM --> works (with dummy FFFFFFFFh values)               |
|       FFFF0000h/ARM9 BIOS    --> works (lower 32K only, upper 32K is zerofilled)   |
|       DTCM/ITCM              --> probably ignored?                                 |
|       Any other              --> returns zero (but without MMIO[80E0h] error flag) |
+------------------------------------------------------------------------------------+
```

3DS in 3DS mode is more restrictive:

```
+----------------------------------------------------------------------------------+
|       20000000h/FCRAM        --> works                                           |
|       1FF80000h/AXI          --> works                                           |
|       1FF40000h/DSP/DATA     --> oddly mirrors to 1FF80000h/AXI                  |
|       Any other              --> rejected (and sets MMIO[80E0h].bit4 error flag) |
+----------------------------------------------------------------------------------+
```


### MMIO\[80E0h\] - AHBM Status (R)

```
+------------------------------------------------------------------------------+
|       0-1   Usually/always 0 ?                                               |
|       2     Burst queue not empty  (0=Empty, 1=Not-empty)                    |
|       3     Usually/always 0 ?                                               |
|       4     Busy/stuck/error?  (0=Normal, 1=Invalid ARM address)  ;3DS only? |
|       5-15  Usually/always 0 ?                                               |
+------------------------------------------------------------------------------+
```

\"Applications wait for all bits to be 0 before connecting AHBM to DMA.\"

### MMIO\[80E2h+(0..2)\*6\] - AHBM Channel 0..2 Configure Burst/Data (R/W)

```
+-----------------------------------------------------------------------+
|       0     Applications set this to 1 if BURST is non-zero, uh?      |
|       1-2   Burst type     (0=x1, 1=x4, 2=x8, 3=?)                    |
|       3     Unknown (R/W)  (0=Normal, 1=Dunno/NoTransfer?)            |
|       4-5   Data type      (0=8bit, 1=16bit, 2=32bit, 3=?)            |
|       6     Unused (0)                                                |
|       7     Unknown (R/W)  (0=Normal, 1=Dunno/TransferHangs/crashes?) |
|       8-11  Unknown (R/W)  (0..Fh=?) (usually 0)                      |
|       12-15 Unused (0)                                                |
+-----------------------------------------------------------------------+
```

Used values: 0010h=?,0020h=?,0025h=dma?

### MMIO\[80E4h+(0..2)\*6\] - AHBM Channel 0..2 Configure Whatever (R/W)

```
+----------------------------------------------------------------------------------+
|       0-7   Unknown (R/W)      (0..FFh=?) (usually 0)                            |
|       8     Transfer direction (0=Read external memory, 1=Write external memory) |
|       9     Applications always set this (usually 1=set) (but also works when 0) |
|       10-15 Unused (0)                                                           |
+----------------------------------------------------------------------------------+
```

Used values: 0200h=read, 0300h=write

### MMIO\[80E6h+(0..2)\*6\] - AHBM Channel 0..2 Configure DMA (R/W)

```
+-----------------------------------------------------------------------+
|       0-7   Connect to DMA channel 0..7   (0=No, 1=Connect)           |
|       8-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```

Used values: bit0-7=dma0..7, 0000h=All off.

### MMIO\[80F4h\] - Unknown 6bit? bit10-15 are used (R/W)
### MMIO\[80F6h\] - AHBM Internal FIFO (R) and maybe also (W?)
### MMIO\[80F8h\] - Unknown always zero? (R?)
### MMIO\[80FAh\] - Read/write-able(!) mirror of MMIO\[80FCh\] (R/W)
### MMIO\[80FCh\] - Unknown 16bit? (R/W)
### MMIO\[80FEh\] - Unknown 16bit? (R/W)
Unknown registers, normally left unused. The FIFO register seems to contain the most recent 8x16bit values that were transferred via AHBM. Unknown if that FIFO (and whatever address setting) could be used for manual (non-DMA) AHBM transfers.



