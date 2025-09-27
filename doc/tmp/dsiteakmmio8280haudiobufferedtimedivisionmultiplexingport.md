# DSi Teak MMIO\[8280h\] - Audio (Buffered Time Division Multiplexing Port)


There are two BTDMP units. The weird name \"Buffered Time Division Multiplexing Port\" does essentially mean \"FIFO with sample rate timer\".

```
+--------------------------------------------------------------------------+
|       BTDMP 0 is used for Receive (microphone) and Transmit (audio out). |
|       BTDMP 1 isn't actually used for anything.                          |
+--------------------------------------------------------------------------+
```


### MMIO\[8280h/82A0h+(0..1)\*80h\] - BTDMP Receive/Transmit Control (R/W)

```
+-------------------------------------------------------------------------+
|       0-3    Unknown (0..Fh) (usually 0Dh/0Fh)                          |
|       4-7    Unknown (0..Fh) (usually 00h)                              |
|       8-11   Enable BTDMP Interrupt when non-zero (0=Off, AnyOther=On?) |
|       12-15  Unknown (0..Fh) (usually 00h)                              |
+-------------------------------------------------------------------------+
```

DSi sets this to 020Dh (receive) or 010Fh (transmit).

### MMIO\[8282h/82A2h+(0..1)\*80h\] - BTDMP Receive/Transmit Period (R/W)

```
+-----------------------------------------------------------------------------------+
|       0-2    Clock Divider? (0..7)    (usually 4)   (affects timing when bit13=1) |
|       3-4    Unused (0)                                                           |
|       5-12   Clock Divider? (0..FFh)  (usually 80h) (affects timing when bit13=1) |
|       13     Clock Select   (0=ExternalDSiAudioClk, 1=InternalClkDivider?)        |
|       14     Unknown        (0..1)    (usually 0)                                 |
|       15     Unused (0)                                                           |
+-----------------------------------------------------------------------------------+
```

Usually set to 1004h, which does select ExternalClk (32.73kHz or 47.61kHz, as selected in SNDEXCNT on ARM side; per 2x16bit stereo data).
Unknown how InternalClk works exactly. Increasing the \"dividers\" doesn\'t consistently increase FIFO transfer time; it seems as if the max time gets truncated somehow; maybe that\'s caused by InternalClk being ANDed with still running ExternalClk.

### MMIO\[8284h/82A4h+(0..1)\*80h\] - BTDMP Receive/Transmit Usually 0004h (R/W)

```
+--------------------------------------------------------------------------------+
|       0-2    Unknown (0..7) (R/W)                                        (R/W) |
|       3-4    Unused? (0)                                                       |
|       5-11   Unknown (0..7Fh) (R/W)                                      (R/W) |
|       12-15  Unused? (0)                                                       |
+--------------------------------------------------------------------------------+
```

Hmmmm, the write-ability of bit0-11 resembles the Period register\...?

### MMIO\[8286h/82A6h+(0..1)\*80h\] - BTDMP Receive/Transmit Usually 0021h (R/W)

```
+--------------------------------------------------------------------------------+
|       0-1    Unknown (0..3) (R/W)                                        (R/W) |
|       2-4    Unused? (0)                                                       |
|       5      Unknown/writeonly? (read=0) (code writes 1 here)            (W?)  |
|       6-15   Unused? (0)                                                       |
+--------------------------------------------------------------------------------+
```


### MMIO\[8288h/82A8h+(0..1)\*80h\] - BTDMP Receive/Transmit Usually 0000h\'a (R/W)

```
+-----------------------------------------------------------------------+
|       0-12   Unknown (0..1FFFh) (R/W) (initially=1FFFh on reset)      |
|       13-15  Unused (0)                                               |
+-----------------------------------------------------------------------+
```


### MMIO\[828Ah/82AAh+(0..1)\*80h\] - BTDMP Receive/Transmit Usually 0000h\'b (R/W)

```
+-----------------------------------------------------------------------+
|       0-11   Unknown (0..0FFFh) (R/W)                                 |
|       12-15  Unused (0)                                               |
+-----------------------------------------------------------------------+
```


### MMIO\[828Ch/82ACh+(0..1)\*80h\] - BTDMP Receive/Transmit Usually 0000h\'c (R/W)

```
+-----------------------------------------------------------------------+
|       0-13   Unknown (0..3FFFh) (R/W)                                 |
|       14-15  Unused (0)                                               |
+-----------------------------------------------------------------------+
```


### MMIO\[828Eh/82AEh+(0..1)\*80h\] - BTDMP Receive/Transmit Usually unused\'a (R/W)
### MMIO\[8290h/82B0h+(0..1)\*80h\] - BTDMP Receive/Transmit Usually unused\'b (R/W)

```
+-----------------------------------------------------------------------+
|       0-15   Unknown (0..FFFFh) (R/W)                                 |
+-----------------------------------------------------------------------+
```


Some of the above unknown stuff might be\... volume, bias, sample.size, mono/stereo, dummy-value-when-fifo-empty, beep generator, filter/equalizer, sample rate interpolation, whatever\...?

### MMIO\[829Eh/82BEh+(0..1)\*80h\] - BTDMP Receive/Transmit Enable (R/W)

```
+-----------------------------------------------------------------------+
|       0-14   Unused (0)                                               |
|       15     Enable Transfer  (0=Off, 1=On, allow Transfer+IRQ's)     |
+-----------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ________________________________ BTDMP FIFOs _________________________________ |
+-------------------------------------------------------------------------------------+
```


### MMIO\[82C0h/82C2h+(0..1)\*80h\] - BTDMP Receive/Transmit FIFO Status (R)

```
+-----------------------------------------------------------------------+
|       0      usually 0                                                |
|       1      If transfer ENABLED usually set, sometimes 0             |
|       2      If transfer ENABLED usually set                          |
|       3      FIFO Full  (0=No, 1=Full, 16x16bit words)                |
|       4      FIFO Empty (0=No, 1=Empty, 0x16bit words)                |
|       5      If transfer ENABLED usually set                          |
|       6      usually 0                                                |
|       7      For TX: gets set when FIFO contains ONE word?            |
|       8-15   usually 0                                                |
+-----------------------------------------------------------------------+
```


### MMIO\[82C4h/82C6h+(0..1)\*80h\] - BTDMP Receive/Transmit FIFO Data (R) and (W)

```
+-----------------------------------------------------------------------+
|       0-15      Signed 16bit audio sample.                            |
+-----------------------------------------------------------------------+
```

FIFO size is 16x16bit. The data is stereo, ie. one needs to write 2x16bit for a full stereo sample (the write-order for left/right is still unknown).
Software seems to be directly writing to the FIFO (rather than using DMA). If DMA is also supported, that would probably require whatever special settings in the BTDMP and/or DMA registers (ie. so that the DMA knows when it needs to transfer new FIFO data).

### MMIO\[82C8h/82CAh+(0..1)\*80h\] - BTDMP Receive/Transmit FIFO Control (R/W)

```
+----------------------------------------------------------------------------------+
|       0-1    Unknown     (0..3=?)                                          (R/W) |
|       2      Flush FIFO  (0=No change, 1=Clear FIFO)                       (W)   |
|       3-15   Unused (0)                                                          |
+----------------------------------------------------------------------------------+
```




