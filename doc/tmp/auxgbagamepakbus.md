# AUX GBA Game Pak Bus


### Game Pak Bus - 32pin cartridge slot
The cartridge bus may be used for both CGB and GBA game paks. In GBA mode, it is used as follows:

```
+-------------------------------------------------------------------------------------+
|      Pin    Name    Dir  Expl.                                                      |
|      1      VDD     O    Power Supply 3.3V DC                                       |
|      2      PHI     O    System Clock (selectable none, 4.19MHz, 8.38MHz, 16.78MHz) |
|      3      /WR     O    Write Select    ;\latched address to be incremented on     
|      4      /RD     O    Read Select     ;/rising edges of /RD or /WR signals       |
|      5      /CS     O    ROM Chip Select ;-A0..A15 to be latched on falling edge    |
|      6-21   AD0-15  I/O  lower 16bit Address    and/or  16bit ROM-data (see below)  |
|      22-29  A16-23  I/O  upper 8bit ROM-Address   or    8bit SRAM-data (see below)  |
|      30     /CS2    O    SRAM Chip Select                                           |
|      31     /REQ    I    Interrupt request (/IREQ) or DMA request (/DREQ)           |
|      32     GND     O    Ground 0V                                                  |
+-------------------------------------------------------------------------------------+
```

When accessing game pak SRAM, a 16bit address is output through AD0-AD15, then 8bit of data are transferred through A16-A23.
When accessing game pak ROM, a 24bit address is output through AD0-AD15 and A16-A23, then 16bit of data are transferred through AD0-AD15.
The 24bit address is formed from the actual 25bit memory address (byte-steps), divided by two (halfword-steps).
Pin Pitch is 1.5mm.

### 8bit-Gamepak-Switch (GBA, GBA SP only) (not DS)
A small switch is located inside of the cartridge slot, the switch is pushed down when an 8bit cartridge is inserted, it is released when a GBA cartridge is inserted (or if no cartridge is inserted).
The switch mechanically controls whether VDD3 or VDD5 are output at VDD35; ie. in GBA mode 3V power supply/signals are used for the cartridge slot and link port, while in 8bit mode 5V are used.
The switch additionally drags IN35 to 3V when an 8bit cart is inserted, the current state of IN35 can be determined in GBA mode via Port 4000204h (WAITCNT), if the switch is pushed, then CGB mode can be activated via Port 4000000h (DISPCNT.3), this bit can be set ONLY by opcodes in BIOS region (eg. via CpuSet SWI function).
In 8bit mode, the cartridge bus works much like for GBA SRAM, however, the 8bit /CS signal is expected at Pin 5, while GBA SRAM /CS2 at Pin 30 is interpreted as /RESET signal by the 8bit MBC chip (if any). In practice, this appears to result in 00h being received as data when attempting to read-out 8bit cartridges from inside of GBA mode.



