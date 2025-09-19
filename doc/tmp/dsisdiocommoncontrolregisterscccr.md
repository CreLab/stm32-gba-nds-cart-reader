# DSi SDIO Common Control Registers (CCCR)


### 0:00000h - CCCR: Revision (R)

```
+-----------------------------------------------------------------------------------+
|       0-3   CCCR/FBR Format Version      (0=v1.00, 1=v1.10, 2=v2.00, 3=v3.00) (R) |
|       4-7   SDIO Spec Version   (0=v1.00, 1=v1.10, 2=v1.20, 3=v2.00, 4=v3.00) (R) |
|       8-11  SD Physical Layer Spec       (0=v1.01, 1=v1.10, 2=v2.00, 3=v3.0x) (R) |
|       12-15 Reserved for Future                                               (-) |
+-----------------------------------------------------------------------------------+
```


### 0:00002h - CCCR: I/O Function Enable/Ready (R/W)

```
+-------------------------------------------------------------------------------------+
|       0     Reserved for Future                                               (-)   |
|       1-7   SDIO Function 1..7 Enable Flags             (0=Disable, 1=Enable) (R/W) |
|       8     Reserved for Future                                               (-)   |
|       9-15  SDIO Function 1..7 Ready Flags         (0=Disabled/Busy, 1=Ready) (R)   |
+-------------------------------------------------------------------------------------+
```


### 0:00004h - CCCR: Interrupt Enable/Pending (R/W)

```
+-------------------------------------------------------------------------------------+
|       0     SDIO Interrupt Master Enable                (0=Disable, 1=Enable) (R/W) |
|       1-7   SDIO Function 1..7 Interrupt Enable         (0=Disable, 1=Enable) (R/W) |
|       8     Reserved for Future                                               (-)   |
|       9-15  SDIO Function 1..7 Interrupt Pending                (0=No, 1=IRQ) (R)   |
+-------------------------------------------------------------------------------------+
```


### 0:00006h - CCCR: I/O Abort (W)

```
+-----------------------------------------------------------------------------------+
|       0-2   SDIO Function Number to be Aborted  (0=None?, 1..7=Function 1..7) (W) |
|                 XXXsee pg 35                                                      |
|       3     Reset SDIO Card                               (0=Normal, 1=Reset) (W) |
|       4-7   Reserved for Future                                               (-) |
+-----------------------------------------------------------------------------------+
```


### 0:00007h - CCCR: Bus Interface Control (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-1   Bus Width       (0=1bit, 1=Reserved, 2=4bit, 3=EmbeddedSDIO/8bit) (R/W) |
|       2     Support 8bit Bus Flag             (0=No, 1=Yes/EmbeddedSDIO only) (R)   |
|       3-4   Reserved for Future                                               (-)   |
|       5     Enable Continous SPI Interrupt              (0=Disable, 1=Enable) (R/W) |
|       6     Support Continous SPI Interrupt                     (0=No, 1=Yes) (R)   |
|       7     Card Detect Disable     (0=Enable Pull-up on DAT3 pin, 1=Disable) (R/W) |
+-------------------------------------------------------------------------------------+
```


### 0:00008h - CCCR: Card Capability

```
+-------------------------------------------------------------------------------------+
|       0     Support Direct Command (CMD52) during Data Transfer (0=No, 1=Yes) (R)   |
|       1     Support Multi-Block transfer (CMD53.block mode)     (0=No, 1=Yes) (R)   |
|       2     Support Read Wait Control (RWC via DAT2 pin)        (0=No, 1=Yes) (R)   |
|       3     Support Bus Control Suspend/Resume                  (0=No, 1=Yes) (R)   |
|       4     Support Block Gap Interrupt during Multi-Block      (0=No, 1=Yes) (R)   |
|       5     Enable Block Gap Interrupt during Multi-Block    (0=No, 1=Enable) (R/W) |
|       6     Low Speed Card                        (0=Full-Speed, 1=Low-Speed) (R)   |
|       7     Support 4bit Mode for Low-Speed Card                (0=No, 1=Yes) (R)   |
+-------------------------------------------------------------------------------------+
```


### 0:00009h - CCCR: Common CIS Pointer, Lo
### 0:0000Ah - CCCR: Common CIS Pointer, Mid
### 0:0000Bh - CCCR: Common CIS Pointer, Hi

```
+-----------------------------------------------------------------------------------+
|       0-16  Pointer to Card Common Card Information Structure (Common CIS)    (R) |
|       17-23 Unspecified (probably reserved)                                   (-) |
+-----------------------------------------------------------------------------------+
```


### 0:0000Ch - CCCR: Bus Suspend

```
+-----------------------------------------------------------------------------------+
|       0     Bus Status              XXX see pg 37                             (R) |
|       1     Bus Release Request     XXX see pg 38                             (R) |
|       2-7   Reserved for Future                                               (-) |
+-----------------------------------------------------------------------------------+
```


### 0:0000Dh - CCCR: Function Select (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-3   Select Function (0=CIA, 1..7=Function 1..7, 8=Memory Card)        (R/W) |
|       4-6   Reserved for Future                                               (-)   |
|       7     Data Flag (more data after resuming) (0=No, 1=Yes)                (R)   |
+-------------------------------------------------------------------------------------+
```


### 0:0000Eh - CCCR: Exec/Ready Flags (R)

```
+-----------------------------------------------------------------------------------+
|       0     Command Execution Flag for Memory (=SD/Combo? or CSA?)            (R) |
|       1-7   Command Execution Flags for Function 1..7       (0=Busy, 1=Ready) (R) |
|       8     Read/Write Ready Flag for Memory (=SD/Combo? or CSA?)             (R) |
|       9-15  Read/Write Ready Flags for Function 1..7        (0=Busy, 1=Ready) (R) |
+-----------------------------------------------------------------------------------+
```


### 0:00010h - CCCR: CMD53 Block Size for Function 0, Lo (R/W)
### 0:00011h - CCCR: CMD53 Block Size for Function 0, Hi (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-15  CMD53 Block size for Function(0)          (0001h..0800h) (0=None) (R/W) |
+-------------------------------------------------------------------------------------+
```


### 0:00012h - CCCR: Power Control

```
+-------------------------------------------------------------------------------------+
|       0     Support Master Power Control                        (0=No, 1=Yes) (R)   |
|       1     Enable Master Power Control    (0=No/max 720mW, 1=Yes/allow more) (R/W) |
|       2-7   Reserved for Future                                               (-)   |
+-------------------------------------------------------------------------------------+
```


### 0:00013h,00014h - CCCR: Bus Speed Select

```
+-------------------------------------------------------------------------------------+
|       0     Support High-Speed Mode (SDR25 or higher)           (0=No, 1=Yes) (R)   |
|       1-3   Bus Speed Select   (0=SDR12, 1=SDR25, 2=SDR50, 3=SDR104, 4=DDR50) (R/W) |
|       4-7   Reserved for Future                                               (-)   |
|       8     Support UHS-I SDR50  (usable in 1.8V mode only)     (0=No, 1=Yes) (R)   |
|       9     Support UHS-I SDR104 (usable in 1.8V mode only)     (0=No, 1=Yes) (R)   |
|       10    Support UHS-I DDR50  (usable in 1.8V mode only)     (0=No, 1=Yes) (R)   |
|       11-15 Reserved for Future                                                     |
+-------------------------------------------------------------------------------------+
```


### 0:00015h - CCCR: Driver Strength

```
+-------------------------------------------------------------------------------------+
|       0     Support Driver Type A ;\see Physical Layer Specs    (0=No, 1=Yes) (R)   
|       1     Support Driver Type C ; version 3.0x for details    (0=No, 1=Yes) (R)   |
|       2     Support Driver Type D ;/                            (0=No, 1=Yes) (R)   |
|       3     Reserved for Future                                               (-)   |
|       5-4   Driver Type Select    (0=Default/B, 1=Type A, 2=Type C, 3=Type D) (R/W) |
|       7-6   Reserved for Future                                               (-)   |
+-------------------------------------------------------------------------------------+
```


### 0:00016h - CCCR: Interrupt Extension

```
+-------------------------------------------------------------------------------------+
|       0     Support Asynchronous Interrupt in 4bit mode         (0=No, 1=Yes) (R)   |
|       1     Enable Asynchronous Interrupt in 4bit mode       (0=No, 1=Enable) (R/W) |
|       7-2   Reserved for Future                                               (-)   |
+-------------------------------------------------------------------------------------+
```




