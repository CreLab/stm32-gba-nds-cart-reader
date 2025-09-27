# DSi Emulation


### Activating DSi emulation (disabled by default)
The DSi emulation is still DISABLED by default, and must be enabled manually by setting the \"NDS Mode/Colors\" option to \"DSi (retail/16MB)\".
The reason is that DSi-enhanced games may run into troubles in DSi emulation mode (but should work fine in NDS emulation mode).

### DSi eMMC bootcode emulation
Using that emulation feature requires DSi BIOS dumps, eMMC dump, and Wifi-Flash dump.
The lower 32K halves of the ARM7/ARM9 BIOSes can be dumped quite easily (if you have any working DSi exploit), the DSi keys in upper 32K halves can be dumped indirectly (via simple exploits on 3DS, or via difficult main memory hacks on DSi). For details, see:
- [BIOS Dumping](./biosdumping.md)
For the ROM filenames, see:
- [Installation](./installation.md)
Getting the eMMC image require a DSiware exploit (eg. for DSi Camera, or Flipnote) (or hardmod), the image must include a footer with CID/CPU IDs (needed for decryption; obviously those IDs will also tell Nintendo \'who you are\', in case you should consider leaking your eMMC dump). For details, see:
- [DSi SD/MMC Images](./dsisdmmcimages.md)
- [DSi Console IDs](./dsiconsoleids.md)
- [AUX DSi SD/MMC Pin-Outs](./auxdsisdmmcpinouts.md)
Optionally, a copy of the DSi Wifi Flash can be stored in file \"WIFI-DSI.BIN\" (should be usually 128Kbytes; or, reportedly it\'s smaller on newer DSi\'s). That file only contains only some stuff like wifi calibration values, no\$gba is auto-generating some dummy calibration values if the file is missing (so the file is needed only if you want to do something like experimenting with different calibration settings).
If needed, the Wifi Flash can be dumped via SPI bus wiring (from wifi daughterboard), or via raw software (in case you can run NDS or DSi programs on your DSi console). For details, see the \"Firmware\" sections (named so because, on NDS, the Wifi Flash did also contain the firmware):
- [DS Cartridges, Encryption, Firmware](./dscartridgesencryptionfirmware.md)
Then, set the \"Reset/Startup Entrypoint\" option in no\$gba to \"BIOS\", and load a DSi cartridge or DSiware file (just as a dummy file, to switch the emulation into DSi mode).

### DSi Atheros Wifi BIOS
The Atheros Wifi BIOS is loaded from these filenames (in no\$gba directory):

```
+------------------------------------------------------------------------+
|       AR6002G.ROM  ;old DSi wifi chip (80Kbytes)   ;wifi-flash[1FDh]=1 |
|       AR6013G.ROM  ;new DSi wifi chip (256Kbytes)  ;wifi-flash[1FDh]=2 |
|       AR6014G.ROM  ;3DS wifi chip     (256Kbytes)  ;wifi-flash[1FDh]=3 |
+------------------------------------------------------------------------+
```

presence of that file doesn\'t affect emulation, it\'s used solely for viewing the wifi bios in the disassembler (via menubar, window, xtensa/wifi). The wifi bios can be dumped via SDIO functions WINDOW_READ_ADDR and WINDOW_DATA.

### DSi Cartridge emulation
For DSi ROM images, set the \"Reset/Startup Entrypoint\" to \"Start Cartridge directly\" (this will skip the eMMC boot process, so you don\'t need the eMMC dump, and you might also get away without BIOS dump, or with partial lower BIOS 32K dumps).
Then, load a DSi ROM-image (observe that older dumping tools can dump only the NDS areas of DSi cartridges; such incomplete dumps won\'t work in DSi mode).
Tested are two games: Cooking Coach (not working yet), and System Flaw (works, but requires cameras for use as \"motion sensors\", so it isn\'t actually playable). Going by reports from other users, most or all other DSi cartridges aren\'t working yet.

### DSi DSiware emulation
DSiware games can be exported to SD card, and the SD card files can be decrypted via homebrew DSi SRL Extract utility (system files can be also downloaded and decrypted via homebrew NUS Downloader utility).
Loading the decrypted files into no\$gba is currently acting as if the files were cartridge ROM images (rather than files on eMMC). Surprisingly, this is actually working to some extent (the games are loading extra data from ROM, instead of from eMMC, which they should be usually doing). However, loading/saving game positions appears to be routed to eMMC (not to cartridge FLASH/EEPROM). Apart from that, most DSiware games are probably stumbling over this or that unemulated detail or uninitialized memory area.

### Nothing working?
Depends on what you want: If you want to play games, then, yes, I don\'t know of any DSi games that are working/playable yet. If you want to do programming/debugging, then you might find out that almost everything is more or less working. I don\'t know of any other active DSi devrs though - not too surprising since the DSi is definitely the most complicated and most unattractive console that I\'ve ever seen.



