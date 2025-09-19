# DSi Aptina Camera Variables: MODE (Mode/Context) (MCU:27xxh)


### Mode Variables MODE (MCU:2700h..2768h)

```
+------------------------------------------------------------------------------------+
|       2700h  ..  RESERVED_MODE_00-02              Reserved                         |
|       2703h   2  MODE_OUTPUT_WIDTH_A        (CX)  (0..FFFFh, def=0320h)  ;\Size A  
|       2705h   2  MODE_OUTPUT_HEIGHT_A       (CY)  (0..FFFFh, def=0258h)  ;/        |
|       2707h   2  MODE_OUTPUT_WIDTH_B              (0..FFFFh, def=0640h)  ;\Size B  
|       2709h   2  MODE_OUTPUT_HEIGHT_B             (0..FFFFh, def=04B0h)  ;/        |
|       270Bh   1  MODE_A_MIPI_VC                   (0..07h) (REV3)        ;-Mipi A  |
|       270Ch   1  MODE_B_MIPI_VC                   (0..07h) (REV3)        ;-Mipi B  |
|       270Dh   2  MODE_SENSOR_ROW_START_A    (Y1)  (0..FFFFh)             ;\        
|       270Fh   2  MODE_SENSOR_COL_START_A    (X1)  (0..FFFFh)             ;         |
|       2711h   2  MODE_SENSOR_ROW_END_A      (Y2)  (0..FFFFh, def=040Dh)  ;         |
|       2713h   2  MODE_SENSOR_COL_END_A      (X2)  (0..FFFFh, def=050Dh)  ; Sensor  |
|       2715h   2  MODE_SENSOR_ROW_SPEED_A          (0..0777h, def=0112h)  ; A       |
|                    0-2:  pixclk_speed (0..7)                             ;         |
|                            1ADC: Pclk = 2 mclks * bits[0:2]              ;         |
|                            2ADC: bits[0:2]                               ;         |
|                    4-6:  Reserved (0..7)                                 ;         |
|                    8-10: Reserved (0..7)                                 ;         |
|       2717h   2  MODE_SENSOR_READ_MODE_A          (0..FFFFh, def=046Ch)  ;         |
|                    0:   horiz_mirror                                     ;         |
|                    1:   vert_flip                                        ;         |
|                    2-4: y_odd_inc (0..7)                                 ;         |
|                    5-7: x_odd_inc (0..7)                                 ;         |
|                    9:   low_power                                        ;         |
|                    10:  xy_bin_en                                        ;         |
|                    11:  x_bin_en                                         ;         |
|       2719h   2  MODE_SENSOR_FINE_CORRECTION_A    (0..FFFFh, def=007Bh)  ;         |
|       271Bh   2  MODE_SENSOR_FINE_IT_MIN_A        (0..FFFFh, def=0408h)  ;         |
|       271Dh   2  MODE_SENSOR_FINE_IT_MAX_MARGIN_A (0..FFFFh, def=00ABh)  ;         |
|       271Fh   2  MODE_SENSOR_FRAME_LENGTH_A       (0..FFFFh, def=0293h)  ;         |
|       2721h   2  MODE_SENSOR_LINE_LENGTH_PCK_A    (0..FFFFh, def=07D0h)  ;/        |
|       2723h   2  MODE_SENSOR_ROW_START_B          (0..FFFFh, def=0004h)  ;\        
|       2725h   2  MODE_SENSOR_COL_START_B          (0..FFFFh, def=0004h)  ; Sensor  |
|       2727h   2  MODE_SENSOR_ROW_END_B            (0..FFFFh, def=040Bh)  ; B       |
|       2729h   2  MODE_SENSOR_COL_END_B            (0..FFFFh, def=050Bh)  ;         |
|       272Bh   2  MODE_SENSOR_ROW_SPEED_B          (0..0777h, def=0111h)  ; (same   |
|       272Dh   2  MODE_SENSOR_READ_MODE_B          (0..FFFFh, def=0024h)  ; as      |
|       272Fh   2  MODE_SENSOR_FINE_CORRECTION_B    (0..FFFFh, def=00A4h)  ; Sensor  |
|       2731h   2  MODE_SENSOR_FINE_IT_MIN_B        (0..FFFFh, def=0408h)  ; A, see  |
|       2733h   2  MODE_SENSOR_FINE_IT_MAX_MARGIN_B (0..FFFFh, def=00A4h)  ; there)  |
|       2735h   2  MODE_SENSOR_FRAME_LENGTH_B       (0..FFFFh, def=04EDh)  ;         |
|       2737h   2  MODE_SENSOR_LINE_LENGTH_PCK_B    (0..FFFFh, def=0D06h)  ;/        |
|       2739h   2  MODE_CROP_X0_A                   (0..FFFFh)             ;\        
|       273Bh   2  MODE_CROP_X1_A                   (0..FFFFh, def=031Fh)  ; Crop A  |
|       273Dh   2  MODE_CROP_Y0_A                   (0..FFFFh)             ;         |
|       273Fh   2  MODE_CROP_Y1_A                   (0..FFFFh, def=0257h)  ;/        |
|       2741h  ..  RESERVED_MODE_41-45              Reserved                         |
|       2747h   2  MODE_CROP_X0_B                   (0..FFFFh)             ;\        
|       2749h   2  MODE_CROP_X1_B                   (0..FFFFh, def=063Fh)  ; Crop B  |
|       274Bh   2  MODE_CROP_Y0_B                   (0..FFFFh)             ;         |
|       274Dh   2  MODE_CROP_Y1_B                   (0..FFFFh, def=04AFh)  ;/        |
|       274Fh  ..  RESERVED_MODE_4F-53              Reserved                         |
|       2755h   2  MODE_OUTPUT_FORMAT_A             Format A (0..FFFFh     ;\        
|       2757h   2  MODE_OUTPUT_FORMAT_B             Format B (0..FFFFh     ;         |
|                    0     swap_channels (swap Cb/Cr in YUV and R/B in RGB);         |
|                    1     swap_chrominance_luma                           ; Format  |
|                    2     bayer_out (Progressive Bayer)                   ; A/B     |
|                    3     monochrome (0..1)                               ;         |
|                    4     Reserved                                        ;         |
|                    5     output_mode (0=YUV, 1=RGB)                      ;         |
|                    6-7   RGB Format (0=565, 1=555, 2=444xh, 3:x444h)     ;         |
|                    8     Processed Bayer (0..1)                          ;         |
|                    9     Invert out_clk (0..1) (REV3)                    ;         |
|                    10-15 Unspecified                                     ;/        |
|       2759h   2  MODE_SPEC_EFFECTS_A              Effects A  (def=6440h) ;\        
|       275Bh   2  MODE_SPEC_EFFECTS_B              Effects B  (def=6440h) ;         |
|                    0-2  Selection (1=Mono, 2=Sepia, 3=Negative,          ; Effects |
|                           4=Solarization, 5=Solarization w/ UV)          ; A/B     |
|                    3-5  Dither_bitwidth                                  ;         |
|                    6    Dither_luma                                      ;         |
|                    8-15 Solarization Threshold (0..7 for diff effects)   ;/        |
|       275Dh   1  MODE_Y_RGB_OFFSET_A              Offset A (00h..FFh)    ;\Offset  
|       275Eh   1  MODE_Y_RGB_OFFSET_B              Offset B (00h..FFh)    ;/A/B     |
|       275Fh   2  MODE_COMMON_MODE_SETTINGS_BRIGHT_COLOR_KILL             ;\        
|                    Shadow register for 35A4h in SOC2                     ;         |
|                    0-2   Color kill saturation point (0..7)              ; Kill    |
|                    3-5   Bright color kill gain      (0..7)              ; Bright  |
|                    6-8   Bright color kill threshold (0..7)              ;         |
|                    9     Signal_ctrl (1=use luma as min/max value)       ;         |
|                    10    en_kl       (1=enable bright color kill)        ;         |
|                    11-15 Unspecified                                     ;/        |
|       2761h   2  MODE_COMMON_MODE_SETTINGS_DARK_COLOR_KILL               ;\        
|                    Shadow register for 35A2h in SOC2                     ;         |
|                    0-2   Dark color kill gain      (0..7)                ; Kill    |
|                    3-5   Dark color kill threshold (0..7)                ; Dark    |
|                    6     Signal_ctrl (1=use luma as min/max value)       ;         |
|                    7     en_dark_kl  (1=enable dark color kill)          ;         |
|                    8-15  Unspecified                                     ;/        |
|       2763h   2  MODE_COMMON_MODE_SETTINGS_FX_SEPIA_SETTINGS             ;\        
|                    0-7   Sepia constants for Cr (00h..FFh)               ; Sepia   |
|                    8-15  Sepia constants for Cb (00h..FFh)               ;/        |
|       2765h   1  MODE_COMMON_MODE_SETTINGS_FILTER_MODE                   ;\        
|                    Shadow register for 326Eh in SOC1                     ;         |
|                    0-2   UV Filter mode (0..7)                           ; Filter  |
|                    3-4   Y Filter mode  (0..3)                           ;         |
|                    5     Enable_y_filter (enable y permanently)          ;         |
|                    6     Threshold_switch, switch for adaptive Y filter threshold  |
|                    7     Off_switch, B/W filter enable switch            ;/        |
|       2766h   1  MODE_COMMON_MODE_SETTINGS_TEST_MODE   Test (00h..FFh)             |
|                    0-?  Test Pattern (0=None?, 1=Flat, 2=Ramp, 3=ColorBars,        |
|                         4=VertStripes, 5=Noise, 6=HoriStripes)                     |
|                    Output test pattern (instead camera image)                      |
|                    requires "Refresh Command" sent to Sequencer                    |
|       2767h  ..  RESERVED_MODE_67-68                   Reserved                    |
+------------------------------------------------------------------------------------+
```




