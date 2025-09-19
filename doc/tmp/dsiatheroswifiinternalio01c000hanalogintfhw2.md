# DSi Atheros Wifi - Internal I/O - 01C000h - Analog Intf (hw2)


### ATH:01C000h - SYNTH_SYNTH1 ;aka - PHY_ANALOG_SYNTH1

```
+-----------------------------------------------------------------------+
|       0      MONITOR_SYNTHLOCKVCOK                                    |
|       1      MONITOR_VC2LOW                                           |
|       2      MONITOR_VC2HIGH                                          |
|       3      MONITOR_FB_DIV2                                          |
|       4      MONITOR_REF                                              |
|       5      MONITOR_FB                                               |
|       6      PWUP_LOBUF5G_PD                                          |
|       7      PWUP_LOMIX_PD                                            |
|       8      PWUP_LODIV_PD                                            |
|       9      PWUP_VCOBUF_PD                                           |
|       10-12  SEL_VCMONABUS                                            |
|       13     CON_IVCOBUF                                              |
|       14     CON_IVCOREG                                              |
|       15     CON_VDDVCOREG                                            |
|       16     SPARE_PWD                                                |
|       17     SLIDINGIF                                                |
|       18-19  VCOREGBIAS                                               |
|       20-21  VCOREGLEVEL                                              |
|       22     VCOREGBYPASS                                             |
|       23     PWD_LOBUF5G                                              |
|       24     FORCE_LO_ON                                              |
|       25     PWD_LOMIX                                                |
|       26     PWD_LODIV                                                |
|       27     PWD_PRESC                                                |
|       28     PWD_VCO                                                  |
|       29     PWD_VCMON                                                |
|       30     PWD_CP                                                   |
|       31     PWD_BIAS                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C004h - SYNTH_SYNTH2 ;aka - PHY_ANALOG_SYNTH2 (one part)

```
+-----------------------------------------------------------------------+
|       0-2    SPARE_BITS                                               |
|       3-4    LOOP_CS                                                  |
|       5-9    LOOP_RS                                                  |
|       10-14  LOOP_CP                                                  |
|       15-19  LOOP_3RD_ORDER_R                                         |
|       20-22  VC_LOW_REF                                               |
|       23-25  VC_MID_REF                                               |
|       26-28  VC_HI_REF                                                |
|       29-31  VC_CAL_REF                                               |
+-----------------------------------------------------------------------+
```


### ATH:01C008h - SYNTH_SYNTH3 ;aka - PHY_ANALOG_SYNTH3

```
+-----------------------------------------------------------------------+
|       0-5    WAIT_VC_CHECK                                            |
|       6-11   WAIT_CAL_LIN                                             |
|       12-17  WAIT_CAL_BIN                                             |
|       18-23  WAIT_PWRUP                                               |
|       24-29  WAIT_SHORTR_PWRUP                                        |
|       30     SEL_CLK_DIV2                                             |
|       31     DIS_CLK_XTAL                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C00Ch - SYNTH_SYNTH4 ;aka - PHY_ANALOG_SYNTH4

```
+-----------------------------------------------------------------------+
|       0      FORCE_SHIFTREG                                           |
|       1      LONGSHIFTSEL                                             |
|       2-3    SPARE_MISC                                               |
|       4      SEL_CLKXTAL_EDGE                                         |
|       5      PSCOUNT_FBSEL                                            |
|       6-7    SDM_DITHER                                               |
|       8      SDM_MODE                                                 |
|       9      SDM_DISABLE                                              |
|       10     RESET_PRESC                                              |
|       11-12  PRESCSEL                                                 |
|       13     PFD_DISABLE                                              |
|       14     PFDDELAY                                                 |
|       15-16  REFDIVSEL                                                |
|       17     VCOCAPPULLUP                                             |
|       18-25  VCOCAP_OVR                                               |
|       26     FORCE_VCOCAP                                             |
|       27     FORCE_PINVC                                              |
|       28     SHORTR_UNTIL_LOCKED                                      |
|       29     ALWAYS_SHORTR                                            |
|       30     DIS_LOSTVC                                               |
|       31     DIS_LIN_CAPSEARCH                                        |
+-----------------------------------------------------------------------+
```


### ATH:01C010h - SYNTH_SYNTH5 ;aka - PHY_ANALOG_SYNTH2 (other part)

```
+-----------------------------------------------------------------------+
|       0-1    SPARE                                                    |
|       2-3    LOBUF5GTUNE_OVR                                          |
|       4      FORCE_LOBUF5GTUNE                                        |
|       5-8    CAPRANGE3                                                |
|       9-12   CAPRANGE2                                                |
|       13-16  CAPRANGE1                                                |
|       17-20  LOOPLEAKCUR                                              |
|       21     CPLOWLK                                                  |
|       22     CPSTEERING_EN                                            |
|       23-24  CPBIAS                                                   |
|       25-27  SLOPE_IP                                                 |
|       28-31  LOOP_IP0                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C014h - SYNTH_SYNTH6

```
+-----------------------------------------------------------------------+
|       0-2    SPARE_BIAS                                               |
|       3-4    VCOBUFBIAS                                               |
|       5-7    ICVCO                                                    |
|       8-10   ICSPAREB                                                 |
|       11-13  ICSPAREA                                                 |
|       14-16  ICLOMIX                                                  |
|       17-19  ICLODIV                                                  |
|       20-22  ICPRESC                                                  |
|       23-25  IRSPARE                                                  |
|       26-28  IRVCMON                                                  |
|       29-31  IRCP                                                     |
+-----------------------------------------------------------------------+
```


### ATH:01C018h - SYNTH_SYNTH7 ;aka \"PHY_ANALOG_SYNTH6\" (six) on later hw

```
+-----------------------------------------------------------------------+
|       0-2    SPARE_READ                                               |
|       3-4    LOBUF5GTUNE                                              |
|       5-8    LOOP_IP                                                  |
|       9      VC2LOW                                                   |
|       10     VC2HIGH                                                  |
|       11     RESET_SDM_B                                              |
|       12     RESET_PSCOUNTERS                                         |
|       13     RESET_PFD                                                |
|       14     RESET_RFD                                                |
|       15     SHORT_R                                                  |
|       16-23  VCO_CAP_ST                                               |
|       24     PIN_VC                                                   |
|       25     SYNTH_LOCK_VC_OK                                         |
|       26     CAP_SEARCH                                               |
|       27-30  SYNTH_SM_STATE                                           |
|       31     SYNTH_ON                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C01Ch - SYNTH_SYNTH8 ;aka \"PHY_ANALOG_SYNTH7\" (seven) on later hw

```
+-----------------------------------------------------------------------+
|       0      FORCE_FRACLSB                                            |
|       1-17   CHANFRAC                                                 |
|       18-26  CHANSEL                                                  |
|       27     SPARE                                                    |
|       28-29  AMODEREFSEL                                              |
|       30     FRACMODE                                                 |
|       31     LOADSYNTHCHANNEL                                         |
+-----------------------------------------------------------------------+
```


### ATH:01C020h - RF5G_RF5G1

```
+-----------------------------------------------------------------------+
|       0-1    SPARE                                                    |
|       2      REGLO_BYPASS5                                            |
|       3      LO5CONTROL                                               |
|       4-6    LO5_ATB_SEL                                              |
|       7      PDREGLO5                                                 |
|       8      PDLO5AGC                                                 |
|       9      PDQBUF5                                                  |
|       10     PDLO5MIX                                                 |
|       11     PDLO5DIV                                                 |
|       12-14  TX5_ATB_SEL                                              |
|       15-17  OB5                                                      |
|       18-20  DB5                                                      |
|       21-23  PWDTXPKD                                                 |
|       24-26  TUNE_PADRV5                                              |
|       27     PDPAOUT5                                                 |
|       28     PDPADRV5                                                 |
|       29     PDTXBUF5                                                 |
|       30     PDTXMIX5                                                 |
|       31     PDTXLO5                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C024h - RF5G_RF5G2

```
+-----------------------------------------------------------------------+
|       0-1    SPARE                                                    |
|       2-4    TUNE_LO                                                  |
|       5      ENABLE_PCA                                               |
|       6-7    LNA5_ATTENMODE                                           |
|       8      REGFE_BYPASS5                                            |
|       9-11   BVGM5                                                    |
|       12-14  BCSLNA5                                                  |
|       15-17  BRFVGA5                                                  |
|       18-20  TUNE_RFVGA5                                              |
|       21     PDREGFE5                                                 |
|       22     PDRFVGA5                                                 |
|       23     PDCSLNA5                                                 |
|       24     PDVGM5                                                   |
|       25     PDCMOSLO5                                                |
|       26-28  RX5_ATB_SEL                                              |
|       29-31  AGCLO_B                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C028h - RF2G_RF2G1

```
+-----------------------------------------------------------------------+
|       0-4    SPARE                                                    |
|       5      SHORTLNA2                                                |
|       6      LOCONTROL                                                |
|       7      SELLNA                                                   |
|       8-10   RF_ATB_SEL                                               |
|       11-13  FE_ATB_SEL                                               |
|       14-16  OB                                                       |
|       17-19  DB                                                       |
|       20-22  BLNA2                                                    |
|       23-25  BLNA1BUF                                                 |
|       26-28  BLNA1F                                                   |
|       29-31  BLNA1                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C02Ch - RF2G_RF2G2

```
+-----------------------------------------------------------------------+
|       0-16   SPARE                                                    |
|       17     ENABLE_PCB                                               |
|       18     REGLO_BYPASS                                             |
|       19     REGLNA_BYPASS                                            |
|       20     PDTXMIX                                                  |
|       21     PDTXLO                                                   |
|       22     PDRXLO                                                   |
|       23     PDRFGM                                                   |
|       24     PDREGLO                                                  |
|       25     PDREGLNA                                                 |
|       26     PDPAOUT                                                  |
|       27     PDPADRV                                                  |
|       28     PDDIV                                                    |
|       29     PDCSLNA                                                  |
|       30     PDCGLNABUF                                               |
|       31     PDCGLNA                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C030h - TOP_GAIN

```
+-----------------------------------------------------------------------+
|       0      SPARE                                                    |
|       1-2    RX6DBHIQGAIN                                             |
|       3-5    RX1DBLOQGAIN                                             |
|       6-7    RX6DBLOQGAIN                                             |
|       8-10   RFGMGN                                                   |
|       11-12  RFVGA5GAIN                                               |
|       13-16  LNAGAIN                                                  |
|       17     LNAON                                                    |
|       18-20  PAOUT2GN                                                 |
|       21-23  PADRVGN                                                  |
|       24     PABUF5GN                                                 |
|       25-26  TXV2IGAIN                                                |
|       27-29  TX1DBLOQGAIN                                             |
|       30-31  TX6DBLOQGAIN                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C034h - TOP_TOP

```
+-----------------------------------------------------------------------+
|       0      FORCE_XPAON                                              |
|       1      INT2GND                                                  |
|       2      PAD2GND                                                  |
|       3      INTH2PAD                                                 |
|       4      INT2PAD                                                  |
|       5-7    REVID                                                    |
|       8-9    DATAOUTSEL                                               |
|       10     PDBIAS                                                   |
|       11     SYNTHON_FORCE                                            |
|       12     SCLKEN_FORCE                                             |
|       13     OSCON                                                    |
|       14     PWDCLKIN                                                 |
|       15     LOCALXTAL                                                |
|       16     PWDDAC                                                   |
|       17     PWDADC                                                   |
|       18     PWDPLL                                                   |
|       19     LOCALADDAC                                               |
|       20     CALTX                                                    |
|       21     PAON                                                     |
|       22     TXON                                                     |
|       23     RXON                                                     |
|       24     SYNTHON                                                  |
|       25     BMODE                                                    |
|       26     CAL_RESIDUE                                              |
|       27     CALDC                                                    |
|       28     CALFC                                                    |
|       29     LOCALMODE                                                |
|       30     LOCALRXGAIN                                              |
|       31     LOCALTXGAIN                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C038h - BIAS_BIAS_SEL

```
+-----------------------------------------------------------------------+
|       0      PWD_ICLDO25                                              |
|       1-3    PWD_ICTXPC25                                             |
|       4-6    PWD_ICTSENS25                                            |
|       7-9    PWD_ICXTAL25                                             |
|       10-12  PWD_ICCOMPBIAS25                                         |
|       13     PWD_ICCPLL25                                             |
|       14     PWD_ICREFOPAMPBIAS25                                     |
|       15     PWD_IRREFMASTERBIAS12P5                                  |
|       16     PWD_IRDACREGREF12P5                                      |
|       17-19  PWD_ICREFBUFBIAS12P5                                     |
|       20     SPARE                                                    |
|       21-24  SEL_SPARE                                                |
|       25-30  SEL_BIAS                                                 |
|       31     PADON                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C03Ch - BIAS_BIAS1

```
+-----------------------------------------------------------------------+
|       0-1    SPARE                                                    |
|       2-4    PWD_IC5GMIXQ25                                           |
|       5-7    PWD_IC5GQB25                                             |
|       8-10   PWD_IC5GTXBUF25                                          |
|       11-13  PWD_IC5GTXPA25                                           |
|       14     PWD_IC5GRXRF25                                           |
|       15     PWD_ICDETECTORA25                                        |
|       16     PWD_ICDETECTORB25                                        |
|       17-19  PWD_IC2GLNAREG25                                         |
|       20-22  PWD_IC2GLOREG25                                          |
|       23-25  PWD_IC2GRFFE25                                           |
|       26-28  PWD_IC2GVGM25                                            |
|       29-31  PWD_ICDAC2BB25                                           |
+-----------------------------------------------------------------------+
```


### ATH:01C040h - BIAS_BIAS2

```
+-----------------------------------------------------------------------+
|       0-2    PWD_IR5GRFVREF2525                                       |
|       3-5    PWD_IR2GLNAREG25                                         |
|       6-8    PWD_IR2GLOREG25                                          |
|       9-11   PWD_IR2GTXMIX25                                          |
|       12     PWD_IRLDO25                                              |
|       13-15  PWD_IRTXPC25                                             |
|       16-18  PWD_IRTSENS25                                            |
|       19-21  PWD_IRXTAL25                                             |
|       22     PWD_IRPLL25                                              |
|       23-25  PWD_IC5GLOREG25                                          |
|       26-28  PWD_IC5GDIV25                                            |
|       29-31  PWD_IC5GMIXI25                                           |
+-----------------------------------------------------------------------+
```


### ATH:01C044h - BIAS_BIAS3

```
+-----------------------------------------------------------------------+
|       0      SPARE                                                    |
|       1-3    PWD_ICDACREG12P5                                         |
|       4-6    PWD_IR25SPARE2                                           |
|       7-9    PWD_IR25SPARE1                                           |
|       10-12  PWD_IC25SPARE2                                           |
|       13-15  PWD_IC25SPARE1                                           |
|       16     PWD_IRBB50                                               |
|       17     PWD_IRSYNTH50                                            |
|       18-20  PWD_IC2GDIV50                                            |
|       21     PWD_ICBB50                                               |
|       22     PWD_ICSYNTH50                                            |
|       23-25  PWD_ICDAC50                                              |
|       26-28  PWD_IR5GAGC25                                            |
|       29-31  PWD_IR5GTXMIX25                                          |
+-----------------------------------------------------------------------+
```


### ATH:01C048h - TXPC_TXPC

```
+-----------------------------------------------------------------------+
|       0-1    ATBSEL                                                   |
|       2      SELCOUNT                                                 |
|       3-4    SELINIT                                                  |
|       5      ON1STSYNTHON                                             |
|       6-13   N                                                        |
|       14-15  TSMODE                                                   |
|       16     SELCMOUT                                                 |
|       17     SELMODREF                                                |
|       18     CLKDELAY                                                 |
|       19     NEGOUT                                                   |
|       20     CURHALF                                                  |
|       21     TESTPWDPC                                                |
|       22-27  TESTDAC                                                  |
|       28-29  TESTGAIN                                                 |
|       30     TEST                                                     |
|       31     SELINTPD                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C04Ch - TXPC_MISC

```
+-----------------------------------------------------------------------+
|       0-5    SPARE                                                    |
|       6-7    XTALDIV                                                  |
|       8-17   DECOUT                                                   |
|       18-20  SPARE_A                                                  |
|       21     SELTSN                                                   |
|       22     SELTSP                                                   |
|       23     LOCALBIAS2X                                              |
|       24     LOCALBIAS                                                |
|       25     PWDXINPAD                                                |
|       26     PWDCLKIND                                                |
|       27     NOTCXODET                                                |
|       28     LDO_TEST_MODE                                            |
|       29-30  LEVEL                                                    |
|       31     FLIPBMODE                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C050h - RXTXBB_RXTXBB1

```
+-----------------------------------------------------------------------+
|       0      PDHIQ                                                    |
|       1      PDLOQ                                                    |
|       2      PDOFFSETI2V                                              |
|       3      PDOFFSETHIQ                                              |
|       4      PDOFFSETLOQ                                              |
|       5      PDRXTXBB                                                 |
|       6      PDI2V                                                    |
|       7      PDV2I                                                    |
|       8      PDDACINTERFACE                                           |
|       6-16   SEL_ATB                                                  |
|       17-18  FNOTCH                                                   |
|       19-31  SPARE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C054h - RXTXBB_RXTXBB2

```
+-----------------------------------------------------------------------+
|       0      PATH_OVERRIDE                                            |
|       1      PATH1LOQ_EN                                              |
|       2      PATH2LOQ_EN                                              |
|       3      PATH3LOQ_EN                                              |
|       4      PATH1HIQ_EN                                              |
|       5      PATH2HIQ_EN                                              |
|       6      FILTERDOUBLEBW                                           |
|       7      LOCALFILTERTUNING                                        |
|       8-12   FILTERFC                                                 |
|       13-14  CMSEL                                                    |
|       15     SEL_I2V_TEST                                             |
|       16     SEL_HIQ_TEST                                             |
|       17     SEL_LOQ_TEST                                             |
|       18     SEL_DAC_TEST                                             |
|       19     SELBUFFER                                                |
|       20     SHORTBUFFER                                              |
|       21-22  SPARE                                                    |
|       23-25  IBN_37P5_OSI2V_CTRL                                      |
|       26-28  IBN_37P5_OSLO_CTRL                                       |
|       29-31  IBN_37P5_OSHI_CTRL                                       |
+-----------------------------------------------------------------------+
```


### ATH:01C058h - RXTXBB_RXTXBB3

```
+-----------------------------------------------------------------------+
|       0-2    IBN_100U_TEST_CTRL                                       |
|       3-5    IBRN_12P5_CM_CTRL                                        |
|       6-8    IBN_25U_LO2_CTRL                                         |
|       9-11   IBN_25U_LO1_CTRL                                         |
|       12-14  IBN_25U_HI2_CTRL                                         |
|       15-17  IBN_25U_HI1_CTRL                                         |
|       18-20  IBN_25U_I2V_CTRL                                         |
|       21-23  IBN_25U_BKV2I_CTRL                                       |
|       24-26  IBN_25U_CM_BUFAMP_CTRL                                   |
|       27-31  SPARE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C05Ch - RXTXBB_RXTXBB4

```
+-----------------------------------------------------------------------+
|       0-4    OFSTCORRI2VQ                                             |
|       5-9    OFSTCORRI2VI                                             |
|       10-14  OFSTCORRLOQ                                              |
|       15-19  OFSTCORRLOI                                              |
|       20-24  OFSTCORRHIQ                                              |
|       25-29  OFSTCORRHII                                              |
|       30     LOCALOFFSET                                              |
|       31     SPARE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C060h - ADDAC_ADDAC1 ;aka \"A/D and D/A Converter\"

```
+-----------------------------------------------------------------------+
|       0-5    SPARE                                                    |
|       6      DISABLE_DAC_REG                                          |
|       7-8    CM_SEL                                                   |
|       9      INV_CLK160_ADC                                           |
|       10     SELMANPWDS                                               |
|       11     FORCEMSBLOW                                              |
|       12     PWDDAC                                                   |
|       13     PWDADC                                                   |
|       14     PWDPLL                                                   |
|       15-22  PLL_FILTER                                               |
|       23-25  PLL_ICP                                                  |
|       26-27  PLL_ATB                                                  |
|       28-30  PLL_SCLAMP                                               |
|       31     PLL_SVREG                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C080h - SW_OVERRIDE

```
+-----------------------------------------------------------------------+
|       0      ENABLE                                                   |
|       1      SUPDATE_DELAY                                            |
+-----------------------------------------------------------------------+
```


### ATH:01C084h - SIN_VAL

```
+-----------------------------------------------------------------------+
|       0      SIN                                                      |
+-----------------------------------------------------------------------+
```


### ATH:01C088h - SW_SCLK

```
+-----------------------------------------------------------------------+
|       0      SW_SCLK                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C08Ch - SW_CNTL

```
+-----------------------------------------------------------------------+
|       0      SW_SOUT                                                  |
|       1      SW_SUPDATE                                               |
|       2      SW_SCAPTURE                                              |
+-----------------------------------------------------------------------+
```




