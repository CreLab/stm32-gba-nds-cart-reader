# DSi TSC\[3:xxh\], Touchscreen/SAR Control and TSC\[FCh:xxh\], Buffer


### TSC\[3:01h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[3:02h\] - SAR ADC Control 1 (00h)

```
+------------------------------------------------------------------------------------+
|       7     Stop  (0=Normal mode, 1=Stop conversion and power down SAR ADC)        |
|       6-5   SAR ADC resolution   (0=12bit, 1=8bit, 2=10bit, 3=12bit)               |
|       4-3   SAR ADC clock divider                                                  |
|               0 = Div1 (use for 8bit resolution mode only) (This divider is only   |
|                         for the conversion clock generation, not for other logic)  |
|               1 = Div2 (use for 8bit/10bit resolution mode only)                   |
|               2 = Div4 (recommended for better performance in 8bit/10bit mode)     |
|               3 = Div8 (recommended for better performance in 12bit mode)          |
|               (See Figure 5-40, uh?)                                               |
|       2     Filter used for on-chip data averaging (0=Mean, 1=Median) (if enabled) |
|       1-0   On-chip data averaging for mean/median filter                          |
|               0 = On-chip data averaging disabled                                  |
|               1 = 4-data averaging (mean),  or 5-data averaging (median)           |
|               2 = 8-data averaging (mean),  or 9-data averaging (median)           |
|               3 = 16-data averaging (mean), or 15-data averaging (median)          |
+------------------------------------------------------------------------------------+
```


### TSC\[3:03h\] - SAR ADC Control 2 (00h)

```
+-------------------------------------------------------------------------------------+
|       7     Conversions controlled,                                                 |
|               0 = Host-controlled conversions                                       |
|               1 = Self-controlled conversions for touch screen based on pen touch   |
|       6     Reserved. Write only zero to this bit.                                  |
|       5-2   Conversion Mode                                                         |
|               0 = No scan                                                           |
|               1 = Scan X/Y         ;\Even in host-controlled mode ;\until either    
|               2 = Scan X/Y/Z1/Z2   ;/                             ; pen is lifted,  |
|               3 = Scan X           ;\                             ; or a stop bit   
|               4 = Scan Y           ; Only in self-controlled mode ; TSC[3:02h].Bit7 |
|               5 = Scan Z1/Z2       ;/                             ;/is sent         |
|               6 = VBAT measurement                                                  |
|               7 = AUX2 measurement                                                  |
|               8 = AUX1 measurement                                                  |
|               9 = Auto scan. Sequence used is AUX1, AUX2, VBAT.                     |
|                   Each of these inputs can be enabled or disabled independently     |
|                   using TSC[3:13h], and with that sequence is modified accordingly. |
|                   Scan continues until stop bit TSC[3:02h].Bit7 is sent,            |
|                   or Bit5-2 of this register are changed.                           |
|              10 = TEMP1 measurement                                                 |
|              11 = Port scan: AUX1, AUX2, VBAT                                       |
|              12 = TEMP2 measurement                                                 |
|              13-15 = Reserved. Do not write these sequences to these bits.          |
|       1-0   Interrupt pin (GPIO1 or GPIO2 pin)                                      |
|               0 = PEN-interrupt    /PENIRQ (active low)                             |
|               1 = Data-available   /DATA_AVA (active low)                           |
|               2 = PEN-interrupt    PENIRQ and Data-available DATA_AVA (active high) |
|               3 = Reserved                                                          |
+-------------------------------------------------------------------------------------+
```


### TSC\[3:04h\] - Precharge and Sense (00h)

```
+-------------------------------------------------------------------------+
|       7     Pen touch detection (0=Enabled, 1=Disabled)                 |
|       6-4   Precharge time before touch detection                       |
|             (0..7 = 0.25us, 1us, 3us, 10us, 30us, 100us, 300us, 1000us) |
|             (when TSC[3:11h] set to 8MHz)                               |
|       3     Reserved. Write only zero to this bit.                      |
|       2-0   Sense time during touch detection                           |
|             (0..7 = 1us, 2us, 3us, 10us, 30us, 100us, 300us, 1000us)    |
|             (when TSC[3:11h] set to 8MHz)                               |
+-------------------------------------------------------------------------+
```


### TSC\[3:05h\] - Panel Voltage Stabilization (00h)

```
+-------------------------------------------------------------------------------------+
|       7-6   SAR comparator bias current (0=Normal, 1..3=Increase by 25%, 50%, 100%) |
|             (use Increase to support higher conversion clock)                       |
|       5     Sample duration (0=Default, 1=Doubled; for higher impedance)            |
|       4-3   Reserved. Write only zeroes to these bits.                              |
|       2-0   Panel voltage stabilization time before conversion                      |
|             (0..7 = 0.25us, 1us, 3us, 10us, 30us, 100us, 300us, 1000us)             |
|             (when TSC[3:11h] set to 8MHz)                                           |
+-------------------------------------------------------------------------------------+
```


### TSC\[3:06h\] - Voltage Reference (20h)

```
+----------------------------------------------------------------------------------+
|       7     Reference for Non-touch-screen Measurement  (0=External, 1=Internal) |
|       6     Internal reference voltage   (0=1.25V, 1=2.5V)                       |
|       5     Internal reference powered   (0=Always, 1=Only during conversion)    |
|       4     Reserved                                                             |
|       3-2   Reference Stabilization Time before Conversion                       |
|             (0=0us, 1=100us, 2=500us, 3=1ms) (when TSC[3:11h] set to 8MHz)       |
|       1     Reserved                                                             |
|       0     Battery measurement input (0=VBAT<=VREF, 1=VBAT=BAT)                 |
+----------------------------------------------------------------------------------+
```


### TSC\[3:07h,08h\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[3:09h\] - Status Bits 1 (40h) (R)

```
+--------------------------------------------------------------------------+
|       7     Pen Touch detected          (0=Not detected, 1=Detected) (R) |
|       6     ADC Ready                   (0=Busy, 1=Ready)            (R) |
|       5     New data is available       (0=None, 1=Yes)              (R) |
|       4     Reserved. Write only the reset value to this bit.            |
|       3     New X data is available     (0=None, 1=Yes)              (R) |
|       2     New Y data is available     (0=None, 1=Yes)              (R) |
|       1     New Z1 data is available    (0=None, 1=Yes)              (R) |
|       0     New Z2 data is available    (0=None, 1=Yes)              (R) |
+--------------------------------------------------------------------------+
```

Bit0-3 and Bit5 are not valid for the buffer mode.
Bit0-3 are cleared after reading the corresponding data.
Bit5 is cleared after completely reading ALL data.

### TSC\[3:0Ah\] - Status Bits 2 (00h) (R)

```
+--------------------------------------------------------------------------+
|       7     New AUX1 data is available  (0=None, 1=Yes)              (R) |
|       6     New AUX2 data is available  (0=None, 1=Yes)              (R) |
|       5     New VBAT data is available  (0=None, 1=Yes)              (R) |
|       4-2   Reserved. Write only zeros to these bits.                    |
|       1     New TEMP1 data is available (0=None, 1=Yes)              (R) |
|       0     New TEMP2 data is available (0=None, 1=Yes)              (R) |
+--------------------------------------------------------------------------+
```

Bit0-1 and Bit5-7 are not valid for the buffer mode.
Bit0-1 and Bit5-7 are cleared after reading the corresponding data.

### TSC\[3:0Bh,0Ch\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[3:0Dh\] - Buffer Mode (03h)

```
+----------------------------------------------------------------------------------+
|       7     Buffer Mode Enable (0=Disabled, 1=Enabled)                           |
|               (when disabled: RDPTR/WRPTR/TGPTR are set to their default values) |
|       6     Buffer Mode Type   (0=Countinuos-conversion, 1=Single-shot)          |
|       5-3   Trigger level for conversion "(N+1)*8*number of converted data"      |
|               0..7 = (8..64)*number of converted data                            |
|               uh, does "X*number of converted data" mean "after X conversions"?  |
|       2     Reserved                                                             |
|       1     Buffer Full  (0=No, 1=Full; contains 64 unread converted data)   (R) |
|       0     Buffer Empty (0=No, 1=Empty; contains 0 unread converted data)   (R) |
+----------------------------------------------------------------------------------+
```

However, in DSi this register is unused, and DSi does instead use TSC\[3:0Eh\].


### TSC\[3:0Eh\] - Reserved / Undocumented (read by DSi for Pen Down Test) (0Fh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```

However, in DSi this is used as so\... (seems to resemble TSC\[3:0Dh\])\...

```
+-----------------------------------------------------------------------+
|       7     Undoc Enable   (0=Disabled, 1=Enabled)  (R/W)             |
|       6     Undoc Whatever (0=Normal)               (R/W)             |
|       5-3   Undoc Whatever (5=Normal)               (R/W)             |
|       2     Undoc Unused                            (?)               |
|       1     Undoc Pendown/DataAvailable?            (R?)              |
|       0     Undoc Unused                            (R?)              |
+-----------------------------------------------------------------------+
```


### TSC\[3:0Fh\] - Scan Mode Timer (40h)

```
+-----------------------------------------------------------------------------------+
|       7     Programmable delay for Touch-screen measurement (0=Disable, 1=Enable) |
|       6-4   Programmable interval timer delay                                     |
|               (0..7 = 8ms, 1ms, 2ms, 3ms, 4ms, 5ms, 6ms, 7ms)                     |
|               (when TSC[3:10h] set to 1MHz)                                       |
|       3     Programmable delay for Non-touch-screen auto measurement   (1=Enable) |
|       2-0   Programmable interval timer delay (0..7 = 1.12min, 3.36min,           |
|               5.59min, 7.83min, 10.01min, 12.30min, 14.54min, 16.78min)           |
|               (uh, what is that? minutes? minimum? or what?)                      |
|               (when TSC[3:10h] set to 1MHz)                                       |
+-----------------------------------------------------------------------------------+
```

These delays are from the end of one data set of conversion to the start of another new data set of conversion.
Bit7: This interval timer mode is for all self-controlled modes. For host-controlled mode, it is valid only for (X/Y) or (X/Y/Z1/Z2) conversions.

### TSC\[3:10h\] - Scan Mode Timer Clock (81h)

```
+-------------------------------------------------------------------------------------+
|       7     Clock used for Programmable Delay Timer (0=Internal Osc/8, 1=Ext. MCLK) |
|       6-0   MCLK Divider to Generate 1-MHz Clock for the Programmable Delay Timer   |
|             (1..127=Div1..127, or 0=Div128)                                         |
+-------------------------------------------------------------------------------------+
```

The timings marked \"(when TSC\[3:10h\] set to 1MHz)\" are assuming the MCLK division result to be 1MHz (1us). Other divider settings will cause those timings to change. Using Internal Osc/8 (Bit7=0) results in 1.025MHz (0.97us), which is almost same as the \"1MHz\" timings (internal osc isn\'t too accurate though).
Bit7: External clock is used only to control the delay programmed between the conversions and not used for doing the actual conversion. This is supported to get an accurate delay, because the internal oscillator frequency varies from device to device.

### TSC\[3:11h\] - SAR ADC Clock (81h)

```
+------------------------------------------------------------------------------------+
|       7     Clock used for SAR ADC and TSC FSM (0=Internal Osc/1, 1=External MCLK) |
|       6-0   MCLK Divider for the SAR (min 40ns)  (1..127=Div1..127, or 0=Div128)   |
+------------------------------------------------------------------------------------+
```

The timings marked \"(when TSC\[3:11h\] set to 8MHz)\" are assuming the MCLK division result to be 8MHz (125ns). Other divider settings will cause those timings to change. For the SAR unit, the division result should be max 25MHz (min 40ns). Using Internal Osc/1 (Bit7=0) results in 8.2MHz (122ns), which is almost same as the \"8MHz\" timings (internal osc isn\'t too accurate though).

### TSC\[3:12h\] - Debounce Time for Pen-Up Detection (00h)

```
+----------------------------------------------------------------------------------+
|       7     Interface used for the buffer data reading   (0=SPI, 1=I2C)          |
|       6     SAR/buffer data update is,                                           |
|               0: held automatically (to avoid simultaneous buffer read and write |
|                    operations) based on internal detection logic.                |
|               1: held using software control and TSC[3:12h].Bit5.                |
|       5     SAR/buffer data update is (only if above Bit6=1),                    |
|                0: enabled all the time                                           |
|                1: stopped so that user can read the last updated data            |
|                      without any data corruption.                                |
|       4-3   Reserved. Write only zeros to these bits.                            |
|       2-0   Pen-touch removal detection with debounce                            |
|               (0..7 = 0us, 8us, 16us, 32us, 64us, 128us, 256us, 512us)           |
|               (when TSC[3:10h] set to 1MHz)                                      |
+----------------------------------------------------------------------------------+
```

The clock used for the debounce has a clock period = debounce duration/8.

### TSC\[3:13h\] - Auto AUX Measurement Selection (00h)

```
+-----------------------------------------------------------------------------------+
|       7     Auto AUX1 measurement during auto non-touch screen scan (0=Off, 1=On) |
|       6     Auto AUX2 measurement during auto non-touch screen scan (0=Off, 1=On) |
|       5     Auto VBAT measurement during auto non-touch screen scan (0=Off, 1=On) |
|       4     Auto TEMP measurement during auto non-touch screen scan (0=Off, 1=On) |
|       3     TEMP Measurement (0=Use TEMP1, 1=Use TEMP2)                           |
|       2     AUX1 Usage (0=Voltage measurement, 1=Resistance measurement)          |
|       1     AUX2 Usage (0=Voltage measurement, 1=Resistance measurement)          |
|       0     Resistance measurement bias (0=Internal bias, 1=External bias)        |
+-----------------------------------------------------------------------------------+
```


### TSC\[3:14h\] - Touch-Screen Pen Down (00h)

```
+-------------------------------------------------------------------------------+
|       7-3   Reserved                                                          |
|       2-0   Debounce Time for Pen-Down Detection                              |
|               (0..7 = 0us, 64us, 128us, 256us, 512us, 1024us, 2048us, 4096us) |
|               (when TSC[3:10h] set to 1MHz)                                   |
+-------------------------------------------------------------------------------+
```

The clock used for the debounce has a clock period = debounce duration/8.

### TSC\[3:15h\] - Threshold Check Flags Register (00h) (R)

```
+------------------------------------------------------------------------+
|       7-6   Reserved. Write only zeros to these bits.                  |
|       5     AUX1 Maximum (0=Inrange, 1=Exceeds Limit; Equal/Above MAX) |
|       4     AUX1 Minimum (0=Inrange, 1=Exceeds Limit; Equal/Below MIN) |
|       3     AUX2 Maximum (0=Inrange, 1=Exceeds Limit; Equal/Above MAX) |
|       2     AUX2 Minimum (0=Inrange, 1=Exceeds Limit; Equal/Below MIN) |
|       1     TEMP Maximum (0=Inrange, 1=Exceeds Limit; Equal/Above MAX) |
|       0     TEMP Minimum (0=Inrange, 1=Exceeds Limit; Equal/Below MIN) |
+------------------------------------------------------------------------+
```

Sticky flag bIts. These are read-only bits. They are automatically cleared once they are read and are set only if the source trigger occurs again.

### TSC\[3:16h,17h\] - AUX1 Maximum Value Check MSB,LSB (0000h)
### TSC\[3:18h,19h\] - AUX1 Minimum Value Check MSB,LSB (0000h)
### TSC\[3:1Ah,1Bh\] - AUX2 Maximum Value Check MSB,LSB (0000h)
### TSC\[3:1Ch,1Dh\] - AUX2 Minimum Value Check MSB,LSB (0000h)
### TSC\[3:1Eh,1Fh\] - Temperature(TEMP1/TEMP2) Maximum Value Check MSB,LSB (0000h)
### TSC\[3:20h,21h\] - Temperature(TEMP1/TEMP2) Minimum Value Check MSB,LSB (0000h)

```
+-----------------------------------------------------------------------+
|       15-13  Reserved                                                 |
|       12     Threshold check (0=Disabled, 1=Enabled)                  |
|              (valid for auto/non-auto scan measurement).              |
|       11-0   Threshold code (12bit)                                   |
+-----------------------------------------------------------------------+
```


### TSC\[3:2Ah,2Bh\] - Touchscreen X-Coordinate Data MSB,LSB (0000h) (R)
### TSC\[3:2Ch,2Dh\] - Touchscreen Y-Coordinate Data MSB,LSB (0000h) (R)
### TSC\[3:2Eh,2Fh\] - Touchscreen Z1-Pressure Register MSB,LSB (0000h) (R)
### TSC\[3:30h,31h\] - Touchscreen Z2-Pressure Register MSB,LSB (0000h) (R)
### TSC\[3:36h,37h\] - AUX1 Data MSB,LSB (0000h) (R)
### TSC\[3:38h,39h\] - AUX2 Data MSB,LSB (0000h) (R)
### TSC\[3:3Ah,3Bh\] - VBAT Data MSB,LSB (0000h) (R)
### TSC\[3:42h,43h\] - Temperature TEMP1 Data Register MSB,LSB (0000h) (R)
### TSC\[3:44h,45h\] - Temperature TEMP2 Data Register MSB,LSB (0000h) (R)

```
+-----------------------------------------------------------------------+
|       15-0   Data... but, seems to be always zero on DSi?             |
+-----------------------------------------------------------------------+
```

Going by the datasheet, these registers should contain current sample values, but they seem to be always zero on DSi.
Instead, the samples for the currently selected Conversion Mode can be read from the buffer at TSC\[FCh:01h,02h\], using the buffer should also ensure that MSB/LSB-pairs won\'t change within 16bit reads.

### TSC\[3:22h\...29h\] - Reserved (xxh)
### TSC\[3:32h\...35h\] - Reserved (xxh)
### TSC\[3:3Ch\...41h\] - Reserved (xxh)
### TSC\[3:46h\...7Fh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0    Reserved. Write only the reset value to these bits.      |
+-----------------------------------------------------------------------+
```


### TSC\[FCh:01h,02h\] - Buffer Mode Data MSB,LSB (xxxxh) (R)

```
+----------------------------------------------------------------------------+
|       15    Ring-buffer Full  (1=All 64 entries are unread)                |
|       14    Ring-buffer Empty (1=All 64 entries are read)                  |
|       13    Reserved          (uh?)                                        |
|       12    Data ID           (0=X/Z1/BAT/AUX2, 1=Y/Z2/AUX1/TEMP)          |
|       11-0  Converted data (12bit), read from "RDPTR" ring-buffer location |
+----------------------------------------------------------------------------+
```

Note: One can/must read multiple words from index 01h (the index will somewhat automatically toggle between 01h and 02h in that case (or perhaps it does increment to 03h and up, but those indices mirror to 01h and 02h)).

### TSC\[FCh:03h..7Fh\] - Reserved (xxh) (actually mirrors of TSC\[FCh:01h,02h\])

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```

These are somewhat mirrors of the buffer at TSC\[FCh:01h,02h\]. Trying to select index=03h starts reading with the 1st buffer byte (ie. it won\'t start at the 3rd byte).



