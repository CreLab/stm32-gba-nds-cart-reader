# DS Wifi Transmit Errors


### Automatic ACKs
Transmit errors occur on missing ACKs. The NDS hardware is automatically responding with an ACK when receiving a packet (if it has been addressed to the receipients W_MACADDR setting). And, when sending a packet, the NDS hardware is automatically checking for ACK responses.
The only exception are packets that are sent to group addresses (ie. Bit0 of the 48bit MAC address being set to \"1\", eg. Beacons sent to FF:FF:FF:FF:FF:FF), the receipient(s) don\'t need to respond to such packets, and the sender always passes okay without checking for ACKs.

### 480802Ch - W_TX_RETRYLIMIT (R/W)
Specifies the maximum number of retries on Transmit Errors (eg. 07h means one initial transmit, plus up to 7 retries, ie. max 8 transmits in total).

```
+-----------------------------------------------------------------------+
|       0-7   Retry Count (usually 07h)                                 |
|       8-15  Unknown     (usually 07h)                                 |
+-----------------------------------------------------------------------+
```

The Retry Count value is decremented on each Error (unless it is already 00h). There\'s no automatic reload, so W_TX_RETRYLIMIT should be reinitialized by software prior to each transmit (or, actually, there IS a reload?).
When sending multiple packets (by setting more than one bit with W_TXREQ_SET), then the first packet may eat-up all retries, leaving only a single try to the other packet(s).

### 48081C0h - W_TX_ERR_COUNT - TransmitErrorCount (R/W)

```
+-----------------------------------------------------------------------+
|       0-7   TransmitErrorCount                                        |
|       8-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Increments on Transmit Errors. Automatically reset to zero after reading.
IRQ03 triggered when W_TX_ERR_COUNT is incremented (for NON-beacons ONLY).
IRQ05 triggered when W_TX_ERR_COUNT \> 7Fh (happens INCLUDING for beacons).

### Error Notification
Transmit Errors can be sensed via W_TX_ERR_COUNT, IRQ03, IRQ05, TX Hardware Header entry \[00h\], and W_TXSTAT.Bit1.

### W_TXBUF_BEACON Errors
As the name says, W_TXBUF_BEACON is intended for sending Beacons to group addresses (which do not require to respond by ACKs). So, transmit errors would occur only when mis-using W_TXBUF_BEACON to send packets to individual addresses, but the W_TXBUF_BEACON error handling isn\'t fully implemented:
First of, W_TX_RETRYLIMIT isn\'t used, instead, W_TXBUF_BEACON errors will result in infinite retries.
Moreover, W_TXBUF_BEACON errors seem to increment W_TX_ERR_COUNT, but without generating IRQ03, however, IRQ05 is generated when W_TX_ERR_COUNT\>7Fh.

### Other Errors
The NDS transmit hardware seems to do little error checking on the packet headers. The only known error-checked part is byte \[04h\] in the TX hardware header (which must be 00h, 01h, or 02h). Aside from that, when sent to a group address, it is passing okay even with invalid IEEE type/subtypes, and even with Length/Rate entries set to zero. However, when sending such data to an individual address, the receiving NDS won\'t respond by ACKs.

### Note
Received ACKs aren\'t stored in WifiRAM (or, possibly, they ARE stored, but without advancing W_RXBUF_WRCSR, so that the software won\'t see them, and so that they will be overwritten by the next packet).



