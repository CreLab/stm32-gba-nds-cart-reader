# ARM11 MPCore - Snoop Control Unit (SCU)


### Snoop Control Unit (SCU)
Below registers exists only once (not per CPU). However, the performance counters are somewhat supposed to be used as two counters per CPU.

### 17E00000h - SCU Control Register (R/W)
The SCU Control Register enables the SCU and controls its behavior. It must be accessed using a read-modify-write sequence.

```
+-------------------------------------------------------------------------------------+
|       0     SCU Enable      (0=Disable, 1=Enable)                                   |
|             (enable: maintain coherency between MP11 CPUs Level 1 data side caches) |
|             (in single CPU configuration, this bit has no effect and is always 0)   |
|       1-4   Allow CPU0..3 to access SCU at 17E00000h..17E000FFh (0=No, 1=Yes)       |
|       5-8   Allow CPU0..3 to access TMR at 17E00200h..17E005FFh (0=No, 1=Yes)       |
|       9-12  Allow CPU0..3 to access IRQ at 17E00700h..17E00AFFh (0=No, 1=Yes)       |
|       13    Report RAM Parity errors via parity error signals (0=Disable, 1=Enable) |
|       14-31 Reserved SBZ                                                            |
+-------------------------------------------------------------------------------------+
```

Bit1-4: There is a mechanism that prevents all bits being cleared at the same time.
Bit13: Before enabling SCU parity checking, all SCU tag must be invalidated.
This register doesn\'t seem to allow to disable access to the Global Interrupt Distributor at 17E01000h-17E01FFFh (however, the MMU can disable the whole 4Kbyte page).

### 17E00004h - SCU Configuration Register (R)

```
+-----------------------------------------------------------------------------------+
|       0-1   Number of ARM11 CPU cores   (0..3 = 1,2,3,4 CPU's)                    |
|       2-3   Reserved SBZ                                                          |
|       4-7   CPU0..3 Symmetric/Asymmetric Multi-processing (0=SMP/coherent, 1=AMP) |
|       8-9   CPU0 Tag RAM cache size (0=16KB, 1=32KB, 2=64KB, 3=Reserved)          |
|       10-11 CPU1 Tag RAM cache size (0=16KB, 1=32KB, 2=64KB, 3=Reserved)          |
|       12-13 CPU2 Tag RAM cache size (0=16KB, 1=32KB, 2=64KB, 3=Reserved)          |
|       14-15 CPU3 Tag RAM cache size (0=16KB, 1=32KB, 2=64KB, 3=Reserved)          |
|       16-31 Reserved SBZ                                                          |
+-----------------------------------------------------------------------------------+
```

Cache size 16KB/32KB/64KB implies 64/128/256 indexes per tag RAM accordingly.
On Old3DS this is 00000011h. On New3DS this is 00005013h (even in Old3DS mode). But changes to 00005003h when using fastboot\...?

### 17E00008h - SCU CPU Status Register (R/W)

```
+--------------------------------------------------------------------------+
|       0-1   CPU0 status (0=Normal, 1=Reserved, 2=Dormant, 3=Powered-off) |
|       2-3   CPU1 status (0=Normal, 1=Reserved, 2=Dormant, 3=Powered-off) |
|       4-5   CPU2 status (0=Normal, 1=Reserved, 2=Dormant, 3=Powered-off) |
|       6-7   CPU3 status (0=Normal, 1=Reserved, 2=Dormant, 3=Powered-off) |
|       8-31  Reserved SBZ                                                 |
+--------------------------------------------------------------------------+
```

Dormant mode and powered-off mode are controlled by an external power controller.
SCU CPU Status Register bits indicate to the external power controller which power domains can be powered down.
Before entering any other power mode than Normal, the MP11 CPU must set its status field to signal to the SCU which mode it is about to enter (so that the SCU can determine if it still can send coherency requests to the CPU). The MP11 CPU then executes a WFI entry instruction. When in WFI state, the PWRCTLOn bus is enabled and signals to the power controller what it must do with power domains.
The SCU CPU Status Register bits are used in conjunction with internal WFI entry signals to generate PWRCTLOn output pins.
The SCU CPU Status Register bits can also be read by a CPU exiting low-power mode to determine its state before executing its reset setup.
MP11 CPUs status fields take PWRCTLIn values at reset, except for nonpresent CPUs.
For nonpresent CPUs writing to this field has no effect.

### 17E0000Ch - SCU Invalidate All Register (W)

```
+---------------------------------------------------------------------------------+
|       0-3   Invalidate CPU0 ways (bit0-3   = Way 0,1,2,3)  (0=No, 1=Invalidate) |
|       4-9   Invalidate CPU1 ways (bit4-9   = Way 0,1,2,3)  (0=No, 1=Invalidate) |
|       8-11  Invalidate CPU2 ways (bit8-11  = Way 0,1,2,3)  (0=No, 1=Invalidate) |
|       12-15 Invalidate CPU3 ways (bit12-15 = Way 0,1,2,3)  (0=No, 1=Invalidate) |
|       16-31 Reserved SBZ                                                        |
+---------------------------------------------------------------------------------+
```

Allows to invalidate the tag RAMs on a per CPU and per way basis. This operation is atomic, that is, a write transfer to this address only terminates when all the lines have been invalidated. This register reads as 0.
Uh, what is a \"way\"?

### 17E00010h - Performance Monitor Control Register (R/W)

```
+-------------------------------------------------------------------------------------+
|       0      Enable bit for all counters     (0=Disable, 1=Enable)                  |
|       1      Reset all count registers       (0=No, 1=Reset)                        |
|       2-7    Reserved SBZ                                                           |
|       8-15   Counter MN0..7 Interrupt Enable (0=Disable, 1=Enable)                  |
|       16-23  Counter MN0..7 Interrupt Flag (0=No, 1=Overflow/IRQ) ;write 1 to clear |
|       24-31  Reserved SBZ/RAZ                                                       |
+-------------------------------------------------------------------------------------+
```


### 17E00014h - SCU Monitor Counter Events 0, bit0-31 (R/W)
### 17E00018h - SCU Monitor Counter Events 1, bit32-63 (R/W)

```
+-----------------------------------------------------------------------+
|       0-7     EvCount0  Identifies the event for counter MN0          |
|       8-15    EvCount1  Identifies the event for counter MN1          |
|       16-23   EvCount2  Identifies the event for counter MN2 (if any) |
|       24-31   EvCount3  Identifies the event for counter MN3 (if any) |
|       48-55   EvCount6  Identifies the event for counter MN6 (if any) |
|       56-63   EvCount7  Identifies the event for counter MN7 (if any) |
|       32-39   EvCount4  Identifies the event for counter MN4 (if any) |
|       40-47   EvCount5  Identifies the event for counter MN5 (if any) |
+-----------------------------------------------------------------------+
```

Event source number definitions:

```
+-------------------------------------------------------------------------------------+
|       00h     Counter disabled                                                      |
|       01h     CPU0 Miss  ;\                                                         
|       02h     CPU1 Miss  ; CPUn requested a coherent linefill that misses in all    |
|       03h     CPU2 Miss  ; other CPUs. The request is sent to external memory       |
|       04h     CPU3 Miss  ;/                                                         |
|       05h     CPU0 Hit   ;\                                                         
|       06h     CPU1 Hit   ; CPUn requested a coherent linefill that hits in another  |
|       07h     CPU2 Hit   ; CPU. The linefill is fetched from the relevant CPU cache |
|       08h     CPU3 Hit   ;/                                                         |
|       09h     CPU0 Error ;\                                                         
|       0Ah     CPU1 Error ; CPUn was expected to have a coherent                     |
|       0Bh     CPU2 Error ; line in its cache but answers nonpresent.                |
|       0Ch     CPU3 Error ;/                                                         |
|       0Dh     Line migration  ;-A line is directly transferred from one             |
|                               ;  CPU to another on a linefill request instead of    |
|                               ;  switching to SHARED.                               |
|       0Eh     Master0 Read port busy                                                |
|       0Fh     Master1 Read port busy                                                |
|       10h     Master0 Write port busy                                               |
|       11h     Master1 Write port busy                                               |
|       12h     A Read transfer is sent to the external memory                        |
|       13h     A Write transfer is sent to the external memory                       |
|       14h-1Eh N/A                                                                   |
|       1Fh     CycleCount   ;-The counter increments on each CPU clock cycle         |
|       20h-FFh N/A                                                                   |
+-------------------------------------------------------------------------------------+
```


### 17E0001Ch - SCU Monitor Counter MN0 (R/W) ;exists always
### 17E00020h - SCU Monitor Counter MN1 (R/W) ;exists always
### 17E00024h - SCU Monitor Counter MN2 (R/W) ;exists only for two or more CPUs
### 17E00028h - SCU Monitor Counter MN3 (R/W) ;exists only for two or more CPUs
### 17E0002Ch - SCU Monitor Counter MN4 (R/W) ;exists only for three or more CPUs
### 17E00030h - SCU Monitor Counter MN5 (R/W) ;exists only for three or more CPUs
### 17E00034h - SCU Monitor Counter MN6 (R/W) ;exists only for four CPUs
### 17E00038h - SCU Monitor Counter MN7 (R/W) ;exists only for four CPUs

```
+-----------------------------------------------------------------------+
|       0-31  Counter (incrementing upon selected event)                |
+-----------------------------------------------------------------------+
```

Old3DS has four counters, MN0-MN3. New3DS has eight counters, MN0-MN7 (even in Old3DS mode).



