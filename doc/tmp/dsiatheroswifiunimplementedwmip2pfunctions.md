# DSi Atheros Wifi - Unimplemented WMI P2P Functions


P2P module definitions

P2P_SSID structure:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1    ssidLength;                                  |
|       01h  A_UINT8  20h  ssid[WMI_MAX_SSID_LEN];                      |
+-----------------------------------------------------------------------+
```


### WMIcmd(F038h) - WMI_P2P_SET_CONFIG_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  go_intent;                                     |
|       01h  A_UINT8  3  country[3];                                    |
|       04h  A_UINT8  1  reg_class;                                     |
|       05h  A_UINT8  1  listen_channel;                                |
|       06h  A_UINT8  1  op_reg_class;                                  |
|       07h  A_UINT8  1  op_channel;                                    |
|       09h  A_UINT16 2  config_methods;                                |
+-----------------------------------------------------------------------+
```


### WMIcmd(F039h) - WMI_WPS_SET_CONFIG_CMD ;P2P related
Parameters:

```
+----------------------------------------------------------------------------+
|       00h  device_type_tuple 4     pri_dev_type;                           |
|       --   outcommented?     0     //A_UINT8 pri_device_type[8];           |
|       04h  device_type_tuple 4*5   sec_dev_type[MAX_P2P_SEC_DEVICE_TYPES]; |
|       18h  A_UINT8           10h   uuid[WPS_UUID_LEN];                     |
|       28h  A_UINT8           20h   device_name[WPS_MAX_DEVNAME_LEN];       |
|       48h  A_UINT8           1     dev_name_len;                           |
+----------------------------------------------------------------------------+
```

\"device_type_tuple\" structure (4 bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2  categ;                                         |
|       02h  A_UINT16 2  sub_categ;                                     |
+-----------------------------------------------------------------------+
```

MAX_P2P_SEC_DEVICE_TYPES = 5
WPS_UUID_LEN = 16
WPS_MAX_DEVNAME_LEN = 32

### WMIcmd(F03Ah) - WMI_SET_REQ_DEV_ATTR_CMD ;P2P related
Parameters:

```
+----------------------------------------------------------------------------+
|       00h  device_type_tuple 4     pri_dev_type;                           |
|       04h  device_type_tuple 4*5   sec_dev_type[MAX_P2P_SEC_DEVICE_TYPES]; |
|       18h  A_UINT8           6     device_addr[ATH_MAC_LEN];               |
+----------------------------------------------------------------------------+
```


### WMIcmd(F03Bh) - WMI_P2P_FIND_CMD
Parameters:
typedef PREPACK struct {

```
+--------------------------------------------------------------------------+
|       00h  A_UINT32 4     timeout;                                       |
|       04h  A_ENUM   ..    type;  ;A_UINTx or so?  ;aka WMI_P2P_DISC_TYPE |
+--------------------------------------------------------------------------+
```

WMI_P2P_DISC_TYPE values:

```
+-----------------------------------------------------------------------+
|       WMI_P2P_FIND_START_WITH_FULL = Unknown (0 or 1 or so)           |
|       WMI_P2P_FIND_ONLY_SOCIAL     = WMI_P2P_FIND_START_WITH_FULL+1   |
|       WMI_P2P_FIND_PROGRESSIVE     = WMI_P2P_FIND_START_WITH_FULL+2   |
+-----------------------------------------------------------------------+
```


### WMIcmd(F03Ch) - WMI_P2P_STOP_FIND_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F03Dh) - WMI_P2P_GO_NEG_START_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   listen_freq;                                  |
|       02h  A_UINT16 2   force_freq;                                   |
|       04h  A_UINT16 2   go_oper_freq;                                 |
|       06h  A_UINT8  1   dialog_token;                                 |
|       07h  A_UINT8  6   peer_addr[ATH_MAC_LEN];                       |
|       0Dh  A_UINT8  6   own_interface_addr[ATH_MAC_LEN];              |
|       13h  A_UINT8  6   member_in_go_dev[ATH_MAC_LEN];                |
|       19h  A_UINT8  1   go_dev_dialog_token;                          |
|       1Ah  P2P_SSID 21h peer_go_ssid;                                 |
|       3Bh  A_UINT8  1   wps_method;                                   |
|       3Ch  A_UINT8  1   dev_capab;                                    |
|       3Dh  A_INT8   1   go_intent;                                    |
|       3Eh  A_UINT8  1   persistent_grp;                               |
+-----------------------------------------------------------------------+
```


### WMIcmd(F03Eh) - WMI_P2P_LISTEN_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4   timeout;                                      |
+-----------------------------------------------------------------------+
```


### WMIcmd(F050h or F053h) - WMI_P2P_GO_NEG_REQ_RSP_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       000h  A_UINT16 2    listen_freq;                                |
|       002h  A_UINT16 2    force_freq;                                 |
|       004h  A_UINT8  1    status;                                     |
|       005h  A_INT8   1    go_intent;                                  |
|       006h  A_UINT8  200h wps_buf[512];                               |
|       206h  A_UINT16 2    wps_buflen;                                 |
|       208h  A_UINT8  200h p2p_buf[512];                               |
|       408h  A_UINT16 2    p2p_buflen;                                 |
|       40Ah  A_UINT8  1    dialog_token;                               |
|       40Bh  A_UINT8  1    wps_method;                                 |
|       40Ch  A_UINT8  1    persistent_grp;                             |
|       40Dh  A_UINT8  6    sa[ATH_MAC_LEN];                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(F051h or F054h) - WMI_P2P_GRP_INIT_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  persistent_group;                              |
|       01h  A_UINT8  1  group_formation;                               |
+-----------------------------------------------------------------------+
```


### WMIcmd(F052h or F055h) - WMI_P2P_GRP_FORMATION_DONE_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6  peer_addr[ATH_MAC_LEN];                        |
|       06h  A_UINT8  1  grp_formation_status;                          |
+-----------------------------------------------------------------------+
```


### WMIcmd(F053h or F056h) - WMI_P2P_INVITE_CMD
Parameters:

```
+------------------------------------------------------------------------+
|       00h  A_ENUM   ..   role;   ;A_UINTx or so?  ;WMI_P2P_INVITE_ROLE |
|       ..   A_UINT16 2    listen_freq;                                  |
|       ..   A_UINT16 2    force_freq;                                   |
|       ..   A_UINT8  1    dialog_token;                                 |
|       ..   A_UINT8  6    peer_addr[ATH_MAC_LEN];                       |
|       ..   A_UINT8  6    bssid[ATH_MAC_LEN];                           |
|       ..   A_UINT8  6    go_dev_addr[ATH_MAC_LEN];                     |
|       ..   P2P_SSID 21h  ssid;                                         |
|       ..   A_UINT8  1    is_persistent;                                |
|       ..   A_UINT8  1    wps_method;                                   |
+------------------------------------------------------------------------+
```

WMI_P2P_INVITE_ROLE values:

```
+-----------------------------------------------------------------------+
|       WMI_P2P_INVITE_ROLE_GO        = Unknown (0 or 1 or so)          |
|       WMI_P2P_INVITE_ROLE_ACTIVE_GO = WMI_P2P_INVITE_ROLE_GO+1        |
|       WMI_P2P_INVITE_ROLE_CLIENT    = WMI_P2P_INVITE_ROLE_GO+2        |
+-----------------------------------------------------------------------+
```


### WMIcmd(F054h or F057h) - WMI_P2P_INVITE_REQ_RSP_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       000h  A_UINT16 2    force_freq;                                 |
|       002h  A_UINT8  1    status;                                     |
|       003h  A_UINT8  1    dialog_token;                               |
|       004h  A_UINT8  200h p2p_buf[512];                               |
|       204h  A_UINT16 2    p2p_buflen;                                 |
|       206h  A_UINT8  1    is_go;                                      |
|       207h  A_UINT8  6    group_bssid[ATH_MAC_LEN];                   |
+-----------------------------------------------------------------------+
```


### WMIcmd(F055h or F058h) - WMI_P2P_PROV_DISC_REQ_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2    wps_method;                                  |
|       02h  A_UINT16 2    listen_freq;                                 |
|       04h  A_UINT8  1    dialog_token;                                |
|       05h  A_UINT8  6    peer[ATH_MAC_LEN];                           |
|       0Bh  A_UINT8  6    go_dev_addr[ATH_MAC_LEN];                    |
|       11h  P2P_SSID 21h  go_oper_ssid;                                |
+-----------------------------------------------------------------------+
```


### WMIcmd(F056h or F059h) - WMI_P2P_SET_CMD
Parameters:

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT8  1    config_id;           ;set to one of WMI_P2P_CONF_ID      |
|      When config_id=1=WMI_P2P_CONFID_LISTEN_CHANNEL  ;WMI_P2P_LISTEN_CHANNEL      |
|       01h  A_UINT8  1    reg_class;                                               |
|       02h  A_UINT8  1    listen_channel;                                          |
|      When config_id=2=WMI_P2P_CONFID_CROSS_CONNECT   ;WMI_P2P_SET_CROSS_CONNECT   |
|       01h  A_UINT8  1    flag;                                                    |
|      When config_id=3=WMI_P2P_CONFID_SSID_POSTFIX    ;WMI_P2P_SET_SSID_POSTFIX    |
|       01h  A_UINT8  17h  ssid_postfix[WMI_MAX_SSID_LEN-9];                        |
|       18h  A_UINT8  1    ssid_postfix_len;                                        |
|      When config_id=4=WMI_P2P_CONFID_INTRA_BSS       ;WMI_P2P_SET_INTRA_BSS       |
|       01h  A_UINT8  1    flag;                                                    |
|      When config_id=5=WMI_P2P_CONFID_CONCURRENT_MODE ;WMI_P2P_SET_CONCURRENT_MODE |
|       01h  A_UINT8  1    flag;                                                    |
|      When config_id=6=WMI_P2P_CONFID_GO_INTENT       ;WMI_P2P_SET_GO_INTENT       |
|       01h  A_UINT8  1    value;                                                   |
|      When config_id=7=WMI_P2P_CONFID_DEV_NAME        ;WMI_P2P_SET_DEV_NAME        |
|       01h  A_UINT8  20h  dev_name[WPS_MAX_DEVNAME_LEN];                           |
|       21h  A_UINT8  1    dev_name_len;                                            |
+-----------------------------------------------------------------------------------+
```


### WMIcmd(F05Bh or F05Ch) - WMI_P2P_SDPD_TX_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       000h  A_UINT8  1    type;                                       |
|       001h  A_UINT8  1    dialog_token;                               |
|       002h  A_UINT8  1    frag_id;                                    |
|       003h  A_UINT8  1    reserved1;          /* alignment            |
|       004h  A_UINT8  6    peer_addr[ATH_MAC_LEN];                     |
|       00Ah  A_UINT16 2    freq;                                       |
|       00Ch  A_UINT16 2    status_code;                                |
|       00Eh  A_UINT16 2    comeback_delay;                             |
|       010h  A_UINT16 2    tlv_length;                                 |
|       012h  A_UINT16 2    update_indic;                               |
|       014h  A_UINT16 2    total_length;                               |
|       016h  A_UINT16 2    reserved2;         /* future                |
|       018h  A_UINT8  400h tlv[WMI_P2P_MAX_TLV_LEN];                   |
+-----------------------------------------------------------------------+
```

WMI_P2P_SDPD_TYPE values:

```
+-----------------------------------------------------------------------+
|       WMI_P2P_SD_TYPE_GAS_INITIAL_REQ   = 01h                         |
|       WMI_P2P_SD_TYPE_GAS_INITIAL_RESP  = 02h                         |
|       WMI_P2P_SD_TYPE_GAS_COMEBACK_REQ  = 03h                         |
|       WMI_P2P_SD_TYPE_GAS_COMEBACK_RESP = 04h                         |
|       WMI_P2P_PD_TYPE_RESP              = 05h                         |
|       WMI_P2P_SD_TYPE_STATUS_IND        = 06h                         |
+-----------------------------------------------------------------------+
```

WMI_P2P_SDPD_TRANSACTION_STATUS values:

```
+-----------------------------------------------------------------------+
|       WMI_P2P_SDPD_TRANSACTION_PENDING  = 01h                         |
|       WMI_P2P_SDPD_TRANSACTION_COMP     = 02h                         |
+-----------------------------------------------------------------------+
```

WMI_P2P_MAX_TLV_LEN = 1024

### WMIcmd(F05Ch or F05Dh) - WMI_P2P_STOP_SDPD_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F05Dh or F05Eh) - WMI_P2P_CANCEL_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F06Dh or N/A) - WMI_GET_P2P_INFO_CMD
Unknown/undocumented (invented around 2012).

\...P2P Events\...

### WMIevent(1036h) - WMI_P2P_GO_NEG_RESULT_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   freq;                                         |
|       02h  A_INT8   1   status;                                       |
|       03h  A_UINT8  1   role_go;                                      |
|       04h  A_UINT8  20h ssid[WMI_MAX_SSID_LEN];                       |
|       24h  A_UINT8  1   ssid_len;                                     |
|       25h  A_CHAR   9   pass_phrase[WMI_MAX_PASSPHRASE_LEN];          |
|       2Eh  A_UINT8  6   peer_device_addr[ATH_MAC_LEN];                |
|       34h  A_UINT8  6   peer_interface_addr[ATH_MAC_LEN];             |
|       3Ah  A_UINT8  1   wps_method;                                   |
|       3Bh  A_UINT8  1   persistent_grp;                               |
+-----------------------------------------------------------------------+
```

WMI_MAX_PASSPHRASE_LEN = 9

### WMIevent(103Dh) - WMI_P2P_GO_NEG_REQ_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       000h  A_UINT8  6    sa[ATH_MAC_LEN];                            |
|       006h  A_UINT8  200h wps_buf[512];                               |
|       206h  A_UINT16 2    wps_buflen;                                 |
|       208h  A_UINT8  200h p2p_buf[512];                               |
|       408h  A_UINT16 2    p2p_buflen;                                 |
|       40Ah  A_UINT8  1    dialog_token;                               |
+-----------------------------------------------------------------------+
```


### WMIevent(103Eh) - WMI_P2P_INVITE_REQ_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       000h  A_UINT8  200h p2p_buf[512];                               |
|       200h  A_UINT16 2    p2p_buflen;                                 |
|       202h  A_UINT8  6    sa[ATH_MAC_LEN];                            |
|       208h  A_UINT8  6    bssid[ATH_MAC_LEN];                         |
|       20Eh  A_UINT8  6    go_dev_addr[ATH_MAC_LEN];                   |
|       214h  P2P_SSID 21h  ssid;                                       |
|       235h  A_UINT8  1    is_persistent;                              |
|       236h  A_UINT8  1    dialog_token;                               |
+-----------------------------------------------------------------------+
```


### WMIevent(103Fh) - WMI_P2P_INVITE_RCVD_RESULT_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   oper_freq;                                    |
|       02h  A_UINT8  6   sa[ATH_MAC_LEN];                              |
|       08h  A_UINT8  6   bssid[ATH_MAC_LEN];                           |
|       0Eh  A_UINT8  1   is_bssid_valid;                               |
|       0Fh  A_UINT8  6   go_dev_addr[ATH_MAC_LEN];                     |
|       15h  P2P_SSID 21h ssid;                                         |
|       36h  A_UINT8  1   status;                                       |
+-----------------------------------------------------------------------+
```


### WMIevent(1040h) - WMI_P2P_INVITE_SENT_RESULT_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   status;                                       |
|       01h  A_UINT8  6   bssid[ATH_MAC_LEN];                           |
|       07h  A_UINT8  1   is_bssid_valid;                               |
+-----------------------------------------------------------------------+
```


### WMIevent(1041h) - WMI_P2P_PROV_DISC_RESP_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6   peer[ATH_MAC_LEN];                            |
|       06h  A_UINT16 2   config_methods;                               |
+-----------------------------------------------------------------------+
```


### WMIevent(1042h) - WMI_P2P_PROV_DISC_REQ_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6   sa[ATH_MAC_LEN];                              |
|       06h  A_UINT16 2   wps_config_method;                            |
|       08h  A_UINT8  6   dev_addr[ATH_MAC_LEN];                        |
|       0Eh  A_UINT8  8   pri_dev_type[WPS_DEV_TYPE_LEN];               |
|       16h  A_UINT8  20h device_name[WPS_MAX_DEVNAME_LEN];             |
|       36h  A_UINT8  1   dev_name_len;                                 |
|       37h  A_UINT16 2   dev_config_methods;                           |
|       39h  A_UINT8  1   device_capab;                                 |
|       3Ah  A_UINT8  1   group_capab;                                  |
+-----------------------------------------------------------------------+
```

WPS_DEV_TYPE_LEN = 8

### WMIevent(1043h) - WMI_P2P_START_SDPD_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIevent(1044h) - WMI_P2P_SDPD_RX_EVENT
Event Data:

```
+----------------------------------------------------------------------------+
|       00h  A_UINT8  1   type;                                              |
|       01h  A_UINT8  1   transaction_status;                                |
|       02h  A_UINT8  1   dialog_token;                                      |
|       03h  A_UINT8  1   frag_id;                                           |
|       04h  A_UINT8  6   peer_addr[ATH_MAC_LEN];                            |
|       0Ah  A_UINT16 2   freq;                                              |
|       0Ch  A_UINT16 2   status_code;                                       |
|       0Eh  A_UINT16 2   comeback_delay;                                    |
|       10h  A_UINT16 2   tlv_length;                                        |
|       12h  A_UINT16 2   update_indic;                                      |
|       14h  VAR      ..  Variable length TLV will be placed after the event |
+----------------------------------------------------------------------------+
```




