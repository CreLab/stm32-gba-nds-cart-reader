# 3DS Files - Video Archive (CGFX)


CGFX files exist as standalone files, and can be also found in CBMD
banner archives, usually with LZ11 compression.
CGFX is a container format used to store graphics resources.

**Overall CGFX Format**
- [3DS Files - Video Archive (CGFX Header, Blocks,DICTs)](./3dsfilesvideoarchivecgfxheaderblocksdicts.md)

**CGFX Sections**
- [3DS Files - Video Archive (CGFX_00h - CMDLModels)](./3dsfilesvideoarchivecgfx00hcmdlmodels.md)
- [3DS Files - Video Archive (CGFX_01h - TXOBTextures)](./3dsfilesvideoarchivecgfx01htxobtextures.md)
- [3DS Files - Video Archive (CGFX_02h - LUTS Look-upTables)](./3dsfilesvideoarchivecgfx02hlutslookuptables.md)
- [3DS Files - Video Archive (CGFX_04h - SHDRShaders)](./3dsfilesvideoarchivecgfx04hshdrshaders.md)
- [3DS Files - Video Archive (CGFX_05h - CCAMCameras)](./3dsfilesvideoarchivecgfx05hccamcameras.md)
- [3DS Files - Video Archive (CGFX_06h - CFLT/CHLT/CALTLights)](./3dsfilesvideoarchivecgfx06hcfltchltcaltlights.md)
- [3DS Files - Video Archive (CGFX_08h - CENVEnvironments)](./3dsfilesvideoarchivecgfx08hcenvenvironments.md)
- [3DS Files - Video Archive (CGFX_09h,0Ah,0Dh - CANMAnimations)](./3dsfilesvideoarchivecgfx09h0ah0dhcanmanimations.md)
- [3DS Files - Video Archive (CGFX_0Eh,0Fh - PEMTEmitters/Particles)](./3dsfilesvideoarchivecgfx0eh0fhpemtemittersparticles.md)

**Unknown CGFX Sections**
These do reportedly exist\... somewhere? Unknown which files do actuall
have such sections.
- 3DS Files - Video Archive (CGFX_03h - ???? Materials)
- 3DS Files - Video Archive (CGFX_07h - CFOG? Fogs)
- 3DS Files - Video Archive (CGFX_0Bh - ???? Visibility animations)
- 3DS Files - Video Archive (CGFX_0Ch - ???? Camera animations)
The Materials are all-unknown. The Fogs are reportedly called CFOG, but
anything else is unknown. The two animation types might use CANM format
like the other three animation types, but that\'s just guessed.

**Skeleton data (uh, what? where?)**
Each entry is E0h bytes in length and organized this way:

```
+-----------------------------------------------------------------------+
|       00h 4     Offset (self relative) to name symbol                 |
|       04h 4     ?                                                     |
|       08h 4     Joint ID                                              |
|       0Ch 4     Parent joint ID                                       |
|       10h 4     Signed offset (self-relative) to parent joint         |
|       14h 18h   unknown/unspecified                                   |
|       2Ch 0Ch   Angle vector (floats, x, y, z)                        |
|       38h 0Ch   Position vector (floats, x, y, z)                     |
|       44h 30h   Transformation matrix (4x3)                           |
|       74h 30h   Identity matrix ? (4x3)                               |
|       A4h 1Ch   unknown/unspecified                                   |
+-----------------------------------------------------------------------+
```

Each entry stores the joint transformation data twice; once as
angle/position vectors and once as a transformation matrix. Each entry
also stores a second matrix which appears to always be identity(?)

**Tools**

```
+-----------------------------------------------------------------------+
|       Every File Explorer                                             |
|       Ohana3DS and its forks                                          |
|       SPICA                                                           |
+-----------------------------------------------------------------------+
```


**Links**
Another CGFX Format Description (Archived Page):
<http://florian.nouwt.com/wiki/index.php/CGFX_(File_Format)>

```
+-----------------------------------------------------------------------+
|                                                                       |
|   https://web.archive.org/web/20150511211029/http://florian.nouwt.com |
|       /wiki/index.php/CGFX_(File_Format)                              |
+-----------------------------------------------------------------------+
```




