# DS Wifi Timers


### 48080E8h - W_US_COUNTCNT - Microsecond counter enable (R/W)

```
+-----------------------------------------------------------------------+
|       0     Counter Enable (0=Disable, 1=Enable)                      |
|       1-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Activates W_US_COUNT, and also W_BEACON_COUNT and W_POST_BEACON (which are decremented when lower 10bit of W_US_COUNT wrap from 3FFh to 000h). Note: W_POWER_US must be enabled, too.

### 48080F8h - W_US_COUNT0 - Microsecond counter, bits 0-15 (R/W)
### 48080FAh - W_US_COUNT1 - Microsecond counter, bits 16-31 (R/W)
### 48080FCh - W_US_COUNT2 - Microsecond counter, bits 32-47 (R/W)
### 48080FEh - W_US_COUNT3 - Microsecond counter, bits 48-63 (R/W)

```
+-----------------------------------------------------------------------+
|       0-63  Counter Value in microseconds (incrementing)              |
+-----------------------------------------------------------------------+
```

Clocked by the 22.00MHz oscillator on the RFU board (ie. not by the 33.51MHz system clock). The 22.00MHz are divided by a 22-step prescaler.

### 48080EAh - W_US_COMPARECNT - Microsecond compare enable (R/W)

```
+-----------------------------------------------------------------------+
|       0     Compare Enable (0=Disable, 1=Enable) (IRQ14/IRQ15)        |
|       1     Force IRQ14    (0=No, 1=Force Now)   (Write-only)         |
|       2-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Activates IRQ14 on W_US_COMPARE matches, and IRQ14/IRQ15 on W_BEACON_COUNT.

### 48080F0h - W_US_COMPARE0 - Microsecond compare, bits 0-15 (R/W)
### 48080F2h - W_US_COMPARE1 - Microsecond compare, bits 16-31 (R/W)
### 48080F4h - W_US_COMPARE2 - Microsecond compare, bits 32-47 (R/W)
### 48080F6h - W_US_COMPARE3 - Microsecond compare, bits 48-63 (R/W)

```
+-------------------------------------------------------------------------------------+
|       0     Block Beacon IRQ14 until W_US_COUNT=W_US_COMPARE (0=No, 1=Block)  (W)   |
|       1-9   Always zero                                                             |
|       10-63 Compare Value in milliseconds (aka microseconds/1024)             (R/W) |
+-------------------------------------------------------------------------------------+
```

Triggers IRQ14 (see IRQ14 notes below) when W_US_COMPARE matches W_US_COUNT.
Usually set to FFFFFFFFFFFFFC00h (ie. almost/practically never). Instead, IRQ14 is usually derived via W_BEACON_COUNT.

### 480811Ch - W_BEACON_COUNT - Beacon Counter (R/W)
Triggers IRQ14 and IRQ15 (see IRQ14/IRQ15 notes below) when it reaches 0000h (if W_PRE_BEACON is non-zero, then IRQ15 occurs that many microseconds in advance).

```
+-------------------------------------------------------------------------------------+
|       0-15  Decrementing Millisecond Counter (reloaded with W_BEACONINT upon IRQ14) |
+-------------------------------------------------------------------------------------+
```

Set to W_BEACONINT upon IRQ14 events (unlike the other W_US_COMPARE related actions, this is done always, even if W_US_COMPARECNT is zero).
When reaching 0000h, it is immediately reloaded (as for US_COUNT matches), so the counting sequence is ..,3,2,1,BEACONINT,.. (not 3,2,1,ZERO,BEACONINT).

### 4808134h - W_POST_BEACON - Post-Beacon Counter (R/W)

```
+-------------------------------------------------------------------------------+
|       0-15  Decrementing Millisecond Counter (reloaded with FFFFh upon IRQ14) |
+-------------------------------------------------------------------------------+
```

Triggers IRQ13 when it reaches 0000h (no matter of W_US_COMPARECNT), and does then stay fixed at 0000h (without any further decrement/wrapping to FFFFh).
Set to FFFFh upon IRQ14 (by hardware), the IRQ14 handler should then adjust the register (by software) by adding the Tag=DDh Beacon header\'s Stepping value (usually 000Ah) to it.
Seems to be used to indicate beacon transmission time (possibly including additional time being reserved for responses)?

### 480808Ch - W_BEACONINT - Beacon Interval (R/W)
Reload value for W_BEACON_COUNT.

```
+-----------------------------------------------------------------------+
|       0-9   Frequency in milliseconds of beacon transmission          |
|       10-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Should be initialized randomly to 0CEh..0DEh or so. The random setting reduces risk of repeated overlaps with beacons from other hosts.

### 4808110h - W_PRE_BEACON - Pre-Beacon Time (R/W)

```
+----------------------------------------------------------------------------------+
|       0-15  Pre-Beacon Time in microseconds (static value, ie. NOT decrementing) |
+----------------------------------------------------------------------------------+
```

Allows to define the distance between IRQ15 and IRQ14. The setting doesn\'t affect the IRQ14 timing (which occurs at the W_BEACON_COUNT\'th millisecond boundary), but IRQ15 occurs in advance (at the W_BEACON_COUNT\'th millisecond boundary minus W_PRE_BEACON microseconds). If W_PRE_BEACON is zero, then both IRQ14 and IRQ15 occur exactly at the same time.

### 4808088h - W_LISTENCOUNT - Listen Count (R/W)

```
+-----------------------------------------------------------------------------+
|       0-7   Decremented by hardware at IRQ14 events (ie. once every beacon) |
|       8-15  Always zero                                                     |
+-----------------------------------------------------------------------------+
```

Reload occurs immediately BEFORE decrement, ie. with W_LISTENINT=04h, it will go through values 03h,02h,01h,00h,03h,02h,01h,00h,etc.

### 480808Eh - W_LISTENINT - Listen Interval (R/W)

```
+-----------------------------------------------------------------------+
|       0-7   Listen Interval, counted in beacons (usually 02h)         |
|       8-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Reload value for W_LISTENCOUNT.

### 480810Ch - W_CONTENTFREE (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Decrementing microsecond counter                          |
+-----------------------------------------------------------------------+
```

Operated always (no matter of W_US_COUNTCNT).
Once when it has reached 0000h, it seems to stay fixed at 0000h.
\"\[Set to the remaining duration of contention-free period when
receiving beacons - only \*really\* necessary for powersaving mode\]\"

### IRQ13 Notes (Post-Beacon Interrupt)
IRQ13 is generated by W_POST_BEACON. It\'s simply doing:

```
+-----------------------------------------------------------------------+
|       W_IF.Bit13=1      ;interrupt request                            |
+-----------------------------------------------------------------------+
```

If W_POWER_TX.Bit1=0, then additionally enter sleep mode:

```
+-------------------------------------------------------------------------------------+
|       [4808034h]=0002h ;W_INTERNAL   ;(similar to W_POWERFORCE=8001h)               |
|       [480803Ch]=02xxh ;W_POWERSTATE ;(W_TXREQ_READ.Bit4 is kept intact though)     |
|       [480819Ch]=0046h ;W_RF_PINS.7=0;disable receive (enter idle mode) (RX.ON=Low) |
|       [4808214h]=0009h ;W_RF_STATUS=9;indicate idle mode                            |
+-------------------------------------------------------------------------------------+
```

Unlike for IRQ14/IRQ15, that\'s done no matter of W_US_COMPARECNT.

### IRQ14 Notes (Beacon Interrupt)
IRQ14 is generated by W_US_COMPARE, and by W_BEACON_COUNT.
Aside from just setting the IRQ flag in W_IF, the hardware does:

```
+--------------------------------------------------------------------------------+
|       W_BEACON_COUNT=W_BEACONINT                             ;next IRQ15/IRQ14 |
|       (Above is NOT done when IRQ14 was forced via W_US_COMPARECNT.Bit1)       |
+--------------------------------------------------------------------------------+
```

If W_US_COMPARECNT is 1, then the hardware does additionally:

```
+-----------------------------------------------------------------------------------+
|       (Below IS ALSO DONE when IRQ14 was forced via W_US_COMPARECNT.Bit1)         |
|       W_IF.Bit14=1                                                                |
|       W_POST_BEACON=FFFFh ;about 64 secs (ie. almost never) ;next IRQ13 ("never") |
|       W_TXREQ_READ=W_TXREQ_READ AND FFF2h                                         |
|       if W_TXBUF_BEACON.15 then W_TXBUSY.Bit4=1                                   |
|       if W_LISTENCOUNT=00h then W_LISTENCOUNT=W_LISTENINT                         |
|       W_LISTENCOUNT=W_LISTENCOUNT-1                                               |
+-----------------------------------------------------------------------------------+
```

If W_TXBUF_BEACON.Bit15=1, then following is done shortly after IRQ14:

```
+-----------------------------------------------------------------------+
|       W_RF_PINS.Bit7=0  ;disable receive (RX.ON=Low)                  |
|       W_RF_STATUS=2     ;indicate switching from RX to TX mode        |
+-----------------------------------------------------------------------+
```

If W_TXBUF_BEACON.Bit15=1, then following is done a bit later:

```
+-----------------------------------------------------------------------+
|       W_RF_PINS.Bit6=1  ;transmit preamble start (TX.ON=High)         |
|       W_RF_STATUS=3     ;indicate TX mode                             |
+-----------------------------------------------------------------------+
```

The IRQ14 handler should then do the following (by software):

```
+------------------------------------------------------------------------+
|       W_POST_BEACON = W_POST_BEACON + TagDDhSteppingValue  ;next IRQ13 |
+------------------------------------------------------------------------+
```

For using only ONE of the two IRQ14 sources: W_BEACON_COUNT can be disabled by setting both W_BEACON_COUNT and W_BEACONINT to zero. W_US_COMPARE can be sorts of \"disabled\" by setting it to value distant from W_US_COUNT, such like compare=count-400h.

### IRQ07 Notes (Transmit Start Data; occurs after preamble)

```
+-------------------------------------------------------------------------------------+
|       W_IF.Bit7=1       ;interrupt request                                          |
|       W_RF_PINS.Bit1=1  ;start data transfer (preamble finished now) (TX.MAIN=High) |
+-------------------------------------------------------------------------------------+
```

Below only if packet was sent through W_TXBUF_BEACON, or if it was sent via W_TXBUF_LOCn, with W_TXBUF_LOCn.Bit13 being zero:

```
+------------------------------------------------------------------------+
|       [TXBUF...] = W_TX_SEQNO*10h   ;auto-adjust IEEE Sequence Control |
|       W_TX_SEQNO=W_TX_SEQNO+1       ;increase sequence number          |
+------------------------------------------------------------------------+
```


### IRQ01 Notes (Transmit Done)
The following happens shortly before IRQ01:

```
+-----------------------------------------------------------------------+
|       W_RF_PINS.Bit6=0  ;disable TX (TX.ON=Low)                       |
|       W_RF_STATUS=4     ;indicate switching from TX to RX mode        |
+-----------------------------------------------------------------------+
```

Then, upon IRQ01, the following happens:

```
+-----------------------------------------------------------------------+
|       W_IF.Bit1=1       ;interrupt request                            |
|       W_RF_PINS.Bit1=0  ;disable TX (TX.MAIN=Low)                     |
|       W_RF_PINS.Bit7=1  ;enable RX (RX.ON=High)                       |
|       W_RF_STATUS=1     ;indicate RX mode                             |
+-----------------------------------------------------------------------+
```


### IRQ15 Notes (Pre-Beacon Interrupt)
IRQ15 is generated via W_BEACON_COUNT and W_PRE_BEACON. It\'s simply doing:

```
+-----------------------------------------------------------------------+
|       if W_US_COMPARECNT=1 then W_IF.Bit15=1                          |
+-----------------------------------------------------------------------+
```

If W_POWER_TX.Bit0=1, then additionally wakeup from sleep mode:

```
+-------------------------------------------------------------------------------------+
|       W_RF_PINS.Bit7=1  ;enable RX (RX.ON=High) ;\gets set like so a good while     
|       W_RF_STATUS=1     ;indicate RX mode       ;/after IRQ15 (but not immediately) |
+-------------------------------------------------------------------------------------+
```


### Beacon IRQ Sequence

```
+-------------------------------------------------------------------------------------+
|       IRQ15  Pre-Beacon  (beacon will be transferred soon)                          |
|       IRQ14  Beacon      (beacon will be transferred very soon) (carrier starts)    |
|       IRQ07  Tx Start    (beacon transfer starts) (if enabled in W_TXBUF_BEACON.15) |
|       IRQ01  Tx End      (beacon transfer done) (if enabled in W_TXSTATCNT.15)      |
|       IRQ13  Post-Beacon (beacon transferred) (unless next IRQ14 occurs earlier)    |
+-------------------------------------------------------------------------------------+
```

That, for tranmitting beacons. (For receiving, IRQ07/IRQ01 would be replaced by Rx IRQ\'s, provided that a remote unit is sending beacons).



