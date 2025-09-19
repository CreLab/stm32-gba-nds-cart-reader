# DS Wifi Multiplay Master


These registers are used for multiplay host-to-client (aka master to slave) commands.

### 48080EEh - W_CMD_COUNTCNT (R/W)

```
+-----------------------------------------------------------------------+
|       0     Enable W_CMD_COUNT (0=Disable, 1=Enable)                  |
|       1-15  Always Zero                                               |
+-----------------------------------------------------------------------+
```


### 4808118h - W_CMD_COUNT (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Decremented once every 10 microseconds (Stopped at 0000h) |
+-----------------------------------------------------------------------+
```

Defines the time interval during which W_TXBUF_CMD transfers are possible. That CMD will be automatically transferred again if there are errors (missing REPLY\'s), but it will abort if there isn\'t enough time left in W_CMD_COUNT.
IRQ12 is thrown when cmd/reply were successful, or when CMD_COUNT reached zero (failed).
Firmware Beacon IRQ14 handler checks for W_CMD_COUNT\<=0Ah.

### 48080C0h - W_CMD_TOTALTIME - (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Duration per ALL slave response packet(s) in microseconds |
+-----------------------------------------------------------------------+
```

Before sending a MASTER packet, this port should be set to the same value as the MASTER packet\'s IEEE header\'s Duration/ID entry.

### 48080C4h - W_CMD_REPLYTIME - (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Duration per SINGLE slave response packet in microseconds |
+-----------------------------------------------------------------------+
```

Before sending a MASTER packet, this port should be set to the expected per slave response time.
Note: Nintendo\'s multiboot/pictochat code is also putting this value in the 1st halfword of the MASTER packet\'s frame body.

### At 2MBit/s transfer rate, the values should be set up sorts of like so:

```
+------------------------------------------------------------------------------------+
|       master_time = (master_bytes*4)+(60h)     ;60h = 96 decimal = short preamble  |
|       slave_time = (slave_bytes*4)+(0D0h..0D2h)                                    |
|       all_slave_time = (EAh..F0h)+(slave_time+0Ah)*num_slaves                      |
|       txhdr[2]   = slave_bits      ;hardware header (*)                            |
|       ieee[2]    = all_slave_time  ;ieee header (duration/id)                      |
|       body[0]    = slave_time      ;duration per slave (for multiboot/pictochat)   |
|       body[2]    = slave_bits      ;frame body -- required (*)                     |
|       [48080C0h] = all_slave_time  ;W_CMD_TOTALTIME                                |
|       [48080C4h] = slave_time      ;W_CMD_REPLYTIME duration per slave             |
|       [4808118h] = (388h+(num_slaves*slave_time)+master_time+32h)/10  ;W_CMD_COUNT |
|       [4808090h] = 8000h+master_packet_address   ;start transmit      ;W_TXBUF_CMD |
+------------------------------------------------------------------------------------+
```

With the byte values counting the ieee frame header+body+fcs.
(\*) The hardware doesn\'t actually seem to use the \"slave_bits\" entry in the hardware header, instead, it is using the \"slave_bits\" entry in the frame body(!)

### Flowchart (at Master side)

```
+--------------------------------------------------------------------------------+
|      After starting transfer via TXREQ and TXBUF_CMD write:                    |
|        TXBUSY=2 (formerly 0) (after TXBUF_CMD write, or sometimes a bit later) |
|      After about 50-500 microseconds:                               ;\         
|        RF_STAT=3 (TXing) (formerly 2)                               ;          |
|        RXTX_ADDR=0006h..0008h (TXbuf+0Ch..) (formerly in RXBUF)     ; CMD      |
|        SEQNO+1                                                      ;          |
|      After TX preamble:                                             ;          |
|        IF=80h (TX Start, for CMD)                                   ;          |
|        RXTX_ADDR=0009h..0xxxh (TXbuf..)                             ;          |
|      After TX data:                                                 ;          |
|        optional: IF=02h (TX Done, for CMD) (if enabled in TXSTATCNT);          |
|        optional: TXSTAT=0800h (CMD done)   (if enabled in TXSTATCNT);          |
|        RF_STAT=5 (CMD done, prepare for REPLY)                      ;/         |
|      US=0017h                                                       ;\         
|        RXTX_ADDR=rxbuf..                                            ;          |
|      After RX preamble:                                             ;          |
|        IF=40h (RX Start, for REPLY)                                 ; REPLY    |
|        RXTX_ADDR=rxbuf..                                            ; (if any) |
|      After RX data:                                                 ;          |
|        IF=01h (RX Done, for REPLY)                                  ;          |
|        WRCSR+18h (for REPLY)                                        ;/         |
|      After a dozen microseconds:                                    ;\         
|        RF_STAT=7 ;Switching from REPLY to ACK                       ;          |
|        RF_STAT=8 ;TXing ACK  (shortly after above STAT=7)           ;          |
|        RXTX_ADDR=0FC0h (special dummy addr during TX ACK)           ;          |
|      After TX preamble:                                             ; ACK      |
|        IF=80h (TX Start, for ACK)                                   ;          |
|      After TX data:                                                 ;          |
|        optional: IF=02h (TX Done, for ACK) (if enabled in TXSTATCNT);          |
|        optional: TXSTAT=0B01h (ACK done)   (if enabled in TXSTATCNT);          |
|        TXBUSY=0000h (formerly 0002h)                                ;          |
|        TXBUF_CMD.bit15=0                                            ;          |
|        TXHDR_0=0001h (okay)           (formerly 0000h)              ;          |
|        TXHDR_2=0000h (no error flags) (formerly 0002h)              ;          |
|        SEQNO+1                                                      ;          |
|        RF_STAT=1   ;RX awaiting                                     ;          |
|        IF=1000h (CMD timeslot done) (shortly AFTER above IF=02h)    ;/         |
+--------------------------------------------------------------------------------+
```



### Sending a W_TXBUF_CMD frame starts the following process:

```
+----------------------------------------------------------------------------------+
|      1. MP host sends the CMD frame, as soon as possible. after preamble,        |
|          IRQ7 is triggered                                                       |
|      2. once the transfer is finished: if bit14 in W_TXSTATCNT is set,           |
|          W_TXSTAT is set to 0x0800, and IRQ1 is triggered                        |
|          somewhere here: set W_RF_STATUS=5, RFPINS=0x0084                        |
|      3. hardware waits for MP clients' replies, duration is:                     |
|          16 + ((10 + W_CMD_REPLYTIME) * count_ones(client_mask_from_frame_body)) |
|      4. MP host sends the CMD ack. after preamble, IRQ7 is triggered             |
|          (this is why you get two IRQ7's from a CMD transfer)                    |
|      5. during the ack transfer, W_RF_STATUS is 8, and W_RXTXADDR is 0x0FC0      |
|      6. once the transfer is finished: if bit13 in W_TXSTATCNT is set,           |
|          W_TXSTAT is set to 0x0B01, and IRQ1 is triggered.                       |
|      7. the TX header of the CMD frame is adjusted: bits in TXheader[02] are     |
|          cleared to indicate that the corresponding clients responded            |
|          successfully. Nintendo software checks this.                            |
+----------------------------------------------------------------------------------+
```

I haven\'t looked a lot into how retries work. they seem to repeat the entire process.
the CMD ack is sent automatically. the packet is what is described here: the 03:09:BF:00:00:03 flow. MP clients will receive it like a regular frame.
IRQ12 is used to signal the end of the CMD transfer process. it will be either when the final ack is done transferring, if everything was successful, or otherwise at the end of W_CMD_COUNT.




