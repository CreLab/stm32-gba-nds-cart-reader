# DSi Atheros Wifi - Internal I/O - 01C000h - Analog Intf (hw4/hw6)


These registers are same in hw4/hw6, except for some small differences:

```
+-----------------------------------------------------------------------+
|       0001C050h  one new bit in hw6.0                                 |
|       0001C148h  several new bits in hw6.0                            |
|       0001C740h  added/removed/renumbered bits in hw6.0               |
|       0001C744h  two changed/renamed bits in hw6.0                    |
+-----------------------------------------------------------------------+
```


### ATH:01C000h - PHY_ANALOG_RXRF_BIAS1

```
+-----------------------------------------------------------------------+
|       0      SPARE                                                    |
|       1-3    PWD_IR25SPARE                                            |
|       4-6    PWD_IR25LO18                                             |
|       7-9    PWD_IC25LO36                                             |
|       10-12  PWD_IC25MXR2_5GH                                         |
|       13-15  PWD_IC25MXR5GH                                           |
|       16-18  PWD_IC25VGA5G                                            |
|       19-21  PWD_IC75LNA5G                                            |
|       22-24  PWD_IR25LO24                                             |
|       25-27  PWD_IC25MXR2GH                                           |
|       28-30  PWD_IC75LNA2G                                            |
|       31     PWD_BIAS                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C004h - PHY_ANALOG_RXRF_BIAS2

```
+-----------------------------------------------------------------------+
|       0      SPARE                                                    |
|       1-3    PKEN                                                     |
|       4-6    VCMVALUE                                                 |
|       7      PWD_VCMBUF                                               |
|       8-10   PWD_IR25SPAREH                                           |
|       11-13  PWD_IR25SPARE                                            |
|       14-16  PWD_IC25LNABUF                                           |
|       17-19  PWD_IR25AGCH                                             |
|       20-22  PWD_IR25AGC                                              |
|       23-25  PWD_IC25AGC                                              |
|       26-28  PWD_IC25VCMBUF                                           |
|       29-31  PWD_IR25VCM                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C008h - PHY_ANALOG_RXRF_GAINSTAGES

```
+-----------------------------------------------------------------------+
|       0      SPARE                                                    |
|       1      LNAON_CALDC                                              |
|       2-3    VGA5G_CAP                                                |
|       4-5    LNA5G_CAP                                                |
|       6      LNA5G_SHORTINP                                           |
|       7      PWD_LO5G                                                 |
|       8      PWD_VGA5G                                                |
|       9      PWD_MXR5G                                                |
|       10     PWD_LNA5G                                                |
|       11-12  LNA2G_CAP                                                |
|       13     LNA2G_SHORTINP                                           |
|       14     LNA2G_LP                                                 |
|       15     PWD_LO2G                                                 |
|       16     PWD_MXR2G                                                |
|       17     PWD_LNA2G                                                |
|       18-19  MXR5G_GAIN_OVR                                           |
|       20-22  VGA5G_GAIN_OVR                                           |
|       23-25  LNA5G_GAIN_OVR                                           |
|       26-27  MXR2G_GAIN_OVR                                           |
|       28-30  LNA2G_GAIN_OVR                                           |
|       31     RX_OVERRIDE                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C00Ch - PHY_ANALOG_RXRF_AGC

```
+-----------------------------------------------------------------------+
|       0      RF5G_ON_DURING_CALPA                                     |
|       1      RF2G_ON_DURING_CALPA                                     |
|       2      AGC_OUT                        (R)                       |
|       3      LNABUFGAIN2X                                             |
|       4      LNABUF_PWD_OVR                                           |
|       5      PWD_LNABUF                                               |
|       6-8    AGC_FALL_CTRL                                            |
|       9-14   AGC5G_CALDAC_OVR                                         |
|       15-18  AGC5G_DBDAC_OVR                                          |
|       19-24  AGC2G_CALDAC_OVR                                         |
|       25-28  AGC2G_DBDAC_OVR                                          |
|       29     AGC_CAL_OVR                                              |
|       30     AGC_ON_OVR                                               |
|       31     AGC_OVERRIDE                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C040h - PHY_ANALOG_TXRF1

```
+-----------------------------------------------------------------------+
|       0      PDLOBUF5G                                                |
|       1      PDLODIV5G                                                |
|       2      LOBUF5GFORCED                                            |
|       3      LODIV5GFORCED                                            |
|       4-7    PADRV2GN5G                                               |
|       8-11   PADRV3GN5G                                               |
|       12-15  PADRV4GN5G                                               |
|       16     LOCALTXGAIN5G                                            |
|       17     PDOUT2G                                                  |
|       18     PDDR2G                                                   |
|       19     PDMXR2G                                                  |
|       20     PDLOBUF2G                                                |
|       21     PDLODIV2G                                                |
|       22     LOBUF2GFORCED                                            |
|       23     LODIV2GFORCED                                            |
|       24-30  PADRVGN2G                                                |
|       31     LOCALTXGAIN2G                                            |
+-----------------------------------------------------------------------+
```


### ATH:01C044h - PHY_ANALOG_TXRF2

```
+-----------------------------------------------------------------------+
|       0-2    D3B5G                                                    |
|       3-5    D4B5G                                                    |
|       6-8    OCAS2G                                                   |
|       9-11   DCAS2G                                                   |
|       12-14  OB2G_PALOFF                                              |
|       15-17  OB2G_QAM                                                 |
|       18-20  OB2G_PSK                                                 |
|       21-23  OB2G_CCK                                                 |
|       24-26  DB2G                                                     |
|       27-30  PDOUT5G                                                  |
|       31     PDMXR5G                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C048h - PHY_ANALOG_TXRF3

```
+-----------------------------------------------------------------------+
|       0-1    FILTR2G                                                  |
|       2      PWDFB2_2G                                                |
|       3      PWDFB1_2G                                                |
|       4      PDFB2G                                                   |
|       5-6    RDIV5G                                                   |
|       7-9    CAPDIV5G                                                 |
|       10     PDPREDIST5G                                              |
|       11-12  RDIV2G                                                   |
|       13     PDPREDIST2G                                              |
|       14-16  OCAS5G                                                   |
|       17-19  D2CAS5G                                                  |
|       20-22  D3CAS5G                                                  |
|       23-25  D4CAS5G                                                  |
|       26-28  OB5G                                                     |
|       29-31  D2B5G                                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C04Ch - PHY_ANALOG_TXRF4

```
+-----------------------------------------------------------------------+
|       0-1    PK1B2G_CCK                                               |
|       2-4    MIOB2G_QAM                                               |
|       5-7    MIOB2G_PSK                                               |
|       8-10   MIOB2G_CCK                                               |
|       11-13  COMP2G_QAM                                               |
|       14-16  COMP2G_PSK                                               |
|       17-19  COMP2G_CCK                                               |
|       20-22  AMP2B2G_QAM                                              |
|       23-25  AMP2B2G_PSK                                              |
|       26-28  AMP2B2G_CCK                                              |
|       29-31  AMP2CAS2G                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C050h - PHY_ANALOG_TXRF5

```
+-----------------------------------------------------------------------+
|       0      hw4: SPARE5                                              |
|       0      hw6: TXMODPALONLY      ;-hw6.0 only                      |
|       1      PAL_LOCKED                     (R)                       |
|       2      FBHI2G                         (R)                       |
|       3      FBLO2G                         (R)                       |
|       4      NOPALGAIN2G                                              |
|       5      ENPACAL2G                                                |
|       6-12   OFFSET2G                                                 |
|       13     ENOFFSETCAL2G                                            |
|       14-16  REFHI2G                                                  |
|       17-19  REFLO2G                                                  |
|       20-21  PALCLAMP2G                                               |
|       22-23  PK2B2G_QAM                                               |
|       24-25  PK2B2G_PSK                                               |
|       26-27  PK2B2G_CCK                                               |
|       28-29  PK1B2G_QAM                                               |
|       30-31  PK1B2G_PSK                                               |
+-----------------------------------------------------------------------+
```


### ATH:01C054h - PHY_ANALOG_TXRF6

```
+-----------------------------------------------------------------------+
|       0      PALCLKGATE2G                                             |
|       1-8    PALFLUCTCOUNT2G                                          |
|       9-10   PALFLUCTGAIN2G                                           |
|       11     PALNOFLUCT2G                                             |
|       12-14  GAINSTEP2G                                               |
|       15     USE_GAIN_DELTA2G                                         |
|       16-19  CAPDIV_I2G                                               |
|       20-23  PADRVGN_INDEX_I2G                                        |
|       24-26  VCMONDELAY2G                                             |
|       27-30  CAPDIV2G                                                 |
|       31     CAPDIV2GOVR                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C058h - PHY_ANALOG_TXRF7 ;PADRVGNTAB_0..4

```
+-----------------------------------------------------------------------+
|       0-1    SPARE7                                                   |
|       2-7    PADRVGNTAB_4                                             |
|       8-13   PADRVGNTAB_3                                             |
|       14-19  PADRVGNTAB_2                                             |
|       20-25  PADRVGNTAB_1                                             |
|       26-31  PADRVGNTAB_0                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C05Ch - PHY_ANALOG_TXRF8 ;PADRVGNTAB_5..9

```
+-----------------------------------------------------------------------+
|       0-1    SPARE8                                                   |
|       2-7    PADRVGNTAB_9                                             |
|       8-13   PADRVGNTAB_8                                             |
|       14-19  PADRVGNTAB_7                                             |
|       20-25  PADRVGNTAB_6                                             |
|       26-31  PADRVGNTAB_5                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C060h - PHY_ANALOG_TXRF9 ;PADRVGNTAB_10..14

```
+-----------------------------------------------------------------------+
|       0-1    SPARE9                                                   |
|       2-7    PADRVGNTAB_14                                            |
|       8-13   PADRVGNTAB_13                                            |
|       14-19  PADRVGNTAB_12                                            |
|       20-25  PADRVGNTAB_11                                            |
|       26-31  PADRVGNTAB_10                                            |
+-----------------------------------------------------------------------+
```


### ATH:01C064h - PHY_ANALOG_TXRF10

```
+-----------------------------------------------------------------------+
|       0-2    SPARE10                                                  |
|       3      PDOUT5G_3CALTX                                           |
|       4-6    D3B5GCALTX                                               |
|       7-9    D4B5GCALTX                                               |
|       10-16  PADRVGN2GCALTX                                           |
|       17-19  DB2GCALTX                                                |
|       20     CALTXSHIFT                                               |
|       21     CALTXSHIFTOVR                                            |
|       22-27  PADRVGN2G_SMOUT                (R)                       |
|       28-31  PADRVGN_INDEX2G_SMOUT          (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:01C068h - PHY_ANALOG_TXRF11

```
+-----------------------------------------------------------------------+
|       0-1    SPARE11                                                  |
|       2-4    PWD_IR25MIXDIV5G                                         |
|       5-7    PWD_IR25PA2G                                             |
|       8-10   PWD_IR25MIXBIAS2G                                        |
|       11-13  PWD_IR25MIXDIV2G                                         |
|       14-16  PWD_ICSPARE                                              |
|       17-19  PWD_IC25TEMPSEN                                          |
|       20-22  PWD_IC25PA5G2                                            |
|       23-25  PWD_IC25PA5G1                                            |
|       26-28  PWD_IC25MIXBUF5G                                         |
|       29-31  PWD_IC25PA2G                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C06Ch - PHY_ANALOG_TXRF12

```
+-----------------------------------------------------------------------+
|       0-7    SPARE12_2                      (R)                       |
|       8-9    SPARE12_1                                                |
|       10-13  ATBSEL5G                                                 |
|       14-16  ATBSEL2G                                                 |
|       17-19  PWD_IRSPARE                                              |
|       20-22  PWD_IR25TEMPSEN                                          |
|       23-25  PWD_IR25PA5G2                                            |
|       26-28  PWD_IR25PA5G1                                            |
|       29-31  PWD_IR25MIXBIAS5G                                        |
+-----------------------------------------------------------------------+
```


### ATH:01C080h - PHY_ANALOG_SYNTH1

```
+-----------------------------------------------------------------------+
|       0-2    SEL_VCMONABUS                                            |
|       3-5    SEL_VCOABUS                                              |
|       6      MONITOR_SYNTHLOCKVCOK                                    |
|       7      MONITOR_VC2LOW                                           |
|       8      MONITOR_VC2HIGH                                          |
|       9      MONITOR_FB_DIV2                                          |
|       10     MONITOR_REF                                              |
|       11     MONITOR_FB                                               |
|       12     SEVENBITVCOCAP                                           |
|       13-15  PWUP_PD                                                  |
|       16     PWD_VCOBUF                                               |
|       17-18  VCOBUFGAIN                                               |
|       19-20  VCOREGLEVEL                                              |
|       21     VCOREGBYPASS                                             |
|       22     PWUP_LOREF                                               |
|       23     PWD_LOMIX                                                |
|       24     PWD_LODIV                                                |
|       25     PWD_LOBUF5G                                              |
|       26     PWD_LOBUF2G                                              |
|       27     PWD_PRESC                                                |
|       28     PWD_VCO                                                  |
|       29     PWD_VCMON                                                |
|       30     PWD_CP                                                   |
|       31     PWD_BIAS                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C084h - PHY_ANALOG_SYNTH2

```
+-----------------------------------------------------------------------+
|       0-3    CAPRANGE3                                                |
|       4-7    CAPRANGE2                                                |
|       8-11   CAPRANGE1                                                |
|       12-15  LOOPLEAKCUR_INTN                                         |
|       16     CPLOWLK_INTN                                             |
|       17     CPSTEERING_EN_INTN                                       |
|       18-19  CPBIAS_INTN                                              |
|       20-22  VC_LOW_REF                                               |
|       23-25  VC_MID_REF                                               |
|       26-28  VC_HI_REF                                                |
|       29-31  VC_CAL_REF                                               |
+-----------------------------------------------------------------------+
```


### ATH:01C088h - PHY_ANALOG_SYNTH3

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


### ATH:01C08Ch - PHY_ANALOG_SYNTH4

```
+-----------------------------------------------------------------------+
|       0      PS_SINGLE_PULSE                                          |
|       1      LONGSHIFTSEL                                             |
|       2-3    LOBUF5GTUNE_OVR                                          |
|       4      FORCE_LOBUF5GTUNE                                        |
|       5      PSCOUNT_FBSEL                                            |
|       6-7    SDM_DITHER1                                              |
|       8      SDM_MODE                                                 |
|       9      SDM_DISABLE                                              |
|       10     RESET_PRESC                                              |
|       11-12  PRESCSEL                                                 |
|       13     PFD_DISABLE                                              |
|       14     PFDDELAY_FRACN                                           |
|       15     FORCE_LO_ON                                              |
|       16     CLKXTAL_EDGE_SEL                                         |
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


### ATH:01C090h - PHY_ANALOG_SYNTH5

```
+-----------------------------------------------------------------------+
|       0-1    VCOBIAS                                                  |
|       2-4    PWDB_ICLOBUF5G50                                         |
|       5-7    PWDB_ICLOBUF2G50                                         |
|       8-10   PWDB_ICVCO25                                             |
|       11-13  PWDB_ICVCOREG25                                          |
|       14     PWDB_IRVCOREG50                                          |
|       15-17  PWDB_ICLOMIX                                             |
|       18-20  PWDB_ICLODIV50                                           |
|       21-23  PWDB_ICPRESC50                                           |
|       24-26  PWDB_IRVCMON25                                           |
|       27-29  PWDB_IRPFDCP                                             |
|       30-31  SDM_DITHER2                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C094h - PHY_ANALOG_SYNTH6

```
+-----------------------------------------------------------------------+
|       0-1    LOBUF5GTUNE                    (R)                       |
|       2-8    LOOP_IP                        (R)                       |
|       9      VC2LOW                         (R)                       |
|       10     VC2HIGH                        (R)                       |
|       11     RESET_SDM_B                    (R)                       |
|       12     RESET_PSCOUNTERS               (R)                       |
|       13     RESET_PFD                      (R)                       |
|       14     RESET_RFD                      (R)                       |
|       15     SHORT_R                        (R)                       |
|       16-23  VCO_CAP_ST                     (R)                       |
|       24     PIN_VC                         (R)                       |
|       25     SYNTH_LOCK_VC_OK               (R)                       |
|       26     CAP_SEARCH                     (R)                       |
|       27-30  SYNTH_SM_STATE                 (R)                       |
|       31     SYNTH_ON                       (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:01C098h - PHY_ANALOG_SYNTH7

```
+-----------------------------------------------------------------------+
|       0      OVRCHANDECODER                                           |
|       1      FORCE_FRACLSB                                            |
|       2-18   CHANFRAC                                                 |
|       19-27  CHANSEL                                                  |
|       28-29  AMODEREFSEL                                              |
|       30     FRACMODE                                                 |
|       31     LOADSYNTHCHANNEL                                         |
+-----------------------------------------------------------------------+
```


### ATH:01C09Ch - PHY_ANALOG_SYNTH8

```
+-----------------------------------------------------------------------+
|       0      CPSTEERING_EN_FRACN                                      |
|       1-7    LOOP_ICPB                                                |
|       8-11   LOOP_CSB                                                 |
|       12-16  LOOP_RSB                                                 |
|       17-21  LOOP_CPB                                                 |
|       22-26  LOOP_3RD_ORDER_RB                                        |
|       27-31  REFDIVB                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C0A0h - PHY_ANALOG_SYNTH9

```
+-----------------------------------------------------------------------+
|       0      PFDDELAY_INTN                                            |
|       1-3    SLOPE_ICPA0                                              |
|       4-7    LOOP_ICPA0                                               |
|       8-11   LOOP_CSA0                                                |
|       12-16  LOOP_RSA0                                                |
|       17-21  LOOP_CPA0                                                |
|       22-26  LOOP_3RD_ORDER_RA                                        |
|       27-31  REFDIVA                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C0A4h - PHY_ANALOG_SYNTH10

```
+-----------------------------------------------------------------------+
|       0-1    SPARE10A                                                 |
|       2-4    PWDB_ICLOBIAS50                                          |
|       5-7    PWDB_IRSPARE25                                           |
|       8-10   PWDB_ICSPARE25                                           |
|       11-13  SLOPE_ICPA1                                              |
|       14-17  LOOP_ICPA1                                               |
|       18-21  LOOP_CSA1                                                |
|       22-26  LOOP_RSA1                                                |
|       27-31  LOOP_CPA1                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C0A8h - PHY_ANALOG_SYNTH11

```
+-----------------------------------------------------------------------+
|       0-4    SPARE11A                                                 |
|       5      FORCE_LOBUF5G_ON                                         |
|       6-7    LOREFSEL                                                 |
|       8-9    LOBUF2GTUNE                                              |
|       10     CPSTEERING_MODE                                          |
|       11-13  SLOPE_ICPA2                                              |
|       14-17  LOOP_ICPA2                                               |
|       18-21  LOOP_CSA2                                                |
|       22-26  LOOP_RSA2                                                |
|       27-31  LOOP_CPA2                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C0ACh - PHY_ANALOG_SYNTH12

```
+-----------------------------------------------------------------------+
|       0-9    SPARE12A                                                 |
|       10-13  LOOPLEAKCUR_FRACN                                        |
|       14     CPLOWLK_FRACN                                            |
|       15-16  CPBIAS_FRACN                                             |
|       17     SYNTHDIGOUTEN                                            |
|       18     STRCONT                                                  |
|       19-22  VREFMUL3                                                 |
|       23-26  VREFMUL2                                                 |
|       27-30  VREFMUL1                                                 |
|       31     CLK_DOUBLER_EN                                           |
+-----------------------------------------------------------------------+
```


### ATH:01C0B0h - PHY_ANALOG_SYNTH13

```
+-----------------------------------------------------------------------+
|       0      SPARE13A                                                 |
|       1-3    SLOPE_ICPA_FRACN                                         |
|       4-7    LOOP_ICPA_FRACN                                          |
|       8-11   LOOP_CSA_FRACN                                           |
|       12-16  LOOP_RSA_FRACN                                           |
|       17-21  LOOP_CPA_FRACN                                           |
|       22-26  LOOP_3RD_ORDER_RA_FRACN                                  |
|       27-31  REFDIVA_FRACN                                            |
+-----------------------------------------------------------------------+
```


### ATH:01C0B4h - PHY_ANALOG_SYNTH14

```
+-----------------------------------------------------------------------+
|       0-1    SPARE14A                                                 |
|       2-3    LOBUF5GTUNE_3                                            |
|       4-5    LOBUF2GTUNE_3                                            |
|       6-7    LOBUF5GTUNE_2                                            |
|       8-9    LOBUF2GTUNE_2                                            |
|       10     PWD_LOBUF5G_3                                            |
|       11     PWD_LOBUF2G_3                                            |
|       12     PWD_LOBUF5G_2                                            |
|       13     PWD_LOBUF2G_2                                            |
|       14-16  PWUPLO23_PD                                              |
|       17-19  PWDB_ICLOBUF5G50_3                                       |
|       20-22  PWDB_ICLOBUF2G50_3                                       |
|       23-25  PWDB_ICLOBUF5G50_2                                       |
|       26-28  PWDB_ICLOBUF2G50_2                                       |
|       29-31  PWDB_ICLVLSHFT                                           |
+-----------------------------------------------------------------------+
```


### ATH:01C0C0h - PHY_ANALOG_BIAS1

```
+-----------------------------------------------------------------------+
|       0-6    SPARE1                                                   |
|       7-9    PWD_IC25V2IQ                                             |
|       10-12  PWD_IC25V2II                                             |
|       13-15  PWD_IC25BB                                               |
|       16-18  PWD_IC25DAC                                              |
|       19-21  PWD_IC25FIR                                              |
|       22-24  PWD_IC25ADC                                              |
|       25-31  BIAS_SEL                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C0C4h - PHY_ANALOG_BIAS2

```
+-----------------------------------------------------------------------+
|       0-4    SPARE2                                                   |
|       5-7    PWD_IC25XPA                                              |
|       8-10   PWD_IC25XTAL                                             |
|       11-13  PWD_IC25TXRF                                             |
|       14-16  PWD_IC25RXRF                                             |
|       17-19  PWD_IC25SYNTH                                            |
|       20-22  PWD_IC25PLLREG                                           |
|       23-25  PWD_IC25PLLCP2                                           |
|       26-28  PWD_IC25PLLCP                                            |
|       29-31  PWD_IC25PLLGM                                            |
+-----------------------------------------------------------------------+
```


### ATH:01C0C8h - PHY_ANALOG_BIAS3

```
+-----------------------------------------------------------------------+
|       0-1    SPARE3                                                   |
|       2-4    PWD_IR25SAR                                              |
|       5-7    PWD_IR25TXRF                                             |
|       8-10   PWD_IR25RXRF                                             |
|       11-13  PWD_IR25SYNTH                                            |
|       14-16  PWD_IR25PLLREG                                           |
|       17-19  PWD_IR25BB                                               |
|       20-22  PWD_IR50DAC                                              |
|       23-25  PWD_IR25DAC                                              |
|       26-28  PWD_IR25FIR                                              |
|       29-31  PWD_IR50ADC                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C0CCh - PHY_ANALOG_BIAS4

```
+-----------------------------------------------------------------------+
|       0-10   SPARE4                                                   |
|       11-13  PWD_IR25SPARED                                           |
|       14-16  PWD_IR25SPAREC                                           |
|       17-19  PWD_IR25SPAREB                                           |
|       20-22  PWD_IR25XPA                                              |
|       23-25  PWD_IC25SPAREC                                           |
|       26-28  PWD_IC25SPAREB                                           |
|       29-31  PWD_IC25SPAREA                                           |
+-----------------------------------------------------------------------+
```


### ATH:01C100h - PHY_ANALOG_RXTX1

```
+-----------------------------------------------------------------------+
|       0      SCFIR_GAIN                                               |
|       1      MANRXGAIN                                                |
|       2-5    AGC_DBDAC                                                |
|       6      OVR_AGC_DBDAC                                            |
|       7      ENABLE_PAL                                               |
|       8      ENABLE_PAL_OVR                                           |
|       9-11   TX1DB_BIQUAD                                             |
|       12-13  TX6DB_BIQUAD                                             |
|       14     PADRVHALFGN2G                                            |
|       15-18  PADRV2GN                                                 |
|       19-22  PADRV3GN5G                                               |
|       23-26  PADRV4GN5G                                               |
|       27-30  TXBB_GC                                                  |
|       31     MANTXGAIN                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C104h - PHY_ANALOG_RXTX2

```
+-----------------------------------------------------------------------+
|       0      BMODE                                                    |
|       1      BMODE_OVR                                                |
|       2      SYNTHON                                                  |
|       3      SYNTHON_OVR                                              |
|       4-5    BW_ST                                                    |
|       6      BW_ST_OVR                                                |
|       7      TXON                                                     |
|       8      TXON_OVR                                                 |
|       9      PAON                                                     |
|       10     PAON_OVR                                                 |
|       11     RXON                                                     |
|       12     RXON_OVR                                                 |
|       13     AGCON                                                    |
|       14     AGCON_OVR                                                |
|       15-17  TXMOD                                                    |
|       18     TXMOD_OVR                                                |
|       19-21  RX1DB_BIQUAD                                             |
|       22-23  RX6DB_BIQUAD                                             |
|       24-25  MXRGAIN                                                  |
|       26-28  VGAGAIN                                                  |
|       29-31  LNAGAIN                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C108h - PHY_ANALOG_RXTX3

```
+-----------------------------------------------------------------------+
|       0-2    SPARE3                                                   |
|       3      SPURON                                                   |
|       4      PAL_LOCKEDEN                                             |
|       5      DACFULLSCALE                                             |
|       6      ADCSHORT                                                 |
|       7      DACPWD                                                   |
|       8      DACPWD_OVR                                               |
|       9      ADCPWD                                                   |
|       10     ADCPWD_OVR                                               |
|       11-16  AGC_CALDAC                                               |
|       17     AGC_CAL                                                  |
|       18     AGC_CAL_OVR                                              |
|       19     LOFORCEDON                                               |
|       20     CALRESIDUE                                               |
|       21     CALRESIDUE_OVR                                           |
|       22     CALFC                                                    |
|       23     CALFC_OVR                                                |
|       24     CALTX                                                    |
|       25     CALTX_OVR                                                |
|       26     CALTXSHIFT                                               |
|       27     CALTXSHIFT_OVR                                           |
|       28     CALPA                                                    |
|       29     CALPA_OVR                                                |
|       30     TURBOADC                                                 |
|       31     TURBOADC_OVR                                             |
+-----------------------------------------------------------------------+
```


### ATH:01C140h - PHY_ANALOG_BB1

```
+-----------------------------------------------------------------------+
|       0      I2V_CURR2X                                               |
|       1      ENABLE_LOQ                                               |
|       2      FORCE_LOQ                                                |
|       3      ENABLE_NOTCH                                             |
|       4      FORCE_NOTCH                                              |
|       5      ENABLE_BIQUAD                                            |
|       6      FORCE_BIQUAD                                             |
|       7      ENABLE_OSDAC                                             |
|       8      FORCE_OSDAC                                              |
|       9      ENABLE_V2I                                               |
|       10     FORCE_V2I                                                |
|       11     ENABLE_I2V                                               |
|       12     FORCE_I2V                                                |
|       13-15  CMSEL                                                    |
|       16-17  ATBSEL                                                   |
|       18     PD_OSDAC_CALTX_CALPA                                     |
|       19-23  OFSTCORRI2VQ                                             |
|       24-28  OFSTCORRI2VI                                             |
|       29     LOCALOFFSET                                              |
|       30-31  RANGE_OSDAC                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C144h - PHY_ANALOG_BB2

```
+-----------------------------------------------------------------------+
|       0-3    SPARE                                                    |
|       4-7    MXR_HIGHGAINMASK                                         |
|       8-9    SEL_TEST                                                 |
|       10-14  RCFILTER_CAP                                             |
|       15     OVERRIDE_RCFILTER_CAP                                    |
|       16-19  FNOTCH                                                   |
|       20     OVERRIDE_FNOTCH                                          |
|       21-25  FILTERFC                                                 |
|       26     OVERRIDE_FILTERFC                                        |
|       27     I2V2RXOUT_EN                                             |
|       28     BQ2RXOUT_EN                                              |
|       29     RXIN2I2V_EN                                              |
|       30     RXIN2BQ_EN                                               |
|       31     SWITCH_OVERRIDE                                          |
+-----------------------------------------------------------------------+
```


### ATH:01C148h - PHY_ANALOG_BB3

```
+-----------------------------------------------------------------------+
|       0-7    SPARE                                                    |
|       8-15   hw4: SPARE                                               |
|       8-9    hw6: SEL_OFST_READBK           ;\                        
|       10     hw6: OVERRIDE_RXONLY_FILTERFC  ; hw6.0 only              |
|       11-15  hw6: RXONLY_FILTERFC           ;/                        |
|       16-20  FILTERFC                       (R)                       |
|       21-25  OFSTCORRI2VQ                   (R)                       |
|       26-30  OFSTCORRI2VI                   (R)                       |
|       31     EN_TXBBCONSTCUR                                          |
+-----------------------------------------------------------------------+
```


### ATH:01C280h - PHY_ANALOG_PLLCLKMODA

```
+-----------------------------------------------------------------------+
|       0      PWD_PLLSDM                                               |
|       1      PWDPLL                                                   |
|       2-16   PLLFRAC                                                  |
|       17-20  REFDIV                                                   |
|       21-30  DIV                                                      |
|       31     LOCAL_PLL                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C284h - PHY_ANALOG_PLLCLKMODA2

```
+-----------------------------------------------------------------------+
|       0-3    SPARE                                                    |
|       4      DACPWD                                                   |
|       5      ADCPWD                                                   |
|       6      LOCAL_ADDAC                                              |
|       7-8    DAC_CLK_SEL                                              |
|       9-12   ADC_CLK_SEL                                              |
|       13     LOCAL_CLKMODA                                            |
|       14     PLLBYPASS                                                |
|       15     LOCAL_PLLBYPASS                                          |
|       16-17  PLLATB                                                   |
|       18     PLL_SVREG                                                |
|       19     HI_FREQ_EN                                               |
|       20     RST_WARM_INT_L                                           |
|       21     RST_WARM_OVR                                             |
|       22-23  PLL_KVCO                                                 |
|       24-26  PLLICP                                                   |
|       27-31  PLLFILTER                                                |
+-----------------------------------------------------------------------+
```


### ATH:01C288h - PHY_ANALOG_TOP

```
+-----------------------------------------------------------------------+
|       0-2    SPARE                                                    |
|       3      PWDBIAS                                                  |
|       4      FLIP_XPABIAS                                             |
|       5      XPAON2                                                   |
|       6      XPAON5                                                   |
|       7      XPASHORT2GND                                             |
|       8-11   XPABIASLVL                                               |
|       12     XPABIAS_EN                                               |
|       13     ATBSELECT                                                |
|       14     LOCAL_XPA                                                |
|       15     XPABIAS_BYPASS                                           |
|       16     TEST_PADQ_EN                                             |
|       17     TEST_PADI_EN                                             |
|       18     TESTIQ_RSEL                                              |
|       19     TESTIQ_BUFEN                                             |
|       20     PAD2GND                                                  |
|       21     INTH2PAD                                                 |
|       22     INTH2GND                                                 |
|       23     INT2PAD                                                  |
|       24     INT2GND                                                  |
|       25     PWDPALCLK                                                |
|       26     INV_CLK320_ADC                                           |
|       27     FLIP_REFCLK40                                            |
|       28     FLIP_PLLCLK320                                           |
|       29     FLIP_PLLCLK160                                           |
|       30-31  CLK_SEL                                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C28Ch - PHY_ANALOG_THERM

```
+-----------------------------------------------------------------------+
|       0-2    LOREG_LVL                                                |
|       3-5    RFREG_LVL                                                |
|       6      SAR_ADC_DONE                   (R)                       |
|       7-14   SAR_ADC_OUT                    (R)                       |
|       15-22  SAR_DACTEST_CODE                                         |
|       23     SAR_DACTEST_EN                                           |
|       24     SAR_ADCCAL_EN                                            |
|       25-26  THERMSEL                                                 |
|       27     SAR_SLOW_EN                                              |
|       28     THERMSTART                                               |
|       29     SAR_AUTOPWD_EN                                           |
|       30     THERMON                                                  |
|       31     LOCAL_THERM                                              |
+-----------------------------------------------------------------------+
```


### ATH:01C290h - PHY_ANALOG_XTAL

```
+-----------------------------------------------------------------------+
|       0-5    SPARE                                                    |
|       6      XTAL_NOTCXODET                                           |
|       7      LOCALBIAS2X                                              |
|       8      LOCAL_XTAL                                               |
|       9      XTAL_PWDCLKIN                                            |
|       10     XTAL_OSCON                                               |
|       11     XTAL_PWDCLKD                                             |
|       12     XTAL_LOCALBIAS                                           |
|       13     XTAL_SHRTXIN                                             |
|       14-15  XTAL_DRVSTR                                              |
|       16-22  XTAL_CAPOUTDAC                                           |
|       23-29  XTAL_CAPINDAC                                            |
|       30     XTAL_BIAS2X                                              |
|       31     TCXODET                        (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:01C380h - PHY_ANALOG_RBIST_CNTRL

```
+-----------------------------------------------------------------------+
|       0      ATE_TONEGEN_DC_ENABLE                                    |
|       1      ATE_TONEGEN_TONE0_ENABLE                                 |
|       2      ATE_TONEGEN_TONE1_ENABLE                                 |
|       3      ATE_TONEGEN_LFTONE0_ENABLE                               |
|       4      ATE_TONEGEN_LINRAMP_ENABLE_I                             |
|       5      ATE_TONEGEN_LINRAMP_ENABLE_Q                             |
|       6      ATE_TONEGEN_PRBS_ENABLE_I                                |
|       7      ATE_TONEGEN_PRBS_ENABLE_Q                                |
|       8      ATE_CMAC_DC_WRITE_TO_CANCEL                              |
|       9      ATE_CMAC_DC_ENABLE                                       |
|       10     ATE_CMAC_CORR_ENABLE                                     |
|       11     ATE_CMAC_POWER_ENABLE                                    |
|       12     ATE_CMAC_IQ_ENABLE                                       |
|       13     ATE_CMAC_I2Q2_ENABLE                                     |
|       14     ATE_CMAC_POWER_HPF_ENABLE                                |
|       15     ATE_RXDAC_CALIBRATE                                      |
|       16     ATE_RBIST_ENABLE                                         |
|       17     ATE_ADC_CLK_INVERT             ;-newer revision only     |
+-----------------------------------------------------------------------+
```


### ATH:01C384h - PHY_ANALOG_TX_DC_OFFSET

```
+-----------------------------------------------------------------------+
|       0-10   ATE_TONEGEN_DC_I                                         |
|       16-26  ATE_TONEGEN_DC_Q                                         |
+-----------------------------------------------------------------------+
```


### ATH:01C388h - PHY_ANALOG_TX_TONEGEN0
### ATH:01C38Ch - PHY_ANALOG_TX_TONEGEN1
### ATH:01C390h - PHY_ANALOG_TX_LFTONEGEN0

```
+-----------------------------------------------------------------------+
|       0-6    ATE_TONEGEN_TONE_FREQ                                    |
|       8-11   ATE_TONEGEN_TONE_A_EXP                                   |
|       16-23  ATE_TONEGEN_TONE_A_MAN                                   |
|       24-30  ATE_TONEGEN_TONE_TAU_K                                   |
+-----------------------------------------------------------------------+
```


### ATH:01C394h - PHY_ANALOG_TX_LINEAR_RAMP_I
### ATH:01C398h - PHY_ANALOG_TX_LINEAR_RAMP_Q

```
+-----------------------------------------------------------------------+
|       0-10   ATE_TONEGEN_LINRAMP_INIT                                 |
|       12-21  ATE_TONEGEN_LINRAMP_DWELL                                |
|       24-29  ATE_TONEGEN_LINRAMP_STEP                                 |
+-----------------------------------------------------------------------+
```


### ATH:01C39Ch - PHY_ANALOG_TX_PRBS_MAG

```
+-----------------------------------------------------------------------+
|       0-9    ATE_TONEGEN_PRBS_MAGNITUDE_I                             |
|       16-25  ATE_TONEGEN_PRBS_MAGNITUDE_Q                             |
+-----------------------------------------------------------------------+
```


### ATH:01C3A0h - PHY_ANALOG_TX_PRBS_SEED_I

```
+-----------------------------------------------------------------------+
|       0-30   ATE_TONEGEN_PRBS_SEED                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C3A4h - PHY_ANALOG_TX_PRBS_SEED_Q

```
+-----------------------------------------------------------------------+
|       0-30   ATE_TONEGEN_PRBS_SEED                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C3A8h - PHY_ANALOG_CMAC_DC_CANCEL

```
+-----------------------------------------------------------------------+
|       0-9    ATE_CMAC_DC_CANCEL_I                                     |
|       16-25  ATE_CMAC_DC_CANCEL_Q                                     |
+-----------------------------------------------------------------------+
```


### ATH:01C3ACh - PHY_ANALOG_CMAC_DC_OFFSET

```
+-----------------------------------------------------------------------+
|       0-3    ATE_CMAC_DC_CYCLES                                       |
+-----------------------------------------------------------------------+
```


### ATH:01C3B0h - PHY_ANALOG_CMAC_CORR

```
+-----------------------------------------------------------------------+
|       0-4    ATE_CMAC_CORR_CYCLES                                     |
|       8-13   ATE_CMAC_CORR_FREQ                                       |
+-----------------------------------------------------------------------+
```


### ATH:01C3B4h - PHY_ANALOG_CMAC_POWER

```
+-----------------------------------------------------------------------+
|       0-3    ATE_CMAC_POWER_CYCLES                                    |
+-----------------------------------------------------------------------+
```


### ATH:01C3B8h - PHY_ANALOG_CMAC_CROSS_CORR

```
+-----------------------------------------------------------------------+
|       0-3    ATE_CMAC_IQ_CYCLES                                       |
+-----------------------------------------------------------------------+
```


### ATH:01C3BCh - PHY_ANALOG_CMAC_I2Q2

```
+-----------------------------------------------------------------------+
|       0-3    ATE_CMAC_I2Q2_CYCLES                                     |
+-----------------------------------------------------------------------+
```


### ATH:01C3C0h - PHY_ANALOG_CMAC_POWER_HPF

```
+-----------------------------------------------------------------------+
|       0-3    ATE_CMAC_POWER_HPF_CYCLES                                |
|       4-7    ATE_CMAC_POWER_HPF_WAIT                                  |
+-----------------------------------------------------------------------+
```


### ATH:01C3C4h - PHY_ANALOG_RXDAC_SET1

```
+-----------------------------------------------------------------------+
|       0-1    ATE_RXDAC_MUX                                            |
|       4      ATE_RXDAC_HI_GAIN                                        |
|       8-13   ATE_RXDAC_CAL_WAIT                                       |
|       16-19  ATE_RXDAC_CAL_MEASURE_TIME                               |
+-----------------------------------------------------------------------+
```


### ATH:01C3C8h - PHY_ANALOG_RXDAC_SET2

```
+-----------------------------------------------------------------------+
|       0-4    ATE_RXDAC_I_HI                                           |
|       8-12   ATE_RXDAC_Q_HI                                           |
|       16-20  ATE_RXDAC_I_LOW                                          |
|       24-28  ATE_RXDAC_Q_LOW                                          |
+-----------------------------------------------------------------------+
```


### ATH:01C3CCh - PHY_ANALOG_RXDAC_LONG_SHIFT

```
+-----------------------------------------------------------------------+
|       0-4    ATE_RXDAC_I_STATIC                                       |
|       8-12   ATE_RXDAC_Q_STATIC                                       |
+-----------------------------------------------------------------------+
```


### ATH:01C3D0h - PHY_ANALOG_CMAC_RESULTS_I

```
+-----------------------------------------------------------------------+
|       0-31   ATE_CMAC_RESULTS                                         |
+-----------------------------------------------------------------------+
```


### ATH:01C3D4h - PHY_ANALOG_CMAC_RESULTS_Q

```
+-----------------------------------------------------------------------+
|       0-31   ATE_CMAC_RESULTS                                         |
+-----------------------------------------------------------------------+
```


### ATH:01C740h - PHY_ANALOG_PMU1
This register differs in hw4/hw6 (in hw6, bits are renumbered, new OVERRIDE bits are added, and the SREG_LVLCTR bit is removed):

```
+-------------------------------------------------------------------------------------+
|       hw4    hw6    name                                                            |
|       0-10   0-3    SPARE                         ;-unused                          |
|       11     4      OTP_V25_PWD                   ;-OTP V25                         |
|       12     5      PAREGON_MAN                   ;\PA REG                          
|       -      6      PAREGON_OVERRIDE_EN           ;/                                |
|       13     7      OTPREGON_MAN                  ;\OTP REG                         
|       -      8      OTPREGON_OVERRIDE_EN          ;/                                |
|       14     9      DREGON_MAN                    ;\DREG                            
|       -      10     DREGON_OVERRIDE_EN            ;/                                |
|       15     11     DISCONTMODEEN                 ;\DISCONT MODE                    
|       -      12     SWREGDISCONT_OVERRIDE_EN      ;/                                |
|       16     13     SWREGON_MAN                   ;\                                
|       -      14     SWREGON_OVERRIDE_EN           ;                                 |
|       17-18  15-16  SWREG_FREQCUR                 ;                                 |
|       19-21  17-19  SWREG_FREQCAP                 ; SW REG                          |
|       -      20     SWREGFREQ_OVERRIDE_EN         ;                                 |
|       22-23  21-22  SWREG_LVLCTR                  ;                                 |
|       -      23     SWREGLVL_OVERRIDE_EN          ;/                                |
|       24-25  -      hw4:SREG_LVLCTR               ;-SREG  ;<---- removed in hw6 (!) |
|       26-27  24-25  DREG_LVLCTR                   ;\DREG                            
|       -      26     DREGLVL_OVERRIDE_EN           ;/                                |
|       28     27     PAREG_XPNP                    ;\                                
|       29-31  28-30  PAREG_LVLCTR                  ; PA REG                          |
|       -      31     PAREGLVL_OVERRIDE_EN          ;/                                |
+-------------------------------------------------------------------------------------+
```


### ATH:01C744h - PHY_ANALOG_PMU2

```
+----------------------------------------------------------------------------------+
|       0-7    SPARE                                                               |
|       8      VBATT_1_3TOATB                                                      |
|       9      VBATT_1_2TOATB                                                      |
|       10     VBATT_2_3TOATB                                                      |
|       11     PWD_BANDGAP_MAN                                                     |
|       12     PWD_LFO_MAN                                                         |
|       13     VBATT_LT_3P2                                                        |
|       14     VBATT_LT_2P8                                                        |
|       15     VBATT_GT_4P2                                                        |
|       16     hw4: PMU_MAN_OVERRIDE_EN               ;\changed/renamed in hw4/hw6 
|       16     hw6: PMU_XPNP_OVERRIDE_EN              ;/                           |
|       17-18  VBATT_GT_LVLCTR                                                     |
|       19     SWREGVSSL2ATB                                                       |
|       20-21  SWREGVSSL_LVLCTR                                                    |
|       22     SWREGVDDH2ATB                                                       |
|       23-24  SWREGVDDH_LVLCTR                                                    |
|       25-27  SWREG2ATB                                                           |
|       28     OTPREG2ATB                                                          |
|       29-30  OTPREG_LVLCTR                                                       |
|       31     hw4: DREG_LVLCTR_MANOVR_EN             ;\changed/renamed in hw4/hw6 
|       31     hw6: OTPREG_LVLCTR_MANOVR_EN           ;/                           |
+----------------------------------------------------------------------------------+
```




