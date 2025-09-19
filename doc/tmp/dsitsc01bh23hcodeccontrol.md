# DSi TSC\[0:1Bh..23h\], Codec Control


### TSC\[0:1Bh\] - Codec Interface Control 1 (00h) (R/W)

```
+---------------------------------------------------------------------------+
|       7-6   Codec interface type        (0=I2S, 1=DSP, 2=RJF, 3=LJF)      |
|       5-4   Codec interface word length (0..3=16,20,24,32 bits)           |
|       3     BCLK Direction              (0=Input, 1=Output)               |
|       2     WCLK Direction              (0=Input, 1=Output)               |
|       1     Reserved                                                      |
|       0     Driving SDOUT to High-Impedance for the Extra BCLK cycle when |
|              data is not being transferred (0=Disabled, 1=Enabled)        |
+---------------------------------------------------------------------------+
```


### TSC\[0:1Ch\] - Data-Slot Offset Programmability (00h)

```
+-----------------------------------------------------------------------+
|       7-0   Offset (0..255 = 0..255 BCLKs)                            |
+-----------------------------------------------------------------------+
```

Note: Measured with respect to WCLK Rising Edge in DSP Mode.

### TSC\[0:1Dh\] - Codec Interface Control 2 (00h)

```
+---------------------------------------------------------------------------------+
|       7-6   Reserved                                                            |
|       5     SDIN-to-SDOUT loopback (0=Disable, 1=Enable)                        |
|       4     ADC-to-DAC loopback    (0=Disable, 1=Enable)                        |
|       3     BCLK Invert            (0=No, 1=Invert)                             |
|       2     BCLK and WCLK active even with Codec powered down (0=No, 1=Yes)     |
|       1-0   BDIV_CLKIN     (0=DAC_CLK, 1=DAC_MOD_CLK, 2=ADC_CLK, 3=ADC_MOD_CLK) |
+---------------------------------------------------------------------------------+
```

The BCLK settings in Bit2,3 do apply to both Primary and Secondary BCLK.

### TSC\[0:1Eh\] - BCLK Divider N Value (01h)

```
+-----------------------------------------------------------------------+
|       7     BCLK divider N Enable (0=Powered down, 1=Powered up)      |
|       6-0   BCLK divider N        (1..127, or 0=128)                  |
+-----------------------------------------------------------------------+
```


### TSC\[0:1Fh\] - Codec Secondary Interface Control 1 (00h)

```
+-------------------------------------------------------------------------------------+
|       7-5   Secondary BCLK is obtained from    ;\(0=GPIO1, 1=SCLK, 2=MISO, 3=SDOUT, 
|       4-2   Secondary WCLK is obtained from    ;/ 4=GPIO2, 5=GPI1, 6=GPI2, 7=GPI3)  |
|       1-0   Secondary SDIN is obtained from (0=GPIO1, 1=SCLK, 2=GPIO2, 3=GPI1)      |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:20h\] - Codec Secondary Interface Control 2 (00h)

```
+------------------------------------------------------------------------------+
|       7-5   ADC_WCLK is obtained from  (0=GPIO1, 1=SCLK, 2=MISO, 3=Reserved, |
|       4     Reserved                        4=GPIO2, 5=GPI1, 6=GPI2, 7=GPI3) |
|       3     Codec/ClockGen BCLK source (0=Primary BCLK, 1=Secondary BCLK)    |
|       2     Codec WCLK source          (0=Primary WCLK, 1=Secondary WCLK)    |
|       1     Codec ADC_WCLK source      (0=DAC_WCLK, 1=ADC_WCLK)              |
|       0     Codec SDIN source          (0=Primary SDIN, 1=Secondary SDIN)    |
+------------------------------------------------------------------------------+
```


### TSC\[0:21h\] - Codec Secondary Interface Control 3 (00h)

```
+-------------------------------------------------------------------------------------+
|       7     Primary BCLK output   (0=Internally generated BCLK, 1=Secondary BCLK)   |
|       6     Secondary BCLK output (0=Primary BCLK, 1=Internally generated BCLK)     |
|       5-4   Primary WCLK output  (0=DAC_fS, 1=ADC_fS, 2=Secondary WCLK, 3=Reserved) |
|       3-2   Secondary WCLK output (0=Primary WCLK, 1=DAC_fS, 2=ADC_fS, 3=Reserved)  |
|       1     Primary SDOUT         (0=SDOUT from codec, 1=Secondary SDIN)            |
|       0     Secondary SDOUT       (0=Primary SDIN, 1=SDOUT from codec)              |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:22h\] - I2C Bus Condition (00h)

```
+--------------------------------------------------------------------------+
|       7-6   Reserved. Write only the reset value to these bits.          |
|       5     Accept I2C general-call address  (0=No/Ignore, 1=Yes/Accept) |
|       4-0   Reserved. Write only zeros to these bits.                    |
+--------------------------------------------------------------------------+
```


### TSC\[0:23h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only zeros to these bits.                 |
+-----------------------------------------------------------------------+
```




