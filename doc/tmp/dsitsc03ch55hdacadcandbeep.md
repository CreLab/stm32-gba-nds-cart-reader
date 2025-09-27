# DSi TSC\[0:3Ch..55h\], DAC/ADC and Beep


### TSC\[0:3Ch\] - DAC Instruction Set (01h)

```
+-----------------------------------------------------------------------+
|       7-5   Reserved. Write only default value.                       |
|       4-0   DAC Signal Processing Block                               |
|               0      = DAC miniDSP is used for signal processing      |
|               1..25  = DAC Signal Processing Block PRB_P1 .. PRB_P25  |
|               26..31 = Reserved. Do not use.                          |
+-----------------------------------------------------------------------+
```


### TSC\[0:3Dh\] - ADC Instruction Set (04h)

```
+------------------------------------------------------------------------------+
|       7-5   Reserved. Write only default values.                             |
|       4-0   ADC Signal Processing Block                                      |
|               0      = ADC miniDSP is used for signal processing             |
|               1..3   = Reserved                                              |
|               4..6   = ADC Signal Processing Block PRB_R4 .. PRB_R6          |
|               7..9   = Reserved                                              |
|               10..12 = ADC Signal Processing Block PRB_R10 .. PRB_R12        |
|               13..15 = Reserved                                              |
|               16..18 = ADC Signal Processing Block PRB_R16 .. PRB_R18        |
|               19..31 = Reserved. Do not write these sequences to these bits. |
+------------------------------------------------------------------------------+
```


### TSC\[0:3Eh\] - Programmable Instruction Mode-Control Bits (00h)

```
+---------------------------------------------------------------------------------+
|       7     Reserved                                                            |
|       6     ADC miniDSP Engine Auxiliary Control bit A (0 or 1)                 |
|       5     ADC miniDSP Engine Auxiliary Control bit B (0 or 1)                 |
|       4     Reset ADC miniDSP instruction counter at start of new frame (0=Yes) |
|       3     Reserved                                                            |
|       2     DAC miniDSP Engine Auxiliary Control bit A (0 or 1)                 |
|       1     DAC miniDSP Engine Auxiliary Control bit B (0 or 1)                 |
|       0     Reset DAC miniDSP instruction counter at start of new frame (0=Yes) |
+---------------------------------------------------------------------------------+
```

Above DAC/ADC bit A and B can be used for conditional instructions like JMP.

### TSC\[0:3Fh\] - DAC Data-Path Setup (14h)

```
+------------------------------------------------------------------------------------+
|       7     Left-channel DAC            (0=Powered down, 1=Powered up)             |
|       6     Right-channel DAC           (0=Powered down, 1=Powered up)             |
|       5-4   Left-channel DAC data path  (0=Off, 1=Left Data, 2=Right Data, 3=Both) |
|       3-2   Right-channel DAC data path (0=Off, 1=Right Data, 2=Left Data, 3=Both) |
|       1-0   DAC channel volume control soft-stepping (0=One step per sample,       |
|              1=One step per 2 samples, 2=Disabled, 3=Reserved)                     |
+------------------------------------------------------------------------------------+
```

Wheras, Both=((L+R)/2).

### TSC\[0:40h\] - DAC Volume Control (0Ch)

```
+-----------------------------------------------------------------------------------+
|       7-4   Reserved. Write only zeros to these bits.                             |
|       3     Left-channel DAC  (0=Not muted, 1=Muted)                              |
|       2     Right-channel DAC (0=Not muted, 1=Muted)                              |
|       1-0   DAC Mono/Stereo Volume                                                |
|               0: Use Left/Right volume control for Left/Right channels ("stereo") |
|               1: Use Right volume control for Both channels            ("mono")   |
|               2: Use Left volume control for Both channels             ("mono")   |
|               3: Same as 0                                             ("stereo") |
+-----------------------------------------------------------------------------------+
```


### TSC\[0:41h\] - DAC Left Volume Control (00h)
### TSC\[0:42h\] - DAC Right Volume Control (00h)

```
+-------------------------------------------------------------------------------------+
|       7-0  Digital gain in 0.5dB units (-127..+48 = -63.5dB..+24dB, Other=Reserved) |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:43h\] - Headset Detection (00h..60h)

```
+----------------------------------------------------------------------------------+
|       7     Headset detection Enable (0=Disabled, 1=Enabled)                     |
|       6-5   Headset detection (0=None, 1=Headset, 2=Reserved, 3=Headset+Mic) (R) |
|       4-2   Debounce for Glitch Rejection During Headset Detection               |
|               (0..5 = 16ms, 32ms, 64ms, 128ms, 256ms, 512ms, 6..7=Reserved)      |
|               (when TSC[3:10h] set to 1MHz)                                      |
|       1-0   Debounce for Glitch Rejection During Headset Button-Press Detection  |
|               (0..3 = 0ms, 8ms, 16ms, 32ms) (when TSC[3:10h] set to 1MHz)        |
+----------------------------------------------------------------------------------+
```

Sampling is 8x faster than above timings (eg. time=32ms uses 4ms sampling).

### TSC\[0:44h\] - DRC Control 1 (0Fh)

```
+----------------------------------------------------------------------------------+
|       7     Reserved. Write only the reset value to these bits.                  |
|       6     DRC for left channel  (0=Disabled, 1=Enabled)                        |
|       5     DRC for right channel (0=Disabled, 1=Enabled)                        |
|       4-2   DRC threshold  (0..7 = -3dB,-6dB,-9dB,-12dB,-15dB,-18dB,-21dB,-24dB) |
|       1-0   DRC hysteresis (0..3 = +0dB,+1dB,+2dB,+3dB)                          |
+----------------------------------------------------------------------------------+
```


### TSC\[0:45h\] - DRC Control 2 (38h)

```
+-----------------------------------------------------------------------+
|       7     Reserved. Write only the reset value to these bits.       |
|       6-3   DRC Hold Time                                             |
|               0  = DRC Hold Disabled        ;-disable                 |
|               1  = 32 DAC Word Clocks       ;\                        
|               2  = 64 DAC Word Clocks       ;                         |
|               3  = 128 DAC Word Clocks      ;                         |
|               4  = 256 DAC Word Clocks      ; powers of 2             |
|               5  = 512 DAC Word Clocks      ;                         |
|               6  = 1024 DAC Word Clocks     ;                         |
|               7  = 2048 DAC Word Clocks     ;                         |
|               8  = 4096 DAC Word Clocks     ;                         |
|               9  = 8192 DAC Word Clocks     ;                         |
|               10 = 16384 DAC Word Clocks    ;/                        |
|               11 = 1*32768 DAC Word Clocks  ;\                        
|               12 = 2*32768 DAC Word Clocks  ;                         |
|               13 = 3*32768 DAC Word Clocks  ; multiples of 32768      |
|               14 = 4*32768 DAC Word Clocks  ;                         |
|               15 = 5*32768 DAC Word Clocks  ;/                        |
|       2-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[0:46h\] - DRC Control 3 (00h)

```
+---------------------------------------------------------------------------------+
|       7-4   DRC attack rate, "(4 SHR N) dB per DAC Word Clock"                  |
|             (0=4dB, 1=2dB, 2=1dB, ..., 15=0.000122dB per DAC Word Clock)        |
|       3-0   DRC decay rate, "(1 SHR (N+6)) dB per DAC Word Clock"               |
|             (0=0.0156dB, 1=0.00781dB, ..., 15=0.000000476dB per DAC Word Clock) |
+---------------------------------------------------------------------------------+
```


### TSC\[0:47h\] - Beep Generator and Left Beep Volume (00h)

```
+--------------------------------------------------------------------------------+
|       7     Beep Generator Enable (0=Disabled/Duration ended, 1=Enabled/Busy)  |
|               (self-clearing based on beep duration)                           |
|       6     Auto beep generator on pen touch (0=Disabled, 1=Enabled)           |
|               (CODEC_CLKIN should be available for this and is                 |
|               used whenever touch is detected).                                |
|       5-0   Left-channel beep volume control "(2-N)dB" (0..63 = +2dB .. -61dB) |
+--------------------------------------------------------------------------------+
```

The beep generator is only available in PRB_P25 DAC processing mode.

### TSC\[0:48h\] - Beep Generator and Right Beep Volume (00h)

```
+-----------------------------------------------------------------------------------+
|       7-6   Beep Mono/Stereo Volume                                               |
|               0: Use Left/Right volume control for Left/Right channels ("stereo") |
|               1: Use Right volume control for Both channels            ("mono")   |
|               2: Use Left volume control for Both channels             ("mono")   |
|               3: Same as 0                                             ("stereo") |
|       5-0   Right-channel beep volume control "(2-N)dB" (0..63 = +2dB .. -61dB)   |
+-----------------------------------------------------------------------------------+
```

The beep generator is only available in PRB_P25 DAC processing mode.

### TSC\[0:49h,4Ah,4Bh\] - Beep Length MSB,MID,LSB (0000EEh)

```
+---------------------------------------------------------------------------+
|       23-0  Number of samples for which beep need to be generated (24bit) |
+---------------------------------------------------------------------------+
```


### TSC\[0:4Ch,4Dh\] - Beep Frequency Sin(x) MSB,LSB (10D8h)
### TSC\[0:4Eh,4Fh\] - Beep Frequency Cos(x) MSB,LSB (7EE3h)

```
+-----------------------------------------------------------------------+
|       15-0  Beep Frequency sin/cos values (16bit, each)               |
+-----------------------------------------------------------------------+
```

These registers should be set to sin(2pi\*fin/fS) and cos(2pi\*fin/fS) accordingly; where fin is the beep frequency and fS is the DAC sample rate.

### TSC\[0:50h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[0:51h\] - ADC Digital Mic (00h)

```
+-------------------------------------------------------------------------------+
|       7     ADC channel   (0=Powered Down, 1=Powered Up)                      |
|       6     Reserved                                                          |
|       5-4   Digital microphone input  (0=GPIO1, 1=SCLK, 2=SDIN, 3=GPIO2)      |
|       3     Digital microphone for delta-sigma mono ADC channel (0=Off, 1=On) |
|       2     Reserved                                                          |
|       1-0   ADC channel volume control soft-stepping (0=One step per sample,  |
|              1=One step per 2 samples, 2=Disabled, 3=Reserved)                |
+-------------------------------------------------------------------------------+
```


### TSC\[0:52h\] - ADC Digital Volume Control Fine Adjust (80h)

```
+----------------------------------------------------------------------------+
|       7     ADC channel   (0=Not muted, 1=Muted)                           |
|       6-4   Delta-Sigma Mono ADC Channel Volume Control Fine Gain          |
|             (0=0dB, 1=-0.1dB, 2=-0.2dB, 3=-0.3dB, 4=-0.4dB, 5..7=Reserved) |
|       3-0   Reserved. Write only zeros to these bits.                      |
+----------------------------------------------------------------------------+
```


### TSC\[0:53h\] - ADC Digital Volume Control Coarse Adjust (00h)

```
+-----------------------------------------------------------------------+
|       7     Reserved                                                  |
|       6-0   Delta-Sigma Mono ADC Channel Volume Control Coarse Gain   |
|               00h..27h = 0..39    = Reserved                          |
|               28h..xxh = 40       = -12 dB                            |
|               29h      = 39       = -11.5 dB                          |
|               ...        ...                                          |
|               67h      = 103      = +19.5 dB                          |
|               68h      = 104      = +20 dB                            |
|               69h..7Fh = 105..127 = Reserved                          |
+-----------------------------------------------------------------------+
```


### TSC\[0:54h,55h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```




