# DSi TSC\[0:00h..1Ah\], Basic PLL and Timing Control


### TSC\[xxh:00h\] - Page Select Register (00h)

```
+----------------------------------------------------------------------------+
|       7-0   Page Select (00h..FEh) (FFh=Undocumented, enter special mode?) |
+----------------------------------------------------------------------------+
```

Selects the \"page\" for the TSC\[page:index\] addresses.

### TSC\[0:01h\] - Software Reset (00h)

```
+-----------------------------------------------------------------------+
|       7-1   Reserved. Write only zeros to these bits.                 |
|       0     Software Reset (0=No change, 1=Reset)                     |
+-----------------------------------------------------------------------+
```


### TSC\[0:02h\] - Reserved (xxh) (R)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to this register.                  |
+-----------------------------------------------------------------------+
```


### TSC\[0:03h\] - Overtemperature OT Flag (02h..FFh) (R)

```
+-----------------------------------------------------------------------+
|       7-2   Reserved. Do not write to these bits. (R)                 |
|       1     Overtemperature protection flag (0=Alert, 1=Normal) (R)   |
|       0     Reserved. Do not write to these bits. (R/W?)              |
+-----------------------------------------------------------------------+
```

Bit1 is valid only if speaker amplifier is powered up. Initial value varies per console:

```
+-----------------------------------------------------------------------+
|       Old3DS    = 16h                                                 |
|       New3DS XL = 36h                                                 |
+-----------------------------------------------------------------------+
```

Maybe the upper bits contain a Chip ID.

### TSC\[0:04h\] - Clock-Gen Muxing (00h)

```
+-----------------------------------------------------------------------+
|       7-4   Reserved. Write only zeros to these bits.                 |
|       3-2   Select PLL_CLKIN   (0=MCLK, 1=BCLK, 2=GPIO1, 3=SDIN)      |
|       1-0   Select CODEC_CLKIN (0=MCLK, 1=BCLK, 2=GPIO1, 3=PLL_CLK)   |
+-----------------------------------------------------------------------+
```

See Section 5.8 for more details on clock generation mutiplexing and dividers.

### TSC\[0:05h\] - PLL P and R-Values (11h)

```
+-----------------------------------------------------------------------+
|       7     PLL Enable        (0=Power down, 1=Power up)              |
|       6-4   PLL Divider P     (1..7=Div1..7, or 0=Div8)               |
|       3-0   PLL Multiplier R  (1..15=Mul1..15, or 0=Mul16)            |
+-----------------------------------------------------------------------+
```


### TSC\[0:06h\] - PLL J-Value (04h)

```
+-----------------------------------------------------------------------+
|       7-6   Reserved. Write only zeros to these bits.                 |
|       5-0   PLL Multiplier J  (1..63=Mul1..63, or 0=Reserved)         |
+-----------------------------------------------------------------------+
```


### TSC\[0:07h,08h\] - PLL D-Value MSB,LSB (0000h)

```
+-----------------------------------------------------------------------+
|       15-14 Reserved. Write only zeros to these bits.                 |
|       13-0  PLL fractional multiplier D-Val (14bit)                   |
+-----------------------------------------------------------------------+
```

Note that LSB register must be written to immediately after writing to MSB.

### TSC\[0:09h,0Ah\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only zeros to these bits.                 |
+-----------------------------------------------------------------------+
```


### TSC\[0:0Bh\] - DAC NDAC Value (01h)

```
+-----------------------------------------------------------------------+
|       7     DAC NDAC Divider Enable (0=Power down, 1=Power up)        |
|       6-0   DAC NDAC Divider (1..127=Div1..127, or 0=Div128)          |
+-----------------------------------------------------------------------+
```


### TSC\[0:0Ch\] - DAC MDAC Value (01h)

```
+-----------------------------------------------------------------------+
|       7     DAC MDAC Divider Enable (0=Power down, 1=Power up)        |
|       6-0   DAC MDAC Divider (1..127=Div1..127, or 0=Div128)          |
+-----------------------------------------------------------------------+
```


### TSC\[0:0Dh,0Eh\] - DAC DOSR Value MSB,LSB (0080h)

```
+-----------------------------------------------------------------------+
|       15-10 Reserved                                                  |
|       9-0   DAC OSR value "DOSR" (1..1023, or 0=1024)                 |
+-----------------------------------------------------------------------+
```

DOSR should be an integral multiple of the interpolation ratio in TSC\[0:10h\].
Note that LSB register must be written to immediately after writing to MSB.

### TSC\[0:0Fh\] - DAC IDAC Value (80h)

```
+-----------------------------------------------------------------------+
|       7-0   Number of instructions for DAC miniDSP engine (IDAC=N*4)  |
|             (1..255 = 4..1020 (N*4), or 0=1024)                       |
+-----------------------------------------------------------------------+
```

IDAC should be an integral multiple of the interpolation ratio in TSC\[0:10h\].

### TSC\[0:10h\] - DAC miniDSP Engine Interpolation (08h)

```
+------------------------------------------------------------------------+
|       7-4   Reserved. Do not write to these registers.                 |
|       3-0   Interpolation ratio in DAC miniDSP engine (1..15, or 0=16) |
+------------------------------------------------------------------------+
```


### TSC\[0:11h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to this register.                  |
+-----------------------------------------------------------------------+
```


### TSC\[0:12h\] - ADC NADC Value (01h)

```
+----------------------------------------------------------------------------------+
|       7     ADC NADC divider is powered                                          |
|               0: ADC NADC divider is powered down and ADC_DSP_CLK = DAC_DSP_CLK. |
|               1: ADC NADC divider is powered up.                                 |
|       6-0   ADC NADC divider  (1..127, or 0=128)                                 |
+----------------------------------------------------------------------------------+
```


### TSC\[0:13h\] - ADC MADC Value (01h)

```
+----------------------------------------------------------------------------------+
|       7     ADC MADC divider is powered                                          |
|               0: ADC MADC divider is powered down and ADC_MOD_CLK = DAC_MOD_CLK. |
|               1: ADC MADC divider is powered up.                                 |
|       6-0   ADC MADC divider  (1..127, or 0=128)                                 |
+----------------------------------------------------------------------------------+
```


### TSC\[0:14h\] - ADC AOSR Value (80h)

```
+-----------------------------------------------------------------------+
|       7-0   ADC OSR "AOSR" divider  (1..255, or 0=256)                |
+-----------------------------------------------------------------------+
```

AOSR should be an integral multiple of the decimation ratio in TSC\[0:16h\].

### TSC\[0:15h\] - ADC IADC Value (80h)

```
+-----------------------------------------------------------------------+
|       7-0   Number of instruction for ADC miniDSP engine (IADC=N*2)   |
|             (1..192 = 2..384 (N*2), or 0,193..255=Reserved)           |
+-----------------------------------------------------------------------+
```

IADC should be an integral multiple of the decimation ratio in TSC\[0:16h\].

### TSC\[0:16h\] - ADC miniDSP Engine Decimation (04h)

```
+-----------------------------------------------------------------------+
|       7-4   Reserved                                                  |
|       3-0   Decimation ratio in ADC miniDSP engine  (1..15, or 0=16)  |
+-----------------------------------------------------------------------+
```


### TSC\[0:17h,18h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Do not write to these registers.                |
+-----------------------------------------------------------------------+
```


### TSC\[0:19h\] - CLKOUT MUX (00h)

```
+----------------------------------------------------------------------------+
|       7-3   Reserved                                                       |
|       2-0   CDIV_CLKIN (0=MCLK, 1=BCLK, 2=SDIN, 3=PLL_CLK, 4=DAC_CLK(DSP), |
|             5=DAC_MOD_CLK, 6=ADC_CLK(DSP), 7=ADC_MOD_CLK)                  |
+----------------------------------------------------------------------------+
```


### TSC\[0:1Ah\] - CLKOUT Divider M Value (01h)

```
+-----------------------------------------------------------------------+
|       7     CLKOUT divider M Enable (0=Powered down, 1=Powered up)    |
|       6-0   CLKOUT divider M        (1..127, or 0=128)                |
+-----------------------------------------------------------------------+
```




