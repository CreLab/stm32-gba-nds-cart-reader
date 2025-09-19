# 3DS Video


### LCD Registers
These registers are used to configure the LCD screens.
- [3DS Video LCD Registers](./3dsvideolcdregisters.md)
Moreover, each screen is having an I2C-bus controller for further configuration.
- [3DS I2C LCD Screen Controllers](./3dsi2clcdscreencontrollers.md)
And, the MCU has enable flags for LCD Power Supplies and LCD Backlights.

### GPU Memory and I/O Map
- [3DS GPU Memory and I/O Map](./3dsgpumemoryandiomap.md)
- [3DS GPU External Register List Summary](./3dsgpuexternalregisterlistsummary.md)
- [3DS GPU Internal Register List Summary](./3dsgpuinternalregisterlistsummary.md)

### GPU External Registers (for memory transfers, and framebuf to LCD output)
- [3DS GPU External Registers - Memory Control/Status Registers](./3dsgpuexternalregistersmemorycontrolstatusregisters.md)
- [3DS GPU External Registers - Top/Bottom Screen and Framebuffer Setup](./3dsgpuexternalregisterstopbottomscreenandframebuffersetup.md)
- [3DS GPU External Registers - Memfill and Memcopy](./3dsgpuexternalregistersmemfillandmemcopy.md)

### GPU Internal Registers (PICA200) (for drawing polygons to colorbuf/depthbuf)
- [3DS GPU Internal Register Overview](./3dsgpuinternalregisteroverview.md)
- [3DS GPU Internal Registers - Command Lists](./3dsgpuinternalregisterscommandlists.md)
- [3DS GPU Internal Registers - Finalize Interrupt registers](./3dsgpuinternalregistersfinalizeinterruptregisters.md)
- [3DS GPU Internal Registers - Geometry Pipeline registers](./3dsgpuinternalregistersgeometrypipelineregisters.md)
- [3DS GPU Internal Registers - Shader registers](./3dsgpuinternalregistersshaderregisters.md)
- [3DS GPU Internal Registers - Rasterizer registers](./3dsgpuinternalregistersrasterizerregisters.md)
- [3DS GPU Internal Registers - Framebuffer registers](./3dsgpuinternalregistersframebufferregisters.md)
- [3DS GPU Internal Registers - Texturing registers (Generic Textures)](./3dsgpuinternalregisterstexturingregistersgenerictextures.md)
- [3DS GPU Internal Registers - Texturing registers (Procedural Texture)](./3dsgpuinternalregisterstexturingregistersproceduraltexture.md)
- [3DS GPU Internal Registers - Texturing registers (Environment)](./3dsgpuinternalregisterstexturingregistersenvironment.md)
- [3DS GPU Internal Registers - Fragment Lighting registers](./3dsgpuinternalregistersfragmentlightingregisters.md)
- [3DS GPU Internal Registers - Unknown/Unused/Undocumented Registers](./3dsgpuinternalregistersunknownunusedundocumentedregisters.md)
- [3DS GPU Shader Instruction Set - Opcode Summary](./3dsgpushaderinstructionsetopcodesummary.md)
- [3DS GPU Shader Instruction Set - Blurp](./3dsgpushaderinstructionsetblurp.md)
Misc notes\...
- [3DS GPU Geometry Pipeline](./3dsgpugeometrypipeline.md)
- [3DS GPU Fragment Lighting](./3dsgpufragmentlighting.md)
- [3DS GPU Pitfalls](./3dsgpupitfalls.md)
- [3DS GPU Primitive Engine and Shaders](./3dsgpuprimitiveengineandshaders.md)
- [3DS GPU Texture Formats](./3dsgputextureformats.md)
- [3DS GPU Texture Types](./3dsgputexturetypes.md)
There is also some 3DS GPU open source driver called citro3d, but it\'s mostly higher level stuff and would require a lot of reverse engineering to extract the lower level functionality from it.

### Sample Code
- [3DS GPU Triangle Drawing Sample Code](./3dsgputriangledrawingsamplecode.md)

### Camera and Video Data Conversion
- [3DS Video CAM Registers (Camera Input)](./3dsvideocamregisterscamerainput.md)
- [3DS Video Y2R Registers (YUV-to-RGBA Converter)](./3dsvideoy2rregistersyuvtorgbaconverter.md)
- [3DS Video L2B Registers (RGB-to-RGBA Converter) (New3DS)](./3dsvideol2bregistersrgbtorgbaconverternew3ds.md)
- [3DS Video MVD Registers (Movie Decoder or so?) (New3DS)](./3dsvideomvdregistersmoviedecoderorsonew3ds.md)
- [3DS Video LGY Registers (Legacy GBA/NDS Video to Framebuffer)](./3dsvideolgyregisterslegacygbandsvideotoframebuffer.md)



