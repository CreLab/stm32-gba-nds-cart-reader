# DS Cartridge GBA Slot


Aside from the 17-pin NDS slot, the DS also includes a 32-pin GBA slot. This slot is used for GBA backwards compatibility mode. Additionally, in DS mode, it can be as expansion port, or for importing data from GBA games.

```
+---------------------------------------------------------------------------+
|       NDS:     Normal 32pin slot                                          |
|       DS Lite: Short 32pin slot (GBA cards stick out)                     |
|       DSi:     N/A (dropped support for GBA carts, and for DS-expansions) |
+---------------------------------------------------------------------------+
```

In DS mode, ROM, SRAM, FLASH backup, and whatever peripherals contained in older GBA cartridges can be accessed (almost) identically as in GBA mode,
- [GBA Cartridges](./gbacartridges.md)

### Addressing
In DS mode, only one ROM-region is present at 8000000h-9FFFFFFh (ie. without the GBA\'s mirrored WS1 and WS2 regions at A000000h-DFFFFFFh). The expansion region (for SRAM/FLASH/etc) has been moved from E000000h-E00FFFFh (GBA-mode) to A000000h-A00FFFFh (DS-mode).

### Timings
GBA timings are specified as \"waitstates\" (excluding 1 access cycle), NDS timings are specified as (total) \"access time\". And, the NDS bus-clock is twice as fast as for GBA. So, for \"N\" GBA waitstates, the NDS access time should be \"(N+1)\*2\". Timings are controlled via NDS EXMEMCNT instead GBA WAITCNT,
- [DS Memory Control - Cartridges and Main RAM](./dsmemorycontrolcartridgesandmainram.md)

### GBA EEPROM Timings
EEPROMs in GBA carts can be accessed via DMA in DS mode, although the timings are a bit too fast. The access time should be 18 clks for 1st/2nd access, but the NDS supports only 4 or 6 clks for 2nd access; of which, 6 clks seems to work stable (and 4 clks doesn\'t work, it seems to ignore writes and returns garnage on reading).



