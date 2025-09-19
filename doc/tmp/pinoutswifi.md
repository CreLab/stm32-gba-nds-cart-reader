# Pinouts - Wifi


### NDS RFU Daughter Board (Firmware FLASH, Wifi BB/RF Chips)

```
+------------------------------------------------------------------------------------+
|       1 N/A      6 FMW.CLK    11 ENABLE 16 RX.DTA? 21 BB./CS     26 22MHz   31 GND |
|       2 GND      7 FMW./SEL   12 GND    17 TX.MAIN 22 RF./CS     27 GND     32 GND |
|       3 high?    8 FMW.DTA.Q  13 GND    18 GND     23 BB.RF.CLK  28 VDD3.3  33 GND |
|       4 RXTX.ON  9 FMW.DTA.D  14 TX.ON  19 TX.CLK  24 BB.RF.RD   29 VDD1.8         |
|       5 FMW./WP  10 FMW./RES  15 RX.ON  20 TX.DTA  25 BB.RF.WR   30 GND            |
+------------------------------------------------------------------------------------+
```


### NDS-Lite RFU Daughter Board DWM-W006 (Firmware FLASH, Wifi BB/RF Chip)

```
+--------------------------------------------------------------------------------+
|       1 GND      6 GND       11 BB.RF.WR  16 VDD3.3   21 RF.SLEEP  26 FMW.Q    |
|       2 TXPE     7 TRCLK     12 BB.RF.CLK 17 GND      22 FMW./RES  27 FMW./WP  |
|       3 RXPE     8 TRDATA    13 GND       18 RF./CS   23 GND       28 FMW./CS  |
|       4 CCA      9 GND       14 MCLK      19 BB.SLEEP 24 FMW.CLK   29 LD  ;hi? |
|       5 TRRDY    10 BB.RF.RD 15 GND       20 BB./CS   25 FMW.D     30 GND      |
+--------------------------------------------------------------------------------+
```

<https://fccid.io/EW4DWMW006/Label/ID-label-format-and-location-706511.pdf>

### Wifi RF Chip: RF9008, 0441, E0121Q (32 pin)

```
+--------------------------------------------------------------------------+
|       1       5       9       13      17         21 RF.CLK  25        29 |
|       2       6       10      14 GND  18         22         26        30 |
|       3       7       11      15      19 RF.RD   23         27        31 |
|       4       8       12      16      20 RF./CS  24         28        32 |
+--------------------------------------------------------------------------+
```

Pin19 RF.RD (oops, should be WR, maybe I\'ve exchanged RD-WR?)
Pin20 RF./CS (via 10ohm)
Pin21 RF.CLK (via 10ohm)
Resembles RF2958 datasheet\...?

### Wifi BB Chip: Mitsumi, Japan, 4418, MM3155 (48 pins)

```
+--------------------------------------------------------------------------------+
|       1 GND   7       13 GND     19      25       31         37 TX.MAIN 43     |
|       2       8       14         20      26       32 BB./CS  38 RX.DTA? 44     |
|       3       9       15 BB.CLK  21      27       33 TX.DTA  39 RX.ON   45 GND |
|       4       10      16 BB.WR   22      28 RST   34 RXTX.ON 40 TX.ON   46     |
|       5       11      17 BB.RD   23      29       35 TX.CLK  41         47     |
|       6       12      18 22MHz   24      30       36         42         48     |
+--------------------------------------------------------------------------------+
```

Pin15 BB.CLK (via 10ohm to RFU.23)
Pin16 BB.WR (RFU.25)
Pin17 BB.RD (RFU.24)
Pin18 22MHz (via 50ohm)
Pin28 RST (same as FMW./RES)
Pin32 BB./CS (RFU.21)
The chip is roughly resembling HSP3824/HFA3824A/HFA3860A/HFA3860B (though pinout and registers aren\'t compatible).

### NDS-LITE BB/RF-Chip Mitsumi MM3218 (56 pins)

```
+-------------------------------------------------------------------------------------+
|       1-VDD18 8-GND   15-CCA    22-GND   29-VDD33     36-BBRF_SDO 43-VDD18 50-      |
|       2-GND   9-NC    16-TXPE   23-MCLK  30-          37-BB_SCS   44-...   51-      |
|       3-VDD18 10-GND  17-RXPE   24-VDD18 31-          38-RF_SCS   45-VDD33 52-VDD18 |
|       4-Ant   11-GND  18-TRRDY  25-NC    32-VDD18     39-GND      46-...   53-NC    |
|       5-Ant'  12-GND  19-TRDATA 26-22MHz 33-VDD18     40-VDD33    47-...   54-NC    |
|       6-VDD18 13-NC   20-VDD33  27-22MHz 34-BBRF_SCLK 41-RF_SLEEP 48-VDD33 55-NC    |
|       7-VDD18 14-/RES 21-TRCLK  28-      35-BBRF_SDI  42-BB_SLEEP 49-GND   56-NC    |
+-------------------------------------------------------------------------------------+
```

Note: Pinout should be same as in DSi (see DSi pinout for details).

### TX Signal/Timing Chart (Host Game)

```
+---------------------------------------------------------------------------+
|       RX.DTA?  __________________________________________________________ |
|       RXTX.ON  __-----------------------_________________________________ |
|       RX.ON    __---_______-------------_________________________________ |
|       TX.ON    _____-------______________________________________________ |
|       TX.MAIN  ________----______________________________________________ |
|       TX.CLK   _____#__####______________________________________________ |
|       TX.DTA   _____#__####______________________________________________ |
+---------------------------------------------------------------------------+
```

This example shows a host sending beacons. The pre-beacon receive period is probably to sense conflicts with other transmitters. The post-beacon receive period is to get responses from other players. The two transmit parts are: The hardware header, followed by inactivity on the tx pins during the rest of the preamble period, then followed by the actual IEEE frame. The rest of the time is spent in idle mode to reduce power consumption.

### RX Signal/Timing Chart (Join Game)

```
+---------------------------------------------------------------------------+
|       RX.DTA?  __________________________________________________________ |
|       RXTX.ON  -----------------------------------------------______----- |
|       RX.ON    -----------------------------------------------_________-- |
|       TX.ON    __________________________________________________________ |
|       TX.MAIN  __________________________________________________________ |
|       TX.CLK   __________________________________________________________ |
|       TX.DTA   _______________________________________________---________ |
+---------------------------------------------------------------------------+
```

This example shows a client trying to receive beacons, so most of the time is spent in receive mode (the short idle periods are probably occuring when it is switching to another channel). Once when it has associated with a host, the client may spend more time in idle mode, and needs to be in receive mode only when expecting to receive beacons or other data.



