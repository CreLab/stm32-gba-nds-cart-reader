# DS Cart Unknown Extras


### DS Cartridges with built-in MicroSD Card Slot
The DS Vision cartridge contains a built-in microSD card slot. Users can download videos from internet (against a fee), store the videos on microSD cards, and then view them on the NDS via DS Vision cartridge.
Unknown how the microSD is accessed; via parallel \'ROM\' bus and/or via serial SPI bus; by which commands? Also unknown if the thing contains built-in video decoder hardware, or if videos are decoded on ARM cpus.

### DS Cartridge with Bluetooth Keyboard (Typing Adventure)
Mostly unknown. The components in the cartridge are:

```
+-----------------------------------------------------------------------+
|       typical Macronix ROM                                            |
|       STMicroelectronics M25PE10 SPI FLASH memory, presumably 128K    |
|       Broadcom BCM2070 Bluetooth controller                           |
|       26MHz crystal oscillator                                        |
+-----------------------------------------------------------------------+
```

the FLASH chip isn\'t connected directly to the cart-SPI bus, instead it\'s prolly accessed through the Bluetooth controller.

### NTR-UNSJ - Japanese TV Tuner
Some huge cartridge with digital TV receiver.
Unknown if the \"U\" in the gamecode means that it contains NAND, too.
DSi Launcher sets BPTWL\[21h\].bit0=0 for this cartridge (unknown what for).

### NTR/TWL-Uxxx gamecodes (for carts with uncommon hardware)

```
+-----------------------------------------------------------------------+
|       NTR-UNSJ      Japanese TV Tuner, with TV receiver               |
|       NTR-UBRP      Nintendo DS Brower, with RAM cart in GBA slot     |
|       NTR-UAMA      DS Vision Starter Kit, with microSD               |
|       NTR-UEIJ      Starry Sky Navigation, with azimuth               |
|       NTR/TWL-Uxxx  NAND carts (see NAND chapter)                     |
+-----------------------------------------------------------------------+
```




