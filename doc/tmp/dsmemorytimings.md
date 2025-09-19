# DS Memory Timings


### System Clock

```
+-----------------------------------------------------------------------+
|       Bus clock  = 33MHz (33.513982 MHz) (1FF61FEh Hertz)             |
|       NDS7 clock = 33MHz (same as bus clock)                          |
|       NDS9 clock = 66MHz (internally twice bus clock; for cache/tcm)  |
+-----------------------------------------------------------------------+
```

Most timings in this document are specified for 33MHz clock (not for the 66MHz clock). Respectively, NDS9 timings are counted in \"half\" cycles.

### Memory Access Times
Tables below show the different access times for code/data fetches on arm7/arm9 cpus, measured for sequential/nonsequential 32bit/16bit accesses.

```
+-------------------------------------------------------------------------------+
|       NDS7/CODE             NDS9/CODE                                         |
|       N32 S32 N16 S16 Bus   N32 S32 N16 S16 Bus                               |
|       9   2   8   1   16    9   9   4.5 4.5 16  Main RAM (read) (cache off)   |
|       1   1   1   1   32    4   4   2   2   32  WRAM,BIOS,I/O,OAM             |
|       2   2   1   1   16    5   5   2.5 2.5 16  VRAM,Palette RAM              |
|       16  12  10  6   16    19  19  9.5 9.5 16  GBA ROM (example 10,6 access) |
|       -   -   -   -   -     0.5 0.5 0.5 0.5 32  TCM, Cache_Hit                |
|       -   -   -   -   -     (--Load 8 words--)  Cache_Miss                    |
+-------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------+
|       NDS7/DATA             NDS9/DATA                                         |
|       N32 S32 N16 S16 Bus   N32 S32 N16 S16 Bus                               |
|       10  2   9   1   16    10  2   9   1   16  Main RAM (read) (cache off)   |
|       1   1   1   1   32    4   1   4   1   32  WRAM,BIOS,I/O,OAM             |
|       1?  2   1   1   16    5   2   4   1   16  VRAM,Palette RAM              |
|       15  12  9   6   16    19  12  13  6   16  GBA ROM (example 10,6 access) |
|       9   10  9   10  8     13  10  13  10  8   GBA RAM (example 10 access)   |
|       -   -   -   -   -     0.5 0.5 0.5 -   32  TCM, Cache_Hit                |
|       -   -   -   -   -     (--Load 8 words--)  Cache_Miss                    |
|       -   -   -   -   -     11  11  11  -   32  Cache_Miss (BIOS)             |
|       -   -   -   -   -     23  23  23  -   16  Cache_Miss (Main RAM)         |
+-------------------------------------------------------------------------------+
```

All timings are counted in 33MHz units (so \"half\" cycles can occur on NDS9).
Note: 8bit data accesses have same timings than 16bit data.

\*\*\* DS Memory Timing Notes \*\*\*

The NDS timings are altogether pretty messed up, with different timings for CODE and DATA fetches, and different timings for NDS7 and NDS9\...

### NDS7/CODE
Timings for this region can be considered as \"should be\" timings.

### NDS7/DATA
Quite the same as NDS7/CODE. Except that, nonsequential Main RAM accesses are 1 cycle slower, and more strange, nonsequential GBA Slot accesses are 1 cycle faster.

### NDS9/CODE
This is the most messiest timing. An infamous PENALTY of 3 cycles is added to all nonsequential accesses (except cache, tcm, and main ram). And, all opcode fetches are forcefully made nonsequential 32bit (the NDS9 simply doesn\'t support fast sequential opcode fetches). That applies also for THUMB code (two 16bit opcodes are fetched by a single nonsequential 32bit access) (so the time per 16bit opcode is one half of the 32bit fetch) (unless a branch causes only one of the two 16bit opcodes to be executed, then that opcode will have the full 32bit access time).

### NDS9/DATA
Allows both sequential and nonsequential access, and both 16bit and 32bit access, so it\'s faster than NDS9/CODE. Nethertheless, it\'s still having the 3 cycle PENALTY on nonsequential accesses. And, similar as NDS7/DATA, it\'s also adding 1 cycle to nonsequential Main RAM accesses.

\*\*\* More Timing Notes / Lots of unsorted Info \*\*\*

### Actual CPU Performance
The 33MHz NDS7 is running more or less nicely at 33MHz. However, the so-called \"66MHz\" NDS9 is having \<much\> higher waitstates, and it\'s effective bus speed is barely about 8..16MHz, the only exception is code/data in cache/tcm, which is eventually reaching real 66MHz (that, assuming cache HITS, otherwise, in case of cache MISSES, the cached memory timing might even drop to 1.4MHz or so?).
\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
ARM9 opcode fetches are always N32 + 3 waits.

```
+-------------------------------------------------------------------------------+
|       S16 and N16 do not exist (because thumb-double-fetching) (see there).   |
|       S32 becomes N32 (ie. the ARM9 does NOT support fast sequential timing). |
+-------------------------------------------------------------------------------+
```

That N32 is having same timing as normal N32 access on NDS7, plus 3 waits.

```
+---------------------------------------------------------------------------+
|       Eg. an ARM9 N32 or S32 to 16bit bus will take: N16 + S16 + 3 waits. |
|       Eg. an ARM9 N32 or S32 to 32bit bus will take: N32 + 3 waits.       |
+---------------------------------------------------------------------------+
```

Main Memory is ALWAYS having the nonsequential 3 wait PENALTY (even on ARM7).
\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
ARM9 Data fetches however are allowed to use sequential timing, as well as raw 16bit accesses (which aren\'t forcefully expanded to slow 32bit accesses).
Nethertheless, the 3 wait PENALTY is added to any NONSEQUENTIAL accesses.
Only exceptions are cache and tcm which do not have that penalty.

```
+-----------------------------------------------------------------------+
|      Eg. LDRH on 16bit-data-bus is N16+3waits.                        |
|      Eg. LDR  on 16bit-data-bus is N16+S16+3waits.                    |
|      Eg. LDM  on 16bit-data-bus is N16+(n*2-1)*S16+3waits.            |
+-----------------------------------------------------------------------+
```

Eventually, data fetches can take place parallel with opcode fetches.

```
+------------------------------------------------------------------------+
|      That is NOT true for LDM (works only for LDR/LDRB/LDRH).          |
|      That is NOT true for DATA in SAME memory region than CODE.        |
|      That is NOT true for DATA in ITCM (no matter if CODE is in ITCM). |
+------------------------------------------------------------------------+
```

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

### NDS9 Busses
Unlike ARM7, the ARM9 has separate code and data busses, allowing it to perform code and data fetches simultaneously (provided that both are in different memory regions).
Normally, opcode execution times are calculated as \"(codetime+datatime)\", with the two busses, it can (ideally) be \"MAX(codetime,datatime)\", so the data access time may virtually take \"NULL\" clock cycles.
In practice, DTCM and Data Cache access can take NULL cycles (however, data access to ITCM can\'t).
When executing code in cache/itcm, data access to non-cache/tcm won\'t be any faster than with only one bus (as it\'s best, it could subtract 0.5 cycles from datatime, but, the access must be \"aligned\" to the bus-clock, so the \"datatime-0.5\" will be rounded back to the original \"datatime\").
When executing code in uncached main ram, and accessing data (elsewhere than in main memory, cache/tcm), then execution time is typically \"codetime+datatime-2\".

### NDS9 Internal Cycles
Additionally to codetime+datatime, some opcodes include one or more internal cycles. Compared with ARM7, the behaviour of that internal cycles is slightly different on ARM9. First of, on the NDS9, the internal cycles are of course \"half\" cycles (ie. counted in 66MHz units, not in 33MHz units) (although they may get rounded to \"full\" cycles upon next memory access outside tcm/cache). And, the ARM9 is in some cases \"skipping\" the internal cycles, that often depending on whether or not the next opcode is using the result of the current opcode.
Another big difference is that the ARM9 has lost the fast-multiply feature for small numbers; in some cases that may result in faster execution, but may also result in slower execution (one workaround would be to manually replace MUL opcodes by the new ARM9 halfword multiply opcodes); the slowest case are MUL opcodes that do update flags (eg. MULS, MLAS, SMULLS, etc. in ARM mode, and all ALL multiply opcodes in THUMB mode).

### NDS9 Thumb Code
In thumb mode, the NDS9 is fetching two 16bit opcodes by a single 32bit read. In case of 32bit bus, this reduces the amount of memory traffic and may result in faster execution time, of course that works only if the two opcodes are within a word-aligned region (eg. loops at word-aligned addresses will be faster than non-aligned loops). However, the double-opcode-fetching is also done on 16bit bus memory, including for unnecessary fetches, such like opcodes after branch commands, so the feature may cause heavy slowdowns.

### Main Memory
Reportedly, the main memory access times would be 5 cycles (nonsequential read), 4 cycles (nonsequential write), and 1 cycle (sequential read or write). Plus whatever termination cycles. Plus 3 cycles on nonsequential access to the last 2-bytes of a 32-byte block.
That\'s of course all wrong. Reads are much slower than 5 cycles. Not yet tested if writes are faster. And, I haven\'t been able to reproduce the 3 cycles on last 2-bytes effect, actually, it looks more as if that 3 cycles are accidently added to ALL nonsequential accesses, at ALL main memory addresses, and even to most OTHER memory regions\... which might be the source of the PENALTY which occurs on VRAM/WRAM/OAM/Palette and I/O accesses.

### DMA
In some cases DMA main memory read cycles are reportedly performed simultaneously with DMA write cycles to other memory.

### NDS9
On the NDS9, all external memory access (and I/O) is delayed to bus clock (or actually MUCH slower due to the massive waitstates), so the full 66MHz can be used only internally in the NDS9 CPU core, ie. with cache and TCM.

### Bus Clock
The exact bus clock is specified as 33.513982 MHz (1FF61FEh Hertz). However, on my own NDS, measured in relation to the RTC seconds IRQ, it appears more like 1FF6231h, that inaccuary of 1 cycle per 657138 cycles (about one second per week) on either oscillator, isn\'t too significant though.

### GBA Slot
The access time for GBA slot can be configured via EXMEMCNT register.

### VRAM Waitstates
Additionally, on NDS9, a one cycle wait can be added to VRAM accesses (when the video controller simultaneously accesses it) (that can be disabled by Forced Blank, see DISPCNT.Bit7). Moreover, additional VRAM waitstates occur when using the video capture function.
Note: VRAM being mapped to NDS7 is always free of additional waits.



