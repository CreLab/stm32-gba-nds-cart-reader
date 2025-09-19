# DS Wifi Transmit Control


### 48080ACh - W_TXREQ_RESET - Reset Transfer Request Bits (W)

```
+-----------------------------------------------------------------------------+
|       0-3   Reset corresponding bits in W_TXREQ_READ (0=No change, 1=Reset) |
|       4-15  Unknown (if any)                                                |
+-----------------------------------------------------------------------------+
```

Firmware writes values 01h,02h,08h,0Dh, and FFFFh.

### 48080AEh - W_TXREQ_SET - Set Transfer Request Bits (W)

```
+---------------------------------------------------------------------------+
|       0-3   Set corresponding bits in W_TXREQ_READ   (0=No change, 1=Set) |
|       4-15  Unknown (if any)                                              |
+---------------------------------------------------------------------------+
```

Firmware writes values 01h,02h,05h,08h,0Dh.

### 48080B0h - W_TXREQ_READ - Get Transfer Request Bits (R)

```
+---------------------------------------------------------------------------------+
|       0     Send W_TXBUF_LOC1  (1=Transfer, if enabled in W_TXBUF_LOC1.Bit15)   |
|       1     Send W_TXBUF_CMD   (1=Transfer, if enabled in W_TXBUF_CMD.Bit15)    |
|       2     Send W_TXBUF_LOC2  (1=Transfer, if enabled in W_TXBUF_LOC2.Bit15)   |
|       3     Send W_TXBUF_LOC3  (1=Transfer, if enabled in W_TXBUF_LOC3.Bit15)   |
|       4     Unknown (Beacon?)  (always 1, except when cleared via W_POWERFORCE) |
|       5-15  Unknown/Not used                                                    |
+---------------------------------------------------------------------------------+
```

Bit0-3 can be set/reset via W_TXREQ_SET/W_TXREQ_RESET. The setting in W_TXREQ_READ remains intact even after the transfer(s) have completed.
If more than one of the LOC1,2,3 bits is set, then LOC3 is transferred first, LOC1 last.
Beacons are transferred in every Beacon Timeslot (if enabled in W_TXBUF_BEACON.Bit15).
Bit0,2,3 are automatically reset upon IRQ14 (by hardware).

### 48080B6h - W_TXBUSY (R)

```
+----------------------------------------------------------------------------------+
|       0     W_TXBUF_LOC1  (1=Requested Transfer busy, or not yet started at all) |
|       1     W_TXBUF_CMD   (1=Requested Transfer busy, or not yet started at all) |
|       2     W_TXBUF_LOC2  (1=Requested Transfer busy, or not yet started at all) |
|       3     W_TXBUF_LOC3  (1=Requested Transfer busy, or not yet started at all) |
|       4     W_TXBUF_BEACON  (1=Beacon Transfer busy)                             |
|       5-15  Unknown (if any)                                                     |
+----------------------------------------------------------------------------------+
```

Busy bits. If all three W_TXBUF_LOC\'s are sent, then it goes through values 0Dh,05h,01h,00h; ie. LOC3 is transferred first, LOC1 last. The register is updated upon IRQ01 (by hardware).
Bit4 is set only in Beacon Timeslots.

### 48080B8h - W_TXSTAT - RESULT - Status of transmitted frame (R)
For LOC1-3, this register is updated at the end of a transfer (upon the IRQ01 request), if retries occur then it is updated only after the final retry.
For BEACON, this register is updated only if enabled in W_TXSTATCNT.Bit15, and only after successful transfers (since beacon errors result in infinite retries).
For CMD, this register is updated only if enabled in W_TXSTATCNT.Bit13,14).
Bit0/1 act similar to W_IF Bit1/3, however, the W_IF Bits are set after each transmit (including retries).

```
+------------------------------------------------------------------------------------+
|       0     One (or more) Packet has Completed (1=Yes)                             |
|             (No matter if successful, for that info see Bit1)                      |
|             (No matter if ALL packets are done, for that info see Bit12-13)        |
|       1     Packet Failed (1=Error)                                                |
|       2-7   Unknown/Not used                                                       |
|       8-11  Usually 0, ...but firmware is checking for values 03h,08h,0Bh          |
|             (gets set to 07h when transferred W_TXBUF_LOC1/2/3 did have Bit12=set) |
|             (gets set to 00h otherwise)                                            |
|             (gets set to 03h after beacons   ;if enabled in W_TXSTATCNT.Bit15)     |
|             (gets set to 08h after cmd's     ;if enabled in W_TXSTATCNT.Bit14)     |
|             (gets set to 0Bh after cmd ack's ;if enabled in W_TXSTATCNT.Bit13)     |
|             (gets set to 04h after reply's   ;if enabled in W_TXSTATCNT.Bit12)     |
|       12-13 Packet that updated W_TXSTAT (0=LOC1/BEACON/CMD/REPLY, 1=LOC2, 2=LOC3) |
|       14-15 Unknown/Not used                                                       |
+------------------------------------------------------------------------------------+
```

No idea how to reset bit0/1 once when they are set?

### 4808008h - W_TXSTATCNT (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-11  Unknown (usually zero) (otherwise disables RXing multiplay REPLY's?)    |
|       12    Update W_TXSTAT=0401h and trigger IRQ01 after REPLY transmits   (1=Yes) |
|       13    Update W_TXSTAT=0B01h and trigger IRQ01 after CMD ACK transmits (1=Yes) |
|       14    Update W_TXSTAT=0800h and trigger IRQ01 after CMD DATA transmits(1=Yes) |
|       15    Update W_TXSTAT=0301h and trigger IRQ01 after BEACON transmits  (1=Yes) |
+-------------------------------------------------------------------------------------+
```

Note: LOC1..3 transmits are always updating W_TXSTAT and triggering IRQ01.

### 4808194h - W_TX_HDR_CNT - Disable Transmit Header Adjustments (R/W)

```
+-------------------------------------------------------------------------------+
|       0     IEEE FC.Bit12 and Duration (0=Auto/whatever, 1=Manual/Wifi RAM)   |
|       1     IEEE Frame Check Sequence  (0=Auto/FCS/CRC32, 1=Manual/Wifi RAM)  |
|       2     IEEE Sequence Control      (0=Auto/W_TX_SEQNO, 1=Manual/Wifi RAM) |
|       3-15  Always zero                                                       |
+-------------------------------------------------------------------------------+
```

Allows to disable automatic adjustments of the IEEE header and checksum.
Note: W_TX_SEQNO can be also disabled by W_TXBUF_LOCn.Bit13 and by TXHDR\[04h\].

### 4808210h - W_TX_SEQNO - Transmit Sequence Number (R)

```
+-----------------------------------------------------------------------+
|       0-11   Increments on IRQ07 (Transmit Start Interrupt)           |
|       12-15  Always zero                                              |
+-----------------------------------------------------------------------+
```

Also incremented shortly after IRQ12.
When enabled in W_TXBUF_LOCn.Bit13, this value replaces the upper 12bit of the IEEE Frame Header\'s Sequence Control value (otherwise, when disabled, the original value in Wifi RAM is used, and, in that case, W_TX_SEQNO is NOT incremented).
Aside from W_TXBUF_LOCn.Bit13, other ways to disable W_TX_SEQNO are: Transmit Hardware Header entry TXHDR\[04h\], and W_TX_HDR_CNT.Bit2.



