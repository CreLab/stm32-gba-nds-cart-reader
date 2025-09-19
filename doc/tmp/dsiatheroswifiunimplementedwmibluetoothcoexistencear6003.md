# DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence (AR6003)


### WMIcmd(003Bh) - WMI_SET_BT_STATUS_CMD ;AR6002 Bluetooth Coexistence only?
This command does maybe exist for AR6003 too (conflicting comments claim that it is for AR6002 only, or for both AR6002 and AR6003). See \"Newer AR6002\" description for details.
Also possible that it\'s replaced by \"WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD\".

### WMIcmd(003Ch) - WMI_SET_BT_PARAMS_CMD ;AR6002 Bluetooth Coexistence only?
This command is used for AR6002 only. On AR6003, it\'s replaced by the new commands described below:

### WMIcmd(F02Ah) - WMI_SET_BTCOEX_FE_ANT_CMD
Parameters:

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT8  1  btcoexFeAntType                                            |
|                         1 - WMI_BTCOEX_FE_ANT_SINGLE for single antenna front end |
|                         2 - WMI_BTCOEX_FE_ANT_DUAL for dual antenna front end     |
|                             (for isolations less 35dB, for higher isolation there |
|                             is not need to pass this command).                    |
|                             (not implemented)                                     |
+-----------------------------------------------------------------------------------+
```

WMI_BTCOEX_FE_ANT_TYPE values:

```
+-----------------------------------------------------------------------+
|       WMI_BTCOEX_NOT_ENABLED          = 0                             |
|       WMI_BTCOEX_FE_ANT_SINGLE        = 1                             |
|       WMI_BTCOEX_FE_ANT_DUAL          = 2                             |
|       WMI_BTCOEX_FE_ANT_DUAL_HIGH_ISO = 3                             |
|       WMI_BTCOEX_FE_ANT_BYPASS_MODE   = 4                             |
|       WMI_BTCOEX_FE_ANT_COMBINE_MODE  = 5                             |
+-----------------------------------------------------------------------+
```

Indicates front end antenna configuration. This command needs to be issued right after initialization and after WMI_SET_BTCOEX_COLOCATED_BT_DEV_CMD. AR6003 enables coexistence and antenna switching based on the configuration.

### WMIcmd(F02Bh) - WMI_SET_BTCOEX_COLOCATED_BT_DEV_CMD
Parameters:

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT8  1  btcoexCoLocatedBTdev;   1 - Qcom BT (3 -wire PTA)        |
|                                                2 - CSR BT  (3 wire PTA)         |
|                                                3 - Atheros 3001 BT (3 wire PTA) |
|                                                4 - STE bluetooth (4-wire ePTA)  |
|                                                5 - Atheros 3002 BT (4-wire MCI) |
|                                                default=3 (Atheros 3001 BT )     |
+---------------------------------------------------------------------------------+
```

Indicate the bluetooth chip to the firmware. Firmware can have different algorithm based bluetooth chip type. Based on bluetooth device, different coexistence protocol would be used.

### WMIcmd(F02Ch) - WMI_SET_BTCOEX_SCO_CONFIG_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       --------------- BTCOEX_SCO_CONFIG scoConfig;                                  |
|       00h  A_UINT32 4  scoSlots (Number of SCO Tx/Rx slots: HVx,EV3,2EV3 = 2)       |
|       04h  A_UINT32 4  scoIdleSlots (Number of Bluetooth idle slots between         |
|                         consecutive SCO Tx/Rx slots: HVx,EV3 = 4, 2EV3 = 10)        |
|       08h  A_UINT32 4  scoFlags;  SCO Options Flags:                                |
|                                   Bit0   Allow Close Range Optimization             |
|                                   Bit1   Is EDR capable or Not                      |
|                                   Bit2   IS Co-located Bt role Master               |
|                                   Bit3   Firmware determines the periodicity of SCO |
|       0Ch  A_UINT32 4  linkId (applicable to STE-BT - not used)                     |
|       --------------- BTCOEX_PSPOLLMODE_SCO_CONFIG scoPspollConfig;                 |
|       10h  A_UINT32 4  scoCyclesForceTrigger (Number SCO cycles after which         |
|                         force a pspoll, default=10)                                 |
|       14h  A_UINT32 4  scoDataResponseTimeout (Timeout Waiting for Downlink pkt     |
|                         in response for ps-poll, default=20 ms)                     |
|       18h  A_UINT32 4  scoStompDutyCyleVal (not implemented)                        |
|       1Ch  A_UINT32 4  scoStompDutyCyleMaxVal (not implemented)                     |
|       20h  A_UINT32 4  scoPsPollLatencyFraction (Fraction of idle period, within    |
|                         which additional ps-polls can be queued                     |
|                           1 - 1/4 of idle duration                                  |
|                           2 - 1/2 of idle duration                                  |
|                           3 - 3/4 of idle duration                                  |
|                           default=2 (1/2)                                           |
|       --------------- BTCOEX_OPTMODE_SCO_CONFIG scoOptModeConfig;                   |
|       24h  A_UINT32 4  scoStompCntIn100ms (max number of SCO stomp in 100ms         |
|                         allowed in opt mode. If exceeds the configured value,       |
|                         switch to ps-poll mode, default=3)                          |
|       28h  A_UINT32 4  scoContStompMax (max number of continous stomp allowed in    |
|                         opt mode. if excedded switch to pspoll mode, default=3)     |
|       2Ch  A_UINT32 4  scoMinlowRateMbps (Low rate threshold)                       |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|       30h  A_UINT32 4  scoLowRateCnt (number of low rate pkts (< scoMinlowRateMbps) |
|                         allowed in 100 ms. If exceeded switch/stay to ps-poll mode, |
|                         lower stay in opt mode, default=36)                         |
|       34h  A_UINT32 4  scoHighPktRatio "(Total Rx pkts in 100 ms + 1)/((Total tx    |
|                         pkts in 100 ms - No of high rate pkts in 100 ms) + 1) in    |
|                         100 ms"                                                     |
|                         if exceeded switch/stay in opt mode and if lower            |
|                         switch/stay in pspoll mode.                                 |
|                         default=5 (80% of high rates)                               |
|       38h  A_UINT32 4  scoMaxAggrSize (Max number of Rx subframes allowed in this   |
|                         mode. (Firmware re-negogiates max number of aggregates if   |
|                         it was negogiated to higher value, default=1,               |
|                         Recommended value Basic rate headsets = 1, EDR (2-EV3) =4.  |
|       --------------- BTCOEX_WLANSCAN_SCO_CONFIG scoWlanScanConfig;                 |
|       3Ch  A_UINT32 4  scanInterval;                                                |
|       40h  A_UINT32 4  maxScanStompCnt;                                             |
+-------------------------------------------------------------------------------------+
```

Configure SCO parameters. These parameters would be used whenever firmware is indicated of (e)SCO profile on bluetooth (via WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD).
Configration of BTCOEX_SCO_CONFIG data structure are common configuration and applies ps-poll mode and opt mode.
Ps-poll Mode - Station is in power-save and retrieves downlink data between sco gaps.
Opt Mode - station is in awake state and access point can send data to station any time.
BTCOEX_PSPOLLMODE_SCO_CONFIG - Configuration applied only during ps-poll mode.
BTCOEX_OPTMODE_SCO_CONFIG - Configuration applied only during opt mode.

```
+-----------------------------------------------------------------------+
|       Aliases for "scoFlags":                                         |
|       #define WMI_SCO_CONFIG_FLAG_ALLOW_OPTIMIZATION   (1 << 0)       |
|       #define WMI_SCO_CONFIG_FLAG_IS_EDR_CAPABLE       (1 << 1)       |
|       #define WMI_SCO_CONFIG_FLAG_IS_BT_MASTER         (1 << 2)       |
|       #define WMI_SCO_CONFIG_FLAG_FW_DETECT_OF_PER     (1 << 3)       |
+-----------------------------------------------------------------------+
```


### WMIcmd(F02Dh) - WMI_SET_BTCOEX_A2DP_CONFIG_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       --------------- BTCOEX_A2DP_CONFIG a2dpConfig;                                |
|       00h  A_UINT32 4  a2dpFlags;  2DP Option flags:                                |
|                                     Bit0   Allow Close Range Optimization           |
|                                     Bit1   IS EDR capable                           |
|                                     Bit2   IS Co-located Bt role Master             |
|                                     Bit3   a2dp traffic is high priority            |
|                                     Bit4   Fw detect the role of bluetooth.         |
|       04h  A_UINT32 4  linkId (Applicable only to STE-BT - not used)                |
|       --------------- BTCOEX_PSPOLLMODE_A2DP_CONFIG a2dppspollConfig;               |
|       08h  A_UINT32 4  a2dpWlanMaxDur (MAX time firmware uses the medium for        |
|                         wlan, after it identifies the idle time, default=30 ms)     |
|       0Ch  A_UINT32 4  a2dpMinBurstCnt (Minimum number of bluetooth data frames     |
|                         to replenish Wlan Usage limit, default=3)                   |
|       10h  A_UINT32 4  a2dpDataRespTimeout (Max duration firmware waits for         |
|                         downlink by stomping on  bluetooth after ps-poll is         |
|                         acknowledged, default=20 ms)                                |
|       --------------- BTCOEX_OPTMODE_A2DP_CONFIG a2dpOptConfig;                     |
|       14h  A_UINT32 4  a2dpMinlowRateMbps (Low rate threshold)                      |
|       18h  A_UINT32 4  a2dpLowRateCnt (number of low rate pkts                      |
|                         (<a2dpMinlowRateMbps) allowed in 100 ms.                    |
|                         If exceeded switch/stay to ps-poll mode, lower stay in      |
|                         opt mode, default=36)                                       |
|       1Ch  A_UINT32 4  a2dpHighPktRatio "(Total Rx pkts in 100 ms + 1)/             |
|                         ((Total tx pkts in 100 ms - No of high rate pkts in 100 ms) |
|                         + 1) in 100 ms",    if exceeded switch/stay in opt mode and |
|                         if lower switch/stay in pspoll mode.                        |
|                         default=5 (80% of high rates)                               |
|       20h  A_UINT32 4  a2dpMaxAggrSize (Max number of Rx subframes allowed in this  |
|                         mode. (Firmware re-negogiates max number of aggregates if   |
|                         it was negogiated to higher value, default=1.               |
|                         Recommended value Basic rate headsets = 1, EDR (2-EV3) =8)  |
|       24h  A_UINT32 4  a2dpPktStompCnt (number of a2dp pkts that can be stomped     |
|                         per burst, default=6)                                       |
+-------------------------------------------------------------------------------------+
```

Configure A2DP profile parameters. These parameters would be used whenver firmware is indicated of A2DP profile on bluetooth (via WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD).
Configuration of BTCOEX_A2DP_CONFIG data structure are common configuration and applies to ps-poll mode and opt mode.
Ps-poll Mode - Station is in power-save and retrieves downlink data between a2dp data bursts.
Opt Mode - station is in power save during a2dp bursts and awake in the gaps.
BTCOEX_PSPOLLMODE_A2DP_CONFIG - Configuration applied only during ps-poll mode.
BTCOEX_OPTMODE_A2DP_CONFIG - Configuration applied only during opt mode.

```
+-----------------------------------------------------------------------+
|       Aliases for "a2dpFlags":                                        |
|       #define WMI_A2DP_CONFIG_FLAG_ALLOW_OPTIMIZATION    (1 << 0)     |
|       #define WMI_A2DP_CONFIG_FLAG_IS_EDR_CAPABLE        (1 << 1)     |
|       #define WMI_A2DP_CONFIG_FLAG_IS_BT_ROLE_MASTER     (1 << 2)     |
|       #define WMI_A2DP_CONFIG_FLAG_IS_A2DP_HIGH_PRI      (1 << 3)     |
|       #define WMI_A2DP_CONFIG_FLAG_FIND_BT_ROLE          (1 << 4)     |
+-----------------------------------------------------------------------+
```


### WMIcmd(F02Eh) - WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|       --------------- BTCOEX_ACLCOEX_CONFIG aclCoexConfig;                          |
|       00h A_UINT32 4  aclWlanMediumDur (Wlan usage time during Acl (non-a2dp)       |
|                        coexistence, default=30 ms)                                  |
|       04h A_UINT32 4  aclBtMediumDur (Bt usage time during acl coexistence,         |
|                        default=30 ms)                                               |
|       08h A_UINT32 4  aclDetectTimeout (BT activity observation time limit.         |
|                        In this time duration, number of bt pkts are counted.        |
|                        If the Cnt reaches "aclPktCntLowerLimit" value for           |
|                        "aclIterToEnableCoex" iteration continuously, firmware gets  |
|                        into ACL coexistence mode. Similarly, if bt traffic count    |
|                        during ACL coexistence has not reached "aclPktCntLowerLimit" |
|                        continuously for "aclIterToEnableCoex", then ACL coexistence |
|                        is disabled, default=100 ms)                                 |
|       0Ch A_UINT32 4  aclPktCntLowerLimit (Acl Pkt Cnt to be received in duration   |
|                        of "aclDetectTimeout" for "aclIterForEnDis" times to         |
|                        enabling ACL coex. Similar logic is used to disable acl      |
|                        coexistence. (If "aclPktCntLowerLimit" cnt of acl pkts       |
|                        are not seen by the for "aclIterForEnDis" then acl           |
|                        coexistence is disabled), default=10)                        |
|       10h  A_UINT32 4  aclIterForEnDis (number of Iteration of                      |
|                         "aclPktCntLowerLimit" for Enabling and Disabling Acl        |
|                         Coexistence, default=3)                                     |
|       14h A_UINT32 4  aclPktCntUpperLimit (This is upperBound limit, if there is    |
|                         more than "aclPktCntUpperLimit" seen in "aclDetectTimeout", |
|                         ACL coexistence is enabled right away, default=15)          |
|       18h A_UINT32 4  aclCoexFlags   A2DP Option flags:                             |
|                                      Bit0  Allow Close Range Optimization           |
|                                      Bit1  disable Firmware detection               |
|                            (Currently supported configuration is aclCoexFlags=0)    |
|       1Ch A_UINT32 4  linkId;           ;Applicable only for STE-BT - not used      |
|       --------------- BTCOEX_PSPOLLMODE_ACLCOEX_CONFIG aclCoexPspollConfig;         |
|       20h  A_UINT32 4  aclDataRespTimeout (Max duration firmware waits for downlink |
|                         by stomping on bluetooth after ps-poll is acknowledged,     |
|                         default=20 ms)                                              |
|       --------------- BTCOEX_OPTMODE_ACLCOEX_CONFIG aclCoexOptConfig;               |
|       24h  A_UINT32 4  aclCoexMinlowRateMbps        ;\                              
|       28h  A_UINT32 4  aclCoexLowRateCnt            ;                               |
|       2Ch  A_UINT32 4  aclCoexHighPktRatio          ; Not implemented yet           |
|       30h  A_UINT32 4  aclCoexMaxAggrSize           ;                               |
|       34h  A_UINT32 4  aclPktStompCnt               ;/                              |
+-------------------------------------------------------------------------------------+
```

Configure non-A2dp ACL profile parameters.The starts of ACL profile can either be indicated via WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD or enabled via firmware detection which is configured via \"aclCoexFlags\".
Configration of BTCOEX_ACLCOEX_CONFIG data structure are common configuration and applies ps-poll mode and opt mode.
Ps-poll Mode - Station is in power-save and retrieves downlink data during wlan medium.
Opt Mode - station is in power save during bluetooth medium time and awake during wlan duration.

```
+-----------------------------------------------------------------------+
|                  (Not implemented yet)    (uh, what?)                 |
+-----------------------------------------------------------------------+
```

BTCOEX_PSPOLLMODE_ACLCOEX_CONFIG - Configuration applied only during ps-poll mode.
BTCOEX_OPTMODE_ACLCOEX_CONFIG - Configuration applied only during opt mode.

```
+-----------------------------------------------------------------------+
|       Aliases for "aclCoexFlags":                                     |
|       #define WMI_ACLCOEX_FLAGS_ALLOW_OPTIMIZATION   (1 << 0)         |
|       #define WMI_ACLCOEX_FLAGS_DISABLE_FW_DETECTION (1 << 1)         |
+-----------------------------------------------------------------------+
```


### WMIcmd(F02Fh) - WMI_SET_BTCOEX_BTINQUIRY_PAGE_CONFIG_CMD
Parameters:

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT32 4  btInquiryDataFetchFrequency (The frequency of querying the  |
|                         AP for data (via pspoll) is configured by this parameter,  |
|                         default=10 ms)                                             |
|       04h  A_UINT32 4  protectBmissDurPostBtInquiry (The firmware will continue to |
|                         be in inquiry state for configured duration, after inquiry |
|                         completion. This is to ensure other bluetooth transactions |
|                         (RDP, SDP profiles, link key exchange, etc.) goes through  |
|                         smoothly without wifi stomping, default=10 secs)           |
|       08h  A_UINT32 4  maxpageStomp (Applicable only for STE-BT interface.         |
|                         Currently not used)                                        |
|       0Ch  A_UINT32 4  btInquiryPageFlag (Not used)                                |
+------------------------------------------------------------------------------------+
```

Configuration parameters during bluetooth inquiry and page. Page configuration is applicable only on interfaces which can distinguish page (applicable only for ePTA - STE bluetooth).
Bluetooth inquiry start and end is indicated via WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD. During this the station will be power-save mode.

### WMIcmd(F030h) - WMI_SET_BTCOEX_DEBUG_CMD
Parameters:

```
+-----------------------------------------------------------------------------+
|       00h  A_UINT32 4  btcoexDbgParam1      ;\                              
|       04h  A_UINT32 4  btcoexDbgParam2      ; Used for firmware development |
|       08h  A_UINT32 4  btcoexDbgParam3      ; and debugging                 |
|       0Ch  A_UINT32 4  btcoexDbgParam4      ;                               |
|       10h  A_UINT32 4  btcoexDbgParam5      ;/                              |
+-----------------------------------------------------------------------------+
```


### WMIcmd(F031h) - WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD
Parameters:

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT32 4  btProfileType (1=SCO, 2=A2DP, 3=INQUIRY_PAGE, 4=ACLCOEX) |
|       04h  A_UINT32 4  btOperatingStatus    ;aka BT_STREAM_STATUS on AR6002 ?   |
|       08h  A_UINT32 4  btLinkId                                                 |
+---------------------------------------------------------------------------------+
```

WMI_BTCOEX_BT_PROFILE values:

```
+-----------------------------------------------------------------------+
|       WMI_BTCOEX_BT_PROFILE_SCO          = 1                          |
|       WMI_BTCOEX_BT_PROFILE_A2DP         = 2                          |
|       WMI_BTCOEX_BT_PROFILE_INQUIRY_PAGE = 3                          |
|       WMI_BTCOEX_BT_PROFILE_ACLCOEX      = 4                          |
+-----------------------------------------------------------------------+
```

This command is probably equivalent to WMI_SET_BT_STATUS_CMD on AR6002.

### WMIcmd(F032h) - WMI_GET_BTCOEX_STATS_CMD ;reply WMI_REPORT_BTCOEX_STATS_EVENT
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(F033h) - WMI_GET_BTCOEX_CONFIG_CMD ;reply WMI_REPORT_BTCOEX_CONFIG_EV.
Parameters:

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT32 4  btProfileType (1=SCO, 2=A2DP, 3=INQUIRY_PAGE, 4=ACLCOEX) |
|       04h  A_UINT32 4  linkId (not used) (reserved/dummy?)                      |
+---------------------------------------------------------------------------------+
```

Command to firmware to get configuration parameters of the bt profile reported via WMI_BTCOEX_CONFIG_EVENTID.

### WMIevent(1029h, or formerly 1028h, or 1027h) - WMI_REPORT_BTCOEX_CONFIG_EVENT
Event Data:

```
+-----------------------------------------------------------------------------------+
|       00h A_UINT32 4  btProfileType (1=SCO, 2=A2DP, 3=INQUIRY_PAGE, 4=ACLCOEX)    |
|       04h A_UINT32 4  linkId (not used)                                           |
|           PREPACK union -- below are same as parameters from corresponding CMD's: |
|       08h ..  WMI_SET_BTCOEX_SCO_CONFIG_CMD            scoConfigCmd;              |
|       08h ..  WMI_SET_BTCOEX_A2DP_CONFIG_CMD           a2dpConfigCmd;             |
|       08h ..  WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMD        aclcoexConfig;             |
|       08h ..  WMI_SET_BTCOEX_BTINQUIRY_PAGE_CONFIG_CMD btinquiryPageConfigCmd;    |
+-----------------------------------------------------------------------------------+
```

Event from firmware to host, sent in response to WMI_GET_BTCOEX_CONFIG_CMD.

### WMIevent(1028h, or formerly 1027h, or 1026h) - WMI_REPORT_BTCOEX_STATS_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       ---------------  BTCOEX_GENERAL_STATS coexStats;                |
|       00h A_UINT32 4  highRatePktCnt;                                 |
|       04h A_UINT32 4  firstBmissCnt;                                  |
|       08h A_UINT32 4  psPollFailureCnt;                               |
|       0Ch A_UINT32 4  nullFrameFailureCnt;                            |
|       10h A_UINT32 4  optModeTransitionCnt;                           |
|       ---------------  BTCOEX_SCO_STATS scoStats;                     |
|       14h A_UINT32 4  scoStompCntAvg;                                 |
|       18h A_UINT32 4  scoStompIn100ms;                                |
|       1Ch A_UINT32 4  scoMaxContStomp;                                |
|       20h A_UINT32 4  scoAvgNoRetries;                                |
|       24h A_UINT32 4  scoMaxNoRetriesIn100ms;                         |
|       ---------------  BTCOEX_A2DP_STATS a2dpStats;                   |
|       28h A_UINT32 4  a2dpBurstCnt;                                   |
|       2Ch A_UINT32 4  a2dpMaxBurstCnt;                                |
|       30h A_UINT32 4  a2dpAvgIdletimeIn100ms;                         |
|       34h A_UINT32 4  a2dpAvgStompCnt;                                |
|       ---------------  BTCOEX_ACLCOEX_STATS aclCoexStats;             |
|       38h A_UINT32 4  aclPktCntInBtTime;                              |
|       3Ch A_UINT32 4  aclStompCntInWlanTime;                          |
|       40h A_UINT32 4  aclPktCntIn100ms;                               |
+-----------------------------------------------------------------------+
```

Used for firmware development and debugging.
Names: WMI_GET_BTCOEX_STATS aka WMI_REPORT_BTCOEX_STATS_EVENT aka WMI_REPORT_BTCOEX_BTCOEX_STATS_EVENT



