# AUX DSi Signals/Testpoints


The DSi has testpoints with friendly names. The DSi XL has \"nameless\" testpoints (numbered TP1 thru TP194, as described on <https://www.dsibrew.org/wiki/DSi_XL_testpoints> which may include some bugs for the Supply and BGA pins though).


```
+-------------------------------------------------------------------------------------+
|       ADPO       TP... U3,U6        Charger connected? (Low=Connected, High=No)     |
|       AOUT       TP... U3,U6        Analog battery level? (max=2.35V?)              |
|       PM_SLP     TP... U1,U3,U6     Sleep or so? (Low=Normal, High=Sleep?)          |
|       PMOFF      TP... U1,U3,U6,U17 Powerman/Headphone off? (Low=Normal)            |
|       PWSWO      TP... U3,U6        Power? (Low=Off, or Reset-tapping, High=On)     |
|       VCNT5      TP... U1,U3,U4,U19 Control for VSHD for Both Screens ?             |
|       mFE        TP... U6          BPTWL Flash Enable (aka FLMD0)    (Low=Normal)   |
|       /mRST      TP... U6          BPTWL Flash Invoke transfer?      (High=Normal)  |
|       /IRQ_O     TP... U1,U6       BPTWL Interrupt (eg. Power Button)               |
|       GPIO330    TP... U1          General Purpose GPIO bit (?)                     |
|       RESET      TP... P5,U1,U3..  Reset WifiFlash,MainCpu,PowerMan,TSC from BPTWL  |
|       P00        TP... U1,SW1      Button A                                         |
|       P01        TP... U1,SW2      Button B                                         |
|       P02        TP... U1,SW5,U6   Button SELECT (also SELECT+VOLP/VOLN=Backlight)  |
|       P03        TP... U1,SW6      Button START                                     |
|       P04        TP... U1,P15      Button DPAD right                                |
|       P05        TP... U1,P15      Button DPAD left                                 |
|       P06        TP... U1,P15      Button DPAD up                                   |
|       P07        TP... U1,P15      Button DPAD down                                 |
|       P08        TP... U1,P16      Button Shoulder R                                |
|       P09        TP... U1,P16      Button Shoulder L                                |
|       R00        TP... U1,SW3      Button X                                         |
|       R01        TP... U1,SW4      Button Y                                         |
|        -?-       TP... -           Button Debug aka R03 (if any exists)             |
|       VOLP       TP... P16,U6      Button Volume Plus  (Backlight when SELECT+VOLP) |
|       VOLN       TP... P16,U6      Button Volume Minus (Backlight when SELECT+VOLN) |
|       PWSW       TP... P15,U3      Button Power (High=Released)                     |
|       PENIRQ     TP... U1,U4       Touchscreen Pen Down                             |
|       R7         TP... U1,U10      Shell Open Magnet Sensor (HINGE)                 |
|       RTC_INT    TP... U9,U1       RTC Real-Time Clock Interrupt                    |
|       -          TP... U9,U1       RTC Real-Time Clock CS                           |
|       -          TP... U9,U1       RTC Real-Time Clock /SCK                         |
|       -          TP... U9,U1       RTC Real-Time Clock SIO                          |
|       SCL        TP... P9,U1,..    Primary I2C Bus Clock (Both Cameras,etc.)        |
|       SDA        TP... P9,U1,..    Primary I2C Bus Data  (Both Cameras,etc.)        |
|       -          TP... U8,U6       Primary I2C Bus Clock (for BPTWL xlated to 3.3V) |
|       -          TP... U8,U6       Primary I2C Bus Data  (for BPTWL xlated to 3.3V) |
|       SCL1       TP... U3,U6,U7    Secondary IC2 bus Clock (BPTWL/Wiper/Powerman)   |
|       SDA1       TP... U3,U6,U7    Secondary IC2 bus Data  (BPTWL/Wiper/Powerman)   |
|       SD10_CLK   TP... U1,P16      SD/MMC SD Slot Clock (typ 16MHz)                 |
|       SD10_CMD   TP... U1,P16      SD/MMC SD Slot Cmd                               |
|       SD10_DATA0 TP... U1,P16      SD/MMC SD Slot Data0                             |
|       SD10_DATA1 TP... U1,P16      SD/MMC SD Slot Data1                             |
|       SD10_DATA2 TP... U1,P16      SD/MMC SD Slot Data2                             |
|       SD10_DATA3 TP... U1,P16      SD/MMC SD Slot Data3                             |
|       SD10_WP    TP... U1,P16      SD/MMC SD Slot Write Protect Switch              |
|       SD10_CD    TP... U1,P16      SD/MMC SD Slot Card Detect Switch                |
|       SD10_VDD   TP... P16         SD/MMC SD Slot Supply (aka VDD33)                |
|       SD11_CLK   TP... U1,U5       SD/MMC eMMC Clock (typ 16MHz)                    |
|       -          TP... U1,U5       SD/MMC eMMC Cmd/Data0..3/CD/WP/VDDI              |
|       SPI_CS1    TP... U1,U3,U4    SPI Chip Select Powerman                         |
|       SPI_CS2    TP... U1,P5       SPI Chip Select Wifi FLASH chip select           |
|       SPI_CS3    TP... U1,U4       SPI Chip Select Touchscreen/Sound TSC            |
|       -          TP... P5,R122     SPI Wifi FLASH_WP (R122)                         |
|       SPI_SCK    TP... U1,P5,U3,U4 SPI Wifi/Pow/TSC Clock                           |
|       SPI_MISO   TP... U1,P5,U3,U4 SPI Wifi/Pow/TSC Master In Slave Out (Reply)     |
|       SPI_MOSI   TP... U1,P5,U3,U4 SPI Wifi/Pow/TSC Master Out Slave In (Command)   |
|       MC1_CLK    TP... U1,P1       NDS/DSi cartridge slot                           |
|       MC1_CS     TP... U1,P1       NDS/DSi cartridge slot                           |
|       MC1_RES    TP... U1,P1       NDS/DSi cartridge slot                           |
|       MC1_CS2    TP... U1,P1       NDS/DSi cartridge slot                           |
|       MC1_IREQ   TP... U1,P1       NDS/DSi cartridge slot                           |
|       MC1_VDD    TP... P1,Q6/Q7    NDS/DSi cartridge slot Power Supply (when on)    |
|       -          TP... U1,R28,Q7   NDS/DSi cartridge slot Power Enable              |
|       MC1_IO0    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO1    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO2    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO3    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO4    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO5    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO6    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_IO7    TP... U1,P1       NDS/DSi cartridge slot Data                      |
|       MC1_DET    TP... U1,P1       NDS/DSi cartridge slot Cart Insert Switch        |
|       -          TP... U1          NDS/DSi 2nd cart slot (NC in retail console)     |
|       -          TP... U1,U2       Main RAM Address A0..A22                         |
|       -          TP... U1,U2       Main RAM Data DQ0..DQ15                          |
|       -          TP... U1,U2       Main RAM /OE                                     |
|       -          TP... U1,U2       Main RAM /WE                                     |
|       -          TP... U1,U2       Main RAM CE1                                     |
|       -          TP... U1,U2       Main RAM CE2                                     |
|       -          TP... U1,U2       Main RAM CLK                                     |
|       -          TP... U1,U2       Main RAM /ADV                                    |
|       -          TP... U1,U2       Main RAM /LB                                     |
|       -          TP... U1,U2       Main RAM /UB                                     |
|       -          TP... U1          Main RAM A23 or Chipsel for debug ver 32Mbyte    |
|       -          TP... P5,U1       Wifi Atheros SDIO Clock (typ 16MHz?)             |
|       -          TP... P5,U1       Wifi Atheros SDIO Command                        |
|       -          TP... P5,U1       Wifi Atheros SDIO Data 1                         |
|       -          TP... P5,U1       Wifi Atheros SDIO Data 2                         |
|       -          TP... P5,U1       Wifi Atheros SDIO Data 3                         |
|       -          TP... P5,U1       Wifi Atheros SDIO Data 3                         |
|       -          TP... P5,U9       Wifi Atheros 32kHz (from RTC_FOUT to Wifi)       |
|       /WIFI_RST  TP... P5,U6       Wifi Atheros Reset?                              |
|       ATH_TX_H   TP... P5,U6       Wifi Atheros TX (for Wifi LED?)                  |
|       -          TP... P5,U1       Wifi SEL_ATH_L (near PENIRQ pin)                 |
|       WL_RXPE    TP... P5,U1,U6    Wifi RX something (for CPU and Wifi LED)         |
|       WL_TXPE    TP... P5,U1,U6    Wifi TX something (for CPU and Wifi LED)         |
|       -          TP... P5,U1       Wifi Mitsumi BBP_SLEEP                           |
|       -          TP... P5,U1       Wifi Mitsumi RF_SLEEP                            |
|       -          TP... P5,U1       Wifi Mitsumi BBP_SCS                             |
|       -          TP... P5,U1       Wifi Mitsumi RF_SCS                              |
|       -          TP... P5,U1       Wifi Mitsumi RB_RF_SDO                           |
|       -          TP... P5,U1       Wifi Mitsumi RB_RF_SDI                           |
|       -          TP... P5,U1       Wifi Mitsumi RB_RF_SCLK                          |
|       -          TP... P5,U1       Wifi Mitsumi CCA                                 |
|       -          TP... P5,U1       Wifi Mitsumi MCLK                                |
|       -          TP... P5,U1       Wifi Mitsumi TRDATA                              |
|       -          TP... P5,U1       Wifi Mitsumi TRCLK                               |
|       -          TP... P5,U1       Wifi Mitsumi TRRDY                               |
|       -          TP... P5          Wifi JTAG_TDO    (NC in console)                 |
|       -          TP... P5          Wifi JTAG_TDI    (NC in console)                 |
|       -          TP... P5          Wifi JTAG_TMS    (NC in console)                 |
|       -          TP... P5          Wifi JTAG_TCK    (NC in console)                 |
|       -          TP... P5          Wifi JTAG_TRST_L (NC in console)                 |
|       -          TP... P5          Wifi to MM3218.pin47 (0ohm)     (NC in console)  |
|       .          TP... P5          Wifi to MM3218.pin28 (0ohm+cap) (NC in console)  |
|       SND_SDI    TP... U1,U4       Audio I2S Data In   (Microphone)                 |
|       SND_SDO    TP... U1,U4       Audio I2S Data Out  (Speaker/Headphone)          |
|       SND_WS     TP... U1,U4       Audio I2S LR Clock  (typ 32kHz)                  |
|       SND_SCLK   TP... U1,U4       Audio I2S Bit Clock (typ 1MHz, aka SND_WS*2*16)  |
|       SND_MCLK   TP... U1,U4       Audio TSC Master Clock (typ 8MHz)                |
|       -          TP... U4,U7       Audio Volume Wiper (from I2C potentiometer)      |
|       SPLN       TP... P7,U4       Audio Speaker Left Minus                         |
|       SPLP       TP... P7,U4       Audio Speaker Left Plus                          |
|       SPRN       TP... P7,U4       Audio Speaker Right Minus                        |
|       SPRP       TP... P7,U4       Audio Speaker Right Plus                         |
|       HP#SP      TP... P4,U1,U4    Audio Headphone/Speaker switch                   |
|       SL         TP... P4,Q5,U4    Audio Headphone Left                             |
|       SR         TP... P4,Q4,U4    Audio Headphone Right                            |
|       -          TP... U1,U17      Audio Headphone Mute (from Main CPU GPIO)        |
|       -          TP... U4,U17,Q..  Audio Headphone Mute (via Q4/Q5 to SR/SL)        |
|       MIC        TP... P4,P23      Audio Microphone (via .. to LIN)                 |
|       LIN        TP... U4,U18      Audio Microphone Input                           |
|       -          TP... U4,U18      Audio Microphone Bias (to U18)                   |
|       BLA2       TP... P7,U3,U14   LCD Upper Screen Backlight Anode (ca. 15V)       |
|       BLC2       TP... P7,U3       LCD Upper Screen Backlight Cathode               |
|       LDB20      TP... P7,U1       LCD Upper Screen Blue Bit0                       |
|       LDB21      TP... P7,U1       LCD Upper Screen Blue Bit1                       |
|       LDB22      TP... P7,U1       LCD Upper Screen Blue Bit2                       |
|       LDB23      TP... P7,U1       LCD Upper Screen Blue Bit3                       |
|       LDB24      TP... P7,U1       LCD Upper Screen Blue Bit4                       |
|       LDB25      TP... P7,U1       LCD Upper Screen Blue Bit5                       |
|       LDR20      TP... P7,U1       LCD Upper Screen Red Bit0                        |
|       LDR21      TP... P7,U1       LCD Upper Screen Red Bit1                        |
|       LDR22      TP... P7,U1       LCD Upper Screen Red Bit2                        |
|       LDR23      TP... P7,U1       LCD Upper Screen Red Bit3                        |
|       LDR24      TP... P7,U1       LCD Upper Screen Red Bit4                        |
|       LDR25      TP... P7,U1       LCD Upper Screen Red Bit5                        |
|       LDG20      TP... P7,U1       LCD Upper Screen Green Bit0                      |
|       LDG21      TP... P7,U1       LCD Upper Screen Green Bit1                      |
|       LDG22      TP... P7,U1       LCD Upper Screen Green Bit2                      |
|       LDG23      TP... P7,U1       LCD Upper Screen Green Bit3                      |
|       LDG24      TP... P7,U1       LCD Upper Screen Green Bit4                      |
|       LDG25      TP... P7,U1       LCD Upper Screen Green Bit5                      |
|       COM2       TP... P7,P16      LCD Upper Screen VCOM Calibration                |
|       DCLK       TP... P7,P8,U1    LCD Both Screens Dot Clock  ;2.8MHz              |
|       LS         TP... P7,P8,U1    LCD Both Screens Latch Pulse;15.6kHz, 0.3us high |
|       SPL        TP... P7,P8,U1    LCD Both Screens Start Pulse;15.6kHz, 0.3us high |
|       GCK        TP... P7,P8,U1    LCD Both Screens Gate Clock ;15.6kHz, 9us low    |
|       REV        TP... P7,P8,U1    LCD Both Screens VcomFlicker;7kHz, toggle@15kHz  |
|       GSP        TP... P7,P8,U1    LCD Both Screens Gate Start ;60Hz, short low     |
|       INI        TP... P7,P8,U1    LCD Both Screens Init? MOD? ;usually high?       |
|       VSHD       TP... P7,P8,U19   LCD Both Screens Supply 3.3V                     |
|       VDD5       TP... P7,P8,P16   LCD Both Screens Supply 5.0V                     |
|       VDD-5      TP... P7,P8       LCD Both Screens Supply -5.0V                    |
|       VDD10      TP... P7,P8       LCD Both Screens Supply 10.0V                    |
|       BLA1       TP... P18,U3,U13  LCD Lower Screen Backlight Anode (ca. 14V)       |
|       BLC1       TP... P18,U3      LCD Lower Screen Backlight Cathode (ca. 0V)      |
|       LDB10      TP... P8,U1       LCD Lower Screen Blue Bit0                       |
|       LDB11      TP... P8,U1       LCD Lower Screen Blue Bit1                       |
|       LDB12      TP... P8,U1       LCD Lower Screen Blue Bit2                       |
|       LDB13      TP... P8,U1       LCD Lower Screen Blue Bit3                       |
|       LDB14      TP... P8,U1       LCD Lower Screen Blue Bit4                       |
|       LDB15      TP... P8,U1       LCD Lower Screen Blue Bit5                       |
|       LDR10      TP... P8,U1       LCD Lower Screen Red Bit0                        |
|       LDR11      TP... P8,U1       LCD Lower Screen Red Bit1                        |
|       LDR12      TP... P8,U1       LCD Lower Screen Red Bit2                        |
|       LDR13      TP... P8,U1       LCD Lower Screen Red Bit3                        |
|       LDR14      TP... P8,U1       LCD Lower Screen Red Bit4                        |
|       LDR15      TP... P8,U1       LCD Lower Screen Red Bit5                        |
|       LDG10      TP... P8,U1       LCD Lower Screen Green Bit0                      |
|       LDG11      TP... P8,U1       LCD Lower Screen Green Bit1                      |
|       LDG12      TP... P8,U1       LCD Lower Screen Green Bit2                      |
|       LDG13      TP... P8,U1       LCD Lower Screen Green Bit3                      |
|       LDG14      TP... P8,U1       LCD Lower Screen Green Bit4                      |
|       LDG15      TP... P8,U1       LCD Lower Screen Green Bit5                      |
|       COM1       TP... P8,P16      LCD Lower Screen VCOM Calibration                |
|       X-         TP... P10,U4      LCD Lower Screen Touchpad X-                     |
|       Y-         TP... P10,U4      LCD Lower Screen Touchpad Y-                     |
|       X+         TP... P10,U4      LCD Lower Screen Touchpad X+                     |
|       Y+         TP... P10,U4      LCD Lower Screen Touchpad Y+                     |
|       VIN        TP2   P11         Supply 4.6V External Power Supply Input (DC IN)  |
|       VGND       TP5   P11         Supply 0.0V External Power Supply Ground         |
|       VDET-      TP... U3,Q3       Supply 4.xV Shortcut with BT+ (via 0 ohm R71)    |
|       BT+        TP... P17,U3,U11  Supply 4.xV Battery Plus (red wire) 3.6V 800mAh  |
|       BT-        TP... P17         Supply 0.0V Battery GND  (black wire)            |
|       DET        TP... P15,U3      Supply Battery Middle Pin  (Low=Normal)          |
|       TH         TP... P15,U11     Supply Battery Thermal Sensor (on DPAD board)    |
|       PVDD       TP... U3,U9       Supply 4.xV Permanent Power for RTC              |
|       VDD12      TP... U3,U1       Supply 1.2V (Main CPU)                           |
|       VDD18      TP... P9,U3,U1,.. Supply 1.8V (Main CPU and many things)           |
|       VDD28      TP... P9,U12,U6   Supply 2.8V (for Cameras and BPTWL)              |
|       VDD33      TP... U3,U1,..    Supply 3.3V (Main CPU and many things)           |
|       VDD42      TP... P15,P9,U3.. Supply 4.2V (for LEDs) (and U19)                 |
|       B+         TP... U3,U4,U19.. Supply 4.xV (for Speakers, or everything?) U11   |
|       SG         TP... U3          Supply 0.0V Ground or Audio GND or so            |
|       GND1       TP... ..          Supply 0.0V Ground (near COM1/COM2 testpoints)   |
|       GND2       TP... ..          Supply 0.0V Ground (near wifi connector)         |
|       EXTB+      TP... U3,U11,Q1   Charger 4.xV or 0V (EXTB+ comes from VIN via Q1) |
|       Rosc       TP... U3,U11      Charger 1.0V ?                                   |
|       RICHG      TP... U3,U11      Charger 0.4V ?                                   |
|       ORANGE     TP... P15,U11     LED Battery Charge                               |
|       BLUE       TP... P15,U6,Q11  LED Power On/Good                                |
|       YELLOW     TP... P15,U6,Q12  LED Wifi                                         |
|       RED        TP... P15,U6      LED Power On/Low                                 |
|       CAM_LED    TP... P9,U6,Q13   LED Camera                                       |
|       CAM_D0     TP... P9,U1       Both Cameras Data Bit0                           |
|       CAM_D1     TP... P9,U1       Both Cameras Data Bit1                           |
|       CAM_D2     TP... P9,U1       Both Cameras Data Bit2                           |
|       CAM_D3     TP... P9,U1       Both Cameras Data Bit3                           |
|       CAM_D4     TP... P9,U1       Both Cameras Data Bit4                           |
|       CAM_D5     TP... P9,U1       Both Cameras Data Bit5                           |
|       CAM_D6     TP... P9,U1       Both Cameras Data Bit6                           |
|       CAM_D7     TP... P9,U1       Both Cameras Data Bit7                           |
|       CAM_RST    TP... P9,U1       Both Cameras Reset?                              |
|       HSYNC      TP... P9,U1       Both Cameras Hsync                               |
|       VSYNC      TP... P9,U1       Both Cameras Vsync                               |
|       RCLK       TP... P9,U1       Both Cameras Data Clock (8MHz, unless blanking)  |
|       CKI        TP... P9,U1       Both Cameras Master Clock (8MHz) (or off)        |
+-------------------------------------------------------------------------------------+
```


### Cut-Links

```
+-----------------------------------------------------------------------+
|       CL1   VDD12    to/near Powerman                                 |
|       CL2                                                             |
|       CL3   VDD18    to/near Powerman                                 |
|       CL4    ?       near Powerman (above L3)                         |
|       CL5   VDD33    PCB top side (near Powerman)                     |
|       CL6   VDD5     near lower screen connector (F)                  |
|       CL7   BLC1     near lower screen connector                      |
|       CL8                                                             |
|       CL9   GNDed     to/near Powerman (near ADPO pin)                |
|       CL10  GNDed     to/near Powerman (near VDD5 pin)                |
|       CL11                                                            |
|       CL12                                                            |
|       CL13                                                            |
|       CL14  SDIO CLK   to/near wifi connector                         |
|       CL15  BB RF CLK  to/near wifi connector                         |
|       CL16  Wifi MCLK  to/near wifi connector                         |
|       CL17                                                            |
|       CL18                                                            |
|       CL19                                                            |
|       CL20                                                            |
|       CL21  VDD42    to/near Powerman                                 |
|       CL22  VDD10    to DA1 and C5, near DPAD board connector         |
|       CL23  VDD-5    near lower screen connector                      |
|       CL24                                                            |
|       CL25  ?        PCB top side (near Button B)                     |
|       CL26                                                            |
|       CL27  ?        PCB top side (near Button B) (D)                 |
|       CL28  ?        PCB top side (near Button B) (D)                 |
|       CL29                                                            |
|       CL30                                                            |
|       CL31                                                            |
|       CL32                                                            |
|       CL33                                                            |
|       CL34  SND_SDI   near TSC chip                                   |
|       CL35  SND_SDO   near TSC chip                                   |
|       CL36  SND_WS    near TSC chip                                   |
|       CL37  SND_SCLK  near TSC chip                                   |
|       CL38  SND_MCLK  near TSC chip                                   |
|       CL39                                                            |
+-----------------------------------------------------------------------+
```


### Short-Links

```
+-----------------------------------------------------------------------+
|       R122  FLASH_WP to VDD33 (not installed)                         |
+-----------------------------------------------------------------------+
```




