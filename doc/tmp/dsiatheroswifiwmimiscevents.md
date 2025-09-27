# DSi Atheros Wifi - WMI Misc Events


### WMIevent(000Eh) - WMI_GET_CHANNEL_LIST_CMD
### WMIevent(001Ch) - WMI_GET_TX_PWR_CMD
### WMIevent(0035h) - WMI_GET_FIXRATES_CMD
### WMIevent(003Eh) - WMI_GET_KEEPALIVE_CMD
### WMIevent(F001h) - WMI_GET_BITRATE_CMD
Events/Responses with same ID as corresponding command.
See corresponding commands for description of reply data.

### WMIevent(1001h) - WMI_READY_EVENT
This event exists with numerous (incorrect) definitions, claiming the event data to be 07h, 0Bh, 0Ch, 0Fh, or 10h bytes in length:
Event Data (0Ch bytes on DSi, as returned by DSi firmware):

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  6  macaddr[ATH_MAC_LEN]   ;MAC addr of DSi console        |
|       06h  A_UINT8  1  phyCapability    (=02h aka "11G")  ;WMI_PHY_CAPABILITY |
|       07h  A_UINT8  1  unused/padding                                         |
|       08h  A_UINT32 4  version (=2100007Bh/2300006Ch) (firmware version)      |
+-------------------------------------------------------------------------------+
```

Event Data (07h bytes, exists in AR6002 ROM, but overridden by DSi firmware):

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  6  macaddr[ATH_MAC_LEN]                                   |
|       06h  A_UINT8  1  phyCapability                      ;WMI_PHY_CAPABILITY |
+-------------------------------------------------------------------------------+
```

Event Data (0Bh bytes, accidently claimed to be so in source code from 2008):

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT32 4  version                                                |
|       04h  A_UINT8  6  macaddr[ATH_MAC_LEN]                                   |
|       0Ah  A_UINT8  1  phyCapability                      ;WMI_PHY_CAPABILITY |
+-------------------------------------------------------------------------------+
```

Event Data (0Fh bytes, accidently claimed to be so in source code from 2010):

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT32 4  sw_version                                             |
|       04h  A_UINT32 4  abi_version                                            |
|       08h  A_UINT8  6  macaddr[ATH_MAC_LEN]                                   |
|       0Eh  A_UINT8  1  phyCapability                      ;WMI_PHY_CAPABILITY |
+-------------------------------------------------------------------------------+
```

Event Data (10h bytes, as done by 3DS function in wifi firmware RAM):

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  6  macaddr[ATH_MAC_LEN]   ;MAC addr of DSi console        |
|       06h  A_UINT8  1  phyCapability    (=02h aka "11G")  ;WMI_PHY_CAPABILITY |
|       07h  A_UINT8  1  unused/padding                                         |
|       08h  A_UINT32 4  version (230000B3h) (firmware version)                 |
|       0Ch  A_UINT16 2  whus         ;=[004134h] ;some I/O register ???        |
|       0Eh  A_UINT16 2  what         ;=[520088h] ;hi_hci_uart_baud  ???        |
+-------------------------------------------------------------------------------+
```

WMI_PHY_CAPABILITY values (maybe the \"11\" is related to \"IEEE 802.11\"?):

```
+-----------------------------------------------------------------------+
|       WMI_11A_CAPABILITY   = 1                                        |
|       WMI_11G_CAPABILITY   = 2                                        |
|       WMI_11AG_CAPABILITY  = 3                                        |
|       WMI_11NA_CAPABILITY  = 4                                        |
|       WMI_11NG_CAPABILITY  = 5                                        |
|       WMI_11NAG_CAPABILITY = 6                                        |
+-----------------------------------------------------------------------+
```


### WMIevent(1004h) - WMI_BSSINFO_EVENT aka WMI_BSS_INFO
Event Data (0Ch+N bytes or 10h+N bytes on DSi, depending on version setting):

```
+-------------------------------------------------------------------------------------+
|      When version<2:                                                                |
|       00h  A_UINT16 2   channel      ;in MHz                ;\                      
|       02h  A_UINT8  1   frameType    ;see WMI_BI_FTYPE      ;                       |
|       03h  A_UINT8  1   snr      ;eg. 33h                   ; WMI_BSS_INFO_HDR      |
|       04h  A_INT16  2   rssi     ;eg. FFD4h aka "33h-95"    ; version 1 (10h bytes) |
|       06h  A_UINT8  6   bssid[ATH_MAC_LEN]                  ;                       |
|       0Ch  A_UINT32 4   ieMask                              ;/                      |
|       10h  BODY     ... beacon or probe-response frame body ;-Body (timestamp etc)  |
|      When version>=2:                                                               |
|       00h  A_UINT16 2   channel      ;in MHz                ;\                      
|       02h  A_UINT8  1   frameType    ;see WMI_BI_FTYPE      ; WMI_BSS_INFO_HDR2     |
|       03h  A_UINT8  1   snr   (implies "rssi=snr-95" in v2) ; version 2 (0Ch bytes) |
|       04h  A_UINT8  6   bssid[ATH_MAC_LEN]                  ;                       |
|       0Ah  A_UINT16 2   ieMask         (only 2 bytes in v2) ;/                      |
|       0Ch  BODY     ... beacon or probe-response frame body ;-Body (timestamp etc)  |
+-------------------------------------------------------------------------------------+
```

BUG: The \"snr\" value can be negative, but isn\'t sign-expanded to 16bit, and the and the rssi value at \[04h\] does then contain nonsense (eg. spotted bytes at\[03h..05h\] are \"FC 9D 00\").
The BODY starts with 64bit Timestamp, 16bit BeaconInterval, etc. For details, see:
- [DS Wifi IEEE802.11 Managment Frames (Type=0)](./dswifiieee80211managmentframestype0.md)
The size of the BODY varies per access point (from around 64 bytes to exceeding 256 bytes).
The DSi firmware contains code for both of the above HDR versions (unknown if/when/how it does use which version; the DSi Browser receives the older type, with 10h+N bytes).
BSS Info Event.
Mechanism used to inform host of the presence and characteristic of wireless networks present. Consists of bss info header followed by the beacon or probe-response frame body. The 802.11 header is not included.
BSS INFO HDR version 2.0:
With 6 bytes HTC header and 6 bytes of WMI header WMI_BSS_INFO_HDR cannot be accomodated in the removed 802.11 management header space.

```
+-----------------------------------------------------------------------+
|       - Reduce the ieMask to 2 bytes as only two bit flags are used   |
|       - Remove rssi and compute it on the host. rssi = snr - 95       |
+-----------------------------------------------------------------------+
```

WMI_BI_FTYPE values:

```
+-----------------------------------------------------------------------+
|       BEACON_FTYPE      = 01h                                         |
|       PROBERESP_FTYPE   = 02h                                         |
|       ACTION_MGMT_FTYPE = 03h                                         |
|       PROBEREQ_FTYPE    = 04h                                         |
+-----------------------------------------------------------------------+
```

BSS_ELEMID values (unclear WHAT that is, maybe the \"ieMask\" stuff, which said to use \"two bit flags\"):

```
+---------------------------------------------------------------------------------+
|       BSS_ELEMID_CHANSWITCH = 01h    ;value for bit0? (or bit-number for bit1?) |
|       BSS_ELEMID_ATHEROS    = 02h    ;value for bit1? (or bit-number for bit2?) |
+---------------------------------------------------------------------------------+
```


### WMIevent(1006h) - WMI_REGDOMAIN_EVENT ;aka WMI_REG_DOMAIN_EVENT
Event Data (04h bytes):

```
+------------------------------------------------------------------------------+
|       00h  A_UINT32 4   regDomain  ;80000188h on DSi (after firmware upload) |
+------------------------------------------------------------------------------+
```

New Regulatory Domain Event.
Value 80000188h on DSi/AR6002 and 80000348h on DSi/AR6013 (these are based on the wifi firmware\'s \"RGBD\" DataSet, with 0188h=\"JP\" and 0348h=\"US\").
The country code seems to be derived from I2C EEPROM\[008h\], and the database is used to translate the country code to enabled channels.

### WMIevent(1008h) - WMI_NEIGHBOR_REPORT_EVENT
Event Data:
typedef PREPACK struct {

```
+-----------------------------------------------------------------------+
|       00h  A_INT8              1     numberOfAps;                     |
|       01h  WMI_NEIGHBOR_INFO   N*7   neighbor[1];                     |
+-----------------------------------------------------------------------+
```

WMI_NEIGHBOR_INFO structure:

```
+-----------------------------------------------------------------------+
|         A_UINT8 6    bssid[ATH_MAC_LEN];                              |
|         A_UINT8 1    bssFlags;            /* see WMI_BSS_FLAGS        |
+-----------------------------------------------------------------------+
```

WMI_BSS_FLAGS values:

```
+-----------------------------------------------------------------------+
|       WMI_DEFAULT_BSS_FLAGS   = 00h                                   |
|       WMI_PREAUTH_CAPABLE_BSS = 01h                                   |
|       WMI_PMKID_VALID_BSS     = 02h                                   |
+-----------------------------------------------------------------------+
```

The WMI_NEIGHBOR_REPORT Event is generated by the target to inform the host of BSS\'s it has found that matches the current profile.
It can be used by the host to cache PMKs and/to initiate pre-authentication if the BSS supports it. The first bssid is always the current associated BSS.
The bssid and bssFlags information repeats according to the number or APs reported.

### WMIevent(100Eh) - WMI_OPT_RX_FRAME_EVENT aka WMI_OPT_RX_INFO
Event Data (10h+N bytes):

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT16 2   channel                        ;\                          
|       02h  A_UINT8  1   frameType  ;see WMI_OPT_FTYPE  ; special frame info header |
|       03h  A_INT8   1   snr                            ;                           |
|       04h  A_UINT8  6   srcAddr[ATH_MAC_LEN]           ;                           |
|       0Ah  A_UINT8  6   bssid[ATH_MAC_LEN]             ;/                          |
|       10h  ...      ..  body (having WHAT length?)     ;-special frame body        |
+------------------------------------------------------------------------------------+
```

Special frame receive Event.
Mechanism used to inform host of the receiption of the special frames.
The 802.11 header is not included.
See also: WMI_OPT_TX_FRAME_CMD

### WMIevent(1010h) - WMI_EXTENSION_EVENT ;prefix for WMIX events\...
Unknown, probably similar prefix as \"WMIX_CMD_HDR\" with 32bit WMIX value.

### WMIevent(1011h) - WMI_CAC_EVENT
Supposedly related to Call Admission Control (CAC), eg. for VoIP.
Event Data (42h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1    ac;                                          |
|       01h  A_UINT8  1    cac_indication;                              |
|       02h  A_UINT8  1    statusCode;                                  |
|       03h  A_UINT8  3Fh  tspecSuggestion[WMM_TSPEC_IE_LEN];           |
+-----------------------------------------------------------------------+
```

CAC_INDICATION values:

```
+-----------------------------------------------------------------------+
|       CAC_INDICATION_ADMISSION      = 00h                             |
|       CAC_INDICATION_ADMISSION_RESP = 01h                             |
|       CAC_INDICATION_DELETE         = 02h                             |
|       CAC_INDICATION_NO_RESP        = 03h                             |
+-----------------------------------------------------------------------+
```

#define WMM_TSPEC_IE_LEN = 63

### WMIevent(1017h) - WMI_APLIST_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8      1    apListVer;                               |
|       01h  A_UINT8      1    numAP;                                   |
|       02h  WMI_AP_INFO  N*8  apList[1];                               |
+-----------------------------------------------------------------------+
```

APLIST_VER values (only one defined):

```
+-----------------------------------------------------------------------+
|         APLIST_VER1 = 1,                                              |
+-----------------------------------------------------------------------+
```

WMI_AP_INFO structure:

```
+-----------------------------------------------------------------------+
|       typedef PREPACK union {                                         |
|         WMI_AP_INFO_V1  8   apInfoV1;                                 |
|       } POSTPACK WMI_AP_INFO;                                         |
+-----------------------------------------------------------------------+
```

WMI_AP_INFO_V1 structure:

```
+-----------------------------------------------------------------------+
|         A_UINT8  6   bssid[ATH_MAC_LEN];                              |
|         A_UINT16 2   channel;                                         |
+-----------------------------------------------------------------------+
```


### WMIevent(1019h) - WMI_GET_PMKID_LIST_EVENT ;reply to CMD F006h
See WMI_GET_PMKID_LIST_CMD for response details.



