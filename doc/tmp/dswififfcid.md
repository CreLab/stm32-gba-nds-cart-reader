# DS Wifi FFC ID


### Wifi FCC ID
The wifi hardware has been registered by Mitsumi, Hon Hai, and Nintendo themselves:

```
+-----------------------------------------------------------------------+
|       https://fccid.io/BKE - Nintendo                                 |
|       https://fccid.io/EW4 - Mitsumi                                  |
|       https://fccid.io/MCL - Hon Hai (Foxconn)                        |
+-----------------------------------------------------------------------+
```

The above webpages include some unrelated stuff (like bluetooth), and some duplicate entries. The wifi/console related entries are:

```
+-------------------------------------------------------------------------------------+
|       https://fccid.io/EW4-AGBWA      GBA        ;\GBA wireless adaptor             
|       https://fccid.io/EW4-OXYWA      GBA-Micro  ;/(not wifi/wlan compatible)       |
|       https://fccid.io/BKENTR001      NDS (non-remove-able board)                   |
|       https://fccid.io/BKEUSG-001     NDS-Lite (old remove-able board, with MM3155) |
|       https://fccid.io/EW4DWMW006     NDS-Lite (new remove-able board, with MM3218) |
|       https://fccid.io/BKERVL036      Wii                                           |
|       https://fccid.io/EW4DWMW004     Wii (mitsumi) (also W016, and maybe W014 ?)   |
|       https://fccid.io/MCLJ27H010     Wii (foxconn) (also H003 ?)                   |
|       https://fccid.io/EW4DWMW015     DSi (old wifi board, mitsumi)                 |
|       https://fccid.io/EW4DWMW024     DSi (new wifi board, mitsumi)                 |
|       https://fccid.io/MCLJ27H020     DSi (new wifi board, foxconn)                 |
|       https://fccid.io/EW4DWMW028     3DS (mitsumi)                                 |
|       https://fccid.io/MCLJ27H023     3DS (foxconn)                                 |
|       https://fccid.io/MCLJ27H02301   2DS (foxconn) (also in 3DS XL)                |
|       https://fccid.io/BKERED001      New3DS (on mainboard)                         |
+-------------------------------------------------------------------------------------+
```

The pages include test reports, photos (including some prototypes), and most interestingly, the Mitsumi \"Label location\" pages are including pinout & signal names for most wifi boards.

### DSi Wifi board pinout
<https://fccid.io/EW4DWMW024/Label/Label-format-and-location-1137926.pdf>
<https://fccid.io/EW4DWMW015/Label/Label-Location-1031953.pdf>

```
+-----------------------------------------------------------------------+
|       1  MX_SD_CLK    2  GND                                          |
|       3  GND          4  VDD_18                                       |
|       5  SDIO_DATA0   6  VDD_18                                       |
|       7  SDIO_DATA3   8  GND                                          |
|       9  SDIO_DATA1   10 VDD_33                                       |
|       11 SDIO_CMD     12 VDD_33                                       |
|       13 SDIO_DATA2   14 GND                                          |
|       15 JTAG_TDO     16 ATH_TX_H                                     |
|       17 JTAG_TMS     18 SYS_RST_L                                    |
|       19 GND          20 JTAG_TDI                                     |
|       21 CLK32k       22 JTAG_TCK                                     |
|       23 GND          24 JTAG_TRST_L                                  |
|       25 NC(VDD28_TP) 26 SEL_ATH_L                                    |
|       27 SPI_CS2      28 W_B      /FLASH_WP                           |
|       29 BBP_SLEEP    30 SPI_CLK                                      |
|       31 RF_SLEEP     32 SPI_DO   MISO                                |
|       33 RF_SCS       34 SPI_DI   MOSI                                |
|       35 BBP_SCS      36 CCA                                          |
|       37 BB_RF_SDO    38 RXPE                                         |
|       39 BB_RF_SDI    40 TRDATA                                       |
|       41 BB_RF_SCLK   42 GND                                          |
|       43 NC(VDD18_TP) 44 TRCLK                                        |
|       45 GND          46 TRRDY                                        |
|       47 MCLK         48 TXPE                                         |
|       49 GND          50 RESET                                        |
+-----------------------------------------------------------------------+
```


### DS-Lite Wifi board DWM-W006 pinout
<https://fccid.io/EW4DWMW006/Label/ID-label-format-and-location-706511.pdf>

```
+-----------------------------------------------------------------------+
|       1  GND          16 +3.3V                                        |
|       2  TXPE         17 GND                                          |
|       3  RXPE         18 RF_SCS                                       |
|       4  CCA          19 BBP_SLEEP                                    |
|       5  TRRDY        20 BBP_SCS                                      |
|       6  GND          21 RF_SLEEP                                     |
|       7  TRCLK        22 RESET                                        |
|       8  TRDATA       23 GND                                          |
|       9  GND          24 SPI_CLK                                      |
|       10 BB_RF_SDO    25 SPI_DI   MOSI                                |
|       11 BB_RF_SDI    26 SPI_DO   MISO                                |
|       12 BB_RF_SCLK   27 W_B      /FLASH_WP                           |
|       13 GND          28 SPI_CS2                                      |
|       14 MCLK         29 LD       ?                                   |
|       15 GND          30 GND                                          |
+-----------------------------------------------------------------------+
```


### Wii Wifi board
<https://fccid.io/EW4DWMW004/Label/ID-Label-670426.pdf>

```
+-----------------------------------------------------------------------+
|       1  GND          12 VDD3.3                                       |
|       2  SDIO_DATA_2  13 GND                                          |
|       3  SDIO_DATA_1  14 GPIO_0                                       |
|       4  GND          15 GND                                          |
|       5  SDIO_CLK     16 SDIO_DATA_3                                  |
|       6  GND          17 SDIO_DATA_0                                  |
|       7  GPIO_1       18 GND                                          |
|       8  GND          19 SDIO_CMD                                     |
|       9  N.C.(VDD1.8) 20 GND                                          |
|       10 N.C.(VDD1.8) 21 ANT_A (MAIN)                                 |
|       11 VDD3.3       22 ANT_B (AUX)                                  |
+-----------------------------------------------------------------------+
```


### 3DS Wifi Board DWM-W028
<https://fccid.io/EW4DWMW028/Label/ID-label-location-1272988.pdf>

```
+-----------------------------------------------------------------------+
|       1  MCLK         2  RF_CSRF                                      |
|       3  GND          4  BB_CSBB                                      |
|       5  RXPE         6  BB_RF_SDIN                                   |
|       7  TXPE         8  BB_RF_SDOUT                                  |
|       9  CCA          10 BB_RF_SCK                                    |
|       11 TRDATA       12 GND                                          |
|       13 TRCLK        14 BBP_SLEEP_L                                  |
|       15 TRRDY        16 RF_SLEEP_L                                   |
|       17 TRST_L       18 SEL_ATH_L                                    |
|       19 GND          20 GND                                          |
|       21 SDIO_DATA_0  22 JTAG_TDO                                     |
|       23 SDIO_DATA_1  24 JTAG_TMS                                     |
|       25 SDIO_DATA_2  26 JTAG_TDI                                     |
|       27 SDIO_DATA_3  28 JTAG_TCK                                     |
|       29 GND          30 SPI_CS2                                      |
|       31 SDIO_CLK     32 W_B      /FLASH_WP                           |
|       33 GND          34 SPI_CLK                                      |
|       35 SDIO_CMD     36 SPI_DO   MISO                                |
|       37 UART_TXD     38 SPI_DI   MOSI                                |
|       39 UART_RXD     40 SYS_RST_L                                    |
|       41 GND          42 ATH_TX_H                                     |
|       43 CLK32k       44 RESET                                        |
|       45 GND          46 GND                                          |
|       47 VDD_18       48 VDD_33                                       |
|       49 VDD_18       50 VDD_33                                       |
+-----------------------------------------------------------------------+
```

Functionally same as DSi, but not pin-compatible, and with two UART pins (instead of the NC pins).

GBA-Micro: device has two channels only: 2426.248MHz and 2456.576MHz.



