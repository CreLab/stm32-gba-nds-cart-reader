# DS Wifi RF9008 Registers


### RF9008 (RF2958 compatible)
2.4GHz Spread-Spectrum Transceiver - RF Micro Devices, Inc.

### RF chip data (Type2) (initial NDS settings from firmware, example)

```
+---------------------------------------------------------------------------------+
|       Firmware   Index   Data                                                   |
|       (24bit)    (4bit)  (18bit)                                                |
|       00C007h  =  00h  + 0C007h ;-also set to 0C008h for power-down             |
|       129C03h  =  04h  + 29C03h                                                 |
|       141728h  =  05h  + 01728h ;\these are also written when changing channels 
|       1AE8BAh  =  06h  + 2E8BAh ;/                                              |
|       1D456Fh  =  07h  + 1456Fh                                                 |
|       23FFFAh  =  08h  + 3FFFAh                                                 |
|       241D30h  =  09h  + 01D30h ;-bit10..14 should be also changed per channel? |
|       """"50h  =  """  + """50h ;firmware v5 and up uses narrower tx filter     |
|       280001h  =  0Ah  + 00001h                                                 |
|       2C0000h  =  0Bh  + 00000h                                                 |
|       069C03h  =  01h  + 29C03h                                                 |
|       080022h  =  02h  + 00022h                                                 |
|       0DFF6Fh  =  03h  + 1FF6Fh                                                 |
+---------------------------------------------------------------------------------+
```


### RF\[00h\] - Configuration Register 1 (CFG1) (Power on: 00007h)

```
+-----------------------------------------------------------------------+
|       17-16 Reserved, program to zero (0)                             |
|       15-14 Reference Divider Value (0=Div2, 1=Div3, 2=Div44, 3=Div1) |
|       3     Sleep Mode Current      (0=Normal, 1=Very Low)            |
|       2     RF VCO Regulator Enable (0=Disable, 1=Enable)             |
|       1     IF VCO Regulator Enable (0=Disable, 1=Enable)             |
|       0     IF VGA Regulator Enable (0=Disable, 1=Enable)             |
+-----------------------------------------------------------------------+
```


### RF\[01h\] - IF PLL Register 1 (IFPLL1) (Power on: 09003h)

```
+-------------------------------------------------------------------------------------+
|       17    IF PLL Enable                      (0=Disable, 1=Enable)                |
|       16    IF PLL KV Calibration Enable       (0=Disable, 1=Enable)                |
|       15    IF PLL Coarse Tuning Enable        (0=Disable, 1=Enable)                |
|       14    IF PLL Loop Filter Select          (0=Internal, 1=External)             |
|       13    IF PLL Charge Pump Leakage Current (0=Minimum value, 1=2*Minimum value) |
|       12    IF PLL Phase Detector Polarity     (0=Positive, 1=Negative)             |
|       11    IF PLL Auto Calibration Enable     (0=Disable, 1=Enable)                |
|       10    IF PLL Lock Detect Enable          (0=Disable, 1=Enable)                |
|       9     IF PLL Prescaler Modulus           (0=4/5 Mode, 1=8/9 Mode)             |
|       8-4   Reserved, program to zero (0)                                           |
|       3-0   IF VCO Coarse Tuning Voltage       (N=Voltage*16/VDD)                   |
+-------------------------------------------------------------------------------------+
```


### RF\[02h\] - IF PLL Register 2 (IFPLL2) (Power on: 00022h)

```
+-----------------------------------------------------------------------+
|       17-16 Reserved, program to zero (0)                             |
|       15-0  IF PLL divide-by-N value                                  |
+-----------------------------------------------------------------------+
```


### RF\[03h\] - IF PLL Register 3 (IFPLL3) (Power on: 1FF78h)

```
+----------------------------------------------------------------------------+
|       17    Reserved, program to zero (0)                                  |
|       16-8  IF VCO KV Calibration, delta N value (signed)  ;DeltaF=(DN/Fr) |
|       7-4   IF VCO Coarse Tuning Default Value                             |
|       3-0   IF VCO KV Calibration Default Value                            |
+----------------------------------------------------------------------------+
```


### RF\[04h\] - RF PLL Register 1 (RFPLL1) (Power on: 09003h)

```
+-----------------------------------------------------------------------+
|       17-10 Same as for RF[01h] (but for RF, not for IF)              |
|       9     RF PLL Prescaler Modulus (0=8/9 Mode, 1=8/10 Mode)        |
|       8-0   Same as for RF[01h] (but for RF, not for IF)              |
+-----------------------------------------------------------------------+
```


### RF\[05h\] - RF PLL Register 2 (RFPLL2) (Power on: 01780h)

```
+-----------------------------------------------------------------------+
|       17-6  RF PLL Divide By N Value                                  |
|       5-0   RF PLL Numerator Value (Bits 23-18)                       |
+-----------------------------------------------------------------------+
```


### RF\[06h\] - RF PLL Register 3 (RFPLL3) (Power on: 00000h)

```
+-----------------------------------------------------------------------+
|       17-0  RF PLL Numerator Value (Bits 17-0)                        |
+-----------------------------------------------------------------------+
```


### RF\[07h\] - RF PLL Register 4 (RFPLL4) (Power on: 14578h)

```
+-----------------------------------------------------------------------------------+
|       17-10 Same as for RF[03h] (but for RF, not for IF) ;and, DN=(deltaF/Fr)*256 |
+-----------------------------------------------------------------------------------+
```


### RF\[08h\] - Calibration Register 1 (CAL1) (Power on: 1E742h)

```
+------------------------------------------------------------------------------------+
|       17-13  VCO1 Warm-up Time  ;TVCO1=(approximate warm-up time)*(Fr/32)          |
|       12-8   VCO1 Tuning Gain Calibration ;TLOCK1=(approximate lock time)*(Fr/128) |
|       7-3    VCO1 Coarse Tune Calibration Reference  ;VALUE=(average time)*(Fr/32) |
|       2-0    Lock Detect Resolution (0..7)                                         |
+------------------------------------------------------------------------------------+
```


### RF\[09h\] - TXRX Register 1 (TXRX1) (Power on: 00120h)

```
+-------------------------------------------------------------------------------------+
|       17    Receiver DC Removal Loop          (0=Enable DC Removal Loop, 1=Disable) |
|       16    Internal Variable Gain for VGA  (0=Disable/External, 1=Enable/Internal) |
|       15    Internal Variable Gain Source (0=From TXVGC Bits, 1=From Power Control) |
|       14-10 Transmit Variable Gain Select (TXVGC)   (0..1Fh = High..low gain)       |
|       9-7   Receive Baseband Low Pass Filter     (0=Wide Bandwidth, 7=Narrow)       |
|       6-4   Transmit Baseband Low Pass Filter    (0=Wide Bandwidth, 7=Narrow)       |
|       3     Mode Switch            (0=Single-ended mode, 1=Differential mode)       |
|       2     Input Buffer Enable TX (0=Input Buffer Controlled by TXEN, 1=By BBEN)   |
|       1     Internal Bias Enable   (0=Disable/External, 1=Enable/Internal)          |
|       0     TX Baseband Filters Bypass        (0=Not Bypassed, 1=Bypassed)          |
+-------------------------------------------------------------------------------------+
```


### RF\[0Ah\] - Power Control Register 1 (PCNT1) (Power on: 00000h)

```
+--------------------------------------------------------------------------------+
|       17-15 Select MID_BIAS Level                          (1.6V through 2.6V) |
|       14-9  Desired output power at antenna                (N*0.5dBm)          |
|       8-3   Power Control loop-variation-adjustment Offset (signed, N*0.5dB)   |
|       2-0   Desired delay for using a single TX_PE line    (N*0.5us)           |
+--------------------------------------------------------------------------------+
```


### RF\[0Bh\] - Power Control Register 2 (PCNT2) (Power on: 00000h)

```
+-----------------------------------------------------------------------+
|       17-12 Desired MAX output power when PABIAS=MAX=2.6V (N*0.5dBm)  |
|       11-6  Desired MAX output power when PABIAS=MID_BIAS (N*0.5dBm)  |
|       5-0   Desired MAX output power when PABIAS=MIN=1.6V (N*0.5dBm)  |
+-----------------------------------------------------------------------+
```


### RF\[0Ch\] - VCOT Register 1 (VCOT1) (Power on: 00000h)

```
+-----------------------------------------------------------------------+
|       17    IF VCO Band Current Compensation (0=Disable, 1=Enable)    |
|       16    RF VCO Band Current Compensation (0=Disable, 1=Enable)    |
|       15-0  Reserved, program to zero (0)                             |
+-----------------------------------------------------------------------+
```


### RF\[0Dh..1Ah\] - N/A (Power on: 00000h)

```
+-----------------------------------------------------------------------+
|       Not used.                                                       |
+-----------------------------------------------------------------------+
```


### RF\[1Bh\] - Test Register 1 (TEST) (Power on: 0000Fh)

```
+-----------------------------------------------------------------------+
|       17-0  This is a test register for internal use only.            |
+-----------------------------------------------------------------------+
```


### RF\[1Ch..1Eh\] - N/A (Power on: 00000h)

```
+-----------------------------------------------------------------------+
|       Not used.                                                       |
+-----------------------------------------------------------------------+
```


### RF\[1Fh\] - Reset Register (Power on: 00001h)

```
+-----------------------------------------------------------------------+
|       17-0  Don't care (writing any value resets the chip)            |
+-----------------------------------------------------------------------+
```




