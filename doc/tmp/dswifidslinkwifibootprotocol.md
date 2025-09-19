# DS Wifi Dslink/Wifiboot Protocol


Below is the transfer protocol for nocash \"wifiboot\" and devkitpro \"dslink\".
All UDP/TCP message are using Port 17491 (4453h).

### Wifiboot UDP announce/reply and listen/connect/accept

```
+---------------------------------------------------------------------------------+
|       PC sends UDP announce message (repeatedly, as broadcast)  ;\              
|       console does TCP listen (if it isn't already listening)   ; UDP and       |
|       console sends UDP reply message (repeatedly, to PC)       ; listen/accept |
|       PC does TCP connect (upon UDP reply)                      ;               |
|       console does TCP accept (upon TCP connect)                ;/              |
+---------------------------------------------------------------------------------+
```

The announce/reply strings in UDP messages depend on the file type:

```
+-----------------------------------------------------------------------+
|       type      NDS/DSi    3DS.firm       3DS.3dsx    3DS.gba         |
|       announce  "dsboot"   "3dsfirmboot"  "3dsboot"   "gbaboot"       |
|       reply     "bootds"   "bootfirm3ds"  "boot3ds"   "bootgba"       |
+-----------------------------------------------------------------------+
```

After passing through the announce/reply phase, the actual data is transferred via TCP:

### Wifiboot TCP blocks for NDS/DSi

```
+--------------------------------------------------------------------------------+
|       PC sends NDS header (170h bytes)                 ;SMALLER ;\             
|       PC sends Info Block (90h bytes)                      ;NEW ;              |
|       console sends 32bit response word (4 bytes)               ;              |
|       PC sends Icon/Title (optional, if response.bit17)    ;NEW ;              |
|       PC sends DSi header (1000h bytes, if response.bit16)      ; TCP transfer |
|       PC sends ARM7 bootcode                                    ;              |
|       PC sends ARM9 bootcode                                    ;              |
|       PC sends ARM7i bootcode (optional, if response.bit16)     ;              |
|       PC sends ARM9i bootcode (optional, if response.bit16)     ;              |
|       PC sends commandline 32bit length (00000000h=none)        ;              |
|       PC sends commandline string (if any)                      ;/             |
+--------------------------------------------------------------------------------+
```


### Wifiboot TCP blocks for 3DS.firm

```
+--------------------------------------------------------------------------------+
|       PC sends FIRM header (200h bytes)                         ;\             
|       PC sends Info Block (90h bytes)                           ;              |
|       console sends 32bit response word (4 bytes)               ;              |
|       PC sends Icon/Title (optional, if response.bit17)         ;              |
|       PC sends Logo       (optional, if response.bit18)         ; TCP transfer |
|       PC sends Banner     (optional, if response.bit19)         ;              |
|       PC sends FIRM section 0                                   ;              |
|       PC sends FIRM section 1                                   ;              |
|       PC sends FIRM section 2                                   ;              |
|       PC sends FIRM section 3                                   ;              |
|       PC sends commandline 32bit length (0=none)                ;              |
|       PC sends commandline string (if any)                      ;/             |
+--------------------------------------------------------------------------------+
```


### Wifiboot TCP blocks for 3DS.gba

```
+--------------------------------------------------------------------------------+
|       PC sends GBA Header (C0h bytes)                           ;\             
|       PC sends Info Block (90h bytes)                           ;              |
|       PC sends GBA Footer (360h bytes)                          ;              |
|       console sends 32bit response word (4 bytes)               ; TCP transfer |
|      ;PC sends Icon/Title (optional, if response.bit17)         ;              |
|      ;PC sends Logo       (optional, if response.bit18)         ;              |
|      ;PC sends Banner     (optional, if response.bit19)         ;              |
|       PC sends GBA ROM-Image                                    ;              |
|       PC sends commandline 32bit length (0=none)                ;              |
|       PC sends commandline string (if any)                      ;/             |
+--------------------------------------------------------------------------------+
```


### Wifiboot TCP blocks for 3DS.3dsx
Not supported by wifiboot, but supported by devkitpro. The exact protocol is unknown, it seems to be similar to the above protocols, but with deflate compression (see \"3dslink\" source code for details).

### Response word (32bit)
This did originally contain 32bit error flags, and was later changed to contain request flags in bit16 and up (nonetheless, uploaders should keep treating any unexpected or unsupported request flags as errors).

```
+-----------------------------------------------------------------------+
|       0-x   Error flags                                               |
|       16    Request DSi header and ARM7i/ARM9i blocks (DSi)           |
|       17    Request Icon/Title (NDS/DSi/3DS)                          |
|       18    Request Logo       (3DS)                                  |
|       19    Request Banner     (3DS)                                  |
|       20-31 Reserved (0)                                              |
+-----------------------------------------------------------------------+
```

The downloader should set request flags only if it wants to receive extra data, and only if the header or info block indicates that data to be available.

### Info Block (90h bytes)
This did formerly contain NDS file bytes 170h..1FFh (ie. as if the cartheader were 200h bytes in size).

```
+-------------------------------------------------------------------------------------+
|       00h 8   Overall ID "BootINFO" (if other: ignore all entries below)            |
|       08h 24  Uploader name/version, zeropadded (eg. "nocash wifiboot v2.6")        |
|       20h 1   Time Seconds    (BCD, 00h..59h)       ;\                              
|       21h 1   Time Minutes    (BCD, 00h..59h)       ; current time (local timezone) |
|       22h 1   Time Hours      (BCD, 00h..23h)       ; (for updating lost RTC time)  |
|       23h 1   Time DayOfWeek  (0..6, 0=Monday)      ; (or all zeroes = none)        |
|       24h 1   Time Day        (BCD, 01h..31h)       ;                               |
|       25h 1   Time Month      (BCD, 01h..12h)       ;                               |
|       26h 1   Time Year       (BCD, 00h..99h)       ;                               |
|       27h 1   Time Century    (BCD, 00h..99h)       ;/                              |
|       28h 4   Icon/Title Size (0=None, 840h/940h/A40h/23C0h=NDS/DSi, 36C0h=3DS)     |
|       2Ch 4   Logo Size       (0=None, Other=3DS only)                              |
|       30h 4   Banner Size     (0=None, Other=3DS only)                              |
|       34h 5Ch Reserved (0)                                                          |
+-------------------------------------------------------------------------------------+
```




