# AUX Sound/Headphone Socket and Battery/Power Supply


### GBA, GBA-Micro, NDS, and NDS-Lite: Stereo Sound Connector (3.5mm, female)

```
+-----------------------------------------------------------------------+
|       Tip     Audio Left         ___ ___ _____.-----------.           |
|       Middle  Audio Right       (___|___|_____|           |           |
|       Base    Ground              L   R   GND '-----------'           |
+-----------------------------------------------------------------------+
```

The NDS socket doesn\'t fully match regular 3.5mm plugs, one needs to cut-off a portion of the DS case to be able to fully insert the plug, which still requires a lot of pressure, furthermore, when fully inserted, left/right become shortcut to mono, so one needs to pull-back the plug a bit to gain stereo output.

### GBA SP and NDS - Power/Headphone Socket (EXT.2)

```
+--------------------------------------------------------------------------+
|       Pin SP   NDS  Expl.                                                |
|       1   P31  SL   Audio LOUT                          _____________    |
|       2   P32  VIN  Supply Input (DC 5.2V)           SW| 5   ___   1 |SL |
|       3   P33  SR   Audio ROUT                         | ----   ---- |   |
|       4   P34  SG   Audio GND (via 100uF to GND)       |_6__4   3__2_|   |
|       5   P35  SW   Audio Speaker Disable (GND=Dis)    GND SG\_/SR VIN   
|       6        GND  Supply GND                                           |
|       Shield        GND                                                  |
+--------------------------------------------------------------------------+
```

External power input is used to charge the built-in battery, it cannot be used to run the SP without that battery.

### NDS-Lite - Power Socket

```
+---------------------------------------------------------------------------+
|       Pin  Expl.                                          __________      |
|       1    Supply Input (DC 5.2V)                        /  ======  \     
|       2    Supply GND                                GND |___2__1___| VIN |
+---------------------------------------------------------------------------+
```


### GBA-Micro - Power Socket
Uses an 8pin socket (which combines SIO and Power), for pin-outs, see
- [AUX Link Port](./auxlinkport.md)

### External Power Supply
GBA: DC 3.3V (no separate power socket, requires 2xAA-battery-shaped adapter)
GBA-SP/NDS: DC 5.2V (or DC 5V) (special connector on power/headphone socket)
NDS-Lite: DC 5.2V (or DC 5V) (another special connector on power socket)

### Internal Battery Supply
GBA: 2xAA (3V)
GBA-SP: Li-ion 3.7V, 600mAh (built-in, recharge-able)
GBA-Micro: Li-ion 3.8V, 460mAh (built-in, recharge-able)
NDS: Li-ion 3.7V, 850mAh (built-in, recharge-able)
NDS-Lite: Li-ion 3.7V, 1000mAh (built-in, recharge-able)

### Using PC +5V DC as Power Supply
Developers whom are using a PC for GBA programming will probably want to use the PC power supply (gained from disk drive power supply cable) for the GBA as well rather than dealing with batteries or external power supplies.
GBA: To lower the voltage to approximately 3 Volts use two diodes, type 1N 4004 or similar, the ring printed onto the diodes points towards the GBA side, connected as such:

```
+-----------------------------------------------------------------------+
|       PC +5V (red)   --------|>|---|>|--------  GBA BT+               |
|       PC GND (black) -------------------------  GBA BT-               |
+-----------------------------------------------------------------------+
```

GBA SP, GBA Micro, NDS, and NDS-Lite: Works directly at +5V connected to EXT.2 socket (not to the internal battery pins), without any diodes.



