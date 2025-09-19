# 3DS Video


**LCD Registers**
These registers are used to configure the LCD screens.
- [3DS Video LCD Registers](./3dsvideolcdregisters.md)
Moreover, each screen is having an I2C-bus controller for further
configuration.
- [3DS I2C LCD Screen Controllers](./3dsi2clcdscreencontrollers.md)
And, the MCU has enable flags for LCD Power Supplies and LCD
Backlights.

**GPU Memory and I/O Map**
- [3DS GPU Memory and I/O Map](./3dsgpumemoryandiomap.md)
- [3DS GPU External Register ListSummary](./3dsgpuexternalregisterlistsummary.md)
- [3DS GPU Internal Register ListSummary](./3dsgpuinternalregisterlistsummary.md)

**GPU External Registers (for memory transfers, and framebuf to LCD
output)**
- [3DS GPU External Registers - Memory Control/StatusRegisters](./3dsgpuexternalregistersmemorycontrolstatusregisters.md)
- [3DS GPU External Registers - Top/Bottom Screen and FramebufferSetup](./3dsgpuexternalregisterstopbottomscreenandframebuffersetup.md)
- [3DS GPU External Registers - Memfill andMemcopy](./3dsgpuexternalregistersmemfillandmemcopy.md)

**GPU Internal Registers (PICA200) (for drawing polygons to
colorbuf/depthbuf)**
- [3DS GPU Internal Register Overview](./3dsgpuinternalregisteroverview.md)
- [3DS GPU Internal Registers - CommandLists](./3dsgpuinternalregisterscommandlists.md)
- [3DS GPU Internal Registers - Finalize Interruptregisters](./3dsgpuinternalregistersfinalizeinterruptregisters.md)
- [3DS GPU Internal Registers - Geometry Pipelineregisters](./3dsgpuinternalregistersgeometrypipelineregisters.md)
- [3DS GPU Internal Registers - Shaderregisters](./3dsgpuinternalregistersshaderregisters.md)
- [3DS GPU Internal Registers - Rasterizerregisters](./3dsgpuinternalregistersrasterizerregisters.md)
- [3DS GPU Internal Registers - Framebufferregisters](./3dsgpuinternalregistersframebufferregisters.md)
- [3DS GPU Internal Registers - Texturing registers (GenericTextures)](./3dsgpuinternalregisterstexturingregistersgenerictextures.md)
- [3DS GPU Internal Registers - Texturing registers (ProceduralTexture)](./3dsgpuinternalregisterstexturingregistersproceduraltexture.md)
- [3DS GPU Internal Registers - Texturing registers(./3dsgpuinternalregisterstexturingregistersenvironment.md)
- [3DS GPU Internal Registers - Fragment Lightingregisters](./3dsgpuinternalregistersfragmentlightingregisters.md)
- [3DS GPU Internal Registers - Unknown/Unused/UndocumentedRegisters](./3dsgpuinternalregistersunknownunusedundocumentedregisters.md)
- [3DS GPU Shader Instruction Set - OpcodeSummary](./3dsgpushaderinstructionsetopcodesummary.md)
- [3DS GPU Shader Instruction Set -Blurp](./3dsgpushaderinstructionsetblurp.md)
Misc notes\...
- [3DS GPU Geometry Pipeline](./3dsgpugeometrypipeline.md)
- [3DS GPU Fragment Lighting](./3dsgpufragmentlighting.md)
- [3DS GPU Pitfalls](./3dsgpupitfalls.md)
- [3DS GPU Primitive Engine andShaders](./3dsgpuprimitiveengineandshaders.md)
- [3DS GPU Texture Formats](./3dsgputextureformats.md)
- [3DS GPU Texture Types](./3dsgputexturetypes.md)
There is also some 3DS GPU open source driver called citro3d, but it\'
mostly higher level stuff and would require a lot of reverse engineering
to extract the lower level functionality from it.

**Sample Code**
- [3DS GPU Triangle Drawing SampleCode](./3dsgputriangledrawingsamplecode.md)

**Camera and Video Data Conversion**
- [3DS Video CAM Registers (CameraInput)](./3dsvideocamregisterscamerainput.md)
- [3DS Video Y2R Registers (YUV-to-RGBAConverter)](./3dsvideoy2rregistersyuvtorgbaconverter.md)
- [3DS Video L2B Registers (RGB-to-RGBA Converter)(./3dsvideol2bregistersrgbtorgbaconverternew3ds.md)
- [3DS Video MVD Registers (Movie Decoder or so?)(./3dsvideomvdregistersmoviedecoderorsonew3ds.md)
- [3DS Video LGY Registers (Legacy GBA/NDS Video toFramebuffer)](./3dsvideolgyregisterslegacygbandsvideotoframebuffer.md)



