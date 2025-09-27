# DSi Teak MMIO\[8200h\] - Interrupt Control Unit (ICU)


### MMIO\[8200h\] - ICU Interrupt Pending Flags (0=No, 1=IRQ Pending) (R)
### MMIO\[8202h\] - ICU Interrupt Acknowledge (0=No change, 1=Set) (W)
### MMIO\[8204h\] - ICU Interrupt Manual Trigger (0=Release, 1=Set) (R/W)
### MMIO\[8206h\] - ICU Enable Interrupt routing to core interrupt 0 (R/W)
### MMIO\[8208h\] - ICU Enable Interrupt routing to core interrupt 1 (R/W)
### MMIO\[820Ah\] - ICU Enable Interrupt routing to core interrupt 2 (R/W)
### MMIO\[820Ch\] - ICU Enable Interrupt routing to vectored interrupt (R/W)
### MMIO\[820Eh\] - ICU Interrupt Trigger mode (0=Level, 1=Edge) (R/W)
### MMIO\[8210h\] - ICU Interrupt Polarity (0=Normal, 1=Invert) (R/W)

```
+------------------------------------------------------------------------------------+
|       0-8   No hardware IRQs (but can be used as Software IRQs via Manual Trigger) |
|       9     Timer 1                                                                |
|       10    Timer 0                                                                |
|       11    BTDMP 0                                                                |
|       12    BTDMP 1                                                                |
|       13    SIO                                                                    |
|       14    APBP                                                                   |
|       15    DMA                                                                    |
+------------------------------------------------------------------------------------+
```


### MMIO\[8212h+(0..15)\*4\] - ICU Vectored Interrupt 0..15 Address, bit16-31 (R/W)
### MMIO\[8214h+(0..15)\*4\] - ICU Vectored Interrupt 0..15 Address, bit0-15 (R/W)

```
+------------------------------------------------------------------------------+
|       0-17  Address of interrupt handler for vectored interrupt 0..15        |
|       18-30 Unused (0)                                                       |
|       31    Context switch on vectored interrupt 0..15 (0=Disable, 1=Enable) |
+------------------------------------------------------------------------------+
```

Observe that upper/lower 16bit are arranged in BIG-ENDIAN style (unlike other registers with lower/upper 16bit).
Default values on reset are 0003FC00h.
Interrupt vector address for Interrupt 0..15, when using \"vectored interrupt\".
The core interrupts and NMI have fixed vector addresses.

### MMIO\[8252h\] - ICU Interrupt Master Disable (0=Normal, 1=Off/undoc) (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-15  Master Disable for interrupt 0..15 (0=Normal, 1=Off, don't set pending) |
+-------------------------------------------------------------------------------------+
```


### MMIO\[8254h\] - Unknown, R/W mask 5555h (R/W)
### MMIO\[8256h\] - Unknown, R/W mask 5555h (R/W)
Unknown.

### Interrupt related CPU registers
- [DSi Teak CPU Control/Status Registers](./dsiteakcpucontrolstatusregisters.md)

### teak exception vectors

```
+----------------------------------------------------------------------------------+
|       code:00000h    start (from reset or timer watchdog)                        |
|       code:00002h    trap_handler (trap/break) (from OCEM or Timers)             |
|       code:00004h    nmi_handler (non-maskable interrupt) (from timer watchdog)  |
|       code:00006h    int0_handler                                                |
|       code:0000Eh    int1_handler                                                |
|       code:00016h    int2_handler                                                |
|       code:variable  vint_handler(s) (with context switch, instead of push/pop?) |
+----------------------------------------------------------------------------------+
```


### Interrupt Behaviour
Pending flags are set somewhat as so:

```
+----------------------------------------------------------------------------------+
|       new_state=incoming_hw_signal             ;always 0 for interrupt 0..8      |
|       if polarity=1 then new_state=new_state xor 1                               |
|       new_state=new_state OR manual_trigger    ;done AFTER above polarity invert |
|       new_state=new_state AND NOT master_disable                                 |
|       if new_state=1 and old_state=0 then pending=1                              |
|       old_state=new_state                                                        |
+----------------------------------------------------------------------------------+
```

Acknowlege is required for clearing pending bits, this is required in both Egde- and Level-triggered modes (the difference is that Level-triggered mode will ignore the acknowledge if new_state is still on).
Manual Trigger won\'t appear in Pending until after two NOP opcodes (or similar delay).

### IRQ-to-interrupt translator
The main job of ICU is to translate 16 IRQ signals to 4 processor interrupt signals (int0, int1, int2 and vint), specified by I0x, I1x, I2x and IVx registers. When an IRQ is signaled, ICU will generate interrupt signal and the processor starts to execute interrupt handling procedure if the core interrupt is enabled. The procedure is supposed check IPx reigster to know the exact IRQ index, and to set IAx registers to clear the IRQ signal.

### Software interrupt
The processor can writes to ITx to generate a software interrupt manually. A use case for this in many 3DS games is that IRQ 0 is used as the reschedule procedure for multithreading. When a thread wants to yield, it triggers IRQ 0, which switches thread context and resume another thread.



