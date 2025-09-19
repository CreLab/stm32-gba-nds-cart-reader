# 3DS GPU External Register List Summary


**GPU Memory Control/Status Registers - Misc**

```
+-----------------------------------------------------------------------+
|       1040000                                                         |
| 0h  GPU_FIXED_00010002h (always 00010002h, maybe ChipID/Version?) (R) |
|       10400004h  GPU_VRAM_CNT (reset=0, bootrom=300h) (R/W)           |
|       10400008h  GPU_UNKNOWN_2BIT (R/W)                               |
|       1040000Ch  Unused (0)                                           |
+-----------------------------------------------------------------------+
```

**GPU Memory Fill Unit 0 and 1**

```
+-----------------------------------------------------------------------+
|       10400010h  GPU_MEMFILL_DST_ADDR0     ;\                         
|       10400014h  GPU_MEMFILL_DST_END0      ; GPU_MEMFILL_0            |
|       10400018h  GPU_MEMFILL_DATA0         ;                          |
|       1040001Ch  GPU_MEMFILL_CNT0          ;/                         |
|       10400020h  GPU_MEMFILL_DST_ADDR1     ;\                         
|       10400024h  GPU_MEMFILL_DST_END1      ; GPU_MEMFILL_1            |
|       10400028h  GPU_MEMFILL_DATA1         ;                          |
|       1040002Ch  GPU_MEMFILL_CNT1          ;/                         |
+-----------------------------------------------------------------------+
```

**GPU Memory Control/Status Registers - Misc**

```
+-----------------------------------------------------------------------+
|       10400030h  GPU_VRAM_POWER (R/W)                                 |
|       10400034h  GPU_STAT_IRQ_FLAGS (R)                               |
|       10400038h  GPU_STAT_SOMETHING (R)                               |
|       1040003Ch  GPU_MAKE_SOMETHING (R/W)                             |
|       10400040h  GPU_STAT_BACKLIGHT_OR_SO (R)                         |
|       10400044h  GPU_UNKNOWN_CAN_BE_7F80h (R)                         |
|       10400048h  GPU_UNKNOWN_32BIT (reset=0) (R/W)                    |
|       1040004Ch  Unused (0)                                           |
|       10400                                                           |
| 050h  GPU_TIMING_CNT1 (R/W=FFFFFFFFh) (res=1111EF00h) ;init=22221200h |
|       10400                                                           |
| 054h  GPU_TIMING_CNT2 (R/W=FFFFFFFFh) (res=00000112h) ;init=00000FF2h |
|       10400058h  GPU_STAT_BUSY_FLAGS (R)                              |
|       1040005Ch  GPU_MAKE_WHATEVER_MESS (R/W)                         |
|       10400060h  GPU_STAT_WHATEVER_MESS (R)                           |
|       10400064h  GPU_UNKNOWN_1BIT (R/W=00000001h) (res=0)             |
|                                                                       |
|      10400068h  GPU_UNKNOWN_INITIALLY_00A80000h (res=00A80000h) (R/W) |
|       1040006Ch  Unused (0)                                           |
+-----------------------------------------------------------------------+
```

**GPU Memory Control/Status Registers - Read-only memory traffic
counters\...**

```
+-----------------------------------------------------------------------+
|       1040007                                                         |
| 0h  GPU_STAT_TOTAL_NON_VRAM_READS      ;\Non-VRAM (eg. AXI,QTM,FCRAM) 
|       10400074h  GPU_STAT_TOTAL_NON_VRAM_WRITES     ;/                |
|                                                                       |
| 10400078h  GPU_STAT_TOTAL_VRAM_A_READS        ;\1st 3Mbyte VRAM block 
|       1040007Ch  GPU_STAT_TOTAL_VRAM_A_WRITES       ;/                |
|                                                                       |
| 10400080h  GPU_STAT_TOTAL_VRAM_B_READS        ;\2nd 3Mbyte VRAM block 
|       10400084h  GPU_STAT_TOTAL_VRAM_B_WRITES       ;/                |
|                                                                       |
|  10400088h  GPU_STAT_POLYGON_ARRAY_READS       ;-ATTR_BUF, INDEX_LIST |
|                                                                       |
|     1040008Ch  GPU_STAT_POLYGON_TEXTURE_READS     ;-cache misses only |
|       10400090h  GPU_STAT_POLYGON_DEPTHBUFFER_READS                   |
|       10400094h  GPU_STAT_POLYGON_DEPTHBUFFER_WRITES                  |
|       10400098h  GPU_STAT_POLYGON_COLORBUFFER_READS                   |
|       1040009Ch  GPU_STAT_POLYGON_COLORBUFFER_WRITES                  |
|       10400                                                           |
| 0A0h  GPU_STAT_LCD_UPPER_SCREEN_READS    ;\for both left+right buffer 
|       104000A4h  GPU_STAT_LCD_LOWER_SCREEN_READS    ;/                |
|       104000A8h  GPU_STAT_MEMCOPY_SRC_READS         ;\GPU_MEMCOPY     
|       104000ACh  GPU_STAT_MEMCOPY_DST_WRITES        ;/                |
|       104000B0h  GPU_STAT_MEMFILL_0_DST_WRITES      ;\GPU_MEMFILL 0/1 
|       104000B4h  GPU_STAT_MEMFILL_1_DST_WRITES      ;/                |
|       10400                                                           |
| 0B8h  GPU_STAT_CPU_READS_FROM_VRAM_A_B   ;\counted by GPU because the 
|       104000B                                                         |
| Ch  GPU_STAT_CPU_WRITES_TO_VRAM_A_B    ;/GPU must forward vram to cpu |
+-----------------------------------------------------------------------+
```

**GPU Memory Control/Status Registers - Misc**

```
+-----------------------------------------------------------------------+
|       104000C0h  GPU_BACKLIGHT_OR_SO_1 (reset=20000000h) (R/W)        |
|       104000C4h  GPU_BASE_ADDR_VRAM_A (reset=18000000h) (R/W)         |
|       104000C8h  GPU_BASE_ADDR_VRAM_B (reset=18300000h) (R/W)         |
|       104000CCh  GPU_BACKLIGHT_OR_SO_2 (reset=20000000h) (R/W)        |
|       104000D0h  GPU_UNKNOWN_4BIT (reset=0) (R/W)                     |
|       104000D4h  Unused (2Ch bytes, zerofilled)                       |
|       10400100h  Unused (300h bytes, mirrors of above 100h bytes)     |
+-----------------------------------------------------------------------+
```

**GPU Display Contollers**

```
+-----------------------------------------------------------------------+
|                                                                       |
|     10400400h  LCD Framebuffer Setup "PDC0" (100h bytes) (top screen) |
|                                                                       |
|  10400500h  LCD Framebuffer Setup "PDC1" (100h bytes) (bottom screen) |
|                                                                       |
|  10400600h  Unused? (200h bytes, Unknown/DANGER, hangs when reading?) |
|       10400800h  Unused? (400h bytes, Unknown/Unused, data abort)     |
+-----------------------------------------------------------------------+
```

**GPU Memory Copy Unit**

```
+-----------------------------------------------------------------------+
|       1                                                               |
| 0400C00h  GPU_MEMCOPY_SRC_ADDR - Memcopy Input physical address (R/W) |
|       10                                                              |
| 400C04h  GPU_MEMCOPY_DST_ADDR - Memcopy Output physical address (R/W) |
|       104                                                             |
| 00C08h  GPU_MEMCOPY_DISPLAY_SIZE - DisplayTransfer width/height (R/W) |
|       10400C                                                          |
| 0Ch  GPU_MEMCOPY_DISPLAY_GAP - DisplayTransfer Input height+gap (R/W) |
|       10400C10h  GPU_MEMCOPY_FLAGS - Memcopy Transfer flags (R/W)     |
|       10400C14h  GPU_MEMCOPY_UNKNOWN_21BIT - Memcopy (R/W)            |
|       10400C18h  GPU_MEMCOPY_CNT - Memcopy Start/Busy (R/W)           |
|       10400C1Ch  GPU_MEMCOPY_REMAIN_IRQ - Memcopy Remain IRQ (R/W)    |
|       10400C20h  GPU_MEMCOPY_TEX_SIZE - TextureCopy total amount      |
|       10                                                              |
| 400C24h  GPU_MEMCOPY_TEX_SRC_WIDTH - TextureCopy input line width/gap |
|       104                                                             |
| 00C28h  GPU_MEMCOPY_TEX_DST_WIDTH - TextureCopy output line width/gap |
|       10400C2Ch  GPU_MEMCOPY_UNKNOWN_FLAG - Memcopy Unknown (R/W)     |
|       10400C30h  Unused (D0h bytes, zerofilled)                       |
|       10400D00h  Unused (300h bytes, mirrors of above 100h bytes)     |
+-----------------------------------------------------------------------+
```




