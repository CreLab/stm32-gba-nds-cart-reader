# DSi Touchscreen/Sound Init Flowcharts


### touch_enable_tsc_init_list:

```
+-------------------------------------------------------------------------------------+
|       TSC[3:0Eh]=00h  ;Undoc (RMW: bit7=0)                                          |
|       TSC[3:02h]=18h  ;SAR ADC clk divider, Div8 (12bit mode) (RMW bit34=3, bit7=?) |
|       TSC[3:0Fh]=A0h  ;Scan Mode Timer                                              |
|       TSC[3:0Eh].28h  ;Undoc (RNW: bit345=5)                                        |
|       TSC[3:0Eh].28h  ;Undoc (RMW: bit6=0)                                          |
|       TSC[3:03h]=87h  ;SAR ADC Control 2 (SelfByPenDown, ScanXY, /PENIRQ)           |
|       TSC[3:05h].04h  ;Stabilization time = 30us (RMW bit012=4)                     |
|       TSC[3:04h].02h  ;Sense time = 3us          (RMW bit012=2)                     |
|       TSC[3:04h].22h  ;Precharge time = 3us      (RMW bit456=2)                     |
|       TSC[3:12h].00h  ;Debounce Time = 0us       (RMW bit012=0)                     |
|       TSC[3:0Eh].A8h  ;Undoc                     (RMW bit7=1)                       |
+-------------------------------------------------------------------------------------+
```


### mic_enable_tsc_init_list:
This is needed to unmute the microphone (otherwise microphone will return only 0000h or FFFFh.

```
+------------------------------------------------------------------------+
|       TSC[1:2Eh]=03h  ;MICBIAS=AVDD                                    |
|       TSC[0:51h]=80h  ;ADC Digital Mic, on                             |
|       TSC[0:52h]=00h  ;ADC Digital Volume Control Fine Adjust, unmute  |
|       TSC[1:2Fh]=37h  ;MIC PGA=27.5dB (or use other value, if desired) |
+------------------------------------------------------------------------+
```


### mic_disable_tsc_init_list:

```
+-----------------------------------------------------------------------+
|       TSC[0:52h]=80h  ;ADC Digital Volume Control Fine Adjust, mute   |
|       TSC[0:51h]=00h  ;ADC Digital Mic, off                           |
|       TSC[1:2Eh]=00h  ;MICBIAS=Off                                    |
+-----------------------------------------------------------------------+
```


### basic_tsc_init_list:
This is done by DSi Launcher/Unlaunch (and other titles usually won\'t need to do this).

```
+--------------------------------------------------------------------------------+
|       TSC[0:01h]=01h  ;Software Reset                                          |
|       TSC[0:39h]=66h  ;ADC DC Measurement 1                                    |
|       TSC[1:20h]=16h  ;Class-D Speaker Amplifier (RMW:bit4=1)                  |
|       TSC[0:04h]=00h  ;Clock-Gen Muxing                                        |
|       TSC[0:12h]=81h  ;ADC NADC Value                                          |
|       TSC[0:13h]=82h  ;ADC MADC Value                                          |
|       TSC[0:51h]=82h  ;ADC Digital Mic                                         |
|       TSC[0:51h]=00h  ;ADC Digital Mic again                                   |
|       TSC[0:04h]=03h  ;Clock-Gen Muxing                                        |
|       TSC[0:05h]=A1h  ;PLL P and R-Values                                      |
|       TSC[0:06h]=15h  ;PLL J-Value                                             |
|       TSC[0:0Bh]=87h  ;DAC NDAC Value                                          |
|       TSC[0:0Ch]=83h  ;DAC MDAC Value                                          |
|       TSC[0:12h]=87h  ;ADC NADC Value                                          |
|       TSC[0:13h]=83h  ;ADC MADC Value                                          |
|       TSC[3:10h]=88h  ;Scan Mode Timer Clock (RMW:bit0-6)                      |
|       TSC[4:08h..0Dh]=7Fh,E1h,80h,1Fh,7Fh,C1h  ;some coeff's                   |
|       TSC[0:41h]=08h  ;DAC Left Volume Control                                 |
|       TSC[0:42h]=08h  ;DAC Right Volume Control                                |
|       TSC[0:3Ah]=00h  ;GPI3 Pin Control                                        |
|       TSC[4:08h..0Dh]=7Fh,E1h,80h,1Fh,7Fh,C1h  ;some coeff's ;again?           |
|       TSC[1:2Fh]=2Bh  ;MIC PGA                                                 |
|       TSC[1:30h]=40h  ;P-Terminal Delta-Sigma Mono ADC Channel Fine-Gain Input |
|       TSC[1:31h]=40h  ;M-Terminal ADC Input Selection                          |
|       TSC[1:32h]=60h  ;Input CM Settings                                       |
|       TSC[0:74h]=82h  ;VOL/MICDET-Pin SAR ADC - Volume Control (RMW)           |
|       TSC[0:74h]=92h  ;VOL/MICDET-Pin SAR ADC - Volume Control (RMW)           |
|       TSC[0:74h]=D2h  ;VOL/MICDET-Pin SAR ADC - Volume Control (RMW)           |
|       TSC[1:21h]=20h  ;HP Output Drivers POP Removal Settings                  |
|       TSC[1:22h]=F0h  ;Output Driver PGA Ramp-Down Period Control              |
|       TSC[0:3Fh]=D4h  ;DAC Data-Path Setup (RMW)                               |
|       TSC[1:23h]=44h  ;DAC_L and DAC_R Output Mixer Routing                    |
|       TSC[1:1Fh]=D4h  ;Headphone Drivers                                       |
|       TSC[1:28h]=4Eh  ;HPL Driver (Left Headphone)                             |
|       TSC[1:29h]=4Eh  ;HPR Driver (Right Headphone)                            |
|       TSC[1:24h]=9Eh  ;Analog Volume to HPL (Left Headphone)                   |
|       TSC[1:25h]=9Eh  ;Analog Volume to HPR (Right Headphone)                  |
|       TSC[1:20h]=D4h  ;Class-D Speaker Amplifier                               |
|       TSC[1:2Ah]=14h  ;SPL Driver (Left Speaker)                               |
|       TSC[1:2Bh]=14h  ;SPR Driver (Right Speaker)                              |
|       TSC[1:26h]=A7h  ;Analog Volume to SPL (Left Speaker)                     |
|       TSC[1:27h]=A7h  ;Analog Volume to SPR (Right Speaker)                    |
|       TSC[0:40h]=00h  ;DAC Volume Control                                      |
|       (should set DSi.GPIO.data.bit7 here, but can be also done elsewhere)     |
|       TSC[0:3Ah]=60h  ;GPI3 Pin Control                                        |
+--------------------------------------------------------------------------------+
```


### nds_mode_tsc_init_list:
Switches to NDS Touchscreen/sound mode. Usually done when starting NDS titles (or DSi titles that request NDS-TSC mode in carthdr\[1BFh\]).

```
+--------------------------------------------------------------------------------+
|       TSC[1:26h]=ACh  ;\special setting (when found special gamecode)          
|       TSC[1:27h]=ACh  ;/                                                       |
|       TSC[1:26h]=A7h  ;\normal setting (for any other gamecodes)               
|       TSC[1:27h]=A7h  ;/                                                       |
|       TSC[1:2Eh]=03h  ;MICBIAS=AVDD                                            |
|       TSC[3:03h]=00h  ;SAR ADC Control 2                                       |
|       TSC[1:21h]=20h  ;HP Output Drivers POP Removal Settings                  |
|       TSC[1:22h]=F0h  ;Output Driver PGA Ramp-Down Period Control (70h OR 80h) |
|       TSC[1:22h]=70h  ;Output Driver PGA Ramp-Down Period Control (bit7=0)     |
|       TSC[0:52h]=80h  ;ADC Digital Volume Control Fine Adjust                  |
|       TSC[0:51h]=00h  ;ADC Digital Mic                                         |
|       READ[3:02h] (returns 00h)                                                |
|       TSC[3:02h].Bit7=1 ;SAR ADC Control 1 (set to 80h) (or 98h?) (RMW)        |
|       TSC[FFh:05h]=00h ;TSC final enter NDS mode                               |
+--------------------------------------------------------------------------------+
```

And, set powerman\[0\].bit0=1 (bit0=sound amplifier on) (this is actually part of TSC chip, accessed via \"POWERMAN\" SPI chipselect signal).



