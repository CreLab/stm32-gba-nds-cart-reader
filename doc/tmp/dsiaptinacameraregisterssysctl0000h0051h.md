# DSi Aptina Camera Registers: SYSCTL (0000h-0051h)


### SYSCTL (0000h-0051h)

```
+------------------------------------------------------------------------------------+
|       0000h   2  CHIP_VERSION_REG       Model ID (2280h=MT9V113 on DSi/3DS) (R)    |
|       0006h  ..  RESERVED_SYSCTL_06     Reserved                                   |
|       0010h   2  PLL_DIVIDERS           PLL Dividers (def=0366h)                   |
|                    0-7   PLL M-Divider value (uh, actually a Multiplier?!)         |
|                    8-13  PLL N-Divider value                                       |
|                    14-15 Unused (0)                                                |
|                  Because the input clock frequency is unknown, the sensor starts   |
|                  up with the PLL disabled. The PLL takes time to power up. During  |
|                  this time, the behavior of its output clock signal is not         |
|                  guaranteed. The PLL output frequency is determined by two         |
|                  constants, M and N, and the input clock frequency.                |
|                    VCO = Fin * 2 * M / (N+1)                                       |
|                    PLL_output_frequency = VCO / (P1+1)                             |
|                  The PLL can generate a master clock signal whose frequency is up  |
|                  to 85 MHz (input clock from 6 MHz through 54 MHz).                |
|       0012h   2  PLL_P_DIVIDERS         PLL P Dividers (def=00F5h)                 |
|                    0-3   P1 (00h..0Fh)                                             |
|                    4-7   Unspecified                                               |
|                    8-11  P3 (00h..0Fh)                                             |
|                    12-13 Division ratio of word clock/clockn from bit_clock (0..3) |
|                    14    Unused (0)                                                |
|                    15    Unspecified                                               |
|       0014h   2  PLL_CONTROL            PLL Control (def=21F9h)                    |
|                    0     PLL Bypass                                                |
|                    1     PLL Enable                                                |
|                    2-3   Reserved (0..3)                                           |
|                    4-7   Reserved (0..0Fh)                                         |
|                    8     Reset_cntr                                                |
|                    9     Reserved                                                  |
|                    10    Reserved                                                  |
|                    11    Reserved                                                  |
|                    12    Reserved                                                  |
|                    13    Reserved                                                  |
|                    14    Unused (0)                                                |
|                    15    PLL Lock (R)                                              |
|       0016h   2  CLOCKS_CONTROL         Clocks Control                             |
|                    0     Reserved                                                  |
|                    1     Reserved                                                  |
|                    2     Reserved                                                  |
|                    3     Reserved                                                  |
|                    4     Reserved                                                  |
|                    5     Reserved/UNDOC/USED (manipulated by DSi)                  |
|                    6     Reserved                                                  |
|                    7     Reserved                                                  |
|                    8     Reserved                                                  |
|                    9     clk_clkin_en                                              |
|                    11-12 Reserved                                                  |
|                    13    Reserved                                                  |
|                    15    Reserved                                                  |
|       0018h   2  STANDBY_CONTROL        Standby Control and Status (def=4029h)     |
|                    0     Ship (uh?) (0=Enable various regs, 1=Standby)             |
|                    1     Reserved                                                  |
|                    2     Stop MCU                                                  |
|                    3     en_IRQ                                                    |
|                    4     Reserved                                                  |
|                    5     Reserved                                                  |
|                    6-13  Unused (0)                                                |
|                    14    Standby_done (0=WakeupDone, 1=StandbyDone) (R?)           |
|                            (takes MUCH time?)                                      |
|                    15    Reserved (R)                                              |
|       001Ah   2  RESET_AND_MISC_CONTROL Reset and Control (def=0050h) (0-0333h)    |
|                    0     Reset SOC I2C                                             |
|                    1     MIPI_TX_Reset                                             |
|                    2     Unused (0)                                                |
|                    3     MIPI_TX_en       (=Serial Data?)                          |
|                    4     IP_PD_en         (=Parallel Data or what?)                |
|                    5     Reserved                                                  |
|                    6     Sensor_full_res                                           |
|                    7     Unused (0)                                                |
|                    8     OE_N_Enable                                               |
|                    9     Parallel_enable  (=Parallel Data?)                        |
|                    10    Unused (0)                                                |
|                    11    Reserved                                                  |
|                    12-15 Unused (0)                                                |
|       001Ch   2  MCU_BOOT_MODE          MCU Boot Mode                              |
|                    0     Reset MCU                                                 |
|                    1     Reserved                                                  |
|                    2     Reserved                                                  |
|                    3     Reserved                                                  |
|                    4-7   Reserved  (0..0Fh)                                        |
|                    8-15  Reserved  (0..FFh) (R)                                    |
|       001Eh   2  PAD_SLEW               Pad Slew Control (def=0400h)               |
|                    0-2   Parallel Data Output Slew Rate Control (0-7)              |
|                    3     Unused (0)                                                |
|                    4-6   GPIO Slew Rate Control (0-7)                              |
|                    7     Unused (0)                                                |
|                    8-10  PCLK aka PXLCLK Slew Rate Control (0-7)                   |
|                    11-15 Unused (0)                                                |
|       0020h  ..  RESERVED_SYSCTL_20     Reserved                                   |
|       0022h   2  VDD_DIS_COUNTER        VDD_DIS_COUNTER (0..FFFFh, def=0438h)      |
|       0024h   2  GPI_STATUS             GPI_STATUS      (0..000Fh) (R)             |
|       0026h  ..  RESERVED_SYSCTL_26     Reserved                                   |
|       0028h   2  EN_VDD_DIS_SOFT        EN_VDD_DIS_SOFT (0..0001h, def=0001h)      |
|       0050h  ..  RESERVED_SYSCTL_50     Reserved                                   |
+------------------------------------------------------------------------------------+
```




