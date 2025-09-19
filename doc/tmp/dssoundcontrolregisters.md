# DS Sound Control Registers


### 4000500h - NDS7 - SOUNDCNT - Sound Control Register (R/W)

```
+-----------------------------------------------------------------------------+
|       Bit0-6   Master Volume       (0..127=silent..loud)                    |
|       Bit7     Not used            (always zero)                            |
|       Bit8-9   Left Output from    (0=Left Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3)  |
|       Bit10-11 Right Output from   (0=Right Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3) |
|       Bit12    Output Ch1 to Mixer (0=Yes, 1=No) (both Left/Right)          |
|       Bit13    Output Ch3 to Mixer (0=Yes, 1=No) (both Left/Right)          |
|       Bit14    Not used            (always zero)                            |
|       Bit15    Master Enable       (0=Disable, 1=Enable)                    |
|       Bit16-31 Not used            (always zero)                            |
+-----------------------------------------------------------------------------+
```


### 4000504h - NDS7 - SOUNDBIAS - Sound Bias Register (R/W)

```
+-----------------------------------------------------------------------+
|       Bit0-9   Sound Bias    (0..3FFh, usually 200h)                  |
|       Bit10-31 Not used      (always zero)                            |
+-----------------------------------------------------------------------+
```

After applying the master volume, the signed left/right audio signals are in range -200h..+1FFh (with medium level zero), the Bias value is then added to convert the signed numbers into unsigned values (with medium level 200h).
BIAS output is always enabled, even when Master Enable (SOUNDCNT.15) is off.

The sampling frequency of the mixer is 1.04876 MHz with an amplitude resolution of 24 bits, but the sampling frequency after mixing with PWM modulation is 32.768 kHz with an amplitude resolution of 10 bits.



