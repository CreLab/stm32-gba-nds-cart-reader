# DSi I2C Bus


### I2C Bus
- [DSi I2C I/O Ports](./dsii2cioports.md)
- [DSi I2C Signals](./dsii2csignals.md)

### Device 4Ah (BPTWL chip) (LED/Volume/Powerbutton/Reset)
- [DSi I2C Device 4Ah (BPTWL chip)](./dsii2cdevice4ahbptwlchip.md)

### Device 78h/7Ah (Aptina MT9V113 Cameras)
- [DSi Aptina Camera Initialization](./dsiaptinacamerainitialization.md)
Directly addressed I2C Registers (16bit index, 16bit data):
- [DSi Aptina Camera Registers: SYSCTL (0000h-0051h)](./dsiaptinacameraregisterssysctl0000h0051h.md)
- [DSi Aptina Camera Registers: RX_SS, FUSE, XDMA (0100h-099Fh)](./dsiaptinacameraregistersrxssfusexdma0100h099fh.md)
- [DSi Aptina Camera Registers: CORE (3000h-31FFh, 38xxh)](./dsiaptinacameraregisterscore3000h31ffh38xxh.md)
- [DSi Aptina Camera Registers: SOC1 (3210h-33FDh)](./dsiaptinacameraregisterssoc13210h33fdh.md)
- [DSi Aptina Camera Registers: SOC2 (3400h-3729h)](./dsiaptinacameraregisterssoc23400h3729h.md)
Indirectly addressed MCU Variables (via above \"XDMA\" commands):
- [DSi Aptina Camera Variables: RAM/SFR/MON (GPIO/Monitor) (MCU:0000h-20xxh)](./dsiaptinacameravariablesramsfrmongpiomonitormcu0000h20xxh.md)
- [DSi Aptina Camera Variables: SEQ (Sequencer) (MCU:21xxh)](./dsiaptinacameravariablesseqsequencermcu21xxh.md)
- [DSi Aptina Camera Variables: AE (Auto Exposure) (MCU:22xxh)](./dsiaptinacameravariablesaeautoexposuremcu22xxh.md)
- [DSi Aptina Camera Variables: AWB (Auto White Balance) (MCU:23xxh)](./dsiaptinacameravariablesawbautowhitebalancemcu23xxh.md)
- [DSi Aptina Camera Variables: FD (Anti-Flicker) (MCU:24xxh)](./dsiaptinacameravariablesfdantiflickermcu24xxh.md)
- [DSi Aptina Camera Variables: MODE (Mode/Context) (MCU:27xxh)](./dsiaptinacameravariablesmodemodecontextmcu27xxh.md)
- [DSi Aptina Camera Variables: HG (Histogram) (MCU:2Bxxh)](./dsiaptinacameravariableshghistogrammcu2bxxh.md)
I2C Bus Caution: The Camera I2C access requires the \"16.76MHz Camera External Clock\" enabled in Port 4004004h.Bit8 on ARM9 Side. For accessing registers other than SYSCTL/CORE, one must also clear the Standby flag in SYSCTL\[0018h\].

### Device A0h/E0h (Unknown, maybe cameras from other manufacturer)
- [DSi Alternate Cameras from Unknown Manufacturer](./dsialternatecamerasfromunknownmanufacturer.md)

### Camera Data Transfers
Camera configuration is done on ARM7 side via serial I2C bus. However, the actual Camera Data transfers are done on ARM9 side through 8bit parallel bus:
- [DSi Cameras](./dsicameras.md)

### Broken Cameras (defunct device 78h/7Ah/A0h/E0h)
Consoles should contain two Aptina cameras, or two Unknown cameras. The Unlaunch installer is throwing a warning when detecting Unknown cameras, so far nobody has reported that case, so Unknown cameras seem to be very rare (if they were ever used at all). However, two people reported that warning showing FFh\'s in the ID bytes for most or all cameras (caused by a broken camera with only one working camera, or broken camera connector with no working cameras at all).
Bottom line is that broken cameras are more common than unknown cameras, and games with optional/extra camera features should support that situation: ie. disable the feature in case of broken camera(s) instead of becoming unplayable.

### Device 90h (Whatever)
Trying to read I2C for this device just returns FFh? Maybe exists in debug version only. The firmware contains a few functions for accessing this register.

```
+-----------------------------------------------------------------------+
|       Register  Width   Description                                   |
|       02h       1       Used for DSi IRQ6 IF flags                    |
|                           uh, IF.Bit6 would be Timer3overflow ?       |
|                           or, IF2.Bit6 would be PowerButton ?         |
|       04h       1       Unknown (bit0 toggled)                        |
+-----------------------------------------------------------------------+
```

Unknown purpose.

### Device 40h (Whatever) (and New3DS QTM)
Trying to read I2C for this device just returns FFh? Maybe exists in debug version only. The firmware doesn\'t use this register (it does only contain the device number in the device table).
Caution: New3DS does use device number 40h for the QTM IO Expander, this device will be visible in DSi mode (and shouldn\'t be mistaken for whatever DSi device 40h was originally used for).

### DSi I2C Devices

```
+-------------------------------------------------------------------------------+
|       Device  Delay      Description                                          |
|       7Ah     0       0  Camera0(internal)  ;Aptina MT9V113 (SelfPortrait)    |
|       78h     0       1  Camera1(external)  ;Aptina MT9V113 (External)        |
|       A0h     0       2  Camera0 config (Ext) ;\maybe for other manufacturer? 
|       E0h     0       3  Camera1 config (Self);/                              |
|       4Ah     180h    4  BPTWL Chip (LED/Volume/Powerbutton/Reset)            |
|       40h     0       5  Debug?                                               |
|       90h     0       6  Debug?                                               |
+-------------------------------------------------------------------------------+
```

Delay: required swiWaitByLoop delay

### DSi Secondary I2C Devices
There are also some internal/secondary I2C busses (not connected to the ARM CPUs).

```
+------------------------------------------------------------------------------------+
|       82h   Power Managment Device                       (connected to BPTWL chip) |
|       50h   I2C bus potentiometer (volume D/A converter) (connected to BPTWL chip) |
|       30h   I2C bus unknown write-only, DSiXL omly ?     (connected to BPUTL chip) |
|       A0h   I2C bus EEPROM                        (connected to Atheros wifi chip) |
|       -     I2C voltage translator                (between ARM CPU and BPTWL chip) |
+------------------------------------------------------------------------------------+
```




