# DS Memory Control - Cartridges and Main RAM


### 4000204h - NDS9 - EXMEMCNT - 16bit - External Memory Control (R/W)
### 4000204h - NDS7 - EXMEMSTAT - 16bit - External Memory Status (R/W..R)

```
+-------------------------------------------------------------------------------------+
|       0-1   32-pin GBA Slot SRAM Access Time    (0-3 = 10, 8, 6, 18 cycles)         |
|       2-3   32-pin GBA Slot ROM 1st Access Time (0-3 = 10, 8, 6, 18 cycles)         |
|       4     32-pin GBA Slot ROM 2nd Access Time (0-1 = 6, 4 cycles)                 |
|       5-6   32-pin GBA Slot PHI-pin out   (0-3 = Low, 4.19MHz, 8.38MHz, 16.76MHz)   |
|       7     32-pin GBA Slot Access Rights     (0=ARM9, 1=ARM7)                      |
|       8-10  Not used (always zero)                                                  |
|       11    17-pin NDS Slot Access Rights     (0=ARM9, 1=ARM7)                      |
|       12    Not used (always zero)                                                  |
|       13    NDS:Always set?  ;set/tested by DSi bootcode: Main RAM enable, CE2 pin? |
|       14    Main Memory Interface Mode Switch (0=Async/GBA/Reserved, 1=Synchronous) |
|       15    Main Memory Access Priority       (0=ARM9 Priority, 1=ARM7 Priority)    |
+-------------------------------------------------------------------------------------+
```

Bit0-6 can be changed by both NDS9 and NDS7, changing these bits affects the local EXMEM register only, not that of the other CPU.
Bit7-15 can be changed by NDS9 only, changing these bits affects both EXMEM registers, ie. both NDS9 and NDS7 can read the current NDS9 setting.
Bit14=0 is intended for GBA mode, however, writes to this bit appear to be ignored?
- [DS Main Memory Control](./dsmainmemorycontrol.md)

### GBA Slot (8000000h-AFFFFFFh)
The GBA Slot can be mapped to ARM9 or ARM7 via EXMEMCNT.7.
For the selected CPU, memory at 8000000h-9FFFFFFh contains the \"GBA ROM\" region, and memory at A000000h-AFFFFFFh contains the \"GBA SRAM\" region (repeated every 64Kbytes). If there is no cartridge in GBA Slot, then the ROM/SRAM regions will contain open-bus values: SRAM region is FFh-filled (High-Z). And ROM region is filled by increasing 16bit values (Addr/2), possibly ORed with garbage depending on the selected ROM Access Time:

```
+-----------------------------------------------------------------------+
|       6 clks   --> returns "Addr/2"                                   |
|       8 clks   --> returns "Addr/2"                                   |
|       10 clks  --> returns "Addr/2 OR FE08h" (or similar garbage)     |
|       18 clks  --> returns "FFFFh" (High-Z)                           |
+-----------------------------------------------------------------------+
```

For the deselected CPU, all memory at 8000000h-AFFFFFFh becomes 00h-filled, this is required for bugged games like Digimon Story: Super Xros Wars (which is accidently reading deselected GBA SRAM at \[main_ram_base+main_ram_addr\*4\], whereas it does presumably want to read Main RAM at \[main_ram_base+index\*4\]).



