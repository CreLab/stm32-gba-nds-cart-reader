# DS Files - 3D Video BMA0 (.NSBMA Material Animation)


Allows to animate \"Material\" whatever that means\... maybe colors/lights?

### BMA0 Header (in .NSBMA files)

```
+------------------------------------------------------------------------+
|       000h 4     ID "BMA0" (Material Animation)                        |
|       004h 2     Byte Order (FEFFh)                                    |
|       006h 2     Version (1)                                           |
|       008h 4     Total Filesize                                        |
|       00Ch 2     Header size, excluding the Chunk offsets (always 10h) |
|       00Eh 2     Number of chunks (1=MAT0)                             |
|       010h 4     Offset from BMA0 to MAT0 Chunk                        |
+------------------------------------------------------------------------+
```


### MAT0 Chunk

```
+----------------------------------------------------------------------------+
|       000h 4     Chunk ID "MAT0" (Material Block)                          |
|       004h 4     Chunk Size                                                |
|       008h ..    Dict (with 32bit offsets from PAT0 to Pattern Animations) |
|       ...  ..    Animation(s)                                              |
+----------------------------------------------------------------------------+
```


### Animations

```
+-----------------------------------------------------------------------+
|       000h 4     ID "M",00h,"AM" (nicknamed "M.AM")                   |
|       004h 2     Unknown (can be 5Ah)   ;is that Number of Frames?    |
|       006h 2     Unknown (can be 3)                                   |
|       008h ..    Dict (with 14h-byte Track entries)                   |
|       ...  ..    Key Frames                                           |
+-----------------------------------------------------------------------+
```


### Track Entries (in Dict)

```
+-------------------------------------------------------------------------------+
|       000h 2     Unknown (40h)   Offset from "M.AM" to Keyframes        ;\    
|       002h 1     Unknown (5Ah)   Number of Keyframes (5Ah*2=B4h bytes)  ; ch0 |
|       003h 1     Unknown (0)     Flags                                  ;/    |
|       004h 2     Unknown (F4h)   Offset from "M.AM" to Keyframes        ;\    
|       006h 1     Unknown (5Ah)   Number of Keyframes (5Ah*2=B4h bytes)  ; ch1 |
|       007h 1     Unknown (0)     Flags                                  ;/    |
|       008h 2     Unknown (0)     Maybe fixed value for all frames?      ;\    
|       00Ah 1     Unknown (5Ah)   Number of Keyframes                    ; ch2 |
|       00Bh 1     Unknown (20h)   Flags (20h=Fixed/Disabled?)            ;/    |
|       00Ch 2     Unknown (0)     Maybe fixed value for all frames?      ;\    
|       00Eh 1     Unknown (5Ah)   Number of Keyframes                    ; ch3 |
|       00Fh 1     Unknown (20h)   Flags (20h=Fixed/Disabled?)            ;/    |
|       010h 2     Unknown (1Fh)   Maybe fixed value for all frames?      ;\    
|       012h 1     Unknown (5Ah)   Number of Keyframes                    ; ch4 |
|       013h 1     Unknown (20h)   Flags (20h=Fixed/Disabled?)            ;/    |
+-------------------------------------------------------------------------------+
```


### Keyframe Entries

```
+-----------------------------------------------------------------------+
|       000h 2     Unknown                                              |
+-----------------------------------------------------------------------+
```




