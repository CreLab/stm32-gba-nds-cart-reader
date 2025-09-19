# DS Wifi I/O Map


### Notice
Wifi Registers & RAM cannot be written to by STRB opcodes (ignored).

### Registers - NDS7 - 4808000h..4808FFFh

```
+-------------------------------------------------------------------------------------+
|       Address  Dir   Name            r/w  [Init] Description                        |
|       4808000h R     W_ID            ---- [1440] Chip ID (1440h=DS, C340h=DS-Lite)  |
|       4808004h R/W   W_MODE_RST      9fff [0000] Mode/Reset                         |
|       4808006h R/W   W_MODE_WEP      --7f [0000] Mode/Wep modes                     |
|       4808008h R/W   W_TXSTATCNT     ffff [0000] Beacon Status Request              |
|       480800Ah R/W   W_X_00Ah        ffff [0000] [bit7 - ingore rx duplicates]      |
|       4808010h R/W   W_IF            ackk [0000] Wifi Interrupt Request Flags       |
|       4808012h R/W   W_IE            ffff [0000] Wifi Interrupt Enable              |
|       4808018h R/W   W_MACADDR_0     ffff [0000] Hardware MAC Address, 1st 2 bytes  |
|       480801Ah R/W   W_MACADDR_1     ffff [0000] Hardware MAC Address, next 2 bytes |
|       480801Ch R/W   W_MACADDR_2     ffff [0000] Hardware MAC Address, last 2 bytes |
|       4808020h R/W   W_BSSID_0       ffff [0000] BSSID (first 2 bytes)              |
|       4808022h R/W   W_BSSID_1       ffff [0000] BSSID (next 2 bytes)               |
|       4808024h R/W   W_BSSID_2       ffff [0000] BSSID (last 2 bytes)               |
|       4808028h R/W   W_AID_LOW       ---f [0000] usually as lower 4bit of AID value |
|       480802Ah R/W   W_AID_FULL      -7ff [0000] AID value assigned by a BSS.       |
|       480802Ch R/W   W_TX_RETRYLIMIT ffff [0707] Tx Retry Limit (set from 00h-FFh)  |
|       480802Eh R/W   W_INTERNAL      ---1 [0000]                                    |
|       4808030h R/W   W_RXCNT         ff0e [0000] Receive control                    |
|       4808032h R/W   W_WEP_CNT       ffff [0000] WEP engine enable                  |
|       4808034h R?    W_INTERNAL      0000 [0000] bit0,1 (see ports 004h,040h,1A0h)  |
+-------------------------------------------------------------------------------------+
```

### Power-Down Registers (and Random Generator)

```
+-----------------------------------------------------------------------+
|       4808036h R/W   W_POWER_US      ---3 [0001]                      |
|       4808038h R/W   W_POWER_TX      ---7 [0003]                      |
|       480803Ch R/W   W_POWERSTATE    -r-2 [0200]                      |
|       4808040h R/W   W_POWERFORCE    8--1 [0000]                      |
|       4808044h R     W_RANDOM        0xxx [0xxx]                      |
|       4808048h R/W   W_POWER_?       ---3 [0000]                      |
+-----------------------------------------------------------------------+
```

### Receive Control/Memory

```
+-----------------------------------------------------------------------+
|       4808050h R/W   W_RXBUF_BEGIN   ffff [4000]                      |
|       4808052h R/W   W_RXBUF_END     ffff [4800]                      |
|       4808054h R     W_RXBUF_WRCSR   0rrr [0000]                      |
|       4808056h R/W   W_RXBUF_WR_ADDR -fff [0000]                      |
|       4808058h R/W   W_RXBUF_RD_ADDR 1ffe [0000]                      |
|       480805Ah R/W   W_RXBUF_READCSR -fff [0000]                      |
|       480805Ch R/W   W_RXBUF_COUNT   -fff [0000]                      |
|       4808060h R     W_RXBUF_RD_DATA rrrr [xxxx]                      |
|       4808062h R/W   W_RXBUF_GAP     1ffe [0000]                      |
|       4808064h R/W   W_RXBUF_GAPDISP -fff [0000]                      |
+-----------------------------------------------------------------------+
```

### Transmit Control/Memory

```
+-------------------------------------------------------------------------------------+
|       4808068h R/W   W_TXBUF_WR_ADDR 1ffe [0000]                                    |
|       480806Ch R/W   W_TXBUF_COUNT   -fff [0000]                                    |
|       4808070h W     W_TXBUF_WR_DATA xxxx [xxxx]                                    |
|       4808074h R/W   W_TXBUF_GAP     1ffe [0000]                                    |
|       4808076h R/W   W_TXBUF_GAPDISP 0fff [0000]                                    |
|       4808078h W     W_INTERNAL      mirr [mirr] Read: Mirror of 068h               |
|       4808080h R/W   W_TXBUF_BEACON  ffff [0000] Beacon Transmit Location           |
|       4808084h R/W   W_TXBUF_TIM     --ff [0000] Beacon TIM Index in Frame Body     |
|       4808088h R/W   W_LISTENCOUNT   --ff [0000] Listen Count                       |
|       480808Ch R/W   W_BEACONINT     -3ff [0064] Beacon Interval                    |
|       480808Eh R/W   W_LISTENINT     --ff [0000] Listen Interval                    |
|       4808090h R/W   W_TXBUF_CMD     ffff [0000] Multiplay Command                  |
|       4808094h R/W   W_TXBUF_REPLY1  ffff [0000] Multiplay Next Reply               |
|       4808098h R     W_TXBUF_REPLY2  0000 [0000] Multiplay Current Reply            |
|       480809Ch R/W   W_INTERNAL      ffff [0050] value 4x00h --> preamble+x*12h us? |
|       48080A0h R/W   W_TXBUF_LOC1    ffff [0000]                                    |
|       48080A4h R/W   W_TXBUF_LOC2    ffff [0000]                                    |
|       48080A8h R/W   W_TXBUF_LOC3    ffff [0000]                                    |
|       48080ACh W     W_TXREQ_RESET   fixx [0050]                                    |
|       48080AEh W     W_TXREQ_SET     fixx [0050]                                    |
|       48080B0h R     W_TXREQ_READ    --1f [0010]                                    |
|       48080B4h W     W_TXBUF_RESET   0000 [0000]    (used by firmware part4)        |
|       48080B6h R     W_TXBUSY        0000 [0000]    (used by firmware part4)        |
|       48080B8h R     W_TXSTAT        0000 [0000]                                    |
|       48080BAh ?     W_INTERNAL      0000 [0000]                                    |
|       48080BCh R/W   W_PREAMBLE      ---3 [0001]                                    |
|       48080C0h R/W x W_CMD_TOTALTIME ffff [0000]    (used by firmware part4)        |
|       48080C4h R/W x W_CMD_REPLYTIME ffff [0000]    (used by firmware part4)        |
+-------------------------------------------------------------------------------------+
```

### xxx

```
+-----------------------------------------------------------------------+
|       48080C8h ?     W_INTERNAL      0000 [0000]                      |
|       48080D0h R/W   W_RXFILTER      1fff [0401]                      |
|       48080D4h R/W   W_CONFIG_0D4h   ---3 [0001]                      |
|       48080D8h R/W   W_CONFIG_0D8h   -fff [0004]                      |
|       48080DAh R/W   W_RX_LEN_CROP   ffff [0602]                      |
|       48080E0h R/W   W_RXFILTER2     ---f [0008]                      |
+-----------------------------------------------------------------------+
```

### Wifi Timers

```
+----------------------------------------------------------------------------------+
|       48080E8h R/W   W_US_COUNTCNT   ---1 [0000] Microsecond counter enable      |
|       48080EAh R/W   W_US_COMPARECNT ---1 [0000] Microsecond compare enable      |
|       48080ECh R/W   W_CONFIG_0ECh   3f1f [3F03]                                 |
|       48080EEh R/W   W_CMD_COUNTCNT  ---1 [0001]                                 |
|       48080F0h R/W   W_US_COMPARE0   fc-- [FC00] Microsecond compare, bits 0-15  |
|       48080F2h R/W   W_US_COMPARE1   ffff [FFFF] Microsecond compare, bits 16-31 |
|       48080F4h R/W   W_US_COMPARE2   ffff [FFFF] Microsecond compare, bits 32-47 |
|       48080F6h R/W   W_US_COMPARE3   ffff [FFFF] Microsecond compare, bits 48-63 |
|       48080F8h R/W   W_US_COUNT0     ffff [0000] Microsecond counter, bits 0-15  |
|       48080FAh R/W   W_US_COUNT1     ffff [0000] Microsecond counter, bits 16-31 |
|       48080FCh R/W   W_US_COUNT2     ffff [0000] Microsecond counter, bits 32-47 |
|       48080FEh R/W   W_US_COUNT3     ffff [0000] Microsecond counter, bits 48-63 |
|       4808100h ?     W_INTERNAL      0000 [0000]                                 |
|       4808102h ?     W_INTERNAL      0000 [0000]                                 |
|       4808104h ?     W_INTERNAL      0000 [0000]                                 |
|       4808106h ?     W_INTERNAL      0000 [0000]                                 |
|       480810Ch R/W   W_CONTENTFREE   ffff [0000] ...                             |
|       4808110h R/W   W_PRE_BEACON    ffff [0000]                                 |
|       4808118h R/W   W_CMD_COUNT     ffff [0000]                                 |
|       480811Ch R/W   W_BEACON_COUNT  ffff [0000] reloaded with W_BEACONINT       |
+----------------------------------------------------------------------------------+
```

### Configuration Ports (and some other Registers)

```
+-------------------------------------------------------------------------------------+
|       4808120h R/W   W_CONFIG_120h   81ff [0048] init from firmware[04Ch]           |
|       4808122h R/W   W_CONFIG_122h   ffff [4840] init from firmware[04Eh]           |
|       4808124h R/W   W_CONFIG_124h   ffff [0000] init from firmware[05Eh], or 00C8h |
|       4808126h ?     W_INTERNAL      fixx [ 0080]                                   |
|       4808128h R/W   W_CONFIG_128h   ffff [0000] init from firmware[060h], or 07D0h |
|       480812Ah ?     W_INTERNAL      fixx [1000] lower 12bit same as W_CONFIG_128h  |
|       4808130h R/W   W_CONFIG_130h   -fff [0142] init from firmware[054h]           |
|       4808132h R/W   W_CONFIG_132h   8fff [8064] init from firmware[056h]           |
|       4808134h R/W   W_POST_BEACON   ffff [FFFF] ...                                |
|       4808140h R/W   W_CONFIG_140h   ffff [0000] init from firmware[058h], or xx    |
|       4808142h R/W   W_CONFIG_142h   ffff [2443] init from firmware[05Ah]           |
|       4808144h R/W   W_CONFIG_144h   --ff [0042] init from firmware[052h]           |
|       4808146h R/W   W_CONFIG_146h   --ff [0016] init from firmware[044h]           |
|       4808148h R/W   W_CONFIG_148h   --ff [0016] init from firmware[046h]           |
|       480814Ah R/W   W_CONFIG_14Ah   --ff [0016] init from firmware[048h]           |
|       480814Ch R/W   W_CONFIG_14Ch   ffff [162C] init from firmware[04Ah]           |
|       4808150h R/W   W_CONFIG_150h   ff3f [0204] init from firmware[062h], or 202h  |
|       4808154h R/W   W_CONFIG_154h   7a7f [0058] init from firmware[050h]           |
+-------------------------------------------------------------------------------------+
```

### Baseband Chip Ports

```
+----------------------------------------------------------------------------------+
|       4808158h W     W_BB_CNT        mirr [00B5] BB Access Start/Direction/Index |
|       480815Ah W     W_BB_WRITE      ???? [0000] BB Access data byte to write    |
|       480815Ch R     W_BB_READ       00rr [00B5] BB Access data byte read        |
|       480815Eh R     W_BB_BUSY       000r [0000] BB Access Busy flag             |
|       4808160h R/W   W_BB_MODE       41-- [0100] BB Access Mode                  |
|       4808168h R/W   W_BB_POWER      8--f [800D] BB Access Powerdown             |
+----------------------------------------------------------------------------------+
```

### Internal Stuff

```
+-----------------------------------------------------------------------+
|       480816Ah ?     W_INTERNAL      0000 [0001] (or 0000h?)          |
|       4808170h ?     W_INTERNAL      0000 [0000]                      |
|       4808172h ?     W_INTERNAL      0000 [0000]                      |
|       4808174h ?     W_INTERNAL      0000 [0000]                      |
|       4808176h ?     W_INTERNAL      0000 [0000]                      |
|       4808178h W     W_INTERNAL      fixx [0800] Read: mirror of 17Ch |
+-----------------------------------------------------------------------+
```

### RF Chip Ports

```
+-----------------------------------------------------------------------+
|       480817Ch R/W   W_RF_DATA2      ffff [0800]                      |
|       480817Eh R/W   W_RF_DATA1      ffff [C008]                      |
|       4808180h R     W_RF_BUSY       000r [0000]                      |
|       4808184h R/W   W_RF_CNT        413f [0018]                      |
+-----------------------------------------------------------------------+
```

### xxx

```
+-------------------------------------------------------------------------------------+
|       4808190h R/W   W_INTERNAL      ffff [0000]                                    |
|       4808194h R/W   W_TX_HDR_CNT    ---7 [0000] used by firmware part4 (0 or 6)    |
|       4808198h R/W   W_INTERNAL      ---f [0000]                                    |
|       480819Ch R     W_RF_PINS       fixx [0004]                                    |
|       48081A0h R/W   W_X_1A0h        -933 [0000] used by firmware part4 (0 or 823h) |
|       48081A2h R/W   W_X_1A2h        ---3 [0001] used by firmware part4             |
|       48081A4h R/W   W_X_1A4h        ffff [0000] "Rate used when signal test..."    |
+-------------------------------------------------------------------------------------+
```

### Wifi Statistics

```
+-----------------------------------------------------------------------------------+
|       48081A8h R     W_RXSTAT_INC_IF rrrr [0000] Stats Increment Flags            |
|       48081AAh R/W   W_RXSTAT_INC_IE ffff [0000] Stats Increment IRQ Enable       |
|       48081ACh R     W_RXSTAT_OVF_IF rrrr [0000] Stats Half-Overflow Flags        |
|       48081AEh R/W   W_RXSTAT_OVF_IE ffff [0000] Stats Half-Overflow IRQ Enable   |
|       48081B0h R/W   W_RXSTAT        --ff [0000]                                  |
|       48081B2h R/W   W_RXSTAT        ffff [0000] RX_LengthRateErrorCount          |
|       48081B4h R/W   W_RXSTAT        rrff [0000] ... firmware uses also MSB ... ? |
|       48081B6h R/W   W_RXSTAT        ffff [0000]                                  |
|       48081B8h R/W   W_RXSTAT        --ff [0000]                                  |
|       48081BAh R/W   W_RXSTAT        --ff [0000]                                  |
|       48081BCh R/W   W_RXSTAT        ffff [0000]                                  |
|       48081BEh R/W   W_RXSTAT        ffff [0000]                                  |
|       48081C0h R/W   W_TX_ERR_COUNT  --ff [0000] TransmitErrorCount               |
|       48081C4h R     W_RX_COUNT      fixx [0000]                                  |
+-----------------------------------------------------------------------------------+
```

\[1D0 - 1DE are 15 entries related to multiplayer response errors\]

```
+-----------------------------------------------------------------------+
|       48081D0h R/W   W_CMD_STAT      ff-- [0000]                      |
|       48081D2h R/W   W_CMD_STAT      ffff [0000]                      |
|       48081D4h R/W   W_CMD_STAT      ffff [0000]                      |
|       48081D6h R/W   W_CMD_STAT      ffff [0000]                      |
|       48081D8h R/W   W_CMD_STAT      ffff [0000]                      |
|       48081DAh R/W   W_CMD_STAT      ffff [0000]                      |
|       48081DCh R/W   W_CMD_STAT      ffff [0000]                      |
|       48081DEh R/W   W_CMD_STAT      ffff [0000]                      |
+-----------------------------------------------------------------------+
```

### Internal Diagnostics Registers (usually not used for anything)

```
+-------------------------------------------------------------------------------------+
|       48081F0h R/W   W_INTERNAL      ---3 [0000]                                    |
|       4808204h ?     W_INTERNAL      fixx [0000]                                    |
|       4808208h ?     W_INTERNAL      fixx [0000]                                    |
|       480820Ch W     W_INTERNAL      fixx [0050]                                    |
|       4808210h R     W_TX_SEQNO      fixx [0000]                                    |
|       4808214h R     W_RF_STATUS     XXXX [0009]    (used by firmware part4)        |
|       480821Ch W     W_IF_SET        fbff [0000] Force Interrupt (set bits in W_IF) |
|       4808220h R/W   W_RAM_DISABLE   ffff [0000] WifiRAM control                    |
|       4808224h R/W   W_INTERNAL      ---3 [0003]                                    |
|       4808228h W     W_X_228h        fixx [0000]    (used by firmware part4) (bit3) |
|       4808230h R/W   W_INTERNAL      --ff [0047]                                    |
|       4808234h R/W   W_INTERNAL      -eff [0EFF]                                    |
|       4808238h R/W   W_INTERNAL      ffff [0000] ;rx_seq_no-60h+/-x   ;why that?    |
|                                        ;other day: fixed value, not seq_no related? |
|       480823Ch ?     W_INTERNAL      fixx [0000] like W_TXSTAT... ONLY for beacons? |
|       4808244h R/W   W_X_244h        ffff [0000]    (used by firmware part4)        |
|       4808248h R/W   W_INTERNAL      ffff [0000]                                    |
|       480824Ch R     W_INTERNAL      fixx [0000] ;rx_mac_addr_0 ;\OverTheHedge      
|       480824Eh R     W_INTERNAL      fixx [0000] ;rx_mac_addr_1 ;/writes FFFFh?     |
|       4808250h R     W_INTERNAL      fixx [0000] ;rx_mac_addr_2                     |
|       4808254h ?     W_CONFIG_254h   fixx [0000] (read: FFFFh=DS, EEEEh=DS-Lite)    |
|       4808258h ?     W_INTERNAL      fixx [0000]                                    |
|       480825Ch ?     W_INTERNAL      fixx [0000]                                    |
|       4808260h ?     W_INTERNAL      fixx [ 0FEF]                                   |
|       4808264h R     W_INTERNAL      fixx [0000] ;rx_addr_1 (usually "rxtx_addr-x") |
|       4808268h R     W_RXTX_ADDR     fixx [0005] ;rxtx_addr                         |
|       4808270h R     W_INTERNAL      fixx [0000] ;rx_addr_2 (usually "rx_addr_1-1") |
|       4808274h ?     W_INTERNAL      fixx [ 0001]                                   |
|       4808278h R/W   W_INTERNAL      ffff [000F]                                    |
|       480827Ch ?     W_INTERNAL      fixx [ 000A]                                   |
|       4808290h (R/W) W_X_290h        fixx [FFFF] bit 0 = ? (used by firmware part4) |
|       4808298h W     W_INTERNAL      fixx [0000]                                    |
|       48082A0h R/W   W_INTERNAL      ffff [0000]                                    |
|       48082A2h R     W_INTERNAL      XXXX [7FFF] 15bit shift reg (used during tx?)  |
|       48082A4h R     W_INTERNAL      fixx [0000] ;rx_rate_1 not ALWAYS same as 2C4h |
|       48082A8h W     W_INTERNAL      fixx [0000]                                    |
|       48082ACh ?     W_INTERNAL      fixx [ 0038]                                   |
|       48082B0h W     W_INTERNAL      fixx [0000]                                    |
|       48082B4h R/W   W_INTERNAL      -1-3 [0000]                                    |
|       48082B8h ?     W_INTERNAL      fixx [0000] ;dsi launcher checks if zero       |
|       48082C0h R/W   W_INTERNAL      ---1 [0000]                                    |
|       48082C4h R     W_INTERNAL      fixx [000A] ;rx_rate_2 (0Ah,14h = 1,2 Mbit/s)  |
|       48082C8h R     W_INTERNAL      fixx [0000] ;rx_duration/length/rate (or so?)  |
|       48082CCh R     W_INTERNAL      fixx [0000] ;rx_framecontrol; from ieee header |
|       48082D0h DIS   W_INTERNAL                  ;"W_POWERACK" (internal garbage)   |
|                                                  ;normally DISABLED (unless FORCE)  |
|       48082F0h R/W   W_INTERNAL      ffff [0000]                                    |
|       48082F2h R/W   W_INTERNAL      ffff [0000]                                    |
|       48082F4h R/W   W_INTERNAL      ffff [0000]                                    |
|       48082F6h R/W   W_INTERNAL      ffff [0000]                                    |
+-------------------------------------------------------------------------------------+
```

All other ports in range 4808000h..4808FFFh are unused.
All registers marked as \"W_INTERNAL\" aren\'t used by Firmware part4, and are probably unimportant, except for whatever special diagnostics purposes.
Reading from write-only ports (W) often mirrors to data from other ports.

Additionally, there are 69h Baseband Chip Registers (BB), and 0Fh RF Chip Registers (see BB and RF chapters).

For Wifi Power Managment (POWCNT2), for Wifi Waitstates (WIFIWAITCNT), see:
- [DS Power Control](./dspowercontrol.md)
For the Power LED Blink Feature (conventionally used to indicate Wifi activity) see:
- [DS Power Management Device](./dspowermanagementdevice.md)

For Wifi Configuration and Calibration data in Firmware Header, see:
- [DS Cartridges, Encryption, Firmware](./dscartridgesencryptionfirmware.md)

### Wifi RAM - NDS7 - Memory (4804000h..4805FFFh)

```
+--------------------------------------------------------------------------------+
|       4804000h W_MACMEM RX/TX Buffers (2000h bytes) (excluding below specials) |
|       4805F60h Used for something, not included in the rx circular buffer.     |
|       4805F80h W_WEPKEY_0 (32 bytes)                                           |
|       4805FA0h W_WEPKEY_1 (32 bytes)                                           |
|       4805FC0h W_WEPKEY_2 (32 bytes)                                           |
|       4805FE0h W_WEPKEY_3 (32 bytes)                                           |
+--------------------------------------------------------------------------------+
```

Unlike all other NDS memory, Wifi RAM is left uninitialized after boot.

### 4805F60h - Reserved 20h-byte RAM area
Nintendo\'s software does init/change several values:

```
+-----------------------------------------------------------------------+
|       [480xxxxh]=5A5Ah/A5A5h  ;-initial dummy WifiRAM memfill values  |
|       [4805F70h]=FFFFh        ;\                                      
|       [4805F72h]=FFFFh        ; set to FFFFh by software              |
|       [4805F76h]=FFFFh        ;                                       |
|       [4805F7Eh]=FFFFh        ;/                                      |
+-----------------------------------------------------------------------+
```

The hardware does update several values (unless disabled in W_RAM_DISABLE.bit5):

```
+--------------------------------------------------------------------------+
|       [4805F6Eh]=0F00h (nothing received), or 0F01h (received something) |
+--------------------------------------------------------------------------+
```

And, if received packet was accepted (eg. when W_RXFILTER.bit0=1=AcceptAll):

```
+--------------------------------------------------------------------------------+
|       [4805F70h]=Received MAC Address (6 bytes, looks same as port 480824Ch)   |
|       [4805F76h]=xxx0h (increasing value, Sequence Control from packet header) |
+--------------------------------------------------------------------------------+
```

And, in multiplay slave mode (when receiving CMD packets?):

```
+--------------------------------------------------------------------------+
|       [4805F7Eh]=xxx0h (next higher sequence number? ie. [4805F76h]+10h) |
+--------------------------------------------------------------------------+
```


### 4805F80h - W_WEPKEY_0 thru W_WEPKEY_3 - Wifi WEP keys (R/W)
These WEP key slots store the WEP keys that are used for encryption for 802.11 keys IDs 0-3.



