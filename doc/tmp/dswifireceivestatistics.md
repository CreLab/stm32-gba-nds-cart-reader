# DS Wifi Receive Statistics


### 48081A8h - W_RXSTAT_INC_IF - Statistics Increment Flags (R)

```
+-----------------------------------------------------------------------+
|       0-12   Increment Flags (see Port 48081B0h..1BFh)                |
|       13-15  Always zero                                              |
+-----------------------------------------------------------------------+
```

Bitmask for which statistics have been increased at least once.
Unknown how to reset/acknowledge these bits (neither reading/writing 48081A8h, nor reading 48081B0h..1BFh, nor writing 48081ACh seem to work).

### 48081AAh - W_RXSTAT_INC_IE - Statistics Increment Interrupt Enable (R/W)

```
+---------------------------------------------------------------------------------+
|       0-12   Counter Increment Interrupt Enable (see 48081B0h..1BFh) (1=Enable) |
|       13-15  Unknown (usually zero)                                             |
+---------------------------------------------------------------------------------+
```

Statistic Interrupt Enable Control register for Count Up.
Note: \-\-\-\-\--\> seems to trigger IRQ02 \...?

### 48081ACh - W_RXSTAT_OVF_IF - Statistics Half-Overflow Flags (R)

```
+-----------------------------------------------------------------------+
|       0-12   Half-Overflow Flags (see Port 48081B0h..1BFh)            |
|       13-15  Always zero                                              |
+-----------------------------------------------------------------------+
```

The W_RXSTAT_OVF_IF bits are simply containing the current bit7-value of the corresponding counters, setting or clearing that counter bits is directly reflected to W_RXSTAT_OVF_IF.
The recommended way to acknowledge W_RXSTAT_OVF_IF is to read the corresponding counters (which are reset to 00h after reading). For some reason, the firmware is additionally writing FFFFh to W_RXSTAT_OVF_IF (that is possibly a bug, or it does acknowledge something internally?).

### 48081AEh - W_RXSTAT_OVF_IE - Statistics Half-Overflow Interrupt Enable (R/W)

```
+----------------------------------------------------------------------------------+
|       0-12   Half-Overflow Interrupt Enable (see Port 48081B0h..1BFh) (1=Enable) |
|       13-15  Unknown (usually zero)                                              |
+----------------------------------------------------------------------------------+
```

Statistic Interrupt Enable for Overflow, bits same as in W_RXSTAT_INC_IE
Note: \-\-\-\-\--\> seems to trigger IRQ04 \...?

### 48081B0h..1BFh - W_RXSTAT - Receive Statistics (R/W, except 1B5h: Read-only)
W_RXSTAT is a collection of 8bit counters, which are incremented upon certain events. These entries are automatically reset to 0000h after reading. Should be accessed with LDRH opcodes (using LDRB to read only 8bits does work, but the read is internally expanded to 16bit, and so, the whole 16bit value will be reset to 0000h).

```
+-------------------------------------------------------------------------------------+
|       Port      Dir  Bit  Expl.                                                     |
|       48081B0h  R/W  0    W_RXSTAT  ?                                               |
|       48081B1h  -    -    Always 0  -                                               |
|       48081B2h  R/W  1    W_RXSTAT  ?    "RX_RateErrorCount"                        |
|       48081B3h  R/W  2    W_RXSTAT  Length>2348 error                               |
|       48081B4h  R/W  3    W_RXSTAT  RXBUF Full error                                |
|       48081B5h  R    4?   W_RXSTAT  ?    (R) (but seems to exist; used by firmware) |
|       48081B6h  R/W  5    W_RXSTAT  Length=0 or Wrong FCS Error                     |
|       48081B7h  R/W  6    W_RXSTAT  Packet Received Okay                            |
|                                  (also increments on W_MACADDR mis-match)           |
|                                  (also increments on internal ACK packets)          |
|                                  (also increments on invalid IEEE type=3)           |
|                                  (also increments TOGETHER with 1BCh and 1BEh)      |
|                                  (not incremented on RXBUF_FULL error)              |
|       48081B8h  R/W  7    W_RXSTAT  ?                                               |
|       48081B9h  -    -    Always 0  -                                               |
|       48081BAh  R/W  8    W_RXSTAT  ?                                               |
|       48081BBh  -    -    Always 0  -                                               |
|       48081BCh  R/W  9    W_RXSTAT  WEP Error (when FC.Bit14 is set)                |
|       48081BDh  R/W  10   W_RXSTAT  ?                                               |
|       48081BEh  R/W  11   W_RXSTAT  (duplicated sequence control)                   |
|       48081BFh  R/W  12   W_RXSTAT  ?                                               |
+-------------------------------------------------------------------------------------+
```


### 48081C4h - W_RX_COUNT (W_INTERNAL) (R)

```
+-------------------------------------------------------------------------------------+
|       0-?   Receive Okay Count (increments together with ports 48081B4h, 48081B7h)  |
|       8-?   Receive Error Count (increments together with ports 48081B3h, 48081B6h) |
+-------------------------------------------------------------------------------------+
```

Increments when receiving a packet. Automatically reset to zero after reading.

### 48081D0h..1DFh - W_CMD_STAT - Multiplay Response Error Counters (R/W)
The multiplay error counters are only used when sending a multiplay command (via W_TXBUF_CMD) to any connected slaves (which must be indicated by flags located in the second halfword of the multiplay command\'s frame body).

```
+-----------------------------------------------------------------------------------+
|       48081D0h        Not used (always zero)                                      |
|       48081D1h..1DFh  Client 1..15 Response Error (increments on missing replies) |
+-----------------------------------------------------------------------------------+
```

If one or more of those slaves fail to respond, then the corresponding error counters get incremented (at the master side). Automatically reset to zero after reading.
Unknown if these counters do also increment at the slave side?



