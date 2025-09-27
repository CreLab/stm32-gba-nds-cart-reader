# DSi Atheros Wifi - Internal I/O Map Summary (hw2)


### Overall Summary (hw2.0)

```
+------------------------------------------------------------------------------------+
|       004000h 1C4h    Clock/RTC Registers (rtc_reg.h) (hw2.0)                      |
|       008000h 208h    Memory Controller (TCAM) (vmc_reg.h) (hw2.0)                 |
|       00C000h 40h     Serial UART (uart_reg.h) (hw2.0)                             |
|       010000h 18h     Serial I2C/SPI Interface (si_reg.h) (hw2.0)                  |
|       0140F4h 4       GPIO Registers (gpio_reg.h) (hw2.0)                          |
|       018000h 114h    MBOX Registers (mbox_reg.h) (hw2.0)                          |
|       01A000h 2000h   HOST_IF_WINDOW (mbox_reg.h) (hw2.0)                          |
|       01C000h 64h     Analog Intf Registers (analog_reg.h) (hw2.0)                 |
|       01C080h 10h     Analog Intf Registers (analog_intf_reg.h) (hw2.0)            |
|       020000h ?       MAC DMA maybe, if any ?                                      |
|       028000h 1800h   MAC PCU Registers (mac_pcu.h) (hw2.0)                        |
|       029800h ...     BB/LC maybe...                                               |
|       029800h ?       Used in hw2, but undocumented... maybe BASEBAND_0 alike hw4? |
|       02A000h ?       Used in hw2, but undocumented... maybe BASEBAND_1 alike hw4? |
|       030000h ?       Used in hw2, but undocumented... maybe RDMA or EFUSE or so?  |
+------------------------------------------------------------------------------------+
```


### Clock/RTC Registers (rtc_reg.h) (hw2.0)

```
+-------------------------------------------------------------------------------+
|       004000h 4       (WLAN_)RESET_CONTROL                                    |
|       004004h 4       (WLAN_)XTAL_CONTROL                                     |
|       004008h 4       (WLAN_)TCXO_DETECT                                      |
|       00400Ch 4       (WLAN_)XTAL_TEST                                        |
|       004010h 4       (WLAN_)QUADRATURE                                       |
|       004014h 4       (WLAN_)PLL_CONTROL                                      |
|       004018h 4       (WLAN_)PLL_SETTLE                                       |
|       00401Ch 4       (WLAN_)XTAL_SETTLE                                      |
|       004020h 4       (WLAN_)CPU_CLOCK                                        |
|       004024h 4       (WLAN_)CLOCK_OUT                                        |
|       004028h 4       (WLAN_)CLOCK_CONTROL                                    |
|       00402Ch 4       (WLAN_)BIAS_OVERRIDE                                    |
|       004030h 4       (WLAN_)WDT_CONTROL            ;\                        
|       004034h 4       (WLAN_)WDT_STATUS             ;                         |
|       004038h 4       (WLAN_)WDT                    ; Watchdog Timer          |
|       00403Ch 4       (WLAN_)WDT_COUNT              ;                         |
|       004040h 4       (WLAN_)WDT_RESET              ;/                        |
|       004044h 4       (WLAN_)INT_STATUS             ;-Interrupt Status        |
|       004048h 4       (WLAN_)LF_TIMER0              ;\                        
|       00404Ch 4       (WLAN_)LF_TIMER_COUNT0        ; Low-Freq Timer          |
|       004050h 4       (WLAN_)LF_TIMER_CONTROL0      ;                         |
|       004054h 4       (WLAN_)LF_TIMER_STATUS0       ;/                        |
|       004058h 4       (WLAN_)LF_TIMER1              ;\                        
|       00405Ch 4       (WLAN_)LF_TIMER_COUNT1        ; Low-Freq Timer          |
|       004060h 4       (WLAN_)LF_TIMER_CONTROL1      ;                         |
|       004064h 4       (WLAN_)LF_TIMER_STATUS1       ;/                        |
|       004068h 4       (WLAN_)LF_TIMER2              ;\                        
|       00406Ch 4       (WLAN_)LF_TIMER_COUNT2        ; Low-Freq Timer          |
|       004070h 4       (WLAN_)LF_TIMER_CONTROL2      ;                         |
|       004074h 4       (WLAN_)LF_TIMER_STATUS2       ;/                        |
|       004078h 4       (WLAN_)LF_TIMER3              ;\                        
|       00407Ch 4       (WLAN_)LF_TIMER_COUNT3        ; Low-Freq Timer          |
|       004080h 4       (WLAN_)LF_TIMER_CONTROL3      ;                         |
|       004084h 4       (WLAN_)LF_TIMER_STATUS3       ;/                        |
|       004088h 4       (WLAN_)HF_TIMER               ;\                        
|       00408Ch 4       (WLAN_)HF_TIMER_COUNT         ; High-Freq Timer         |
|       004090h 4       (WLAN_)HF_LF_COUNT      ;<--  ;                         |
|       004094h 4       (WLAN_)HF_TIMER_CONTROL       ;                         |
|       004098h 4       (WLAN_)HF_TIMER_STATUS        ;/                        |
|       00409Ch 4       (WLAN_)RTC_CONTROL            ;\                        
|       0040A0h 4       (WLAN_)RTC_TIME               ;                         |
|       0040A4h 4       (WLAN_)RTC_DATE               ;                         |
|       0040A8h 4       (WLAN_)RTC_SET_TIME           ; Real-Time Clock         |
|       0040ACh 4       (WLAN_)RTC_SET_DATE           ;                         |
|       0040B0h 4       (WLAN_)RTC_SET_ALARM          ;                         |
|       0040B4h 4       (WLAN_)RTC_CONFIG             ;                         |
|       0040B8h 4       (WLAN_)RTC_ALARM_STATUS       ;/                        |
|       0040BCh 4       (WLAN_)UART_WAKEUP                                      |
|       0040C0h 4       (WLAN_)RESET_CAUSE                                      |
|       0040C4h 4       (WLAN_)SYSTEM_SLEEP                                     |
|       0040C8h 4       (WLAN_)SDIO_WRAPPER                                     |
|       0040CCh 4       (WLAN_)MAC_SLEEP_CONTROL                                |
|       0040D0h 4       (WLAN_)KEEP_AWAKE                                       |
|       0040D4h 4       (WLAN_)LPO_CAL_TIME                 ;\                  
|       0040D8h 4       (WLAN_)LPO_INIT_DIVIDEND_INT        ;                   |
|       0040DCh 4       (WLAN_)LPO_INIT_DIVIDEND_FRACTION   ;                   |
|       0040E0h 4       (WLAN_)LPO_CAL                      ;                   |
|       0040E4h 4       (WLAN_)LPO_CAL_TEST_CONTROL         ;                   |
|       0040E8h 4       (WLAN_)LPO_CAL_TEST_STATUS          ;/                  |
|       0040ECh 4       (WLAN_)CHIP_ID                                          |
|       0040F0h 4       (WLAN_)DERIVED_RTC_CLK                                  |
|       0040F4h 4       MAC_PCU_SLP32_MODE                                      |
|       0040F8h 4       MAC_PCU_SLP32_WAKE                                      |
|       0040FCh 4       MAC_PCU_SLP32_INC                                       |
|       004100h 4       MAC_PCU_SLP_MIB1                                        |
|       004104h 4       MAC_PCU_SLP_MIB2                                        |
|       004108h 4       MAC_PCU_SLP_MIB3                                        |
|       00410Ch 4       MAC_PCU_SLP_BEACON          ;<-- hw2.0 only (not hw4.0) |
|       004110h 4       (WLAN_)POWER_REG            ;\located here in hw2.0     
|       004114h 4       (WLAN_)CORE_CLK_CTRL        ;/                          |
|       004118h 1x8     PAD0                        ;\                          
|       004120h 4x8     SDIO_SETUP_CIRCUIT[8]       ;                           |
|       004140h 4       SDIO_SETUP_CONFIG           ;                           |
|       004144h 4       CPU_SETUP_CONFIG            ; hw2.0 only (not hw4.0)    |
|       004148h 1x24    PAD1                        ;                           |
|       004160h 4x8     CPU_SETUP_CIRCUIT[8]        ;                           |
|       004180h 4       BB_SETUP_CONFIG             ;                           |
|       004184h 1x28    PAD2                        ;                           |
|       0041A0h 4x8     BB_SETUP_CIRCUIT[8]         ;/                          |
|       0041C0h 4       (WLAN_)GPIO_WAKEUP_CONTROL  ;-located here in hw2.0     |
+-------------------------------------------------------------------------------+
```


### Memory Controller (vmc_reg.h) (hw2.0)

```
+-------------------------------------------------------------------------+
|       008000h 4x32    (WLAN_)MC_TCAM_VALID[0..31]         ;\            
|       008080h 4x32    (WLAN_)MC_TCAM_MASK[0..31]          ; ROM Patches |
|       008100h 4x32    (WLAN_)MC_TCAM_COMPARE[0..31]       ;             |
|       008180h 4x32    (WLAN_)MC_TCAM_TARGET[0..31]        ;/            |
|       008200h 4       (WLAN_)ADDR_ERROR_CONTROL           ;\ADDR_ERROR  
|       008204h 4       (WLAN_)ADDR_ERROR_STATUS            ;/            |
+-------------------------------------------------------------------------+
```


### Serial UART (uart_reg.h) (hw2.0)

```
+-----------------------------------------------------------------------------------+
|       00C000h 4       (WLAN_UART_)RBR  - RX Data FIFO (R)           (when DLAB=0) |
|       00C000h 4       (WLAN_UART_)THR  - TX Data FIFO (W)           (when DLAB=0) |
|       00C000h 4       (WLAN_UART_)DLL  - Baudrate Divisor LSB (R/W) (when DLAB=1) |
|       00C004h 4       (WLAN_UART_)IER  - Interrupt Control (R/W)    (when DLAB=0) |
|       00C004h 4       (WLAN_UART_)DLH  - Baudrate Divisor MSB (R/W) (when DLAB=1) |
|       00C008h 4       (WLAN_UART_)IIR  - Interrupt Status (R)                     |
|       00C008h 4       (WLAN_UART_)FCR  - FIFO Control (W)                         |
|       00C00Ch 4       (WLAN_UART_)LCR  - Character Format Control (R/W)           |
|       00C010h 4       (WLAN_UART_)MCR  - Handshaking Control (R/W)                |
|       00C014h 4       (WLAN_UART_)LSR  - RX/TX Status (R) (W=don't do)            |
|       00C018h 4       (WLAN_UART_)MSR  - Handshaking Status (R) (W=don't do)      |
|       00C01Ch 4       (WLAN_UART_)SCR  - Scratch (R/W)                            |
|       00C020h 4       (WLAN_UART_)SRBR - (mirror of RBR?)          (when DLAB=0?) |
|       00C024h 1x4     PAD0                                                        |
|       00C028h 4       (WLAN_UART_)SIIR - (mirror or IIR?)                         |
|       00C02Ch 4       (WLAN_UART_?)MWR - Whatever "M Write Register?"             |
|       00C030h 1x4     PAD1                                                        |
|       00C034h 4       (WLAN_UART_)SLSR - (mirror or LSR?) <-- used by AR6002 ROM  |
|       00C038h 4       (WLAN_UART_)SMSR - (mirror of MSR?)                         |
|       00C03Ch 4       (WLAN_UART_?)MRR - Whatever "M Read Register?"              |
+-----------------------------------------------------------------------------------+
```


### Serial I2C/SPI Interface (si_reg.h) (hw2.0)

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


### GPIO Registers (gpio_reg.h) (hw2.0)

```
+-------------------------------------------------------------------------------------+
|       014000h 4       (WLAN_)GPIO_OUT          ;\GPIO Output Data                   
|       014004h 4       (WLAN_)GPIO_OUT_W1TS     ; (direct, and Write-1-To-Set/Clr)   |
|       014008h 4       (WLAN_)GPIO_OUT_W1TC     ;/                                   |
|       01400Ch 4       (WLAN_)GPIO_ENABLE       ;\GPIO Output Enable                 
|       014010h 4       (WLAN_)GPIO_ENABLE_W1TS  ; (direct, and Write-1-To-Set/Clr)   |
|       014014h 4       (WLAN_)GPIO_ENABLE_W1TC  ;/                                   |
|       014018h 4       (WLAN_)GPIO_IN           ;-GPIO Input                         |
|       01401Ch 4       (WLAN_)GPIO_STATUS       ;\GPIO Interrupt Status              
|       014020h 4       (WLAN_)GPIO_STATUS_W1TS  ; (direct, and Write-1-To-Set/Clr)   |
|       014024h 4       (WLAN_)GPIO_STATUS_W1TC  ;/                                   |
|       014028h 4       (WLAN_)GPIO_PIN0   ;GPIO0  Bluetooth coex BT_PRIORITY         |
|       01402Ch 4       (WLAN_)GPIO_PIN1   ;GPIO1  Bluetooth coex WLAN_ACTIVE         |
|       014030h 4       (WLAN_)GPIO_PIN2   ;GPIO2  Bluetooth coex BT_FREQ    ;I2C SCL |
|       014034h 4       (WLAN_)GPIO_PIN3   ;GPIO3  Bluetooth coex BT_ACTIVE  ;I2C SDA |
|       014038h 4       (WLAN_)GPIO_PIN4   ;GPIO4  SDIO/GSPI interface select         |
|       01403Ch 4       (WLAN_)GPIO_PIN5   ;GPIO5  SDIO/GSPI interface select         |
|       014040h 4       (WLAN_)GPIO_PIN6   ;GPIO6  -                                  |
|       014044h 4       (WLAN_)GPIO_PIN7   ;GPIO7  TRST for JTAG debug                |
|       014048h 4       (WLAN_)GPIO_PIN8   ;GPIO8  external 32kHz clock in            |
|       01404Ch 4       (WLAN_)GPIO_PIN9   ;GPIO9  I2C SCL  or SPI CLK                |
|       014050h 4       (WLAN_)GPIO_PIN10  ;GPIO10 I2C SDA  or SPI MISO               |
|       014054h 4       (WLAN_)GPIO_PIN11  ;GPIO11 UART RXD or SPI MOSI               |
|       014058h 4       (WLAN_)GPIO_PIN12  ;GPIO12 UART TXD or SPI /CS                |
|       01405Ch 4       (WLAN_)GPIO_PIN13  ;GPIO13 Reset in for JTAG debug            |
|       014060h 4       (WLAN_)GPIO_PIN14  ;GPIO14 UART CTS                           |
|       014064h 4       (WLAN_)GPIO_PIN15  ;GPIO15 UART RTS                           |
|       014068h 4       (WLAN_)GPIO_PIN16  ;GPIO16 -                                  |
|       01406Ch 4       (WLAN_)GPIO_PIN17  ;GPIO17 -                                  |
|       014070h 4       SDIO_PIN    - Config: Pad Pull/Strength                       |
|       014074h 4       CLK_REQ_PIN - Config: Pad Pull/Strength/AteOeLow              |
|       014078h 4       (WLAN_)SIGMA_DELTA                                            |
|       01407Ch 4       (WLAN_)DEBUG_CONTROL                                          |
|       014080h 4       (WLAN_)DEBUG_INPUT_SEL                                        |
|       014084h 4       (WLAN_)DEBUG_OUT                                              |
|       014088h 4       LA_CONTROL                                                    |
|       01408Ch 4       LA_CLOCK                                                      |
|       014090h 4       LA_STATUS                                                     |
|       014094h 4       LA_TRIGGER_SAMPLE                                             |
|       014098h 4       LA_TRIGGER_POSITION                                           |
|       01409Ch 4       LA_PRE_TRIGGER                                                |
|       0140A0h 4       LA_POST_TRIGGER                                               |
|       0140A4h 4       LA_FILTER_CONTROL                                             |
|       0140A8h 4       LA_FILTER_DATA                                                |
|       0140ACh 4       LA_FILTER_WILDCARD                                            |
|       0140B0h 4       LA_TRIGGERA_DATA                                              |
|       0140B4h 4       LA_TRIGGERA_WILDCARD                                          |
|       0140B8h 4       LA_TRIGGERB_DATA                                              |
|       0140BCh 4       LA_TRIGGERB_WILDCARD                                          |
|       0140C0h 4       LA_TRIGGER                                                    |
|       0140C4h 4       LA_FIFO                                                       |
|       0140C8h 4x2     LA[0..1]                                                      |
|       0140D0h 4       ANT_PIN     - Config: Pad Pull/Strength                       |
|       0140D4h 4       ANTD_PIN    - Config: Pad Pull                                |
|       0140D8h 4       GPIO_PIN    - Config: Pad Pull/Strength                       |
|       0140DCh 4       GPIO_H_PIN  - Config: Pad Pull                                |
|       0140E0h 4       BT_PIN      - Config: Pad Pull/Strength                       |
|       0140E4h 4       BT_WLAN_PIN - Config: Pad Pull                                |
|       0140E8h 4       SI_UART_PIN - Config: Pad Pull/Strength                       |
|       0140ECh 4       CLK32K_PIN  - Config: Pad Pull                                |
|       0140F0h 4       (WLAN_)RESET_TUPLE_STATUS                                     |
+-------------------------------------------------------------------------------------+
```


### MBOX Registers (mbox_reg.h) (hw2.0)

```
+-------------------------------------------------------------------------+
|       018000h 4x4     (WLAN_)MBOX_FIFO[0..3]                            |
|       018010h 4       (WLAN_)MBOX_FIFO_STATUS                           |
|       018014h 4       (WLAN_)MBOX_DMA_POLICY                            |
|       018018h 4       (WLAN_)MBOX0_DMA_RX_DESCRIPTOR_BASE   ;\          
|       01801Ch 4       (WLAN_)MBOX0_DMA_RX_CONTROL           ; MBOX 0    |
|       018020h 4       (WLAN_)MBOX0_DMA_TX_DESCRIPTOR_BASE   ;           |
|       018024h 4       (WLAN_)MBOX0_DMA_TX_CONTROL           ;/          |
|       018028h 4       (WLAN_)MBOX1_DMA_RX_DESCRIPTOR_BASE   ;\          
|       01802Ch 4       (WLAN_)MBOX1_DMA_RX_CONTROL           ; MBOX 1    |
|       018030h 4       (WLAN_)MBOX1_DMA_TX_DESCRIPTOR_BASE   ;           |
|       018034h 4       (WLAN_)MBOX1_DMA_TX_CONTROL           ;/          |
|       018038h 4       (WLAN_)MBOX2_DMA_RX_DESCRIPTOR_BASE   ;\          
|       01803Ch 4       (WLAN_)MBOX2_DMA_RX_CONTROL           ; MBOX 2    |
|       018040h 4       (WLAN_)MBOX2_DMA_TX_DESCRIPTOR_BASE   ;           |
|       018044h 4       (WLAN_)MBOX2_DMA_TX_CONTROL           ;/          |
|       018048h 4       (WLAN_)MBOX3_DMA_RX_DESCRIPTOR_BASE   ;\          
|       01804Ch 4       (WLAN_)MBOX3_DMA_RX_CONTROL           ; MBOX 3    |
|       018050h 4       (WLAN_)MBOX3_DMA_TX_DESCRIPTOR_BASE   ;           |
|       018054h 4       (WLAN_)MBOX3_DMA_TX_CONTROL           ;/          |
|       018058h 4       (WLAN_)MBOX_INT_STATUS                ;\Interrupt 
|       01805Ch 4       (WLAN_)MBOX_INT_ENABLE                ;/          |
|       018060h 4       (WLAN_)INT_HOST                                   |
|       018064h 1x28    PAD0                                              |
|       018080h 4x8     (WLAN_)LOCAL_COUNT[0..7]                          |
|       0180A0h 4x8     (WLAN_)COUNT_INC[0..7]                            |
|       0180C0h 4x8     (WLAN_)LOCAL_SCRATCH[0..7]                        |
|       0180E0h 4       (WLAN_)USE_LOCAL_BUS                              |
|       0180E4h 4       (WLAN_)SDIO_CONFIG                                |
|       0180E8h 4       (WLAN_)MBOX_DEBUG                                 |
|       0180ECh 4       (WLAN_)MBOX_FIFO_RESET                            |
|       0180F0h 4x4     (WLAN_)MBOX_TXFIFO_POP[0..3]                      |
|       018100h 4x4     (WLAN_)MBOX_RXFIFO_POP[0..3]                      |
|       018110h 4       (WLAN_)SDIO_DEBUG                                 |
|       018114h 1x7916  PAD1                                              |
|       01A000h 4x2048  (WLAN_)HOST_IF_WINDOW[0..2047]                    |
+-------------------------------------------------------------------------+
```


### Analog Intf Registers (analog_reg.h) (hw2.0)

```
+----------------------------------------------------------------------------+
|       01C000h 4       SYNTH_SYNTH1        ;\                               
|       01C004h 4       SYNTH_SYNTH2        ;                                |
|       01C008h 4       SYNTH_SYNTH3        ;                                |
|       01C00Ch 4       SYNTH_SYNTH4        ; also defined in "synth_reg.h"  |
|       01C010h 4       SYNTH_SYNTH5        ;                                |
|       01C014h 4       SYNTH_SYNTH6        ;                                |
|       01C018h 4       SYNTH_SYNTH7        ;                                |
|       01C01Ch 4       SYNTH_SYNTH8        ;/                               |
|       01C020h 4       RF5G_RF5G1          ;\also defined in "rf5G_reg.h"   
|       01C024h 4       RF5G_RF5G2          ;/                               |
|       01C028h 4       RF2G_RF2G1          ;\also defined in "rf2G_reg.h"   
|       01C02Ch 4       RF2G_RF2G2          ;/                               |
|       01C030h 4       TOP_GAIN            ;\also defined in "top_reg.h"    
|       01C034h 4       TOP_TOP             ;/                               |
|       01C038h 4       BIAS_BIAS_SEL       ;\                               
|       01C03Ch 4       BIAS_BIAS1          ; also defined in "bias_reg.h"   |
|       01C040h 4       BIAS_BIAS2          ;                                |
|       01C044h 4       BIAS_BIAS3          ;/                               |
|       01C048h 4       TXPC_TXPC           ;\also defined in "txpc_reg.h"   
|       01C04Ch 4       TXPC_MISC           ;/                               |
|       01C050h 4       RXTXBB_RXTXBB1      ;\                               
|       01C054h 4       RXTXBB_RXTXBB2      ; also defined in "rxtxbb_reg.h" |
|       01C058h 4       RXTXBB_RXTXBB3      ;                                |
|       01C05Ch 4       RXTXBB_RXTXBB4      ;/                               |
|       01C060h 4       ADDAC_ADDAC1        ;-also defined in "addac.h"      |
|       01C064h 1x1Ch   -                                                    |
+----------------------------------------------------------------------------+
```


### More Analog Intf Registers (analog_intf_reg.h) (hw2.0)

```
+---------------------------------------------------------------------------------+
|       01C080h 4       SW_OVERRIDE         ;\                                    
|       01C084h 4       SIN_VAL             ; defined ONLY in "analog_intf_reg.h" |
|       01C088h 4       SW_SCLK             ;                                     |
|       01C08Ch 4       SW_CNTL             ;/                                    |
+---------------------------------------------------------------------------------+
```


### MAC PCU Registers (mac_pcu.h) (hw2.0)

```
+-----------------------------------------------------------------------------------+
|       028000h (00h) - REG_STA_ID0             ;aka MAC_PCU_STA_ADDR_L32           |
|       028004h (01h) - REG_STA_ID1             ;aka MAC_PCU_STA_ADDR_U16           |
|       028008h (02h) - REG_BSS_ID0             ;aka MAC_PCU_BSSID_L32              |
|       02800Ch (03h) - REG_BSS_ID1             ;aka MAC_PCU_BSSID_U16              |
|       028010h (04h) - MAC_PCU_REG_BCNRSSI     ;aka MAC_PCU_BCN_RSSI_AVE           |
|       028014h (05h) - REG_TIME_OUT            ;aka MAC_PCU_ACK_CTS_TIMEOUT        |
|       028018h (06h) - MAC_PCU_REG_BCNSIG      ;aka MAC_PCU_BCN_RSSI_CTL           |
|       02801Ch (07h) - REG_USEC                ;aka MAC_PCU_USEC_LATENCY           |
|       028020h (08h) - REG_BEACON                                                  |
|       028024h (09h) - REG_CFP_PERIOD          ;aka (MAC_???)PCU_MAX_CFP_DUR (?)   |
|       028028h (0Ah) - REG_TIMER0                                                  |
|       02802Ch (0Bh) - REG_TIMER1                                                  |
|       028030h (0Ch) - REG_TIMER2                                                  |
|       028034h (0Dh) - REG_TIMER3                                                  |
|       028038h (0Eh) - REG_CFP_DUR             ;aka (MAC_???)PCU_MAX_CFP_DUR (?)   |
|       02803Ch (0Fh) - REG_RX_FILTER           ;aka MAC_PCU_RX_FILTER              |
|       028040h (10h) - REG_MCAST_FIL0          ;aka MAC_PCU_MCAST_FILTER_L32       |
|       028044h (11h) - REG_MCAST_FIL1          ;aka MAC_PCU_MCAST_FILTER_U32       |
|       028048h (12h) - MAC_PCU_REG_DIAGSW      ;aka MAC_PCU_DIAG_SW                |
|       02804Ch (13h) - REG_TSF_L32                                                 |
|       028050h (14h) - REG_TSF_U32                                                 |
|       028054h (15h) - REG_TST_ADDAC           ;aka MAC_PCU_TST_ADDAC              |
|       028058h (16h) - REG_DEF_ANT             ;aka MAC_PCU_DEF_ANTENNA            |
|       02805Ch (17h) - MAC_PCU_REG_MUTE_MASKS0 ;aka MAC_PCU_AES_MUTE_MASK_0        |
|       028060h (18h) - MAC_PCU_REG_MUTE_MASKS1 ;aka MAC_PCU_AES_MUTE_MASK_1        |
|       028064h (19h) - MAC_PCU_REG_GATED_CLKS  ;aka MAC_PCU_GATED_CLKS             |
|       028068h (1Ah) - MAC_PCU_REG_OBS2        ;aka MAC_PCU_OBS_BUS_2              |
|       02806Ch (1Bh) - MAC_PCU_REG_OBS1        ;aka MAC_PCU_OBS_BUS_1              |
|       028070h (1Ch..1Fh) - N/A                                                    |
|       028080h (20h) - REG_LAST_TSTP           ;aka MAC_PCU_LAST_BEACON_TSF (?)    |
|       028084h (21h) - REG_NAV                 ;aka MAC_PCU_NAV                    |
|       028088h (22h) - REG_RTS_OK              ;aka MAC_PCU_RTS_SUCCESS_CNT        |
|       02808Ch (23h) - REG_RTS_FAIL            ;aka MAC_PCU_RTS_FAIL_CNT           |
|       028090h (24h) - REG_ACK_FAIL            ;aka MAC_PCU_ACK_FAIL_CNT           |
|       028094h (25h) - REG_FCS_FAIL            ;aka MAC_PCU_FCS_FAIL_CNT           |
|       028098h (26h) - REG_BEACON_CNT          ;aka MAC_PCU_BEACON_CNT             |
|       02809Ch (27h..2Fh) - N/A                                                    |
|       0280C0h (30h) - MAC_PCU_REG_XRMODE      ;aka MAC_PCU_XRMODE                 |
|       0280C4h (31h) - MAC_PCU_REG_XRDEL       ;aka MAC_PCU_XRDEL                  |
|       0280C8h (32h) - MAC_PCU_REG_XRTO        ;aka MAC_PCU_XRTO                   |
|       0280CCh (33h) - MAC_PCU_REG_XRCRP       ;aka MAC_PCU_XRCRP                  |
|       0280D0h (34h) - MAC_PCU_REG_XRSTMP      ;aka MAC_PCU_XRSTMP                 |
|       0280D4h (35h) - MAC_PCU_REG_SLP1        ;aka MAC_PCU_SLP1 ;\moved to        
|       0280D8h (36h) - MAC_PCU_REG_SLP2        ;aka MAC_PCU_SLP2 ; 004xxxh/005xxxh |
|       0280DCh (37h) - (//MAC_PCU_REG_SLP3)    ;aka MAC_PCU_SLP3 ;/in hw4/hw6 (!)  |
|       0280E0h (38h) - MAC_PCU_REG_BSSMSKL     ;aka MAC_PCU_ADDR1_MASK_L32         |
|       0280E4h (39h) - MAC_PCU_REG_BSSMSKH     ;aka MAC_PCU_ADDR1_MASK_U16         |
|       0280E8h (3Ah) - MAC_PCU_REG_TPC         ;aka MAC_PCU_TPC                    |
|       0280ECh (3Bh) - MAC_PCU_REG_TFC         ;aka MAC_PCU_TX_FRAME_CNT           |
|       0280F0h (3Ch) - MAC_PCU_REG_RFC         ;aka MAC_PCU_RX_FRAME_CNT           |
|       0280F4h (3Dh) - MAC_PCU_REG_RCC         ;aka MAC_PCU_RX_CLEAR_CNT           |
|       0280F8h (3Eh) - MAC_PCU_REG_CC          ;aka MAC_PCU_CYCLE_CNT              |
|       0280FCh (3Fh) - MAC_PCU_REG_QT1         ;aka MAC_PCU_QUIET_TIME_1           |
|       028100h (40h) - MAC_PCU_REG_QT2         ;aka MAC_PCU_QUIET_TIME_2           |
|       028104h (41h) - MAC_PCU_REG_TSF                                             |
|       028108h (42h) - MAC_PCU_REG_NOACK       ;aka MAC_PCU_QOS_NO_ACK             |
|       02810Ch (43h) - MAC_PCU_REG_PHYERR      ;aka MAC_PCU_PHY_ERROR_MASK         |
|       028110h (44h) - MAC_PCU_REG_XRLAT       ;aka MAC_PCU_XRLAT                  |
|       028114h (45h) - MAC_PCU_REG_ACKSIFS_RESERVED                                |
|       028118h (46h) - MAC_PCU_REG_MICQOSCTL   ;aka MAC_PCU_MIC_QOS_CONTROL        |
|       02811Ch (47h) - MAC_PCU_REG_MICQOSSEL   ;aka MAC_PCU_MIC_QOS_SELECT         |
|       028120h (48h) - MAC_PCU_REG_MISCMODE    ;aka MAC_PCU_MISC_MODE              |
|       028124h (49h) - MAC_PCU_REG_FILTOFDM    ;aka MAC_PCU_FILTER_OFDM_CNT        |
|       028128h (4Ah) - MAC_PCU_REG_FILTCCK     ;aka MAC_PCU_FILTER_CCK_CNT         |
|       02812Ch (4Bh) - MAC_PCU_REG_PHYCNT1     ;aka MAC_PCU_PHY_ERR_CNT_1          |
|       028130h (4Ch) - MAC_PCU_REG_PHYCNTMASK1 ;aka MAC_PCU_PHY_ERR_CNT_1_MASK     |
|       028134h (4Dh) - MAC_PCU_REG_PHYCNT2     ;aka MAC_PCU_PHY_ERR_CNT_2          |
|       028138h (4Eh) - MAC_PCU_REG_PHYCNTMASK2 ;aka MAC_PCU_PHY_ERR_CNT_2_MASK     |
|       02813Ch (4Fh) - MAC_PCU_REG_TSFTHRESH   ;aka MAC_PCU_TSF_THRESHOLD          |
|       028140h (50h) - outcommented:MAC_PCU_REG_TSFCAL ;Misc                       |
|       028144h (51h) - MAC_PCU_REG_PHYERR_EIFS ;aka MAC_PCU_PHY_ERROR_EIFS_MASK    |
|       028148h (52h) - outcommented:MAC_PCU_REG_SYNC1 ;Time                        |
|       02814Ch (53h) - outcommented:MAC_PCU_REG_SYNC2 ;Misc                        |
|       028150h (54h) - outcommented:MAC_PCU_REG_SYNC3 ;MCAST Addr_L                |
|       028154h (55h) - outcommented:MAC_PCU_REG_SYNC4 ;MCAST Addr_U                |
|       028158h (56h) - outcommented:MAC_PCU_REG_SYNC5 ;RX Time                     |
|       02815Ch (57h) - outcommented:MAC_PCU_REG_SYNC6 ;INC                         |
|       028160h (58h) - outcommented:MAC_PCU_REG_SYNC7 ;Last Time                   |
|       028164h (59h) - outcommented:MAC_PCU_REG_SYNC8 ;Updated Time                |
|       028168h (5Ah) - MAC_PCU_REG_PHYCNT3     ;aka MAC_PCU_PHY_ERR_CNT_3          |
|       02816Ch (5Bh) - MAC_PCU_REG_PHYCNTMASK3 ;aka MAC_PCU_PHY_ERR_CNT_3_MASK     |
|       028170h (5Ch) - MAC_PCU_REG_BTMODE      ;aka MAC_PCU_BLUETOOTH_MODE         |
|       028174h (5Dh) - MAC_PCU_REG_BTWEIGHT    ;aka MAC_PCU_BLUETOOTH_WEIGHTS      |
|       028178h (5Eh) - MAC_PCU_REG_HCF         ;aka MAC_PCU_HCF_TIMEOUT            |
|       02817Ch (5Fh) - MAC_PCU_REG_BTMODE2     ;aka MAC_PCU_BLUETOOTH_MODE2        |
|       028180h (60h..67h) - MAC_PCU_REG_BFCOEF1[0..7]                              |
|       0281A0h (68h..6Fh) - N/A                                                    |
|       0281C0h (70h) - MAC_PCU_REG_BFCOEF2                                         |
|       0281C4h (71h) - MAC_PCU_REG_KCMASK                                          |
|       0281C8h (72h..73h) - N/A                                                    |
|       0281D0h (74h) - MAC_PCU_REG_TXSIFS      ;aka MAC_PCU_TXSIFS                 |
|       0281D4h (75h..7Ah) - N/A                                                    |
|       0281ECh (7Bh) - MAC_PCU_REG_TXOP_X      ;aka MAC_PCU_TXOP_X                 |
|       0281F0h (7Ch) - MAC_PCU_REG_TXOP_0_3    ;aka MAC_PCU_TXOP_0_3               |
|       0281F4h (7Dh) - MAC_PCU_REG_TXOP_4_7    ;aka MAC_PCU_TXOP_4_7               |
|       0281F8h (7Eh) - MAC_PCU_REG_TXOP_8_11   ;aka MAC_PCU_TXOP_8_11              |
|       0281FCh (7Fh) - MAC_PCU_REG_TXOP_12_15  ;aka MAC_PCU_TXOP_12_15             |
|       028200h (80h..87h) - MAC_PCU_REG_GNRCTMR_N[0..7]  ;aka GENERIC_TIMERSxxx?   |
|       028220h (88h..8Fh) - MAC_PCU_REG_GNRCTMR_P[0..7]  ;aka GENERIC_TIMERSxxx?   |
|       028240h (90h) - MAC_PCU_REG_GNRCTMR_M   ;aka MAC_PCU_GENERIC_TIMERS_MODE    |
|       028244h (91h) - MAC_PCU_REG_SLP32_MODE                                      |
|       028248h (92h) - MAC_PCU_REG_SLP32_WAKE                                      |
|       02824Ch (93h) - MAC_PCU_REG_SLP32_TSF_INC                                   |
|       028250h (94h) - MAC_PCU_REG_SLPMIB1                                         |
|       028254h (95h) - MAC_PCU_REG_SLPMIB2                                         |
|       028258h (96h) - MAC_PCU_REG_SLPMIB3                                         |
|       02825Ch (97h) - MAC_PCU_REG_MISCMODE2   ;aka MAC_PCU_MISC_MODE2             |
|       028260h (98h) - MAC_PCU_REG_SLP4                                            |
|       028264h (99h) - MAC_PCU_REG_SLP5                                            |
|       028268h (9Ah) - MAC_PCU_REG_MCICTL   ;\                                     
|       02826Ch (9Bh) - MAC_PCU_REG_MCIISR   ;                                      |
|       028270h (9Ch) - MAC_PCU_REG_MCIIER   ;                                      |
|       028274h (9Dh) - MAC_PCU_REG_MCIWLP   ;                                      |
|       028278h (9Eh) - MAC_PCU_REG_MCIARW   ;                                      |
|       02827Ch (9Fh) - MAC_PCU_REG_MCIARR   ; whatever MCI stuff                   |
|       028280h (A0h) - MAC_PCU_REG_MCIADW   ;                                      |
|       028284h (A1h) - MAC_PCU_REG_MCIADR   ;                                      |
|       028288h (A2h) - MAC_PCU_REG_MCIFRW   ;                                      |
|       02828Ch (A3h) - MAC_PCU_REG_MCIFRR   ;                                      |
|       028290h (A4h) - MAC_PCU_REG_MCIQRW   ;                                      |
|       028294h (A5h) - MAC_PCU_REG_MCIQRR   ;                                      |
|       028298h (A6h) - MAC_PCU_REG_MCIGRW   ;                                      |
|       02829Ch (A7h) - MAC_PCU_REG_MCIGRR   ;                                      |
|       0282A0h (A8h) - MAC_PCU_REG_MCISTAT  ;/                                     |
|       0282A4h (A9h) - MAC_PCU_REG_BASIC_RATE_SET0 ;aka MAC_PCU_BASIC_RATE_SET0    |
|       0282A8h (AAh) - MAC_PCU_REG_BASIC_RATE_SET1 ;aka MAC_PCU_BASIC_RATE_SET1    |
|       0282ACh (ABh) - MAC_PCU_REG_BASIC_RATE_SET2 ;aka MAC_PCU_BASIC_RATE_SET2    |
|       0282B0h (ACh) - MAC_PCU_REG_SEC_BSSID_L32   ;aka MAC_PCU_BSSID2_L32         |
|       0282B4h (ADh) - MAC_PCU_REG_SEC_BSSID_U16   ;aka MAC_PCU_BSSID2_U16         |
|       0282B8h (AEh..13Fh) - N/A                                                   |
|       028500h (140h..17Fh) - MAC_PCU_REG_FTYPE[0..3Fh]                            |
|       028600h (180h..19Fh) - N/A                                                  |
|       028680h (1A0h..1BFh) - MAC_PCU_REG_ACKSIFSMEM_RESERVED[0..1Fh]              |
|       028700h (1C0h..1DFh) - MAC_PCU_REG_DUR[0..1Fh]                              |
|       028780h (1E0h..1EFh) - N/A                                                  |
|       0287C0h (1F0h..1F7h) - MAC_PCU_REG_RTD[0..7]                                |
|       0287E0h (1F8h..1FFh) - MAC_PCU_REG_DTR[0..7]                                |
|       028800h (200h..5FFh) - MAC_PCU_REG_KC[0..3FFh]  ;aka KC = KEY_CACHE ?       |
+-----------------------------------------------------------------------------------+
```


### Undocumented hw2 registers

```
+------------------------------------------------------------------------------------+
|       029800h ?       Used in hw2, but undocumented... maybe BASEBAND_0 alike hw4? |
|       02A000h ?       Used in hw2, but undocumented... maybe BASEBAND_1 alike hw4? |
|       030000h ?       Used in hw2, but undocumented... maybe mode switch?          |
+------------------------------------------------------------------------------------+
```

Note: 030000h seems to be used only in AR6013/AR6014 (not AR6002), maybe RDMA or EFUSE alike hw4, or maybe for atheros/mitsumi mode switch.



