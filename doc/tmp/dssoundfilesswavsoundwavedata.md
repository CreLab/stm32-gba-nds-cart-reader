# DS Sound Files - SWAV (Sound Wave Data)


### SWAV Header (present only in standalone SWAV files) (not in SWAR archives)

```
+---------------------------------------------------------------------------+
|       000h 4     ID "SWAV"                                  ;\            
|       004h 2     Byte Order    (FEFFh)                      ;             |
|       006h 2     Version       (0100h)                      ; Main header |
|       008h 4     Total Filesize                             ;             |
|       00Ch 2     Header Size (usually 10h)                  ;             |
|       00Eh 2     Number of Blocks (usually 1 = DATA)        ;/            |
|       010h 4     ID "DATA"                                  ;\Sub header  
|       014h 4     Total Filesize, minus 10h                  ;/            |
|       018h ..    Sample block (see below)                                 |
+---------------------------------------------------------------------------+
```

Note: System Flaw has a lot of SWAV files (instead of using SWAR archives).

### Sample Block Format (present in SWAV files and SWAR archives)

```
+-------------------------------------------------------------------------------+
|       000h 1    WaveType (0=PCM8, 1=PCM16, 2=IMA-ADPCM)                       |
|       001h 1    Loop flag = TRUE|FALSE   ;uh?                                 |
|       002h 2    Sampling Rate                                                 |
|       004h 2    Time (ARM7_CLOCK / nSampleRate)                               |
|                     [ARM7_CLOCK: 33.513982MHz/2 = 1.6756991 E +7]             |
|       006h 2    Loop Offset, in 4-byte units                                  |
|       008h 4    Sound Length, in 4-byte units (exluding ADPCM header, if any) |
|       00Ch ...  Data... (samples) (with 32bit header in case of ADPCM)        |
+-------------------------------------------------------------------------------+
```




