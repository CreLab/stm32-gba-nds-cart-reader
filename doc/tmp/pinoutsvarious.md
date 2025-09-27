# Pinouts - Various


### Advance Gameboy 256Kbytes RAM 128Kx16bit (NEC D442012LGY-B85x-MJH) (wide)
### GBA SP 256Kbytes RAM 128Kx16bit (F 82D12160-10FN) (square)

```
+-----------------------------------------------------------------------+
|       1 A15   7 A9    13 IC    19 A6   25 A0   31 D2   37 VCC  43 D15 |
|       2 A14   8 A8    14 /UB   20 A5   26 /CE1 32 D10  38 D5   44 D8  |
|       3 A13   9 NC    15 /LB   21 A4   27 GND  33 D3   39 D13  45 D16 |
|       4 A12   10 NC   16 NC    22 A3   28 /OE  34 D11  40 D6   46 GND |
|       5 A11   11 /WE  17 NC    23 A2   29 D1   35 D4   41 D14  47 NC  |
|       6 A10   12 CE2  18 A7    24 A1   30 D9   36 D12  42 D7   48 A16 |
+-----------------------------------------------------------------------+
```

Connection in GBA and GBA SP: IC-GND, /CE1-GND, CE2-VDD2, VCC-VDD2, Pin16-VDD2, the other NC pins seem to be actually not connected, all other pins connect to the corresponding Wxx CPU pins. Note: Both GBA and GBA SP have soldering points for wide (12x18mm) and square (12x14mm) RAMs, so either could be used.
The GBA additionally contains 32K built-in WRAM, and built-in VRAM, so the above 256K RAM chip is probably not used in 8bit classic/color gameboy mode.
Note: In the GBA Micro, the 256K RAM are contained on-chip in the CPU.

### Advance Gameboy Schematic Fragments
P2-VSS = VDD-15
VIN = VCC3 via R33
REGEXT (on my modified board, REGEXT underneath of my diodes)
/RES (OUT) (via R40)
/CS (via R39)
/WR (via R38)
SC (via Rxx)
SD (via Rxx)
SI (via Rxx)
SO (via Rxx)
DCK (via R36)
A-GND via CP4 (100uF) to GND (used speaker, and on headphone socket)

### GBA SP Schematic Fragments
P2VDD = VDD13
P2VSS = VDD15
/RES via R46
/CS via R45
/WR via R44
DCK via R20
VS=BT+
In my repaired GBA-SP: CK1 test-point is disconnected (instead GND\'ed).
In my repaired GBA-SP: broken oscillator replaced
In my repaired GBA-SP: broken r1 1mOhm replaced (near oscillator)
In my repaired GBA-SP: broken EXT2 socket metal-spring/snapper removed
CL1 FIQ (near SW4)
CL2 ?
CL3 ?
CL4 VOUT1/VDD1 (near U4)
CL5 VOUT3/VDD3 (near U4)
CL6 VOUT5/VDD5 (near U4)
DL1-red (power low) \-\--R32\--Q4\--R6\--
DL2-green (power good) \-\--Q6\--LOWBAT/R34-VDD3
DL3-orange (charge) \--R24\--Q2\--VIN/U57
P2VDD\--VDD13
P2VSS\--VDD15
S+ and S- are (almost) shortcut by R23 (1.0 ohm)
S+ via Q1 to VIN
VS via D1 to S-
A-GND via CP1 (100uF) to GND
U4 pin 12 to r6 (towards red led)
U4 pin 14 to D6\-\--to U7
SC (CPU pin48) with R7 100K ohm pullup to VDD35
P35 via Q11 to SW (speaker disable)

### GBA SP Backlight-Button Schematic (U6,U8,Q12)

```
+---------------------------------------------------------------------------+
|             ______                _____                                   |
|       GND--|1 U8 6|-- U85        |     |--VDD5                            |
|       U82--|2    5|-- U85    U61-| Q12 |         U83  ------> to display  |
|       U83--|3____4|-- U82        |_____|--Q12B   Q12B <------ from button |
|       U61--|1 U6 8|--VDD5    (X)---R51--VDD5    (X)---C70--GND            |
|       U62--|2    7|--VDD5    U62---R49--VDD5    U61---R40--GND            |
|       U62--|3    6|--(X)     Q12B--R39--VDD5    U82---R38--GND            |
|       GND--|4____5|--NC?     Q12B--C69--VDD5    U85---R50--U62            |
+---------------------------------------------------------------------------+
```




