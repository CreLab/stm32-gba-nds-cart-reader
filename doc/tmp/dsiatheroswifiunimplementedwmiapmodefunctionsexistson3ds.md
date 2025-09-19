# DSi Atheros Wifi - Unimplemented WMI AP Mode Functions (exists on 3DS)


### AP Mode
Whatever that is\... probably something where the AR600x acts as Access Point (AP) for other Stations (STA).
The DSi doesn\'t support AP Mode stuff, however, 3DS firmware type4 does support most of them (but with F00Ah..F013h renumbered to 004Ah..0052h).

### AP Mode definitions
Changing the following values needs compilation of both driver and firmware.

```
+-----------------------------------------------------------------------------------+
|       AP_MAX_NUM_STA = 4   ;for old AR6002_REV2 version                           |
|       AP_MAX_NUM_STA = 10  ;for newer versions                                    |
|       NUM_DEV        = 3   ;Maximum no. of virtual interface supported            |
|       NUM_CONN       = (AP_MAX_NUM_STA + NUM_DEV)                                 |
|       AP_ACL_SIZE         = 10                                                    |
|       IEEE80211_MAX_IE    = 256                                                   |
|       MCAST_AID           = 0FFh   ;Spl. AID used to set DTIM flag in the beacons |
|       DEF_AP_COUNTRY_CODE = "US "                                                 |
|       DEF_AP_WMODE_G      = WMI_11G_MODE                                          |
|       DEF_AP_WMODE_AG     = WMI_11AG_MODE                                         |
|       DEF_AP_DTIM         = 5                                                     |
|       DEF_BEACON_INTERVAL = 100                                                   |
|       AP_DISCONNECT_STA_LEFT     = 101  ;\                                        
|       AP_DISCONNECT_FROM_HOST    = 102  ;                                         |
|       AP_DISCONNECT_COMM_TIMEOUT = 103  ; AP mode disconnect reasons              |
|       AP_DISCONNECT_MAX_STA      = 104  ; (101..107 decimal):                     |
|       AP_DISCONNECT_ACL          = 105  ;                                         |
|       AP_DISCONNECT_STA_ROAM     = 106  ;                                         |
|       AP_DISCONNECT_DFS_CHANNEL  = 107  ;/                                        |
+-----------------------------------------------------------------------------------+
```


### WMIcmd(F00Bh or 004Ah) - WMI_AP_HIDDEN_SSID_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   hidden_ssid;                                  |
+-----------------------------------------------------------------------+
```

#define HIDDEN_SSID_FALSE = 0
#define HIDDEN_SSID_TRUE = 1

### WMIcmd(F00Ch or 004Bh) - WMI_AP_SET_NUM_STA_CMD aka WMI_AP_NUM_STA_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   num_sta;                                      |
+-----------------------------------------------------------------------+
```


### WMIcmd(F00Dh or 004Ch) - WMI_AP_ACL_POLICY_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   policy;                                       |
|      #define AP_ACL_DISABLE          = 00h                            |
|      #define AP_ACL_ALLOW_MAC        = 01h                            |
|      #define AP_ACL_DENY_MAC         = 02h                            |
|      #define AP_ACL_RETAIN_LIST_MASK = 80h                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(F00Eh or 004Dh) - WMI_AP_ACL_MAC_LIST_CMD aka WMI_AP_ACL_MAC_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   action;                                       |
|       01h  A_UINT8  1   index;                                        |
|       02h  A_UINT8  6   mac[ATH_MAC_LEN];                             |
|       08h  A_UINT8  1   wildcard;                                     |
+-----------------------------------------------------------------------+
```

ADD_MAC_ADDR = 1
DEL_MAC_ADDR = 2
There is also a \"WMI_AP_ACL\" structure with unknown purpose (maybe internally used in Xtensa memory or whatever):

```
+-----------------------------------------------------------------------+
|       A_UINT16 2   index;                                             |
|       A_UINT8  ... acl_mac[AP_ACL_SIZE][ATH_MAC_LEN];                 |
|       A_UINT8  ..  wildcard[AP_ACL_SIZE];                             |
|       A_UINT8  1   policy;                                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(F00Fh or 004Eh) - WMI_AP_CONFIG_COMMIT_CMD
Unknown/undocumented? Except, see this:
sp.chip1stop.com/sp/wp-content/uploads/2015/05/gt202wifimoduleapiguidev13.pdf
Parameters: 34h bytes on 3DS.
Command Parameters: WMI_AP_CONFIG_COMMIT_CMD

```
+------------------------------------------------------------------------------------+
|       Type Name Comment                                                            |
|       00h  A_UINT8 networktype NETWORK_TYPE                                        |
|              0x01 INFRA_NETWORK                                                    |
|              0x02 ADHOC_NETWORK                                                    |
|              0x04 ADHOC_CREATOR                                                    |
|       01h  A_UINT8 dot11authmode DOT11_AUTH_MODE                                   |
|              0x01 OPEN_AUTH                                                        |
|              0x02 SHARED_AUTH                                                      |
|       02h  A_UINT8 authmode AUTH_MODE                                              |
|              0x01 NONE_AUTH                                                        |
|              0x02 WPA_AUTH                                                         |
|              0x04 WPA2_AUTH                                                        |
|              0x08 WPA_PSK_AUTH                                                     |
|              0x10 WPA2_PSK_AUTH                                                    |
|              0x20 WPA_AUTH_CCKM                                                    |
|              0x40 WPA2_AUTH_CCKM                                                   |
|       03h  A_UINT8 pairwiseCryptoType CRYPTO_TYPE                                  |
|              0x01 NONE_CRYPT                                                       |
|              0x02 WEP_CRYPT                                                        |
|              0x04 TKIP_CRYPT                                                       |
|              0x08 AES_CRYPT                                                        |
|       04h  A_UINT8 pairwiseCryptoLen Length in bytes. Valid when the type is       |
|              WEP_CRYPT, otherwise this should be 0                                 |
|       05h  A_UINT8 groupCryptoType CRYPTO_TYPE                                     |
|       06h  A_UINT8 groupCryptoLen Length in bytes. Valid when the type is          |
|              WEP_CRYPT, otherwise this should be 0                                 |
|       07h  A_UINT8 ssidLength SSID length for the AP mode                          |
|       08h  A_UCHAR ssid[32] SSID value for the SoftAP mode                         |
|       28h  A_UINT16 channel Channel in which the AP mode has to be started         |
|       2Ah  A_UINT8 bssid[6]                                                        |
|       30h  A_UINT8 ctrl_flags WMI_CONNECT_CTRL_FLAGS_BITS                          |
|         0x0001 CONNECT_ASSOC_POLICY_USER  Associative frames are sent using        |
|                  the policy specified by the CONNECT_SEND-_REASSOC flag            |
|         0x0004 CONNECT_IGNORE_WPAx-_GROUP_CIPHER  Ignore the WPAx group cipher     |
|                  for WPA/WPA2                                                      |
|         0x0040 CONNECT_DO_WPA_OFFLOAD  Use the authenticator in the QCA4002(=chip) |
|         0x0100 CONNECT_WPS_FLAG   Set to indicate that the AP will add WPS IE to   |
|                  its beacon                                                        |
|         0xFFFF                    Reset all control flags                          |
+------------------------------------------------------------------------------------+
```

Uh, the flags are said to be 8bit\... but can be as large as FFFFh?
Also, 3DS seems to use 34h bytes total\... so flags would be 32bit maybe?
Whereof, 3DS seems to be simply ignoring param \[2Ah..33h\].

### WMIcmd(F010h or 004Fh) - WMI_AP_SET_MLME_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6  mac[ATH_MAC_LEN];                              |
|       06h  A_UINT16 2  reason;              /* 802.11 reason code     |
|       08h  A_UINT8  1  cmd;                 /* operation to perform   |
+-----------------------------------------------------------------------+
```

MLME Commands (aka above \"cmd\"):

```
+-----------------------------------------------------------------------+
|       WMI_AP_MLME_ASSOC       1   /* associate station                |
|       WMI_AP_DISASSOC         2   /* disassociate station             |
|       WMI_AP_DEAUTH           3   /* deauthenticate station           |
|       WMI_AP_MLME_AUTHORIZE   4   /* authorize station                |
|       WMI_AP_MLME_UNAUTHORIZE 5   /* unauthorize station              |
+-----------------------------------------------------------------------+
```


### WMIcmd(F011h or 0050h) - WMI_AP_SET_PVB_CMD
Parameters (06h bytes on 3DS, but other variant exists, too):

```
+-----------------------------------------------------------------------+
|       06h 08h  <---- total size (on 3DS it's 06h)                     |
|       00h 00h  A_BOOL   4  flag;                                      |
|       --  04h  A_UINT16 2  rsvd;                                      |
|       04h 06h  A_UINT16 2  aid;                                       |
+-----------------------------------------------------------------------+
```

Note: The 3DS command list does support the 6-byte variant, but it seem to be simply ignoring the command & parameters.

### WMIcmd(F012h or 0051h) - WMI_AP_CONN_INACT_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  period;                                        |
+-----------------------------------------------------------------------+
```


### WMIcmd(F013h or 0052h) - WMI_AP_PROT_SCAN_TIME_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  period_min;                                    |
|       04h  A_UINT32 4  dwell_ms;                                      |
+-----------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _____________________ Below doesn't seem to exist on 3DS _____________________ |
+-------------------------------------------------------------------------------------+
```


### WMIcmd(F014h) - WMI_AP_SET_COUNTRY_CMD ;aka formerly WMI_SET_COUNTRY_CMD
Parameters:

```
+----------------------------------------------------------------------------------+
|       00h  A_UCHAR  3  countryCode[3]      ;two letter ASCII... plus ending 00h? |
+----------------------------------------------------------------------------------+
```

WMI_DISABLE_REGULATORY_CODE = \"FF\" ;uh, are that THREE chars?

### WMIcmd(F015h) - WMI_AP_SET_DTIM_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  dtim;   ;wake up each N beacon interval units  |
+-----------------------------------------------------------------------+
```

DTIM interval used to check for multicast packets.

### WMIcmd(F016h or N/A) - WMI_AP_MODE_STAT_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (if any)                                                |
+-----------------------------------------------------------------------+
```

Reply:

```
+-----------------------------------------------------------------------+
|       Unknown (if any)                                                |
+-----------------------------------------------------------------------+
```

There is an \"WMI_AP_MODE_STAT\" structure (said to be an event, although there is no WMIevent(xxxxh) number defined for it anywhere) (and, the \"action\" entry sounds more like an command/parameter than like an event/response?):
WMI_AP_MODE_STAT structure:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32            action;                                |
|       04h  WMI_PER_STA_STAT    sta[AP_MAX_NUM_STA];                   |
+-----------------------------------------------------------------------+
```

Mysterious values (probably for the \"action\" entry:

```
+-----------------------------------------------------------------------+
|       AP_GET_STATS   = 0                                              |
|       AP_CLEAR_STATS = 1                                              |
+-----------------------------------------------------------------------+
```

WMI_PER_STA_STAT structure (for the \"sta\" entries):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 tx_bytes;                                         |
|       04h  A_UINT32 tx_pkts;                                          |
|       08h  A_UINT32 tx_error;                                         |
|       0Ch  A_UINT32 tx_discard;                                       |
|       10h  A_UINT32 rx_bytes;                                         |
|       14h  A_UINT32 rx_pkts;                                          |
|       18h  A_UINT32 rx_error;                                         |
|       1Ch  A_UINT32 rx_discard;                                       |
|       20h  A_UINT32 aid;                                              |
+-----------------------------------------------------------------------+
```


### WMIcmd(F027h or N/A) - WMI_AP_SET_11BG_RATESET_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  rateset;                                       |
|      AP_11BG_RATESET1    = 1                                          |
|      AP_11BG_RATESET2    = 2                                          |
|      DEF_AP_11BG_RATESET = AP_11BG_RATESET1                           |
+-----------------------------------------------------------------------+
```


### WMIcmd(F05Ah or F059h or N/A) - WMI_AP_SET_APSD_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  enable;                                        |
+-----------------------------------------------------------------------+
```

WMI_AP_APSD_DISABLED = 0
WMI_AP_APSD_ENABLED = 1

### WMIcmd(F05Bh or F05Ah or N/A) - WMI_AP_APSD_BUFFERED_TRAFFIC_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2  aid;                                           |
|       02h  A_UINT16 2  bitmap;                                        |
|       04h  A_UINT32 4  flags;                                         |
+-----------------------------------------------------------------------+
```

WMI_AP_APSD_BUFFERED_TRAFFIC_FLAGS values (only one defined)

```
+-----------------------------------------------------------------------+
|       WMI_AP_APSD_NO_DELIVERY_FRAMES_FOR_THIS_TRIGGER = 01h           |
+-----------------------------------------------------------------------+
```


### WMIcmd(F06Eh or N/A) - WMI_AP_JOIN_BSS_CMD
Unknown/undocumented (some new command, invented in 2012 or so).

### WMIevent(?) - WMI_AP_MODE_STAT_EVENT ;reply to WMI_AP_MODE_STAT_CMD ?
Maybe there is an event/reply for the \"WMI_AP_MODE_STAT_CMD\" command (see above).

### WMIevent(101Ch) - WMI_PSPOLL_EVENT ;aka WMI_PS_POLL_EVENT ;AP mode related?
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2  aid;                                           |
+-----------------------------------------------------------------------+
```

Whatever. Said to be an \"AP mode event\". Maybe WMI_SET_AP_PS_CMD related?

### WMIcmd(F0AFh) - WMI_AP_PSBUFF_OFFLOAD ;QCA4002 chipset on GT202 WiFi module

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT8 Enable                                                           |
|               0 Enable buffering mechanism in firmware to handle power save clients |
|               1 Disable buffering mechanism                                         |
|       01h  A_UINT8 psBufCount  Range: 1-3,                                          |
|               Specifies number of buffers allowed to buffer power save packets.     |
+-------------------------------------------------------------------------------------+
```




