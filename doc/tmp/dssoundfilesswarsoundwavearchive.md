# DS Sound Files - SWAR (Sound Wave Archive)


It is a collection of mono wave (SWAV) samples only (which can be in either PCM8, PCM16 or ADPCM compression).

### SWAR Header

```
+-------------------------------------------------------------------------------------+
|       000h 4     ID "SWAR"                                  ;\                      
|       004h 2     Byte Order    (FEFFh)                      ;                       |
|       006h 2     Version       (0100h)                      ; Main header           |
|       008h 4     Total Filesize (including SWAV's)          ;                       |
|       00Ch 2     Header Size (usually 10h)                  ;                       |
|       00Eh 2     Number of Blocks (usually 1 = DATA)        ;/                      |
|       010h 4     ID "DATA"                                  ;\                      
|       014h 4     Total Filesize, minus 10h                  ;                       |
|       018h 20h   Reserved (0) (for use at runtime)          ; Sub header            |
|       038h 4     Number of SWAV sample blocks               ;                       |
|       03Ch N*4   Offsets to Sample blocks (from SWAR+0)     ;/                      |
|       ..   ..    Sample blocks... starting with Type (0=PCM8, 1=PCM16, 2=IMA-ADPCM) |
+-------------------------------------------------------------------------------------+
```

When extracting single sample block, one can convert them to SWAV files (by inserting an 18h-byte SWAV header).
The sample blocks are usually (always?) stored at increasing offsets (so one can determine the size by computing the distance to next offset; or to filesize for last entry) (alternately, the size can be computed by looking at the Sound Length entry of sample block).



