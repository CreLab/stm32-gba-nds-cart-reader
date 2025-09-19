# AUX DS Game Card Slot



```
+------------------------------------------------------------------------------+
|       Pin    Dir  Name  Connection in cartridge                              |
|       1   >  -    GND   (ROM all unused Pins, EEPROM Pin 4 = VSS)            |
|       2      Out  CLK   (4MB/s, ROM Pin 5, EEPROM Pin 6 = CLK)               |
|       3   N  -    ?     (ROM Pin 17) (Seems to be not connected in console)  |
|       4   i  Out  /CS1  (ROM Pin 44) ROM Chipselect                          |
|       5   n  Out  /RES  (ROM Pin 42) Reset, switches ROM to unencrypted mode |
|       6   t  Out  /CS2  (EEPROM Pin 1) EEPROM Chipselect                     |
|       7   e  In   IRQ   (GND)                                                |
|       8   n  -    3.3V  (ROM Pins 2, 23, EEPROM Pins 3,7,8 = /W,/HOLD,VCC)   |
|       9   d  I/O  D0    (ROM Pin 18)                                         |
|       10  o  I/O  D1    (ROM Pin 19)                                         |
|       11     I/O  D2    (ROM Pin 20)                                         |
|       12  C  I/O  D3    (ROM Pin 21)                                         |
|       13  0  I/O  D4    (ROM Pin 24)                                         |
|       14  1  I/O  D5    (ROM Pin 25)                                         |
|       15  -  I/O  D6    (ROM Pin 26, EEPROM Pin 2 = Q = Data EEPROM to NDS)  |
|       16  0  I/O  D7    (ROM Pin 27, EEPROM Pin 5 = D = Data NDS to EEPROM)  |
|       17  1  -    GND   (ROM all unused Pins, EEPROM Pin 4 = VSS)            |
+------------------------------------------------------------------------------+
```


Chipselect High-to-Low transitions are invoking commands, which are transmitted through data lines during next following eight CLK pulses, after the command transmission, further CLK pulses are used to transfer data, the data transfer ends at chipselect Low-to-High transition.
Data should be stable during CLK=LOW period throughout CLK rising edge.
Note: Supply Pins (1,8,17) are slightly longer than other pins. Pin pitch is 1.5mm.

The DS does also have a 32pin cartridge slot, that slot is used to run GBA carts in GBA mode, it can be also used as expansion port in DS mode.



