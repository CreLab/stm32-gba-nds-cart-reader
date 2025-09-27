# DSi Atheros Wifi - Command Summary


### BMI Command Summary (Bootloader Messaging Interface)

```
+-------------------------------------------------------------------------------------+
|       00h   BMI_NO_COMMAND                             Invalid (ignored)            |
|       01h   BMI_DONE                                   Launch Firmware              |
|       02h   BMI_READ_MEMORY                            Read Memory                  |
|       03h   BMI_WRITE_MEMORY (normal)                  Write Memory                 |
|       03h   BMI_WRITE_MEMORY (with dest=00001234h)     Segmented Write (not in DSi) |
|       04h   BMI_EXECUTE                                Execute                      |
|       05h   BMI_SET_APP_START                          Set App Start                |
|       06h   BMI_READ_SOC_REGISTER                      Read Register                |
|       07h   BMI_WRITE_SOC_REGISTER                     Write Register               |
|       08h   BMI_GET_TARGET_ID aka BMI_GET_TARGET_INFO  Get Version                  |
|       09h   BMI_ROMPATCH_INSTALL                       TCAM/BCAM_xxxxx              |
|       0Ah   BMI_ROMPATCH_UNINSTALL                     TCAM/BCAM_Clr_index_and_xxx  |
|       0Bh   BMI_ROMPATCH_ACTIVATE                      TCAM/BCAM_Set_indices   ;\   
|       0Ch   BMI_ROMPATCH_DEACTIVATE                    TCAM/BCAM_Clr_indices   ;/   |
|       0Dh   BMI_LZ_STREAM_START                        LZ Uncompress Stream Start   |
|       0Eh   BMI_LZ_DATA                                LZ Data Input                |
|       0Fh   BMI_NVRAM_PROCESS ;not implemented in DSi  Invalid (ignored)            |
|       10h..FFFFFFFFh  Unused                           Invalid (ignored)            |
+-------------------------------------------------------------------------------------+
```


### HTC Services/Handshake
After BMI, and before WMI, there is a \"HTC_SERVICES\" handshake with following values:

```
+-----------------------------------------------------------------------+
|       RSVD_SERVICE_GROUP     = 0                                      |
|       WMI_SERVICE_GROUP      = 1                                      |
|       HTC_TEST_GROUP         = 254                                    |
|       HTC_SERVICE_GROUP_LAST = 255                                    |
+-----------------------------------------------------------------------+
```

MAKE_SERVICE_ID(group,index) = group\*100h + index
NOTE: service ID of 0000h is reserved and should never be used

```
+------------------------------------------------------------------------------+
|       HTC_CTRL_RSVD_SVC = MAKE_SERVICE_ID(RSVD_SERVICE_GROUP,1)              |
|       WMI_CONTROL_SVC   = MAKE_SERVICE_ID(WMI_SERVICE_GROUP,0)  ;control     |
|       WMI_DATA_BE_SVC   = MAKE_SERVICE_ID(WMI_SERVICE_GROUP,1)  ;best effort |
|       WMI_DATA_BK_SVC   = MAKE_SERVICE_ID(WMI_SERVICE_GROUP,2)  ;background  |
|       WMI_DATA_VI_SVC   = MAKE_SERVICE_ID(WMI_SERVICE_GROUP,3)  ;video       |
|       WMI_DATA_VO_SVC   = MAKE_SERVICE_ID(WMI_SERVICE_GROUP,4)  ;voice       |
|       WMI_MAX_SERVICES  = 5                                                  |
+------------------------------------------------------------------------------+
```

raw stream service (i.e. flash, tcmd, calibration apps):

```
+-----------------------------------------------------------------------+
|       HTC_RAW_STREAMS_SVC = MAKE_SERVICE_ID(HTC_TEST_GROUP,0)         |
+-----------------------------------------------------------------------+
```

Obscure note: The above services are also known as ACs or ENDPOINTs (whatever that means).

### WMI Command Summary (Wireless Module Interface)

```
+-------------------------------------------------------------------------------------+
|       0001h  WMI_CONNECT_CMD                                                        |
|       0002h  WMI_RECONNECT_CMD                                                      |
|       0003h  WMI_DISCONNECT_CMD                                                     |
|       0004h  WMI_SYNCHRONIZE_CMD                                                    |
|       0005h  WMI_CREATE_PSTREAM_CMD      ;aka WMI_CRE_PRIORITY_STREAM               |
|       0006h  WMI_DELETE_PSTREAM_CMD      ;aka WMI_DEL_PRIORITY_STREAM               |
|       0007h  WMI_START_SCAN_CMD                                                     |
|       0008h  WMI_SET_SCAN_PARAMS_CMD                                                |
|       0009h  WMI_SET_BSS_FILTER_CMD      ;aka WMI_BSS_FILTER_CMD                    |
|       000Ah  WMI_SET_PROBED_SSID_CMD                                                |
|       000Bh  WMI_SET_LISTEN_INT_CMD                                                 |
|       000Ch  WMI_SET_BMISS_TIME_CMD                                                 |
|       000Dh  WMI_SET_DISC_TIMEOUT_CMD    ;aka WMI_SET_DISCONNECT_TIMEOUT            |
|       000Eh  WMI_GET_CHANNEL_LIST_CMD    ;reply 000Eh  ;aka WMI_CHANNEL_LIST        |
|       000Fh  WMI_SET_BEACON_INT_CMD                                                 |
|       0010h  WMI_GET_STATISTICS_CMD      ;reply WMI_REPORT_STATISTICS               |
|       0011h  WMI_SET_CHANNEL_PARAMS_CMD  ;aka WMI_CHANNEL_PARAMS_CMD                |
|       0012h  WMI_SET_POWER_MODE_CMD      ;aka WMI_POWER_MODE_CMD                    |
|       0013h  WMI_SET_IBSS_PM_CAPS_CMD    ;aka WMI_IBSS_PM_CAPS_CMD                  |
|       0014h  WMI_SET_POWER_PARAMS_CMD    ;aka WMI_POWER_PARAMS_CMD                  |
|       0015h  WMI_SET_POWERSAVE_TIMERS_POLICY_CMD  ;aka WMI_POWERSAVE...             |
|       0016h  WMI_ADD_CIPHER_KEY_CMD                                                 |
|       0017h  WMI_DELETE_CIPHER_KEY_CMD   ;\                                         
|       0018h  WMI_ADD_KRK_CMD             ; ignored dummy commands on DSi            |
|       0019h  WMI_DELETE_KRK_CMD          ;/                                         |
|       001Ah  WMI_SET_PMKID_CMD                                                      |
|       001Bh  WMI_SET_TX_PWR_CMD                                                     |
|       001Ch  WMI_GET_TX_PWR_CMD          ;aka WMI_TX_PWR ;reply 001Ch               |
|       001Dh  WMI_SET_ASSOC_INFO_CMD                                                 |
|       001Eh  WMI_ADD_BAD_AP_CMD                                                     |
|       001Fh  WMI_DELETE_BAD_AP_CMD                                                  |
|       0020h  WMI_SET_TKIP_COUNTERMEASURES_CMD                                       |
|       0021h  WMI_RSSI_THRESHOLD_PARAMS_CMD                                          |
|       0022h  WMI_TARGET_ERROR_REPORT_BITMASK_CMD                                    |
|       0023h  WMI_SET_ACCESS_PARAMS_CMD                                              |
|       0024h  WMI_SET_RETRY_LIMITS_CMD                                               |
|       0025h  WMI_SET_OPT_MODE_CMD                                                   |
|       0026h  WMI_OPT_TX_FRAME_CMD                                                   |
|       0027h  WMI_SET_VOICE_PKT_SIZE_CMD                                             |
|       0028h  WMI_SET_MAX_SP_LEN_CMD                                                 |
|       0029h  WMI_SET_ROAM_CTRL_CMD                                                  |
|       002Ah  WMI_GET_ROAM_TBL_CMD ;aka REPORT_ROAM_TBL,TARGET_ROAM_TBL ;reply 100Fh |
|       002Bh  WMI_GET_ROAM_DATA_CMD       ;reply 1015h ?    ;\                       
|       002Ch  WMI_ENABLE_RM_CMD                             ; not implemented in DSi |
|       002Dh  WMI_SET_MAX_OFFHOME_DURATION_CMD              ;/                       |
|       002Eh  WMI_EXTENSION_CMD   ;prefix for WMIX "Non-wireless extensions"...      |
|       002Eh:2001h  WMIX_DSETOPEN_REPLY_CMD ;reply to 3001h ;\not implemented in DSi 
|       002Eh:2002h  WMIX_DSETDATA_REPLY_CMD ;reply to 3003h ;/                       |
|       002Eh:2003h  WMIX_GPIO_OUTPUT_SET_CMD   ;reply=3006h          ;\              
|       002Eh:2004h  WMIX_GPIO_INPUT_GET_CMD    ;reply=3005h          ;               |
|       002Eh:2005h  WMIX_GPIO_REGISTER_SET_CMD ;reply=3006h, too     ; GPIO          |
|       002Eh:2006h  WMIX_GPIO_REGISTER_GET_CMD ;reply=3005h, too     ;               |
|       002Eh:2007h  WMIX_GPIO_INTR_ACK_CMD ;reply to 3004h           ;/              |
|       002Eh:2008h  WMIX_HB_CHALLENGE_RESP_CMD ;reply=3007h          ;-HB=heartbeat  |
|       002Eh:2009h  WMIX_DBGLOG_CFG_MODULE_CMD                                       |
|       002Eh:200Ah  WMIX_PROF_CFG_CMD                       ;\                       
|       002Eh:200Bh  WMIX_PROF_ADDR_SET_CMD                  ;                        |
|       002Eh:200Ch  WMIX_PROF_START_CMD                     ; not implemented in DSi |
|       002Eh:200Dh  WMIX_PROF_STOP_CMD                      ;                        |
|       002Eh:200Eh  WMIX_PROF_COUNT_GET_CMD ;reply 3009h    ;/                       |
|       002Fh  WMI_SNR_THRESHOLD_PARAMS_CMD                                           |
|       0030h  WMI_LQ_THRESHOLD_PARAMS_CMD                                            |
|       0031h  WMI_SET_LPREAMBLE_CMD                                                  |
|       0032h  WMI_SET_RTS_CMD                                                        |
|       0033h  WMI_CLR_RSSI_SNR_CMD                                                   |
|       0034h  WMI_SET_FIXRATES_CMD   ;aka WMI_FIX_RATES_CMD                          |
|       0035h  WMI_GET_FIXRATES_CMD        ;reply 0035h                               |
|       0036h  WMI_SET_AUTH_MODE_CMD  ;aka WMI_SET_RECONNECT_AUTH_MODE_CMD            |
+-------------------------------------------------------------------------------------+
```

;below not in AR6001

```
+-------------------------------------------------------------------------------------+
|       0037h  WMI_SET_REASSOC_MODE_CMD                                               |
|       0038h  WMI_SET_WMM_CMD                                                        |
|       0039h  WMI_SET_WMM_TXOP_CMD                                                   |
|      ;NOT!   WMI_SET_QOS_SUPP_CMD     ;<-- this NOT here!                           |
|       003Ah  WMI_TEST_CMD                                  ;-not implemented in DSi |
|       003Bh  WMI_SET_BT_STATUS_CMD    ;\AR6002 Bluetooth Coexistence only?          
|       003Ch  WMI_SET_BT_PARAMS_CMD    ;/                                            |
|       003Dh  WMI_SET_KEEPALIVE_CMD                                                  |
|       003Eh  WMI_GET_KEEPALIVE_CMD       ;reply 003Eh                               |
|       003Fh  WMI_SET_APPIE_CMD  ;aka SET_APP_IE                                     |
|       0040h  WMI_GET_APPIE_CMD  ;aka GET_APP_IE ;reply=?   ;-not implemented in DSi |
|       0041h  WMI_SET_WSC_STATUS_CMD   ;aka WSC_REG                                  |
|       0042h  WMI_SET_HOST_SLEEP_MODE_CMD                   ;\                       
|       0043h  WMI_SET_WOW_MODE_CMD                          ;                        |
|       0044h  WMI_GET_WOW_LIST_CMD        ;reply=1018h      ; Wake on Wireless (WOW) |
|       0045h  WMI_ADD_WOW_PATTERN_CMD                       ;                        |
|       0046h  WMI_DEL_WOW_PATTERN_CMD                       ;/                       |
|      ;below four as of "AR6kSDK.build_sw.18/include/wmi.h" (from 2006)              |
|      ;0047h  WMI_SET_MAC_ADDRESS_CMD (later moved to F003h)                         |
|      ;0048h  WMI_SET_AKMP_PARAMS_CMD (later moved to F004h)                         |
|      ;0049h  WMI_SET_PMKID_LIST_CMD  (later moved to F005h)                         |
|      ;004Ah  WMI_GET_PMKID_LIST_CMD  (later moved to F006h)                         |
|      ;below two are almost always supported (but DSi is somewhat different)         |
|      ;0047h  WMI_SET_FRAMERATES_CMD    ;aka WMI_FRAME_RATES_CMD  ;-cmd 48h on DSi!  |
|      ;0048h  WMI_SET_AP_PS_CMD         ;aka WMI_AP_PS_CMD        ;-not on DSi       |
+-------------------------------------------------------------------------------------+
```

Special DSi commands:

```
+------------------------------------------------------------------------------------+
|       0047h  WMI_SET_HB_CHALLENGE_RESP_PARAMS_CMD                                  |
|       0048h  WMI_SET_FRAMERATES_CMD    ;aka WMI_FRAME_RATES_CMD  ;-cmd 48h on DSi! |
|       0049h  WMI_HOST_EXIT_NOTIFY_CMD  ;special DSi/3DS command                    |
+------------------------------------------------------------------------------------+
```

Special 3DS commands (for Type4 firmware):

```
+-------------------------------------------------------------------------------------+
|       004Ah  WMI_AP_HIDDEN_SSID_CMD                         ;01h bytes (1)          |
|       004Bh  WMI_AP_SET_NUM_STA_CMD aka WMI_AP_NUM_STA_CMD  ;01h bytes (1)          |
|       004Ch  WMI_AP_ACL_POLICY_CMD                          ;01h bytes (1)          |
|       004Dh  WMI_AP_ACL_MAC_LIST_CMD aka WMI_AP_ACL_MAC_CMD ;09h bytes (1+1+6+1)    |
|       004Eh  WMI_AP_CONFIG_COMMIT_CMD                       ;34h bytes (..)         |
|       004Fh  WMI_AP_SET_MLME_CMD                            ;09h bytes (6+2+1)      |
|       0050h  WMI_AP_SET_PVB_CMD     ;ignored on 3DS         ;06h bytes (ignored)    |
|       0051h  WMI_AP_CONN_INACT_CMD                          ;04h bytes (4)          |
|       0052h  WMI_AP_PROT_SCAN_TIME_CMD                      ;08h bytes (4+4)        |
|       0053h  WMI_?                                      ;01h bytes (1)              |
|       0054h  N/A                                                                    |
|       0055h  WMI_?                                      ;04h bytes (2+2)            |
|       0056h  WMI_ignored_?                              ;01h bytes (ignored)        |
|       0057h  WMI_?  ;with EVENT_1022h                   ;00h bytes                  |
|       0058h  WMI_?     <-- with optional params?        ;var       (2+2+1+1+N)      |
|       0059h  WMI_?       ;only lower 8bit used          ;04h bytes (4; only 1 used) |
|       005Ah  WMI_?                                      ;01h bytes (1)              |
|       005Bh  WMI_?                                      ;04h bytes (2+1+1)          |
|       005Ch  WMI_?                                      ;04h bytes (1+3)            |
|       005Dh  WMI_?                                      ;0Ah bytes (1+1+2+1+1+2+2)  |
|       005Eh  WMI_?                                      ;01h bytes (1)              |
|       005Fh  WMI_?                                      ;04h bytes (4)              |
+-------------------------------------------------------------------------------------+
```

Special 3DS commands (for Type5 firmware):

```
+-----------------------------------------------------------------------+
|       0060h  WMI_?                             ;3Ah bytes             |
|       0061h  WMI_?                             ;28h bytes             |
|       0062h  WMI_?                             ;12h bytes             |
|       0063h  WMI_?                             ;02h bytes             |
|       0064h  WMI_?                             ;03h bytes             |
|       0065h  WMI_?                             ;07h bytes             |
|       0066h  WMI_?                             ;07h bytes             |
|       0067h  WMI_?                             ;03h bytes             |
|       0068h  WMI_?  ;can be with EVENT_1023h   ;01h bytes             |
|       0069h  WMI_?                             ;00h bytes             |
|       006Ah  WMI_?                             ;00h bytes             |
|       006Bh  WMI_?                             ;01h bytes             |
|       006Ch  WMI_?                             ;06h bytes             |
|       006Dh  WMI_?  ;with EVENT_1026h          ;00h bytes             |
|       006Eh  WMI_?                             ;01h bytes             |
|       006Fh  WMI_?                             ;06h bytes             |
|       0070h  WMI_?                             ;01h bytes             |
|       0071h  WMI_?                             ;08h bytes             |
|       0072h  WMI_?                             ;02h bytes             |
|       0073h  WMI_?  ;with EVENT_1027h          ;01h bytes             |
+-----------------------------------------------------------------------+
```

Newer commands

```
+-------------------------------------------------------------------------------------+
|       0049h  WMI_SET_QOS_SUPP_CMD  ;<-- this shall be HERE ;\                       
|       004Ah  WMI_SET_IE_CMD  ;new cmd from 2012            ; not implemented in DSi |
|       08xxh  WILOCITY types         ;\wil6210 stuff        ;                        
|       09xxh  Performance monitoring ;/                     ;/                       |
|       8000h  WMI_THIN_RESERVED_START                       ;\                       
|       8000h  WMI_THIN_CONFIG_CMD                           ;                        |
|       8001h  WMI_THIN_SET_MIB_CMD                          ; not implemented in DSi |
|       8002h  WMI_THIN_GET_MIB_CMD ;reply=8001h             ; (thin commands         |
|       8003h  WMI_THIN_JOIN_CMD      ;\newer                ; from wmi_thin.h)       
|       8004h  WMI_THIN_CONNECT_CMD   ; versions             ;                        |
|       8005h  WMI_THIN_RESET_CMD     ;/only                 ;                        |
|       8FFFh  WMI_THIN_RESERVED_END                         ;/                       |
+-------------------------------------------------------------------------------------+
```

Developer commands

```
+-------------------------------------------------------------------------------------+
|       F000h  WMI_SET_BITRATE_CMD    ;aka WMI_BIT_RATE_CMD                           |
|       F001h  WMI_GET_BITRATE_CMD                         ;reply=F001h               |
|       F002h  WMI_SET_WHALPARAM_CMD  ;aka WHAL_PARAMCMD                              |
|       F003h  WMI_SET_MAC_ADDRESS_CMD   ;formerly 0047h     ;-not implemented in DSi |
|       F004h  WMI_SET_AKMP_PARAMS_CMD   ;formerly 0048h                              |
|       F005h  WMI_SET_PMKID_LIST_CMD    ;formerly 0049h                              |
|       F006h  WMI_GET_PMKID_LIST_CMD    ;formerly 004Ah   ;reply 1019h               |
+-------------------------------------------------------------------------------------+
```

Below stuff (F007h..F05Eh) is not implemented in DSi\...

```
+-------------------------------------------------------------------------------------+
|       F007h  WMI_ABORT_SCAN_CMD                                                     |
|       F008h  WMI_SET_TARGET_EVENT_REPORT_CMD                                        |
|       F009h  WMI_UNUSED1 or WMI_PYXIS_CONFIG_CMD    ;\Unused (or Pyxis specific     
|       F00Ah  WMI_UNUSED2 or WMI_PYXIS_OPERATION_CMD ;/commands)                     |
|       F00Bh  WMI_AP_HIDDEN_SSID_CMD                          ;\                     
|       F00Ch  WMI_AP_SET_NUM_STA_CMD aka WMI_AP_NUM_STA_CMD   ; AP mode commands     |
|       F00Dh  WMI_AP_ACL_POLICY_CMD                           ;                      |
|       F00Eh  WMI_AP_ACL_MAC_LIST_CMD aka WMI_AP_ACL_MAC_CMD  ; (not on DSi, but     |
|       F00Fh  WMI_AP_CONFIG_COMMIT_CMD                        ; 3DS type4 supports   |
|       F010h  WMI_AP_SET_MLME_CMD                             ; F00Ah..F013h,        |
|       F011h  WMI_AP_SET_PVB_CMD                              ; renumbered to        |
|       F012h  WMI_AP_CONN_INACT_CMD                           ; 004Ah..0052h)        |
|       F013h  WMI_AP_PROT_SCAN_TIME_CMD                       ;                      |
|       F014h  WMI_AP_SET_COUNTRY_CMD ;aka WMI_SET_COUNTRY_CMD ;                      |
|       F015h  WMI_AP_SET_DTIM_CMD                             ;                      |
|       F016h  WMI_AP_MODE_STAT_CMD      ;formerly N/A         ;/                     |
|       F017h  WMI_SET_IP_CMD            ;formerly F016h                      ;\      
|       F018h  WMI_SET_PARAMS_CMD        ;formerly F017h   ;reply=101Fh       ;       |
|       F019h  WMI_SET_MCAST_FILTER_CMD  ;formerly F018h                      ;       |
|       F01Ah  WMI_DEL_MCAST_FILTER_CMD  ;formerly F019h                      ;/      |
|       F01Bh  WMI_ALLOW_AGGR_CMD                                             ;\      
|       F01Ch  WMI_ADDBA_REQ_CMD                                              ;       |
|       F01Dh  WMI_DELBA_REQ_CMD                                              ;       |
|       F01Eh  WMI_SET_HT_CAP_CMD                                             ;       |
|       F01Fh  WMI_SET_HT_OP_CMD                                              ;       |
|       F020h  WMI_SET_TX_SELECT_RATES_CMD                                    ;       |
|       F021h  WMI_SET_TX_SGI_PARAM_CMD                                       ;       |
|       F022h  WMI_SET_RATE_POLICY_CMD                                        ;/      |
|       F023h  WMI_HCI_CMD_CMD aka WMI_HCI_CMD                                ;\      
|       F024h  WMI_RX_FRAME_FORMAT_CMD                                        ;       |
|       F025h  WMI_SET_THIN_MODE_CMD                                          ;       |
|       F026h  WMI_SET_BT_WLAN_CONN_PRECEDENCE_CMD                            ;/      |
|       F027h  WMI_AP_SET_11BG_RATESET_CMD                                    ;\      
|       F028h  WMI_SET_PMK_CMD                                                ;       |
|       F029h  WMI_MCAST_FILTER_CMD                                           ;/      |
|       F02Ah  WMI_SET_BTCOEX_FE_ANT_CMD                      ;\                      
|       F02Bh  WMI_SET_BTCOEX_COLOCATED_BT_DEV_CMD            ;                       |
|       F02Ch  WMI_SET_BTCOEX_SCO_CONFIG_CMD                  ; AR6003                |
|       F02Dh  WMI_SET_BTCOEX_A2DP_CONFIG_CMD                 ; Bluetooth Coexistence |
|       F02Eh  WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMD              ;                       |
|       F02Fh  WMI_SET_BTCOEX_BTINQUIRY_PAGE_CONFIG_CMD       ;                       |
|       F030h  WMI_SET_BTCOEX_DEBUG_CMD                       ;                       |
|       F031h  WMI_SET_BTCOEX_BT_OPERATING_STATUS_CMD         ;                       |
|       F032h  WMI_GET_BTCOEX_STATS_CMD  ;reply=1026h..1028h  ;                       |
|       F033h  WMI_GET_BTCOEX_CONFIG_CMD ;reply=1027h..1029h  ;/                      |
|       F034h  WMI_SET_DFS_ENABLE_CMD        ;aka WMI_SET_DFS_CMD maybe ?   ;\        
|       F035h  WMI_SET_DFS_MINRSSITHRESH_CMD ;aka WMI_SET_DFS_CMD too ??    ; DFS     |
|       F036h  WMI_SET_DFS_MAXPULSEDUR_CMD   ;aka WMI_SET_DFS_CMD too ??    ;         |
|       F037h  WMI_DFS_RADAR_DETECTED_CMD    ;aka WMI_RADAR_DETECTED_CMD    ;/        |
|       F038h  WMI_P2P_SET_CONFIG_CMD                 ;\  ;<-- confirmed to be F038h  
|       F039h  WMI_WPS_SET_CONFIG_CMD   ;P2P related  ;                               |
|       F03Ah  WMI_SET_REQ_DEV_ATTR_CMD ;P2P related  ; P2P CMDS                      |
|       F03Bh  WMI_P2P_FIND_CMD                       ;                               |
|       F03Ch  WMI_P2P_STOP_FIND_CMD                  ;                               |
|       F03Dh  WMI_P2P_GO_NEG_START_CMD               ;                               |
|       F03Eh  WMI_P2P_LISTEN_CMD                     ;/                              |
|       F03Fh  WMI_CONFIG_TX_MAC_RULES_CMD            ;\  ;<-- claimed to be F040h ?  
|       F040h  WMI_SET_PROMISCUOUS_MODE_CMD           ;                               |
|       F041h  WMI_RX_FRAME_FILTER_CMD                ;                               |
|       F042h  WMI_SET_CHANNEL_CMD                    ;/                              |
|       F043h  WMI_WAC_ENABLE_CMD aka WMI_ENABLE_WAC_CMD      ;\                      
|       F044h  WMI_WAC_SCAN_REPLY_CMD                         ; WAC commands          |
|       F045h  WMI_WAC_CTRL_REQ_CMD                           ;/                      |
|       F046h  WMI_SET_DIV_PARAMS_CMD aka WMI_DIV_PARAMS_CMD                          |
|       F047h  WMI_GET_PMK_CMD         ;reply?                ;\                      
|       F048h  WMI_SET_PASSPHRASE_CMD                         ;/                      |
|       F049h  WMI_SEND_ASSOC_RES_CMD      ;aka WMI_SEND_ASSOCRES_CMD     ;\ASSOC     
|       F04Ah  WMI_SET_ASSOC_REQ_RELAY_CMD ;aka WMI_SET_ASSOCREQ_RELAY    ;/          |
+-------------------------------------------------------------------------------------+
```

Below uses entirely different numbering in code from 2010 vs 2012\...

```
+------------------------------------------------------------------------------------+
|       F04Bh or F04Dh WMI_ACS_CTRL_CMD ;aka WMI_ACS_CTRL_MSG  ;-ACS sub-commands    |
|       F04Ch or F052h WMI_SET_EXCESS_TX_RETRY_THRES_CMD                             |
|       F04Dh or N/A   WMI_SET_TBD_TIME_CMD   ;-added for wmiconfig command for TBD  |
|       F04Eh or N/A   WMI_PKTLOG_ENABLE_CMD                ;\Pktlog cmds            
|       F04Fh or N/A   WMI_PKTLOG_DISABLE_CMD               ;/(code from 2012 only)  |
|       F050h or F053h WMI_P2P_GO_NEG_REQ_RSP_CMD           ;\                       
|       F051h or F054h WMI_P2P_GRP_INIT_CMD                 ;                        |
|       F052h or F055h WMI_P2P_GRP_FORMATION_DONE_CMD       ;                        |
|       F053h or F056h WMI_P2P_INVITE_CMD                   ; More P2P commands      |
|       F054h or F057h WMI_P2P_INVITE_REQ_RSP_CMD           ;                        |
|       F055h or F058h WMI_P2P_PROV_DISC_REQ_CMD            ;                        |
|       F056h or F059h WMI_P2P_SET_CMD                      ;/                       |
|       F057h or F04Bh WMI_GET_RFKILL_MODE_CMD                          ;\RFKILL     
|       F058h or F04Ch WMI_SET_RFKILL_MODE_CMD ;aka WMI_RFKILL_MODE_CMD ;/           |
|       F059h or F05Ah WMI_AP_SET_APSD_CMD                  ;\More AP commands       
|       F05Ah or F05Bh WMI_AP_APSD_BUFFERED_TRAFFIC_CMD     ;/                       |
|       F05Bh or F05Ch WMI_P2P_SDPD_TX_CMD                  ;\                       
|       F05Ch or F05Dh WMI_P2P_STOP_SDPD_CMD                ; More P2P commands      |
|       F05Dh or F05Eh WMI_P2P_CANCEL_CMD                   ;/                       |
|       F05Eh or F04Eh WMI_STORERECALL_CONFIGURE_CMD        ;\Ultra low power        
|       F05Fh or F04Fh WMI_STORERECALL_RECALL_CMD           ; store/recall commands  |
|       F060h or F050h WMI_STORERECALL_HOST_READY_CMD       ;/                       |
|       F061h or F051h WMI_FORCE_TARGET_ASSERT_CMD          ;-                       |
|       F062h or N/A   WMI_SET_PROBED_SSID_EX_CMD           ;\                       
|       F063h or N/A   WMI_SET_NETWORK_LIST_OFFLOAD_CMD     ;                        |
|       F064h or N/A   WMI_SET_ARP_NS_OFFLOAD_CMD           ;                        |
|       F065h or N/A   WMI_ADD_WOW_EXT_PATTERN_CMD          ; NEW stuff              |
|       F066h or N/A   WMI_GTK_OFFLOAD_OP_CMD               ; (code from 2012 only)  |
|       F067h or N/A   WMI_REMAIN_ON_CHNL_CMD               ;                        |
|       F068h or N/A   WMI_CANCEL_REMAIN_ON_CHNL_CMD        ;                        |
|       F069h or N/A   WMI_SEND_ACTION_CMD                  ;                        |
|       F06Ah or N/A   WMI_PROBE_REQ_REPORT_CMD             ;                        |
|       F06Bh or N/A   WMI_DISABLE_11B_RATES_CMD            ;                        |
|       F06Ch or N/A   WMI_SEND_PROBE_RESPONSE_CMD          ;                        |
|       F06Dh or N/A   WMI_GET_P2P_INFO_CMD                 ;                        |
|       F06Eh or N/A   WMI_AP_JOIN_BSS_CMD                  ;/                       |
|       ?              WMI_SET_ADHOC_BSSID_CMD              ;-old, not implemented?  |
|       F0AFh          WMI_AP_PSBUFF_OFFLOAD  ;-QCA4002 chipset on GT202 WiFi module |
+------------------------------------------------------------------------------------+
```




