# DSi Aptina Camera Variables: SEQ (Sequencer) (MCU:21xxh)


### Sequencer Variables SEQ (MCU:2100h..215Ah)

```
+-------------------------------------------------------------------------------------+
|       2100h  ..  RESERVED_SEQ_00           Reserved                                 |
|       2102h   1  SEQ_MODE                  SEQ Mode (enables "drivers") (def=0Fh)   |
|                    0    Enable AE   (ID=2)                                          |
|                    1    Enable FD   (ID=4)                                          |
|                    2    Enable AWB  (ID=3)                                          |
|                    3    Enable HG   (ID=11)                                         |
|                    4-7  Unspecified                                                 |
|       2103h   1  SEQ_CMD                   SEQ Cmd   (0..FFh, def=01h)              |
|                    0-7  Cmd   (0=Run, 1=Preview, 2=Capture, 3=Standby,              |
|                               4=Lock, 5=Refresh, 6=Refresh Mode)                    |
|       2104h   1  SEQ_STATE                 SEQ State (0..FFh)                       |
|                    0-7  State (0=Run, 1=ToPreview, 2=Enter, 3=Preview               |
|                                4=Leave, 5=ToCapture, 6=Enter, 7=Capture,            |
|                                8=Leave, 9=Standby)                                  |
|       2105h  ..  RESERVED_SEQ_05           Reserved                                 |
|       2106h   1  SEQ_FLASHTYPE             Type of flash to be used                 |
|                    0-6 Flash Type (0=None, 1=LED, 2=Xenon, 3=XenonBurst)            |
|                    7   Set flash to LOCK mode (0=Normal, 1=LOCK mode)               |
|       2107h  ..  RESERVED_SEQ_07-08        Reserved                                 |
|       2109h   1  SEQ_AE_FASTBUFF           AE Fast Buff  (0..FFh, def=10h)          |
|       210Ah   1  SEQ_AE_FASTSTEP           AE Fast Step  (0..FFh, def=02h)          |
|       210Bh   1  SEQ_AWB_CONTBUFF          AWB Cont Buff (0..FFh, def=08h)          |
|       210Ch   1  SEQ_AWB_CONTSTEP          AWB Cont Step (0..FFh, def=02h)          |
|       210Dh  ..  RESERVED_SEQ_0D-10        Reserved                                 |
|       2111h   1  SEQ_OPTIONS               SEQ Options (0..FFh, def=08h)            |
|                    0  Reserved                                                      |
|                    1  Reserved                                                      |
|                    2  Reserved                                                      |
|                    3  seq_crop_win_ae, Use crop window for AE statistics            |
|                    4  seq_crop_win_awb, Use crop window for AWB statistics          |
|                    7  Reserved                                                      |
|       2112h  ..  RESERVED_SEQ_12           Reserved                                 |
|       2113h   2  SEQ_FLASH_TH              SEQ Flash TH (0..FFFFh)                  |
|       2115h   1  SEQ_CAP_MODE              Capture mode (in Capture state only)     |
|                    0  Xenon Flash (Still Only)                                      |
|                    1  Video                                                         |
|                    2  Turn Flash off before last frame in capture state             |
|                    4  Video AE on                                                   |
|                    5  Video AWB on                                                  |
|                    6  Video HG on                                                   |
|       2116h   1  SEQ_CAP_NUMFRAMES         Num still frames captured (0..FFh,def=3) |
|       2117h   1  SEQ_PREVIEW_0_AE          Preview 0 AE (PREVIEW ENTER)     ;\      
|                    0-3  AE (0=Off, 1=Fast, 2=Manual, 3=Continuous, 4=MDR)   ;       |
|                    4-7  Unspecified (0..5) (0..0Fh for PREVIEW_2/3)         ; Pre-  |
|       2118h   1  SEQ_PREVIEW_0_FD          Preview 0 FD (PREVIEW ENTER)     ; view  |
|                    0-7  FD (0=Off, 1=Continuous, 2=Manual)                  ; 0     |
|       2119h   1  SEQ_PREVIEW_0_AWB         Preview 0 AWB (PREVIEW ENTER)    ;       |
|                    0-7  AWB (0=Off, 1=On)                                   ; PRE-  |
|       211Ah   1  SEQ_PREVIEW_0_HG          Preview 0 HG (PREVIEW ENTER)     ; VIEW  |
|                    0-7  HG (0=Off, 1=Fast, 2=Manual, 3=Continuous)          ; ENTER |
|       211Bh   1  SEQ_PREVIEW_0_FLASH       Flash Config (0..FFh)            ;       |
|                    0-6 Flash (0=Off,1=On,2=Locked,3=AutoEvaluate,7=UserDef) ;       |
|                    7   Reserved                                             ;       |
|       211Ch   1  SEQ_PREVIEW_0_SKIPFRAME   Skipframe State Config (def=40h) ;       |
|                    0-3 Unspecified                                          ;       |
|                    4   Unspecified (except PREVIEW_2: Reserved)             ;       |
|                    5   Skip_led_on                                          ;       |
|                    6   Skip_state (0=No skip state, 1=Skip state)           ;       |
|                    7   Turn_off_fen                                         ;/      |
|       211Dh   1  SEQ_PREVIEW_1_AE            ;\                             def=01h 
|       211Eh   1  SEQ_PREVIEW_1_FD            ; Preview 1 (PREVIEW)          def=01h |
|       211Fh   1  SEQ_PREVIEW_1_AWB           ; (same as Preview 0, but      def=01h |
|       2120h   1  SEQ_PREVIEW_1_HG            ; without AE=MDR,              def=01h |
|       2121h   1  SEQ_PREVIEW_1_FLASH         ; without HG=Manual/Continous)         |
|       2122h   1  SEQ_PREVIEW_1_SKIPFRAME     ;/                             def=N/A |
|       2123h   1  SEQ_PREVIEW_2_AE            ;\                                     
|       2124h   1  SEQ_PREVIEW_2_FD            ; Preview 2 (PREVIEW LEAVE)            |
|       2125h   1  SEQ_PREVIEW_2_AWB           ; (same as Preview 0, but              |
|       2126h   1  SEQ_PREVIEW_2_HG            ; without HG=Manual/Continous)         |
|       2127h   1  SEQ_PREVIEW_2_FLASH         ;                                      |
|       2128h   1  SEQ_PREVIEW_2_SKIPFRAME     ;/                                     |
|       2129h   1  SEQ_PREVIEW_3_AE            ;\                                     
|       212Ah   1  SEQ_PREVIEW_3_FD            ; Preview 3 (CAPTURE ENTER)            |
|       212Bh   1  SEQ_PREVIEW_3_AWB           ; (same as Preview 0)                  |
|       212Ch   1  SEQ_PREVIEW_3_HG            ;                                      |
|       212Dh   1  SEQ_PREVIEW_3_FLASH         ;                                      |
|       212Eh   1  SEQ_PREVIEW_3_SKIPFRAME     ;/                                     |
|       212Fh  ..  RESERVED_SEQ_2F-33        Reserved                                 |
|       2134h   1  UNDOC_SEQ_34              (0..FFh)                                 |
|       2135h  ..  RESERVED_SEQ_35-44        Reserved                                 |
|       2145h   2  UNDOC_SEQ_45              (0..FFFFh)                               |
|       2147h  ..  RESERVED_SEQ_47-59        Reserved                                 |
+-------------------------------------------------------------------------------------+
```




