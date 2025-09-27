# DSi Atheros Wifi - WMI Bluetooth Coexistence (older AR6002)


Bluetooth Coexistence support has underwent significant changes:

```
+------------------------------------------------------------------------------------+
|       Older AR6002 from 2008 ;-original Bluetooth COEX version                     |
|       Newer AR6002 from 2008 ;\same commands as above, but with entirely different 
|       Newer AR6002 from 2010 ;/parameters (and minor changes for 2008 vs 2010)     |
|       AR6003 from 2010       ;-completely different commands for Bluetooth COEX    |
+------------------------------------------------------------------------------------+
```

Below are Bluetooth COEX functions for OLDER AR6002 - as used on DSi - and as defined in \"AR6kSDK.build_sw.18\".

On DSi, AR6002 does handle command 003Ch and 003Ch, but AR6013/AR6014 do merely redirect them to dummy handlers; despite of also having (unused) actual handlers for those commands.

### WMIcmd(003Bh) - WMI_SET_BT_STATUS_CMD ;AR6002 Bluetooth Coexistence only?
Parameters (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   streamType          ;aka BT_STREAM_TYPE ?     |
|       01h  A_UINT8  1   status              ;aka BT_STREAM_STATUS ?   |
+-----------------------------------------------------------------------+
```

BT_STREAM_TYPE values:

```
+-------------------------------------------------------------------------------------+
|       BT_STREAM_UNDEF = 0                   ;\                                      
|       BT_STREAM_SCO   = 1 ;SCO stream       ; only this three types in Older AR6002 |
|       BT_STREAM_A2DP  = 2 ;A2DP stream      ;/                                      |
+-------------------------------------------------------------------------------------+
```

BT_STREAM_STATUS values:

```
+------------------------------------------------------------------------------------+
|       BT_STATUS_UNDEF        = 0  ;\                                               
|       BT_STATUS_START        = 1  ; this five states in Older AR6002               |
|       BT_STATUS_STOP         = 2  ; (Newer A6002 has added/removed/renamed states) |
|       BT_STATUS_RESUME       = 3  ;                                                |
|       BT_STATUS_SUSPEND      = 4  ;/                                               |
+------------------------------------------------------------------------------------+
```

AR6002 only? (although other comment says \"COMMON to AR6002 and AR6003\"?)

### WMIcmd(003Ch) - WMI_SET_BT_PARAMS_CMD ;AR6002 Bluetooth Coexistence only?
Parameters (16h bytes on DSi?, whatever that might match up with below?):

```
+-------------------------------------------------------------------------------------+
|      when paramType=1=BT_PARAM_SCO:    ;SCO stream parameters (BT_PARAMS_SCO)       |
|       00h  A_UINT8  1   noSCOPkts                                                   |
|       01h  A_UINT8  1   pspollTimeout                                               |
|       02h  A_UINT8  1   stompbt                                                     |
|       03h  PAD      12h undefined/padding                                           |
|      when paramType=2=BT_PARAM_A2DP:   ;whatever (BT_PARAMS_A2DP)                   |
|       00h  A_UINT32 4   period                                                      |
|       04h  A_UINT32 4   dutycycle                                                   |
|       08h  A_UINT8  1   stompbt                                                     |
|       09h  PAD      0Ch undefined/padding                                           |
|      when paramType=3=BT_PARAM_MISC and paramSubType=1=WLAN_PROTECT_POLICY:         |
|       00h  A_UINT32 4   period                                                      |
|       04h  A_UINT32 4   dutycycle                                                   |
|       08h  A_UINT8  1   stompbt                                                     |
|       09h  A_UINT8  1   policy                                                      |
|       0Ah  A_UINT8  1   paramSubType  (=1 in this case)                             |
|       0Bh  PAD      0Ah undefined/padding                                           |
|      when paramType=3=BT_PARAM_MISC and paramSubType=2=WLAN_COEX_CTRL_FLAGS:        |
|       00h  A_UINT16 2   wlanCtrlFlags                                               |
|       02h  PAD      8   undefined/padding                                           |
|       0Ah  A_UINT8  1   paramSubType  (=2 in this case)                             |
|       0Bh  PAD      0Ah undefined/padding                                           |
|      when paramType=4=BT_PARAM_REGS:   ;co-existence register params (BT_COEX_REGS) |
|       00h  A_UINT32 4   mode                                                        |
|       04h  A_UINT32 4   scoWghts                                                    |
|       08h  A_UINT32 4   a2dpWghts                                                   |
|       0Ch  A_UINT32 4   genWghts                                                    |
|       10h  A_UINT32 4   mode2                                                       |
|       14h  A_UINT8  1   setVal                                                      |
|      and, in all cases:                                                             |
|       15h  A_UINT8  1   paramType    ;<-- selects which of the above to use         |
+-------------------------------------------------------------------------------------+
```


Below might be \"policy\" for WLAN_PROTECT_POLICY(?):

```
+-----------------------------------------------------------------------+
|       WLAN_PROTECT_PER_STREAM = 01h   /* default                      |
|       WLAN_PROTECT_ANY_TX     = 02h                                   |
+-----------------------------------------------------------------------+
```


Below might be \"wlanCtrlFlags\" for WLAN_COEX_CTRL_FLAGS(?):

```
+-----------------------------------------------------------------------+
|       WLAN_DISABLE_COEX_IN_DISCONNECT = 0001h   ;default              |
|       WLAN_KEEP_COEX_IN_DISCONNECT    = 0002h                         |
|       WLAN_STOMPBT_IN_DISCONNECT      = 0004h                         |
|       WLAN_DISABLE_COEX_IN_ROAM       = 0010h   ;default              |
|       WLAN_KEEP_COEX_IN_ROAM          = 0020h                         |
|       WLAN_STOMPBT_IN_ROAM            = 0040h                         |
|       WLAN_DISABLE_COEX_IN_SCAN       = 0100h   ;default              |
|       WLAN_KEEP_COEX_IN_SCAN          = 0200h                         |
|       WLAN_STOMPBT_IN_SCAN            = 0400h                         |
|       WLAN_DISABLE_COEX_BT_OFF        = 1000h   ;default              |
|       WLAN_KEEP_COEX_BT_OFF           = 2000h                         |
|       WLAN_STOMPBT_BT_OFF             = 4000h                         |
+-----------------------------------------------------------------------+
```




