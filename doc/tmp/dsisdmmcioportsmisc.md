# DSi SD/MMC I/O Ports: Misc


### Toshiba Chips
The DSi SDIO/MMC port addresses and status bits appear to be identical to those on Toshiba SD/MMC/SDIO controller chips.
One small difference is that the DSi can set SD_IRQ_MASK.Bit27 (which wasn\'t used on (older) Toshiba chips). The Toshiba chips seem to include additional \"CNF\" configuration registers (which seem to be missing on DSi).

```
+---------------------------------------------------------------------------------+
|       Chip             Year   Pages Features                                    |
|       Toshiba TC6371AF 2000-2002 58 SD/MMC/Smart/PCI (old/basic specs, no SDIO) |
|       Toshiba TC6380AF 2001-2002 90 SD/MMC/SDIO/SmartMedia                      |
|       Toshiba TC6387XB 2001-2002 62 SD/MMC/SDIO/SDLED                           |
|       Toshiba TC6391XB 2002     202 SD/MMC/SDIO/SmartMedia/USB/LCD/etc.         |
|       Toshiba TC6393XB ?  ;\unknown features, no datasheet exists (the chips    
|       Toshiba T7L66XB  ?  ;/are mentioned in tmio_mmc.h and tmio_mmc.c source)  |
+---------------------------------------------------------------------------------+
```

Related source code:

```
+-------------------------------------------------------------------------------+
|       https://github.com/torvalds/linux/tree/master/drivers/mmc/host/         |
|       (see files toshsd.* and tmio_mmc.*)                                     |
|       (that just as historic references, meanwhile there's better source code |
|       around, written specifically for DSi and 3DS hardware)                  |
+-------------------------------------------------------------------------------+
```

The TC6380AF/TC6387XB/TC6391XB datasheets are more or less identical on the SD/MMC/SDIO section, TC6387XB is probably the best reference because it doesn\'t contain offtopic extras like SmartMedia, USB, LCD, etc. The datasheets contain I/O Maps with port addresses, but no description tables for the bits in those ports (though some bits are mentioned here and there in the text, scattered across many different pages, and other bits are left completely undocumented).



