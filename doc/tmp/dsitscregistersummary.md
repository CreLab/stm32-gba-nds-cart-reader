# DSi TSC, Register Summary


The DSi\'s Touchscreen/Sound controller (AIC3000D) is essentially a Texas Instruments TSC2117 chip (possibly with some customizations for NDS backwards compatibility mode).

TSC\[page:index\] registers are accessed via SPI bus with 15bit address space:

```
+--------------------------------------------------------------------------------+
|       7bit index: selected via the first SPI byte, with direction flag in bit0 |
|       8bit page:  selected by writing to index 00h, ie. to TSC[xxh:00h]        |
+--------------------------------------------------------------------------------+
```


### TSC page select (for \"TSC\[page:index\]\" addressing)

```
+-----------------------------------------------------------------------+
|       TSC[xxh:00h] - Page Select Register (00h)                       |
+-----------------------------------------------------------------------+
```

### TSC Basic PLL and Timing Control

```
+-----------------------------------------------------------------------+
|       TSC[0:01h] - Software Reset (00h)                               |
|       TSC[0:02h] - Reserved (xxh) (R)                                 |
|       TSC[0:03h] - Overtemperature OT Flag (02h..FFh) (R)             |
|       TSC[0:04h] - Clock-Gen Muxing (00h)                             |
|       TSC[0:05h] - PLL P and R-Values (11h)                           |
|       TSC[0:06h] - PLL J-Value (04h)                                  |
|       TSC[0:07h,08h] - PLL D-Value MSB,LSB (0000h)                    |
|       TSC[0:09h,0Ah] - Reserved (xxh)                                 |
|       TSC[0:0Bh] - DAC NDAC Value (01h)                               |
|       TSC[0:0Ch] - DAC MDAC Value (01h)                               |
|       TSC[0:0Dh,0Eh] - DAC DOSR Value MSB,LSB (0080h)                 |
|       TSC[0:0Fh] - DAC IDAC Value (80h)                               |
|       TSC[0:10h] - DAC miniDSP Engine Interpolation (08h)             |
|       TSC[0:11h] - Reserved (xxh)                                     |
|       TSC[0:12h] - ADC NADC Value (01h)                               |
|       TSC[0:13h] - ADC MADC Value (01h)                               |
|       TSC[0:14h] - ADC AOSR Value (80h)                               |
|       TSC[0:15h] - ADC IADC Value (80h)                               |
|       TSC[0:16h] - ADC miniDSP Engine Decimation (04h)                |
|       TSC[0:17h,18h] - Reserved (xxh)                                 |
|       TSC[0:19h] - CLKOUT MUX (00h)                                   |
|       TSC[0:1Ah] - CLKOUT Divider M Value (01h)                       |
+-----------------------------------------------------------------------+
```

### TSC Codec Control

```
+-----------------------------------------------------------------------+
|       TSC[0:1Bh] - Codec Interface Control 1 (00h) (R/W)              |
|       TSC[0:1Ch] - Data-Slot Offset Programmability (00h)             |
|       TSC[0:1Dh] - Codec Interface Control 2 (00h)                    |
|       TSC[0:1Eh] - BCLK Divider N Value (01h)                         |
|       TSC[0:1Fh] - Codec Secondary Interface Control 1 (00h)          |
|       TSC[0:20h] - Codec Secondary Interface Control 2 (00h)          |
|       TSC[0:21h] - Codec Secondary Interface Control 3 (00h)          |
|       TSC[0:22h] - I2C Bus Condition (00h)                            |
|       TSC[0:23h] - Reserved (xxh)                                     |
+-----------------------------------------------------------------------+
```

### TSC Status and Interrupt Flags

```
+-----------------------------------------------------------------------+
|       TSC[0:24h] - ADC Flag Register (0xh) (R)                        |
|       TSC[0:25h] - DAC Flag Register (00h) (R)                        |
|       TSC[0:26h] - DAC Flag Register (00h) (R)                        |
|       TSC[0:27h] - Overflow Flags (00h) (R)                           |
|       TSC[0:28h..2Bh] - Reserved (xxh)                                |
|       TSC[0:2Ch] - Interrupt Flags DAC, sticky (00h..30h) (R)         |
|       TSC[0:2Dh] - Interrupt Flags ADC, sticky (00h..18h) (R)         |
|       TSC[0:2Eh] - Interrupt Flags DAC, non-sticky? (00h..30h) (R)    |
|       TSC[0:2Fh] - Interrupt Flags ADC, non-sticky? (00h..18h) (R)    |
|       TSC[0:30h] - INT1 Control Register (Select INT1 Sources) (00h)  |
|       TSC[0:31h] - INT2 Control Register (Select INT2 Sources) (00h)  |
|       TSC[0:32h] - INT1 and INT2 Control Register (00h)               |
+-----------------------------------------------------------------------+
```

### TSC Pin Control

```
+-----------------------------------------------------------------------+
|       TSC[0:33h] - GPIO1 In/Out Pin Control (00h..C2h)                |
|       TSC[0:34h] - GPIO2 In/Out Pin Control (00h..C2h)                |
|       TSC[0:35h] - SDOUT (OUT Pin) Control (12h)                      |
|       TSC[0:36h] - SDIN (IN Pin) Control (02h or 03h)                 |
|       TSC[0:37h] - MISO (OUT Pin) Control (02h)                       |
|       TSC[0:38h] - SCLK (IN Pin) Control (02h..03h)                   |
|       TSC[0:39h] - GPI1 and GPI2 Pin Control (00h..11h)               |
|       TSC[0:3Ah] - GPI3 Pin Control (00h..10h)                        |
|       TSC[0:3Bh] - Reserved (xxh)                                     |
+-----------------------------------------------------------------------+
```

### TSC DAC/ADC and Beep

```
+-----------------------------------------------------------------------+
|       TSC[0:3Ch] - DAC Instruction Set (01h)                          |
|       TSC[0:3Dh] - ADC Instruction Set (04h)                          |
|       TSC[0:3Eh] - Programmable Instruction Mode-Control Bits (00h)   |
|       TSC[0:3Fh] - DAC Data-Path Setup (14h)                          |
|       TSC[0:40h] - DAC Volume Control (0Ch)                           |
|       TSC[0:41h] - DAC Left Volume Control (00h)                      |
|       TSC[0:42h] - DAC Right Volume Control (00h)                     |
|       TSC[0:43h] - Headset Detection (00h..60h)                       |
|       TSC[0:44h] - DRC Control 1 (0Fh)                                |
|       TSC[0:45h] - DRC Control 2 (38h)                                |
|       TSC[0:46h] - DRC Control 3 (00h)                                |
|       TSC[0:47h] - Beep Generator and Left Beep Volume (00h)          |
|       TSC[0:48h] - Beep Generator and Right Beep Volume (00h)         |
|       TSC[0:49h,4Ah,4Bh] - Beep Length MSB,MID,LSB (0000EEh)          |
|       TSC[0:4Ch,4Dh] - Beep Frequency Sin(x) MSB,LSB (10D8h)          |
|       TSC[0:4Eh,4Fh] - Beep Frequency Cos(x) MSB,LSB (7EE3h)          |
|       TSC[0:50h] - Reserved (xxh)                                     |
|       TSC[0:51h] - ADC Digital Mic (00h)                              |
|       TSC[0:52h] - ADC Digital Volume Control Fine Adjust (80h)       |
|       TSC[0:53h] - ADC Digital Volume Control Coarse Adjust (00h)     |
|       TSC[0:54h,55h] - Reserved (xxh)                                 |
+-----------------------------------------------------------------------+
```

### TSC AGC and ADC (Auto-Gain-Control & Analog-to-Digital Converter)

```
+--------------------------------------------------------------------------------+
|       TSC[0:56h] - AGC Control 1 (00h)                                         |
|       TSC[0:57h] - AGC Control 2 (00h)                                         |
|       TSC[0:58h] - AGC Maximum Gain (7Fh, uh that's 7Fh=Reserved?)             |
|       TSC[0:59h] - AGC Attack Time (00h)                                       |
|       TSC[0:5Ah] - AGC Decay Time (00h)                                        |
|       TSC[0:5Bh] - AGC Noise Debounce (00h)                                    |
|       TSC[0:5Ch] - AGC Signal Debounce (00h)                                   |
|       TSC[0:5Dh] - AGC Gain-Applied Reading (xxh) (R)                          |
|       TSC[0:5Eh...65h] - Reserved (xxh)                                        |
|       TSC[0:66h] - ADC DC Measurement 1 (00h)                                  |
|       TSC[0:67h] - ADC DC Measurement 2 (00h)                                  |
|       TSC[0:68h,69h,6Ah] - ADC DC Measurement Output MSB,MID,LSB (R) (000000h) |
|       TSC[0:6Bh...73h] - Reserved (xxh)                                        |
|       TSC[0:74h] - VOL/MICDET-Pin SAR ADC - Volume Control (00h)               |
|       TSC[0:75h] - VOL/MICDET-Pin Gain (xxh) (R)                               |
|       TSC[0:76h...7Fh] - Reserved (xxh)                                        |
+--------------------------------------------------------------------------------+
```

### TSC TSC, DAC and ADC Routing, PGA, Power-Controls and MISC Logic

```
+----------------------------------------------------------------------------------+
|       TSC[1:01h..1Dh] - Reserved (xxh)                                           |
|       TSC[1:1Eh] - Headphone and Speaker Amplifier Error Control (00h)           |
|       TSC[1:1Fh] - Headphone Drivers (04h)                                       |
|       TSC[1:20h] - Class-D Speaker Amplifier (06h)                               |
|       TSC[1:21h] - HP Output Drivers POP Removal Settings (3Eh)                  |
|       TSC[1:22h] - Output Driver PGA Ramp-Down Period Control (00h)              |
|       TSC[1:23h] - DAC_L and DAC_R Output Mixer Routing (00h)                    |
|       TSC[1:24h] - Analog Volume to HPL (Left Headphone) (7Fh)                   |
|       TSC[1:25h] - Analog Volume to HPR (Right Headphone) (7Fh)                  |
|       TSC[1:26h] - Analog Volume to SPL (Left Speaker) (7Fh)                     |
|       TSC[1:27h] - Analog Volume to SPR (Right Speaker) (7Fh)                    |
|       TSC[1:28h] - HPL Driver (Left Headphone) (02h)                             |
|       TSC[1:29h] - HPR Driver (Right Headphone) (02h)                            |
|       TSC[1:2Ah] - SPL Driver (Left Speaker) (00h)                               |
|       TSC[1:2Bh] - SPR Driver (Right Speaker) (00h)                              |
|       TSC[1:2Ch] - HP Driver Control (00h)                                       |
|       TSC[1:2Dh] - Reserved (xxh)                                                |
|       TSC[1:2Eh] - MICBIAS (00h)                                                 |
|       TSC[1:2Fh] - MIC PGA (80h)                                                 |
|       TSC[1:30h] - P-Terminal Delta-Sigma Mono ADC Channel Fine-Gain Input (00h) |
|       TSC[1:31h] - M-Terminal ADC Input Selection (00h)                          |
|       TSC[1:32h] - Input CM Settings (00h)                                       |
|       TSC[1:33h..FFh] - Reserved (xxh)                                           |
+----------------------------------------------------------------------------------+
```

### Reserved Page

```
+-----------------------------------------------------------------------+
|       TSC[2:01h..FFh] - Reserved (00h)                                |
+-----------------------------------------------------------------------+
```

### TSC Touchscreen/SAR Control

```
+-------------------------------------------------------------------------------------+
|       TSC[3:01h] - Reserved (xxh)                                                   |
|       TSC[3:02h] - SAR ADC Control 1 (00h)                                          |
|       TSC[3:03h] - SAR ADC Control 2 (00h)                                          |
|       TSC[3:04h] - Precharge and Sense (00h)                                        |
|       TSC[3:05h] - Panel Voltage Stabilization (00h)                                |
|       TSC[3:06h] - Voltage Reference (20h)                                          |
|       TSC[3:07h,08h] - Reserved (xxh)                                               |
|       TSC[3:09h] - Status Bits 1 (40h) (R)                                          |
|       TSC[3:0Ah] - Status Bits 2 (00h) (R)                                          |
|       TSC[3:0Bh,0Ch] - Reserved (xxh)                                               |
|       TSC[3:0Dh] - Buffer Mode (03h)  ;DSi: Unused,seems to use TSC[3:0Eh] instead  |
|       TSC[3:0Eh] - Reserved / Undocumented (read by DSi for Pen Down Test) (0Fh)    |
|       TSC[3:0Fh] - Scan Mode Timer (40h)                                            |
|       TSC[3:10h] - Scan Mode Timer Clock (81h)                                      |
|       TSC[3:11h] - SAR ADC Clock (81h)                                              |
|       TSC[3:12h] - Debounce Time for Pen-Up Detection (00h)                         |
|       TSC[3:13h] - Auto AUX Measurement Selection (00h)                             |
|       TSC[3:14h] - Touch-Screen Pen Down (00h)                                      |
|       TSC[3:15h] - Threshold Check Flags Register (00h) (R)                         |
|       TSC[3:16h,17h] - AUX1 Maximum Value Check MSB,LSB (0000h)                     |
|       TSC[3:18h,19h] - AUX1 Minimum Value Check MSB,LSB (0000h)                     |
|       TSC[3:1Ah,1Bh] - AUX2 Maximum Value Check MSB,LSB (0000h)                     |
|       TSC[3:1Ch,1Dh] - AUX2 Minimum Value Check MSB,LSB (0000h)                     |
|       TSC[3:1Eh,1Fh] - Temperature(TEMP1/TEMP2) Maximum Value Check MSB,LSB (0000h) |
|       TSC[3:20h,21h] - Temperature(TEMP1/TEMP2) Minimum Value Check MSB,LSB (0000h) |
|       TSC[3:22h...29h] - Reserved (xxh)                                             |
|       TSC[3:2Ah,2Bh] - Touchscreen X-Coordinate Data MSB,LSB (0000h) (R)            |
|       TSC[3:2Ch,2Dh] - Touchscreen Y-Coordinate Data MSB,LSB (0000h) (R)            |
|       TSC[3:2Eh,2Fh] - Touchscreen Z1-Pressure Register MSB,LSB (0000h) (R)         |
|       TSC[3:30h,31h] - Touchscreen Z2-Pressure Register MSB,LSB (0000h) (R)         |
|       TSC[3:32h...35h] - Reserved (xxh)                                             |
|       TSC[3:36h,37h] - AUX1 Data MSB,LSB (0000h) (R)                                |
|       TSC[3:38h,39h] - AUX2 Data MSB,LSB (0000h) (R)                                |
|       TSC[3:3Ah,3Bh] - VBAT Data MSB,LSB (0000h) (R)                                |
|       TSC[3:3Ch...41h] - Reserved (xxh)                                             |
|       TSC[3:42h,43h] - Temperature TEMP1 Data Register MSB,LSB (0000h) (R)          |
|       TSC[3:44h,45h] - Temperature TEMP2 Data Register MSB,LSB (0000h) (R)          |
|       TSC[3:46h...7Fh] - Reserved (xxh)                                             |
+-------------------------------------------------------------------------------------+
```

### TSC Coefficient RAM and Instruction RAM for ADC/DAC

```
+---------------------------------------------------------------------------+
|       TSC[04h..05h:xxh] - ADC Coefficient RAM (126 x 16bit)               |
|       TSC[06h..07h:xxh] - Reserved (00h)                                  |
|       TSC[08h:01h]      - DAC Coefficient RAM Control (00h)               |
|       TSC[08h..0Bh:xxh] - DAC Coefficient RAM, DAC Buffer A (252 x 16bit) |
|       TSC[0Ch..0Fh:xxh] - DAC Coefficient RAM, DAC Buffer B (252 x 16bit) |
|       TSC[10h..1Fh:xxh] - Reserved (00h)                                  |
|       TSC[20h..2Bh:xxh] - ADC DSP Engine Instruction RAM (384 x 24bit)    |
|       TSC[2Ch..3Fh:xxh] - Reserved (00h)                                  |
|       TSC[40h..5Fh:xxh] - DAC DSP Engine Instruction RAM (1024 x 24bit)   |
|       TSC[60h..FBh:xxh] - Reserved (00h)                                  |
+---------------------------------------------------------------------------+
```

### TSC Additional 3DS Registers (3DS only, and only on the 2nd SPI bus)

```
+-------------------------------------------------------------------------------+
|       TSC[64h:01h..xxh] - 3DS Config Registers for Sound (and Microphone?)    |
|       TSC[65h:01h..xxh] - 3DS Config Registers for Sound (and Microphone?)    |
|       TSC[67h:01h..xxh] - 3DS Config Registers for Touchscreen and Circle Pad |
|       TSC[FBh:01h..xxh] - 3DS Buffer Mode Data for Touchscreen and Circle Pad |
+-------------------------------------------------------------------------------+
```

### TSC Touchscreen/SAR Buffer

```
+-----------------------------------------------------------------------+
|       TSC[FCh:01h..xxh] - Buffer Mode Data MSB,LSB (xxxxh) (R)        |
|       TSC[FCh:xxh..7Fh] - Reserved (xxh)                              |
+-----------------------------------------------------------------------+
```

### TSC Undocumented Registers

```
+---------------------------------------------------------------------------------+
|       TSC[FDh:xxh] - Contains some undocumented non-zero values (DSi specific?) |
|       TSC[FEh:xxh] - Reserved (00h)                                             |
|       TSC[FFh:xxh] - Accessing this page changes operation (DSi specific?)      |
+---------------------------------------------------------------------------------+
```




