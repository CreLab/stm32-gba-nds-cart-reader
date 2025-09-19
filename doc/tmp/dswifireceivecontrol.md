# DS Wifi Receive Control


### 4808030h - W_RXCNT - Wifi Receive Control (parts R/W and W)

```
+-------------------------------------------------------------------------------------+
|       0     Copy W_RXBUF_WR_ADDR to W_RXBUF_WRCSR (aka force RX buf empty)      (W) |
|       1-3   Unknown                                                           (R/W) |
|       4-6   Always zero                                                             |
|       7     Copy W_TXBUF_REPLY1 to W_TXBUF_REPLY2, set W_TXBUF_REPLY1 to 0000h  (W) |
|       8-14  Unknown                                                           (R/W) |
|       15    Enable Queuing received data to RX FIFO                           (R/W) |
+-------------------------------------------------------------------------------------+
```


### 48080D0h - W_RXFILTER - (R/W)

```
+-----------------------------------------------------------------------------------+
|       0     For Broadcasts? (0=Insist on W_BSSID, 1=Accept no matter of W_BSSID)  |
|       1     Unknown (usually zero)                                                |
|       2     Unknown (usually zero)                                                |
|       3     Unknown (usually zero)                                                |
|       4     Unknown (usually zero)                                                |
|       5     Unknown (usually zero)                                                |
|       6     Unknown (usually zero)                                                |
|       7     Unknown (0 or 1)                                                      |
|       8     Empty Packets (0=Ignore, 1=Accept; with RXHDR[0]=801Fh)               |
|       9     Unknown (0 or 1)                                                      |
|       10    Unknown (0 or 1)       (when set, receives beacons, and maybe others) |
|       11    Unknown (usually zero)     ;reportedly "allow toDS" ?                 |
|       12    Update W_RXBUF_WRCSR after IEEE header (instead after full packets?)  |
|              (setting bit12 causes a mess, where new "packets" in RX buf could    |
|              either contain RXHDR+IEEE header, or Data corresponding to that      |
|              headers, which could be useful only if there's a way to distinguish  |
|              between headers and data, and knowing the size of the data blocks).  |
|       13-15 Not used (always zero)                                                |
+-----------------------------------------------------------------------------------+
```

Specifies what packets to allow. Some random notes\...

```
+-----------------------------------------------------------------------+
|       0000h = Disable receive.                                        |
|       FFFFh = Enable receive.                                         |
|       0400h = Receives managment frames (and possibly others, too)    |
+-----------------------------------------------------------------------+
```

The exact meaning of the bits is unknown. The most import part is the address filtering based on the DA and BSSID values in IEEE header:

```
+---------------------------------------------------------------------------+
|       DA=W_MACADDR                    is always received                  |
|       DA=Broadcast, and BSSID=W_BSSID is always received                  |
|       DA=Broadcast, and BSSID=other   is received only if RXFILTER.bit0=1 |
+---------------------------------------------------------------------------+
```

Broadcast addresses (aka group addresses) have DA.firstbyte.bit0=1. RXFILTER.bit0 should be set when searching beacons, and cleared after connecting to an access point.

### 48080E0h - W_RXFILTER2 - (R/W)

```
+-----------------------------------------------------------------------+
|       0     Unknown (0=Receive Data Frames, 1=Ignore Data Frames) (?) |
|       1     Unknown                                                   |
|       2     Unknown                                                   |
|       3     Unknown (usually set)                                     |
|       4-15  Not used (always zero)                                    |
+-----------------------------------------------------------------------+
```

Firmware writes values 08h, 0Bh, 0Dh (aka 1000b, 1011b, 1101b).
Firmware usually has bit0 set, even when receiving data frames, so, in some situations data frames seem to pass-through even when bit0 is set\...? Possibly that situation is when W_BSSID matches\...?
Control/PS-Poll frames seem to be passed always (even if W_RXFILTER2=0Fh).



