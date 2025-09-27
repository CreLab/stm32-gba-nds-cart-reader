# DSi Atheros Wifi - Internal I/O - 014000h - GPIO 18/26/57 pin (hw2/hw4/hw6)


### ATH:014000h/014000h/014000h - WLAN_GPIO_OUT ;GPIO Data Out ;hw2/hw4/hw6
### ATH:014004h/014004h/014004h - WLAN_GPIO_OUT_W1TS ;Write-1-to-Set ;hw2/hw4/hw6
### ATH:014008h/014008h/014008h - WLAN_GPIO_OUT_W1TC ;Write-1-to-Clr ;hw2/hw4/hw6
### ATH:01400Ch - WLAN_GPIO_OUT_HIGH ;for pin32 and up ;hw6
### ATH:014010h - WLAN_GPIO_OUT_W1TS_HIGH ;for pin32 and up ;hw6
### ATH:014014h - WLAN_GPIO_OUT_W1TC_HIGH ;for pin32 and up ;hw6

```
+-----------------------------------------------------------------------+
|       0-17   hw2: DATA (for pin 0..17)                                |
|       0-25   hw4: DATA (for pin 0..25)                                |
|       0-63   hw6: DATA (for pin 0..56) (and bit57-63=unused or so?)   |
+-----------------------------------------------------------------------+
```


### ATH:01400Ch/01400Ch/014018h - WLAN_GPIO_ENABLE ;GPIO Out Enable ;hw2/hw4/hw6
### ATH:014010h/014010h/01401Ch - WLAN_GPIO_ENABLE_W1TS ;Wr-1-to-Set ;hw2/hw4/hw6
### ATH:014014h/014014h/014020h - WLAN_GPIO_ENABLE_W1TC ;Wr-1-to-Clr ;hw2/hw4/hw6
### ATH:014024h - WLAN_GPIO_ENABLE_HIGH ;for pin32 and up ;hw6
### ATH:014028h - WLAN_GPIO_ENABLE_W1TS_HIGH ;for pin32 and up ;hw6
### ATH:01402Ch - WLAN_GPIO_ENABLE_W1TC_HIGH ;for pin32 and up ;hw6

```
+-----------------------------------------------------------------------+
|       0-17   hw2: DATA (for pin 0..17)                                |
|       0-25   hw4: DATA (for pin 0..25)                                |
|       0-63   hw6: DATA (for pin 0..56) (and bit57-63=unused or so?)   |
+-----------------------------------------------------------------------+
```


### ATH:014018h/014018h/014030h - WLAN_GPIO_IN - GPIO Data In ;hw2/hw4/hw6
### ATH:014038h - WLAN_GPIO_IN_HIGH ;for pin32 and up ;hw6

```
+-----------------------------------------------------------------------+
|       0-17   hw2: DATA (for pin 0..17)                                |
|       0-25   hw4: DATA (for pin 0..25)                                |
|       0-63   hw6: DATA (for pin 0..56) (and bit57-63=unused or so?)   |
+-----------------------------------------------------------------------+
```


### ATH:01401Ch/01401Ch/014034h - WLAN_GPIO_STATUS - GPIO Interrupt ;hw2/hw4/hw6
### ATH:014020h/014020h/014040h - WLAN_GPIO_STATUS_W1TS ;Wr-1-to-Set ;hw2/hw4/hw6
### ATH:014024h/014024h/014044h - WLAN_GPIO_STATUS_W1TC ;Wr-1-to-Clr ;hw2/hw4/hw6
### ATH:01403Ch - WLAN_GPIO_STATUS_HIGH ;for pin32 and up ;hw6
### ATH:014048h - WLAN_GPIO_STATUS_W1TS_HIGH ;for pin32 and up ;hw6
### ATH:01404Ch - WLAN_GPIO_STATUS_W1TC_HIGH ;for pin32 and up ;hw6

```
+--------------------------------------------------------------------------+
|       0-17   hw2: INTERRUPT (for pin 0..17)                              |
|       0-25   hw4: INTERRUPT (for pin 0..25)                              |
|       0-63   hw6: INTERRUPT (for pin 0..56) (and bit57-63=unused or so?) |
+--------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ______________________________ hw2 GPIO ports ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:014028h - GPIO_PIN0 ;GPIO0 Bluetooth coex BT_PRIORITY
### ATH:01402Ch - GPIO_PIN1 ;GPIO1 Bluetooth coex WLAN_ACTIVE
### ATH:014030h - GPIO_PIN2 ;GPIO2 Bluetooth coex BT_FREQUENCY ;I2C SCL
### ATH:014034h - GPIO_PIN3 ;GPIO3 Bluetooth coex BT_ACTIVE ;I2C_SDA
### ATH:014038h - GPIO_PIN4 ;GPIO4 SDIO/GSPI interface select
### ATH:01403Ch - GPIO_PIN5 ;GPIO5 SDIO/GSPI interface select
### ATH:014040h - GPIO_PIN6 ;GPIO6 -
### ATH:014044h - GPIO_PIN7 ;GPIO7 TRST for JTAG debug
### ATH:014048h - GPIO_PIN8 ;GPIO8 external 32kHz clock in
### ATH:01404Ch - GPIO_PIN9 ;GPIO9 I2C SCL or SPI CLK
### ATH:014050h - GPIO_PIN10 ;GPIO10 I2C SDA or SPI MISO
### ATH:014054h - GPIO_PIN11 ;GPIO11 UART RXD or SPI MOSI
### ATH:014058h - GPIO_PIN12 ;GPIO12 UART TXD or SPI /CS
### ATH:01405Ch - GPIO_PIN13 ;GPIO13 Reset in for JTAG debug
### ATH:014060h - GPIO_PIN14 ;GPIO14 UART CTS
### ATH:014064h - GPIO_PIN15 ;GPIO15 UART RTS
### ATH:014068h - GPIO_PIN16 ;GPIO16 -
### ATH:01406Ch - GPIO_PIN17 ;GPIO17 -

```
+-----------------------------------------------------------------------+
|       0      SOURCE                                                   |
|       1      -                                                        |
|       2      PAD_DRIVER                                               |
|       3-6    -                                                        |
|       7-9    INT_TYPE                                                 |
|       10     WAKEUP_ENABLE                                            |
|       11-12  CONFIG                                                   |
+-----------------------------------------------------------------------+
```

Note: The I2C EEPROM in DSi/3DS is accessed via Pin9/10 on AR6002, and Pin2/3 on AR6013/AR6014.


```
+-----------------------------------------------------------------------------------+
|      ______________________________ hw4 GPIO ports ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:014028h - WLAN_GPIO_PIN0 ;GPIO0 Bluetooth coex BT_FREQUENCY
### ATH:01402Ch - WLAN_GPIO_PIN1 ;GPIO1 Bluetooth coex WLAN_ACTIVE
### ATH:014030h - WLAN_GPIO_PIN2 ;GPIO2 Bluetooth coex BT_ACTIVE
### ATH:014034h - WLAN_GPIO_PIN3 ;GPIO3 Bluetooth coex BT_PRIORITY
### ATH:014038h - WLAN_GPIO_PIN4 ;GPIO4 -
### ATH:01403Ch - WLAN_GPIO_PIN5 ;GPIO5 JTAG TMS input
### ATH:014040h - WLAN_GPIO_PIN6 ;GPIO6 JTAG TCK input
### ATH:014044h - WLAN_GPIO_PIN7 ;GPIO7 JTAG TDI input
### ATH:014048h - WLAN_GPIO_PIN8 ;GPIO8 JTAG TDO output
### ATH:01404Ch - WLAN_GPIO_PIN9 ;GPIO9 SDIO CMD
### ATH:014050h - WLAN_GPIO_PIN10 ;GPIO10 SDIO D3
### ATH:014054h - WLAN_GPIO_PIN11 ;GPIO11 SDIO D2
### ATH:014058h - WLAN_GPIO_PIN12 ;GPIO12 SDIO D1
### ATH:01405Ch - WLAN_GPIO_PIN13 ;GPIO13 SDIO D0
### ATH:014060h - WLAN_GPIO_PIN14 ;GPIO14 SDIO CLK
### ATH:014064h - WLAN_GPIO_PIN15 ;GPIO15 HCI UART TXD
### ATH:014068h - WLAN_GPIO_PIN16 ;GPIO16 HCI UART RTS
### ATH:01406Ch - WLAN_GPIO_PIN17 ;GPIO17 HCI UART RXD
### ATH:014070h - WLAN_GPIO_PIN18 ;GPIO18 HCI UART CTS
### ATH:014074h - WLAN_GPIO_PIN19 ;GPIO19 SDIO/GSPI interface select
### ATH:014078h - WLAN_GPIO_PIN20 ;GPIO20 SDIO/GSPI interface select
### ATH:01407Ch - WLAN_GPIO_PIN21 ;GPIO21 external input sleep clock
### ATH:014080h - WLAN_GPIO_PIN22 ;GPIO22 wake on wireless input (WOW)
### ATH:014084h - WLAN_GPIO_PIN23 ;GPIO23 reference clk output to BT chip
### ATH:014088h - WLAN_GPIO_PIN24 ;GPIO24 request clk from BT chip
### ATH:01408Ch - WLAN_GPIO_PIN25 ;GPIO25 request reference clk (CLK_REQ)

```
+-----------------------------------------------------------------------------+
|       0      SOURCE                                                         |
|       1      -                                                              |
|       2      PAD_DRIVER                                                     |
|       3-4    PAD_STRENGTH   ;\pull/strength supported for PIN0..PIN22 only  
|       5-6    PAD_PULL       ;/(bit3-6 are unused in PIN23..PIN25 registers) |
|       7-9    INT_TYPE                                                       |
|       10     WAKEUP_ENABLE                                                  |
|       11-13  CONFIG                                                         |
+-----------------------------------------------------------------------------+
```

AR6003 datasheet assigns only the above stuff with a single UART, although the AR6003 should additionally support a DBG_UART (and I2C).


```
+-----------------------------------------------------------------------------------+
|      ______________________________ hw6 GPIO ports ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:014050h - WLAN_GPIO_PIN0 ;GPIO0 or SDIO_CMD
### ATH:014054h - WLAN_GPIO_PIN1 ;GPIO1 or SDIO_D3
### ATH:014058h - WLAN_GPIO_PIN2 ;GPIO2 or SDIO_D2
### ATH:01405Ch - WLAN_GPIO_PIN3 ;GPIO3 or SDIO_D1
### ATH:014060h - WLAN_GPIO_PIN4 ;GPIO4 or SDIO_D0
### ATH:014064h - WLAN_GPIO_PIN5 ;GPIO5 or SDIO_CLK
### ATH:014068h - WLAN_GPIO_PIN6
### ATH:01406Ch - WLAN_GPIO_PIN7
### ATH:014070h - WLAN_GPIO_PIN8
### ATH:014074h - WLAN_GPIO_PIN9
### ATH:014078h - WLAN_GPIO_PIN10
### ATH:01407Ch - WLAN_GPIO_PIN11
### ATH:014080h - WLAN_GPIO_PIN12
### ATH:014084h - WLAN_GPIO_PIN13
### ATH:014088h - WLAN_GPIO_PIN14
### ATH:01408Ch - WLAN_GPIO_PIN15
### ATH:014090h - WLAN_GPIO_PIN16
### ATH:014094h - WLAN_GPIO_PIN17
### ATH:014098h - WLAN_GPIO_PIN18
### ATH:01409Ch - WLAN_GPIO_PIN19
### ATH:0140A0h - WLAN_GPIO_PIN20
### ATH:0140A4h - WLAN_GPIO_PIN21
### ATH:0140A8h - WLAN_GPIO_PIN22
### ATH:0140ACh - WLAN_GPIO_PIN23
### ATH:0140B0h - WLAN_GPIO_PIN24
### ATH:0140B4h - WLAN_GPIO_PIN25
### ATH:0140B8h - WLAN_GPIO_PIN26
### ATH:0140BCh - WLAN_GPIO_PIN27
### ATH:0140C0h - WLAN_GPIO_PIN28
### ATH:0140C4h - WLAN_GPIO_PIN29
### ATH:0140C8h - WLAN_GPIO_PIN30
### ATH:0140CCh - WLAN_GPIO_PIN31
### ATH:0140D0h - WLAN_GPIO_PIN32
### ATH:0140D4h - WLAN_GPIO_PIN33
### ATH:0140D8h - WLAN_GPIO_PIN34
### ATH:0140DCh - WLAN_GPIO_PIN35
### ATH:0140E0h - WLAN_GPIO_PIN36
### ATH:0140E4h - WLAN_GPIO_PIN37
### ATH:0140E8h - WLAN_GPIO_PIN38
### ATH:0140ECh - WLAN_GPIO_PIN39
### ATH:0140F0h - WLAN_GPIO_PIN40
### ATH:0140F4h - WLAN_GPIO_PIN41
### ATH:0140F8h - WLAN_GPIO_PIN42
### ATH:0140FCh - WLAN_GPIO_PIN43
### ATH:014100h - WLAN_GPIO_PIN44
### ATH:014104h - WLAN_GPIO_PIN45
### ATH:014108h - WLAN_GPIO_PIN46
### ATH:01410Ch - WLAN_GPIO_PIN47
### ATH:014110h - WLAN_GPIO_PIN48
### ATH:014114h - WLAN_GPIO_PIN49
### ATH:014118h - WLAN_GPIO_PIN50
### ATH:01411Ch - WLAN_GPIO_PIN51
### ATH:014120h - WLAN_GPIO_PIN52
### ATH:014124h - WLAN_GPIO_PIN53
### ATH:014128h - WLAN_GPIO_PIN54
### ATH:01412Ch - WLAN_GPIO_PIN55
### ATH:014130h - WLAN_GPIO_PIN56

```
+-----------------------------------------------------------------------+
|       0      SOURCE                                                   |
|       1      -                                                        |
|       2      PAD_DRIVER                                               |
|       3-4    PAD_STRENGTH                                             |
|       5-6    PAD_PULL                                                 |
|       7-9    INT_TYPE                                                 |
|       10     WAKEUP_ENABLE                                            |
|       11-14  CONFIG                                                   |
+-----------------------------------------------------------------------+
```

AR6004 datasheet assigns only six SDIO signals to GPIO pins. However, signals similar as on AR6002/AR6003 should exist (I2C/SPI, UART, etc.), plus TWO additional UARTs).


```
+------------------------------------------------------------------------------------+
|      _____________________________ hw2/hw4/hw6 stuff _____________________________ |
+------------------------------------------------------------------------------------+
```


### ATH:014078h/01409Ch/01413Ch - WLAN_SIGMA_DELTA ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TARGET                                                   |
|       8-15   PRESCALAR      ;uh, scalar?                              |
|       16     ENABLE                                                   |
+-----------------------------------------------------------------------+
```


### ATH:01407Ch/0140A8h/01414Ch - WLAN_DEBUG_CONTROL ;hw2/hw4/hw6

```
+--------------------------------------------------------------------------+
|       0      ENABLE                 ;-hw2/hw4/hw6                        |
|       1      hw2: OBS_OE_L          ;-hw2 only (bit1 removed in hw4/hw6) |
+--------------------------------------------------------------------------+
```


### ATH:014080h/0140ACh/014150h - WLAN_DEBUG_INPUT_SEL ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-3    SRC                    ;-hw2/hw4/hw6                     |
|       4-5    hw4/hw6: SHIFT         ;-hw4/hw6                         |
+-----------------------------------------------------------------------+
```


### ATH:014084h/0140B0h/014154h - WLAN_DEBUG_OUT ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------------------+
|       0-17   DATA (whatever) (always 18bit, no matter if GPIO with 18,25,57 pins) |
+-----------------------------------------------------------------------------------+
```


### ATH:0140F0h/0140B4h/014158h - WLAN_RESET_TUPLE_STATUS ;hw2/hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    PIN_RESET_TUPLE                                          |
|       8-11   TEST_RESET_TUPLE                                         |
+-----------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      _______________________________ hw4/hw6 stuff _______________________________ |
+------------------------------------------------------------------------------------+
```


### ATH:014090h/014134h - SDIO ;hw4/hw6
### ATH:014160h - SDIO2 ;hw6
### ATH:014164h - SDHC ;hw6

```
+-----------------------------------------------------------------------+
|       0      PINS_EN                                                  |
+-----------------------------------------------------------------------+
```


### ATH:014098h/014138h - WL_SOC_APB ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      TOGGLE                                                   |
+-----------------------------------------------------------------------+
```


### ATH:0140A0h/014140h - WL_BOOTSTRAP ;hw4/hw6

```
+-------------------------------------------------------------------------------------+
|       0-22   hw4: STATUS (23bit) ;maybe for pin 0..22 (but not pin 23-25 ?)         |
|       0-11   hw6: STATUS (12bit) ;maybe for pin 0..57 (with below "CORE_BOOTSTRAP") |
|       12     hw6: CPU_MBIST_EN                                                      |
+-------------------------------------------------------------------------------------+
```


### ATH:014144h - CORE_BOOTSTRAP_LOW ;hw6

```
+------------------------------------------------------------------------------------+
|       0-31   hw6: STATUS (32bit) (extra bits, expanding STATUS in "WL_BOOTSTRAP"?) |
+------------------------------------------------------------------------------------+
```


### ATH:014148h - CORE_BOOTSTRAP_HIGH ;hw6

```
+------------------------------------------------------------------------------------+
|       0-12   hw6: STATUS (13bit) (extra bits, expanding STATUS in "WL_BOOTSTRAP"?) |
+------------------------------------------------------------------------------------+
```


### ATH:0140B8h/01415Ch - ANTENNA_SLEEP_CONTROL/ANTENNA_CONTROL ;hw4/hw6

```
+---------------------------------------------------------------------------+
|       0-4    hw4: ENABLE   (5bit)           ;\                            
|       5-9    hw4: VALUE    (5bit)           ; hw4 "ANTENNA_SLEEP_CONTROL" |
|       10-14  hw4: OVERRIDE (5bit)           ;/                            |
|       0-3    hw6: ENABLE   (4bit)           ;\                            
|       4-7    hw6: VALUE    (4bit)           ;                             |
|       8-11   hw6: OVERRIDE (4bit)           ;                             |
|       12-13  hw6: LED_SEL  (2bit)           ; hw6 "ANTENNA_CONTROL"       |
|       14     hw6: SPI_MODE                  ;                             |
|       15     hw6: SPI_CS                    ;                             |
|       16     hw6: RX_CLEAR                  ;/                            |
+---------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      _________________________________ hw6 stuff _________________________________ |
+------------------------------------------------------------------------------------+
```


### ATH:014168h - AMBA_DEBUG_BUS ;hw6

```
+-----------------------------------------------------------------------+
|       0-4    SEL                                                      |
+-----------------------------------------------------------------------+
```


### ATH:01416Ch - CPU_MBIST ;hw6

```
+-----------------------------------------------------------------------+
|       0      DONE                                                     |
|       1      GLOBAL_FAIL                                              |
|       2-10   BLOCK_FAIL                                               |
+-----------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      _________________________________ hw4 stuff _________________________________ |
+------------------------------------------------------------------------------------+
```


### ATH:014094h - FUNC_BUS ;hw4

```
+-----------------------------------------------------------------------+
|       0-21   OE_L                                                     |
|       22     GPIO_MODE                                                |
+-----------------------------------------------------------------------+
```


### ATH:0140A4h - CLOCK_GPIO ;hw4

```
+-----------------------------------------------------------------------+
|       0      hw4: BT_CLK_OUT_EN                                       |
|       1      hw4: BT_CLK_REQ_EN                                       |
|       2      hw4: CLK_REQ_OUT_EN                                      |
+-----------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      ____________________________ hw2 GPIO PIN config ____________________________ |
+------------------------------------------------------------------------------------+
```


### ATH:0140D4h - ANTD_PIN - Config: Pad Pull ;hw2
### ATH:0140DCh - GPIO_H_PIN - Config: Pad Pull ;hw2
### ATH:0140E4h - BT_WLAN_PIN - Config: Pad Pull ;hw2
### ATH:0140ECh - CLK32K_PIN - Config: Pad Pull ;hw2

```
+-----------------------------------------------------------------------+
|       0-1    hw2: PAD_PULL                                            |
+-----------------------------------------------------------------------+
```


### ATH:014070h - SDIO_PIN - Config: Pad Pull/Strength ;hw2
### ATH:0140D0h - ANT_PIN - Config: Pad Pull/Strength ;hw2
### ATH:0140D8h - GPIO_PIN - Config: Pad Pull/Strength ;hw2
### ATH:0140E0h - BT_PIN - Config: Pad Pull/Strength ;hw2
### ATH:0140E8h - SI_UART_PIN - Config: Pad Pull/Strength ;hw2

```
+-----------------------------------------------------------------------+
|       0-1    hw2: PAD_STRENGTH                                        |
|       2-3    hw2: PAD_PULL                                            |
+-----------------------------------------------------------------------+
```


### ATH:014074h - CLK_REQ_PIN - Config: Pad Pull/Strength/AteOeLow ;hw2

```
+-----------------------------------------------------------------------+
|       0-1    hw2: PAD_STRENGTH                                        |
|       2-3    hw2: PAD_PULL                                            |
|       4      hw2: ATE_OE_L                                            |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      _______________________________ hw2 LA stuff _______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:014088h - LA_CONTROL ;hw2

```
+-----------------------------------------------------------------------+
|       0      hw2: TRIGGERED                                           |
|       1      hw2: RUN                                                 |
+-----------------------------------------------------------------------+
```


### ATH:01408Ch - LA_CLOCK ;hw2

```
+-----------------------------------------------------------------------+
|       0-7    hw2: DIV                                                 |
+-----------------------------------------------------------------------+
```


### ATH:014090h - LA_STATUS ;hw2

```
+-----------------------------------------------------------------------+
|       0      hw2: INTERRUPT                                           |
+-----------------------------------------------------------------------+
```


### ATH:014094h - LA_TRIGGER_SAMPLE ;hw2

```
+-----------------------------------------------------------------------+
|       0-15   hw2: COUNT                                               |
+-----------------------------------------------------------------------+
```


### ATH:014098h - LA_TRIGGER_POSITION ;hw2

```
+-----------------------------------------------------------------------+
|       0-15   hw2: VALUE                                               |
+-----------------------------------------------------------------------+
```


### ATH:01409Ch - LA_PRE_TRIGGER ;hw2
### ATH:0140A0h - LA_POST_TRIGGER ;hw2

```
+-----------------------------------------------------------------------+
|       0-15   hw2: COUNT                                               |
+-----------------------------------------------------------------------+
```


### ATH:0140A4h - LA_FILTER_CONTROL ;hw2

```
+-----------------------------------------------------------------------+
|       0      hw2: DELTA                                               |
+-----------------------------------------------------------------------+
```


### ATH:0140A8h - LA_FILTER_DATA ;hw2
### ATH:0140B0h - LA_TRIGGERA_DATA ;hw2
### ATH:0140B8h - LA_TRIGGERB_DATA ;hw2
### ATH:0140ACh - LA_FILTER_WILDCARD ;hw2
### ATH:0140B4h - LA_TRIGGERA_WILDCARD ;hw2
### ATH:0140BCh - LA_TRIGGERB_WILDCARD ;hw2

```
+------------------------------------------------------------------------------+
|       0-17   hw2: MATCH                 ... maybe related to GPIO_PIN0..17 ? |
+------------------------------------------------------------------------------+
```


### ATH:0140C0h - LA_TRIGGER ;hw2

```
+-----------------------------------------------------------------------+
|       0-2    hw2: EVENT                                               |
+-----------------------------------------------------------------------+
```


### ATH:0140C4h - LA_FIFO ;hw2

```
+-----------------------------------------------------------------------+
|       0      hw2: EMPTY                                               |
|       1      hw2: FULL                                                |
+-----------------------------------------------------------------------+
```


### ATH:0140C8h..0140CCh - LA\[0..1\] ;hw2

```
+-----------------------------------------------------------------------+
|       0-17   hw2: DATA                                                |
+-----------------------------------------------------------------------+
```




