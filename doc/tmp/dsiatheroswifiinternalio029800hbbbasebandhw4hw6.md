# DSi Atheros Wifi - Internal I/O - 029800h - BB Baseband (hw4/hw6)


### ATH:029800h/02A360h - BB_TEST_CONTROLS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    CF_TSTTRIG_SEL                                           |
|       4      CF_TSTTRIG                                               |
|       5-6    CF_RFSHIFT_SEL                                           |
|       8-9    CARDBUS_MODE                                             |
|       10     CLKOUT_IS_CLK32                                          |
|       13     ENABLE_RFSILENT_BB                                       |
|       15     ENABLE_MINI_OBS                                          |
|       17     SLOW_CLK160                                              |
|       18     AGC_OBS_SEL_3                                            |
|       19-22  CF_BBB_OBS_SEL                                           |
|       23     RX_OBS_SEL_5TH_BIT                                       |
|       24     AGC_OBS_SEL_4                                            |
|       28     FORCE_AGC_CLEAR                                          |
|       30-31  TSTDAC_OUT_SEL                                           |
+-----------------------------------------------------------------------+
```


### ATH:029804h/02A204h - BB_GEN_CONTROLS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      TURBO                                                    |
|       1      CF_SHORT20                                               |
|       2      DYN_20_40                                                |
|       3      DYN_20_40_PRI_ONLY                                       |
|       4      DYN_20_40_PRI_CHN                                        |
|       5      DYN_20_40_EXT_CHN                                        |
|       6      HT_ENABLE                                                |
|       7      ALLOW_SHORT_GI                                           |
|       8      CF_2_CHAINS_USE_WALSH                                    |
|       9      hw4: CF_SINGLE_HT_LTF1                         ;-hw4     |
|       9      hw6: CF_3_CHAINS_USE_WALSH                     ;-hw6     |
|       10     GF_ENABLE                                                |
|       11     hw4: BYPASS_DAC_FIFO_N                         ;-hw4     |
|       11     hw6: ENABLE_DAC_ASYNC_FIFO                     ;\        
|       14     hw6: BOND_OPT_CHAIN_SEL                        ;         |
|       15     hw6: STATIC20_MODE_HT40_PACKET_HANDLING        ;         |
|       16     hw6: STATIC20_MODE_HT40_PACKET_ERROR_RPT       ; hw6     |
|       17     hw6: ENABLE_CSD_PHASE_DITHERING                ;         |
|       18-24  hw6: UNSUPP_HT_RATE_THRESHOLD                  ;         |
|       25     hw6: EN_ERR_TX_CHAIN_MASK_ZERO                 ;         |
|       26     hw6: IS_MCKINLEY_TPC                           ;/        |
+-----------------------------------------------------------------------+
```


### ATH:029808h/02A364h - BB_TEST_CONTROLS_STATUS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      CF_TSTDAC_EN                                             |
|       1      CF_TX_SRC_IS_TSTDAC                                      |
|       2-4    CF_TX_OBS_SEL                                            |
|       5-6    CF_TX_OBS_MUX_SEL                                        |
|       7      CF_TX_SRC_ALTERNATE                                      |
|       8      CF_TSTADC_EN                                             |
|       9      CF_RX_SRC_IS_TSTADC                                      |
|       10-13  RX_OBS_SEL                                               |
|       14     DISABLE_A2_WARM_RESET                                    |
|       15     RESET_A2                                                 |
|       16-18  AGC_OBS_SEL                                              |
|       19     CF_ENABLE_FFT_DUMP                                       |
|       23     CF_DEBUGPORT_IN                                          |
|       27     DISABLE_AGC_TO_A2                                        |
|       28     CF_DEBUGPORT_EN                                          |
|       29-30  CF_DEBUGPORT_SEL                                         |
+-----------------------------------------------------------------------+
```


### ATH:02980Ch/029800h - BB_TIMING_CONTROLS_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    STE_THR                                                  |
|       7-12   STE_TO_LONG1                                             |
|       13-16  TIMING_BACKOFF                                           |
|       17     ENABLE_HT_FINE_PPM                                       |
|       18-19  HT_FINE_PPM_STREAM                                       |
|       20-21  HT_FINE_PPM_QAM                                          |
|       22     ENABLE_LONG_CHANFIL                                      |
|       23     ENABLE_RX_STBC                                           |
|       24     ENABLE_CHANNEL_FILTER                                    |
|       25-26  FALSE_ALARM                                              |
|       27     ENABLE_LONG_RESCALE                                      |
|       28     TIMING_LEAK_ENABLE                                       |
|       29-30  COARSE_PPM_SELECT                                        |
|       31     FFT_SCALING                                              |
+-----------------------------------------------------------------------+
```


### ATH:029810h/029804h - BB_TIMING_CONTROLS_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   FORCED_DELTA_PHI_SYMBOL                                  |
|       12     FORCE_DELTA_PHI_SYMBOL                                   |
|       13     ENABLE_MAGNITUDE_TRACK                                   |
|       14     ENABLE_SLOPE_FILTER                                      |
|       15     ENABLE_OFFSET_FILTER                                     |
|       16-22  DC_OFF_DELTAF_THRES                                      |
|       24-26  DC_OFF_TIM_CONST                                         |
|       27     ENABLE_DC_OFFSET                                         |
|       28     ENABLE_DC_OFFSET_TRACK                                   |
|       29     ENABLE_WEIGHTING                                         |
|       30     TRACEBACK128                                             |
|       31     ENABLE_HT_FINE_TIMING                                    |
+-----------------------------------------------------------------------+
```


### ATH:029814h/029808h - BB_TIMING_CONTROLS_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    PPM_RESCUE_INTERVAL                                      |
|       8      ENABLE_PPM_RESCUE                                        |
|       9      ENABLE_FINE_PPM                                          |
|       10     ENABLE_FINE_INTERP                                       |
|       11     CONTINUOUS_PPM_RESCUE                                    |
|       12     ENABLE_DF_CHANEST                                        |
|       13-16  DELTA_SLOPE_COEF_EXP                                     |
|       17-31  DELTA_SLOPE_COEF_MAN                                     |
+-----------------------------------------------------------------------+
```


### ATH:029818h/02A200h - BB_D2_CHIP_ID (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    OLD_ID            (R)                                    |
|       8-31   ID                (R)                                    |
+-----------------------------------------------------------------------+
```


### ATH:02981Ch/02A20Ch - BB_ACTIVE ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      CF_ACTIVE                                                |
+-----------------------------------------------------------------------+
```


### ATH:029820h/02A258h - BB_TX_TIMING_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_FRAME_TO_ADC_OFF                                      |
|       8-15   TX_FRAME_TO_A2_RX_OFF                                    |
|       16-23  TX_FRAME_TO_DAC_ON                                       |
|       24-31  TX_FRAME_TO_A2_TX_ON                                     |
+-----------------------------------------------------------------------+
```


### ATH:029824h/02A25Ch - BB_TX_TIMING_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_FRAME_TO_TX_D_START                                   |
|       8-15   TX_FRAME_TO_PA_ON                                        |
|       16-23  TX_END_TO_PA_OFF                                         |
|       24-31  TX_END_TO_A2_TX_OFF                                      |
+-----------------------------------------------------------------------+
```


### ATH:029828h/02A260h - BB_TX_TIMING_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_END_TO_DAC_OFF                                        |
|       8-15   TX_FRAME_TO_THERM_CHAIN_ON                               |
|       16-23  TX_END_TO_A2_RX_ON                                       |
|       24-31  TX_END_TO_ADC_ON                                         |
+-----------------------------------------------------------------------+
```


### ATH:02982Ch/02A350h - BB_ADDAC_PARALLEL_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       12     OFF_DACLPMODE                                            |
|       13     OFF_PWDDAC                                               |
|       15     OFF_PWDADC                                               |
|       28     ON_DACLPMODE                                             |
|       29     ON_PWDDAC                                                |
|       31     ON_PWDADC                                                |
+-----------------------------------------------------------------------+
```


### ATH:029834h/02A264h - BB_XPA_TIMING_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_FRAME_TO_XPAA_ON                                      |
|       8-15   TX_FRAME_TO_XPAB_ON                                      |
|       16-23  TX_END_TO_XPAA_OFF                                       |
|       24-31  TX_END_TO_XPAB_OFF                                       |
+-----------------------------------------------------------------------+
```


### ATH:029838h/02A280h - BB_MISC_PA_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      XPAA_ACTIVE_HIGH                                         |
|       1      XPAB_ACTIVE_HIGH                                         |
|       2      ENABLE_XPAA                                              |
|       3      ENABLE_XPAB                                              |
+-----------------------------------------------------------------------+
```


### ATH:02983Ch/0298A4h - BB_TSTDAC_CONSTANT ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-10   CF_TSTDAC_CONSTANT_I                                     |
|       11-21  CF_TSTDAC_CONSTANT_Q                                     |
+-----------------------------------------------------------------------+
```


### ATH:029840h/029820h - BB_FIND_SIGNAL_LOW ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    RELSTEP_LOW                                              |
|       6-11   FIRSTEP_LOW                                              |
|       12-19  FIRPWR_LOW                                               |
|       20-23  YCOK_MAX_LOW                                             |
|       24-30  LONG_SC_THRESH                                           |
+-----------------------------------------------------------------------+
```


### ATH:029844h/029E00h - BB_SETTLING_TIME ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    AGC_SETTLING                                             |
|       7-13   SWITCH_SETTLING                                          |
|       14-19  ADCSAT_THRL                                              |
|       20-25  ADCSAT_THRH                                              |
|       26-29  LBRESET_ADVANCE                                          |
+-----------------------------------------------------------------------+
```


### ATH:029848h/029E04h - BB_GAIN_FORCE_MAX_GAINS_B0 ;hw4/hw6
### ATH:02A848h/02AE04h - BB_GAIN_FORCE_MAX_GAINS_B1 ;hw4/hw6

```
+----------------------------------------------------------------------------------+
|       7-13   hw4: XATTEN1_HYST_MARGIN_0/1   ;\      ;\separate settings in B0/B1 
|       14-20  hw4: XATTEN2_HYST_MARGIN_0/1   ; hw4   ;/                           |
|       21     hw4: GAIN_FORCE                ;       ;\global setting (not in B1) 
|       31     hw4: ENABLE_SHARED_RX          ;/      ;/                           |
|       0-7    hw6: RF_GAIN_F_0/1             ;\      ;\                           
|       8-15   hw6: MB_GAIN_F_0/1             ;       ;                            |
|       16     hw6: XATTEN1_SW_F_0/1          ; hw6   ; separate settings in B0/B1 |
|       17     hw6: XATTEN2_SW_F_0/1          ;       ;                            |
|       18-24  hw6: XATTEN1_HYST_MARGIN_0/1   ;       ;                            |
|       25-31  hw6: XATTEN2_HYST_MARGIN_0/1   ;/      ;/                           |
+----------------------------------------------------------------------------------+
```


### ATH:02984Ch - BB_GAINS_MIN_OFFSETS_B0 ;hw4
### ATH:02A84Ch - BB_GAINS_MIN_OFFSETS_B1 ;hw4
### ATH:029E08h - BB_GAINS_MIN_OFFSETS ;hw6 (only global setting for B0 and B1)

```
+-------------------------------------------------------------------------------------+
|       0-6    OFFSETC1                       ;\              ;\global setting        
|       7-11   OFFSETC2                       ; hw4/hw6       ; (not in B1 register)  |
|       12-16  OFFSETC3                       ;/              ;/                      |
|       17-24  hw4: RF_GAIN_F_0/1             ;\              ;\separate settings     
|       25     hw4: XATTEN1_SW_F_0/1          ; hw4           ; in B0/B1 registers    |
|       26     hw4: XATTEN2_SW_F_0/1          ;/              ;/                      |
|       17     hw6: GAIN_FORCE                ;\              ;\                      
|       18     hw6: CF_AGC_HIST_ENABLE        ;               ; global setting        |
|       19     hw6: CF_AGC_HIST_GC            ; hw6           ; (hw6 doesn't have     |
|       20     hw6: CF_AGC_HIST_VOTING        ;               ; a B1 register at all) |
|       21     hw6: CF_AGC_HIST_PHY_ERR       ;/              ;/                      |
+-------------------------------------------------------------------------------------+
```


### ATH:029850h/029E0Ch - BB_DESIRED_SIGSIZE ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    ADC_DESIRED_SIZE                                         |
|       20-27  TOTAL_DESIRED                                            |
|       28-29  INIT_GC_COUNT_MAX                                        |
|       30     REDUCE_INIT_GC_COUNT                                     |
|       31     ENA_INIT_GAIN                                            |
+-----------------------------------------------------------------------+
```


### ATH:029854h/029C00h - BB_TIMING_CONTROL_3A ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    STE_THR_HI_RSSI                        ;-hw4/hw6         |
|       7      hw6: USE_HTSIG1_20_40_BW_VALUE         ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:029858h/029E10h - BB_FIND_SIGNAL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    RELSTEP                                                  |
|       6-11   RELPWR                                                   |
|       12-17  FIRSTEP                                                  |
|       18-25  FIRPWR                                                   |
|       26-31  M1COUNT_MAX                                              |
+-----------------------------------------------------------------------+
```


### ATH:02985Ch/029E14h - BB_AGC ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    COARSEPWR_CONST                                          |
|       7-14   COARSE_LOW                                               |
|       15-21  COARSE_HIGH                                              |
|       22-29  QUICK_DROP                                               |
|       30-31  RSSI_OUT_SELECT                                          |
+-----------------------------------------------------------------------+
```


### ATH:029860h/02A2C4h - BB_AGC_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      DO_CALIBRATE                                             |
|       1      DO_NOISEFLOOR                                            |
|       3-5    MIN_NUM_GAIN_CHANGE                                      |
|       6-9    YCOK_MAX                                                 |
|       10     LEAKY_BUCKET_ENABLE                                      |
|       11     CAL_ENABLE                                               |
|       12     USE_TABLE_SEED                                           |
|       13     AGC_UPDATE_TABLE_SEED                                    |
|       15     ENABLE_NOISEFLOOR                                        |
|       16     ENABLE_FLTR_CAL                                          |
|       17     NO_UPDATE_NOISEFLOOR                                     |
|       18     EXTEND_NF_PWR_MEAS                                       |
|       19     CLC_SUCCESS                    (R)                       |
|       20     ENABLE_PKDET_CAL                                         |
+-----------------------------------------------------------------------+
```


### ATH:029864h/029E1Ch - BB_CCA_B0 ;hw4/hw6
### ATH:02AE1Ch - BB_CCA_B1 ;hw6

```
+----------------------------------------------------------------------------------+
|       0-8    CF_MAXCCAPWR_0                         ;-separate settings (on hw6) |
|       9-11   CF_CCA_COUNT_MAXC                      ;\global setting (not in B1) 
|       12-19  CF_THRESH62                            ;/                           |
|       20-28  MINCCAPWR_0                        (R) ;-separate settings (on hw6) |
+----------------------------------------------------------------------------------+
```


### ATH:029868h/029824h - BB_SFCORR ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    M2COUNT_THR                                              |
|       5-10   ADCSAT_THRESH                                            |
|       11-16  ADCSAT_ICOUNT                                            |
|       17-23  M1_THRES                                                 |
|       24-30  M2_THRES                                                 |
+-----------------------------------------------------------------------+
```


### ATH:02986Ch/029828h - BB_SELF_CORR_LOW ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      USE_SELF_CORR_LOW                                        |
|       1-7    M1COUNT_MAX_LOW                                          |
|       8-13   M2COUNT_THR_LOW                                          |
|       14-20  M1_THRESH_LOW                                            |
|       21-27  M2_THRESH_LOW                                            |
+-----------------------------------------------------------------------+
```


### ATH:029874h/02A340h - BB_SYNTH_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-16   RFCHANFRAC                                               |
|       17-25  RFCHANNEL                                                |
|       26-27  RFAMODEREFSEL                                            |
|       28     RFFRACMODE                                               |
|       29     RFBMODE                                                  |
|       30     RFSYNTH_CTRL_SSHIFT                                      |
+-----------------------------------------------------------------------+
```


### ATH:029878h/02A344h - BB_ADDAC_CLK_SELECT ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       2-3    BB_DAC_CLK_SELECT                                        |
|       4-5    BB_ADC_CLK_SELECT                                        |
+-----------------------------------------------------------------------+
```


### ATH:02987Ch/02A348h - BB_PLL_CNTL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    BB_PLL_DIV                                               |
|       10-13  BB_PLL_REFDIV                                            |
|       14-15  BB_PLL_CLK_SEL                                           |
|       16     BB_PLLBYPASS                                             |
|       17-27  BB_PLL_SETTLE_TIME                                       |
+-----------------------------------------------------------------------+
```


### ATH:029900h/02A220h - BB_VIT_SPUR_MASK_A ;CF_PUNC_MASK_A ;hw4/hw6
### ATH:029904h/02A224h - BB_VIT_SPUR_MASK_B ;CF_PUNC_MASK_B ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    CF_PUNC_MASK_A     / CF_PUNC_MASK_B                      |
|       10-16  CF_PUNC_MASK_IDX_A / CF_PUNC_MASK_IDX_B                  |
+-----------------------------------------------------------------------+
```


### ATH:029908h/029C0Ch - BB_PILOT_SPUR_MASK ;CF_PILOT_MASK_A/B ;hw4/hw6
### ATH:02990Ch/029C10h - BB_CHAN_SPUR_MASK ;CF_CHAN_MASK_A/B ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    CF_PILOT_MASK_A     / CF_CHAN_MASK_A                     |
|       5-11   CF_PILOT_MASK_IDX_A / CF_CHAN_MASK_IDX_A                 |
|       12-16  CF_PILOT_MASK_B     / CF_CHAN_MASK_B                     |
|       17-23  CF_PILOT_MASK_IDX_B / CF_CHAN_MASK_IDX_B                 |
+-----------------------------------------------------------------------+
```


### ATH:029910h/02A228h - BB_SPECTRAL_SCAN ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      SPECTRAL_SCAN_ENA                                        |
|       1      SPECTRAL_SCAN_ACTIVE                                     |
|       2      DISABLE_RADAR_TCTL_RST                                   |
|       3      DISABLE_PULSE_COARSE_LOW                                 |
|       4-7    SPECTRAL_SCAN_FFT_PERIOD                                 |
|       8-15   SPECTRAL_SCAN_PERIOD                                     |
|       16-27  SPECTRAL_SCAN_COUNT                                      |
|       28     SPECTRAL_SCAN_SHORT_RPT                                  |
|       29     SPECTRAL_SCAN_PRIORITY                                   |
|       30     SPECTRAL_SCAN_USE_ERR5                                   |
|       31     hw6: SPECTRAL_SCAN_COMPRESSED_RPT      ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A248h - BB_SPECTRAL_SCAN_2 ;hw6

```
+-----------------------------------------------------------------------+
|       0      hw6: SPECTRAL_SCAN_RPT_MODE            ;\hw6             
|       1-8    hw6: SPECTRAL_SCAN_NOISE_FLOOR_REF     ;/                |
+-----------------------------------------------------------------------+
```


### ATH:029914h/02A254h - BB_ANALOG_POWER_ON_TIME ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-13   ACTIVE_TO_RECEIVE                                        |
+-----------------------------------------------------------------------+
```


### ATH:029918h/02A230h - BB_SEARCH_START_DELAY ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   SEARCH_START_DELAY                                       |
|       12     ENABLE_FLT_SVD                                           |
|       13     ENABLE_SEND_CHAN                                         |
|       14     hw6: RX_SOUNDING_ENABLE                                  |
|       15     hw6: RM_HCSD4SVD                                         |
+-----------------------------------------------------------------------+
```


### ATH:02991Ch/02A234h - BB_MAX_RX_LENGTH ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   MAX_RX_LENGTH                                            |
|       12-29  MAX_HT_LENGTH                                            |
+-----------------------------------------------------------------------+
```


### ATH:029920h/02980Ch - BB_TIMING_CONTROL_4 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       12-15  CAL_LG_COUNT_MAX                                         |
|       16     DO_GAIN_DC_IQ_CAL                                        |
|       17-20  USE_PILOT_TRACK_DF                                       |
|       21-27  EARLY_TRIGGER_THR                                        |
|       28     ENABLE_PILOT_MASK                                        |
|       29     ENABLE_CHAN_MASK                                         |
|       30     ENABLE_SPUR_FILTER                                       |
|       31     ENABLE_SPUR_RSSI                                         |
+-----------------------------------------------------------------------+
```


### ATH:029924h/029810h - BB_TIMING_CONTROL_5 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_CYCPWR_THR1                                       |
|       1-7    CYCPWR_THR1                                              |
|       15     ENABLE_RSSI_THR1A                                        |
|       16-22  RSSI_THR1A                                               |
|       23-29  LONG_SC_THRESH_HI_RSSI                                   |
|       30     FORCED_AGC_STR_PRI                                       |
|       31     FORCED_AGC_STR_PRI_EN                                    |
+-----------------------------------------------------------------------+
```


### ATH:029928h/02A7D0h - BB_PHYONLY_WARM_RESET ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      PHYONLY_RST_WARM_L                                       |
+-----------------------------------------------------------------------+
```


### ATH:02992Ch/02A7D4h - BB_PHYONLY_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RX_DRAIN_RATE                                            |
|       1      LATE_TX_SIGNAL_SYMBOL                                    |
|       2      GENERATE_SCRAMBLER                                       |
|       3      TX_ANTENNA_SELECT                                        |
|       4      STATIC_TX_ANTENNA                                        |
|       5      RX_ANTENNA_SELECT                                        |
|       6      STATIC_RX_ANTENNA                                        |
|       7      EN_LOW_FREQ_SLEEP                                        |
+-----------------------------------------------------------------------+
```


### ATH:02993Ch/02A3F0h - BB_POWERTX_MAX ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       6      USE_PER_PACKET_POWERTX_MAX                               |
|       7      hw6: USE_PER_PACKET_OLPC_GAIN_DELTA_ADJ                  |
+-----------------------------------------------------------------------+
```


### ATH:029940h/02983Ch - BB_EXTENSION_RADAR ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       8-13   BLOCKER40_MAX_RADAR                                      |
|       14     ENABLE_EXT_RADAR                                         |
|       15-22  RADAR_DC_PWR_THRESH                                      |
|       23-30  RADAR_LB_DC_CAP                                          |
|       31     DISABLE_ADCSAT_HOLD                                      |
+-----------------------------------------------------------------------+
```


### ATH:029944h/02A238h - BB_FRAME_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-1    CF_OVERLAP_WINDOW                                        |
|       2      CF_SCALE_SHORT                                           |
|       3-5    CF_TX_CLIP                                               |
|       6-7    CF_TX_DOUBLESAMP_DAC                                     |
|       8-15   TX_END_ADJUST                                            |
|       16     PREPEND_CHAN_INFO                                        |
|       17     SHORT_HIGH_PAR_NORM                                      |
|       18     EN_ERR_GREEN_FIELD                                       |
|       19     hw4: EN_ERR_XR_POWER_RATIO                               |
|       19     hw6: EN_ERR_STATIC20_MODE_HT40_PACKET                    |
|       20     EN_ERR_OFDM_XCORR                                        |
|       21     EN_ERR_LONG_SC_THR                                       |
|       22     EN_ERR_TIM_LONG1                                         |
|       23     EN_ERR_TIM_EARLY_TRIG                                    |
|       24     EN_ERR_TIM_TIMEOUT                                       |
|       25     EN_ERR_SIGNAL_PARITY                                     |
|       26     EN_ERR_RATE_ILLEGAL                                      |
|       27     EN_ERR_LENGTH_ILLEGAL                                    |
|       28     hw4: EN_ERR_HT_SERVICE                                   |
|       28     hw6: NO_6MBPS_SERVICE_ERR                                |
|       29     EN_ERR_SERVICE                                           |
|       30     EN_ERR_TX_UNDERRUN                                       |
|       31     EN_ERR_RX_ABORT                                          |
+-----------------------------------------------------------------------+
```


### ATH:029948h/029814h - BB_TIMING_CONTROL_6 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    HI_RSSI_THRESH                                           |
|       8-14   EARLY_TRIGGER_THR_HI_RSSI                                |
|       15-20  OFDM_XCORR_THRESH                                        |
|       21-27  OFDM_XCORR_THRESH_HI_RSSI                                |
|       28-31  LONG_MEDIUM_RATIO_THR                                    |
+-----------------------------------------------------------------------+
```


### ATH:02994Ch/02981Ch - BB_SPUR_MASK_CONTROLS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    SPUR_RSSI_THRESH                                         |
|       8      EN_VIT_SPUR_RSSI                                         |
|       17     ENABLE_MASK_PPM                                          |
|       18-25  MASK_RATE_CNTL                                           |
|       26     hw6: ENABLE_NF_RSSI_SPUR_MIT                             |
+-----------------------------------------------------------------------+
```


### ATH:029950h/0298DCh - BB_RX_IQ_CORR_B0 ;hw4/hw6
### ATH:02A8DCh - BB_RX_IQ_CORR_B1 ;hw6

```
+--------------------------------------------------------------------------+
|       0-6    RX_IQCORR_Q_Q_COFF_0/1         ;\separate settings (on hw6) 
|       7-13   RX_IQCORR_Q_I_COFF_0/1         ;/                           |
|       14     RX_IQCORR_ENABLE               ;-global setting (not in B1) |
|       15-21  LOOPBACK_IQCORR_Q_Q_COFF_0/1   ;\separate settings (on hw6) 
|       22-28  LOOPBACK_IQCORR_Q_I_COFF_0/1   ;/                           |
|       29     LOOPBACK_IQCORR_ENABLE         ;-global setting (not in B1) |
+--------------------------------------------------------------------------+
```


### ATH:029954h/029834h - BB_RADAR_DETECTION ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      PULSE_DETECT_ENABLE                                      |
|       1-5    PULSE_IN_BAND_THRESH                                     |
|       6-11   PULSE_RSSI_THRESH                                        |
|       12-17  PULSE_HEIGHT_THRESH                                      |
|       18-23  RADAR_RSSI_THRESH                                        |
|       24-30  RADAR_FIRPWR_THRESH                                      |
|       31     ENABLE_RADAR_FFT                                         |
+-----------------------------------------------------------------------+
```


### ATH:029958h/029838h - BB_RADAR_DETECTION_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    RADAR_LENGTH_MAX                                         |
|       8-12   PULSE_RELSTEP_THRESH                                     |
|       13     ENABLE_PULSE_RELSTEP_CHECK                               |
|       14     ENABLE_MAX_RADAR_RSSI                                    |
|       15     ENABLE_BLOCK_RADAR_CHECK                                 |
|       16-21  RADAR_RELPWR_THRESH                                      |
|       22     RADAR_USE_FIRPWR_128                                     |
|       23     ENABLE_RADAR_RELPWR_CHECK                                |
|       24-26  CF_RADAR_BIN_THRESH_SEL                                  |
|       27     ENABLE_PULSE_GC_COUNT_CHECK                              |
+-----------------------------------------------------------------------+
```


### ATH:02995Ch/0298D0h - BB_TX_PHASE_RAMP_B0 ;hw4/hw6
### ATH:02A8D0h - BB_TX_PHASE_RAMP_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0      CF_PHASE_RAMP_ENABLE                                     |
|       1-6    CF_PHASE_RAMP_BIAS                                       |
|       7-16   CF_PHASE_RAMP_INIT                                       |
|       17-24  CF_PHASE_RAMP_ALPHA                                      |
+-----------------------------------------------------------------------+
```


### ATH:029960h/02A284h - BB_SWITCH_TABLE_CHN_B0 ;hw4/hw6
### ATH:02B284h - BB_SWITCH_TABLE_CHN_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-1    SWITCH_TABLE_IDLE                                        |
|       2-3    SWITCH_TABLE_T                                           |
|       4-5    SWITCH_TABLE_R                                           |
|       6-7    SWITCH_TABLE_RX1                                         |
|       8-9    SWITCH_TABLE_RX12                                        |
|       10-11  SWITCH_TABLE_B                                           |
+-----------------------------------------------------------------------+
```


### ATH:029964h/02A288h - BB_SWITCH_TABLE_COM1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    SWITCH_TABLE_COM_IDLE                                    |
|       4-7    SWITCH_TABLE_COM_T1                                      |
|       8-11   SWITCH_TABLE_COM_T2                                      |
|       12-15  SWITCH_TABLE_COM_B                                       |
|       16-19  hw6: SWITCH_TABLE_COM_IDLE_ALT         ;\hw6             
|       20-23  hw6: SWITCH_TABLE_COM_SPDT             ;/                |
+-----------------------------------------------------------------------+
```


### ATH:029968h/029E20h - BB_CCA_CTRL_2_B0 ;hw4/hw6
### ATH:02AE20h - BB_CCA_CTRL_2_B1 ;hw6

```
+--------------------------------------------------------------------------+
|       0-8    MINCCAPWR_THR_0/1              ;-separate settings (on hw6) |
|       9      ENABLE_MINCCAPWR_THR           ;-global setting (not in B1) |
|       10-17  NF_GAIN_COMP_0/1               ;-separate settings (on hw6) |
|       18     THRESH62_MODE                  ;-global setting (not in B1) |
+--------------------------------------------------------------------------+
```


### ATH:02996Ch/02A28Ch - BB_SWITCH_TABLE_COM2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    hw4: SWITCH_TABLE_COM_RA1NXAL1         ;\                
|       4-7    hw4: SWITCH_TABLE_COM_RA2NXAL1         ;                 |
|       8-11   hw4: SWITCH_TABLE_COM_RA1XAL1          ;                 |
|       12-15  hw4: SWITCH_TABLE_COM_RA2XAL1          ; hw4             |
|       16-19  hw4: SWITCH_TABLE_COM_RA1NXAL2         ;                 |
|       20-23  hw4: SWITCH_TABLE_COM_RA2NXAL2         ;                 |
|       24-27  hw4: SWITCH_TABLE_COM_RA1XAL2          ;                 |
|       28-31  hw4: SWITCH_TABLE_COM_RA2XAL2          ;/                |
|       0-3    hw6: SWITCH_TABLE_COM_RA1L1            ;\                
|       4-7    hw6: SWITCH_TABLE_COM_RA2L1            ;                 |
|       8-11   hw6: SWITCH_TABLE_COM_RA1L2            ; hw6             |
|       12-15  hw6: SWITCH_TABLE_COM_RA2L2            ;                 |
|       16-19  hw6: SWITCH_TABLE_COM_RA12             ;/                |
+-----------------------------------------------------------------------+
```


### ATH:029970h/029E24h - BB_RESTART ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_RESTART                                           |
|       1-5    RESTART_LGFIRPWR_DELTA                                   |
|       6      ENABLE_PWR_DROP_ERR                                      |
|       7-11   PWRDROP_LGFIRPWR_DELTA                                   |
|       12-17  OFDM_CCK_RSSI_BIAS                                       |
|       18-20  ANT_FAST_DIV_GC_LIMIT                                    |
|       21     ENABLE_ANT_FAST_DIV_M2FLAG                               |
|       22-28  WEAK_RSSI_VOTE_THR                                       |
|       29     ENABLE_PWR_DROP_ERR_CCK                                  |
|       30     DISABLE_DC_RESTART                                       |
|       31     RESTART_MODE_BW40                                        |
+-----------------------------------------------------------------------+
```


### ATH:029978h/02A390h - BB_SCRAMBLER_SEED ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    FIXED_SCRAMBLER_SEED                                     |
+-----------------------------------------------------------------------+
```


### ATH:02997Ch/02A23Ch - BB_RFBUS_REQUEST ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RFBUS_REQUEST                                            |
+-----------------------------------------------------------------------+
```


### ATH:0299A0h/029818h - BB_TIMING_CONTROL_11 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-19   SPUR_DELTA_PHASE                                         |
|       20-29  SPUR_FREQ_SD                                             |
|       30     USE_SPUR_FILTER_IN_AGC                                   |
|       31     USE_SPUR_FILTER_IN_SELFCOR                               |
+-----------------------------------------------------------------------+
```


### ATH:0299A4h/02A2A0h - BB_MULTICHAIN_ENABLE ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-2    RX_CHAIN_MASK                                            |
+-----------------------------------------------------------------------+
```


### ATH:0299A8h/029880h - BB_MULTICHAIN_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_ANALOG_GAIN_DIFF                                   |
|       1-7    FORCED_GAIN_DIFF_01                                      |
|       8      SYNC_SYNTHON                                             |
|       9      USE_POSEDGE_REFCLK                                       |
|       10-20  CF_SHORT_SAT                                             |
|       22-28  FORCED_GAIN_DIFF_02                                      |
|       29     FORCE_SIGMA_ZERO                                         |
+-----------------------------------------------------------------------+
```


### ATH:0299ACh/029E28h - BB_MULTICHAIN_GAIN_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    QUICKDROP_LOW                                            |
|       8      ENABLE_CHECK_STRONG_ANT                                  |
|       9-14   ANT_FAST_DIV_BIAS                                        |
|       15-20  CAP_GAIN_RATIO_SNR                                       |
|       21     CAP_GAIN_RATIO_ENA                                       |
|       22     CAP_GAIN_RATIO_MODE                                      |
|       23     ENABLE_ANT_SW_RX_PROT                                    |
|       24     ENABLE_ANT_DIV_LNADIV                                    |
|       25-26  ANT_DIV_ALT_LNACONF                                      |
|       27-28  ANT_DIV_MAIN_LNACONF                                     |
|       29     ANT_DIV_ALT_GAINTB                                       |
|       30     ANT_DIV_MAIN_GAINTB                                      |
+-----------------------------------------------------------------------+
```


### ATH:0299B4h/0298D4h - BB_ADC_GAIN_DC_CORR_B0 ;hw4/hw6
### ATH:02A8D4h - BB_ADC_GAIN_DC_CORR_B1 ;hw6

```
+--------------------------------------------------------------------------+
|       0-5    ADC_GAIN_CORR_Q_COEFF_0/1      ;\                           
|       6-11   ADC_GAIN_CORR_I_COEFF_0/1      ; separate settings (on hw6) |
|       12-20  ADC_DC_CORR_Q_COEFF_0/1        ;                            |
|       21-29  ADC_DC_CORR_I_COEFF_0/1        ;/                           |
|       30     ADC_GAIN_CORR_ENABLE           ;\global setting (not in B1) 
|       31     ADC_DC_CORR_ENABLE             ;/                           |
+--------------------------------------------------------------------------+
```


### ATH:0299B8h/029E2Ch - BB_EXT_CHAN_PWR_THR_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    THRESH62_EXT                                             |
|       8-15   ANT_DIV_ALT_ANT_MINGAINIDX                               |
|       16-20  ANT_DIV_ALT_ANT_DELTAGAINIDX                             |
|       21-26  ANT_DIV_ALT_ANT_DELTANF                                  |
+-----------------------------------------------------------------------+
```


### ATH:0299BCh/029830h - BB_EXT_CHAN_PWR_THR_2_B0 ;hw4/hw6
### ATH:02A830h - BB_EXT_CHAN_PWR_THR_2_B1 ;hw6

```
+--------------------------------------------------------------------------+
|       0-8    CF_MAXCCAPWR_EXT_0/1           ;-separate settings (on hw6) |
|       9-15   CYCPWR_THR1_EXT                ;-global setting (not in B1) |
|       16-24  MINCCAPWR_EXT_0/1         (R)  ;-separate settings (on hw6) |
+--------------------------------------------------------------------------+
```


### ATH:0299C0h/02982Ch - BB_EXT_CHAN_SCORR_THR ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-6    M1_THRES_EXT                                             |
|       7-13   M2_THRES_EXT                                             |
|       14-20  M1_THRES_LOW_EXT                                         |
|       21-27  M2_THRES_LOW_EXT                                         |
|       28     SPUR_SUBCHANNEL_SD                                       |
+-----------------------------------------------------------------------+
```


### ATH:0299C4h/029E30h - BB_EXT_CHAN_DETECT_WIN ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    DET_DIFF_WIN_WEAK                                        |
|       4-7    DET_DIFF_WIN_WEAK_LOW                                    |
|       8-12   DET_DIFF_WIN_WEAK_CCK                                    |
|       13-15  DET_20H_COUNT                                            |
|       16-18  DET_EXT_BLK_COUNT                                        |
|       19-24  WEAK_SIG_THR_CCK_EXT                                     |
|       25-28  DET_DIFF_WIN_THRESH                                      |
+-----------------------------------------------------------------------+
```


### ATH:0299C8h/029E34h - BB_PWR_THR_20_40_DET ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    PWRDIFF40_THRSTR                                         |
|       5-10   BLOCKER40_MAX                                            |
|       11-15  DET40_PWRSTEP_MAX                                        |
|       16-23  DET40_THR_SNR                                            |
|       24-28  DET40_PRI_BIAS                                           |
|       29     PWRSTEP40_ENA                                            |
|       30     LOWSNR40_ENA                                             |
+-----------------------------------------------------------------------+
```


### ATH:0299D0h/029C14h - BB_SHORT_GI_DELTA_SLOPE ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    DELTA_SLOPE_COEF_EXP_SHORT_GI                            |
|       4-18   DELTA_SLOPE_COEF_MAN_SHORT_GI                            |
+-----------------------------------------------------------------------+
```


### ATH:0299DCh/02A370h - BB_CHANINFO_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      CAPTURE_CHAN_INFO                                        |
|       1      DISABLE_CHANINFOMEM                                      |
|       2      hw6: CAPTURE_SOUNDING_PACKET                             |
|       3      hw6: CHANINFOMEM_S2_READ                                 |
+-----------------------------------------------------------------------+
```


### ATH:0299E0h/02A3A4h - BB_HEAVY_CLIP_CTRL ;hw4/hw6

```
+--------------------------------------------------------------------------------+
|       0-8    CF_HEAVY_CLIP_ENABLE                                              |
|       9      PRE_EMP_HT40_ENABLE                                               |
|       10-17  hw6: HEAVY_CLIP_FACTOR_XR   ;-hw6 (moved from hw4's BB_RIFS_SRCH) |
+--------------------------------------------------------------------------------+
```


### ATH:0299E4h/02A3A8h - BB_HEAVY_CLIP_20 ;FACTOR_0..3 ;hw4/hw6
### ATH:0299E8h/02A3ACh - BB_HEAVY_CLIP_40 ;FACTOR_4..7 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    HEAVY_CLIP FACTOR_0 / FACTOR_4                           |
|       8-15   HEAVY_CLIP FACTOR_1 / FACTOR_5                           |
|       16-23  HEAVY_CLIP FACTOR_2 / FACTOR_6                           |
|       24-31  HEAVY_CLIP FACTOR_3 / FACTOR_7                           |
+-----------------------------------------------------------------------+
```


### ATH:0299ECh/029E38h - BB_RIFS_SRCH ;hw4/hw6

```
+-------------------------------------------------------------------------------------+
|       0-7    hw4: HEAVY_CLIP_FACTOR_XR   ;-hw4 (moved to BB_HEAVY_CLIP_CTRL in hw6) |
|       8-15   INIT_GAIN_DB_OFFSET                                                    |
|       16-25  RIFS_INIT_DELAY                                                        |
|       26     RIFS_DISABLE_PWRLOW_GC                                                 |
|       27     RIFS_DISABLE_CCK_DET                                                   |
+-------------------------------------------------------------------------------------+
```


### ATH:0299F0h/02A2C8h - BB_IQ_ADC_CAL_MODE ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-1    GAIN_DC_IQ_CAL_MODE                                      |
|       2      TEST_CALADCOFF                                           |
+-----------------------------------------------------------------------+
```


### ATH:0299FCh/029884h - BB_PER_CHAIN_CSD ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    CSD_CHN1_2CHAINS                                         |
|       5-9    CSD_CHN1_3CHAINS                                         |
|       10-14  CSD_CHN2_3CHAINS                                         |
+-----------------------------------------------------------------------+
```


### ATH:029A00h..029BFCh - BB_RX_OCGAIN\[0..127\] (W) ;hw4
### ATH:02A000h..02A1FCh - BB_RX_OCGAIN\[0..127\] (R/W?) ;hw6
### ATH:02AA00h..02ABFCh - BB_RX_OCGAIN2\[0..127\] (W) ;hw4
### ATH:02B000h..02B1FCh - BB_RX_OCGAIN2\[0..127\] (R/W?) ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   GAIN_ENTRY                                               |
+-----------------------------------------------------------------------+
```


### ATH:029C00h/0298A0h - BB_TX_CRC (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   TX_CRC                         (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C10h/0298C0h - BB_IQ_ADC_MEAS_0_B0 (R) ;hw4/hw6
### ATH:029C14h/0298C4h - BB_IQ_ADC_MEAS_1_B0 (R) ;hw4/hw6
### ATH:029C18h/0298C8h - BB_IQ_ADC_MEAS_2_B0 (R) ;hw4/hw6
### ATH:029C1Ch/0298CCh - BB_IQ_ADC_MEAS_3_B0 (R) ;hw4/hw6
### ATH:02A8C0h - BB_IQ_ADC_MEAS_0_B1 (R) ;hw6
### ATH:02A8C4h - BB_IQ_ADC_MEAS_1_B1 (R) ;hw6
### ATH:02A8C8h - BB_IQ_ADC_MEAS_2_B1 (R) ;hw6
### ATH:02A8CCh - BB_IQ_ADC_MEAS_3_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   GAIN_DC_IQ_CAL_MEAS            (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C20h/02A240h - BB_RFBUS_GRANT (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RFBUS_GRANT                    (R)                       |
|       1      BT_ANT                         (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C24h/029C20h - BB_TSTADC (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    TSTADC_OUT_Q                   (R)                       |
|       10-19  TSTADC_OUT_I                   (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C28h/02A368h - BB_TSTDAC (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    TSTDAC_OUT_Q                   (R)                       |
|       10-19  TSTDAC_OUT_I                   (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C30h/02A3B0h - BB_ILLEGAL_TX_RATE (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ILLEGAL_TX_RATE                (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C34h/0298A8h - BB_SPUR_REPORT_B0 (R) ;hw4/hw6
### ATH:02A8A8h - BB_SPUR_REPORT_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    SPUR_EST_I                     (R)                       |
|       8-15   SPUR_EST_Q                     (R)                       |
|       16-31  POWER_WITH_SPUR_REMOVED        (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C38h/02A36Ch - BB_CHANNEL_STATUS (R) ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      BT_ACTIVE                      (R)                       |
|       1      RX_CLEAR_RAW                   (R)                       |
|       2      RX_CLEAR_MAC                   (R)                       |
|       3      RX_CLEAR_PAD                   (R)                       |
|       4-5    BB_SW_OUT_0                    (R)                       |
|       6-7    BB_SW_OUT_1                    (R)                       |
|       8-9    BB_SW_OUT_2                    (R)                       |
|       10-13  BB_SW_COM_OUT                  (R)                       |
|       14-16  ANT_DIV_CFG_USED               (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C3Ch/029F80h - BB_RSSI_B0 (R) ;hw4/hw6
### ATH:02AF80h - BB_RSSI_B1 (R) ;hw6
### ATH:02CF80h - BB_RSSI_B3 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    RSSI                           (R)                       |
|       8-15   RSSI_EXT                       (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029C40h/029F84h - BB_SPUR_EST_CCK_REPORT_B0 (R) ;hw4/hw6
### ATH:02AF84h - BB_SPUR_EST_CCK_REPORT_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    SPUR_EST_SD_I_CCK              (R)                       |
|       8-15   SPUR_EST_SD_Q_CCK              (R)                       |
|       16-23  SPUR_EST_I_CCK                 (R)                       |
|       24-31  SPUR_EST_Q_CCK                 (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029CF0h/029CACh/02A374h - BB_CHAN_INFO_NOISE_PWR ;hw4/hw4.2/hw6

```
+-----------------------------------------------------------------------+
|       0-11   NOISE_POWER                    (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029CF4h/029CB0h/02A378h - BB_CHAN_INFO_GAIN_DIFF ;hw4/hw4.2/hw6

```
+-----------------------------------------------------------------------+
|       0-11   FINE_PPM                       (R)                       |
|       12-18  hw6: ANALOG_GAIN_DIFF_01       (R)     ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:029CF8h/029CB4h/02A37Ch - BB_CHAN_INFO_FINE_TIMING ;hw4/hw4.2/hw6

```
+-----------------------------------------------------------------------+
|       0-11   COARSE_PPM                     (R)                       |
|       12-21  FINE_TIMING                    (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029CFCh/029CB8h/02A380h - BB_CHAN_INFO_GAIN_B0 ;hw4/hw4.2/hw6
### ATH:02B380h - BB_CHAN_INFO_GAIN_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    CHAN_INFO_RSSI                 (R)                       |
|       8-15   CHAN_INFO_RF_GAIN              (R)                       |
|       16     hw4: CHAN_INFO_XATTEN1_SW      (R)     ;\hw4 (and hw4.2) 
|       17     hw4: CHAN_INFO_XATTEN2_SW      (R)     ;/                |
|       16-22  hw6: CHAN_INFO_MB_GAIN         (R)     ;\                
|       23     hw6: CHAN_INFO_XATTEN1_SW      (R)     ; hw6             |
|       24     hw6: CHAN_INFO_XATTEN2_SW      (R)     ;/                |
+-----------------------------------------------------------------------+
```


### ATH:029D00h.. - BB_CHAN_INFO_CHAN_TAB_B0\[0..59\] ;hw4
### ATH:029CBCh.. - BB_CHAN_INFO_CHAN_TAB_B0\[0..59\] ;hw4.2
### ATH:029B00h.. - BB_CHAN_INFO_CHAN_TAB_B0\[0..59\] ;hw6
### ATH:02AB00h.. - BB_CHAN_INFO_CHAN_TAB_B1\[0..59\] ;hw6

```
+-----------------------------------------------------------------------+
|       0-5    hw4: MAN_Q_0    ;\             (R)     ;\                
|       6-11   hw4: MAN_I_0    ; aka B0 ?     (R)     ;                 |
|       12-15  hw4: EXP_0      ;/             (R)     ; hw4 (and hw4.2) |
|       16-21  hw4: MAN_Q_1    ;\             (R)     ;                 
|       22-27  hw4: MAN_I_1    ; aka B1 ?     (R)     ;                 |
|       28-31  hw4: EXP_1      ;/             (R)     ;/                |
|       0-31   hw6: CHANINFO_WORD             (R)     ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A000h/029E3Ch - BB_PEAK_DET_CTRL_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      USE_OC_GAIN_TABLE                                        |
|       1      USE_PEAK_DET                                             |
|       2-7    PEAK_DET_WIN_LEN                                         |
|       8-12   PEAK_DET_TALLY_THR_LOW(_0)                               |
|       13-17  PEAK_DET_TALLY_THR_MED(_0)                               |
|       18-22  PEAK_DET_TALLY_THR_HIGH(_0)                              |
|       23-29  PEAK_DET_SETTLING                                        |
|       30     PWD_PKDET_DURING_CAL                                     |
|       31     PWD_PKDET_DURING_RX                                      |
+-----------------------------------------------------------------------+
```


### ATH:02A004h/029E40h - BB_PEAK_DET_CTRL_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    RFSAT_2_ADD_RFGAIN_DEL                                   |
|       10-14  RF_GAIN_DROP_DB_LOW(_0)                                  |
|       15-19  RF_GAIN_DROP_DB_MED(_0)                                  |
|       20-24  RF_GAIN_DROP_DB_HIGH(_0)                                 |
|       25-29  RF_GAIN_DROP_DB_NON(_0)                                  |
|       30     hw6: ENABLE_RFSAT_RESTART                                |
+-----------------------------------------------------------------------+
```


### ATH:02A008h/029E44h - BB_RX_GAIN_BOUNDS_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    RX_MAX_MB_GAIN                                           |
|       8-15   RX_MAX_RF_GAIN_REF                                       |
|       16-23  RX_MAX_RF_GAIN                                           |
|       24     RX_OCGAIN_SEL_2G                                         |
|       25     RX_OCGAIN_SEL_5G                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A00Ch/029E48h - BB_RX_GAIN_BOUNDS_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    GC_RSSI_LOW_DB                                           |
|       8-15   RF_GAIN_REF_BASE_ADDR                                    |
|       16-23  RF_GAIN_BASE_ADDR                                        |
|       24-31  RF_GAIN_DIV_BASE_ADDR                                    |
+-----------------------------------------------------------------------+
```


### ATH:02A010h/029E4Ch - BB_PEAK_DET_CAL_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    PKDET_CAL_WIN_THR                                        |
|       6-11   PKDET_CAL_BIAS                                           |
|       12-13  PKDET_CAL_MEAS_TIME_SEL                                  |
+-----------------------------------------------------------------------+
```


### ATH:02A014h/029E50h - BB_AGC_DIG_DC_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      USE_DIG_DC                                               |
|       1-3    DIG_DC_SCALE_BIAS                                        |
|       4-9    DIG_DC_CORRECT_CAP                                       |
|       10     hw6: DIG_DC_SWITCH_CCK         ;-hw6                     |
|       16-31  DIG_DC_MIXER_SEL_MASK                                    |
+-----------------------------------------------------------------------+
```


### ATH:02A018h/029F88h - BB_AGC_DIG_DC_STATUS_I_B0 (R) ;DIG_DC RES_I_0 ;hw4/hw6
### ATH:02A01Ch/029F8Ch - BB_AGC_DIG_DC_STATUS_Q_B0 (R) ;DIG_DC RES_Q_0 ;hw4/hw6
### ATH:02AF88h - BB_AGC_DIG_DC_STATUS_I_B1 (R) ;hw6
### ATH:02AF8Ch - BB_AGC_DIG_DC_STATUS_Q_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-8    DIG_DC_C1 RES_I_0 / RES_Q_0 / RES_I_1 / RES_Q_1    (R)   |
|       9-17   DIG_DC_C2 RES_I_0 / RES_Q_0 / RES_I_1 / RES_Q_1    (R)   |
|       18-26  DIG_DC_C3 RES_I_0 / RES_Q_0 / RES_I_1 / RES_Q_1    (R)   |
+-----------------------------------------------------------------------+
```


### ATH:02A1F4h/02A398h - BB_BBB_TXFIR_0 ;TXFIR_COEFF_H0..H3 ;hw4/hw6
### ATH:02A1F8h/02A39Ch - BB_BBB_TXFIR_1 ;TXFIR_COEFF_H4..H7 ;hw4/hw6
### ATH:02A1FCh/02A3A0h - BB_BBB_TXFIR_2 ;TXFIR_COEFF_H8..H11 ;hw4/hw6

```
+-------------------------------------------------------------------------+
|       0-7    TXFIR COEFF_H0 (4bit) / COEFF_H4 (6bit) / COEFF_H8 (8bit)  |
|       8-15   TXFIR COEFF_H1 (4bit) / COEFF_H5 (6bit) / COEFF_H9 (8bit)  |
|       16-23  TXFIR COEFF_H2 (5bit) / COEFF_H6 (7bit) / COEFF_H10 (8bit) |
|       24-31  TXFIR COEFF_H3 (5bit) / COEFF_H7 (7bit) / COEFF_H11 (8bit) |
+-------------------------------------------------------------------------+
```

Note: The entries are aligned to 8bit boundaries, but not all entries are 8bit wide (eg. COEFF H0 and H1 are located in bit0-3 and bit8-11, with bit4-7 left unused).

### ATH:02A200h/02A208h - BB_MODES_SELECT ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      CCK_MODE                                                 |
|       2      DYN_OFDM_CCK_MODE                                        |
|       5      HALF_RATE_MODE                                           |
|       6      QUARTER_RATE_MODE                                        |
|       7      MAC_CLK_MODE                                             |
|       8      DISABLE_DYN_CCK_DET                                      |
|       9      hw6: SVD_HALF_RATE_MODE        ;\hw6                     
|       10     hw6: DISABLE_DYN_FAST_ADC      ;/                        |
+-----------------------------------------------------------------------+
```


### ATH:02A204h/02A394h - BB_BBB_TX_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      DISABLE_SCRAMBLER                                        |
|       1      USE_SCRAMBLER_SEED                                       |
|       2-3    TX_DAC_SCALE_CCK                                         |
|       4      TXFIR_JAPAN_CCK                                          |
|       5      ALLOW_1MBPS_SHORT                                        |
|       6-8    TX_CCK_DELAY_1                                           |
|       9-11   TX_CCK_DELAY_2                                           |
+-----------------------------------------------------------------------+
```


### ATH:02A208h/029FC0h - BB_BBB_SIG_DETECT ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    WEAK_SIG_THR_CCK                                         |
|       6-12   ANT_SWITCH_TIME                                          |
|       13     ENABLE_ANT_FAST_DIV                                      |
|       14     LB_ALPHA_128_CCK                                         |
|       15     LB_RX_ENABLE_CCK                                         |
|       16     CYC32_COARSE_DC_EST_CCK                                  |
|       17     CYC64_COARSE_DC_EST_CCK                                  |
|       18     ENABLE_COARSE_DC_CCK                                     |
|       19     CYC256_FINE_DC_EST_CCK                                   |
|       20     ENABLE_FINE_DC_CCK                                       |
|       21     DELAY_START_SYNC_CCK                                     |
|       22     USE_DC_EST_DURING_SRCH                                   |
|       23     hw6: BBB_MRC_OFF_NO_SWAP               ;\hw6             
|       24     hw6: SWAP_DEFAULT_CHAIN_CCK            ;/                |
|       31     ENABLE_BARKER_TWO_PHASE                                  |
+-----------------------------------------------------------------------+
```


### ATH:02A20Ch/029E18h - BB_EXT_ATTEN_SWITCH_CTL_B0 ;hw4/hw6
### ATH:02B20Ch/02AE18h - BB_EXT_ATTEN_SWITCH_CTL_B1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    XATTEN1_DB                                               |
|       6-11   XATTEN2_DB                                               |
|       12-16  XATTEN1_MARGIN                                           |
|       17-21  XATTEN2_MARGIN                                           |
|       22-26  hw6: XLNA_GAIN_DB                      ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A210h/029D00h - BB_BBB_RX_CTRL_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-2    COARSE_TIM_THRESHOLD_2                                   |
|       3-7    COARSE_TIM_THRESHOLD                                     |
|       8-10   COARSE_TIM_N_SYNC                                        |
|       11-15  MAX_BAL_LONG                                             |
|       16-20  MAX_BAL_SHORT                                            |
|       21-23  RECON_LMS_STEP                                           |
|       24-30  SB_CHECK_WIN                                             |
|       31     EN_RX_ABORT_CCK                                          |
+-----------------------------------------------------------------------+
```


### ATH:02A214h/029D04h - BB_BBB_RX_CTRL_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    FREQ_EST_N_AVG_LONG                                      |
|       6-11   CHAN_AVG_LONG                                            |
|       12-16  COARSE_TIM_THRESHOLD_3                                   |
|       17-21  FREQ_TRACK_UPDATE_PERIOD                                 |
|       22-25  FREQ_EST_SCALING_PERIOD                                  |
|       26-31  LOOP_COEF_DPSK_C2_DATA                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A218h/029D08h - BB_BBB_RX_CTRL_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TIM_ADJUST_FREQ_DPSK                                     |
|       8-15   TIM_ADJUST_FREQ_CCK                                      |
|       16-23  TIMER_N_SFD                                              |
+-----------------------------------------------------------------------+
```


### ATH:02A21Ch/029D0Ch - BB_BBB_RX_CTRL_4 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    TIMER_N_SYNC                                             |
|       4-15   TIM_ADJUST_TIMER_EXP                                     |
|       16     FORCE_UNLOCKED_CLOCKS                                    |
|       17     DYNAMIC_PREAM_SEL                                        |
|       18     SHORT_PREAMBLE                                           |
|       19-24  FREQ_EST_N_AVG_SHORT                                     |
|       25-30  CHAN_AVG_SHORT                                           |
|       31     hw6: USE_MRC_WEIGHT                    ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A220h/029D10h - BB_BBB_RX_CTRL_5 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    LOOP_COEF_DPSK_C1_DATA                                   |
|       5-9    LOOP_COEF_DPSK_C1_HEAD                                   |
|       10-15  LOOP_COEF_DPSK_C2_HEAD                                   |
|       16-20  LOOP_COEF_CCK_C1                                         |
|       21-26  LOOP_COEF_CCK_C2                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A224h/029D14h - BB_BBB_RX_CTRL_6 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    SYNC_START_DELAY                                         |
|       10     MAP_1S_TO_2S                                             |
|       11-20  START_IIR_DELAY                                          |
|       21     hw6: USE_MCORR_WEIGHT                  ;\                
|       22     hw6: USE_BKPWR_FOR_CENTER_INDEX        ;                 |
|       23     hw6: CCK_SEL_CHAIN_BY_EO               ; hw6             |
|       24     hw6: FORCE_CCK_SEL_CHAIN               ;                 |
|       25     hw6: FORCE_CENTER_INDEX                ;/                |
+-----------------------------------------------------------------------+
```


### ATH:02A228h/029FC4h - BB_BBB_DAGC_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_DAGC_CCK                                          |
|       1-8    DAGC_TARGET_PWR_CCK                                      |
|       9      ENABLE_BARKER_RSSI_THR                                   |
|       10-16  BARKER_RSSI_THR                                          |
|       17     ENABLE_FIRSTEP_SEL                                       |
|       18-23  FIRSTEP_2                                                |
|       24-27  FIRSTEP_COUNT_LGMAX                                      |
|       28-29  hw6: FORCE_RX_CHAIN_CCK_0              ;\hw6             
|       30-31  hw6: FORCE_RX_CHAIN_CCK_1              ;/                |
+-----------------------------------------------------------------------+
```


### ATH:02A22Ch/029D18h - BB_FORCE_CLKEN_CCK ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_RX_ENABLE0                                         |
|       1      FORCE_RX_ENABLE1                                         |
|       2      FORCE_RX_ENABLE2                                         |
|       3      FORCE_RX_ENABLE3                                         |
|       4      FORCE_RX_ALWAYS                                          |
|       5      FORCE_TXSM_CLKEN                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A230h/02A250h - BB_RX_CLEAR_DELAY ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    OFDM_XR_RX_CLEAR_DELAY                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A240h/029FCCh - BB_CCK_SPUR_MIT ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      USE_CCK_SPUR_MIT                                         |
|       1-8    SPUR_RSSI_THR                                            |
|       9-28   CCK_SPUR_FREQ                                            |
|       29-30  SPUR_FILTER_TYPE                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A244h/02A7C0h - BB_PANIC_WATCHDOG_STATUS/BB_WATCHDOG_STATUS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-2    (PANIC_)WATCHDOG_STATUS_1                                |
|       3      hw4: (PANIC_)WATCHDOG_DET_HANG         ;-hw4             |
|       3      hw6: (PANIC_)WATCHDOG_TIMEOUT          ;-hw6             |
|       4-7    (PANIC_)WATCHDOG_STATUS_2                                |
|       8-11   (PANIC_)WATCHDOG_STATUS_3                                |
|       12-15  (PANIC_)WATCHDOG_STATUS_4                                |
|       16-19  (PANIC_)WATCHDOG_STATUS_5                                |
|       20-23  (PANIC_)WATCHDOG_STATUS_6                                |
|       24-27  (PANIC_)WATCHDOG_STATUS_7                                |
|       28-31  (PANIC_)WATCHDOG_STATUS_8                                |
+-----------------------------------------------------------------------+
```


### ATH:02A248h/02A7C4h - BB_PANIC_WATCHDOG_CTRL_1/BB_WATCHDOG_CTRL_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_(PANIC_)WATCHDOG_(TIMEOUT_RESET_)NON_IDLE         |
|       1      ENABLE_(PANIC_)WATCHDOG_(TIMEOUT_RESET_)IDLE             |
|       2-15   (PANIC_)WATCHDOG_(TIMEOUT_RESET_)NON_IDLE_LIMIT          |
|       16-31  (PANIC_)WATCHDOG_(TIMEOUT_RESET_)IDLE_LIMIT              |
+-----------------------------------------------------------------------+
```


### ATH:02A24Ch/02A7C8h - BB_PANIC_WATCHDOG_CTRL_2/BB_WATCHDOG_CTRL_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_FAST_ADC_CLK                                       |
|       1      (PANIC_)WATCHDOG_(TIMEOUT_)RESET_ENA                     |
|       2      (PANIC_)WATCHDOG_IRQ_ENA                                 |
+-----------------------------------------------------------------------+
```


### ATH:02A250h/029FC8h - BB_IQCORR_CTRL_CCK ;hw4/hw6

```
+---------------------------------------------------------------------------------+
|       0-4    IQCORR_Q_Q_COFF_CCK                                                |
|       5-10   IQCORR_Q_I_COFF_CCK                                                |
|       11     ENABLE_IQCORR_CCK                                                  |
|       12-13  RXCAL_MEAS_TIME_SEL                                                |
|       14-15  CLCAL_MEAS_TIME_SEL                                                |
|       16-20  CF_CLC_INIT_RFGAIN                                                 |
|       21     hw4.2: CF_CLC_PAL_MODE         ;-hw4.2 only (removed again in hw6) |
+---------------------------------------------------------------------------------+
```


### ATH:02A254h/02A7CCh - BB_BLUETOOTH_CNTL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      BT_BREAK_CCK_EN                                          |
|       1      BT_ANT_HALT_WLAN                                         |
|       2      hw6:ENABLE_RFBUS_GRANT_WAKEUP          ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A258h/02A3F8h - BB_TPC_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_DAC_GAIN                                           |
|       1-5    FORCED_DAC_GAIN                                          |
|       6-13   PD_DC_OFFSET_TARGET                                      |
|       14-15  NUM_PD_GAIN                                              |
|       16-17  PD_GAIN_SETTING1                                         |
|       18-19  PD_GAIN_SETTING2                                         |
|       20-21  PD_GAIN_SETTING3                                         |
|       22     ENABLE_PD_CALIBRATE                                      |
|       23-28  PD_CALIBRATE_WAIT                                        |
|       29     FORCE_PDADC_GAIN                                         |
|       30-31  FORCED_PDADC_GAIN                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A25Ch/02A3FCh - BB_TPC_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_FRAME_TO_PDADC_ON                                     |
|       8-15   TX_FRAME_TO_PD_ACC_OFDM                                  |
|       16-23  TX_FRAME_TO_PD_ACC_CCK                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A260h/02A400h - BB_TPC_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TX_END_TO_PDADC_ON                                       |
|       8-15   TX_END_TO_PD_ACC_ON                                      |
|       16-18  PD_ACC_WINDOW_DC_OFF                                     |
|       19-21  PD_ACC_WINDOW_CAL                                        |
|       22-24  PD_ACC_WINDOW_OFDM                                       |
|       25-27  PD_ACC_WINDOW_CCK                                        |
|       31     TPC_CLK_GATE_ENABLE                                      |
+-----------------------------------------------------------------------+
```


### ATH:02A264h/02A404h - BB_TPC_4_B0 ;hw4/hw6
### ATH:02B404h - BB_TPC_4_B1 ;hw6

```
+----------------------------------------------------------------------------------+
|       0      PD_AVG_VALID_0/1               (R)     ;\                           
|       1-8    PD_AVG_OUT_0/1                 (R)     ;                            |
|       9-13   DAC_GAIN_0/1                   (R)     ; separate settings (on hw6) |
|       14-19  TX_GAIN_SETTING_0/1            (R)     ;                            |
|       20-24  RATE_SENT_0/1                  (R)     ;/                           |
|       25-30  ERROR_EST_UPDATE_POWER_THRESH          ;-global setting (not in B1) |
+----------------------------------------------------------------------------------+
```


### ATH:02A268h/02A34Ch - BB_ANALOG_SWAP ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-2    ANALOG_RX_SWAP_CNTL                                      |
|       3-5    ANALOG_TX_SWAP_CNTL                                      |
|       6      SWAP_ALT_CHN                                             |
|       7      ANALOG_DC_DAC_POLARITY                                   |
|       8      ANALOG_PKDET_DAC_POLARITY                                |
+-----------------------------------------------------------------------+
```


### ATH:02A26Ch/02A408h - BB_TPC_5_B0 ;hw4/hw6
### ATH:02B408h - BB_TPC_5_B1 ;hw6

```
+----------------------------------------------------------------------------------+
|       0-3    PD_GAIN_OVERLAP                        ;-global setting (not in B1) |
|       4-9    PD_GAIN_BOUNDARY_1_0/1                 ;\                           
|       10-15  PD_GAIN_BOUNDARY_2_0/1                 ; separate settings (on hw6) |
|       16-21  PD_GAIN_BOUNDARY_3_0/1                 ;                            |
|       22-27  PD_GAIN_BOUNDARY_4_0/1                 ;/                           |
+----------------------------------------------------------------------------------+
```


### ATH:02A270h/02A40Ch - BB_TPC_6_B0 ;hw4/hw6
### ATH:02B40Ch - BB_TPC_6_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-5    PD_DAC_SETTING_1                                         |
|       6-11   PD_DAC_SETTING_2                                         |
|       12-17  PD_DAC_SETTING_3                                         |
|       18-23  PD_DAC_SETTING_4                                         |
|       24-25  ERROR_EST_MODE                                           |
|       26-28  ERROR_EST_FILTER_COEFF                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A274h/02A410h - BB_TPC_7 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    TX_GAIN_TABLE_MAX                                        |
|       6-11   INIT_TX_GAIN_SETTING                                     |
|       12     EN_CL_GAIN_MOD                                           |
|       13     USE_TX_PD_IN_XPA                                         |
|       14     EXTEND_TX_FRAME_FOR_TPC                                  |
|       15     USE_INIT_TX_GAIN_SETTING_AFTER_WARM_RESET                |
+-----------------------------------------------------------------------+
```


### ATH:02A280h..02A2FCh - BB_PDADC_TAB_B0\[0..31\] (W) ;hw4
### ATH:02A480h..02A4FCh - BB_PDADC_TAB_B0\[0..31\] (W) ;hw6
### ATH:02B480h..02B4FCh - BB_PDADC_TAB_B1\[0..31\] (W) ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   TAB_ENTRY                      (W)                       |
+-----------------------------------------------------------------------+
```


### ATH:02A300h..02A33Ch - BB_CL_TAB_B0\[0..15\] ;hw4
### ATH:02A300h..02A33Ch - BB_CL_TAB_B0\[0..15\] ;hw6
### ATH:02B300h..02B33Ch - BB_CL_TAB_B1\[0..15\] ;hw6 only (B1)

```
+-----------------------------------------------------------------------+
|       0-4    CL_GAIN_MOD                                              |
|       5-15   CARR_LK_DC_ADD_Q                                         |
|       16-26  CARR_LK_DC_ADD_I                                         |
|       27-30  BB_GAIN                                                  |
+-----------------------------------------------------------------------+
```


### ATH:02A340h/02A2DCh - BB_CL_MAP_0_B0 ;hw4/hw6
### ATH:02A344h/02A2E0h - BB_CL_MAP_1_B0 ;hw4/hw6
### ATH:02A348h/02A2E4h - BB_CL_MAP_2_B0 ;hw4/hw6
### ATH:02A34Ch/02A2E8h - BB_CL_MAP_3_B0 ;hw4/hw6
### ATH:02B2DCh - BB_CL_MAP_0_B1 ;hw6
### ATH:02B2E0h - BB_CL_MAP_1_B1 ;hw6
### ATH:02B2E4h - BB_CL_MAP_2_B1 ;hw6
### ATH:02B2E8h - BB_CL_MAP_3_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   CL_MAP                                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A358h/02A2D8h - BB_CL_CAL_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_PARALLEL_CAL                                      |
|       1      ENABLE_CL_CALIBRATE                                      |
|       2-3    CF_CLC_TEST_POINT                                        |
|       4-7    CF_CLC_FORCED_PAGAIN                                     |
|       8-15   CARR_LEAK_MAX_OFFSET                                     |
|       16-21  CF_CLC_INIT_BBGAIN                                       |
|       22-29  CF_ADC_BOUND                                             |
|       30     USE_DAC_CL_CORRECTION                                    |
|       31     CL_MAP_HW_GEN                                            |
+-----------------------------------------------------------------------+
```


### ATH:02A388h/02A244h - BB_RIFS ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       25     DISABLE_FCC_FIX                                          |
|       26     ENABLE_RESET_TDOMAIN                                     |
|       27     DISABLE_FCC_FIX2                                         |
|       28     DISABLE_RIFS_CCK_FIX                                     |
|       29     DISABLE_ERROR_RESET_FIX                                  |
|       30     RADAR_USE_FDOMAIN_RESET                                  |
+-----------------------------------------------------------------------+
```


### ATH:029934h/02A3C0h - BB_POWERTX_RATE1 ;Power TX_0..3 ;hw4/hw6
### ATH:029938h/02A3C4h - BB_POWERTX_RATE2 ;Power TX_4..7 ;hw4/hw6
### ATH:02A234h/02A3C8h - BB_POWERTX_RATE3 ;Power TX_1L,2L,2S ;hw4/hw6
### ATH:02A238h/02A3CCh - BB_POWERTX_RATE4 ;Power TX_55L,55S,11L,11S ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    POWERTX_0 / POWERTX_4 / POWERTX_1L / POWERTX_55L         |
|       8-13   POWERTX_1 / POWERTX_5 / -          / POWERTX_55S         |
|       16-21  POWERTX_2 / POWERTX_6 / POWERTX_2L / POWERTX_11L         |
|       24-29  POWERTX_3 / POWERTX_7 / POWERTX_2S / POWERTX_11S         |
+-----------------------------------------------------------------------+
```


### ATH:02A38Ch/02A3D0h - BB_POWERTX_RATE5 ;Power TX HT20_0..3 ;hw4/hw6
### ATH:02A390h/02A3D4h - BB_POWERTX_RATE6 ;Power TX HT20_4..7 ;hw4/hw6
### ATH:02A3CCh/02A3E4h - BB_POWERTX_RATE10 ;Power TX HT20_8..11 ;hw4/hw6
### ATH:02A3D0h/02A3E8h - BB_POWERTX_RATE11 ;Power TX HT20/40_12/13 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    POWERTX HT20_0 / HT20_4 / HT20_8  / HT20_12              |
|       8-13   POWERTX HT20_1 / HT20_5 / HT20_9  / HT20_13              |
|       16-21  POWERTX HT20_2 / HT20_6 / HT20_10 / HT40_12              |
|       24-29  POWERTX HT20_3 / HT20_7 / HT20_11 / HT40_13              |
+-----------------------------------------------------------------------+
```


### ATH:02A3C0h/02A3D8h - BB_POWERTX_RATE7 ;Power TX HT40_0..3 ;hw4/hw6
### ATH:02A3C4h/02A3DCh - BB_POWERTX_RATE8 ;Power TX HT40_4..7 ;hw4/hw6
### ATH:02A3D4h/02A3ECh - BB_POWERTX_RATE12 ;Power TX HT40_8..11 ;hw4/hw6
### ATH:02A3C8h/02A3E0h - BB_POWERTX_RATE9 ;PowerTX DUP40/EXT20_CCK/OFDM ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    POWERTX HT40_0 / HT40_4 / HT40_8  / DUP40_CCK            |
|       8-13   POWERTX HT40_1 / HT40_5 / HT40_9  / DUP40_OFDM           |
|       16-21  POWERTX HT40_2 / HT40_6 / HT40_10 / EXT20_CCK            |
|       24-29  POWERTX HT40_3 / HT40_7 / HT40_11 / EXT20_OFDM           |
+-----------------------------------------------------------------------+
```


### ATH:02A3BCh/02A3F4h - BB_POWERTX_SUB ;Power TX Sub_for_2chain ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    POWERTX SUB_FOR_2CHAIN                                   |
+-----------------------------------------------------------------------+
```


### ATH:02A278h/02A414h - BB_TPC_8 ;DESIRED_SCALE_0..5 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    DESIRED_SCALE_0                                          |
|       5-9    DESIRED_SCALE_1                                          |
|       10-14  DESIRED_SCALE_2                                          |
|       15-19  DESIRED_SCALE_3                                          |
|       20-24  DESIRED_SCALE_4                                          |
|       25-29  DESIRED_SCALE_5                                          |
+-----------------------------------------------------------------------+
```


### ATH:02A27Ch/02A418h - BB_TPC_9 ;DESIRED_SCALE_6,7,CCK and MISC ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-4    DESIRED_SCALE_6                                          |
|       5-9    DESIRED_SCALE_7                                          |
|       10-14  DESIRED_SCALE_CCK                                        |
|       20     EN_PD_DC_OFFSET_THR                                      |
|       21-26  PD_DC_OFFSET_THR                                         |
|       27-30  WAIT_CALTX_SETTLE                                        |
|       31     DISABLE_PDADC_RESIDUAL_DC_REMOVAL                        |
+-----------------------------------------------------------------------+
```


### ATH:02A394h/02A41Ch - BB_TPC_10 ;DESIRED_SCALE HT20_0..5 ;hw4/hw6
### ATH:02A3E4h/02A42Ch - BB_TPC_14 ;DESIRED_SCALE HT20_8..13 ;hw4/hw6
### ATH:02A3DCh/02A424h - BB_TPC_12 ;DESIRED_SCALE HT40_0..5 ;hw4/hw6
### ATH:02A3E0h/02A428h - BB_TPC_13 ;DESIRED_SCALE HT40_6..7 ;hw4/hw6
### ATH:02A3E8h/02A430h - BB_TPC_15 ;DESIRED_SCALE HT40_8..13 ;hw4/hw6

```
+-------------------------------------------------------------------------+
|       0-4    DESIRED_SCALE HT20_0 / HT20_8  / HT40_0 / HT40_6 / HT40_8  |
|       5-9    DESIRED_SCALE HT20_1 / HT20_9  / HT40_1 / HT40_7 / HT40_9  |
|       10-14  DESIRED_SCALE HT20_2 / HT20_10 / HT40_2 / -      / HT40_10 |
|       15-19  DESIRED_SCALE HT20_3 / HT20_11 / HT40_3 / -      / HT40_11 |
|       20-24  DESIRED_SCALE HT20_4 / HT20_12 / HT40_4 / -      / HT40_12 |
|       25-29  DESIRED_SCALE HT20_5 / HT20_13 / HT40_5 / -      / HT40_13 |
+-------------------------------------------------------------------------+
```


### ATH:02A398h/02A420h - BB_TPC_11_B0 ;DESIRED_SCALE HT20_6..7 and OLPC ;hw4/hw6
### ATH:02B420h - BB_TPC_11_B1 ;hw6

```
+----------------------------------------------------------------------------------+
|       0-4    DESIRED_SCALE HT20_6                   ;\global setting (not in B1) 
|       5-9    DESIRED_SCALE HT20_7                   ;/                           |
|       16-23  OLPC_GAIN_DELTA_0/1                    ;\                           
|       24-31  hw4: OLPC_GAIN_DELTA_0/1_PAL_ON  ;-hw4 ; separate settings (on hw6) |
|       24-25  hw6: OLPC_GAIN_DELTA_0/1_LSB_EXT ;-hw6 ;/                           |
+----------------------------------------------------------------------------------+
```


### ATH:02A39Ch/02A2C0h - BB_CAL_CHAIN_MASK ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-2    CAL_CHAIN_MASK                                           |
+-----------------------------------------------------------------------+
```


### ATH:02A3D8h/02A358h - BB_FORCE_ANALOG ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_XPAON                                              |
|       1-3    FORCED_XPAON                                             |
|       4      FORCE_PDADC_PWD                                          |
|       5-7    FORCED_PDADC_PWD                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A3ECh/02A434h - BB_TPC_16 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       8-13   PDADC_PAR_CORR_CCK                                       |
|       16-21  PDADC_PAR_CORR_OFDM                                      |
|       24-29  PDADC_PAR_CORR_HT40                                      |
+-----------------------------------------------------------------------+
```


### ATH:02A3F0h/02A438h - BB_TPC_17 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE_PAL                                               |
|       1      ENABLE_PAL_CCK                                           |
|       2      ENABLE_PAL_OFDM_20                                       |
|       3      ENABLE_PAL_OFDM_40                                       |
|       4-9    PAL_POWER_THRESHOLD                                      |
|       10     FORCE_PAL_LOCKED                                         |
|       11-16  INIT_TX_GAIN_SETTING_PAL_ON                              |
+-----------------------------------------------------------------------+
```


### ATH:02A3F4h/02A43Ch - BB_TPC_18 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    THERM_CAL_VALUE                                          |
|       8-15   VOLT_CAL_VALUE                                           |
|       16     USE_LEGACY_TPC                                           |
|       17-22  hw6: MIN_POWER_THERM_VOLT_GAIN_CORR    ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A3F8h/02A440h - BB_TPC_19/BB_TPC_19_B0 ;hw4/hw6
### ATH:02B440h - BB_TPC_19_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    ALPHA_THERM                                              |
|       8-15   ALPHA_THERM_PAL_ON                                       |
|       16-20  ALPHA_VOLT                                               |
|       21-25  ALPHA_VOLT_PAL_ON                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A3FCh/02A444h - BB_TPC_20 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-23   ENABLE_PAL_MCS_0..23                                     |
+-----------------------------------------------------------------------+
```


### ATH:02A518h..02A554h - BB_CALTX_GAIN_SET\_(0,2,4,6,..,28,30) ;hw4
### ATH:02A600h..02A63Ch - BB_CALTX_GAIN_SET\_(0,2,4,6,..,28,30) ;hw6
Contains 32 table entries (numbered 0..31), with two 14bit entries per word.

```
+----------------------------------------------------------------------------+
|       0-13   CALTX_GAIN_SET_nn   table entry 0,2,4,6,...,28,30 accordingly |
|       14-27  CALTX_GAIN_SET_nn   table entry 1,3,5,7,...,29,31 accordingly |
|       28-31  -                                                             |
+----------------------------------------------------------------------------+
```


### ATH:02A400h..02A47Ch - BB_TX_GAIN_TAB\_(1..32) ;hw4
### ATH:02A500h..02A57Ch - BB_TX_GAIN_TAB\_(1..32) ;hw6
Contains 32 table entries (numbered 1..32), with one 32bit entry per word.

```
+-----------------------------------------------------------------------+
|       0-31   TG_TABLE entry   entry 1..32 accordingly                 |
+-----------------------------------------------------------------------+
```

On hw6, the 32bit entries are expanded to 34bit size (with extra 2bits in the BB_TX_GAIN_TAB_xxx_LSB_EXT registers).

### ATH:02A58Ch - BB_TX_GAIN_TAB_1_16_LSB_EXT ;hw6
### ATH:02A590h - BB_TX_GAIN_TAB_17_32_LSB_EXT ;hw6
Contains 32 table entries (numbered 1..32), with sixteen 2bit entries per word.

```
+-----------------------------------------------------------------------+
|       0-31   TG_TABLE_LSB_EXT  (sixteen 2bit entries per word)        |
+-----------------------------------------------------------------------+
```

These 2bit values are used to expand the 32bit entries in BB_TX_GAIN_TAB\_(1..32) to 34bit size.

### ATH:02A6DCh/02A644h - BB_TXIQCAL_CONTROL_0 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      IQC_TX_TABLE_SEL                                         |
|       1-6    BASE_TX_TONE_DB                                          |
|       7-12   MAX_TX_TONE_GAIN                                         |
|       13-18  MIN_TX_TONE_GAIN                                         |
|       19-22  CALTXSHIFT_DELAY                                         |
|       23-29  LOOPBACK_DELAY                                           |
|       30     hw6: ENABLE_COMBINED_CARR_IQ_CAL       ;\hw6             
|       31     hw6: ENABLE_TXIQ_CALIBRATE             ;/                |
+-----------------------------------------------------------------------+
```


### ATH:02A6E0h/02A648h - BB_TXIQCAL_CONTROL_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    RX_INIT_GAIN_DB                                          |
|       6-11   MAX_RX_GAIN_DB                                           |
|       12-17  MIN_RX_GAIN_DB                                           |
|       18-24  IQCORR_I_Q_COFF_DELPT                                    |
+-----------------------------------------------------------------------+
```


### ATH:02A6E4h/02A64Ch - BB_TXIQCAL_CONTROL_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    IQC_FORCED_PAGAIN                                        |
|       4-8    IQCAL_MIN_TX_GAIN                                        |
|       9-13   IQCAL_MAX_TX_GAIN                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A6E8h/0298B0h - BB_TXIQCAL_CONTROL_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    PWR_HIGH_DB                                              |
|       6-11   PWR_LOW_DB                                               |
|       12-21  IQCAL_TONE_PHS_STEP                                      |
|       22-23  DC_EST_LEN                                               |
|       24     ADC_SAT_LEN                                              |
|       25-26  ADC_SAT_SEL                                              |
|       27-28  IQCAL_MEAS_LEN                                           |
|       29-30  DESIRED_SIZE_DB                                          |
|       31     TX_IQCORR_EN                                             |
+-----------------------------------------------------------------------+
```


### ATH:02A6ECh/02A650h - BB_TXIQ_CORR_COEFF_01_B0 ;hw4/hw6
### ATH:02A6F0h/02A654h - BB_TXIQ_CORR_COEFF_23_B0 ;hw4/hw6
### ATH:02A6F4h/02A658h - BB_TXIQ_CORR_COEFF_45_B0 ;hw4/hw6
### ATH:02A6F8h/02A65Ch - BB_TXIQ_CORR_COEFF_67_B0 ;hw4/hw6
### ATH:02A6FCh/02A660h - BB_TXIQ_CORR_COEFF_89_B0 ;hw4/hw6
### ATH:02A700h/02A664h - BB_TXIQ_CORR_COEFF_AB_B0 ;hw4/hw6
### ATH:02A704h/02A668h - BB_TXIQ_CORR_COEFF_CD_B0 ;hw4/hw6
### ATH:02A708h/02A66Ch - BB_TXIQ_CORR_COEFF_EF_B0 ;hw4/hw6
### ATH:02B650h - BB_TXIQ_CORR_COEFF_01_B1 ;hw6
### ATH:02B654h - BB_TXIQ_CORR_COEFF_23_B1 ;hw6
### ATH:02B658h - BB_TXIQ_CORR_COEFF_45_B1 ;hw6
### ATH:02B65Ch - BB_TXIQ_CORR_COEFF_67_B1 ;hw6
### ATH:02B660h - BB_TXIQ_CORR_COEFF_89_B1 ;hw6
### ATH:02B664h - BB_TXIQ_CORR_COEFF_AB_B1 ;hw6
### ATH:02B668h - BB_TXIQ_CORR_COEFF_CD_B1 ;hw6
### ATH:02B66Ch - BB_TXIQ_CORR_COEFF_EF_B1 ;hw6
The B0 (and B1) table each contain 16 entries (numbered 0..F), with two 14bit entries per word.

```
+----------------------------------------------------------------------------------+
|       0-13   IQC_COEFF_TABLE_n      ;table entry (n=0,2,4,6,8,A,C,E) accordingly |
|       14-27  IQC_COEFF_TABLE_n      ;table entry (n=1,3,5,7,9,B,D,F) accordingly |
|       28-31  -                                                                   |
+----------------------------------------------------------------------------------+
```


### ATH:02A70Ch/02A670h - BB_CAL_RXBB_GAIN_TBL_0 ;hw4/hw6
### ATH:02A710h/02A674h - BB_CAL_RXBB_GAIN_TBL_4 ;hw4/hw6
### ATH:02A714h/02A678h - BB_CAL_RXBB_GAIN_TBL_8 ;hw4/hw6
### ATH:02A718h/02A67Ch - BB_CAL_RXBB_GAIN_TBL_12 ;hw4/hw6
### ATH:02A71Ch/02A680h - BB_CAL_RXBB_GAIN_TBL_16 ;hw4/hw6
### ATH:02A720h/02A684h - BB_CAL_RXBB_GAIN_TBL_20 ;hw4/hw6
### ATH:02A724h/02A688h - BB_CAL_RXBB_GAIN_TBL_24 ;hw4/hw6
Contains 25 table entries (numbered 0..24), with four 6bit entries per word (except, only one entry in the last word).

```
+-----------------------------------------------------------------------------+
|       0-5    TXCAL_RX_BB_GAIN_TABLE_n   ;table entry (n=0,4, 8,12,16,20,24) |
|       6-11   TXCAL_RX_BB_GAIN_TABLE_n   ;table entry (n=1,5, 9,13,17,21)    |
|       12-17  TXCAL_RX_BB_GAIN_TABLE_n   ;table entry (n=2,6,10,14,18,22)    |
|       18-23  TXCAL_RX_BB_GAIN_TABLE_n   ;table entry (n=3,7,11,15,19,23)    |
|       24-31  -                                                              |
+-----------------------------------------------------------------------------+
```


### ATH:02A728h/02A68Ch - BB_TXIQCAL_STATUS_B0 (R) ;hw4/hw6
### ATH:02B68Ch - BB_TXIQCAL_STATUS_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0      TXIQCAL_FAILED                 (R)                       |
|       1-5    CALIBRATED_GAINS               (R)                       |
|       6-11   TONE_GAIN_USED                 (R)                       |
|       12-17  RX_GAIN_USED                   (R)                       |
|       18-24  hw4: LAST_MEAS_ADDR (7bit)     (R)     ;-hw4             |
|       18-23  hw6: LAST_MEAS_ADDR (6bit)     (R)     ;-hw6             |
+-----------------------------------------------------------------------+
```


### ATH:02A7D8h/02A2CCh - BB_FCAL_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-9    FLC_PB_FSTEP                                             |
|       10-19  FLC_SB_FSTEP                                             |
|       20-24  FLC_PB_ATTEN                                             |
|       25-29  FLC_SB_ATTEN                                             |
+-----------------------------------------------------------------------+
```


### ATH:02A7DCh/02A2D0h - BB_FCAL_2_B0 ;hw4/hw6
### ATH:02B2D0h - BB_FCAL_2_B1 ;hw6

```
+----------------------------------------------------------------------------------+
|       0-2    FLC_PWR_THRESH                         ;-global setting (not in B1) |
|       3-7    FLC_SW_CAP_VAL_0/1                     ;-separate settings (on hw6) |
|       8-9    FLC_BBMISCGAIN                         ;\                           
|       10-12  FLC_BB1DBGAIN                          ;                            |
|       13-14  FLC_BB6DBGAIN                          ; global setting (not in B1) |
|       15     FLC_SW_CAP_SET                         ;                            |
|       16-18  FLC_MEAS_WIN                           ;/                           |
|       20-24  FLC_CAP_VAL_STATUS_0/1         (R)     ;-separate settings (on hw6) |
+----------------------------------------------------------------------------------+
```


### ATH:02A7E0h/02A22Ch - BB_RADAR_BW_FILTER ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RADAR_AVG_BW_CHECK                                       |
|       1      RADAR_DC_SRC_SEL                                         |
|       2-3    RADAR_FIRPWR_SEL                                         |
|       4-5    RADAR_PULSE_WIDTH_SEL                                    |
|       8-14   RADAR_DC_FIRPWR_THRESH                                   |
|       15-20  RADAR_DC_PWR_BIAS                                        |
|       21-26  RADAR_BIN_MAX_BW                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A7E4h/02A2D4h - BB_DFT_TONE_CTRL_B0 ;hw4/hw6
### ATH:02B2D4h - BB_DFT_TONE_CTRL_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0      DFT_TONE_EN                                              |
|       2-3    DFT_TONE_AMP_SEL                                         |
|       4-12   DFT_TONE_FREQ_ANG                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A7E8h/02A448h - BB_THERM_ADC_1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    INIT_THERM_SETTING                                       |
|       8-15   INIT_VOLT_SETTING                                        |
|       16-23  INIT_ATB_SETTING                                         |
|       24-25  SAMPLES_CNT_CODING                                       |
|       26     USE_INIT_THERM_VOLT_ATB_AFTER_WARM_RESET                 |
|       27     FORCE_THERM_VOLT_ATB_TO_INIT_SETTINGS                    |
|       28     hw6: CHECK_DONE_FOR_1ST_ADC_MEAS_OF_EACH_FRAME   ;\hw6   
|       29     hw6: THERM_MEASURE_RESET                         ;/      |
+-----------------------------------------------------------------------+
```


### ATH:02A7ECh/02A44Ch - BB_THERM_ADC_2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   MEASURE_THERM_FREQ                                       |
|       12-21  MEASURE_VOLT_FREQ                                        |
|       22-31  MEASURE_ATB_FREQ                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A7F0h/02A450h - BB_THERM_ADC_3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    THERM_ADC_OFFSET                                         |
|       8-16   THERM_ADC_SCALED_GAIN                                    |
|       17-29  ADC_INTERVAL                                             |
+-----------------------------------------------------------------------+
```


### ATH:02A7F4h/02A454h - BB_THERM_ADC_4 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    LATEST_THERM_VALUE             (R)                       |
|       8-15   LATEST_VOLT_VALUE              (R)                       |
|       16-23  LATEST_ATB_VALUE               (R)                       |
|       24     hw6: FORCE_THERM_CHAIN                           ;\hw6   
|       25-27  hw6: PREFERRED_THERM_CHAIN                       ;/      |
+-----------------------------------------------------------------------+
```


### ATH:02A7F8h/02A458h - BB_TX_FORCED_GAIN ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      FORCE_TX_GAIN                                            |
|       1-3    FORCED_TXBB1DBGAIN                                       |
|       4-5    FORCED_TXBB6DBGAIN                                       |
|       6-9    FORCED_TXMXRGAIN                                         |
|       10-13  FORCED_PADRVGNA                                          |
|       14-17  FORCED_PADRVGNB                                          |
|       18-21  FORCED_PADRVGNC                                          |
|       22-23  FORCED_PADRVGND                                          |
|       24     FORCED_ENABLE_PAL                                        |
|       25-27  hw6: FORCED_OB                         ;\                
|       28-30  hw6: FORCED_DB                         ; hw6             |
|       31     hw6: FORCED_GREEN_PAPRD_ENABLE         ;/                |
+-----------------------------------------------------------------------+
```


### ATH:02A7FCh/02A7DCh - BB_ECO_CTRL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    ECO_CTRL                                                 |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ______________ below in hw4.2 and hw6 only (not original hw4) ______________ |
+-----------------------------------------------------------------------------------+
```


### ATH:029DE4h/0298E4h - BB_PAPRD_AM2AM_MASK ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-24   PAPRD_AM2AM_MASK                       ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:029DE8h/0298E8h - BB_PAPRD_AM2PM_MASK ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-24   PAPRD_AM2PM_MASK                       ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:029DECh/0298ECh - BB_PAPRD_HT40_MASK ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-24   PAPRD_HT40_MASK                        ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:029DF0h - BB_PAPRD_CTRL0 ;hw4.2 (not original hw4)
### ATH:0298F0h - BB_PAPRD_CTRL0_B0 ;hw6
### ATH:02A8F0h - BB_PAPRD_CTRL0_B1 ;hw6

```
+---------------------------------------------------------------------------+
|       0      PAPRD_ENABLE                           ;\                    
|       1      PAPRD_ADAPTIVE_USE_SINGLE_TABLE        ; newer revision only |
|       2-26   PAPRD_VALID_GAIN                       ;                     |
|       27-31  PAPRD_MAG_THRSH                        ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:029DF4h - BB_PAPRD_CTRL1 ;hw4.2 (not original hw4)
### ATH:0298F4h - BB_PAPRD_CTRL1_B0 ;hw6
### ATH:02A8F4h - BB_PAPRD_CTRL1_B1 ;hw6

```
+---------------------------------------------------------------------------+
|       0      PAPRD_ADAPTIVE_SCALING_ENABLE          ;\                    
|       1      PAPRD_ADAPTIVE_AM2AM_ENABLE            ;                     |
|       2      PAPRD_ADAPTIVE_AM2PM_ENABLE            ; newer revision only |
|       3-8    PAPRD_POWER_AT_AM2AM_CAL               ;                     |
|       9-16   PA_GAIN_SCALE_FACTOR                   ;                     |
|       17-26  PAPRD_MAG_SCALE_FACTOR                 ;                     |
|       27     PAPRD_TRAINER_IANDQ_SEL                ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:029DF8h - BB_PA_GAIN123 ;hw4.2 (not original hw4)
### ATH:0298F8h - BB_PA_GAIN123_B0 ;hw6
### ATH:02A8F8h - BB_PA_GAIN123_B1 ;hw6

```
+---------------------------------------------------------------------------+
|       0-9    PA_GAIN1                               ;\                    
|       10-19  PA_GAIN2                               ; newer revision only |
|       20-29  PA_GAIN3                               ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:029DFCh - BB_PA_GAIN45 ;hw4.2 (not original hw4)
### ATH:0298FCh - BB_PA_GAIN45_B0 ;hw6
### ATH:02A8FCh - BB_PA_GAIN45_B1 ;hw6

```
+---------------------------------------------------------------------------+
|       0-9    PA_GAIN4                               ;\                    
|       10-19  PA_GAIN5                               ; newer revision only |
|       20-24  PAPRD_ADAPTIVE_TABLE_VALID             ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:029E00h..029E1Ch - BB_PAPRD_PRE_POST_SCALE\_(0..7) ;hw4.2 (not hw4)
### ATH:029900h..02991Ch - BB_PAPRD_PRE_POST_SCALE\_(0..7)\_B0 ;hw6
### ATH:02A900h..02A91Ch - BB_PAPRD_PRE_POST_SCALE\_(0..7)\_B1 ;hw6

```
+---------------------------------------------------------------------------+
|       0-17   PAPRD_PRE_POST_SCALING                 ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:029E20h.. - BB_PAPRD_MEM_TAB\[\...\...\] ;hw4.2 (not original hw4)
### ATH:029920h.. - BB_PAPRD_MEM_TAB_B0\[0..119\] ;hw6
### ATH:02A920h.. - BB_PAPRD_MEM_TAB_B1\[0..119\] ;hw6

```
+---------------------------------------------------------------------------+
|       0-21   PAPRD_MEM                              ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:02A35Ch/02A2ECh - BB_CL_MAP_PAL_0_B0 ;hw4.2/hw6 (not original hw4)
### ATH:02A360h/02A2F0h - BB_CL_MAP_PAL_1_B0 ;hw4.2/hw6 (not original hw4)
### ATH:02A364h/02A2F4h - BB_CL_MAP_PAL_2_B0 ;hw4.2/hw6 (not original hw4)
### ATH:02A368h/02A2F8h - BB_CL_MAP_PAL_3_B0 ;hw4.2/hw6 (not original hw4)
### ATH:02B2ECh - BB_CL_MAP_PAL_0_B1 ;hw6
### ATH:02B2F0h - BB_CL_MAP_PAL_1_B1 ;hw6
### ATH:02B2F4h - BB_CL_MAP_PAL_2_B1 ;hw6
### ATH:02B2F8h - BB_CL_MAP_PAL_3_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   CL_MAP_PAL                                               |
+-----------------------------------------------------------------------+
```


### ATH:02A72Ch/02A690h - BB_PAPRD_TRAINER_CNTL1 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0      CF_PAPRD_TRAIN_ENABLE                  ;\                    
|       1-7    CF_PAPRD_AGC2_SETTLING                 ;                     |
|       8      CF_PAPRD_IQCORR_ENABLE                 ; newer revision only |
|       9      CF_PAPRD_RX_BB_GAIN_FORCE              ;                     |
|       10     CF_PAPRD_TX_GAIN_FORCE                 ;                     |
|       11     CF_PAPRD_LB_ENABLE                     ;                     |
|       12-18  CF_PAPRD_LB_SKIP                       ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:02A730h/02A694h - BB_PAPRD_TRAINER_CNTL2 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-31   CF_PAPRD_INIT_RX_BB_GAIN               ;-newer revision only |
+---------------------------------------------------------------------------+
```


### ATH:02A734h/02A698h - BB_PAPRD_TRAINER_CNTL3 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-5    CF_PAPRD_ADC_DESIRED_SIZE              ;\                    
|       6-11   CF_PAPRD_QUICK_DROP                    ;                     |
|       12-16  CF_PAPRD_MIN_LOOPBACK_DEL              ;                     |
|       17-19  CF_PAPRD_NUM_CORR_STAGES               ; newer revision only |
|       20-23  CF_PAPRD_COARSE_CORR_LEN               ;                     |
|       24-27  CF_PAPRD_FINE_CORR_LEN                 ;/                    |
|       28     hw4.2: CF_PAPRD_BBTXMIX_DISABLE        ;-hw4.2               |
|       28     hw6: CF_PAPRD_REUSE_CORR               ;\hw6                 
|       29     hw6: CF_PAPRD_BBTXMIX_DISABLE          ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:02A738h/02A69Ch - BB_PAPRD_TRAINER_CNTL4 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-11   CF_PAPRD_MIN_CORR                      ;\                    
|       12-15  CF_PAPRD_SAFETY_DELTA                  ; newer revision only |
|       16-25  CF_PAPRD_NUM_TRAIN_SAMPLES             ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:02A73Ch/02A6A0h - BB_PAPRD_TRAINER_STAT1 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0      PAPRD_TRAIN_DONE                       ;\                    
|       1      PAPRD_TRAIN_INCOMPLETE         (R)     ;                     |
|       2      PAPRD_CORR_ERR                 (R)     ; newer revision only |
|       3      PAPRD_TRAIN_ACTIVE             (R)     ;                     |
|       4-8    PAPRD_RX_GAIN_IDX              (R)     ;                     |
|       9-16   PAPRD_AGC2_PWR                 (R)     ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:02A740h/02A6A4h - BB_PAPRD_TRAINER_STAT2 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-15   PAPRD_FINE_VAL                 (R)     ;\                    
|       16-20  PAPRD_COARSE_IDX               (R)     ; newer revision only |
|       21-22  PAPRD_FINE_IDX                 (R)     ;/                    |
+---------------------------------------------------------------------------+
```


### ATH:02A744h/02A6A8h - BB_PAPRD_TRAINER_STAT3 ;hw4.2/hw6 (not original hw4)

```
+---------------------------------------------------------------------------+
|       0-19   PAPRD_TRAIN_SAMPLES_CNT        (R)     ;-newer revision only |
+---------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      ____________________________ below on hw4 only ____________________________ |
+----------------------------------------------------------------------------------+
```


### ATH:02A480h..02A4FCh - BB_TX_GAIN_TAB_PAL\_(1..32) ;hw4 only (not hw6)
Contains 32 table entries (numbered 1..32), with one 32bit entry per word.

```
+-----------------------------------------------------------------------+
|       0-31   TG_TABLE_PAL_ON   entry 1..32 accordingly                |
+-----------------------------------------------------------------------+
```

Seems to be some extra table, alternately to \"BB_TX_GAIN_TAB\_(1..32)\". In hw6, this has been replaced by the \"LSB_EXT\" feature (see BB_TPC_11).

### ATH:02A558h..02A6D4h - BB_TXIQCAL_MEAS_B0\[0..95\] (R) ;hw4 only (not hw6)

```
+----------------------------------------------------------------------------+
|       0-11   TXIQC_MEAS_DATA0_0             (R)   ;entry 0,2,4,...,190 (?) |
|       12-23  TXIQC_MEAS_DATA1_0             (R)   ;entry 1,3,5,...,191 (?) |
|       24-31  -                                                             |
+----------------------------------------------------------------------------+
```


### ATH:02A6D8h - BB_TXIQCAL_START ;hw4 only (not hw6)

```
+-----------------------------------------------------------------------+
|       0      DO_TX_IQCAL                                              |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      ____________________________ below on hw6 only ____________________________ |
+----------------------------------------------------------------------------------+
```


### ATH:029C04h - BB_LDPC_CNTL1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   LDPC_LLR_SCALING0                                        |
+-----------------------------------------------------------------------+
```


### ATH:029C08h - BB_LDPC_CNTL2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   LDPC_LLR_SCALING1                                        |
|       16-26  LDPC_LATENCY                                             |
+-----------------------------------------------------------------------+
```


### ATH:029C18h - BB_ML_CNTL1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-23   CF_ML_2S_WEIGHT_TABLE                                    |
|       24-25  CF_IS_FLAT_CH_THR_ML                                     |
|       26-27  CF_IS_FLAT_CH_THR_ZF                                     |
+-----------------------------------------------------------------------+
```


### ATH:029C1Ch - BB_ML_CNTL2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-23   CF_ML_3S_WEIGHT_TABLE                                    |
+-----------------------------------------------------------------------+
```


### ATH:029E54h - BB_BT_COEX_1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-4    PEAK_DET_TALLY_THR_LOW_1                                 |
|       5-9    PEAK_DET_TALLY_THR_MED_1                                 |
|       10-14  PEAK_DET_TALLY_THR_HIGH_1                                |
|       15-19  RF_GAIN_DROP_DB_LOW_1                                    |
|       20-24  RF_GAIN_DROP_DB_MED_1                                    |
|       25-29  RF_GAIN_DROP_DB_HIGH_1                                   |
|       30     BT_TX_DISABLE_NF_CAL                                     |
+-----------------------------------------------------------------------+
```


### ATH:029E58h - BB_BT_COEX_2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-4    PEAK_DET_TALLY_THR_LOW_2                                 |
|       5-9    PEAK_DET_TALLY_THR_MED_2                                 |
|       10-14  PEAK_DET_TALLY_THR_HIGH_2                                |
|       15-19  RF_GAIN_DROP_DB_LOW_2                                    |
|       20-24  RF_GAIN_DROP_DB_MED_2                                    |
|       25-29  RF_GAIN_DROP_DB_HIGH_2                                   |
|       30-31  RFSAT_RX_RX                                              |
+-----------------------------------------------------------------------+
```


### ATH:029E5Ch - BB_BT_COEX_3 ;hw6

```
+-----------------------------------------------------------------------+
|       0-1    RFSAT_BT_SRCH_SRCH                                       |
|       2-3    RFSAT_BT_RX_SRCH                                         |
|       4-5    RFSAT_BT_SRCH_RX                                         |
|       6-7    RFSAT_WLAN_SRCH_SRCH                                     |
|       8-9    RFSAT_WLAN_RX_SRCH                                       |
|       10-11  RFSAT_WLAN_SRCH_RX                                       |
|       12-13  RFSAT_EQ_SRCH_SRCH                                       |
|       14-15  RFSAT_EQ_RX_SRCH                                         |
|       16-17  RFSAT_EQ_SRCH_RX                                         |
|       18-22  RF_GAIN_DROP_DB_NON_1                                    |
|       23-27  RF_GAIN_DROP_DB_NON_2                                    |
|       28-31  BT_RX_FIRPWR_INCR                                        |
+-----------------------------------------------------------------------+
```


### ATH:029E60h - BB_BT_COEX_4 ;RFGAIN_EQV_LNA_0..3 ;hw6
### ATH:029E64h - BB_BT_COEX_5 ;RFGAIN_EQV_LNA_4..7 ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    RFGAIN_EQV_LNA_0 / RFGAIN_EQV_LNA_4                      |
|       8-15   RFGAIN_EQV_LNA_1 / RFGAIN_EQV_LNA_5                      |
|       16-23  RFGAIN_EQV_LNA_2 / RFGAIN_EQV_LNA_6                      |
|       24-31  RFGAIN_EQV_LNA_3 / RFGAIN_EQV_LNA_7                      |
+-----------------------------------------------------------------------+
```


### ATH:029E68h - BB_REDPWR_CTRL_1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-1    REDPWR_MODE                                              |
|       2      REDPWR_MODE_CLR                                          |
|       3      REDPWR_MODE_SET                                          |
|       4-8    GAIN_CORR_DB2                                            |
|       9-12   SCFIR_ADJ_GAIN                                           |
|       13-17  QUICKDROP_RF                                             |
|       18     BYPASS_FIR_F                                             |
|       19     ADC_HALF_REF_F                                           |
+-----------------------------------------------------------------------+
```


### ATH:029E6Ch - BB_REDPWR_CTRL_2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-6    SC01_SW_INDEX                                            |
|       7-13   SC10_SW_INDEX                                            |
|       14-20  LAST_SC0_INDEX                                           |
+-----------------------------------------------------------------------+
```


### ATH:029FD0h - BB_MRC_CCK_CTRL ;hw6

```
+-----------------------------------------------------------------------+
|       0      BBB_MRC_EN                                               |
|       1      AGCDP_CCK_MRC_MUX_REG                                    |
|       2-4    AGCDP_CCK_PD_ACCU_THR_HI                                 |
|       5-7    AGCDP_CCK_PD_ACCU_THR_LOW                                |
|       8-11   AGCDP_CCK_BARKER_RSSI_THR                                |
|       12-16  AGCDP_CCK_MRC_BK_THR_HI                                  |
|       17-21  AGCDP_CCK_MRC_BK_THR_LOW                                 |
|       22-27  AGCDP_CCK_MIN_VALUE                                      |
+-----------------------------------------------------------------------+
```


### ATH:029FD4h - BB_CCK_BLOCKER_DET ;hw6

```
+-----------------------------------------------------------------------+
|       0      CCK_FREQ_SHIFT_BLOCKER_DETECTION                         |
|       1      CCK_BLOCKER_DET_RESTART_WEAK_SIG                         |
|       2-5    CCK_BLOCKER_DET_BKSUM_NUM                                |
|       6-8    BK_VALID_DELAY                                           |
|       9-13   CCK_BLOCKER_DET_THR                                      |
|       14-19  CCK_BLOCKER_DET_DELAY_THR                                |
|       20-25  CCK_BLOCKER_MONITOR_TIME                                 |
|       26     SKIP_RAMP_ENABLE                                         |
|       27-31  CCK_DET_RAMP_THR                                         |
+-----------------------------------------------------------------------+
```


### ATH:02A384h - BB_SM_HIST ;hw6

```
+-----------------------------------------------------------------------+
|       0      SM_REC_EN                                                |
|       1      SM_REC_MODE                                              |
|       2-3    SM_REC_TIME_RES                                          |
|       4-11   SM_REC_PART_EN                                           |
|       12-14  SM_REC_CHN_EN                                            |
|       15-18  SM_REC_DATA_NUM                                          |
|       19     SM_REC_AGC_SEL                                           |
|       20-22  SM_REC_MAC_TRIG                                          |
|       24-29  SM_REC_LAST_ADDR               (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02A580h - BB_RTT_CTRL ;hw6

```
+-----------------------------------------------------------------------+
|       0      ENA_RADIO_RETENTION                                      |
|       1-6    RESTORE_MASK                                             |
|       7      FORCE_RADIO_RESTORE                                      |
+-----------------------------------------------------------------------+
```


### ATH:0298BCh - BB_GREEN_TX_CONTROL_1 ;hw6

```
+-----------------------------------------------------------------------+
|       0      GREEN_TX_ENABLE                                          |
|       1      GREEN_CASES                                              |
+-----------------------------------------------------------------------+
```


### ATH:02D800h - BB_MIT_RF_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0      MIT_FORCE_SYNTH_ON                                       |
|       1      MIT_FORCE_SYNTH_ON_EN                                    |
|       2      MIT_FORCE_ACTIVE_ON                                      |
+-----------------------------------------------------------------------+
```


### ATH:02D804h - BB_MIT_CCA_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-2    MIT_CCA_MODE_SEL                                         |
|       3-20   MIT_CCA_COUNT                                            |
+-----------------------------------------------------------------------+
```


### ATH:02D808h - BB_MIT_RSSI_CNTL_1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-5    MIT_RSSI_TH                                              |
|       6-11   MIT_RX_RF_ATT_TH_H                                       |
|       12-17  MIT_RX_RF_ATT_TH_L                                       |
|       18-23  MIT_RX_RF_ATT_OFFSET                                     |
|       24-29  MIT_AGC_LIMIT                                            |
+-----------------------------------------------------------------------+
```


### ATH:02D80Ch - BB_MIT_RSSI_CNTL_2 ;hw6

```
+-----------------------------------------------------------------------+
|       0      MIT_AGC_SEL                                              |
|       1-11   MIT_RSSI_BASE                                            |
+-----------------------------------------------------------------------+
```


### ATH:02D810h - BB_MIT_TX_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    MIT_TX_STA_CNT                                           |
|       8-21   MIT_TX_END_DLY_CNT                                       |
|       22     MIT_TX_THROUGH_ENA                                       |
|       23-25  MIT_TXHDR_CHAIN_MASK_CCK                                 |
|       26-28  MIT_TXHDR_PAPRD_TRAIN_MASK_CCK                           |
|       29-30  MIT_TXHDR_CHAN_MODE_CCK                                  |
+-----------------------------------------------------------------------+
```


### ATH:02D814h - BB_MIT_RX_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    MIT_RX_END_DLY_CNT                                       |
|       8      MIT_RX_THROUGH_ENA                                       |
+-----------------------------------------------------------------------+
```


### ATH:02D818h - BB_MIT_OUT_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-1    MIT_CLK_TUNE_MOD                                         |
|       2      MIT_NO_DATA_TO_ATH                                       |
+-----------------------------------------------------------------------+
```


### ATH:02D81Ch - BB_MIT_SPARE_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-30   MIT_SPARE_IN                                             |
|       31     MIT_SPARE_OUT                  (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:029F90h - BB_DC_CAL_STATUS_B0 (R) ;hw6
### ATH:02AF90h - BB_DC_CAL_STATUS_B1 (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0-4    OFFSETC1I                      (R)                       |
|       5-9    OFFSETC1Q                      (R)                       |
|       10-14  OFFSETC2I                      (R)                       |
|       15-19  OFFSETC2Q                      (R)                       |
|       20-24  OFFSETC3I                      (R)                       |
|       25-29  OFFSETC3Q                      (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02A584h - BB_RTT_TABLE_SW_INTF_B0 ;hw6
### ATH:02B584h - BB_RTT_TABLE_SW_INTF_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       0      SW_RTT_TABLE_ACCESS                                      |
|       1      SW_RTT_TABLE_WRITE                                       |
|       2-4    SW_RTT_TABLE_ADDR                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A588h - BB_RTT_TABLE_SW_INTF_1_B0 ;hw6
### ATH:02B588h - BB_RTT_TABLE_SW_INTF_1_B1 ;hw6

```
+-----------------------------------------------------------------------+
|       4-31   SW_RTT_TABLE_DATA                                        |
+-----------------------------------------------------------------------+
```


### ATH:02A7F0h - BB_TABLES_INTF_ADDR_B0 ;hw6
### ATH:02B7F0h - BB_TABLES_INTF_ADDR_B1 ;hw6
### ATH:029BF0h - BB_CHN_TABLES_INTF_ADDR ;hw6
### ATH:02ABF0h - BB_CHN1_TABLES_INTF_ADDR ;hw6

```
+-----------------------------------------------------------------------+
|       2-17   TABLES_ADDR                                              |
|       31     ADDR_AUTO_INCR                                           |
+-----------------------------------------------------------------------+
```


### ATH:02A7F4h - BB_TABLES_INTF_DATA_B0 ;hw6
### ATH:02B7F4h - BB_TABLES_INTF_DATA_B1 ;hw6
### ATH:029BF4h - BB_CHN_TABLES_INTF_DATA ;hw6
### ATH:02ABF4h - BB_CHN1_TABLES_INTF_DATA ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   TABLES_DATA                                              |
+-----------------------------------------------------------------------+
```


### ATH:02CE00h - BB_DUMMY (R) ;hw6
### ATH:02C800h - BB_DUMMY1\[0..255\] (R) ;hw6
### ATH:02D200h - BB_DUMMY2\[0..383\] (R) ;hw6

```
+-----------------------------------------------------------------------+
|       0      DUMMY                          (R)                       |
+-----------------------------------------------------------------------+
```

Whatever \"dummy\" registers, maybe intended only for padding purposes; to get the three BB_RSSI_B0/B1/B3 registers mapped to 029F80h+(0,1,3)\*1000h on hw6.


```
+----------------------------------------------------------------------------------+
|      _______________________ missing B1 registers in hw4 _______________________ |
+----------------------------------------------------------------------------------+
```


hw4 does have only a few \"B1\" registers defined, although it does have a lot of \"B0\" registers - which would suggest the presence of corresponding \"B1\" registers, but those seem to exist only on hw6.
Maybe the hw4 designed was already aimed at adding \"B1\" registers in future.
Or maybe the \"B1\" registers DO EXIST even on hw4, being accessd by using something like \"address of B0 register PLUS some offset\", or by using the so-called \"BASEBAND_2\" and/or \"BASEBAND_3\" regions - and without mentioning that anywhere in hw4 source code?



