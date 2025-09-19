# DSi Atheros Wifi - WMI Power Functions


### WMIcmd(0012h) - WMI_SET_POWER_MODE_CMD ;aka WMI_POWER_MODE_CMD
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   powerMode           ;WMI_POWER_MODE           |
+-----------------------------------------------------------------------+
```

WMI_POWER_MODE values:

```
+-----------------------------------------------------------------------+
|       REC_POWER      = 01h     ;recommended,receive,record,rectal?    |
|       MAX_PERF_POWER = 02h     ;maximum performance,perforation?      |
+-----------------------------------------------------------------------+
```


### WMIcmd(0013h) - WMI_SET_IBSS_PM_CAPS_CMD ;aka WMI_IBSS_PM_CAPS_CMD
Parameters (06h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  power_saving                                   |
|       01h  A_UINT8  1  ttl                  ;number of beacon periods |
|       02h  A_UINT16 2  atim_windows         ;msec                     |
|       04h  A_UINT16 2  timeout_value        ;msec                     |
+-----------------------------------------------------------------------+
```

Adhoc power save types aka WMI_ADHOC_PS_TYPE:

```
+-----------------------------------------------------------------------+
|       ADHOC_PS_DISABLE = 1                                            |
|       ADHOC_PS_ATH     = 2                                            |
|       ADHOC_PS_IEEE    = 3                                            |
|       ADHOC_PS_OTHER   = 4                                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(0014h) - WMI_SET_POWER_PARAMS_CMD ;aka WMI_POWER_PARAMS_CMD
Parameters (06h bytes on DSi?, but other sources claim 0Ch bytes):

```
+-----------------------------------------------------------------------+
|       06h 0Ch   <---- total size (on DSi it's 06h, ie. left column)   |
|       00h 00h  A_UINT16 2   idle_period             ;msec             |
|       02h 02h  A_UINT16 2   pspoll_number                             |
|       04h 04h  A_UINT16 2   dtim_policy                               |
|       --  06h  A_UINT16 2   tx_wakeup_policy                          |
|       --  08h  A_UINT16 2   num_tx_to_wakeup                          |
|       --  0Ah  A_UINT16 2   ps_fail_event_policy                      |
+-----------------------------------------------------------------------+
```

WMI_DTIM_POLICY values:

```
+-----------------------------------------------------------------------+
|       IGNORE_DTIM = 01h                                               |
|       NORMAL_DTIM = 02h                                               |
|       STICK_DTIM  = 03h                                               |
|       AUTO_DTIM   = 04h                                               |
+-----------------------------------------------------------------------+
```

WMI_TX_WAKEUP_POLICY_UPON_SLEEP values (Policy to determnine (Nine?) whether TX should wakeup WLAN if sleeping):

```
+-----------------------------------------------------------------------+
|       TX_WAKEUP_UPON_SLEEP      = 1                                   |
|       TX_DONT_WAKEUP_UPON_SLEEP = 2                                   |
+-----------------------------------------------------------------------+
```

POWER_SAVE_FAIL_EVENT_POLICY values (Policy to determnine (Nine?) whether power save failure event should be sent to host during scanning):

```
+-----------------------------------------------------------------------+
|       SEND_POWER_SAVE_FAIL_EVENT_ALWAYS        = 1                    |
|       IGNORE_POWER_SAVE_FAIL_EVENT_DURING_SCAN = 2                    |
+-----------------------------------------------------------------------+
```


### WMIcmd(0015h) - WMI_SET_POWERSAVE_TIMERS_POLICY_CMD ;aka WMI_POWERSAVE\...
Parameters (0Ch bytes):

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT16 2  psPollTimeout (msec)                                     |
|       02h  A_UINT16 2  triggerTimeout (msec)                                    |
|       04h  A_UINT32 4  apsdTimPolicy (TIM behavior with ques (=?) APSD enabled. |
|                         Default is IGNORE_TIM_ALL_QUEUES_APSD)                  |
|       08h  A_UINT32 4  simulatedAPSDTimPolicy (TIM behavior with simulated APSD |
|                         enabled. Default is PROCESS_TIM_SIMULATED_APSD)         |
+---------------------------------------------------------------------------------+
```

APSD_TIM_POLICY values:

```
+-----------------------------------------------------------------------+
|       IGNORE_TIM_ALL_QUEUES_APSD  = 0                                 |
|       PROCESS_TIM_ALL_QUEUES_APSD = 1                                 |
|       IGNORE_TIM_SIMULATED_APSD   = 2                                 |
|       PROCESS_TIM_SIMULATED_APSD  = 3                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(001Bh) - WMI_SET_TX_PWR_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   dbM                 ;in dbM units             |
+-----------------------------------------------------------------------+
```


### WMIcmd(001Ch) - WMI_GET_TX_PWR_CMD ;aka WMI_TX_PWR ;reply 001Ch
Parameters:

```
+-----------------------------------------------------------------------+
|       None                                                            |
+-----------------------------------------------------------------------+
```

Reply:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   dbM                 ;in dbM units             |
+-----------------------------------------------------------------------+
```


### WMIcmd(0048h) - WMI_SET_AP_PS_CMD ;aka WMI_AP_PS_CMD ;not implemented on DSi
This supported in most or all atheros code versions, but DSi doesn\'t support it.
Parameters (0Ah bytes):

```
+----------------------------------------------------------------------------------+
|       -   00h  A_UINT32 4   idle_time      ;in msec                              |
|       -   04h  A_UINT32 4   ps_period      ;in usec                              |
|       -   08h  A_UINT8  1   sleep_period   ;in ps_period's (=above "ps_period"?) |
|       -   09h  A_UINT8  1   psType         ;AP power save type                   |
+----------------------------------------------------------------------------------+
```

WMI_AP_PS_TYPE, AP power save types:

```
+-----------------------------------------------------------------------+
|       AP_PS_DISABLE = 1                                               |
|       AP_PS_ATH     = 2                                               |
+-----------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      _________________________________ Heartbeat __________________________________ |
+-------------------------------------------------------------------------------------+
```


Heartbeat Challenge Response is said to be an \"Error Detection support\" feature, but it isn\'t exactly clear what it is supposed to do. DSi software does usually set the heartbeat timeout to 2, and does then throw heartbeat commands once per second or so (which will respond with a heartbeat event and restart the heartbeat timeout).
If a timeout occurs because of not sending heartbeat commands in time: Some firmwares do simply ignoring the timeout (eg. DSi/AR6013, or 3DS/AR6014 with basic Type1 firmware). However, other firmwares do hang up (eg. 3DS/AR6014 with AP-mode Type4 firmware). There seems to be no error message/event on timeout, and no known way to recover from timeout.

### WMIcmd(002Eh:2008h) - WMIX_HB_CHALLENGE_RESP_CMD ;reply=3007h ;HB=heartbeat

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4    cookie    ;usually increasing 1,2,3,4,5,etc. |
|       04h  A_UINT32 4    source    ;usually 0                         |
+-----------------------------------------------------------------------+
```

This should be sent once per second or so, the command does reload the heartbeat timeout and (immediately) trigger a WMIX_HB_CHALLENGE_RESP_EVENT.
The cookie/source parameters are passed on to the reponse event (and seem to have no other function).

### WMIevent(1010h:3007h) - WMIX_HB_CHALLENGE_RESP_EVENT ;used (reply to 2008h)
Event Data:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT32  4    cookie    ;\same reply-format as command parameters 
|       04h  A_UINT32  4    source    ;/                                        |
+-------------------------------------------------------------------------------+
```


### WMIcmd(0047h) - WMI_SET_HB_CHALLENGE_RESP_PARAMS_CMD
This seems to be a nintendo-specific command with 4-byte parameter (official atheros source code contains a 5-byte WMI_SET_HB_CHALLENGE_RESP_PARAMS_CMD structure, but doesn\'t have any CMD number assigned to it).
Parameters (04h or 05h bytes):

```
+------------------------------------------------------------------------------------+
|       04h 05h  <---- total size (on DSi it's 04h, ie. left column)                 |
|       00h -    A_UINT32 4  timeout  ;in seconds, used: 00000002h ;(or 0=Disable)   |
|       -   00h  A_UINT32 4  frequency   ;\whatever, not really used because there's 
|       -   04h  A_UINT8  1  threshold   ;/no WMIcmd(xxxxh) value assigned           |
+------------------------------------------------------------------------------------+
```

BUG: The function uses a bizarre timeout\*1000/1000 mechanism. Values in range timeout=21h..83h (aka timeout\*1000=8000h..1FFFFh) won\'t work on AR6002 (which tries to add a 17bit fractional part to such values; this is bugfixed in AR6013/AR6014 by using only 15bit fractions). And, on all chips, there will be an overflow on very large values (when timeout\*1000/1000 plus 15bit/17bit fraction exceeds 32bit).



