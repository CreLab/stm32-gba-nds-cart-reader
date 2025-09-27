# DSi Atheros Wifi - Internal I/O - 028000h - WMAC PCU (hw2/hw4/hw6)


### ATH:028000h - MAC_PCU_STA_ADDR_L32 (aka hw2: REG_STA_ID0) ;hw2/hw4/hw6
### ATH:028004h - MAC_PCU_STA_ADDR_U16 (aka hw2: REG_STA_ID1) ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-47   ADDR (called STA_ADDR in hw2) (local MAC address)        |
|       48     STA_AP (called AP in hw2)                                |
|       49     ADHOC                                                    |
|       50     PW_SAVE (called PWR_SV in hw2)                           |
|       51     KEYSRCH_DIS (called NO_KEYSRCH in hw2)                   |
|       52     PCF                                                      |
|       53     USE_DEFANT (called USE_DEF_ANT in hw2)                   |
|       54     DEFANT_UPDATE (called DEF_ANT_UPDATE in hw2)             |
|       55     RTS_USE_DEF (called RTS_DEF_ANT in hw2)                  |
|       56     ACKCTS_6MB                                               |
|       57     BASE_RATE_11B (called RATE_11B in hw2)                   |
|       58     SECTOR_SELF_GEN                                          |
|       59     CRPT_MIC_ENABLE                                          |
|       60     KSRCH_MODE                                               |
|       61     PRESERVE_SEQNUM                                          |
|       62     CBCIV_ENDIAN                                             |
|       63     ADHOC_MCAST_SEARCH                                       |
+-----------------------------------------------------------------------+
```


### ATH:028008h - MAC_PCU_BSSID_L32 (aka hw2: REG_BSS_ID0) ;hw2/hw4/hw6
### ATH:02800Ch - MAC_PCU_BSSID_U16 (aka hw2: REG_BSS_ID1) ;hw2/hw4/hw6

```
+------------------------------------------------------------------------------+
|       0-47   ADDR (called BSSID in hw2)                                      |
|       48-58  AID (11bit, although claimed to be 16bit wide, bit48-63 in hw2) |
+------------------------------------------------------------------------------+
```


### ATH:0282B0h/02839Ch/028398h - MAC_PCU_BSSID2_L32 ;hw2/hw4/hw6
### ATH:0282B4h/0283A0h/02839Ch - MAC_PCU_BSSID2_U16 ;hw2/hw4/hw6

```
+---------------------------------------------------------------------------+
|       0-47   ADDR    (hw2: SEC_BSSID, ini:0)                ;\hw2/hw4/hw6 
|       48     ENABLE  (hw2: SEC_BSSID_ENABLE, ini:0)         ;/            |
|       49-51  -                                                            |
|       52-62  hw6: AID                                       ;-hw 6 only   |
|       63     -                                                            |
+---------------------------------------------------------------------------+
```

Observe that hw2/hw6 port addresses are different here (unlike as usually).

### ATH:028010h - MAC_PCU_BCN_RSSI_AVE (aka hw2:BCNRSSI) (R) ;hw2/hw4/hw6

```
+---------------------------------------------------------------------------+
|       0-11   AVE_VALUE (aka hw2:BCN_RSSI_AVE ini:800h) (R)  ;-hw2/hw4/hw6 |
|       16-27  hw6: AVE_VALUE2                           (R)  ;-hw6 only    |
+---------------------------------------------------------------------------+
```


### ATH:028014h - MAC_PCU_ACK_CTS_TIMEOUT (aka hw2:REG_TIME_OUT) ;hw2/hw4/hw6

```
+--------------------------------------------------------------------------+
|       0-13   ACK_TIMEOUT (aka 16bit wide, bit0-15: ACK_TIME_OUT in hw2)  |
|       16-29  CTS_TIMEOUT (aka 16bit wide, bit16-31: CTS_TIME_OUT in hw2) |
+--------------------------------------------------------------------------+
```


### ATH:028018h - MAC_PCU_BCN_RSSI_CTL (aka hw2:BCNSIG) ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    RSSI_LOW_THRESH  (aka hw2: BCN_RSSI_LO_THR, ini:0)       |
|       8-15   MISS_THRESH      (aka hw2: BCN_MISS_THR, ini:FFh)        |
|       16-23  RSSI_HIGH_THRESH (aka hw2: BCN_RSSI_HI_THR, ini:7Fh)     |
|       24-28  WEIGHT           (aka hw2: BCN_RSSI_WEIGHT, ini:0)       |
|       29     RESET            (aka hw2: BCN_RSSI_RESET)               |
+-----------------------------------------------------------------------+
```


### ATH:02801Ch - MAC_PCU_USEC_LATENCY (aka hw2:REG_USEC) ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       <-- hw2 (REG_USEC) -->    <--- hw4/hw6 ---------->              |
|       0-6    USEC     (7bit)    0-7    USEC       (8bit)              |
|       7-13   USEC32   (7bit)    8-13   -          (-)                 |
|       14-18  TX_DELAY (5bit)    14-22  TX_LATENCY (9bit)              |
|       19-24  RX_DELAY (6bit)    23-28  RX_LATENCY (6bit)              |
+-----------------------------------------------------------------------+
```


### ATH:02803Ch/028024h/02803Ch - MAC_PCU_RX_FILTER ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------------------+
|       0      UNICAST                                                              |
|       1      MULTICAST                                                            |
|       2      BROADCAST                                                            |
|       3      CONTROL                                                              |
|       4      BEACON                                                               |
|       5      PROMISCUOUS                                                          |
|       6      XR_POLL                                                              |
|       7      PROBE_REQ                                                            |
|       8      hw2: outcommented: SYNC        ;\hw4 and hw6 (outcommented in hw2)   
|       8      hw4/hw6: SYNC_FRAME            ;/                                    |
|       9      MY_BEACON                                                            |
|       10     hw4/hw6: COMPRESSED_BAR        ;\                                    
|       11     hw4/hw6: COMPRESSED_BA         ;                                     |
|       12     hw4/hw6: UNCOMPRESSED_BA_BAR   ; hw4 and hw6                         |
|       13     hw4/hw6: ASSUME_RADAR          ;                                     |
|       14     hw4/hw6: PS_POLL               ;                                     |
|       15     hw4/hw6: MCAST_BCAST_ALL       ;                                     |
|       16     hw4/hw6: RST_DLMTR_CNT_DISABLE ;/                                    |
|       17     hw4: FROM_TO_DS                ;\                                    
|       18-23  hw4: GENERIC_FTYPE             ; hw4 only (moved to bit20-28 in hw6) |
|       24-25  hw4: GENERIC_FILTER            ;/                                    |
|       17     hw6: HW_BCN_PROC_ENABLE        ;\                                    
|       18     hw6: MGMT_ACTION_MCAST         ; hw6 only                            |
|       19     hw6: CONTROL_WRAPPER           ;                                     |
|       20     hw6: FROM_TO_DS                ;   ;\these bits were formerly        
|       21-26  hw6: GENERIC_FTYPE             ;   ; in bit17-25 in hw4)             |
|       27-28  hw6: GENERIC_FILTER            ;   ;/                                |
|       29     hw6: MY_BEACON2                ;/                                    |
+-----------------------------------------------------------------------------------+
```


### ATH:028040h/028028h/028040h - MAC_PCU_MCAST_FILTER_L32 ;hw2/hw4/hw6
### ATH:028044h/02802Ch/028044h - MAC_PCU_MCAST_FILTER_U32 ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-63   VALUE (aka hw2: unspecified)                             |
+-----------------------------------------------------------------------+
```


### ATH:028048h/028030h/028048h - MAC_PCU_DIAG_SW ;hw2/hw4/hw6

```
+------------------------------------------------------------------------------+
|       0      INVALID_KEY_NO_ACK        (aka hw2:DIS_WEP_ACK          ;ini:0) |
|       1      NO_ACK                    (aka hw2:DIS_ACK              ;ini:0) |
|       2      NO_CTS                    (aka hw2:DIS_CTS              ;ini:0) |
|       3      NO_ENCRYPT                (aka hw2:DIS_ENC              ;ini:0) |
|       4      NO_DECRYPT                (aka hw2:DIS_DEC              ;ini:0) |
|       5      HALT_RX                   (aka hw2:DIS_RX               ;ini:0) |
|       6      LOOP_BACK                 (aka hw2:LOOP_BACK            ;ini:0) |
|       7      CORRUPT_FCS               (aka hw2:CORR_FCS             ;ini:0) |
|       8      DUMP_CHAN_INFO            (aka hw2:CHAN_INFO            ;ini:0) |
|       9-16   - (aka hw2: RESERVED)     (aka hw2:RESERVED             ;ini:0) |
|       17     ACCEPT_NON_V0             (aka hw2:ACCEPT_NONV0         ;ini:0) |
|       18-19  OBS_SEL_1_0               (aka hw2:OBS_SEL_0_1          ;ini:0) |
|       20     RX_CLEAR_HIGH             (aka hw2:RXCLR_HIGH           ;ini:0) |
|       21     IGNORE_NAV                (aka hw2:IGNORE_NAV           ;ini:0) |
|       22     CHAN_IDLE_HIGH            (aka hw2:CHANIDLE_HIGH        ;ini:0) |
|       23     PHYERR_ENABLE_EIFS_CTL    (aka hw2:PHYERR_ENABLE_NEW    ;ini:0) |
|       24     DUAL_CHAIN_CHAN_INFO      (aka hw2:DUAL_CHAIN_CHAN_INFO ;ini:0) |
|       25     FORCE_RX_ABORT            (aka hw2:FORCE_RX_ABORT       ;ini:0) |
|       26     SATURATE_CYCLE_CNT        (aka hw2:SATURATE_CYCLE_CNT   ;ini:0) |
|       27     OBS_SEL_2                 (aka hw2:OBS_SEL_2            ;ini:0) |
|       28     hw4/hw6: RX_CLEAR_CTL_LOW              ;\                       
|       29     hw4/hw6: RX_CLEAR_EXT_LOW              ; hw4/hw6 only           |
|       30-31  hw4/hw6: DEBUG_MODE                    ;/                       |
+------------------------------------------------------------------------------+
```


### ATH:028054h/028034h/028054h - MAC_PCU_TST_ADDAC ;hw2/hw4/hw6

```
+---------------------------------------------------------------------------------+
|       0      hw2: TEST_MODE                 ;\                                  
|       1      hw2: TEST_LOOP                 ; hw2 (moved to bit1-14 in hw4/hw6) |
|       2-12   hw2: LOOP_LEN                  ;                                   |
|       13     hw2: TEST_UPPER_8B             ;/                                  |
|       14     hw2: TEST_MSB                  ;-hw2 only                          |
|       15     hw2: TEST_CAPTURE              ;-hw2 (moved to bit19 in hw4/hw6)   |
+---------------------------------------------------------------------------------+
```

Differently arranged in hw4/hw6:

```
+---------------------------------------------------------------------------------+
|       0      hw4/hw6: CONT_TX               ;-hw4/hw6 only                      |
|       1      hw4/hw6: TESTMODE              ;\                                  
|       2      hw4/hw6: LOOP                  ; hw4/hw6 (formerly bit0-13 in hw2) |
|       3-13   hw4/hw6: LOOP_LEN              ;                                   |
|       14     hw4/hw6: UPPER_8B              ;/                                  |
|       15     hw6:     SAMPLE_SIZE_2K        ;-hw6 only                          |
|       16     hw4/hw6: TRIG_SEL              ;\                                  
|       17     hw4/hw6: TRIG_POLARITY         ; hw4/hw6 only                      |
|       18     hw4/hw6: CONT_TEST         (R) ;/                                  |
|       19     hw4/hw6: TEST_CAPTURE          ;-hw4/hw6 (formerly bit15 in hw2)   |
|       20     hw4/hw6: TEST_ARM              ;-hw4/hw6 only                      |
+---------------------------------------------------------------------------------+
```


### ATH:028058h/028038h/028058h - MAC_PCU_DEF_ANTENNA ;hw2/hw4/hw6

```
+----------------------------------------------------------------------------+
|       0-23   VALUE                          ;\hw4/hw6 (and maybe hw2, too) 
|       24     TX_DEF_ANT_SEL                 ;/                             |
|       25     hw6: SLOW_TX_ANT_EN            ;\                             
|       26     hw6: TX_CUR_ANT                ; hw6 only                     |
|       27     hw6: FAST_DEF_ANT              ;/                             |
|       28     RX_LNA_CONFIG_SEL              ;-hw4/hw6 (and maybe hw2, too) |
|       29     hw6: FAST_TX_ANT_EN            ;\                             
|       30     hw6: RX_ANT_EN                 ; hw6 only                     |
|       31     hw6: RX_ANT_DIV_ON             ;/                             |
+----------------------------------------------------------------------------+
```


### ATH:02805Ch/02803Ch/02805Ch - MAC_PCU_AES_MUTE_MASK_0 ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   FC      (hw2: ini:C7FFh)                                 |
|       16-31  QOS     (hw2: ini:FFFFh)                                 |
+-----------------------------------------------------------------------+
```


### ATH:028060h/028040h/028060h - MAC_PCU_AES_MUTE_MASK_1 ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   SEQ     (hw2: ini:000Fh)                                 |
|       16-31  FC_MGMT (hw2: ini:E7FFh)                                 |
+-----------------------------------------------------------------------+
```


### ATH:028064h/028044h/028064h - MAC_PCU_GATED_CLKS ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      -         (aka hw2: outcommented: SYNC, ini:1)           |
|       1      GATED_TX  (aka hw2: TX, ini:0)                           |
|       2      GATED_RX  (aka hw2: RX, ini:0)                           |
|       3      GATED_REG (aka hw2: REG, ini:0)                          |
+-----------------------------------------------------------------------+
```


### ATH:028068h/028048h/028068h - MAC_PCU_OBS_BUS_2 (R) ;hw2/hw4/hw6

```
+------------------------------------------------------------------------+
|       0-17   VALUE (aka hw2: OBS_BUS)               (R)  ;-hw2/hw4/hw6 |
|       18-21  hw6: WCF_STATE                         (R)  ;\            
|       22     hw6: WCF0_FULL                         (R)  ;             |
|       23     hw6: WCF1_FULL                         (R)  ; hw6 only    |
|       24-28  hw6: WCF_COUNT                         (R)  ;             |
|       29     hw6: MACBB_ALL_AWAKE                   (R)  ;/            |
+------------------------------------------------------------------------+
```


### ATH:02806Ch/02804Ch/02806Ch - MAC_PCU_OBS_BUS_1 (R) ;hw2/hw4/hw6

```
+-------------------------------------------------------------------------------+
|       0      PCU_DIRECTED                           (R)                       |
|       1      PCU_RX_END                             (R)                       |
|       2      RX_WEP                                 (R)                       |
|       3      RX_MY_BEACON                           (R)                       |
|       4      FILTER_PASS                            (R)                       |
|       5      TX_HCF                                 (R)                       |
|       6      TM_QUIET_TIME    (aka hw2: QUIET_TIME) (R)                       |
|       7      PCU_CHANNEL_IDLE (aka hw2: CHAN_IDLE)  (R)                       |
|       8      TX_HOLD                                (R)                       |
|       9      TX_FRAME                               (R)                       |
|       10     RX_FRAME                               (R)                       |
|       11     RX_CLEAR                               (R)                       |
|       12-17  WEP_STATE                              (R)                       |
|       20-23  hw2: RX_STATE (4bit)                   (R)  ;\hw2 (less bits)    
|       24-28  hw2: TX_STATE (5bit)                   (R)  ;/                   |
|       20-24  hw4/hw6: RX_STATE (5bit)               (R)  ;\hw4/hw6 (one more  
|       25-30  hw4/hw6: TX_STATE (6bit)               (R)  ;/bit than hw2 each) |
+-------------------------------------------------------------------------------+
```


### ATH:028080h/028054h/028080h - MAC_PCU_LAST_BEACON_TSF (R) ;hw2/hw4/hw6
### ATH:028664h - MAC_PCU_LAST_BEACON2_TSF ;extra beacon (R) ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   VALUE (hw2: unspecified/LAST_TSTP)          (R)          |
+-----------------------------------------------------------------------+
```


### ATH:028084h/028058h/028084h - MAC_PCU_NAV ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-25   VALUE (hw2: unspecified/NAV)                             |
+-----------------------------------------------------------------------+
```


### ATH:028088h/02805Ch/028088h - MAC_PCU_RTS_SUCCESS_CNT (R) ;hw2/hw4/hw6
### ATH:02808Ch/028060h/02808Ch - MAC_PCU_RTS_FAIL_CNT (R) ;hw2/hw4/hw6
### ATH:028090h/028064h/028090h - MAC_PCU_ACK_FAIL_CNT (R) ;hw2/hw4/hw6
### ATH:028094h/028068h/028094h - MAC_PCU_FCS_FAIL_CNT (R) ;hw2/hw4/hw6
### ATH:028098h/02806Ch/028098h - MAC_PCU_BEACON_CNT (R) ;hw2/hw4/hw6
### ATH:02809Ch - MAC_PCU_BEACON2_CNT (R) ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-15   VALUE (COUNT or so?) (hw2: unspecified)     (R)          |
+-----------------------------------------------------------------------+
```


### ATH:0280C0h/028070h/0280C0h - MAC_PCU_XRMODE ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    POLL_TYPE             (hw2: ini:1Ah)                     |
|       7      WAIT_FOR_POLL         (hw2: ini:0)                       |
|       20-31  FRAME_HOLD            (hw2: ini:680 decimal)             |
+-----------------------------------------------------------------------+
```


### ATH:0280C4h/028074h/0280C4h - MAC_PCU_XRDEL ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   SLOT_DELAY            (hw2: ini:360 (decimal)            |
|       16-31  CHIRP_DATA_DELAY      (hw2: ini:1680 decimal)            |
+-----------------------------------------------------------------------+
```


### ATH:0280C8h/028078h/0280C8h - MAC_PCU_XRTO ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   CHIRP_TIMEOUT         (hw2: ini:7200 decimal)            |
|       16-31  POLL_TIMEOUT          (hw2: ini:5000 decimal)            |
+-----------------------------------------------------------------------+
```


### ATH:0280CCh/02807Ch/0280CCh - MAC_PCU_XRCRP ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      SEND_CHIRP            (hw2: ini:0)                       |
|       16-31  CHIRP_GAP             (hw2: ini:500 decimal)             |
+-----------------------------------------------------------------------+
```


### ATH:0280D0h/028080h/0280D0h - MAC_PCU_XRSTMP ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RX_ABORT_RSSI         (hw2: ini:0)                       |
|       1      RX_ABORT_BSSID        (hw2: ini:0)                       |
|       2      TX_STOMP_RSSI         (hw2: ini:0)                       |
|       3      TX_STOMP_BSSID        (hw2: ini:0)                       |
|       4      TX_STOMP_DATA         (hw2: ini:0)                       |
|       5      RX_ABORT_DATA         (hw2: ini:0)                       |
|       8-15   TX_STOMP_RSSI_THRESH  (hw2: ini:25h)                     |
|       16-23  RX_ABORT_RSSI_THRESH  (hw2: ini:25h)                     |
+-----------------------------------------------------------------------+
```


### ATH:0280E0h/028084h/0280E0h - MAC_PCU_ADDR1_MASK_L32 ;hw2/hw4/hw6
### ATH:0280E4h/028088h/0280E4h - MAC_PCU_ADDR1_MASK_U16 ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-47   VALUE   (aka hw2:BSSID_MASK, ini:FFFFFFFFFFFFh)          |
+-----------------------------------------------------------------------+
```

This should be 48bit (as so in hw2/hw6, though hw4 claims 64bit, bit0-63).

### ATH:0280E8h/02808Ch/0280E8h - MAC_PCU_TPC ;hw2/hw4/hw6

```
+------------------------------------------------------------------------+
|       0-5    ACK_PWR   (hw2: ini:3Fh)                                  |
|       8-13   CTS_PWR   (hw2: ini:3Fh)                                  |
|       16-21  CHIRP_PWR (hw2: ini:3Fh)                                  |
|       24-29  hw6: RPT_PWR                                   ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:0280ECh/028090h/0280ECh - MAC_PCU_TX_FRAME_CNT ;hw2/hw4/hw6
### ATH:0280F0h/028094h/0280F0h - MAC_PCU_RX_FRAME_CNT ;hw2/hw4/hw6
### ATH:0280F4h/028098h/0280F4h - MAC_PCU_RX_CLEAR_CNT ;hw2/hw4/hw6
### ATH:0280F8h/02809Ch/0280F8h - MAC_PCU_CYCLE_CNT ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE (aka COUNT or so?) (aka hw2: CNT, ini:0)           |
+-----------------------------------------------------------------------+
```


### ATH:0280FCh/0280A0h/0280FCh - MAC_PCU_QUIET_TIME_1 ;hw2/hw4/hw6

```
+-------------------------------------------------------------------------------------+
|       0-15   hw2: NEXT_QUIET   (hw2: ini:0)                ;\hw2 only (not hw4/hw6) 
|       16     hw2: QUIET_ENABLE (hw2: ini:0)                ;/                       |
|       17     ACK_CTS_ENABLE    (hw2: ini:1)                ;-hw2/hw4/hw6            |
+-------------------------------------------------------------------------------------+
```


### ATH:028100h/0280A4h/028100h - MAC_PCU_QUIET_TIME_2 ;hw2/hw4/hw6

```
+----------------------------------------------------------------------------+
|       0-15   hw2: QUIET_PERIOD            (hw2: ini:0002h) ;\differs in    
|       0-15   hw4: -                                        ; hw2, hw4, hw6 |
|       0-15   hw6: DURATION2         ;-hw6 only             ;/              |
|       16-31  DURATION (aka hw2: QUIET_DURATION, ini:0001h) ;-hw2/hw/hw6    |
+----------------------------------------------------------------------------+
```


### ATH:028108h/0280A8h/028108h - MAC_PCU_QOS_NO_ACK ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    TWO_BIT_VALUES (hw2: NOACK_2_BIT_VALUES, ini:2)          |
|       4-6    BIT_OFFSET     (hw2: NOACK_BIT_OFFSET, ini:5)            |
|       7-8    BYTE_OFFSET    (hw2: NOACK_BYTE_OFFSET, ini:0)           |
+-----------------------------------------------------------------------+
```


### ATH:02810Ch/0280ACh/02810Ch - MAC_PCU_PHY_ERROR_MASK ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE          (hw2: PHYERR_MASK, ini:0)                 |
+-----------------------------------------------------------------------+
```


### ATH:028110h/0280B0h/028110h - MAC_PCU_XRLAT ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   VALUE          (hw2: XR_TX_DELAY, ini:168h)              |
+-----------------------------------------------------------------------+
```


### ATH:0280B4h/028114h - MAC_PCU_RXBUF ;hw4/hw6 (not hw2)

```
+-------------------------------------------------------------------------------------+
|       0-10   HIGH_PRIORITY_THRSHD                          ;\hw4/hw6 only (not hw2) 
|       11     REG_RD_ENABLE                                 ;/                       |
+-------------------------------------------------------------------------------------+
```

Note: hw2 does have a \"MAC_PCU_REG_TSF\" register in this place, which seems to be something different than the hw4/hw6 stuff (unless the hw4/hw6 \"RXBUF\" is related to the hw2 \"ACKSIFSMEM\" array?).

### ATH:028118h/0280B8h/028118h - MAC_PCU_MIC_QOS_CONTROL ;hw2/hw4/hw6

```
+-------------------------------------------------------------------------+
|       0-15   VALUE_0..7 (2bit each)  (aka hw2: MICQOSCTL, ini:00AAh)    |
|       16     ENABLE                  (aka hw2: MICQOSCTL_ENABLE, ini:1) |
+-------------------------------------------------------------------------+
```


### ATH:02811Ch/0280BCh/02811Ch - MAC_PCU_MIC_QOS_SELECT ;hw2/hw4/hw6

```
+--------------------------------------------------------------------------+
|       0-31   VALUE_0..7 (4bit each)  (aka hw2: MICQOSSEL, ini:00003210h) |
+--------------------------------------------------------------------------+
```


### ATH:028124h/0280C4h/028124h - MAC_PCU_FILTER_OFDM_CNT ;hw2/hw4/hw6
### ATH:028128h/0280C8h/028128h - MAC_PCU_FILTER_CCK_CNT ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-23   VALUE (count or so?)    (hw2: CNT, ini:0)                |
+-----------------------------------------------------------------------+
```


### ATH:02812Ch/0280CCh/02812Ch - MAC_PCU_PHY_ERR_CNT_1 ;hw2/hw4/hw6
### ATH:028134h/0280D4h/028134h - MAC_PCU_PHY_ERR_CNT_2 ;hw2/hw4/hw6
### ATH:028168h/0280E4h/028168h - MAC_PCU_PHY_ERR_CNT_3 ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-23   VALUE (count or so?)    (hw2: PHYCNT, ini:0)             |
+-----------------------------------------------------------------------+
```


### ATH:028130h/0280D0h/028130h - MAC_PCU_PHY_ERR_CNT_1_MASK ;hw2/hw4/hw6
### ATH:028138h/0280D8h/028138h - MAC_PCU_PHY_ERR_CNT_2_MASK ;hw2/hw4/hw6
### ATH:02816Ch/0280E8h/02816Ch - MAC_PCU_PHY_ERR_CNT_3_MASK ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE (mask or so?)     (hw2: PHYCNTMASK, ini:0)         |
+-----------------------------------------------------------------------+
```


### ATH:02813Ch/0280DCh/005144h - MAC_PCU_TSF_THRESHOLD ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   VALUE                   (hw2: TSFTHRESH, ini:FFFFh)      |
+-----------------------------------------------------------------------+
```

Observe that hw2/hw6 port addresses are different here (unlike as usually).

### ATH:028144h/0280E0h/028144h - MAC_PCU_PHY_ERROR_EIFS_MASK ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                   (hw2: MASK, ini:0)               |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      ________________________________ Misc Mode ________________________________ |
+----------------------------------------------------------------------------------+
```


### ATH:028120h/0280C0h/028120h - MAC_PCU_MISC_MODE ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      BSSID_MATCH_FORCE              (hw2: ini:0)              |
|       1      hw2: ACKSIFS_MEMORY_RESERVED   (hw2: ini:0)              |
|       1      hw4/hw6: DEBUG_MODE_AD                                   |
|       2      MIC_NEW_LOCATION(_ENABLE)      (hw2: ini:0)              |
|       3      TX_ADD_TSF                     (hw2: ini:0)              |
|       4      CCK_SIFS_MODE                  (hw2: ini:0)              |
|       5      hw2: BFCOEF_MODE_RESERVED      (hw2: ini:0)              |
|       6      hw2: BFCOEF_ENABLE             (hw2: ini:0)              |
|       7      hw2: BFCOEF_UPDATE_SELF_GEN    (hw2: ini:1)              |
|       8      hw2: BFCOEF_MCAST              (hw2: ini:1)              |
|       9      hw2: DUAL_CHAIN_ANT_MODE       (hw2: ini:0)              |
|       10     hw2: FALCON_DESC_MODE          (hw2: ini:0)              |
|       5-8    hw4: -                                                   |
|       5      hw6: RXSM2SVD_PRE_RST                                    |
|       6      hw6: RCV_DELAY_SOUNDING_IM_TXBF                          |
|       7-8    hw6: -                                                   |
|       9      hw4/hw6: DEBUG_MODE_BA_BITMAP                            |
|       10     hw4/hw6: DEBUG_MODE_SIFS                                 |
|       11     KC_RX_ANT_UPDATE               (hw2: ini:1)              |
|       12     TXOP_TBTT_LIMIT(_ENABLE)       (hw2: ini:0)              |
|       13     hw2: FALCON_BB_INTERFACE       (hw2: ini:0)              |
|       14     MISS_BEACON_IN_SLEEP           (hw2: ini:1)              |
|       15-16  -                                                        |
|       17     hw2: BUG_12306_FIX_ENABLE      (hw2: ini:1)              |
|       18     FORCE_QUIET_COLLISION          (hw2: ini:0)              |
|       19     hw2: BUG_12549_FORCE_TXBF      (hw2: ini:0)              |
|       20     BT_ANT_PREVENTS_RX             (hw2: ini:1)              |
|       21     TBTT_PROTECT                   (hw2: ini:1)              |
|       22     HCF_POLL_CANCELS_NAV           (hw2: ini:1)              |
|       23     RX_HCF_POLL_ENABLE             (hw2: ini:1)              |
|       24     CLEAR_VMF                      (hw2: ini:0)              |
|       25     CLEAR_FIRST_HCF                (hw2: ini:0)              |
|       26     hw2: ADHOC_MCAST_KEYID_ENABLE  (hw2: ini:0)              |
|       27     hw2: ALLOW_RAC                 (hw2: ini:0)              |
|       28-31  hw2: -                                                   |
|       26     hw4/hw6: CLEAR_BA_VALID                                  |
|       27     hw4/hw6: SEL_EVM                                         |
|       28     hw4/hw6: ALWAYS_PERFORM_KEY_SEARCH                       |
|       29     hw4/hw6: USE_EOP_PTR_FOR_DMA_WR                          |
|       30-31  hw4/hw6: DEBUG_MODE                                      |
+-----------------------------------------------------------------------+
```


### ATH:02825Ch/028144h/028344h - MAC_PCU_MISC_MODE2 ;hw2/hw4/hw6

```
+-------------------------------------------------------------------------------------+
|       0      hw2: MGMT_CRYPTO_ENABLE        (ini:0) ;moved to bit1 in hw4 ;\        
|       1      hw2: NO_CRYPTO_FOR_NON_DATA_PKT(ini:0) ;moved to bit2 in hw4 ; hw2     |
|       2-7    hw2: RESERVED                                                ;/        |
|       0      hw4/hw6: BUG_21532_FIX_ENABLE                                ;\        
|       1      hw4/hw6: MGMT_CRYPTO_ENABLE                                  ; hw4/hw6 |
|       2      hw4/hw6: NO_CRYPTO_FOR_NON_DATA_PKT                          ;/        |
|       3      hw4: RESERVED                                                          |
|       3      hw6: BUG_58603_FIX_ENABLE                                    ;-hw6     |
|       4      hw6 and hw4.2: BUG_58057_FIX_ENABLE ;-hw4.2 and up (not hw2 and hw4.0) |
|       5      hw4/hw6: RESERVED                                            ;\        
|       6      hw4/hw6: ADHOC_MCAST_KEYID_ENABLE                            ; hw4/hw6 |
|       7      hw4/hw6: CFP_IGNORE                                          ;/        |
|       8-15   MGMT_QOS                                                     ;-all hw  |
|       16     hw2: BC_MC_WAPI_MODE          (ini:0) ;moved to bit18 in hw4 ;\        
|       17     hw2: IGNORE_TXOP_FOR_1ST_PKT  (ini:0) ;moved to bit22 in hw4 ; hw2     |
|       18     hw2: IGNORE_TXOP_IF_ZERO      (ini:0) ;moved to bit23 in hw4 ;         |
|       19-31  hw2_ RESERVED                                                ;/        |
|       16     hw4/hw6: ENABLE_LOAD_NAV_BEACON_DURATION                     ;\        
|       17     hw4/hw6: AGG_WEP                                             ;         |
|       18     hw4/hw6: BC_MC_WAPI_MODE                                     ;         |
|       19     hw4/hw6: DUR_ACCOUNT_BY_BA                                   ; hw4/hw6 |
|       20     hw4/hw6: BUG_28676                                           ;         |
|       21     hw4/hw6: CLEAR_MORE_FRAG                                     ;         |
|       22     hw4/hw6: IGNORE_TXOP_1ST_PKT                                 ;/        |
|       23     hw4: IGNORE_TXOP_IF_ZERO  ;moved to MISC_MODE3.bit22 in hw6  ;\        
|       24     hw4: PM_FIELD_FOR_DAT     ;moved to MISC_MODE3.bit24 in hw6  ;         |
|       25     hw4: PM_FIELD_FOR_MGMT    ;moved to MISC_MODE3.bit25 in hw6  ; hw4     |
|       26     hw4: BEACON_FROM_TO_DS    ;moved to MISC_MODE3.bit23 in hw6? ;         |
|       27     hw4: RCV_TIMESTAMP_FIX    ;moved to bit25 in hw6             ;         |
|       28-31  hw4: RESERVED                                                ;/        |
|       23     hw6: MPDU_DENSITY_STS_FIX                                    ;\        
|       24     hw6: MPDU_DENSITY_WAIT_WEP                                   ;         |
|       25     hw6: RCV_TIMESTAMP_FIX    ;moved from bit27 in hw4           ;         |
|       27     hw6: DECOUPLE_DECRYPTION                                     ; hw6     |
|       28     hw6: H_TO_SW_DEBUG_MODE                                      ;         |
|       29     hw6: TXBF_ACT_RPT_DONE_PASS                                  ;         |
|       30     hw6: PCU_LOOP_TXBF                                           ;         |
|       31     hw6: CLEAR_WEP_TXBUSY_ON_TXURN                               ;/        |
+-------------------------------------------------------------------------------------+
```

Observe that hw2/hw6 port addresses are different here (unlike as usually).

### ATH:0283D0h - MAC_PCU_MISC_MODE3 ;hw6

```
+------------------------------------------------------------------------------------+
|       0      BUG_55702_FIX_ENABLE                                                  |
|       1      AES_3STREAM                                                           |
|       2      REGULAR_SOUNDING                                                      |
|       3      BUG_58011_FIX_ENABLE                                                  |
|       4      BUG_56991_FIX_ENABLE                                                  |
|       5      WOW_ADDR1_MASK_ENABLE                                                 |
|       6      BUG_61936_FIX_ENABLE                                                  |
|       7      CHECK_LENGTH_FOR_BA                                                   |
|       8-15   BA_FRAME_LENGTH                                                       |
|       16     MATCH_TID_FOR_BA                                                      |
|       17     WAPI_ORDER_MASK                                                       |
|       18     BB_LDPC_EN                                                            |
|       19     SELF_GEN_SMOOTHING                                                    |
|       20     SMOOTHING_FORCE                                                       |
|       21     ALLOW_RAC                                                             |
|       22     IGNORE_TXOP_IF_ZER0  ;uh, ZerNull or Zero?   ;moved from MODE2.bit23  |
|       23     BEACON_FROM_TO_DS_CHECK                      ;moved from MODE2.bit26? |
|       24     PM_FIELD_FOR_DAT                             ;moved from MODE2.bit24  |
|       25     PM_FIELD_FOR_MGMT                            ;moved from MODE2.bit25  |
|       26     PM_FIELD2_FOR_CTL                                                     |
|       27     PM_FIELD2_FOR_DAT                                                     |
|       28     PM_FIELD2_FOR_MGT                                                     |
|       29     KEY_MISS_FIX                                                          |
|       30     PER_STA_WEP_ENTRY_ENABLE                                              |
|       31     TIME_BASED_DISCARD_EN                                                 |
+------------------------------------------------------------------------------------+
```


### ATH:0283D4h - MAC_PCU_MISC_MODE4 ;hw6

```
+-----------------------------------------------------------------------+
|       0      BC_MC_WAPI_MODE2_EN                                      |
|       1      BC_MC_WAPI_MODE2                                         |
|       2      SYNC_TSF_ON_BEACON                                       |
|       3      SYNC_TSF_ON_BCAST_PROBE_RESP                             |
|       4      SYNC_TSF_ON_MCAST_PROBE_RESP                             |
|       5      SYNC_TSF_ON_UCAST_MOON_PROBE_RESP                        |
|       6      SYNC_TSF_ON_UCAST_PROBE_RESP                             |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ______________________________ Basic Rate Set ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:0282A4h - MAC_PCU_BASIC_RATE_SET0 ;hw2 (other as in hw4/hw6)
### ATH:0282A8h - MAC_PCU_BASIC_RATE_SET1 ;hw2 (other as in hw4/hw6)
### ATH:0282ACh - MAC_PCU_BASIC_RATE_SET2 ;hw2 (other as in hw4/hw6)

```
+-----------------------------------------------------------------------+
|      Bitfields for hw2 RATE_SET0 register:                            |
|       0-4    BRATE_1MB_L             (hw2: ini:#CCK_RATE_1Mb_L)       |
|       5-9    BRATE_2MB_L             (hw2: ini:#CCK_RATE_2Mb_L)       |
|       10-14  BRATE_2MB_S             (hw2: ini:#CCK_RATE_2Mb_S)       |
|       15-19  BRATE_5_5MB_L           (hw2: ini:#CCK_RATE_5_5Mb_L)     |
|       20-24  BRATE_5_5MB_S           (hw2: ini:#CCK_RATE_5_5Mb_S)     |
|       25-29  BRATE_11MB_L            (hw2: ini:#CCK_RATE_11Mb_L)      |
|      Bitfields for hw2 RATE_SET1 register:                            |
|       0-4    BRATE_11MB_S            (hw2: ini:#CCK_RATE_11Mb_S)      |
|       5-9    BRATE_6MB               (hw2: ini:#OFDM_RATE_6Mb)        |
|       10-14  BRATE_9MB               (hw2: ini:#OFDM_RATE_6Mb, too?)  |
|       15-19  BRATE_12MB              (hw2: ini:#OFDM_RATE_12Mb)       |
|       20-24  BRATE_18MB              (hw2: ini:#OFDM_RATE_12Mb, too?) |
|       25-29  BRATE_24MB              (hw2: ini:#OFDM_RATE_24Mb)       |
|      Bitfields for hw2 RATE_SET2 register:                            |
|       0-4    BRATE_36MB              (hw2: ini:#OFDM_RATE_24Mb, too?) |
|       5-9    BRATE_48MB              (hw2: ini:#OFDM_RATE_24Mb, too?) |
|       10-14  BRATE_54MB              (hw2: ini:#OFDM_RATE_24Mb, too?) |
+-----------------------------------------------------------------------+
```

Alongsides, hw2 source code defines following \"Rate\" values:

```
+-------------------------------------------------------------------------------------+
|       OFDM_RATE_6Mb    = 0Bh     CCK_RATE_1Mb_L   = 1Bh      XR_RATE_0_25Mb   = 03h |
|       OFDM_RATE_9Mb    = 0Fh     CCK_RATE_2Mb_L   = 1Ah      XR_RATE_0_5Mb    = 07h |
|       OFDM_RATE_12Mb   = 0Ah     CCK_RATE_2Mb_S   = 1Eh      XR_RATE_1Mb      = 02h |
|       OFDM_RATE_18Mb   = 0Eh     CCK_RATE_5_5Mb_L = 19h      XR_RATE_2Mb      = 06h |
|       OFDM_RATE_24Mb   = 09h     CCK_RATE_5_5Mb_S = 1Dh      XR_RATE_3Mb      = 01h |
|       OFDM_RATE_36Mb   = 0Dh     CCK_RATE_11Mb_L  = 18h      (the XR_stuff might be |
|       OFDM_RATE_48Mb   = 08h     CCK_RATE_11Mb_S  = 1Ch      unrelated to RATE_SET) |
|       OFDM_RATE_54Mb   = 0Ch                                                        |
+-------------------------------------------------------------------------------------+
```

Note: The hw2 RATE_SET registers contain 75bit (30+30+15bit), hw4/hw6 has similar RATE_SET registers with 100bit (4x25bit), that registers may have similar functions - but their content is obviously differently arranged.

### ATH:028328h/0283E0h - MAC_PCU_BASIC_RATE_SET0 ;hw4/hw6 (other as in hw2)
### ATH:02832Ch/0283E4h - MAC_PCU_BASIC_RATE_SET1 ;hw4/hw6 (other as in hw2)
### ATH:028330h/0283E8h - MAC_PCU_BASIC_RATE_SET2 ;hw4/hw6 (other as in hw2)
### ATH:028334h/0283ECh - MAC_PCU_BASIC_RATE_SET3 ;hw4/hw6 (new in hw4/hw6)

```
+-----------------------------------------------------------------------------------+
|       0-24   VALUE (maybe this 25bit value is meant to contain 5 rates of 5bit ?) |
+-----------------------------------------------------------------------------------+
```

Note: The hw4/hw6 RATE_SET registers contain 100bit (4x25bit), hw2 has similar RATE_SET registers with 75bit (30+30+15bit), that registers may have similar functions - but their content is obviously differently arranged.


```
+-----------------------------------------------------------------------------------+
|      ______________________________ Bluetooth Mode ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028170h/0280ECh/028170h - MAC_PCU_BLUETOOTH_MODE ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TIME_EXTEND            (hw2: ini:20h)                    |
|       8      TX_STATE_EXTEND        (hw2: ini:1)                      |
|       9      TX_FRAME_EXTEND        (hw2: ini:1)                      |
|       10-11  MODE                   (hw2: ini:3)                      |
|       12     QUIET                  (hw2: ini:1)                      |
|       13-16  QCU_THRESH             (hw2: ini:1)                      |
|       17     RX_CLEAR_POLARITY      (hw2: ini:0)                      |
|       18-23  PRIORITY_TIME          (hw2: ini:05h)                    |
|       24-31  FIRST_SLOT_TIME        (hw2: ini:9Bh)                    |
+-----------------------------------------------------------------------+
```


### ATH:02817Ch/0280F4h/02817Ch - MAC_PCU_BLUETOOTH_MODE2 ;hw2/hw4/hw6

```
+------------------------------------------------------------------------------------+
|       0-7    BCN_MISS_THRESH (hw2: ini:0)                                          |
|       8-15   BCN_MISS_CNT                           (R)                            |
|       16     HOLD_RX_CLEAR (hw2: ini:0)                                            |
|       17     SLEEP_ALLOW_BT_ACCESS (hw2: WL_CONTROL_ANT, ini:0)                    |
|       18     hw2: RESPOND_TO_BT_ACTIVE (hw2: ini:0)                 ;-hw2 only     |
|       19     PROTECT_BT_AFTER_WAKEUP (hw2: ini:0)                                  |
|       20     DISABLE_BT_ANT (hw2: ini:0)                                           |
|       21     hw4/hw6: QUIET_2_WIRE                                  ;\             
|       22-23  hw4/hw6: WL_ACTIVE_MODE                                ;              |
|       24     hw4/hw6: WL_TXRX_SEPARATE                              ;              |
|       25     hw4/hw6: RS_DISCARD_EXTEND                             ; hw4/hw6 only |
|       26-27  hw4/hw6: TSF_BT_ACTIVE_CTRL                            ;              |
|       28-29  hw4/hw6: TSF_BT_PRIORITY_CTRL                          ;              |
|       30     hw4/hw6: INTERRUPT_ENABLE                              ;              |
|       31     hw4/hw6: PHY_ERR_BT_COLL_ENABLE                        ;/             |
+------------------------------------------------------------------------------------+
```


### ATH:028164h/0281D4h - MAC_PCU_BLUETOOTH_MODE3 ;hw4/hw6 (not hw2)

```
+-------------------------------------------------------------------------------------+
|       0-7    WL_ACTIVE_TIME                                ;\                       
|       8-15   WL_QC_TIME                                    ;                        |
|       16-19  ALLOW_CONCURRENT_ACCESS                       ;                        |
|       20     hw4: SHARED_RX                      ;<-- hw4  ;                        |
|       20     hw6: AGC_SATURATION_CNT_ENABLE      ;<-- hw6  ; hw4/hw6 only (not hw2) |
|       21     WL_PRIORITY_OFFSET_EN                         ;                        |
|       22     RFGAIN_LOCK_SRC                               ;                        |
|       23     DYNAMIC_PRI_EN                                ;                        |
|       24     DYNAMIC_TOGGLE_WLA_EN                         ;                        |
|       25-26  SLOT_SLOP                                     ;                        |
|       27     BT_TX_ON_EN                                   ;                        |
|       28-31  BT_PRIORITY_EXTEND_THRES                      ;/                       |
+-------------------------------------------------------------------------------------+
```


### ATH:028168h/0281D8h - MAC_PCU_BLUETOOTH_MODE4 ;hw4/hw6 (not hw2)

```
+-------------------------------------------------------------------------------------+
|       0-15   BT_ACTIVE_EXTEND                              ;\hw4/hw6 only (not hw2) 
|       16-31  BT_PRIORITY_EXTEND                            ;/                       |
+-------------------------------------------------------------------------------------+
```


### ATH:0281DCh - MAC_PCU_BLUETOOTH_MODE5 ;hw6 (not hw2/hw4)

```
+-------------------------------------------------------------------------------------+
|       0-2    MCI_WL_LEVEL_MULT                             ;\                       
|       3      TX_ON_SRC                                     ;                        |
|       4-19   TIMER_TARGET                                  ; hw6 only (not hw2/hw4) |
|       20     SHARED_RX                                     ;                        |
|       21     USE_BTP_EXT                                   ;/                       |
+-------------------------------------------------------------------------------------+
```


### ATH:028174h/0280F0h/0281E0h - MAC_PCU_BLUETOOTH_WEIGHTS ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   BT_WEIGHT              (hw2: ini:FA50h)                  |
|       16-31  WL_WEIGHT              (hw2: ini:FAA4h)                  |
+-----------------------------------------------------------------------+
```

Observe that hw2/hw6 port addresses are different here (unlike as usually).
For hw4 only: There\'s also a \"WL_WEIGHT_CONTD\" in a \"WEIGHTS\" register.

### ATH:028158h - MAC_PCU_BLUETOOTH_WEIGHTS2 ;hw4 only (not hw2/hw6)

```
+-------------------------------------------------------------------------------------+
|       16-31  WL_WEIGHT_CONTD (extends "WL_WEIGHT" or so)   ;-hw4 only (not hw2/hw6) |
+-------------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      _______________________________ hw2/hw6 only _______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028178h/028154h/028178h - MAC_PCU_HCF_TIMEOUT ;hw2/hw6 (not hw4)

```
+-------------------------------------------------------------------------------------+
|       0-15   VALUE      (hw2: TIMEOUT, ini:100h)           ;-hw2/hw6 only (not hw4) |
+-------------------------------------------------------------------------------------+
```


### ATH:0281D0h/0280F8h/0281D0h - MAC_PCU_TXSIFS ;hw2/hw6 (not hw4)

```
+-----------------------------------------------------------------------+
|       0-7    SIFS_TIME               (hw2: ini: 16 decimal)           |
|       8-11   TX_LATENCY              (hw2: ini:2)                     |
|       12-14  ACK_SHIFT               (hw2: ini:3)                     |
+-----------------------------------------------------------------------+
```


### ATH:0281ECh/0280FCh/0281ECh - MAC_PCU_TXOP_X ;hw2/hw6 (not hw4)

```
+-----------------------------------------------------------------------+
|       0-7    VALUE                   (hw2: TXOP_X, ini:0)             |
+-----------------------------------------------------------------------+
```


### ATH:0281F0h/028100h/0281F0h - MAC_PCU_TXOP_0_3 ;hw2/hw6 (not hw4)
### ATH:0281F4h/028104h/0281F4h - MAC_PCU_TXOP_4_7 ;hw2/hw6 (not hw4)
### ATH:0281F8h/028108h/0281F8h - MAC_PCU_TXOP_8_11 ;hw2/hw6 (not hw4)
### ATH:0281FCh/02810Ch/0281FCh - MAC_PCU_TXOP_12_15 ;hw2/hw6 (not hw4)

```
+-----------------------------------------------------------------------+
|       0-7    TXOP_0 / TXOP_4 / TXOP_8  / TXOP_12   (hw2: ini:0)       |
|       8-15   TXOP_1 / TXOP_5 / TXOP_9  / TXOP_13   (hw2: ini:0)       |
|       16-23  TXOP_2 / TXOP_6 / TXOP_10 / TXOP_14   (hw2: ini:0)       |
|       24-31  TXOP_3 / TXOP_7 / TXOP_11 / TXOP_15   (hw2: ini:0)       |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      _______________________________ hw4/hw6 only _______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028304h/028024h - MAC_PCU_BT_WL_1 ;hw4/hw6
### ATH:028308h/028028h - MAC_PCU_BT_WL_2 ;hw4/hw6
### ATH:02830Ch/02802Ch - MAC_PCU_BT_WL_3 ;hw4/hw6
### ATH:028310h/028030h - MAC_PCU_BT_WL_4 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   WEIGHT                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028314h/028034h - MAC_PCU_COEX_EPTA ;hw4/hw6 only

```
+-----------------------------------------------------------------------+
|       0-5    LINKID                                                   |
|       6-12   WT_IDX                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028300h/0281E4h - MAC_PCU_BT_BT_ASYNC ;hw4/hw6 (not hw2)

```
+------------------------------------------------------------------------------+
|       0-3    TXHP_WEIGHT                            ;\                       
|       4-7    TXLP_WEIGHT                            ; hw4/hw6 only (not hw2) |
|       8-11   RXHP_WEIGHT                            ;                        |
|       12-15  RXLP_WEIGHT                            ;/                       |
+------------------------------------------------------------------------------+
```


### ATH:028110h/028264h - MAC_PCU_LOGIC_ANALYZER ;hw4/hw6 (not hw2)

```
+------------------------------------------------------------------------------+
|       0      HOLD                                   ;\                       
|       1      CLEAR                                  ;                        |
|       2      STATE                          (R)     ; hw4/hw6 only (not hw2) |
|       3      ENABLE                                 ;                        |
|       4-7    QCU_SEL                                ;                        |
|       8-17   INT_ADDR                       (R)     ;                        |
|       18-31  DIAG_MODE                              ;/                       |
+------------------------------------------------------------------------------+
```


### ATH:028114h/028268h - MAC_PCU_LOGIC_ANALYZER_32L ;hw4/hw6 (not hw2)
### ATH:028118h/02826Ch - MAC_PCU_LOGIC_ANALYZER_16U ;hw4/hw6 (not hw2)

```
+------------------------------------------------------------------------------+
|       0-47   MASK                                   ;\hw4/hw6 only (not hw2) 
|       48-31  -                                      ;/                       |
+------------------------------------------------------------------------------+
```


### ATH:02815Ch/0281C8h - MAC_PCU_BLUETOOTH_TSF_BT_ACTIVE ;hw4/hw6 (not hw2)

```
+------------------------------------------------------------------------------+
|       0-31   VALUE                          (R)     ;-hw4/hw6 only (not hw2) |
+------------------------------------------------------------------------------+
```


### ATH:028160h/0281CCh - MAC_PCU_BLUETOOTH_TSF_BT_PRIORITY ;hw4/hw6 (not hw2)

```
+------------------------------------------------------------------------------+
|       0-31   VALUE                          (R)     ;-hw4/hw6 only (not hw2) |
+------------------------------------------------------------------------------+
```


### ATH:028318h/028150h - MAC_PCU_COEX_LNAMAXGAIN1 ;hw4/hw6 (not hw2)
### ATH:02831Ch/028154h - MAC_PCU_COEX_LNAMAXGAIN2 ;hw4/hw6 (not hw2)
### ATH:028320h/028158h - MAC_PCU_COEX_LNAMAXGAIN3 ;hw4/hw6 (not hw2)
### ATH:028324h/02815Ch - MAC_PCU_COEX_LNAMAXGAIN4 ;hw4/hw6 (not hw2)

```
+-------------------------------------------------------------------------------------+
|       0-7    MAXGAIN1     ;\that are 4 gain value          ;\                       
|       8-15   MAXGAIN2     ; for each of the 4 registers    ; hw4/hw6 only (not hw2) |
|       16-23  MAXGAIN3     ; (ie. 16 values in total)       ;                        |
|       24-31  MAXGAIN4     ;/                               ;/                       |
+-------------------------------------------------------------------------------------+
```


### ATH:028050h/028070h - MAC_PCU_DYM_MIMO_PWR_SAVE ;hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0      hw4/hw6: USE_MAC_CTRL                          ;\             
|       1      hw4/hw6: HW_CTRL_EN                            ;              |
|       2      hw4/hw6: SW_CHAIN_MASK_SEL                     ; hw4/hw6 only |
|       4-6    hw4/hw6: LOW_PWR_CHAIN_MASK                    ;              |
|       8-10   hw4/hw6: HI_PWR_CHAIN_MASK                     ;/             |
+----------------------------------------------------------------------------+
```


### ATH:02811Ch/02829Ch - MAC_PCU_PHY_ERR_CNT_MASK_CONT ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-7    MASK1                                                    |
|       8-15   MASK2                                                    |
|       16-23  MASK3                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028120h/028300h - MAC_PCU_AZIMUTH_MODE ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0      DISABLE_TSF_UPDATE                                       |
|       1      KEY_SEARCH_AD1                                           |
|       2      TX_TSF_STATUS_SEL                                        |
|       3      RX_TSF_STATUS_SEL                                        |
|       4      CLK_EN                                                   |
|       5      TX_DESC_EN                                               |
|       6      ACK_CTS_MATCH_TX_AD2                                     |
|       7      BA_USES_AD1                                              |
|       8      hw6: WMAC_CLK_SEL                                        |
|       9      hw6: FILTER_PASS_HOLD                                    |
+-----------------------------------------------------------------------+
```


### ATH:02814Ch/028314h - MAC_PCU_AZIMUTH_TIME_STAMP ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028124h/028318h - MAC_PCU_20_40_MODE ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0      JOINED_RX_CLEAR                                          |
|       1      EXT_PIFS_ENABLE                                          |
|       2      TX_HT20_ON_EXT_BUSY                                      |
|       3      SWAMPED_FORCES_RX_CLEAR_CTL_IDLE                         |
|       4-15   PIFS_CYCLES                                              |
+-----------------------------------------------------------------------+
```


### ATH:028128h/028328h - MAC_PCU_RX_CLEAR_DIFF_CNT ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:02812Ch/02832Ch - MAC_PCU_SELF_GEN_ANTENNA_MASK ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-2    VALUE                                                    |
|       3      hw6: ONE_RESP_EN                                         |
|       4      hw6: FORCE_CHAIN_0                                       |
+-----------------------------------------------------------------------+
```


### ATH:028130h/028330h - MAC_PCU_BA_BAR_CONTROL ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-3    COMPRESSED_OFFSET                                        |
|       4-7    ACK_POLICY_OFFSET                                        |
|       8      COMPRESSED_VALUE                                         |
|       9      ACK_POLICY_VALUE                                         |
|       10     FORCE_NO_MATCH                                           |
|       11     TX_BA_CLEAR_BA_VALID                                     |
|       12     UPDATE_BA_BITMAP_QOS_NULL                                |
+-----------------------------------------------------------------------+
```


### ATH:028134h/028334h - MAC_PCU_LEGACY_PLCP_SPOOF ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-7    EIFS_MINUS_DIFS                                          |
|       8-12   MIN_LENGTH                                               |
+-----------------------------------------------------------------------+
```


### ATH:028138h/028338h - MAC_PCU_PHY_ERROR_MASK_CONT ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-7    MASK_VALUE                                               |
|       16-23  EIFS_VALUE                                               |
|       24-31  hw6: AIFS_VALUE                                          |
+-----------------------------------------------------------------------+
```


### ATH:02813Ch/02833Ch - MAC_PCU_TX_TIMER ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-14   TX_TIMER                                                 |
|       15     TX_TIMER_ENABLE                                          |
|       16-19  RIFS_TIMER                                               |
|       20-24  QUIET_TIMER                                              |
|       25     QUIET_TIMER_ENABLE                                       |
+-----------------------------------------------------------------------+
```


### ATH:028140h/028340h - MAC_PCU_TXBUF_CTRL ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       0-11   USABLE_ENTRIES                                           |
|       16     TX_FIFO_WRAP_ENABLE                                      |
+-----------------------------------------------------------------------+
```


### ATH:028148h/028348h - MAC_PCU_ALT_AES_MUTE_MASK ;hw4/hw6 (not hw2)

```
+-----------------------------------------------------------------------+
|       16-31  QOS                                                      |
+-----------------------------------------------------------------------+
```


### ATH:028338h/028600h - MAC_PCU_RX_INT_STATUS0 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    FRAME_CONTROL_L                (R)                       |
|       8-15   FRAME_CONTROL_H                (R)                       |
|       16-23  DURATION_L                     (R)                       |
|       24-31  DURATION_H                     (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02833Ch/028604h - MAC_PCU_RX_INT_STATUS1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-17   VALUE                          (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:028340h/028608h - MAC_PCU_RX_INT_STATUS2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-26   VALUE                          (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:028344h/02860Ch - MAC_PCU_RX_INT_STATUS3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-23   VALUE                          (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:028348h/028610h - HT_HALF_GI_RATE1 ;MCS0..3 ;hw4/hw6
### ATH:02834Ch/028614h - HT_HALF_GI_RATE2 ;MCS4..7 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    MCS0 / MCS4                                              |
|       8-15   MCS1 / MCS5                                              |
|       16-23  MCS2 / MCS6                                              |
|       24-31  MCS3 / MCS7                                              |
+-----------------------------------------------------------------------+
```


### ATH:028350h/028618h - HT_FULL_GI_RATE1 ;MCS0..3 ;hw4/hw6
### ATH:028354h/02861Ch - HT_FULL_GI_RATE2 ;MCS4..7 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    MCS0 / MCS4                                              |
|       8-15   MCS1 / MCS5                                              |
|       16-23  MCS2 / MCS6                                              |
|       24-31  MCS3 / MCS7                                              |
+-----------------------------------------------------------------------+
```


### ATH:028358h/028620h - LEGACY_RATE1 ;RATE 8..12 ;hw4/hw6
### ATH:02835Ch/028624h - LEGACY_RATE2 ;RATE 13..15 and RATE 24..25 ;hw4/hw6
### ATH:028360h/028628h - LEGACY_RATE3 ;RATE 26..30 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    RATE8  / RATE13 / RATE26                                 |
|       6-11   RATE9  / RATE14 / RATE27                                 |
|       12-17  RATE10 / RATE15 / RATE28                                 |
|       18-23  RATE11 / RATE24 / RATE29                                 |
|       24-29  RATE12 / RATE25 / RATE30                                 |
+-----------------------------------------------------------------------+
```


### ATH:028364h/02862Ch - RX_INT_FILTER ;hw4/hw6

```
+-----------------------------------------------------------------------------------+
|       0      ENABLE                                                               |
|       1      DIRECTED                                                             |
|       2      BCAST                                                                |
|       3      MCAST                                                                |
|       4      RTS                                                                  |
|       5      ACK                                                                  |
|       6      CTS                                                                  |
|       7      RETRY                                                                |
|       8      MORE_DATA                                                            |
|       9      MORE_FRAG                                                            |
|       10     RATE_HIGH                                                            |
|       11     RATE_LOW                                                             |
|       12     RSSI                                                                 |
|       13     LENGTH_HIGH                                                          |
|       14     LENGTH_LOW                                                           |
|       15     EOSP                                                                 |
|       16     AMPDU                                                                |
|       17     hw4.2: BEACON                  ;-hw6 and newer "hw4.2" revision only |
|       18     hw6:   RSSI_HIGH               ;-hw6 only                            |
+-----------------------------------------------------------------------------------+
```


### ATH:028368h/028630h - RX_INT_OVERFLOW ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      STATUS                                                   |
+-----------------------------------------------------------------------+
```


### ATH:02836Ch/028634h - RX_FILTER_THRESH0 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    RATE_HIGH                                                |
|       8-15   RATE_LOW                                                 |
|       16-23  RSSI_LOW                                                 |
|       24-31  hw6: RSSI_HIGH                                           |
+-----------------------------------------------------------------------+
```


### ATH:028370h/028638h - RX_FILTER_THRESH1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   LENGTH_HIGH                                              |
|       12-23  LENGTH_LOW                                               |
+-----------------------------------------------------------------------+
```


### ATH:028374h/02863Ch - RX_PRIORITY_THRESH0 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    RATE_HIGH                                                |
|       8-15   RATE_LOW                                                 |
|       16-23  RSSI_HIGH                                                |
|       24-31  RSSI_LOW                                                 |
+-----------------------------------------------------------------------+
```


### ATH:028378h/028640h - RX_PRIORITY_THRESH1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-11   LENGTH_HIGH                                              |
|       12-23  LENGTH_LOW                                               |
|       24-31  XCAST_RSSI_HIGH                                          |
+-----------------------------------------------------------------------+
```


### ATH:02837Ch/028644h - RX_PRIORITY_THRESH2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    PRESP_RSSI_HIGH                                          |
|       8-15   MGMT_RSSI_HIGH                                           |
|       16-23  BEACON_RSSI_HIGH                                         |
|       24-31  NULL_RSSI_HIGH                                           |
+-----------------------------------------------------------------------+
```


### ATH:028380h/028648h - RX_PRIORITY_THRESH3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    PREQ_RSSI_HIGH                                           |
|       8-15   PS_POLL_RSSI_HIGH                                        |
+-----------------------------------------------------------------------+
```


### ATH:028384h/02864Ch - RX_PRIORITY_OFFSET0 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    PHY_RATE_HIGH                                            |
|       6-11   PHY_RATE_LOW                                             |
|       12-17  RSSI_HIGH                                                |
|       18-23  RSSI_LOW                                                 |
|       24-29  XCAST_RSSI_HIGH                                          |
+-----------------------------------------------------------------------+
```


### ATH:028388h/028650h - RX_PRIORITY_OFFSET1 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    LENGTH_HIGH                                              |
|       6-11   LENGTH_LOW                                               |
|       12-17  PRESP_RSSI_HIGH                                          |
|       18-23  RETX                                                     |
|       24-29  RTS                                                      |
+-----------------------------------------------------------------------+
```


### ATH:02838Ch/028654h - RX_PRIORITY_OFFSET2 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    XCAST                                                    |
|       6-11   PRESP                                                    |
|       12-17  ATIM                                                     |
|       18-23  MGMT                                                     |
|       24-29  BEACON                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028390h/028658h - RX_PRIORITY_OFFSET3 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    MORE                                                     |
|       6-11   EOSP                                                     |
|       12-17  AMPDU                                                    |
|       18-23  AMSDU                                                    |
|       24-29  PS_POLL                                                  |
+-----------------------------------------------------------------------+
```


### ATH:028394h/02865Ch - RX_PRIORITY_OFFSET4 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    PREQ                                                     |
|       6-11   NULL                                                     |
|       12-17  BEACON_SSID                                              |
|       18-23  MGMT_RSSI_HIGH                                           |
|       24-29  BEACON_RSSI_HIGH                                         |
+-----------------------------------------------------------------------+
```


### ATH:028398h/028660h - RX_PRIORITY_OFFSET5 ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-5    NULL_RSSI_HIGH                                           |
|       6-11   PREQ_RSSI_HIGH                                           |
|       12-17  PS_POLL_RSSI_HIGH                                        |
+-----------------------------------------------------------------------+
```


### ATH:028200h..0282FCh - MAC_PCU_BT_BT\[0..63\] ;hw4 (at 028200h)
### ATH:028500h..0285FCh - MAC_PCU_BT_BT\[0..63\] ;hw6 (at 028500h)

```
+-----------------------------------------------------------------------+
|       0-31   WEIGHT                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028400h..0284FCh - MAC_PCU_TXBUF_BA\[0..63\] ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:028800h..028BFCh - MAC_PCU_KEY_CACHE_1\[0..255\] ;hw4 (256 words)
### ATH:028800h..028FFCh - MAC_PCU_KEY_CACHE\[0..511\] ;hw6 (512 words)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:02E000h..02E7FCh - MAC_PCU_BUF\[0..511\] ;hw4 (512 words)
### ATH:02E000h..02FFFCh - MAC_PCU_BUF\[0..2047\] ;hw6 (2048 words)

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      _________________________________ hw6 only _________________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:0280A0h - MAC_PCU_BASIC_SET ;hw6 only

```
+------------------------------------------------------------------------+
|       0-31   MCS                                            ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:0280A4h - MAC_PCU_MGMT_SEQ ;hw6 only

```
+------------------------------------------------------------------------+
|       0-11   MIN                                            ;\hw6 only 
|       16-27  MAX                                            ;/         |
+------------------------------------------------------------------------+
```


### ATH:0280A8h - MAC_PCU_BF_RPT1 ;hw6 only

```
+------------------------------------------------------------------------+
|       0-7    V_ACTION_VALUE                                 ;\         
|       8-15   CV_ACTION_VALUE                                ; hw6 only |
|       16-23  CATEGORY_VALUE                                 ;          |
|       24-27  FRAME_SUBTYPE_VALUE                            ;          |
|       28-29  FRAME_TYPE_VALUE                               ;/         |
+------------------------------------------------------------------------+
```


### ATH:0280ACh - MAC_PCU_BF_RPT2 ;hw6 only

```
+------------------------------------------------------------------------+
|       0-3    FRAME_SUBTYPE_VALUE                            ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:0280B0h - MAC_PCU_TX_ANT_1 ;hw6 only
### ATH:0280B4h - MAC_PCU_TX_ANT_2 ;hw6 only
### ATH:0280B8h - MAC_PCU_TX_ANT_3 ;hw6 only
### ATH:0280BCh - MAC_PCU_TX_ANT_4 ;hw6 only

```
+------------------------------------------------------------------------+
|       0-31   VALUE                                          ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:028038h - MAC_PCU_MAX_CFP_DUR ;hw6 only (merged two hw4 registers here)

```
+-----------------------------------------------------------------------------------+
|       0-15   VALUE                     ;-formerly bit0-15 of "PCU_MAX_CFP_DUR"    |
|       16-19  USEC_FRAC_NUMERATOR       ;-formerly bit0-3 of "MAC_PCU_MAX_CFP_DUR" |
|       24-27  USEC_FRAC_DENOMINATOR     ;-formerly bit4-7 of "MAC_PCU_MAX_CFP_DUR" |
+-----------------------------------------------------------------------------------+
```


### ATH:028020h - MAC_PCU_BCN_RSSI_CTL2 ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-7    RSSI2_LOW_THRESH                                         |
|       16-23  RSSI2_HIGH_THRESH                                        |
|       29     RESET2                                                   |
+-----------------------------------------------------------------------+
```


### ATH:0280DCh - MAC_PCU_SELF_GEN_DEFAULT ;hw6 only

```
+------------------------------------------------------------------------+
|       0-2    MMSS                                           ;\         
|       3-4    CEC                                            ; hw6 only |
|       5      STAGGER_SOUNDING                               ;/         |
+------------------------------------------------------------------------+
```


### ATH:02831Ch - MAC_PCU_H_XFER_TIMEOUT ;hw6 only

```
+------------------------------------------------------------------------+
|       0-4    VALUE                                          ;\         
|       5      DISABLE                                        ;          |
|       6      EXTXBF_IMMEDIATE_RESP                          ; hw6 only |
|       7      DELAY_EXTXBF_ONLY_UPLOAD_H                     ;          |
|       8      EXTXBF_NOACK_NORPT                             ;/         |
+------------------------------------------------------------------------+
```


### ATH:028200h - MAC_PCU_TDMA_TXFRAME_START_TIME_TRIGGER_LSB ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028204h - MAC_PCU_TDMA_TXFRAME_START_TIME_TRIGGER_MSB ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028208h - MAC_PCU_TDMA_SLOT_ALERT_CNTL ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028284h - PCU_1US ;hw6

```
+-----------------------------------------------------------------------+
|       0-6    SCALER                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028288h - PCU_KA ;hw6

```
+-----------------------------------------------------------------------+
|       0-11   DEL                                                      |
+-----------------------------------------------------------------------+
```


### ATH:028350h - ASYNC_FIFO_REG1 ;hw6

```
+-----------------------------------------------------------------------+
|       0-29   DBG                                                      |
+-----------------------------------------------------------------------+
```


### ATH:028354h - ASYNC_FIFO_REG2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-27   DBG                                                      |
+-----------------------------------------------------------------------+
```


### ATH:028358h - ASYNC_FIFO_REG3 ;hw6

```
+-----------------------------------------------------------------------+
|       0-9    DBG                                                      |
|       10     DATAPATH_SEL                                             |
|       31     SFT_RST_N                                                |
+-----------------------------------------------------------------------+
```



### ATH:028388h - MAC_PCU_LOCATION_MODE_CONTROL ;hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE                                                   |
|       1      UPLOAD_H_DISABLE                                         |
+-----------------------------------------------------------------------+
```


### ATH:02838Ch - MAC_PCU_LOCATION_MODE_TIMER ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```



### ATH:0283A0h - MAC_PCU_DIRECT_CONNECT ;hw6

```
+-----------------------------------------------------------------------+
|       0      TSF2_ENABLE                                              |
|       1      TS_TSF_SEL                                               |
|       2      TSF1_UPDATE                                              |
|       3      TSF2_UPDATE                                              |
|       4      MY_BEACON_OVERRIDE                                       |
|       5      MY_BEACON2_OVERRIDE                                      |
|       6      BMISS_CNT_TSF_SEL                                        |
|       7      BMISS_CNT_OVERRIDE                                       |
|       8-31   RESERVED                                                 |
+-----------------------------------------------------------------------+
```


### ATH:0283A4h - MAC_PCU_TID_TO_AC ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:0283A8h - MAC_PCU_HP_QUEUE ;hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE                                                   |
|       1      AC_MASK_BE                                               |
|       2      AC_MASK_BK                                               |
|       3      AC_MASK_VI                                               |
|       4      AC_MASK_VO                                               |
|       5      HPQON_UAPSD                                              |
|       6      FRAME_FILTER_ENABLE0                                     |
|       7      FRAME_BSSID_MATCH0                                       |
|       8-9    FRAME_TYPE0                                              |
|       10-11  FRAME_TYPE_MASK0                                         |
|       12-15  FRAME_SUBTYPE0                                           |
|       16-19  FRAME_SUBTYPE_MASK0                                      |
|       20     UAPSD_EN                                                 |
|       21     PM_CHANGE                                                |
|       22     NON_UAPSD_EN                                             |
|       23     UAPSD_AC_MUST_MATCH                                      |
|       24     UAPSD_ONLY_QOS                                           |
+-----------------------------------------------------------------------+
```


### ATH:0283BCh - MAC_PCU_AGC_SATURATION_CNT0 ;hw6
### ATH:0283C0h - MAC_PCU_AGC_SATURATION_CNT1 ;hw6
### ATH:0283C4h - MAC_PCU_AGC_SATURATION_CNT2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:0283C8h - MAC_PCU_HW_BCN_PROC1 ;hw6

```
+-----------------------------------------------------------------------+
|       0      CRC_ENABLE                                               |
|       1      RESET_CRC                                                |
|       2      EXCLUDE_BCN_INTVL                                        |
|       3      EXCLUDE_CAP_INFO                                         |
|       4      EXCLUDE_TIM_ELM                                          |
|       5      EXCLUDE_ELM0                                             |
|       6      EXCLUDE_ELM1                                             |
|       7      EXCLUDE_ELM2                                             |
|       8-15   ELM0_ID                                                  |
|       16-23  ELM1_ID                                                  |
|       24-31  ELM2_ID                                                  |
+-----------------------------------------------------------------------+
```


### ATH:0283CCh - MAC_PCU_HW_BCN_PROC2 ;hw6

```
+-----------------------------------------------------------------------+
|       0      FILTER_INTERVAL_ENABLE                                   |
|       1      RESET_INTERVAL                                           |
|       2      EXCLUDE_ELM3                                             |
|       8-15   FILTER_INTERVAL                                          |
|       16-23  ELM3_ID                                                  |
+-----------------------------------------------------------------------+
```


### ATH:0283DCh - MAC_PCU_PS_FILTER ;hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE                                                   |
|       1      PS_SAVE_ENABLE                                           |
+-----------------------------------------------------------------------+
```


### ATH:028668h - MAC_PCU_PHY_ERROR_AIFS ;hw6

```
+-----------------------------------------------------------------------+
|       0      MASK_ENABLE                                              |
+-----------------------------------------------------------------------+
```


### ATH:02866Ch - MAC_PCU_PHY_ERROR_AIFS_MASK ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028670h - MAC_PCU_FILTER_RSSI_AVE ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    AVE_VALUE                                                |
|       8-10   NUM_FRAMES_EXPONENT                                      |
|       11     ENABLE                                                   |
|       12     RESET                                                    |
+-----------------------------------------------------------------------+
```


### ATH:028674h - MAC_PCU_TBD_FILTER ;hw6

```
+-----------------------------------------------------------------------+
|       0      USE_WBTIMER_TX_TS                                        |
|       1      USE_WBTIMER_RX_TS                                        |
+-----------------------------------------------------------------------+
```


### ATH:028678h - MAC_PCU_BT_ANT_SLEEP_EXTEND ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   CNT                                                      |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      _____________________ Wake on Wireless (WOW) hw6 only _____________________ |
+----------------------------------------------------------------------------------+
```


### ATH:02825Ch - MAC_PCU_WOW1 ;WOW Misc ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    PATTERN_ENABLE                                           |
|       8-15   PATTERN_DETECT                 (R)                       |
|       16     MAGIC_ENABLE                                             |
|       17     MAGIC_DETECT                   (R)                       |
|       18     INTR_ENABLE                                              |
|       19     INTR_DETECT                    (R)                       |
|       20     KEEP_ALIVE_FAIL                (R)                       |
|       21     BEACON_FAIL                    (R)                       |
|       28-31  CW_BITS                                                  |
+-----------------------------------------------------------------------+
```


### ATH:028260h - MAC_PCU_WOW2 ;WOW AIFS/SLOT/TRY_CNT ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    AIFS                                                     |
|       8-15   SLOT                                                     |
|       16-23  TRY_CNT                                                  |
+-----------------------------------------------------------------------+
```


### ATH:028270h - MAC_PCU_WOW3_BEACON_FAIL ;WOW Beacon Fail Enable ;hw6

```
+-----------------------------------------------------------------------+
|       0      ENABLE                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028274h - MAC_PCU_WOW3_BEACON ;WOW Beacon Timeout ;hw6
### ATH:028278h - MAC_PCU_WOW3_KEEP_ALIVE ;WOW Keep-Alive Timeout ;hw6

```
+-----------------------------------------------------------------------+
|       0-31   TIMEOUT                                                  |
+-----------------------------------------------------------------------+
```


### ATH:028370h - MAC_PCU_WOW4 ;WOW Pattern Enable/Detect ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    PATTERN_ENABLE                                           |
|       8-15   PATTERN_DETECT                 (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02835Ch - MAC_PCU_WOW5 ;WOW RX Abort Enable ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   RX_ABORT_ENABLE                                          |
+-----------------------------------------------------------------------+
```


### ATH:02834Ch - MAC_PCU_WOW6 (R) ;WOW RX Buf Start Addr ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   RXBUF_START_ADDR               (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:02827Ch - MAC_PCU_WOW_KA ;WOW Auto/Fail/BkoffCs Enable/Disable ;hw6

```
+-----------------------------------------------------------------------+
|       0      AUTO_DISABLE                                             |
|       1      FAIL_DISABLE                                             |
|       2      BKOFF_CS_ENABLE                                          |
+-----------------------------------------------------------------------+
```


### ATH:028294h - PCU_WOW4 ;WOW Offset 0..3 ;hw6
### ATH:028298h - PCU_WOW5 ;WOW Offset 4..7 ;hw6
### ATH:028378h - PCU_WOW6 ;WOW Offset 8..11 ;hw6
### ATH:02837Ch - PCU_WOW7 ;WOW Offset 12..15 ;hw6

```
+-------------------------------------------------------------------------------------+
|       0-7    OFFSET0 / OFFSET4 / OFFSET8  / OFFSET12        ;<-- 1st offset in LSBs |
|       8-15   OFFSET1 / OFFSET5 / OFFSET9  / OFFSET13                                |
|       16-23  OFFSET2 / OFFSET6 / OFFSET10 / OFFSET14                                |
|       24-31  OFFSET3 / OFFSET7 / OFFSET11 / OFFSET15                                |
+-------------------------------------------------------------------------------------+
```


### ATH:028360h - MAC_PCU_WOW_LENGTH1 ;WOW Pattern 0..3 ;hw6
### ATH:028364h - MAC_PCU_WOW_LENGTH2 ;WOW Pattern 4..7 ;hw6
### ATH:028380h - MAC_PCU_WOW_LENGTH3 ;WOW Pattern 8..11 ;hw6
### ATH:028384h - MAC_PCU_WOW_LENGTH4 ;WOW Pattern 12..15 ;hw6

```
+-------------------------------------------------------------------------------------+
|       0-7    PATTERN_3 / PATTERN_7 / PATTERN_11 / PATTERN_15                        |
|       8-15   PATTERN_2 / PATTERN_6 / PATTERN_10 / PATTERN_14                        |
|       16-23  PATTERN_1 / PATTERN_5 / PATTERN_9  / PATTERN_13                        |
|       24-31  PATTERN_0 / PATTERN_4 / PATTERN_8  / PATTERN_12   ;1st pattern in MSBs |
+-------------------------------------------------------------------------------------+
```


### ATH:02828Ch - WOW_EXACT ;WOW Exact Length/Offset 1 ;hw6
### ATH:028374h - WOW2_EXACT ;WOW Exact Length/Offset 2 ;hw6

```
+-----------------------------------------------------------------------+
|       0-7    LENGTH                                                   |
|       8-15   OFFSET                                                   |
+-----------------------------------------------------------------------+
```


### ATH:028368h - WOW_PATTERN_MATCH_LESS_THAN_256_BYTES ;hw6

```
+-----------------------------------------------------------------------+
|       0-15   EN                                                       |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      _________________________________ hw4 only _________________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028020h - PCU_MAX_CFP_DUR ;hw4 only

```
+-----------------------------------------------------------------------+
|       0-15   VALUE                                                    |
+-----------------------------------------------------------------------+
```

Note: This register does have (almost) the same name as the register below, but without the \"MAC\_\" prefix. In hw6, these two registers have been merged into a single register (called MAC_PCU_MAX_CFP_DUR). In hw2, registers REG_CFP_PERIOD and REG_CFP_DUR might be equivalent?

### ATH:028150h - MAC_PCU_MAX_CFP_DUR ;hw4 only

```
+-----------------------------------------------------------------------+
|       0-3    USEC_FRAC_NUMERATOR                                      |
|       4-7    USEC_FRAC_DENOMINATOR                                    |
+-----------------------------------------------------------------------+
```

Note: See \"PCU_MAX_CFP_DUR\" (other register with similar name, but without \"MAC\_\" prefix).

### ATH:0283A4h - MAC_PCU_TSF1_STATUS_L32 ;hw4 only
### ATH:0283A8h - MAC_PCU_TSF1_STATUS_U32 ;hw4 only

```
+-----------------------------------------------------------------------+
|       0-63   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:0283ACh - MAC_PCU_TSF2_STATUS_L32 ;hw4 only
### ATH:0283B0h - MAC_PCU_TSF2_STATUS_U32 ;hw4 only

```
+-----------------------------------------------------------------------+
|       0-63   VALUE                                                    |
+-----------------------------------------------------------------------+
```


### ATH:029800h..029FFCh - MAC_PCU_BASEBAND_0\[0..511\] ;hw4
### ATH:02A000h..02BFFCh - MAC_PCU_BASEBAND_1\[0..2047\] ;hw4

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```

These two \"MAC_PCU\" areas are just placeholders for the Baseband Registers at 029800h and up (see BB chapter for details).

### ATH:02C000h..02CFFCh - MAC_PCU_BASEBAND_2\[0..1023\] ;hw4
### ATH:02D000h..02DFFCh - MAC_PCU_BASEBAND_3\[0..1023\] ;hw4

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```

Unknown what these two \"MAC_PCU\" areas are intended for.


```
+-----------------------------------------------------------------------------------+
|      _________________________________ hw2 only _________________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028500h.. (140h..17Fh) - MAC_PCU_REG_FTYPE\[0..3Fh\] ;hw2

```
+-----------------------------------------------------------------------+
|       0      BFCOEF_RX_UPDATE_NORMAL                                  |
|       1      BFCOEF_RX_UPDATE_SELF_GEN                                |
|       2      BFCOEF_TX_ENABLE_NORMAL                                  |
|       3      BFCOEF_TX_ENABLE_SELF_GEN                                |
|       4      BFCOEF_TX_ENABLE_GEN                                     |
|       5      BFCOEF_TX_ENABLE_MCAST                                   |
|       6      FILTER_PASS_IF_ALL                                       |
|       7      FILTER_PASS_IF_DIRECTED                                  |
|       8      FILTER_PASS_IF_MCAST                                     |
|       9      FILTER_PASS_IF_BCAST                                     |
|       10     FILTER_PASS_MC_BC_BSSID                                  |
+-----------------------------------------------------------------------+
```


### ATH:028020h - REG_BEACON ;hw2 only

```
+-----------------------------------------------------------------------------------+
|       0-15   BEACON_PERIOD                                                        |
|       16-22  TIM_OFFSET                                                           |
|       23     unspecified                                                          |
|       24     RESET_TSF           <--- related to hw4/hw6: see MAC_PCU_RESET_TSF ? |
+-----------------------------------------------------------------------------------+
```


### ATH:028024h - REG_CFP_PERIOD ;hw2 only
### ATH:028038h - REG_CFP_DUR ;hw2 only

```
+-----------------------------------------------------------------------+
|       unspecified                                                     |
+-----------------------------------------------------------------------+
```

These two hw2 registers have unspecified content and purpose. Going by the names, they might be similar or equivalent to \"MAC_PCU_MAX_CFP_DUR\" and \"PCU_MAX_CFP_DUR\" on hw4 (although if so, unknown which one would be which).

### ATH:028028h - REG_TIMER0 ;hw2 only
### ATH:02802Ch - REG_TIMER1 ;hw2 only
### ATH:028030h - REG_TIMER2 ;hw2 only
### ATH:028034h - REG_TIMER3 ;hw2 only

```
+-------------------------------------------------------------------------------------+
|       unspecified         ;MAYBE related to MAC_PCU_BT_WL_1..4 or so in hw4/hw6 (?) |
+-------------------------------------------------------------------------------------+
```


### ATH:02804Ch - REG_TSF_L32 ;hw2 only \... aka MAC_PCU_TSF_L32 ?
### ATH:028050h - REG_TSF_U32 ;hw2 only \... aka MAC_PCU_TSF_U32 ?

```
+-----------------------------------------------------------------------+
|       unspecified                                                     |
+-----------------------------------------------------------------------+
```


### ATH:028104h - MAC_PCU_REG_TSF ;hw2 only ;aka MAC_PCU_TSF_ADD_PLL on hw4?

```
+--------------------------------------------------------------------------------+
|       0-7    TSF_INCREMENT          (hw2: ini:1)                    ;-hw2 only |
+--------------------------------------------------------------------------------+
```


### ATH:028114h - MAC_PCU_REG_ACKSIFS_RESERVED ;hw2 only

```
+--------------------------------------------------------------------------------+
|       0-7    ACKSIFS_INCREMENT_RESERVED     (hw2: ini:0)            ;-hw2 only |
+--------------------------------------------------------------------------------+
```

Related to the \"MAC_PCU_REG_ACKSIFSMEM_RESERVED\[0..1Fh\]\" array?

### ATH:028680h.. (1A0h..1BFh) - MAC_PCU_REG_ACKSIFSMEM_RESERVED\[0..1Fh\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-9    NORMAL_RESERVED                                          |
|       10-19  TURBO_RESERVED                                           |
+-----------------------------------------------------------------------+
```


### ATH:028700h.. (1C0h..1DFh) - MAC_PCU_REG_DUR\[0..1Fh\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-15   DUR_RATE_TO_DURATION                                     |
+-----------------------------------------------------------------------+
```


### ATH:0287C0h.. (1F0h..1F7h) - MAC_PCU_REG_RTD\[0..7\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-4    RTD_RATE_TO_DB_0                                         |
|       8-12   RTD_RATE_TO_DB_1                                         |
|       16-20  RTD_RATE_TO_DB_2                                         |
|       24-28  RTD_RATE_TO_DB_3                                         |
+-----------------------------------------------------------------------+
```


### ATH:0287E0h.. (1F8h..1FFh) - MAC_PCU_REG_DTR\[0..7\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-4    DTR_DB_TO_RATE_0                                         |
|       8-12   DTR_DB_TO_RATE_1                                         |
|       16-20  DTR_DB_TO_RATE_2                                         |
|       24-28  DTR_DB_TO_RATE_3                                         |
+-----------------------------------------------------------------------+
```


### ATH:028800h.. (200h..5FFh) - MAC_PCU_REG_KC\[0..3FFh\] ;hw2
Below bitfields are supposedly somehow stored in multiple words\...?

```
+-------------------------------------------------------------------------------------+
|       0-31   KC_KEY_31_0                ;aka byte 00h..03h ?                        |
|       0-15   KC_KEY_47_32               ;aka byte 04h..05h (and 06h..07h unused?) ? |
|       0-31   KC_KEY_79_48               ;aka byte 08h..0Bh ?                        |
|       0-15   KC_KEY_95_80               ;aka byte 0Ch..0Dh (and 0Eh..0Fh unused?) ? |
|       0-31   KC_KEY_127_96              ;aka byte 10h..13h ?                        |
|       0-2    KC_KEY_TYPE                ;\                                          
|       3      KC_LAST_ANTENNA            ;                                           |
|       4-8    KC_ASYNC_ACK_OFFSET        ;                                           |
|       9      KC_UPDATE_BEAM_FORMING     ;aka byte 14h..15h (and 16h..17h unused?) ? |
|       10     KC_RX_CHAIN_0_ACK_ANT      ;                                           |
|       11     KC_RX_CHAIN_1_ACK_ANT      ;                                           |
|       12     KC_TX_CHAIN_0_ANT_SEL      ;                                           |
|       13     KC_TX_CHAIN_1_ANT_SEL      ;                                           |
|       14     KC_TX_CHAIN_SEL            ;/                                          |
|       0-31   KC_ADDR_32_1               ;aka byte 18h..1Bh ? (no bit 0 ?)           |
|       0-14   KC_ADDR_47_33              ;aka byte 1Ch..1Dh (and 1Eh..1Fh unused?) ? |
|       1      KC_VALID                   ;aka byte 20h      (and 21h..xxh unused?) ? |
+-------------------------------------------------------------------------------------+
```


### ATH:028180h..02819Ch - MAC_PCU_REG_BFCOEF1\[0..7\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-23   TSF                                                      |
|       24-30  KEYIDX                                                   |
|       31     KEY_VALID                    (hw2: ini:0)                |
+-----------------------------------------------------------------------+
```


### ATH:0281C0h - MAC_PCU_REG_BFCOEF2 ;hw2

```
+-----------------------------------------------------------------------+
|       0-22   THRESH                       (hw2: ini:0)                |
|       23     unspecified                                              |
|       24-31  LOCK                         (hw2: ini:0)                |
+-----------------------------------------------------------------------+
```


### ATH:0281C4h - MAC_PCU_REG_KCMASK ;hw2

```
+-----------------------------------------------------------------------+
|       0-15   KCMASK_47_32                 (hw2: ini:0000h)            |
|       16     KCMASK_31_0                  (hw2: ini:0)                |
+-----------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      ___________________________ hw2 "MCI" registers ___________________________ |
+----------------------------------------------------------------------------------+
```


Below \"MCIxxx\" registers exist on hw2 only. Purpose is unknown. There seems to be nothing equivalent in hw4. However, hw6 is having several \"MCI_xxx\" registers (see WLAN Coex section; unknown if that\'s related to hw2 MCI stuff).

### ATH:028268h - MAC_PCU_REG_MCICTL ;Control ;hw2

```
+-----------------------------------------------------------------------+
|       0      MCI_ENABLE              (hw2: ini:0)                     |
|       1      OLA_ENABLE              (hw2: ini:1)                     |
|       2      PREEMPT_ENABLE          (hw2: ini:1)                     |
|       3      CHANNEL_BUSY_ENABLE     (hw2: ini:1)                     |
|       4-9    EARLY_NOTIFY_DELAY      (hw2: ini:5)                     |
|       10     BMISS_FORCE_WL          (hw2: ini:0)                     |
|       11     SLEEP_FORCE_BT          (hw2: ini:1)                     |
|       12     HP_QCU_STOMP_BT         (hw2: ini:0)                     |
|       31     MCI_BUSY                                                 |
+-----------------------------------------------------------------------+
```


### ATH:02826Ch - MAC_PCU_REG_MCIISR ;Interrupt Status ;hw2
### ATH:028270h - MAC_PCU_REG_MCIIER ;Interrupt Enable ;hw2

```
+-----------------------------------------------------------------------+
|       0      ACT_RPT_RCV_INT         (hw2: stat and enable: ini:0)    |
|       1      ACT_DEN_RCV_INT         (hw2: stat and enable: ini:0)    |
|       2      FRQ_RPT_RCV_INT         (hw2: stat and enable: ini:0)    |
|       3      QOS_RPT_RCV_INT         (hw2: stat and enable: ini:0)    |
|       4      GEN_RPT_RCV_INT         (hw2: stat and enable: ini:0)    |
+-----------------------------------------------------------------------+
```


### ATH:028274h - MAC_PCU_REG_MCIWLP ;WLP ?? ;hw2 (hw2: ini:0)

```
+-----------------------------------------------------------------------+
|       unspecified                                                     |
+-----------------------------------------------------------------------+
```


### ATH:028278h - MAC_PCU_REG_MCIARW ;AR Write? ;hw2 (hw2: ini:0)
### ATH:02827Ch - MAC_PCU_REG_MCIARR ;AR Read? ;hw2
### ATH:028280h - MAC_PCU_REG_MCIADW ;AD Write? ;hw2 (hw2: ini:0)
### ATH:028284h - MAC_PCU_REG_MCIADR ;AD Read? ;hw2
### ATH:028288h - MAC_PCU_REG_MCIFRW ;FR Write? ;hw2 (hw2: ini:0)
### ATH:02828Ch - MAC_PCU_REG_MCIFRR ;FR Read? ;hw2
### ATH:028290h - MAC_PCU_REG_MCIQRW ;QR Write? ;hw2 (hw2: ini:0)
### ATH:028294h - MAC_PCU_REG_MCIQRR ;QR Read? ;hw2
### ATH:028298h - MAC_PCU_REG_MCIGRW ;GR Write? ;hw2 (hw2: ini:0)
### ATH:02829Ch - MAC_PCU_REG_MCIGRR ;GR Read? ;hw2

```
+-----------------------------------------------------------------------+
|       unspecified                                                     |
+-----------------------------------------------------------------------+
```


### ATH:0282A0h - MAC_PCU_REG_MCISTAT ;Status (counters?) ;hw2

```
+-----------------------------------------------------------------------+
|       0-7    ACT_RPT_RCV_CNT         (hw2: ini:0)                     |
|       8-15   QC_CNT                  (hw2: ini:0)                     |
|       16-23  OLA_CNT                 (hw2: ini:0)                     |
|       24-31  PREEMPT_CNT             (hw2: ini:0)                     |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ___________ hw2 MAC_PCU registers (moved to RTC WLAN in hw4/hw6) ___________ |
+-----------------------------------------------------------------------------------+
```


### ATH:028200h..02821Ch - MAC_PCU_REG_GNRCTMR_N\[0..7\] ;hw2
### ATH:028220h..02823Ch - MAC_PCU_REG_GNRCTMR_P\[0..7\] ;hw2
### ATH:028240h - MAC_PCU_GENERIC_TIMERS_MODE ;aka MAC_PCU_REG_GNRCTMR_M ;hw2
### ATH:0280D4h - MAC_PCU_SLP1 ;aka MAC_PCU_REG_SLP1 ;hw2
### ATH:0280D8h - MAC_PCU_SLP2 ;aka MAC_PCU_REG_SLP2 ;hw2
### ATH:0280DCh - (outcommented) ;aka MAC_PCU_REG_SLP3 ;hw2 (but outcommented)
### ATH:028260h - MAC_PCU_SLP3 ;aka old name: MAC_PCU_REG_SLP4 (four) ;hw2
This stuff is located in \"WMAC PCU\" at 028xxxh in hw2 only. Later versions have it moved to the \"RTC WLAN\" area (at 004xxxh or 005xxxh), see there for details.

### ATH:028244h (mirror of 0040F4h) - MAC_PCU_REG_SLP32_MODE (ini:10F424h) ;hw2
### ATH:028248h (mirror of 0040F8h) - MAC_PCU_REG_SLP32_WAKE (ini:07EFh) ;hw2
### ATH:02824Ch (mirror of 0040FCh) - MAC_PCU_REG_SLP32_TSF_INC (ini:1E848h) ;hw2
### ATH:028250h (mirror of 004100h) - MAC_PCU_REG_SLPMIB1 ;hw2
### ATH:028254h (mirror of 004104h) - MAC_PCU_REG_SLPMIB2 ;hw2
### ATH:028258h (mirror of 004108h) - MAC_PCU_REG_SLPMIB3 ;hw2
### ATH:028264h (mirror of 00410Ch) - MAC_PCU_REG_SLP5 (ini: 0FFFFFFh) ;hw2
These hw2 registers seem to be just mirrors of other hw2 registers in the RTC area at 004xxxh (see RTC WLAN chapter for details).
In hw4/hw6, the mirrors at 028xxxh are removed (and only the registers at 004xxxh are kept; whereas, in hw6 that part moved to 005xxxh).


```
+-----------------------------------------------------------------------------------+
|      __________________________ outcommented hw2 stuff __________________________ |
+-----------------------------------------------------------------------------------+
```


Below outcommented stuff is found in hw2 source code, maybe it was used in older hw2 revisions (in case there multiple hw2 revisions), or maybe it was used in even older pre-hw2 chips, or maybe it\'s just some experimental stuff that was never implemented in hardware.

### ATH:028140h - outcommented:MAC_PCU_REG_TSFCAL ;Misc ;hw2

```
+-----------------------------------------------------------------------------------+
|       0-3    outcommented:COUNT          (hw2: ini:8)       ;\                    
|       4-7    outcommented:INTERVAL       (hw2: ini:0Ah)     ; hw2 only            |
|       8      outcommented:ENABLE         (hw2: ini:1)       ; (although it's      |
|       9      outcommented:AUTO_CAL       (hw2: ini:1)       ; outcommented even   |
|       10     outcommented:VALUE_WE       (hw2: ini:0)       ; in hw2 source code) |
|       16-31  outcommented:VALUE          (hw2: ini:8000h)   ;/                    |
+-----------------------------------------------------------------------------------+
```


### ATH:02814Ch - outcommented:MAC_PCU_REG_SYNC2 ;Misc ;hw2

```
+-----------------------------------------------------------------------+
|       0-7    outcommented:TIME_OFFSET     (hw2: ini:0)                |
|       8      outcommented:MASTER          (hw2: ini:0)                |
|       9      outcommented:REPLACE         (hw2: ini:0)                |
|       10     outcommented:TUNE            (hw2: ini:0)                |
|       11     outcommented:CLEAR           (hw2: ini:0)                |
|       16-31  outcommented:INTR_THRESH     (hw2: ini:FFFFh)            |
+-----------------------------------------------------------------------+
```


### ATH:028148h - outcommented:MAC_PCU_REG_SYNC1 ;Time (ini:0) ;hw2
### ATH:028158h - outcommented:MAC_PCU_REG_SYNC5 ;RX Time ;hw2
### ATH:028160h - outcommented:MAC_PCU_REG_SYNC7 ;Last Time ;hw2
### ATH:028164h - outcommented:MAC_PCU_REG_SYNC8 ;Updated Time ;hw2

```
+-----------------------------------------------------------------------+
|       0-30   outcommented:TIME                                        |
|       31     -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:028150h - outcommented:MAC_PCU_REG_SYNC3 ;MCAST Addr_L ;hw2
### ATH:028154h - outcommented:MAC_PCU_REG_SYNC4 ;MCAST Addr_U ;hw2

```
+-----------------------------------------------------------------------+
|       0-47   outcommented:MCAST_ADDR      (hw2: ini:0)                |
|       48-63  -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:02815Ch - outcommented:MAC_PCU_REG_SYNC6 ;INC ;hw2

```
+-----------------------------------------------------------------------+
|       0-31   outcommented:INC                                         |
+-----------------------------------------------------------------------+
```




