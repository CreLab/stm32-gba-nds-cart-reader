# DS Wifi Hardware Headers


### Hardware TX Header (12 bytes) (TXHDR)
The TX header immediately precedes the data to be sent, and should be put at the location that will be given to the register activating a transmission.

```
+-------------------------------------------------------------------------------------+
|       Addr Siz Expl.                                                                |
|       00h  2   Status - In: Don't care - Out: Status (0000h=Failed, 0001h=Okay)     |
|                  0000h=Retrying? (TXBUF_LOCn)                                       |
|                  0001h=Okay      (TXBUF_LOCn,TXBUF_BEACON,TXBUF_CMD)                |
|                  xx01h=Okay      (TXBUF_REPLY, with increasing "xx")                |
|                  0003h=Failed    (TXBUF_LOCn)                                       |
|                  0005h=Failed    (TXBUF_CMD, with errorflags in TXHDR[2])           |
|       02h  2   Unknown - In: Don't care                                             |
|                  Bit0: Usually zero.                                                |
|                  Bit1..15 --------> flags for multiboot slaves number 1..15         |
|                  (Should be usually zero, except when sending multiplay commands    |
|                  via W_TXBUF_CMD. In that case, the slave flags should be ALSO      |
|                  stored in the second halfword of the FRAME BODY. Actually, the     |
|                  hardware seems to use only that entry (in the BODY), rather than   |
|                  using this entry (in the hardware header)).                        |
|       04h  1   Unknown - In: Must be 00h..02h (should be 00h)                       |
|                  00h = use W_TX_SEQNO (if enabled in TXBUF_LOCn)                    |
|                  01h = force NOT to use W_TX_SEQNO (even if it is enabled in LOCn)  |
|                  02h = seems to behave same as 01h                                  |
|                  03h..FFh = results in error: W_TXSTAT.Bit1 gets set (though        |
|                             header entry[00h] is kept set to 0001h=Okay)            |
|                  other theory: maybe an 8bit retry count with 00h=first try?        |
|       05h  1   Unknown - In: Don't care - Out: Set to 00h                           |
|       06h  2   Unknown - In: Don't care                                             |
|       08h  1   Transfer Rate (0Ah=1Mbit/s, 14h=2Mbit/s) (other values=1MBit/s, too) |
|       09h  1   Unknown - In: Don't care                                             |
|       0Ah  2   Length of IEEE Frame Header+Body+checksum(s) in bytes                |
|                (14bits, upper 2bits are unused/don't care)                          |
+-------------------------------------------------------------------------------------+
```

The eight \"Don\'t care\" bytes should be usually set to zero (although setting them to FFh seems to be working as well). Entries \[00h\] and \[05h\] are modified by hardware, all other entries are kept unchanged.

Important note! TX length includes the length of a 4-byte \"FCS\" (checksum) for the packet. The hardware generates the FCS for you, but you still must include it in the packet length. Also note that if the 802.11 WEP enabled bit is set in the header, the packet will be automatically encrypted via the wep algorithm - however, the software is responsible for providing the 4-byte IV block with the WEP key ID and the 24bit IV value. - ALSO, you must include the length of the \*encrypted\* FCS used in packets that have wep enabled (increase the tx length by another 4 bytes) - this value is calculated automaticly for you, but you are responsible for including it in the length of your packet (if you have data there, it\'ll be replaced by the FCS.)

### Hardware RX Header (12 bytes) (RXHDR)
The RX header is an informational structure that provides needed information about a received packet. It is written right before the received packet data in the rx circular buffer.

```
+-------------------------------------------------------------------------------------+
|       Addr Siz Expl.                                                                |
|       00h  2   Flags                                                                |
|                  Bit0-3: Frame type/subtype:                                        |
|                    00h: managment/any frame (except beacon and invalid subtypes)    |
|                    01h: managment/beacon frame                                      |
|                    05h: control/ps-poll frame                                       |
|                    08h: data/any frame (subtype0..7) (ie. except invalid subtypes)  |
|                   Values 0Ch..0Fh are for Multiplay cmd/reply packets:              |
|                    0Ch: CMD frame            ;FC=0228h=Data, FromDS, Data+CF_Poll   |
|                    0Dh: CMD ack frame        ;FC=0218h=Data, FromDS, Data+CF-Ack    |
|                    0Eh: REPLY frame (data)   ;FC=0118h=Data, ToDS, Data+CF-Ack      |
|                    0Fh: REPLY frame (empty)  ;FC=0158h=Data, ToDS, CF_Ack           |
|                    0Fh: Also ALL empty packets (raw IEEE header, with 0-byte body)  |
|                  Bit4:   Seems to be always set                                     |
|                  Bit5-7: Seems to be always zero                                    |
|                  Bit8: Set when FC.Bit10 is set (more fragments)                    |
|                  Bit9: Set when the lower-4bit of Sequence Control are nonzero,     |
|                        it is also set when FC.Bit10 is set (more fragments)         |
|                        So, probably, it is set on fragment-mismatch-errors          |
|                  Bit10-14: Seems to be always zero                                  |
|                  Bit15: Set when Frame Header's BSSID value equals W_BSSID register |
|       02h  2   Unknown (0040h=Normal, 0440h=WEP?, or Unchanged for multiplay CMDs?) |
|       04h  2   Unchanged (not updated by hardware, contains old Wifi RAM content)   |
|       06h  2   Transfer Rate (N*100kbit/s) (ie. 14h for 2Mbit/s)                    |
|       08h  2   Length of IEEE Frame Header+Body in bytes (excluding FCS checksum)   |
|       0Ah  1   MAX RSSI (bit0=always 1?)  ;\Received Signal Strength Indicator      
|       0Bh  1   MIN RSSI                   ;/                                        |
+-------------------------------------------------------------------------------------+
```

Important Note: Received frame lengths are always multiples of 4 bytes. While the actual header length + received frame length may be less, when incrementing the read cursor you must pad the length to a multiple of 4 bytes.

### IEEE Header
The above Hardware headers should (must) be followed by valid IEEE headers. Although that headers are to be generated by software, the hardware does do some interaction with the IEEE headers, such like comparing address fields with W_MACADDR and W_BSSID. And, it does modify some entries of it:
1) The sequence control value is replaced by W_TX_SEQNO\*10h (when enabled in W_TXBUF_LOCn.Bit13), this replacement does also overwrite the local TXBUF value.
2) The frame control value is modified, namely, the hardware tends to set Bit12 of it. This replacement does NOT modify the local TXBUF, but the remote RXBUF will receive the modified value. Also, Bit0-1 (protocol version) are forcefully set to 0.
3) Transmits via W_TXBUF_BEACON do additionally modify the 64bit timestamp (so W_TXBUF_BEACON should be used ONLY for packets WITH timestamp, ie. Beacons or Probe-Responses). The local TXBUF seems to be left unchanged, but the remote RXBUF will contain the (sender\'s) W_US_COUNT value.
C) For Control Frames, the hardware headers Length value is transferred as normally (ie. excluding the FCS length, remote RXBUF will contain TXBUF length minus 4), but - no matter of that length value - only 10 or 16 bytes (depending on the subtype) of the IEEE frame are actually transferred and/or stored in RXBUF.
X) For Control Frames with Subtype 0Ah, the AID entry is set to C000h, that, probably ORed with original value in WifiRAM, or with the W_AID_FULL register?
XX) No idea if it\'s possible to send Control Frames with subtype 0Bh..0Fh, as for now, it seems that either they aren\'t sent, or the receipient is ignoring them (or processing them internally, but without storing them in RXBUF).

### RSSI (Received Signal Strength Indicator)
The MAX RSSI is decoded as so:

```
+-------------------------------------------------------------------------------------+
|      arm7_xlat_rssi_r0:  ;bit0=unused, bit1=extraflag, bit2-7=unsigned value        |
|       tst     r0,2h           ;bit1                                                 |
|       mov     r0,r0,asr 2h    ;div4 (sign bits in bit31-8 are always zero-expanded) |
|       addeq   r0,r0,19h       ;add extra constant... when bit1=0 !!!!!!             |
|       and     r0,r0,0FFh      ;blah (max is FFh/4+19h)                              |
|       bx      r14                                                                   |
+-------------------------------------------------------------------------------------+
```

The MIN RSSI value is unknown and not used by existing software (it\'s usually smaller than the 8bit MAX RSSI value, though that value is actually 6bit+1bit, so it\'s hard to say what is bigger/smaller), actually MIN RSSI might be something different like SNR (Signal to Noise Ratio).



