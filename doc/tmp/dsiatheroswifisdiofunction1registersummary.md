# DSi Atheros Wifi SDIO Function 1 Register Summary


### Atheros SDIO \"Function 1\" area

```
+-------------------------------------------------------------------------------+
|       1:00000..000FF  Mbox0 (100h bytes) <--DMA----------> Internal 256MB     |
|       1:00100..001FF  Mbox1 (100h bytes) <--DMA----------> Internal 256MB     |
|       1:00200..002FF  Mbox2 (100h bytes) <--DMA----------> Internal 256MB     |
|       1:00300..003FF  Mbox3 (100h bytes) <--DMA----------> Internal 256MB     |
|       1:00400..005FF  Control Registers  <--WINDOW_DATA--> Internal 256MB     |
|       1:00600..007FF  CIS Window; Window ---huh???-------> Internal 256MB ??? |
|       1:00800..00FFF  Mbox0 Alias (bigger 800h bytes alias)                   |
|       1:01000..017FF  Mbox1 Alias (bigger 800h bytes alias)                   |
|       1:01800..01FFF  Mbox2 Alias (bigger 800h bytes alias)                   |
|       1:02000..027FF  Mbox3 Alias (bigger 800h bytes alias)                   |
|       1:02800..03FFF  Extra Mbox0 Alias "for future usage" (1800h bytes)      |
|       1:04000..1FFFF  Unspecified                                             |
+-------------------------------------------------------------------------------+
```


### mbox_wlan_host_reg.h \-- in SDIO Function 1 address space

```
+-------------------------------------------------------------------------------------+
|       1:00000h 100h    Mbox0 (100h bytes) <--DMA----------> Internal 256MB          |
|       1:00100h 100h    Mbox1 (100h bytes) <--DMA----------> Internal 256MB          |
|       1:00200h 100h    Mbox2 (100h bytes) <--DMA----------> Internal 256MB          |
|       1:00300h 100h    Mbox3 (100h bytes) <--DMA----------> Internal 256MB          |
|       1:00400h 1       HOST_INT_STATUS    (R)                                       |
|       1:00401h 1       CPU_INT_STATUS     (R/W)                                     |
|       1:00402h 1       ERROR_INT_STATUS   (R/W)                                     |
|       1:00403h 1       COUNTER_INT_STATUS (R)                                       |
|       1:00404h 1       MBOX_FRAME         (R)                                       |
|       1:00405h 1       RX_LOOKAHEAD_VALID (R)                                       |
|       1:00406h 1       HOST_INT_STATUS2             ;\GMBOX related, hw4/hw6 only   
|       1:00407h 1       GMBOX_RX_AVAIL               ;/                              |
|       1:00408h 1x4     RX_LOOKAHEAD0[0..3] (R)                                      |
|       1:0040Ch 1x4     RX_LOOKAHEAD1[0..3] (R)                                      |
|       1:00410h 1x4     RX_LOOKAHEAD2[0..3] (R)                                      |
|       1:00414h 1x4     RX_LOOKAHEAD3[0..3] (R)                                      |
|       1:00418h 1       (HOST_)INT_STATUS_ENABLE  (R/W)                              |
|       1:00419h 1       CPU_INT_STATUS_ENABLE     (R/W)                              |
|       1:0041Ah 1       ERROR_(INT_)STATUS_ENABLE (R/W)                              |
|       1:0041Bh 1       COUNTER_INT_STATUS_ENABLE (R/W)                              |
|       1:0041Ch 1x4     PAD1                 (FFh,6Eh,D7h,BFh - maybe some mirror?)  |
|       1:00420h 1x8     COUNT[0..7]         (R/W)                                    |
|       1:00428h 1x24    PAD2                                                         |
|         00428h 4       -   (mirror of 1:00468h?)                                    |
|         0042Ch 4       -   (mirror of 1:0041Ch?)                                    |
|         00430h 4       -   (mirror of 1:00410h?)                                    |
|         00434h 4       -   (mirror of 1:00...h?)                                    |
|         00438h 4       -   (mirror of 1:00468h?)                                    |
|         0043Ch 4       -   (mirror of 1:0041Ch?)                                    |
|       1:00440h 4x8     COUNT_DEC[0..7]     (R, or Write=any)                        |
|       1:00460h 1x8     SCRATCH[0..7]       (R/W)                                    |
|       1:00468h 1       FIFO_TIMEOUT        (R/W)                                    |
|       1:00469h 1       FIFO_TIMEOUT_ENABLE (R/W)                                    |
|       1:0046Ah 1       DISABLE_SLEEP       (R/W)                                    |
|       1:0046Bh 1x3     -                                                            |
|       1:0046Eh 1       LOCAL_BUS_ENDIAN    (R/W) (AR6001 only, not hw2/hw4/hw6)     |
|       1:0046Fh 1       -                                                            |
|       1:00470h 1       LOCAL_BUS           (R and R/W)                              |
|       1:00471h 1x1     PAD4                                                         |
|       1:00472h 1       INT_WLAN            (R/W)                                    |
|       1:00473h 1x1     PAD5                                                         |
|       1:00474h 4       WINDOW_DATA         (R/W)    ;\                              
|       1:00478h 4       WINDOW_WRITE_ADDR   (W)      ;                               |
|       1:0047Ch 4       WINDOW_READ_ADDR    (W)      ;/                              |
|       1:00480h 1       HOST_CTRL_SPI_CONFIG (R/W)                                   |
|       1:00481h 1       HOST_CTRL_SPI_STATUS (R/W)                                   |
|       1:00482h 1       NON_ASSOC_SLEEP_EN ;hw2/hw4/hw6 (but didn't exist on AR6001) |
|       1:00483h 1       CPU_DBG_SEL                    ;\DBG, hw4/hw6 only           
|       1:00484h 1x4     CPU_DBG[0..3]                  ;/                            |
|       1:00488h 1       (HOST_)INT_STATUS2_ENABLE (R/W);\                            
|       1:00489h 1x7     PAD6                           ; GMBOX related, hw4/hw6 only |
|       1:00490h 1x8     GMBOX_RX_LOOKAHEAD[0..7]       ;                             |
|       1:00498h 1       GMBOX_RX_LOOKAHEAD_MUX         ;/                            |
|       1:00499h 1x359   PAD7                                                         |
|       1:00600h 1x512   CIS_WINDOW[0..511]   (R/W?!)       ;SDIO 0:01000h..0:011FFh  |
|       1:00800h 800h    Mbox0 Alias (bigger 800h bytes alias)                        |
|       1:01000h 800h    Mbox1 Alias (bigger 800h bytes alias)                        |
|       1:01800h 800h    Mbox2 Alias (bigger 800h bytes alias)                        |
|       1:02000h 800h    Mbox3 Alias (bigger 800h bytes alias)                        |
|       1:02800h 1800h   Extra Mbox0 Alias "for future usage" (1800h bytes)           |
|       1:04000h 1C000h  Unspecified                                                  |
+-------------------------------------------------------------------------------------+
```




