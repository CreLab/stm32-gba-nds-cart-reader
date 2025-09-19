# DSi Teak MMIO\[8050h\] - Serial Port (SIO)


This is a SPI-style serial I/O interface, allowing to connect some peripheral or debugging hardware (unused in DSi/3DS).

### MMIO\[8050h\] - SIO Control (R/W)

```
+---------------------------------------------------------------------------------+
|       0     Chip Select Polarity       (0=Active High, 1=Active Low)            |
|       1     Chip Select Output         (0=Disable/Hangs, 1=Enable) (for Master) |
|       2     Master/Slave Clock         (0=FromClkDivider, 1=ExternalClk/Hangs)  |
|       3     Clock Polarity             (0=Idle Low, 1=Idle High)                |
|       4     Clock Edge Phase           (0=InputOnRising, 1=OutputOnRising)      |
|       5     Transfer End Interrupt     (0=Enable, 1=Disable/Hangs/NoStatusDone) |
|       6-11  Unused (0)                                                          |
|       12-15 Num data bits per transfer (0=Hangs, 1..15=2bit..16bit)             |
+---------------------------------------------------------------------------------+
```


### MMIO\[8052h\] - SIO Clock Divider (R/W)

```
+------------------------------------------------------------------------------+
|       0-6   Clock Divider 1            (1..7Fh = Div1..Div127) (0=Div1, too) |
|       7     Unused (0)                                                       |
|       8-14  Clock Divider 2            (1..7Fh = Div1..Div127) (0=Div1, too) |
|       15    Unused (0)                                                       |
+------------------------------------------------------------------------------+
```

The transfer shift clock is 134MHz/(Divider1\*Divider2).

### MMIO\[8054h\] - SIO Data (R) and (W)

```
+-----------------------------------------------------------------------+
|       0-15  Transfer data (probably using only LSBs when NumBits<16)  |
+-----------------------------------------------------------------------+
```

Writing the transmit data starts the transfer, the reply data can be read when Transfer Done status flag gets set.

### MMIO\[8056h\] - SIO Enable (R/W)

```
+-----------------------------------------------------------------------+
|       0     Enable SIO operation       (0=Disable/Hangs, 1=Enable)    |
|       1-15  Unused (0)                                                |
+-----------------------------------------------------------------------+
```


### MMIO\[8058h\] - SIO Status (R)

```
+--------------------------------------------------------------------------------+
|       0     Transfer done   (0=No, 1=Done, Data can be read now)               |
|       1     Overrun error   (0=No, 1=New data arrived before reading old data) |
|       2-15  Unused (0)                                                         |
+--------------------------------------------------------------------------------+
```

Bit0,1 are automatically cleared after reading the status register.

### SIO Transfer Timing Bugs
After transfer end, one must apparently wait at least \"Divider1\*Divider2/2\" cycles before starting another transfer, else the new transfer won\'t start.
There are two dummy transfer clocks inserted (so transferring 2..16 bits does actually take \"(4..18)\*Divider1\*Divider2\" cycles).
And, transfer start doesn\'t seem to take place until next clock boundary (that may take between \"0 and 0.999\*Divider1\*Divider2\" extra cycles).



