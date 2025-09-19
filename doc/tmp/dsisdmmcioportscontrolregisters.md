# DSi SD/MMC I/O Ports: Control Registers


### 4004802h/4004A02h - SD_CARD_PORT_SELECT

```
+-------------------------------------------------------------------------------------+
|       15-11 Always zero                                                             |
|       10    Unknown (should be set on write) (reads as zero) (1=CardIRQ off!) (W)   |
|       9-8   Unknown (Always 2 for SD/4004802h, always 1 for SDIO/4004A02h)    (R)   |
|       7-4   Always zero                                                             |
|       3-1   Unknown (read/write-able)                                         (R/W) |
|       0     Port Select (0=SD Card Slot, 1=Onboard eMMC) (for SDIO: Unknown)  (R/W) |
+-------------------------------------------------------------------------------------+
```

Known written values are 0400h and 0401h for SD/MMC. The register is left uninitialized for SDIO.

### 4004828h/4004A28h - SD_CARD_OPTION - Card Option Setup

```
+-------------------------------------------------------------------------------------+
|       15   undoc Bus Width (0=4bit, 1=1bit)                                   (R/W) |
|       14   undoc Unknown (usually set)                                        (R?)  |
|       13-9 0     Always zero                                                        |
|       8    undoc Unknown (firmware tries to toggle this after CLK change?)    (W?)  |
|       7-4  RTO   Data start/busy timeout (2000h SHL 0..14, or 15=100h SDCLK's)(R/W) |
|       0-3  TO?   SIGSTATE detect delay   (400h SHL 0..14, or 15=100h HCLK's)  (R/W) |
+-------------------------------------------------------------------------------------+
```

See Timeout Notes below for details.

### 4004824h/4004A24h - SD_CARD_CLK_CTL Card Clock Control

```
+-------------------------------------------------------------------------------------+
|       15-11 Always zero          ;unlike Toshiba: no HCLK divider-disable in bit15) |
|       10    Unknown (0=Normal, 1=Unknown, doesn't affect SDCLK output?)       (R/W) |
|       9     SDCLK Auto pause (0=Normal, 1=Freeze SDCLK output when inactive)  (R/W) |
|       8     SDCLK Pin Enable (0=Force SDCLK=LOW, 1=Output SDCLK=HCLK/n)       (R/W) |
|       7-0   HCLK Div (0,1,2,4,8,16,32,64,128 = Div2,4,8,16,32,64,128,256,512) (R/W) |
+-------------------------------------------------------------------------------------+
```

The DSi uses HCLK=33.513982 MHz, the SDCLK pin can range from HCLK/512=65kHz to HCLK/2=16.757MHz, max transfer rate would be thus 8MByte/s in 4bit mode.
### Max CLK speed:
Observe that card detection/initialization should be done at lower CLK rate than during normal operation.
For SD/MMC initialization: The DSi firmware starts with HCLK/128=262kHz (max allowed would be 400kHz for MMC). This is actually required: The DSi\'s onboard Samsung KMAPF0000M-S998 eMMC chip won\'t respond to ALL_GET_CID when trying to use 16MHz CLK). Higher CLK can be used once when detecting max speed (see TRAN_SPEED in CSD register; when extracting bits from CSD: mind the different 120bit-without-CRC vs 128bit-with-CRC notations).
For SDIO/Wifi initialization: The DSi firmware starts with HCLK/256=131kHz, and switches to HCLK/2=16.757MHz after reading SDIO Bus Speed register (Function0:00013h).
After init, one can use the detected speeds (see above), it should be also safe to assume that HCLK/2=16.757MHz is always supported after initialization (all SD devices should support at least 25MHz, and all(?) MMC devices at least 26MHz, and all DSi SDIO/Wifi boards should be fast enough either).
### Notes:
The SDCLK pins are permanently pulsed, even for devices deselected via SD_CARD_PORT_SELECT.0, and even if no CMD or DATA is being transferred. However, the DSi firmware is usually stopping SDCLK via Bit8=0 when not accessing SD/MMC (doing so may reduce noise and power consumption).
Setting bit9, or to trying to set more than one bit in bit7-0 will freeze the SDCLK output (in this case SDCLK may get stuck HIGH or LOW, unlike Bit8=0 which forces LOW).
Odd Effect: Setting bit10-8 to ALL ones, combined with an invalid HDIV (eg. writing 0703h) does disable CardIRQ on Data1 pin.

### 4004808h/4004A08h - SD_STOP_INTERNAL_ACTION

```
+-----------------------------------------------------------------------------------+
|       15-9   Always zero                                                          |
|       8      Auto-Stop (1=Automatically send CMD12 after BLK_COUNT blocks)  (R/W) |
|       7-1    Always zero                                                          |
|       0      Unknown (firmware often clears this bit, but never sets it?)   (R/W) |
+-----------------------------------------------------------------------------------+
```

Existing code does set bit8 (prior to changing SD_DATA16_BLK_COUNT).
Existing code does clear bit0 (alongsides with IRQ enable/acknowledge or so).
Note: Bit8 MUST be also set for SDIO with multiple blocks (although SDIO doesn\'t literally have CMD12).

### 40048E0h/4004AE0h - SD_SOFT_RESET - Software Reset

```
+--------------------------------------------------------------------------------+
|       15-3 Always zero                                                         |
|       2    Unknown (always 1)                                            (R?)  |
|       1    Unknown (always 1) (though firmware tries to toggle this bit) (R?)  |
|       0    SRST Soft Reset (0=Reset, 1=Release)                          (R/W) |
+--------------------------------------------------------------------------------+
```

Software should apply reset after sensing card insertion/removal, and (thereafter) release reset in case of card insertion. Software reset does acknowledge all IRQs (except that from SDIO /IRQ pin?), and does probably also reinitialize some other registers.
Clearing bit0 does force following settings (while and as long as Bit0=0):

```
+-------------------------------------------------------------------------------------+
|       SD_STOP_INTERNAL_ACTION   = 0000h                                             |
|       SD_RESPONSE0-7            = zerofilled                                        |
|       SD_IRQ_STATUS0-1          = all IRQ flags acknowledged                        |
|       SD_ERROR_DETAIL_STATUS0-1 = all bits cleared (except bit13/always set)        |
|       SD_CARD_CLK_CTL           = bit 8 and 10 cleared                              |
|       SD_CARD_OPTION            = 40EEh                                             |
|       SD_CARD_IRQ_STAT          = 0000h                                             |
|       Internal FIFO16 address is reset to first halfword of FIFO_A                  |
|       Reading FIFO16 returns 0000h (but old content reappears when releasing reset) |
+-------------------------------------------------------------------------------------+
```

All other registers seem to be left unaffected (including the extra IRQ flags in 4004900h); though there may be some further hidden effects (like aborting transfers or resetting internal registers).
Note: The DSi firmware does issue reset by toggling both bit0 and bit1, although bit1 does seem to be read-only (always 1), and trying to clear that bit doesn\'t seem to have any effect at all.

### Timeout Notes
Timeouts are counted in SDCLK units (the CLK-Pin rate selected in SD_CARD_CLK_CTL register). For Response-Timeouts, the timeout is fixed: Around 290h SDCLK\'s (preceeded by 30h SDCLK\'s for sending the command). For Data-Timeouts, the timeout can be selected in SD_CARD_OPTION.bit4-7, which is apparently what toshiba tried to describe as \"RTO\" bits. Values 0..14 select timeout \"2000h SHL 0..14 SDCLK\'s\" and value 15 selects \"100h SDCLK\'s\" (that, oddly, resulting in Data-timeout getting triggered before Response-timeout, which is rather nonsense since it\'s opposite of the actual transfer order).
For data/read, the timeout starts counting after transferring Command+Response. For data/write it starts after transferring Command+Response+DataBlock. The maximum duration for data timeouts (with RTO=14) would be around 8 seconds (at SDCLK=HCLK/2), or up to about 30 minutes (at HCLK/512).
One odd effect is that Response-Timeouts can occur (after 290h SDCLKs, and recursing the selected SDCLK=HCLK/n rate) even if SDCLK is stopped via SD_CARD_CLK_CTL.Bit8 (ie. the selected clock is kept running internally, and only the CLK-Pin output is forced LOW when Bit8=0).

### CFG9_SDMMC_CTL and SD_CARD_OPTION
On DSi, SD/MMC Slot power supply is always on (it takes about 3ms to reach the 3.3V after power on; if the console booted up and loaded data from eMMC, one can be sure that the SD/MMC Slot is properly powered up).
On 3DS, SD/MMC Slot power supply can be enabled/disabled, the bootrom does leave it disabled, so, before accessing SD/MMC Slot or before testing the card insert flag, FIRM software must enable it (set CFG9_SDMMC_CTL bit0=0 and usually bit9=1, it takes about 4.2ms to reach 3.3V, SD cards may take 1ms to boot up, for those 4.2ms+1ms delays, best set the SIGSTATE detect delay in SD_CARD_OPTION.bit0-3 to 09h, ie. circa 8ms).



