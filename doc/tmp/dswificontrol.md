# DS Wifi Control


### 4808000h - W_ID - Wifi Chip ID (R)

```
+-----------------------------------------------------------------------+
|       0-15   Chip ID (1440h on NDS, C340h on NDS-lite)                |
+-----------------------------------------------------------------------+
```

The NDS-lite is more or less backwards compatible with the original NDS (the W_RXBUF_GAPDISP and W_TXBUF_GAPDISP are different, and most of the garbage effects on unused/mirrored ports are different, too).

### 4808004h - W_MODE_RST - Wifi Hardware mode / reset (R/W)

```
+---------------------------------------------------------------------------------+
|       0     Adjust some ports (0/1=see lists below) (R/W)                       |
|             TX Master Enable for LOC1..3 and Beacon  (0=Disable, 1=Enable)      |
|       1-12  Unknown (R/W)                                                       |
|       13    Reset some ports (0=No change, 1=Reset/see list below) (Write-Only) |
|       14    Reset some ports (0=No change, 1=Reset/see list below) (Write-Only) |
|       15    Unknown (R/W)                                                       |
+---------------------------------------------------------------------------------+
```


### 4808006h - W_MODE_WEP - Wifi Software mode / Wep mode (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-2   Unknown, specify a software mode for wifi operation                     |
|             (may be related to hardware but a correlation has not yet been found)   |
|       3-5   WEP Encryption Key Size:                                                |
|              0=Reserved (acts same as 1)                                            |
|              1=64bit WEP  (IV=24bit + KEY=40bit)  (aka 3+5 bytes)   ;standard/us    |
|              2=128bit WEP (IV=24bit + KEY=104bit) (aka 3+13 bytes)  ;standard/world |
|              3=152bit WEP (IV=24bit + KEY=128bit) (aka 3+16 bytes)  ;uncommon       |
|              4=Unknown, mabye 256bit WEP (IV=24bit + KEY=232bit) (aka 3+29 bytes)?  |
|              5=Reserved (acts same as 1)                                            |
|              6=Reserved (acts same as 1)                                            |
|              7=Reserved (acts same as 1)                                            |
|       6     Unknown                                                                 |
|       7-15  Always zero                                                             |
+-------------------------------------------------------------------------------------+
```


### 4808018h - W_MACADDR_0 - MAC Address (R/W)
### 480801Ah - W_MACADDR_1 - MAC Address (R/W)
### 480801Ch - W_MACADDR_2 - MAC Address (R/W)
48bit MAC Address of the console. Should be initialized from firmware\[036h\]. The hardware receives only packets that are sent to this address (or to group addresses, like FF:FF:FF:FF:FF:FF).

### 4808020h - W_BSSID_0 - BSSID (R/W)
### 4808022h - W_BSSID_1 - BSSID (R/W)
### 4808024h - W_BSSID_2 - BSSID (R/W)
48bit BSSID stored here. Ie. the MAC address of the host, obtained from Beacon frames (on the host itself, that should be just same as W_MACADDR). See W_RXFILTER.

### 4808028h - W_AID_LOW (R/W)

```
+-----------------------------------------------------------------------+
|       Bit0-3   Multiplay Slave number (1..15, or 0)                   |
|       Bit4-15  Not used                                               |
+-----------------------------------------------------------------------+
```

Usually set to zero, or equal to the lower 4bit of the W_AID_FULL value.

### 480802Ah - W_AID_FULL - Association ID (R/W)

```
+-----------------------------------------------------------------------+
|       Bit0-10  Association ID (AID) (1..2007, or zero)                |
|       Bit11-15 Not used                                               |
+-----------------------------------------------------------------------+
```


### 4808032h - W_WEP_CNT - WEP Engine Enable (R/W)

```
+-----------------------------------------------------------------------+
|       0-14  Unknown (usually zero)                                    |
|       15    WEP Engine Enable  (0=Disable, 1=Enable)                  |
+-----------------------------------------------------------------------+
```

Normally, bit15 should be always set (but it will only affect WEP-encrypted packets, ie. packets with Frame Control bit14=1 in 802.11 header). When disabled, WEP packets aren\'t received at all (neither in encrypted nor decrypted form), and sending WEP packets might be also ignored(?).
The firmware contains some code that does toggle the bit off for a moment (apparently to reset something after transfer errors).

### 4808044h - W_RANDOM - Random Generator (R)

```
+-----------------------------------------------------------------------+
|       0-10  Random                                                    |
|       11-15 Not used (zero)                                           |
+-----------------------------------------------------------------------+
```

The random generator is updated at 33.51MHz rate, as such:

```
+-----------------------------------------------------------------------+
|       X = (X AND 1) XOR (X ROL 1)  ;(rotation within 11bit range)     |
+-----------------------------------------------------------------------+
```

That random sequence goes through 5FDh different values before it restarts.
When reading from the random register, the old latched value is returned to the CPU, and the new current random value is then latched, so reads always return the older value, timed from the previous read.
Occassionally, about once every some thousand reads, the latching appears to occur 4 cycles earlier than normally, so the value on the next read will be 4 cycles older than expected.
The random register has ACTIVE mirrors.

### 48080BCh - W_PREAMBLE - Preamble Control (R/W)

```
+-------------------------------------------------------------------------------------+
|       Bit   Dir  Expl.                                                              |
|       0     R/W  Unknown                    (this does NOT affect TX)               |
|       1     R/W  Preamble (0=Long, 1=Short) (this does NOT affect TX)               |
|       2     W    Preamble (0=Long, 1=Short) (this does affect TX) (only at 2Mbit/s) |
|       3-15  -    Always zero                                                        |
+-------------------------------------------------------------------------------------+
```

Short preamble works only with 2Mbit/s transfer rate (ie. when set as so in TX hardware header). 1Mbit/s rate always uses long preamble.

```
+-----------------------------------------------------------------------------------+
|       Type   Carrier Signal  SFD Value     PLCP Header     Data                   |
|       Long   128bit, 1Mbit   16bit, 1Mbit  48bit, 1Mbit    N bits, 1Mbit or 2Mbit |
|       Short  56bit, 1Mbit    16bit, 1Mbit  48bit, 2Mbit    N bits, 2Mbit          |
+-----------------------------------------------------------------------------------+
```

Length of the Carrier+SFD+PLCP part is thus 192us (long) or 96us (short).
Note: The Carrier+SFD+PLCP part is sent between IRQ14 and IRQ07 (not between IRQ07 and IRQ01).
Firmware also changes W_CONFIG_140h alongsides with the preamble setting.

### Writing \"0-then-1\" to W_MODE_RST.Bit0 does reset following ports:

```
+-----------------------------------------------------------------------+
|       [4808034h]=0002h ;W_INTERNAL                                    |
|       [480819Ch]=0046h ;W_RF_PINS                                     |
|       [4808214h]=0009h ;W_RF_STATUS                                   |
|       [480827Ch]=0005h ;W_INTERNAL                                    |
|       [48082A2h]=?     ;...unstable?                                  |
+-----------------------------------------------------------------------+
```


### Writing \"1-then-0\" to W_MODE_RST.Bit0 does reset following ports:

```
+-----------------------------------------------------------------------+
|       [480827Ch]=000Ah ;W_INTERNAL                                    |
+-----------------------------------------------------------------------+
```


### Writing \"1\" to W_MODE_RST.Bit13 does reset following ports:

```
+------------------------------------------------------------------------------+
|       [4808056h]=0000h ;W_RXBUF_WR_ADDR                                      |
|       [48080C0h]=0000h ;W_CMD_TOTALTIME                                      |
|       [48080C4h]=0000h ;W_CMD_REPLYTIME                                      |
|       [48081A4h]=0000h ;W_X_1A4h                                             |
|       [4808278h]=000Fh ;W_INTERNAL                                           |
|       ...Also, following may be affected (results are unstable though)...    |
|       [48080AEh]=?     ;or rather the actual port (which it is an mirror of) |
|       [48080BAh]=?     ;W_INTERNAL (occassionally unstable)                  |
|       [4808204h]=?     ;W_INTERNAL                                           |
|       [480825Ch]=?     ;W_INTERNAL                                           |
|       [4808268h]=?     ;W_RXTX_ADDR                                          |
|       [4808274h]=?     ;W_INTERNAL                                           |
+------------------------------------------------------------------------------+
```


### Writing \"1\" to W_MODE_RST.Bit14 does reset following ports:

```
+-----------------------------------------------------------------------+
|       [4808006h]=0000h ;W_MODE_WEP                                    |
|       [4808008h]=0000h ;W_TXSTATCNT                                   |
|       [480800Ah]=0000h ;W_X_00Ah                                      |
|       [4808018h]=0000h ;W_MACADDR_0                                   |
|       [480801Ah]=0000h ;W_MACADDR_1                                   |
|       [480801Ch]=0000h ;W_MACADDR_2                                   |
|       [4808020h]=0000h ;W_BSSID_0                                     |
|       [4808022h]=0000h ;W_BSSID_1                                     |
|       [4808024h]=0000h ;W_BSSID_2                                     |
|       [4808028h]=0000h ;W_AID_LOW                                     |
|       [480802Ah]=0000h ;W_AID_FULL                                    |
|       [480802Ch]=0707h ;W_TX_RETRYLIMIT                               |
|       [480802Eh]=0000h ;W_INTERNAL                                    |
|       [4808050h]=4000h ;W_RXBUF_BEGIN                                 |
|       [4808052h]=4800h ;W_RXBUF_END                                   |
|       [4808084h]=0000h ;W_TXBUF_TIM                                   |
|       [48080BCh]=0001h ;W_PREAMBLE                                    |
|       [48080D0h]=0401h ;W_RXFILTER                                    |
|       [48080D4h]=0001h ;W_CONFIG_0D4h                                 |
|       [48080E0h]=0008h ;W_RXFILTER2                                   |
|       [48080ECh]=3F03h ;W_CONFIG_0ECh                                 |
|       [4808194h]=0000h ;W_TX_HDR_CNT                                  |
|       [4808198h]=0000h ;W_INTERNAL                                    |
|       [48081A2h]=0001h ;W_X_1A2h                                      |
|       [4808224h]=0003h ;W_INTERNAL                                    |
|       [4808230h]=0047h ;W_INTERNAL                                    |
+-----------------------------------------------------------------------+
```




