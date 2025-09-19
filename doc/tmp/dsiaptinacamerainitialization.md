# DSi Aptina Camera Initialization


Aptina I2C registers are accessed via 16bit index, and one or more data bytes at auto-increasing indices (usually, all transfers are done as big-endian 2-byte (16bit) values at even indices). Additional MCU Variables are accessed indirectly via XMDA registers.

### aptina_get_chip_id:
Reading a 16bit value from index 0000h returns the CHIP_VERSION_REG (always 2280h=MT9V113 for DSi/3DS/New3DS), the DSi games are actually reading that register, but they seem to ignore it\'s value.
If the DSi isn\'t fitted with Aptina cameras, then reading anything from device 78h/7Ah would most likely return FFh-bytes.

### brightness / low light environments
Below configurations are okay for daylight (without much sunshine), but the picture will be almost completely black at night (in rooms with small bulbs). There are probably numerous good/bad ways to manipulate the brightness. Some random solutions are:
Leave AE_MIN_INDEX/AE_MAX_INDEX at their power-on defaults (instead of using below settings) (the power-on defaults will greatly improve the brightness, but the conversion will be also much slower). Increasing COARSE_INTEGRATION_TIME to some big value (like 0800h) does also seem to raise the brightness.

### aptina_code_list_init:
Below is some minimal initialization (though it might still include some unnecessary stuff). Most important sections are leaving standby mode, matching PLL to DSi timings, selecting desired resolution(s) and YUV color format.
DSi games are usually initializing further stuff like P0..P4 Coefficients, Gamma Tables, and Color Correction Matrices - but the cameras are also working when leaving those settings at their power-on defaults.
It\'s recommended to initialize both cameras in parallel (eg. issue Wakeup to \<both\> cameras, and \<then\> wait for Wakeup completion; this is faster than doing it separately for each camera).

```
+-------------------------------------------------------------------------------------+
|       AptWr     ,0001Ah,00003h   ;RESET_AND_MISC_CONTROL (issue reset)   ;\reset    
|       AptWr     ,0001Ah,00000h   ;RESET_AND_MISC_CONTROL (release reset) ;/         |
|       AptWr     ,00018h,04028h   ;STANDBY_CONTROL (wakeup)               ;\         
|       AptWr     ,0001Eh,00201h   ;PAD_SLEW                               ; wakeup   |
|       AptWr     ,00016h,042DFh   ;CLOCKS_CONTROL                         ;          |
|       AptWaitClr,00018h,04000h   ;STANDBY_CONTROL (wait for WakeupDone)  ;          |
|       AptWaitSet,0301Ah,00004h   ;UNDOC_CORE_301A (wait for WakeupDone)  ;/         |
|       AptWrMcu  ,002F0h,00000h   ;UNDOC! RAM?                                       |
|       AptWrMcu  ,002F2h,00210h   ;UNDOC! RAM?                                       |
|       AptWrMcu  ,002F4h,0001Ah   ;UNDOC! RAM?                                       |
|       AptWrMcu  ,02145h,002F4h   ;UNDOC! SEQ?                                       |
|       AptWrMcu  ,0A134h,  001h   ;UNDOC! SEQ?                                       |
|       AptSetMcu ,0A115h,  002h   ;SEQ_CAP_MODE (set bit1=video)                     |
|       AptWrMcu  ,02755h,00002h   ;MODE_OUTPUT_FORMAT_A (bit5=0=YUV)      ;\select   
|       AptWrMcu  ,02757h,00002h   ;MODE_OUTPUT_FORMAT_B                   ;/YUV mode |
|       AptWr     ,00014h,02145h   ;PLL_CONTROL                            ;\         
|       AptWr     ,00010h,00111h   ;PLL_DIVIDERS                           ; match    |
|       AptWr     ,00012h,00000h   ;PLL_P_DIVIDERS                         ; PLL      |
|       AptWr     ,00014h,0244Bh   ;PLL_CONTROL                            ; to DSi   |
|       AptWr     ,00014h,0304Bh   ;PLL_CONTROL                            ; timings  |
|       AptWaitSet,00014h,08000h   ;PLL_CONTROL (wait for PLL Lock okay)   ;          |
|       AptClr    ,00014h,00001h   ;PLL_CONTROL (disable PLL Bypass)       ;/         |
|       AptWrMcu  ,02703h,00100h   ;MODE_OUTPUT_WIDTH_A              ;\Size A         
|       AptWrMcu  ,02705h,000C0h   ;MODE_OUTPUT_HEIGHT_A             ;/ 256x192       |
|       AptWrMcu  ,02707h,00280h   ;MODE_OUTPUT_WIDTH_B              ;\Size B         
|       AptWrMcu  ,02709h,001E0h   ;MODE_OUTPUT_HEIGHT_B             ;/ 640x480       |
|       AptWrMcu  ,02715h,00001h   ;MODE_SENSOR_ROW_SPEED_A          ;\               
|       AptWrMcu  ,02719h,0001Ah   ;MODE_SENSOR_FINE_CORRECTION_A    ;                |
|       AptWrMcu  ,0271Bh,0006Bh   ;MODE_SENSOR_FINE_IT_MIN_A        ; Sensor A       |
|       AptWrMcu  ,0271Dh,0006Bh   ;MODE_SENSOR_FINE_IT_MAX_MARGIN_A ;                |
|       AptWrMcu  ,0271Fh,002C0h   ;MODE_SENSOR_FRAME_LENGTH_A       ;                |
|       AptWrMcu  ,02721h,0034Bh   ;MODE_SENSOR_LINE_LENGTH_PCK_A    ;/               |
|       AptWrMcu  ,0A20Bh,  000h   ;AE_MIN_INDEX                     ;\AE min/max     
|       AptWrMcu  ,0A20Ch,  006h   ;AE_MAX_INDEX                     ;/               |
|       AptWrMcu  ,0272Bh,00001h   ;MODE_SENSOR_ROW_SPEED_B          ;\               
|       AptWrMcu  ,0272Fh,0001Ah   ;MODE_SENSOR_FINE_CORRECTION_B    ;                |
|       AptWrMcu  ,02731h,0006Bh   ;MODE_SENSOR_FINE_IT_MIN_B        ; Sensor B       |
|       AptWrMcu  ,02733h,0006Bh   ;MODE_SENSOR_FINE_IT_MAX_MARGIN_B ;                |
|       AptWrMcu  ,02735h,002C0h   ;MODE_SENSOR_FRAME_LENGTH_B       ;                |
|       AptWrMcu  ,02737h,0034Bh   ;MODE_SENSOR_LINE_LENGTH_PCK_B    ;/               |
|       AptSet    ,03210h,00008h   ;COLOR_PIPELINE_CONTROL (PGA pixel shading..)      |
|       AptWrMcu  ,0A208h,  000h   ;UNDOC! RESERVED_AE_08                             |
|       AptWrMcu  ,0A24Ch,  020h   ;AE_TARGETBUFFERSPEED                              |
|       AptWrMcu  ,0A24Fh,  070h   ;AE_BASETARGET                                     |
|       If Device=7Ah                                                ;\               
|         AptWrMcu,02717h,00024h   ;MODE_SENSOR_READ_MODE_A          ; Read Mode      |
|         AptWrMcu,0272Dh,00024h   ;MODE_SENSOR_READ_MODE_B          ; with x-flip    |
|       Else (xflip)                                                 ; on internal    |
|         AptWrMcu,02717h,00025h   ;MODE_SENSOR_READ_MODE_A          ; camera         |
|         AptWrMcu,0272Dh,00025h   ;MODE_SENSOR_READ_MODE_B          ;/               |
|       If Device=7Ah                                                ;\               
|         AptWrMcu,0A202h,  022h   ;AE_WINDOW_POS                    ;                |
|         AptWrMcu,0A203h,  0BBh   ;AE_WINDOW_SIZE                   ;                |
|       Else (?)                                                     ;                |
|         AptWrMcu,0A202h,  000h   ;AE_WINDOW_POS                    ;                |
|         AptWrMcu,0A203h,  0FFh   ;AE_WINDOW_SIZE                   ;/               |
|       AptSet    ,00016h,00020h   ;CLOCKS_CONTROL (set bit5=1, reserved)             |
|       AptWrMcu  ,0A115h,  072h   ;SEQ_CAP_MODE (was already manipulated above)      |
|       AptWrMcu  ,0A11Fh,  001h   ;SEQ_PREVIEW_1_AWB                ;\               
|       If Device=7Ah                                                ;                |
|         AptWr   ,0326Ch,00900h   ;APERTURE_PARAMETERS              ;                |
|         AptWrMcu,0AB22h,  001h   ;HG_LL_APCORR1                    ;                |
|       Else (?)                                                     ;                |
|         AptWr   ,0326Ch,01000h   ;APERTURE_PARAMETERS              ;                |
|         AptWrMcu,0AB22h,  002h   ;HG_LL_APCORR1                    ;/               |
|       AptWrMcu     ,0A103h,  006h   ;SEQ_CMD (06h=RefreshMode)                      |
|       AptWaitMcuClr,0A103h,  00Fh   ;SEQ_CMD (wait above to become ZERO)            |
|       AptWrMcu     ,0A103h,  005h   ;SEQ_CMD (05h=Refresh)                          |
|       AptWaitMcuClr,0A103h,  00Fh   ;SEQ_CMD (wait above to become ZERO)            |
+-------------------------------------------------------------------------------------+
```

Above does set two Mode/Contexts, 256x192 and 640x480. Yet unknown how to activate the latter one.

### aptina_code_list_activate:

```
+-----------------------------------------------------------------------------------+
|       AptClr    ,00018h,00001h   ;STANDBY_CONTROL (bit0=0=wakeup)       ;\        
|       AptWaitClr,00018h,04000h   ;STANDBY_CONTROL (wait for WakeupDone) ; Wakeup  |
|       AptWaitSet,0301Ah,00004h   ;UNDOC_CORE_301A (wait for WakeupDone) ;/        |
|       AptWr     ,03012h,000xxh   ;COARSE_INTEGRATION_TIME (Y Time)                |
|       AptSet    ,0001Ah,00200h   ;RESET_AND_MISC_CONTROL (Parallel On)  ;-Data on |
+-----------------------------------------------------------------------------------+
```

Also, don\'t forget to activate the Camera LED via BPTWL chip (when using the external camera).

### aptina_code_list_deactivate:
Before activating another camera: First disable the Parallel output of the old camera (for avoiding collisions on the camera\'s parallel databus). When not using the camera for longer time, also enter standby mode (for reducing power consumption).

```
+------------------------------------------------------------------------------------+
|       AptClr    ,0001Ah,00200h  ;RESET_AND_MISC_CONTROL (Parallel Off)  ;-Data off |
|       AptSet    ,00018h,00001h  ;STANDBY_CONTROL (set bit0=1=Standby)   ;\         
|       AptWaitSet,00018h,04000h  ;STANDBY_CONTROL (wait for StandbyDone) ; Standby  |
|       AptWaitClr,0301Ah,00004h  ;UNDOC_CORE_301A (wait for StandbyDone) ;/         |
+------------------------------------------------------------------------------------+
```


### References
There aren\'t any MT9V113 specs released, but info for MT9D113 (a higher resolution variant) does exist: a pdf datasheet, and an xml reference for the I2C registers.
There are several source code files for MT9V113 cameras (different files from different people; for use with linux/android/whatever) including samples for adjusting stuff like contrast and sharpness. However, observe that the source code may need some adjustments: PLL register matched to DSi timings, and, use YUV 8bit parallel databus transfer for DSi.



