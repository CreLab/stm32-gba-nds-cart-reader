# DS Memory Control - WRAM


### 4000247h - NDS9 - WRAMCNT - 8bit - WRAM Bank Control (R/W)
### 4000241h - NDS7 - WRAMSTAT - 8bit - WRAM Bank Status (R)
Should not be changed when using Nintendo\'s API.

```
+--------------------------------------------------------------------------------+
|       0-1   ARM9/ARM7 (0-3 = 32K/0K, 2nd 16K/1st 16K, 1st 16K/2nd 16K, 0K/32K) |
|       2-7   Not used                                                           |
+--------------------------------------------------------------------------------+
```

The ARM9 WRAM area is 3000000h-3FFFFFFh (16MB range).
The ARM7 WRAM area is 3000000h-37FFFFFh (8MB range).
The allocated 16K or 32K are mirrored everywhere in the above areas.
De-allocation (0K) is a special case: At the ARM9-side, the WRAM area is then empty (containing undefined data). At the ARM7-side, the WRAM area is then containing mirrors of the 64KB ARM7-WRAM (the memory at 3800000h and up).



