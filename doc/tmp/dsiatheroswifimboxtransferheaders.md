# DSi Atheros Wifi - MBOX Transfer Headers


MBOX transfers include a small header for distinguishing between Data Packets and Commands/Events, and for indicating the actual length (as opposed to the MBOX transfer length, which is usually garbage-padded to 80h-byte boundary).
The exception are BMI Bootloader commands/responses (which don\'t have such headers or padding).

### SDIO Functions used after BMI init

```
+-----------------------------------------------------------------------------+
|       Func[0:00005h]        R   1     Interrupt Flags (bit1=Function 1 IRQ) |
|       Func[1:00400h]        R   10h   Interrupt Status, etc. and Lookahead  |
|       Func[1:00800h..00FFF] R/W ..    MBOX0                                 |
+-----------------------------------------------------------------------------+
```


### MBOX Send Header/Body

```
+----------------------------------------------------------------------------------+
|       00h 1    Type (0=BootInfo, 1=WMI Command, 2/3/4/5=Data Packet BE/BK/VI/VO) |
|       01h 1    Request Ack (00h=No, 01h=Yes)                                     |
|       02h 2    Length of entries [06h..end]  (LEN)                               |
|       04h 2    ?                                                                 |
|       06h LEN  Body (BootInfo/Event/Data)                                        |
|       ..  ..   Padding to 80h-byte boundary (for SDIO block size 80h)            |
+----------------------------------------------------------------------------------+
```

Send Body for BootInfo:

```
+-------------------------------------------------------------------------------------+
|       06h ..   related to BE/BK/VI/VO stuff (best effort, background, video, voice) |
+-------------------------------------------------------------------------------------+
```

Send Body for WMI Commands:

```
+-----------------------------------------------------------------------+
|       06h 2  WMI Command Number                                       |
|       08h .. Parameters                                               |
+-----------------------------------------------------------------------+
```

Send Body for Data Packets:

```
+--------------------------------------------------------------------------------+
|       06h 2  <Unknown6>?? 0000h or 1C00h    ;maybe whatever ?                  |
|       08h 6  Destination (MAC Addr of Router) (or FF:FF:FF:FF:FF:FF=Broadcast) |
|       0Eh 6  Source      (MAC Addr of DSi console)                             |
|       14h 2  Length Data at [16h...]  ;(LEN1-10h)   ;<-- BIG-ENDIAN !!!        |
|       16h .. Data (usually starting with LLC stuff, ie. AAh,AAh,03h,00h...)    |
+--------------------------------------------------------------------------------+
```

Send Body for empty Data Packets (used when changing WPA/WPA2 CIPHER keys):

```
+----------------------------------------------------------------------------+
|       06h 1  Garbage (usually LSB of a previously used WMI command number) |
|       07h 1  Unknown (02h)                                                 |
+----------------------------------------------------------------------------+
```


### MBOX Receive Header/Body

```
+-------------------------------------------------------------------------------------+
|       00h      1    Type (0=Ack only, 1=WMI Event, 2/3/4/5=Data Packet BE/BK/VI/VO) |
|       01h      1    Ack Present (00h=No, 02h=Yes)                                   |
|       02h      2    Length of entries [06h..end]     (LEN1+LEN2)                    |
|       04h      1    Length of Ack at [06h+LEN1..end] (LEN2) ;garbage when [01h]=00h |
|       05h      1    ? (00h,20h?,7Fh,F4h,FFh)                                        |
|       06h      LEN1 Body (Event/Data)                                               |
|       06h+LEN1 LEN2 Ack List                                                        |
|       ..       ..   Padding to 80h-byte boundary (for SDIO block size 80h)          |
+-------------------------------------------------------------------------------------+
```

Receive Body for Ack only:

```
+------------------------------------------------------------------------+
|       06h -  N/A (or boot request info; occurs only shortly after BMI) |
+------------------------------------------------------------------------+
```

Receive Body for Events:

```
+-----------------------------------------------------------------------+
|       06h 2  WMI Event Number                                         |
|       08h .. Parameters                                               |
+-----------------------------------------------------------------------+
```

Receive Body for Data Packets:

```
+-------------------------------------------------------------------------------------+
|       06h 1  RSSI (Received Signal Strength Indicator) (00h..3Ch) (aka 0..60)       |
|       07h 1  <Unknown7> 00h                                                         |
|       08h 6  Destination (MAC Addr of DSi console) (or FF:FF:FF:FF:FF:FF=Broadcast) |
|       0Eh 6  Source      (MAC Addr of Router)                                       |
|       14h 2  Length of Data entries at [16h..(end-xtracrap)]   ;<-- BIG-ENDIAN !!!  |
|       16h .. Data (usually LLC stuff, ie. AAh,AAh,03h.. or, once F0h,F0h,03h..??)   |
+-------------------------------------------------------------------------------------+
```

Ack List (aka Trailer) (can contain multiple List items):

```
+-----------------------------------------------------------------------+
|       X+00h  List Item Type (01h=Ack, 02h=Lookahead)                  |
|       X+01h  List Item Len (02h*N for Ack's, 06h for Lookahead)       |
|       X+02h  List Item data                                           |
+-----------------------------------------------------------------------+
```

Ack Items (can contain multiple Ack items):

```
+--------------------------------------------------------------------------------+
|       Y+00h  Ack Item Type (01h=Command Ack, 02h=Data Ack, 05h=Data Ack, too?) |
|       Y+01h  Ack Item Count? (usually 1) (or 2 for double-ack?)                |
+--------------------------------------------------------------------------------+
```

Lookahead Item (if valid: allows to omit reading Func\[1:00408h\]):

```
+-----------------------------------------------------------------------+
|       Z+00h  Lookahead valid ID1 (00h=No, 55h=Valid)                  |
|       Z+01h  Lookahead MBOX0 (or garbage if ID1/ID2 not valid)        |
|       Z+05h  Lookahead valid ID2 (00h=No, AAh=Valid)                  |
+-----------------------------------------------------------------------+
```


### Types
There are four data packet types (BE/BK/VI/VO), most packets are using type=2 (Best Effort), however, some weird access points are sending other types (eg. Asus RT-AX56U has type=4 (video) in WPA2/EAPOL handshakes). Basically, one can ignore that, and simply all types in range 2,3,4,5 as data packets.

### Notes
Data Packet Type is usually 02h=BE (best effort),
The send/receive DATA headers are apparently containing incomplete wifi \"Frame Headers\":

```
+-------------------------------------------------------------------------+
|       without 3rd address field                                         |
|       without WEP entries (those are apparently automatically inserted) |
|       without Frame Control, Duration/ID, Sequence Control              |
|       there seem to be only Data Frames (no Managment/Control Frames)   |
+-------------------------------------------------------------------------+
```

That, unless some of the missing info would be encoded in the \<Unknown\> header entries.



