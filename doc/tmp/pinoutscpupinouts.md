# Pinouts - CPU - Pinouts


### Advance Gameboy CPU Pinouts (CPU AGB)

```
+--------------------------------------------------------------------------------+
|       1 VDD3  17 D0   33 A0    49 WA4   65 VDD2  81 WD9   97 LDB5   113 CK1    |
|       2 IN35  18 A15  34 /CS   50 WA5   66 WD5   82 WD1   98 LDB4   114 CK2    |
|       3 TP8   19 A14  35 /RD   51 WA6   67 WD13  83 /WOE  99 LDB3   115 VDD2   |
|       4 TP0   20 A13  36 /WR   52 WA7   68 WD6   84 DCK   100 LDB2  116 GND    |
|       5 TP1   21 A12  37 PHI   53 /WLB  69 WD14  85 LP    101 LDB1  117 VDD2   |
|       6 SO1   22 A11  38 VDD35 54 /WUB  70 WD7   86 PS    102 GND   118 VCNT5  |
|       7 SO2   23 A10  39 GND   55 /WWE  71 WD15  87 LDR5  103 VDD3  119 TP9    |
|       8 Vin   24 A9   40 SC    56 WA8   72 WD8   88 LDR4  104 SPL   120 TP6    |
|       9 /RES  25 A8   41 SD    57 WA9   73 WD16  89 LDR3  105 CLS   121 TP5    |
|       10 D7   26 A7   42 SI    58 WA10  74 WA16  90 LDR2  106 SPS   122 TP7    |
|       11 D6   27 A6   43 SO    59 WA11  75 WD12  91 LDR1  107 MOD   123 TP4    |
|       12 D5   28 A5   44 VDD2  60 WA12  76 WD4   92 LDG5  108 REVC  124 /FIQ   |
|       13 D4   29 A4   45 WA0   61 WA13  77 WD11  93 LDG4  109 GNDed 125 /RESET |
|       14 D3   30 A3   46 WA1   62 WA14  78 WD3   94 LDG3  110 GNDed 126 TP2    |
|       15 D2   31 A2   47 WA2   63 WA15  79 WD10  95 LDG2  111 GNDed 127 TP3    |
|       16 D1   32 A1   48 WA3   64 GND   80 WD2   96 LDG1  112 GNDed 128 GND    |
+--------------------------------------------------------------------------------+
```


### GBA SP CPU Pinouts (CPU AGB B)

```
+-----------------------------------------------------------------------------------+
|       1 IN35   21 D0    41 A0    61 WA4   81 WD13  101 GND   121 LDB4  141 GND    |
|       2 TP8    22 A15   42 /CS   62 WA5   82 WD6   102 VDD1  122 LDB3  142 VDD3   |
|       3 TP0    23 A14   43 /RD   63 WA6   83 WD14  103 GND   123 LDB2  143 GND    |
|       4 TP1    24 A13   44 /WR   64 WA7   84 WD7   104 VDD3  124 LDB1  144 VCNT5  |
|       5 SO1    25 A12   45 PHI   65 /WLB  85 WD15  105 DCK   125 GND   145 TP9    |
|       6 SO2    26 A11   46 VDD35 66 /WUB  86 WD8   106 LP    126 VDD3  146 TP6    |
|       7 Vin    27 GND   47 GND   67 GND   87 WD16  107 PS    127 SPL   147 TP5    |
|       8 VDD1   28 VDD35 48 SC    68 VDD2  88 WA16  108 LDR5  128 CLS   148 TP7    |
|       9 GND    29 A10   49 SD    69 /WWE  89 VDD2  109 LDR4  129 SPS   149 TP4    |
|       10 VDD35 30 A9    50 SI    70 WA8   90 GND   110 LDR3  130 MOD   150 /FIQ   |
|       11 /RES  31 A8    51 SO    71 WA9   91 WD12  111 LDR2  131 REVC  151 /RESET |
|       12 D7    32 A7    52 VDD35 72 WA10  92 WD4   112 LDR1  132 GND   152 ?      |
|       13 D6    33 A6    53 GND   73 WA11  93 WD11  113 LDG5  133 GND   153 TP3    |
|       14 D5    34 A5    54 VDD1  74 WA12  94 WD3   114 LDG4  134 GND   154 TP2    |
|       15 D4    35 A4    55 GND   75 WA13  95 WD10  115 LDG3  135 GND   155 VDD3   |
|       16 D3    36 GND   56 VDD2  76 WA14  96 WD2   116 LDG2  136 VDD1  156 GND    |
|       17 D2    37 VDD35 57 WA0   77 WA15  97 WD9   117 LDG1  137 GND              |
|       18 GND   38 A3    58 WA1   78 GND   98 WD1   118 GND   138 CK1              |
|       19 VDD35 39 A2    59 WA2   79 VDD2  99 /WOE  119 VDD3  139 CK2              |
|       20 D1    40 A1    60 WA3   80 WD5   100 VDD2 120 LDB5  140 VDD2             |
+-----------------------------------------------------------------------------------+
```

Pin 152 seems to be not connected on the mainboard, maybe an undoc output.

### GBA-Micro, NDS, NDS-Lite Pinouts
Unknown. The CPU BGA Pins are hidden underneath of the CPU. And, in NDS and NDS-Lite, the CPU itself hides underneath of the DS Cartridge Slot.



