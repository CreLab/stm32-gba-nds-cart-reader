# DS Power Control


The DS contains several Power Managment functions, some accessed via I/O ports (described below), and some accessed via SPI bus:
- [DS Power Management Device](./dspowermanagementdevice.md)

### 4000304h - NDS9 - POWCNT1 - Graphics Power Control Register (R/W)

```
+-------------------------------------------------------------------------------------+
|       0     Enable Flag for both LCDs (0=Disable) (Prohibited, see notes)           |
|       1     2D Graphics Engine A      (0=Disable) (Ports 008h-05Fh, Pal 5000000h)   |
|       2     3D Rendering Engine       (0=Disable) (Ports 320h-3FFh)                 |
|       3     3D Geometry Engine        (0=Disable) (Ports 400h-6FFh)                 |
|       4-8   Not used                                                                |
|       9     2D Graphics Engine B      (0=Disable) (Ports 1008h-105Fh, Pal 5000400h) |
|       10-14 Not used                                                                |
|       15    Display Swap (0=Send Display A to Lower Screen, 1=To Upper Screen)      |
|       16-31 Not used                                                                |
+-------------------------------------------------------------------------------------+
```

Use SwapBuffers command once after enabling Rendering/Geometry Engine.
Improper use of Bit0 may damage the hardware?
When disabled, corresponding Ports become Read-only, corresponding (palette-) memory becomes read-only-zero-filled.

### 4000304h - NDS7 - POWCNT2 - Sound/Wifi Power Control Register (R/W)

```
+------------------------------------------------------------------------+
|       Bit   Expl.                                                      |
|       0     Sound Speakers (0=Disable, 1=Enable) (Initial setting = 1) |
|       1     Wifi           (0=Disable, 1=Enable) (Initial setting = 0) |
|       2-31  Not used                                                   |
+------------------------------------------------------------------------+
```

Note: Bit0 disables the internal Speaker only, headphones are not disabled.
Bit1 disables Port 4000206h, and Ports 4800000h-480FFFFh.

### 4000206h - NDS7 - WIFIWAITCNT - Wifi Waitstate Control

```
+------------------------------------------------------------------------------------+
|       Bit   Expl.                                                                  |
|       0-1   WS0 nonsequential time (0-3 = 10, 8, 6, 18 cycles) ;\4800000h-4807FFFh 
|       2     WS0 sequential time    (0-1 = 6, 4 cycles)         ;/   (used for RAM) |
|       3-4   WS1 nonsequential time (0-3 = 10, 8, 6, 18 cycles) ;\4808000h-480FFFFh 
|       5     WS1 sequential time    (0-1 = 10, 4 cycles)        ;/   (used for I/O) |
|       6-15  Not used (zero)                                                        |
+------------------------------------------------------------------------------------+
```

This register is initialized by firmware on power-up (set to 0030h, other software shouldn\'t change that setting). The timings are per 16bit halfword access.
Note: WIFIWAITCNT can be accessed only when enabled in POWCNT2.

### 4000301h - NDS7 - HALTCNT - Low Power Mode Control (R/W)
In Halt mode, the CPU is paused as long as (IE AND IF)=0.
In Sleep mode, most of the hardware including sound and video are paused, this very-low-power mode could be used much like a screensaver.

```
+---------------------------------------------------------------------------------+
|       Bit   Expl.                                                               |
|       0-5   Not used (zero)                                                     |
|       6-7   Power Down Mode  (0=No function, 1=Enter GBA Mode, 2=Halt, 3=Sleep) |
+---------------------------------------------------------------------------------+
```

The HALTCNT register should not be accessed directly. Instead, the BIOS Halt, Sleep, CustomHalt, IntrWait, or VBlankIntrWait SWI functions should be used.
- [BIOS Halt Functions](./bioshaltfunctions.md)
- [ARM CP15 System Control Coprocessor](./armcp15systemcontrolcoprocessor.md)
The NDS9 does not have a HALTCNT register, instead, the Halt function uses the co-processor opcode \"mcr p15,0,r0,c7,c0,4\" - this opcode locks up if interrupts are disabled via IME=0 (unlike NDS7 HALTCNT method which doesn\'t check IME).

### 4000300h - NDS7/NDS9 - POSTFLG - BYTE - Post Boot Flag (R/W)
The NDS7 and NDS9 post boot flags are usually set upon BIOS/Firmware boot completion, once when set the reset vector is redirected to the debug handler of Nintendo\'s hardware debugger. That allows the NDS7 debugger to capture accidental jumps to address 0, that appears to be a common problem with HLL-programmers, asm-coders know that (and why) they should not jump to 0.

```
+------------------------------------------------------------------------+
|       Bit   Expl.                                                      |
|       0     Post Boot Flag (0=Boot in progress, 1=Boot completed)      |
|       1     NDS7: Not used (always zero), NDS9: Bit1 is read-writeable |
|       2-7   Not used (always zero)                                     |
+------------------------------------------------------------------------+
```

There are some write-restrictions: The NDS7 register can be written to only from code executed in BIOS (done by NDS boot ROM, or by DSi firmware, whereas the DSi firmware is using the CpuSet SWI function to issue the POSTFLG write from within ROM). Bit0 of both NDS7 and NDS9 registers cannot be cleared (except by Reset) once when it is set. DSi games seem to run regardless of POSTFLG, whilst NDS games somewhat refuse to run when POSTFLG=0.

### Memory Power Down Functions
- [DS Main Memory Control](./dsmainmemorycontrol.md)
- [DS Firmware Serial Flash Memory](./dsfirmwareserialflashmemory.md)



