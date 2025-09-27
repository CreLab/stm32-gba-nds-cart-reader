# DS Debug Registers (Emulator/Devkits)


### No\$gba Emulator Pseudo I/O Ports (no\$gba) (GBA,NDS9,NDS7)

```
+------------------------------------------------------------------------------------+
|       4FFFA00h..A0Fh R Emulation ID (16 bytes, eg. "no$gba v2.7", padded with 20h) |
|       4FFFA10h       W String Out (raw)                                            |
|       4FFFA14h       W String Out (with %param's)                                  |
|       4FFFA18h       W String Out (with %param's, plus linefeed)                   |
|       4FFFA1Ch       W Char Out (nocash)                                           |
|       4FFFA20h..A27h R Clock Cycles (64bit)                                        |
|       4FFFA28h..A3Fh - N/A                                                         |
+------------------------------------------------------------------------------------+
```

Note: Above ports can be disabled via the \"Debug I/O\" option in no\$gba setup.

### Ensata Emulator Pseudo I/O Ports (NDS9)

```
+------------------------------------------------------------------------------------+
|       4000640h (32bit) ;aka CLIPMTX_RESULT (mis-used to invoke detection)          |
|       4000006h (16bit) ;aka VCOUNT (mis-used to get detection result)              |
|       4FFF010h (32bit) ;use to initialize/unlock/reset something                   |
|       4FFF000h (8bit)  ;debug message character output (used when Ensata detected) |
+------------------------------------------------------------------------------------+
```

The Ensata detection works by mis-using CLIPMTX_RESULT and VCOUNT registers:

```
+-----------------------------------------------------------------------------------+
|       [4000640h]=2468ACE0h      ;CLIPMTX_RESULT (on real hardware it's read-only) |
|       if ([4000006h] AND 1FFh)=10Eh ;VCOUNT (on real hardware it's 000h..106h)    |
|         [4FFF010h]=13579BDFh        ;\initialize/reset something                  
|         [4FFF010h]=FDB97531h        ;/                                            |
|         Ensata=true                                                               |
|       else                                                                        |
|         Ensata=false                                                              |
|       endif                                                                       |
+-----------------------------------------------------------------------------------+
```

Once when a commercial game has detected Ensata, it stops communicating with the ARM7, and instead it does seem to want to communicate with the Ensata executable (which has little to do with real NDS hardware). Ie. aside from \"unlocking\" port 4FFF000h, it does also \"lock\" access to the ARM7 hardware (like sound, touchscreen, RTC, etc).

### ISD (Intelligent Systems Debugger or so) I/O Ports
The ISD ports seem to be real (non-emulated) debugging ports, mapped to the GBA Slot region at 8000000h-9FFFFFFh, and used to output text messages, and possible also other debugging stuff.
There are appear to be two variants: nitroemu and cgbemu (the latter appears to be dating back to old 8bit CGB hardware; which was apparently still used for the NDS two hardware generations later).

### NDS Devkit
In Nintendo\'s devkit, debug messages are handled in file \"os_printf.c\", this file detects the available hardware/software based debug I/O ports, and redirects the \[OS_PutString\] vector to the corresponding string_out function (eg. to OS_PutStringAris for writing a 00h-terminated string to port 4FFF000h). With some minimal efforts, this could be redirected to the corresponding no\$gba debug I/O ports.



