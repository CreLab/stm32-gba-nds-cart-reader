# DSi Atheros Wifi - Internal I/O - 020080h - WMAC IRQ Interrupt (hw4/hw6)


### ATH:020080h - MAC_DMA_ISR(\_P) - MAC Primary interrupt status register
### ATH:0200A0h - MAC_DMA_IMR(\_P) - MAC Primary interrupt mask register
### ATH:0200C0h - MAC_DMA_ISR(\_P)\_RAC - MAC Primary interrupt read-and-clear
Interrupt Status Registers
Only the bits in the ISR_P register and the IMR_P registers control whether the MAC\'s INTA# output is asserted. The bits in the secondary interrupt status/mask registers control what bits are set in the primary interrupt status register; however the IMR_S\* registers DO NOT determine whether INTA# is asserted. That is INTA# is asserted only when the logical AND of ISR_P and IMR_P is non-zero. The secondary interrupt mask/status registers affect what bits are set in ISR_P but they do not directly affect whether INTA# is asserted.
Interrupt Mask Registers
Only the bits in the IMR control whether the MAC\'s INTA# output will be asserted. The bits in the secondary interrupt mask registers control what bits get set in the primary interrupt status register; however the IMR_S\* registers DO NOT determine whether INTA# is asserted.
Read-and-Clear Registers
The read-and-clear registers are read-only (R) \"shadow copies\" of the interrupt status registers, with read-and-clear access.

```
+-------------------------------------------------------------------------------------+
|       0     At least one frame received sans errors  ;\                             
|       1     Receive interrupt request                ;                              |
|       2     Receive error interrupt                  ; RX                           |
|       3     No frame received within timeout clock   ;                              |
|       4     Received descriptor empty interrupt      ;                              |
|       5     Receive FIFO overrun interrupt           ;/                             |
|       6     Transmit okay interrupt                  ;\       ;<-- ISR_S0.Bit0..9   
|       7     Transmit interrupt request               ;                              |
|       8     Transmit error interrupt                 ; TX     ;<-- ISR_S1.Bit0..9   |
|       9     No frame transmitted interrupt           ;                              |
|       10    Transmit descriptor empty interrupt      ;                              |
|       11    Transmit FIFO underrun interrupt         ;/       ;<-- ISR_S2.Bit0..9   |
|       12    MIB interrupt - see MIBC                                                |
|       13    Software interrupt                                                      |
|       14    PHY receive error interrupt                                             |
|       15    Key-cache miss interrupt                                                |
|       16    Beacon rssi high threshold interrupt  ;aka Beacon rssi hi threshold     |
|       17    Beacon threshold interrupt            ;aka Beacon rssi lo threshold     |
|       18    Beacon missed interrupt                                                 |
|       19    Maximum transmit interrupt rate                                         |
|       20    Beacon not ready interrupt            ;aka BNR interrupt                |
|       21    An unexpected bus error has occurred                                    |
|       22    -                                                                       |
|       23    Beacon Misc (TIM, CABEND, DTIMSYNC, BCNTO)        ;<-- ISR_S2.Bit24..27 |
|       24    Maximum receive interrupt rate                                          |
|       25    QCU CBR overflow interrupt                        ;<-- ISR_S3.Bit0..9   |
|       26    QCU CBR underrun interrupt                        ;<-- ISR_S3.Bit16..27 |
|       27    QCU scheduling trigger interrupt                  ;<-- ISR_S4.Bit0..9   |
|       28    GENTMR interrupt (aka GENERIC_TIMERS... and/or ISR_S5?)                 |
|       29    HCFTO interrupt                                                         |
|       30    Transmit completion mitigation interrupt                                |
|       31    Receive completion mitigation interrupt                                 |
+-------------------------------------------------------------------------------------+
```


### ATH:020084h - MAC_DMA_ISR_S0 - MAC Secondary Interrupt 0 Stat TX OK/DESC
### ATH:0200A4h - MAC_DMA_IMR_S0 - MAC Secondary Interrupt 0 Mask TX OK/DESC
### ATH:0200C4h - MAC_DMA_ISR_S0_S - MAC Secondary Interrupt 0 Read-and-Clear

```
+------------------------------------------------------------------------------------+
|       0-9   TXOK (QCU 0-9)                                   ;--> Primary_ISR.Bit6 |
|       16-27 TXDESC (QCU 0-9)                                 ;--> Primary_ISR. ??  |
+------------------------------------------------------------------------------------+
```


### ATH:020088h - MAC_DMA_ISR_S1 - MAC Secondary Interrupt 1 Stat TX ERR/EOL
### ATH:0200A8h - MAC_DMA_IMR_S1 - MAC Secondary Interrupt 1 Mask TX ERR/EOL
### ATH:0200C8h - MAC_DMA_ISR_S1_S - MAC Secondary Interrupt 1 Read-and-Clear

```
+------------------------------------------------------------------------------------+
|       0-9   TXERR (QCU 0-9)                                  ;--> Primary_ISR.Bit8 |
|       16-27 TXEOL (QCU 0-9)                                                        |
+------------------------------------------------------------------------------------+
```


### ATH:02008Ch - MAC_DMA_ISR_S2 - MAC Secondary Interrupt 2 Stat TX URN/MISC
### ATH:0200ACh - MAC_DMA_IMR_S2 - MAC Secondary Interrupt 2 Mask TX URN/MISC
### ATH:0200CCh (hw6:000200D0h?) - MAC_DMA_ISR_S2_S - MAC .. 2 Read-and-Clear

```
+-------------------------------------------------------------------------------------+
|       0-9   TXURN (QCU 0-9)                                  ;--> Primary_ISR.Bit11 |
|       10    -                                                                       |
|       11    RX_INT                  ;RX                                             |
|       12    WL_STOMPED                                                              |
|       13    RX_PTR_BAD              ;RX                                             |
|       14    BT_LOW_PRIORITY_RISING                                                  |
|       15    BT_LOW_PRIORITY_FALLING                                                 |
|       16    BB_PANIC_IRQ                                                            |
|       17    BT_STOMPED                                                              |
|       18    BT_ACTIVE_RISING                                                        |
|       19    BT_ACTIVE_FALLING                                                       |
|       20    BT_PRIORITY_RISING                                                      |
|       21    BT_PRIORITY_FALLING                                                     |
|       22    CST                                                                     |
|       23    GTT                                                                     |
|       24    TIM                                 ;\                                  
|       25    CABEND                              ; Beacon Misc --> Primary_ISR.Bit23 |
|       26    DTIMSYNC                            ;                                   |
|       27    BCNTO                               ;/                                  |
|       28    CABTO                                                                   |
|       29    DTIM                                                                    |
|       30    TSFOOR                                                                  |
|       31    -                                                                       |
+-------------------------------------------------------------------------------------+
```


### ATH:020090h - MAC_DMA_ISR_S3 - MAC Secondary Interrupt 3 Stat QCBR OVF/URN
### ATH:0200B0h - MAC_DMA_IMR_S3 - MAC Secondary Interrupt 3 Mask QCBR OVF/URN
### ATH:0200D0h (hw6:000200D4h?) - MAC_DMA_ISR_S3_S - MAC .. 3 Read-and-Clear

```
+-------------------------------------------------------------------------------------+
|       0-9   QCBROVF (QCU 0-9)                                ;--> Primary_ISR.Bit25 |
|       16-27 QCBRURN (QCU 0-9)                                ;--> Primary_ISR.Bit26 |
+-------------------------------------------------------------------------------------+
```


### ATH:020094h - MAC_DMA_ISR_S4 - MAC Secondary Interrupt 4 Stat QTRIG
### ATH:0200B4h - MAC_DMA_IMR_S4 - MAC Secondary Interrupt 4 Mask QTRIG
### ATH:0200D4h (hw6:000200D8h?) - MAC_DMA_ISR_S4_S - MAC .. 4 Read-and-Clear

```
+-------------------------------------------------------------------------------------+
|       0-9   QTRIG (QCU 0-9)                                  ;--> Primary_ISR.Bit27 |
+-------------------------------------------------------------------------------------+
```


### ATH:020098h - MAC_DMA_ISR_S5 - MAC Secondary Interrupt 5 Stat TIMERS
### ATH:0200B8h - MAC_DMA_IMR_S5 - MAC Secondary Interrupt 5 Mask TIMERS
### ATH:0200D8h (hw6:000200DCh?) - MAC_DMA_ISR_S5_S - MAC .. 5 Read-and-Clear

```
+-------------------------------------------------------------------------+
|       0     TBTT_TIMER_TRIGGER              ;-TBTT timer                |
|       1     DBA_TIMER_TRIGGER               ;\                          
|       2     SBA_TIMER_TRIGGER               ;                           |
|       3     HCF_TIMER_TRIGGER               ;                           |
|       4     TIM_TIMER_TRIGGER               ; timer's                   |
|       5     DTIM_TIMER_TRIGGER              ;                           |
|       6     QUIET_TIMER_TRIGGER             ;                           |
|       7     NDP_TIMER_TRIGGER               ;                           |
|       8-15  GENERIC_TIMER2_TRIGGER          ;/                          |
|       16    TIMER_OVERFLOW                  ;<-- which timer overflow ? |
|       17    DBA_TIMER_THRESHOLD             ;\                          
|       18    SBA_TIMER_THRESHOLD             ;                           |
|       19    HCF_TIMER_THRESHOLD             ;                           |
|       20    TIM_TIMER_THRESHOLD             ; threshold's               |
|       21    DTIM_TIMER_THRESHOLD            ;                           |
|       22    QUIET_TIMER_THRESHOLD           ;                           |
|       23    NDP_TIMER_THRESHOLD             ;                           |
|       24-31 GENERIC_TIMER2_THRESHOLD        ;/                          |
+-------------------------------------------------------------------------+
```


### ATH:02009Ch - MAC_DMA_ISR_S6 - hw6 only ;Interrupt 6 Stat UNKNOWN(?)
### ATH:0200BCh - MAC_DMA_IMR_S6 - hw6 only ;Interrupt 6 Mask UNKNOWN(?)
### ATH:0200CCh (hw6:really?) - MAC_DMA_ISR_S6_S (R) shadow - hw6 only

```
+----------------------------------------------------------------------------------+
|       0-31   ?? (probably related to the new "hw6" registers in MAC DMA chapter) |
+----------------------------------------------------------------------------------+
```

Note: According to hw6.0 source code, \"S6_S\" has been accidently inserted between \"S1_S\" and \"S2_S\" (thus smashing the old hw4-style port numbering for \"S2_S thru S5_S\") (not checked if that\'s a source code bug, or if it\'s actually implemented as so in real hardware).
The hw6.0 source code leaves ALL primary and secondary IRQ bits undocumented, thw above descriptions are based on hw4 (but hw6 might have some added/changed bits here and there).



