# Installation


### Required Hardware
Miminum requirement would be a 32bit CPU (eg. 80386SX and up). No\$gba has been programmed on a 66MHz 80486DX2, smaller games (eg. simple 2D games, text output) are working relative smoothly at 100% speed on that computer. Larger games (eg. 3D games, plasma demos) may require a CPU speed of up to 400..500MHz.
Emulation performance mainly depends on whether (and how much) the game is using the low power Halt/IntrWait GBA bios functions in idle mode, or not.

### Installing No\$gba
Just copy the executable to harddisk, preferably into a new/blank folder, below text will refer to this folder as the \'No\$gba\' folder, you may use any other name though. The program will automatically create some subdirecties. For example, the Slot directory is the suggested location for rom-images.
You will eventually also need some additional files - see below!

### Installing Updates
Just overwrite the old executable by the newer version. The setup file from the older version may be used, any unrecognized options will be set to the default value.

### Uninstalling No\$gba
The program does not infect the windows registry. If you wish to uninstall it just delete the \'No\$gba\' folder and all sub-directories.
Of course excluding any important files which you may have stored in these directories and which you may want to keep (ie. source code, binaries, game positions, and/or your registration key).

Optional Files

### NO\$GBA.ROM
No\$gba includes a built-in BIOS clone which is used if the BIOS ROM-image(s) are not found. However, the emulation accuracy (eg. exact execution time) of BIOS SWI-functions increases when using the original BIOS ROM-images. BIOS images are loaded if the following file(s) exist in your no\$gba folder.

```
+-----------------------------------------------------------------------+
|       NO$GBA.ROM    GBA+NDS7+NDS9 BIOS-images (16K+16K+4K)            |
+-----------------------------------------------------------------------+
```

Alternately, the images can be split into separate files, with filenames:

```
+-----------------------------------------------------------------------+
|       BIOSNDS.ROM   NDS7+NDS9 BIOS-images (16K+4K)                    |
|       BIOSNDS7.ROM  NDS7 BIOS-image (16K)                             |
|       BIOSNDS9.ROM  NDS9 BIOS-image (4K) (or 32K padded with zero's)  |
|       BIOSGBA.ROM   GBA BIOS-image (16K)                              |
|       GBA.ROM       Same as BIOSGBA.ROM (16K)                         |
+-----------------------------------------------------------------------+
```

For DSi emulation,

```
+------------------------------------------------------------------------------------+
|       BIOSDSI.ROM   DSi7+DSi9 BIOS-images (64K+64K)  ;\these are only 66% dumpable 
|       BIOSDSI7.ROM  DSi7 BIOS-image (64K)            ; yet (please pad undumped    |
|       BIOSDSI9.ROM  DSi9 BIOS-image (64K)            ;/regions with 00h-bytes)     |
+------------------------------------------------------------------------------------+
```

For 3DS emulation,

```
+---------------------------------------------------------------------------------+
|       BIOS3DS.ROM   3ds9+3ds11 BIOS-images (64K+64K) ;\                         
|       BIOS3DS9.ROM  3ds9 BIOS-image (64K)            ; these are filly dumpable |
|       BIOS3DS11.ROM 3ds11 BIOS-image (64K)           ;/                         |
+---------------------------------------------------------------------------------+
```

The no\$gba utility menu (and the Xboo tool on the no\$gba webpage) includes a function for downloading the BIOS from GBA/NDS to file (by simple cable connection).
Be careful when downloading the BIOSes from internet, there seems to be a very popular GBA BIOS in the net (probably a very old prototype version), which is NOT compatible with the actual GBA release version, also some NDS7 BIOS-images may be incomplete dumps (with first 4K zero-filled), no\$gba outputs a warning message if using an incorrect, incomplete, damaged, or patched BIOS version.

### FIRMWARE.BIN
A copy of the original NDS firmware in Wifi FLASH. This file increases emulation accuracy only by means of delaying the boot process. The no\$gba setup default setting is to start the cartridge directly, without executing the BIOS/Firmware boot code, so the presence of the firmware image doesn\'t actually disturb emulation performance.

### DSi Firmware (onboard eMMC) and DSi External SD Card
- [DSi SD/MMC Images](./dsisdmmcimages.md)

### PKUNZIP.EXE and/or ARJ.EXE
These decompression programs are required when loading ARJ or ZIP compressed cartridges. The programs must be stored in a directory which is part of your \'Path\' (ie. a directory which is automatically searched by the operating system, if you do not understand this, try using your C:\\Windows folder). Alternately, decompress the files by hand before loading them.




