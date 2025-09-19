# DS Files - 3D Video BTA0 (.NSBTA Texture Coordinate Animation)


Allows Texture scrolling\... and maybe also texture scale/rotate?

### BTA0 Header (in .NSBTA files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BTA0" (Texture Animation)                         |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (1)                                           |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=SRT0)                             |
|       010h 4     Offset from BTA0 to SRT0 Chunk                        |
+------------------------------------------------------------------------+
```


### SRT0 Chunk

```
+----------------------------------------------------------------------------+
|       000h 4     Chunk ID "SRT0" (maybe short for Scale/Rotate/Translate?) |
|       004h 4     Chunk Size                                                |
|       008h ..    Dict (with 32bit offsets from SRT0 to Animations)         |
|       ...  ..    Animation(s)                                              |
+----------------------------------------------------------------------------+
```


### Animation

```
+-----------------------------------------------------------------------+
|       000h 4     ID "M",00h,"AT" (nicknamed "M.AT")                   |
|       004h 2     Unknown (can be 3Bh)   ;is that Number of Frames?    |
|       006h 2     Unknown (can be 0)                                   |
|       008h ..    Dict (with 28h-byte Track entries)                   |
|       ...  ..    Key Frames                                           |
+-----------------------------------------------------------------------+
```


### Track Entries (in Dict)

```
+---------------------------------------------------------------------------------+
|       000h 8     Channel 0 - unknown, maybe Scale U       ;\                    
|       008h 8     Channel 1 - unknown, maybe Scale V       ; maybe scale/rotate? |
|       010h 8     Channel 2 - unknown, maybe Rotate Matrix ;/                    |
|       018h 8     Channel 3 - Translation U                ;\texture scrolling   
|       020h 8     Channel 4 - Translation V                ;/                    |
+---------------------------------------------------------------------------------+
```


### Channel (within Tracks in Dict)

```
+------------------------------------------------------------------------------------+
|       000h 2     Number of Keyframes (can be 3Bh)                                  |
|       002h 2     Flags (1000h, 2000h or 3000h) (maybe loop flags and/or rate?)     |
|       004h 4     When Flags=1000h: Offset from "M.AT" to Keyframe(s)               |
|                  When Flags=2000h: Unknown (10000000h)   ;\maybe disable, or fixed 
|                  When Flags=3000h: Unknown (1000h or 0)  ;/setting for all frames? |
+------------------------------------------------------------------------------------+
```


### Keyframe Entries

```
+-----------------------------------------------------------------------+
|       000h 2     Value (for Translation: fixed point 1.10.5)          |
+-----------------------------------------------------------------------+
```




