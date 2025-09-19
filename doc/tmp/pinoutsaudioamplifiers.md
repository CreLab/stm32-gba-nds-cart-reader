# Pinouts - Audio Amplifiers


### Advance Gameboy Audio Amplifier (AMP AGB IR3R60N) (U6)

```
+------------------------------------------------------------------------------------+
|       1   2   3   4   5   6   7   8   9   10  11  12   13   14   15   16   17  18  |
|       C38 FR1 FR2 FL1 FL2 GND RIN LIN C39 VOL SW  VDD5 LOUT VCC3 ROUT VCC3 SP  GND |
+------------------------------------------------------------------------------------+
```

SW=Headphone Switch (grounded when none connected).

### GBA SP Audio Amplifier (uses AMB AGB IR3R60N, too) (U3)
Same connection as in GBA, except that pin14/16 connect to VR21 (instead VCC3), and pin1/9 connect to different capacitors.

### NDS - National Semiconductor LM4880M Dual 250mW Audio Power Amplifier (U12)

```
+--------------------------------------------------------------------------------+
|       1-OUT A  2-IN A  3-BYPASS  4-GND  5-SHUTDOWN  6-IN B  7-OUT A  8-VDD.VQ5 |
+--------------------------------------------------------------------------------+
```

NDS-Lite: No external amplifier (Mitsumi 3205B Powermanagment Device contains internal amplifier).



