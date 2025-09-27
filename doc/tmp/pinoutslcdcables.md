# Pinouts - LCD Cables


### Advance Gameboy Display Socket

```
+----------------------------------------------------------------------------------+
|       1 ?     6 GND    11 LDR2   16 LDG2   21 LDB3   26 SPS     31 P2-VSS  36 V4 |
|       2 VSHD  7 VSHD   12 LDR1   17 LDG1   22 LDB2   27 ?       32 P2-VCC  37 V3 |
|       3 DCK   8 LDR5   13 LDG5   18 GND    23 LDB1   28 MOD     33 ?       38 V2 |
|       4 LP    9 LDR4   14 LDG4   19 LDB5   24 SPL    29 VCOM    34 VDD5    39 V1 |
|       5 PS    10 LDR3  15 LDG3   20 LDB4   25 CLS    30 P2-VEE  35 GND     40 V0 |
+----------------------------------------------------------------------------------+
```


### GBA SP Display Socket

```
+------------------------------------------------------------------------------------+
|       1 VSHD 5 VSHD  9 LDR3   13 LDG4  17 GND   21 LDB2  25 SPS   29 P2VSS 33 U83  |
|       2 DCK  6 GND   10 LDR2  14 LDG3  18 LDB5  22 LDB1  26 MOD   30 COM   34 VDD5 |
|       3 LP   7 LDR5  11 LDR1  15 LDG2  19 LDB4  23 SPL   27 REVC  31 VDD5          |
|       4 PS   8 LDR4  12 LDG5  16 LDG1  20 LDB3  24 CLS   28 P2VDD 32 GND           |
+------------------------------------------------------------------------------------+
```


### GBA Micro Display Sockets

```
+---------------------------------------------------------------------------+
|       __GBA Mirco display socket (P1)____________________________________ |
|       1-PS    6-5bit  11-MD    16-5bit  21-5bit  26-CL             31-GND |
|       2-RV    7-5bit  12-SL    17-5bit  22-5bit  27-SS             32-GND |
|       3-GND   8-5bit  13-CK    18-5bit  23-5bit  28-via C5 to VR1  33-V10 |
|       4-5bit  9-LP    14-GND   19-5bit  24-5bit  29-V5             34-V-5 |
|       5-5bit  10-VD   15-5bit  20-GND   25-5bit  30-to VR1                |
|       __GBA Mirco backlight socket (P3)__________________________________ |
|       1-LC  2-LC  3-LA  4-LA                                              |
+---------------------------------------------------------------------------+
```


### NDS Upper/Lower Display Sockets

```
+-------------------------------------------------------------------------------------+
|       ___NDS upper screen/upper backlight/speakers socket (P3)_____________________ |
|       1-SPLO 7-PS2   13-LDR2  19-GND   25-LDG2  31-LDB2  37-MOD2  43-VDD15  49-SPRO |
|       2-SPLO 8-REV2  14-LDR1  20-DCLK2 26-LDG1  32-LDB1  38-GND   44-VDD-5  50-GND  |
|       3-SSC2 9-GND   15-LDR0  21-GND   27-LDG0  33-LDB0  39-VDD5  45-VDD-10 51-GND  |
|       4-ASC2 10-LDR5 16-LS2   22-LDG5  28-LDB5  34-GCK2  40-VDD10 46-LEDC2          |
|       5-GND  11-LDR4 17-VSHD  23-LDG4  29-LDB4  35-GSP2  41-COM2  47-LEDA2          |
|       6-SPL2 12-LDR3 18-DISP1 24-LDG3  30-LDB3  36-GND   42-GND   48-SPRO           |
|       ___NDS lower screen socket (P4)______________________________________________ |
|       1-SSC1 6-REV1  11-LDR2  16-DISP0 21-LDG4  26-LDB5  31-LDB0  36-GND  41-VDD15  |
|       2-ASC1 7-GND   12-LDR1  17-SPL1  22-LDG3  27-LDB4  32-GCK1  37-?    42-VDD10  |
|       3-GND  8-LDR5  13-LDR0  18-DCLK1 23-LDG2  28-LDB3  33-GSP1  38-VDD5 43-GND    |
|       4-?    9-LDR4  14-LS1   19-GND   24-LDG1  29-LDB2  34-VSHD  39-COM1 44-VDD-5  |
|       5-PS1  10-LDR3 15-VSHD  20-LDG5  25-LDG0  30-LDB1  35-MOD1  40-GND  45-VDD-10 |
|       ___NDS lower backlight socket (P5)____   ___NDS touchscreen socket (P6)______ |
|       1:LEDA1  2:LEDA1  3:LEDC1  4:LEDC1       1:Y-    2:X-    3:Y+    4:X+         |
+-------------------------------------------------------------------------------------+
```


### NDS-Lite Upper/Lower Display Sockets

```
+-------------------------------------------------------------------------------------+
|       ___NDS-Lite upper screen/upper backlight/speakers socket (P3)________________ |
|       1-VDD-5 6-MOD    11-LD2xx 16-LD2xx 21-LD2xx 26-LD2xx 31-LS   36-GND   41-SPRO |
|       2-VDD10 7-GSP    12-LD2xx 17-LD2xx 22-LD2xx 27-LD2xx 32-VSHD 37-COM2  42-SG   |
|       3-VDD5  8-GCK    13-LD2xx 18-GND   23-LD2xx 28-GND   33-GND  38-LEDA2 43-SG   |
|       4-GND   9-LD2xx  14-LD2xx 19-LD2xx 24-LD2xx 29-DCLK  34-xx2? 39-LEDC2 44-SPLO |
|       5-VSHD  10-LD2xx 15-LD2xx 20-LD2xx 25-LD2xx 30-SPL   35-REV  40-SPRO  45-SPLO |
|       ___NDS-Lite lower screen/lower backlight (P4)________________________________ |
|       1-VDD-5 6-MOD    11-LD1xx 16-LD1xx 21-LD1xx 26-LD1xx 31-LS   36-GND           |
|       2-VDD10 7-GSP    12-LD1xx 17-LD1xx 22-LD1xx 27-LD1xx 32-VSHD 37-COM1          |
|       3-VDD5  8-GCK    13-LD1xx 18-GND   23-LD1xx 28-GND   33-GND  38-LEDA1         |
|       4-GND   9-LD1xx  14-LD1xx 19-LD1xx 24-LD1xx 29-DCLK  34-xx1? 39-LEDC1         |
|       5-VSHD  10-LD1xx 15-LD1xx 20-LD1xx 25-LD1xx 30-SPL   35-REV                   |
|       ___NDS-Lite touchscreen socket (P6)______   ___NDS-Lite white coax (P12)_____ |
|       1:X-  2:Y-  3:X+  4:Y+                      Center:MICIN  Shield:GND          |
+-------------------------------------------------------------------------------------+
```




