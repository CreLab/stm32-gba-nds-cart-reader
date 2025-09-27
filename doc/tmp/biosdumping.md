# BIOS Dumping


### BIOSes

```
+----------------------------------------------------------------------------------+
|       GBA BIOS 16K  (fully dumpable, CRC32=81977335 on GBA with [3F0Ch]=00h)     |
|       GBA BIOS 16K  (fully dumpable, CRC32=A6473709 on NDS/3DS with [3F0Ch]=01h) |
|       NDS7 BIOS 16K (fully dumpable, CRC32=1280F0D5)                             |
|       NDS9 BIOS 4K  (fully dumpable, CRC32=2AB23573)                             |
|       DSi7 BIOS 64K (about 41K dumpable) (new: fully dumped now)                 |
|       DSi9 BIOS 64K (about 41K dumpable)                                         |
|       3DS9 BIOS 64K (fully dumpable)                                             |
|       3DS11 BIOS 64K (fully dumpable)                                            |
|       DSiWifi BIOS 80K on older DSi (fully dumpable)                             |
|       DSiWifi BIOS Unknown size on newer DSi (fully dumpable)                    |
|       3DSWifi BIOS Unknown size on 3DS (fully dumpable)                          |
+----------------------------------------------------------------------------------+
```


### GBA BIOS
Contains SWI Functions and Bootcode (for starting cartridges, or booting via Serial Port). The GBA BIOS can be read only by opcodes executed in BIOS area, for example, via the MidiKey2Freq function (most other SWI Functions (like CpuSet) are refusing source addresses within BIOS area).

### NDS BIOSes
Contains SWI Functions and Bootcode (for booting from SPI Bus Firmware FLASH memory). The NDS9 BIOS can be dumped without restrictions (eg. via CpuSet, or via LDR opcodes in RAM). The NDS7 BIOS has same restrictions as GBA, ie. reading works only by BIOS opcodes, and not by functions like CpuSet. The GetCRC16 functions does work though (at least for memory at 1204h..3FFFh). As an additional obstacle, memory at 0000h..1203h can be dumped only by opcodes within 0000h..1203h (that memory does mainly contain data, but some of the data values can serve as THUMB LDR opcodes). For details see:
- [DS Memory Control - BIOS](./dsmemorycontrolbios.md)
Note: DSi consoles are containing a copy of the NDS BIOSes, but with BIOSPROT set to 0020h (even when running in NDS mode), so the first 20h bytes of the DSi\'s NDS7 BIOS aren\'t dumpable (except via tracing, see below), that 20h bytes should be just same as on original NDS7 though.

### DSi BIOSes - Lower 32K-halves (SWI Functions)
The lower 32K of DSi9 doesn\'t have any restricions. The lower 32K of DSi7 has similar restrictions as NDS7, but with BIOSPROT set to 0020h (instead of 1204h), this is making it more easy to dump memory at 0020h..7FFFh (eg. via GetCRC16), but makes it impossible to dump the exception vectors at 0000h..001Fh, however, they can be deduced by tracing (with timer IRQs):

```
+-----------------------------------------------------------------------+
|       ROM:00000000h  EA000006  b 20h   ;dsi7_reset_vector             |
|       ROM:00000004h  EA000006  b 24h   ;dsi7_undef_handler            |
|       ROM:00000008h  EA00001F  b 8Ch   ;dsi7_swi_handler              |
|       ROM:0000000Ch  EA000004  b 24h   ;dsi7_prefetch_abort_handler   |
|       ROM:00000010h  EA000003  b 24h   ;dsi7_data_abort_handler       |
|       ROM:00000014h  EAFFFFFE  b 14h   ;reserved_vector               |
|       ROM:00000018h  EA000013  b 6Ch   ;dsi7_irq_handler              |
|       ROM:0000001Ch  EA000000  b 24h   ;dsi7_fiq_handler              |
+-----------------------------------------------------------------------+
```

Aside from branch opcodes, above could theoretically contain ALU opcodes that modify R15 (but that would be very unlikely, and would make no difference) (and, the above 20h bytes are dumped/confirmed on 3DS in DSi mode).

### DSi BIOSes - Upper 32K-halves (Bootcode, for booting from eMMC memory)
The upper 32K of the DSi9 and DSi7 BIOSes are locked at some point during booting, and there\'s no known way to dump them directly. However, portions of that memory are relocated to RAM/TCM before locking, and that relocated copies can be dumped.
On a DSi, the following DSi ROM data can be dumped (originally done via Main Memory hacks, ie. with complex external hardware soldered to the mainboard, but it\'s now also possible via Unlaunch.dsi exploit):

```
+-------------------------------------------------------------------------------------+
|       ROM:FFFF87F4h / TCM:1FFC400h (400h)  (C3 02 93 DE ..) RSA keys (8x80h)        |
|       ROM:FFFF9920h / TCM:1FFC800h (80h)   (30 33 26 D5 ..) Whatever                |
|       ROM:FFFF99A0h / TCM:1FFC894h (1048h) (99 D5 20 5F ..) Blowfish/NDS-mode       |
|       ROM:FFFFA9E8h / TCM:1FFD8DCh (1048h) (D8 18 FA BF ..) Blowfish/unused?        |
|       ROM:00008188h / RAM:3FFC400h (200h)  (CA 13 31 79 ..) Whatever, 32x10h AES?   |
|       ROM:0000B5D8h / RAM:3FFC600h (40h)   (AF 1B F5 16 ..) Whatever, "common key"? |
|       ROM:0000C6D0h / RAM:3FFC654h (1048h) (59 AA 56 8E ..) Blowfish/DSi-mode       |
|       ROM:0000D718h / RAM:3FFD69Ch (1048h) (54 86 13 3B ..) Blowfish/unused?        |
+-------------------------------------------------------------------------------------+
```

On a 3DS, the following \"DSi ROM data\" can be dumped from the 2470h-byte DSi key area in 3DS memory at ARM9 ITCM 01FFD000h..01FFF46F (via 3DS exploits that are capable of executing code on ARM9 side):

```
+-----------------------------------------------------------------------------+
|       ROM:FFFF87F4h / 3DS:01FFD000h  200h  RSA keys 0..3 (4x80h)            |
|       ROM:00008308h / 3DS:01FFD200h  80h   some AES keys                    |
|       ROM:FFFF9920h / 3DS:01FFD280h  80h   whatever                         |
|       ROM:0000B5D8h / 3DS:01FFD300h  40h   AES keys and values (common etc) |
|       ROM:?         / 3DS:01FFD340h  A0h   misc "Nintendo" string etc.      |
|       ROM:0000C6D0h / 3DS:01FFD3E0h  1048h Blowfish for DSi-mode            |
|       ROM:FFFF99A0h / 3DS:01FFE428h  1048h Blowfish for DS-mode             |
+-----------------------------------------------------------------------------+
```

The 3DS does have only half of the DSi keys (the extra keys might be used for DSi debug version, but aren\'t needed for normal DSi software).
The 40h-byte area for ROM:0000B5D8h can be fully dumped from 3DS ITCM, the same vales should also exist in DSi ITCM, but the DSi zerofills a 10h-byte fraction of that area after initialization, and it doesn\'t seem be possible to read that values via Main Memory hacks (most of that erased values can be found in AES keyslots though).
The A0h-byte area is found only in 3DS ITCM, it should also exist somewhere in DSi ROM, but isn\'t relocated to DSi ITCM (however, the relevant values can be found in AES keyslots, eg. the \"Nintendo\" string).

### Checksums for BiosDSi.rom (20000h bytes)

```
+--------------------------------------------------------------------------------+
|       Offset Size  CRC32                                                       |
|       00000h 8000h 5434691Dh                ;\                                 
|       08000h 188h  ?                        ;                                  |
|       08188h 180h  E5632151h  (not 3ds)     ;                                  |
|       08308h 80h   64515306h                ;                                  |
|       08388h 3250h ?                        ;                                  |
|       0B5D8h 20h   85BE2749h                ; ARM7                             |
|       0B5F8h 10h   25A46A54h  (3ds only)    ;                                  |
|       0B608h 10h   E882B9A9h                ;                                  |
|       0B618h 10B8h ?                        ;                                  |
|       0C6D0h 1048h 3B5CDF06h                ;                                  |
|       0D718h 1048h 5AC363F9h  (not 3ds)     ;                                  |
|       0E860h 18A0h ?                        ;/                                 |
|       10000h 8000h 11E7C1EAh                ;\                                 
|       18000h 7F4h  ?                        ;                                  |
|       187F4h 200h  4405D4BAh                ;                                  |
|       189F4h 200h  2A32F2E7h  (not 3ds)     ;                                  |
|       18BF4h D2Ch  ?                        ; ARM9                             |
|       19920h 80h   2699A10Fh                ;                                  |
|       199A0h 1048h A8F58AE7h                ;                                  |
|       1A9E8h 1048h E94759ACh  (not 3ds)     ;                                  |
|       1BA30h 45D0h ?                        ;/                                 |
|       ?      A0h   180DF59Bh  (3ds only)    ;-whatever, "Nintendo" string etc. |
|       ?      80h   ........h  (TWL-FIRM)    ;-RSA key for eMMC boot info       |
+--------------------------------------------------------------------------------+
```

Checksums for the \'whole\' 20000h-byte file (with unknown/missing areas zerofilled):

```
+-----------------------------------------------------------------------+
|       180DF59Bh (tcm/ram dump)  (missing 10h bytes)                   |
|       03A21235h (3ds dump)      (missing 180h+200h+1048h+1048h bytes) |
|       CDAA8FF6h (combined dump) (missing only the unknown "?" areas)  |
+-----------------------------------------------------------------------+
```


### 3DS BIOS
Can be dumped by crashing the 3DS with wrong voltages, or by using sighax to crash the bootrom before disabling the upper 32Kbyte halves of the ARM9/ARM11 ROMs.

### DSiWifi BIOS
The Wifi BIOS can be dumped by using the WINDOW_DATA register via SDIO CMD53.

### Further DSi BIOSes
The DSi cameras and several other I2C/SPI devices are probably having BIOS ROMs, too. Unknown if/how that ROMs are dumpable.

### DSi BIOS Dumping via voltage errors
Lowering VDD12 for a moment does work quite reliable for crashing the ARM9 and trapping the 2FFFD9Ch vector in Main RAM. The problem is that Main RAM seems to be disabled during bootstage 1 (it gets enabled at begin of bootstage 2 via EXMEMCNT, that is, shortly after the upper BIOS 32Kbyte areas are disabled). More on that here:

```
+-----------------------------------------------------------------------+
|       http://4dsdev.kuribo64.net/thread.php?id=130                    |
+-----------------------------------------------------------------------+
```

One theory/idea (from dark_samus) is that EXMEMCNT controls the CE2 pin on the Main RAM chip, so one could try to rewire that pin to get Main RAM enabled regardless of EXMEMCNT, if that\'s actually working, then trapping the 2FFFD9Ch vector should work even while BIOS ROMs are fully readable.



