# DS Sound Files - SSAR (Sound Sequence Archive)


It is a collection of SSEQ sequences (mainly for relative short sound effects) (longer sequences like music are usually stored in separate SSEQ files instead of in SSAR archives).

### SSAR Header

```
+---------------------------------------------------------------------------+
|       000h 4     ID "SSAR"                                  ;\            
|       004h 2     Byte Order    (FEFFh)                      ;             |
|       006h 2     Version       (0100h)                      ; Main header |
|       008h 4     Total Filesize                             ;             |
|       00Ch 2     Header Size (usually 10h)                  ;             |
|       00Eh 2     Number of Blocks (usually 1 = DATA)        ;/            |
|       010h 4     ID "DATA"                                  ;\            
|       014h 4     Total Filesize, minus 10h                  ;             |
|       018h 4     Offset to data (from SSAR+0) (20h+N*0Ch)   ; Sub header  |
|       01Ch 4     Number of records                          ;             |
|       020h N*0Ch Records (12 bytes each)                    ;/            |
|       ..   ..    data... unknown content? alike SSEQ?       ;-            |
+---------------------------------------------------------------------------+
```


### SSAR Records

```
+------------------------------------------------------------------------------+
|       000h 4   nOffset    ;relative offset of the archived SEQ file,         |
|                                absolute offset = nOffset + SSAR::nDataOffset |
|       004h 2   bnk        ;bank                                              |
|       006h 1   vol        ;volume                                            |
|       007h 1   cpr        ;channel pressure                                  |
|       008h 1   ppr        ;polyphonic pressure                               |
|       009h 1   ply        ;play                                              |
|       00Ah 2   reserved (0)                                                  |
+------------------------------------------------------------------------------+
```


### SSAR Data (addressed via relative offset in above 0Ch-byte record)

```
+-----------------------------------------------------------------------+
|       data... unknown content? alike SSEQ?                            |
+-----------------------------------------------------------------------+
```


NB. Archived SSEQ files are not stored in sequence (order). So Rec\[0\].nOffset may point to 0x100 but Rec\[1\].nOffset points to 0x40.

NB. Archived SSEQ files cannot be readily extracted from SSAR file because data in one SSEQ may \'call\' data in other SSEQ.



