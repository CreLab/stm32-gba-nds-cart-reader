# DS Firmware Wifi Calibration Data


### Wifi Calibration/Settings (located directly after Firmware Header)

```
+-------------------------------------------------------------------------------------+
|       Addr Size Expl.                                                               |
|       000h-029h Firmware Header (see previous chapter)                              |
|       02Ah 2    CRC16 (with initial value 0) of [2Ch..2Ch+config_length-1]          |
|       02Ch 2    config_length (usually 0138h, ie. entries 2Ch..163h)                |
|       02Eh 1    Unused        (00h)                                                 |
|       02Fh 1    Version (0=v1..v4, 3=v5, 5=v6..v7,6=W006,15=W015,24=W024,34=N3DS)   |
|       030h 6    Unused        (00h-filled) (DS-Lite and DSi: FF,FF,FF,FF,FF,00)     |
|       036h 6    48bit MAC address (v1-v5: 0009BFxxxxxx, v6-v7: 001656xxxxxx)        |
|       03Ch 2    list of enabled channels ANDed with 7FFE (Bit1..14 = Channel 1..14) |
|                 (usually 3FFEh, ie. only channel 1..13 enabled)                     |
|       03Eh 2    Whatever Flags (usually FFFFh)                                      |
|       040h 1    RF Chip Type (NDS: usually 02h) (DS-Lite and DSi/3DS: usually 03h)  |
|       041h 1    RF Bits per entry at 0CEh (usually 18h=24bit=3byte) (Bit7=?)        |
|       042h 1    RF Number of entries at 0CEh (usually 0Ch)                          |
|       043h 1    Unknown (usually 01h)                                               |
|       044h 2    Initial Value for [4808146h]  ;W_CONFIG_146h                        |
|       046h 2    Initial Value for [4808148h]  ;W_CONFIG_148h                        |
|       048h 2    Initial Value for [480814Ah]  ;W_CONFIG_14Ah                        |
|       04Ah 2    Initial Value for [480814Ch]  ;W_CONFIG_14Ch                        |
|       04Ch 2    Initial Value for [4808120h]  ;W_CONFIG_120h                        |
|       04Eh 2    Initial Value for [4808122h]  ;W_CONFIG_122h                        |
|       050h 2    Initial Value for [4808154h]  ;W_CONFIG_154h                        |
|       052h 2    Initial Value for [4808144h]  ;W_CONFIG_144h                        |
|       054h 2    Initial Value for [4808130h]  ;W_CONFIG_130h                        |
|       056h 2    Initial Value for [4808132h]  ;W_CONFIG_132h                        |
|       058h 2    Initial Value for [4808140h]  ;W_CONFIG_140h ;maybe ACK timeout?    |
|       05Ah 2    Initial Value for [4808142h]  ;W_CONFIG_142h                        |
|       05Ch 2    Initial Value for [4808038h]  ;W_POWER_TX                           |
|       05Eh 2    Initial Value for [4808124h]  ;W_CONFIG_124h                        |
|       060h 2    Initial Value for [4808128h]  ;W_CONFIG_128h                        |
|       062h 2    Initial Value for [4808150h]  ;W_CONFIG_150h                        |
|       064h 69h  Initial 8bit values for BB[0..68h]                                  |
|       0CDh 1    Unused (00h)                                                        |
+-------------------------------------------------------------------------------------+
```

Below for Type2 (ie. when \[040h\]=2) (Mitsumi MM3155 and RF9008):

```
+------------------------------------------------------------------------------------+
|       0CEh 24h  Initial 24bit values for RF[0,4,5,6,7,8,9,0Ah,0Bh,1,2,3]           |
|       0F2h 54h  Channel 1..14 2x24bit values for RF[5,6]                           |
|       146h 0Eh  Channel 1..14 8bit values for BB[1Eh] (usually somewhat B1h..B7h)  |
|       154h 0Eh  Channel 1..14 8bit values for RF[9].Bit10..14 (usually 10h-filled) |
+------------------------------------------------------------------------------------+
```

Below for Type3 (ie. when \[040h\]=3) (Mitsumi MM3218) (and AR6013G):

```
+------------------------------------------------------------------------------------+
|       --- Type3 values are originated at 0CEh, following addresses depend on:  --- |
|       1) number of initial values, found at [042h]        ;usually 29h             |
|       2) number of BB indices,     found at [0CEh+[042h]] ;usually 02h             |
|       3) number of RF indices,     found at [043h]        ;usually 02h             |
|       --- Below example addresses assume above values to be set to 29h,02h,02h --- |
|       0CEh 29h  Initial 8bit values for RF[0..28h]                                 |
|       0F7h 1    Number of BB indices per channel                                   |
|       0F8h 1    1st BB index                                                       |
|       0F9h 14   1st BB data for channel 1..14                                      |
|       107h 1    2nd BB index                                                       |
|       108h 14   2nd BB data for channel 1..14                                      |
|       116h 1    1st RF index                                                       |
|       117h 14   1st RF data for channel 1..14                                      |
|       125h 1    2nd RF index                                                       |
|       126h 14   2nd RF data for channel 1..14                                      |
|       134h 46   Unused (FFh-filled)                                                |
+------------------------------------------------------------------------------------+
```

Below for both Type2 and Type3:

```
+-------------------------------------------------------------------------------------+
|       162h 1    Unknown (usually 19h..1Ch)                                          |
|       163h 1    Unused (FFh) (Inside CRC16 region, with config_length=138h)         |
|       164h 99h  Unused (FFh-filled) (Outside CRC16 region, with config_length=138h) |
|       1FDh 1    DSi/3DS Wifi Board (01h=W015, 02h=W024, 03h=W028);\this was         
|       1FEh 1    DSi/3DS Wifi Flash (20h=With access point 4/5/6) ; FFh-filled on DS |
|       1FFh 1    DSi/3DS Same as on DS (FFh)                      ;/                 |
+-------------------------------------------------------------------------------------+
```

Most of the Wifi settings seem to be always the same values on all currently existing consoles. Except for:
Values that are (obviously) different are the CRC16, and 4th-6th bytes of the MAC address. Also, initial values for BB\[01h\] and BB\[1Eh\], and channel 1..14 values for BB\[1Eh\], and unknown entry \[162h\] contain different calibration settings on all consoles.
Firmware v5 is having a new wifi ID \[2Fh\]=03h, and different RF\[9\] setting.
Firmware v6 (dslite) has wifi ID \[2Fh\]=05h, and same RF\[9\] setting as v5, additionally, v6 and up have different 2nd-3rd bytes of the MAC address.

Moreover, a LOT of values are different with Type3 chips (ie. when \[040h\]=3).

### Note
Unlike for Firmware User Settings, the Firmware Header (and Wifi Settings) aren\'t stored in RAM upon boot. So the data must be retrieved via SPI bus by software.



