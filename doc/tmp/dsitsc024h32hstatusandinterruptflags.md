# DSi TSC\[0:24h..32h\], Status and Interrupt Flags


### TSC\[0:24h\] - ADC Flag Register (0xh) (R)

```
+-----------------------------------------------------------------------------+
|       7     ADC PGA applied gain = programmed gain (0=Differs, 1=Equal) (R) |
|       6     ADC powered                  (0=Powered down, 1=Powered up) (R) |
|       5     AGC saturated        (0=No/inrange, 1=Yes/saturated to max) (R) |
|       4-0   Reserved. Write only zeros to these bits.                       |
+-----------------------------------------------------------------------------+
```

Note on D5(?): Sticky flag bIts. These are read-only bits. They are automatically cleared once they are read and are set only if the source trigger occurs again.

### TSC\[0:25h\] - DAC Flag Register (00h) (R)

```
+-------------------------------------------------------------------------------------+
|       7     Left-channel DAC powered             (0=Powered down, 1=Powered up) (R) |
|       6     Reserved. Write only zero to this bit.                                  |
|       5     Left Headphone HPL driver powered    (0=Powered down, 1=Powered up) (R) |
|       4     Left-channel class-D driver powered  (0=Powered down, 1=Powered up) (R) |
|       3     Right-channel DAC powered            (0=Powered down, 1=Powered up) (R) |
|       2     Reserved. Write only zero to this bit.                                  |
|       1     Right Headphone HPR driver powered   (0=Powered down, 1=Powered up) (R) |
|       0     Right-channel class-D driver powered (0=Powered down, 1=Powered up) (R) |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:26h\] - DAC Flag Register (00h) (R)

```
+-------------------------------------------------------------------------------------+
|       7-5   Reserved. Do not write to these bits.                                   |
|       4     Left-channel DAC PGA applied gain=programmed gain  (0=Differs, 1=Equal) |
|       3-1   Reserved. Write only zeros to these bits.                               |
|       0     Right-channel DAC PGA applied gain=programmed gain (0=Differs, 1=Equal) |
+-------------------------------------------------------------------------------------+
```


### TSC\[0:27h\] - Overflow Flags (00h) (R)

```
+-------------------------------------------------------------------------------+
|       7     Left-Channel DAC Overflow Flag           (0=None, 1=Overflow) (R) |
|       6     Right-Channel DAC Overflow Flag          (0=None, 1=Overflow) (R) |
|       5     DAC Barrel Shifter Output Overflow Flag  (0=None, 1=Overflow) (R) |
|       4     Reserved. Write only zeros to these bits.                         |
|       3     Delta-Sigma Mono ADC Overflow Flag       (0=None, 1=Overflow) (R) |
|       2     Reserved. Write only zero to this bit.                            |
|       1     ADC Barrel Shifter Output Overflow Flag  (0=None, 1=Overflow) (R) |
|       0     Reserved. Write only zero to this bit.                            |
+-------------------------------------------------------------------------------+
```

Sticky flag bIts. These are read-only bits. They are automatically cleared once they are read and are set only if the source trigger occurs again.

### TSC\[0:28h..2Bh\] - Reserved (xxh)

```
+-----------------------------------------------------------------------+
|       7-0   Reserved. Write only the reset value to these bits.       |
+-----------------------------------------------------------------------+
```


### TSC\[0:2Ch\] - Interrupt Flags DAC, sticky (00h..30h) (R)

```
+-------------------------------------------------------------------------------------+
|       7     Short-circuit detected at HPL/left class-D driver         (0=No, 1=Yes) |
|       6     Short-circuit detected at HPR/right class-D driver        (0=No, 1=Yes) |
|       5     Headset button pressed                                    (0=No, 1=Yes) |
|       4     Headset insertion/removal is detected                     (0=No, 1=Yes) |
|       3     Left DAC signal power vs signal threshold of DRC (0=Less/Equal,1=Above) |
|       2     Right DAC signal power vs signal threshold of DRC(0=Less/Equal,1=Above) |
|       1     DAC miniDSP Engine Standard Interrupt-Port Output  (0=Read 0, 1=Read 1) |
|       0     DAC miniDSP Engine Auxiliary Interrupt-Port Output (0=Read 0, 1=Read 1) |
+-------------------------------------------------------------------------------------+
```

Sticky flag bIts. These are read-only bits. They are automatically cleared once they are read and are set only if the source trigger occurs again.

### TSC\[0:2Dh\] - Interrupt Flags ADC, sticky (00h..18h) (R)

```
+-------------------------------------------------------------------------------------+
|       7     Reserved. Write only zero to this bit.                                  |
|       6     ADC signal power vs noise threshold for AGC (0=Greater, 1=Less)         |
|       5     Reserved. Write only zeros to these bits.                               |
|       4     ADC miniDSP Engine Standard Interrupt Port Output  (0=Read 0, 1=Read 1) |
|       3     ADC miniDSP Engine Auxiliary Interrupt Port Output (0=Read 0, 1=Read 1) |
|       2     DC measurement using Delta Sigma Audio ADC                              |
|               (0=Not available, 1=Not available, too, uh?)                          |
|       1-0   Reserved. Write only zeros to these bits.                               |
+-------------------------------------------------------------------------------------+
```

Sticky flag bIts. These are read-only bits. They are automatically cleared once they are read and are set only if the source trigger occurs again.

### TSC\[0:2Eh\] - Interrupt Flags DAC, non-sticky? (00h..30h) (R)

```
+-------------------------------------------------------------------------------------+
|       7     Short circuit detected at HPL/left class-D driver         (0=No, 1=Yes) |
|       6     Short circuit detected at HPR/right class-D driver        (0=No, 1=Yes) |
|       5     Headset button pressed                                    (0=No, 1=Yes) |
|       4     Headset removal/insertion detected             (0=Removal, 1=Insertion) |
|       3     Left DAC signal power vs signal threshold of DRC     (0=Below, 1=Above) |
|       2     Right DAC signal power vs signal threshold of DRC    (0=Below, 1=Above) |
|       1     DAC miniDSP Engine Standard Interrupt Port Output  (0=Read 0, 1=Read 1) |
|       0     DAC miniDSP Engine Auxiliary Interrupt Port Output (0=Read 0, 1=Read 1) |
+-------------------------------------------------------------------------------------+
```

This is (almost?) same as TSC\[0:2Ch\]. Maybe this is current state (non-sticky)?

### TSC\[0:2Fh\] - Interrupt Flags ADC, non-sticky? (00h..18h) (R)

```
+-------------------------------------------------------------------------------------+
|       7     Reserved                                                                |
|       6     Delta-sigma mono ADC signal power vs noise threshold for left AGC       |
|       5     Reserved                                       (0=Greater, 1=Less)      |
|       4     ADC miniDSP Engine Standard Interrupt Port Output  (0=Read 0, 1=Read 1) |
|       3     ADC miniDSP Engine Auxiliary Interrupt Port Output (0=Read 0, 1=Read 1) |
|       2     DC measurement using Delta Sigma Audio ADC                              |
|               (0=Not available, 1=Not available, too, uh?)                          |
|       1-0   Reserved. Write only zeros to these bits.                               |
+-------------------------------------------------------------------------------------+
```

This is (almost?) same as TSC\[0:2Dh\]. Maybe this is current state (non-sticky)?

### TSC\[0:30h\] - INT1 Control Register (Select INT1 Sources) (00h)
### TSC\[0:31h\] - INT2 Control Register (Select INT2 Sources) (00h)

```
+-------------------------------------------------------------------------------------+
|       7     Headset-insertion detect                                  (0=Off, 1=On) |
|       6     Button-press detect                                       (0=Off, 1=On) |
|       5     DAC DRC signal-power                                      (0=Off, 1=On) |
|       4     ADC AGC noise                                             (0=Off, 1=On) |
|       3     Short-circuit                                             (0=Off, 1=On) |
|       2     Engine-generated                                          (0=Off, 1=On) |
|       1     DC measurement using Delta Sigma Audio ADC data-available (0=Off, 1=On) |
|       0     INT duration (0=Pulse Once, 1=Pulse Repeatedly until Acknowledge)       |
+-------------------------------------------------------------------------------------+
```

Bit1-7 select which sources shall trigger INT1/INT2, a few more sources can be selected in TSC\[0:32h\].Bit5-7.
Bit0 selects how the INT1/INT2 signal shall be pulsed (once with 2ms length, or repeating every 4ms with 50% duty, until it gets acknowledged by reading TSC\[0:2Ch,2Dh,32h\]).

### TSC\[0:32h\] - INT1 and INT2 Control Register (00h)

```
+-------------------------------------------------------------------------------------+
|       7     INT1 upon SAR measurement data-out-of-threshold range   (0=Off, 1=Off?) |
|       6     INT1 upon Pen touch/SAR data-available                    (0=Off, 1=On) |
|       5     INT2 upon SAR measurement data-out-of-threshold range   (0=Off, 1=Off?) |
|       4     Reserved                                                                |
|       3     Pen touch detected                          (0=No, 1=Touch)     (R)     |
|       2     Data available for read                     (0=No, 1=Available) (R)     |
|       1     SAR data out of programmed threshold range  (0=No, 1=Out)       (R)     |
|       0     Reserved. Write only the default value to this bit.             (R)     |
+-------------------------------------------------------------------------------------+
```




