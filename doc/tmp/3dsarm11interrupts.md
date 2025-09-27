# 3DS ARM11 Interrupts


### Private Software Interrupts (can be different for each CPU)

```
+-------------------------------------------------------------------------------------+
|       IRQ    Listener      Description                                              |
|       00h                  MPCore software IRQ, not configured                      |
|       01h                  MPCore software IRQ, used by BOOT11 to kickstart Core1   |
|       02h-03h              MPCore software IRQ, seem to be unused                   |
|       04h    Kernel        MPCore software IRQ, used to manage performance counter  |
|       05h    Kernel        MPCore software IRQ, does apparently nothing             |
|       06h    Kernel        MPCore software IRQ, extensively used by                 |
|                              KernelSetState (and contains most of the actual        |
|                              code of the latter)                                    |
|       07h    Kernel        MPCore software IRQ, see KCacheMaintenanceInterruptEvent |
|       08h    Kernel        MPCore software IRQ, used for scheduling                 |
|       09h    Kernel        MPCore software IRQ, used when handling                  |
|                              exceptions that require termination of a thread or     |
|                              a process, and in some cases by                        |
|                              svcSetDebugThreadContext, to store VFP registers       |
|                              in the thread's register storage.                      |
|       0Ah    Kernel        TLB operations IRQ, see KTLBOperationsInterruptEvent     |
|       0Bh-0Eh              MPCore software IRQ, not configured                      |
|       0Fh    dmnt/debugger MPCore software IRQ, used to abstract FIQ (debug),       |
|                              this interrupt is never sent to New3DS core2/core3     |
+-------------------------------------------------------------------------------------+
```


### Private Timer Interrupts (has separate timers for each CPU)

```
+-----------------------------------------------------------------------------------+
|       10h-1Ch              Hmmmm, these do NOT EXIST (?) in interrupt controller? |
|       1Dh    Kernel        MPCore Timer0 (Port 17E00600h)                         |
|       1Eh    Kernel        MPCore Timer1 (Port 17E00620h) (3DS used on "core 1")  |
|       1Fh                  MPCore Legacy "nIRQ" pin (is that used in 3DS?)        |
+-----------------------------------------------------------------------------------+
```


### Hardware Interrupts (can be used for all CPUs that are selected as Target)

```
+-------------------------------------------------------------------------------------+
|       20h     -           Unused?                                     ;\maybe       
|       21h     -           Unused? But [17E01D00h].bit33 is set        ; related to  |
|       22h     -           Unused?                                     ; first two   |
|       23h     -           Unused? But [17E01D00h].bit35 is set        ;/CPU cores?  |
|       24h     spi?        SPI_BUS2 (unused)                    (Port 10143000h)     |
|       25h-27h -           Unused?                                                   |
|       28h     gsp, TwlBg  PSC0 (GPU_MEMFILL 0)                 (Port 10400010h)     |
|       29h     gsp, TwlBg  PSC1 (GPU_MEMFILL 1)                 (Port 10400020h)     |
|       2Ah     gsp, TwlBg  PDC0 (GPU H/V-IRQ for top screen)    (Port 10400400h)     |
|       2Bh     gsp, TwlBg  PDC1 (GPU H/V-IRQ for bottom screen) (Port 10400500h)     |
|       2Ch     gsp, TwlBg  PPF  (GPU_MEMCOPY)                   (Port 10400C00h)     |
|       2Dh     gsp, TwlBg  P3D  (GPUREG_IRQ_CMP/REQ)            (Port 10401040h)     |
|       2Eh-2Fh -           Unused?                                                   |
|       30h-38h Kernel      Old CDMA Event 0..8 (nine events with separate IRQs)      |
|       39h     Kernel      Old CDMA Faulting (eg. CCR=0, or event>15)                |
|       3Ah     Kernel      New CDMA Event 0..31 (32 events sharing one IRQ) ;\New3DS 
|       3Bh     Kernel      New CDMA Faulting (eg. CCR=0)                    ;/       |
|       3Ch     -           Unused?                                     ;\maybe alike 
|       3Dh     -           Unused? But New3DS [17E01D00h].bit61 is set ; IRQ 20h-23h |
|       3Eh     -           Unused?                                     ; for extra   |
|       3Fh     -           Unused? But New3DS [17E01D00h].bit63 is set ;/CPU cores?  |
|       40h     nwm         WIFI SDIO Controller            (Port 10122000h)          |
|       41h     nwm         WIFI SDIO IRQ Pin                                         |
|       42h     nwm_dev?    Alternate SD/MMC Slot controller (Port 10100000h?)        |
|       43h     -           Unused? Or maybe Card IRQ Pin for above?                  |
|       44h     -           NTRCARD                         (Port 10164000h)          |
|       45h     mvd         L2B_0 (First RGB-to-RGBA Converter)  (10130000h) ;\New3DS 
|       46h     mvd         L2B_1 (Second RGB-to-RGBA Converter) (10131000h) ;/       |
|       47h     -           Unused?                                                   |
|       48h     camera      Camera Bus 0 (DSi cameras)      (Port 10120000h)          |
|       49h     camera      Camera Bus 1 (left-eye)         (Port 10121000h)          |
|       4Ah     dsp         ...probably Teak DSP... ?      (maybe 10203000h)          |
|       4Bh     camera      Y2R_0 (First YUV-to-RGBA Converter)  (10102000h)          |
|       4Ch     TwlBg       LGYFB_0 Legacy GBA/NDS Video    (Port 10110000h)          |
|       4Dh     TwlBg       LGYFB_1 Legacy GBA/NDS Video    (Port 10111000h)          |
|       4Eh     mvd         Y2R_1 (Second YUV-to-RGBA Converter) (10132000h) ;\New3DS 
|       4Fh     mvd         MVD Registers                   (Port 10207000h) ;/       |
|       50h     pxi, TwlBg  PXI_SYNC.bit29 from ARM9 (commonly used)                  |
|       51h     pxi, TwlBg  PXI_SYNC.bit30 from ARM9 (rarely used)                    |
|       52h     pxi, TwlBg  PXI Send Fifo Empty                                       |
|       53h     pxi, TwlBg  PXI Receive Fifo Not Empty                                |
|       54h     i2c, TwlBg  I2C_BUS0 (DSi devices)          (Port 10161000h)          |
|       55h     i2c, TwlBg  I2C_BUS1 (3DS devices)          (Port 10144000h)          |
|       56h     spi, TwlBg  SPI_BUS0 (Pwrman,WifiFlash,Tsc) (Port 10160000h)          |
|       57h     spi, TwlBg  SPI_BUS1 (Tsc)                  (Port 10142000h)          |
|       58h     Kernel      CFG11_MPCORE_CLKCNT (clk change)(Port 10141300h) ;-New3DS |
|       59h     TwlBg       CFG11_TWLMODE_SLEEP             (Port 10141104h)          |
|       5Ah     mic         Microphone maybe?              (maybe 10162000h)          |
|       5Bh     -           HID PAD Controller Buttons      (Port 10146000h)          |
|       5Ch     i2c, TwlBg  I2C_BUS2 (3DS extra gimmicks)   (Port 10148000h)          |
|       5Dh-5Eh -           Unused?                                                   |
|       5Fh     -           NDS-Wifi Registers (aka MP)     (Port 10170000h)          |
|       60h     gpio, TwlBg GPIO_DATA0.bit2=0  Shell opened (GPIO falling edge)       |
|       61h     -           Unused?                                                   |
|       62h     gpio, TwlBg GPIO_DATA0.bit2=1  Shell closed (GPIO rising edge)        |
|       63h     gpio, TwlBg GPIO_DATA0.bit1    Touchscreen Pen Down (if enabled)      |
|       64h     gpio, TwlBg GPIO_DATA1.bit0    Headphone jack plugged in/out          |
|       65h     -           Unused?                                                   |
|       66h     gpio, TwlBg GPIO_DATA1.bit1    ?                                      |
|       67h     -           Unused?                                                   |
|       68h     gpio, TwlBg GPIO_DATA3.bit0    C-stick Interrupt (New3DS)             |
|       69h     gpio, TwlBg GPIO_DATA3.bit1    IrDA Interrupt                         |
|       6Ah     gpio, TwlBg GPIO_DATA3.bit2    Gyro Interrupt                         |
|       6Bh     gpio, TwlBg GPIO_DATA3.bit3    ?                                      |
|       6Ch     gpio, TwlBg GPIO_DATA3.bit4    IrDA TX-RC (manual out)                |
|       6Dh     gpio, TwlBg GPIO_DATA3.bit5    IrDA RXD   (manual in)                 |
|       6Eh     gpio, TwlBg GPIO_DATA3.bit6    ?                                      |
|       6Fh     gpio, TwlBg GPIO_DATA3.bit7    ?                                      |
|       70h     gpio, TwlBg GPIO_DATA3.bit8    TSC[67h:2Bh] (Headphone connect)       |
|       71h     gpio, TwlBg GPIO_DATA3.bit9    MCU Interrupt (MCU[10h-1Fh])           |
|       72h     gpio, TwlBg GPIO_DATA3.bit10   NFC Interrupt (New3DS)                 |
|       73h     TwlBg       GPIO_DATA3.bit11   ??                                     |
|       74h     ?           CGC Gamecard power off     (CFG9_CARD_PWROFF_DELAY)       |
|       75h     ?           CGC Gamecard insert switch (CFG9_CARD_INSERT_DELAY)       |
|       76h     -           L2C Level 2 Cache Controller    (Port 17E10000h)   New3DS |
|       77h     -           Unused?                                                   |
|       78h     Kernel      CPU0 cp15 Performance monitor count (any) overflow        |
|       79h     Kernel      CPU1 cp15 Performance monitor count (any) overflow        |
|       7Ah     Kernel      CPU2 cp15 Performance monitor count (any) overflow New3DS |
|       7Bh     Kernel      CPU3 cp15 Performance monitor count (any) overflow New3DS |
|       7Ch-7Fh -           Unused?                                                   |
|       80h-3FEh            Don't exist (3DS/New3DS has only 80h IRQ sources)         |
|       3FFh                None, no interrupt (or spurious interrupt)                |
+-------------------------------------------------------------------------------------+
```

The spurious interrupt (3FFh) might appear in an interrupt handler if the handler got triggered, but something (eg. another CPU) has cleared the IRQ flag before the handler got a chance to process it.



