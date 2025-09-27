# DS Wifi IEEE802.11 Frames


### MAC Frame Format

```
+-------------------------------------------------------------------------------------+
|       10..30 bytes    MAC Header                                                    |
|       0..2312 bytes   Frame Body (in practice, network MTU is circa 1500 bytes max) |
|       4 bytes         Frame Check Sequence (FCS) (aka CRC32 on Header+Body)         |
+-------------------------------------------------------------------------------------+
```


### MAC Header (10..30 bytes)

```
+-----------------------------------------------------------------------+
|       Size Content                                                    |
|       2    Frame Control Field (FC)                                   |
|       2    Duration/ID                                                |
|       6    Address 1                                                  |
|      (6)   Address 2 (if any)                                         |
|      (6)   Address 3 (if any)                                         |
|      (2)   Sequence Control (if any)                                  |
|      (6)   Address 4 (if any)                                         |
+-----------------------------------------------------------------------+
```


### Frame Control Field (FC)

```
+------------------------------------------------------------------------------------+
|       Bit  Expl.                                                                   |
|       0-1  Protocol Version   (0=Current, 1..3=Reserved)                           |
|       2-3  Type               (0=Managment, 1=Control, 2=Data, 3=Reserved)         |
|       4-7  Subtype            (see next chapters) (meaning depends on above Type)  |
|       8    To Distribution System (ToDS)                                           |
|       9    From Distribution System (FromDS)                                       |
|       10   More Fragments                                                          |
|       11   Retry                                                                   |
|       12   Power Managment    (0=Active, 1=STA will enter Power-Safe mode after..) |
|       13   More Data                                                               |
|       14   Wired Equivalent Privacy (WEP) Encryption (0=No, 1=Yes)                 |
|       15   Order                                                                   |
+------------------------------------------------------------------------------------+
```

Bit 8-11 and Bit 13-15 are always 0 in Control Frames.

### Duration/ID Field (16bit)

```
+--------------------------------------------------------------------------+
|       0000h..7FFFh  Duration (0-32767)                                   |
|       8000h         Fixed value within frames transmitted during the CFP |
|                     (CFP=Contention Free Period)                         |
|       8001h..BFFFh  Reserved                                             |
|       C000h         Reserved                                             |
|       C001h..C7D7h  Association ID (AID) (1..2007) in PS-Poll frames     |
|       C7D8h..FFFFh  Reserved                                             |
+--------------------------------------------------------------------------+
```


### 48bit MAC Addresses
MAC Addresses are 48bit (6 bytes) (Bit0 is the LSB of the 1st byte),

```
+-------------------------------------------------------------------------------------+
|       0     Group Flag (0=Individual Address, 1=Group Address)                      |
|       1     Local Flag (0=Universally Administered Address, 1=Locally Administered) |
|       2-23  22bit Manufacturer ID (assigned by IEEE)                                |
|       24-47 24bit Device ID (assigned by the Manufacturer)                          |
+-------------------------------------------------------------------------------------+
```

Special NDS related Addresses:

```
+-----------------------------------------------------------------------------------+
|       00 09 BF xx xx xx  NDS-Consoles (Original NDS with firmware v1-v5)          |
|       00 16 56 xx xx xx  NDS-Consoles (Newer NDS-Lite with firmware v6 and up)    |
|       00 23 CC xx xx xx  DSi-Consoles (Original DSi with early mainboard; nocash) |
|       00 24 1E xx xx xx  DSi-Consoles (Another DSi; scanlime)                     |
|       40 F4 07 xx xx xx  DSi-Consoles (with DWM-W024; nocash)                     |
|       E0 E7 51 xx xx xx  DSi-Consoles (with DWM-W024; nocash/desoldered)          |
|       CC 9E 00 xx xx xx  DSi-Consoles (with J27H020; nocash)                      |
|       03 09 BF 00 00 00  NDS-Multiboot: host to client (main data flow)           |
|       03 09 BF 00 00 10  NDS-Multiboot: client to host (replies)                  |
|       03 09 BF 00 00 03  NDS-Multiboot: host to client (acknowledges replies)     |
|       FF FF FF FF FF FF  Broadcast to all stations (eg. Beacons)                  |
+-----------------------------------------------------------------------------------+
```


### Sequence Control Field

```
+-----------------------------------------------------------------------+
|       Bit  Expl.                                                      |
|       0-3  Fragment Number (0=First (or only) fragment)               |
|       4-15 Sequence Number                                            |
+-----------------------------------------------------------------------+
```

(increment by 1, except on retransmissions, ie. retries)

### WEP Frame Body

```
+-----------------------------------------------------------------------+
|       3 bytes     Initialization Vector (WEP IV)                      |
|       1 byte      Pad (6bit, all zero), Key ID (2bit)                 |
|       1..? bytes  Data (encrypted data)                               |
|       4 bytes     ICV (encrypted CRC32 across Data)                   |
+-----------------------------------------------------------------------+
```




