# 3DS DMA Registers


**ARM9 NDMA**
- [3DS DMA - NDMA Registers](./3dsdmandmaregisters.md)

**ARM9 XDMA and ARM11 CDMA**
- [3DS DMA - Corelink DMA PeripheralIDs](./3dsdmacorelinkdmaperipheralids.md)
- [3DS DMA - Corelink DMA RegisterSummary](./3dsdmacorelinkdmaregistersummary.md)
- [3DS DMA - Corelink DMA - Interrupt and Fault StatusRegisters](./3dsdmacorelinkdmainterruptandfaultstatusregisters.md)
- [3DS DMA - Corelink DMA - Internal State StatusRegisters](./3dsdmacorelinkdmainternalstatestatusregisters.md)
- [3DS DMA - Corelink DMA - Transfer Start (aka \"Debug\Registers)](./3dsdmacorelinkdmatransferstartakadebugregisters.md)
- [3DS DMA - Corelink DMA - Fixed Configuration and IDRegisters](./3dsdmacorelinkdmafixedconfigurationandidregisters.md)
- [3DS DMA - Corelink DMA OpcodeSummary](./3dsdmacorelinkdmaopcodesummary.md)
The ARM Corelink DMA hardware is documented in

```
+-----------------------------------------------------------------------+
|       DDI0424                                                         |
| D_dma330_r1p2_trm        - DMA controller (also covers r0p0 and r1p1) |
|       IHI0022D amba axi_specification - Memory (ARCACHE, ARPROT etc.) |
+-----------------------------------------------------------------------+
```


**ARM11 GPU DMA**
- [3DS GPU External Registers - Memfill andMemcopy](./3dsgpuexternalregistersmemfillandmemcopy.md)
The GPU does probably also have DMA(s) for reading things like command
lists, and texture data, and for rendering to framebuffer.



