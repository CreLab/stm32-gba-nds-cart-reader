# DSi Atheros Wifi - Unimplemented WMI WAC Functions


### WMIcmd(F043h) - WMI_WAC_ENABLE_CMD aka WMI_ENABLE_WAC_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4   period;                                       |
|       04h  A_UINT32 4   threshold;                                    |
|       08h  A_INT32  4   rssi;                                         |
|       0Ch  A_BOOL   4   enable;                                       |
|       10h  A_CHAR   8   wps_pin[8];     ;WPS related?                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F044h) - WMI_WAC_SCAN_REPLY_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_ENUM   ..  cmdid ;A_UINTx or so?  (WAC_SUBCMD)           |
+-----------------------------------------------------------------------+
```

WAC_SUBCMD values:

```
+-----------------------------------------------------------------------+
|       WAC_MORE_SCAN      = -1                                         |
|       WAC_SEND_PROBE_IDX = 0                                          |
+-----------------------------------------------------------------------+
```


### WMIcmd(F045h) - WMI_WAC_CTRL_REQ_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   req;     ;aka WAC_REQUEST_TYPE                |
|       01h  A_UINT8  1   cmd;     ;aka WAC_COMMAND                     |
|       02h  A_UINT8  1   frame;   ;aka WAC_FRAME_TYPE                  |
|       03h  A_UINT8  11h ie[17];                                       |
|       14h  A_INT32  4   status;  ;aka WAC_STATUS                      |
+-----------------------------------------------------------------------+
```

WAC related constants (from wac_defs.h):
WAC_REQUEST_TYPE values:

```
+-----------------------------------------------------------------------+
|       WAC_SET        = Unknown (0 or 1 or so)                         |
|       WAC_GET        = WAC_SET+1                                      |
+-----------------------------------------------------------------------+
```

WAC_COMMAND values:

```
+-----------------------------------------------------------------------+
|       WAC_ADD        = Unknown (0 or 1 or so)                         |
|       WAC_DEL        = WAC_ADD+1                                      |
|       WAC_GET_STATUS = WAC_ADD+2                                      |
|       WAC_GET_IE     = WAC_ADD+3                                      |
+-----------------------------------------------------------------------+
```

WAC_FRAME_TYPE values:

```
+-----------------------------------------------------------------------+
|       PRBREQ         = Unknown (0 or 1 or so)                         |
|       PRBRSP         = PRBREQ+1                                       |
|       BEACON         = PRBREQ+2                                       |
+-----------------------------------------------------------------------+
```

WAC_STATUS values:

```
+-----------------------------------------------------------------------+
|       WAC_FAILED_NO_WAC_AP      = -4                                  |
|       WAC_FAILED_LOW_RSSI       = -3                                  |
|       WAC_FAILED_INVALID_PARAM  = -2                                  |
|       WAC_FAILED_REJECTED       = -1                                  |
|       WAC_SUCCESS               = 0                                   |
|       WAC_DISABLED              = 1                                   |
|       WAC_PROCEED_FIRST_PHASE   = 2                                   |
|       WAC_PROCEED_SECOND_PHASE  = 3                                   |
+-----------------------------------------------------------------------+
```


### WMIevent(1037h) - WMI_WAC_SCAN_DONE_EVENT
### WMIevent(1038h) - WMI_WAC_REPORT_BSS_EVENT
### WMIevent(1039h) - WMI_WAC_START_WPS_EVENT
### WMIevent(103Ah) - WMI_WAC_CTRL_REQ_REPLY_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (if any?)                                               |
+-----------------------------------------------------------------------+
```

WAC Events. Event data format is unknown, maybe related to below two structs:
WMI_GET_WAC_INFO structure (UNION):

```
+-----------------------------------------------------------------------+
|      When some case:                                                  |
|       00h  A_UINT8  11h  ie[17];                                      |
|      When some other case:                                            |
|       00h  A_INT32  4    wac_status;                                  |
+-----------------------------------------------------------------------+
```

WMI_WPS_PIN_INFO structure: ;\"WPS\" might be WAC_START_WPS related?

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  6  bssid[ATH_MAC_LEN];                            |
|       06h  A_UINT8  8  pin[8];        ;aka "wps_pin[8]" presumably?   |
+-----------------------------------------------------------------------+
```




