# DS Wifi IEEE802.11 Control and Data Frames (Type=1 and 2)


### Control Frames (Type=1)
All Control Frames have 10-byte or 16-byte headers, depending on the Subtype:

```
+-----------------------------------------------------------------------+
|       Subtype                          Frame Header                   |
|       0-9 Reserved                     -   -         -      -         |
|       A   Power Save (PS)-Poll         FC  AID       BSSID  TA        |
|       B   Request To Send (RTS)        FC  Duration  RA     TA        |
|       C   Clear To Send (CTS)          FC  Duration  RA     -         |
|       D   Acknowledgment (ACK)         FC  Duration  RA     -         |
|       E   Contention-Free (CF)-End     FC  Duration  RA     BSSID     |
|       F   CF-End + CF-Ack              FC  Duration  RA     BSSID     |
+-----------------------------------------------------------------------+
```

Control Frames do not have a Frame Body, so the Header is directly followed by the FCS.

### Data Frames (Type=2)
All Data Frames consist of the following components:

```
+---------------------------------------------------------------------------+
|       FC, Duration/ID, Address 1, Address 2, Address 3, Sequence Control, |
|       Address 4 (only on From DS to DS), Frame Body, FCS.                 |
+---------------------------------------------------------------------------+
```

The meaning of the 3 or 4 addresses depends on Frame Control FromDS/ToDS bits:

```
+-----------------------------------------------------------------------+
|       Frame Control    Address 1  Address 2  Address 3  Address 4     |
|       From STA to STA  DA         SA         BSSID      -             |
|       From DS  to STA  DA         BSSID      SA         -             |
|       From STA to DS   BSSID      SA         DA         -             |
|       From DS  to DS   RA         TA         DA         SA            |
+-----------------------------------------------------------------------+
```

Frame Control Subtypes for Data Frames (Type=2) are:

```
+-----------------------------------------------------------------------+
|       0   Data                                                        |
|       1   Data + CF-Ack                                               |
|       2   Data + CF-Poll                                              |
|       3   Data + CF-Ack + CF-Poll                                     |
|       4   Null function (no data)                                     |
|       5   CF-Ack (no data)                                            |
|       6   CF-Poll (no data)                                           |
|       7   CF-Ack + CF-Poll (no data)                                  |
|       8-F Reserved                                                    |
+-----------------------------------------------------------------------+
```

Note: The Frame Header is 24 bytes (or 30 bytes if with Address 4). The Data in Frame Body is usually starting with LLC stuff, ie. AAh,AAh,03h,00h\...



