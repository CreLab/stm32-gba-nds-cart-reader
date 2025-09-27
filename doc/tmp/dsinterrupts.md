# DS Interrupts


### 4000208h - NDS9/NDS7 - IME - Interrupt Master Enable (R/W)

```
+------------------------------------------------------------------------+
|       0     Disable all interrupts  (0=Disable All, 1=See IE register) |
|       1-31  Not used                                                   |
+------------------------------------------------------------------------+
```


### 4000210h - NDS9/NDS7 - IE - 32bit - Interrupt Enable (R/W)
### 4000214h - NDS9/NDS7 - IF - 32bit - Interrupt Request Flags (R/W)
Bits in the IE register are 0=Disable, 1=Enable.
Reading IF returns 0=No request, 1=Interrupt Request.
Writing IF acts as 0=No change, 1=Acknowledge (clears that bit).

```
+---------------------------------------------------------------------------------+
|       0     LCD V-Blank                                                         |
|       1     LCD H-Blank                                                         |
|       2     LCD V-Counter Match                                                 |
|       3     Timer 0 Overflow                                                    |
|       4     Timer 1 Overflow                                                    |
|       5     Timer 2 Overflow                                                    |
|       6     Timer 3 Overflow                                                    |
|       7     NDS7 only: SIO/RCNT/RTC (Real Time Clock)                           |
|       8     DMA 0                                                               |
|       9     DMA 1                                                               |
|       10    DMA 2                                                               |
|       11    DMA 3                                                               |
|       12    Keypad                                                              |
|       13    GBA-Slot (external IRQ source) / DSi: None such                     |
|       14    Not used                       / DSi9: NDS-Slot Card change?        |
|       15    Not used                       / DSi: dito for 2nd NDS-Slot?        |
|       16    IPC Sync                                                            |
|       17    IPC Send FIFO Empty                                                 |
|       18    IPC Recv FIFO Not Empty                                             |
|       19    NDS-Slot Game Card Data Transfer Completion                         |
|       20    NDS-Slot Game Card IREQ_MC                                          |
|       21    NDS9 only: Geometry Command FIFO                                    |
|       22    NDS7 only: Screens unfolding                                        |
|       23    NDS7 only: SPI bus                                                  |
|       24    NDS7 only: Wifi    / DSi9: XpertTeak DSP                            |
|       25    Not used           / DSi9: Camera                                   |
|       26    Not used           / DSi9: Undoc, IF.26 set on FFh-filling 40021Axh |
|       27    Not used           / DSi:  Maybe IREQ_MC for 2nd gamecard?          |
|       28    Not used           / DSi: NewDMA0                                   |
|       29    Not used           / DSi: NewDMA1                                   |
|       30    Not used           / DSi: NewDMA2                                   |
|       31    Not used           / DSi: NewDMA3                                   |
|       ?     DSi7: any further new IRQs on ARM7 side... in bit13-15,21,25-26?    |
+---------------------------------------------------------------------------------+
```

Raw TCM-only IRQs can be processed even during DMA ?
Trying to set all IE bits gives FFFFFFFFh (DSi7) or FFFFFF7Fh (DSi9).

### 4000218h - DSi7 - IE2 - DSi7 Extra Interrupt Enable Bits
### 400021Ch - DSi7 - IF2 - DSi7 Extra Interrupt Flags

```
+------------------------------------------------------------------------------------+
|       0     DSi7: GPIO18[0]   ;\                                                   
|       1     DSi7: GPIO18[1]   ; maybe 1.8V signals?                                |
|       2     DSi7: GPIO18[2]   ;/                                                   |
|       3     DSi7: Unused (0)                                                       |
|       4     DSi7: GPIO33[0] unknown (related to "GPIO330" testpoint on mainboard?) |
|       5     DSi7: GPIO33[1] Headphone connect (HP#SP) (static state)               |
|       6     DSi7: GPIO33[2] Powerbutton interrupt (short pulse upon key-down)      |
|       7     DSi7: GPIO33[3] Sound Enable Output (ie. not a useful irq-input)       |
|       8     DSi7: SD/MMC Controller   ;-Onboard eMMC and External SD Slot          |
|       9     DSi7: SD Slot Data1 pin   ;-For SDIO hardware in External SD Slot      |
|       10    DSi7: SDIO Controller     ;\Atheros Wifi Unit                          
|       11    DSi7: SDIO Data1 pin      ;/                                           |
|       12    DSi7: AES interrupt                                                    |
|       13    DSi7: I2C interrupt                                                    |
|       14    DSi7: Microphone Extended interrupt                                    |
|       15-31 DSi7: Unused (0)                                                       |
+------------------------------------------------------------------------------------+
```

Trying to set all IE2 bits gives 00007FF7h (DSi7) or 00000000h (DSi9).

### DTCM+3FFCh - NDS9 - IRQ Handler (hardcoded DTCM address)
### 380FFFCh - NDS7 - IRQ Handler (hardcoded RAM address)

```
+-----------------------------------------------------------------------+
|       Bit 0-31  Pointer to IRQ Handler                                |
+-----------------------------------------------------------------------+
```

NDS7 Handler must use ARM code, NDS9 Handler can be ARM/THUMB (Bit0=Thumb).

### DTCM+3FF8h - NDS9 - IRQ Check Bits (hardcoded DTCM address)
### 380FFF8h - NDS7 - IRQ Check Bits (hardcoded RAM address)

```
+-----------------------------------------------------------------------+
|       Bit 0-31  IRQ Flags (same format as IE/IF registers)            |
+-----------------------------------------------------------------------+
```

When processing & acknowleding interrupts via IF register, the user interrupt handler should also set the corresponding bits of the IRQ Check value (required for BIOS IntrWait and VBlankIntrWait SWI functions).

### 380FFC0h - DSi7 only - Extra IRQ Check Bits for IE2/IF2 (hardcoded RAM addr)
Same as the above 380FFF8h value, but for new IE2/IF2 registers, intended for use with IntrWait and VBlankIntrWait functions. However, that functions are BUGGED on DSi and won\'t actually work in practice (they do support only the new 380FFC0h bits, but do accidently ignore the old 380FFF8h bits).

\-\-- Below for other (non-IRQ) exceptions \-\--

### 27FFD9Ch - RAM - NDS9 Debug Stacktop / Debug Vector (0=None)
### 380FFDCh - RAM - NDS7 Debug Stacktop / Debug Vector (0=None)
These addresses contain a 32bit pointer to the Debug Handler, and, memory below of the addresses is used as Debug Stack. The debug handler is called on undefined instruction exceptions, on data/prefetch aborts (caused by the protection unit), on FIQ (possibly caused by hardware debuggers). It is also called by accidental software-jumps to the reset vector, and by unused SWI numbers within range 0..1Fh.



