# DSi Atheros Wifi - Unimplemented WMI RF Kill and Store/Recall Functions


### WMIcmd(F057h or F04Bh) - WMI_GET_RFKILL_MODE_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: See WMI_RFKILL_GET_MODE_CMD_EVENT

### WMIcmd(F058h or F04Ch) - WMI_SET_RFKILL_MODE_CMD ;aka WMI_RFKILL_MODE_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  GPIOPinNumber  ;GPIO related                   |
|       01h  A_UINT8  1  IntrType       ;?                              |
|       02h  A_UINT8  1  RadioState     ;RFKILL_RADIO_STATE             |
+-----------------------------------------------------------------------+
```

RFKILL_RADIO_STATE values:

```
+-----------------------------------------------------------------------+
|       RADIO_STATE_OFF     = 01h                                       |
|       RADIO_STATE_ON      = 02h                                       |
|       RADIO_STATE_INVALID = FFh                                       |
+-----------------------------------------------------------------------+
```


### WMIevent(103Bh) - WMI_RFKILL_STATE_CHANGE_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (if any?)                                               |
+-----------------------------------------------------------------------+
```


### WMIevent(103Ch) - WMI_RFKILL_GET_MODE_CMD_EVENT
Event Data:

```
+--------------------------------------------------------------------------+
|       Unknown (maybe some format as in "SET_RFKILL" command parameters?) |
+--------------------------------------------------------------------------+
```


### WMIcmd(F05Eh or F04Eh) - WMI_STORERECALL_CONFIGURE_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT8 1  enable (probably some flag)                                   |
|       01h  A_UINT8 1  recipient (only one value defined: STRRCL_RECIPIENT_HOST = 1) |
+-------------------------------------------------------------------------------------+
```

Ultra low power store/recall feature. Seems to be intended to memorize data in HOST memory\... allowing the AR600x chip to power-down its on memory, or so?

### WMIcmd(F05Fh or F04Fh) - WMI_STORERECALL_RECALL_CMD
Parameters:

```
+------------------------------------------------------------------------+
|       00h  A_UINT32 4  length;      ;number of bytes of data to follow |
|       04h  A_UINT8  .. data[1];     ;start of "RECALL" data            |
+------------------------------------------------------------------------+
```

Ultra low power store/recall feature. Maybe RECALL is meant to restore data that was formerly memorized from a WMI_STORERECALL_STORE_EVENT.

### WMIcmd(F060h or F050h) - WMI_STORERECALL_HOST_READY_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  sleep_msec;                                    |
|       04h  A_UINT8  1  store_after_tx_empty;                          |
|       05h  A_UINT8  1  store_after_fresh_beacon_rx;                   |
+-----------------------------------------------------------------------+
```

Ultra low power store/recall feature. Whatever parameters.

### WMIevent(9004h) - WMI_STORERECALL_STORE_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  msec_sleep;   ;time between power off/on       |
|       04h  A_UINT32 4  length;       ;length of following data        |
|       08h  A_UINT8  .. data[1];      ;start of "STORE" data           |
+-----------------------------------------------------------------------+
```

Ultra low power store/recall feature. Maybe this requests to memorize the \"STORE\" data in host memory?



