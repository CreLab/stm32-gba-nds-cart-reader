# DSi Aptina Camera Variables: AWB (Auto White Balance) (MCU:23xxh)


### Auto White Balance Variables AWB (MCU:2300h..236Eh)

```
+-------------------------------------------------------------------------------------+
|       2300h  ..  RESERVED_AWB_00           Reserved                                 |
|       2302h   1  AWB_WINDOW_POS            AWB Window Position Y0 and X0            |
|                    0-3  X0 (in units of 1/16th of frame width)  (0..0Fh)            |
|                    4-7  Y0 (in units of 1/16th of frame height) (0..0Fh)            |
|       2303h   1  AWB_WINDOW_SIZE           AWB Window Size (def=EFh)                |
|                    0-3  Width  (units of 1/16th of frame width, minus 1)  (0..0Fh)  |
|                    4-7  Height (units of 1/16th of frame height, minus 1) (0..0Fh)  |
|       2304h  ..  RESERVED_AWB_04           Reserved                                 |
|       2306h 3x2  AWB_CCM_L_0-2             Left CCM K11,K12,K13 (0180h,FF00h,0080h) |
|       230Ch 3x2  AWB_CCM_L_3-5             Left CCM K21,K22,K23 (FF66h,0180h,FFEEh) |
|       2312h 3x2  AWB_CCM_L_6-8             Left CCM K31,K32,K33 (FFCDh,FECDh,019Ah) |
|       2318h   2  AWB_CCM_L_9               Left CCM Red/Green gain  (0020h)         |
|       231Ah   2  AWB_CCM_L_10              Left CCM Blue/Green gain (0033h)         |
|       231Ch 3x2  AWB_CCM_RL_0-2            DeltaCCM D11,D12,D13 (0100h,FF9Ah,xxxxh) |
|       2322h 3x2  AWB_CCM_RL_3-5            DeltaCCM D21,D22,D23 (004Dh,FFCDh,FFB8h) |
|       2328h 3x2  AWB_CCM_RL_6-8            DeltaCCM D31,D32,D33 (004Dh,0080h,FF66h) |
|       232Eh   2  AWB_CCM_RL_9              DeltaCCM Red/Green gain  (0008h)         |
|       2330h   2  AWB_CCM_RL_10             DeltaCCM Blue/Green gain (FFF7h)         |
|       2332h 3x2  AWB_CCM_0-2               Curr CCM C11,C12,C13 (01BAh,FF5Bh,FFF1h) |
|       2338h 3x2  AWB_CCM_3-5               Curr CCM C21,C22,C23 (FFC7h,01B9h,FF87h) |
|       233Eh 3x2  AWB_CCM_6-8               Curr CCM C31,C32,C33 (FFF9h,FF32h,01DCh) |
|       2344h   2  AWB_CCM_9                 Curr CCM Red/Green gain  (003Ch)         |
|       2346h   2  AWB_CCM_10                Curr CCM Blue/Green gain (002Bh)         |
|       2348h   1  AWB_GAIN_BUFFER_SPEED     Gain Speed (1-20h, def=08h, 20h=fastest) |
|       2349h   1  AWB_JUMP_DIVISOR          Jump Divisor (1-FFh, def=02h, 1=fastest) |
|       234Ah   1  AWB_GAIN_MIN              Min AWB Red     (def=59h) ;\Digital Gain 
|       234Bh   1  AWB_GAIN_MAX              Max allowed Red (def=B6h) ; Min/max      |
|       234Ch   1  AWB_GAINMIN_B             Min AWB         (def=59h) ; (0..FFh)     |
|       234Dh   1  AWB_GAINMAX_B             Max allowed     (def=A6h) ;/             |
|       234Eh   1  AWB_GAIN_R                Current R digital gain    ;\Current Gain 
|       234Fh   1  AWB_GAIN_G                Current G digital gain    ; (0..FFh,     |
|       2350h   1  AWB_GAIN_B                Current B digital gain    ;/def=80h)     |
|       2351h   1  AWB_CCM_POSITION_MIN      Min/Left  (def=?)   ;\(range 0..FFh,     
|       2352h   1  AWB_CCM_POSITION_MAX      Max/Right (def=7Fh) ; 00h=incandescent,  |
|       2353h   1  AWB_CCM_POSITION          Position  (def=40h) ;/7Fh=daylight)      |
|       2354h   1  AWB_SATURATION            Saturation (0..FFh, def=80h, 80h=100%)   |
|       2355h   1  AWB_MODE                  Misc control for AWB (0..FFh)            |
|                    0  Steady         (1=AWB is done)                                |
|                    1  Limits Reached (1=AWB limit is reached)                       |
|                    2  Reserved                                                      |
|                    3  Reserved                                                      |
|                    4  Reserved                                                      |
|                    5  Force_unit_dgains                                             |
|                    6  NormCCM_off                                                   |
|       2356h   2  AWB_GAINR_BUF             Time-buffered R gain (0..FFFFh)          |
|       2358h   2  AWB_GAINB_BUF             Time-buffered B gain (0..FFFFh)          |
|       235Ah  ..  RESERVED_AWB_5A-5C        Reserved                                 |
|       235Dh   1  AWB_STEADY_BGAIN_OUT_MIN  (0-FF, def=78h)                          |
|       235Eh   1  AWB_STEADY_BGAIN_OUT_MAX  (0-FF, def=86h)                          |
|       235Fh   1  AWB_STEADY_BGAIN_IN_MIN   (0-FF, def=7Eh)                          |
|       2360h   1  AWB_STEADY_BGAIN_IN_MAX   (0-FF, def=82h)                          |
|       2361h   2  UNDOC_AWB_61              (0..FFFFh, def=0040h)                    |
|       2363h   1  AWB_TG_MIN0               True Gray minimum (0..FFh, def=D2h)      |
|       2364h   1  AWB_TG_MAX0               True Gray maximum (0..FFh, def=F6h)      |
|       2365h   1  AWB_X0                    (0-FFh, def=10h)                         |
|       2366h   1  AWB_KR_L                  (0-FFh, def=80h)                         |
|       2367h   1  AWB_KG_L                  (0-FFh, def=80h)                         |
|       2368h   1  AWB_KB_L                  (0-FFh, def=80h)                         |
|       2369h   1  AWB_KR_R                  (0-FFh, def=80h)                         |
|       236Ah   1  AWB_KG_R                  (0-FFh, def=80h)                         |
|       236Bh   1  AWB_KB_R                  (0-FFh, def=80h)                         |
|       236Ch  ..  RESERVED_AWB_6C-6E        Reserved                                 |
+-------------------------------------------------------------------------------------+
```




