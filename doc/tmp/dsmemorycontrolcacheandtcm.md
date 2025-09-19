# DS Memory Control - Cache and TCM


TCM and Cache are controlled by the System Control Coprocessor,
- [ARM CP15 System Control Coprocessor](./armcp15systemcontrolcoprocessor.md)

The specifications for the NDS9 are:

### Tightly Coupled Memory (TCM)

```
+-----------------------------------------------------------------------+
|       ITCM 32K, base=00000000h (fixed, not move-able)                 |
|       DTCM 16K, base=moveable  (default base=27C0000h)                |
+-----------------------------------------------------------------------+
```

Note: Although ITCM is NOT moveable, the NDS Firmware configures the ITCM size to 32MB, and so, produces ITCM mirrors at 0..1FFFFFFh. Furthermore, the PU can be used to lock/unlock memory in that region. That trick allows to move ITCM anywhere within the lower 32MB of memory.

### Cache

```
+------------------------------------------------------------------------+
|       Data Cache 4KB, Instruction Cache 8KB                            |
|       4-way set associative method                                     |
|       Cache line 8 words (32 bytes)                                    |
|       Read-allocate method (ie. writes are not allocating cache lines) |
|       Round-robin and Pseudo-random replacement algorithms selectable  |
|       Cache Lockdown, Instruction Prefetch, Data Preload               |
|       Data write-through and write-back modes selectable               |
+------------------------------------------------------------------------+
```


### Protection Unit (PU)
Recommended/default settings are:

```
+-----------------------------------------------------------------------+
|       Region  Name            Address   Size   Cache WBuf Code Data   |
|       -       Background      00000000h 4GB    -     -    -    -      |
|       0       I/O and VRAM    04000000h 64MB   -     -    R/W  R/W    |
|       1       Main Memory     02000000h 4MB    On    On   R/W  R/W    |
|       2       ARM7-dedicated  027C0000h 256KB  -     -    -    -      |
|       3       GBA Slot        08000000h 128MB  -     -    -    R/W    |
|       4       DTCM            027C0000h 16KB   -     -    -    R/W    |
|       5       ITCM            01000000h 32KB   -     -    R/W  R/W    |
|       6       BIOS            FFFF0000h 32KB   On    -    R    R      |
|       7       Shared Work     027FF000h 4KB    -     -    -    R/W    |
+-----------------------------------------------------------------------+
```

Notes: In Nintendo\'s hardware-debugger, Main Memory is expanded to 8MB (for that reason, some addresses are at 27NN000h instead 23NN000h) (some of the extra memory is reserved for the debugger, some can be used for game development). Region 2 and 7 are not understood? GBA Slot should be max 32MB+64KB, rounded up to 64MB, no idea why it is 128MB? DTCM and ITCM do not use Cache and Write-Buffer because TCM is fast. Above settings do not allow to access Shared Memory at 37F8000h? Do not use cache/wbuf for I/O, doing so might suppress writes, and/or might read outdated values.
The main purpose of the Protection Unit is debugging, a major problem with GBA programs have been faulty accesses to memory address 00000000h and up (due to \[base+offset\] addressing with uninitialized (zero) base values). This problem has been fixed in the NDS, for the ARM9 processor at least, still there are various leaks: For example, the 64MB I/O and VRAM area contains only ca. 660KB valid addresses, and the ARM7 probably doesn\'t have a Protection Unit at all. Alltogether, the protection is better than in GBA, but it\'s still pretty crude compared with software debugging tools.
Region address/size are unified (same for code and data), however, cachabilty and access rights are non-unified (and may be separately defined for code and data).

Note: The NDS7 doesn\'t have any TCM, Cache, or CP15.



