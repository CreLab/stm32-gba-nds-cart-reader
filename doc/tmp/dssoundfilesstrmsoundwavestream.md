# DS Sound Files - STRM (Sound Wave Stream)


It is an individual mono/stereo wave file (PCM8, PCM16 or ADPCM) (eg. used in Ultimate Spiderman rom:\\sound\\sound_stream.sdat).

### STRM Header

```
+-----------------------------------------------------------------------------------+
|       000h 4     ID "STRM"                                          ;\            
|       004h 2     Byte Order    (FEFFh)                              ;             |
|       006h 2     Version       (0100h)                              ; Main header |
|       008h 4     Total Filesize                                     ;             |
|       00Ch 2     Header Size (usually 10h)                          ;             |
|       00Eh 2     Number of Blocks (usually 2 = HEAD+DATA)           ;/            |
|       010h 4     ID "HEAD"                                          ;\            
|       014h 4     Size of HEAD structure (uh, this is... 50h?)       ;             |
|       018h 1     Type       (0=PCM8, 1=PCM16, 2=IMA-ADPCM)          ; Sub header  |
|       019h 1     Loop flag  (?=TRUE|FALSE)  ;uh?                    ;             |
|       01Ah 1     Channels   (?=What)        ;mono/stereo?           ;             |
|       01Bh 1     Unknown    (always 0)                              ;             |
|       01Ch 2     Sampling Rate (perhaps resampled from original)    ;             |
|       01Eh 2     Time (1.0 / rate * ARM7_CLOCK / 32)                ;             |
|                    [ARM7_CLOCK: 33.513982MHz/2 = 1.6756991e7]       ;             |
|       020h 4     Loop Offset (samples)                              ;             |
|       024h 4     Number of Samples                                  ;             |
|       028h 4     Wave Data Offset (always 68h)                      ;             |
|       02Ch 4     Number of Blocks       (per what?)                 ;             |
|       030h 4     Block Length           (per Channel)               ;             |
|       034h 4     Samples Per Block      (per Channel)               ;             |
|       038h 4     Last Block Length      (per Channel)               ;             |
|       03Ch 4     Samples Per Last Block (per Channel)               ;             |
|       040h 20h   Reserved (always 0)                                ;/            |
|       060h 4     ID "DATA"                                          ;\Data header 
|       064h 4     Data Size (8+N ?)                                  ;/            |
|       068h N     Wave Data blocks...                                ;-Sample data |
+-----------------------------------------------------------------------------------+
```

Mono blocks are ordered: Block1, Block2, Block3, etc.
Stereo blocks are ordered: LeftBlock1, RightBlock1, LeftBlock2, etc.



