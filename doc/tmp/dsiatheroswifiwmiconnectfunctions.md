# DSi Atheros Wifi - WMI Connect Functions


### WMIcmd(0001h) - WMI_CONNECT_CMD
Parameters (34h bytes):

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT8  1   networkType          ;somewhat NETWORK_TYPE related ?   (1) |
|       01h  A_UINT8  1   dot11AuthMode        ;aka DOT11_AUTH_MODE ? (1=Open, 2=WEP) |
|       02h  A_UINT8  1   authMode             ;aka AUTH_MODE ?                   (1) |
|       03h  A_UINT8  1   pairwiseCryptoType   ;aka CRYPTO_TYPE       (1=Open, 2=WEP) |
|       04h  A_UINT8  1   pairwiseCryptoLen                                       (0) |
|       05h  A_UINT8  1   groupCryptoType      ;aka CRYPTO_TYPE       (1=Open, 2=WEP) |
|       06h  A_UINT8  1   groupCryptoLen                                          (0) |
|       07h  A_UINT8  1   ssidLength                                                  |
|       08h  A_UCHAR  32  ssid[WMI_MAX_SSID_LEN]                                      |
|       28h  A_UINT16 2   channel              ;in MHz                                |
|       2Ah  A_UINT8  6   bssid[ATH_MAC_LEN]                                          |
|       30h  A_UINT32 4   ctrl_flags                                              (0) |
+-------------------------------------------------------------------------------------+
```

Returns WMI_CONNECT_EVENT (or WMI_DISCONNECT_EVENT, eg. upon bad WEP password).
NETWORK_TYPE values:

```
+--------------------------------------------------------------------------+
|       INFRA_NETWORK       = 01h      ;DSi uses 01h for Open/WEP/WPA/WPA2 |
|       ADHOC_NETWORK       = 02h                                          |
|       ADHOC_CREATOR       = 04h                                          |
|       AP_NETWORK          = 10h                                          |
+--------------------------------------------------------------------------+
```

NETWORK_SUBTYPE values (unknown purpose, and unknown if they start at 0 or 1 or so):

```
+-----------------------------------------------------------------------+
|       SUBTYPE_NONE        = unknown (maybe 0 or 1 or so?)             |
|       SUBTYPE_BT          = SUBTYPE_NONE+1                            |
|       SUBTYPE_P2PDEV      = SUBTYPE_NONE+2                            |
|       SUBTYPE_P2PCLIENT   = SUBTYPE_NONE+3                            |
|       SUBTYPE_P2PGO       = SUBTYPE_NONE+4                            |
+-----------------------------------------------------------------------+
```

DOT11_AUTH_MODE values:

```
+-------------------------------------------------------------------------------+
|       OPEN_AUTH           = 01h      ;DSi uses 01h for Open/WPA/WPA2          |
|       SHARED_AUTH         = 02h      ;DSi uses 02h for WEP                    |
|       LEAP_AUTH           = 04h  /* different from IEEE_AUTH_MODE definitions |
+-------------------------------------------------------------------------------+
```

AUTH_MODE values:

```
+-------------------------------------------------------------------------------------+
|       WMI_NONE_AUTH       = 01h      ;DSi uses 01h for Open/WEP                     |
|       WMI_WPA_AUTH        = 02h  ;\whatever maybe for RADIUS?                       
|       WMI_WPA2_AUTH       = 04h  ;/                                                 |
|       WMI_WPA_PSK_AUTH    = 08h      ;DSi uses 03h (not 08h) for WPA-PSK            |
|       WMI_WPA2_PSK_AUTH   = 10h      ;DSi uses 05h (not 10h) for WPA2-PSK           |
|       WMI_WPA_AUTH_CCKM   = 20h  ;\whatever for "Cisco Centralized Key Management"? 
|       WMI_WPA2_AUTH_CCKM  = 40h  ;/                                                 |
+-------------------------------------------------------------------------------------+
```

CRYPTO_TYPE values:

```
+-----------------------------------------------------------------------+
|       NONE_CRYPT          = 01h      ;DSi uses 01h for Open           |
|       WEP_CRYPT           = 02h      ;DSi uses 02h for WEP            |
|       TKIP_CRYPT          = 04h      ;DSi uses 03h (not 04h) for WPA  |
|       AES_CRYPT           = 08h      ;DSi uses 04h (not 08h) for WPA2 |
|       WAPI_CRYPT          = 10h  ;only if WAPI_ENABLE                 |
+-----------------------------------------------------------------------+
```

connect \"ctrl_flags\":

```
+-------------------------------------------------------------------------------------+
|       0   CONNECT_ASSOC_POLICY_USER           = 0001h                               |
|       1   CONNECT_SEND_REASSOC                = 0002h                               |
|       2   CONNECT_IGNORE_WPAx_GROUP_CIPHER    = 0004h                               |
|       3   CONNECT_PROFILE_MATCH_DONE          = 0008h                               |
|       4   CONNECT_IGNORE_AAC_BEACON           = 0010h                               |
|       5   CONNECT_CSA_FOLLOW_BSS              = 0020h                               |
|       6   CONNECT_PYXIS_REMOTE                = 0040h  ;-old code from 2008         |
|       6   CONNECT_DO_WPA_OFFLOAD              = 0040h  ;\                           
|       7   CONNECT_DO_NOT_DEAUTH               = 0080h  ; new code from 2010         |
|       8   CONNECT_WPS_FLAG                    = 0100h  ;                            |
|       9   CONNECT_IGNORE_BSSID_HINT           = 0200h  ;                            |
|       16  AP_NO_DISASSOC_UPON_DEAUTH          = 10000h ;/ <--AP configuration flags |
+-------------------------------------------------------------------------------------+
```

DEFAULT_CONNECT_CTRL_FLAGS = (CONNECT_CSA_FOLLOW_BSS)

### WMIcmd(0002h) - WMI_RECONNECT_CMD
Parameters (optional\...?\... 08h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   channel                     ;hint             |
|       02h  A_UINT8  6   bssid[ATH_MAC_LEN]          ;mandatory if set |
+-----------------------------------------------------------------------+
```


### WMIcmd(0003h) - WMI_DISCONNECT_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Returns WMI_DISCONNECT_EVENT. Uhm, or seems to crash on AR6013\...?

### WMIcmd(000Dh) - WMI_SET_DISC_TIMEOUT_CMD ;aka WMI_SET_DISCONNECT_TIMEOUT
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   disconnectTimeout           ;seconds          |
+-----------------------------------------------------------------------+
```


### WMIevent(1002h) - WMI_CONNECT_EVENT
First 10h bytes of response can be \"infra_ibss_bss\" or \"ap_sta\" or \"ap_bss\" (unclear which selects/indicates which it is, maybe the parameters from preceeding WMI_CONNECT_CMD, or from WMI_BSSINFO_EVENT\'s frame body?)
Upon error, DISCONNECT_EVENT is sent instead of WMI_CONNECT_EVENT (eg. when using WMI_CONNECT with wrong WEP password).
Event Data:

```
+----------------------------------------------------------------------------------+
|      When "infra_ibss_bss":                      ;<-- occurs for my WPA2 connect |
|       00h  A_UINT16 2   channel                     ;in MHz                      |
|       02h  A_UINT8  6   bssid[ATH_MAC_LEN]          ;                            |
|       08h  A_UINT16 2   listenInterval              ;0064h                       |
|       0Ah  A_UINT16 2   beaconInterval              ;0064h                       |
|       0Ch  A_UINT32 4   networkType                 ;00000001h                   |
|      When "ap_sta":                                                              |
|       00h  A_UINT8  1   phymode                                                  |
|       01h  A_UINT8  1   aid                                                      |
|       02h  A_UINT8  6   mac_addr[ATH_MAC_LEN]                                    |
|       08h  A_UINT8  1   auth                                                     |
|       09h  A_UINT8  1   keymgmt                                                  |
|       0Ah  A_UINT16 2   cipher                                                   |
|       0Ch  A_UINT8  1   apsd_info                                                |
|       0Dh  A_UINT8  3   unused[3]                                                |
|      When "ap_bss":                                                              |
|       00h  A_UINT16 2   channel                                                  |
|       02h  A_UINT8  6   bssid[ATH_MAC_LEN]                                       |
|       08h  A_UINT8  8   unused[8]                                                |
|      And, in all three cases:                                                    |
|       10h  A_UINT8  1   beaconIeLen                 ;16h                         |
|       11h  A_UINT8  1   assocReqLen                 ;2Fh                         |
|       12h  A_UINT8  1   assocRespLen                ;16h                         |
|       13h  A_UINT8  ..  assocInfo[1]                ;whatever 100 bytes?         |
+----------------------------------------------------------------------------------+
```

In STA mode networkType comes along with connected phy mode.
To get networkType, WMI_NETWORK_TYPE (networkType).
To get connected phymode, WMI_CONNECTED_PHYMODE(networkType) will give the phymode value.

### WMIevent(1003h) - WMI_DISCONNECT_EVENT
This event can occur when using WMI_CONNECT with wrong WEP password (instead of WMI_CONNECT_EVENT), or when failing to respond to WPA/WPA2 handshake messages, or when using WMI_DISCONNECT.
Event Data (0Ah+N bytes):

```
+------------------------------------------------------------------------------+
|       00h  A_UINT16 2    protocolReasonStatus ;reason code, see 802.11 spec. |
|       02h  A_UINT8  6    bssid[ATH_MAC_LEN]   ;set if known                  |
|       08h  A_UINT8  1    disconnectReason     ;see WMI_DISCONNECT_REASON     |
|       09h  A_UINT8  1    assocRespLen (00h=none)                             |
|       0Ah  A_UINT8  N*1  assocInfo[1]                                        |
+------------------------------------------------------------------------------+
```

WMI_DISCONNECT_REASON values:

```
+-------------------------------------------------------------------------------------+
|       NO_NETWORK_AVAIL      = 01h  ;-occurs on wrong WEP key                        |
|       LOST_LINK             = 02h  ;-bmiss                                          |
|       DISCONNECT_CMD        = 03h  ;-requested via disconnect command               |
|       BSS_DISCONNECTED      = 04h  ;-occurs after some minutes of inactivity?       |
|       AUTH_FAILED           = 05h  ;-reportedly occurs if AP was already connected? |
|       ASSOC_FAILED          = 06h                                                   |
|       NO_RESOURCES_AVAIL    = 07h                                                   |
|       CSERV_DISCONNECT      = 08h                                                   |
|       INVALID_PROFILE       = 0Ah                                                   |
|       DOT11H_CHANNEL_SWITCH = 0Bh                                                   |
|       PROFILE_MISMATCH      = 0Ch                                                   |
|       PYXIS_VIRT_ADHOC_DISC = 0Dh  ;-old code from 2008                             |
|       CONNECTION_EVICTED    = 0Dh  ;\                                               
|       IBSS_MERGE            = 0Eh  ; new code from 2010                             |
|       EXCESS_TX_RETRY       = 0Fh  ;/  <--TX frames failed after excessive retries  |
+-------------------------------------------------------------------------------------+
```




