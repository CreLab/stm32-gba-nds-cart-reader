# AUX DSi SD/MMC Pin-Outs


### SD/MMC Transfer Modes

```
+-------------------------------------------------------------------------+
|       Transfer Modes        SPI-Mode    1-bit-Bus  4-bit-Bus   SDIO     |
|       MMC Cards             Optional    Yes        MMCplus     No       |
|       SD Cards              Yes         Yes        Optional??  Optional |
+-------------------------------------------------------------------------+
```

Note: SDIO is an extension to the SD protocol, allowing to access other non-memory-card hardware (such like cameras or network adaptors) via SD connectors.
Note: Original MMC cards don\'t support 4-bit bus, but there are revisions like MMCplus and MMCmobile (with extra pin rows) which do support 4-bit and 8bit bus.

### SD/MMC Pin-Outs

```
+------------------------------------------------------------------------------------+
|       MMC  MMCplus SD  miniSD microSD SPI-Mode    1-bit-Bus   4-bit/8bit-Bus       |
|       1    1       1   1      2       /CS         CardDetect  Data3                |
|       2    2       2   2      3       DataIn      CMD/REPLY   CMD/REPLY            |
|       3    3       3   3      --      GND         GND         GND                  |
|       4    4       4   4      4       VDD         VDD         VDD                  |
|       5    5       5   5      5       CLK         CLK         CLK                  |
|       6    6       6   6      6       GND         GND         GND                  |
|       7    7       7   7      7       DataOut     Data        Data0                |
|       --   8       8   8      8       /IRQ (SDIO) /IRQ (SDIO) Data1 or /IRQ (SDIO) |
|       --   9       9   9      1       NC          NC          Data2                |
|       --   10      --  --     --      NC          NC          Data4  ;\            
|       --   11      --  --     --      NC          NC          Data5  ; MMCplus     |
|       --   12      --  --     --      NC          NC          Data6  ; 8bit        |
|       --   13      --  --     --      NC          NC          Data7  ;/            |
|       --   --      --  10     --      Reserved    Reserved    Reserved             |
|       --   --      --  11     --      Reserved    Reserved    Reserved             |
+------------------------------------------------------------------------------------+
```

Moreover, the card sockets (not the cards themselves) are usually containing a Card Detect switch, and, for SD card sockets, also a write protect switch:

```
+-----------------------------------------------------------------------------------+
|       --   --      CD  CD     CD      Card Detect (senses if card is inserted)    |
|       --   ---     WP  --     --      Write Protect (senses position of LOCK tab) |
+-----------------------------------------------------------------------------------+
```

Note that the LOCK tab on SD cards is just a small piece of plastic without any electronics attached to it, the actual switch/sensor is located in the SD card socket (ie. the LOCK works much like the write-protect tabs on audio tapes, video tapes, and floppy discs).
Card detect can be an actual switch (however, some sockets are simply having dual contacts for Pin 3 (GND), one being GND, and the other becoming GNDed when a cartridge is inserted).

### SD/MMC Card Shapes

```
+-----------------------------------------------------------------------------+
|          ______________________________                                     |
|         /    __ __ __ __ __ __ __      |                                    |
|        /    |  |  |  |  |  |  |  |     |                                    |
|       |     | 1| 2| 3| 4| 5| 6| 7|     |                                    |
|       | MMC |__|__|__|__|__|__|__|     |                                    |
|       |    ______________________________                                   |
|       |   /    __ __ __ __ __ __ __ _    |                                  |
|       |  /  __|  |  |  |  |  |  |  | |   |                                  |
|       | |  |  | 1| 2| 3| 4| 5| 6| 7|8|   | MMCplus:                         |
|       | |  | 9|__|__|__|__|__|__|__| |   | pinout is same as 9pin SD cards, |
|       | |  |_ |_ __ __       __ __ | |   | with extra DAT4-7 on pin10-13    |
|       | |    |  | 1| 1|     | 1| 1|  |   |                                  |
|       | |MMC | 9| 0| 1|     | 2| 3| 8|   |                                  |
|       | |plus|__|__|__|     |__|__|__|   |                                  |
|       | |    ______________________________                                 |
|       | |   /    __ __ __ __ __ __ __ _    |                                |
|       | |  /  __|  |  |  |  |  |  |  | |   |                                |
|       | | |  |  | 1| 2| 3| 4| 5| 6| 7|8|   |                                |
|       | | |  | 9|__|__|__|__|__|__|__|_|   |                                |
|       | | '. |__| SD                      .'      SD Write Protect Tab      |
|       | |  |  _________________________   |   <-- Unlock position           |
|       | | .' |  _ _ _ _ _ _ _ _ _ _ _  |  |#  <-- LOCK position             |
|       | | |  | | | | | |1|1| | | | | | |  '.                                |
|       | | |  | |9|1|2|3|0|1|4|5|6|7|8| |   |                                |
|       |_| |  | |_|_|_|_|_|_|_|_|_|_|_| |   |                                |
|         | |  |   miniSD                 \  |                                
|         | |  |     _________________     | |                                |
|         | |  |    | _ _ _ _ _ _ _ _ |    | |                                |
|         | |  |    || | | | | | | | ||    | |                                |
|         |_|  |    ||1|2|3|4|5|6|7|8||    | |                                |
|           |  |    ||_|_|_|_|_|_|_|_||    | |                                |
|           |  |   /                  |    | |                                |
|           |  |  |_  microSD         |    | |                                |
|           |  |    |                 |    | |                                |
|           |  |   /                  |    | |                                |
|           |  |  |                   |    | |                                |
|           |  |  |                   |    | |                                |
|           |  |_ |                   | ___| |                                |
|           |____ |___________________| _____|                                |
+-----------------------------------------------------------------------------+
```


### SD/MMC Signals for on-board eMMC chip on DSi Mainboard \"C/TWL-CPU-01\"
Below are the required eMMC signals. Low-end hardware may get away with using Data0 as single data line (eg. small microprocessors with few I/O pins), but higher quality hardware should support 4bit data mode (eg. off-the-shelve SD card interfaces may insist on all four data lines being connected). Data3 (aka CardDetect) might be also needed even in 1bit data mode.

```
+-------------------------------------------------------------------------------------+
|                              _______ CLK (SPI: CLK)    _______ Data3 (SPI: /CS)     |
|                             |                         | ______ Data0 (SPI: DataOut) |
|                      <#>  <#>  <#>                    || _____ Data1                |
|                     EM14  R113 C130                   ||| ____ Data2                |
|             .------------------------.                ||||                          |
|             |                        |          <#>  <####> #  #                    |
|             |                        |     U5   C57   RA4  C54 C55                  |
|             |  Shielding-plate       '---.  o .------------------.                  |
|             |                            |    |o                 |                  |
|             |                            |    |                  |                  |
|             |                            |    |  Samsung     834 |                  |
|             |                            |    |  KMAPF0000M-S998 |                  |
|             |  CPU              RAM      |    |                  |                  |
|             |                            |    |                  |                  |
|             |                            |    '------------------'                  |
|             '----------------------------'     R94 R54  C50 C51                     |
|                  |                             <#> <#>  <#> <#>                     |
|                  |                               |                                  |
|                  |___ shield = GND               |___ CMD/REPLY (SPI: DataIn)       |
+-------------------------------------------------------------------------------------+
```

For other DSi mainboards, see:

```
+-----------------------------------------------------------------------+
|       http://www.dsibrew.org/wiki/Hardware                            |
+-----------------------------------------------------------------------+
```

The KMAPF0000M chip does probably NOT support SPI mode, and it does probably support only MMC protocol (not SD protocol). That, assuming that the chip does have similar capabilities as in KMCEN0000M datasheet (there\'s no KMAPF0000M datasheet online).

### SD/MMC Signals and 3DS Hardmodding
Pictures with eMMC solder pads for 3DS mainboards boards can be found at:

```
+-----------------------------------------------------------------------+
|       https://www.3dbrew.org/wiki/Hardware                            |
+-----------------------------------------------------------------------+
```

However, hardmodding is much more difficult for 3DS as than for DSi. Three 3DS-specific problems:

```
+-------------------------------------------------------------------------------------+
|       CLK resistor                                                                  |
|       The 3DS tends to hold CLK low, and there is no resistor installed between     |
|       3DS CPU and eMMC chip, so the card reader may be unable to pull CLK high.     |
|       As workaround, install a resistor in the CLK line (the mainboard has square   |
|       solder pads just for that purpose) (330..660 ohms have worked for me, I am    |
|       currently using 470 ohms; smaller resistors like 0..120 ohm won't work with   |
|       the card reader, and much larger resistors won't work with the 3DS itself).   |
|       Incompatible Card readers                                                     |
|       Newer 3DS/New3DS models seem to contain eMMC chips that are incompatible with |
|       older card readers, maybe because their firmware/driver treats the CSD        |
|       version number as unknown, despite of the eMMC chip being nothing special.    |
|       As workaround, try to use some newer card readers, or use a DSi console as    |
|       card reader (ie. write you software that can happily ignore CSD version).     |
|       Mechanical problems                                                           |
|       Most solder points are on the wrong PCB side (unlike as on DSi, you will      |
|       need to remove the 3DS mainboard). Whereas, the connector for the top screen  |
|       backlight is rated to survive max 10 mating cycles (mine died after 5-7).     |
|       Part of the problem was that I wasn't aware of the other problems mentioned   |
|       above (so I had removed the mainboard several times to check my soldering),   |
|       and, the connector is 'underneath' of the PCB, making it difficult to insert  |
|       the cable straight and smoothly, causing pins in the connector may get bent,  |
|       making it impossible to insert the ribbon cable (maybe it will help if you    |
|       take time, and don't impatiently try to push the cable into the socket).      |
+-------------------------------------------------------------------------------------+
```


### Soldering Notes
Connect CLK/CMD to the pins on right side of R113/R94 (as shown in the drawing). Connect Data3/0/1/2 to the LOWER pins of RA4 (unlike as shown in the drawing, ie. NOT to the upper pins), or alternately, connect them to the four vias below of RA4. Connect GND somewhere to shielding plate, for example.
My own setup is: A 8pin ribbon cable soldered to a spare SD-to-SDmicro adapter (used as connector for SD/MMC slots), the ribbon cable is wired to a small circuit board, which is soldered to the shielding of the DSi\'s game cartridge slot (just for mechanical stability). Next, some fragile wires are forwarded from the circuit board to the actual mainboard pins.

### Software Notes
Remove the DSi wifiboard (not absolutely required, but doing so will hang the DSi before accessing the eMMC, which ensures that the eMMC won\'t be accessed simultaneously by the DSi and PC). Switch on the DSi. Connect it to SD/MMC card reader. Under Windows, the eMMC should show up as MMC-storagedevice in Windows Explorer (alongsides with your HDD drives), due to the encryption it isn\'t possible to access the filesystem or logical partitions of the chip. However, the physical sectors can be accessed.
For example, using HxD hex editor: Click Extras, Open Disk, and select the MMC (in HxD it shows up under Physical Discs: as Removeable Disk). Click Edit, Select All, Copy. Click File, New. Then Edit, Paste. And finally File, Save As for saving an image of the whole 240MByte FLASH chip.
I\'ve tried accessing the eMMC on two PCs, one worked, the other didn\'t:

```
+--------------------------------------------------------------------------------+
|       Win98 with External Card reader: Windows didn't recognize the MMC chip   |
|       Win7  with External Card reader: Okay (recognized as "unformatted" disk) |
|       Win7  with Internal Card reader: Okay (recognized as "unformatted" disk) |
+--------------------------------------------------------------------------------+
```

For testing the Operating System/Card Reader side: Connect a normal SD card to the card reader. If HxD is showing it as both Logical Disc and Physical Disc, then you are fine. If it shows up as Logical Disc only, then your setup won\'t work for accessing the eMMC chip.



