# ARM11 MPCore Private Memory Region Register Summary


### MPCore private memory region
The MPCore Private Memory Region contains additional ARM control registers (additionally to the CP15 coprocessor registers). The 3DS does have this region mapped at address 17E00000h and up.

```
+------------------------------------------------------------------------------------+
|       17E00000h 100h  MPCore SCU (Snoop Control Unit)                              |
|       17E00100h 100h  MPCore CPU interrupt interface for LOCAL CPU                 |
|       17E00200h 100h  MPCore CPU0 interrupt interface (aliased for debug purposes) |
|       17E00300h 100h  MPCore CPU1 interrupt interface (aliased for debug purposes) |
|       17E00400h 100h  MPCore CPU2 interrupt interface (aliased for debug purposes) |
|       17E00500h 100h  MPCore CPU3 interrupt interface (aliased for debug purposes) |
|       17E00600h 100h  MPCore CPU timer and watchdog for LOCAL CPU                  |
|       17E00700h 100h  MPCore CPU0 timer and watchdog                               |
|       17E00800h 100h  MPCore CPU1 timer and watchdog                               |
|       17E00900h 100h  MPCore CPU2 timer and watchdog  ;\if enabled in              
|       17E00A00h 100h  MPCore CPU3 timer and watchdog  ;/10141312h/13h              |
|       17E00B00h 500h  MPCore Reserved (access causes a DECERR abort exception)     |
|       17E01000h 1000h MPCore Global Interrupt distributor                          |
+------------------------------------------------------------------------------------+
```


### Snoop Control Unit (SCU)

```
+-----------------------------------------------------------------------------+
|       Offset       Type Reset      Name                                     |
|       17E00000h 4   R/W 00001FFEh  SCU Control Register                     |
|       17E00004h 4   R   (var)      SCU Configuration Register               |
|       17E00008h 4   R/W -          SCU CPU Status                           |
|       17E0000Ch 4   W   -          SCU Invalidate All                       |
|       17E00010h 4   R/W 00000000h  SCU Performance Monitor Control Register |
|       17E00014h 4   R/W 00000000h  SCU Monitor Counter Events 0             |
|       17E00018h 4   R/W 00000000h  SCU Monitor Counter Events 1             |
|       17E0001Ch 4   R/W 00000000h  SCU Monitor Counter 0                    |
|       17E00020h 4   R/W 00000000h  SCU Monitor Counter 1                    |
|       17E00024h 4   R/W 00000000h  SCU Monitor Counter 2                    |
|       17E00028h 4   R/W 00000000h  SCU Monitor Counter 3                    |
|       17E0002Ch 4   R/W 00000000h  SCU Monitor Counter 4                    |
|       17E00030h 4   R/W 00000000h  SCU Monitor Counter 5                    |
|       17E00034h 4   R/W 00000000h  SCU Monitor Counter 6                    |
|       17E00038h 4   R/W 00000000h  SCU Monitor Counter 7                    |
|       17E0003Ch C4h -   -          SCU Reserved (0)                         |
+-----------------------------------------------------------------------------+
```

All SCU registers are byte accessible.

### MP11 CPU Interrupt Interface Registers (for Interrupt Handling)

```
+-------------------------------------------------------------------------------+
|       Address       Type Reset value Function                                 |
|       17E00100h 4   R/W  00000000h CPU IRQ Control Register                   |
|       17E00104h 4   R/W  000000F0h CPU IRQ Priority Mask Register             |
|       17E00108h 4   R/W  00000003h CPU IRQ Binary Point Register              |
|       17E0010Ch 4   R    000003FFh CPU IRQ Interrupt Acknowledge?? Register   |
|       17E00110h 4   W    -         CPU IRQ End of Interrupt Register          |
|       17E00114h 4   R    000000F0h CPU IRQ Running Priority Register          |
|       17E00118h 4   R    000003FFh CPU IRQ Highest Pending Interrupt Register |
|       17E0011Ch E4h -    -         CPU IRQ Reserved                           |
+-------------------------------------------------------------------------------+
```

Above registers are for the LOCAL CPU, below are aliases for EACH CPU core.

```
+-------------------------------------------------------------------------------------+
|       17E00200h 100h   MPCore CPU0 interrupt interface (aliased for debug purposes) |
|       17E00300h 100h   MPCore CPU1 interrupt interface (aliased for debug purposes) |
|       17E00400h 100h   MPCore CPU2 interrupt interface (aliased for debug purposes) |
|       17E00500h 100h   MPCore CPU3 interrupt interface (aliased for debug purposes) |
+-------------------------------------------------------------------------------------+
```

All registers of the MP11 CPU interrupt interfaces must be accessed by 32bit transactions only.

### Timer and Watchdog registers

```
+----------------------------------------------------------------------------------+
|       Offset       Type Reset     Name                                           |
|       17E00600h 4   R/W 00000000h MPCore Timer0 Reload Value                     |
|       17E00604h 4   R/W 00000000h MPCore Timer0 Counter Value (decrementing)     |
|       17E00608h 4   R/W 00000000h MPCore Timer0 Control Register                 |
|       17E0060Ch 4   R/W 00000000h MPCore Timer0 Interrupt Status                 |
|       17E00610h 10h -             Reserved                                       |
|       17E00620h 4   R/W 00000000h MPCore Timer1/Watchdog Reload Value            |
|       17E00624h 4   R/W 00000000h MPCore Timer1/Watchdog Counter Value (decrem.) |
|       17E00628h 4   R/W 00000000h MPCore Timer1/Watchdog Control Register        |
|       17E0062Ch 4   R/W 00000000h MPCore Timer1/Watchdog Interrupt Status        |
|       17E00630h 4   R/W 00000000h MPCore Timer1/Watchdog Reset Sent Register     |
|       17E00634h 4   W   -         MPCore Timer1/Watchdog Disable Register        |
|       17E00638h C8h -             Reserved                                       |
+----------------------------------------------------------------------------------+
```

Above registers are for the LOCAL CPU, below are aliases for EACH CPU core.

```
+-----------------------------------------------------------------------------------+
|       17E00700h 100h              MPCore CPU0 timer and watchdog                  |
|       17E00800h 100h              MPCore CPU1 timer and watchdog                  |
|       17E00900h 100h              MPCore CPU2 timer and watchdog  ;\if enabled in 
|       17E00A00h 100h              MPCore CPU3 timer and watchdog  ;/10141312h/13h |
+-----------------------------------------------------------------------------------+
```

All timer and watchdog registers are word accessible only.
Note: There\'s also another ARM11 timer/cycle counter in CP15 registers.

### Distributed Interrupt controller registers (for Interrupt Configuration)

```
+------------------------------------------------------------------------------------+
|       Address   Size  Type Reset     Function                                      |
|       17E01000h 4     R/W  00000000h Interrupt Distributor Control Register        |
|       17E01004h 4     R    -         Interrupt Controller Type Register            |
|       17E01008h F8h   -    ....      Reserved                                      |
|       17E01100h 20h   R/W  0000FFFFh Interrupt Enable set Registers ID0-ID31       |
|       17E01104h ()         00000000h Interrupt Enable set Registers ID32 and up    |
|       17E01120h 60h   -    ....      Reserved                                      |
|       17E01180h 20h   R/W  0000FFFFh Interrupt Enable clear Registers ID0-ID31     |
|       17E01184h ()         00000000h Interrupt Enable clear Registers ID32 and up  |
|       17E011A0h 60h   -    ....      Reserved                                      |
|       17E01200h 20h   R/W  00000000h Interrupt Pending set Registers               |
|       17E01220h 60h   -    ....      Reserved                                      |
|       17E01280h 20h   R/W  00000000h Interrupt Pending clear Registers             |
|       17E012A0h 60h   -    ....      Reserved                                      |
|       17E01300h 20h   R    00000000h Interrupt Active Bit Registers                |
|       17E01320h E0h   -    ....      Reserved                                      |
|       17E01400h 100h  R/W  00000000h Interrupt Priority Registers                  |
|       17E01500h 300h  -    ....      Reserved                                      |
|       17E01800h 100h  R/W  00000000h Interrupt CPU targets Registers (a.)          |
|       17E01900h 300h  -    ....      Reserved                                      |
|       17E01C00h 40h   R/W  AAAAAAAAh Interrupt Configuration Registers ID0-ID15    |
|       17E01C04h ()         28000000h Interrupt Configuration Registers ID29-ID31   |
|       17E01C08h ()         00000000h Interrupt Configuration Registers ID32 and up |
|       17E01C40h C0h   -    ....      Reserved                                      |
|       17E01D00h 20h   R    00000000h Interrupt Line Level Registers ID0-ID31       |
|       17E01D04h ()         -         Interrupt Line Level Registers ID32 and up    |
|       17E01D20h E0h   -    ....      Oddly: mirrors of above 20h bytes             |
|       17E01E00h 100h  -    ....      Reserved                                      |
|       17E01F00h 4     W    -         Software Interrupt Register                   |
|       17E01F0xh DCh?  -    ....      Reserved                                      |
|       17E01FE0h 4     R    90h       Peripheral Identification Register 0          |
|       17E01FE4h 4     R    13h       Peripheral Identification Register 1          |
|       17E01FE8h 4     R    04h       Peripheral Identification Register 2          |
|       17E01FECh 4     R    00h       Peripheral Identification Register 3          |
|       17E01FF0h 4     R    0Dh       PrimeCell Identification Register 0           |
|       17E01FF4h 4     R    F0h       PrimeCell Identification Register 1           |
|       17E01FF8h 4     R    05h       PrimeCell Identification Register 2           |
|       17E01FFCh 4     R    B1h       PrimeCell Identification Register 3           |
|         a. Except for address 0x81C. See Interrupt CPU Targets Registers.          |
+------------------------------------------------------------------------------------+
```

All Interrupt Distributor Registers are byte accessible.

Official specs: DDI0360F_arm11_mpcore_r2p0_trm.pdf



