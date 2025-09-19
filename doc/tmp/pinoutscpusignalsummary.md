# Pinouts - CPU - Signal Summary


### Advance Gameboy CPU Signal Summary
Cart Bus: D0-D7, A0-A15, /CS, /RD, /WR (different usage in GBA/DMG mode)
WRAM Bus: WA0-WA16, WD0-WD15, /WLB, /WUB, /WWE, /WOE (used in GBA mode only)
LCD Bus : LDR1-5, LDG1-5, LDB1-5, DCK, LP, PS, SPL, CLS, SPS, MOD, REVC
Joypad: TP0-3 (Buttons), TP4-7 (Directions), TP8-9 (L/R-Buttons, via R43/R44)
Serial Link: SC, SD (aka P14?), SI, SO - Audio: SO1-2, Vin
Other: CK1-2, PHI, IN35, VCNT5, /FIQ (via CL1 to VDD3), /RESET (IN), /RES (OUT)
Supply: VDD35, VDD3, VDD2, GND (some are probably undoc inputs)
GBA SP: Same as GBA, plus VDD1, plus duplicated supply pins, plus pin 152.



