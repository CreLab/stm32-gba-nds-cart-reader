# DSi Atheros Wifi - Internal I/O - 021000h - WMAC DCU (hw4/hw6)


### ATH:021000h..021024h - MAC_DCU_QCUMASK\[0..9\] aka MAC_DMA_D(0..9)\_QCUMASK
The \"DCU_QCU\" Mask is some two-dimensional array: An array of ten DCU registers, each containing an array of ten QCU bits.

```
+-----------------------------------------------------------------------+
|       0-9   QCU Mask (QCU 0-9)                                        |
+-----------------------------------------------------------------------+
```


### ATH:021030h - MAC_DCU_GBL_IFS_SIFS aka MAC_DMA_D_GBL_IFS_SIFS

```
+------------------------------------------------------------------------+
|       0-15   DURATION                       ;-DCU global SIFS settings |
+------------------------------------------------------------------------+
```


### ATH:021040h..021064h - MAC_DCU_LCL_IFS\[0..9\] aka MAC_DMA_D(0..9)\_LCL_IFS

```
+-------------------------------------------------------------------------------------+
|       0-9    CW_MIN                                 ;\                              
|       10-19  CW_MAX                                 ; MAC DCU-specific IFS settings |
|       20-27  AIFS                                   ;                               |
|       28     hw6: LONG_AIFS     ;-hw6 only          ;                               |
|       29-31  -                                      ;/                              |
+-------------------------------------------------------------------------------------+
```

Note: Even though this field is 8 bits wide the maximum supported AIFS value is FCh. Setting the AIFS value to FDh,FEh,FFh will not work correctly and will cause the DCU to hang (said to be so; at least for hw4).

### ATH:021070h - MAC_DCU_GBL_IFS_SLOT aka MAC_DMA_D_GBL_IFS_SLOT

```
+-----------------------------------------------------------------------+
|       0-15   DURATION       ;DC global slot interval                  |
+-----------------------------------------------------------------------+
```


### ATH:021080h..0210A4h - MAC_DCU_RETRY_LIMIT\[0..9\] aka MAC_DMA_D(0..9)\_RETR..

```
+------------------------------------------------------------------------+
|       0-3   frame RTS failure limit (FRFL)          ;\                 
|       4-7   -                                       ; MAC Retry limits |
|       8-13  station RTS failure limit (SRFL)        ;                  |
|       14-19 station short retry limit (SDFL)        ;                  |
|       20-31 -                                       ;/                 |
+------------------------------------------------------------------------+
```


### ATH:0210B0h - MAC_DCU_GBL_IFS_EIFS aka MAC_DMA_D_GBL_IFS_EIFS

```
+-------------------------------------------------------------------------------+
|       0-15   DURATION                               ;-DCU global EIFS setting |
+-------------------------------------------------------------------------------+
```


### ATH:0210C0h..0210E4h - MAC_DCU_CHANNEL_TIME\[0..9\] aka MAC_DMA_D(0..9)\_CH..

```
+--------------------------------------------------------------------------------+
|       0-15  ChannelTime duration (us) (DURATION)    ;\MAC ChannelTime settings 
|       16    ChannelTime enable        (ENABLE)      ;/                         |
+--------------------------------------------------------------------------------+
```


### ATH:0210F0h - MAC_DCU_GBL_IFS_MISC aka MAC_DMA_D_GBL_IFS_MISC

```
+--------------------------------------------------------------------------+
|       0-2    LFSR slice select (LFSR_SLICE_SEL)       ;\                 
|       3      Turbo mode indication (TURBO_MODE)       ;                  |
|       4-9    hw6: SIFS_DUR_USEC           ;-hw6 only  ;                  |
|       10-19  -                                        ;                  |
|       20-21  DCU arbiter delay (ARB_DLY)              ; DCU global misc. |
|       22     hw6: SIFS_RST_UNCOND         ;\          ; IFS settings     
|       23     hw6: AIFS_RST_UNCOND         ;           ;                  |
|       24     hw6: LFSR_SLICE_RANDOM_DIS   ; hw6 only  ;                  |
|       25-26  hw6: CHAN_SLOT_WIN_DUR       ;           ;                  |
|       27     hw6: CHAN_SLOT_ALWAYS        ;/          ;                  |
|       28     IGNORE_BACKOFF                           ;                  |
|       29     hw6: SLOT_COUNT_RST_UNCOND   ;-hw6 only  ;                  |
|       30-31  -                                        ;/                 |
+--------------------------------------------------------------------------+
```


### ATH:021100h..021124h - MAC_DCU_MISC\[0..9\] aka MAC_DMA_D(0..9)\_MISC

```
+------------------------------------------------------------------------------------+
|       0-5    BKOFF_THRESH                   ;\                                     
|       6      SFC_RST_AT_TS_END_EN           ;                                      |
|       7      CW_RST_AT_TS_END_DIS           ;                                      |
|       8      FRAG_BURST_WAIT_QCU_EN         ;                                      |
|       9      FRAG_BURST_BKOFF_EN            ; MAC Miscellaneous                    |
|       10     -                              ; DCU-specific settings                |
|       11     HCF_POLL_EN                    ;                                      |
|       12     BKOFF_PF                       ; (specified as so for hw6)            |
|       13     -                              ; (hw4 bit numbers are undocumented,   |
|       14-15  VIRT_COLL_POLICY               ; although... actually the SAME bits   |
|       16     IS_BCN                         ; ARE documented, but for the "EOL"    |
|       17     ARB_LOCKOUT_IF_EN              ; registers instead of for "MISC"...?) |
|       18     LOCKOUT_GBL_EN                 ;                                      |
|       19     LOCKOUT_IGNORE                 ;                                      |
|       20     SEQNUM_FREEZE                  ;                                      |
|       21     POST_BKOFF_SKIP                ;                                      |
|       22     VIRT_COLL_CW_INC_EN            ;                                      |
|       23     RETRY_ON_BLOWN_IFS_EN          ;                                      |
|       24     SIFS_BURST_CHAN_BUSY_IGNORE    ;                                      |
|       25-31  -                              ;/                                     |
+------------------------------------------------------------------------------------+
```


### ATH:021140h - MAC_DCU_SEQ aka MAC_DMA_D_SEQNUM - MAC Frame sequence number

```
+-----------------------------------------------------------------------+
|       0-31   NUM                                                      |
+-----------------------------------------------------------------------+
```

BUG: The original hw4 header file used sorted addresses, but it\'s been having 00021140h placed between 000211A4h and 00021230h\... either it\'s just mis-sorted, or the address is mis-spelled? Probably just mis-sorted, because hw6 does confirm the address.

### ATH:021270h - MAC_DCU_PAUSE aka MAC_DMA_D_TXPSE

```
+-------------------------------------------------------------------------------+
|       0-9    REQUEST                      ;\DCU transmit pause control/status 
|       16     STATUS               (R)     ;/                                  |
+-------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      _____________ below in hw4 only _____________                    |
+-----------------------------------------------------------------------+
```


### ATH:021230h - MAC_DMA_D_FPCTL - DCU frame prefetch settings - hw4 only?

```
+-----------------------------------------------------------------------+
|       ...   unspecified                                               |
+-----------------------------------------------------------------------+
```


### ATH:021180h..021xx4h - MAC_DMA_D(0..9)\_EOL - hw4 only (removed in hw6)
;BUG: entry D(8..9) are officially at 21200h..21204h ;\\which is implemented
;BUG: entry D(8..9) are \*intended\* at 211A0h..211A4h ;/in actual hardware?
;BUG: below bits are probably meant to be \"MISC\" (not \"EOL\") ?

```
+------------------------------------------------------------------------------------+
|       0-5   Backoff threshold                                                      |
|       6     End of transmission series station RTS/data failure count reset policy |
|       7     End of transmission series CW reset policy                             |
|       8     Fragment Starvation Policy                                             |
|       9     Backoff during a frag burst                                            |
|       10    -                                                                      |
|       11    HFC poll enable                                                        |
|       12    Backoff persistence factor setting                                     |
|       13                                                                           |
|       14-15 Mask for Virtual collision handling policy                             |
|               (0=Normal, 1=Ignore, 2..3=Unspecified)                               |
|       16    Beacon use indication                                                  |
|       17-18 Mask for DCU arbiter lockout control                                   |
|               (0=No Lockout, 1=Intra-frame, 2=Global, 3=Unspecified)               |
|       19    DCU arbiter lockout ignore control                                     |
|       20    Sequence number increment disable                                      |
|       21    Post-frame backoff disable                                             |
|       22    Virtual coll. handling policy                                          |
|       23    Blown IFS handling policy                                              |
|       24-31 -                                                                      |
+------------------------------------------------------------------------------------+
```

BUG: The official source code assigns incorrect \"BCD-style\" values to MAC_DMA_D8_EOL and MAC_DMA_D9_EOL, the source code does also have a MAC_DMA_DEOL_ADDRESS(i) macro function; that function would work okay even with i=8..9.


```
+-----------------------------------------------------------------------+
|      _____________ below in hw6 only _____________                    |
+-----------------------------------------------------------------------+
```


### ATH:0212B0h - MAC_DCU_WOW_KACFG - hw6 only

```
+-----------------------------------------------------------------------+
|       0      TX_EN                                                    |
|       1      TIM_EN                                                   |
|       4-11   BCN_CNT                                                  |
|       12-23  RX_TIMEOUT_CNT                                           |
+-----------------------------------------------------------------------+
```


### ATH:0212F0h - MAC_DCU_TXSLOT - hw6 only

```
+-----------------------------------------------------------------------+
|       0-15   MASK                                                     |
+-----------------------------------------------------------------------+
```


### ATH:02143Ch - MAC_DCU_TXFILTER_CLEAR - hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:02147Ch - MAC_DCU_TXFILTER_SET - hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:021038h - MAC_DCU_TXFILTER_DCU0_31_0 - hw6 only
### ATH:021078h - MAC_DCU_TXFILTER_DCU0_63_32 - hw6 only
### ATH:0210B8h - MAC_DCU_TXFILTER_DCU0_95_64 - hw6 only
### ATH:0210F8h - MAC_DCU_TXFILTER_DCU0_127_96 - hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:02103Ch - MAC_DCU_TXFILTER_DCU8_31_0 - hw6 only (R)
### ATH:02107Ch - MAC_DCU_TXFILTER_DCU8_63_32 - hw6 only (R)
### ATH:0210BCh - MAC_DCU_TXFILTER_DCU8_95_64 - hw6 only (R)
### ATH:0210FCh - MAC_DCU_TXFILTER_DCU8_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021138h - MAC_DCU_TXFILTER_DCU1_31_0 - hw6 only (R)
### ATH:021178h - MAC_DCU_TXFILTER_DCU1_63_32 - hw6 only (R)
### ATH:0211B8h - MAC_DCU_TXFILTER_DCU1_95_64 - hw6 only (R)
### ATH:0211F8h - MAC_DCU_TXFILTER_DCU1_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02113Ch - MAC_DCU_TXFILTER_DCU9_31_0 - hw6 only (R)
### ATH:02117Ch - MAC_DCU_TXFILTER_DCU9_63_32 - hw6 only (R)
### ATH:0211BCh - MAC_DCU_TXFILTER_DCU9_95_64 - hw6 only (R)
### ATH:0211FCh - MAC_DCU_TXFILTER_DCU9_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021238h - MAC_DCU_TXFILTER_DCU2_31_0 - hw6 only (R)
### ATH:021278h - MAC_DCU_TXFILTER_DCU2_63_32 - hw6 only (R)
### ATH:0212B8h - MAC_DCU_TXFILTER_DCU2_95_64 - hw6 only (R)
### ATH:0212F8h - MAC_DCU_TXFILTER_DCU2_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021338h - MAC_DCU_TXFILTER_DCU3_31_0 - hw6 only (R)
### ATH:021378h - MAC_DCU_TXFILTER_DCU3_63_32 - hw6 only (R)
### ATH:0213B8h - MAC_DCU_TXFILTER_DCU3_95_64 - hw6 only (R)
### ATH:0213F8h - MAC_DCU_TXFILTER_DCU3_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021438h - MAC_DCU_TXFILTER_DCU4_31_0 - hw6 only (R)
### ATH:021478h - MAC_DCU_TXFILTER_DCU4_63_32 - hw6 only (R)
### ATH:0214B8h - MAC_DCU_TXFILTER_DCU4_95_64 - hw6 only (R)
### ATH:0214F8h - MAC_DCU_TXFILTER_DCU4_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021538h - MAC_DCU_TXFILTER_DCU5_31_0 - hw6 only (R)
### ATH:021578h - MAC_DCU_TXFILTER_DCU5_63_32 - hw6 only (R)
### ATH:0215B8h - MAC_DCU_TXFILTER_DCU5_95_64 - hw6 only (R)
### ATH:0215F8h - MAC_DCU_TXFILTER_DCU5_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021638h - MAC_DCU_TXFILTER_DCU6_31_0 - hw6 only (R)
### ATH:021678h - MAC_DCU_TXFILTER_DCU6_63_32 - hw6 only (R)
### ATH:0216B8h - MAC_DCU_TXFILTER_DCU6_95_64 - hw6 only (R)
### ATH:0216F8h - MAC_DCU_TXFILTER_DCU6_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:021738h - MAC_DCU_TXFILTER_DCU7_31_0 - hw6 only (R)
### ATH:021778h - MAC_DCU_TXFILTER_DCU7_63_32 - hw6 only (R)
### ATH:0217B8h - MAC_DCU_TXFILTER_DCU7_95_64 - hw6 only (R)
### ATH:0217F8h - MAC_DCU_TXFILTER_DCU7_127_96 - hw6 only (R)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                           (R)                       |
+-----------------------------------------------------------------------+
```




