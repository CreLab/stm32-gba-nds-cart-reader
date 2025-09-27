# DSi Atheros Wifi - Unimplemented WMI THIN Functions


### WMIcmd(8000h) - WMI_THIN_RESERVED_START
### WMIcmd(8FFFh) - WMI_THIN_RESERVED_END
Area for Thin commands. These command IDs can be found in \"wmi_thin.h\".

### WMIcmd(8000h) - WMI_THIN_CONFIG_CMD
Parameters:

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT32 4   cfgField      ;combination of WMI_THIN_CFG_...            |
|       04h  A_UINT16 2   length        ;length in bytes of appended sub-command(s) |
|       06h  A_UINT8  2   reserved[2]   ;align padding                              |
|       08h  ...      ..  structure(s) selected in "cfgField"...                    |
+-----------------------------------------------------------------------------------+
```

When cfgField.Bit0 set: append WMI_THIN_CONFIG_TXCOMPLETE struct:
Used to configure the params and content for TX Complete messages the will come from the Target. these messages are disabled by default but can be enabled using this structure and the WMI_THIN_CONFIG_CMDID.

```
+------------------------------------------------------------------------------------+
|       +00h  A_UINT8  1  version (the versioned type of messages to use, 0=disable) |
|       +01h  A_UINT8  1  countThreshold (msg count threshold triggering a tx        |
|                          complete message)                                         |
|       +02h  A_UINT16 2  timeThreshold (timeout interval in MSEC triggering a       |
|                          tx complete message)                                      |
+------------------------------------------------------------------------------------+
```

When cfgField.Bit1 set: append WMI_THIN_CONFIG_DECRYPT_ERR struct:
Used to configure behavior for received frames that have decryption errors. The default behavior is to discard the frame without notification. Alternately, the MAC Header is forwarded to the host with the failed status.

```
+-----------------------------------------------------------------------------+
|       +00h  A_UINT8  1  enable (1=send decrypt errors to the host, 0=don't) |
|       +01h  A_UINT8  3  reserved[3] (align padding)                         |
+-----------------------------------------------------------------------------+
```

When cfgField.Bit2 set: Unused \-\-- NEW VERSION

```
+-----------------------------------------------------------------------+
|       Unused.                                                         |
+-----------------------------------------------------------------------+
```

When cfgField.Bit2 set: append WMI_THIN_CONFIG_TX_MAC_RULES \-\-- OLD VERSION
Used to configure behavior for transmitted frames that require partial MAC header construction. These rules are used by the target to indicate which fields need to be written.

```
+-----------------------------------------------------------------------+
|       +00h  A_UINT32 4  rules (combination of WMI_WRT_... values)     |
+-----------------------------------------------------------------------+
```

When cfgField.Bit3 set: append WMI_THIN_CONFIG_RX_FILTER_RULES struct:
Used to configure behavior for received frames as to which frames should get forwarded to the host and which should get processed internally.

```
+-----------------------------------------------------------------------+
|       +00h  A_UINT32 4  rules (combination of WMI_FILT_... values)    |
+-----------------------------------------------------------------------+
```

When cfgField.Bit4 set: append WMI_THIN_CONFIG_CIPHER_ENCAP struct:
Used to configure behavior for both TX and RX frames regarding security cipher encapsulation. The host may specify whether or not the firmware is responsible for cipher encapsulation. If the firmware is responsible it will add the security header and trailer for TX frames and remove the header and trailer for Rx frames. Also, the firmware will examine the resource counter if any and behave appropriately when a bad value is detected. If the host indicates responsibility for encapsulation then it is responsible for all aspects of encapsulation, however the device will still perform the encryption and decryption of the frame payload if a key has been provided.

```
+---------------------------------------------------------------------------------+
|       +00h  A_UINT8  1  enable (enables/disables firmware cipher encapsulation) |
|       +01h  A_UINT8  3  reserved[3] (align padding)                             |
+---------------------------------------------------------------------------------+
```

Summary of values for \"cfgField\":

```
+-----------------------------------------------------------------------------------+
|       WMI_THIN_CFG_TXCOMP       = 00000001h                                       |
|       WMI_THIN_CFG_DECRYPT      = 00000002h                                       |
|       WMI_THIN_CFG_MAC_RULES    = 00000004h ;old version (or planned for future?) |
|       WMI_THIN_UNUSED1          = 00000004h ;current version                      |
|       WMI_THIN_CFG_FILTER_RULES = 00000008h                                       |
|       WMI_THIN_CFG_CIPHER_ENCAP = 00000010h                                       |
+-----------------------------------------------------------------------------------+
```


### WMIcmd(8001h) - WMI_THIN_SET_MIB_CMD
Parameters:

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT16 2  length;     /* the length in bytes of the appended MIB data |
|       02h  A_UINT8  1  mibID;      /* the ID of the MIB element being set          |
|       03h  A_UINT8  1  reserved;   /* align padding                                |
+------------------------------------------------------------------------------------+
```


### WMIcmd(8002h) - WMI_THIN_GET_MIB_CMD ;reply?
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT8  1   mibID;        /* the ID of the MIB element being set |
|       01h  A_UINT8  3   reserved[3];  /* align padding                       |
+------------------------------------------------------------------------------+
```

Reply: See WMI_THIN_GET_MIB_EVENT

### WMIcmd(8003h) - WMI_THIN_JOIN_CMD ;newer ver only
Parameters:

```
+------------------------------------------------------------------------------+
|       00h  A_UINT32 4   basicRateMask;    /* bit mask of basic rates         |
|       04h  A_UINT32 4   beaconIntval;     /* TUs                             |
|       08h  A_UINT16 2   atimWindow;       /* TUs                             |
|       0Ah  A_UINT16 2   channel;          /* frequency in MHz                |
|       0Ch  A_UINT8  1   networkType;      /* INFRA_NETWORK | ADHOC_NETWORK   |
|       0Dh  A_UINT8  1   ssidLength;       /* 0 - 32                          |
|       0Eh  A_UINT8  1   probe;            /* != 0 : issue probe req at start |
|       0Fh  A_UINT8  1   reserved;         /* alignment                       |
|       10h  A_UCHAR  20h ssid[WMI_MAX_SSID_LEN];                              |
|       30h  A_UINT8  6   bssid[ATH_MAC_LEN];                                  |
+------------------------------------------------------------------------------+
```

Reply: See WMI_THIN_JOIN_EVENT

### WMIcmd(8004h) - WMI_THIN_CONNECT_CMD ;newer ver only
Parameters:

```
+------------------------------------------------------------------------+
|       00h  A_UINT16 2  dtim;   /* dtim interval in num beacons         |
|       02h  A_UINT16 2  aid;    /* 80211 association ID from Assoc resp |
+------------------------------------------------------------------------+
```


### WMIcmd(8005h) - WMI_THIN_RESET_CMD ;newer ver only
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  4  reserved[4];                                   |
+-----------------------------------------------------------------------+
```


### WMIevent(8000h) - WMI_THIN_EVENTID_RESERVED_START
### WMIevent(8FFFh) - WMI_THIN_EVENTID_RESERVED_END
Events/Responses with special IDs for THIN stuff (wmi_thin.h)

### WMIevent(8001h) - WMI_THIN_GET_MIB_EVENT
Event Data:

```
+--------------------------------------------------------------------------------+
|       Unknown (maybe same/similar format as for "SET_MIB" command parameters?) |
+--------------------------------------------------------------------------------+
```


### WMIevent(8002h) - WMI_THIN_JOIN_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8 1  result (the result of the join command)         |
|       01h  A_UINT8 3  reserved[3]; /* alignment                       |
+-----------------------------------------------------------------------+
```

WMI_THIN_JOIN_RESULT values (aka above \"result\" value):

```
+-----------------------------------------------------------------------------------+
|       WMI_THIN_JOIN_RES_SUCCESS    = 0  ;device has joined the network            |
|       WMI_THIN_JOIN_RES_FAIL       = 1  ;failed for unspecified reason            |
|       WMI_THIN_JOIN_RES_TIMEOUT    = 2  ;failed due to no beacon rx in time limit |
|       WMI_THIN_JOIN_RES_BAD_PARAM  = 3  ;failed due to bad cmd param              |
|       WMI_THIN_JOIN_RES_IBSS_START = 4  ;device started new IBSS network          |
+-----------------------------------------------------------------------------------+
```


### MIB Access Identifiers tailored for Symbian - mibID
Below are \"mibID\" values for SET_MIB and GET_MIB commands, with corresponding data structures. GET/SET works only if the corresponding structure is read/write-able, as indicated by (R), (W), and (R/W). Some structures aren\'t actually implemented (-), ie. not read/write-able.

```
+-------------------------------------------------------------------------------------+
|      When mibID=01h=MIB_ID_STA_MAC; WMI_THIN_MIB_STA_MAC struct:                (R) |
|       00h  A_UINT8  6  addr[ATH_MAC_LEN];                                           |
|      When mibID=02h=MIB_ID_RX_LIFE_TIME; WMI_THIN_MIB_RX_LIFE_TIME struct:      (-) |
|       00h  A_UINT32 4  time (units = msec)                                          |
|      When mibID=03h=MIB_ID_SLOT_TIME; WMI_THIN_MIB_SLOT_TIME struct:          (R/W) |
|       00h  A_UINT32 4  time (units = usec)                                          |
|      When mibID=04h=MIB_ID_RTS_THRESHOLD; WMI_THIN_MIB_RTS_THRESHOLD struct:  (R/W) |
|       00h  A_UINT16 2  length (units = bytes)                                       |
|      When mibID=05h=MIB_ID_CTS_TO_SELF; WMI_THIN_MIB_CTS_TO_SELF struct:      (R/W) |
|       00h  A_UINT8  1  enable (1=on, 0=off)                                         |
|      When mibID=06h=MIB_ID_TEMPLATE_FRAME; WMI_THIN_MIB_TEMPLATE_FRAME struct:  (W) |
|       00h  A_UINT8  1  type (type of frame, 0..5, see below "FRM" values)           |
|       01h  A_UINT8  1  rate (tx rate to be used, one of WMI_BIT_RATE)               |
|       02h  A_UINT16 2  length (num bytes following this structure as template data) |
|       04h  ..       .. template data                                                |
|       Frame "type" values:          frame max length:                               |
|       TEMPLATE_FRM_PROBE_REQ = 0    FRM_LEN_PROBE_REQ  = 256  ;\Symbian dictates a  
|       TEMPLATE_FRM_BEACON    = 1    FRM_LEN_BEACON     = 256  ; minimum of 256 for  |
|       TEMPLATE_FRM_PROBE_RESP= 2    FRM_LEN_PROBE_RESP = 256  ;/these 3 frame types |
|       TEMPLATE_FRM_NULL      = 3    FRM_LEN_NULL       = 32                         |
|       TEMPLATE_FRM_QOS_NULL  = 4    FRM_LEN_QOS_NULL   = 32                         |
|       TEMPLATE_FRM_PSPOLL    = 5    FRM_LEN_PSPOLL     = 32                         |
|       Total sum of above lengths: TEMPLATE_FRM_LEN_SUM = 256+256+256+32+32+32       |
|      When mibID=07h=MIB_ID_RXFRAME_FILTER; WMI_THIN_MIB_RXFRAME_FILTER struct:(R/W) |
|       00h  A_UINT32 4  filterMask;                                                  |
|       FRAME_FILTER_PROMISCUOUS = 00000001h                                          |
|       FRAME_FILTER_BSSID       = 00000002h                                          |
|      When mibID=08h=MIB_ID_BEACON_FILTER_TABLE; Several structure(s)...?        (W) |
|       There are three related sturctures; the actual "TABLE", and additional        |
|       "TABLE_OUI" and "TABLE_HEADER"; unknown which of those structure(s) are       |
|       meant to be used here...                                                      |
|       WMI_THIN_MIB_BEACON_FILTER_TABLE structure:                                   |
|       00h  A_UINT8  1  ie;                                                          |
|       01h  A_UINT8  1  treatment;                                                   |
|       IE_FILTER_TREATMENT_CHANGE = 1                                                |
|       IE_FILTER_TREATMENT_APPEAR = 2                                                |
|       WMI_THIN_MIB_BEACON_FILTER_TABLE_OUI structure:                               |
|       00h  A_UINT8  1  ie;                                                          |
|       01h  A_UINT8  1  treatment;                                                   |
|       02h  A_UINT8  3  oui[3];                                                      |
|       05h  A_UINT8  1  type;                                                        |
|       06h  A_UINT16 2  version;                                                     |
|       WMI_THIN_MIB_BEACON_FILTER_TABLE_HEADER structure:                            |
|       00h  A_UINT16 2  numElements                                                  |
|       02h  A_UINT8  1  entrySize (sizeof(WMI_THIN_MIB_BEACON_FILTER_TABLE) on       |
|       03h  A_UINT8  1  reserved                    host cpu may be 2 may be 4)      |
|      When mibID=09h=MIB_ID_BEACON_FILTER; WMI_THIN_MIB_BEACON_FILTER struct:  (R/W) |
|       00h  A_UINT32 4  count (num beacons between deliveries)                       |
|       04h  A_UINT8  1  enable;                                                      |
|       05h  A_UINT8  3  reserved[3];                                                 |
|      When mibID=0Ah=MIB_ID_BEACON_LOST_COUNT; WMI_THIN_MIB_BEACON_LOST_COUNT:   (W) |
|       00h  A_UINT32 4  count (num consec lost beacons after which send event)       |
|      When mibID=0Bh=MIB_ID_RSSI_THRESHOLD; WMI_THIN_MIB_RSSI_THRESHOLD struct:  (W) |
|       00h  A_UINT8 1   rssi (the low threshold which can trigger an event warning)  |
|       01h  A_UINT8 1   tolerance (the range above and below the threshold to        |
|                         prevent event flooding to the host)                         |
|       02h  A_UINT8 1   count (the sample count of consecutive frames necessary to   |
|                         trigger an event)                                           |
|       03h  A_UINT8 1   reserved[1] (padding)                                        |
|      When mibID=0Ch=MIB_ID_HT_CAP; WMI_THIN_MIB_HT_CAP struct:                  (-) |
|       00h  A_UINT32 4  cap;                                                         |
|       04h  A_UINT32 4  rxRateField;                                                 |
|       08h  A_UINT32 4  beamForming;                                                 |
|       0Ch  A_UINT8  6  addr[ATH_MAC_LEN];                                           |
|       12h  A_UINT8  1  enable;                                                      |
|       13h  A_UINT8  1  stbc;                                                        |
|       14h  A_UINT8  1  maxAMPDU;                                                    |
|       15h  A_UINT8  1  msduSpacing;                                                 |
|       16h  A_UINT8  1  mcsFeedback;                                                 |
|       17h  A_UINT8  1  antennaSelCap;                                               |
|      When mibID=0Dh=MIB_ID_HT_OP; WMI_THIN_MIB_HT_OP struct:                    (-) |
|       00h  A_UINT32 4  infoField;                                                   |
|       04h  A_UINT32 4  basicRateField;                                              |
|       08h  A_UINT8  1  protection;                                                  |
|       09h  A_UINT8  1  secondChanneloffset;                                         |
|       0Ah  A_UINT8  1  channelWidth;                                                |
|       0Bh  A_UINT8  1  reserved;                                                    |
|      When mibID=0Eh=MIB_ID_HT_2ND_BEACON; WMI_THIN_MIB_HT_2ND_BEACON struct:    (-) |
|       00h  A_UINT8  1  cfg (see below SECOND_BEACON_xxx values)                     |
|       01h  A_UINT8  3  reserved[3] (padding)                                        |
|       SECOND_BEACON_PRIMARY   = 1                                                   |
|       SECOND_BEACON_EITHER    = 2                                                   |
|       SECOND_BEACON_SECONDARY = 3                                                   |
|      When mibID=0Fh=MIB_ID_HT_BLOCK_ACK; WMI_THIN_MIB_HT_BLOCK_ACK struct:      (-) |
|       00h  A_UINT8  1  txTIDField                                                   |
|       01h  A_UINT8  1  rxTIDField                                                   |
|       02h  A_UINT8  2  reserved[2] (padding)                                        |
|      When mibID=10h=MIB_ID_PREAMBLE; WMI_THIN_MIB_PREAMBLE struct:            (R/W) |
|       00h  A_UINT8  1  enableLong (1=long preamble, 0=short preamble)               |
|       01h  A_UINT8  3  reserved[3]                                                  |
|      When mibID=N/A=MIB_ID_GROUP_ADDR_TABLE    ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_WEP_DEFAULT_KEY_ID  ;satisfied by wmi_addKey_cmd()   (-) |
|      When mibID=N/A=MIB_ID_TX_POWER            ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_ARP_IP_TABLE        ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_SLEEP_MODE          ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_WAKE_INTERVAL       ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_STAT_TABLE          ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_IBSS_PWR_SAVE       ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_COUNTERS_TABLE      ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_ETHERTYPE_FILTER    ;[NOT IMPLEMENTED]               (-) |
|      When mibID=N/A=MIB_ID_BC_UDP_FILTER       ;[NOT IMPLEMENTED]               (-) |
|       N/A                                                                           |
+-------------------------------------------------------------------------------------+
```


### THIN related constants\...
MAC Header Build Rules
These values allow the host to configure the target code that is responsible for constructing the MAC header. In cases where the MAC header is provided by the host framework, the target has a diminished responsibility over what fields it must write. This will vary from framework to framework.
Symbian requires different behavior from MAC80211 which requires different behavior from MS Native Wifi.

```
+--------------------------------------------------------------------------------+
|       WMI_WRT_VER_TYPE  = 00000001h                                            |
|       WMI_WRT_DURATION  = 00000002h                                            |
|       WMI_WRT_DIRECTION = 00000004h                                            |
|       WMI_WRT_POWER     = 00000008h                                            |
|       WMI_WRT_WEP       = 00000010h                                            |
|       WMI_WRT_MORE      = 00000020h                                            |
|       WMI_WRT_BSSID     = 00000040h                                            |
|       WMI_WRT_QOS       = 00000080h                                            |
|       WMI_WRT_SEQNO     = 00000100h                                            |
|       WMI_GUARD_TX      = 00000200h ;prevent TX ops that are not allowed for a |
|                                     ; current state                            |
|       WMI_WRT_DEFAULT_CONFIG = 3FFh             ;<-- default all bits set      |
+--------------------------------------------------------------------------------+
```


See also: WMI_SET_THIN_MODE_CMD



