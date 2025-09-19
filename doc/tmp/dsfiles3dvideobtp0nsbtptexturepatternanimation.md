# DS Files - 3D Video BTP0 (.NSBTP Texture Pattern Animation)


Allows to use different textures/palettes in each frame (ie. to use a short \"movie clip\" instead of a static \"bitmap\" as texture).

### BTP0 Header (in .NSBTP files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BTP0" (Texture Pattern Animation)                 |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (1)                                           |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=PAT0)                             |
|       010h 4     Offset from BTP0 to PAT0 Chunk                        |
+------------------------------------------------------------------------+
```


### PAT0 Chunk

```
+----------------------------------------------------------------------------+
|       000h 4     Chunk ID "PAT0" (Pattern Block)                           |
|       004h 4     Chunk Size                                                |
|       008h ..    Dict (with 32bit offsets from PAT0 to Pattern Animations) |
|       ...  ..    Pattern Animation(s)                                      |
+----------------------------------------------------------------------------+
```


### Pattern Animation

```
+-----------------------------------------------------------------------------------+
|       000h 4     ID "M",00h,"PT" (nicknamed "M.PT")                               |
|       004h 2     Unknown (can be 08h or 32h)   ;rather NOT Number of Frames?      |
|       006h 1     Number of Texture Names (Y)                                      |
|       007h 1     Number of Palette Names (Z)                                      |
|       008h 2     Offset from "M.PT" to Texture Names                              |
|       00Ah 2     Offset from "M.PT" to Palette Names                              |
|       00Ch ..    Dict (with 8-byte Track entries; includes offsets to Key Frames) |
|       ...  X*4   Key Frames                                                       |
|       ...  Y*10h Texture Names (each 10h-byte ASCII, zeropadded)                  |
|       ...  Z*10h Palette Names (each 10h-byte ASCII, zeropadded)                  |
+-----------------------------------------------------------------------------------+
```


### Track Entries (in Dict)

```
+------------------------------------------------------------------------------------+
|       000h 4     Number of Keyframes                                               |
|       004h 2     Unknown (1000h or 00F5h) (maybe loop flags and/or framerate etc.) |
|       006h 2     Offset from "M.PT" to Keyframe(s)                                 |
+------------------------------------------------------------------------------------+
```


### Keyframe Entries

```
+-----------------------------------------------------------------------+
|       000h 2     Frame Number (increasing 0000h..NumKeyFrames-1)      |
|       002h 1     Index into Texture Names                             |
|       003h 1     Index into Palette Names                             |
+-----------------------------------------------------------------------+
```




