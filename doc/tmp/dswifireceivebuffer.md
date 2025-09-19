# DS Wifi Receive Buffer


The dimensions of the circular Buffer are set with BEGIN/END values, hardware automatically wraps to BEGIN when an incremented pointer hits END address.

### Write Area
Memory between WRCSR and READCSR is free for receiving data, the hardware writes incoming packets to this region (to WRCSR and up) (but without exceeding READCSR), once when it has successfully received a complete packet, the hardware moves WRCSR after the packet (aligned to a 4-byte boundary).

### Read Area
Memory between READCSR and WRCSR contains received data, which can be read by the CPU via RD_ADDR and RD_DATA registers (or directly from memory). Once when having processed that data, the CPU must set READCSR to the end of it.

### 4808050h - W_RXBUF_BEGIN - Wifi RX Fifo start location (R/W)
### 4808052h - W_RXBUF_END - Wifi RX Fifo end location (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Byte-offset in Wifi Memory (usually 4000h..5FFEh)         |
+-----------------------------------------------------------------------+
```

Although the full 16bit are R/W, only the 12bit halfword offset in Bit1-12 is actually used, the other bits seem to have no effect.
Some or all (?) of the below incrementing registers are automatically matched to begin/end, that is, after incrementing, IF adr=end THEN adr=begin.

### 4808054h - W_RXBUF_WRCSR - Wifi RX Fifo Write or \"end\" cursor (R)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword Address in RAM                                   |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Hardware does set this register pointing to end of the most recently received packet (plus 32bit alignment padding). Hardware will write the next packet to that address. And more importantly, software can read from RX fifo up to that address.

### 4808056h - W_RXBUF_WR_ADDR - Wifi RX Fifo Write Cursor Latch value (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword Address in RAM                                   |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

This is a value that is latched into W_RXBUF_WRCSR, when the W_RXCNT latch bit (W_RXCNT.Bit0) is written.

### 4808058h - W_RXBUF_RD_ADDR - Wifi CircBuf Read Address (R/W)

```
+-----------------------------------------------------------------------+
|       0     Always zero                                               |
|       1-12  Halfword Address in RAM for reading via W_RXBUF_RD_DATA   |
|       13-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

The circular buffer limits are the same as the range specified for the receive FIFO, however the address can be set outside of that range and will only be affected by the FIFO boundary if it crosses the FIFO end location by reading from the circular buffer.

### 480805Ah - W_RXBUF_READCSR - Wifi RX Fifo Read or \"start\" cursor (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword Address in RAM                                   |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

This value is specified the same as W_RXBUF_WRCSR - it\'s purely software controlled so it\'s up to the programmer to move the start cursor after loading a packet. If W_RXBUF_READCSR != W_RXBUF_WRCSR, then one or more packets exist in the FIFO that need to be processed (see the section on HW RX Headers, for information on calculating packet lengths). Once a packet has been processed, the software should advance the read cursor to the beginning of the next packet.

### 4808060h - W_RXBUF_RD_DATA - Wifi CircBuf Read Data (R)

```
+-----------------------------------------------------------------------+
|       0-15  Data                                                      |
+-----------------------------------------------------------------------+
```

returns the 16bit value at the address specified by W_RXBUF_RD_ADDR, and increments W_RXBUF_RD_ADDR by 2. If the increment causes W_RXBUF_RD_ADDR to equal the address specified in W_RXBUF_END, W_RXBUF_RD_ADDR will be reset to the address specified in W_RXBUF_BEGIN.
Ports 1060h, 6060h, 7060h are PASSIVE mirrors of 0060h, reading from these mirrors returns the old latched value from previous read from 0060h, but without reading a new value from RAM, and without incrementing the address.

### 4808062h - W_RXBUF_GAP - Wifi RX Gap Address (R/W)

```
+-----------------------------------------------------------------------+
|       0     Always zero                                               |
|       1-12  Halfword Address in RAM                                   |
|       13-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Seems to be intended to define a \"gap\" in the circular buffer, done like so:

```
+---------------------------------------------------------------------------------+
|       Addr=Addr+2 and 1FFEh  ;address increment (by W_RXBUF_RD_DATA read)       |
|       if Addr=RXBUF_END then ;normal begin/end wrapping (done before gap wraps) |
|          Addr=RXBUF_BEGIN                                                       |
|       if Addr=RXBUF_GAP then ;now gap-wrap (may include further begin/end wrap) |
|          Addr=RXBUF_GAP+RXBUF_GAPDISP*2                                         |
|          if Addr>=RXBUF_END then Addr=Addr+RXBUF_BEGIN-RXBUF_END  ;wrap more    |
+---------------------------------------------------------------------------------+
```

To disable the gap stuff, set both W_RXBUF_GAP and W_RXBUF_GAPDISP to zero.

### 4808064h - W_RXBUF_GAPDISP - Wifi RX Gap Displacement Offset (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Halfword Offset, used with W_RXBUF_GAP (see there)        |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Caution: On the DS-Lite, after adding it to W_RXBUF_RD_ADDR, the W_RXBUF_GAPDISP setting is destroyed (reset to 0000h) by hardware. The original DS leaves W_RXBUF_GAPDISP intact.

### 480805Ch - W_RXBUF_COUNT (R/W)

```
+-----------------------------------------------------------------------+
|       0-11  Decremented on reads from W_RXBUF_RD_DATA                 |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Triggers IRQ09 when it reaches zero, and does then stay at zero (without further decrementing, and without generating further IRQs).
Note: Also decremented on (accidental) writes to read-only W_RXBUF_RD_DATA.



