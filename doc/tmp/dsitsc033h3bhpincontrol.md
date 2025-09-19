# DSi TSC\[0:33h..3Bh\], Pin Control


### TSC\[0:33h\] - GPIO1 In/Out Pin Control (00h..C2h)
### TSC\[0:34h\] - GPIO2 In/Out Pin Control (00h..C2h)

```
+---------------------------------------------------------------------------------+
|       7-6   Reserved. Do not write any value other than reset value.            |
|       5-2   GPIOx Mode                                                 (R/W)    |
|               0 = GPIOx disabled (input and output buffers powered down)        |
|               1 = GPIOx input mode (as secondary BCLK/WCLK/SDIN input, or       |
|                        as ADC_WCLK input, Dig_Mic_In or in ClockGen block)      |
|               2 = GPIOx input mode (as GPI general-purpose input)               |
|               3 = GPIOx output = general-purpose output                         |
|               4 = GPIOx output = CLKOUT output                                  |
|               5 = GPIOx output = INT1 output                                    |
|               6 = GPIOx output = INT2 output                                    |
|               7 = GPIOx output = ADC_WCLK output for codec interface            |
|               8 = GPIOx output = secondary BCLK output for codec interface      |
|               9 = GPIOx output = secondary WCLK output for codec interface      |
|               10 = GPIOx output = ADC_MOD_CLK output for the digital microphone |
|               11 = GPIOx output = secondary SDOUT for codec interface           |
|               12 = GPIOx output = TouchScreen/SAR ADC interrupt (active-low),   |
|               13-15 = Reserved                              as PINTDAV signal   |
|       1     GPIOx input buffer value (0 or 1)                         (R)       |
|       0     GPIOx general-purpose output value (0 or 1)               (R/W)     |
+---------------------------------------------------------------------------------+
```


### TSC\[0:35h\] - SDOUT (OUT Pin) Control (12h)

```
+-----------------------------------------------------------------------+
|       7-5   Reserved                                                  |
|       4     SDOUT bus keeper (0=Enabled, 1=Disabled)                  |
|       3-1   SDOUT Mode                                                |
|               0 = SDOUT disabled (output buffer powered down)         |
|               1 = SDOUT = primary SDOUT output for codec interface    |
|               2 = SDOUT = general-purpose output                      |
|               3 = SDOUT = CLKOUT output                               |
|               4 = SDOUT = INT1 output                                 |
|               5 = SDOUT = INT2 output                                 |
|               6 = SDOUT = secondary BCLK output for codec interface   |
|               7 = SDOUT = secondary WCLK output for codec interface   |
|       0     SDOUT general-purpose output value (0 or 1)               |
+-----------------------------------------------------------------------+
```


### TSC\[0:36h\] - SDIN (IN Pin) Control (02h or 03h)

```
+----------------------------------------------------------------------------------+
|       7-3   Reserved                                                             |
|       2-1   SDIN Mode                                                            |
|               0 = SDIN disabled (input buffer powered down)                      |
|               1 = SDIN enabled (as codec SDIN, Dig_Mic_In, or in ClockGen block) |
|               2 = SDIN enabled (as GPI general-purpose input)                    |
|               3 = Reserved                                                       |
|       0     SDIN input-buffer value (0 or 1)                          (R)        |
+----------------------------------------------------------------------------------+
```


### TSC\[0:37h\] - MISO (OUT Pin) Control (02h)

```
+------------------------------------------------------------------------------+
|       7-5   Reserved                                                         |
|       4-1   MISO Mode                                                        |
|               0 = MISO disabled (output buffer powered down)                 |
|               1 = MISO = MISO output for SPI interface (or disabled for I2C) |
|               2 = General-purpose output                                     |
|               3 = MISO = CLKOUT output                                       |
|               4 = MISO = INT1 output                                         |
|               5 = MISO = INT2 output                                         |
|               6 = MISO = ADC_WCLK output for codec interface                 |
|               7 = MISO = ADC_MOD_CLK output for the digital microphone       |
|               8 = MISO = secondary SDOUT for codec interface                 |
|               9 = MISO = secondary BCLK output for codec interface           |
|               10 = MISO = secondary WCLK output for codec interface          |
|               11-15 = Reserved                                               |
|       0     MISO general-purpose output value (0 or 1)                       |
+------------------------------------------------------------------------------+
```


### TSC\[0:38h\] - SCLK (IN Pin) Control (02h..03h)

```
+--------------------------------------------------------------------------+
|       7-3   Reserved                                                     |
|       2-1   SCLK Mode                                                    |
|               0 = SCLK disabled (input buffer powered down)              |
|               1 = SCLK enabled (for the SPI interface)                   |
|               2 = SCLK enabled (as a GPI general-purpose input)          |
|               3 = SCLK enabled (as secondary SDIN/BCLK/WCLK input,       |
|                                 or as ADC_WCLK input, or Dig_Mic_In)     |
|       0     SCLK input buffer value (0 or 1)                         (R) |
+--------------------------------------------------------------------------+
```


### TSC\[0:39h\] - GPI1 and GPI2 Pin Control (00h..11h)

```
+-------------------------------------------------------------------------------------+
|       7     Reserved. Write only zero to this bit.                                  |
|       6-5   GPI1 Mode                                                               |
|               0 = GPI1 disabled (input buffer powered down)                         |
|               1 = GPI1 enabled (as secondary SDIN/BCLK/WCLK input, or ADC_WCLK inp) |
|               2 = GPI1 enabled (as a GPI general-purpose input)                     |
|               3 = Reserved (unlike below GPI2)                                      |
|       4     GPI1 pin value (0 or 1)         (R)                                     |
|       3     Reserved. Write only zero to this bit.                                  |
|       2-1   GPI2 Mode                                                               |
|               0 = GPI2 disabled (input buffer powered down)                         |
|               1 = GPI2 enabled (as secondary BCLK/WCLK input, or ADC_WCLK input)    |
|               2 = GPI2 enabled (as a GPI general-purpose input)                     |
|               3 = GPI2 enabled (as an HP_SP input)                                  |
|       0     GPI2 pin value (0 or 1)         (R)                                     |
+-------------------------------------------------------------------------------------+
```

The DSi has GPI1 wired to VCNT5.
The DSi has GPI2 wired to HP#SP (headphone/speaker switch).

### TSC\[0:3Ah\] - GPI3 Pin Control (00h..10h)

```
+----------------------------------------------------------------------------------+
|       7     Reserved. Write only zero to this bit.                               |
|       6-5   GPI3 Mode                                                            |
|               0 = GPI3 disabled (input buffer powered down)                      |
|               1 = GPI3 enabled (as secondary BCLK/WCLK input, or ADC_WCLK input) |
|               2 = GPI3 enabled (as a GPI general purpose input)                  |
|               3 = Reserved (Undocumented - used by DSi?)                         |
|       4     GPI3 pin value (0 or 1)         (R)                                  |
|       3-0   Reserved. Write only zeros to these bits.                            |
+----------------------------------------------------------------------------------+
```

The DSi has the GPI3 pin wired to Headphone Mute logic.

### TSC\[0:3Bh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only zeros to these bits.                 |
+-----------------------------------------------------------------------+
```




