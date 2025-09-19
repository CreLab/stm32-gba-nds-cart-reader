# DS Wifi Transmit Buffers


### 4808068h - W_TXBUF_WR_ADDR - Wifi CircBuf Write Address (R/W)

```
+-----------------------------------------------------------------------+
|       0     Always zero                                               |
|       1-12  Halfword Address in RAM for Writes via W_TXBUF_WR_DATA    |
|       13-15 Always zero                                               |
+-----------------------------------------------------------------------+
```


### 4808070h - W_TXBUF_WR_DATA - Wifi CircBuf Write Data (W)

```
+------------------------------------------------------------------------+
|       0-15  Data to be written to address specified in W_TXBUF_WR_ADDR |
+------------------------------------------------------------------------+
```

After writing to this register, W_TXBUF_WR_ADDR is automatically incremented by 2, and, if it gets equal to W_TXBUF_GAP, then it gets additonally incremented by W_TXBUF_GAPDISP\*2.

### 4808074h - W_TXBUF_GAP - Wifi CircBuf Write Top (R/W)

```
+-----------------------------------------------------------------------+
|       0     Always zero                                               |
|       1-12  Halfword Address                                          |
|       13-15 Always zero                                               |
+-----------------------------------------------------------------------+
```


### 4808076h - W_TXBUF_GAPDISP - CircBuf Write Offset from Top to Bottom (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword Offset (added to; if equal to W_TXBUF_GAP)       |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Should be \"0-write_buffer_size\" (wrap from end to begin), or zero (no wrapping).
Caution: On the DS-Lite, after adding it to W_TXBUF_WR_ADDR, the W_TXBUF_GAPDISP setting is destroyed (reset to 0000h) by hardware. The original DS leaves W_TXBUF_GAPDISP intact.

Note: W_TXBUF_GAP and W_TXBUF_GAPDISP may be (not TOO probably) also used by transmits via W_TXBUF_LOCn and W_TXBUF_BEACON (not tested).

### 4808080h - W_TXBUF_BEACON - Beacon Transmit Location (R/W)
### 4808090h - W_TXBUF_CMD - Multiplay Command Transmit Location (R/W)
### 48080A0h - W_TXBUF_LOC1 - Transmit location 1 (R/W)
### 48080A4h - W_TXBUF_LOC2 - Transmit location 2 (R/W)
### 48080A8h - W_TXBUF_LOC3 - Transmit location 3 (R/W)

```
+-----------------------------------------------------------------------------------+
|       0-11  Halfword Address of TX Frame Header in RAM                            |
|       12    For LOC1-3: When set, W_TXSTAT.bit8-10 are set to 07h after transfer  |
|                         And, when set, the transferred frame-body gets messed up? |
|             For BEACON: Unknown, no effect on W_TXSTAT                            |
|             For CMD: Unknown, no effect on W_TXSTAT                               |
|       13    IEEE Sequence Control (0=From W_TX_SEQNO, 1=Value in Wifi RAM)        |
|             For BEACON: Unknown (always uses W_TX_SEQNO) (no matter of bit13)     |
|       14    Unknown                                                               |
|       15    Transfer Request (1=Request/Pending)                                  |
+-----------------------------------------------------------------------------------+
```

For LOC1..3 and CMD, Bit15 is automatically cleared after (or rather: during?) transfer (no matter if the transfer was successful). For Beacons, bit15 is kept unchanged since beacons are intended to be transferred repeatedly.
W_TXBUF_CMD.Bit15 can be set ONLY while W_CMD_COUNT is non-zero.

### 48080B4h - W_TXBUF_RESET (W)

```
+-------------------------------------------------------------------------+
|       0     Disable LOC1    (0=No change, 1=Reset W_TXBUF_LOC1.Bit15)   |
|       1     Disable CMD     (0=No change, 1=Reset W_TXBUF_CMD.Bit15)    |
|       2     Disable LOC2    (0=No change, 1=Reset W_TXBUF_LOC2.Bit15)   |
|       3     Disable LOC3    (0=No change, 1=Reset W_TXBUF_LOC3.Bit15)   |
|       4-5   Unknown/Not used                                            |
|       6     Disable REPLY2  (0=No change, 1=Reset W_TXBUF_REPLY2.Bit15) |
|       7     Disable REPLY1  (0=No change, 1=Reset W_TXBUF_REPLY1.Bit15) |
|       8-15  Unknown/Not used                                            |
+-------------------------------------------------------------------------+
```

Firmware writes values FFFFh, 40h, 02h, xxxx, 09h, 01h, 02h, C0h.

### 4808084h - W_TXBUF_TIM - Beacon TIM Index in Frame Body (R/W)

```
+-----------------------------------------------------------------------+
|       0-7   Location of TIM parameters within Beacon Frame Body       |
|       8-15  Not used/zero                                             |
+-----------------------------------------------------------------------+
```

Usually set to 15h, that assuming that preceding Frame Body content is: Timestamp(8), BeaconInterval(2), Capability(2), SuppRatesTagLenParams(4), ChannelTagLenParam(3), TimTagLen(2); so the value points to TimParams (ie. after TimTagLen).

### 480806Ch - W_TXBUF_COUNT (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Decremented on writes to W_TXBUF_WR_DATA                  |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Triggers IRQ08 when it reaches zero, and does then stay at zero (without further decrementing, and without generating further IRQs).
Note: Not affected by (accidental) reads from write-only W_TXBUF_WR_DATA.



