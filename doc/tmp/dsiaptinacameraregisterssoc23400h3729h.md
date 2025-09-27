# DSi Aptina Camera Registers: SOC2 (3400h-3729h)


### SOC2 (3400h-3729h)

```
+-------------------------------------------------------------------------------------+
|       3400h   2  MIPI_CONTROL              MIPI_Control (def=782Eh)                 |
|                    0     MIPI restart enable                                        |
|                    1     MIPI standby                                               |
|                    2     Continuous MIPI clock                                      |
|                    3     Frame boundary sync bit (R)                                |
|                    4     Wait until eof to react to standby                         |
|                    5     Reserved                                                   |
|                    6-8   MIPI channel number                                        |
|                    9     Unused (0) or Reserved (REV3)                              |
|                    10-15 Data Type (1Eh=YUV422_8bit, 20h=RGB444, 21h=RGB555,        |
|                            22h=RGB565, 2Ah=RAW8, 2Bh=RAW10)                         |
|       3402h   2  MIPI_STATUS               MIPI_Status (def=0011h)                  |
|                    0     MIPI in standby (R)                                        |
|                    1-3   Unused (0)                                                 |
|                    4     MIPI aka MIPICCP idle (R)                                  |
|                    5     MIPI ready to receive data (R)                             |
|                    6-8   Unused (0)                                                 |
|                    9     Reserved (R)                                               |
|                    10    Reserved (R)                                               |
|                    11    Reserved                                                   |
|                    12    Reserved                                                   |
|                    13-15 Unused (0)                                                 |
|       3404h   2  CUSTOM_SHORT_PKT          MIPI_Custom_Short_Packet (0000h-3F00h)   |
|                    0-5   Unused (0)                                                 |
|                    6     frame_cnt_reset (sent in frame start/end short packets)    |
|                    7     frame_cnt_en (Insert frame counter value in WC field)      |
|                    8-10  custom_short_packet_data_type                              |
|                    11    custom_short_packet_request                                |
|                    12    custom_short_packet_frame_sync                             |
|                    13    custom_short_packet_reset (R)                              |
|                    14-15 Unused (0)                                                 |
|       3408h   2  LINE_BYTE_CNT             MIPI line byte count (def=0C80h)         |
|       340Ch   2  CUSTOM_SHORT_PKT_WC       WC field of a custom short packet        |
|       340Eh  ..  RESERVED_SOC2_340E-341A   Reserved                                 |
|       3580h   2  AE_ZONE_X                 AE Window/Zone X (def=1300h)             |
|                    0-7:  ae_zone_x_start (00h..FFh) (div8)          ;for WINDOW     |
|                    8-15: ae_zone_x_width (00h..FFh) (div8, minus 1) ;for each ZONE  |
|       3582h   2  AE_ZONE_Y                 AE Window/Zone Y (def=0E00h)             |
|                    0-7:  ae_zone_y_start (00h..FFh) (div8)          ;for WINDOW     |
|                    8-15: ae_zone_y_width (00h..FFh) (div8, minus 1) ;for each ZONE  |
|       3584h   2  AE_WINDOW_SIZE_LO         LSBs ;\Size of each AE zone in pixels    
|       3586h   2  AE_WINDOW_SIZE_HI         MSBs ;/(0..0001FFFFh, def=000x4B00h ?)   |
|       3588h  ..  RESERVED_SOC2_3588-35AE   Reserved                                 |
|       35B0h      UNDOC_SOC2_35B0           (mask=FFFFh, 0..FFFFh, def=05FAh) USED!  |
|       35B2h  ..  RESERVED_SOC2_35B2-3602   Reserved                                 |
|       3604h  20  R_GAMMA_CURVE_KNEES_0-18  Red Gamma Curve Knees 0..18   (1B00h,..) |
|       3618h  20  G_GAMMA_CURVE_KNEES_0-18  Green Gamma Curve Knees 0..18 (1B00h,..) |
|       362Ch  20  B_GAMMA_CURVE_KNEES_0-18  Blue Gamma Curve Knees 0..18  (1B00h,..) |
|                    Above 20-byte knees consist of ten 16bit values (Knee0 in LSB)   |
|                    Due to the 16bit-big-endian format, the byte-order is:           |
|                    Knee1,Knee0,Knee3,Knee2,...,Knee17,Knee16,UNUSED,Knee18          |
|       3640h  ..  RESERVED_SOC2_3640        Reserved                                 |
|       3642h   2  POLY_ORIGIN_R             Center Row    (max 07FFh, def=025Ch)     |
|       3644h   2  POLY_ORIGIN_C             Center Column (max 07FFh, def=0324h)     |
|       3646h  ..  RESERVED_SOC2_3646-364C   Reserved                                 |
|       364Eh 5x2  P_GR_P0Q0-4               P0Q for Green1  ;\P0 Coefficients        
|       3658h 5x2  P_RD_P0Q0-4               P0Q for Red     ; (5 x float16 each)     |
|       3662h 5x2  P_BL_P0Q0-4               P0Q for Blue    ; (0010h,... each)       |
|       366Ch 5x2  P_GB_P0Q0-4               P0Q for Green2  ;/                       |
|       3676h 5x2  P_GR_P1Q0-4               P1Q for Green1  ;\                       
|       3680h 5x2  P_RD_P1Q0-4               P1Q for Red     ; P1 Coefficients        |
|       368Ah 5x2  P_BL_P1Q0-4               P1Q for Blue    ; (5 x float16 each)     |
|       3694h 5x2  P_GB_P1Q0-4               P1Q for Green2  ;/                       |
|       369Eh 5x2  P_GR_P2Q0-4               P2Q for Green1  ;\                       
|       36A8h 5x2  P_RD_P2Q0-4               P2Q for Red     ; P2 Coefficients        |
|       36B2h 5x2  P_BL_P2Q0-4               P2Q for Blue    ; (5 x float16 each)     |
|       36BCh 5x2  P_GB_P2Q0-4               P2Q for Green2  ;/                       |
|       36C6h 5x2  P_GR_P3Q0-4               P3Q for Green1  ;\                       
|       36D0h 5x2  P_RD_P3Q0-4               P3Q for Red     ; P3 Coefficients        |
|       36DAh 5x2  P_BL_P3Q0-4               P3Q for Blue    ; (5 x float16 each)     |
|       36E4h 5x2  P_GB_P3Q0-4               P3Q for Green2  ;/                       |
|       36EEh 5x2  P_GR_P4Q0-4               P4Q for Green1  ;\                       
|       36F8h 5x2  P_RD_P4Q0-4               P4Q for Red     ; P4 Coefficients        |
|       3702h 5x2  P_BL_P4Q0-4               P4Q for Blue    ; (5 x float16 each)     |
|       370Ch 5x2  P_GB_P4Q0-4               P4Q for Green2  ;/                       |
|       3716h  ..  RESERVED_SOC2_3716-3278   Reserved                                 |
+-------------------------------------------------------------------------------------+
```




