# DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence (newer AR6002)


/\*\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--COMMON to AR6002 and AR6003 \-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\-\--\*/

BT_PARAMS_SCO_PSPOLL_LATENCY values:

```
+-----------------------------------------------------------------------+
|       BT_PARAM_SCO_PSPOLL_LATENCY_ONE_FOURTH   = 1     ;aka 25%       |
|       BT_PARAM_SCO_PSPOLL_LATENCY_HALF         = 2     ;aka 50%       |
|       BT_PARAM_SCO_PSPOLL_LATENCY_THREE_FOURTH = 3     ;aka 75%       |
+-----------------------------------------------------------------------+
```


BT_PARAMS_SCO_STOMP_RULES values:

```
+-----------------------------------------------------------------------+
|       BT_PARAMS_SCO_STOMP_SCO_NEVER      = 1                          |
|       BT_PARAMS_SCO_STOMP_SCO_ALWAYS     = 2                          |
|       BT_PARAMS_SCO_STOMP_SCO_IN_LOWRSSI = 3                          |
+-----------------------------------------------------------------------+
```


BT_ANT_FRONTEND_CONFIG values:

```
+-----------------------------------------------------------------------+
|       BT_ANT_TYPE_UNDEF         = 0   ;aka "Disabled (default)"       |
|       BT_ANT_TYPE_DUAL          = 1                                   |
|       BT_ANT_TYPE_SPLITTER      = 2                                   |
|       BT_ANT_TYPE_SWITCH        = 3                                   |
|       BT_ANT_TYPE_HIGH_ISO_DUAL = 4    ;<-- not in "code aurora"      |
+-----------------------------------------------------------------------+
```


BT_COLOCATED_DEV_TYPE values:

```
+-----------------------------------------------------------------------+
|       BT_COLOCATED_DEV_BTS4020  = 0                                   |
|       BT_COLCATED_DEV_CSR       = 1                                   |
|       BT_COLOCATED_DEV_VALKYRIE = 2   ;aka BT_COLOCATED_DEV_VALKYRIe  |
+-----------------------------------------------------------------------+
```


/\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\* Applicable to AR6002 ONLY \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*/

### WMIcmd(003Bh) - WMI_SET_BT_STATUS_CMD ;AR6002 Bluetooth Coexistence only?
Parameters (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   streamType;         ;aka BT_STREAM_TYPE ?     |
|       01h  A_UINT8  1   status;             ;aka BT_STREAM_STATUS ?   |
+-----------------------------------------------------------------------+
```

BT_STREAM_TYPE values:

```
+---------------------------------------------------------------------------------+
|       BT_STREAM_UNDEF = 0                                                       |
|       BT_STREAM_SCO   = 1 ;SCO stream                                           |
|       BT_STREAM_A2DP  = 2 ;A2DP stream                                          |
|       BT_STREAM_SCAN  = 3 ;BT Discovery or Page ;\"Newer AR6002 from 2008-2010" 
|       BT_STREAM_ESCO  = 4 ;Whatever             ;/                              |
|       BT_STREAM_ALL   = 5 ;Whatever             ;-"Newer AR6002 from 2008 only" |
+---------------------------------------------------------------------------------+
```

BT_STREAM_STATUS values:

```
+--------------------------------------------------------------------------------+
|       BT_STATUS_UNDEF        = 0                                               |
|       BT_STATUS_START        = 1  ;-renamed to BT_STATUS_ON in code from 2010  |
|       BT_STATUS_STOP         = 2  ;-renamed to BT_STATUS_OFF in code from 2010 |
|       BT_STATUS_RESUME       = 3  ;\defined in "Older/Newer AR6002 from 2008"  
|       BT_STATUS_SUSPEND      = 4  ;/(not in "Newer AR6002 for 2010")           |
|       BT_STATUS_SUSPEND_A2DP = 5  ;\defined in "Newer AR6002 from 2008")       
|       BT_STATUS_SUSPEND_SCO  = 6  ; (not in "Older AR6002 for 2008")           |
|       BT_STATUS_SUSPEND_ACL  = 7  ; (not in "Newer AR6002 for 2010")           |
|       BT_STATUS_SUSPEND_SCAN = 8  ;/                                           |
+--------------------------------------------------------------------------------+
```

AR6002 only? (although other comment says \"COMMON to AR6002 and AR6003\"?)

### WMIcmd(003Ch) - WMI_SET_BT_PARAMS_CMD ;AR6002 Bluetooth Coexistence only?
Parameters (1Fh or 19h bytes, for \"Newer AR6002\" code from 2008 or 2010):

```
+-------------------------------------------------------------------------------------+
|       1Fh 19h  <--- total size (1Fh for code from 2008, 19h for code from 2010)     |
|      when paramType=1=BT_PARAM_SCO:  ;SCO stream parameters (BT_PARAMS_SCO)         |
|       00h 00h A_UINT32 4  numScoCyclesForceTrigger (Number SCO cycles after which   |
|                            force a pspoll, default=10)                              |
|       04h 04h A_UINT32 4  dataResponseTimeout (Timeout Waiting for Downlink pkt in  |
|                            response for ps-poll, default=10 ms)                     |
|       08h 08h A_UINT32 4  stompScoRules    ;aka BT_PARAMS_SCO_STOMP_RULES ?         |
|       0Ch 0Ch A_UINT32 4  scoOptFlags (SCO Options Flags)                           |
|       10h --  A_UINT32 4  p2lrpOptModeBound     ;\PacketToLowRatePacketRatio's      
|       14h --  A_UINT32 4  p2lrpNonOptModeBound  ;/                                  |
|       18h 10h A_UINT8  1  stompDutyCyleVal (SCO cycles to limit ps-poll queuing     |
|                            if stomped)                                              |
|       19h 11h A_UINT8  1  stompDutyCyleMaxVal (firmware increases stomp duty cycle  |
|                            gradually uptill this value on need basis)               |
|       1Ah 12h A_UINT8  1  psPollLatencyFraction (Fraction of idle period, within    |
|                            which additional ps-polls can be queued)                 |
|       1Bh 13h A_UINT8  1  noSCOSlots (Number of SCO Tx/Rx slots. HVx,EV3,2EV3=2)    |
|       1Ch 14h A_UINT8  1  noIdleSlots (Number of Bluetooth idle slots between       |
|                            consecutive SCO Tx/Rx slots. HVx,EV3=4, 2EV3=10)         |
|       1Dh --  A_UINT8  1  reserved8 (maintain word algnment) (uh, really?)          |
|       --  15h A_UINT8  1  scoOptOffRssi (RSSI value below which we go to ps poll)   |
|       --  16h A_UINT8  1  scoOptOnRssi (RSSI value above which we reenter opt mode) |
|       --  17h A_UINT8  1  scoOptRtsCount                                            |
|      when paramType=2=BT_PARAM_A2DP: ;whatever (BT_PARAMS_A2DP)                     |
|       00h 00h A_UINT32 4  a2dpWlanUsageLimit (MAX time firmware uses the medium for |
|                            wlan, after it identifies the idle time, default=30 ms)  |
|       04h 04h A_UINT32 4  a2dpBurstCntMin (Minimum number of bluetooth data frames  |
|                            to replenish Wlan Usage limit, default 3)                |
|       08h 08h A_UINT32 4  a2dpDataRespTimeout                                       |
|       0Ch 0Ch A_UINT32 4  a2dpOptFlags (A2DP Option flags)                          |
|       10h --  A_UINT32 4  p2lrpOptModeBound     ;\PacketToLowRatePacketRatio's      
|       14h --  A_UINT32 4  p2lrpNonOptModeBound  ;/                                  |
|       18h --  A_UINT16 2  reserved16 (maintain word alignment)                      |
|       1Ah 10h A_UINT8  1  isCoLocatedBtRoleMaster                                   |
|       1Bh --  A_UINT8  1  reserved8 (maintain word alignment)                       |
|       1Ch --  PAD      2  undefined/padding                                         |
|       --  11h A_UINT8  1  a2dpOptOffRssi (RSSI value below which we go to ps poll)  |
|       --  12h A_UINT8  1  a2dpOptOnRssi(RSSI value above which we reenter opt mode) |
|       --  13h A_UINT8  1  a2dpOptRtsCount                                           |
|       --  14h PAD      4  undefined/padding                                         |
|      when paramType=3=BT_PARAM_ANTENNA_CONFIG:                                      |
|       00h 00h A_UINT8  1   antType          aka BT_ANT_FRONTEND_CONFIG              |
|       01h --  PAD      1Dh undefined/padding                                        |
|       --  01h PAD      17h undefined/padding                                        |
|      when paramType=4=BT_PARAM_COLOCATED_BT_DEVICE:                                 |
|       00h 00h A_UINT8  1   coLocatedBtDev   aka BT_COLOCATED_DEV_TYPE               |
|       01h --  PAD      1Dh undefined/padding                                        |
|       --  01h PAD      17h undefined/padding                                        |
|      when paramType=5=BT_PARAM_ACLCOEX: ;whatever (BT_PARAMS_ACLCOEX)               |
|       ;During BT ftp/ BT OPP or any another data based acl profile on bluetooth     |
|       ;(non a2dp).                                                                  |
|       00h 00h A_UINT32 4   aclWlanMediumUsageTime (Wlan usage time during           |
|                             Acl (non-a2dp) coexistence, default=30 ms)              |
|       04h 04h A_UINT32 4   aclBtMediumUsageTime (Bt usage time during               |
|                             acl coexistence, default=30 ms)                         |
|       08h 08h A_UINT32 4   aclDataRespTimeout                                       |
|       0Ch 0Ch A_UINT32 4   aclDetectTimeout (ACL coexistence enabled if we get      |
|                             10 Pkts in X ms, default=100 ms)                        |
|       10h 10h A_UINT32 4   aclmaxPktCnt (No of ACL pkts to receive before           |
|                             enabling ACL coex)                                      |
|       14h --  PAD      0Ah undefined/padding                                        |
|       --  14h PAD      4   undefined/padding                                        |
|      when paramType=6=BT_PARAM_11A_SEPARATE_ANT:                                    |
|       00h 00h UNKNOWN  ?   unknown (maybe same as antType ?)                        |
|       xxh --  PAD      ..  undefined/padding                                        |
|       --  xxh PAD      ..  undefined/padding                                        |
|      and, in all cases:                                                             |
|       1Eh 18h A_UINT8  1   paramType                                                |
+-------------------------------------------------------------------------------------+
```


Values for \"scoOptFlags\" and \"a2dpOptFlags\":

```
+----------------------------------------------------------------------------+
|       Bit0       Allow Close Range Optimization             ;\all versions 
|       Bit1       Force awake during close range             ;/             |
|       Bit2       If set use (host supplied) threshold       ;\Newer AR6002 
|       Bit3..23   Unused                                     ;/from 2008    |
|       Bit2       If set use host supplied RSSI for OPT      ;\             
|       Bit3       If set use host supplied RTS COUNT for OPT ; Newer AR6002 |
|       Bit4..7    Unused                                     ; from 2010    |
|       Bit8..15   Low Data Rate Min Cnt                      ;              |
|       Bit16..23  Low Data Rate Max Cnt                      ;/             |
|       Bit24..31  Undocumented (unused?)                     ;-all versions |
+----------------------------------------------------------------------------+
```

PacketToLowRatePacketRatio\'s (p2lrp) entries (in code from 2008 only):

```
+--------------------------------------------------------------------------+
|       p2lrpOptModeBound:    Minimum ratio required to STAY IN opt mode   |
|       p2lrpNonOptModeBound: Minimum ratio required to SWITCH TO opt mode |
+--------------------------------------------------------------------------+
```




