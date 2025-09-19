# DSi SDIO Memory and I/O Maps


### Function 0 - Common I/O Area (CIA)

```
+-----------------------------------------------------------------------------------+
|       0:00000h..000FFh  Card Common Control Registers (CCCR)                      |
|       0:00100h..001FFh  Function Basic Registers (FBR) for Function 1             |
|       0:00200h..002FFh  Function Basic Registers (FBR) for Function 2             |
|       0:00300h..003FFh  Function Basic Registers (FBR) for Function 3             |
|       0:00400h..004FFh  Function Basic Registers (FBR) for Function 4             |
|       0:00500h..005FFh  Function Basic Registers (FBR) for Function 5             |
|       0:00600h..006FFh  Function Basic Registers (FBR) for Function 6             |
|       0:00700h..007FFh  Function Basic Registers (FBR) for Function 7             |
|       0:00800h..00FFFh  Reserved for Future                                       |
|       0:01000h..17FFFh  Card Information Structures (Common CIS and Func 1-7 CIS) |
|       0:18000h..1FFFFh  Reserved for Future                                       |
+-----------------------------------------------------------------------------------+
```


### Function 1..7 - Function specific Register Space

```
+------------------------------------------------------------------------------+
|       n:00000h..1FFFFh  Registers (seven 128K spaces, one for each function) |
+------------------------------------------------------------------------------+
```


### Code Storage Area (CSA) (optional, R or R/W)

```
+----------------------------------------------------------------------------------+
|       CSA:00000h..FFFFFh  16Mbyte FAT12/FAT16 (accessed indirectly via "Window") |
+----------------------------------------------------------------------------------+
```


### Card Common Control Registers (CCCR)

```
+-----------------------------------------------------------------------+
|       0:00000h 2   CCCR: Revision (R)                                 |
|       0:00002h 2   CCCR: I/O Function Enable/Ready (R/W)              |
|       0:00004h 2   CCCR: Interrupt Enable/Pending (R/W)               |
|       0:00006h 1   CCCR: I/O Abort (W)                                |
|       0:00007h 1   CCCR: Bus Interface Control (R/W)                  |
|       0:00008h 1   CCCR: Card Capability                              |
|       0:00009h 3   CCCR: Common CIS Pointer, Lo/Mid/Hi                |
|       0:0000Ch 1   CCCR: Bus Suspend                                  |
|       0:0000Dh 1   CCCR: Function Select (R/W)                        |
|       0:0000Eh 2   CCCR: Exec/Ready Flags (R)                         |
|       0:00010h 2   CCCR: CMD53 Block Size for Function 0, Lo/Hi (R/W) |
|       0:00012h 1   CCCR: Power Control                                |
|       0:00013h 2   CCCR: Bus Speed Select                             |
|       0:00015h 1   CCCR: Driver Strength                              |
|       0:00016h 1   CCCR: Interrupt Extension                          |
|       0:00017h D9h CCCR: Reserved for Future                          |
|       0:000F0h 10h CCCR: Reserved for Vendors                         |
+-----------------------------------------------------------------------+
```


### Function Basic Registers (FBR) for Function n (n=1..7)

```
+------------------------------------------------------------------------------------+
|       0:00n00h 1    FBR(n): Misc                                                   |
|       0:00n01h 1    FBR(n): Extended standard SDIO Function interface code         |
|       0:00n02h 1    FBR(n): Misc                                                   |
|       0:00n02h 7    FBR(n): Reserved for Future                                    |
|       0:00n09h 3    FBR(n): Pointer to Card Information Structure (CIS), Lo/Mid/Hi |
|       0:00n0Ch 3    FBR(n): Code Storage Area (CSA) Address, Lo/Mid/Hi             |
|       0:00n0Fh 1    FBR(n): Code Storage Area (CSA) Data "Window"                  |
|       0:00n10h 2    FBR(n): CMD53 Block Size for Function n, Lo/Hi                 |
|       0:00n12h EEh  FBR(n): Reserved for Future                                    |
+------------------------------------------------------------------------------------+
```




