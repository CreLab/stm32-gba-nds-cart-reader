# DSi Atheros Wifi - WMI Misc Commands


### WMIcmd(0004h) - WMI_SYNCHRONIZE_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  dataSyncMap          ;00h, 01h, or 09h used?   |
+-----------------------------------------------------------------------+
```


### WMIcmd(0009h) - WMI_SET_BSS_FILTER_CMD ;aka WMI_BSS_FILTER_CMD
Parameters (08h bytes):

```
+------------------------------------------------------------------------------+
|       00h  A_UINT8  1  bssFilter;                      /* see WMI_BSS_FILTER |
|       01h  A_UINT8  1  reserved1;                      /* For alignment      |
|       02h  A_UINT16 2  reserved2;                      /* For alignment      |
|       04h  A_UINT32 4  ieMask;                                               |
+------------------------------------------------------------------------------+
```

WMI_BSS_FILTER values:

```
+------------------------------------------------------------------------+
|       NONE_BSS_FILTER        = 00h  ;no beacons forwarded              |
|       ALL_BSS_FILTER         = 01h  ;all beacons forwarded             |
|       PROFILE_FILTER         = 02h  ;only beacons matching profile     |
|       ALL_BUT_PROFILE_FILTER = 03h  ;all but beacons matching profile  |
|       CURRENT_BSS_FILTER     = 04h  ;only beacons matching current BSS |
|       ALL_BUT_BSS_FILTER     = 05h  ;all but beacons matching BSS      |
|       PROBED_SSID_FILTER     = 06h  ;beacons matching probed ssid      |
|       LAST_BSS_FILTER        = 07h  ;marker only                       |
+------------------------------------------------------------------------+
```


### WMIcmd(000Ah) - WMI_SET_PROBED_SSID_CMD
Parameters (23h bytes):

```
+------------------------------------------------------------------------+
|       00h  A_UINT8  1   entryIndex;      /* 0 to MAX_PROBED_SSID_INDEX |
|       01h  A_UINT8  1   flag;            /* WMI_SSID_FLG               |
|       02h  A_UINT8  1   ssidLength;                                    |
|       03h  A_UINT8  32  ssid[32];                                      |
+------------------------------------------------------------------------+
```

#define MAX_PROBED_SSID_INDEX = 15
WMI_SSID_FLAG values:

```
+-----------------------------------------------------------------------+
|       DISABLE_SSID_FLAG  = 00h    /* disables entry                   |
|       SPECIFIC_SSID_FLAG = 01h    /* probes specified ssid            |
|       ANY_SSID_FLAG      = 02h    /* probes for any ssid              |
+-----------------------------------------------------------------------+
```


### WMIcmd(000Bh) - WMI_SET_LISTEN_INT_CMD
Parameters (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   listenInterval;                               |
|       02h  A_UINT16 2   numBeacons;                                   |
+-----------------------------------------------------------------------+
```

The Listen interval is between 15 and 3000 TUs

```
+-----------------------------------------------------------------------+
|       MIN_LISTEN_INTERVAL = 15     ;min = 15                          |
|       MAX_LISTEN_INTERVAL = 5000   ;max = 5000 or 3000, uh?           |
|       MIN_LISTEN_BEACONS  = 1                                         |
|       MAX_LISTEN_BEACONS  = 500                                       |
+-----------------------------------------------------------------------+
```


### WMIcmd(000Ch) - WMI_SET_BMISS_TIME_CMD
Parameters (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   bmissTime;                                    |
|       02h  A_UINT16 2   numBeacons;                                   |
+-----------------------------------------------------------------------+
```

Valid values are between 1000 and 5000 TUs

```
+-----------------------------------------------------------------------+
|       MIN_BMISS_TIME    = 1000                                        |
|       MAX_BMISS_TIME    = 5000                                        |
|       MIN_BMISS_BEACONS = 1                                           |
|       MAX_BMISS_BEACONS = 50                                          |
+-----------------------------------------------------------------------+
```


### WMIcmd(000Fh) - WMI_SET_BEACON_INT_CMD
Parameters (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2    beaconInterval;                              |
+-----------------------------------------------------------------------+
```


### WMIcmd(001Ah) - WMI_SET_PMKID_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6   bssid[ATH_MAC_LEN];                           |
|       06h  A_UINT8  1   enable;                 /* PMKID_ENABLE_FLG   |
|       07h  A_UINT8  16  pmkid[WMI_PMKID_LEN];                         |
+-----------------------------------------------------------------------+
```

#define WMI_PMKID_LEN = 16
PMKID_ENABLE_FLG values:

```
+-----------------------------------------------------------------------+
|       PMKID_DISABLE = 0                                               |
|       PMKID_ENABLE  = 1                                               |
+-----------------------------------------------------------------------+
```


### WMIcmd(001Dh) - WMI_SET_ASSOC_INFO_CMD
Parameters:

```
+----------------------------------------------------------------------------+
|       00h  A_UINT8  1   ieType                                             |
|       01h  A_UINT8  1   bufferSize                                         |
|       02h  A_UINT8  N*1 assocInfo[1]         ;up to WMI_MAX_ASSOC_INFO_LEN |
+----------------------------------------------------------------------------+
```

A maximum of 2 private IEs can be sent in the \[Re\]Assoc request.
A 3rd one, the CCX version IE can also be set from the host.

```
+-----------------------------------------------------------------------+
|       WMI_MAX_ASSOC_INFO_TYPE   = 2                                   |
|       WMI_CCX_VER_IE            = 2   /* ieType to set CCX Version IE |
|       WMI_MAX_ASSOC_INFO_LEN    = 240                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(001Eh) - WMI_ADD_BAD_AP_CMD
Parameters (07h bytes):

```
+-------------------------------------------------------------------------+
|       00h  A_UINT8  1  badApIndex            ;0 to WMI_MAX_BAD_AP_INDEX |
|       01h  A_UINT8  6  bssid[ATH_MAC_LEN]                               |
|      WMI_MAX_BAD_AP_INDEX     = 1                                       |
+-------------------------------------------------------------------------+
```


### WMIcmd(001Fh) - WMI_DELETE_BAD_AP_CMD
Parameters (01h bytes):

```
+-------------------------------------------------------------------------+
|       00h  A_UINT8  1  badApIndex            ;0 to WMI_MAX_BAD_AP_INDEX |
+-------------------------------------------------------------------------+
```


### WMIcmd(0023h) - WMI_SET_ACCESS_PARAMS_CMD
Parameters:

```
+---------------------------------------------------------------------------+
|       00h  A_UINT16 2  txop           ;in units of 32 usec                |
|       02h  A_UINT8  1  eCWmin                                             |
|       03h  A_UINT8  1  eCWmax                                             |
|       04h  A_UINT8  1  aifsn                                              |
|       05h  A_UINT8  1  ac                                                 |
|      WMI_DEFAULT_TXOP_ACPARAM   = 0       /* implies one MSDU             |
|      WMI_DEFAULT_ECWMIN_ACPARAM = 4       /* corresponds to CWmin of 15   |
|      WMI_DEFAULT_ECWMAX_ACPARAM = 10      /* corresponds to CWmax of 1023 |
|      WMI_MAX_CW_ACPARAM         = 15      /* maximum eCWmin or eCWmax     |
|      WMI_DEFAULT_AIFSN_ACPARAM  = 2                                       |
|      WMI_MAX_AIFSN_ACPARAM      = 15                                      |
+---------------------------------------------------------------------------+
```


### WMIcmd(0025h) - WMI_SET_OPT_MODE_CMD
Parameters (01h bytes on DSi?, but parameter structure is undocumented):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8     optMode (documented in code from 2008 only)    |
+-----------------------------------------------------------------------+
```

OPT_MODE_TYPE values:

```
+----------------------------------------------------------------------------------+
|       SPECIAL_OFF      = unknown (maybe 0 or 1 or so)  ;\                        
|       SPECIAL_ON       = SPECIAL_OFF+1                 ; code from 2008 only     |
|       PYXIS_ADHOC_ON   = SPECIAL_OFF+2                 ; (removed/undoc in 2010) |
|       PYXIS_ADHOC_OFF  = SPECIAL_OFF+3                 ;/                        |
+----------------------------------------------------------------------------------+
```


### WMIcmd(0026h) - WMI_OPT_TX_FRAME_CMD
Unknown/undocumented purpose. Unknown if/how this is implemented in DSi. The DSi does redirect cmd 0026h to a function handler, but that handler does just trigger a misalign exception. However, the DSi does also have a function for handling the command (with \"opt_tx_frame_cmd\" string in AR6013/AR6014), but that function doesn\'t seem to be called upon command number 0026h. Maybe the CMD is triggered upon special flags in the SDIO transfer block header, rather than by the command number?
Parameters (11h bytes on DSi)

```
+-----------------------------------------------------------------------+
|       Unknown (11h bytes, but parameter structure is undocumented)    |
+-----------------------------------------------------------------------+
```

See also: WMI_OPT_RX_FRAME_EVENT (counterpart in opposite direction), and WMI_SET_OPT_MODE_CMD.

### WMIcmd(0027h) - WMI_SET_VOICE_PKT_SIZE_CMD
Parameters (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   voicePktSize                                  |
+-----------------------------------------------------------------------+
```


### WMIcmd(0028h) - WMI_SET_MAX_SP_LEN_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  maxSPLen                                       |
+-----------------------------------------------------------------------+
```

APSD_SP_LEN_TYPE values:

```
+-----------------------------------------------------------------------+
|         DELIVER_ALL_PKT = 00h                                         |
|         DELIVER_2_PKT   = 01h                                         |
|         DELIVER_4_PKT   = 02h                                         |
|         DELIVER_6_PKT   = 03h                                         |
+-----------------------------------------------------------------------+
```


### WMIcmd(002Eh) - WMI_EXTENSION_CMD ;prefix for WMIX \"Non-wireless extensions\"
Parameters:

```
+----------------------------------------------------------------------------+
|       00h  UNIT32   4    WMIX Command (values 2001h and up)  ;WMIX_CMD_HDR |
|       04h  ...      ..   WMIX Parameter(s)                                 |
+----------------------------------------------------------------------------+
```

Prefix for WMIX commands.

### WMIcmd(0031h) - WMI_SET_LPREAMBLE_CMD
Parameters (01h bytes on DSi?, but other sources claim 02h bytes):

```
+-----------------------------------------------------------------------+
|       01h 02h   <---- total size (on DSi it's 01h, ie. left column)   |
|       00h 00h  A_UINT8  1   status                                    |
|       --  01h  A_UINT8  1   preamblePolicy                            |
+-----------------------------------------------------------------------+
```

WMI_LPREAMBLE_STATUS values:

```
+-----------------------------------------------------------------------+
|       WMI_LPREAMBLE_DISABLED = 0                                      |
|       WMI_LPREAMBLE_ENABLED  = 1                                      |
+-----------------------------------------------------------------------+
```

WMI_PREAMBLE_POLICY values:

```
+-----------------------------------------------------------------------+
|       WMI_IGNORE_BARKER_IN_ERP       = 0                              |
|       WMI_DONOT_IGNORE_BARKER_IN_ERP = 1                              |
+-----------------------------------------------------------------------+
```


### WMIcmd(0032h) - WMI_SET_RTS_CMD
Parameters (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   threshold                                     |
+-----------------------------------------------------------------------+
```


### WMIcmd(0036h) - WMI_SET_AUTH_MODE_CMD ;aka WMI_SET_RECONNECT_AUTH_MODE_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   mode                                          |
+-----------------------------------------------------------------------+
```

WMI_AUTH_MODE values:

```
+-----------------------------------------------------------------------+
|       RECONN_DO_AUTH  = 00h                                           |
|       RECONN_NOT_AUTH = 01h                                           |
+-----------------------------------------------------------------------+
```

Set authentication mode

### WMIcmd(0037h) - WMI_SET_REASSOC_MODE_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   mode                                          |
+-----------------------------------------------------------------------+
```

WMI_REASSOC_MODE values:

```
+-----------------------------------------------------------------------+
|       REASSOC_DO_DISASSOC    = 00h                                    |
|       REASSOC_DONOT_DISASSOC = 01h                                    |
+-----------------------------------------------------------------------+
```

Set authentication(?) mode (uh, so SET_REASSOC is same as SET_AUTH?)

### WMIcmd(0038h) - WMI_SET_WMM_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   status                                        |
+-----------------------------------------------------------------------+
```

WMI_WMM_STATUS values:

```
+-----------------------------------------------------------------------+
|       WMI_WMM_DISABLED = 0                                            |
|       WMI_WMM_ENABLED  = 1                                            |
+-----------------------------------------------------------------------+
```

WMM stands for Wi-Fi Multimedia (WMM) aka Wireless Multimedia Extensions (WME) aka some QOS related stuff?
\"WMM prioritizes traffic according to four Access Categories (AC): voice (AC_VO), video (AC_VI), best effort (AC_BE), and background (AC_BK).\"

### WMIcmd(0039h) - WMI_SET_WMM_TXOP_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   txopEnable                                    |
+-----------------------------------------------------------------------+
```

WMI_TXOP_CFG values:

```
+-----------------------------------------------------------------------+
|       WMI_TXOP_DISABLED = 0                                           |
|       WMI_TXOP_ENABLED  = 1                                           |
+-----------------------------------------------------------------------+
```


### WMIcmd(003Dh) - WMI_SET_KEEPALIVE_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT8  1   keepaliveInterval    ;MAYBE in seconds? usually 00h=what? |
+-----------------------------------------------------------------------------------+
```


### WMIcmd(003Eh) - WMI_GET_KEEPALIVE_CMD ;reply 003Eh
Parameters:

```
+-----------------------------------------------------------------------+
|       None                                                            |
+-----------------------------------------------------------------------+
```

Reply: WMI_GET_KEEPALIVE_REPLY

```
+-----------------------------------------------------------------------+
|       00h  A_BOOL   4   configured (what?)                            |
|       04h  A_UINT8  1   keepaliveInterval                             |
+-----------------------------------------------------------------------+
```


### WMIcmd(003Fh) - WMI_SET_APPIE_CMD ;aka WMI_SET_APP_IE_CMD
Can be used to add custom Information Elements (IE) to beacons?
Parameters (old=2+N bytes, or new=4+N bytes):

```
+------------------------------------------------------------------------------------+
|      Older version (used on DSi, and on older 3DS firmwares):                      |
|       00h  A_UINT8  1    mgmtFrmType ;one of WMI_MGMT_FRAME_TYPE                   |
|       01h  A_UINT8  1    ieLen     ;Length of the IE to be added to the MGMT frame |
|       02h  A_UINT8  N*1  ieInfo[1] ;                                               |
|      Newer version (used on newer 3DS firmwares):                                  |
|       00h  A_UINT8  1    mgmtFrmType ;one of WMI_MGMT_FRAME_TYPE                   |
|       01h  A_UINT8  1    reserved (zero, actually USED as MSB of above type value) |
|       02h  A_UINT16 2    ieLen     ;Length of the IE to be added to the MGMT frame |
|       04h  A_UINT8  N*1  ieInfo[1]                                                 |
+------------------------------------------------------------------------------------+
```

WMI_MGMT_FRAME_TYPE values:

```
+-----------------------------------------------------------------------------------+
|       WMI_FRAME_BEACON     = 0   ;\old version (with 8bit ieLen):                 
|       WMI_FRAME_PROBE_REQ  = 1   ;  supports type 0,1,2,3,4 (or 5..FFh=same as 4) |
|       WMI_FRAME_PROBE_RESP = 2   ; new version (with 16bit ieLen):                |
|       WMI_FRAME_ASSOC_REQ  = 3   ;  supports type 1,3 only (ignores all other)    |
|       WMI_FRAME_ASSOC_RESP = 4   ;/                                               |
+-----------------------------------------------------------------------------------+
```

Add Application specified IE to a management frame

```
+----------------------------------------------------------------------------------+
|       WMI_MAX_IE_LEN = 78    ;older versions (with 8bit ieLen) ;<-- actual limit |
|       WMI_MAX_IE_LEN = 255   ;older versions (with 8bit ieLen) ;<-- incorrect    |
|       WMI_MAX_IE_LEN = 1024  ;newer versions (with 16bit ieLen) (from 2014)      |
+----------------------------------------------------------------------------------+
```

Uh, if that newer 3DS firmware is also used in DSi mode (?) then the changed parameter format would be incompatible with DSi software (the APPIE command is rarely (perhaps never) used though).

### WMIcmd(0041h) - WMI_SET_WSC_STATUS_CMD ;aka WSC_REG
Parameters:

```
+----------------------------------------------------------------------------+
|       Unknown (none? or maybe UINT8 or so, maybe with values listed below) |
|       DSi uses 1 byte parameter.                                           |
|      WSC_REG_ACTIVE   = 1                                                  |
|      WSC_REG_INACTIVE = 0                                                  |
+----------------------------------------------------------------------------+
```

Notify the WSC registration status to the target.
WSC means Wifi Simple Config?

### WMIcmd(0049h) - WMI_HOST_EXIT_NOTIFY_CMD ;special DSi/3DS command
Parameters:

```
+-----------------------------------------------------------------------+
|       None                                                            |
+-----------------------------------------------------------------------+
```

This is apparently a special nintendo command, supported on DSi and 3DS (supported on AR6002/AR6013/AR6014, whereof, AR6013/AR6014 have it bundled with a \"wmi_host_exit_notify_cmd\" message, so, this is apparently not the official WMI_SET_QOS_SUPP_CMD from atheros).

### WMIcmd(0049h) - WMI_SET_QOS_SUPP_CMD ;not implemented in DSi/3DS\...?
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   status;                                       |
+-----------------------------------------------------------------------+
```

QOS or QoS stands for \"Quality of service\"?
Note: Some older source code from 2008 did have this command accidently inserted between WMIcmd(0039h and 003Ah), thereby smashing the numbering for WMIcmd(003Ah..004xh), that issue is fixed in newer source code from 2010.

\...Developer commands\...

### WMIcmd(F002h) - WMI_SET_WHALPARAM_CMD ;aka WHAL_PARAMCMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   whalCmdId;    ;see WHAL_CMDID enumeration     |
|       01h  A_UINT8  ..  data[1];      ;aka SETCABTO structure ?       |
+-----------------------------------------------------------------------+
```

Generic Hal Interface for setting hal parameters.
Add new Set HAL Param cmdIds here for newer params.
WHAL_CMDID values (only one defined):

```
+-----------------------------------------------------------------------+
|       WHAL_SETCABTO_CMDID = 1                                         |
+-----------------------------------------------------------------------+
```

WHAL_SETCABTO_PARAM structure:

```
+-----------------------------------------------------------------------+
|       A_UINT8 cabTimeOut;                                             |
+-----------------------------------------------------------------------+
```


### WMIcmd(F004h, or formerly 0048h) - WMI_SET_AKMP_PARAMS_CMD
Parameters (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  akmpInfo;                                      |
+-----------------------------------------------------------------------+
```

WMI_AKMP_MULTI_PMKID_EN = 000001h

### WMIcmd(F005h, or formerly 0049h) - WMI_SET_PMKID_LIST_CMD
Parameters (01h bytes on DSi?, but below would be 4+N\*? bytes?):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4     numPMKID;                                  |
|       04h  WMI_PMKID N*..  pmkidList[WMI_MAX_PMKID_CACHE];            |
+-----------------------------------------------------------------------+
```

#define WMI_MAX_PMKID_CACHE = 8
WMI_PMKID structure:

```
+-----------------------------------------------------------------------+
|       A_UINT8  pmkid[WMI_PMKID_LEN];                                  |
+-----------------------------------------------------------------------+
```


### WMIcmd(F006h, or formerly 004Ah) - WMI_GET_PMKID_LIST_CMD ;reply 1019h
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: WMI_GET_PMKID_LIST_EVENT ;aka WMI_PMKID_LIST_REPLY

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4    numPMKID;                                   |
|       04h  A_UINT8   N*6  bssidList[ATH_MAC_LEN][1];                  |
|       ..   WMI_PMKID N*1  pmkidList[1];                               |
+-----------------------------------------------------------------------+
```

\"Following the Number of PMKIDs is the list of PMKIDs\" uh, what exactly?
WMI_PMKID structure:

```
+-----------------------------------------------------------------------+
|         A_UINT8 pmkid[WMI_PMKID_LEN];                                 |
+-----------------------------------------------------------------------+
```




