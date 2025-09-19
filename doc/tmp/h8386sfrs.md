# H8/386 SFRs


### H8/386 Special Function Registers at F000h and up

```
+-------------------------------------------------------------------------+
|       F020h FLMCR1  FLASH Memory Control 1                              |
|       F021h FLMCR2  FLASH Memory Control 2                              |
|       F022h FLPWCR  FLASH Memory Power Control                          |
|       F023h EBR1    FLASH Erase Block 1                                 |
|       F02Bh FENR    FLASH Memory Enable                                 |
|       F067h RTCFLG  RTC Interrupt Flag                                  |
|       F068h RSECDR  RTC Seconds / Free running counter                  |
|       F069h RMINDR  RTC Minutes                                         |
|       F06Ah RHRDR   RTC Hours                                           |
|       F06Bh RWKDR   RTC Day-of-week                                     |
|       F06Ch RTCCR1  RTC Control 1                                       |
|       F06Dh RTCCR2  RTC Control 2                                       |
|       F06Fh RTCCSR  RTC Clock Source Select                             |
|       F078h ICCR1   I2C Bus Control 1                                   |
|       F079h ICCR2   I2C Bus Control 2                                   |
|       F07Ah ICMR    I2C Bus Mode                                        |
|       F07Bh ICIER   I2C Bus Interrupt Enable                            |
|       F07Ch ICSR    I2C Bus Status                                      |
|       F07Dh SAR     I2C Slave Address                                   |
|       F07Eh ICDRT   I2C Bus Transmit Data                               |
|       F07Fh ICDRR   I2C Bus Receive Data                                |
|       F085h PFCR    System Port Function Control                        |
|       F086h PUCR8   Port 8 Pull-up Control                              |
|       F087h PUCR9   Port 9 Pull-up Control                              |
|       F08Ch PODR9   Port 9 Open-drain Control                           |
|       F0D0h TMB1    Timer B1 Mode                                       |
|       F0D1h TC/LB1  Timer B1 Counter (R) / Load (W)                     |
|       F0DCh CMCR0   Compare Control 0                                   |
|       F0DDh CMCR1   Compare Control 1                                   |
|       F0DEh CMDR    Compare Data                                        |
|       F0E0h SSCRH   SPI Synchronous Serial Control H     (AccessState3) |
|       F0E1h SSCRL   SPI Synchronous Serial Control L     (AccessState3) |
|       F0E2h SSMR    SPI Synchronous Serial Mode          (AccessState3) |
|       F0E3h SSER    SPI Synchronous Serial Enable        (AccessState3) |
|       F0E4h SSSR    SPI Synchronous Serial Status        (AccessState3) |
|       F0E9h SSRDR   SPI Synchronous Serial Receive Data  (AccessState3) |
|       F0EBh SSTDR   SPI Synchronous Serial Transmit Data (AccessState3) |
|       F0F0h TMRW    Timer W Mode                                        |
|       F0F1h TCRW    Timer W Control                                     |
|       F0F2h TIERW   Timer W Interrupt Enable                            |
|       F0F3h TSRW    Timer W Status                                      |
|       F0F4h TIOR0   Timer W I/O control 0                               |
|       F0F5h TIOR1   Timer W I/O control 1                               |
|       F0F6h TCNT    Timer W Counter   (16bit)                           |
|       F0F8h GRA     Timer W General A (16bit)                           |
|       F0FAh GRB     Timer W General B (16bit)                           |
|       F0FCh GRC     Timer W General C (16bit)                           |
|       F0FEh GRD     Timer W General D (16bit)                           |
+-------------------------------------------------------------------------+
```

### H8/386 Special Function Registers at FF80h and up, with \[FFnn\] & \[FFnn\].bitno

```
+-----------------------------------------------------------------------+
|       FF8Ch ECPWCR  Async Event Counter PWM Compare (16bit)           |
|       FF8Eh ECPWDR  Async Event Counter PWM Data (16bit)              |
|       FF91h SPCR    IrDA UART Serial 3 Port Control                   |
|       FF92h AEGSR   Async Event Input Pin Edge Select                 |
|       FF94h ECCR    Async Event Counter Control                       |
|       FF95h ECCSR   Async Event Counter Control/Status                |
|       FF96h ECH     Async Event Counter H                             |
|       FF97h ECL     Async Event Counter L                             |
|       FF98h SMR3    IrDA UART Serial 3 Mode          (AccessState3)   |
|       FF99h BRR3    IrDA UART Serial 3 Bit Rate      (AccessState3)   |
|       FF9Ah SCR3    IrDA UART Serial 3 Control       (AccessState3)   |
|       FF9Bh TDR3    IrDA UART Serial 3 Transmit Data (AccessState3)   |
|       FF9Ch SSR3    IrDA UART Serial 3 Status        (AccessState3)   |
|       FF9Dh RDR3    IrDA UART Serial 3 Receive Data  (AccessState3)   |
|       FFA6h SEMR    IrDA UART Serial 3 Extended Mode (AccessState3)   |
|       FFA7h IrCR    IrDA Control                                      |
|       FFB0h TMWD    Timer WD Watchdog Mode                            |
|       FFB1h TCSRWD1 Timer WD Watchdog Control/Status 1                |
|       FFB2h TCSRWD2 Timer WD Watchdog Control/Status 2                |
|       FFB3h TCWD    Timer WD Watchdog Counter                         |
|       FFBCh ADRR    A/D Converter Result (16bit)                      |
|       FFBEh AMR     A/D Converter Mode                                |
|       FFBFh ADSR    A/D Converter Start                               |
|       FFC0h PMR1    Port 1 Mode                                       |
|       FFC2h PMR3    Port 3 Mode                                       |
|       FFCAh PMRB    Port B Mode                                       |
|       FFD4h PDR1    Port 1 Data                                       |
|       FFD6h PDR3    Port 3 Data                                       |
|       FFDBh PDR8    Port 8 Data                                       |
|       FFDCh PDR9    Port 9 Data                                       |
|       FFDEh PDRB    Port B Data                                       |
|       FFE0h PUCR1   Port 1 Pull-up Control                            |
|       FFE1h PUCR3   Port 3 Pull-up Control                            |
|       FFE4h PCR1    Port 1 Control                                    |
|       FFE6h PCR3    Port 3 Control                                    |
|       FFEBh PCR8    Port 8 Control                                    |
|       FFECh PCR9    Port 9 Control                                    |
|       FFF0h SYSCR1  System Control 1                                  |
|       FFF1h SYSCR2  System Control 2                                  |
|       FFF2h IEGR    Interrupt Edge Select                             |
|       FFF3h IENR1   Interrupt Enable 1                                |
|       FFF4h IENR2   Interrupt Enable 2                                |
|       FFF5h OSCCR   System Oscillator Control                         |
|       FFF6h IRR1    Interrupt Flag 1                                  |
|       FFF7h IRR2    Interrupt Flag 2                                  |
|       FFFAh CKSTPR1 Clock Stop 1                                      |
|       FFFBh CKSTPR2 Clock Stop 2                                      |
+-----------------------------------------------------------------------+
```




