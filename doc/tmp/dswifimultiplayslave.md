# DS Wifi Multiplay Slave


The slave mode is activated by setting W_AID_LOW to a nonzero value (the slave number in range 1..15). That settings specifies that (and when) to send replies to incoming commands.

The replies are queued in W_TXBUF_REPLY1 (next packet) and W_TXBUF_REPLY2 (readonly, current packet).
Software does usually write to the REPLY1 register. Upon incomings CMD\'s, the hardware does automatically forward REPLY1 to REPLY2 (and reset REPLY1 to 0000h).
Because of that queuing, one should use two alternating Wifi RAM locations (ie. don\'t overwrite the current packet when preparing the next packet).
Alternately, one can manually forward REPLY1 to REPLY2 (via W_RXCNT.bit7, but that\'s normally not needed, except maybe for things like manually resetting REPLY2).

These registers are used for multiplay client-to-host (aka slave to master) responses.

### 4808094h - W_TXBUF_REPLY1 - Multiplay Next Reply Transmit Location (R/W)
### 4808098h - W_TXBUF_REPLY2 - Multiplay Current Reply Transmit Location (R)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword address                                          |
|       12-14 Unknown (the bits can be set, ie. they DO exist)          |
|       15    Enable                                                    |
+-----------------------------------------------------------------------+
```

Note: W_TXBUF_REPLY2.Bit15 is NOT cleared after SENDING the reply (instead, REPLY2 gets overwritten by REPLY1 when RECEIVING the next CMD).

### Flowchart (at Slave side)

```
+-------------------------------------------------------------------------------------+
|       At incoming CMD DATA packet:                                          ;\      
|         RF_STATUS=6  ;RX processing incoming stuff                          ;       |
|       After RX preamble:                                                    ; CMD   |
|         IRQ6 (RX Start, for CMD DATA)                                       ; DATA  |
|       After RX data:                                                        ;       |
|         IRQ0 (RX Done, for CMD DATA)                                        ;       |
|         WRCSR=WRCSR+(size of CMD DATA)                                      ;       |
|         RF_STATUS=5  ;preparing REPLY                                       ;       |
|         if REPLY2.bit15=1                                                   ;       |
|           TXHDR[1]=TXHDR[0]  ;<-- or sometimes random?  ;\adjust TXHDR[0,1] ;       
|           TXHDR[0]=01h       ;<-- mark done/discarded   ;/for <old> REPLY2  ;       |
|         REPLY2=REPLY1, REPLY1=0000h                     ;-forward new reply ;       |
|         if REPLY2.bit15=1                                                   ;       |
|           TXHDR[4] incremented (unless already max FFh) ;\adjust TXHDR[4,5] ;       
|           TXHDR[5]=00h                                  ;/for <new> REPLY2  ;       |
|           TX_SEQNO incremented  ;<-- done here if REPLY2 exists             ;/      |
|       After some moment (at the AID_LOW slot?):                             ;\      
|         RF_STATUS=8  ;TX sending REPLY                                      ;       |
|       After TX preamble:                                                    ; REPLY |
|         IRQ7 (TX Start, for REPLY)                                          ;       |
|       After TX data:                                                        ;       |
|         RF_STATUS=1  ;RX awaiting next packet                               ;       |
|         optional: IRQ1 (TX Done) (only if enabled in TXSTATCNT, and REPLY2.bit15=1) |
|         optional: TXSTAT=0401h   (only if enabled in TXSTATCNT)             ;       |
|         if REPLY2.bit15=0                                                   ;       |
|           SEQNO increased      ;<-- done here when REPLY2 is empty          ;/      |
|       After some moment:                                                    ;\      
|         RF_STATUS=6  ;RX processing incoming stuff                          ;       |
|       After RX preamble:                                                    ; CMD   |
|         IRQ6 (RX Start, for CMD ACK)                                        ; ACK   |
|       After RX data:                                                        ;       |
|         IRQ0 (RX Done, for CMD ACK)                                         ;       |
|         WRCSR=WRCSR+(size of CMD ACK)                                       ;       |
|         RF_STATUS=1  ;RX awaiting next packet                               ;/      |
|       Thereafter, Nintendo's software seems to require a delay (at least            |
|       100h microseconds) before receiving the next CMD DATA packet.                 |
+-------------------------------------------------------------------------------------+
```



### on client side
The reply transfer is automatically initiated when receiving a MP CMD frame (this seems to be based on the incoming IEEE header\'s frame control value and/or broadcast address, CMD frames typically have FC=0228h).

When receiving the MP CMD frame, the hardware determines its position using its W_AID_LOW register and the frame\'s client bitmask, then waits for its turn to reply.

W_TXBUF_REPLY1 is latched into W_TXBUF_REPLY2, and reset to zero.
The byte at TXHDR\[04h\] is set incremented. Nintendo software checks for this.

when transferring the MP reply itself:
IRQ7 is triggered. W_RF_STATUS is 8.
at the end: if W_TXSTATCNT.bit12=1, W_TXSTAT is set to 0401h, and IRQ1 is triggered.

### Reportedly\...
It will always send a reply - if W_TXBUF_REPLY1 isn\'t configured, it will send an empty reply frame (with frame control 0x0158). W_RXTXADDR isn\'t modified when sending a default empty reply.




