# AUX DSi Internal Connectors


### P1 - 19pin - NDS/DSi cartridge slot (17pin slot + 2pin switch at right side)

```
+-----------------------------------------------------------------------+
|       1   GND                                                         |
|       2   MC1_CLK                                                     |
|       3   -                                                           |
|       4   MC1_CS                                                      |
|       5   MC1_RES                                                     |
|       6   MC1_CS2                                                     |
|       7   MC1_IREQ                                                    |
|       8   MC1_VDD via Q6 to VDD33 (cpu signal preamplified from Q7)   |
|       9   MC1_IO0                                                     |
|       10  MC1_IO1                                                     |
|       11  MC1_IO2                                                     |
|       12  MC1_IO3                                                     |
|       13  MC1_IO4                                                     |
|       14  MC1_IO5                                                     |
|       15  MC1_IO6                                                     |
|       16  MC1_IO7                                                     |
|       17  GND                                                         |
|       18  MC1_DET           ;\switch closed when cart inserted        
|       19  GND               ;/                                        |
|       Shield GND                                                      |
+-----------------------------------------------------------------------+
```


### P4 - 8pin - External microphone/headphone combo socket

```
+-----------------------------------------------------------------------------------+
|       1  GND    ;\      ;\                                                        
|       2  SL     ; head- ; headphone gnd/left/right                                |
|       3  SR     ; phone ;/                                                        |
|       4  GND    ;       ;\headphone/speaker switch (pin 4+5 shortcut with each    
|       5  HP#SP  ;/      ;/other when no headphone connected)                      |
|       6  MIC    ;\    ;\microphone switch (pin6+7 shortcut when no mic connected) 
|       7  Switch ; mic ;/(internal mic from P23 is then passed from pin7 to pin6)  |
|       8  GND    ;/                                                                |
+-----------------------------------------------------------------------------------+
```


### P5 - 50pin - DSi Wifi-Daughterboard (DWM-W015, DWM-W024, or J27H020)

```
+-------------------------------------------------------------------------------------+
|                                GND   2  1   SDIO.CLK       ;\                       
|                              VDD18   4  3   GND            ; SDIO for               |
|                              VDD18   6  5   SDIO.DAT0      ; Atheros Wifi           |
|                                GND   8  7   SDIO.DAT3      ; (CLK, CMD, DATA0-3)    |
|                              VDD33  10  9   SDIO.DAT1      ;                        |
|                              VDD33  12  11  SDIO.CMD       ;                        |
|                                GND  14  13  SDIO.DAT2      ;/                       |
|                           ATH_TX_H  16  15  DSi: NC (DWM: JTAG_TDO)                 |
|                          /WIFI_RST  18  17  DSi: NC (DWM: JTAG_TMS)                 |
|          (DWM:JTAG_TDI)    DSi: NC  20  19  GND                                     |
|          (DWM:JTAG_TCK)    DSi: NC  22  21  RTC_FOUT (or RTC_F32K?)  ;for Atheros?  |
|          (DWM:JTAG_TRST_L) DSi: NC  24  23  GND                                     |
|      (near CPU irq pins) SEL_ATH_L  26  25  DSi: NC (wifi: via 0 ohm MM3218.pin47)  |
|                    /FLASH_WP (R122) 28  27  SPI_CS2 (wifi FLASH memory)             |
|                            SPI_SCK  30  29  BBP_SLEEP    to MM3218.pin42            |
|                           SPI_MISO  32  31  RF_SLEEP     to MM3218.pin41            |
|                           SPI_MOSI  34  33  RF_SCS       to MM3218.pin38            |
|            to MM3218.pin15     CCA  36  35  BBP_SCS      to MM3218.pin37            |
|                            WL_RXPE  38  37  BB_RF_SDO    to MM3218.pin36            |
|            to MM3218.pin19  TRDATA  40  39  BB_RF_SDI    to MM3218.pin35            |
|                                GND  42  41  BB_RF_SCLK   to MM3218.pin34            |
|            to MM3218.pin21   TRCLK  44  43  NC(VDD18_TP) to MM3218.pin28 (0ohm+cap) |
|            to MM3218.pin18   TRRDY  46  45  GND                                     |
|                            WL_TXPE  48  47  MCLK    to MM3218.pin23 (via XX & CLxx) |
|                              RESET  50  49  GND                                     |
+-------------------------------------------------------------------------------------+
```

<https://fccid.io/EW4DWMW024/Label/Label-format-and-location-1137926.pdf>
<https://fccid.io/EW4DWMW015/Label/Label-Location-1031953.pdf>
Pin 25 and 43 are VDD test points on DWM-W015 wifiboard (but are NC on DSi mainboard & DWM-W024 wifiboard).

### P7 - 47pin - To UPPER lcd screen (video+backlight+speakers) (on PCB backside)

```
+-----------------------------------------------------------------------+
|                               BLA2   1  2   BLC2    ;-backlight       |
|                               SPLN   3  4   SPLN    ;\left speaker    
|                               SPLP   5  6   SPLP    ;/                |
|                               SPRN   7  8   SPRN    ;\right speaker   
|                               SPRP   9  10  SPRP    ;/                |
|                              VDD-5  11  12  VDD10                     |
|                               VDD5  13  14  GND                       |
|                               VSHD  15  16  VSHD                      |
|                                INI  17  18  GSP                       |
|                                GCK  19  20  LDB20                     |
|                              LDB21  21  22  LDB22                     |
|                              LDB23  23  24  LDB24                     |
|                              LDB25  25  26  LDG20                     |
|                              LDG21  27  28  LDG22                     |
|                                GND  29  30  LDG23                     |
|                              LDG24  31  32  LDG25                     |
|                              LDR20  33  34  LDR21                     |
|                              LDR22  35  36  LDR23                     |
|                              LDR24  37  38  LDR25                     |
|                                GND  39  40  DCLK                      |
|                                SPL  41  42  LS                        |
|                                GND  43  44  via C79 to COM2           |
|                                REV  45  46  GND                       |
|                               COM2  47                                |
+-----------------------------------------------------------------------+
```


### P8 - 37pin - To LOWER lcd screen (video signals)

```
+-----------------------------------------------------------------------+
|                              VDD-5   1  2   VDD10                     |
|                               VDD5   3  4   GND                       |
|                               VSHD   5  6   VSHD                      |
|                                INI   7  8   GSP                       |
|                                GCK   9  10  LDB10                     |
|                              LDB11  11  12  LDB12                     |
|                              LDB13  13  14  LDB14                     |
|                              LDB15  15  16  LDG10                     |
|                              LDG11  17  18  LDG12                     |
|                                GND  19  20  LDG13                     |
|                              LDG14  21  22  LDG15                     |
|                              LDR10  23  24  LDR11                     |
|                              LDR12  25  26  LDR13                     |
|                              LDR14  27  28  LDR15                     |
|                                GND  29  30  DCLK                      |
|                                SPL  31  32  LS                        |
|                                GND  33  34  via C93 to COM1           |
|                                REV  35  36  GND                       |
|                               COM1  37                                |
+-----------------------------------------------------------------------+
```


### P9 - 25pin - To UPPER lcd screen (signals for both cameras, and camera led)

```
+-----------------------------------------------------------------------+
|                                GND   1  2   CAM_LED                   |
|                              VDD42   3  4   GND                       |
|                       R100    RCLK   5  6   GND                       |
|                                GND   7  8   HSYNC                     |
|                              VSYNC   9  10  CAM_D5  RA7               |
|                        RA7  CAM_D6  11  12  CAM_D4  RA7               |
|                            CAM_RST  13  14  SCL                       |
|                                SDA  15  16  CAM_D7  RA7               |
|                        RA6  CAM_D0  17  18  CAM_D3  RA6               |
|                        RA6  CAM_D1  19  20  CAM_D2  RA6               |
|                              VDD28  21  22  GND                       |
|                                CKI  23  24  GND                       |
|                              VDD18  25                                |
+-----------------------------------------------------------------------+
```


### P10 - 4pin - To LOWER lcd screen (touchpad X-,Y-,X+,Y+)

```
+-----------------------------------------------------------------------+
|       1 X-                                                            |
|       2 Y-                                                            |
|       3 X+                                                            |
|       4 Y+                                                            |
+-----------------------------------------------------------------------+
```


### P11 2pin External Power Supply input (4.6V DC IN)

```
+-----------------------------------------------------------------------+
|       1 VIN  (+4.6V)                                                  |
|       2 VGND (GND)                                                    |
|       Shield (GND)                                                    |
+-----------------------------------------------------------------------+
```


### P15 - 15pin - To battery/DPAD/PowerButton board (and onwards to 3xLEDs)

```
+--------------------------------------------------------------------------------+
|       dpad up button      P06  1  2  ORANGE (LED) Battery Charge               |
|       dpad right button   P04  3  4  BLUE   (LED) Power On/Good                |
|       dpad left button    P05  5  6  YELLOW (LED) Wifi                         |
|       dpad down button    P07  7  8  RED    (LED) Power On/Low                 |
|                           GND  9  10 VDD42 (to LEDs)                           |
|                           GND 11  12 TH on DPAD board (via R102 to TH on main) |
|       middle battery pin  DET 13  14 GND                                       |
|       power button       PWSW 15                                               |
+--------------------------------------------------------------------------------+
```

Note: On Daughterboard, pins are mirrored (eg. PWSW=Pin1 instead Pin15)

### P16 - 26pin - To bottom cover (SD Slot and L/R/VOL+/- buttons)
On original DSi:

```
+-------------------------------------------------------------------------------------+
|                           GND  2  1  SD10_CLK                   ;\                  
|                    SD10_DATA0  4  3  SD10_VDD (aka VDD33)       ;                   |
|                    SD10_DATA1  6  5  SD10_VDD (aka VDD33)       ; pin 1..18         |
|                       SD10_WP  8  7  GND                        ; to RIGHT side:    |
|                           GND 10  9  SD10_CMD                   ; R-button, and     |
|       shoulder button R   P08 12  11 GND                        ; SD-card slot      |
|                           GND 14  13 SD10_DATA3                 ;                   |
|                       SD10_CD 16  15 SD10_DATA2                 ;                   |
|                           GND 18  17 GND                        ;/                  |
|                           GND 20  19 GND                        ;\pin 19..20        
|       maybe display ;\   VDD5 22  21 VOLP  volume plus          ; to LEFT side:     
|       calibration?  ;    COM1 24  23 VOLN  volume minus         ; L-button, VOL +/- |
|       (at battery)  ;/   COM2 26  25 P09   shoulder button L    ;/and calibration   |
+-------------------------------------------------------------------------------------+
```

On DSi XL (changed pins, COM1/COM2 removed, and L/VOL+- moved to P24):

```
+-----------------------------------------------------------------------+
|            GND  1  2  GND                                             |
|            GND  3  4  GND                                             |
|            GND  5  6  GND                                             |
|       SD10_CLK  7  8  GND                                             |
|          VDD33  9  10 SD10_D0                                         |
|          VDD33 11  12 SD10_D1                                         |
|            GND 13  14 SD10_WP                                         |
|       SD10_CMD 15  16 VDD33                                           |
|            GND 17  18 P08 (should button R)                           |
|        SD10_D3 19  20 VDD33                                           |
|        SD10_D2 21  22 SD10_CD                                         |
|            GND 23  24 GND                                             |
|            GND 25  26 GND                                             |
+-----------------------------------------------------------------------+
```


### P17 - 2pin - Battery cable (lower-right) ;see text-layer (B)

```
+-----------------------------------------------------------------------+
|       + BT+ (plus) (red wire)                                         |
|       - BT- (GND)  (black wire)                                       |
+-----------------------------------------------------------------------+
```


### P18 - 4pin - To LOWER lcd screen (backlight cathode/anode)

```
+-----------------------------------------------------------------------+
|       1 BLC1  ;\both same                                             
|       2 BLC1  ;/                                                      |
|       3 BLA1  ;\both same                                             
|       4 BLA1  ;/                                                      |
+-----------------------------------------------------------------------+
```


### P19 - 1pin - Shielding-Plate for CPU (lower clip)
### P20 - 1pin - Shielding-Plate for CPU (upper clip)
### P21 - 1pin - Shielding-Plate for CPU (right clip)

```
+-----------------------------------------------------------------------+
|       Shield GND                                                      |
+-----------------------------------------------------------------------+
```


### P23 - 2pin - To Internal Microphone (via orange shielded wire)

```
+--------------------------------------------------------------------------------+
|       Pin  MIC (from P4.Pin7, disconnected when external microphone connected) |
|       Shield GND                                                               |
+--------------------------------------------------------------------------------+
```


### P24 - 14pin - DSi XL only (L/VOL+/- were formerly on P16 in old DSi)

```
+-----------------------------------------------------------------------+
|                    GND 1  2  GND                                      |
|                    N/C 3  4  VOLP                                     |
|       P09 (shoulder-L) 5  6  VOLN                                     |
|                 GND 7-13  8-14 GND                                    |
+-----------------------------------------------------------------------+
```


### DPAD-BOARD - P2 - 6pin - To LEDs

```
+-----------------------------------------------------------------------+
|       1  YELLOW  Wifi                                                 |
|       2  BLUE    Power On/Good                                        |
|       3  ORANGE  Battery Charge                                       |
|       4  GND   (for red+orange)                                       |
|       5  RED     Power On/Low                                         |
|       6  VDD42 (for yellow+blue)                                      |
+-----------------------------------------------------------------------+
```




