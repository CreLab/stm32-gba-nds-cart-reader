# DS Wifi Interrupts


### 4808010h - W_IF - Wifi Interrupt Request Flags (R/W)

```
+-------------------------------------------------------------------------------------+
|       0   Receive Complete  (packet received and stored in the RX fifo)             |
|       1   Transmit Complete (packet is done being transmitted) (no matter if error) |
|       2   Receive Event Increment        (IRQ02, see W_RXSTAT_INC_IE)               |
|       3   Transmit Error Increment       (IRQ03, see W_TX_ERR_COUNT)                |
|       4   Receive Event Half-Overflow    (IRQ04, see W_RXSTAT_OVF_IE)               |
|       5   Transmit Error Half-Overflow   (IRQ05, see W_TX_ERR_COUNT.Bit7)           |
|       6   Start Receive     (IRQ06, a packet has just started to be received)       |
|       7   Start Transmit    (IRQ07, a packet has just started to be transmitted)    |
|       8   Txbuf Count Expired            (IRQ08, see W_TXBUF_COUNT)                 |
|       9   Rxbuf Count Expired            (IRQ09, see W_RXBUF_COUNT)                 |
|       10  Not used (always zero, even when trying to set it with W_IF_SET)          |
|       11  RF Wakeup                      (IRQ11, see W_POWERSTATE)                  |
|       12  Multiplay CMD done (or failed) (IRQ12, see W_CMD_COUNT)                   |
|       13  Post-Beacon Timeslot           (IRQ13, see W_POST_BEACON)                 |
|       14  Beacon Timeslot                (IRQ14, see W_BEACON_COUNT/W_US_COMPARE)   |
|       15  Pre-Beacon Timeslot            (IRQ15, see W_BEACON_COUNT/W_PRE_BEACON)   |
+-------------------------------------------------------------------------------------+
```

Write a \'1\' to a bit to clear it. For the Half-Overflow flags that works ONLY if the counter MSBs are zero (ie. one must first read the counters (to reset them), and THEN acknowledge the corresponding W_IF bit).
The Transmit Start/Complete bits (Bit7,1) are set for EACH packet (including beacons, and including retries).

### 4808012h - W_IE - Wifi Interrupt Enable Flags (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Enable Flags, same bits as W_IF  (0=Disable, 1=Enable)    |
+-----------------------------------------------------------------------+
```

In W_IE, Bit10 is R/W, but seems to have no function since IRQ10 doesn\'t exist.

### 480821Ch - W_IF_SET (W_INTERNAL) - Force Wifi Interrupt Flags (W)

```
+-----------------------------------------------------------------------+
|       0-15  Set corresponding bits in W_IF  (0=No change, 1=Set Bit)  |
+-----------------------------------------------------------------------+
```

Notes: Bit10 cannot be set since no IRQ10 exists. This register does only set IRQ flags, but without performing special actions (such like W_BEACON_COUNT and W_POST_BEACON reloads that occur on real IRQ14\'s).

### Wifi Primary IRQ Flag (IF.Bit24, Port 4000214h)
IF.Bit24 gets set \<only\> when (W_IF AND W_IE) changes from 0000h to non-zero.
IF.Bit24 can be reset (ack) \<even\> when (W_IF AND W_IE) is still non-zero.

```
+---------------------------------------------------------------------------+
|       Caution  Caution  Caution  Caution  Caution                         |
|       That means, when acknowledging IF.Bit24, then NO FURTHER wifi IRQs  |
|       will be executed whilst and as long as (W_IF AND W_IE) is non-zero. |
+---------------------------------------------------------------------------+
```

One work-around is to process/acknowledge ALL wifi IRQs in a loop, including further IRQs that may occur inside of that loop, until (W_IF AND W_IE) becomes 0000h.
Another work-around (for single IRQs) would be to acknowledge IF and W_IF, and then to set W_IE temporarily to 0000h, and then back to the old W_IE setting.



