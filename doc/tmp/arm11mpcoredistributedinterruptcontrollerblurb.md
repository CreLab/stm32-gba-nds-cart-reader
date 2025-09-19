# ARM11 MPCore Distributed Interrupt Controller (Blurb)


### 10.1.1 Distributed Interrupt Controller clock frequency
The Distributed Interrupt Controller logic is clocked at half the frequency of the MPCore CPUs because of power and area considerations. Reducing clock speed reduces dynamic power consumption. The lower clock speed requires less pipelining in the design. This means that the overall impact of the reduced clock speed on the Distributed Interrupt Controller is kept to a minimum.
Note
As a consequence, the minimum pulse width of signals driving external interrupt lines is two CPU clock cycles.

### 10.2 Terminology - From point of view of an MP11 CPU, an interrupt can be:

```
+-----------------------------------------------------------------------------------+
|       Inactive: An Inactive interrupt is one that is nonasserted, or which in a   |
|         multi-processing environment has been completely processed by that MP11   |
|         CPU but can still be either Pending or Active in some of the MP11 CPUs to |
|         which it is targeted, and so might not have been cleared at the interrupt |
|         source.                                                                   |
|       Pending: A Pending interrupt is one that has been asserted, and for which   |
|         processing has not started on that MP11 CPU.                              |
|       Active: An Active interrupt is one that has been started on that MP11 CPU,  |
|         but processing is not complete.                                           |
+-----------------------------------------------------------------------------------+
```

An interrupt can be Pending and Active at the same time. This can happen in the case of edge triggered interrupts, when the interrupt is asserted while the MP11 CPU has not finished handling the first occurrence. For level-sensitive interrupts it can only happen if software triggers it. See Interrupt Configuration Registers, 0xC00-0xC3C on page 10-17.

```
+-----------------------------------------------------------------------------------+
|       Pre-emption: An Active interrupt can be pre-empted when a new interrupt of  |
|         higher priority interrupts MP11 CPU interrupt processing. For the purpose |
|         of this document, an Active interrupt can be running if it is actually    |
|         being processed, or pre-empted.                                           |
+-----------------------------------------------------------------------------------+
```

The Distributed Interrupt Controller consists of:
Interrupt Distributor:
The Interrupt Distributor handles interrupt detection and interrupt prioritization.
CPU interrupt interfaces:
There is one CPU interrupt interface per MP11 CPU. The MP11 CPU interrupt interfaces handle interrupt acknowledgement, interrupt masking, and interrupt completion acknowledgement.

### 10.3 Interrupt Distributor
The Interrupt Distributor centralizes all interrupt sources for the ARM11 MPCore processor before dispatching the highest priority ones to each individual MP11 CPU.
All interrupt sources are identified by a unique ID. All interrupt sources have their own configurable priority and list of targeted CPUs, that is, a list of CPUs to which the interrupt is sent when triggered by the Interrupt Distributor.
Note
nFIQ interrupts are not handled by the Distributed Interrupt Controller so that nFIQ interrupt input pins are directly routed to their respective CPU.
Interrupt sources are of the following types:
### Interprocessor interrupts (IPI)
Each MP11 CPU has private interrupts, ID0-ID15, that can only be triggered by software. These interrupts are aliased so that there is no requirement for a requesting MP11 CPU to determine its own ID when it deals with IPIs. The priority of an IPI depends on the receiving CPU, not the sending CPU.
### Private timer and/or watchdog interrupts.
Each MP11 CPU has its own private timer and watchdog that can generate interrupts, using ID29 and ID30.
### A legacy nIRQ pin
In legacy IRQ mode the legacy nIRQ pin, on a per CPU basis, bypasses the Interrupt Distributor logic and directly drives interrupt requests into the MP11 CPU. In legacy IRQ mode, if bit \[0\] of the CPU Interface Control Register is 0, then no interrupts are raised based on input from the Interrupt Distributor. If bit \[0\] is 1, then all interrupts are received from the Interrupt Distributor.
When an MP11 CPU uses the Distributed Interrupt Controller (rather than the legacy pin in the legacy mode) by enabling its own CPU interface, the legacy nIRQ pin is treated like other interrupt lines and uses ID31.
### Hardware interrupts
Hardware interrupts are triggered by programmable events on associated interrupt input lines. MP11 CPUs can support up to 224 interrupt input lines. The interrupt input lines can be configured to be edge sensitive (posedge) or level sensitive (high level). Hardware interrupts start at ID32.

### 10.3.1 Interrupt Distributor overview
The Interrupt Distributor holds the list of Pending interrupts for each CPU, and then selects the highest priority interrupt before issuing it to the CPU interface. Interrupts of equal priority are resolved by selecting the lowest ID.
The Interrupt Distributor consists of a register-based list of interrupts, their priorities and activation requirements (CPU targets). In addition the state of each interrupt on each CPU is held in the associated state storage.
The prioritization logic is physically duplicated for each CPU to enable the selection of the highest priority for each CPU.
The Interrupt Distributor holds the central list of interrupts, processors and activation information, and is responsible for triggering software interrupts to processors.
The CPU Interface acknowledges interrupts and changes interrupt priority masks.

The Interrupt Distributor transmits to the CPU interrupt interfaces their highest Pending interrupt. It receives back the information that the interrupt has been acknowledged, and can then change the status of the corresponding interrupt. The CPU Interface also transmits End of Interrupt Information (EOI), which enables the Interrupt Distributor to update the status of this interrupt from Active to Inactive.

```
+----------------------------------------------------------------------------------+
|                         .-----------.  .------------- Core Acknowledge, and      |
|             .---------->|  Decoder  |  |------------- End Of Interrupt (EOI)     |
|             |           '-----------'  |------------- from CPU Interface         |
|             |              ^       ^   |-------------                            |
|             |              |       |   |                                         |
|             V              V       V   V               Top priority interrupts   |
|          .-----------.----------.--------.---------.                             |
|       -->|           | Priority | Status |         |   .--------.------.         |
|       -->|           | Priority | Status |         |-->| Irq.no | Prio |--> CPU0 |
|       -->|           | Priority | Status | Priori- |   '--------'------'         |
|       -->| Interrupt | Priority | Status | zation  |   .--------.------.         |
|       -->| Interface | Priority | Status | and     |-->| Irq.no | Prio |--> CPU1 |
|       -->|           | Priority | Status | Select- |   '--------'------'         |
|       -->|           | Priority | Status | ion     |   .--------.------.         |
|       -->|           | Priority | Status |         |-->| Irq.no | Prio |--> CPU2 |
|       -->|           | Priority | Status |         |   '--------'------'         |
|       -->|           | Priority | Status |         |   .--------.------.         |
|       -->|           | Priority | Status |         |-->| Irq.no | Prio |--> CPU3 |
|       -->|           | Priority | Status |         |   '--------'------'         |
|          '-----------'----------'--------'---------'                    IRQ's to |
|                          Interrupt List                                 each CPU |
+----------------------------------------------------------------------------------+
```


### 10.3.2 Behavior of the Interrupt Distributor
When the Interrupt Distributor detects an interrupt assertion, it sets the status of the interrupt for the targeted MP11 CPUs to Pending. Level-triggered interrupts cannot be marked as Pending if they are already Active for at least one MP11 CPU.
For each MP11 CPU the prioritization and selection block searches for the Pending interrupt with the highest priority. This interrupt is then sent with its priority to the CPU Interface.


The CPU Interface returns information to the Distributor when the CPU acknowledges (Pending to Active transition) or clears an interrupt (Active to Inactive transition). With the given interrupt ID, the Interrupt Distributor updates the status of this interrupt according to the information sent by the CPU Interface.
When an interrupt is triggered by the Software Interrupt Register or the Set-pending Register, the status of that interrupt for the targeted CPU or CPUs is set to Pending. This interrupt then has the same behavior as a hardware interrupt. The distributor does not differentiate between software and hardware triggered interrupts.



