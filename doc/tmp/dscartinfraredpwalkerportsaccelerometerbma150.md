# DS Cart Infrared P-Walker Ports Accelerometer BMA150


### Might do drilling machine, not good honking out paste pretty screenshot?
Official BMA150 register specs are in a Bosch-Captcha, which appears to be intended to fool humans and bots alike (text on hatched background, undefined color codes, increasingly unpleasant medusa-like details at closer look). Anyways, here\'s a plaintext-hack of the Bosch-Captcha:

```
+-------------------------------------------------------------------------------------+
|       00h  Chip ID     (bit7-3=Unused, bit2-0=02h)                                  |
|       01h  Version     (bit7-4=al_version, bit3-0=ml_version) (undefined values)    |
|       02h  Acc X Low   (bit7-6=DataLsb, bit5-1=Unused, bit0=NewDataFlag)            |
|       03h  Acc X High  (bit7-0=DataMsb)                                             |
|       04h  Acc Y Low   (bit7-6=DataLsb, bit5-1=Unused, bit0=NewDataFlag)            |
|       05h  Acc Y High  (bit7-0=DataMsb)                                             |
|       06h  Acc Z Low   (bit7-6=DataLsb, bit5-1=Unused, bit0=NewDataFlag)            |
|       07h  Acc Z High  (bit7-0=DataMsb)                                             |
|       08h  Temperature (bit7-0=DataTempMsb) (Lsb not existing, except in Trimming?) |
|       09h  Status Flags     (see below)                                             |
|       0Ah  Control Flags    (see below)                                             |
|       0Bh  Config Flags     (see below)                                             |
|       0Ch  LG Threshold     (bit7-0)                                                |
|       0Dh  LG Duration      (bit7-0)                                                |
|       0Eh  HG Threshold     (bit7-0)                                                |
|       0Fh  HG Duration      (bit7-0)                                                |
|       10h  Any Motion Threshold (bit7-0)                                            |
|       11h  Misc Stuff       (bit7-6=AnyMotionDur, bit5-3=HG Hyst, bit2-0=LG Hyst)   |
|       12h  Customer Reserved 1 (bit7-0)                                             |
|       13h  Customer Reserved 2 (bit7-0)                                             |
|       14h  Range/Bandwidth  (bit7-5=Reserved, bit4-3=Range, bit2-0=Bandwidth)       |
|       15h  Misc Flags       (see below)                                             |
|       16h  Trimming X Low   (bit7-6=OffsetLsb, bit5-0=Gain)                         |
|       17h  Trimming Y Low   (bit7-6=OffsetLsb, bit5-0=Gain)                         |
|       18h  Trimming Z Low   (bit7-6=OffsetLsb, bit5-0=Gain)                         |
|       19h  Trimming T Low   (bit7-6=OffsetLsb, bit5-0=Gain)                         |
|       1Ah  Trimming X High  (bit7-0=OffsetMsb)                                      |
|       1Bh  Trimming Y High  (bit7-0=OffsetMsb)                                      |
|       1Ch  Trimming Z High  (bit7-0=OffsetMsb)                                      |
|       1Dh  Trimming T High  (bit7-0=OffsetMsb)                                      |
|       1Eh-22h BST reserved  (official blank/green)                                  |
|       23h     BST reserved  (official blank/white)                                  |
|       24h-2Ah Not used      (official gray/dither)                                  |
|       2Bh-3Dh EEPROM Defaults for Registers 0Bh-1Dh                                 |
|       3Eh-42h BST reserved  (official blank/orange)                                 |
|       43h-49h Not used      (official gray/dither)                                  |
|       4Ah-4Fh Not mentioned (official not here)                                     |
|       50h-7Fh BST reserved  (official blank/cyan)                                   |
+-------------------------------------------------------------------------------------+
```

Obscure Notes: Registers are 00h-06h,21h-22h,43h-7Fh are classifed as NOTHING, 07h-20h as IMAGE, and 23h-42h as EEPROM (whatever that crap means). Also, Registers 00h-15h are OPERATIONAL, 16h-3Dh are DEFAULT SETTING, 3Eh-7Fh are BOSCH SENSORTEC RESERVED.

### Register 09h - Status Flags

```
+-----------------------------------------------------------------------+
|       7   ST Result                                                   |
|       6-5 Not used (official piss/dither)                             |
|       4   Alert Phase                                                 |
|       3   LG_latched                                                  |
|       2   HG_latched                                                  |
|       1   LG_status                                                   |
|       0   HG_status                                                   |
+-----------------------------------------------------------------------+
```


### Register 0Ah - Control Flags

```
+-----------------------------------------------------------------------+
|       7   Reserved (official gray/dither)                             |
|       6   Reset INT                                                   |
|       5   Update IMAGE                                                |
|       4   EE_W (uh? maybe eeprom write?)                              |
|       3   Self Test 1                                                 |
|       2   Self Test 0                                                 |
|       1   Soft Reset                                                  |
|       0   Sleep                                                       |
+-----------------------------------------------------------------------+
```


### Register 0Bh - Config Flags

```
+-----------------------------------------------------------------------+
|       7   Alert                                                       |
|       6   Any Motion                                                  |
|       5-4 Counter HG                                                  |
|       3-2 Counter LG                                                  |
|       1   Enable HG                                                   |
|       0   Enable LG                                                   |
+-----------------------------------------------------------------------+
```


### Register 15h - Misc Flags

```
+-----------------------------------------------------------------------+
|       7   SPI4                                                        |
|       6   enable_adv_INT                                              |
|       5   new_data_INT                                                |
|       4   latch_INT                                                   |
|       3   shadow_dis                                                  |
|       2-1 wake_up_pause                                               |
|       0   wake_up                                                     |
+-----------------------------------------------------------------------+
```




