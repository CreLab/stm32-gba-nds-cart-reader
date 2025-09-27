# DS Firmware Extended Settings


Extended Settings contain some additional information which is not supported by the original firmware (current century, date/time formats, temperature calibration, etc.), the settings are supported by Nocash Firmware, by the no\$gba emulator, and may be eventually also supported by other emulators. If present, the values can be used by games, otherwise games should use either whatever default settings, or contain their own configuration menu.

### Extended Settings - loaded to 23FEE00h (aka fragments of NDS9 boot code)

```
+------------------------------------------------------------------------------------+
|       Addr Siz Expl.                                                               |
|       00h  8  ID "XbooInfo"                                                        |
|       08h  2  CRC16 Value [0Ch..0Ch+Length-1]                                      |
|       0Ah  2  CRC16 Length (from 0Ch and up)                                       |
|       0Ch  1  Version (currently 01h)                                              |
|       0Dh  1  Update Count (newer = (older+1) AND FFh)                             |
|       0Eh  1  Bootmenu Flags                                                       |
|                 Bit6   Important Info  (0=Disable, 1=Enable)                       |
|                 Bit7   Bootmenu Screen (0=Upper, 1=Lower)                          |
|       0Fh  1  GBA Border (0=Black, 1=Gray Line)                                    |
|       10h  2  Temperature Calibration TP0 ADC value  (x16) (sum of 16 ADC values)  |
|       12h  2  Temperature Calibration TP1 ADC value  (x16) (sum of 16 ADC values)  |
|       14h  2  Temperature Calibration Degrees Kelvin (x100) (0=none)               |
|       16h  1  Temperature Flags                                                    |
|                 Bit0-1 Format (0=Celsius, 1=Fahrenheit, 2=Reaumur, 3=Kelvin)       |
|       17h  1  Backlight Intensity (0=0ff .. FFh=Full)                              |
|       18h  4  Date Century Offset       (currently 20, for years 2000..2099)       |
|       1Ch  1  Date Month Recovery Value (1..12)                                    |
|       1Dh  1  Date Day Recovery Value   (1..31)                                    |
|       1Eh  1  Date Year Recovery Value  (0..99)                                    |
|       1Fh  1  Date/Time Flags                                                      |
|                 Bit0-1 Date Format   (0=YYYY-MM-DD, 1=MM-DD-YYYY, 2=DD-MM-YYYY)    |
|                 Bit2   Friendly Date (0=Raw Numeric, 1=With Day/Month Names)       |
|                 Bit5   Time DST      (0=Hide DST, 1=Show DST=On/Off)               |
|                 Bit6   Time Seconds  (0=Hide Seconds, 1=Show Seconds)              |
|                 Bit7   Time Format   (0=24 hour, 1=12 hour)                        |
|       20h  1  Date Separator      (Ascii, usually Slash, or Dot)                   |
|       21h  1  Time Separator      (Ascii, usually Colon, or Dot)                   |
|       22h  1  Decimal Separator   (Ascii, usually Comma, or Dot)                   |
|       23h  1  Thousands Separator (Ascii, usually Comma, or Dot)                   |
|       24h  1  Daylight Saving Time (Nth)                                           |
|                  Bit 0-3 Activate on (0..4 = Last,1st,2nd,3rd,4th)                 |
|                  Bit 4-7 Deactivate on (0..4 = Last,1st,2nd,3rd,4th)               |
|       25h  1  Daylight Saving Time (Day)                                           |
|                  Bit 0-3 Activate on (0..7 = Mon,Tue,Wed,Thu,Fri,Sat,Sun,AnyDay)   |
|                  Bit 4-7 Deactivate on (0..7 = Mon,Tue,Wed,Thu,Fri,Sat,Sun,AnyDay) |
|       26h  1  Daylight Saving Time (of Month)                                      |
|                  Bit 0-3 Activate DST in Month   (1..12)                           |
|                  Bit 4-7 Deactivate DST in Month (1..12)                           |
|       27h  1  Daylight Saving Time (Flags)                                         |
|                  Bit 0   Current DST State (0=Off, 1=On)                           |
|                  Bit 1   Adjust DST Enable (0=Disable, 1=Enable)                   |
+------------------------------------------------------------------------------------+
```

Note: With the original firmware, the memory region at 23FEE00h and up contains un-initialized, non-zero-filled data (fragments of boot code).



