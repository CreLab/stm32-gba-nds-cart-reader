# DSi Atheros Wifi - Internal I/O Map Summary (hw4)


### Overall Summary (hw4.0)

```
+----------------------------------------------------------------------------------+
|       004000h 2E8h    (rtc_wlan_reg.h)                                           |
|       008000h 630h    Memory Controller (BCAM) (vmc_wlan_reg.h)                  |
|       00C000h 14h     (uart_reg.h)                                               |
|       00D000h ..      DBG_UART_BASE_ADDRESS  ;another UART, as above, for debug? |
|       00E000h 38h     (umbox_wlan_reg.h)                                         |
|       010000h 18h     (si_reg.h)                                                 |
|       014000h BCh     (gpio_athr_wlan_reg.h)                                     |
|       018000h 12Ch    (mbox_wlan_reg.h)                                          |
|       01A000h 20000h  WLAN_HOST_IF_WINDOW (mbox_wlan_reg.h)                      |
|       01C000h 748h    (analog_intf_athr_wlan_reg.h)                              |
|       020000h DCh     WMAC DMA and IRQ   (mac_dma_reg.h)                         |
|       020800h 244h    WMAC QCU Queue     (mac_dma_reg.h)                         |
|       021000h 274h    WMAC DCU           (mac_dma_reg.h)                         |
|       028000h C00h    MAC_PCU            (mac_pcu_reg.h)                         |
|       029800h 800h    MAC_PCU_BASEBAND_0 (bb_lc_reg.h)                           |
|       02A000h 1210h   MAC_PCU_BASEBAND_1 (bb_lc_reg.h)                           |
|       02C000h 1000h   MAC_PCU_BASEBAND_2 (mac_pcu_reg.h)                         |
|       02D000h 1000h   MAC_PCU_BASEBAND_3 (mac_pcu_reg.h)                         |
|       02E000h 800h    MAC_PCU_BUF        (mac_pcu_reg.h)                         |
|       030100h 68h     (rdma_reg.h)                                               |
|       031000h 1000h   (efuse_reg.h)                                              |
+----------------------------------------------------------------------------------+
```


### rtc_wlan_reg.h (hw4.0)

```
+---------------------------------------------------------------------------------+
|       004000h 4       WLAN_RESET_CONTROL                                        |
|       004004h 4       WLAN_XTAL_CONTROL                                         |
|       004008h 4       WLAN_TCXO_DETECT                                          |
|       00400Ch 4       WLAN_XTAL_TEST                                            |
|       004010h 4       WLAN_QUADRATURE                                           |
|       004014h 4       WLAN_PLL_CONTROL                                          |
|       004018h 4       WLAN_PLL_SETTLE                                           |
|       00401Ch 4       WLAN_XTAL_SETTLE                                          |
|       004020h 4       WLAN_CPU_CLOCK                                            |
|       004024h 4       WLAN_CLOCK_OUT                                            |
|       004028h 4       WLAN_CLOCK_CONTROL                                        |
|       00402Ch 4       WLAN_BIAS_OVERRIDE                                        |
|       004030h 4       WLAN_WDT_CONTROL            ;\                            
|       004034h 4       WLAN_WDT_STATUS             ;                             |
|       004038h 4       WLAN_WDT                    ; Watchdog Timer              |
|       00403Ch 4       WLAN_WDT_COUNT              ;                             |
|       004040h 4       WLAN_WDT_RESET              ;/                            |
|       004044h 4       WLAN_INT_STATUS             ;-Interrupt Status            |
|       004048h 4       WLAN_LF_TIMER0              ;\                            
|       00404Ch 4       WLAN_LF_TIMER_COUNT0        ; Low-Freq Timer 0            |
|       004050h 4       WLAN_LF_TIMER_CONTROL0      ;                             |
|       004054h 4       WLAN_LF_TIMER_STATUS0       ;/                            |
|       004058h 4       WLAN_LF_TIMER1              ;\                            
|       00405Ch 4       WLAN_LF_TIMER_COUNT1        ; Low-Freq Timer 1            |
|       004060h 4       WLAN_LF_TIMER_CONTROL1      ;                             |
|       004064h 4       WLAN_LF_TIMER_STATUS1       ;/                            |
|       004068h 4       WLAN_LF_TIMER2              ;\                            
|       00406Ch 4       WLAN_LF_TIMER_COUNT2        ; Low-Freq Timer 2            |
|       004070h 4       WLAN_LF_TIMER_CONTROL2      ;                             |
|       004074h 4       WLAN_LF_TIMER_STATUS2       ;/                            |
|       004078h 4       WLAN_LF_TIMER3              ;\                            
|       00407Ch 4       WLAN_LF_TIMER_COUNT3        ; Low-Freq Timer 3            |
|       004080h 4       WLAN_LF_TIMER_CONTROL3      ;                             |
|       004084h 4       WLAN_LF_TIMER_STATUS3       ;/                            |
|       004088h 4       WLAN_HF_TIMER               ;\                            
|       00408Ch 4       WLAN_HF_TIMER_COUNT         ; High-Freq Timer             |
|       004090h 4       WLAN_HF_LF_COUNT      ;<--  ;                             |
|       004094h 4       WLAN_HF_TIMER_CONTROL       ;                             |
|       004098h 4       WLAN_HF_TIMER_STATUS        ;/                            |
|       00409Ch 4       WLAN_RTC_CONTROL            ;\                            
|       0040A0h 4       WLAN_RTC_TIME               ;                             |
|       0040A4h 4       WLAN_RTC_DATE               ;                             |
|       0040A8h 4       WLAN_RTC_SET_TIME           ; Real-Time Clock             |
|       0040ACh 4       WLAN_RTC_SET_DATE           ;                             |
|       0040B0h 4       WLAN_RTC_SET_ALARM          ;                             |
|       0040B4h 4       WLAN_RTC_CONFIG             ;                             |
|       0040B8h 4       WLAN_RTC_ALARM_STATUS       ;/                            |
|       0040BCh 4       WLAN_UART_WAKEUP                                          |
|       0040C0h 4       WLAN_RESET_CAUSE                                          |
|       0040C4h 4       WLAN_SYSTEM_SLEEP                                         |
|       0040C8h 4       WLAN_SDIO_WRAPPER                                         |
|       0040CCh 4       WLAN_MAC_SLEEP_CONTROL                                    |
|       0040D0h 4       WLAN_KEEP_AWAKE                                           |
|       0040D4h 4       WLAN_LPO_CAL_TIME                   ;\                    
|       0040D8h 4       WLAN_LPO_INIT_DIVIDEND_INT          ;                     |
|       0040DCh 4       WLAN_LPO_INIT_DIVIDEND_FRACTION     ; LPO                 |
|       0040E0h 4       WLAN_LPO_CAL                        ;                     |
|       0040E4h 4       WLAN_LPO_CAL_TEST_CONTROL           ;                     |
|       0040E8h 4       WLAN_LPO_CAL_TEST_STATUS            ;/                    |
|       0040ECh 4       WLAN_CHIP_ID                        ;-Chip ID             |
|       0040F0h 4       WLAN_DERIVED_RTC_CLK                                      |
|       0040F4h 4       MAC_PCU_SLP32_MODE          ;\                            
|       0040F8h 4       MAC_PCU_SLP32_WAKE          ;                             |
|       0040FCh 4       MAC_PCU_SLP32_INC           ;                             |
|       004100h 4       MAC_PCU_SLP_MIB1            ;                             |
|       004104h 4       MAC_PCU_SLP_MIB2            ;                             |
|       004108h 4       MAC_PCU_SLP_MIB3            ;/                            |
|       00410Ch 4       WLAN_POWER_REG              ;\located here in hw4.0       
|       004110h 4       WLAN_CORE_CLK_CTRL          ; (other address as in hw2.0) |
|       004114h 4       WLAN_GPIO_WAKEUP_CONTROL    ;/                            |
|       (below 4118h..42E8h is new in hw4.0, didn't exist in hw2.0)               |
|       004118h 4       (WLAN_)HT                                                 |
|       00411Ch 4       MAC_PCU_TSF_L32                                           |
|       004120h 4       MAC_PCU_TSF_U32                                           |
|       004124h 4       MAC_PCU_WBTIMER                                           |
|       004128h 1x24    PAD0                                                      |
|       004140h 4x16    MAC_PCU_GENERIC_TIMERS[0..15]                             |
|       004180h 4       MAC_PCU_GENERIC_TIMERS_MODE                               |
|       004184h 1x60    PAD1                                                      |
|       0041C0h 4x16    MAC_PCU_GENERIC_TIMERS2[0..15]                            |
|       004200h 4       MAC_PCU_GENERIC_TIMERS_MODE2                              |
|       004204h 4       MAC_PCU_SLP1                                              |
|       004208h 4       MAC_PCU_SLP2                                              |
|       00420Ch 4       MAC_PCU_RESET_TSF                                         |
|       004210h 4       MAC_PCU_TSF_ADD_PLL                                       |
|       004214h 4       SLEEP_RETENTION                                           |
|       004218h 4       BTCOEXCTRL                          ;\                    
|       00421Ch 4       WBSYNC_PRIORITY1                    ;                     |
|       004220h 4       WBSYNC_PRIORITY2                    ;                     |
|       004224h 4       WBSYNC_PRIORITY3                    ;                     |
|       004228h 4       BTCOEX0  ;SYNC_DUR                  ;                     |
|       00422Ch 4       BTCOEX1  ;CLK_THRES                 ;                     |
|       004230h 4       BTCOEX2  ;FRAME_THRES               ; Bluetooth           |
|       004234h 4       BTCOEX3  ;CLK_CNT                   ; Coexistance         |
|       004238h 4       BTCOEX4  ;FRAME_CNT                 ;                     |
|       00423Ch 4       BTCOEX5  ;IDLE_CNT                  ;                     |
|       004240h 4       BTCOEX6  ;IDLE_RESET_LVL_BITMAP     ;                     |
|       004244h 4       LOCK                                ;                     |
|       004248h 4       NOLOCK_PRIORITY                     ;                     |
|       00424Ch 4       WBSYNC                              ;                     |
|       004250h 4       WBSYNC1                             ;                     |
|       004254h 4       WBSYNC2                             ;                     |
|       004258h 4       WBSYNC3                             ;                     |
|       00425Ch 4       WB_TIMER_TARGET                     ;                     |
|       004260h 4       WB_TIMER_SLOP                       ;                     |
|       004264h 4       BTCOEX_INT_EN                       ;                     |
|       004268h 4       BTCOEX_INT_STAT                     ;                     |
|       00426Ch 4       BTPRIORITY_INT_EN                   ;                     |
|       004270h 4       BTPRIORITY_INT_STAT                 ;                     |
|       004274h 4       BTPRIORITY_STOMP_INT_EN             ;                     |
|       004278h 4       BTPRIORITY_STOMP_INT_STAT           ;/                    |
|       00427Ch 4       MAC_PCU_BMISS_TIMEOUT                                     |
|       004280h 4       MAC_PCU_CAB_AWAKE                                         |
|       004284h 4       LP_PERF_COUNTER                                           |
|       004288h 4       LP_PERF_LIGHT_SLEEP                                       |
|       00428Ch 4       LP_PERF_DEEP_SLEEP                                        |
|       004290h 4       LP_PERF_ON                                                |
|       004294h 4       ST_64_BIT                           ;\                    
|       004298h 4       MESSAGE_WR                          ; also Bluetooth Coex |
|       00429Ch 4       MESSAGE_WR_P                        ; related? (sorted as |
|       0042A0h 4       MESSAGE_RD                          ; so in hw6 files)    |
|       0042A4h 4       MESSAGE_RD_P                        ;/                    |
|       0042A8h 4       CHIP_MODE                                                 |
|       0042ACh 4       CLK_REQ_FALL_EDGE                                         |
|       0042B0h 4       OTP                                                       |
|       0042B4h 4       OTP_STATUS                                                |
|       0042B8h 4       PMU                                                       |
|       0042BCh 1x4     PAD2                                                      |
|       0042C0h 4x2     PMU_CONFIG[0..1]                                          |
|       0042C8h 4       PMU_BYPASS                                                |
|       0042CCh 4       MAC_PCU_TSF2_L32                                          |
|       0042D0h 4       MAC_PCU_TSF2_U32                                          |
|       0042D4h 4       MAC_PCU_GENERIC_TIMERS_MODE3                              |
|       0042D8h 4       MAC_PCU_DIRECT_CONNECT                                    |
|       0042DCh 4       THERM_CTRL1                                               |
|       0042E0h 4       THERM_CTRL2                                               |
|       0042E4h 4       THERM_CTRL3                                               |
|       0042E8h -       unused/unspecified                                        |
+---------------------------------------------------------------------------------+
```


### vmc_wlan_reg.h (hw4.0)

```
+-------------------------------------------------------------------------+
|       008000h 4x128   WLAN_MC_BCAM_VALID[0..127]          ;\            
|       008200h 4x128   WLAN_MC_BCAM_COMPARE[0..127]        ; ROM Patches |
|       008400h 4x128   WLAN_MC_BCAM_TARGET[0..127]         ;/            |
|       008600h 4       WLAN_APB_ADDR_ERROR_CONTROL         ;\            
|       008604h 4       WLAN_APB_ADDR_ERROR_STATUS          ; ADDR_ERROR  |
|       008608h 4       WLAN_AHB_ADDR_ERROR_CONTROL         ;             |
|       00860Ch 4       WLAN_AHB_ADDR_ERROR_STATUS          ;/            |
|       008610h 4       WLAN_BCAM_CONFLICT_ERROR                          |
|       008614h 4       WLAN_CPU_PERF_CNT                                 |
|       008618h 4       WLAN_CPU_INST_FETCH                               |
|       00861Ch 4       WLAN_CPU_DATA_FETCH                               |
|       008620h 4       WLAN_CPU_RAM1_CONFLICT                            |
|       008624h 4       WLAN_CPU_RAM2_CONFLICT                            |
|       008628h 4       WLAN_CPU_RAM3_CONFLICT                            |
|       00862Ch 4       WLAN_CPU_RAM4_CONFLICT                            |
|       008630h -       unused/unspecified                                |
+-------------------------------------------------------------------------+
```


### uart_reg.h (hw4.0)

```
+----------------------------------------------------------------------------------+
|       00C000h 4       UART_DATA                                                  |
|       00C004h 4       UART_CONTROL                                               |
|       00C008h 4       UART_CLKDIV                                                |
|       00C00Ch 4       UART_INT                                                   |
|       00C010h 4       UART_INT_EN                                                |
|       00C014h -       unused/unspecified                                         |
|       00D000h ..      DBG_UART_BASE_ADDRESS  ;another UART, as above, for debug? |
|       00Dxxxh -       unused/unspecified                                         |
+----------------------------------------------------------------------------------+
```


### umbox_wlan_reg.h (hw4.0)

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
|       00E038h -       unused/unspecified                              |
+-----------------------------------------------------------------------+
```


### si_reg.h (hw4.0)

```
+-----------------------------------------------------------------------+
|       010000h 4       SI_CONFIG                                       |
|       010004h 4       SI_CS                                           |
|       010008h 4       SI_TX_DATA0                                     |
|       01000Ch 4       SI_TX_DATA1                                     |
|       010010h 4       SI_RX_DATA0                                     |
|       010014h 4       SI_RX_DATA1                                     |
|       010018h -       unused/unspecified                              |
+-----------------------------------------------------------------------+
```


### gpio_athr_wlan_reg.h (hw4.0)

```
+-----------------------------------------------------------------------------------+
|       014000h 4       WLAN_GPIO_OUT            ;\GPIO Output Data                 
|       014004h 4       WLAN_GPIO_OUT_W1TS       ; (direct, and Write-1-To-Set/Clr) |
|       014008h 4       WLAN_GPIO_OUT_W1TC       ;/                                 |
|       01400Ch 4       WLAN_GPIO_ENABLE         ;\GPIO Output Enable               
|       014010h 4       WLAN_GPIO_ENABLE_W1TS    ; (direct, and Write-1-To-Set/Clr) |
|       014014h 4       WLAN_GPIO_ENABLE_W1TC    ;/                                 |
|       014018h 4       WLAN_GPIO_IN             ;-GPIO Input                       |
|       01401Ch 4       WLAN_GPIO_STATUS         ;\GPIO Interrupt Status            
|       014020h 4       WLAN_GPIO_STATUS_W1TS    ; (direct, and Write-1-To-Set/Clr) |
|       014024h 4       WLAN_GPIO_STATUS_W1TC    ;/                                 |
|       014028h 4       WLAN_GPIO_PIN0     ;GPIO0  Bluetooth coex BT_FREQUENCY      |
|       01402Ch 4       WLAN_GPIO_PIN1     ;GPIO1  Bluetooth coex WLAN_ACTIVE       |
|       014030h 4       WLAN_GPIO_PIN2     ;GPIO2  Bluetooth coex BT_ACTIVE         |
|       014034h 4       WLAN_GPIO_PIN3     ;GPIO3  Bluetooth coex BT_PRIORITY       |
|       014038h 4       WLAN_GPIO_PIN4     ;GPIO4  -                                |
|       01403Ch 4       WLAN_GPIO_PIN5     ;GPIO5  JTAG TMS input                   |
|       014040h 4       WLAN_GPIO_PIN6     ;GPIO6  JTAG TCK input                   |
|       014044h 4       WLAN_GPIO_PIN7     ;GPIO7  JTAG TDI input                   |
|       014048h 4       WLAN_GPIO_PIN8     ;GPIO8  JTAG TDO output                  |
|       01404Ch 4       WLAN_GPIO_PIN9     ;GPIO9  SDIO CMD                         |
|       014050h 4       WLAN_GPIO_PIN10    ;GPIO10 SDIO D3                          |
|       014054h 4       WLAN_GPIO_PIN11    ;GPIO11 SDIO D2                          |
|       014058h 4       WLAN_GPIO_PIN12    ;GPIO12 SDIO D1                          |
|       01405Ch 4       WLAN_GPIO_PIN13    ;GPIO13 SDIO D0                          |
|       014060h 4       WLAN_GPIO_PIN14    ;GPIO14 SDIO CLK                         |
|       014064h 4       WLAN_GPIO_PIN15    ;GPIO15 HCI UART TXD                     |
|       014068h 4       WLAN_GPIO_PIN16    ;GPIO16 HCI UART RTS                     |
|       01406Ch 4       WLAN_GPIO_PIN17    ;GPIO17 HCI UART RXD                     |
|       014070h 4       WLAN_GPIO_PIN18    ;GPIO18 HCI UART CTS                     |
|       014074h 4       WLAN_GPIO_PIN19    ;GPIO19 SDIO/GSPI interface select       |
|       014078h 4       WLAN_GPIO_PIN20    ;GPIO20 SDIO/GSPI interface select       |
|       01407Ch 4       WLAN_GPIO_PIN21    ;GPIO21 external input sleep clock       |
|       014080h 4       WLAN_GPIO_PIN22    ;GPIO22 wake on wireless input (WOW)     |
|       014084h 4       WLAN_GPIO_PIN23    ;GPIO23 reference clk output to BT chip  |
|       014088h 4       WLAN_GPIO_PIN24    ;GPIO24 request clk from BT chip         |
|       01408Ch 4       WLAN_GPIO_PIN25    ;GPIO25 request reference clk (CLK_REQ)  |
|       014090h 4       SDIO                                                        |
|       014094h 4       FUNC_BUS                                                    |
|       014098h 4       WL_SOC_APB                                                  |
|       01409Ch 4       WLAN_SIGMA_DELTA                                            |
|       0140A0h 4       WL_BOOTSTRAP                                                |
|       0140A4h 4       CLOCK_GPIO                                                  |
|       0140A8h 4       WLAN_DEBUG_CONTROL                                          |
|       0140ACh 4       WLAN_DEBUG_INPUT_SEL                                        |
|       0140B0h 4       WLAN_DEBUG_OUT                                              |
|       0140B4h 4       WLAN_RESET_TUPLE_STATUS                                     |
|       0140B8h 4       ANTENNA_SLEEP_CONTROL                                       |
|       0140BCh -       unused/unspecified                                          |
+-----------------------------------------------------------------------------------+
```


### MBOX Registers (mbox_wlan_reg.h) (hw4.0)

```
+--------------------------------------------------------------------------------+
|       018000h 4x4     WLAN_MBOX_FIFO[0..3]                                     |
|       018010h 4       WLAN_MBOX_FIFO_STATUS                                    |
|       018014h 4       WLAN_MBOX_DMA_POLICY                                     |
|       018018h 4       WLAN_MBOX0_DMA_RX_DESCRIPTOR_BASE   ;\                   
|       01801Ch 4       WLAN_MBOX0_DMA_RX_CONTROL           ; MBOX 0             |
|       018020h 4       WLAN_MBOX0_DMA_TX_DESCRIPTOR_BASE   ;                    |
|       018024h 4       WLAN_MBOX0_DMA_TX_CONTROL           ;/                   |
|       018028h 4       WLAN_MBOX1_DMA_RX_DESCRIPTOR_BASE   ;\                   
|       01802Ch 4       WLAN_MBOX1_DMA_RX_CONTROL           ; MBOX 1             |
|       018030h 4       WLAN_MBOX1_DMA_TX_DESCRIPTOR_BASE   ;                    |
|       018034h 4       WLAN_MBOX1_DMA_TX_CONTROL           ;/                   |
|       018038h 4       WLAN_MBOX2_DMA_RX_DESCRIPTOR_BASE   ;\                   
|       01803Ch 4       WLAN_MBOX2_DMA_RX_CONTROL           ; MBOX 2             |
|       018040h 4       WLAN_MBOX2_DMA_TX_DESCRIPTOR_BASE   ;                    |
|       018044h 4       WLAN_MBOX2_DMA_TX_CONTROL           ;/                   |
|       018048h 4       WLAN_MBOX3_DMA_RX_DESCRIPTOR_BASE   ;\                   
|       01804Ch 4       WLAN_MBOX3_DMA_RX_CONTROL           ; MBOX 3             |
|       018050h 4       WLAN_MBOX3_DMA_TX_DESCRIPTOR_BASE   ;                    |
|       018054h 4       WLAN_MBOX3_DMA_TX_CONTROL           ;/                   |
|       018058h 4       WLAN_MBOX_INT_STATUS                ;\Interrupt          
|       01805Ch 4       WLAN_MBOX_INT_ENABLE                ;/                   |
|       018060h 4       WLAN_INT_HOST            ;IRQ to sdio/host               |
|       018064h 1x28    PAD0                                                     |
|       018080h 4x8     WLAN_LOCAL_COUNT[0..7]        ;SDIO func1 ?              |
|       0180A0h 4x8     WLAN_COUNT_INC[0..7]          ;SDIO func1 ?              |
|       0180C0h 4x8     WLAN_LOCAL_SCRATCH[0..7]      ;SDIO func1 ?              |
|       0180E0h 4       WLAN_USE_LOCAL_BUS                                       |
|       0180E4h 4       WLAN_SDIO_CONFIG              ;SDIO func0 ?              |
|       0180E8h 4       WLAN_MBOX_DEBUG                                          |
|       0180ECh 4       WLAN_MBOX_FIFO_RESET                                     |
|       0180F0h 4x4     WLAN_MBOX_TXFIFO_POP[0..3]                               |
|       018100h 4x4     WLAN_MBOX_RXFIFO_POP[0..3]                               |
|       018110h 4       WLAN_SDIO_DEBUG                                          |
|       018114h 4       WLAN_GMBOX0_DMA_RX_DESCRIPTOR_BASE  ;\                   
|       018118h 4       WLAN_GMBOX0_DMA_RX_CONTROL          ;                    |
|       01811Ch 4       WLAN_GMBOX0_DMA_TX_DESCRIPTOR_BASE  ; new (unlike hw2.0) |
|       018120h 4       WLAN_GMBOX0_DMA_TX_CONTROL          ;                    |
|       018124h 4       WLAN_GMBOX_INT_STATUS               ;                    |
|       018128h 4       WLAN_GMBOX_INT_ENABLE               ;/                   |
|       01812Ch 1x7892  PAD1                                                     |
|       01A000h 4x2048  WLAN_HOST_IF_WINDOW[0..2047]                             |
+--------------------------------------------------------------------------------+
```


### analog_intf_athr_wlan_reg.h (hw4.0)

```
+-----------------------------------------------------------------------------+
|       01C000h 4       RXRF_BIAS1                                            |
|       01C004h 4       RXRF_BIAS2                                            |
|       01C008h 4       RXRF_GAINSTAGES                                       |
|       01C00Ch 4       RXRF_AGC                                              |
|       01C010h 1x48    PAD__0                                                |
|       01C040h 4       TXRF1                                                 |
|       01C044h 4       TXRF2                                                 |
|       01C048h 4       TXRF3                                                 |
|       01C04Ch 4       TXRF4                                                 |
|       01C050h 4       TXRF5                                                 |
|       01C054h 4       TXRF6                                                 |
|       01C058h 4       TXRF7 ;PADRVGNTAB_0..4    ;\                          
|       01C05Ch 4       TXRF8 ;PADRVGNTAB_5..9    ;                           |
|       01C060h 4       TXRF9 ;PADRVGNTAB_10..14  ;/                          |
|       01C064h 4       TXRF10                                                |
|       01C068h 4       TXRF11                                                |
|       01C06Ch 4       TXRF12                                                |
|       01C070h 1x16    PAD__1                                                |
|       01C080h 4       SYNTH1                                                |
|       01C084h 4       SYNTH2                                                |
|       01C088h 4       SYNTH3                                                |
|       01C08Ch 4       SYNTH4                                                |
|       01C090h 4       SYNTH5                                                |
|       01C094h 4       SYNTH6                                                |
|       01C098h 4       SYNTH7                                                |
|       01C09Ch 4       SYNTH8                                                |
|       01C0A0h 4       SYNTH9                                                |
|       01C0A4h 4       SYNTH10                                               |
|       01C0A8h 4       SYNTH11                                               |
|       01C0ACh 4       SYNTH12                                               |
|       01C0B0h 4       SYNTH13                                               |
|       01C0B4h 4       SYNTH14                                               |
|       01C0B8h 1x8     PAD__2                                                |
|       01C0C0h 4       BIAS1                                                 |
|       01C0C4h 4       BIAS2                                                 |
|       01C0C8h 4       BIAS3                                                 |
|       01C0CCh 4       BIAS4                                                 |
|       01C0D0h 1x48    PAD__3                                                |
|       01C100h 4       RXTX1                                                 |
|       01C104h 4       RXTX2                                                 |
|       01C108h 4       RXTX3                                                 |
|       01C10Ch 1x52    PAD__4                                                |
|       01C140h 4       BB1                                                   |
|       01C144h 4       BB2                                                   |
|       01C148h 4       BB3                                                   |
|       01C14Ch 1x308   PAD__5                                                |
|       01C280h 4       PLLCLKMODA                                            |
|       01C284h 4       PLLCLKMODA2                                           |
|       01C288h 4       TOP                                                   |
|       01C28Ch 4       THERM                                                 |
|       01C290h 4       XTAL                                                  |
|       01C294h 1x236   PAD__6                                                |
|       01C380h 4       RBIST_CNTRL         ;with extra bit in newer revision |
|       01C384h 4       TX_DC_OFFSET                                          |
|       01C388h 4       TX_TONEGEN0                                           |
|       01C38Ch 4       TX_TONEGEN1                                           |
|       01C390h 4       TX_LFTONEGEN0                                         |
|       01C394h 4       TX_LINEAR_RAMP_I                                      |
|       01C398h 4       TX_LINEAR_RAMP_Q                                      |
|       01C39Ch 4       TX_PRBS_MAG                                           |
|       01C3A0h 4       TX_PRBS_SEED_I                                        |
|       01C3A4h 4       TX_PRBS_SEED_Q                                        |
|       01C3A8h 4       CMAC_DC_CANCEL                                        |
|       01C3ACh 4       CMAC_DC_OFFSET                                        |
|       01C3B0h 4       CMAC_CORR                                             |
|       01C3B4h 4       CMAC_POWER                                            |
|       01C3B8h 4       CMAC_CROSS_CORR                                       |
|       01C3BCh 4       CMAC_I2Q2                                             |
|       01C3C0h 4       CMAC_POWER_HPF                                        |
|       01C3C4h 4       RXDAC_SET1                                            |
|       01C3C8h 4       RXDAC_SET2                                            |
|       01C3CCh 4       RXDAC_LONG_SHIFT                                      |
|       01C3D0h 4       CMAC_RESULTS_I                                        |
|       01C3D4h 4       CMAC_RESULTS_Q                                        |
|       01C3D8h 1x872   PAD__7                                                |
|       01C740h 4       PMU1                                                  |
|       01C744h 4       PMU2                                                  |
|       01C748h -       unused/unspecified                                    |
+-----------------------------------------------------------------------------+
```


### mac_dma_reg.h (hw4.0)

```
+-------------------------------------------------------------------------------------+
|       020000h 1x8     -                                                             |
|       020008h 4       MAC_DMA_CR      - MAC Control Register                        |
|       02000Ch 4       MAC_DMA_RXDP    - MAC receive queue descriptor pointer        |
|       020010h 4       -                                                             |
|       020014h 4       MAC_DMA_CFG     - MAC configuration and status register       |
|       020018h 4       -                                                             |
|       02001Ch 4       -                                                             |
|       020020h 4       MAC_DMA_MIRT    - Maximum rate threshold register             |
|       020024h 4       MAC_DMA_IER     - MAC Interrupt enable register               |
|       020028h 4       MAC_DMA_TIMT    - Transmit Interrupt Mitigation Threshold     |
|       02002Ch 4       MAC_DMA_RIMT    - Receive Interrupt Mitigation Threshold      |
|       020030h 4       MAC_DMA_TXCFG   - MAC tx DMA size config register             |
|       020034h 4       MAC_DMA_RXCFG   - MAC rx DMA size config register             |
|       020038h 4       -                                                             |
|       02003Ch 4       -                                                             |
|       020040h 4       MAC_DMA_MIBC    - MAC MIB control register                    |
|       020044h 4       MAC_DMA_TOPS    - MAC timeout prescale count                  |
|       020048h 4       MAC_DMA_RXNPTO  - MAC no frame received timeout               |
|       02004Ch 4       MAC_DMA_TXNPTO  - MAC no frame trasmitted timeout             |
|       020050h 4       MAC_DMA_RPGTO   - MAC receive frame gap timeout               |
|       020054h 4       MAC_DMA_RPCNT   - MAC receive frame count limit               |
|       020058h 4       MAC_DMA_MACMISC - MAC miscellaneous control/status register   |
|       02005Ch ..      -                                                             |
|      MAC IRQ...                                                                     |
|       020080h 4       MAC_DMA_ISR    - Primary Interrupt Status Register         ;\ 
|       020084h 4       MAC_DMA_ISR_S0 - Secondary Interrupt 0 Status TX OK/DESC   ;  |
|       020088h 4       MAC_DMA_ISR_S1 - Secondary Interrupt 1 Status TX ERR/EOL   ;  |
|       02008Ch 4       MAC_DMA_ISR_S2 - Secondary Interrupt 2 Status TX URN/MISC  ;  |
|       020090h 4       MAC_DMA_ISR_S3 - Secondary Interrupt 3 Status QCBR OVF/URN ;  |
|       020094h 4       MAC_DMA_ISR_S4 - Secondary Interrupt 4 Status QTRIG        ;  |
|       020098h 4       MAC_DMA_ISR_S5 - Secondary Interrupt 5 Status TIMERS       ;/ |
|       02009Ch 4       -                                                             |
|       0200A0h 4       MAC_DMA_IMR    - Primary Interrupt Mask Register           ;\ 
|       0200A4h 4       MAC_DMA_IMR_S0 - Secondary Interrupt 0 Mask TX OK/DESC     ;  |
|       0200A8h 4       MAC_DMA_IMR_S1 - Secondary Interrupt 1 Mask TX ERR/EOL     ;  |
|       0200ACh 4       MAC_DMA_IMR_S2 - Secondary Interrupt 2 Mask TX URN/MISC    ;  |
|       0200B0h 4       MAC_DMA_IMR_S3 - Secondary Interrupt 3 Mask QCBR OVF/URN   ;  |
|       0200B4h 4       MAC_DMA_IMR_S4 - Secondary Interrupt 4 Mask QTRIG          ;  |
|       0200B8h 4       MAC_DMA_IMR_S5 - Secondary Interrupt 5 Mask TIMERS         ;/ |
|       0200BCh 4       -                                                             |
|       0200C0h 4       MAC_DMA_ISR_RAC  - Primary Interrupt Read-and-Clear        ;\ 
|       0200C4h 4       MAC_DMA_ISR_S0_S - Secondary 0 Read-and-Clear TX OK/DESC   ;  |
|       0200C8h 4       MAC_DMA_ISR_S1_S - Secondary 1 Read-and-Clear TX ERR/EOL   ;  |
|       0200CCh 4       MAC_DMA_ISR_S2_S - Secondary 2 Read-and-Clear TX URN/MISC  ;  |
|       0200D0h 4       MAC_DMA_ISR_S3_S - Secondary 3 Read-and-Clear QCBR OVF/URN ;  |
|       0200D4h 4       MAC_DMA_ISR_S4_S - Secondary 4 Read-and-Clear QTRIG        ;  |
|       0200D8h 4       MAC_DMA_ISR_S5_S - Secondary 5 Read-and-Clear TIMERS       ;/ |
|       0200DCh ..      -                                                             |
|      MAC QCU...                                                                     |
|       020800h 4x10    MAC_DMA_Q(0..9)_TXDP         ;MAC Transmit Queue descr.ptr    |
|       020828h ..      -                                                             |
|       020840h 4       MAC_DMA_Q_TXE                ;MAC Transmit Queue enable       |
|       020844h ..      -                                                             |
|       020880h 4       MAC_DMA_Q_TXD                ;MAC Transmit Queue disable      |
|       020884h ..      -                                                             |
|       0208C0h 4x10    MAC_DMA_Q(0..9)_CBRCFG       ;MAC CBR configuration           |
|       0208E8h ..      -                                                             |
|       020900h 4x10    MAC_DMA_Q(0..9)_RDYTIMECFG   ;MAC ReadyTime configuration     |
|       020928h ..      -                                                             |
|       020940h 4       MAC_DMA_Q_ONESHOTMAC_DMAM_SC ;MAC OneShotArm set control      |
|       020944h ..      -                                                             |
|       020980h 4       MAC_DMA_Q_ONESHOTMAC_DMAM_CC ;MAC OneShotArm clear control    |
|       020984h ..      -                                                             |
|       0209C0h 4x10    MAC_DMA_Q(0..9)_MISC         ;MAC Misc QCU settings           |
|       0209E8h ..      -                                                             |
|       020A00h 4x10    MAC_DMA_Q(0..9)_STS          ;MAC Misc QCU status/counter     |
|       020A28h ..      -                                                             |
|       020A40h 4       MAC_DMA_Q_RDYTIMESHDN        ;MAC ReadyTimeShutdown status    |
|       020A44h ..      -                                                             |
|      MAC DCU...                                                                     |
|       021000h 4x10    MAC_DMA_D(0..9)_QCUMASK - MAC QCU Mask (DCU-to-QCU or so?)    |
|       021028h 8       -                                                             |
|       021030h 4       MAC_DMA_D_GBL_IFS_SIFS  - DCU global SIFS settings            |
|       021034h 12      -                                                             |
|       021040h 4x10    MAC_DMA_D(0..9)_LCL_IFS - MAC DCU-specific IFS settings       |
|       021068h 8       -                                                             |
|       021070h 4       MAC_DMA_D_GBL_IFS_SLOT   - DC global slot interval            |
|       021074h 12      -                                                             |
|       021080h 4x10    MAC_DMA_D(0..9)_RETRY_LIMIT - MAC Retry limits                |
|       0210A8h 8       -                                                             |
|       0210B0h 4       MAC_DMA_D_GBL_IFS_EIFS   - DCU global EIFS setting            |
|       0210B4h 12      -                                                             |
|       0210C0h 4x10    MAC_DMA_D(0..9)_CHNTIME  - MAC ChannelTime settings           |
|       0210E8h 8       -                                                             |
|       0210F0h 4       MAC_DMA_D_GBL_IFS_MISC   - DCU global misc. IFS settings      |
|       0210F4h 12      -                                                             |
|       021100h 4x10    MAC_DMA_D(0..9)_MISC     - MAC Misc DCU-specific settings     |
|       021128h ..      -                                                             |
|       021140h 4       MAC_DMA_D_SEQNUM         - MAC Frame sequence number          |
|       021144h ..      -                                                             |
|       021180h 4x10    MAC_DMA_D(0..9)_EOL     -                                     |
|       0211A8h ..      -                                                             |
|       021230h 4       MAC_DMA_D_FPCTL         - DCU frame prefetch settings         |
|       021234h ..      -                                                             |
|       021270h 4       MAC_DMA_D_TXPSE         - DCU transmit pause control/status   |
|       021274h ..      -                                                             |
+-------------------------------------------------------------------------------------+
```


### mac_pcu_reg.h (1) (hw4.0)

```
+--------------------------------------------------------------------------------+
|       028000h 4       MAC_PCU_STA_ADDR_L32                                     |
|       028004h 4       MAC_PCU_STA_ADDR_U16                                     |
|       028008h 4       MAC_PCU_BSSID_L32                                        |
|       02800Ch 4       MAC_PCU_BSSID_U16                                        |
|       028010h 4       MAC_PCU_BCN_RSSI_AVE                                     |
|       028014h 4       MAC_PCU_ACK_CTS_TIMEOUT                                  |
|       028018h 4       MAC_PCU_BCN_RSSI_CTL                                     |
|       02801Ch 4       MAC_PCU_USEC_LATENCY                                     |
|       028020h 4       PCU_MAX_CFP_DUR                                          |
|       028024h 4       MAC_PCU_RX_FILTER                                        |
|       028028h 4       MAC_PCU_MCAST_FILTER_L32                                 |
|       02802Ch 4       MAC_PCU_MCAST_FILTER_U32                                 |
|       028030h 4       MAC_PCU_DIAG_SW                                          |
|       028034h 4       MAC_PCU_TST_ADDAC                                        |
|       028038h 4       MAC_PCU_DEF_ANTENNA                                      |
|       02803Ch 4       MAC_PCU_AES_MUTE_MASK_0                                  |
|       028040h 4       MAC_PCU_AES_MUTE_MASK_1                                  |
|       028044h 4       MAC_PCU_GATED_CLKS                                       |
|       028048h 4       MAC_PCU_OBS_BUS_2                                        |
|       02804Ch 4       MAC_PCU_OBS_BUS_1                                        |
|       028050h 4       MAC_PCU_DYM_MIMO_PWR_SAVE                                |
|       028054h 4       MAC_PCU_LAST_BEACON_TSF                                  |
|       028058h 4       MAC_PCU_NAV                                              |
|       02805Ch 4       MAC_PCU_RTS_SUCCESS_CNT                                  |
|       028060h 4       MAC_PCU_RTS_FAIL_CNT                                     |
|       028064h 4       MAC_PCU_ACK_FAIL_CNT                                     |
|       028068h 4       MAC_PCU_FCS_FAIL_CNT                                     |
|       02806Ch 4       MAC_PCU_BEACON_CNT                                       |
|       028070h 4       MAC_PCU_XRMODE                                           |
|       028074h 4       MAC_PCU_XRDEL                                            |
|       028078h 4       MAC_PCU_XRTO                                             |
|       02807Ch 4       MAC_PCU_XRCRP                                            |
|       028080h 4       MAC_PCU_XRSTMP                                           |
|       028084h 4       MAC_PCU_ADDR1_MASK_L32                                   |
|       028088h 4       MAC_PCU_ADDR1_MASK_U16                                   |
|       02808Ch 4       MAC_PCU_TPC                                              |
|       028090h 4       MAC_PCU_TX_FRAME_CNT                                     |
|       028094h 4       MAC_PCU_RX_FRAME_CNT                                     |
|       028098h 4       MAC_PCU_RX_CLEAR_CNT                                     |
|       02809Ch 4       MAC_PCU_CYCLE_CNT                                        |
|       0280A0h 4       MAC_PCU_QUIET_TIME_1                                     |
|       0280A4h 4       MAC_PCU_QUIET_TIME_2                                     |
|       0280A8h 4       MAC_PCU_QOS_NO_ACK                                       |
|       0280ACh 4       MAC_PCU_PHY_ERROR_MASK                                   |
|       0280B0h 4       MAC_PCU_XRLAT                                            |
|       0280B4h 4       MAC_PCU_RXBUF                                            |
|       0280B8h 4       MAC_PCU_MIC_QOS_CONTROL                                  |
|       0280BCh 4       MAC_PCU_MIC_QOS_SELECT                                   |
|       0280C0h 4       MAC_PCU_MISC_MODE                                        |
|       0280C4h 4       MAC_PCU_FILTER_OFDM_CNT                                  |
|       0280C8h 4       MAC_PCU_FILTER_CCK_CNT                                   |
|       0280CCh 4       MAC_PCU_PHY_ERR_CNT_1                                    |
|       0280D0h 4       MAC_PCU_PHY_ERR_CNT_1_MASK                               |
|       0280D4h 4       MAC_PCU_PHY_ERR_CNT_2                                    |
|       0280D8h 4       MAC_PCU_PHY_ERR_CNT_2_MASK                               |
|       0280DCh 4       MAC_PCU_TSF_THRESHOLD                                    |
|       0280E0h 4       MAC_PCU_PHY_ERROR_EIFS_MASK                              |
|       0280E4h 4       MAC_PCU_PHY_ERR_CNT_3                                    |
|       0280E8h 4       MAC_PCU_PHY_ERR_CNT_3_MASK                               |
|       0280ECh 4       MAC_PCU_BLUETOOTH_MODE                                   |
|       0280F0h 4       MAC_PCU_BLUETOOTH_WEIGHTS                                |
|       0280F4h 4       MAC_PCU_BLUETOOTH_MODE2                                  |
|       0280F8h 4       MAC_PCU_TXSIFS                                           |
|       0280FCh 4       MAC_PCU_TXOP_X                                           |
|       028100h 4       MAC_PCU_TXOP_0_3                                         |
|       028104h 4       MAC_PCU_TXOP_4_7                                         |
|       028108h 4       MAC_PCU_TXOP_8_11                                        |
|       02810Ch 4       MAC_PCU_TXOP_12_15                                       |
|       028110h 4       MAC_PCU_LOGIC_ANALYZER                                   |
|       028114h 4       MAC_PCU_LOGIC_ANALYZER_32L                               |
|       028118h 4       MAC_PCU_LOGIC_ANALYZER_16U                               |
|       02811Ch 4       MAC_PCU_PHY_ERR_CNT_MASK_CONT                            |
|       028120h 4       MAC_PCU_AZIMUTH_MODE                                     |
|       028124h 4       MAC_PCU_20_40_MODE                                       |
|       028128h 4       MAC_PCU_RX_CLEAR_DIFF_CNT                                |
|       02812Ch 4       MAC_PCU_SELF_GEN_ANTENNA_MASK                            |
|       028130h 4       MAC_PCU_BA_BAR_CONTROL                                   |
|       028134h 4       MAC_PCU_LEGACY_PLCP_SPOOF                                |
|       028138h 4       MAC_PCU_PHY_ERROR_MASK_CONT                              |
|       02813Ch 4       MAC_PCU_TX_TIMER                                         |
|       028140h 4       MAC_PCU_TXBUF_CTRL                                       |
|       028144h 4       MAC_PCU_MISC_MODE2     ;with extra bit in newer revision |
|       028148h 4       MAC_PCU_ALT_AES_MUTE_MASK                                |
|       02814Ch 4       MAC_PCU_AZIMUTH_TIME_STAMP                               |
|       028150h 4       MAC_PCU_MAX_CFP_DUR                                      |
|       028154h 4       MAC_PCU_HCF_TIMEOUT                                      |
|       028158h 4       MAC_PCU_BLUETOOTH_WEIGHTS2                               |
|       02815Ch 4       MAC_PCU_BLUETOOTH_TSF_BT_ACTIVE                          |
|       028160h 4       MAC_PCU_BLUETOOTH_TSF_BT_PRIORITY                        |
|       028164h 4       MAC_PCU_BLUETOOTH_MODE3                                  |
|       028168h 4       MAC_PCU_BLUETOOTH_MODE4                                  |
|       02816Ch 1x148   PAD0                                                     |
|       028200h 4x64    MAC_PCU_BT_BT[0..63]                                     |
|       028300h 4       MAC_PCU_BT_BT_ASYNC                                      |
|       028304h 4       MAC_PCU_BT_WL_1                                          |
|       028308h 4       MAC_PCU_BT_WL_2                                          |
|       02830Ch 4       MAC_PCU_BT_WL_3                                          |
|       028310h 4       MAC_PCU_BT_WL_4                                          |
|       028314h 4       MAC_PCU_COEX_EPTA                                        |
|       028318h 4       MAC_PCU_COEX_LNAMAXGAIN1                                 |
|       02831Ch 4       MAC_PCU_COEX_LNAMAXGAIN2                                 |
|       028320h 4       MAC_PCU_COEX_LNAMAXGAIN3                                 |
|       028324h 4       MAC_PCU_COEX_LNAMAXGAIN4                                 |
|       028328h 4       MAC_PCU_BASIC_RATE_SET0                                  |
|       02832Ch 4       MAC_PCU_BASIC_RATE_SET1                                  |
|       028330h 4       MAC_PCU_BASIC_RATE_SET2                                  |
|       028334h 4       MAC_PCU_BASIC_RATE_SET3                                  |
|       028338h 4       MAC_PCU_RX_INT_STATUS0                                   |
|       02833Ch 4       MAC_PCU_RX_INT_STATUS1                                   |
|       028340h 4       MAC_PCU_RX_INT_STATUS2                                   |
|       028344h 4       MAC_PCU_RX_INT_STATUS3                                   |
|       028348h 4       HT_HALF_GI_RATE1                                         |
|       02834Ch 4       HT_HALF_GI_RATE2                                         |
|       028350h 4       HT_FULL_GI_RATE1                                         |
|       028354h 4       HT_FULL_GI_RATE2                                         |
|       028358h 4       LEGACY_RATE1                                             |
|       02835Ch 4       LEGACY_RATE2                                             |
|       028360h 4       LEGACY_RATE3                                             |
|       028364h 4       RX_INT_FILTER          ;with extra bit in newer revision |
|       028368h 4       RX_INT_OVERFLOW                                          |
|       02836Ch 4       RX_FILTER_THRESH(0)                                      |
|       028370h 4       RX_FILTER_THRESH1                                        |
|       028374h 4       RX_PRIORITY_THRESH0                                      |
|       028378h 4       RX_PRIORITY_THRESH1                                      |
|       02837Ch 4       RX_PRIORITY_THRESH2                                      |
|       028380h 4       RX_PRIORITY_THRESH3                                      |
|       028384h 4       RX_PRIORITY_OFFSET0                                      |
|       028388h 4       RX_PRIORITY_OFFSET1                                      |
|       02838Ch 4       RX_PRIORITY_OFFSET2                                      |
|       028390h 4       RX_PRIORITY_OFFSET3                                      |
|       028394h 4       RX_PRIORITY_OFFSET4                                      |
|       028398h 4       RX_PRIORITY_OFFSET5                                      |
|       02839Ch 4       MAC_PCU_BSSID2_L32                                       |
|       0283A0h 4       MAC_PCU_BSSID2_U16                                       |
|       0283A4h 4       MAC_PCU_TSF1_STATUS_L32                                  |
|       0283A8h 4       MAC_PCU_TSF1_STATUS_U32                                  |
|       0283ACh 4       MAC_PCU_TSF2_STATUS_L32                                  |
|       0283B0h 4       MAC_PCU_TSF2_STATUS_U32                                  |
|       0283B4h 1x76    PAD1                                                     |
|       028400h 4x64    MAC_PCU_TXBUF_BA[0..63]                                  |
|       028500h 1x768   PAD2                                                     |
|       028800h 4x256   MAC_PCU_KEY_CACHE_1[0..255]                              |
|       028C00h 1x3072  PAD3                                                     |
|       029800h 4x512   MAC_PCU_BASEBAND_0[0..511]   ;\aka BB_xxx ports          
|       02A000h 4x2048  MAC_PCU_BASEBAND_1[0..2047]  ;/(see below)               |
|       02C000h 4x1024  MAC_PCU_BASEBAND_2[0..1023]  ;\                          
|       02D000h 4x1024  MAC_PCU_BASEBAND_3[0..1023]  ; after BB registers        |
|       02E000h 4x512   MAC_PCU_BUF[0..511]          ;/                          |
|       02E800h -       unused/unspecified                                       |
+--------------------------------------------------------------------------------+
```


### bb_lc_reg.h (hw4.0)

```
+---------------------------------------------------------------------------------+
|      "BASEBAND_0"                                                               |
|       029800h 4       BB_TEST_CONTROLS                                          |
|       029804h 4       BB_GEN_CONTROLS                                           |
|       029808h 4       BB_TEST_CONTROLS_STATUS                                   |
|       02980Ch 4       BB_TIMING_CONTROLS_1                                      |
|       029810h 4       BB_TIMING_CONTROLS_2                                      |
|       029814h 4       BB_TIMING_CONTROLS_3                                      |
|       029818h 4       BB_D2_CHIP_ID                                             |
|       02981Ch 4       BB_ACTIVE                                                 |
|       029820h 4       BB_TX_TIMING_1                                            |
|       029824h 4       BB_TX_TIMING_2                                            |
|       029828h 4       BB_TX_TIMING_3                                            |
|       02982Ch 4       BB_ADDAC_PARALLEL_CONTROL                                 |
|       029830h 1x4     PAD__1                                                    |
|       029834h 4       BB_XPA_TIMING_CONTROL                                     |
|       029838h 4       BB_MISC_PA_CONTROL                                        |
|       02983Ch 4       BB_TSTDAC_CONSTANT                                        |
|       029840h 4       BB_FIND_SIGNAL_LOW                                        |
|       029844h 4       BB_SETTLING_TIME                                          |
|       029848h 4       BB_GAIN_FORCE_MAX_GAINS_B0                                |
|       02984Ch 4       BB_GAINS_MIN_OFFSETS_B0                                   |
|       029850h 4       BB_DESIRED_SIGSIZE                                        |
|       029854h 4       BB_TIMING_CONTROL_3A                                      |
|       029858h 4       BB_FIND_SIGNAL                                            |
|       02985Ch 4       BB_AGC                                                    |
|       029860h 4       BB_AGC_CONTROL                                            |
|       029864h 4       BB_CCA_B0                                                 |
|       029868h 4       BB_SFCORR                                                 |
|       02986Ch 4       BB_SELF_CORR_LOW                                          |
|       029870h 1x4     PAD__2                                                    |
|       029874h 4       BB_SYNTH_CONTROL                                          |
|       029878h 4       BB_ADDAC_CLK_SELECT                                       |
|       02987Ch 4       BB_PLL_CNTL                                               |
|       029880h 1x128   PAD__3                                                    |
|       029900h 4       BB_VIT_SPUR_MASK_A                                        |
|       029904h 4       BB_VIT_SPUR_MASK_B                                        |
|       029908h 4       BB_PILOT_SPUR_MASK                                        |
|       02990Ch 4       BB_CHAN_SPUR_MASK                                         |
|       029910h 4       BB_SPECTRAL_SCAN                                          |
|       029914h 4       BB_ANALOG_POWER_ON_TIME                                   |
|       029918h 4       BB_SEARCH_START_DELAY                                     |
|       02991Ch 4       BB_MAX_RX_LENGTH                                          |
|       029920h 4       BB_TIMING_CONTROL_4                                       |
|       029924h 4       BB_TIMING_CONTROL_5                                       |
|       029928h 4       BB_PHYONLY_WARM_RESET                                     |
|       02992Ch 4       BB_PHYONLY_CONTROL                                        |
|       029930h 1x4     PAD__4                                                    |
|       029934h 4       BB_POWERTX_RATE1   ;Power TX 0..3                         |
|       029938h 4       BB_POWERTX_RATE2   ;Power TX 4..7                         |
|       02993Ch 4       BB_POWERTX_MAX     ;Power TX Flags                        |
|       029940h 4       BB_EXTENSION_RADAR                                        |
|       029944h 4       BB_FRAME_CONTROL                                          |
|       029948h 4       BB_TIMING_CONTROL_6                                       |
|       02994Ch 4       BB_SPUR_MASK_CONTROLS                                     |
|       029950h 4       BB_RX_IQ_CORR_B0                                          |
|       029954h 4       BB_RADAR_DETECTION                                        |
|       029958h 4       BB_RADAR_DETECTION_2                                      |
|       02995Ch 4       BB_TX_PHASE_RAMP_B0                                       |
|       029960h 4       BB_SWITCH_TABLE_CHN_B0                                    |
|       029964h 4       BB_SWITCH_TABLE_COM1                                      |
|       029968h 4       BB_CCA_CTRL_2_B0                                          |
|       02996Ch 4       BB_SWITCH_TABLE_COM2                                      |
|       029970h 4       BB_RESTART                                                |
|       029974h 1x4     PAD__5                                                    |
|       029978h 4       BB_SCRAMBLER_SEED                                         |
|       02997Ch 4       BB_RFBUS_REQUEST                                          |
|       029980h 1x32    PAD__6                                                    |
|       0299A0h 4       BB_TIMING_CONTROL_11                                      |
|       0299A4h 4       BB_MULTICHAIN_ENABLE                                      |
|       0299A8h 4       BB_MULTICHAIN_CONTROL                                     |
|       0299ACh 4       BB_MULTICHAIN_GAIN_CTRL                                   |
|       0299B0h 1x4     PAD__7                                                    |
|       0299B4h 4       BB_ADC_GAIN_DC_CORR_B0                                    |
|       0299B8h 4       BB_EXT_CHAN_PWR_THR_1                                     |
|       0299BCh 4       BB_EXT_CHAN_PWR_THR_2_B0                                  |
|       0299C0h 4       BB_EXT_CHAN_SCORR_THR                                     |
|       0299C4h 4       BB_EXT_CHAN_DETECT_WIN                                    |
|       0299C8h 4       BB_PWR_THR_20_40_DET                                      |
|       0299CCh 1x4     PAD__8                                                    |
|       0299D0h 4       BB_SHORT_GI_DELTA_SLOPE                                   |
|       0299D4h 1x8     PAD__9                                                    |
|       0299DCh 4       BB_CHANINFO_CTRL                                          |
|       0299E0h 4       BB_HEAVY_CLIP_CTRL                                        |
|       0299E4h 4       BB_HEAVY_CLIP_20                                          |
|       0299E8h 4       BB_HEAVY_CLIP_40                                          |
|       0299ECh 4       BB_RIFS_SRCH                                              |
|       0299F0h 4       BB_IQ_ADC_CAL_MODE                                        |
|       0299F4h 1x8     PAD__10                                                   |
|       0299FCh 4       BB_PER_CHAIN_CSD                                          |
|       029A00h 4x128   BB_RX_OCGAIN[0..127]                                      |
|       029C00h 4       BB_TX_CRC                                                 |
|       029C04h 1x12    PAD__11                                                   |
|       029C10h 4       BB_IQ_ADC_MEAS_0_B0                                       |
|       029C14h 4       BB_IQ_ADC_MEAS_1_B0                                       |
|       029C18h 4       BB_IQ_ADC_MEAS_2_B0                                       |
|       029C1Ch 4       BB_IQ_ADC_MEAS_3_B0                                       |
|       029C20h 4       BB_RFBUS_GRANT                                            |
|       029C24h 4       BB_TSTADC                                                 |
|       029C28h 4       BB_TSTDAC                                                 |
|       029C2Ch 1x4     PAD__12                                                   |
|       029C30h 4       BB_ILLEGAL_TX_RATE                                        |
|       029C34h 4       BB_SPUR_REPORT_B0                                         |
|       029C38h 4       BB_CHANNEL_STATUS                                         |
|       029C3Ch 4       BB_RSSI_B0                                                |
|       029C40h 4       BB_SPUR_EST_CCK_REPORT_B0                                 |
|       029C44h 1x104   PAD__13  ;(old 1x172)                                     |
|       029CF0h 4       BB_CHAN_INFO_NOISE_PWR              ;\                    
|       029CF4h 4       BB_CHAN_INFO_GAIN_DIFF              ; located HERE in     |
|       029CF8h 4       BB_CHAN_INFO_FINE_TIMING            ; older revision      |
|       029CFCh 4       BB_CHAN_INFO_GAIN_B0                ; (unlike below)      |
|       029D00h 4x60    BB_CHAN_INFO_CHAN_TAB_B0[0..59]     ;/                    |
|       029CACh 4       BB_CHAN_INFO_NOISE_PWR              ;\                    
|       029CB0h 4       BB_CHAN_INFO_GAIN_DIFF              ; located HERE in     |
|       029CB4h 4       BB_CHAN_INFO_FINE_TIMING            ; newer revision      |
|       029CB8h 4       BB_CHAN_INFO_GAIN_B0                ; (unlike above)      |
|       029CBCh 4x60    BB_CHAN_INFO_CHAN_TAB_B0[0..59]     ;/                    |
|       029DACh 1x56    PAD__14  ;(old 1x528 at 9DF0h)                            |
|       029DE4h 4       BB_PAPRD_AM2AM_MASK                 ;\                    
|       029DE8h 4       BB_PAPRD_AM2PM_MASK                 ;                     |
|       029DECh 4       BB_PAPRD_HT40_MASK                  ;                     |
|       029DF0h 4       BB_PAPRD_CTRL0                      ; exists ONLY in      |
|       029DF4h 4       BB_PAPRD_CTRL1                      ; newer revision      |
|       029DF8h 4       BB_PA_GAIN123                       ;                     |
|       029DFCh 4       BB_PA_GAIN45                        ;                     |
|       029E00h 4x8     BB_PAPRD_PRE_POST_SCALE_(0..7)      ;                     |
|       029E20h 4x120   BB_PAPRD_MEM_TAB[....]              ;/                    |
|      "BASEBAND_1"                                                               |
|       02A000h 4       BB_PEAK_DET_CTRL_1                                        |
|       02A004h 4       BB_PEAK_DET_CTRL_2                                        |
|       02A008h 4       BB_RX_GAIN_BOUNDS_1                                       |
|       02A00Ch 4       BB_RX_GAIN_BOUNDS_2                                       |
|       02A010h 4       BB_PEAK_DET_CAL_CTRL                                      |
|       02A014h 4       BB_AGC_DIG_DC_CTRL                                        |
|       02A018h 4       BB_AGC_DIG_DC_STATUS_I_B0                                 |
|       02A01Ch 4       BB_AGC_DIG_DC_STATUS_Q_B0                                 |
|       02A020h 1x468   PAD__15                                                   |
|       02A1F4h 4       BB_BBB_TXFIR_0                                            |
|       02A1F8h 4       BB_BBB_TXFIR_1                                            |
|       02A1FCh 4       BB_BBB_TXFIR_2                                            |
|       02A200h 4       BB_MODES_SELECT                                           |
|       02A204h 4       BB_BBB_TX_CTRL                                            |
|       02A208h 4       BB_BBB_SIG_DETECT                                         |
|       02A20Ch 4       BB_EXT_ATTEN_SWITCH_CTL_B0                                |
|       02A210h 4       BB_BBB_RX_CTRL_1                                          |
|       02A214h 4       BB_BBB_RX_CTRL_2                                          |
|       02A218h 4       BB_BBB_RX_CTRL_3                                          |
|       02A21Ch 4       BB_BBB_RX_CTRL_4                                          |
|       02A220h 4       BB_BBB_RX_CTRL_5                                          |
|       02A224h 4       BB_BBB_RX_CTRL_6                                          |
|       02A228h 4       BB_BBB_DAGC_CTRL                                          |
|       02A22Ch 4       BB_FORCE_CLKEN_CCK                                        |
|       02A230h 4       BB_RX_CLEAR_DELAY                                         |
|       02A234h 4       BB_POWERTX_RATE3   ;Power TX 1L,2L,2S                     |
|       02A238h 4       BB_POWERTX_RATE4   ;Power TX 55L,55S,11L,11S              |
|       02A23Ch 1x4     PAD__16                                                   |
|       02A240h 4       BB_CCK_SPUR_MIT                                           |
|       02A244h 4       BB_PANIC_WATCHDOG_STATUS                                  |
|       02A248h 4       BB_PANIC_WATCHDOG_CTRL_1                                  |
|       02A24Ch 4       BB_PANIC_WATCHDOG_CTRL_2                                  |
|       02A250h 4       BB_IQCORR_CTRL_CCK      ;with extra bit in newer revision |
|       02A254h 4       BB_BLUETOOTH_CNTL                                         |
|       02A258h 4       BB_TPC_1                                                  |
|       02A25Ch 4       BB_TPC_2                                                  |
|       02A260h 4       BB_TPC_3                                                  |
|       02A264h 4       BB_TPC_4_B0                                               |
|       02A268h 4       BB_ANALOG_SWAP                                            |
|       02A26Ch 4       BB_TPC_5_B0                                               |
|       02A270h 4       BB_TPC_6_B0                                               |
|       02A274h 4       BB_TPC_7                                                  |
|       02A278h 4       BB_TPC_8                                                  |
|       02A27Ch 4       BB_TPC_9                                                  |
|       02A280h 4x32    BB_PDADC_TAB_B0[0..31]                                    |
|       02A300h 4x16    BB_CL_TAB_B0[0..15]                                       |
|       02A340h 4       BB_CL_MAP_0_B0                                            |
|       02A344h 4       BB_CL_MAP_1_B0                                            |
|       02A348h 4       BB_CL_MAP_2_B0                                            |
|       02A34Ch 4       BB_CL_MAP_3_B0                                            |
|       02A350h 1x8     PAD__17                                                   |
|       02A358h 4       BB_CL_CAL_CTRL                                            |
|       02A35Ch 4       BB_CL_MAP_PAL_0_B0            ;\                          
|       02A360h 4       BB_CL_MAP_PAL_1_B0            ; exists ONLY in            |
|       02A364h 4       BB_CL_MAP_PAL_2_B0            ; newer revision            |
|       02A368h 4       BB_CL_MAP_PAL_3_B0            ;/                          |
|       02A36Ch 1x28    PAD__18  ;(old 1x44 at A35Ch)                             |
|       02A388h 4       BB_RIFS                                                   |
|       02A38Ch 4       BB_POWERTX_RATE5   ;Power TX HT20_0..3                    |
|       02A390h 4       BB_POWERTX_RATE6   ;Power TX HT20_4..7                    |
|       02A394h 4       BB_TPC_10                                                 |
|       02A398h 4       BB_TPC_11_B0                                              |
|       02A39Ch 4       BB_CAL_CHAIN_MASK                                         |
|       02A3A0h 1x28    PAD__19                                                   |
|       02A3BCh 4       BB_POWERTX_SUB     ;Power TX Sub_for_2chain               |
|       02A3C0h 4       BB_POWERTX_RATE7   ;Power TX HT40_0..3                    |
|       02A3C4h 4       BB_POWERTX_RATE8   ;Power TX HT40_4..7                    |
|       02A3C8h 4       BB_POWERTX_RATE9   ;Power TX DUP40/EXT20_CCK/OFDM         |
|       02A3CCh 4       BB_POWERTX_RATE10  ;Power TX HT20_8..11                   |
|       02A3D0h 4       BB_POWERTX_RATE11  ;Power TX HT20/40_12/13                |
|       02A3D4h 4       BB_POWERTX_RATE12  ;Power TX HT40_8..11                   |
|       02A3D8h 4       BB_FORCE_ANALOG                                           |
|       02A3DCh 4       BB_TPC_12                                                 |
|       02A3E0h 4       BB_TPC_13                                                 |
|       02A3E4h 4       BB_TPC_14                                                 |
|       02A3E8h 4       BB_TPC_15                                                 |
|       02A3ECh 4       BB_TPC_16                                                 |
|       02A3F0h 4       BB_TPC_17                                                 |
|       02A3F4h 4       BB_TPC_18                                                 |
|       02A3F8h 4       BB_TPC_19                                                 |
|       02A3FCh 4       BB_TPC_20                                                 |
|       02A400h 4x32    BB_TX_GAIN_TAB_(1..32)                                    |
|       02A480h 4x32    BB_TX_GAIN_TAB_PAL_(1..32)                                |
|       02A500h 1x24    PAD__20                                                   |
|       02A518h 4x16    BB_CALTX_GAIN_SET_(0,2,4,6,..,28,30)                      |
|       02A558h 4x96    BB_TXIQCAL_MEAS_B0[0..95]                                 |
|       02A6D8h 4       BB_TXIQCAL_START                                          |
|       02A6DCh 4       BB_TXIQCAL_CONTROL_0                                      |
|       02A6E0h 4       BB_TXIQCAL_CONTROL_1                                      |
|       02A6E4h 4       BB_TXIQCAL_CONTROL_2                                      |
|       02A6E8h 4       BB_TXIQCAL_CONTROL_3                                      |
|       02A6ECh 4       BB_TXIQ_CORR_COEFF_01_B0                                  |
|       02A6F0h 4       BB_TXIQ_CORR_COEFF_23_B0                                  |
|       02A6F4h 4       BB_TXIQ_CORR_COEFF_45_B0                                  |
|       02A6F8h 4       BB_TXIQ_CORR_COEFF_67_B0                                  |
|       02A6FCh 4       BB_TXIQ_CORR_COEFF_89_B0                                  |
|       02A700h 4       BB_TXIQ_CORR_COEFF_AB_B0                                  |
|       02A704h 4       BB_TXIQ_CORR_COEFF_CD_B0                                  |
|       02A708h 4       BB_TXIQ_CORR_COEFF_EF_B0                                  |
|       02A70Ch 4       BB_CAL_RXBB_GAIN_TBL_0                                    |
|       02A710h 4       BB_CAL_RXBB_GAIN_TBL_4                                    |
|       02A714h 4       BB_CAL_RXBB_GAIN_TBL_8                                    |
|       02A718h 4       BB_CAL_RXBB_GAIN_TBL_12                                   |
|       02A71Ch 4       BB_CAL_RXBB_GAIN_TBL_16                                   |
|       02A720h 4       BB_CAL_RXBB_GAIN_TBL_20                                   |
|       02A724h 4       BB_CAL_RXBB_GAIN_TBL_24                                   |
|       02A728h 4       BB_TXIQCAL_STATUS_B0                                      |
|       02A72Ch 4       BB_PAPRD_TRAINER_CNTL1        ;\                          
|       02A730h 4       BB_PAPRD_TRAINER_CNTL2        ;                           |
|       02A734h 4       BB_PAPRD_TRAINER_CNTL3        ; exists ONLY in            |
|       02A738h 4       BB_PAPRD_TRAINER_CNTL4        ; newer revision            |
|       02A73Ch 4       BB_PAPRD_TRAINER_STAT1        ;                           |
|       02A740h 4       BB_PAPRD_TRAINER_STAT2        ;                           |
|       02A744h 4       BB_PAPRD_TRAINER_STAT3        ;/                          |
|       02A748h 1x144   PAD__21  ;(old 1x172 at A72Ch)                            |
|       02A7D8h 4       BB_FCAL_1                                                 |
|       02A7DCh 4       BB_FCAL_2_B0                                              |
|       02A7E0h 4       BB_RADAR_BW_FILTER                                        |
|       02A7E4h 4       BB_DFT_TONE_CTRL_B0                                       |
|       02A7E8h 4       BB_THERM_ADC_1                                            |
|       02A7ECh 4       BB_THERM_ADC_2                                            |
|       02A7F0h 4       BB_THERM_ADC_3                                            |
|       02A7F4h 4       BB_THERM_ADC_4                                            |
|       02A7F8h 4       BB_TX_FORCED_GAIN                                         |
|       02A7FCh 4       BB_ECO_CTRL                                               |
|       02A800h 1x72    PAD__22                                                   |
|       02A848h 4       BB_GAIN_FORCE_MAX_GAINS_B1                                |
|       02A84Ch 4       BB_GAINS_MIN_OFFSETS_B1                                   |
|       02A850h 1x432   PAD__23                                                   |
|       02AA00h 4x128   BB_RX_OCGAIN2[0..127]                                     |
|       02AC00h 1x1548  PAD__24                                                   |
|       02B20Ch 4       BB_EXT_ATTEN_SWITCH_CTL_B1                                |
|       02B210h -       unused/unspecified                                        |
+---------------------------------------------------------------------------------+
```


### mac_pcu_reg.h (2) (hw4.0)

```
+-------------------------------------------------------------------------+
|       02C000h 4x1024  MAC_PCU_BASEBAND_2[0..1023]  ;\                   
|       02D000h 4x1024  MAC_PCU_BASEBAND_3[0..1023]  ; after BB registers |
|       02E000h 4x512   MAC_PCU_BUF[0..511]          ;/                   |
|       02E800h -       unused/unspecified                                |
+-------------------------------------------------------------------------+
```


### rdma_reg.h (hw4.0)

```
+-----------------------------------------------------------------------+
|       030100h 4       DMA_CONFIG                                      |
|       030104h 4       DMA_CONTROL                                     |
|       030108h 4       DMA_SRC                                         |
|       03010Ch 4       DMA_DEST                                        |
|       030110h 4       DMA_LENGTH                                      |
|       030114h 4       VMC_BASE                                        |
|       030118h 4       INDIRECT_REG                                    |
|       03011Ch 4       INDIRECT_RETURN                                 |
|       030120h 4x16    RDMA_REGION_(0..15)_                            |
|       030160h 4       DMA_STATUS                                      |
|       030164h 4       DMA_INT_EN                                      |
|       030168h -       unused/unspecified                              |
+-----------------------------------------------------------------------+
```


### efuse_reg.h (hw4.0)

```
+-----------------------------------------------------------------------+
|       031000h 4       EFUSE_WR_ENABLE_REG                             |
|       031004h 4       EFUSE_INT_ENABLE_REG                            |
|       031008h 4       EFUSE_INT_STATUS_REG                            |
|       03100Ch 4       BITMASK_WR_REG                                  |
|       031010h 4       VDDQ_SETTLE_TIME_REG                            |
|       031014h 4       RD_STROBE_PW_REG                                |
|       031018h 4       PG_STROBE_PW_REG                                |
|       03101Ch 1x2020  PAD0                                            |
|       031800h 4x512   EFUSE_INTF[0..511]                              |
|       032000h -       unused/unspecified                              |
+-----------------------------------------------------------------------+
```




