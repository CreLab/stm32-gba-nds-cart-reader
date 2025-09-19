# 3DS Memory and I/O Map


**ARM11 Memory Map**

```
+-----------------------------------------------------------------------+
|       Old3DS Address   Size          Description                      |
|       Yes                                                             |
|  00000000h  10000h        ARM11 Bootrom mirror  ;also ITCM in ARM11 ? |
|       Yes   00010000h  10000h    64K ARM11 Bootrom                    |
|       Yes   10000000h  ?             IO "memory"                      |
|       Yes   1                                                         |
| 7E00000h  2000h      8K MPCore private memory region (aka... IRQ ???) |
|       No    17                                                        |
| E10000h  1000h      4K New3DS: L2C-310 Level 2 Cache Controller (2MB) |
|       Yes                                                             |
|   18000000h  600000h  6M   VRAM (two 3Mbyte banks, VRAM_A and VRAM_B) |
|       No    1                                                         |
| F000000h  400000h  4M   New3DS: extra memory (maybe VRAM and/or QTM?) |
|                                                                       |
| Yes   1FF00000h  40000h   256K Teak DSP Code memory (aka Shared WRAM) |
|                                                                       |
| Yes   1FF40000h  40000h   256K Teak DSP Data memory (aka Shared WRAM) |
|       Yes   1FF80000h  80000h   512K AXI WRAM                         |
|       Yes   20000000h  8000000h 128M FCRAM                            |
|       No    28000000h  8000000h 128M New3DS: FCRAM extension          |
|       Yes   FFFF0000h  10000h        ARM11 Bootrom mirror             |
+-----------------------------------------------------------------------+
```

Note: ARM11 MMU supports virtual memory addresses (so above physical
addresses may appear elsewhere in virtual memory).

**ARM9 Memory Map**

```
+-----------------------------------------------------------------------+
|       Old3DS Address   Size          Description                      |
|       Yes                                                             |
|   00000000h  "8000000h"    Instruction TCM, mirrored each 8000h bytes |
|       Yes   01                                                        |
| FF8000h  8000h     32K Instruction TCM (used here by kernel & titles) |
|                                                                       |
| Yes   07FF8000h  8000h         Instruction TCM (used here by bootrom) |
|       Yes                                                             |
| 08000000h  100000h   1M  ARM9-only internal memory (and ARM7 regions) |
|       No    08                                                        |
| 100000h  80000h   512K New3DS:ARM9-only extension (if any/if enabled) |
|       Yes   10000000h  8000000h      IO "memory"                      |
|       Yes                                                             |
|   18000000h  600000h   6M  VRAM (two 3Mbyte banks, VRAM_A and VRAM_B) |
|                                                                       |
| Yes   1FF00000h  40000h   256K Teak DSP Code memory (aka Shared WRAM) |
|                                                                       |
| Yes   1FF40000h  40000h   256K Teak DSP Data memory (aka Shared WRAM) |
|       Yes   1FF80000h  80000h   512K AXI WRAM                         |
|       Yes   20000000h  8000000h 128M FCRAM                            |
|       No    28000000h  8000000h 128M New3DS: FCRAM extension          |
|                                                                       |
|  Yes   FFF00000h  4000h     16K Data TCM (mapped here during bootrom) |
|       Yes   FFFF0000h  10000h    64K ARM9 Bootrom                     |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      _________                                                        |
| _________________________ I/O Maps __________________________________ |
+-----------------------------------------------------------------------+
```


**ARM9-only Registers**

```
+-----------------------------------------------------------------------+
|       Physaddr   Old3DS  A9/A11  Category                             |
|       10000000h  Yes     A9      CONFIG9 Registers                    |
|       10001000h  Yes     A9      IRQ Registers                        |
|                                                                       |
|  10002000h  Yes     A9      NDMA Registers     DMA (alike DSi's NDMA) |
|       100                                                             |
| 03000h  Yes     A9      TIMER Registers    Timers (alike GBA/NDS/DSi) |
|                                                                       |
|    10004000h  Yes     A9      CTRCARD Registers  ROM cart in 3DS mode |
|                                                                       |
|      10005000h          A9      CTRCARD?           2nd ROM cart slot? |
|       10                                                              |
| 006000h  Yes     A9      SDMMC Registers    For eMMC and SD Card slot |
|       100070                                                          |
| 00h  Yes     A9      Alternate SD/MMC Slot controller ;CFG9_SDMMC_CTL |
|       10008000h  Yes     A9      PXI Registers      aka IPC           |
|       10009000h  Yes     A9      AES Registers      Crypto            |
|       1000A000h  Yes     A9      SHA Registers      Crypto            |
|       1000B000h  Yes     A9      RSA Registers      Crypto            |
|       1000C000h  Yes     A9      XDMA Registers     DMA               |
|                                                                       |
|   1000D000h  Yes     A9      SPI_CARD Registers Savedata in ROM carts |
|                                                                       |
|  10010000h  Yes     A9      CONFIG Registers   More CONFIG9 registers |
|                                                                       |
| 10011000h  Yes     A9      PRNG Registers     Pseudo Random Generator |
|       10012000h  Yes     A9      OTP Registers      Console IDs       |
|                                                                       |
| 10018000h  Yes     A9      ARM7 Registers     GBA/NDS/DSi mode config |
+-----------------------------------------------------------------------+
```


**ARM11/ARM9 Registers**
Below registers can be accessed by both ARM11 and ARM9. However, most of
them are working best on ARM11 side (because IRQ and DMA startup modes
are implemented on ARM11 side only; and, in some cases, even FIFOs are
in a separate ARM11-only area at 10300000h and up).
One exception is NTRCARD (this does have IRQ/DMA on both ARM9 and ARM11
side).

```
+-----------------------------------------------------------------------+
|       101000                                                          |
| 00h  Yes     A11/A9  Alternate SD/MMC Slot controller ;CFG9_SDMMC_CTL |
|                                                                       |
|    10101000h  Yes     A11/A9  HASH Registers     Crypto (same as SHA) |
|       10102000h  Yes     A11/A9  Y2R_0 Registers    First YUV-to-RGBA |
|       101                                                             |
| 03000h  Yes     A11/A9  CSND Registers     Sound channels and capture |
|                                                                       |
|    10110000h  Yes     A11/A9  LGYFB_0            Legacy GBA/NDS Video |
|                                                                       |
|    10111000h  Yes     A11/A9  LGYFB_1            Legacy GBA/NDS Video |
|       101                                                             |
| 20000h  Yes     A11/A9  Camera Registers   Camera Bus 0 (DSi cameras) |
|                                                                       |
| 10121000h  Yes     A11/A9  Camera Registers   Camera Bus 1 (left-eye) |
|       10122000h  Yes     A11/A9  WIFI Registers     SDIO Wifi         |
|       1012300                                                         |
| 0h  Yes     A11/A9  ?                  SDIO?   ;uh, actually data.abt |
|       10                                                              |
| 130000h  No      A11/A9  L2B_0              New3DS: First RGB-to-RGBA |
|       101                                                             |
| 31000h  No      A11/A9  L2B_1              New3DS: Second RGB-to-RGBA |
|       101                                                             |
| 32000h  No      A11/A9  Y2R_1              New3DS: Second YUV-to-RGBA |
|       10140000h  Yes     A11/A9  CONFIG11 Registers                   |
|       10141000h  Yes     A11/A9  CONFIG11 Registers                   |
|       10142000h  Yes     A11/A9  SPI Registers      SPI Bus1 (Tsc)    |
|       10143000h  Yes     A11/A9  SPI Registers      SPI Bus2 (unused) |
|       101                                                             |
| 44000h  Yes     A11/A9  I2C Registers      I2C Bus1 (for 3DS devices) |
|                                                                       |
|     10145000h  Yes     A11/A9  CODEC Registers    ? aka I2S registers |
|       10146000h  Yes     A11/A9  HID Registers      Keypad            |
|       10147000h  Yes     A11/A9  GPIO Registers                       |
|       1014                                                            |
| 8000h  Yes     A11/A9  I2C Registers      I2C Bus2 (for 3DS gimmicks) |
|       10160000                                                        |
| h  Yes     A11/A9  SPI Registers      SPI Bus0 (Pwrman,WifiFlash,Tsc) |
|       101                                                             |
| 61000h  Yes     A11/A9  I2C Registers      I2C Bus0 (for DSi devices) |
|       10162000h  Yes     A11/A9  MIC Registers      Microphone        |
|       10163000h  Yes     A11/A9  PXI Registers      aka IPC           |
|       1                                                               |
| 0164000h  Yes     A9/A11  NTRCARD Registers  ROM Cart in NDS/DSi mode |
|       10165000                                                        |
| h  Yes     A11/A9  MP Registers       NDS-Wifi WIFIWAITCNT(10165206h) |
|       10170000                                                        |
| h  Yes     A11/A9  MP Registers       NDS-Wifi WS0 Area (8000h bytes) |
|       10178000                                                        |
| h  Yes     A11/A9  MP Registers       NDS-Wifi WS1 Area (8000h bytes) |
|                                                                       |
|     10180000h                                     (end of above area) |
+-----------------------------------------------------------------------+
```


**ARM11-only Registers**

```
+-----------------------------------------------------------------------+
|       10200000h  Yes     A11     CDMA               DMA               |
|       10201000h  Yes     A11     FCRAM Registers    FCRAM Control     |
|       10202000h  Yes     A11     LCD Registers      LCD               |
|                                                                       |
|   10203000h  Yes     A11     DSP Registers      Teak DSP (if enabled) |
|       10204000h  No      A11     UNKNOWN            New3DS: ?         |
|       10205000h  ?       -       N/A ?              ?                 |
|       10206000h  No      A11     CDMA               New3DS: DMA       |
|       10207                                                           |
| 000h  No      A11     MVD Registers      New3DS: Movie Decoder or so? |
|       1020F000h  Yes     A11     AXI                ?                 |
|       1                                                               |
| 0300000h  Yes     A11     FIFO? debug?  Maybe debug wifi FIFOs or so? |
|                                                                       |
|     10301000h  Yes     A11     FIFO HASH (SHA)          contains FIFO |
|       10302000h  Yes     A11     FIFO Y2R_0                           |
|       10310000h  Yes     A11     FIFO LGYFB_0                         |
|       10311000h  Yes     A11     FIFO LGYFB_1                         |
|                                                                       |
|   10320000h  Yes     A11     FIFO Camera Bus 0 (20h-word window FIFO) |
|                                                                       |
|   10321000h  Yes     A11     FIFO Camera Bus 1 (20h-word window FIFO) |
|       103220                                                          |
| 00h  Yes     A11     FIFO? wifi??  Maybe contains DATA32 FIFOs or so? |
|       10323000                                                        |
| h  ?       ?       data abort (maybe SDIO FIFO for 10123000h, if any) |
|       10330000                                                        |
| h  No      A11     FIFO L2B_0     New3DS: L2B_0 FIFO (empty=data_abt) |
|       10331000                                                        |
| h  No      A11     FIFO L2B_1     New3DS: L2B_1 FIFO (empty=data_abt) |
|       10332000h  No      A11     FIFO MVD Y2R_1 New3DS: MVD Y2R FIFO  |
|       10400000h  Yes     A11     GPU External Registers               |
|       10401000h  Yes     A11     GPU Internal Registers               |
|       17E00000h 100h     A11     MPCore SCU (Snoop Control Unit)      |
|       17E00100h 100h     A11     MPCore CPU Interrupt Interface       |
|       17E00200h 100h     A11     MPCore CPU0 Interrupt Interface ;\   
|       17E0                                                            |
| 0300h 100h     A11     MPCore CPU1 Interrupt Interface ; (aliased for |
|       17E0040                                                         |
| 0h 100h     A11     MPCore CPU2 Interrupt Interface ; debug purposes) |
|       17E00500h 100h     A11     MPCore CPU3 Interrupt Interface ;/   |
|       17E00600h 100h     A11     MPCore CPU Timer and Watchdog        |
|       17E00700h 100h     A11     MPCore CPU0 Timer and Watchdog  ;\   
|       17E0080                                                         |
| 0h 100h     A11     MPCore CPU1 Timer and Watchdog  ; (aliased, too?) |
|       17E00900                                                        |
| h 100h     A11     MPCore CPU2 Timer and Watchdog  ;  <-- N/A in 3DS? |
|       17E00A00                                                        |
| h 100h     A11     MPCore CPU3 Timer and Watchdog  ;/ <-- N/A in 3DS? |
|       17E0                                                            |
| 0B00h 500h     A11     MPCore Reserved (access causes a DECERR abort) |
|       17E01000h 1000h    A11     MPCore Global Interrupt Distributor  |
|                                                                       |
|   17E10000h  No      A11     New3DS: L2C-310 Level 2 Cache Controller |
+-----------------------------------------------------------------------+
```

IO registers starting at physical address 10200000h are not accessible
from the ARM9 (which includes all LCD/GPU registers). It seems IO
registers below physical address 10100000h are not accessible from the
ARM11 bus (=trigger data abort, as so on all unused 1000h-byte areas).

ARM11 kernel virtual address mappings for these registers varies for
different builds. For ARM11 user mode applications you have:

```
+-----------------------------------------------------------------------+
|       physaddr = virtaddr-1EC00000h+10100000h                         |
+-----------------------------------------------------------------------+
```

That is:

```
+-----------------------------------------------------------------------+
|       Physical   Virtual                                              |
|       101xxxxxh  1ECxxxxxh                                            |
|       102xxxxxh  1EDxxxxxh                                            |
+-----------------------------------------------------------------------+
```




