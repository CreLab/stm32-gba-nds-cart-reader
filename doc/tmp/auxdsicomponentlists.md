# AUX DSi Component Lists


### DSi Mainboard \"C/TWL-CPU-01\" Components

```
+-------------------------------------------------------------------------------------+
|       U1 352pin   CPU TWL       (under shielding plate)                    ;\under  
|       U2   ?pin   RAM 8Mx16, Fujitsu MB82DBS08164D-70L, NEC uPD46128512AF1 ;/shield |
|       U3  56pin   "TexasIns 72071B0" or "Mitsumi 3317A" (Powerman) (right of NAND)  |
|       U4  48pin   "AIC3000D, TI 89K, EXDK G4" (PAIC3 codec? above headphone socket) |
|       U5   ?pin   Samsung KMAPF0000M-S998 (eMMC, 256Mbyte NAND FLASH)               |
|       U6  36pin   "BPTWL, K007K, 0902KM00D" (small/square, left of cartridge slot)  |
|       U7   8pin   "AOK, S8BXS" (ISL95810, I2C potentiometer)         ;\on PCB       
|       U8   8pin   "7BDS" (PCA9306, I2C voltage translator)           ;/backside     |
|       U9  12pin   "199A, 01IU" (Seiko S-35199A01) (RTC) ;under shielding plate (A)  |
|       U10  4pin   "6800" or "688F" Hinge Magnet Sensor (PCB backside, near A/B/X/Y) |
|       U11 10pin   ",\\ 908, 335A" or "2005D, 8350" (right of cartridge slot)        
|       U12  5pin   "L8NX" or "C7JHN" (upper-right of PCB back-side) ;text layer (B)  |
|       U13  5pin   Backlight 1, "U01" or "KER"  ;\lower-right board edge             
|       U14  5pin   Backlight 2, "U01" or "KER"  ;/see text-layer (B)                 |
|       U15  4pin   VIN to EXB+ control via Q1, ",\\ T34" (near external power input) 
|       U16     -   N/A                                                               |
|       U17  6pin   Headphone Mute, "VY" or "Z198" (in lower-right, on PCB backside)  |
|       U18  6pin   Mic Bias, "YJ" (above headphone socket, not always installed)     |
|       U19  5pin   "E30H6" or "L2SX" (at lower right of cartridge slot)              |
|       U20  3pin   Whatever, DSi XL only (maybe magnet Sensor instead of U10?)       |
|       Q1   6pin   external power supply related (VIN to EXTB+) (controlled by U15)  |
|       Q2    pin   N/A ?                                                             |
|       Q3   6pin   ... above battery plug                                            |
|       Q4   3pin   Headphone MUTE for SR  ;\old TWL-CPU-01 mainboard only            
|       Q5   3pin   Headphone MUTE for SL  ;/(replaced by Q17/Q18 on newer boards)    |
|       Q6   6pin   MC1_VDD power ON (supply)                                         |
|       Q7   3pin   MC1_VDD power OFF (pulldown)                                      |
|       Q8    pin   N/A ?                                                             |
|       Q9    pin   N/A ?                                                             |
|       Q10   pin   N/A ?                                                             |
|       Q11  3pin   BLUE (LED)   ;\LEDs (note: the other LEDs, ORANGE                 
|       Q12  3pin   YELLOW (LED) ;      and YELLOW, are driven directly)              |
|       Q13  3pin   CAM_LED      ;/                                                   |
|       Q14  3pin   not installed (above powerman chip)                               |
|       Q15  3pin   not installed (above powerman chip)                               |
|       Q16  3pin   VDD-5 related, near DPAD socket (P15)                             |
|       Q17  6pin   Headphone MUTE for ..?  ;\new TWL-CPU-10 mainboard only           
|       Q18  6pin   Headphone MUTE for ..?  ;/(formerly Q4/Q5 on older boards)        |
|       X1   4pin   16.756  (rectangular oscillator)        ;\under shielding plate   
|       X2   4pin   CB837 or CB822 (long slim osc) for RTC? ;/text layer: see (A)     |
|       F1   2pin   Fuse for external power input                                     |
|       SW1  2pin   Button A (right)                                                  |
|       SW2  2pin   Button B (lower)                                                  |
|       SW3  2pin   Button X (upper)                                                  |
|       SW4  2pin   Button Y (left)                                                   |
|       SW5  2pin   Button Select (lower)                                             |
|       SW6  2pin   Button Start  (upper)                                             |
|       P1  19pin   NDS/DSi cartridge slot (17pin slot + 2pin switch at right side)   |
|       P2      -   N/A                                                               |
|       P3      -   N/A                                                               |
|       P4   8pin   External microphone/headphone combo socket                        |
|       P5  50pin   Wifi-Daughterboard                                                |
|       P6      -   N/A                                                               |
|       P7  47pin   To UPPER lcd screen (video+backlight+speakers) (on PCB backside)  |
|       P8  37pin   To LOWER lcd screen (video signals)                               |
|       P9  25pin   To UPPER lcd screen (signals for both cameras, and camera led)    |
|       P10  4pin   To LOWER lcd screen (touchpad X-,Y-,X+,Y+)                        |
|       P11  2pin   External Power Supply input (4.6V DC IN)                          |
|       P12     -   N/A                                                               |
|       P13     -   N/A                                                               |
|       P14     -   N/A                                                               |
|       P15 15pin   To battery/DPAD/PowerButton board (and onwards to 3xLEDs)         |
|       P16 26pin   To bottom cover (SD Slot and L/R/VOL+/- buttons)                  |
|       P17  2pin   Battery cable (lower-right) ;see text-layer (B)                   |
|       P18  4pin   To LOWER lcd screen (backlight cathode/anode)                     |
|       P19  1pin   Shielding-Plate for CPU (lower clip)                              |
|       P20  1pin   Shielding-Plate for CPU (upper clip)                              |
|       P21  1pin   Shielding-Plate for CPU (right clip)                              |
|       P22     -   N/A                                                               |
|       P23  2pin   To Internal Microphone (via orange shielded wire)                 |
|       P24 14pin   DSi XL only (L/VOL+/-, which were formerly on P16 in old DSi)     |
+-------------------------------------------------------------------------------------+
```

DSi Front/bottom-Side Text Layer sections (in upper left of mainboard)

```
+------------------------------------------------------------------------------+
|       (A)  For components underneath of shielding plate                      |
|       (B)  For components in lower-right board edge (near battery connector) |
|       (C)  For components at middle/right of cartridge slot                  |
|       (D)  For components left of U4 (left board edge)                       |
|       (E)  For components right of U4 (above headphone socket)               |
|       (F)  For components at lower/right of cartridge slot                   |
+------------------------------------------------------------------------------+
```

DSi Back/top-Side Text Layer sections (at various places)

```
+-----------------------------------------------------------------------+
|       (A)  at top/middle,  for components at upper right edge         |
|       (B)  at middle/left, for components near upper right edge       |
|       (C)  at lower/left,  for components left of Y-button            |
|       (D)  at lower/righz, for components at right edge               |
+-----------------------------------------------------------------------+
```


### DSi Wifi Daughterboard (DWM-W015) (older DSi version)
PCB Text: \"RU (S)-717V 01 ,\\\\\" or \"RU (S)-717V 03 ,\\\\\" or \"FK RU 06 ,\\\\\"

```
+-------------------------------------------------------------------------------------+
|       U   56pin "Mitsumi, Japan, 844L, MM3218" (same as in DS Lite)                 |
|       U  132pin "ROCm, Atheros, AR6002G-AC1B, E19077.1B, 0844, Taiwan"              |
|       U    8pin I2C EEPROM "408F, B837" (HN58X2408F; 1Kx8 for atheros calibration)  |
|       U    8pin SPI FLASH big chip "45PE10V6, HPASC VS, KOR 8364, ST"  ;\either one 
|       U    8pin SPI FLASH tiny chip "5A32, 8936?"                      ;/installed  |
|       U    8pin "4P, K" or "S6, K" (odd 3+1+3+1 pin package, near antenna)          |
|       U    4pin "3VP, OT" or "3VB, OS" (at board edge, near 50pin connector)        |
|       X    4pin "26.000, 9848" (bigger oscillator, for atheros chip)                |
|       X    4pin "22.000, xxxx" (smaller oscillator, for mitsumi chip)               |
|       P   50pin Connector to Mainboard                                              |
|       P    2pin Connector for Antenna (shielded white cable)                        |
+-------------------------------------------------------------------------------------+
```

The \"3VP/3VP\" thing is some 1.2V voltage regulator (sth like LP3983 or TPS799xx or similar).
White PCB sticker (underneath of the black isolation sticker): \"DWM-W015, IC:4250A-DWMW015, FCC ID:EW4DWMW015, \[R\]003WWA080444, \[T\]D080261003, MADE IN PHILIPINES, MITSUMI ELEC. CO., LTD.\"

### DSi Wifi Daughterboard (DWM-W024) (newer DSi version)
PCB Text: \"FB RU 06 ,\\\\\"

```
+-----------------------------------------------------------------------------------+
|       U   76pin "ROCm, Atheros, AR6013G-AL1C" (or 80pin, with 4pins at edges?)    |
|       U    8pin I2C EEPROM? "4DA?, D940?"   ;maybe I2C eeprom for atheros         |
|       U    8pin SPI FLASH "5A32, 8937?"   ;FLASH (small solder pads)              |
|       U    8pin SPI FLASH not installed (alternate bigger solder pads for FLASH?) |
|       U    4pin "?" (at board edge, near 50pin connector)                         |
|       X    4pin "??" (oscillator, near ROCm chip)                                 |
|       P   50pin Connector to Mainboard                                            |
|       P    2pin Connector for Antenna (shielded white cable)                      |
+-----------------------------------------------------------------------------------+
```


### DSi Wifi Daughterboard (J27H020) (alternate newer DSi version)
This seems to be functionally same as DWM-W024, but the PCB is different, and the circuit seems to use a different voltage regulator, and includes solder pads for some additional uninstalled components. And the shielding is difficult to remove because it\'s soldered all way round (rather than just at some solder points).

```
+-------------------------------------------------------------------------------+
|      Sticker 1:                                                               |
|       HON HAI PRECISION IND.CO.,LTD.        ;aka Foxconn                      |
|       MODEL: J27H020                                                          |
|       [R] 003WWA100195                                                        |
|       [T] D100196003                                                          |
|       FCC ID: MCLJ27H020                                                      |
|       IC: 2878D-27H020                                                        |
|      Sticker 2:                                                               |
|       (barcode)                                                               |
|       <mac.address> J27H020.00 LF, 4xxxxxx-xxx                                |
|      Board:                                                                   |
|       U1   76pin atheros ... "ATHEROS, AR6013G-AL1C, N2U586.00C, 1035, KOREA" |
|       U2    -    -                                                            |
|       U3    -    -                                                            |
|       U4    8pin I2C EEPROM "G80, 8, G02"                                     |
|       U5    8pin SPI FLASH big chip "26FV032T, OGK01"  (installed)            |
|       U6    -    -                                                            |
|       U7    8pin SPI FLASH small chip (not installed)                         |
|       U?    5pin voltage regulator or so "IG19P"                              |
|       U?    6pin whatever near antenna (not installed)                        |
|       Y1    4pin crystal "H400K"                                              |
|       J3    2pin Connector for Antenna (shielded white cable)                 |
|       J6   50pin Connector to Mainboard                                       |
+-------------------------------------------------------------------------------+
```


### 3DS Wifi Daughterboard (DWM-W028, or J27H023, or J27H023.01)
Component list is unknown. The thing is said to use a \"Atheros AR6014\" chip.
Later 3DS models have the Wifi unit (with AR6014G chip) on the mainboard (instead of using a removeable DWM board).

### DSi Battery/DPAD Daughterboard \"C/TWL-SUB-01\"

```
+-------------------------------------------------------------------------------------+
|       TH1  2pin  Battery Thermistor Thermal Sensor (ca. 10kOhm at room temperature) |
|       F1   2pin  Battery Fuse                                                       |
|       SW1  2pin  DPAD Up Button                                                     |
|       SW2  2pin  DPAD Down Button                                                   |
|       SW3  2pin  DPAD Left Button                                                   |
|       SW4  2pin  DPAD Right Button                                                  |
|       SW5  2pin  Power/Reset Button                                                 |
|       P1  15pin  To Mainboard (P15) (button/led signals) (wire "15P-01")            |
|       P2   6pin  To 3xLEDs                                                          |
|       P3   3pin  To battery (TWL-003 3.6V 840mAh 3Wh C/TWL-A-BP, Li-ion 00"         |
|       Wire 2pin  To Mainboard (P17) (battery supply) (red=vcc, black=gnd)           |
+-------------------------------------------------------------------------------------+
```


### DSi LED Board/Foil \"LED-01, (DF)\"

```
+-----------------------------------------------------------------------+
|       D    2pin  Left LED      ;-wifi                                 |
|       D    2pin  Middle LED    ;-charge                               |
|       D    2pin  Right LED 1   ;\power "two-color-LED"                
|       D    2pin  Right LED 2   ;/composed of 2 single LEDs            |
|       Wire 6pin  To Battery/DPAD Daughterboard                        |
+-----------------------------------------------------------------------+
```


### DSi Lower Screen with Touchpad

```
+-----------------------------------------------------------------------+
|       Wire 4pin  Touchpad                                             |
|       Wire 4pin  Backlight (actually 2pins, each 2 pins are same)     |
|       Wire xxpin Video Signals                                        |
|       LCD  "LS033A1DG48R, 8X16Q U0003986"                             |
+-----------------------------------------------------------------------+
```


### DSi Upper Screen with Speakers & Cameras & LED & Microphone

```
+----------------------------------------------------------------------------------+
|       Orange Ribbon Cable: Video Signals, Backlight, and Speakers                |
|       Black Ribbon Cable: Cameras and Camera LED                                 |
|       Shielded Orange 2pin Wire: Microphone                                      |
|       Shielded White 2pin Wire: Wifi PCB Antenna                                 |
|       LCD  "LS033A1DG38R, BX16Q L0005532"                                        |
|       The speakers use red/black wires, which connect to the orange ribbon cable |
+----------------------------------------------------------------------------------+
```


### DSi Upper Screen Area Extra Components: Speakers & Cameras & LED & Microphone

### DSi Lower Case (SD Slot, L/R and VOL+/- Buttons, and screen calibration)

```
+-----------------------------------------------------------------------+
|       Whatever, not checked yet                                       |
+-----------------------------------------------------------------------+
```


### DSi Disassembly Notes
Bottom Cover Screws:

```
+-----------------------------------------------------------------------+
|       7 screws (two are under battery cover)                          |
+-----------------------------------------------------------------------+
```

Remove bottom cover, and:

```
+--------------------------------------------------------------------------------+
|       P16: To bottom cover (SD Slot and L/R/VOL+/-) --> pull (away from board) |
+--------------------------------------------------------------------------------+
```

Remove Wifi Daughterboard:

```
+-------------------------------------------------------------------------------------+
|       P5:  Wifi-board (without cable)               --> pull (away from board)      |
|       WHITE: Wifi-Antenna (shielded 2pin)           --> pull (away from wifi-board) |
+-------------------------------------------------------------------------------------+
```

Remove mainboard:

```
+-------------------------------------------------------------------------------------+
|       ORANGE P24 (shielded 2pin)  --> pull (away from board)                        |
|       WHITE SUPPLY                --> lift (use screwdriver & push away from board) |
|       3x bigger white/black connectors --> lift black lid (at cable-side)           |
|       2x smaller black connectors      --> lift black lid (at cable-end) (!!!)      |
+-------------------------------------------------------------------------------------+
```

Turn mainboard over, then unlock the connector at back side:

```
+---------------------------------------------------------------------------+
|       1x bigger white/black connector  --> lift black lid (at cable-side) |
+---------------------------------------------------------------------------+
```

Remove Battery board:

```
+--------------------------------------------------------------------------------+
|       1x smaller black connector       --> lift black lid (at cable-end) (!!!) |
|       1x bigger white/black connectors --> lift black lid (at cable-side)      |
|       (don't disconnect bigger connector if the other cable end is already     |
|       disconnected from mainboard) (or if you did do, reassemble as follows:   |
|       longer cable end to battery board, short cable end to mainboard)         |
|       1x battery cable (disconnect at mainboard side, see there)               |
+--------------------------------------------------------------------------------+
```

Top Cover Disassembly:

```
+-----------------------------------------------------------------------+
|       Disconnect upper LCD and mic/antenna from mainboard (see above) |
|       Remove 4 screws (all hidden under square rubber pieces)         |
|       slide rear bezel upwards by two millimeters?                    |
|       push metal hinge inwards by three millimeters (under LED unit)  |
+-----------------------------------------------------------------------+
```




