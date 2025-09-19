# DS Wifi Flowcharts


### Wifi Transmit Procedure
To transmit data via wifi (Assuming you\'ve already initialized wifi and changed channels to the channel you want):

```
+----------------------------------------------------------------------------------+
|      (1) Copy the TX Header followed by the 802.11 packet to send anywhere it    |
|           will fit in MAC memory (halfword-aligned)                              |
|      (2) Take the offset from start of MAC memory that you put the packet,       |
|           divide it by 2, and or with 0x8000 - store this in one of the          |
|           W_TXBUF_LOC registers                                                  |
|      (3) Set W_TX_RETRYLIMIT, to allow your packet to be retried until an ack is |
|           received (set it to 7, or something similar)                           |
|      (4) Store the bit associated with the W_TXBUF_LOC register you used         |
|           into W_TXREQ_SET - this will send the packet.                          |
|      (5) You can then read the result data in W_TXSTAT when the TX is over       |
|           (you can tell either by polling or interrupt) to find out how many     |
|           retries were used, and if the packet was ACK'd                         |
+----------------------------------------------------------------------------------+
```

Of course, this is just the simplest approach, you can be a lot more clever about it.

### Wifi Receive Procedure
To receive data via wifi, you either need to handle the wifi received data interrupt, or you need to poll W_RXBUF_WRCSR - whenever it is != W_RXBUF_READCSR, there is a new packet. When there is a new packet, take the following approach:

```
+--------------------------------------------------------------------------------+
|      (1) Calculate the length of the new packet (read "received frame length"  |
|           which is +8 bytes from the start of the packet) - total frame length |
|           is (12 + received frame length) padded to a multiple of 4 bytes.     |
|      (2) Read the data out of the RX FIFO area (keep in mind it's a circular   |
|           buffer and you may have to wrap around the end of the buffer)        |
|      (3) Set the value of W_RXBUF_READCSR to the location of the next packet   |
|           (add the length of the packet, and wrap around if necessary)         |
+--------------------------------------------------------------------------------+
```

Keep in mind, W_RXBUF_READCSR and W_RXBUF_WRCSR must be multiplied by 2 to get a byte offset from the start of MAC memory.

### Wifi Change Channels Procedure (ch=1..14)
For Type2 or Type5 (ie. firmware\[040h\]\<\>3): ;(Type2, used in Original-DS)

```
+------------------------------------------------------------------------------------+
|       RF[firmware[F2h+(ch-1)*6]/40000h] = firmware[F2h+(ch-1)*6] AND 3FFFFh        |
|       RF[firmware[F5h+(ch-1)*6]/40000h] = firmware[F5h+(ch-1)*6] AND 3FFFFh        |
|       delay a few milliseconds  ;huh?                                              |
|       IF RF[09h].bit16=0     ;External Gain (default)                              |
|        BB[1Eh]=firmware[146h+(ch-1)]                         ;set BB.Gain register |
|       ELSEIF RF[09h].bit15=0 ;Internal Gain from TXVGC Bits                        |
|        RF[09h].Bit10..14 = (firmware[154h+(ch-1)] AND 1Fh)   ;set RF.TXVGC Bits    |
|       ENDIF                                                                        |
+------------------------------------------------------------------------------------+
```

For Type3 (ie. firmware\[040h\]=3): ;(Type3, used in DS-Lite)

```
+-----------------------------------------------------------------------+
|       num_initial_regs = firmware[042h]                               |
|       addr=0CEh+num_initial_regs                                      |
|       num_bb_writes = firmware[addr]                                  |
|       num_rf_writes = firmware[43h]                                   |
|       addr=addr+1                                                     |
|       for i=1 to num_bb_writes                                        |
|         BB[firmware[addr]] = firmware[addr+ch]                        |
|         addr=addr+15                                                  |
|       next i                                                          |
|       for i=1 to num_rf_writes                                        |
|         RF[firmware[addr]] = firmware[addr+ch]                        |
|         addr=addr+15                                                  |
|       next i                                                          |
+-----------------------------------------------------------------------+
```

Congrats, you are now ready to transmit/receive on whatever channel you picked.

### Channels
The IEEE802.11b standard (and the NDS hardware) support 14 channels (1..14).
Channels 1..13 use frequencies 2412MHz..2472MHz (in 5MHz steps). Channel 14 uses frequency 2484MHz. Which channels are allowed to be used varies from country to country, as indicated by Bit1..14 of firmware\[03Ch\]. Channel 14 is rarely used (dated back to an older japanese standard).

Caution: Nearby channels do overlap, you\'ll get transmission errors on packets that are transferred simultaneously with packets on nearby channels. But, you won\'t successfully receive packets from nearby channels (so you won\'t even \"see\" that they are there, which is bad, as it doesn\'t allow you to share the channel synchronized with other hosts; ie. it\'d be better if two hosts are using the SAME channel, rather than to use nearby channels).
To avoid that problem, conventionally only channels 1,6,11 are used - however Nintendo uses channels 1,7,13 - which is causing conflicts between channel 6,7, and maybe also between 11,13.



