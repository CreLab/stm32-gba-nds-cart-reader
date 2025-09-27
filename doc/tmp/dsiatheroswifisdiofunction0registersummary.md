# DSi Atheros Wifi SDIO Function 0 Register Summary


### Atheros SDIO \"Function 0\" area

```
+-------------------------------------------------------------------------------------+
|       0:00000 2      Revision       (0011h = CCCRv1.10, SDIOv1.10, SDv1.01)  ;\     
|       0:00002 2      Function       (0202h = Function 1 enabled/ready)       ;      |
|       0:00004 2      Interrupt Flags(0000h = None enabled/pending)           ;      |
|       0:00006 1      Abort/Reset    (00h)                                    ;      |
|       0:00007 1      Bus Interface  (82h = 4bit mode, pulldown=off)          ;      |
|       0:00008 1      Card Capability(17h)                                    ; CCCR |
|       0:00009 3      CIS0 Pointer   (001000h = CIS0 at 0:01000h)             ;      |
|       0:0000C ..       ..suspend..? (zero-filled)                            ;      |
|       0:00010 2      Block Size     (0000h = Function 0 Block Size, variable);      |
|       0:00012 1      Power Control  (03h = supports/uses more than 720mW)    ;      |
|       0:00013 2      Bus Speed      (0000h = Supports only SDR12)            ;      |
|       0:00015 1      Driver Strength(00h)                                    ;      |
|       0:00016 1      Interrupt Ext  (00h = No aysnc IRQ support in 4bit mode);      |
|       0:00017 E9h    Reserved       (zero-filled)                            ;/     |
|       0:00100 2      Interface Type (0000h=Not SDIO standard, no CSA)        ;\     
|       0:00102 1      Power          (00h=No power selection)                 ;      |
|       0:00103 6      Reserved       (zero-filled)                            ;      |
|       0:00109 3      CIS1 Pointer   (001100h = CIS1 at 0:01100h)             ; FBR1 |
|       0:0010C 4      CSA Stuff      (zero-filled, CSA isn't supported)       ;      |
|       0:00110 2      Block Size     (0080h = Function 1 Block Size, variable);      |
|       0:00112 EEh    Reserved       (zero-filled)                            ;/     |
|       0:00200 600h   FBR2..FBR7     (zero-filled)                            ;-FBRn |
|       0:00800 800h   Reserved       (zero-filled)                            ;-N/A  |
|       0:01000         01 03 D9 01 FF    ;DEVICE (D9h=FUNCSPEC,01h=Siz,FFh=End;\     
|       0:01005         20 04 71 02 00 02 ;MANFID (0271h=Atheros, 0200h=AR6002);      |
|       0:0100B         21 02 0C 00       ;FUNCID (0Ch,00h=Standard for SDIO)  ;      |
|       0:0100F         22 04 00 00 08 32 ;FUNCE (0800h=MaxBlkSiz,32h=25Mbit/s); CIS0 |
|       0:01015         1A 05 01 01 00 02 07            ;\       ;CONFIG       ;      
|       0:0101C         1B 08 C1 41 30 30 FF FF 32 00   ; PROM?  ;CFTABLE_ENTRY;      |
|       0:01026         14 00                           ; RAM?   ;NO_LINK      ;      |
|       0:01028..01044  FF-filled (1Dh bytes) ;uh?      ;/       ;END          ;      |
|       0:01045..010FF  00-filled (BBh bytes) ;unused                          ;/     |
|       0:01100         20 04 71 02 00 02 ;MANFID (0271h=Atheros, 0200h=AR6002);\     
|       0:01106         21 02 0C 00     ;FUNCID (0Ch,00h=Standard for SDIO)    ;      |
|       0:0110A         22 2A 01        ;FUNCE                                 ;      |
|       0:0110D          01 11          ;FUNCE WakeUpSupport(01h), v1.1(11h)   ;      |
|       0:0110F          00 00 00 00    ;FUNCE Serial Number (00000000h=None)  ;      |
|       0:01113          00 00 00 00 00 ;FUNCE CSA Stuff (00000000h,00h=None)  ;      |
|       0:01118          00 08          ;FUNCE Max Block Size (0800h)          ; CIS1 |
|       0:0111A          00 00 FF 80    ;FUNCE OCR (80FF0000h)                 ;      |
|       0:0111E          00 00 00       ;FUNCE Operate Min/Avg/Max (00,00,00)  ;      |
|       0:01121          00 01 0A       ;FUNCE Standby Min/Avg/Max (00,01,0A)  ;      |
|       0:01124          00 00 00 00    ;FUNCE Bandwidth Min/Opt (0000h,0000h) ;      |
|       0:01128          00 00          ;FUNCE Timeout Enable-till-Rdy (0000h) ;      |
|       0:0112A          00 00 00 00    ;FUNCE Operation  Avg/Max (0000h,0000h);      |
|       0:0112E          00 01 00 01    ;FUNCE HighCurrentAvg/Max (0100h,0100h);      |
|       0:01132          00 01 00 01    ;FUNCE LowCurrent Avg/Max (0100h,0100h);      |
|       0:01136         80 01 06        ;VENDOR                                ;      |
|       0:01139         81 01 07        ;VENDOR                                ;      |
|       0:0113C         82 01 DF        ;VENDOR                                ;      |
|       0:0113F         FF              ;END                                   ;      |
|       0:01140         01              ;Garbage?                              ;      |
|       0:01141..011FF  00-filled (BFh bytes) ;unused                          ;/     |
|       0:01200..02FFF  mirrors of 01000h..011FFh (CIS0 and CIS1) (1E00h bytes);\N/A  
|       0:03000..       00-filled (.... bytes) ;unused... reserved             ;/     |
+-------------------------------------------------------------------------------------+
```


### Briefly

```
+---------------------------------------------------------------------------------+
|       0:00000         11 00 02 02 00 00 00 82  17 00 10 00 00 00 00 00  ;\      
|       0:00010         00 00 03 00 00 00 00                              ;       |
|       0:00017..000FF  unused (zerofilled)                               ;/      |
|       0:00100         00 00 00 00 00 00 00 00  00 00 11 00 00 00 00 00  ;\      
|       0:00110         80 00                                             ;       |
|       0:00112..00FFF  unused (zerofilled)                               ;/      |
|       0:01000         01 03 D9 01 FF                          ;\                
|       0:01005         20 04 71 02 00 02       ;hif.h: 271h    ;                 |
|       0:0100B         21 02 0C 00                             ;                 |
|       0:0100F         22 04 00 00 08 32                       ;                 |
|       0:01015         1A 05 01 01 00 02 07            ;\      ;                 
|       0:0101C         1B 08 C1 41 30 30 FF FF 32 00   ; PROM? ;                 |
|       0:01026         14 00                           ; RAM?  ;                 |
|       0:01028..01044  FF-filled (1Dh bytes) uh?       ;/      ;                 |
|       0:01045..010FF  00-filled                               ;/                |
|       0:01100         20 04 71 02 00 02                       ;\                
|       0:01106         21 02 0C 00                             ;                 |
|       0:0110A         22 2A 01 01 11 00  00 00 00 00  00 00 00 00  00 08 00 00  |
|       0:0111C               FF 80 00 00  00 00 01 0A  00 00 00 00  00 00 00 00  |
|       0:0112C               00 00 00 01  00 01 00 01  00 01                     |
|       0:01136         80 01 06                                ;                 |
|       0:01139         81 01 07                                ;                 |
|       0:0113C         82 01 DF                                ;                 |
|       0:0113F         FF 01 00                                ;                 |
|       0:01142..011FF  00-filled                               ;/                |
|       0:01200..02FFF  mirrors of 01000..011FF (common cis and function 1 cis) ? |
|       0:03000..       00-filled                                                 |
+---------------------------------------------------------------------------------+
```




