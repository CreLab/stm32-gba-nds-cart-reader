# DSi TSC\[1:xxh\], DAC and ADC Routing, PGA, Power-Controls and MISC Logic


### TSC\[1:01h..1Dh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0  Reserved. Do not write to these registers.                 |
+-----------------------------------------------------------------------+
```


### TSC\[1:1Eh\] - Headphone and Speaker Amplifier Error Control (00h)

```
+--------------------------------------------------------------------------------+
|       7-2  Reserved                                                            |
|       1    Reset HPL/HPR power-up bits upon short-circuit detect (0=Yes, 1=No) |
|       0    Reset SPL/SPR power-up bits upon short-circuit detect (0=Yes, 1=No) |
+--------------------------------------------------------------------------------+
```

The HPL/HPR auto-reset occurs only if TSC\[1:1Fh\].Bit1=1 (action=power down).

### TSC\[1:1Fh\] - Headphone Drivers (04h)

```
+-----------------------------------------------------------------------------+
|       7    HPL output driver (0=Powered down, 1=Powered up)                 |
|       6    HPR output driver (0=Powered down, 1=Powered up)                 |
|       5    Reserved. Write only zero to this bit.                           |
|       4-3  Output common-mode voltage (0=1.35V, 1=1.5V, 2=1.65V, 3=1.8V)    |
|       2    Reserved. Write only 1 to this bit. (!!!)                        |
|       1    Action when short-circuit protection is enabled/detected,        |
|                0=Limit the maximum current to the load.                     |
|                1=Power down the output driver.                              |
|       0    Short-circuit detected on the headphone driver (0=No, 1=Yes) (R) |
+-----------------------------------------------------------------------------+
```


### TSC\[1:20h\] - Class-D Speaker Amplifier (06h)

```
+-------------------------------------------------------------------------------+
|       7    Left-channel class-D output driver  (0=Powered down, 1=Powered up) |
|       6    Right-channel class-D output driver (0=Powered down, 1=Powered up) |
|       5-1  Reserved. Write only the reset value (00011b) to these bits (!!!)  |
|       0    Short-circuit is detected on the class-D driver (0=No, 1=Yes) (R)  |
+-------------------------------------------------------------------------------+
```

Bit0 is Valid only if class-D amplifier is powered up. For short-circuit flag sticky bit, see TSC\[0:2Ch\].

### TSC\[1:21h\] - HP Output Drivers POP Removal Settings (3Eh)

```
+-----------------------------------------------------------------------------------+
|       7    If power down sequence is activated by device software power down      |
|            using TSC[1:2Eh].Bit7 then power down DAC,                             |
|              0: simultaneously with the HP and SP amplifiers.                     |
|              1: after HP and SP amplifiers are completely powered down.           |
|              (the latter setting is to optimize power-down POP).                  |
|       6-3  Driver power-on time (at 8.2MHz) (1=15.3us, 2=153us, 3=1.53ms,         |
|              4=15.3ms,5=76.2ms, 6=153ms, 7=304ms, 8=610ms, 9=1.22s, 10=3.04s,     |
|              11=6.1s, 12..15=Reserved)                                            |
|       2-1  Driver ramp-up step time (8.2MHz) (0=0ms, 1=0.98ms, 2=1.95ms, 3=3.9ms) |
|       0    Weakly driven output common-mode voltage is generated from,            |
|              0=resistor divider of the AVDD supply.                               |
|              1=band-gap reference.                                                |
+-----------------------------------------------------------------------------------+
```


### TSC\[1:22h\] - Output Driver PGA Ramp-Down Period Control (00h)

```
+----------------------------------------------------------------------------------+
|       7    Reserved. Write only the reset value to this bit.    (USED on DSi!)   |
|       6-4  Speaker Power-Up Wait Time (at 8.2MHz) (0=0 ms, 1=3.04 ms, 2=7.62 ms, |
|              3=12.2 ms, 4=15.3 ms, 5=19.8 ms, 6=24.4 ms, 7=30.5 ms)              |
|       3-0  Reserved. Write only the reset value to these bits.                   |
+----------------------------------------------------------------------------------+
```


### TSC\[1:23h\] - DAC_L and DAC_R Output Mixer Routing (00h)

```
+------------------------------------------------------------------------------------+
|       7-6  DAC_L route      (0=Nowhere, 1=To L-Mixer, 2=Direct to HPL, 3=Reserved) |
|       5    MIC input routed to the left-channel mixer amplifier      (0=No, 1=Yes) |
|       4    AUX1 input routed to the left-channel mixer amplifier     (0=No, 1=Yes) |
|       3-2  DAC_R route      (0=Nowhere, 1=To R-Mixer, 2=Direct to HPR, 3=Reserved) |
|       1    AUX1 input routed to the right-channel mixer amplifier    (0=No, 1=Yes) |
|       0    HPL driver output routed to HPR driver (for differential) (0=No, 1=Yes) |
+------------------------------------------------------------------------------------+
```


### TSC\[1:24h\] - Analog Volume to HPL (Left Headphone) (7Fh)
### TSC\[1:25h\] - Analog Volume to HPR (Right Headphone) (7Fh)
### TSC\[1:26h\] - Analog Volume to SPL (Left Speaker) (7Fh)
### TSC\[1:27h\] - Analog Volume to SPR (Right Speaker) (7Fh)

```
+--------------------------------------------------------------------------------+
|       7    Analog volume control routed to HPx/SPx output driver (0=No, 1=Yes) |
|       6-0  Analog volume control gain (non-linear) (0 dB to -78 dB)            |
+--------------------------------------------------------------------------------+
```

See Table 5-37 and Table 5-38, uh?

### TSC\[1:28h\] - HPL Driver (Left Headphone) (02h)
### TSC\[1:29h\] - HPR Driver (Right Headphone) (02h)

```
+-------------------------------------------------------------------------------------+
|       7    Reserved. Write only zero to this bit.                                   |
|       6-3  HPx driver PGA  (0..9 = 0dB..9dB, 10..15=Reserved)                       |
|       2    HPx driver      (0=Muted, 1=Not muted)                                   |
|       1    HPx driver during power down (0=Weakly driven to a common mode,          |
|             1=High-impedance)                                                       |
|       0    All programmed gains to HPx have been applied (0=Not yet, 1=Yes/all) (R) |
+-------------------------------------------------------------------------------------+
```


### TSC\[1:2Ah\] - SPL Driver (Left Speaker) (00h)
### TSC\[1:2Bh\] - SPR Driver (Right Speaker) (00h)

```
+-------------------------------------------------------------------------------------+
|       7-5  Reserved. Write only zeros to these bits.                                |
|       4-3  SPx class-D driver output stage gain (0=6dB, 1=12dB, 2=18dB, 3=24dB)     |
|       2    SPx class-D driver (0=Muted, 1=Not muted)                                |
|       1    Reserved. Write only zero to this bit.                                   |
|       0    All programmed gains to SPx have been applied (0=Not yet, 1=Yes/all) (R) |
+-------------------------------------------------------------------------------------+
```


### TSC\[1:2Ch\] - HP Driver Control (00h)

```
+-------------------------------------------------------------------------------------+
|       7-5  Debounce time for the headset short-circuit detection                    |
|              (0..7 = 0us, 8us, 16us, 32us, 64us, 128us, 256us)                      |
|              (when TSC[3:10h] set to 1MHz)                                          |
|       4-3  DAC Performance (0=Normal, 1=Increased, 2=Reserved, 3=Further Increased) |
|            (increased: by increased current, further: by increased current gain)    |
|       2    HPL output driver type (0=Headphone, 1=Lineout)                          |
|       1    HPR output driver type (0=Headphone, 1=Lineout)                          |
|       0    Reserved. Write only zero to this bit.                                   |
+-------------------------------------------------------------------------------------+
```

The clock used for the debounce has a clock period = debounce duration/8.

### TSC\[1:2Dh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0  Reserved. Do not write to these registers.                 |
+-----------------------------------------------------------------------+
```


### TSC\[1:2Eh\] - MICBIAS (00h)

```
+--------------------------------------------------------------------------------+
|       7    Device software power-down (0=Disabled, 1=PowerDown?-Enabled)       |
|       6-4  Reserved. Write only zeros to these bits.                           |
|       3    Power up programmed MICBIAS  (0=Only if Headset inserted, 1=Always) |
|       2    Reserved. Write only zero to this bit.                              |
|       1-0  MICBIAS output (0=Off, 1=2V, 2=2.5V, 3=AVDD)                        |
+--------------------------------------------------------------------------------+
```


### TSC\[1:2Fh\] - MIC PGA (80h)

```
+-----------------------------------------------------------------------+
|       7    MIC PGA            (0=Controlled by bits6-0, 1=Force 0dB)  |
|       6-0  PGA in 0.5dB units (0..119 = 0..59.5dB, 120..127=Reserved) |
+-----------------------------------------------------------------------+
```


### TSC\[1:30h\] - P-Terminal Delta-Sigma Mono ADC Channel Fine-Gain Input (00h)

```
+---------------------------------------------------------------------------------+
|       7-6  MIC to MIC PGA feed-forward    (0=Off, 1=10kOhm, 2=20kOhm, 3=40kOhm) |
|       5-4  AUX1 to MIC PGA feed-forward   (0=Off, 1=10kOhm, 2=20kOhm, 3=40kOhm) |
|       3-2  AUX2 to MIC PGA feed-forward   (0=Off, 1=10kOhm, 2=20kOhm, 3=40kOhm) |
|       1-0  Reserved. Write only zeros to these bits.                            |
+---------------------------------------------------------------------------------+
```

Program Bit7-6 of registers TSC\[1:30h\] and TSC\[1:31h\] with same value. Input impedance selection affects the microphone PGA gain. See the Analog Front End section for details.

### TSC\[1:31h\] - M-Terminal ADC Input Selection (00h)

```
+---------------------------------------------------------------------------------+
|       7-6  CM to MIC PGA feed-forward     (0=Off, 1=10kOhm, 2=20kOhm, 3=40kOhm) |
|       5-4  AUX2 to MIC PGA feed-forward   (0=Off, 1=10kOhm, 2=20kOhm, 3=40kOhm) |
|       3-0  Reserved. Write only zeros to these bits.                            |
+---------------------------------------------------------------------------------+
```

Program Bit7-6 of registers TSC\[1:30h\] and TSC\[1:31h\] with same value. Input impedance selection affects the microphone PGA gain. See the Analog Front End section for details.

### TSC\[1:32h\] - Input CM Settings (00h)

```
+-------------------------------------------------------------------------------------+
|       7    MIC input  (0=Floating, 1=Connected to CM internally)                    |
|             (when not used for MIC PGA and analog bypass)                           |
|       6    AUX1 input (0=Floating, 1=Connected to CM internally)                    |
|             (when not used for MIC PGA and analog bypass)                           |
|       5    AUX2 input (0=Floating, 1=Connected to CM internally)                    |
|             (when not used for MIC PGA)                                             |
|       4-1  Reserved. Write only zeros to these bits.                                |
|       0    All programmed gains to ADC have been applied (0=Not yet, 1=Yes/all) (R) |
+-------------------------------------------------------------------------------------+
```


### TSC\[1:33h..FFh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0  Reserved. Write only the reset value to these bits.        |
+-----------------------------------------------------------------------+
```




