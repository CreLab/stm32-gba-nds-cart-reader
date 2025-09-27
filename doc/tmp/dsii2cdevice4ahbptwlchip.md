# DSi I2C Device 4Ah (BPTWL chip)


I2C Bus Caution: The BPTWL chip requires swiWaitByLoop(180h) after each I2C byte transfer (if the Version/Speed byte at BPTWL\[00h\] indicates \"Fast\", then the delay can be reduced to 90h instead of 180h).
And, SPI bus Powerman chip does somehow interact with I2C BPTWL chip; there must be a similar delay between Powerman writes and BPTWL writes.

### BPTWL Chip (LED/Volume/Powerbutton/Reset) (Device 4Ah)

```
+-------------------------------------------------------------------------------------+
|       00h     R   Version/Speed (usually 33h) (00h..20h=Slow, 21h..FFh=Fast)        |
|       01h     R   ?  Unknown, Powerman Status 1 (00h) ;some hw/sw type/version?     |
|       02h     R   ?  Unknown, Powerman Status 2 (50h) ;30h=AlternateCamLedHardware? |
|       03h-0Fh -   Reserved (5Ah-filled)                                             |
|       10h     R   Power Button Status (bit0=WasWhat?, bit1=IsDown, bit3=WasDown?)   |
|                     (bit0/3 are cleared after reading)                              |
|       11h     R/W System Reset (00h=No, 01h=Force Reset, 02h=Prevent Reset?)        |
|       12h     R/W Power Button Tapping (00h=Auto-Reset, 01h=IRQ) (bit1=WL_RXPE??)   |
|                     bit0: Enable IRQs (for Power/Vol+/- button, battery low)        |
|                     bit1: battery boundaries (and 0=disable battery low IRQs)       |
|                     bit5: initially set (while bptwl chip is booting up?)           |
|                     bit7: Linear volume button mode                                 |
|       13h-1Fh -   Reserved (5Ah-filled)                                             |
|       20h     R   Battery State (bit0..3=Battery Level, bit7=Charge)                |
|               W   On 3DS in DSi mode: Write 8=Shutdown, 4=Return to 3DS mode ?      |
|       21h     R/W Powerman Sleep?, NDS Cartridge related? (07h=normal)              |
|       22h-2Fh -   Reserved (5Ah-filled)                                             |
|       30h     R/W Wifi LED (0/2=Off, 1=On, 3=BlinkOnTraffic) and bit4=SDIO enable   |
|       31h     R/W Camera LED (00h=Off, 01h=On, 02h=Blink)                           |
|       32h-3Fh -   Reserved (5Ah-filled)                                             |
|       40h     R/W Volume Level (00h..1Fh)             ;\nonvolatile!                
|       41h     R/W Backlight Level (00h..04h)          ;/                            |
|       42h-4Fh -   Reserved (5Ah-filled)                                             |
|       50h     R/W     Unknown Value   (DSi-XL only) (output to I2C device 30h)      |
|       51h     R/W     Unknown Trigger (DSi-XL only) (cleared when processed)        |
|       50h-5Fh -   Reserved (5Ah-filled) (except 50h-51h on DSi XL)                  |
|       60h     R/W Battery Calibration Mode (bit0=1=Calibrate, Stop I2C, Purple LED) |
|       61h     R   Battery Calibration Flag (01h=Calibrated, E0h/E8h=NotCalibrated)  |
|       62h     R   Battery Calibration Data (xxh=BatteryBias, 50h=NotCalibrated)     |
|       63h     R/W Force Power LED (0=Automatic, 1=Red, 2=Blue, 3=Purple)            |
|       64h-6Fh -   Reserved (5Ah-filled)                                             |
|       70h     R/W Bootflag (00h=Coldboot, 01h=Warmboot/SkipHealthSafety)            |
|       71h     R/W ?  Unknown (00h)          ;\more general-purpose bootflags?       
|       72h-76h R/W ?  Unknown (00h-filled)   ;/                                      |
|       77h     ?/W Firmware Updater (write 4Ah, plus HEX file with delays) (danger!) |
|       78h-7Fh -   Reserved (5Ah-filled)                                             |
|       80h     R/W Power Button Tap delay   (10h)  ;\can affect/disable              
|       81h     R/W Power Button Hold delay  (64h)  ;/Power Button Tapping            |
|       82h-FFh -   Reserved (5Ah-filled)                                             |
+-------------------------------------------------------------------------------------+
```

The R/W values can be set to 00h..FFh (except Index 40h/41h are quickly cropped to max 1Fh/04h, and Index 70h/71h are (after some time) cropped to 01h/02h).
Above should probably also include:

```
+-----------------------------------------------------------------------------+
|       Forced volume (for alerts) (ie. alternately to current "user volume") |
+-----------------------------------------------------------------------------+
```


### BPTWL Emulation on 3DS
The 3DS MCU emulates the BPTWL chip for DSi mode (and the emulated registers can be also accessed in 3DS mode). The emulation supports only a few of the original BPTWL registers & bits though:

```
+-----------------------------------------------------------------------------+
|       00h     R   Version/Speed (35h on New3DS)                             |
|       10h     R   Power Button Status (only 2 bits?: bit3=WasDown?, bit6=?) |
|       11h     R/W Reset (01h=Reset, other=ignored) (read: always 00h)       |
|       12h     R/W Power Button Tapping (bit0,1,7=?)                         |
|       20h     R   Battery State                                             |
|       31h     R/W Camera LED (bit0,1)                                       |
|       40h     R/W Volume Level                                              |
|       70h     R/W Bootflag                                                  |
|       Other   -   Unused (FFh)                                              |
+-----------------------------------------------------------------------------+
```


### DSi Power Button
Logically, the Power Button has two functions:

```
+---------------------------------------------------------------------------------+
|       Short tap --> reset (warmboot, go to DSi menu, without health and safety) |
|       Hold 1 second --> power-off                                               |
+---------------------------------------------------------------------------------+
```

Technically, the button can have three functions:

```
+----------------------------------------------------------------------------------+
|       Auto-Reset (used for NDS games)                                            |
|       IRQ (supposed to be used with Manual-Reset) (used for DSi games)           |
|       Forced Power-off (for games which fail to handle the IRQ within 5 seconds) |
+----------------------------------------------------------------------------------+
```

DSi games should handle the IRQ as follows: First, do some clean up (like finishing writes to SD/MMC storage; to avoid FAT corruption). Then, issue a Reset manually (via I2C/BPTWL registers \[70h\]=01h/Warmboot, \[11h\]=01h/Reset).
Power-Off can be implemented via SPI/Power Managment Device, however, games only need to implement Manual-Reset or Auto-Reset, but don\'t need to implement Power-Off (the firmware will do that automatically if the button is held down for 1 second after issuing the Reset).
Ideally, emulators should also reproduce the power button (when resetting or closing the emulator): Signalize power-button and keep the emulation running until the game responds by Reset (or until five second timeout). That will allow the game to finish writes to emulated SD/MMC storage.

### DSi Autostart on Warmboot (20h-byte area) (also requires BPTWL\[70h\]=01h)
The DSi can be commanded to load a different title (eg. System Settings), instead of showing the Boot Menu after warmboot.
- [DSi Autoload on Warmboot](./dsiautoloadonwarmboot.md)

### Older blurb\...

```
+-----------------------------------------------------------------------------------+
|       0x10    1       Power flags. When bit0 is set, arm7 does a system reset.    |
|                         When bit1 or bit3 are set, arm7 does a shutdown. Bits 0-2 |
|                         are used for DSi IRQ6 IF flags (uh, rather IF2 maybe?).   |
|       0x20    1       Battery flags. When zero the battery is at critical level,  |
|                         arm7 does a shutdown. Bit7 is set when the battery is     |
|                         charging. Battery levels in the low 4-bits: battery icon  |
|                         bars full 0xF, 3 bars 0xB, 2 bars 0x7, one solid red bar  |
|                         0x3, and one blinking red bar 0x1. When plugging in or    |
|                         removing recharge cord, this value increases/decreases    |
|                         between the real battery level and 0xF, thus the battery  |
|                         level while bit7 is set is useless.                       |
+-----------------------------------------------------------------------------------+
```


### BPTWL/BPUTL Chip Names

```
+-----------------------------------------------------------------------------------+
|       DSi:      Renesas Electronics "BPTWL, KG07K"           ;reg[00h]=33h        |
|       DSiXL:    Renesas Electronics "BP UTL-1, KG08"         ;reg[00h]=BBh or B7h |
|       3DS:      Renesas Electronics "UC CTR, 041KM73, KG10"  ;reg[00h]=?          |
|       New3DSXL: Renesas Electronics "UC KTR, 423KM01, 'TK14" ;reg[00h]=35h        |
+-----------------------------------------------------------------------------------+
```


### Inner workings
The DSi\'s BPTWL chip contains a 78K/0 microprocessor. The BPTWL firmware has aparently leaked in a \"TWL_MCU_33-MP_95811supp.hex\" file. There is also a \"UTL_MCU_BA.hex\" file (for DSi XL?).
- [78K/0 Opcode List](./78k0opcodelist.md)
- [78K/0 Opcode Map](./78k0opcodemap.md)
- [78K/0 Memory Map and SFRs](./78k0memorymapandsfrs.md)
Programming via external serial cable is about same as on 3DS:
- [3DS I2C MCU - RL78 Flash Programming via UART](./3dsi2cmcurl78flashprogrammingviauart.md)
The 3DS\' MCU emulates the BPTWL functions by using a 78K0R/ microprocessor (with similar asm syntax, but completely different opcode numbering, with more 16bit ALU opcodes, new conditional-skip opcodes, and 20bit addressing).



