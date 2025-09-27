# DSi TSC\[0:56h..7Fh\], AGC and ADC


Auto-Gain-Control & Analog-to-Digital Converter

### TSC\[0:56h\] - AGC Control 1 (00h)

```
+-----------------------------------------------------------------------+
|       7     AGC (0=Disabled, 1=Enabled)                               |
|       6-4   AGC target level     (0=-5.5dB, 1=-8dB, 2=-10dB, 3=-12dB, |
|                                   4=-14dB, 5=-17dB, 6=-20dB, 7=-24dB) |
|       3-0   Reserved. Write only zeros to these bits.                 |
+-----------------------------------------------------------------------+
```


### TSC\[0:57h\] - AGC Control 2 (00h)

```
+------------------------------------------------------------------------------------+
|       7-6   AGC hysterysis setting (0=1dB, 1=2dB, 2=4dB, 3=Disable AGC hysterysis) |
|       5-1   AGC noise threshold (and silence detection)                            |
|               0   = AGC noise/silence detection is disabled.                       |
|               1   = AGC noise threshold = -30dB                                    |
|               2   = AGC noise threshold = -32dB                                    |
|               3   = AGC noise threshold = -34dB                                    |
|               ...                                                                  |
|               29  = AGC noise threshold = -86dB                                    |
|               30  = AGC noise threshold = -88dB                                    |
|               31  = AGC noise threshold = -90dB                                    |
|       0     Reserved. Write only zero to this bit.                                 |
+------------------------------------------------------------------------------------+
```


### TSC\[0:58h\] - AGC Maximum Gain (7Fh, uh that\'s 7Fh=Reserved?)

```
+------------------------------------------------------------------------------------+
|       7     Reserved. Write only zero to this bit.                                 |
|       6-0   AGC maximum gain in 0.5dB units (0..119=0..+59.5dB, 120..127=Reserved) |
+------------------------------------------------------------------------------------+
```


### TSC\[0:59h\] - AGC Attack Time (00h)
### TSC\[0:5Ah\] - AGC Decay Time (00h)

```
+--------------------------------------------------------------------------------+
|       7-3   AGC attack/decay time, (N*2+1)*32/fS (0..31 = 1*32/fS .. 63*32/fS) |
|       2-0   AGC attack/decay time Multiply factor, 1 SHL N (0..7 = 1..128)     |
+--------------------------------------------------------------------------------+
```

Whereas, fS is the ADC sample rate.

### TSC\[0:5Bh\] - AGC Noise Debounce (00h)

```
+--------------------------------------------------------------------------------+
|       7-5   Reserved. Write only zeros to these bits.                          |
|       4-0   AGC noise debounce                                                 |
|               0..5   = 0/fS, 4/fS, 8/fS, 16/fS, 32/fS, 64/fS     ;\powers of 2 
|               6..10  = 128/fS, 256/fS, 512/fS, 1024/fS, 2048/fS  ;/            |
|               11..14 = 1*4096/fS, 2*4096/fS, 3*4096/fS           ;\multiples   
|               14..31 = 4*4096/fS, .., 20*4096/fS, 21*4096/fS     ;/of 4096     |
+--------------------------------------------------------------------------------+
```


### TSC\[0:5Ch\] - AGC Signal Debounce (00h)

```
+--------------------------------------------------------------------------------+
|       7-4   Reserved. Write only zeros to these bits.                          |
|       3-0   AGC signal debounce                                                |
|               0..5   = 0/fS, 4/fS, 8/fS, 16/fS, 32/fS, 64/fS     ;\powers of 2 
|               6..9   = 128/fS, 256/fS, 512/fS, 1024/fS           ;/            |
|               10..13 = 1*2048/fS, 2*2048/fS, 3*2048/fS           ;\multiples   
|               13..15 = 4*2048/fS, 5*2048/fS, 6*2048/fS           ;/of 2048     |
+--------------------------------------------------------------------------------+
```


### TSC\[0:5Dh\] - AGC Gain-Applied Reading (xxh) (R)

```
+-----------------------------------------------------------------------------------+
|       7-0   Gain applied by AGC in 0.5dB units (-24..+119 = -12dB..+59.5dB)   (R) |
+-----------------------------------------------------------------------------------+
```


### TSC\[0:5Eh\...65h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to these registers.                |
+-----------------------------------------------------------------------+
```


### TSC\[0:66h\] - ADC DC Measurement 1 (00h)

```
+----------------------------------------------------------------------------------+
|       7     DC measurement for mono ADC channel (0=Disabled, 1=Enabled)          |
|       6     Reserved. Write only reset value.                                    |
|       5     DC measurement is done based on                                      |
|               0: 1st order sinc filter with averaging of 2^D.                    |
|               1: 1st order low-pass IIR filter whose coefficients                |
|                   are calculated based on D value.                               |
|       4-0   DC Meaurement D setting (1..20 = D=1 .. D=20) (0 or 21..31=Reserved) |
+----------------------------------------------------------------------------------+
```


### TSC\[0:67h\] - ADC DC Measurement 2 (00h)

```
+-------------------------------------------------------------------------------------+
|       7     Reserved. Write only reset value.                                       |
|       6     DC measurement data update (0=Enabled, 1=Disabled/allow stable reading) |
|             (Disabled: user can read the last updated data without corruption)      |
|       5     For IIR based DC measurement, the measurment value is                   |
|               0: the instantaneous output of the IIR filter                         |
|               1: update before periodic clearing of the IIR filter                  |
|       4-0   IIR based DC measurment, average time setting:                          |
|               0       Infinite average is used                                      |
|               1       Averaging time is 2^1 ADC modulator clock periods             |
|               2       Averaging time is 2^2 ADC modulator clock periods             |
|               ...                                                                   |
|               19      Averaging time is 2^19 ADC modulator clock periods            |
|               20      Averaging time is 2^20 ADC modulator clock periods            |
|               21..31  Reserved. Don't use.                                          |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:68h,69h,6Ah\] - ADC DC Measurement Output MSB,MID,LSB (R) (000000h)

```
+-----------------------------------------------------------------------+
|       23-0  ADC DC Measurement Output (24bit)                         |
+-----------------------------------------------------------------------+
```


### TSC\[0:6Bh\...73h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to these registers.                |
+-----------------------------------------------------------------------+
```


### TSC\[0:74h\] - VOL/MICDET-Pin SAR ADC - Volume Control (00h)

```
+-------------------------------------------------------------------------------------+
|       7     DAC volume control is controlled by,                                    |
|               0: controlled by control register (7-bit Vol ADC is powered down)     |
|               1: controlled by pin (analog volume input)                            |
|       6     Clock for the 7-bit Vol ADC for pin volume control,                     |
|               0: Internal on-chip RC oscillator                                     |
|               1: External MCLK                                                      |
|       5-4   Hysteresis                                                              |
|               0: No hysteresis for volume control ADC output                        |
|               1: Hysteresis of +/-1 bit                                             |
|               2: Hysteresis of +/-2 bits                                            |
|               3: Reserved. Do not write this sequence to these bits.                |
|       3     Reserved. Write only reset value.                                       |
|       2-0   Throughput of the 7-bit Vol ADC for pin volume control,                 |
|             When Bit6=1 and external MCLK is 12MHz:                                 |
|               (0..7=15.625Hz, 31.25Hz, 62.5Hz, 125Hz, 250Hz, 500Hz, 1000Hz, 2000Hz) |
|             When Bit6=0 (use Internal oscillator):                                  |
|               (0..7=10.68Hz, 21.35Hz, 42.71Hz, 85Hz?, 170Hz, 340Hz, 680Hz, 1370Hz)  |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:75h\] - VOL/MICDET-Pin Gain (xxh) (R)

```
+----------------------------------------------------------------------------+
|       7     Reserved. Write only zero to this bit.                         |
|       6-0   Gain applied by pin volume control                             |
|               0   = +18 dB                                                 |
|               1   = +17.5 dB                                               |
|               2   = +17 dB                                                 |
|               ...                                                          |
|               35  = +0.5 dB                                                |
|               36  = 0 dB                                                   |
|               37  = -0.5 dB                                                |
|               ...                                                          |
|               89  = -26.5 dB                                               |
|               90  = -27 dB    ;below in 1dB steps instead of 0.5dB steps ! |
|               91  = -28 dB                                                 |
|               ...                                                          |
|               125 = -62 dB                                                 |
|               126 = -63 dB                                                 |
|               127 = Reserved                                               |
+----------------------------------------------------------------------------+
```


### TSC\[0:76h\...7Fh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to these registers.                |
+-----------------------------------------------------------------------+
```




