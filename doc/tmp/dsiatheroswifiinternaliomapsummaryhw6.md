# DSi Atheros Wifi - Internal I/O Map Summary (hw6)


### Overall Summary (hw6.0)

```
+-------------------------------------------------------------------------------+
|       004000h 33Ch    (rtc_soc_reg.h)                                         |
|       xxx240h 1Ch     (rtc_sync_reg.h)    ;-unknown base address              |
|       005000h 164h    (rtc_wlan_reg.h)                                        |
|       006000h 264h    (wlan_coex_reg.h)                                       |
|       007000h 94h     (bt_coex_reg.h)                                         |
|       008000h ..      MIT (what is that...?) (maybe related to MITSUMI mode?) |
|       00C000h 14h     (uart_reg.h)                                            |
|       00D000h ...     DBG_UART (another UART ?)                               |
|       00E000h 38h     (umbox_wlan_reg.h)                                      |
|       010000h 18h     Serial I2C/SPI (si_reg.h)                               |
|       010018h 18h     ADDR_ERROR (si_reg.h)                                   |
|       014000h 170h    (gpio_athr_wlan_reg.h)                                  |
|       018000h 130h    (mbox_wlan_reg.h)                                       |
|       01A000h 2000h   WLAN_HOST_IF_WINDOW (mbox_wlan_reg.h)                   |
|       01C000h 748h    (analog_intf_athr_wlan_reg.h)                           |
|       020000h 130h    (wmac_dma_reg.h)                                        |
|       020800h 24Ch    (wmac_qcu_reg.h)                                        |
|       021000h 7FCh    (wmac_dcu_reg.h)                                        |
|       028000h 1000h   (wmac_pcu_reg.h)                                        |
|       029800h 3F8h    bb_reg.h (1) - bb_chn_reg_map                           |
|       029C00h 24h     bb_reg.h (2) - bb_mrc_reg_map                           |
|       029D00h 1Ch     bb_reg.h (3) - bb_bbb_reg_map                           |
|       029E00h 400h    bb_reg.h (4) - bb_agc_reg_map                           |
|       02A200h 5F8h    bb_reg.h (5) - bb_sm_reg_map                            |
|       02A800h 3F8h    bb_reg.h (6) - bb_chn1_reg_map                          |
|       02AE00h 400h    bb_reg.h (7) - bb_agc1_reg_map                          |
|       02B200h 5F8h    bb_reg.h (8) - bb_sm1_reg_map                           |
|       02C800h 400h    bb_reg.h (9) - bb_chn3_reg_map (DUMMY)                  |
|       02CE00h 184h    bb_reg.h (10) - bb_agc3_reg_map (mostly DUMMY)          |
|       02D200h 600h    bb_reg.h (11) - bb_sm3_reg_map (DUMMY)                  |
|       02D800h 20h     bb_reg.h (12) - mit_local_reg_map, aka bb_mit_reg_map   |
|       02E000h 4x2048  MAC_PCU_BUF (wmac_pcu_reg.h)                            |
|       030000h 1800h   EFUSE (efuse_wlan_reg.h)                                |
|       034000h 1Ch     STEREO 0 (stereo_reg.h)                                 |
|       035000h 58h     (chk_sum_seg_acc_reg.h)                                 |
|       036000h ?       STEREO 1 (maybe same format as STEREO 0 ?)              |
|       038000h 3Ch     (mmac_reg.h)                                            |
|       039000h 0Ch     (fpga_reg.h)                                            |
|       040000h 8       (bridge_intr_reg.h)                                     |
|       040100h 8       (mii_reg.h)                                             |
|       040200h 28h     (mdio_reg.h)                                            |
|       040800h 20h     (bridge_chain_gmac_0_rx_reg.h)                          |
|       040C00h 1Ch     (bridge_chain_gmac_0_tx_reg.h)                          |
|       050000h ..      SVD (what is that...?)                                  |
|       054000h ...     (usb_cast_reg.h)    ;<--- located at 54000h (?)         |
|       054100h ..      usb RX chain 0..5 at 00054100h+(0..5)*100h  (?)         |
|       054700h ..      usb TX chain 0..5 at 00054700h+(0..5)*100h  (?)         |
|       054C00h ...     UART2 (yet another UART ?)                              |
|       054D00h A8h     (rdma_reg.h)                                            |
|       054E00h 50h     (athrI2cSlaveApbCsr.h)                                  |
|       055000h 40h     I2S (mbox_i2s_reg.h)                                    |
|       056000h ..      I2S_1 (maybe same format as above "mbox_i2s_reg.h"?)    |
|       xxxxxxh A00h    (map_rf_reg.h)      ;\unknown base address              
|       xxxxxxh 20h     (odin_reg.h)        ;/                                  |
+-------------------------------------------------------------------------------+
```


### rtc_soc_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       004000h 4       SOC_RESET_CONTROL                               |
|       004004h 4       SOC_TCXO_DETECT                                 |
|       004008h 4       SOC_XTAL_TEST                                   |
|       00400Ch 1x20    PAD0                                            |
|       004020h 4       SOC_CPU_CLOCK                                   |
|       004024h 1x4     PAD1                                            |
|       004028h 4       SOC_CLOCK_CONTROL                               |
|       00402Ch 1x4     PAD2                                            |
|       004030h 4       SOC_WDT_CONTROL             ;\                  
|       004034h 4       SOC_WDT_STATUS              ;                   |
|       004038h 4       SOC_WDT                     ; Watchdog Timer    |
|       00403Ch 4       SOC_WDT_COUNT               ;                   |
|       004040h 4       SOC_WDT_RESET               ;/                  |
|       004044h 4       SOC_INT_STATUS              ;-Interrupt Status  |
|       004048h 4       SOC_LF_TIMER0               ;\                  
|       00404Ch 4       SOC_LF_TIMER_COUNT0         ; Low-Freq Timer    |
|       004050h 4       SOC_LF_TIMER_CONTROL0       ;                   |
|       004054h 4       SOC_LF_TIMER_STATUS0        ;/                  |
|       004058h 4       SOC_LF_TIMER1               ;\                  
|       00405Ch 4       SOC_LF_TIMER_COUNT1         ; Low-Freq Timer    |
|       004060h 4       SOC_LF_TIMER_CONTROL1       ;                   |
|       004064h 4       SOC_LF_TIMER_STATUS1        ;/                  |
|       004068h 4       SOC_LF_TIMER2               ;\                  
|       00406Ch 4       SOC_LF_TIMER_COUNT2         ; Low-Freq Timer    |
|       004070h 4       SOC_LF_TIMER_CONTROL2       ;                   |
|       004074h 4       SOC_LF_TIMER_STATUS2        ;/                  |
|       004078h 4       SOC_LF_TIMER3               ;\                  
|       00407Ch 4       SOC_LF_TIMER_COUNT3         ; Low-Freq Timer    |
|       004080h 4       SOC_LF_TIMER_CONTROL3       ;                   |
|       004084h 4       SOC_LF_TIMER_STATUS3        ;/                  |
|       004088h 4       SOC_HF_TIMER                ;\                  
|       00408Ch 4       SOC_HF_TIMER_COUNT          ; High-Freq Timer   |
|       004090h 4       SOC_HF_LF_COUNT       ;<--  ;                   |
|       004094h 4       SOC_HF_TIMER_CONTROL        ;                   |
|       004098h 4       SOC_HF_TIMER_STATUS         ;/                  |
|       00409Ch 4       SOC_RTC_CONTROL             ;\                  
|       0040A0h 4       SOC_RTC_TIME                ;                   |
|       0040A4h 4       SOC_RTC_DATE                ;                   |
|       0040A8h 4       SOC_RTC_SET_TIME            ; Real-Time Clock   |
|       0040ACh 4       SOC_RTC_SET_DATE            ;                   |
|       0040B0h 4       SOC_RTC_SET_ALARM           ;                   |
|       0040B4h 4       SOC_RTC_CONFIG              ;                   |
|       0040B8h 4       SOC_RTC_ALARM_STATUS        ;/                  |
|       0040BCh 4       SOC_UART_WAKEUP                                 |
|       0040C0h 4       SOC_RESET_CAUSE                                 |
|       0040C4h 4       SOC_SYSTEM_SLEEP                                |
|       0040C8h 4       SOC_SDIO_WRAPPER                                |
|       0040CCh 4       SOC_INT_STATUS1                                 |
|       0040D0h 1x4     PAD3                                            |
|       0040D4h 4       SOC_LPO_CAL_TIME                    ;\          
|       0040D8h 4       SOC_LPO_INIT_DIVIDEND_INT           ;           |
|       0040DCh 4       SOC_LPO_INIT_DIVIDEND_FRACTION      ; LPO       |
|       0040E0h 4       SOC_LPO_CAL                         ;           |
|       0040E4h 4       SOC_LPO_CAL_TEST_CONTROL            ;           |
|       0040E8h 4       SOC_LPO_CAL_TEST_STATUS             ;/          |
|       0040ECh 4       LEGACY_SOC_CHIP_ID                  ;\Chip ID   
|       0040F0h 4       SOC_CHIP_ID                         ;/          |
|       0040F4h 1x24    PAD4                                            |
|       00410Ch 4       SOC_POWER_REG                                   |
|       004110h 4       SOC_CORE_CLK_CTRL                               |
|       004114h 4       SOC_GPIO_WAKEUP_CONTROL                         |
|       004118h 1x252   PAD5                                            |
|       004214h 4       SLEEP_RETENTION                                 |
|       004218h 1x108   PAD6                                            |
|       004284h 4       LP_PERF_COUNTER                     ;\          
|       004288h 4       LP_PERF_LIGHT_SLEEP                 ; Perf      |
|       00428Ch 4       LP_PERF_DEEP_SLEEP                  ;           |
|       004290h 4       LP_PERF_ON                          ;/          |
|       004294h 1x20    PAD7                                            |
|       0042A8h 4       CHIP_MODE                                       |
|       0042ACh 4       CLK_REQ_FALL_EDGE                               |
|       0042B0h 4       OTP                                 ;\OTP       
|       0042B4h 4       OTP_STATUS                          ;/          |
|       0042B8h 4       PMU                                             |
|       0042BCh 4       PMU_CONFIG                                      |
|       0042C0h 4       PMU_PAREG                                       |
|       0042C4h 4       PMU_BYPASS                                      |
|       0042C8h 1x20    PAD8                                            |
|       0042DCh 4       THERM_CTRL1                         ;\          
|       0042E0h 4       THERM_CTRL2                         ; Therm     |
|       0042E4h 4       THERM_CTRL3                         ;/          |
|       0042E8h 4       LISTEN_MODE1                                    |
|       0042ECh 4       LISTEN_MODE2                                    |
|       0042F0h 4       AUDIO_PLL_CONFIG                                |
|       0042F4h 4       AUDIO_PLL_MODULATION                            |
|       0042F8h 4       AUDIO_PLL_MOD_STEP                              |
|       0042FCh 4       CURRENT_AUDIO_PLL_MODULATION                    |
|       004300h 4       ETH_PLL_CONFIG                                  |
|       004304h 4       CPU_PLL_CONFIG                                  |
|       004308h 4       BB_PLL_CONFIG                                   |
|       00430Ch 4       ETH_XMII                                        |
|       004310h 4       USB_PHY_CONFIG                                  |
|       004314h 4       MITSUMI_INT_CONTROL_REG                         |
|       004318h 4       MITSUMI_INT_STATUS_REG                          |
|       00431Ch 4       CURRENT_WORKING_MODE                            |
|       004320h 4       RTC_SLEEP_COUNT                                 |
|       004324h 4       MIT2_VAP                                        |
|       004328h 4       SECOND_HOST_INFT                                |
|       00432Ch 4       SDIO_HOST                                       |
|       004330h 4       ENTERPRISE_CONFIG                               |
|       004334h 4       RTC_DEBUG_BUS                                   |
|       004338h 4       RTC_EXT_CLK_BUF                                 |
+-----------------------------------------------------------------------+
```


### rtc_sync_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       000000h 1x576   PAD__0                                          |
|       000240h 4       RTC_SYNC_RESET                                  |
|       000244h 4       RTC_SYNC_STATUS                                 |
|       000248h 4       RTC_SYNC_DERIVED                                |
|       00024Ch 4       RTC_SYNC_FORCE_WAKE                             |
|       000250h 4       RTC_SYNC_INTR_CAUSE                             |
|       000254h 4       RTC_SYNC_INTR_ENABLE                            |
|       000258h 4       RTC_SYNC_INTR_MASK                              |
|       00025Ch ..      -                                               |
+-----------------------------------------------------------------------+
```


### rtc_wlan_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       005000h 4       WLAN_RESET_CONTROL                              |
|       005004h 4       WLAN_XTAL_CONTROL                               |
|       005008h 4       WLAN_REG_CONTROL0                               |
|       00500Ch 4       WLAN_REG_CONTROL1                               |
|       005010h 4       WLAN_QUADRATURE                                 |
|       005014h 4       WLAN_PLL_CONTROL                                |
|       005018h 4       WLAN_PLL_SETTLE                                 |
|       00501Ch 4       WLAN_XTAL_SETTLE                                |
|       005020h 4       WLAN_CLOCK_OUT                                  |
|       005024h 4       WLAN_BIAS_OVERRIDE                              |
|       005028h 4       WLAN_RESET_CAUSE                                |
|       00502Ch 4       WLAN_SYSTEM_SLEEP                               |
|       005030h 4       WLAN_MAC_SLEEP_CONTROL                          |
|       005034h 4       WLAN_KEEP_AWAKE                                 |
|       005038h 4       WLAN_DERIVED_RTC_CLK                            |
|       00503Ch 4       MAC_PCU_SLP32_MODE                              |
|       005040h 4       MAC_PCU_SLP32_WAKE                              |
|       005044h 4       MAC_PCU_SLP32_INC                               |
|       005048h 4       MAC_PCU_SLP_MIB1                                |
|       00504Ch 4       MAC_PCU_SLP_MIB2                                |
|       005050h 4       MAC_PCU_SLP_MIB3                                |
|       005054h 4       MAC_PCU_TSF_L32                                 |
|       005058h 4       MAC_PCU_TSF_U32                                 |
|       00505Ch 4       MAC_PCU_WBTIMER_0                               |
|       005060h 4       MAC_PCU_WBTIMER_1                               |
|       005064h 4x16    MAC_PCU_GENERIC_TIMERS[0..15]                   |
|       0050A4h 1x24    PAD__0                                          |
|       0050BCh 4       MAC_PCU_GENERIC_TIMERS_MODE                     |
|       0050C0h 4       MAC_PCU_SLP1                                    |
|       0050C4h 4       MAC_PCU_SLP2                                    |
|       0050C8h 4       MAC_PCU_SLP3                                    |
|       0050CCh 4       MAC_PCU_SLP4                                    |
|       0050D0h 4       MAC_PCU_RESET_TSF                               |
|       0050D4h 4       MAC_PCU_TSF2_L32                                |
|       0050D8h 4       MAC_PCU_TSF2_U32                                |
|       0050DCh 4x16    MAC_PCU_GENERIC_TIMERS2[0..15]                  |
|       00511Ch 1x24    PAD__1                                          |
|       005134h 4       MAC_PCU_GENERIC_TIMERS_MODE2                    |
|       005138h 1x12    PAD__2                                          |
|       005144h 4       MAC_PCU_TSF_THRESHOLD                           |
|       005148h 4       WLAN_HT                                         |
|       00514Ch 1x4     PAD__3                                          |
|       005150h 4       MAC_PCU_GENERIC_TIMERS_TSF_SEL                  |
|       005154h 4       MAC_PCU_BMISS_TIMEOUT                           |
|       005158h 4       MAC_PCU_BMISS2_TIMEOUT                          |
|       00515Ch 4       RTC_AXI_AHB_BRIDGE                              |
|       005160h 4       UNIFIED_MAC_REVID                               |
|       005164h ..      -                                               |
+-----------------------------------------------------------------------+
```


### wlan_coex_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       006000h 4       MCI_COMMAND0                                    |
|       006004h 4       MCI_COMMAND1                                    |
|       006008h 4       MCI_COMMAND2                                    |
|       00600Ch 4       MCI_RX_CTRL                                     |
|       006010h 4       MCI_TX_CTRL                                     |
|       006014h 4       MCI_MSG_ATTRIBUTES_TABLE                        |
|       006018h 4       MCI_SCHD_TABLE_0                                |
|       00601Ch 4       MCI_SCHD_TABLE_1                                |
|       006020h 4       MCI_GPM_0                                       |
|       006024h 4       MCI_GPM_1                                       |
|       006028h 4       MCI_INTERRUPT_RAW                               |
|       00602Ch 4       MCI_INTERRUPT_EN                                |
|       006030h 4       MCI_REMOTE_CPU_INT                              |
|       006034h 4       MCI_REMOTE_CPU_INT_EN                           |
|       006038h 4       MCI_INTERRUPT_RX_MSG_RAW                        |
|       00603Ch 4       MCI_INTERRUPT_RX_MSG_EN                         |
|       006040h 4       MCI_CPU_INT                                     |
|       006044h 4       MCI_RX_STATUS                                   |
|       006048h 4       MCI_CONT_STATUS                                 |
|       00604Ch 4       MCI_BT_PRI0                                     |
|       006050h 4       MCI_BT_PRI1                                     |
|       006054h 4       MCI_BT_PRI2                                     |
|       006058h 4       MCI_BT_PRI3                                     |
|       00605Ch 4       MCI_BT_PRI                                      |
|       006060h 4       MCI_WL_FREQ0                                    |
|       006064h 4       MCI_WL_FREQ1                                    |
|       006068h 4       MCI_WL_FREQ2                                    |
|       00606Ch 4       MCI_GAIN                                        |
|       006070h 4       MCI_WBTIMER1                                    |
|       006074h 4       MCI_WBTIMER2                                    |
|       006078h 4       MCI_WBTIMER3                                    |
|       00607Ch 4       MCI_WBTIMER4                                    |
|       006080h 4       MCI_MAXGAIN                                     |
|       006084h 1x40    PAD__0                                          |
|       0060ACh 4       BTCOEX_CTRL                                     |
|       0060B0h 1x156   PAD__1                                          |
|       00614Ch 4       BTCOEX_CTRL2                                    |
|       006150h 1x260   PAD__2                                          |
|       006254h 4       BTCOEX_DBG                                      |
|       006258h 4       MCI_LAST_HW_MSG_HDR                             |
|       00625Ch 4       MCI_LAST_HW_MSG_BDY                             |
|       006260h 4       MCI_MAXGAIN_RST                                 |
|       006264h ..      -                                               |
+-----------------------------------------------------------------------+
```


### bt_coex_reg.h (hw6.0)

```
+----------------------------------------------------------------------------------+
|       007000h 4       BTCOEXCTRL                      ;\                         
|       007004h 4       WBSYNC_PRIORITY1                ;                          |
|       007008h 4       WBSYNC_PRIORITY2                ;                          |
|       00700Ch 4       WBSYNC_PRIORITY3                ;                          |
|       007010h 4       BTCOEX0  ;SYNC_DUR              ;                          |
|       007014h 4       BTCOEX1  ;CLK_THRES             ;                          |
|       007018h 4       BTCOEX2  ;FRAME_THRES           ;                          |
|       00701Ch 4       BTCOEX3  ;CLK_CNT               ; moved from 004218h (hw4) |
|       007020h 4       BTCOEX4  ;FRAME_CNT             ; to 007000h (hw6)         |
|       007024h 4       BTCOEX5  ;IDLE_CNT              ;                          |
|       007028h 4       BTCOEX6  ;IDLE_RESET_LVL_BITMAP ;                          |
|       00702Ch 4       LOCK                            ;                          |
|       007030h 4       NOLOCK_PRIORITY                 ;                          |
|       007034h 4       WBSYNC                          ;                          |
|       007038h 4       WBSYNC1                         ;                          |
|       00703Ch 4       WBSYNC2                         ;                          |
|       007040h 4       WBSYNC3                         ;                          |
|       007044h 4       WB_TIMER_TARGET                 ;                          |
|       007048h 4       WB_TIMER_SLOP                   ;                          |
|       00704Ch 4       BTCOEX_INT_EN                   ;                          |
|       007050h 4       BTCOEX_INT_STAT                 ;                          |
|       007054h 4       BTPRIORITY_INT_EN               ;                          |
|       007058h 4       BTPRIORITY_INT_STAT             ;                          |
|       00705Ch 4       BTPRIORITY_STOMP_INT_EN         ;                          |
|       007060h 4       BTPRIORITY_STOMP_INT_STAT       ;/                         |
|       007064h 4       ST_64_BIT                       ;\                         
|       007068h 4       MESSAGE_WR                      ; moved from 004294h (hw4) |
|       00706Ch 4       MESSAGE_WR_P                    ; to 007064h (hw6)         |
|       007070h 4       MESSAGE_RD                      ;                          |
|       007074h 4       MESSAGE_RD_P                    ;/                         |
|       007078h 4       BTPRIORITY_INT                  ;\                         
|       00707Ch 4       SCO_PARAMS                      ;                          |
|       007080h 4       SCO_PRIORITY                    ;                          |
|       007084h 4       SCO_SYNC                        ; new, hw6.0 only          |
|       007088h 4       BTCOEX_RAW_STAT                 ;                          |
|       00708Ch 4       BTPRIORITY_RAW_STAT             ;                          |
|       007090h 4       BTPRIORITY_STOMP_RAW_STAT       ;/                         |
+----------------------------------------------------------------------------------+
```


### uart_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       00C000h 4       UART_DATA                                       |
|       00C004h 4       UART_CONTROL                                    |
|       00C008h 4       UART_CLKDIV                                     |
|       00C00Ch 4       UART_INT                                        |
|       00C010h 4       UART_INT_EN                                     |
|       00C014h ..      -                                               |
|       00D000h ..      ??                                              |
+-----------------------------------------------------------------------+
```


### umbox_wlan_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       00E000h 4x2     UMBOX_FIFO[0..1]                                |
|       00E008h 4       UMBOX_FIFO_STATUS                               |
|       00E00Ch 4       UMBOX_DMA_POLICY                                |
|       00E010h 4       UMBOX0_DMA_RX_DESCRIPTOR_BASE                   |
|       00E014h 4       UMBOX0_DMA_RX_CONTROL                           |
|       00E018h 4       UMBOX0_DMA_TX_DESCRIPTOR_BASE                   |
|       00E01Ch 4       UMBOX0_DMA_TX_CONTROL                           |
|       00E020h 4       UMBOX_FIFO_TIMEOUT                              |
|       00E024h 4       UMBOX_INT_STATUS                                |
|       00E028h 4       UMBOX_INT_ENABLE                                |
|       00E02Ch 4       UMBOX_DEBUG                                     |
|       00E030h 4       UMBOX_FIFO_RESET                                |
|       00E034h 4       UMBOX_HCI_FRAMER                                |
+-----------------------------------------------------------------------+
```


### Serial I2C/SPI (si_reg.h) (hw6.0)

```
+-----------------------------------------------------------------------+
|       010000h 4       SI_CONFIG                                       |
|       010004h 4       SI_CS                                           |
|       010008h 4       SI_TX_DATA0                                     |
|       01000Ch 4       SI_TX_DATA1                                     |
|       010010h 4       SI_RX_DATA0                                     |
|       010014h 4       SI_RX_DATA1                                     |
+-----------------------------------------------------------------------+
```


### ADDR_ERROR (si_reg.h) (hw6.0)

```
+-------------------------------------------------------------------------------+
|       010018h 4       WLAN_APB_ADDR_ERROR_CONTROL ;\                          
|       01001Ch 4       WLAN_APB_ADDR_ERROR_STATUS  ; ADDR_ERROR                |
|       010020h 4       WLAN_AHB_ADDR_ERROR_CONTROL ; (located at 8xxxh in hw4) |
|       010024h 4       WLAN_AHB_ADDR_ERROR_STATUS  ;/                          |
|       010028h 4       WLAN_AHB_CONFIG                                         |
|       01002Ch 4       WLAN_MEMORY_MAP                                         |
+-------------------------------------------------------------------------------+
```


### gpio_athr_wlan_reg.h (hw6.0)

```
+-----------------------------------------------------------------------------------+
|       014000h 4       WLAN_GPIO_OUT_LOW        ;\                                 
|       014004h 4       WLAN_GPIO_OUT_W1TS_LOW   ;                                  |
|       014008h 4       WLAN_GPIO_OUT_W1TC_LOW   ; GPIO Output Data                 |
|       01400Ch 4       WLAN_GPIO_OUT_HIGH       ; (direct, and Write-1-To-Set/Clr) |
|       014010h 4       WLAN_GPIO_OUT_W1TS_HIGH  ;                                  |
|       014014h 4       WLAN_GPIO_OUT_W1TC_HIGH  ;/                                 |
|       014018h 4       WLAN_GPIO_ENABLE_LOW                ;\                      
|       01401Ch 4       WLAN_GPIO_ENABLE_W1TS_LOW           ;                       |
|       014020h 4       WLAN_GPIO_ENABLE_W1TC_LOW           ; GPIO Output Enable    |
|       014024h 4       WLAN_GPIO_ENABLE_HIGH               ; (direct, and Set/Clr) |
|       014028h 4       WLAN_GPIO_ENABLE_W1TS_HIGH          ;                       |
|       01402Ch 4       WLAN_GPIO_ENABLE_W1TC_HIGH          ;/                      |
|       014030h 4       WLAN_GPIO_IN_LOW                       ;\                   
|       014034h 4       WLAN_GPIO_STATUS_LOW                ;\ ; GPIO Input         
|       014038h 4       WLAN_GPIO_IN_HIGH                   ;  ;/                   |
|       01403Ch 4       WLAN_GPIO_STATUS_HIGH               ;                       |
|       014040h 4       WLAN_GPIO_STATUS_W1TS_LOW           ; GPIO Interrupt Status |
|       014044h 4       WLAN_GPIO_STATUS_W1TC_LOW           ; (direct, and Set/Clr) |
|       014048h 4       WLAN_GPIO_STATUS_W1TS_HIGH          ;                       |
|       01404Ch 4       WLAN_GPIO_STATUS_W1TC_HIGH          ;/                      |
|       014050h 4       WLAN_GPIO_PIN0   ;GPIO0 or SDIO_CMD                         |
|       014054h 4       WLAN_GPIO_PIN1   ;GPIO1 or SDIO_D3                          |
|       014058h 4       WLAN_GPIO_PIN2   ;GPIO2 or SDIO_D2                          |
|       01405Ch 4       WLAN_GPIO_PIN3   ;GPIO3 or SDIO_D1                          |
|       014060h 4       WLAN_GPIO_PIN4   ;GPIO4 or SDIO_D0                          |
|       014064h 4       WLAN_GPIO_PIN5   ;GPIO5 or SDIO_CLK                         |
|       014068h 4       WLAN_GPIO_PIN6   ;GPIO6                                     |
|       01406Ch 4       WLAN_GPIO_PIN7   ;GPIO7                                     |
|       014070h 4       WLAN_GPIO_PIN8   ;...                                       |
|       014074h 4       WLAN_GPIO_PIN9   ;..                                        |
|       014078h 4       WLAN_GPIO_PIN10                                             |
|       01407Ch 4       WLAN_GPIO_PIN11                                             |
|       014080h 4       WLAN_GPIO_PIN12                                             |
|       014084h 4       WLAN_GPIO_PIN13                                             |
|       014088h 4       WLAN_GPIO_PIN14                                             |
|       01408Ch 4       WLAN_GPIO_PIN15                                             |
|       014090h 4       WLAN_GPIO_PIN16                                             |
|       014094h 4       WLAN_GPIO_PIN17                                             |
|       014098h 4       WLAN_GPIO_PIN18                                             |
|       01409Ch 4       WLAN_GPIO_PIN19                                             |
|       0140A0h 4       WLAN_GPIO_PIN20                                             |
|       0140A4h 4       WLAN_GPIO_PIN21                                             |
|       0140A8h 4       WLAN_GPIO_PIN22                                             |
|       0140ACh 4       WLAN_GPIO_PIN23                                             |
|       0140B0h 4       WLAN_GPIO_PIN24                                             |
|       0140B4h 4       WLAN_GPIO_PIN25                                             |
|       0140B8h 4       WLAN_GPIO_PIN26                                             |
|       0140BCh 4       WLAN_GPIO_PIN27                                             |
|       0140C0h 4       WLAN_GPIO_PIN28                                             |
|       0140C4h 4       WLAN_GPIO_PIN29                                             |
|       0140C8h 4       WLAN_GPIO_PIN30                                             |
|       0140CCh 4       WLAN_GPIO_PIN31                                             |
|       0140D0h 4       WLAN_GPIO_PIN32                                             |
|       0140D4h 4       WLAN_GPIO_PIN33                                             |
|       0140D8h 4       WLAN_GPIO_PIN34                                             |
|       0140DCh 4       WLAN_GPIO_PIN35                                             |
|       0140E0h 4       WLAN_GPIO_PIN36                                             |
|       0140E4h 4       WLAN_GPIO_PIN37                                             |
|       0140E8h 4       WLAN_GPIO_PIN38                                             |
|       0140ECh 4       WLAN_GPIO_PIN39                                             |
|       0140F0h 4       WLAN_GPIO_PIN40                                             |
|       0140F4h 4       WLAN_GPIO_PIN41                                             |
|       0140F8h 4       WLAN_GPIO_PIN42                                             |
|       0140FCh 4       WLAN_GPIO_PIN43                                             |
|       014100h 4       WLAN_GPIO_PIN44                                             |
|       014104h 4       WLAN_GPIO_PIN45                                             |
|       014108h 4       WLAN_GPIO_PIN46                                             |
|       01410Ch 4       WLAN_GPIO_PIN47                                             |
|       014110h 4       WLAN_GPIO_PIN48                                             |
|       014114h 4       WLAN_GPIO_PIN49                                             |
|       014118h 4       WLAN_GPIO_PIN50                                             |
|       01411Ch 4       WLAN_GPIO_PIN51                                             |
|       014120h 4       WLAN_GPIO_PIN52                                             |
|       014124h 4       WLAN_GPIO_PIN53                                             |
|       014128h 4       WLAN_GPIO_PIN54                                             |
|       01412Ch 4       WLAN_GPIO_PIN55                                             |
|       014130h 4       WLAN_GPIO_PIN56                                             |
|       014134h 4       SDIO                                                        |
|       014138h 4       WL_SOC_APB                                                  |
|       01413Ch 4       WLAN_SIGMA_DELTA                                            |
|       014140h 4       WL_BOOTSTRAP                                                |
|       014144h 4       CORE_BOOTSTRAP_LOW                                          |
|       014148h 4       CORE_BOOTSTRAP_HIGH                                         |
|       01414Ch 4       WLAN_DEBUG_CONTROL                                          |
|       014150h 4       WLAN_DEBUG_INPUT_SEL                                        |
|       014154h 4       WLAN_DEBUG_OUT                                              |
|       014158h 4       WLAN_RESET_TUPLE_STATUS                                     |
|       01415Ch 4       ANTENNA_CONTROL                                             |
|       014160h 4       SDIO2                                                       |
|       014164h 4       SDHC                                                        |
|       014168h 4       AMBA_DEBUG_BUS                                              |
|       01416Ch 4       CPU_MBIST                                                   |
+-----------------------------------------------------------------------------------+
```


### MBOX Registers (mbox_wlan_reg.h) (hw6.0)

```
+-----------------------------------------------------------------------------+
|       018000h 4x4     WLAN_MBOX_FIFO[0..3]                                  |
|       018010h 4       WLAN_MBOX_FIFO_STATUS                                 |
|       018014h 4       WLAN_MBOX_DMA_POLICY                                  |
|       018018h 4       WLAN_MBOX0_DMA_RX_DESCRIPTOR_BASE   ;\                
|       01801Ch 4       WLAN_MBOX0_DMA_RX_CONTROL           ; MBOX 0          |
|       018020h 4       WLAN_MBOX0_DMA_TX_DESCRIPTOR_BASE   ;                 |
|       018024h 4       WLAN_MBOX0_DMA_TX_CONTROL           ;/                |
|       018028h 4       WLAN_MBOX1_DMA_RX_DESCRIPTOR_BASE   ;\                
|       01802Ch 4       WLAN_MBOX1_DMA_RX_CONTROL           ; MBOX 1          |
|       018030h 4       WLAN_MBOX1_DMA_TX_DESCRIPTOR_BASE   ;                 |
|       018034h 4       WLAN_MBOX1_DMA_TX_CONTROL           ;/                |
|       018038h 4       WLAN_MBOX2_DMA_RX_DESCRIPTOR_BASE   ;\                
|       01803Ch 4       WLAN_MBOX2_DMA_RX_CONTROL           ; MBOX 2          |
|       018040h 4       WLAN_MBOX2_DMA_TX_DESCRIPTOR_BASE   ;                 |
|       018044h 4       WLAN_MBOX2_DMA_TX_CONTROL           ;/                |
|       018048h 4       WLAN_MBOX3_DMA_RX_DESCRIPTOR_BASE   ;\                
|       01804Ch 4       WLAN_MBOX3_DMA_RX_CONTROL           ; MBOX 3          |
|       018050h 4       WLAN_MBOX3_DMA_TX_DESCRIPTOR_BASE   ;                 |
|       018054h 4       WLAN_MBOX3_DMA_TX_CONTROL           ;/                |
|       018058h 4       WLAN_MBOX_INT_STATUS                ;\Interrupt       
|       01805Ch 4       WLAN_MBOX_INT_ENABLE                ;/                |
|       018060h 4       WLAN_INT_HOST                                         |
|       018064h 1x28    PAD0                                                  |
|       018080h 4x8     WLAN_LOCAL_COUNT[0..7]                                |
|       0180A0h 4x8     WLAN_COUNT_INC[0..7]                                  |
|       0180C0h 4x8     WLAN_LOCAL_SCRATCH[0..7]                              |
|       0180E0h 4       WLAN_USE_LOCAL_BUS                                    |
|       0180E4h 4       WLAN_SDIO_CONFIG                                      |
|       0180E8h 4       WLAN_MBOX_DEBUG                                       |
|       0180ECh 4       WLAN_MBOX_FIFO_RESET                                  |
|       0180F0h 4x4     WLAN_MBOX_TXFIFO_POP[0..3]                            |
|       018100h 4x4     WLAN_MBOX_RXFIFO_POP[0..3]                            |
|       018110h 4       WLAN_SDIO_DEBUG                                       |
|       018114h 4       WLAN_GMBOX0_DMA_RX_DESCRIPTOR_BASE  ;\                
|       018118h 4       WLAN_GMBOX0_DMA_RX_CONTROL          ;                 |
|       01811Ch 4       WLAN_GMBOX0_DMA_TX_DESCRIPTOR_BASE  ; hw4.0 and hw6.0 |
|       018120h 4       WLAN_GMBOX0_DMA_TX_CONTROL          ;                 |
|       018124h 4       WLAN_GMBOX_INT_STATUS               ;                 |
|       018128h 4       WLAN_GMBOX_INT_ENABLE               ;/                |
|       01812Ch 4       STE_MODE                            ;<-- hw6.0 only   |
|       018130h 1x7888  PAD1                                                  |
|       01A000h 4x2048  WLAN_HOST_IF_WINDOW[0..2047]                          |
+-----------------------------------------------------------------------------+
```


### analog_intf_athr_wlan_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       01C000h 4       RXRF_BIAS1                                      |
|       01C004h 4       RXRF_BIAS2                                      |
|       01C008h 4       RXRF_GAINSTAGES                                 |
|       01C00Ch 4       RXRF_AGC                                        |
|       01C010h 1x48    PAD__0                                          |
|       01C040h 4       TXRF1                                           |
|       01C044h 4       TXRF2                                           |
|       01C048h 4       TXRF3                                           |
|       01C04Ch 4       TXRF4                                           |
|       01C050h 4       TXRF5                                           |
|       01C054h 4       TXRF6                                           |
|       01C058h 4       TXRF7                                           |
|       01C05Ch 4       TXRF8                                           |
|       01C060h 4       TXRF9                                           |
|       01C064h 4       TXRF10                                          |
|       01C068h 4       TXRF11                                          |
|       01C06Ch 4       TXRF12                                          |
|       01C070h 1x16    PAD__1                                          |
|       01C080h 4       SYNTH1                                          |
|       01C084h 4       SYNTH2                                          |
|       01C088h 4       SYNTH3                                          |
|       01C08Ch 4       SYNTH4                                          |
|       01C090h 4       SYNTH5                                          |
|       01C094h 4       SYNTH6                                          |
|       01C098h 4       SYNTH7                                          |
|       01C09Ch 4       SYNTH8                                          |
|       01C0A0h 4       SYNTH9                                          |
|       01C0A4h 4       SYNTH10                                         |
|       01C0A8h 4       SYNTH11                                         |
|       01C0ACh 4       SYNTH12                                         |
|       01C0B0h 4       SYNTH13                                         |
|       01C0B4h 4       SYNTH14                                         |
|       01C0B8h 1x8     PAD__2                                          |
|       01C0C0h 4       BIAS1                                           |
|       01C0C4h 4       BIAS2                                           |
|       01C0C8h 4       BIAS3                                           |
|       01C0CCh 4       BIAS4                                           |
|       01C0D0h 1x48    PAD__3                                          |
|       01C100h 4       RXTX1                                           |
|       01C104h 4       RXTX2                                           |
|       01C108h 4       RXTX3                                           |
|       01C10Ch 1x52    PAD__4                                          |
|       01C140h 4       BB1                                             |
|       01C144h 4       BB2                                             |
|       01C148h 4       BB3                                             |
|       01C14Ch 1x308   PAD__5                                          |
|       01C280h 4       PLLCLKMODA                                      |
|       01C284h 4       PLLCLKMODA2                                     |
|       01C288h 4       TOP                                             |
|       01C28Ch 4       THERM                                           |
|       01C290h 4       XTAL                                            |
|       01C294h 1x236   PAD__6                                          |
|       01C380h 4       RBIST_CNTRL                                     |
|       01C384h 4       TX_DC_OFFSET                                    |
|       01C388h 4       TX_TONEGEN0                                     |
|       01C38Ch 4       TX_TONEGEN1                                     |
|       01C390h 4       TX_LFTONEGEN0                                   |
|       01C394h 4       TX_LINEAR_RAMP_I                                |
|       01C398h 4       TX_LINEAR_RAMP_Q                                |
|       01C39Ch 4       TX_PRBS_MAG                                     |
|       01C3A0h 4       TX_PRBS_SEED_I                                  |
|       01C3A4h 4       TX_PRBS_SEED_Q                                  |
|       01C3A8h 4       CMAC_DC_CANCEL                                  |
|       01C3ACh 4       CMAC_DC_OFFSET                                  |
|       01C3B0h 4       CMAC_CORR                                       |
|       01C3B4h 4       CMAC_POWER                                      |
|       01C3B8h 4       CMAC_CROSS_CORR                                 |
|       01C3BCh 4       CMAC_I2Q2                                       |
|       01C3C0h 4       CMAC_POWER_HPF                                  |
|       01C3C4h 4       RXDAC_SET1                                      |
|       01C3C8h 4       RXDAC_SET2                                      |
|       01C3CCh 4       RXDAC_LONG_SHIFT                                |
|       01C3D0h 4       CMAC_RESULTS_I                                  |
|       01C3D4h 4       CMAC_RESULTS_Q                                  |
|       01C3D8h 1x872   PAD__7                                          |
|       01C740h 4       PMU1                                            |
|       01C744h 4       PMU2                                            |
+-----------------------------------------------------------------------+
```


### wmac_dma_reg.h (hw6.0)

```
+-------------------------------------------------------------------------------------+
|       020000h 1x8     PAD__0                                                        |
|       020008h 4       MAC_DMA_CR                                                    |
|       020004h 1x4     PAD__1                                                        |
|       02000Ch 1x4     PAD__1                                                        |
|       020014h 4       MAC_DMA_CFG                                                   |
|       020018h 4       MAC_DMA_RXBUFPTR_THRESH                                       |
|       02001Ch 4       MAC_DMA_TXDPPTR_THRESH                                        |
|       020020h 4       MAC_DMA_MIRT                                                  |
|       020024h 4       MAC_DMA_GLOBAL_IER                                            |
|       020028h 4       MAC_DMA_TIMT_0                                                |
|       02002Ch 4       MAC_DMA_RIMT                                                  |
|       020030h 4       MAC_DMA_TXCFG                                                 |
|       020034h 4       MAC_DMA_RXCFG                                                 |
|       020038h 4       MAC_DMA_RXJLA                                                 |
|       02003Ch 1x4     PAD__2                                                        |
|       020040h 4       MAC_DMA_MIBC                                                  |
|       020044h 4       MAC_DMA_TOPS                                                  |
|       020048h 4       MAC_DMA_RXNPTO                                                |
|       02004Ch 4       MAC_DMA_TXNPTO                                                |
|       020050h 4       MAC_DMA_RPGTO                                                 |
|       020054h 1x4     PAD__3                                                        |
|       020058h 4       MAC_DMA_MACMISC                                               |
|       02005Ch 4       MAC_DMA_INTER                                                 |
|       020060h 4       MAC_DMA_DATABUF                                               |
|       020064h 4       MAC_DMA_GTT                                                   |
|       020068h 4       MAC_DMA_GTTM                                                  |
|       02006Ch 4       MAC_DMA_CST                                                   |
|       020070h 4       MAC_DMA_RXDP_SIZE                                             |
|       020074h 4       MAC_DMA_RX_QUEUE_HP_RXDP                                      |
|       020078h 4       MAC_DMA_RX_QUEUE_LP_RXDP                                      |
|       02007Ch 1x4     PAD__4                                                        |
|       020080h 4       MAC_DMA_ISR_P  - Primary Interrupt Status Register         ;\ 
|       020084h 4       MAC_DMA_ISR_S0 - Secondary Interrupt 0 Status TX OK/DESC   ;  |
|       020088h 4       MAC_DMA_ISR_S1 - Secondary Interrupt 1 Status TX ERR/EOL   ;  |
|       02008Ch 4       MAC_DMA_ISR_S2 - Secondary Interrupt 2 Status TX URN/MISC  ;  |
|       020090h 4       MAC_DMA_ISR_S3 - Secondary Interrupt 3 Status QCBR OVF/URN ;  |
|       020094h 4       MAC_DMA_ISR_S4 - Secondary Interrupt 4 Status QTRIG        ;  |
|       020098h 4       MAC_DMA_ISR_S5 - Secondary Interrupt 5 Status TIMERS       ;  |
|       02009Ch 4       MAC_DMA_ISR_S6 - Secondary Interrupt 6 Status UNKNOWN?     ;/ |
|       0200A0h 4       MAC_DMA_IMR_P  - Primary Interrupt Mask Register           ;\ 
|       0200A4h 4       MAC_DMA_IMR_S0 - Secondary Interrupt 0 Mask TX OK/DESC     ;  |
|       0200A8h 4       MAC_DMA_IMR_S1 - Secondary Interrupt 1 Mask TX ERR/EOL     ;  |
|       0200ACh 4       MAC_DMA_IMR_S2 - Secondary Interrupt 2 Mask TX URN/MISC    ;  |
|       0200B0h 4       MAC_DMA_IMR_S3 - Secondary Interrupt 3 Mask QCBR OVF/URN   ;  |
|       0200B4h 4       MAC_DMA_IMR_S4 - Secondary Interrupt 4 Mask QTRIG          ;  |
|       0200B8h 4       MAC_DMA_IMR_S5 - Secondary Interrupt 5 Mask TIMERS         ;  |
|       0200BCh 4       MAC_DMA_IMR_S6 - Secondary Interrupt 6 Mask UNKNOWN?       ;/ |
|       0200C0h 4       MAC_DMA_ISR_P_RAC - Primary Interrupt Read-and-Clear       ;\ 
|       0200C4h 4       MAC_DMA_ISR_S0_S  - Secondary 0 Read-and-Clr TX OK/DESC    ;  |
|       0200C8h 4       MAC_DMA_ISR_S1_S  - Secondary 1 Read-and-Clr TX ERR/EOL    ;  |
|       0200CCh 4       MAC_DMA_ISR_S6_S  - Secondary 6? Read-and-Clr UNKNOWN? <-- ;  |
|       0200D0h 4       MAC_DMA_ISR_S2_S  - Secondary 2? Read-and-Clr TX URN/MISC  ;  |
|       0200D4h 4       MAC_DMA_ISR_S3_S  - Secondary 3? Read-and-Clr QCBR OVF/URN ;  |
|       0200D8h 4       MAC_DMA_ISR_S4_S  - Secondary 4? Read-and-Clr QTRIG        ;  |
|       0200DCh 4       MAC_DMA_ISR_S5_S  - Secondary 5? Read-and-Clr TIMERS       ;/ |
|       0200E0h 4       MAC_DMA_DMADBG_0                                              |
|       0200E4h 4       MAC_DMA_DMADBG_1                                              |
|       0200E8h 4       MAC_DMA_DMADBG_2                                              |
|       0200ECh 4       MAC_DMA_DMADBG_3                                              |
|       0200F0h 4       MAC_DMA_DMADBG_4                                              |
|       0200F4h 4       MAC_DMA_DMADBG_5                                              |
|       0200F8h 4       MAC_DMA_DMADBG_6                                              |
|       0200FCh 4       MAC_DMA_DMADBG_7                                              |
|       020100h 4       MAC_DMA_QCU_TXDP_REMAINING_QCU_7_0                            |
|       020104h 4       MAC_DMA_QCU_TXDP_REMAINING_QCU_9_8                            |
|       020108h 4       MAC_DMA_TIMT_1       ;note: "MAC_DMA_TIMT_0" is at 020028h    |
|       02010Ch 4       MAC_DMA_TIMT_2                                                |
|       020110h 4       MAC_DMA_TIMT_3                                                |
|       020114h 4       MAC_DMA_TIMT_4                                                |
|       020118h 4       MAC_DMA_TIMT_5                                                |
|       02011Ch 4       MAC_DMA_TIMT_6                                                |
|       020120h 4       MAC_DMA_TIMT_7                                                |
|       020124h 4       MAC_DMA_TIMT_8                                                |
|       020128h 4       MAC_DMA_TIMT_9                                                |
|       02012Ch 4       MAC_DMA_CHKACC                                                |
+-------------------------------------------------------------------------------------+
```


### wmac_qcu_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       020800h 4x10    MAC_QCU_TXDP[0..9]                              |
|       020828h 1x8     PAD__1                                          |
|       020830h 4       MAC_QCU_STATUS_RING_START                       |
|       020834h 4       MAC_QCU_STATUS_RING_END                         |
|       020838h 4       MAC_QCU_STATUS_RING_CURRENT                     |
|       02083Ch 1x4     PAD__2                                          |
|       020840h 4       MAC_QCU_TXE                                     |
|       020844h 1x60    PAD__3                                          |
|       020880h 4       MAC_QCU_TXD                                     |
|       020884h 1x60    PAD__4                                          |
|       0208C0h 4x10    MAC_QCU_CBR[0..9]                               |
|       0208E8h 1x24    PAD__5                                          |
|       020900h 4x10    MAC_QCU_RDYTIME[0..9]                           |
|       020928h 1x24    PAD__6                                          |
|       020940h 4       MAC_QCU_ONESHOT_ARM_SC                          |
|       020944h 1x60    PAD__7                                          |
|       020980h 4       MAC_QCU_ONESHOT_ARM_CC                          |
|       020984h 1x60    PAD__8                                          |
|       0209C0h 4x10    MAC_QCU_MISC[0..9]                              |
|       0209E8h 1x24    PAD__9                                          |
|       020A00h 4x10    MAC_QCU_CNT[0..9]                               |
|       020A28h 1x24    PAD__10                                         |
|       020A40h 4       MAC_QCU_RDYTIME_SHDN                            |
|       020A44h 4       MAC_QCU_DESC_CRC_CHK                            |
|       020A48h 4       MAC_QCU_EOL                                     |
+-----------------------------------------------------------------------+
```


### wmac_dcu_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       021000h 4x10    MAC_DCU_QCUMASK[0..9]                           |
|       021028h 1x8     PAD__1                                          |
|       021030h 4       MAC_DCU_GBL_IFS_SIFS                            |
|       021034h 1x4     PAD__2                                          |
|       021038h 4       MAC_DCU_TXFILTER_DCU0_31_0                      |
|       02103Ch 4       MAC_DCU_TXFILTER_DCU8_31_0                      |
|       021040h 4x10    MAC_DCU_LCL_IFS[0..9]                           |
|       021068h 1x8     PAD__3                                          |
|       021070h 4       MAC_DCU_GBL_IFS_SLOT                            |
|       021074h 1x4     PAD__4                                          |
|       021078h 4       MAC_DCU_TXFILTER_DCU0_63_32                     |
|       02107Ch 4       MAC_DCU_TXFILTER_DCU8_63_32                     |
|       021080h 4x10    MAC_DCU_RETRY_LIMIT[0..9]                       |
|       0210A8h 1x8     PAD__5                                          |
|       0210B0h 4       MAC_DCU_GBL_IFS_EIFS                            |
|       0210B4h 1x4     PAD__6                                          |
|       0210B8h 4       MAC_DCU_TXFILTER_DCU0_95_64                     |
|       0210BCh 4       MAC_DCU_TXFILTER_DCU8_95_64                     |
|       0210C0h 4x10    MAC_DCU_CHANNEL_TIME[0..9]                      |
|       0210E8h 1x8     PAD__7                                          |
|       0210F0h 4       MAC_DCU_GBL_IFS_MISC                            |
|       0210F4h 1x4     PAD__8                                          |
|       0210F8h 4       MAC_DCU_TXFILTER_DCU0_127_96                    |
|       0210FCh 4       MAC_DCU_TXFILTER_DCU8_127_96                    |
|       021100h 4x10    MAC_DCU_MISC[0..9]                              |
|       021128h 1x16    PAD__9                                          |
|       021138h 4       MAC_DCU_TXFILTER_DCU1_31_0                      |
|       02113Ch 4       MAC_DCU_TXFILTER_DCU9_31_0                      |
|       021140h 4       MAC_DCU_SEQ                                     |
|       021144h 1x52    PAD__10                                         |
|       021178h 4       MAC_DCU_TXFILTER_DCU1_63_32                     |
|       02117Ch 4       MAC_DCU_TXFILTER_DCU9_63_32                     |
|       021180h 1x56    PAD__11                                         |
|       0211B8h 4       MAC_DCU_TXFILTER_DCU1_95_64                     |
|       0211BCh 4       MAC_DCU_TXFILTER_DCU9_95_64                     |
|       0211C0h 1x56    PAD__12                                         |
|       0211F8h 4       MAC_DCU_TXFILTER_DCU1_127_96                    |
|       0211FCh 4       MAC_DCU_TXFILTER_DCU9_127_96                    |
|       021200h 1x56    PAD__13                                         |
|       021238h 4       MAC_DCU_TXFILTER_DCU2_31_0                      |
|       02123Ch 1x52    PAD__14                                         |
|       021270h 4       MAC_DCU_PAUSE                                   |
|       021274h 1x4     PAD__15                                         |
|       021278h 4       MAC_DCU_TXFILTER_DCU2_63_32                     |
|       02127Ch 1x52    PAD__16                                         |
|       0212B0h 4       MAC_DCU_WOW_KACFG                               |
|       0212B4h 1x4     PAD__17                                         |
|       0212B8h 4       MAC_DCU_TXFILTER_DCU2_95_64                     |
|       0212BCh 1x52    PAD__18                                         |
|       0212F0h 4       MAC_DCU_TXSLOT                                  |
|       0212F4h 1x4     PAD__19                                         |
|       0212F8h 4       MAC_DCU_TXFILTER_DCU2_127_96                    |
|       0212FCh 1x60    PAD__20                                         |
|       021338h 4       MAC_DCU_TXFILTER_DCU3_31_0          ;\          
|       02133Ch 1x60    PAD__21                             ;           |
|       021378h 4       MAC_DCU_TXFILTER_DCU3_63_32         ;           |
|       02137Ch 1x60    PAD__22                             ;           |
|       0213B8h 4       MAC_DCU_TXFILTER_DCU3_95_64         ;           |
|       0213BCh 1x60    PAD__23                             ;           |
|       0213F8h 4       MAC_DCU_TXFILTER_DCU3_127_96        ;/          |
|       0213FCh 1x60    PAD__24                                         |
|       021438h 4       MAC_DCU_TXFILTER_DCU4_31_0                      |
|       02143Ch 4       MAC_DCU_TXFILTER_CLEAR                          |
|       021440h 1x56    PAD__25                                         |
|       021478h 4       MAC_DCU_TXFILTER_DCU4_63_32                     |
|       02147Ch 4       MAC_DCU_TXFILTER_SET                            |
|       021480h 1x56    PAD__26                                         |
|       0214B8h 4       MAC_DCU_TXFILTER_DCU4_95_64                     |
|       0214BCh 1x60    PAD__27                                         |
|       0214F8h 4       MAC_DCU_TXFILTER_DCU4_127_96                    |
|       0214FCh 1x60    PAD__28                                         |
|       021538h 4       MAC_DCU_TXFILTER_DCU5_31_0          ;\          
|       02153Ch 1x60    PAD__29                             ;           |
|       021578h 4       MAC_DCU_TXFILTER_DCU5_63_32         ;           |
|       02157Ch 1x60    PAD__30                             ;           |
|       0215B8h 4       MAC_DCU_TXFILTER_DCU5_95_64         ;           |
|       0215BCh 1x60    PAD__31                             ;           |
|       0215F8h 4       MAC_DCU_TXFILTER_DCU5_127_96        ;/          |
|       0215FCh 1x60    PAD__32                                         |
|       021638h 4       MAC_DCU_TXFILTER_DCU6_31_0          ;\          
|       02163Ch 1x60    PAD__33                             ;           |
|       021678h 4       MAC_DCU_TXFILTER_DCU6_63_32         ;           |
|       02167Ch 1x60    PAD__34                             ;           |
|       0216B8h 4       MAC_DCU_TXFILTER_DCU6_95_64         ;           |
|       0216BCh 1x60    PAD__35                             ;           |
|       0216F8h 4       MAC_DCU_TXFILTER_DCU6_127_96        ;/          |
|       0216FCh 1x60    PAD__36                                         |
|       021738h 4       MAC_DCU_TXFILTER_DCU7_31_0          ;\          
|       02173Ch 1x60    PAD__37                             ;           |
|       021778h 4       MAC_DCU_TXFILTER_DCU7_63_32         ;           |
|       02177Ch 1x60    PAD__38                             ;           |
|       0217B8h 4       MAC_DCU_TXFILTER_DCU7_95_64         ;           |
|       0217BCh 1x60    PAD__39                             ;           |
|       0217F8h 4       MAC_DCU_TXFILTER_DCU7_127_96        ;/          |
+-----------------------------------------------------------------------+
```


### wmac_pcu_reg.h (1) (hw6.0)

```
+-----------------------------------------------------------------------------------+
|       028000h 4       MAC_PCU_STA_ADDR_L32                                        |
|       028004h 4       MAC_PCU_STA_ADDR_U16                                        |
|       028008h 4       MAC_PCU_BSSID_L32                                           |
|       02800Ch 4       MAC_PCU_BSSID_U16                                           |
|       028010h 4       MAC_PCU_BCN_RSSI_AVE                                        |
|       028014h 4       MAC_PCU_ACK_CTS_TIMEOUT                                     |
|       028018h 4       MAC_PCU_BCN_RSSI_CTL                                        |
|       02801Ch 4       MAC_PCU_USEC_LATENCY                                        |
|       028020h 4       MAC_PCU_BCN_RSSI_CTL2                                       |
|       028024h 4       MAC_PCU_BT_WL_1                                             |
|       028028h 4       MAC_PCU_BT_WL_2                                             |
|       02802Ch 4       MAC_PCU_BT_WL_3                                             |
|       028030h 4       MAC_PCU_BT_WL_4                                             |
|       028034h 4       MAC_PCU_COEX_EPTA                                           |
|       028038h 4       MAC_PCU_MAX_CFP_DUR                                         |
|       02803Ch 4       MAC_PCU_RX_FILTER                                           |
|       028040h 4       MAC_PCU_MCAST_FILTER_L32                                    |
|       028044h 4       MAC_PCU_MCAST_FILTER_U32                                    |
|       028048h 4       MAC_PCU_DIAG_SW                                             |
|       02804Ch 1x8     PAD__1                                                      |
|       028054h 4       MAC_PCU_TST_ADDAC                                           |
|       028058h 4       MAC_PCU_DEF_ANTENNA                                         |
|       02805Ch 4       MAC_PCU_AES_MUTE_MASK_0                                     |
|       028060h 4       MAC_PCU_AES_MUTE_MASK_1                                     |
|       028064h 4       MAC_PCU_GATED_CLKS                                          |
|       028068h 4       MAC_PCU_OBS_BUS_2                                           |
|       02806Ch 4       MAC_PCU_OBS_BUS_1                                           |
|       028070h 4       MAC_PCU_DYM_MIMO_PWR_SAVE                                   |
|       028074h 1x12    PAD__2                                                      |
|       028080h 4       MAC_PCU_LAST_BEACON_TSF                                     |
|       028084h 4       MAC_PCU_NAV                                                 |
|       028088h 4       MAC_PCU_RTS_SUCCESS_CNT                                     |
|       02808Ch 4       MAC_PCU_RTS_FAIL_CNT                                        |
|       028090h 4       MAC_PCU_ACK_FAIL_CNT                                        |
|       028094h 4       MAC_PCU_FCS_FAIL_CNT                                        |
|       028098h 4       MAC_PCU_BEACON_CNT                                          |
|       02809Ch 4       MAC_PCU_BEACON2_CNT                                         |
|       0280A0h 4       MAC_PCU_BASIC_SET                                           |
|       0280A4h 4       MAC_PCU_MGMT_SEQ                                            |
|       0280A8h 4       MAC_PCU_BF_RPT1                                             |
|       0280ACh 4       MAC_PCU_BF_RPT2                                             |
|       0280B0h 4       MAC_PCU_TX_ANT_1                                            |
|       0280B4h 4       MAC_PCU_TX_ANT_2                                            |
|       0280B8h 4       MAC_PCU_TX_ANT_3                                            |
|       0280BCh 4       MAC_PCU_TX_ANT_4                                            |
|       0280C0h 4       MAC_PCU_XRMODE                                              |
|       0280C4h 4       MAC_PCU_XRDEL                                               |
|       0280C8h 4       MAC_PCU_XRTO                                                |
|       0280CCh 4       MAC_PCU_XRCRP                                               |
|       0280D0h 4       MAC_PCU_XRSTMP                                              |
|       0280D4h 1x8     PAD__3                                                      |
|       0280DCh 4       MAC_PCU_SELF_GEN_DEFAULT                                    |
|       0280E0h 4       MAC_PCU_ADDR1_MASK_L32                                      |
|       0280E4h 4       MAC_PCU_ADDR1_MASK_U16                                      |
|       0280E8h 4       MAC_PCU_TPC                                                 |
|       0280ECh 4       MAC_PCU_TX_FRAME_CNT                                        |
|       0280F0h 4       MAC_PCU_RX_FRAME_CNT                                        |
|       0280F4h 4       MAC_PCU_RX_CLEAR_CNT                                        |
|       0280F8h 4       MAC_PCU_CYCLE_CNT                                           |
|       0280FCh 4       MAC_PCU_QUIET_TIME_1                                        |
|       028100h 4       MAC_PCU_QUIET_TIME_2                                        |
|       028104h 1x4     PAD__4                                                      |
|       028108h 4       MAC_PCU_QOS_NO_ACK                                          |
|       02810Ch 4       MAC_PCU_PHY_ERROR_MASK                                      |
|       028110h 4       MAC_PCU_XRLAT                                               |
|       028114h 4       MAC_PCU_RXBUF                                               |
|       028118h 4       MAC_PCU_MIC_QOS_CONTROL                                     |
|       02811Ch 4       MAC_PCU_MIC_QOS_SELECT                                      |
|       028120h 4       MAC_PCU_MISC_MODE                                           |
|       028124h 4       MAC_PCU_FILTER_OFDM_CNT                                     |
|       028128h 4       MAC_PCU_FILTER_CCK_CNT                                      |
|       02812Ch 4       MAC_PCU_PHY_ERR_CNT_1                                       |
|       028130h 4       MAC_PCU_PHY_ERR_CNT_1_MASK                                  |
|       028134h 4       MAC_PCU_PHY_ERR_CNT_2                                       |
|       028138h 4       MAC_PCU_PHY_ERR_CNT_2_MASK                                  |
|       02813Ch 1x8     PAD__5                                                      |
|       028144h 4       MAC_PCU_PHY_ERROR_EIFS_MASK                                 |
|       028148h 1x8     PAD__6                                                      |
|       028150h 4       MAC_PCU_COEX_LNAMAXGAIN1                                    |
|       028154h 4       MAC_PCU_COEX_LNAMAXGAIN2                                    |
|       028158h 4       MAC_PCU_COEX_LNAMAXGAIN3                                    |
|       02815Ch 4       MAC_PCU_COEX_LNAMAXGAIN4                                    |
|       028160h 1x8     PAD__7                                                      |
|       028168h 4       MAC_PCU_PHY_ERR_CNT_3                                       |
|       02816Ch 4       MAC_PCU_PHY_ERR_CNT_3_MASK                                  |
|       028170h 4       MAC_PCU_BLUETOOTH_MODE                                      |
|       028174h 1x4     PAD__8                                                      |
|       028178h 4       MAC_PCU_HCF_TIMEOUT                                         |
|       02817Ch 4       MAC_PCU_BLUETOOTH_MODE2                                     |
|       028180h 1x72    PAD__9                                                      |
|       0281C8h 4       MAC_PCU_BLUETOOTH_TSF_BT_ACTIVE                             |
|       0281CCh 4       MAC_PCU_BLUETOOTH_TSF_BT_PRIORITY                           |
|       0281D0h 4       MAC_PCU_TXSIFS                                              |
|       0281D4h 4       MAC_PCU_BLUETOOTH_MODE3                                     |
|       0281D8h 4       MAC_PCU_BLUETOOTH_MODE4                                     |
|       0281DCh 4       MAC_PCU_BLUETOOTH_MODE5                                     |
|       0281E0h 4       MAC_PCU_BLUETOOTH_WEIGHTS                                   |
|       0281E4h 4       MAC_PCU_BT_BT_ASYNC                                         |
|       0281E8h 1x4     PAD__10                                                     |
|       0281ECh 4       MAC_PCU_TXOP_X                                              |
|       0281F0h 4       MAC_PCU_TXOP_0_3                                            |
|       0281F4h 4       MAC_PCU_TXOP_4_7                                            |
|       0281F8h 4       MAC_PCU_TXOP_8_11                                           |
|       0281FCh 4       MAC_PCU_TXOP_12_15                                          |
|       028200h 4       MAC_PCU_TDMA_TXFRAME_START_TIME_TRIGGER_LSB                 |
|       028204h 4       MAC_PCU_TDMA_TXFRAME_START_TIME_TRIGGER_MSB                 |
|       028208h 4       MAC_PCU_TDMA_SLOT_ALERT_CNTL                                |
|       02820Ch 1x80    PAD__11                                                     |
|       02825Ch 4       MAC_PCU_WOW1                ;WOW Misc                       |
|       028260h 4       MAC_PCU_WOW2                ;WOW AIFS/SLOT/TRY_CNT          |
|       028264h 4       MAC_PCU_LOGIC_ANALYZER                                      |
|       028268h 4       MAC_PCU_LOGIC_ANALYZER_32L                                  |
|       02826Ch 4       MAC_PCU_LOGIC_ANALYZER_16U                                  |
|       028270h 4       MAC_PCU_WOW3_BEACON_FAIL    ;WOW Beacon Fail Enable         |
|       028274h 4       MAC_PCU_WOW3_BEACON         ;WOW Beacon Timeout             |
|       028278h 4       MAC_PCU_WOW3_KEEP_ALIVE     ;WOW Keep-Alive Timeout         |
|       02827Ch 4       MAC_PCU_WOW_KA        ;WOW Auto/Fail/BkoffCs Enable/Disable |
|       028280h 1x4     PAD__12                                                     |
|       028284h 4       PCU_1US                                                     |
|       028288h 4       PCU_KA                                                      |
|       02828Ch 4       WOW_EXACT                   ;WOW Exact Length/Offset 1      |
|       028290h 1x4     PAD__13                                                     |
|       028294h 4       PCU_WOW4                    ;WOW Offset 0..3                |
|       028298h 4       PCU_WOW5                    ;WOW Offset 4..7                |
|       02829Ch 4       MAC_PCU_PHY_ERR_CNT_MASK_CONT                               |
|       0282A0h 1x96    PAD__14                                                     |
|       028300h 4       MAC_PCU_AZIMUTH_MODE                                        |
|       028304h 1x16    PAD__15                                                     |
|       028314h 4       MAC_PCU_AZIMUTH_TIME_STAMP                                  |
|       028318h 4       MAC_PCU_20_40_MODE                                          |
|       02831Ch 4       MAC_PCU_H_XFER_TIMEOUT                                      |
|       028320h 1x8     PAD__16                                                     |
|       028328h 4       MAC_PCU_RX_CLEAR_DIFF_CNT                                   |
|       02832Ch 4       MAC_PCU_SELF_GEN_ANTENNA_MASK                               |
|       028330h 4       MAC_PCU_BA_BAR_CONTROL                                      |
|       028334h 4       MAC_PCU_LEGACY_PLCP_SPOOF                                   |
|       028338h 4       MAC_PCU_PHY_ERROR_MASK_CONT                                 |
|       02833Ch 4       MAC_PCU_TX_TIMER                                            |
|       028340h 4       MAC_PCU_TXBUF_CTRL                                          |
|       028344h 4       MAC_PCU_MISC_MODE2                                          |
|       028348h 4       MAC_PCU_ALT_AES_MUTE_MASK                                   |
|       02834Ch 4       MAC_PCU_WOW6                ;;WOW RX Buf Start Addr (R)     |
|       028350h 4       ASYNC_FIFO_REG1                                             |
|       028354h 4       ASYNC_FIFO_REG2                                             |
|       028358h 4       ASYNC_FIFO_REG3                                             |
|       02835Ch 4       MAC_PCU_WOW5                ;WOW RX Abort Enable            |
|       028360h 4       MAC_PCU_WOW_LENGTH1         ;WOW Pattern 0..3               |
|       028364h 4       MAC_PCU_WOW_LENGTH2         ;WOW Pattern 4..7               |
|       028368h 4       WOW_PATTERN_MATCH_LESS_THAN_256_BYTES                       |
|       02836Ch 1x4     PAD__17                                                     |
|       028370h 4       MAC_PCU_WOW4                ;WOW Pattern Enable/Detect      |
|       028374h 4       WOW2_EXACT                  ;WOW Exact Length/Offset 2 ;\   
|       028378h 4       PCU_WOW6                    ;WOW Offset 8..11          ;    |
|       02837Ch 4       PCU_WOW7                    ;WOW Offset 12..15         ;    |
|       028380h 4       MAC_PCU_WOW_LENGTH3         ;WOW Pattern 8..11         ;    |
|       028384h 4       MAC_PCU_WOW_LENGTH4         ;WOW Pattern 12..15        ;/   |
|       028388h 4       MAC_PCU_LOCATION_MODE_CONTROL                               |
|       02838Ch 4       MAC_PCU_LOCATION_MODE_TIMER                                 |
|       028390h 1x8     PAD__18                                                     |
|       028398h 4       MAC_PCU_BSSID2_L32                                          |
|       02839Ch 4       MAC_PCU_BSSID2_U16                                          |
|       0283A0h 4       MAC_PCU_DIRECT_CONNECT                                      |
|       0283A4h 4       MAC_PCU_TID_TO_AC                                           |
|       0283A8h 4       MAC_PCU_HP_QUEUE                                            |
|       0283ACh 1x16    PAD__19                                                     |
|       0283BCh 4       MAC_PCU_AGC_SATURATION_CNT0                                 |
|       0283C0h 4       MAC_PCU_AGC_SATURATION_CNT1                                 |
|       0283C4h 4       MAC_PCU_AGC_SATURATION_CNT2                                 |
|       0283C8h 4       MAC_PCU_HW_BCN_PROC1                                        |
|       0283CCh 4       MAC_PCU_HW_BCN_PROC2                                        |
|       0283D0h 4       MAC_PCU_MISC_MODE3                                          |
|       0283D4h 4       MAC_PCU_MISC_MODE4                                          |
|       0283D8h 1x4     PAD__20                                                     |
|       0283DCh 4       MAC_PCU_PS_FILTER                                           |
|       0283E0h 4       MAC_PCU_BASIC_RATE_SET0                                     |
|       0283E4h 4       MAC_PCU_BASIC_RATE_SET1                                     |
|       0283E8h 4       MAC_PCU_BASIC_RATE_SET2                                     |
|       0283ECh 4       MAC_PCU_BASIC_RATE_SET3                                     |
|       0283F0h 1x16    PAD__21                                                     |
|       028400h 4x64    MAC_PCU_TXBUF_BA[0..63]                                     |
|       028500h 4x64    MAC_PCU_BT_BT[0..63]                                        |
|       028600h 4       MAC_PCU_RX_INT_STATUS0                                      |
|       028604h 4       MAC_PCU_RX_INT_STATUS1                                      |
|       028608h 4       MAC_PCU_RX_INT_STATUS2                                      |
|       02860Ch 4       MAC_PCU_RX_INT_STATUS3                                      |
|       028610h 4       HT_HALF_GI_RATE1                                            |
|       028614h 4       HT_HALF_GI_RATE2                                            |
|       028618h 4       HT_FULL_GI_RATE1                                            |
|       02861Ch 4       HT_FULL_GI_RATE2                                            |
|       028620h 4       LEGACY_RATE1                                                |
|       028624h 4       LEGACY_RATE2                                                |
|       028628h 4       LEGACY_RATE3                                                |
|       02862Ch 4       RX_INT_FILTER                                               |
|       028630h 4       RX_INT_OVERFLOW                                             |
|       028634h 4       RX_FILTER_THRESH0                                           |
|       028638h 4       RX_FILTER_THRESH1                                           |
|       02863Ch 4       RX_PRIORITY_THRESH0                                         |
|       028640h 4       RX_PRIORITY_THRESH1                                         |
|       028644h 4       RX_PRIORITY_THRESH2                                         |
|       028648h 4       RX_PRIORITY_THRESH3                                         |
|       02864Ch 4       RX_PRIORITY_OFFSET0                                         |
|       028650h 4       RX_PRIORITY_OFFSET1                                         |
|       028654h 4       RX_PRIORITY_OFFSET2                                         |
|       028658h 4       RX_PRIORITY_OFFSET3                                         |
|       02865Ch 4       RX_PRIORITY_OFFSET4                                         |
|       028660h 4       RX_PRIORITY_OFFSET5                                         |
|       028664h 4       MAC_PCU_LAST_BEACON2_TSF                                    |
|       028668h 4       MAC_PCU_PHY_ERROR_AIFS                                      |
|       02866Ch 4       MAC_PCU_PHY_ERROR_AIFS_MASK                                 |
|       028670h 4       MAC_PCU_FILTER_RSSI_AVE                                     |
|       028674h 4       MAC_PCU_TBD_FILTER                                          |
|       028678h 4       MAC_PCU_BT_ANT_SLEEP_EXTEND                                 |
|       02867Ch 1x388   PAD__22                                                     |
|       028800h 4x512   MAC_PCU_KEY_CACHE[0..511]                                   |
|       029000h 1x20480 PAD__23                     ;<-- this includes BB regs      |
|       02E000h 4x2048  MAC_PCU_BUF[0..2047]        ;<-- this after BB regs         |
+-----------------------------------------------------------------------------------+
```


### bb_reg.h (1) - bb_chn_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       029800h 4       BB_TIMING_CONTROLS_1                            |
|       029804h 4       BB_TIMING_CONTROLS_2                            |
|       029808h 4       BB_TIMING_CONTROLS_3                            |
|       02980Ch 4       BB_TIMING_CONTROL_4                             |
|       029810h 4       BB_TIMING_CONTROL_5                             |
|       029814h 4       BB_TIMING_CONTROL_6                             |
|       029818h 4       BB_TIMING_CONTROL_11                            |
|       02981Ch 4       BB_SPUR_MASK_CONTROLS                           |
|       029820h 4       BB_FIND_SIGNAL_LOW                              |
|       029824h 4       BB_SFCORR                                       |
|       029828h 4       BB_SELF_CORR_LOW                                |
|       02982Ch 4       BB_EXT_CHAN_SCORR_THR                           |
|       029830h 4       BB_EXT_CHAN_PWR_THR_2_B0                        |
|       029834h 4       BB_RADAR_DETECTION                              |
|       029838h 4       BB_RADAR_DETECTION_2                            |
|       02983Ch 4       BB_EXTENSION_RADAR                              |
|       029840h 1x64    PAD__0                                          |
|       029880h 4       BB_MULTICHAIN_CONTROL                           |
|       029884h 4       BB_PER_CHAIN_CSD                                |
|       029888h 1x24    PAD__1                                          |
|       0298A0h 4       BB_TX_CRC                                       |
|       0298A4h 4       BB_TSTDAC_CONSTANT                              |
|       0298A8h 4       BB_SPUR_REPORT_B0                               |
|       0298ACh 1x4     PAD__2                                          |
|       0298B0h 4       BB_TXIQCAL_CONTROL_3                            |
|       0298B4h 1x8     PAD__3                                          |
|       0298BCh 4       BB_GREEN_TX_CONTROL_1                           |
|       0298C0h 4       BB_IQ_ADC_MEAS_0_B0                             |
|       0298C4h 4       BB_IQ_ADC_MEAS_1_B0                             |
|       0298C8h 4       BB_IQ_ADC_MEAS_2_B0                             |
|       0298CCh 4       BB_IQ_ADC_MEAS_3_B0                             |
|       0298D0h 4       BB_TX_PHASE_RAMP_B0                             |
|       0298D4h 4       BB_ADC_GAIN_DC_CORR_B0                          |
|       0298D8h 1x4     PAD__4                                          |
|       0298DCh 4       BB_RX_IQ_CORR_B0                                |
|       0298E0h 1x4     PAD__5                                          |
|       0298E4h 4       BB_PAPRD_AM2AM_MASK                             |
|       0298E8h 4       BB_PAPRD_AM2PM_MASK                             |
|       0298ECh 4       BB_PAPRD_HT40_MASK                              |
|       0298F0h 4       BB_PAPRD_CTRL0_B0                               |
|       0298F4h 4       BB_PAPRD_CTRL1_B0                               |
|       0298F8h 4       BB_PA_GAIN123_B0                                |
|       0298FCh 4       BB_PA_GAIN45_B0                                 |
|       029900h 4       BB_PAPRD_PRE_POST_SCALE_0_B0                    |
|       029904h 4       BB_PAPRD_PRE_POST_SCALE_1_B0                    |
|       029908h 4       BB_PAPRD_PRE_POST_SCALE_2_B0                    |
|       02990Ch 4       BB_PAPRD_PRE_POST_SCALE_3_B0                    |
|       029910h 4       BB_PAPRD_PRE_POST_SCALE_4_B0                    |
|       029914h 4       BB_PAPRD_PRE_POST_SCALE_5_B0                    |
|       029918h 4       BB_PAPRD_PRE_POST_SCALE_6_B0                    |
|       02991Ch 4       BB_PAPRD_PRE_POST_SCALE_7_B0                    |
|       029920h 4x120   BB_PAPRD_MEM_TAB_B0[0..119]                     |
|       029B00h 4x60    BB_CHAN_INFO_CHAN_TAB_B0[0..59]                 |
|       029BF0h 4       BB_CHN_TABLES_INTF_ADDR                         |
|       029BF4h 4       BB_CHN_TABLES_INTF_DATA                         |
+-----------------------------------------------------------------------+
```


### bb_reg.h (2) - bb_mrc_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       029C00h 4       BB_TIMING_CONTROL_3A                            |
|       029C04h 4       BB_LDPC_CNTL1                                   |
|       029C08h 4       BB_LDPC_CNTL2                                   |
|       029C0Ch 4       BB_PILOT_SPUR_MASK                              |
|       029C10h 4       BB_CHAN_SPUR_MASK                               |
|       029C14h 4       BB_SHORT_GI_DELTA_SLOPE                         |
|       029C18h 4       BB_ML_CNTL1                                     |
|       029C1Ch 4       BB_ML_CNTL2                                     |
|       029C20h 4       BB_TSTADC                                       |
+-----------------------------------------------------------------------+
```


### bb_reg.h (3) - bb_bbb_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       029D00h 4       BB_BBB_RX_CTRL_1                                |
|       029D04h 4       BB_BBB_RX_CTRL_2                                |
|       029D08h 4       BB_BBB_RX_CTRL_3                                |
|       029D0Ch 4       BB_BBB_RX_CTRL_4                                |
|       029D10h 4       BB_BBB_RX_CTRL_5                                |
|       029D14h 4       BB_BBB_RX_CTRL_6                                |
|       029D18h 4       BB_FORCE_CLKEN_CCK                              |
+-----------------------------------------------------------------------+
```


### bb_reg.h (4) - bb_agc_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       029E00h 4       BB_SETTLING_TIME                                |
|       029E04h 4       BB_GAIN_FORCE_MAX_GAINS_B0                      |
|       029E08h 4       BB_GAINS_MIN_OFFSETS                            |
|       029E0Ch 4       BB_DESIRED_SIGSIZE                              |
|       029E10h 4       BB_FIND_SIGNAL                                  |
|       029E14h 4       BB_AGC                                          |
|       029E18h 4       BB_EXT_ATTEN_SWITCH_CTL_B0                      |
|       029E1Ch 4       BB_CCA_B0                                       |
|       029E20h 4       BB_CCA_CTRL_2_B0                                |
|       029E24h 4       BB_RESTART                                      |
|       029E28h 4       BB_MULTICHAIN_GAIN_CTRL                         |
|       029E2Ch 4       BB_EXT_CHAN_PWR_THR_1                           |
|       029E30h 4       BB_EXT_CHAN_DETECT_WIN                          |
|       029E34h 4       BB_PWR_THR_20_40_DET                            |
|       029E38h 4       BB_RIFS_SRCH                                    |
|       029E3Ch 4       BB_PEAK_DET_CTRL_1                              |
|       029E40h 4       BB_PEAK_DET_CTRL_2                              |
|       029E44h 4       BB_RX_GAIN_BOUNDS_1                             |
|       029E48h 4       BB_RX_GAIN_BOUNDS_2                             |
|       029E4Ch 4       BB_PEAK_DET_CAL_CTRL                            |
|       029E50h 4       BB_AGC_DIG_DC_CTRL                              |
|       029E54h 4       BB_BT_COEX_1                                    |
|       029E58h 4       BB_BT_COEX_2                                    |
|       029E5Ch 4       BB_BT_COEX_3                                    |
|       029E60h 4       BB_BT_COEX_4                                    |
|       029E64h 4       BB_BT_COEX_5                                    |
|       029E68h 4       BB_REDPWR_CTRL_1                                |
|       029E6Ch 4       BB_REDPWR_CTRL_2                                |
|       029E70h 1x272   PAD__0                                          |
|       029F80h 4       BB_RSSI_B0                                      |
|       029F84h 4       BB_SPUR_EST_CCK_REPORT_B0                       |
|       029F88h 4       BB_AGC_DIG_DC_STATUS_I_B0                       |
|       029F8Ch 4       BB_AGC_DIG_DC_STATUS_Q_B0                       |
|       029F90h 4       BB_DC_CAL_STATUS_B0                             |
|       029F94h 1x44    PAD__1                                          |
|       029FC0h 4       BB_BBB_SIG_DETECT                               |
|       029FC4h 4       BB_BBB_DAGC_CTRL                                |
|       029FC8h 4       BB_IQCORR_CTRL_CCK                              |
|       029FCCh 4       BB_CCK_SPUR_MIT                                 |
|       029FD0h 4       BB_MRC_CCK_CTRL                                 |
|       029FD4h 4       BB_CCK_BLOCKER_DET                              |
|       029FD8h 1x40    PAD__2                                          |
|       02A000h 4x128   BB_RX_OCGAIN[0..127]                            |
+-----------------------------------------------------------------------+
```


### bb_reg.h (5) - bb_sm_reg_map (hw6.0)

```
+-------------------------------------------------------------------------+
|       02A200h 4       BB_D2_CHIP_ID                                     |
|       02A204h 4       BB_GEN_CONTROLS                                   |
|       02A208h 4       BB_MODES_SELECT                                   |
|       02A20Ch 4       BB_ACTIVE                                         |
|       02A210h 1x16    PAD__0                                            |
|       02A220h 4       BB_VIT_SPUR_MASK_A                                |
|       02A224h 4       BB_VIT_SPUR_MASK_B                                |
|       02A228h 4       BB_SPECTRAL_SCAN                                  |
|       02A22Ch 4       BB_RADAR_BW_FILTER                                |
|       02A230h 4       BB_SEARCH_START_DELAY                             |
|       02A234h 4       BB_MAX_RX_LENGTH                                  |
|       02A238h 4       BB_FRAME_CONTROL                                  |
|       02A23Ch 4       BB_RFBUS_REQUEST                                  |
|       02A240h 4       BB_RFBUS_GRANT                                    |
|       02A244h 4       BB_RIFS                                           |
|       02A248h 4       BB_SPECTRAL_SCAN_2                                |
|       02A24Ch 1x4     PAD__1                                            |
|       02A250h 4       BB_RX_CLEAR_DELAY                                 |
|       02A254h 4       BB_ANALOG_POWER_ON_TIME                           |
|       02A258h 4       BB_TX_TIMING_1                                    |
|       02A25Ch 4       BB_TX_TIMING_2                                    |
|       02A260h 4       BB_TX_TIMING_3                                    |
|       02A264h 4       BB_XPA_TIMING_CONTROL                             |
|       02A268h 1x24    PAD__2                                            |
|       02A280h 4       BB_MISC_PA_CONTROL                                |
|       02A284h 4       BB_SWITCH_TABLE_CHN_B0                            |
|       02A288h 4       BB_SWITCH_TABLE_COM1                              |
|       02A28Ch 4       BB_SWITCH_TABLE_COM2                              |
|       02A290h 1x16    PAD__3                                            |
|       02A2A0h 4       BB_MULTICHAIN_ENABLE                              |
|       02A2A4h 1x28    PAD__4                                            |
|       02A2C0h 4       BB_CAL_CHAIN_MASK                                 |
|       02A2C4h 4       BB_AGC_CONTROL                                    |
|       02A2C8h 4       BB_IQ_ADC_CAL_MODE                                |
|       02A2CCh 4       BB_FCAL_1                                         |
|       02A2D0h 4       BB_FCAL_2_B0                                      |
|       02A2D4h 4       BB_DFT_TONE_CTRL_B0                               |
|       02A2D8h 4       BB_CL_CAL_CTRL                                    |
|       02A2DCh 4       BB_CL_MAP_0_B0                                    |
|       02A2E0h 4       BB_CL_MAP_1_B0                                    |
|       02A2E4h 4       BB_CL_MAP_2_B0                                    |
|       02A2E8h 4       BB_CL_MAP_3_B0                                    |
|       02A2ECh 4       BB_CL_MAP_PAL_0_B0                                |
|       02A2F0h 4       BB_CL_MAP_PAL_1_B0                                |
|       02A2F4h 4       BB_CL_MAP_PAL_2_B0                                |
|       02A2F8h 4       BB_CL_MAP_PAL_3_B0                                |
|       02A2FCh 1x4     PAD__5                                            |
|       02A300h 4x16    BB_CL_TAB_B0[0..15]                               |
|       02A340h 4       BB_SYNTH_CONTROL                                  |
|       02A344h 4       BB_ADDAC_CLK_SELECT                               |
|       02A348h 4       BB_PLL_CNTL                                       |
|       02A34Ch 4       BB_ANALOG_SWAP                                    |
|       02A350h 4       BB_ADDAC_PARALLEL_CONTROL                         |
|       02A354h 1x4     PAD__6                                            |
|       02A358h 4       BB_FORCE_ANALOG                                   |
|       02A35Ch 1x4     PAD__7                                            |
|       02A360h 4       BB_TEST_CONTROLS                                  |
|       02A364h 4       BB_TEST_CONTROLS_STATUS                           |
|       02A368h 4       BB_TSTDAC                                         |
|       02A36Ch 4       BB_CHANNEL_STATUS                                 |
|       02A370h 4       BB_CHANINFO_CTRL                                  |
|       02A374h 4       BB_CHAN_INFO_NOISE_PWR                            |
|       02A378h 4       BB_CHAN_INFO_GAIN_DIFF                            |
|       02A37Ch 4       BB_CHAN_INFO_FINE_TIMING                          |
|       02A380h 4       BB_CHAN_INFO_GAIN_B0                              |
|       02A384h 4       BB_SM_HIST                                        |
|       02A388h 1x8     PAD__8                                            |
|       02A390h 4       BB_SCRAMBLER_SEED                                 |
|       02A394h 4       BB_BBB_TX_CTRL                                    |
|       02A398h 4       BB_BBB_TXFIR_0                                    |
|       02A39Ch 4       BB_BBB_TXFIR_1                                    |
|       02A3A0h 4       BB_BBB_TXFIR_2                                    |
|       02A3A4h 4       BB_HEAVY_CLIP_CTRL                                |
|       02A3A8h 4       BB_HEAVY_CLIP_20                                  |
|       02A3ACh 4       BB_HEAVY_CLIP_40                                  |
|       02A3B0h 4       BB_ILLEGAL_TX_RATE                                |
|       02A3B4h 1x12    PAD__9                                            |
|       02A3C0h 4       BB_POWERTX_RATE1   ;Power TX 0..3                 |
|       02A3C4h 4       BB_POWERTX_RATE2   ;Power TX 4..7                 |
|       02A3C8h 4       BB_POWERTX_RATE3   ;Power TX 1L,2L,2S             |
|       02A3CCh 4       BB_POWERTX_RATE4   ;Power TX 55L,55S,11L,11S      |
|       02A3D0h 4       BB_POWERTX_RATE5   ;Power TX HT20_0..3            |
|       02A3D4h 4       BB_POWERTX_RATE6   ;Power TX HT20_4..7            |
|       02A3D8h 4       BB_POWERTX_RATE7   ;Power TX HT40_0..3            |
|       02A3DCh 4       BB_POWERTX_RATE8   ;Power TX HT40_4..7            |
|       02A3E0h 4       BB_POWERTX_RATE9   ;Power TX DUP40/EXT20_CCK/OFDM |
|       02A3E4h 4       BB_POWERTX_RATE10  ;Power TX HT20_8..11           |
|       02A3E8h 4       BB_POWERTX_RATE11  ;Power TX HT20/40_12/13        |
|       02A3ECh 4       BB_POWERTX_RATE12  ;Power TX HT40_8..11           |
|       02A3F0h 4       BB_POWERTX_MAX     ;Power TX Flags                |
|       02A3F4h 4       BB_POWERTX_SUB     ;Power TX Sub_for_2chain       |
|       02A3F8h 4       BB_TPC_1                                          |
|       02A3FCh 4       BB_TPC_2                                          |
|       02A400h 4       BB_TPC_3                                          |
|       02A404h 4       BB_TPC_4_B0                                       |
|       02A408h 4       BB_TPC_5_B0                                       |
|       02A40Ch 4       BB_TPC_6_B0                                       |
|       02A410h 4       BB_TPC_7                                          |
|       02A414h 4       BB_TPC_8                                          |
|       02A418h 4       BB_TPC_9                                          |
|       02A41Ch 4       BB_TPC_10                                         |
|       02A420h 4       BB_TPC_11_B0                                      |
|       02A424h 4       BB_TPC_12                                         |
|       02A428h 4       BB_TPC_13                                         |
|       02A42Ch 4       BB_TPC_14                                         |
|       02A430h 4       BB_TPC_15                                         |
|       02A434h 4       BB_TPC_16                                         |
|       02A438h 4       BB_TPC_17                                         |
|       02A43Ch 4       BB_TPC_18                                         |
|       02A440h 4       BB_TPC_19_B0                                      |
|       02A444h 4       BB_TPC_20                                         |
|       02A448h 4       BB_THERM_ADC_1                                    |
|       02A44Ch 4       BB_THERM_ADC_2                                    |
|       02A450h 4       BB_THERM_ADC_3                                    |
|       02A454h 4       BB_THERM_ADC_4                                    |
|       02A458h 4       BB_TX_FORCED_GAIN                                 |
|       02A45Ch 1x36    PAD__10                                           |
|       02A480h 4x32    BB_PDADC_TAB_B0[0..31]                            |
|       02A500h 4x32    BB_TX_GAIN_TAB_(1..32)                            |
|       02A580h 4       BB_RTT_CTRL                                       |
|       02A584h 4       BB_RTT_TABLE_SW_INTF_B0                           |
|       02A588h 4       BB_RTT_TABLE_SW_INTF_1_B0                         |
|       02A58Ch 4       BB_TX_GAIN_TAB_1_16_LSB_EXT                       |
|       02A590h 4       BB_TX_GAIN_TAB_17_32_LSB_EXT                      |
|       02A594h 1x108   PAD__11                                           |
|       02A600h 4x16    BB_CALTX_GAIN_SET_(0,2,4,6,..,28,30)              |
|       02A640h 1x4     PAD__12                                           |
|       02A644h 4       BB_TXIQCAL_CONTROL_0                              |
|       02A648h 4       BB_TXIQCAL_CONTROL_1                              |
|       02A64Ch 4       BB_TXIQCAL_CONTROL_2                              |
|       02A650h 4       BB_TXIQ_CORR_COEFF_01_B0                          |
|       02A654h 4       BB_TXIQ_CORR_COEFF_23_B0                          |
|       02A658h 4       BB_TXIQ_CORR_COEFF_45_B0                          |
|       02A65Ch 4       BB_TXIQ_CORR_COEFF_67_B0                          |
|       02A660h 4       BB_TXIQ_CORR_COEFF_89_B0                          |
|       02A664h 4       BB_TXIQ_CORR_COEFF_AB_B0                          |
|       02A668h 4       BB_TXIQ_CORR_COEFF_CD_B0                          |
|       02A66Ch 4       BB_TXIQ_CORR_COEFF_EF_B0                          |
|       02A670h 4       BB_CAL_RXBB_GAIN_TBL_0                            |
|       02A674h 4       BB_CAL_RXBB_GAIN_TBL_4                            |
|       02A678h 4       BB_CAL_RXBB_GAIN_TBL_8                            |
|       02A67Ch 4       BB_CAL_RXBB_GAIN_TBL_12                           |
|       02A680h 4       BB_CAL_RXBB_GAIN_TBL_16                           |
|       02A684h 4       BB_CAL_RXBB_GAIN_TBL_20                           |
|       02A688h 4       BB_CAL_RXBB_GAIN_TBL_24                           |
|       02A68Ch 4       BB_TXIQCAL_STATUS_B0                              |
|       02A690h 4       BB_PAPRD_TRAINER_CNTL1                            |
|       02A694h 4       BB_PAPRD_TRAINER_CNTL2                            |
|       02A698h 4       BB_PAPRD_TRAINER_CNTL3                            |
|       02A69Ch 4       BB_PAPRD_TRAINER_CNTL4                            |
|       02A6A0h 4       BB_PAPRD_TRAINER_STAT1                            |
|       02A6A4h 4       BB_PAPRD_TRAINER_STAT2                            |
|       02A6A8h 4       BB_PAPRD_TRAINER_STAT3                            |
|       02A6ACh 1x276   PAD__13                                           |
|       02A7C0h 4       BB_WATCHDOG_STATUS                                |
|       02A7C4h 4       BB_WATCHDOG_CTRL_1                                |
|       02A7C8h 4       BB_WATCHDOG_CTRL_2                                |
|       02A7CCh 4       BB_BLUETOOTH_CNTL                                 |
|       02A7D0h 4       BB_PHYONLY_WARM_RESET                             |
|       02A7D4h 4       BB_PHYONLY_CONTROL                                |
|       02A7D8h 1x4     PAD__14                                           |
|       02A7DCh 4       BB_ECO_CTRL                                       |
|       02A7E0h 1x16    PAD__15                                           |
|       02A7F0h 4       BB_TABLES_INTF_ADDR_B0                            |
|       02A7F4h 4       BB_TABLES_INTF_DATA_B0                            |
+-------------------------------------------------------------------------+
```


### bb_reg.h (6) - bb_chn1_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02A800h 1x48    PAD__0                                          |
|       02A830h 4       BB_EXT_CHAN_PWR_THR_2_B1                        |
|       02A834h 1x116   PAD__1                                          |
|       02A8A8h 4       BB_SPUR_REPORT_B1                               |
|       02A8ACh 1x20    PAD__2                                          |
|       02A8C0h 4       BB_IQ_ADC_MEAS_0_B1                             |
|       02A8C4h 4       BB_IQ_ADC_MEAS_1_B1                             |
|       02A8C8h 4       BB_IQ_ADC_MEAS_2_B1                             |
|       02A8CCh 4       BB_IQ_ADC_MEAS_3_B1                             |
|       02A8D0h 4       BB_TX_PHASE_RAMP_B1                             |
|       02A8D4h 4       BB_ADC_GAIN_DC_CORR_B1                          |
|       02A8D8h 1x4     PAD__3                                          |
|       02A8DCh 4       BB_RX_IQ_CORR_B1                                |
|       02A8E0h 1x16    PAD__4                                          |
|       02A8F0h 4       BB_PAPRD_CTRL0_B1                               |
|       02A8F4h 4       BB_PAPRD_CTRL1_B1                               |
|       02A8F8h 4       BB_PA_GAIN123_B1                                |
|       02A8FCh 4       BB_PA_GAIN45_B1                                 |
|       02A900h 4       BB_PAPRD_PRE_POST_SCALE_0_B1                    |
|       02A904h 4       BB_PAPRD_PRE_POST_SCALE_1_B1                    |
|       02A908h 4       BB_PAPRD_PRE_POST_SCALE_2_B1                    |
|       02A90Ch 4       BB_PAPRD_PRE_POST_SCALE_3_B1                    |
|       02A910h 4       BB_PAPRD_PRE_POST_SCALE_4_B1                    |
|       02A914h 4       BB_PAPRD_PRE_POST_SCALE_5_B1                    |
|       02A918h 4       BB_PAPRD_PRE_POST_SCALE_6_B1                    |
|       02A91Ch 4       BB_PAPRD_PRE_POST_SCALE_7_B1                    |
|       02A920h 4x120   BB_PAPRD_MEM_TAB_B1[0..119]                     |
|       02AB00h 4x60    BB_CHAN_INFO_CHAN_TAB_B1[0..59]                 |
|       02ABF0h 4       BB_CHN1_TABLES_INTF_ADDR                        |
|       02ABF4h 4       BB_CHN1_TABLES_INTF_DATA                        |
+-----------------------------------------------------------------------+
```


### bb_reg.h (7) - bb_agc1_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02AE00h 1x4     PAD__0                                          |
|       02AE04h 4       BB_GAIN_FORCE_MAX_GAINS_B1                      |
|       02AE08h 1x16    PAD__1                                          |
|       02AE18h 4       BB_EXT_ATTEN_SWITCH_CTL_B1                      |
|       02AE1Ch 4       BB_CCA_B1                                       |
|       02AE20h 4       BB_CCA_CTRL_2_B1                                |
|       02AE24h 1x348   PAD__2                                          |
|       02AF80h 4       BB_RSSI_B1                                      |
|       02AF84h 4       BB_SPUR_EST_CCK_REPORT_B1                       |
|       02AF88h 4       BB_AGC_DIG_DC_STATUS_I_B1                       |
|       02AF8Ch 4       BB_AGC_DIG_DC_STATUS_Q_B1                       |
|       02AF90h 4       BB_DC_CAL_STATUS_B1                             |
|       02AF94h 1x108   PAD__3                                          |
|       02B000h 4x128   BB_RX_OCGAIN2[0..127]                           |
+-----------------------------------------------------------------------+
```


### bb_reg.h (8) - bb_sm1_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02B200h 1x132   PAD__0                                          |
|       02B284h 4       BB_SWITCH_TABLE_CHN_B1                          |
|       02B288h 1x72    PAD__1                                          |
|       02B2D0h 4       BB_FCAL_2_B1                                    |
|       02B2D4h 4       BB_DFT_TONE_CTRL_B1                             |
|       02B2D8h 1x4     PAD__2                                          |
|       02B2DCh 4       BB_CL_MAP_0_B1                                  |
|       02B2E0h 4       BB_CL_MAP_1_B1                                  |
|       02B2E4h 4       BB_CL_MAP_2_B1                                  |
|       02B2E8h 4       BB_CL_MAP_3_B1                                  |
|       02B2ECh 4       BB_CL_MAP_PAL_0_B1                              |
|       02B2F0h 4       BB_CL_MAP_PAL_1_B1                              |
|       02B2F4h 4       BB_CL_MAP_PAL_2_B1                              |
|       02B2F8h 4       BB_CL_MAP_PAL_3_B1                              |
|       02B2FCh 1x4     PAD__3                                          |
|       02B300h 4x16    BB_CL_TAB_B1[0..15]                             |
|       02B340h 1x64    PAD__4                                          |
|       02B380h 4       BB_CHAN_INFO_GAIN_B1                            |
|       02B384h 1x128   PAD__5                                          |
|       02B404h 4       BB_TPC_4_B1                                     |
|       02B408h 4       BB_TPC_5_B1                                     |
|       02B40Ch 4       BB_TPC_6_B1                                     |
|       02B410h 1x16    PAD__6                                          |
|       02B420h 4       BB_TPC_11_B1                                    |
|       02B424h 1x28    PAD__7                                          |
|       02B440h 4       BB_TPC_19_B1                                    |
|       02B444h 1x60    PAD__8                                          |
|       02B480h 4x32    BB_PDADC_TAB_B1[0..31]                          |
|       02B500h 1x132   PAD__9                                          |
|       02B584h 4       BB_RTT_TABLE_SW_INTF_B1                         |
|       02B588h 4       BB_RTT_TABLE_SW_INTF_1_B1                       |
|       02B58Ch 1x196   PAD__10                                         |
|       02B650h 4       BB_TXIQ_CORR_COEFF_01_B1                        |
|       02B654h 4       BB_TXIQ_CORR_COEFF_23_B1                        |
|       02B658h 4       BB_TXIQ_CORR_COEFF_45_B1                        |
|       02B65Ch 4       BB_TXIQ_CORR_COEFF_67_B1                        |
|       02B660h 4       BB_TXIQ_CORR_COEFF_89_B1                        |
|       02B664h 4       BB_TXIQ_CORR_COEFF_AB_B1                        |
|       02B668h 4       BB_TXIQ_CORR_COEFF_CD_B1                        |
|       02B66Ch 4       BB_TXIQ_CORR_COEFF_EF_B1                        |
|       02B670h 1x28    PAD__11                                         |
|       02B68Ch 4       BB_TXIQCAL_STATUS_B1                            |
|       02B690h 1x352   PAD__12                                         |
|       02B7F0h 4       BB_TABLES_INTF_ADDR_B1                          |
|       02B7F4h 4       BB_TABLES_INTF_DATA_B1                          |
+-----------------------------------------------------------------------+
```


### bb_reg.h (9) - bb_chn3_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02C800h 4x256   BB_DUMMY1[0..255]                               |
+-----------------------------------------------------------------------+
```


### bb_reg.h (10) - bb_agc3_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02CE00h 4       BB_DUMMY                                        |
|       02CE04h 1x380   PAD__0                                          |
|       02CF80h 4       BB_RSSI_B3                                      |
+-----------------------------------------------------------------------+
```


### bb_reg.h (11) - bb_sm3_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02D200h 4x384   BB_DUMMY2[0..383]                               |
+-----------------------------------------------------------------------+
```


### bb_reg.h (12) - mit_local_reg_map, aka bb_mit_reg_map (hw6.0)

```
+-----------------------------------------------------------------------+
|       02D800h 4       BB_MIT_RF_CNTL                                  |
|       02D804h 4       BB_MIT_CCA_CNTL                                 |
|       02D808h 4       BB_MIT_RSSI_CNTL_1                              |
|       02D80Ch 4       BB_MIT_RSSI_CNTL_2                              |
|       02D810h 4       BB_MIT_TX_CNTL                                  |
|       02D814h 4       BB_MIT_RX_CNTL                                  |
|       02D818h 4       BB_MIT_OUT_CNTL                                 |
|       02D81Ch 4       BB_MIT_SPARE_CNTL                               |
+-----------------------------------------------------------------------+
```


### wmac_pcu_reg.h (2) (hw6.0)

```
+-----------------------------------------------------------------------+
|       02E000h 4x2048  MAC_PCU_BUF[0..2047]                            |
+-----------------------------------------------------------------------+
```


### efuse_wlan_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       030000h 4       EFUSE_WR_ENABLE_REG                             |
|       030004h 4       EFUSE_INT_ENABLE_REG                            |
|       030008h 4       EFUSE_INT_STATUS_REG                            |
|       03000Ch 4       BITMASK_WR_REG                                  |
|       030010h 4       VDDQ_SETTLE_TIME_REG                            |
|       030014h 4       VDDQ_HOLD_TIME_REG                              |
|       030018h 4       RD_STROBE_PW_REG                                |
|       03001Ch 4       PG_STROBE_PW_REG                                |
|       030020h 4       PGENB_SETUP_HOLD_TIME_REG                       |
|       030024h 4       STROBE_PULSE_INTERVAL_REG                       |
|       030028h 4       CSB_ADDR_LOAD_SETUP_HOLD_REG                    |
|       03002Ch 1x2004  PAD0                                            |
|       030800h 4x512   EFUSE_INTF0[0..511]                             |
|       031000h 4x512   EFUSE_INTF1[0..511]                             |
+-----------------------------------------------------------------------+
```


### stereo_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       034000h 4       STEREO0_CONFIG              ;\Stereo 0          
|       034004h 4       STEREO0_VOLUME              ;/                  |
|       034008h 4       STEREO_MASTER_CLOCK         ;-Stereo Master     |
|       03400Ch 4       STEREO0_TX_SAMPLE_CNT_LSB   ;\                  
|       034010h 4       STEREO0_TX_SAMPLE_CNT_MSB   ; Stereo 0          |
|       034014h 4       STEREO0_RX_SAMPLE_CNT_LSB   ;                   |
|       034018h 4       STEREO0_RX_SAMPLE_CNT_MSB   ;/                  |
+-----------------------------------------------------------------------+
```


### chk_sum_seg_acc_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       035000h 4       CHKSUM_ACC_DMATX_CONTROL0                       |
|       035004h 4       CHKSUM_ACC_DMATX_CONTROL1                       |
|       035008h 4       CHKSUM_ACC_DMATX_CONTROL2                       |
|       03500Ch 4       CHKSUM_ACC_DMATX_CONTROL3                       |
|       035010h 4       CHKSUM_ACC_DMATX_DESC0                          |
|       035014h 4       CHKSUM_ACC_DMATX_DESC1                          |
|       035018h 4       CHKSUM_ACC_DMATX_DESC2                          |
|       03501Ch 4       CHKSUM_ACC_DMATX_DESC3                          |
|       035020h 4       CHKSUM_ACC_DMATX_DESC_STATUS                    |
|       035024h 4       CHKSUM_ACC_DMATX_ARB_CFG                        |
|       035028h 4       CHKSUM_ACC_RR_PKTCNT01                          |
|       03502Ch 4       CHKSUM_ACC_RR_PKTCNT23                          |
|       035030h 4       CHKSUM_ACC_TXST_PKTCNT                          |
|       035034h 4       CHKSUM_ACC_DMARX_CONTROL                        |
|       035038h 4       CHKSUM_ACC_DMARX_DESC                           |
|       03503Ch 4       CHKSUM_ACC_DMARX_DESC_STATUS                    |
|       035040h 4       CHKSUM_ACC_INTR                                 |
|       035044h 4       CHKSUM_ACC_IMASK                                |
|       035048h 4       CHKSUM_ACC_ARB_BURST                            |
|       03504Ch 1x4     PAD__0                                          |
|       035050h 4       CHKSUM_ACC_RESET_DMA                            |
|       035054h 4       CHKSUM_CONFIG                                   |
+-----------------------------------------------------------------------+
```


### mmac_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       038000h 4       RX_FRAME0                                       |
|       038004h 4       RX_FRAME_0                                      |
|       038008h 4       RX_FRAME1                                       |
|       03800Ch 4       RX_FRAME_1                                      |
|       038010h 4       MMAC_INTERRUPT_RAW                              |
|       038014h 4       MMAC_INTERRUPT_EN                               |
|       038018h 4       RX_PARAM1                                       |
|       03801Ch 4       RX_PARAM0                                       |
|       038020h 4       TX_COMMAND0                                     |
|       038024h 4       TX_COMMAND                                      |
|       038028h 4       TX_PARAM                                        |
|       03802Ch 4       BEACON_PARAM                                    |
|       038030h 4       BEACON                                          |
|       038034h 4       TSF_L                                           |
|       038038h 4       TSF_U                                           |
+-----------------------------------------------------------------------+
```


### fpga_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       039000h 4       FPGA_REG1                                       |
|       039004h 4       FPGA_REG2                                       |
|       039008h 4       FPGA_REG4                                       |
+-----------------------------------------------------------------------+
```


### bridge_intr_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       040000h 4       INTERRUPT                                       |
|       040004h 4       INTERRUPT_MASK                                  |
+-----------------------------------------------------------------------+
```


### mii_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       040100h 4       MII0_CNTL                                       |
|       040104h 4       STAT_CNTL                                       |
+-----------------------------------------------------------------------+
```


### mdio_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       040200h 4x8     MDIO_REG[0..7]                                  |
|       040220h 4       MDIO_ISR                                        |
|       040224h 4       PHY_ADDR                                        |
+-----------------------------------------------------------------------+
```


### bridge_chain_gmac_0_rx_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       040800h 4       GMAC_RX_0_DESC_START_ADDRESS                    |
|       040804h 4       GMAC_RX_0_DMA_START                             |
|       040808h 4       GMAC_RX_0_BURST_SIZE                            |
|       04080Ch 4       GMAC_RX_0_PKT_OFFSET                            |
|       040810h 4       GMAC_RX_0_CHECKSUM                              |
|       040814h 4       GMAC_RX_0_DBG_RX                                |
|       040818h 4       GMAC_RX_0_DBG_RX_CUR_ADDR                       |
|       04081Ch 4       GMAC_RX_0_DATA_SWAP                             |
+-----------------------------------------------------------------------+
```


### bridge_chain_gmac_0_tx_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       040C00h 4       GMAC_TX_0_DESC_START_ADDRESS                    |
|       040C04h 4       GMAC_TX_0_DMA_START                             |
|       040C08h 4       GMAC_TX_0_INTERRUPT_LIMIT                       |
|       040C0Ch 4       GMAC_TX_0_BURST_SIZE                            |
|       040C10h 4       GMAC_TX_0_DBG_TX                                |
|       040C14h 4       GMAC_TX_0_DBG_TX_CUR_ADDR                       |
|       040C18h 4       GMAC_TX_0_DATA_SWAP                             |
+-----------------------------------------------------------------------+
```


### usb_cast_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       054000h 4       ENDP0                                           |
|       054004h 1x4     PAD0                                            |
|       054008h 4       OUT1ENDP                                        |
|       05400Ch 4       IN1ENDP                                         |
|       054010h 4       OUT2ENDP                                        |
|       054014h 4       IN2ENDP                                         |
|       054018h 4       OUT3ENDP                                        |
|       05401Ch 4       IN3ENDP                                         |
|       054020h 4       OUT4ENDP                                        |
|       054024h 4       IN4ENDP                                         |
|       054028h 4       OUT5ENDP                                        |
|       05402Ch 4       IN5ENDP                                         |
|       054030h 1x92    PAD1                                            |
|       05408Ch 4       USBMODESTATUS                                   |
|       054090h 1x248   PAD2                                            |
|       054188h 4       EPIRQ                                           |
|       05418Ch 4       USBIRQ                                          |
|       054190h 1x4     PAD3                                            |
|       054194h 4       EPIEN                                           |
|       054198h 4       PIEN                                            |
|       05419Ch 1x8     PAD4                                            |
|       0541A4h 4       FNCTRL                                          |
|       0541A8h 1x20    PAD5                                            |
|       0541BCh 4       OTGREG                                          |
|       0541C0h 1x12    PAD6                                            |
|       0541CCh 4       DMASTART                                        |
|       0541D0h 4       DMASTOP                                         |
|       0541D4h 1x556   PAD7                                            |
|       054400h 4       EP0DMAADDR                                      |
|       054404h 1x28    PAD8                                            |
|       054420h 4       EP1DMAADDR                                      |
|       054424h 1x8     PAD9                                            |
|       05442Ch 4       OUT1DMACTRL                                     |
|       054430h 1x16    PAD10                                           |
|       054440h 4       EP2DMAADDR                                      |
|       054444h 1x8     PAD11                                           |
|       05444Ch 4       OUT2DMACTRL                                     |
|       054450h 1x16    PAD12                                           |
|       054460h 4       EP3DMAADDR                                      |
|       054464h 1x8     PAD13                                           |
|       05446Ch 4       OUT3DMACTRL                                     |
|       054470h 1x16    PAD14                                           |
|       054480h 4       EP4DMAADDR                                      |
|       054484h 1x8     PAD15                                           |
|       05448Ch 4       OUT4DMACTRL                                     |
|       054490h 1x16    PAD16                                           |
|       0544A0h 4       EP5DMAADDR                                      |
|       0544A4h 1x8     PAD17                                           |
|       0544ACh 4       OUT5DMACTRL                                     |
|       0544B0h 1x539472 PAD18            ;pad to BASE + 84000h         |
|       0D8000h 4       USB_IP_BASE                                     |
+-----------------------------------------------------------------------+
```


### rdma_reg.h (formerly at 00030100h in hw4.0) (hw6.0)

```
+-----------------------------------------------------------------------+
|       054D00h 4       DMA_CONFIG                                      |
|       054D04h 4       DMA_CONTROL                                     |
|       054D08h 4       DMA_SRC                                         |
|       054D0Ch 4       DMA_DEST                                        |
|       054D10h 4       DMA_LENGTH                                      |
|       054D14h 4       VMC_BASE                                        |
|       054D18h 4       INDIRECT_REG                                    |
|       054D1Ch 4       INDIRECT_RETURN                                 |
|       054D20h 4x16    RDMA_REGION_(0..15)_                            |
|       054DA0h 4       DMA_STATUS                                      |
|       054DA4h 4       DMA_INT_EN                                      |
+-----------------------------------------------------------------------+
```


### athrI2cSlaveApbCsr.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       054E00h 4       I2CFIFOCONTROL                                  |
|       054E04h 4       I2CFIFOREADPTR                                  |
|       054E08h 4       I2CFIFOREADUPDATE                               |
|       054E0Ch 4       I2CFIFOREADBASEADDR                             |
|       054E10h 4       I2CFIFOWRITEPTR                                 |
|       054E14h 4       I2CFIFOWRITEUPDATE                              |
|       054E18h 4       I2CFIFOWRITEBASEADDR                            |
|       054E1Ch 4       I2CMEMCONTROL                                   |
|       054E20h 4       I2CMEMBASEADDR                                  |
|       054E24h 4       I2CREGREADDATA                                  |
|       054E28h 4       I2CREGWRITEDATA                                 |
|       054E2Ch 4       I2CREGCONTROL                                   |
|       054E30h 4       I2CCSRREADDATA                                  |
|       054E34h 4       I2CCSRWRITEDATA                                 |
|       054E38h 4       I2CCSRCONTROL                                   |
|       054E3Ch 4       I2CFILTERSIZE                                   |
|       054E40h 4       I2CADDR                                         |
|       054E44h 4       I2CINT                                          |
|       054E48h 4       I2CINTEN                                        |
|       054E4Ch 4       I2CINTCSR                                       |
+-----------------------------------------------------------------------+
```


### mbox_i2s_reg.h (hw6.0)

```
+--------------------------------------------------------------------------+
|       055000h 4x1     MBOX_FIFO    ;<-- defined as array of ONE word (?) |
|       055004h 4       MBOX_FIFO_STATUS                                   |
|       055008h 4       MBOX_DMA_POLICY                                    |
|       05500Ch 4       MBOX0_DMA_RX_DESCRIPTOR_BASE                       |
|       055010h 4       MBOX0_DMA_RX_CONTROL                               |
|       055014h 4       MBOX0_DMA_TX_DESCRIPTOR_BASE                       |
|       055018h 4       MBOX0_DMA_TX_CONTROL                               |
|       05501Ch 4       MBOX_FRAME                                         |
|       055020h 4       FIFO_TIMEOUT                                       |
|       055024h 4       MBOX_INT_STATUS                                    |
|       055028h 4       MBOX_INT_ENABLE                                    |
|       05502Ch 4       MBOX_FIFO_RESET                                    |
|       055030h 4       MBOX_DEBUG_CHAIN0                                  |
|       055034h 4       MBOX_DEBUG_CHAIN1                                  |
|       055038h 4       MBOX_DEBUG_CHAIN0_SIGNALS                          |
|       05503Ch 4       MBOX_DEBUG_CHAIN1_SIGNALS                          |
+--------------------------------------------------------------------------+
```


### map_rf_reg.h (hw6.0)

```
+------------------------------------------------------------------------+
|       xxx000h 4x256   RAM1[0..255]                                     |
|       xxx400h 4x12    INT_PENDING[0..11]                               |
|       xxx430h 4       BB_WR_MASK_0                ;\                   
|       xxx434h 4       BB_WR_MASK_1                ; BB Write Mask 0..3 |
|       xxx438h 4       BB_WR_MASK_2                ;                    |
|       xxx43Ch 4       BB_WR_MASK_3                ;/                   |
|       xxx440h 4       RF_WR_MASK_0                ;\RF Write Mask 0..1 
|       xxx444h 4       RF_WR_MASK_1                ;/                   |
|       xxx448h 4       BB_RD_MASK_0                ;\                   
|       xxx44Ch 4       BB_RD_MASK_1                ; BB Read Mask 0..3  |
|       xxx450h 4       BB_RD_MASK_2                ;                    |
|       xxx454h 4       BB_RD_MASK_3                ;/                   |
|       xxx458h 4       RF_RD_MASK_0                ;\RF Read Mask 0..1  
|       xxx45Ch 4       RF_RD_MASK_1                ;/                   |
|       xxx460h 4       INT_SRC                                          |
|       xxx464h 1x924   PAD__0                                           |
|       xxx800h 4x128   RAM2[0..127]                                     |
+------------------------------------------------------------------------+
```


### odin_reg.h (hw6.0)

```
+-----------------------------------------------------------------------+
|       xxx000h 4       PHY_CTRL0                                       |
|       xxx004h 4       PHY_CTRL1                                       |
|       xxx008h 4       PHY_CTRL2                                       |
|       xxx00Ch 4       PHY_CTRL3                                       |
|       xxx010h 4       PHY_CTRL4                                       |
|       xxx014h 4       PHY_CTRL5                                       |
|       xxx018h 4       PHY_CTRL6                                       |
|       xxx01Ch 4       PHY_STATUS                                      |
+-----------------------------------------------------------------------+
```





