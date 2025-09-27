# DS Cart Slider with Rumble


Add-on device for the japanese title Magukiddo. The optical sensor is attached underneath of the console (connected to the GBA slot).
The sensor is an Agilent ADNS-2030 Low Power Optical Mouse Sensor (16pin DIP chip with built-in optical sensor, and external LED light source) with two-wire serial bus (CLK and DTA).

### ADNS-2030 Registers (write 1 byte index, then read/write 1 byte data)
Index (Bit7=Direction; 0=Read, 1=Write):

```
+--------------------------------------------------------------------------------+
|       00h Product_ID (R) (03h)                                                 |
|       01h Revision_ID (R) (10h=Rev. 1.0) (20h=Used in DS-option-pak)           |
|       02h Motion/Status Flags (R)                                              |
|       03h Delta_X (R) (signed 8bit) (automatically reset to 00h after reading) |
|       04h Delta_Y (R) (signed 8bit) (automatically reset to 00h after reading) |
|       05h SQUAL (R) (surface quality) (unsigned 8bit)                          |
|       06h Average_Pixel (R) (unsigned 6bit, upper 2bit unused)                 |
|       07h Maximum_Pixel (R) (unsigned 6bit, upper 2bit unused)                 |
|       08h Reserved                                                             |
|       09h Reserved                                                             |
|       0Ah Configuration_bits (R/W)                                             |
|       0Bh Reserved                                                             |
|       0Ch Data_Out_Lower (R)                                                   |
|       0Dh Data_Out_Upper (R)                                                   |
|       0Eh Shutter_Lower (R)                                                    |
|       0Fh Shutter_Upper (R)                                                    |
|       10h Frame_Period_Lower (R/W)                                             |
|       11h Frame_Period_Upper (R/W)                                             |
+--------------------------------------------------------------------------------+
```

Motion/Status Flags:

```
+-----------------------------------------------------------------------+
|       7 Motion since last report or PD (0=None, 1=Motion occurred)    |
|       6 Reserved                                                      |
|       5 LED Fault detected (0=No fault,  1=Fault detected)            |
|       4 Delta Y Overflow (0=No overflow, 1=Overflow occured)          |
|       3 Delta X Overflow (0=No overflow, 1=Overflow occured)          |
|       2 Reserved                                                      |
|       1 Reserved                                                      |
|       0 Resolution in counts per inch (0=400, 1=800)                  |
+-----------------------------------------------------------------------+
```

Configuration_bits:

```
+--------------------------------------------------------------------------------+
|       7 Reset Power up defaults (W) (0=No, 1=Reset)                            |
|       6 LED Shutter Mode (0=LED always on, 1=LED only on when shutter is open) |
|       5 Self Test (W) (0=No, 1=Perform all self tests)                         |
|       4 Resolution in counts per inch (0=400, 1=800)                           |
|       3 Dump 16x16 Pixel bitmap (0=No, 1=Dump via Data_Out ports)              |
|       2 Reserved                                                               |
|       1 Reserved                                                               |
|       0 Sleep Mode (0=Normal/Sleep after 1 second, 1=Always awake)             |
|                               _______                                          |
|                              |74273  |                                         |
|       /WR -----------------> |CLK    |                       _____             |
|       AD1/SIO CLK ---------> |D1   Q1|--------------> CLK   |74125|            |
|       AD2 power control ---> |D2   Q2|--->     ____         |     |            |
|       AD3/SIO DIR ---------> |D3   Q3|------o-|7400\________|/EN  |            
|       AD8 rumble on/off ---> |D?   Q?|--->  '-|____/        |     |            |
|       AD0/SIO DTA ----o----> |D5   Q5|----------------------|A   Y|--o--DTA    |
|                       |      |_______|                      |- - -|  |         |
|               ____    '-------------------------------------|Y   A|--'         |
|       /RD ---|7400\______ ____                              |     |            
|       /RD ---|____/      |7400\_____________________________|/EN  |            
|       A19 _______________|____/                             |_____|            |
+--------------------------------------------------------------------------------+
```


7400 Quad NAND Gate, 74273 8bit Latch

AD0 Optical Sensor Serial Data (0=Low, 1=High)
AD1 Optical Sensor Serial Clock (0=Low, 1=High)
AD2 Optical Sensor Power (0=Off, 1=On)
AD3 Optical Sensor Serial Direction (0=Read, 1=Write)
AD8 Rumble Motor (0=Off, 1=On)

Thanks: Daniel Palmer



