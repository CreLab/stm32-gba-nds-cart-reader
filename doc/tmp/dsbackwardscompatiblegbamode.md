# DS Backwards-compatible GBA-Mode


When booting a 32pin GBA cartridge, the NDS is automatically switched into GBA mode, in that mode all NDS related features are disabled, and the console behaves (almost) like a GBA.

### GBA Features that are NOT supported on NDS in GBA Mode.
Unlike real GBA, the NDS does not support 8bit DMG/CGB cartridges.
The undocumented Internal Memory Control register (Port 800h) isn\'t supported, so the NDS doesn\'t allow to use \'overclocked\' RAM.
The NDS doesn\'t have a link-port, so GBA games can be played only in single player mode, link-port accessories cannot be used, and the NDS cannot run GBA code via multiboot.

### GBA Features that are slightly different on NDS in GBA Mode.
The CPU, Timers, and Sound Frequencies are probably clocked at 16.76MHz; 33.51MHz/2; a bit slower than the original GBA\'s 16.78MHz clock?
In the BIOS, a single byte in a formerly 00h-filled area has been changed from 00h to 01h, resulting in SWI 0Dh returning a different BIOS checksum.
The GBA picture can be shown on upper or lower screen (selectable in boot-menu), the backlight for the selected screen is always on, resulting in different colors & much better visibility than original GBA. Unlike GBA-SP, the NDS doesn\'t have a backlight-button.

### Screen Border in GBA mode
The GBA screen is centered in the middle of the NDS screen. The surrounding pixels are defined by 32K-color bitmap data in VRAM Block A and B. Each frame, the GBA picture is captured into one block, and is displayed in the next frame (while capturing new data to the other block).
To get a flicker-free border, both blocks should be initialized to contain the same image before entering GBA mode (usually both are zero-filled, resulting in a plain black border).
Note: When using two different borders, the flickering will be irregular - so there appears to be a frame inserted or skipped once every some seconds in GBA mode?!

### Switching from NDS Mode to GBA Mode

```
+-----------------------------------------------------------------------------------+
|       --- NDS9: ---                                                               |
|       ZEROFILL VRAM A,B     ;init black screen border (or other color/image)      |
|       POWCNT=8003h          ;enable 2D engine A on upper screen (0003h=lower)     |
|       EXMEMCNT=...          ;set Async Main Memory mode (clear bit14)             |
|       IME=0                 ;disable interrupts                                   |
|       SWI 06h               ;halt with interrupts disabled (lockdown)             |
|       --- NDS7: ---                                                               |
|       POWERMAN.REG0=09h     ;enable sound amplifier & upper backlight (05h=lower) |
|       IME=0                 ;disable interrupts                                   |
|       wait for VCOUNT=200   ;wait until VBlank                                    |
|       SWI 1Fh with R2=40h   ;enter GBA mode, by CustomHalt(40h)                   |
+-----------------------------------------------------------------------------------+
```

After that, the GBA BIOS will be booted, the GBA Intro will be displayed, and the GBA cartridge (if any) will be started.



