# DS DMA Transfers


The DS includes four DMA channels for each CPU (ie. eight channels in total), which are working more or less the same as on GBA:
- [GBA DMA Transfers](./gbadmatransfers.md)
All NDS9 and NDS7 DMA Registers are R/W. The gamepak bit (Bit 27) has been removed (on the NDS9 the bit is used to expand the mode setting to 3bits).

### NDS9 DMA
Word count of all channels is expanded to 21bits (max 1..1FFFFFh units, or 0=200000h units), and SAD/DAD registers for all channels support ranges of 0..0FFFFFFEh. The transfer modes (DMACNT Bit27-29) are:

```
+-----------------------------------------------------------------------+
|       0  Start Immediately                                            |
|       1  Start at V-Blank                                             |
|       2  Start at H-Blank (paused during V-Blank)                     |
|       3  Synchronize to start of display                              |
|       4  Main memory display                                          |
|       5  DS Cartridge Slot                                            |
|       6  GBA Cartridge Slot                                           |
|       7  Geometry Command FIFO                                        |
+-----------------------------------------------------------------------+
```


### NDS7 DMA
Word Count, SAD, and DAD are R/W, aside from that they do have the same restrictions as on GBA (max 4000h or 10000h units, some addresses limited to 0..07FFFFFEh). DMACNT Bit27 is unused on NDS7. The transfer modes (DMACNT Bit28-29) are:

```
+-----------------------------------------------------------------------+
|       0  Start Immediately                                            |
|       1  Start at V-Blank                                             |
|       2  DS Cartridge Slot                                            |
|       3  DMA0/DMA2: Wireless interrupt, DMA1/DMA3: GBA Cartridge Slot |
+-----------------------------------------------------------------------+
```


### 40000E0h - NDS9 only - DMA0FILL - DMA 0 Filldata (R/W)
### 40000E4h - NDS9 only - DMA1FILL - DMA 1 Filldata (R/W)
### 40000E8h - NDS9 only - DMA2FILL - DMA 2 Filldata (R/W)
### 40000ECh - NDS9 only - DMA3FILL - DMA 3 Filldata (R/W)

```
+-----------------------------------------------------------------------+
|       Bit0-31 Filldata                                                |
+-----------------------------------------------------------------------+
```

The DMA Filldata registers contain 16 bytes of general purpose WRAM, intended to be used as fixed source addresses for DMA memfill operations.
This is useful because DMA cannot read from TCM, and reading from Main RAM would require to recurse cache & write buffer.
The DMA Filldata is used with Src=Fixed and SAD=40000Exh (which isn\'t optimal because it\'s doing repeated reads from SAD, and, for that reason, a memfill via STMIA opcodes can be faster than DMA; the DSi\'s new NDMA channels are providing a faster fill method with Src=Fill and SAD=Unused).

### NDS7 Sound DMA
The NDS additionally includes 16 Sound DMA channels, plus 2 Sound Capture DMA channels (see Sound chapter). The priority of these channels is unknown.

### NDS9 Cache, Writebuffer, DTCM, and ITCM
Cache and tightly coupled memory are connected directly to the NDS9 CPU, without using the system bus. So that, DMA cannot access DTCM/ITCM, and access to cached memory regions must be handled with care: Drain the writebuffer before DMA-reads, and invalidate the cache after DMA-writes. See,
- [ARM CP15 System Control Coprocessor](./armcp15systemcontrolcoprocessor.md)
The CPU can be kept running during DMA, provided that it is accessing only TCM (or cached memory), otherwise the CPU is halted until DMA finishes.
Respectively, interrupts executed during DMA will usually halt the CPU (unless the IRQ handler uses only TCM and cache; the IRQ vector at FFFF00xxh must be cached, or relocated to ITCM at 000000xxh, and the IRQ handler may not access IE, IF, or other I/O ports).

### NDS Sequential Main Memory DMA
Main RAM has different access time for sequential and non-sequential access. Normally DMA uses sequential access (except for the first word), however, if the source and destination addresses are both in Main RAM, then all accesses become non-sequential. In that case it would be faster to use two DMA transfers, one from Main RAM to a scratch buffer in WRAM, and one from WRAM to Main RAM.



