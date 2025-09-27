# ARM11 MPCore - Interrupt Handling


### CPU Interrupt Interface Registers (for Interrupt Handling)
Below registers are for the LOCAL CPU core (the other CPU cores have their own registers, mapped at the same address).

### 17E00100h - CPU Interface Control Register (R/W)

```
+-----------------------------------------------------------------------+
|       0     Interrupt Enable for local CPU   (0=Disable, 1=Enable)    |
|       1-31  Reserved                                                  |
+-----------------------------------------------------------------------+
```

When disabled: External nIRQ input is still working (and, in that case, nIRQ should be handled directly; without using the disabled ACK/EOI registers).

### 17E00104h - Priority Mask Register (R/W)
The priority mask is used to prevent interrupts from being sent to the MP11 CPU. The CPU Interface asserts an interrupt request to an MP11 CPU if the priority of the highest Pending interrupt sent by the Interrupt Distributor is strictly higher than the mask set in the Priority Mask Register.

```
+-------------------------------------------------------------------------+
|       0-3  Unused SBZ                                                   |
|       4-7  Priority Mask value                                          |
|                 NOTE: This is a 4bit COMPARE value (not an AND-mask)    |
|                    0xF Interrupts with priority 0x0-0xE are not masked. |
|                    0x0 All interrupts are masked.                       |
|       8-31 Unused SBZ                                                   |
+-------------------------------------------------------------------------+
```


### 17E00108h - Binary Point Register (R/W)
The Binary Point Register is used to determime whether a new interrupt pre-empts a currently Active one, using only part, or none of the priority level.

```
+-----------------------------------------------------------------------+
|       0-2   Binary Point (see below)                                  |
|       3-31  Reserved                                                  |
+-----------------------------------------------------------------------+
```

Binary point bit values assignment:

```
+----------------------------------------------------------------------------+
|       03h = All bits4,5,6,7 of priority are compared for pre-emption       |
|       04h = Only bit5,6,7   of priority are compared for pre-emption       |
|       05h = Only bit6,7     of priority are compared for pre-emption       |
|       06h = Only bit7       of priority is compared for pre-emption        |
|       07h = No bits compared, no pre-emption is performed (no nested IRQs) |
|       00h,01h,02h = Same as 03h                                            |
+----------------------------------------------------------------------------+
```

This is related to the \"Running Priority Register\" (see there for details).

### 17E0010Ch - Interrupt Acknowledge (ACK) Register (R)

```
+---------------------------------------------------------------------------------+
|       0-9     Interrupt ID          (00h..FFh, or 3FFh=None)                    |
|       10-12   Source for ID=00h-0Fh (0..3=CPU0..3, or always 0 for ID=10h-3FFh) |
|       13-31   Unused (0)                                                        |
+---------------------------------------------------------------------------------+
```

Reading returns the ID of the next pending interrupt with highest priority, and automatically switches the interrupt from pending state to active state (indicating that it is being processed). The CPU should then process the interrupt, and, thereafer, use End of Interrupt register (to indicate that processing is done).

### 17E00110h - End of Interrupt (EOI) Register (W)

```
+-------------------------------------------------------------------------+
|       0-31    Same format as Interrupt Acknowledge Register (see there) |
+-------------------------------------------------------------------------+
```

Writing clears the Active flag for the corresponding interrupt, indicating that interrupt processing is done. The written value should be same as the (memorized) value from the Interrupt Acknowledge Register.

### 17E00114h - Running Priority Register (R)
Indicates the priority of the currently processed interrupt (the last acknowledged and not yet completed interrupt on the local CPU core).

```
+------------------------------------------------------------------------------------+
|       0-3  Reserved SBZ                                                            |
|       4-7  Priority (0=Highest .. 14=lowest, 15=None/No interrupt being processed) |
|       8-31 Reserved                                                                |
+------------------------------------------------------------------------------------+
```

All interrupts with same or lower priority are automatically disabled until finishing the current interrupt (by writing to End of Interrupt register).
Optionally, the \"Binary Point Register\" allows to ignore the priority LSB(s) when comparing the new Interrupt\'s priority with the currently \"Running Priority\" (for example, ignoring the lower two bits would cause an interrupt with priority=5 to also disable slighly higher priority interrupts with priority=6..7).

### 17E00118h - Highest Pending Interrupt Register (R)

```
+-------------------------------------------------------------------------+
|       0-31    Same format as Interrupt Acknowledge Register (see there) |
+-------------------------------------------------------------------------+
```

Same as Interrupt Acknowledge Register, except that reading doesn\'t make the corresponding interrupt Active.
Uh, and supposedly doesn\'t clear its Pending state\... or does it?



