# DSi Atheros Wifi - Unimplemented WMI Misc Functions


Not implemented in DSi.

### WMIcmd(002Bh) - WMI_GET_ROAM_DATA_CMD ;reply 1015h ? ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: See WMI_REPORT_ROAM_DATA_EVENT

### WMIevent(1015h) - WMI_REPORT_ROAM_DATA_EVENT

```
+-----------------------------------------------------------------------+
|       ;-not implemented in DSi ;related to 002Bh?                     |
+-----------------------------------------------------------------------+
```

Event Data:

```
+-----------------------------------------------------------------------+
|            PREPACK union {                                            |
|       00h      WMI_TARGET_ROAM_TIME roamTime;                         |
|            } POSTPACK u;                                              |
|       14h  A_UINT8 roamDataType ;                                     |
+-----------------------------------------------------------------------+
```

ROAM_DATA_TYPE values (only one defined)

```
+-----------------------------------------------------------------------+
|       ROAM_DATA_TIME = 1          /* Get The Roam Time Data           |
+-----------------------------------------------------------------------+
```

WMI_TARGET_ROAM_TIME structure:

```
+------------------------------------------------------------------------+
|       00h  A_UINT32  4     disassoc_time                               |
|       04h  A_UINT32  4     no_txrx_time                                |
|       08h  A_UINT32  4     assoc_time                                  |
|       0Ch  A_UINT32  4     allow_txrx_time                             |
|       10h  A_UINT8   6     disassoc_bssid[ATH_MAC_LEN]                 |
|       16h  A_INT8    1     disassoc_bss_rssi                           |
|       17h  A_UINT8   6     assoc_bssid[ATH_MAC_LEN]      ;UNALIGNED!!! |
|       1Dh  A_INT8    1     assoc_bss_rssi                              |
+------------------------------------------------------------------------+
```

Names: WMI_GET_ROAM_DATA aka WMI_REPORT_ROAM_DATA aka WMI_TARGET_ROAM_DATA

### WMIcmd(002Ch) - WMI_ENABLE_RM_CMD ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_BOOL   4    enable_radio_measurements;                   |
+-----------------------------------------------------------------------+
```


### WMIcmd(002Dh) - WMI_SET_MAX_OFFHOME_DURATION_CMD ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1    max_offhome_duration;                        |
+-----------------------------------------------------------------------+
```


### WMIcmd(002Eh:200Ah) - WMIX_PROF_CFG_CMD
### WMIcmd(002Eh:200Bh) - WMIX_PROF_ADDR_SET_CMD
### WMIcmd(002Eh:200Ch) - WMIX_PROF_START_CMD
### WMIcmd(002Eh:200Dh) - WMIX_PROF_STOP_CMD
### WMIcmd(002Eh:200Eh) - WMIX_PROF_COUNT_GET_CMD ;reply 3009h
Not implemented in DSi. Said to be \"Target Profiling support\".
Parameter structures are defined only for WMIX_PROF_CFG_CMD and WMIX_PROF_ADDR_SET_CMD.
Parameters for WMIX_PROF_CFG_CMD:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT32 4   period;     /* Time (in 30.5us ticks) between samples |
|       04h  A_UINT32 4   nbins;                                                |
+-------------------------------------------------------------------------------+
```

Parameters for WMIX_PROF_ADDR_SET_CMD:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4   addr;                                         |
+-----------------------------------------------------------------------+
```

Maybe the other three WMIX_PROF_xxx_CMD\'s don\'t have any parameters.
See also: WMIX_PROF_COUNT_EVENT

### WMIevent(1010h:3009h) - WMIX_PROF_COUNT_EVENT ;-not implemented in DSi
Not implemented in DSi. Response to WMIX_PROF_COUNT_GET_CMD.
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4     addr;                                      |
|       04h  A_UINT32  4     count;                                     |
+-----------------------------------------------------------------------+
```

Target responds to Hosts\'s earlier WMIX_PROF_COUNT_GET_CMD request using a WMIX_PROF_COUNT_EVENT with addr set to the next address count set to the corresponding count.

### WMIcmd(003Ah) - WMI_TEST_CMD ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (maybe related to file "testcmd.h"?)                    |
+-----------------------------------------------------------------------+
```


### WMIevent(1016h) - WMI_TEST_EVENT ;not implemented in DSi
Event Data:

```
+--------------------------------------------------------------------------+
|       Unknown (maybe related to file "testcmd.h"?) (or general purpose?) |
+--------------------------------------------------------------------------+
```


### WMIcmd(0040h) - WMI_GET_APPIE_CMD ;aka GET_APP_IE ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: Unknown:

```
+-------------------------------------------------------------------------------------+
|       EVENTID is unknown (maybe 0040h, ie. same as GET_APPIE_CMD)                   |
|       Reply structure is unknown (maybe same parameter structure for SET_APPIE_CMD) |
+-------------------------------------------------------------------------------------+
```


### WMIcmd(004Ah) - WMI_SET_IE_CMD ;not implemented in DSi (newer 2012 stuff)
Parameters:

```
+-----------------------------------------------------------------------+
|       00h   u8  1   ie_id;                                            |
|       01h   u8  1   ie_field;    /* enum wmi_ie_field_type            |
|       02h   u8  1   ie_len;                                           |
|       03h   u8  1   reserved;                                         |
|       04h   u8  ..  ie_info[0];                                       |
+-----------------------------------------------------------------------+
```

wmi_ie_field_type:

```
+-----------------------------------------------------------------------+
|       WMI_RSN_IE_CAPB = 01h                                           |
|       WMI_IE_FULL     = FFh  /* indicats full IE    ;uh, kittykats?   |
+-----------------------------------------------------------------------+
```

See also: WMI_SET_APP_IE_CMD (similar older command)

### WMIcmd(08xxh) - wil6210: WILOCITY types ;not implemented in DSi
### WMIcmd(09xxh) - wil6210: Performance monitoring ;not implemented in DSi

```
+-----------------------------------------------------------------------+
|       not implemented in DSi                                          |
+-----------------------------------------------------------------------+
```


### WMIcmd(F003h, or formerly 0047h) - WMI_SET_MAC_ADDRESS_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6   macaddr[ATH_MAC_LEN];                         |
+-----------------------------------------------------------------------+
```


### WMIcmd(F007h) - WMI_ABORT_SCAN_CMD ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: Unknown, if any (see (optional?) SCAN_ABORT_EVENT)

### WMIcmd(F008h) - WMI_SET_TARGET_EVENT_REPORT_CMD ;not implemented in DSi
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 1   evtConfig;                                    |
+-----------------------------------------------------------------------+
```

TARGET_EVENT_REPORT_CONFIG values:

```
+-----------------------------------------------------------------------+
|       DISCONN_EVT_IN_RECONN    = 0   ;default                         |
|       NO_DISCONN_EVT_IN_RECONN = 1                                    |
+-----------------------------------------------------------------------+
```

Apparently related to cases where to throw WMI_DISCONNECT_EVENT.

### WMIcmd(F017h or formerly F016h) - WMI_SET_IP_CMD
Parameters:

```
+------------------------------------------------------------------------+
|       00h  A_UINT32 4*2  ips[MAX_IP_ADDRS]   ;IP in Network Byte Order |
+------------------------------------------------------------------------+
```

#define MAX_IP_ADDRS 2

### WMIcmd(F018h or formerly F017h) - WMI_SET_PARAMS_CMD ;reply=101Fh
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4   opcode;                                       |
|       04h  A_UINT32 4   length;                                       |
|       08h  A_CHAR   ... buffer[1];      /* WMI_SET_PARAMS             |
+-----------------------------------------------------------------------+
```

Reply: See WMI_SET_PARAMS_REPLY_EVENT

### WMIevent(101Fh) - WMI_SET_PARAMS_REPLY_EVENT ;reply to \"SET\" CMD F018h
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_INT8  1   status;      /* WMI_SET_PARAMS_REPLY           |
+-----------------------------------------------------------------------+
```

Reply to WMI_SET_PARAMS_CMD (?) aka WMI_SET_PARAMS_REPLY aka WMI_SET_PARAMS_REPLY_EVENT.

### WMIcmd(F019h or formerly F018h) - WMI_SET_MCAST_FILTER_CMD
Parameters:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  6   multicast_mac[ATH_MAC_LEN];   /* WMI_SET_MCAST_FILTER |
+-------------------------------------------------------------------------------+
```


### WMIcmd(F01Ah or formerly F019h) - WMI_DEL_MCAST_FILTER_CMD
Parameters:

```
+-------------------------------------------------------------------------+
|       Unknown (None?) (or maybe same as for WMI_SET_MCAST_FILTER_CMD ?) |
+-------------------------------------------------------------------------+
```


### WMIcmd(F029h) - WMI_MCAST_FILTER_CMD ;related to SET/DEL \"MCAST\" commands?
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  enable;      /* WMI_MCAST_FILTER               |
+-----------------------------------------------------------------------+
```

Related to SET/DEL \"MCAST\" commands?

### WMIcmd(F01Bh) - WMI_ALLOW_AGGR_CMD
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT16 2   tx_allow_aggr (16bit mask to allow tx/uplink ADDBA   |
|                          negotiation - bit position indicates tid)           |
|       02h  A_UINT16 2   rx_allow_aggr (16bit mask to allow rx/donwlink ADDBA |
|                          negotiation - bit position indicates tid)           |
+------------------------------------------------------------------------------+
```

Configures tid\'s to allow ADDBA negotiations on each tid, in each direction.
uh, donwlink?

### WMIcmd(F01Ch) - WMI_ADDBA_REQ_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   tid                                           |
+-----------------------------------------------------------------------+
```

\"f/w starts performing ADDBA negotiations with peer on the given tid\"
\"f/w\" means FirmWare? ForWard? Fail/Wrong? or What?

### WMIcmd(F01Dh) - WMI_DELBA_REQ_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   tid                                           |
|       01h  A_UINT8  1   is_sender_initiator                           |
+-----------------------------------------------------------------------+
```

\"f/w would teardown BA with peer.\" - uh, \"f/w\"?
\"is_send_initiator indicates if it\'s or tx or rx side\" - uh, \"it\'s or\"?

### WMIevent(1020h) - WMI_ADDBA_REQ_EVENT
Event Data:

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT8  1   tid                                                         |
|       01h  A_UINT8  1   win_sz                                                      |
|       02h  A_UINT16 2   st_seq_no                                                   |
|       04h  A_UINT8  1   status  "f/w response for ADDBA Req; OK(0) or failure(!=0)" |
+-------------------------------------------------------------------------------------+
```


### WMIevent(1021h) - WMI_ADDBA_RESP_EVENT
Event Data:

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT8  1   tid                                                     |
|       01h  A_UINT8  1   status      /* OK(0), failure (!=0)                     |
|       02h  A_UINT16 2   amsdu_sz    /* Three values: Not supported(0), 3839, 8k |
+---------------------------------------------------------------------------------+
```

Uhm, does \"8k\" mean 8192 or 8000 or so?

### WMIevent(1022h) - WMI_DELBA_REQ_EVENT aka WMI_DELBA_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   tid;                                          |
|       01h  A_UINT8  1   is_peer_initiator;                            |
|       02h  A_UINT16 2   reason_code;                                  |
+-----------------------------------------------------------------------+
```

\"f/w received a DELBA for peer and processed it. Host is notified of this.\"

### WMIcmd(F01Eh) - WMI_SET_HT_CAP_CMD
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT8 1  band (specifies which band to apply these values)      |
|       01h  A_UINT8 1  enable (allows 11n to be disabled on a per band basis) |
|       02h  A_UINT8 1  chan_width_40M_supported                               |
|       03h  A_UINT8 1  short_GI_20MHz                                         |
|       04h  A_UINT8 1  short_GI_40MHz                                         |
|       05h  A_UINT8 1  intolerance_40MHz                                      |
|       06h  A_UINT8 1  max_ampdu_len_exp                                      |
+------------------------------------------------------------------------------+
```


### WMIcmd(F01Fh) - WMI_SET_HT_OP_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   sta_chan_width;                               |
+-----------------------------------------------------------------------+
```


### WMIcmd(F020h) - WMI_SET_TX_SELECT_RATES_CMD
Parameters:

```
+-------------------------------------------------------------------------+
|       00h  A_UINT32 4*8*2  rateMasks[WMI_MODE_MAX * WMI_MAX_RATE_MASK]; |
+-------------------------------------------------------------------------+
```


### WMIcmd(F021h) - WMI_SET_TX_SGI_PARAM_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4*2  sgiMask[WMI_MAX_RATE_MASK];                  |
|       08h  A_UINT8  1    sgiPERThreshold;                             |
+-----------------------------------------------------------------------+
```

DEFAULT_SGI_MASK_L32 = 08080000h
DEFAULT_SGI_MASK_U32 = 00000000h
DEFAULT_SGI_PER = 10

### WMIcmd(F022h) - WMI_SET_RATE_POLICY_CMD
Parameters:

```
+--------------------------------------------------------------------------------+
|       00h  A_UINT32 4*2  rateField[WMI_MAX_RATE_MASK]                          |
|                           (rateField: "1 bit per rate corresponding to index") |
|       08h  A_UINT8  1    id    ;range 1..5 (aka 1..WMI_RATE_POLICY_ID_MAX)     |
|       09h  A_UINT8  1    shortTrys                                             |
|       0Ah  A_UINT8  1    longTrys                                              |
|       0Bh  A_UINT8  1    reserved   ;padding                                   |
+--------------------------------------------------------------------------------+
```

WMI_RATE_POLICY_ID_MAX = 5

### WMIcmd(F023h) - WMI_HCI_CMD_CMD aka WMI_HCI_CMD
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT16 2   cmd_buf_sz      ;HCI cmd buffer size                 |
|       02h  A_UINT8  ..  buf[1]          ;Absolute HCI cmd (see file "hci.h") |
+------------------------------------------------------------------------------+
```


### WMIevent(1024h) - WMI_HCI_EVENT_EVENT aka WMI_HCI_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   evt_buf_sz      ;HCI event buffer size        |
|       02h  A_UINT8  ..  buf[1]          ;HCI event (see file "hci.h") |
+-----------------------------------------------------------------------+
```


### WMIcmd(F024h) - WMI_RX_FRAME_FORMAT_CMD
Parameters:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  1  metaVersion  ;version of meta data for rx packets      |
|                                     ;(0-7=valid, 0=default)                   |
|       01h  A_UINT8  1  dot11Hdr  ;1=leave .11 header intact,                  |
|                                  ;0=default/replace .11 header with .3        |
|       02h  A_UINT8  1  defragOnHost  ;1=defragmentation is performed by host, |
|                                      ;0=performed by target <default>         |
|       03h  A_UINT8  1  reserved[1]     ;alignment                             |
+-------------------------------------------------------------------------------+
```


### WMIcmd(F025h) - WMI_SET_THIN_MODE_CMD
Parameters:

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT8  1  enable      ;0=default/normal mode, 1=operate in thin mode |
|       01h  A_UINT8  3  reserved[3]                                                |
+-----------------------------------------------------------------------------------+
```


### WMIcmd(F026h) - WMI_SET_BT_WLAN_CONN_PRECEDENCE_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  precedence;                                    |
+-----------------------------------------------------------------------+
```

BT_WLAN_CONN_PRECEDENCE values:

```
+-----------------------------------------------------------------------+
|       BT_WLAN_CONN_PRECDENCE_WLAN = 0  ;default                       |
|       BT_WLAN_CONN_PRECDENCE_PAL  = 1                                 |
+-----------------------------------------------------------------------+
```

Unknown purpose. Maybe related to BT=Bluetooth? CONN=Connect? PAL=What?

### WMIcmd(F03Fh) - WMI_CONFIG_TX_MAC_RULES_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT32 4  rules  ;combination of WMI_WRT_xxx values (see "wmi_thin.h") |
+-------------------------------------------------------------------------------------+
```


### WMIcmd(F040h) - WMI_SET_PROMISCUOUS_MODE_CMD
Parameters:

```
+---------------------------------------------------------------------------+
|       00h  A_UINT8  1  enable (0=default/normal mode, 1=promiscuous mode) |
+---------------------------------------------------------------------------+
```


### WMIcmd(F041h) - WMI_RX_FRAME_FILTER_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2  filtermask(0)      ;WMI_FILTERMASK_MGMT        |
|       02h  A_UINT16 2  filtermask(1)      ;WMI_FILTERMASK_CTRL        |
|       04h  A_UINT16 2  filtermask(2)      ;WMI_FILTERMASK_DATA        |
|       06h  A_UINT16 2  reserved           ;alignment                  |
+-----------------------------------------------------------------------+
```


### WMIcmd(F042h) - WMI_SET_CHANNEL_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT16 2  channel   ;frequency in MHz                                  |
|       --  //A_UINT8 -  mode      ;outcommented (HT20 or HT40 flag?)                 |
|       --  //A_UINT8 -  secondary ;outcommented (HT40 2nd channel above/below flag?) |
+-------------------------------------------------------------------------------------+
```

See also: WMI_SET_CHANNEL_EVENT

### WMIevent(9000h) - WMI_SET_CHANNEL_EVENT
Event Data:

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT8 1  result       ;WMI_SET_CHANNEL_RES (or WMI_THIN_JOIN_RESULT??) |
|       01h  A_UINT8 3  reserved[3]  ;alignment                                       |
+-------------------------------------------------------------------------------------+
```

WMI_SET_CHANNEL_RES values:

```
+-----------------------------------------------------------------------+
|       WMI_SET_CHANNEL_RES_SUCCESS = 0                                 |
|       WMI_SET_CHANNEL_RES_FAIL    = 1                                 |
+-----------------------------------------------------------------------+
```

This is probably the reply to WMI_SET_CHANNEL_CMD (although official comments claim it to be WMI_THIN_JOIN related; probably because of copying/pasting the WMI_THIN_JOIN parameter structure without adjusting the comments).

### WMIcmd(F046h) - WMI_SET_DIV_PARAMS_CMD aka WMI_DIV_PARAMS_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  divIdleTime;                                   |
|       04h  A_UINT8  1  antRssiThresh;                                 |
|       05h  A_UINT8  1  divEnable;                                     |
|       06h  A_UINT16 2  active_treshold_rate;                          |
+-----------------------------------------------------------------------+
```


### WMIcmd(F028h) - WMI_SET_PMK_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  20h  pmk[WMI_PMK_LEN];                            |
+-----------------------------------------------------------------------+
```

WMI_PMK_LEN = 32

### WMIcmd(F047h) - WMI_GET_PMK_CMD ;reply?
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: See WMI_GET_PMK_EVENT aka WMI_GET_PMK_REPLY

### WMIevent(102Ah) - WMI_GET_PMK_EVENT aka WMI_GET_PMK_REPLY
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  20h  pmk[WMI_PMK_LEN];                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(F048h) - WMI_SET_PASSPHRASE_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UCHAR  20h  ssid[WMI_MAX_SSID_LEN];                      |
|       20h  A_UINT8  40h  passphrase[WMI_PASSPHRASE_LEN];              |
|       60h  A_UINT8  1    ssid_len;                                    |
|       61h  A_UINT8  1    passphrase_len;                              |
+-----------------------------------------------------------------------+
```

WMI_PASSPHRASE_LEN = 64

### WMIcmd(F049h) - WMI_SEND_ASSOC_RES_CMD ;aka WMI_SEND_ASSOCRES_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8 1  host_accept;                                    |
|       01h  A_UINT8 1  host_reasonCode;                                |
|       02h  A_UINT8 1  target_status;                                  |
|       03h  A_UINT8 6  sta_mac_addr[ATH_MAC_LEN];                      |
|       09h  A_UINT8 1  rspType;                                        |
+-----------------------------------------------------------------------+
```


### WMIcmd(F04Ah) - WMI_SET_ASSOC_REQ_RELAY_CMD ;aka WMI_SET_ASSOCREQ_RELAY
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8 1  enable;                                         |
+-----------------------------------------------------------------------+
```


### WMIevent(9001h) - WMI_ASSOC_REQ_EVENT aka WMI_ASSOCREQ_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8 1  status;                                         |
|       01h  A_UINT8 1  rspType;                                        |
+-----------------------------------------------------------------------+
```


### WMIcmd(F04Bh or F04Dh) - WMI_ACS_CTRL_CMD ;aka WMI_ACS_CTRL_MSG
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT8 1   ctrl_id;     /* control identifier (aka sub-command?) |
|       01h  A_UINT8 1   length;      /* number of bytes of data to follow     |
|       02h  A_UINT8 ..  data[1];     /* start of control data                 |
+------------------------------------------------------------------------------+
```

WMI_ACS_CTRL_HDR_LEN = (sizeof(WMI_ACS_CTRL_MSG) - sizeof(A_UINT8))

### WMIevent(9002h) - WMI_ACS_EVENT ;generic ACS event
Event Data:

```
+-----------------------------------------------------------------------------+
|       00h  A_UINT8 1   event_id;    /* event identifier                     |
|       01h  A_UINT8 1   length;      /* number of bytes of data that follows |
|       02h  A_UINT8 ..  data[1];     /* start of event data                  |
+-----------------------------------------------------------------------------+
```

WMI_ACS_EVENT_HDR_LEN = (sizeof(WMI_ACS_EVENT_MSG) - sizeof(A_UINT8))

### WMIcmd(F04Ch or F052h) - WMI_SET_EXCESS_TX_RETRY_THRES_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  threshold;                                     |
+-----------------------------------------------------------------------+
```


### WMIcmd(F061h or F051h) - WMI_FORCE_TARGET_ASSERT_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (None?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F04Dh or N/A) - WMI_SET_TBD_TIME_CMD ;added for wmiconfig cmd for TBD
### WMIcmd(F04Eh or N/A) - WMI_PKTLOG_ENABLE_CMD
### WMIcmd(F04Fh or N/A) - WMI_PKTLOG_DISABLE_CMD
### WMIcmd(F062h or N/A) - WMI_SET_PROBED_SSID_EX_CMD
### WMIcmd(F063h or N/A) - WMI_SET_NETWORK_LIST_OFFLOAD_CMD
### WMIcmd(F064h or N/A) - WMI_SET_ARP_NS_OFFLOAD_CMD
### WMIcmd(F065h or N/A) - WMI_ADD_WOW_EXT_PATTERN_CMD
### WMIcmd(F066h or N/A) - WMI_GTK_OFFLOAD_OP_CMD
### WMIcmd(F067h or N/A) - WMI_REMAIN_ON_CHNL_CMD
### WMIcmd(F068h or N/A) - WMI_CANCEL_REMAIN_ON_CHNL_CMD
### WMIcmd(F069h or N/A) - WMI_SEND_ACTION_CMD
### WMIcmd(F06Ah or N/A) - WMI_PROBE_REQ_REPORT_CMD
### WMIcmd(F06Bh or N/A) - WMI_DISABLE_11B_RATES_CMD
### WMIcmd(F06Ch or N/A) - WMI_SEND_PROBE_RESPONSE_CMD
Unknown/undocumented (invented 2012 or so).

### WMIevent(?) - WMI_GET_APPIE_CMD ;aka GET_APP_IE ;-not implemented in DSi
The \"GET_APP\" command name suggests that there should be some reply, but:

```
+-------------------------------------------------------------------------------------+
|       EVENTID is unknown (maybe 0040h, ie. same as GET_APPIE_CMD)                   |
|       Reply structure is unknown (maybe same parameter structure for SET_APPIE_CMD) |
+-------------------------------------------------------------------------------------+
```


### WMIevent(?) - WMI_CRE_PRIORITY_STREAM_REPLY ;-not implemented in DSi
Unknown crap. The DSi doesn\'t send a reply to WMI_CREATE_PSTREAM_CMD, nonetheless, existing source code does have a WMI_CRE_PRIORITY_STREAM_REPLY structure for whatever reason, maybe it\'s send only in certain firmware version(s), with whatever/unknown WMIevent(xxxx) number. The reply structure is:

```
+------------------------------------------------------------------------+
|       00h  A_UINT8  1  status;                 /* PSTREAM_REPLY_STATUS |
|       01h  A_UINT8  1  txQueueNumber;                                  |
|       02h  A_UINT8  1  rxQueueNumber;                                  |
|       03h  A_UINT8  1  trafficClass;                                   |
|       04h  A_UINT8  1  trafficDirection;       /* DIR_TYPE             |
+------------------------------------------------------------------------+
```

PSTREAM_REPLY_STATUS values:

```
+-----------------------------------------------------------------------+
|       A_SUCCEEDED = A_OK                   = 0                        |
|       A_FAILED_DELETE_STREAM_DOESNOT_EXIST = 250                      |
|       A_SUCCEEDED_MODIFY_STREAM            = 251                      |
|       A_FAILED_INVALID_STREAM              = 252                      |
|       A_FAILED_MAX_THINSTREAMS             = 253                      |
|       A_FAILED_CREATE_REMOVE_PSTREAM_FIRST = 254                      |
+-----------------------------------------------------------------------+
```


### WMIevent(?) - WMI_DEL_PRIORITY_STREAM_REPLY ;-not implemented in DSi
Unknown crap. See above for details. The WMI_DEL_PRIORITY_STREAM_REPLY structure is:

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT8  1   status;            ;\                                      
|       01h  A_UINT8  1   txQueueNumber;     ; same as WMI_CRE_PRIORITY_STREAM_REPLY |
|       02h  A_UINT8  1   rxQueueNumber;     ;/                                      |
|       03h  A_UINT8  1   trafficDirection;  ;\unlike WMI_CRE_PRIORITY_STREAM_REPLY  
|       04h  A_UINT8  1   trafficClass;      ;/(entries are swapped)                 |
+------------------------------------------------------------------------------------+
```


### WMIevent(?) - WMI_FRAME_RATES_REPLY ;-not implemented in DSi
Unknown crap. WMI_FRAME_RATES_REPLY is said to have same structure as WMI_SET_FRAMERATES_CMD parameter structure. But WMIevent(?) number is unknown, and DSi doesn\'t seem to send any such REPLY.

### WMIevent(101Bh) - WMI_PEER_NODE_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  eventCode;                                     |
|       01h  A_UINT8  6  peerMacAddr[ATH_MAC_LEN];                      |
+-----------------------------------------------------------------------+
```

Below PEER values are probably meant to be the \"eventCode\" values(?):

```
+-----------------------------------------------------------------------+
|       PEER_NODE_JOIN_EVENT       = 00h                                |
|       PEER_NODE_LEAVE_EVENT      = 01h                                |
|       PEER_FIRST_NODE_JOIN_EVENT = 10h                                |
|       PEER_LAST_NODE_LEAVE_EVENT = 11h                                |
+-----------------------------------------------------------------------+
```


### WMIevent(101Dh) - WMI_DTIMEXPIRY_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (if any)                                                |
+-----------------------------------------------------------------------+
```


### WMIevent(101Eh) - WMI_WLAN_VERSION_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  version;                                       |
+-----------------------------------------------------------------------+
```

Whatever event with whatever version?

### WMIevent(1023h) - WMI_TX_COMPLETE_EVENT
Event Data:

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT8  1  numMessages ;number of tx comp msgs following               |
|       01h  A_UINT8  1  msgLen   ;length in bytes for each individual msg following |
|       02h  A_UINT8  1  msgType  ;version of tx complete msg data following         |
|       03h  A_UINT8  1  reserved                                                    |
|      When msgType=01h=WMI_TXCOMPLETE_VERSION_1                                     |
|       04h  ...      .. individual message(s) (see TX_COMPLETE_MSG_V1 structure)    |
|      When msgType=Other                                                            |
|       04h  ...      .. reserved for other MSG types (none such defined yet)        |
+------------------------------------------------------------------------------------+
```

TX_COMPLETE_MSG_V1 structure:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8 1   status      /* one of TX_COMPLETE_STATUS_xxx values    |
|       01h  A_UINT8 1   pktID       /* packet ID to identify parent packet     |
|       02h  A_UINT8 1   rateIdx     /* rate index on successful transmission   |
|       03h  A_UINT8 1   ackFailures /* number of ACK failures in tx attempt    |
|            #if 0  ;optional "host delivery time" params currently ommitted... |
|       --     A_UINT32  queueDelay  /* usec delay measured Tx Start time       |
|       --     A_UINT32  mediaDelay  /* usec delay measured ACK rx time         |
|            #endif                                                             |
+-------------------------------------------------------------------------------+
```

TX_COMPLETE_STATUS_xxx values:

```
+-----------------------------------------------------------------------+
|       TX_COMPLETE_STATUS_SUCCESS = 0                                  |
|       TX_COMPLETE_STATUS_RETRIES = 1                                  |
|       TX_COMPLETE_STATUS_NOLINK  = 2                                  |
|       TX_COMPLETE_STATUS_TIMEOUT = 3                                  |
|       TX_COMPLETE_STATUS_OTHER   = 4                                  |
+-----------------------------------------------------------------------+
```

Transmit complete event.

### WMIevent(1025h) - WMI_ACL_DATA_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (what?)                                                 |
+-----------------------------------------------------------------------+
```

ACL is what? Is that somehow related to \"ACLCOEX\"?

### WMIevent(1026h, or formerly N/A, or N/A) - WMI_REPORT_SLEEP_STATE_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  sleepState;                                    |
+-----------------------------------------------------------------------+
```

Values for \"sleepState\":

```
+-----------------------------------------------------------------------+
|       WMI_REPORT_SLEEP_STATUS_IS_DEEP_SLEEP = 0                       |
|       WMI_REPORT_SLEEP_STATUS_IS_AWAKE      = 1                       |
+-----------------------------------------------------------------------+
```

Names: WMI_REPORT_SLEEP_STATE_EVENT aka WMI_REPORT_SLEEP_STATUS

### WMIevent(1027h, or formerly 1026h, or N/A) - WMI_WAPI_REKEY_EVENT
This event is added/removed randomly in different source code versions.
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   type;                                         |
|       01h  A_UINT8  6   macAddr[ATH_MAC_LEN];                         |
+-----------------------------------------------------------------------+
```

Values (probably for above \"type\" field?):

```
+-----------------------------------------------------------------------+
|       WAPI_REKEY_UCAST = 1                                            |
|       WAPI_REKEY_MCAST = 2                                            |
+-----------------------------------------------------------------------+
```

The numbering for WMIevent(1026h..1029h) does vary in older source versions because WMI_REPORT_SLEEP_STATE_EVENT originally didn\'t exist, and WMI_WAPI_REKEY_EVENT originally did exist only if \"WAPI_ENABLE\". Later source code did always include WMI_WAPI_REKEY_EVENT, and even later code did re-remove it completely.
Names: WMI_WAPI_REKEY_EVENT aka WMI_WAPIREKEY_EVENT

### WMIevent(1035h) - WMI_CCX_RM_STATUS_EVENT ;CCX Evants, uh, EvAntS?
Event Data:

```
+------------------------------------------------------------------------------------+
|       00h  A_INT32 4  rm_type   ;\one of these MIGHT be "WMI_CCX_RM_STATUS_TYPE" ? 
|       04h  A_INT32 4  status    ;/                                                 |
+------------------------------------------------------------------------------------+
```

WMI_CCX_RM_STATUS_TYPE values (probably for the \"rm_type\" field?):

```
+-----------------------------------------------------------------------+
|       WMI_CCX_RM_STATUS_UNKNOWN     = 0                               |
|       WMI_CCX_RM_REPORT_SENT        = 1                               |
|       WMI_CCX_RM_REFUSE_REPORT_SENT = 2                               |
+-----------------------------------------------------------------------+
```

Uh, \"CCX\" means\... What?
Uh, \"RM\" means\... maybe \"radio_measurements\" or What?
Maybe this is somehow related to \"WMI_ENABLE_RM_CMD\"?

### WMIevent(1045h) - WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (if any?)                                               |
+-----------------------------------------------------------------------+
```

This event exists ONLY in source code from 2010, not in older code, and it\'s removed in newer code from 2012.
Special event used to notify host that AR6003 has processed sleep command (aka WMI_SET_HOST_SLEEP_MODE_CMD?) (needed to prevent a late incoming credit report from crashing the system).

### WMIevent(9003h) - WMI_REPORT_WMM_PARAMS_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  wmm_params  6*4  wmm_params[4];                            |
+-----------------------------------------------------------------------+
```

\"wmm_params\" structure:

```
+-------------------------------------------------------------------------+
|       00h  A_UINT8     1    acm;           /* ACM parameter             |
|       01h  A_UINT8     1    aifsn;         /* AIFSN parameters          |
|       02h  A_UINT8     1    logcwmin;      /* cwmin in exponential form |
|       03h  A_UINT8     1    logcwmax;      /* cwmax in exponential form |
|       04h  A_UINT16    2    txopLimit;     /* txopLimit                 |
+-------------------------------------------------------------------------+
```


### WMIcmd(?) - WMI_SET_ADHOC_BSSID_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6   bssid[ATH_MAC_LEN];                           |
+-----------------------------------------------------------------------+
```

The above parameter structure is defined in \"wmi.h\", but there\'s no WMIcmd(xxxxh) command ID for it. Maybe the command did exist only in older versions (from dates before 2006)?



