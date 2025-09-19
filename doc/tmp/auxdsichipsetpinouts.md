# AUX DSi Chipset Pinouts


A photo of the DSi mainboard (with extra text layer on vias and solderpads) can be found at:

```
+-----------------------------------------------------------------------+
|       http://problemkaputt.de/twl-core.jpg                            |
+-----------------------------------------------------------------------+
```


### DSi U1 - TWL-CPU (19x19 pin grid) (352 pins, aka 19x19 minus middle 3x3 pins)

```
+-------------------------------------------------------------------------------------+
|           Wifi    MC2 maybe      MC1           SD/MMC  eMMC  SPI     RTC   IRQs     |
|       .---.---.---------------.---------------.-------.---.-------.-------.---.---. |
|       |NC |CSB|NC  NC  NC  NC |D7  D3  IRQ CLK|D0  CLK|CLK|CS3 SCK|CS  SCK|R7 |NC | |
|       +---'   |               |               |       |   |       |   .---'   '---+ |
```
|       |SDI CSR|NC  NC  NC  NC |D6  D2  DET CS |D1  CMD|D0 |CS2 MIS|SIO|PEN NC  WIF| |
```
|       |       |               |               |       |   |       +---+---.   .---+ |
|       |SCK SDO|NC  NC  NC  NC |D5  D1  PWR CS2|D2  CD |D1 |CS1 MOS|R00 R01|RTC|P09| |
|       |       '---.       .---+           .---'   .---'   '---.---+       '---'   | |
|       |TCK TDA RDY|NC  NC |V33|D4  D0  RES|D3  WP |D3  D2  CMD| ? |P08 P07 P06 P05| |
|       |           '---+---'   '-----------'-------'-----------'---+               | |
```
|       |MCK CCA RXP TXP|GND V12 V33 GND V12 V33 G?  V12 V33 GND V33|P04 P03 P02 P01| |
```
|       | . .           |                                           +-----------.   | |
|       |DT3|SLR SLB ?  |GND V33 V12 GND GND GND V33 G?  GND V33 V12| ?  RES NC |P00| |
|       |   '. . . . . .|                                           |           '---+ |
|       |CLK DT2 DT1 DT0|V33 GND V12 V33 GND V12 G?  V12 GND GND V33|PMO VC5 PMS X  | |
|       +-----------.   |                                           '-----------.   | |
```
|       |V33 NC  GND|CMD|V12 GND V33 GND V12 V33 GND V33 V12 V12 V33 GND GND GND|X  | |
|       |           '---'               .-----------.               .-----------'   | |
|       |V33 NC  V33 V33 GND V33 GND V33|-   -   -  |GND GND GND GND|HP# IRQ mut GND| |
```
|       +---.   .---.                   |           |               |               | |
|       |B15|V33|NC |V33 V12 GND V12 V12|-   -   -  |V12 V18 GND V12|NC  NC  NC  GP | |
|       |   '---'---'---.               |           |               +---------------+ |
```
|       |B14 B13 B12 B11|V33 GND V33 GND|-   -   -  |V18 GND V18 GND|A1  D1  A0  D0 | |
|       |               |               '-----------'               |               | |
|       |B10 G15 G14 G13|GND V33 V12 GND V18 V12 V18 GND V18 V12 V18|A3  D3  A2  D2 | |
|       |               |                                           |               | |
|       |G12 G11 G10 R15|V33 V12 GND V12 GND V18 GND V12 GND V18 GND|A5  D5  A4  D4 | |
|       |               |                                           |               | |
|       |R14 R13 R12 R11|GND V33 V18 GND V18 V12 V18 GND V18 V12 V18|A7  D7  A6  D6 | |
```
|       +-----------.   |                                           |               | |
|       |DCK GSP SPL|R10|V33 V12 GND V18 GND V18 GND V12 GND V18 GND|A9  D9  A8  D8 | |
|       |       .---'---'-------.-------.---.---.-------.-----------'               | |
|       |LS  REV|B22 G24 G20 R22|D7  D3 |NC |RST|SCK WS |CE1 /OE A20 A11 D11 A10 D10| |
|       |   .---'               |       |   |   |       |                           | |
|       |GCK|B25 B21 G23 R25 R21|D6  D2 |NC |VSY|MCK SDO|NC  CE2 A19 A13 D13 A12 D12| |
|       |   |                   |       |   |   +---.   |                           | |
```
|       |INI|B24 B20 G22 R24 R20|D5  D1 |NC |HSY|SDA|SDI|/LB CLK A18 A21 A14 D15 D14| |
```
|       +---+               .---+       '---'   |   +---'                       .---+ |
|       |NC |B23 G25 G21 R23|NC |D4  D0  CKI RCK|SCL|/UB ADV /WE A15 A17 A22 A16|NC | |
|       '---'---------------'---'---------------'---'---------------------------'---' |
|               LCD                  CAM         I2C SND          RAM               o |
+-------------------------------------------------------------------------------------+
```


### DSi U2 - Main RAM (8Mx16) (Fujitsu MB82DBS08164, or NEC uPD46128512)
DSi mainboard solder pads (12x8 grid, within 14x10 grid):

```
+-------------------------------------------------------------------------------+
|            A    B    C    D    E    F    G    H    J    K    L    M    N    P |
|       10   -    -    -    -    -    -    -    -    -    -    -    -    -    - |
|       9    -    NC   NC   -    A15  A21  A22  A16  NC   VSS  -    NC   NC   - |
|       8    -    NC   NC   A11  A12  A13  A14  NC   DQ15 DQ7  DQ14 NC   NC   - |
|       7    -    -    -    A8   A19  A9   A10  DQ6  DQ13 DQ12 DQ5  -    -    - |
|       6    -    -    -    /WE  CE2  A20  -    -    DQ4  VDD  NC   -    -    - |
|       5    -    -    -    CLK  /ADV (W)  -    -    DQ3  VDD  DQ11 -    -    - |
|       4    -    -    -    /LB  /UB  A18  A17  DQ1  DQ9  DQ10 DQ2  -    -    - |
|       3    -    NC   -    A7   A6   A5   A4   VSS  /OE  DQ0  DQ8  NC   NC   - |
|       2    -    NC   NC   -    A3   A2   A1   A0   NC   /CE1 -    NC   NC   - |
|       1 o  -    -    -    -    -    -    -    -    -    -    -    -    -    - |
+-------------------------------------------------------------------------------+
```

DSi RAM - Fujitsu MB82DBS08164 (14x10 grid):

```
+--------------------------------------------------------------------------------+
|            A    B    C    D    E    F    G    H    J    K    L    M    N    P  |
|       10   NC   NC   NC   NC   NC   NC   VDD  VSS  NC   NC   NC   NC   NC   NC |
|       9    NC   NC   NC   NC   A15  A21  A22  A16  NC   VSS  NC   NC   NC   NC |
|       8    -    -    NC   A11  A12  A13  A14  NC   DQ15 DQ7  DQ14 NC   -    -  |
|       7    -    -    NC   A8   A19  A9   A10  DQ6  DQ13 DQ12 DQ5  NC   -    -  |
|       6    -    -    NC   /WE  CE2  A20  NC   NC   DQ4  VDD  NC   NC   -    -  |
|       5    -    -    NC   CLK  /ADV /WAI NC   VDD  DQ3  VDD  DQ11 VDD  -    -  |
|       4    -    -    NC   /LB  /UB  A18  A17  DQ1  DQ9  DQ10 DQ2  VSS  -    -  |
|       3    -    -    VSS  A7   A6   A5   A4   VSS  /OE  DQ0  DQ8  NC   -    -  |
|       2    NC   NC   NC   NC   A3   A2   A1   A0   NC   /CE1 NC   NC   NC   NC |
|       1 o  NC   NC   -    NC   NC   NC   VDD  VSS  NC   NC   NC   NC   NC   NC |
+--------------------------------------------------------------------------------+
```

DSi RAM - NEC uPD46128512 (14x10 grid):

```
+--------------------------------------------------------------------------------+
|            A    B    C    D    E    F    G    H    J    K    L    M    N    P  |
|       10   NC   NC   NC   -    -    -    NC   NC   -    -    -    NC   NC   NC |
|       9    -    NC   NC   -    A15  A21  A22  A16  NC   VSS  -    NC   NC   -  |
|       8    -    -    NC   A11  A12  A13  A14  NC   DQ15 DQ7  DQ14 NC   -    -  |
|       7    -    -    -    A8   A19  A9   A10  DQ6  DQ13 DQ12 DQ5  -    -    -  |
|       6    -    -    NC   /WE  CE2  A20  NC   NC   DQ4  VCC  NC   NC   -    -  |
|       5    -    -    NC   CLK  /ADV /WAI NC   NC   DQ3  VCC  DQ11 NC   -    -  |
|       4    -    -    -    /LB  /UB  A18  A17  DQ1  DQ9  DQ10 DQ2  -    -    -  |
|       3    -    -    NC   A7   A6   A5   A4   GND  /OE  DQ0  DQ8  NC   -    -  |
|       2    -    NC   NC   NC   A3   A2   A1   A0   NC   /CE1 -    NC   NC   -  |
|       1 o  NC   NC   NC   -    -    -    NC   NC   -    -    -    NC   NC   NC |
+--------------------------------------------------------------------------------+
```

The Fujitsu & NEC datasheets are specifing 14x10 grid (the chips are essentially pin-compatible, except that: NEC has removed some NC pins, changed some supply pins to NC, and (attempted to) rename VSS to GND).
However, the DSi mainboard has 12x8 grid solder pads (and the installed NEC/Fujitsu chip/packages are actually only 12x8, too).
The DSi debug version is said to have 32Mbyte RAM, there is no provision for that feature on DSi retail boards; dev boards are probably somewhere having an extra address line (or an extra chip select for a 2nd RAM chip).

### DSi U3 - Power Managment (Texas Instruments 72071B0, or Mitsumi 3317A)

```
+---------------------------------------------------------------------------+
|       1   GND (via CL9)                                                   |
|       2   ADPO                                                            |
|       3   EXTB+                                                           |
|       4   VDD33                                                           |
|       5   RESET         ;\                                                
|       6   SPI_SCK       ; main cpu bus                                    |
|       7   SPI_MOSI      ; (reset and spi)                                 |
|       8   SPI_MISO      ;                                                 |
|       9   SPI_CS1       ;/  <-- powerman (this does ALSO connect to U4)   |
|       10  GND                                                             |
|       11  PMOFF                                                           |
|       12  PWSWO                                                           |
|       13  VCNT5                                                           |
|       14  PM_SLP                                                          |
|       ---                                                                 |
|       15  B+                                                              |
|       16  VDD12 via L1                                                    |
|       17  VDD12                                                           |
|       18  GND                                                             |
|       19  BLC1          ;\                                                
|       20  BLA1 via U13  ; backlight 1+2                                   |
|       21  BLA2 via U14  ; anode/cathode                                   |
|       22  BLC2          ;/                                                |
|       23  GND                                                             |
|       24  B+                                                              |
|       25  B+                                                              |
|       26  VDD18 via L2                                                    |
|       27  VDD18 via L2                                                    |
|       28  VDD18                                                           |
|       ---                                                                 |
|       29  DET     ;\battery contacts                                      
|       30  BT+     ;/    ;\these are almost shortcut                       
|       31  VDET-         ;/with each other (via 0 ohm R71)                 |
|       32  PVDD                                                            |
|       33  PWSW (when off: very few ohms to PVDD ???)                      |
|       34        ... via R104 (100K) to Q3 (B+ enable or so?)              |
|       35  B+                                                              |
|       36        ... via to C18 to GND (seems to have no other connection) |
|       37  GND                                                             |
|       38  AOUT  ;\to U6                                                   
|       39  GND   ;                                                         |
|       40  SCL1  ;   ;\secondary IC2 bus (to U6)                           
|       41  SDA1  ;/  ;/                                                    |
|       42  VDD33                                                           |
|       ---                                                                 |
|       43  GND via CL10                                                    |
|       44  VDD5 input (sense if VDD5/C16 has reached voltage)              |
|       45  charge-pump for VDD5 (L7 and via DA3 to VDD5/C16)               |
|       46  charge-pump for VDD5 (L5 and C14)                               |
|       47  VDD33 (via CL5)                                                 |
|       48  VDD33 (via L3)                                                  |
|       49  VDD33                                                           |
|       50  VDD33                                                           |
|       51  B+                                                              |
|       52  B+                                                              |
|       53  B+                                                              |
|       54  charge-pump for VDD42 (L7 and C23)                              |
|       55  charge-pump for VDD42 (L7 and via D3 to VDD42/C22)              |
|       56  VDD42 input (sense if VDD42/C22 has reached voltage)            |
+---------------------------------------------------------------------------+
```


### DSi U4 - Sound and Touchscreen controller (AIC3000D)
AIC3000D pinout is same as in TSC2117 datasheet (aside from GPIx/GPIOx pins).

```
+---------------------------------------------------------------------------------+
|       Pin TSC2117 AIC3000D                                                      |
|       1   MISO    SPI_MISO                                                      |
|       2   MOSI    SPI_MOSI                                                      |
|       3   /SS     SPI_CS1 (powerman, this does ALSO connect to U3)              |
|       4   SCLK    SPI_SCLK                                                      |
|       5   GPIO1   SPI_CS3 (touchscreen)                                         |
|       6   GPIO2   PENIRQ                                                        |
|       7   IOVSS   GND                                                           |
|       8   IOVDD   VDD33                                                         |
|       9   DVDD    VDD18                                                         |
|       10  SDOUT   SND_SDI              ;\                                       
|       11  SDIN    SND_SDO              ;                                        |
|       12  WCLK    SND_WS               ; serial sound input from main cpu       |
|       ---                              ; (and serial output? microphone maybe?) |
|       13  BCLK    SND_SCLK             ;                                        |
|       14  MCLK    SND_MCLK             ;/                                       |
|       15  SDA       ... via R107 to VDD18  ;\unused I2C bus (?)                 
|       16  SCL       ... via R106 to VDD18  ;/                                   |
|       17  VOL/M   wiper (sound volume, from I2C potentiometer) "VOL/MICDET?"    |
|       18  MICBIAS micbias (to U18)                  ;\                          
|       19  MIC     LIN (to U18) (and to MIC via C31) ; microphone related        |
|       20  AUX1    aux  ;\via 0ohm R108 to U18       ;                           
|       21  AUX2    aux  ;/(that is almost GND)       ;/                          |
|       22  AVSS    GND                                                           |
|       23  AVDD    VDD33                                                         |
|       24  VBAT    GND                                                           |
|       ---                                                                       |
|       25  VREF    VDD33                                                         |
|       26  TSVSS   GND                                                           |
|       27  YN      Y-                   ;\                                       
|       28  XN      X-                   ;                                        |
|       29  DVSS    GND                  ; touchscreen input                      |
|       30  YP      Y+                   ;                                        |
|       31  XP      X+                   ;/                                       |
|       32  TSVDD   VDD33                                                         |
|       33  SPLN    SPLN                 ;\                                       
|       34  SLVSS   GND                  ;                                        |
|       35  SLVDD   B+                   ; speaker output                         |
|       36  SPLP    SPLP                 ;                                        |
|       ---                              ;                                        |
|       37  SPRN    SPRN                 ;                                        |
|       38  SRVDD   B+                   ;                                        |
|       39  SRVSS   GND                  ;                                        |
|       40  SPRP    SPRP                 ;/                                       |
|       41  HPL     SL via CP2 and R88      ;\                                    
|       42  HVDD    VDD33                   ;                                     |
|       43  HVSS    GND                     ; headphone output                    |
|       44  HPR     SR via CP3 and R89      ;                                     |
|       45  GPI3    MUTE via Q4/Q5 to SR/SL ;                                     |
|       46  GPI2    HP#SP switch            ;/                                    |
|       47  GPI1    VCNT5                                                         |
|       48  /RESET  RESET                                                         |
+---------------------------------------------------------------------------------+
```


### DSi U5 - 256Mbyte eMMC NAND (14x14 grid)

```
+--------------------------------------------------------------------------------+
|            1    2    3    4    5    6    7    8    9    10   11   12   13   14 |
|       o A  NC   NC   DAT0 DAT1 DAT2 NC   NC   NC   NC   NC   NC   NC   NC   NC |
|         B  NC   DAT3 DAT4 DAT5 DAT6 DAT7 NC   NC   NC   NC   NC   NC   NC   NC |
|         C  NC   VDDI NC   VSSQ NC   VCCQ NC   NC   NC   NC   NC   NC   NC   NC |
|         D  NC   NC   NC   NC   -    -    -    -    -    -    -    NC   NC   NC |
|         E  NC   NC   NC   -    NC   VCC  VSS  NC   NC   NC   -    NC   NC   NC |
|         F  NC   NC   NC   -    VCC  -    -    -    -    NC   -    NC   NC   NC |
|         G  NC   NC   NC   -    VSS  -    -    -    -    NC   -    NC   NC   NC |
|         H  NC   NC   NC   -    NC   -    -    -    -    VSS  -    NC   NC   NC |
|         J  NC   NC   NC   -    NC   -    -    -    -    VCC  -    NC   NC   NC |
|         K  NC   NC   NC   -    NC   NC   NC   VSS  VCC  NC   -    NC   NC   NC |
|         L  NC   NC   NC   -    -    -    -    -    -    -    -    NC   NC   NC |
|         M  NC   NC   NC   VCCQ CMD  CLK  NC   NC   NC   NC   NC   NC   NC   NC |
|         N  NC   VSSQ NC   VCCQ VSSQ NC   NC   NC   NC   NC   NC   NC   NC   NC |
|         P  NC   NC   VCCQ VSSQ VCCQ VSSQ NC   NC   NC   NC   NC   NC   NC   NC |
+--------------------------------------------------------------------------------+
```

Note: The pinout follows JEDEC\'s eMMC standard. The \"NC\" pins are GNDed in DSi, the \"DAT4..DAT7\" pins are not connected in DSi. The \"VDDI\" pin isn\'t wired to VDD, instead it goes to a capacitor (0.1uF min) \"for internal power stability\".

### DSi U6 - \"BPTWL\" - I2C bus(ses), LEDs, volume, power, wifi (6x6 grid)

```
+-----------------------------------------------------------------------------------+
|            1           2           3            4           5           6         |
|       o A  GND         WL_TXPE     P02 button   SDA'33      ADPO        GND       |
|         B  ATH_TX_H    BLUE(LED)   RED(LED)     SCL'33      V33         GND       |
|         C  YELLOW(LED) VOLP button VOLN button  PM_SLP      V33'        /WIFI_RST |
|         D  SDA1        RESET       SCL1         to C46      GND         PMOFF     |
|         E  VDD28       GND         CAM_LED      PWSWO       mFE         /mRST     |
|         F  GND         AOUT        mFE'(R79)    WL_RXPE     /IRQ_O      GND       |
+-----------------------------------------------------------------------------------+
```

Aka from 78K0/KB2 datasheet\...

```
+------------------------------------------------------------------------------------+
|            1           2           3            4           5           6          |
|       o A  NC          P32/INT3    P30/INT1     P61/SDA     P33/INT4/T  NC         |
|         B  P31/INT2    P16/INT5/T  P15/TOH0     P60/SCL0    EVDD        EVSS       |
|         C  P17/T'50    P14/RxD6    P13/TxD6     P00/TI000   VDD         P121/X1    |
|         D  P11/SI10/Rx P12/SO10    P10/SCK10/Tx REGC        VSS      P122/X2/EXCLK |
|         E  AVREF       AVSS        P22/ANI2     P21/ANI1    FLMD0       RESET      |
|         F  NC          P23/ANI3    P20/ANI0  P01/TI010/TO00 P120/INT0/EXLVI  NC    |
+------------------------------------------------------------------------------------+
```


### DSi U7 - I2C bus potentiometer (ISL95810) (Device 50h)

```
+-----------------------------------------------------------------------+
|       1  /WP (DSi: VDD33)  writeprotect                               |
|       2  SCL (DSi: SCL1)   i2c bus   ;\from U6                        
|       3  SDA (DSi: SDA1)   i2c bus   ;/                               |
|       4  GND (DSi: GND)    ground                                     |
|       5  RW  (DSi: wiper)  pot.wiper ;-to U4                          |
|       6  RL  (DSi: VDD18)  pot.L                                      |
|       7  RH  (DSi: GND)    pot.H                                      |
|       8  VCC (DSi: VDD33)  supply                                     |
+-----------------------------------------------------------------------+
```


### DSi U8 - bidirectional I2C voltage translator (PCA9306)

```
+-----------------------------------------------------------------------+
|       1  GND   (DSi: GND)                                             |
|       2  VREF1 (DSi: VDD18)                                           |
|       3  SCL1  (DSi: SCL)     ;\to U1 (CPU)                           
|       4  SDA1  (DSi: SDA)     ;/                                      |
|       5  SDA2  (DSi: SDA'33)  ;\to U6 (BPTWL)                         
|       6  SCL2  (DSi: SCL'33)  ;/                                      |
|       7  VREF2 (DSi: VDD33)                                           |
|       8  EN    (DSi: VDD33)                                           |
+-----------------------------------------------------------------------+
```


### DSi U9 - RTC - Seiko S-35199A01 (4x3 grid)

```
+-----------------------------------------------------------------------+
|            A    B    C    D                                           |
|       3    CS   /SCK VDD  F32K                                        |
|       2    SIO  CTRL /INT FOUT                                        |
|       1 o  VSS  XIN  XOUT VDDL                                        |
+-----------------------------------------------------------------------+
```


### DSi U10 - Magnet Sensor (for hinge, aka shell opened/closed)

```
+-----------------------------------------------------------------------+
|       1  VDD33                                                        |
|       2  R7 (HINGE)  ;to U1                                           |
|       3  GND                                                          |
|       4  GND                                                          |
+-----------------------------------------------------------------------+
```


### DSi U11 - Charge

```
+-----------------------------------------------------------------------+
|       1  EXTB+                                                        |
|       2  Rosc                                                         |
|       3  ORANGE (via R2)              ;-charge LED                    |
|       4  GND                                                          |
|       5  TH' (via R76 to TH)          ;\thermal sensor                
|       6  TH  (via R102 to DPAD board) ;/for battery?                  |
|       7  B+                                                           |
|       8  RICHG                                                        |
|       9  BT+                                                          |
|       10 BT+                                                          |
+-----------------------------------------------------------------------+
```

Note: Seems to resemble Mitsumi MM3358 datasheet.

### DSi U12 - 5pin, VDD33 to VDD28 converter? (near upper screen socket)

```
+-----------------------------------------------------------------------+
|       1  VDD28                                                        |
|       2  GND                                                          |
|       3  VDD33                                                        |
|       4  VDD33                                                        |
|       5  (no pin)                                                     |
|       6  ... to DA6/DA7                                               |
+-----------------------------------------------------------------------+
```


### DSi U13 - 5pin, Backlight 1 (Lower Screen), near power managment chip
### DSi U14 - 5pin, Backlight 2 (Upper Screen), near power managment chip

```
+-----------------------------------------------------------------------+
|       1  from U3 (wanted backlight pulse/level or so?)                |
|       2  GND                                                          |
|       3  B+                                                           |
|       4  BLA1/BLA2 backlight anode output                             |
|       5  (no pin)                                                     |
|       6  B+                                                           |
+-----------------------------------------------------------------------+
```


### DSi U15 - 4pin, near external power input

```
+-----------------------------------------------------------------------+
|       1  via R4 to C100,Q1 (controls Q1 for forwarding VIN to EXTB+)  |
|       2  VIN'' (from VIN via EM1 and F1)                              |
|       3  ?                                                            |
|       4  via C132,R14 to GND, and via D1 to VIN''                     |
+-----------------------------------------------------------------------+
```

VIN power-input related.

### DSi U16 - N/A
None such.

### DSi U17 - Headphone Mute logic, near headphone socket

```
+-----------------------------------------------------------------------+
|       1  mute (from main CPU GPIO)                                    |
|       2  GND                                                          |
|       3  PMOFF                                                        |
|       4  MUTE (to Q4/Q5/TSC)                                          |
|       5  VDD33                                                        |
|       6  ?                                                            |
+-----------------------------------------------------------------------+
```


### DSi U18 - Microphone Bias, near headphone socket (not always installed)

```
+-----------------------------------------------------------------------+
|       1  NC                                                           |
|       2  GND                                                          |
|       3  LIN (via C31/EM5 to MIC)                                     |
|       4  aux (via 0 ohm to TSC AUX1/AUX2)                             |
|       5  VDD33                                                        |
|       6  micbias (from TSC micbias)                                   |
+-----------------------------------------------------------------------+
```


### DSi U19 - 5pin, something near dpad socket

```
+-----------------------------------------------------------------------+
|       1  via D5/D6 from B+/VDD42                                      |
|       2  GND                                                          |
|       3  VCNT5                                                        |
|       4  ?                                                            |
|       5  (no pin)                                                     |
|       6  VSHD                                                         |
+-----------------------------------------------------------------------+
```

Note: Pin-numbering is unclear, here is no Pin 1 marker.

### DSi U20 - Whatever, DSi XL only (maybe magnet Sensor instead of U10?)

```
+-----------------------------------------------------------------------+
|       1  ?                                                            |
|       2  ?                                                            |
|       3  ?                                                            |
+-----------------------------------------------------------------------+
```


### DSi LEDs:

```
+-----------------------------------------------------------------------+
|       CAM_LED (via R68 and Q13) ;Camera LED    ;\                     
|       BLUE    (via R21 and Q11) ;Power On/Good ; from U6              |
|       YELLOW  (via R22 and Q12) ;Wifi LED      ;/                     |
|       RED     (via R20)         ;Power On/Low  ;-from U6 (or to U6 ?) |
|       ORANGE  (via R2)          ;Charge LED    ;-from U11             |
+-----------------------------------------------------------------------+
```


### MM3218 chip (same chip as in DS Lite) (on DSi Wifi Daughterboard)

```
+------------------------------------------------------------------------------------+
|       1  VDD18                                                                     |
|       2  GND                                                                       |
|       3  VDD18                                                                     |
|       4  Antenna signal                                                            |
|       5  Antenna shield                                                            |
|       6  VDD18                                                                     |
|       7  VDD18                                                                     |
|       8  GND                                                                       |
|       9  NC                                                                        |
|       10 GND                                                                       |
|       11 GND                                                                       |
|       12 GND                                                                       |
|       13 NC                                                                        |
|       14 /RESET                                                                    |
|       ---                                                                          |
|       15 CCA    ... to DSi mainboard connector pin 36                              |
|       16 WL_TXPE                                                                   |
|       17 WL_RXPE                                                                   |
|       18 TRRDY  ... to DSi mainboard connector pin 46 !!!                          |
|       19 TRDATA ... to DSi mainboard connector pin 40                              |
|       20 VDD33                                                                     |
|       21 TRCLK  ... to DSi mainboard connector pin 44                              |
|       22 GND                                                                       |
|       23 MCLK   ... via nearby big component ... to DSi mainboard connector pin 47 |
|       24 VDD18                                                                     |
|       25 NC                                                                        |
|       26 22MHz                                                                     |
|       27 22MHz'                                                                    |
|       28 ... to DSi mainboard connector pin 43 NC? (with cap to GND and via 0 ohm) |
|       ---                                                                          |
|       29 VDD33                                                                     |
|       30 via capacitor to VDD33                                                    |
|       31 via 1K2 + 120K to GND (aka via 121.2K to GND)                             |
|       32 VDD18                                                                     |
|       33 VDD18                                                                     |
|       34 BB_RF_SCLK   ... to DSi mainboard connector pin 41                        |
|       35 BB_RF_SDI    ... to DSi mainboard connector pin 39                        |
|       36 BB_RF_SDO    ... to DSi mainboard connector pin 37                        |
|       37 BBP_SCS      ... to DSi mainboard connector pin 35                        |
|       38 RF_SCS       ... to DSi mainboard connector pin 33                        |
|       39 GND                                                                       |
|       40 VDD33                                                                     |
|       41 RF_SLEEP     ... to DSi mainboard connector pin 31                        |
|       42 BBP_SLEEP    ... to DSi mainboard connector pin 29                        |
|       ---                                                                          |
|       43 VDD18                                                                     |
|       44 ... shortcut to MM3218.pin50, and via resistor to MM3218.pin46            |
|       45 VDD33                                                                     |
|       46 ... via resistor to MM3218.pin44+50                                       |
|       47 ... to DSi mainboard connector pin 25 (via 0 ohm) (+cap) (NC in DSi)      |
|       48 VDD33                                                                     |
|       49 GND                                                                       |
|       50 ... shortcut to MM3218.pin44, and via resistor to MM3218.pin46            |
|       51 ... via resistor to GND                                                   |
|       52 VDD18                                                                     |
|       53 NC                                                                        |
|       54 NC                                                                        |
|       55 NC                                                                        |
|       56 NC                                                                        |
+------------------------------------------------------------------------------------+
```


### ROCm Atheros AR6002G-AC1B chip (on DSi DWM-W015 Wifi Daughterboard)

```
+-------------------------------------------------------------------------------------+
|        1     2     3     4     5     6     7    8    9     10    11    12    13     |
|      A AGND  RF2   RF2   RF2   RF2   PDET  NC   NC   VDD18 VDD12 XTAL  XTAL  BT_CLK |
|              OUTN  OUTP  INP   INN                   BIAS  XTAL  I     O     OUT    |
|      B RF5   AGND  VDD18 VDD12 VDD12 BIAS  NC   NC   VDD12 VDD12 VDD18 BT_   DVDD12 |
|        INP         FE    LNA   BIAS  REF             D_SYN BB    XTAL  CLKEN        |
|      C RF5   VDD12 -     -     AGND  AGND  AGND AGND AGND  -     -     GPIO  GPIO   |
|        INN   FE                                                        17    16     |
|      D PA5   NC    -     -     -     -     -    -    -     -     -     GPIO  GPIO   |
|        BIAS                                                            14    15     |
|      E RF5   VDD18 AGND  -     AGND  AGND  AGND AGND DVSS  -     -     DVDD  DVDD   |
|        OUT   VCO                                                       GPIO1 GPIO0  |
|      F VDD12 VDD12 AGND  -     AGND  AGND  AGND AGND DVSS  -     DVSS  GPIO  GPIO   |
|        TX5   SYNTH                                                     12    13     |
|      G XPA   XPA   AGND  -     AGND  AGND  AGND AGND DVSS  -     DVSS  GPIO  GPIIO  |
|        BIAS2 BIAS5                                                     10    11     |
|      H VCCFE LDO_  AGND  -     AGND  AGND  AGND AGND DVSS  -     DVSS  GPIO  DVDD   |
|        M     OUT                                                       9     12     |
|      J ANTA  VDDIO AGND  -     DVSS  DVSS  DVSS DVSS DVSS  -     DVSS  CLK_  DVDD   |
|              ANT                                                       REQ   12     |
|      K ANTC  ANTB  -     -     -     -     -    -    -     -     -     SYS_  CHIP_  |
|                                                                        RST_L PWD_L  |
|      L ANTD  ANTE  -     -     DVSS  DVSS  DVSS  DVSS DVSS -     -     DVDD  DVDD_  |
|                                                                        12    SDIO   |
|      M AGND  GPIO0 GPIO2 DVDD  GPIO4 GPIO6 GPIO8 JTAG JTAG JTAG  SDIO_ SDIO_ SDIO_  |
|                          12                      TMS  TCK  TDO   DATA3 DATA2 CLK    |
|      N DVDD  GPIO1 GPIO3 DVDD_ GPIO5 GPIO7 DVDD_ DVDD JTAG DVDD_ SDIO_ SDIO_ SDIO_  |
|        12                BT                SDIO  12   TDI  SDIO  CMD   DATA1 DATA0  |
+-------------------------------------------------------------------------------------+
```


### Atheros AR6013 chip (on DSi DWM-W024 Wifi Daughterboard)

```
+-----------------------------------------------------------------------+
|       1  1.2V                                                         |
|       2  VDD18                                                        |
|       3  NC                                                           |
|       4  NC                                                           |
|       5  VDD18                                                        |
|       6  NC                                                           |
|       7  1.2V                                                         |
|       8  VDD18                                                        |
|       9  1.2V                                                         |
|       10 NC                                                           |
|       11 NC (except, wired to testpoint)                              |
|       12 VDD33                                                        |
|       13 via 0 ohm to ATH_TX_H  ;<--with 0 ohm connection             |
|       14 via (N/A) to ATH_TX_H  ;<--connection not installed          |
|       15 to a dead-end-via                                            |
|       16 to a dead-end-via                                            |
|       17 1.2V                                                         |
|       18 P5.pin24       JTAG_TRST_L     (plus testpoint)              |
|       19 NC (except, wired to testpoint)                              |
|       ---                                                             |
|       20 VDD18                                                        |
|       21 1.2V                                                         |
|       22 I2C.SCL                                                      |
|       23 I2C.SDA                                                      |
|       24 P5.pin21 RTC 32KHZ via 0 ohm                                 |
|       25 /WIFI_RST                                                    |
|       26 ATH_TX_H                                                     |
|       27 SDKI.CMD                                                     |
|       28 SDIO.CLK                                                     |
|       29 VDD33                                                        |
|       30 SDIO.DAT0                                                    |
|       31 SDIO.DAT2                                                    |
|       32 SDIO.DAT1                                                    |
|       33 SDIO.DAT3                                                    |
|       34 P5.pin22       JTAG_TCK                                      |
|       35 P5.pin20       JTAG_TDI                                      |
|       36 P5.pin17       JTAG_TMS                                      |
|       37 1.2V                                                         |
|       38 P5.pin15       JTAG_TDO                                      |
|       ---                                                             |
|       39 P5.pin36       CCA                                           |
|       40 VDD33                                                        |
|       41 1.2V                                                         |
|       42 P5.pin46       TRRDY                                         |
|       43 P5.pin44       TRCLK                                         |
|       44 P5.pin40       TRDATA                                        |
|       45 WL_TXPE                                                      |
|       46 WL_RXPE                                                      |
|       47 P5.pin47       MCLK                                          |
|       48 P5.pin33       RF_SCS      ... and 6.9ohm to P5.47 ?         |
|       49 P5.pin35       BBP_SCS                                       |
|       50 P5.pin39       BB_RF_SDI                                     |
|       51 VDD33                                                        |
|       52 P5.pin37       BB_RF_SDO                                     |
|       53 P5.pin41       BB_RF_SCLK                                    |
|       54 P5.pin29       BBP_SLEEP                                     |
|       55 P5.pin31       RF_SLEEP                                      |
|       56 P5.pin26       SEL_ATH_L   ... IRQ?                          |
|       57 1.2V                                                         |
|       ---                                                             |
|       58 VDD18                                                        |
|       59 XTALx                                                        |
|       60 XTALx                                                        |
|       61 1.2V                                                         |
|       62 1.2V                                                         |
|       63 VDD18                                                        |
|       64 NC (except, wired to testpoint)                              |
|       65 NC (except, wired to testpoint)                              |
|       66 NC (except, wired to testpoint)                              |
|       67 NC (except, wired to testpoint)                              |
|       68 NC                                                           |
|       69 via 6.1K to GND                                              |
|       70 1.2V                                                         |
|       71 NC                                                           |
|       72 NC                                                           |
|       73 VDD18                                                        |
|       74 RF2.OUTx                                                     |
|       75 RF2.OUTx                                                     |
|       76 VDD18                                                        |
|       ---                                                             |
|       GND center plates                                               |
+-----------------------------------------------------------------------+
```

Note: /RESET connects to Wifi FLASH only, ie. NOT to the MM3218 clone within AR6013G (that\'s unlike as real MM3218).

### Atheros AR6014 chip (on 3DS DWM-W028 Wifi Daughterboard) (and J27H023?)
Pinouts unknown.

There is a 3rd part number, J27H020, made by hon hai (Foxconn) instead of Mitsumi.



