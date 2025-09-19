# Pinouts - Power Switches, DC/DC Converters, Reset Generators


### Advance Gameboy Power Switch (2-position slider, with two common pins)
### GBA SP Power Switch (same as GBA)

```
+-----------------------------------------------------------------------+
|       1 via resistor to GND (OFF)                                     |
|       2 VS (BT+) (ON)                                                 |
|       C VCC (to board)                                                |
+-----------------------------------------------------------------------+
```


### GBA Micro Power Switch
Same as GBA and GBA SP, but Pin 1 and 2 exchanged.

### Advance Gameboy Cartridge Slot Switch (integrated 4pin micro switch)
### GBA SP Cartridge Slot Switch (separate 4pin micro switch)

```
+-----------------------------------------------------------------------+
|       C1 VDD35  (to S2 when PRESSED, to S1 when RELEASED)             |
|       S1 VDD3   (to C2 when PRESSED, to C1 when RELEASED)             |
|       C2 IN35   (to S1 when PRESSED)                                  |
|       S2 VDD5   (to C1 when PRESSED)                                  |
+-----------------------------------------------------------------------+
```

Pressed=8bit DMG/MGB/CGB cart, Released=32bit GBA cart (or no cart inserted)
GBA: switch integrated in cart socket, GBA-SP: separate switch next to socket.

### Advance Gameboy Power Controller (M 121 514X) (U4)

```
+-----------------------------------------------------------------------------------+
|       1-VIN    2-VOUT5  3-CSS5    4-VDRV5  5-GND    6-VDRV3    7-CSS3    8-VOUT3  |
|       9-VCNT5  10-CSCP  11-REGEXT 12-VDD3  13-VDD2  14-/RESET  15-LOWBAT 16-VDD13 |
+-----------------------------------------------------------------------------------+
```

/RESET is passed to the CPU, and then forwarded to /RES pin on cart slot.

### Advance Gameboy LCD Regulator (AGB-REG IR3E09N) (U3)

```
+-------------------------------------------------------------------------------------+
|       1  2  3    4      5   6   7   8   9   10   11  12  13  14  15  16   17     18 |
|       ?  ?  REVC U3-COM V0  V1  ?   ?   ?   GND  ?   V2  ?   V3  V4  VDD5 U3-VDD ?  |
+-------------------------------------------------------------------------------------+
```


### GBA SP Power Controller 1 (S6403 AU227 9276) (U4)

```
+------------------------------------------------------------------------------------+
|       1-VCC    2-SCP1   3-SCP2 4-VDRV3 5-VOUT3/VDD3 6-VDD2  7-VOUT1/VDD1  8-VDRV1  |
|       9-LOWBAT 10-VCNT5 11-LS5 12-?    13-GND       14-?    15-VOUT5/VDD5 16-VDRV5 |
+------------------------------------------------------------------------------------+
```


### GBA SP Power Controller 2 (2253B 2808) (U5)

```
+---------------------------------------------------------------------------+
|       1-TIN     2-U5C3     3-ADJ  4-U5VDD  5-VIN   6-?    7-U57  8-?      |
|       9-to-C29  10-to-C30  11-?   12-GND   13-VS   14-S-  15-S+  16-U5OUT |
+---------------------------------------------------------------------------+
```


### GBA Micro - Power Managment Device (U2)

```
+-----------------------------------------------------------------------+
|      1 via C43 to GND                                                 |
|      2 via R24 to C34 to R25 back to U2.2                             |
|      3 via C35 to GND                                                 |
|      4 via C36 to GND                                                 |
|      5                                                                |
|      6 audio.in ? (see BP)                                            |
|      7   via C48 to GND                                               |
|      8   via R21 to C46 to C47 to C38 to R23 to phones                |
|      9  VL (to U4)                                                    |
|      10  via R27 to C33 to C44 to C49 to R22 to phones                |
|      11  via C45 to GND                                               |
|      12 audio.in ? (see BP)                                           |
|      13  via C41 to GND                                               |
|      14 phones (switch)                                               |
|      15 phones (tip via R22)                                          |
|      16 phones (mid via R23)                                          |
|      17 VCS                                                           |
|      18 SP                                                            |
|      19 GND                                                           |
|      20 LB                                                            |
|      21 via C52 to GND                                                |
|      22 via C53 to GND                                                |
|      23 RS         (looks like RESET output)                          |
|      24 to R37/C56 (looks like RESET input)                           |
|      25                                                               |
|      26                                                               |
|      27 via C54 to V3                                                 |
|      28 V3                                                            |
|      29 GND                                                           |
|      30 V3                                                            |
|      31 VC                                                            |
|      32 to C58                                                        |
|      33 to R41/C58                                                    |
|      34 GND                                                           |
|      35                                                               |
|      36 VC                                                            |
|      37 VC                                                            |
|      38                                                               |
|      39 V5                                                            |
|      40 GND                                                           |
|      41 GND                                                           |
|      42                                                               |
|      43                                                               |
|      44                                                               |
|      45 B+                                                            |
|      46 S-                                                            |
|      47 S+                                                            |
|      48                                                               |
+-----------------------------------------------------------------------+
```


### GBA Micro - Volume/Backlight Level Up/Down Controller (U5)

```
+-----------------------------------------------------------------------+
|       1-     5-GND  9-      13-XD      17-     21-     25-    29-     |
|       2-     6-GND  10-     14-to U4.7 18-XR   22-CN   26-    30-     |
|       3-     7-     11-XC   15-        19-V+   23-CNS  27-    31-BP   |
|       4-LN   8-     12-GND  16-        20-V-   24-     28-V3  32-     |
+-----------------------------------------------------------------------+
```


### NDS Powermanagment Device (Mitsumi 3152A) (U3)

```
+--------------------------------------------------------------------------+
|       1 R50-EXTB+        17               33 LEDC1           49 VCNT5    |
|       2 R39-ORANGE       18               34 GND             50          |
|       3 GND              19 VQ5           35 LEDC2           51 RST      |
|       4                  20               36                 52          |
|       5 Rxx-Q4           21               37 U10-LEDA2       53          |
|       6 INS+             22 GND           38                 54          |
|       7 INS-             23 VQ5           39 MIC.C53-AIN     55 VQ5      |
|       8                  24               40 MIC.TSC.AUX     56 R24-SR   |
|       9 VDET             25 VDD3.3        41 GND             57          |
|       10 PVDD            26 GND           42 R38-RED         58 R22-SL   |
|       11                 27 CL60-VDD3.3   43 R37-GREEN       59 GND      |
|       12 PWSW            28 VSHD          44 VDD3.3          60 VR3.PIN2 |
|       13                 29               45 PWM.SPI.CLK     61          |
|       14 GND             30 VDD5          46 PWM.SPI.D       62          |
|       15 GND             31 U9-LEDA1      47 PWM.SPI.Q       63          |
|       16 VQ5             32               48 PWM.SPI.SEL     64 GND      |
+--------------------------------------------------------------------------+
```


### NDS-LITE Powermanagment Device (Mitsumi 3205B) (U3)

```
+------------------------------------------------------------------------------+
|       1 SW               17               33 LEDC1           49 VCNT5        |
|       2 R50-EXTB+        18               34 GND             50              |
|       3 R39-ORANGE       19 VQ5           35 LEDC2           51 RST          |
|       4 GND              20               36                 52              |
|       5                  21               37 U10-LEDA2       53              |
|       6 R30-Q4           22 GND           38                 54              |
|       7 INS+             23 VQ5           39 MIC.C53-AIN     55 CL63-VQ5     |
|       8 INS-             24               40 MIC.TSC.AUX     56 R24-SR       |
|       9 VDET             25 VDD3.3        41 GND             57 SPRO         |
|       10 PVDD            26 GND           42 R38-RED         58 SPLO         |
|       11                 27 CL60-VDD3.3   43 R37-GREEN       59 R22-SL       |
|       12 PWSW            28 VSHD          44 VDD3.3          60 GND          |
|       13 GND             29               45 PWM.SPI.CLK     61 R79-VR3.PIN2 |
|       14 GND             30 VDD5          46 PWM.SPI.D       62              |
|       15 GND             31 U9-LEDA1      47 PWM.SPI.Q       63              |
|       16 VQ5             32               48 PWM.SPI.SEL     64              |
+------------------------------------------------------------------------------+
```


### NDS-LITE Power Switch

```
+-----------------------------------------------------------------------+
|       1 PWSW (grounded when switch is pulled)                         |
|       2 GND                                                           |
|       3 GND                                                           |
|       4 NC? (grounded when switch is not pulled)                      |
+-----------------------------------------------------------------------+
```




