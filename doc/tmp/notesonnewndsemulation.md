# Notes on New NDS Emulation


Hello to newer no\$gba version(s) with NDS support. Most of it is working fine by now, a few details are still under construction. The most important (missing) things to be aware of are:

### Major Missing Features
WLAN emulation is almost complete (but still incompatible with commercial games) (parts for transfer timing reasons, and parts because nobody knows yet how multiplayer packets work).
3D emulation is almost complete, too, only missing feature is Anti-Aliasing.

### Things that work only with real NDS-BIOS-image
The \"decompression-with-callback\" BIOS functions are currently working only if you do have a copy of the real BIOSes as ROM-images (see Installation and DS Xboo chapters).
Encrypted ROM-images (with encrypted first 2Kbytes of the secure area) can be used only if the (full) NDS7 BIOS ROM-image is present (which contains the 1048h-byte decryption seed data).

### Minor Missing Features and Glitches (in NDS mode)
VRAM viewer Tile/OBJ windows don\'t work.
Saving Snapshots doesn\'t work yet.
Backup media type isn\'t autodetected.

### Recommended TCM Areas
No\$gba decodes memory blocks by examining address bits24-27 (so memory is split into 16MB blocks). TCM emulation works fastest if DTCM and ITCM are each located at the bottom of free 16MB blocks (ie. blocks that do not contain other memory, such like WRAM, VRAM, etc.), recommended ITCM/DTCM base addresses would be:

```
+-------------------------------------------------------------------------+
|       ITCM at 00000000h, or (mirrored to) 01000000h.                    |
|       DTCM at 01000000h, 0B000000h, 0C000000h, 0D000000h, or 0E000000h. |
+-------------------------------------------------------------------------+
```

Other addresses are supported by no\$gba v2.2c and up, for example, the Metroid Demo uses DTCM base overlapping with the Main Memory region, a possible advantage is that DTCM & Main RAM can be used as continous memory region, however, the emulation performance won\'t be optimal.

### Note
Use Ctrl+T in debug mode to toggle between the two CPUs.



