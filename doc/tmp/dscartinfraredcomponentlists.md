# DS Cart Infrared Component Lists


### Gamecart for Walk with Me/Laufrhythmus

```
+-------------------------------------------------------------------------------------+
|       Case "Nintendo, NTR-031. PAT. PEND., IMWPN1J12"                               |
|       PCB  "DA A-4  IRU01-10" (two layers) plus "IRL01-01 "(brown extra film layer) |
|       U1 32pin  "S906748-1, SanDisk, 11014-64B, P0A837.00, 0843, NTR-IMWP-1" (ROM)  |
|       U2 32pin  "38600R, A06V, AH00167, 0832" (CPU, ROM 8Kbyte, RAM 0.5KByte)       |
|       U3  5pin  "?" (OR-gate? flipflop?) (for forwarding SPI /CS to FLASH /CS)      |
|       U4  8pin  "45PE80VG, HPAMZ V5, KOR 833X, ST e3" (SPI FLASH 1024 Kbytes)       |
|       U1' 7pin  "5  S.. 9" IR transceiver (on brown film layer)                     |
|       X1  6pin  "737Wv"   ;7.37MHz?    /FLASH.CS --|""""|-- GND                     |
|       R1,R2,RA1 resistors                          | U3 |-- /SPI.CS (from NDS)      |
|       C1,C2,C3,C4,C5,C6 capacitors         VDD33 --|____|-- U2.pinxxx               |
+-------------------------------------------------------------------------------------+
```

Note: The printed part number on the CPU is 38600R, which does officially have ROM 8Kbyte, RAM 0.5KByte (and the software does use only that much memory, but it does actually contain twice as much ROM and RAM, ie. it seems to be a 38602R chip\... or, as the part number is wrong, it MIGHT even be a F38602 with FLASH memory?).
IR transceiver wiring: 1=GND, 2=CPU.pin24=TXD, 3=CPU.pin25=RXD, 4=CPU.pin26=PWDOWN, 5=NC, 6=GND, 7=VCC.

### Gamecart for P-Letter Black

```
+----------------------------------------------------------------------------------+
|       PCB  "DI Y-1  IRC02-01" (two layers, without brown extra film layer)       |
|       U1 32pin  "MXIC..." (ROM)                                                  |
|       U2 32pin  "..." (CPU, ROM 8Kbyte, RAM 0.5KByte)                            |
|       U3  5pin  "..." (OR-gate? flipflop?) (for forwarding SPI /CS to FLASH /CS) |
|       U4  8pin  "..." (SPI FLASH)                                                |
|       U5  7pin  "..." IR transceiver                                             |
|       X1  6pin  "..."                                                            |
|       R1,R2,RA1 resistors                                                        |
|       C1,C2,C3,C4,C5,C6 capacitors                                               |
+----------------------------------------------------------------------------------+
```

More or less same as in Walk with Me, but without film layer, and with non-legible part numbers on existing photos.

### Activity Meter (Actimeter in german) (Nintendo, 2008-2009)
NTR-IMWJ Aruite Wakaru Seikatsu Rhythm (JP)
NTR-IMWE Personal Trainer: Walking (US)
NTR-IMWP Walk with Me (EU) (Laufrhythmus in german)
NTR-IA8P Active Health with Carol Vorderman (EU)

```
+-------------------------------------------------------------------------------------+
|       Case "Nintendo DS, NTR-027, (C) 2008 Nintendo, NTR-A-HC, Made in Japan"       |
|       Case "CE ./ VCI, ACN 060 566 083, Nintendo"                                   |
|       PCB  "NTR-DHC-01" (in water resistant case)                                   |
|       Ux  32pin Side-A "38602R, F22V, AH04731, 0834" (CPU, ROM 16Kbyte, RAM 1KByte) |
|       U2  8pin  Side-B "564X, 48H3, 30" (SPI EEPROM 8Kbyte, ST M95640-W or similar) |
|       U3  7pin  Side-B "1  S.  9" IR transceiver                                    |
|       ??  2pin  Side-A huge smd capacitor shaped thing, maybe analog 1-axis sensor? |
|       ??  2pin  Side-A huge smd capacitor shaped thing, maybe analog 1-axis sensor? |
|       Ux/Qx     Side-A many small chips with 3-6 pins and few markings              |
|       Xx  3pin  Side-A "CB825"      ;32.768-kHz or 38.4-kHz Crystal Resonator?      |
|       Yx  6pin  Side-A ":i] 3.68t"  ;3.68MHz (115.2kHz*32)                          |
|       C1..C34   Plenty capacitors                                                   |
|       R1..R28   Plenty resistors                                                    |
|       BTI 2pin  Side-B Battery holder (for CR2032 H, 3V)                            |
|       Button    Side-A Push button (communication button)                           |
|       |<  4pin  Side-A Two color LED                                                |
+-------------------------------------------------------------------------------------+
```

Activity Meter Instruction Booklet, 310 pages: \"Do not disassemble or attempt to repair the Activity Meter yourself. Doing so could result in injury or electrocution.\"
IR transceiver wiring: 1=BAT+, 2=TX-RC=NC?, 3=1K-to-CPU.pin25=RXD, 4=CPU.pin26=PWDOWN, 5=CPU.pin24=TXD, 6=?, 7=GND.

### P-Walker (Nintendo, 2009)
NTR-IPKx/NTR-IPGx P-letter HeartGold/SoulSilver
TWL-IRBO/TWL-IRAO P-letter Black/White
TWL-IREO/TWL-IRDO P-letter Black/White 2

```
+-------------------------------------------------------------------------------------+
|       Case "?"                                                                      |
|       PCB "NTR-PHC-01" (with green solder stop & unconventional black text layer)   |
|       U1  32pin Side-B "F38606, F04V, AK04052, 0942" (CPU,FLASH 48Kbyte,RAM 2KByte) |
|       U2  4pin  Side-A "?"                                                          |
|       U3  4pin  Side-A "?"                                                          |
|       U4  4pin  Side-A "M_RA"                                                       |
|       U5  7pin  Side-B IR transceiver                                               |
|       U6  8pin  Side-A "Sxxxx, xxxx" (maybe SPI EEPROM?)                            |
|       U7  12pin Side-B "043, A939, 021" (accelerometer?) (Bosch BMA150 ?)           |
|       U8  5pin  Side-A "?"                                                          |
|       Q1  6pin  Side-A "Z4"                                                         |
|       D1  3pin  Side-A "?" dual diode or so                                         |
|       X1  3pin  Side-B "EAJJ"       ;32.768-kHz or 38.4-kHz Crystal Resonator?      |
|       Y1  6pin  Side-B "3.68"       ;3.68MHz (115.2kHz*32)                          |
|       BZ1 2pin  Side-B wires to piezo speaker (aka buzzer)                          |
|       CN1 14pin Side-A LCD connector 14pin? or 2x14pin? (without backlight)         |
|                 (with SSD1850 display controller (or similar) inside of LCD screen) |
|                 (96x64 2-bit greyscale screen) (reportedly with SPI bus)            |
|       BT+/-     Side-B Battery contacts for removeable battery (for CR2032, 3V)     |
|       C1..C29   Plenty capacitors                                                   |
|       R1..R22   Plenty resistors                                                    |
|       SW's      Side-A Three buttons (left, center, right)                          |
+-------------------------------------------------------------------------------------+
```


### Fit Meter (for Wii Fit U) (2013?)

```
+--------------------------------------------------------------------------------+
|       PCB "SAMU-01" (with green solder stop & unconventional black text layer) |
|       U1  40pin Side-B "R5F101EEA, 1242KE415, SINGAPORE" (RL78 CPU)            |
|       U2  7pin  Side-B "845G2947" IR transceiver, with metal shield            |
|       U3  16pin Side-B (not installed)                                         |
|       U4  16pin Side-A --UNKNOWN MARKING, BAD PHOTO-- maybe accelerometer      |
|       U5  4pin  Side-A --UNKNOWN MARKING, BAD PHOTO-- maybe SPI EEPROM/FLASH   |
|       U6  4pin  Side-A (not installed)                                         |
|       U7  7pin  Side-B "I357, U231, 094" whatever, in metal shielded case      |
|       X1  3pin  Side-B "EABL" crystal or so                                    |
|       BZ1 2pin  Side-B wires to piezo speaker (aka buzzer)                     |
|       CN1 14pin Side-A LCD connector 14pin? or 2x14pin? (without backlight)    |
|       BT+/-     Side-B Battery contacts for removeable battery                 |
|       Q1  3pin  Side-A Transistor or so                                        |
|       D1..D2    Side-A Diodes (3pin each)                                      |
|       C1..C29   Plenty capacitors                                              |
|       R1..R22   Plenty resistors                                               |
|       SW's      Side-A Three buttons (left, center, right)                     |
+--------------------------------------------------------------------------------+
```

Similar as P-Walker, but uses a RL78 CPU (alike 3DS MCU) instead of H8/386.

The IR transceivers do resemble RPM841-H16 or similar (as used in 3DS). Observe that 7pin transceiver pinouts are NOT same. Walk with Me, Activity Meter, and 3DS all have different 7pin transceiver wirings (and, some have additional metal shields).



