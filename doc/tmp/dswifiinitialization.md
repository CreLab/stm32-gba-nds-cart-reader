# DS Wifi Initialization


### Initialization sequence
These events must be done somewhat in sequence. There is some flexibility as to how they can be ordered but it\'s best to follow this order:

```
+-----------------------------------------------------------------------+
|       [4000304h].Bit1 = 1 ;POWCNT2  ;-Enable power to the wifi system |
|       W_MACADDR = firmware[036h]    ;-Set 48bit Mac address           |
|       reg[012h] = 0000h   ;W_IE     ;-Disable interrupts              |
+-----------------------------------------------------------------------+
```

Wake Up the wireless system:

```
+-------------------------------------------------------------------------------------+
|       reg[036h] = 0000h ;W_POWER_US ;\clear all powerdown bits                      
|       delay 8 ms                    ; (works without that killer-delay ?)           |
|       reg[168h] = 0000h ;W_BB_POWER ;/                                              |
|       IF firmware[040h]=02h         ;\                                              
|         temp=BB[01h]                ; for wifitype=02h only:                        |
|         BB[01h]=temp AND 7Fh        ; reset BB[01h].Bit7, then restore old BB[01h]  |
|         BB[01h]=temp                ; (that BB setting enables the RF9008 chip)     |
|       ENDIF                         ;/                                              |
|       delay 30 ms                   ;-(more killer-delay now getting REALLY slow)   |
|       call init_sub_functions       ;- same as "Init 16 registers by firmware[..]"  |
|                                     ;  and "Init RF registers", below.              |
|                                     ;  this or the other one probably not necessary |
+-------------------------------------------------------------------------------------+
```

Init the Mac system:

```
+-------------------------------------------------------------------------------------+
|       reg[004h] = 0000h   - W_MODE_RST       ;set hardware mode                     |
|       reg[008h] = 0000h   - W_TXSTATCNT      ;                                      |
|       reg[00Ah] = 0000h   - ? W_X_00Ah       ;(related to rx filter)                |
|       reg[012h] = 0000h   - W_IE             ;disable interrupts (again)            |
|       reg[010h] = FFFFh   - W_IF             ;acknowledge/clear any interrupts      |
|       reg[254h] = 0000h   - W_CONFIG_254h    ;                                      |
|       reg[0B4h] = FFFFh   - W_TXBUF_RESET    ;--reset all TXBUF_LOC's               |
|       reg[080h] = 0000h   - W_TXBUF_BEACON   ;disable automatic beacon transmission |
|       reg[02Ah] = 0000h   - W_AID_FULL       ;\clear AID                            
|       reg[028h] = 0000h   - W_AID_LOW        ;/                                     |
|       reg[0E8h] = 0000h   - W_US_COUNTCNT    ;disable microsecond counter           |
|       reg[0EAh] = 0000h   - W_US_COMPARECNT  ;disable microsecond compare           |
|       reg[0EEh] = 0001h   - W_CMD_COUNTCNT   ;(is 0001h on reset anyways)           |
|       reg[0ECh] = 3F03h   - W_CONFIG_0ECh    ;                                      |
|       reg[1A2h] = 0001h   - ?                ;                                      |
|       reg[1A0h] = 0000h   - ?                ;                                      |
|       reg[110h] = 0800h   - W_PRE_BEACON     ;                                      |
|       reg[0BCh] = 0001h   - W_PREAMBLE       ;disable short preamble                |
|       reg[0D4h] = 0003h   - W_CONFIG_0D4h    ;                                      |
|       reg[0D8h] = 0004h   - W_CONFIG_0D8h    ;                                      |
|       reg[0DAh] = 0602h   - W_RX_LEN_CROP    ;                                      |
|       reg[076h] = 0000h   - W_TXBUF_GAPDISP  ;disable gap/skip (offset=zero)        |
+-------------------------------------------------------------------------------------+
```

Init 16 registers by firmware\[044h..063h\]

```
+-----------------------------------------------------------------------+
|       reg[146h] = firmware[044h] ;W_CONFIG_146h                       |
|       reg[148h] = firmware[046h] ;W_CONFIG_148h                       |
|       reg[14Ah] = firmware[048h] ;W_CONFIG_14Ah                       |
|       reg[14Ch] = firmware[04Ah] ;W_CONFIG_14Ch                       |
|       reg[120h] = firmware[04Ch] ;W_CONFIG_120h                       |
|       reg[122h] = firmware[04Eh] ;W_CONFIG_122h                       |
|       reg[154h] = firmware[050h] ;W_CONFIG_154h                       |
|       reg[144h] = firmware[052h] ;W_CONFIG_144h                       |
|       reg[130h] = firmware[054h] ;W_CONFIG_130h                       |
|       reg[132h] = firmware[056h] ;W_CONFIG_132h                       |
|       reg[140h] = firmware[058h] ;W_CONFIG_140h                       |
|       reg[142h] = firmware[05Ah] ;W_CONFIG_142h                       |
|       reg[038h] = firmware[05Ch] ;W_POWER_TX                          |
|       reg[124h] = firmware[05Eh] ;W_CONFIG_124h                       |
|       reg[128h] = firmware[060h] ;W_CONFIG_128h                       |
|       reg[150h] = firmware[062h] ;W_CONFIG_150h                       |
+-----------------------------------------------------------------------+
```

Init RF registers

```
+----------------------------------------------------------------------------------+
|       numbits = BYTE firmware[041h]    ;usually 18h                              |
|       numbytes = (numbits+7)/8         ;usually 3                                |
|       reg[0x184] = (numbits+80h) AND 017Fh  -- W_RF_CNT                          |
|       for i=0 to BYTE firmware[042h]-1 ;number of entries (usually 0Ch) (0..0Bh) |
|        if BYTE firmware[040h]=3                                                  |
|         RF[i]=firmware[0CEh+i]                                                   |
|        else                                                                      |
|         RF_Write(numbytes at firmware[0CEh+i*numbytes])                          |
|        endif                                                                     |
+----------------------------------------------------------------------------------+
```

Init the BaseBand System

```
+-----------------------------------------------------------------------+
|       (this should be not required, already set by firmware bootcode) |
|       reg[160h] = 0100h  ;W_BB_MODE                                   |
|       BB[0..68h] = firmware[64h+(0..68h)]                             |
+-----------------------------------------------------------------------+
```

Set Mac address

```
+------------------------------------------------------------------------------------+
|       copy 6 bytes from firmware[036h] to mac address at 0x04800018  (why again ?) |
+------------------------------------------------------------------------------------+
```

Now just set some default variables

```
+-----------------------------------------------------------------------------------+
|       reg[02Ch]=0007h  ;W_TX_RETRYLIMIT - XXX needs to be set for every transmit? |
|       Set channel (see section on changing channels)                              |
|       Set Mode 2 -- sets bottom 3 bits of W_MODE_WEP to 2                         |
|       Set Wep Mode / key -- Wep mode is bits 3..5 of W_MODE_WEP                   |
|       BB[13h] = 00h  ;CCA operation (use only carrier sense, without ED)          |
|       BB[35h] = 1Fh  ;Energy Detection Threshold (ED)                             |
+-----------------------------------------------------------------------------------+
```

\-- To further init wifi to the point that you can properly send
\-- and receive data, there are some more variables that need to be set.

```
+----------------------------------------------------------------------------------+
|       reg[032h] = 8000h -- W_WEP_CNT     ;Enable WEP processing                  |
|       reg[134h] = FFFFh -- W_POST_BEACON ;reset post-beacon counter to LONG time |
|       reg[028h] = 0000h -- W_AID_LOW     ;\clear W_AID value, again?!            
|       reg[02Ah] = 0000h -- W_AID_FULL    ;/                                      |
|       reg[0E8h] = 0001h -- W_US_COUNTCNT ;enable microsecond counter             |
|       reg[038h] = 0000h -- W_POWER_TX    ;disable transmit power save            |
|       reg[020h] = 0000h -- W_BSSID_0     ;\                                      
|       reg[022h] = 0000h -- W_BSSID_1     ; clear BSSID                           |
|       reg[024h] = 0000h -- W_BSSID_2     ;/                                      |
+----------------------------------------------------------------------------------+
```

\-- TX prepare

```
+-----------------------------------------------------------------------------+
|       reg[0AEh] = 000Dh -- W_TXREQ_SET   ;flush all pending transmits (uh?) |
+-----------------------------------------------------------------------------+
```

\-- RX prepare

```
+------------------------------------------------------------------------------------+
|       reg[030h] = 8000h    W_RXCNT         ;enable RX system (done again below)    |
|       reg[050h] = 4C00h    W_RXBUF_BEGIN   ;(example values)                       |
|       reg[052h] = 5F60h    W_RXBUF_END     ;(length = 4960 bytes)                  |
|       reg[056h] = 0C00h/2  W_RXBUF_WR_ADDR ;fifo begin latch address               |
|       reg[05Ah] = 0C00h/2  W_RXBUF_READCSR     ;fifo end, same as begin at start.  |
|       reg[062h] = 5F60h-2  W_RXBUF_GAP     ;(set gap<end) (zero should work, too)  |
|       reg[030h] = 8001h    W_RXCNT  ;enable, and latch new fifo values to hardware |
+------------------------------------------------------------------------------------+
```

\--

```
+-------------------------------------------------------------------------------------+
|       reg[030h] = 8000h    W_RXCNT       enable receive (again?)                    |
|       reg[010h] = FFFFh    W_IF          clear interrupt flags                      |
|       reg[012h] = whatever W_IE          set enabled interrupts                     |
|       reg[1AEh] = 1FFFh    W_RXSTAT_OVF_IE desired STAT Overflow interrupts         |
|       reg[1AAh] = 0000h    W_RXSTAT_INC_IE desired STAT Increase interrupts         |
|       reg[0D0h] = 0181h    W_RXFILTER set to 0x581 when you successfully connect    |
|                             to an access point and fill W_BSSID with a mac          |
|                             address for it. (W_RXFILTER) [not sure on the values    |
|                             for this yet]                                           |
|       reg[0E0h] = 000Bh  -- W_RXFILTER2     ;                                       |
|       reg[008h] = 0000h  -- ? W_TXSTATCNT   ;(again?)                               |
|       reg[00Ah] = 0000h  -- ? W_X_00Ah      ;(related to rx filter) (again?)        |
|       reg[004h] = 0001h  -- W_MODE_RST      ;hardware mode                          |
|       reg[0E8h] = 0001h  -- W_US_COUNTCNT   ;enable microsecond counter (again?)    |
|       reg[0EAh] = 0001h  -- W_US_COMPARECNT ;enable microsecond compare             |
|       reg[048h] = 0000h  -- W_POWER_?    ;[disabling a power saving technique]      |
|       reg[038h].Bit1 = 0 -- W_POWER_TX   ;[this too]                                |
|       reg[048h] = 0000h  -- W_POWER_?    ;[umm, it's done again. necessary?]        |
|       reg[0AEh] = 0002h  -- W_TXREQ_SET  ;                                          |
|       reg[03Ch].Bit1 = 1 -- W_POWERSTATE ;queue enable power (RX power, we believe) |
|       reg[0ACh] = FFFFh  -- W_TXREQ_RESET;reset LOC1..3                             |
+-------------------------------------------------------------------------------------+
```

That\'s it, the DS should be now happy to send and receive packets.
It\'s very possible that there are some unnecessary registers set in here.



