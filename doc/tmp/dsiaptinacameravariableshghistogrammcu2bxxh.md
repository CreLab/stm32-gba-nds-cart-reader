# DSi Aptina Camera Variables: HG (Histogram) (MCU:2Bxxh)


### Histogram Variables HG (MCU:2B00h..2B61h)

```
+-------------------------------------------------------------------------------------+
|       2B00h  ..  RESERVED_HG_00-03         Reserved                                 |
|       2B04h   1  HG_MAX_DLEVEL             DarkLevel Limit (0..FFh, def=40h)        |
|       2B05h  ..  RESERVED_HG_05            Reserved                                 |
|       2B06h   1  HG_PERCENT                Percent?        (0..FFh, def=03h)        |
|       2B07h  ..  RESERVED_HG_07            Reserved                                 |
|       2B08h   1  HG_DLEVEL                 DarkLevel       (0..FFh, def=10h)        |
|       2B09h  ..  RESERVED_HG_09-16         Reserved                                 |
|       2B17h   1  HG_AVERAGELUMA            Average Luma      (0..FFh)               |
|       2B18h  ..  RESERVED_HG_18-1A         Reserved                                 |
|       2B1Bh   2  HG_BRIGHTNESSMETRIC       Brightness Metric (0..FFFFh)             |
|       2B1Dh  ..  RESERVED_HG_1D            Reserved                                 |
|       2B1Fh   1  HG_LLMODE                 Low Light mode controls (def=C4h)        |
|                    0-3  Brightness Metric Prescaler (01h..0Fh)                      |
|                    4-5  Unused (0)                                                  |
|                    6    HG_2d_corr_vs_clusterdc                                     |
|                    7    Clusterdc_vs_gains                                          |
|       2B20h   1  HG_LL_SAT1                LL_SAT1            (0..FFh, def=43h)     |
|       2B21h   1  UNDOC_HG_21               Whatever           (0..FFh, def=10h)     |
|       2B22h   1  HG_LL_APCORR1             LL_APCORR1         (0..FFh, def=03h)     |
|       2B23h   1  UNDOC_HG_23               Whatever           (0..FFh, def=04h)     |
|       2B24h   1  HG_LL_SAT2                LL_SAT2            (0..FFh, def=0Ch)     |
|       2B25h   1  HG_LL_INTERPTHRESH2       LL_INTERPTHRESH2   (0..FFh, def=23h)     |
|       2B26h   1  HG_LL_APCORR2             LL_APCORR2         (0..FFh)              |
|       2B27h   1  HG_LL_APTHRESH2           LL_APTHRESH2       (0..FFh, def=04h)     |
|       2B28h   2  HG_LL_BRIGHTNESSSTART     LL_BRIGHTNESSSTART (0..FFFFh, def=0A8Ch) |
|       2B2Ah   2  HG_LL_BRIGHTNESSSTOP      LL_BRIGHTNESSSTOP  (0..FFFFh, def=34BCh) |
|       2B2Ch   1  HG_NR_START_R             NR_START_R         (0..FFh, def=06h)     |
|       2B2Dh   1  HG_NR_START_G             NR_START_G         (0..FFh, def=0Eh)     |
|       2B2Eh   1  HG_NR_START_B             NR_START_B         (0..FFh, def=06h)     |
|       2B2Fh   1  HG_NR_START_OL            NR_START_OL        (0..FFh, def=06h)     |
|       2B30h   1  HG_NR_STOP_R              NR_STOP_R          (0..FFh, def=1Eh)     |
|       2B31h   1  HG_NR_STOP_G              NR_STOP_G          (0..FFh, def=1Eh)     |
|       2B32h   1  HG_NR_STOP_B              NR_STOP_B          (0..FFh, def=1Eh)     |
|       2B33h   1  HG_NR_STOP_OL             NR_STOP_OL         (0..FFh, def=1Eh)     |
|       2B34h   1  HG_NR_GAINSTART           NR_GAINSTART       (0..FFh, def=08h)     |
|       2B35h   1  HG_NR_GAINSTOP            NR_GAINSTOP        (0..FFh, def=80h)     |
|       2B36h   1  HG_CLUSTERDC_TH           CLUSTERDC_TH       (0..FFh, def=1Eh)     |
|       2B37h   1  HG_GAMMA_MORPH_CTRL       Gamma Morphing Control (0..FFh, def=3)   |
|                    0-1 Enable Gamma Morph (0=Disable, 1=Use Table A, 2=Use Table B, |
|                        3=AutoMorph between Table A and B based on BrightnessMetric) |
|                    2-7 Unspecified                                                  |
|       2B38h   2  HG_GAMMASTARTMORPH        Gamma Start Morph (0..FFFFh, def=0A8Ch)  |
|       2B3Ah   2  HG_GAMMASTOPMORPH         Gamma Stop Morph  (0..FFFFh, def=34BCh)  |
|       2B3Ch  19  HG_GAMMA_TABLE_A_0-18     Gamma Table A for normal light condition |
|                   Default=xx,1B,2E,4C,78,98,B0,E8,CF,D9,E1,E8,EE,F2,F6,F9,FB,FD,FF  |
|       2B4Fh  19  HG_GAMMA_TABLE_B_0-18     Gamma Table B for low light condition    |
|                   Default=xx,0F,1A,2E,50,6A,80,91,A1,AF,BB,C6,D0,D9,E2,EA,F1,F9,FF  |
|                   Above 2 tables have normal byte-order (Entry0,Entry1,...,Entry18) |
|       2B62h   2  HG_FTB_START_BM           (0..FFFFh, def=7FBCh) (REV3)             |
|       2B64h   2  HG_FTB_STOP_BM            (0..FFFFh, def=82DCh) (REV3)             |
|       2B66h   2  HG_CLUSTER_DC_BM          (0..FFFFh, def=4A38h) (REV3)             |
+-------------------------------------------------------------------------------------+
```




