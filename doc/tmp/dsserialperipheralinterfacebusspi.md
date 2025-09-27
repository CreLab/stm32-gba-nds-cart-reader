# DS Serial Peripheral Interface Bus (SPI)


### Serial Peripheral Interface Bus
SPI Bus is a 4-wire (Data In, Data Out, Clock, and Chipselect) serial bus.
The NDS supports the following SPI devices (each with its own chipselect).
- [DS Firmware Serial Flash Memory](./dsfirmwareserialflashmemory.md)
- [DS Touch Screen Controller (TSC)](./dstouchscreencontrollertsc.md)
- [DS Power Management Device](./dspowermanagementdevice.md)

### 40001C0h - NDS7 - SPICNT - SPI Bus Control/Status Register

```
+-------------------------------------------------------------------------------------+
|       0-1   Baudrate (0=4MHz/Firmware, 1=2MHz/Touchscr, 2=1MHz/Powerman., 3=512KHz) |
|       2     DSi: Baudrate MSB   (4=8MHz, 5..7=None/0Hz) (when SCFG_EXT7.bit9=1)     |
|       2     NDS: Not used       (Zero)                                              |
|       3-6   Not used            (Zero)                                              |
|       7     Busy Flag           (0=Ready, 1=Busy) (presumably Read-only)            |
|       8-9   Device Select       (0=Powerman., 1=Firmware, 2=Touchscr, 3=Reserved)   |
|       10    Transfer Size       (0=8bit/Normal, 1=16bit/Bugged)                     |
|       11    Chipselect Hold     (0=Deselect after transfer, 1=Keep selected)        |
|       12-13 Not used            (Zero)                                              |
|       14    Interrupt Request   (0=Disable, 1=Enable)                               |
|       15    SPI Bus Enable      (0=Disable, 1=Enable)                               |
+-------------------------------------------------------------------------------------+
```

The \"Hold\" flag should be cleared BEFORE transferring the LAST data unit, the chipselect will be then automatically cleared after the transfer, the program should issue a WaitByLoop(3) manually AFTER the LAST transfer.

### 40001C2h - NDS7 - SPIDATA - SPI Bus Data/Strobe Register (R/W)
The SPI transfer is started on writing to this register, so one must \<write\> a dummy value (should be zero) even when intending to \<read\> from SPI bus.

```
+-----------------------------------------------------------------------+
|       0-7   Data                                                      |
|       8-15  Not used (always zero, even in bugged-16bit mode)         |
+-----------------------------------------------------------------------+
```

During transfer, the Busy flag in SPICNT is set, and the written SPIDATA value is transferred to the device (via output line), simultaneously data is received (via input line). Upon transfer completion, the Busy flag goes off (with optional IRQ), and the received value can be then read from SPIDATA, if desired.

### Notes/Glitches
SPICNT Bits 12,13 appear to be unused (always zero), although the BIOS (attempts to) set Bit13=1, and Bit12=Bit11 when accessing the firmware.
The SPIDATA register is restricted to 8bit, so that only each 2nd byte will appear in SPIDATA when attempting to use the bugged-16bit mode.

### Cartridge Backup Auxiliar SPI Bus
The NDS Cartridge Slot uses a separate SPI bus (with other I/O Ports), see
- [DS Cartridge Backup](./dscartridgebackup.md)



