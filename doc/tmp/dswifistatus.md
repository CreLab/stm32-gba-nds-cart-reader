# DS Wifi Status


### 480819Ch - W_RF_PINS - Status of RF-Chip Control Signals (R)

```
+------------------------------------------------------------------------------+
|       0    Reportedly "carrier sense" (maybe 1 during RX.DTA?) (usually 0)   |
|       1    TX.MAIN (RFU.Pin17) Transmit Data Phase          (0=No, 1=Active) |
|       2    Unknown (RFU.Pin3)  Seems to be always high      (Always 1=high?) |
|       3-5  Not used                                         (Always zero)    |
|       6    TX.ON   (RFU.Pin14) Transmit Preamble+Data Phase (0=No, 1=Active) |
|              Uhhh, no that seems to be still wrong...                        |
|              Bit6 is often set, even when not transmitting anything...       |
|       7    RX.ON   (RFU.Pin15) Receive Mode                 (0=No, 1=Enable) |
|       8-15 Not used                                         (Always zero)    |
+------------------------------------------------------------------------------+
```

Physical state of the RFU board\'s RX/TX pins. Similar to W_RF_STATUS.
XXX better expl. for bit0-1:

```
+--------------------------------------------------------------------------------+
|       0    RX.BUSY Receiving Preamble or Data   (0=Idle or TX Busy, 1=RX Busy) |
|       1    Data Phase (for both RX/TX mode)     (0=Idle or Preamble, 1=Data)   |
+--------------------------------------------------------------------------------+
```


### 4808214h - W_RF_STATUS - Current Transmit/Receive State (R)

```
+------------------------------------------------------------------------------------+
|       0-3  Current Transmit/Receive State:                                         |
|             0 = Initial value on Power-up (before raising W_MODE_RST.Bit0)         |
|             1 = RX Mode enabled (waiting for incoming data)                        |
|             2 = Switching from RX to TX (takes a few clock cycles)                 |
|             3 = TX Mode active  (sending preamble and data)                        |
|             4 = Switching from TX to RX (takes a few clock cycles)                 |
|             5 = Multiplay: CMD was sent, waiting for replies (RF_PINS=0084h) (uh?) |
|                 Or rather: CMD was received, preparing reply? (on slave side!)     |
|             6 = RX (processing incoming data?)                                     |
|             7 = Switching from RX/REPLY to TX/ACK (between STAT=5 and STAT=8)      |
|             8 = Multiplay: Sending REPLY, or CMD-Ack (RF_PINS=0046h)               |
|             9 = Idle (upon IRQ13, and upon raising W_MODE_RST.Bit0)                |
|       4-15 Always zero?                                                            |
+------------------------------------------------------------------------------------+
```

Numeric Status Code. Similar to W_RF_PINS.

### 4808268h - W_RXTX_ADDR - Current Receive/Transmit Address (R)

```
+-----------------------------------------------------------------------+
|       0-11   Halfword address                                         |
|       12-15  Always zero                                              |
+-----------------------------------------------------------------------+
```

Indicates the halfword that is currently transmitted or received. Can be used by Start Receive IRQ06 handler to determine how many halfwords of the packet have been already received (allowing to pre-examine portions of the packet header even when the whole packet isn\'t fully received). Can be also used in Transmit Start IRQ07 handler to determine which packet is currently transmitted.



