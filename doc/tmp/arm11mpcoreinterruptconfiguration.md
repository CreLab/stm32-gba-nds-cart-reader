# ARM11 MPCore - Interrupt Configuration


### Distributed Interrupt Controller (for Interrupt Configuration)
These registers are mostly used for interrupt configuration (and for internally maintaining an list of pending/active interrupts).

```
+-----------------------------------------------------------------------+
|       -- Most of these registers exists only once (not per CPU) --    |
+-----------------------------------------------------------------------+
```

Except, the Priority for Software Interrupts 00h-0Fh can be configured per LOCAL CPU. And, the Pending and Active flags do \<internally\> exist for each CPU (for Software Interrupts 00h-0Fh, they do even exists for \"From each CPU to each CPU\"). However, reading the Pending/Active/Priority flags doesn\'t fully represent all of the internal per-CPU states.

### 17E01000h - Interrupt Distributor Control Register (R/W)

```
+-------------------------------------------------------------------------+
|       0     Global Interrupt Controller Enable    (0=Disable, 1=Enable) |
|       1-31  Reserved                                                    |
+-------------------------------------------------------------------------+
```

If bit0=0, no interrupts at all are sent to the CPU interrupt interfaces.

### 17E01004h - Interrupt Controller Type Register (R)

```
+------------------------------------------------------------------------------------+
|       0-4   Number of Interrupt IDs   (0-7 = 20h,40h,60h,...,100h) (8-31=Reserved) |
|       5-7   Number of ARM11 CPU cores (0-3 = 1,2,3,4 CPU's)        (4-7=Reserved)  |
|       8-31  Reserved                                                               |
+------------------------------------------------------------------------------------+
```

Note: Interrupt ID 00h-1Fh are internal IRQs, ID 20h-FFh are external IRQs.
On Old3DS this 00000023h, 2 CPUs and 80h IRQs.
On New3DS this 00000063h, 4 CPUs and 80h IRQs (even in Old3DS mode).

### 17E01100h..17E0111Fh - Interrupt Enable Set Registers (256 x 1bit) (R/W)
### 17E01180h..17E0119Fh - Interrupt Enable Clear Registers (256 x 1bit) (R/W)

```
+------------------------------------------------------------------------------------+
|       0-15    Interrupt 00h-0Fh (Read: Always 1=Enabled)      (Write=No effect)    |
|       16-255  Interrupt 10h-FFh (Read: 0=Disabled, 1=Enabled) (Write: 1=Set/Clear) |
+------------------------------------------------------------------------------------+
```

Enable means that pending IRQs will be transmitted to the targeted CPUs.
The enable bit, when set to 0, does not prevent an edge-triggered interrupt from becoming Pending.
The enable bit, when set to 0, does prevent a level sensitive interrupt from becoming Pending only if asserted by the hardware pin, INT.
Note: If an interrupt is Pending or Active when its enable bit is set to 0, it remains in its current state.

### 17E01200h..17E0121Fh - Interrupt Pending set Registers (256 x 1bit) (R/W)
### 17E01280h..17E0129Fh - Interrupt Pending clear Registers (256 x 1bit) (R/W)

```
+-----------------------------------------------------------------------------------+
|       0-15   Interrupt 00h-0Fh pending on local CPU (0=No, 1=Pending) (W=??)      |
|       16-31  Interrupt 10h-1Fh pending on local CPU (0=No, 1=Pending) (W=?)       |
|       32-255 Interrupt 20h-FFh pending on CPU(s)??  (0=No, 1=Pending) (W=Set/Clr) |
|      Bit0-31:   Reading returns 1 if pending on local CPU core                    |
|      Bit32-255: Reading returns 1 if pending on one or more ANY CPU cores         |
|                  (if it's pending on the LOCAL CPU can be seen only once when     |
|                  reading the Acknowledge register?)                               |
|                  (the Enable and Target bits do also somewhat imply whether       |
|                  the interrupt could have become pending on local CPU)            |
|      Bit0-15:   Write/Set is ignored (use 17E01F00h Software Interrupt instead)   |
|      Bit16-31:  Write/Set is...?                                                  |
|      Bit32-255: Write/Set allows to force the state=1 for ALL TARGET CPU cores    |
|      Bit0-15:   Write/Clear is...?                                                |
|      Bit16-31:  Write/Clear is...?                                                |
|      Bit32-255: Write/Clear allows to force the state=0 for ALL CPU cores         |
+-----------------------------------------------------------------------------------+
```


### 17E01300h..17E0131Fh - Active Bit Registers (256 x 1bit) (R)

```
+-------------------------------------------------------------------------------+
|       0-31   Interrupt 00h-1Fh is active on local CPU        (0=No, 1=Active) |
|       32-255 Interrupt 20h-FFh is active on one or more CPUs (0=No, 1=Active) |
+-------------------------------------------------------------------------------+
```

Active means that the interrupt is being processed on at least one MP11 CPU.

### 17E01400h..17E014FFh - Interrupt Priority Registers (256 x 8bit) (R/W)
The priority determines which interrupt will show up next in the interrupt interface registers. And, the interface registers can be used to manually disable lower priority interrupts during \'critical sections\'. And, while processing an interrupt, the hardware will automatically disable interrupts with same or lower priority (optionally, the \"Binary Point\" feature allows to ignore the LSBs of the priorioty, eg. ignoring the lowest bit with allow to also disable interrupts with slightly higher priority).

```
+------------------------------------------------------------------------------------+
|       0-127     Interrupt 00h-0Fh Priority for local CPU (bit0-3=SBZ, bit4-7=Prio) |
|       128-231   Interrupt 10h-1Ch Priority for nothing?  (bit0-7=Unused/zero)      |
|       232-255   Interrupt 1Dh-1Fh Priority for local CPU (bit0-3=SBZ, bit4-7=Prio) |
|       256-2047  Interrupt 20h-FFh Priority for all CPUs  (bit0-3=SBZ, bit4-7=Prio) |
+------------------------------------------------------------------------------------+
```

Priority values are 00h=Highest\... E0h=Lowest, or F0h=None (same as interrupt disabled).
When multiple Pending interrupts have the same priority, the selected interrupt is the one with lowest ID. If there are multiple Pending software interrupts with the same ID, the lowest MP11 CPU source is selected.

### 17E01800h..17E018FFh - Interrupt CPU Targets Registers (256 x 8bit) (R/W)
These registers store the list of MP11 CPUs for which an interrupt can be Pending. Interrupt target registers are ignored in cases of software triggered interrupts.

```
+-----------------------------------------------------------------------------------+
|       0-231     Interrupt 00h-1Ch Target (fixed 00h) (see 17E01F00h instead)  (-) |
|       232-255   Interrupt 1Dh-1Fh Target (fixed 01h/02h/04h/08h for CPU0..3)  (R) |
|       256-2047  Interrupt 20h-FFh Target (bit0-3=CPU0..3, bit4-7=SBZ)       (R/W) |
+-----------------------------------------------------------------------------------+
```

Modifying a CPU target list has no influence on a Pending or Active interrupt, but takes effect on a subsequent assertion of the interrupt.

### 17E01C00h..17E01C3Fh - Interrupt Configuration Registers (256 x 2bit) (R/W)
Interrupt Configuration Registers define the assertion condition and the software model of each interrupt.

```
+------------------------------------------------------------------------------------+
|       0-31     Interrupt 00h-0Fh Condition (can be 2,3) (always rising-edge)       |
|       32-57    Interrupt 10h-1Ch Condition (always 0)                              |
|       58-61    Interrupt 1Dh-1Eh Condition (always 2) (always N-N, rising-edge)    |
|       62-63    Interrupt 1Fh     Condition (always 0) (ignored, always low active) |
|       64-511   Interrupt 20h-FFh Condition (can be 0,1,2,3)                        |
+------------------------------------------------------------------------------------+
```

Interrupt line encodings for bits 1 and 0:

```
+-----------------------------------------------------------------------+
|       00h = N-N software model, level high active                     |
|       01h = 1-N software model, level high active                     |
|       02h = N-N software model, rising edge sensitive                 |
|       03h = 1-N software model, rising edge sensitive                 |
+-----------------------------------------------------------------------+
```

The N-N and 1-N models are relevant only if more than one CPU is configured as Target:

```
+------------------------------------------------------------------------------------+
|       1-N model: An interrupt that is taken on any CPU clears the Pending status   |
|         on all CPUs.                                                               |
|       N-N model: All CPUs receive the interrupt independently. The Pending status  |
|         is cleared only for the CPU that takes it, not for the other CPUs. The N-N |
|         model has been deprecated in the latest interrupt controller architecture. |
+------------------------------------------------------------------------------------+
```

Unknown how 1-N and N-N differ for Interrupt 00h-0Fh (it\'s said that each CPU has it\'s own pending flags for 00h-0Fh, so the model should be always \"1-1\").

```
+----------------------------------------------------------------------------------+
|       Obscure Notes:                                                             |
|       - With the 1-N software model, the nIRQ input is asserted on all CPUs      |
|         configured in the CPU Targets Register. Uh, but Interrupt 1Fh is fixed?  |
|       - If more than one of these CPUs reads the Interrupt Acknowledge Register  |
|         at the same time, they can all acknowledge the same interrupt. The       |
|         interrupt service routine must ensure that only one of them tries to     |
|         process the interrupt, with the others returning after writing the ID to |
|         the End of Interrupt Register. Uh, does that apply to nIRQ only? Or to   |
|         all IRQs?                                                                |
+----------------------------------------------------------------------------------+
```


### 17E01D00h..17E01D1Fh - Interrupt Line Level Registers (256 x 1bit) (R)

```
+-------------------------------------------------------------------------------+
|       0-31    Dummy line level bits for Internal IRQ 00h..1Fh (always 0)      |
|       32-255  Interrupt line level for External IRQ 20h..FFh  (0=Low, 1=High) |
+-------------------------------------------------------------------------------+
```


### 17E01F00h - Software Interrupt Register (W)

```
+------------------------------------------------------------------------------------+
|       0-9     Interrupt ID (0..FFh? or 0..0Fh/1Fh?) (100h..1FFh=Reserved/ignored)  |
|       10-15   SBZ                                                                  |
|       16-19   Send the interrupt to CPU0..3 (0=No, 1=Yes) ;used only if Bit24-25=0 |
|       20-23   SBZ                                                                  |
|       24-25   Target list mode (0=Bit16-19, 1=Other CPUs, 2=Local CPU, 3=Reserved) |
|       26-31   SBZ                                                                  |
+------------------------------------------------------------------------------------+
```

This can be used to trigger an interrupt (identified with its ID) to a list of MP11 CPUs.



