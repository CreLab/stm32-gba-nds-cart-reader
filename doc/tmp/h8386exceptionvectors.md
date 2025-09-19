# H8/386 Exception Vectors


### H8/386 Exception Vectors (Vector 0000h has highest priority, 004Eh lowest)
Below are for Normal Mode with 16bit addressing (Extended Mode has 32bit vectors at 0000h..009Fh accordingly).

```
+------------------------------------------------------------------------+
|       0000h Reset/Watchdog                                             |
|       0002h Reserved                                                   |
|       0004h Reserved                                                   |
|       0006h Reserved                                                   |
|       0008h Reserved                                                   |
|       000Ah Reserved                                                   |
|       000Ch Reserved                                                   |
|       000Eh External NMI interrupt                                     |
|       0010h Trap 0 opcode                                              |
|       0012h Trap 1 opcode                                              |
|       0014h Trap 2 opcode                                              |
|       0016h Trap 3 opcode                                              |
|       0018h Reserved                                                   |
|       001Ah CPU Direct transition by executing SLEEP                   |
|       001Ch Reserved                                                   |
|       001Eh Reserved                                                   |
|       0020h External IRQ0 interrupt                                    |
|       0022h External IRQ1 interrupt                                    |
|       0024h External IRQAEC interrupt                                  |
|       0026h Reserved                                                   |
|       0028h Reserved                                                   |
|       002Ah Comparator COMP0                                           |
|       002Ch Comparator COMP1                                           |
|       002Eh RTC per 0.25 seconds (4Hz)  ;0.25-second overflow          |
|       0030h RTC per 0.5 seconds (2Hz)   ;0.5-second overflow           |
|       0032h RTC per second (1Hz)        ;Second periodic overflow      |
|       0034h RTC per minute              ;Minute periodic overflow      |
|       0036h RTC per hour                ;Hour periodic overflow        |
|       0038h RTC per day                 ;Day-of-week periodic overflow |
|       003Ah RTC per week (7 days)       ;Week periodic overflow        |
|       003Ch RTC Free-running overflow                                  |
|       003Eh WDT overflow (interval timer)                              |
|       0040h Asynchronous event counter overflow                        |
|       0042h Timer B1 Overflow                                          |
|       0044h Serial SPI (or IIC2) (aka I2C ?)                           |
|       0046h Timer W Overflow or Capture/compare A,B,C,D                |
|       0048h Reserved                                                   |
|       004Ah IrDA UART Serial 3                                         |
|       004Ch A/D Conversion end                                         |
|       004Eh Reserved                                                   |
+------------------------------------------------------------------------+
```

Note: The SSU (aka SPI) and IIC (aka I2C) share the same vector address. When using the IIC, shift the SSU to standby mode using CKSTPR2.



