# DS Cart Infrared/Pedometers


**NDS/DSi Cartridges with IR port**
- [DS Cart Infrared Cartridge SPICommands](./dscartinfraredcartridgespicommands.md)
- [DS Cart Infrared Cartridge MemoryMap](./dscartinfraredcartridgememorymap.md)

**Activity Meter**
Pedometer with two-color LED and button. The step counter results can be
transferred to NDS via IrDA.
- [DS Cart Infrared Activity Meter IRCommands](./dscartinfraredactivitymeterircommands.md)
- [DS Cart Infrared Activity Meter MemoryMap](./dscartinfraredactivitymetermemorymap.md)

**P-Walker**
Pedometer with LCD, speaker, and three buttons. There is no intended way
to run custom program code (though it can be tweaked to do so via CPU
Memory Write command).
- [DS Cart Infrared P-Walker IRCommands](./dscartinfraredpwalkerircommands.md)
- [DS Cart Infrared P-Walker Memory Map](./dscartinfraredpwalkermemorymap.md)
- [DS Cart Infrared P-Walker Ports LCDController](./dscartinfraredpwalkerportslcdcontroller.md)
- [DS Cart Infrared P-Walker Ports AccelerometerBMA150](./dscartinfraredpwalkerportsaccelerometerbma150.md)
The purpose is more or less unknown: Apart from communicating with the
NDS, the IrDA can be also used communicate with other P-Walkers (maybe
for trading/fighting?). The GUI supports Teams, Routes, Events, Items
(maybe for some built-in interactice game engine?).

**Component Lists**
- [DS Cart Infrared Component Lists](./dscartinfraredcomponentlists.md)

**H8/38602 CPU series with H8/300H instruction set**
The NDS cartridges and Activity Meter and P-Walker contain Renesas
H8/3860X CPUs with H8/300H instruction set and on-chip firmware. In the
cartridge it\'s merely used for forwading IR messages via SPI bus, i
the pedometer it\'s handling step sensors, step counting, EEPRO
logging, buttons, LED/LCD, RTC/time, IR messages, etc.
- [H8/386 SFRs](./h8386sfrs.md)
- [H8/386 Exception Vectors](./h8386exceptionvectors.md)
- [H8/300H Operands](./h8300hoperands.md)
- [H8/300H Opcodes](./h8300hopcodes.md)

**References**

```
+-----------------------------------------------------------------------+
|                                                                       |
|     H8/300H Series Programming Manual (Hitachi, 257 pages)  ;-Opcodes |
|       H8/38602R Group Hardware Manual (Renesas, 554 pages)    ;-SFR's |
|       Th                                                              |
| e addition of H8/38606 Group (Renesas, 6 pages)       ;-FLASH/ROM/RAM |
+-----------------------------------------------------------------------+
```

For P-Walker:

```
+-----------------------------------------------------------------------+
|       BMA                                                             |
| 150 Triaxial digital acceleration sensor Data sheet (Bosch, 56 pages) |
|                                                                       |
|  SSD1850 Advance Information (Solomon System, 56 pages)  ;-LCD driver |
|       http:/                                                          |
| /dmitry.gr/?r=05.Projects&proj=28.%20pokewalker   ;-Disassembly/Story |
|                                                                       |
|  http://forums.nesdev.org/viewtopic.php?f=23&t=21140#p265388  ;-Forum |
+-----------------------------------------------------------------------+
```




