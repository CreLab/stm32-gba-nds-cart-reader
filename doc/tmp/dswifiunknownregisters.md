# DS Wifi Unknown Registers


### 480800Ah - W_X_00Ah (R/W)

```
+-----------------------------------------------------------------------+
|       0-15  Unknown (usually zero)                                    |
+-----------------------------------------------------------------------+
```

\"\[bit7 - ingore rx duplicates\]\" \<\-\-- that is NOT correct (no effect).
Firmware writes 0000h to it. That, done many times. So, eventually some bits in this register are automatically set by hardware in whatever situations, otherwise repeatedly writing 0000h to it would be kinda useless\...?

\-\--

Below Ports W_X_244h and W_X_228h might be related to deciding when to send multiplay replies\...?

### 4808244h - W_X_244h (R/W) x ffff \[0000\] (used by firmware part4)
Unknown. Seems to be W_IF/W_IE related. Firmware sets Port 4808244h bits 6,7,12 to 1-then-0 upon IRQ06,IRQ07,IRQ12 respectively.

### 4808228h - W_X_228h (W) fixx \[0000\] (used by firmware part4) (bit3)
Unknown. Firmware writes 8-then-0 (done in IRQ06 handler, after Port 4808244h access).

\-\--

Below Ports 48081A0h, 48081A2h, 48081A4h are somehow related to BB\[02h\]\...

### 48081A0h - W_X_1A0h - (R/W) -933 \[0000\]

```
+-----------------------------------------------------------------------+
|       0-1   Unknown                                                   |
|       2-3   Always zero                                               |
|       4-5   Unknown                                                   |
|       6-7   Always zero                                               |
|       8     Unknown                                                   |
|       9-10  Always zero                                               |
|       11    Unknown                                                   |
|       12-15 Always zero                                               |
+-----------------------------------------------------------------------+
```

Firmware writes values 000h, 823h. Seems to be power-related. The following experimental code toggles RXTX.ON (RFU.Pin4): \"x=0 / @@lop: / \[48081A0h\]=x / \[4808036h\]=0 / x=x XOR 3 / wait_by_loop(1000h) / b @@lop\".
Also, writing to port 48081A0h affects ports 4808034h, 480819Ch, 480821Ch, and 48082A2h.

### 48081A2h - W_X_1A2h - (R/W) \-\--3 \[0001\] (used by firmware part4)

```
+-----------------------------------------------------------------------+
|       0-1   Unknown. Firmware writes values 03h, 01h, and VAR.        |
|       2-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Used in combination with Port 48081A0h, so it\'s probably power-related, too.

### 48081A4h - W_X_1A4h - (R/W) ffff \[0000\]
\"Rate used when signal test is enabled (0x0A or 0x14 for 1 or 2 mbit)\"
(Not too sure if that\'s correct, there is no visible relation to any rate.)
(This register seems to be R/W only on certain Port 48081A0h settings.)
Unknown. Firmware writes whatever.

\-\--

### 4808220h - W_RAM_DISABLE - RAM Control (R/W)

```
+-----------------------------------------------------------------------------------+
|       0-1   Disable WifiRAM      (0=Normal, other=locks memory at 4804000h-5FFFh) |
|       2-4   Unknown              (0=Normal, other=prevents/affects RX to ram?)    |
|       5     Disable Special Log? (0=Normal, 1=Prevent 4805F6Eh..5F77h updates)    |
|       6-15  Unknown              (0=Normal, other=?)                              |
+-----------------------------------------------------------------------------------+
```


### 4808290h - W_X_290h - (R/W or Disabled)
Reportedly, this is the \"antenna\" register, which should exist on official devkits, allowing to switch between wired Ethernet, and wireless Wifi mode.

```
+-----------------------------------------------------------------------+
|       0     Unknown (R/W) (if present)                                |
|       1-15  Not used                                                  |
+-----------------------------------------------------------------------+
```

On normal NDS release versions, this register seems to be disabled (if it is implemented at all), and trying to read from it acts as for unused registers, ie. reads return FFFFh (or probably 0000h on NDS-lite). The NDS firmware contains code for accessing this port, even in release versions.

### W_INTERNAL
All registers marked as \"W_INTERNAL\" aren\'t used by Firmware part4, and are probably unimportant, except for whatever special diagnostics purposes.

### Wifi DMA
Wifi RAM can be accessed with normal \"Start Immediately\" DMA transfers (typically by reading through W_RXBUF_RD_DATA, so the DMA automatically wraps from END to BEGIN).
Additionally, DMA0 and DMA2 can be reportedly synchronized to \"Wireless Interrupt\" (rather than using \"Start Immediately\" timing), no idea if/how that\'s working though\... and if it gets started on any Wifi IRQ, or only on specific IRQs\...?
Possibly some of the above unknown registers, or some unknown bits in other registers, are DMA related\...?
Reportedly, early firmwares did use \"Wireless Interrupt\" DMAs (that\'d be firmware v1/v2\... or, only earlier unreleased prototype versions?).



