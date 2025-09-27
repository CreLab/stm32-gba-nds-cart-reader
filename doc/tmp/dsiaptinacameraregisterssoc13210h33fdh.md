# DSi Aptina Camera Registers: SOC1 (3210h-33FDh)


### SOC1 Registers (3210h-33FDh)

```
+-------------------------------------------------------------------------------------+
|       3210h   2  COLOR_PIPELINE_CONTROL     (mask=05B8h, 0..05B0h, def=01B0h)       |
|                    3   Enable PGA pixel shading correction                          |
|                          All coefficients and other configuration settings          |
|                          (including other fields in this register) must be set up   |
|                          before enabling shading correction.                        |
|                    4   Enable 2D aperture correction                                |
|                    5   Enable color correction                                      |
|                    7   Enable gamma correction                                      |
|                    8   Decimator (1=Enable scale)                                   |
|                    10  Reserved                                                     |
|       3216h  ..  RESERVED_SOC1_3216-321A    Reserved                                |
|       321Ch   2  OFIFO_CONTROL_STATUS       Ofifo control status 1 (def=0003h)      |
|                    0-3 txfifo_bypass                                                |
|                          (0=tx_fifo, 1=sensor, 2=sam observe, 3=cpipe format,       |
|                          4=test walking ones cpipe frequency,                       |
|                          5=test walking ones sensor frequency,                      |
|                          6=RESERVED, 7=test PIXCLK, 8..F=Unspecified)               |
|                    4-6 Unused (0)                                                   |
|                    7   sensor_bypass (0=cpipe, 1=sensor)                            |
|                    8   Reserved                                                     |
|                    9   Reserved                                                     |
|                    10  Reserved                                                     |
|                    11  Reserved                                                     |
|                    12  Reserved (R)                                                 |
|                    13  Reserved (R)                                                 |
|                    14  Reserved (R)                                                 |
|                    15  Reserved (R)                                                 |
|       321Eh   2  OFIFO_CONTROL_STATUS_2     Ofifo control status 2 (def=0010h)      |
|                    0-9   Reserved (0..3FFh)                                         |
|                    10    Disable PV output clock during blank (1=disable)           |
|                    11-15 Reserved (0..1Fh)                                          |
|       3220h  ..  RESERVED_SOC1_3220         Reserved                                |
|       3222h   2  LOWER_X_BOUND_ZOOM_WINDOW  Lower X  ;def=?      ;\Zoom Window      
|       3224h   2  UPPER_X_BOUND_ZOOM_WINDOW  Upper X  ;def=063Fh  ; Boundaries       |
|       3226h   2  LOWER_Y_BOUND_ZOOM_WINDOW  Lower Y  ;def=?      ; (0..07FFh)       |
|       3228h   2  UPPER_Y_BOUND_ZOOM_WINDOW  Upper Y  ;def=04AFh  ;/                 |
|       322Ah   2  UNDOC_SOC1_322A            (mask=0016h, 0..0016h) USED by DSi!     |
|       322Ch   2  WEIGHT_HORIZ_DECIMATION    Scaling Weight X ;\Scaling Weight X,Y   
|       322Eh   2  WEIGHT_VERTICAL_DECIMATION Scaling Weight Y ;/(0..0FFFh, def=800h) |
|       323Eh   2  UNDOC_SOC1_323E            (0..FFFFh, def=1A2Dh) (DSi: C22Ch)      |
|       3240h   2  UNDOC_SOC1_3240            (0..FFFFh, def=C814h) (DSi: 6214h)      |
|       3242h  ..  RESERVED_SOC1_3242         Reserved                                |
|       3244h   2  UNDOC_SOC1_3244            (mask=03FFh, range=0..00FFh?, def=0310) |
|       3254h  ..  RESERVED_SOC1_3254-326A    Reserved                                |
|       326Ch   2  APERTURE_PARAMETERS        Aperture Params (0..7FFFh, def=0A08h)   |
|                    0-7   2D aperture threshold (knee) (00h-FFh)                     |
|                    8-10  2D aperture gain (0-7)                                     |
|                    11-13 2D aperture gain's exponent (0-7)                          |
|                    14    Abs (1=force aperture gain be positive)                    |
|                    15    Unused (0)                                                 |
|       326Eh  ..  RESERVED_SOC1_326E-3276    Reserved                                |
|       327Ah   2  BLACK_LEVEL_1ST_RED        Offset Red     ;\Offsets subtracted     
|       327Ch   2  BLACK_LEVEL_1ST_GREEN1     Offset Green1  ; from RGB pixels        |
|       327Eh   2  BLACK_LEVEL_1ST_GREEN2     Offset Green2  ; (0000-01FFh/03FFh,     |
|       3280h   2  BLACK_LEVEL_1ST_BLUE       Offset Blue    ;/def=002Ah)             |
|       328Eh   2  THRESH_EDGE_DETECT         Demosaic Edge Threshold (def=000Ch)     |
|       3290h   2  TEST_PATTERN               Test Pattern Enable/Width               |
|                    0-4   Unused (0)                                                 |
|                    5     en_walk_ones_tp  Enable Test Pattern (0=disable, 1=enable) |
|                    6     walk_ones_10     Pattern Width (0=8-bit, 1=10-bit)         |
|                    7-15  Unused (0)                                                 |
|       329Eh  ..  RESERVED_SOC1_329E-32A0    Reserved                                |
|       32C0h   2  COLOR_CORR_MATRIX_SCALE_14 Exponents C11..C22 (0-7FFFh, def=3923h) |
|       32C2h   2  COLOR_CORR_MATRIX_SCALE_11 Exponents C23..C33 (0-0FFFh, def=0724h) |
|       32C4h   2  COLOR_CORR_MATRIX_1_2      Elements C11=LSB, C12=MSB   (def=7DCCh) |
|       32C6h   2  COLOR_CORR_MATRIX_3_4      Elements C13=LSB, C21=MSB   (def=2711h) |
|       32C8h   2  COLOR_CORR_MATRIX_5_6      Elements C22=LSB, C23=MSB   (def=62E5h) |
|       32CAh   2  COLOR_CORR_MATRIX_7_8      Elements C31=LSB, C32=MSB   (def=690Dh) |
|       32CCh   2  COLOR_CORR_MATRIX_9        Element C33=LSB, Signs=MSB  (def=2DCDh) |
|       32D4h   2  DIGITAL_GAIN_1_RED         Gain for Red channel    ;\Digital Gain1 
|       32D6h   2  DIGITAL_GAIN_1_GREEN1      Gain for Green1 channel ; (mul 128,     |
|       32D8h   2  DIGITAL_GAIN_1_GREEN2      Gain for Green2 channel ; 0000h..03FFh, |
|       32DAh   2  DIGITAL_GAIN_1_BLUE        Gain for Blue channel   ;/def=0080h)    |
|       32F4h  ..  RESERVED_SOC1_32F4-332E    Reserved                                |
|       3330h   2  OUTPUT_FORMAT_TEST         OUTPUT_FORMAT_TEST (0..0FFFh)           |
|                    0     Disable Cr channel                                         |
|                    1     Disable Y channel                                          |
|                    2     Disable Cb channel                                         |
|                    3-5   Test ramp output                                           |
|                    6     8+2 bypass                                                 |
|                    7     Reserved                                                   |
|                    8     Enable Lens Correction Bypass                              |
|                    9     Reserved                                                   |
|                    10    Reserved                                                   |
|                    11    Reserved                                                   |
|                    12-15 Unused (0)                                                 |
|       3332h  ..  RESERVED_SOC1_3332-334A    Reserved                                |
|       337Ch   2  YUV_YCBCR_CONTROL          YUV_YCBCR_CONTROL (0..000Fh, def=0006h) |
|                    0     Mult_y_uv (normalize Y in 16-235; U and V in 16-240)       |
|                    1     Coefficient control                                        |
|                    2     Add 128 to U and V                                         |
|                    3     Clip Y in 16-235; U and V in 16-240                        |
|                    4-15  Unused (0)                                                 |
|       337Eh   2  Y_RGB_OFFSET               Y_RGB Offset                            |
|                    0-7   Reserved (0..FFh)                                          |
|                    8-15  Y offset (0..FFh)                                          |
|       33E6h  ..  RESERVED_SOC1_33E6-33EE    Reserved                                |
|       33F4h   2  KERNEL_CONFIG              Kernel Config (0..01FFh, def=0003h)     |
|                    0     Defect correction (DC) enable                              |
|                    1     Reserved                                                   |
|                    2     Reserved                                                   |
|                    3     Noise reduction (NR) enable                                |
|                    4     Reserved                                                   |
|                    5     Reserved                                                   |
|                    6     Reserved                                                   |
|                    7     Reserved                                                   |
|                    8     Reserved                                                   |
|       33F6h  ..  RESERVED_SOC1_33F6-33FC    Reserved                                |
+-------------------------------------------------------------------------------------+
```




