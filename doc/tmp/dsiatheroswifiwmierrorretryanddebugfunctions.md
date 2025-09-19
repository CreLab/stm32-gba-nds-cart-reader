# DSi Atheros Wifi - WMI Error, Retry and Debug Functions


### WMIcmd(0024h) - WMI_SET_RETRY_LIMITS_CMD
Parameters:

```
+---------------------------------------------------------------------------+
|       00h  A_UINT8  1  frameType          ;WMI_FRAMETYPE                  |
|       01h  A_UINT8  1  trafficClass       ;applies only to DATA_FRAMETYPE |
|       02h  A_UINT8  1  maxRetries                                         |
|       03h  A_UINT8  1  enableNotify                                       |
+---------------------------------------------------------------------------+
```

This command is used to customize the number of retries the wlan device will perform on a given frame.

```
+-----------------------------------------------------------------------+
|       WMI_MIN_RETRIES = 2                                             |
|       WMI_MAX_RETRIES = 13                                            |
+-----------------------------------------------------------------------+
```

WMI_FRAMETYPE values:

```
+-----------------------------------------------------------------------+
|       MGMT_FRAMETYPE    = 0                                           |
|       CONTROL_FRAMETYPE = 1                                           |
|       DATA_FRAMETYPE    = 2                                           |
+-----------------------------------------------------------------------+
```


### WMIcmd(0022h) - WMI_TARGET_ERROR_REPORT_BITMASK_CMD
Parameters (04h bytes):

```
+---------------------------------------------------------------------------+
|       00h  A_UINT32 4   bitmask    ;... probably "WMI_TARGET_ERROR_VAL" ? |
+---------------------------------------------------------------------------+
```

Sets the error reporting event bitmask in target. Target clears it upon an error. Subsequent errors are counted, but not reported via event, unless the bitmask is set again.
See also: WMI_TARGET_ERROR_REPORT_EVENT

### WMIevent(1005h) - WMI_CMDERROR_EVENT ;aka WMI_CMD_ERROR_EVENT
Event Data (03h bytes):

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT16 2   commandId    ;on DSi, this can be: 0001h,0011h,0016h,0026h |
|       02h  A_UINT8  1   errorCode    ;on DSi, this can be: 01h,02h                 |
+------------------------------------------------------------------------------------+
```

WMI_ERROR_CODE values:

```
+-----------------------------------------------------------------------+
|       INVALID_PARAM  = 01h                                            |
|       ILLEGAL_STATE  = 02h                                            |
|       INTERNAL_ERROR = 03h                                            |
|       DFS_CHANNEL    = 04h                                            |
+-----------------------------------------------------------------------+
```

Command Error Event

### WMIevent(100Dh) - WMI_ERROR_REPORT_EVENT ;aka WMI_TARGET_ERROR_REPORT_EVENT
Event Data (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4  errorVal                                      |
+-----------------------------------------------------------------------+
```

WMI_TARGET_ERROR_VAL values:

```
+-----------------------------------------------------------------------+
|       WMI_TARGET_PM_ERR_FAIL      = 00000001h                         |
|       WMI_TARGET_KEY_NOT_FOUND    = 00000002h                         |
|       WMI_TARGET_DECRYPTION_ERR   = 00000004h                         |
|       WMI_TARGET_BMISS            = 00000008h                         |
|       WMI_PSDISABLE_NODE_JOIN     = 00000010h                         |
|       WMI_TARGET_COM_ERR          = 00000020h                         |
|       WMI_TARGET_FATAL_ERR        = 00000040h                         |
|       WMI_TARGET_BCN_FOUND        = 00000080h                         |
+-----------------------------------------------------------------------+
```


### WMIevent(1014h) - WMI_TX_RETRY_ERR_EVENT
Event Data (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   retrys                                        |
+-----------------------------------------------------------------------+
```


### WMIcmd(002Eh:2009h) - WMIX_DBGLOG_CFG_MODULE_CMD
Parameters (08h bytes):

```
+------------------------------------------------------------------------------+
|       00h  A_UINT32 4   cfgvalid        ;change mask (0=no change, 1=change) |
|       04h  A_UINT32 4   dbglog_config   ;new state   (0=clear, 1=set)        |
+------------------------------------------------------------------------------+
```

The cfgvalid mask and dbglog_config bits are:

```
+------------------------------------------------------------------------------------+
|       Bit0-15   DBGLOG_MODULE_LOG_ENABLE     ;logging enable flags for module 0-15 |
|       Bit16     DBGLOG_REPORTING_ENABLED     ;reporting enable flag (1=enable)     |
|       Bit17-19  DBGLOG_TIMESTAMP_RESOLUTION  ;timestamp resolution (default=1 ms)  |
|       Bit20-29  DBGLOG_REPORT_SIZE           ;report size in number of messages    |
|       Bit30-31  Reserved                     ;reserved                             |
+------------------------------------------------------------------------------------+
```

Using parameters FFFFFFFFh,00000000h or 0001FFFFh,00000000h does disable WMIX_DBGLOG_EVENT.

### WMIevent(1010h:3008h) - WMIX_DBGLOG_EVENT ;used (probably related to 2009h)
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (?) (related/enabled by WMIX_DBGLOG_CFG_MODULE_CMD)     |
+-----------------------------------------------------------------------+
```

DSi Browser does receive this - with LOTs of data (almost 1.5Kbyte)
Reportedly there is a dbglog message value (with numeric \"message\" IDs, perhaps related to dbglog EVENT response headers):

```
+----------------------------------------------------------------------------------+
|       Bit0-15    DBGLOG_TIMESTAMP  ;contains bit8-23 of the LF0 timer (0..FFFFh) |
|       Bit16-25   DBGLOG_DBGID      ;minor ID (defined in "dbglog_id.h")          |
|       Bit26-29   DBGLOG_MODULEID   ;major ID (defined in "dbglog.h")             |
|       Bit30-31   DBGLOG_NUM_ARGS   ;whatever "num args"                          |
+----------------------------------------------------------------------------------+
```




