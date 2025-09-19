# DSi Aptina Camera Registers: CORE (3000h-31FFh, 38xxh)


### CORE (3000h-31FFh)

```
+-------------------------------------------------------------------------------------+
|       3000h  ..  RESERVED_CORE_3000        Reserved (same as CHIP_VERSION_REG)      |
|       3002h   2  Y_ADDR_START              Y1      ;\Image Position/Size ;def=0004h 
|       3004h   2  X_ADDR_START              X1      ; (up to including    ;def=0004h |
|       3006h   2  Y_ADDR_END                Y2      ; X2,Y2) (0-07FFh)    ;def=04BBh |
|       3008h   2  X_ADDR_END                X2      ;/                    ;def=064Bh |
|       300Ah   2  FRAME_LENGTH_LINES        Y Total ;\Total X/Y Size with ;def=0512h 
|       300Ch   2  LINE_LENGTH_PCK           X Total ;/blanking (0..FFFFh) ;def=0886h |
|       3010h  ..  RESERVED_CORE_3010        Reserved                                 |
|       3012h   2  COARSE_INTEGRATION_TIME   Y Time  ;\Integration Time in ;def=0010h 
|       3014h   2  FINE_INTEGRATION_TIME     X Time  ;/lines/pix (0..FFFFh);def=00F6h |
|       3016h   2  ROW_SPEED                 Row Speed (def=0111h)                    |
|                    0-2   Pixclk_speed (0..7)                                        |
|                    3     Unused (0)                                                 |
|                    4-6   Reserved                                                   |
|                    7     Unused (0)                                                 |
|                    8-10  Reserved                                                   |
|                    11-15 Unused (0)                                                 |
|       3018h  ..  RESERVED_CORE_3018-3019   Reserved                                 |
|       301Ah      UNDOC_CORE_301A           Undocumented Status Reg (mask=D7FFh)     |
|                    0-1   Unspecified                                                |
|                    2     Undoc/USED (1=WakeupDone) (opposite of 0018h.bit14)        |
|                    3-4   Unspecified                                                |
|                    5     Whatever "demo_system, version_reg_write, value=1"         |
|                    6-8   Unspecified                                                |
|                    9     Mask_corrupted_frames     (alias of 3022h.bit0)            |
|                    10    Unspecified                                                |
|                    11    Unused (0)                                                 |
|                    12    Unspecified                                                |
|                    13    Unused (0)                                                 |
|                    14    Unspecified                                                |
|                    15    Grouped_parameter_hold    (alias of 3022h.bit8)            |
|       301Ch  ..  RESERVED_CORE_301C-3020   Reserved                                 |
|       3022h   2  GROUPED_PARAMETER_HOLD_MASK_CORRUPTED_FRAMES                       |
|                    0     Mask_corrupted_frames  (alias of Reg 301Ah.bit9)           |
|                    1-7   Unused (0)                                                 |
|                    8     Grouped_parameter_hold (alias of Reg 301Ah.bit15)          |
|                    9-15  Unused (0)                                                 |
|       3024h   2  PIXEL_ORDER                Pixel Order (mask=0300h, 0..0300h) (R)  |
|       3026h  ..  RESERVED_CORE_3026         Reserved                                |
|       3028h   2  ANALOGUE_GAIN_CODE_GLOBAL  Analog Global   ;\                      
|       302Ah   2  ANALOGUE_GAIN_CODE_GREENR  Analog GreenR   ; Analogue Gain Codes   |
|       302Ch   2  ANALOGUE_GAIN_CODE_RED     Analog Red      ; with 3bit fraction    |
|       302Eh   2  ANALOGUE_GAIN_CODE_BLUE    Analog Blue     ; (0..007Fh, def=000Bh) |
|       3030h   2  ANALOGUE_GAIN_CODE_GREENB  Analog GreenB   ;/                      |
|       3032h   2  DIGITAL_GAIN_GREENR        Digital GreenR  ;\Digital Gain with     
|       3034h   2  DIGITAL_GAIN_RED           Digital Red     ; 8bit dummy-fraction   |
|       3036h   2  DIGITAL_GAIN_BLUE          Digital Blue    ; (bit8-10=Gain, 0..7)  |
|       3038h   2  DIGITAL_GAIN_GREENB        Digital GreenB  ;/(mask=0700h,def=100h) |
|       303Ah  ..  RESERVED_CORE_303A-3C      Reserved                                |
|       3040h   2  READ_MODE                  Read Mode (0-DEFFh, def=0024h)          |
|                    0    horiz_mirror                                                |
|                    1    vert_flip                                                   |
|                    2-4  y_odd_inc (0..7)                                            |
|                    5-7  x_odd_inc (0..7)                                            |
|                    8    Unused (0)                                                  |
|                    9    low_power                                                   |
|                    10   xy_bin_en                                                   |
|                    11   x_bin_en                                                    |
|                    12   bin_sum (Enable summing mode for binning)                   |
|                    13   read_mode_y_sumen                                           |
|                    14   Reserved                                                    |
|                    15   Reserved                                                    |
|       3044h  ..  RESERVED_CORE_3044-3048    Reserved                                |
|       304Ah   2  OTPM_CONTROL               One-time Programmable Memory? Control   |
|                    0    auto_wr_start              ;\                               
|                    1    auto_wr_end (finished) (R) ; automatic write sequence       |
|                    2    auto_wr_success (okay) (R) ;/                               |
|                    3    unspecified                                                 |
|                    4    auto_rd_start              ;\                               
|                    5    auto_rd_end (finished) (R) ; automatic read sequence        |
|                    6    auto_rd_success (okay) (R) ;/                               |
|                    7-15 Unused (0)                                                  |
|       3050h  ..  RESERVED_CORE_3050-3054    Reserved                                |
|       3056h   2  GREEN1_GAIN                Gain Green1             ;\              
|       3058h   2  BLUE_GAIN                  Gain Blue               ; Gain Values   |
|       305Ah   2  RED_GAIN                   Gain Red                ; (0..0FFFh,    |
|       305Ch   2  GREEN2_GAIN                Gain Green2             ; def=022Ch)    |
|                    0-6   Initial Gain (0..7Fh, with 5bit fraction)  ;               |
|                    7-8   Analog Gain  (0..3)   (bit8+1)*(bit7+1)*(initial_gain/32)  |
|                    9-11  Digital Gain (1..7)                        ;               |
|                    12-15 Unused (0)                                 ;/              |
|       305Eh  ..  RESERVED_CORE_305E-31DF    Reserved                                |
|       31E0h   2  UNDOC_CORE_31E0            (mask=E003h, 0..8001h, def=0001h) USED! |
|                    Used by DSi (set to 0001h) (reportedly "PIX_DEF_ID")             |
|       31E2h  ..  RESERVED_CORE_31E2-31F9    Reserved                                |
|       31FAh   2  UNDOC_CORE_31FA            Whatever (mask=FFFFh, def=CDEFh)        |
|                    0-4   Unspecified                                                |
|                    5-11  Whatever "demo_system, version_reg_read, value=3"          |
|                    12-15 Unspecified                                                |
|       31FCh  ..  RESERVED_CORE_305E-31FE    Reserved                                |
+-------------------------------------------------------------------------------------+
```



### More CORE (3800h..3803h)

```
+-----------------------------------------------------------------------+
|       3800h  ..  RESERVED_CORE_3800-3802   Reserved                   |
+-----------------------------------------------------------------------+
```




