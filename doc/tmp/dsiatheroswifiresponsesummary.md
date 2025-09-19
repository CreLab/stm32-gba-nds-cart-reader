# DSi Atheros Wifi - Response Summary


Events can be actual hardware events, or responses to certain commands. See MBOX Transfer Headers chapter for details on the transfer format.

### WMI Events/Responses
Events/Responses with same ID as corresponding command

```
+-----------------------------------------------------------------------+
|       000Eh  WMI_GET_CHANNEL_LIST_CMD                                 |
|       001Ch  WMI_GET_TX_PWR_CMD                                       |
|       0035h  WMI_GET_FIXRATES_CMD                                     |
|       003Eh  WMI_GET_KEEPALIVE_CMD                                    |
|       F001h  WMI_GET_BITRATE_CMD                                      |
+-----------------------------------------------------------------------+
```

Events/Responses that could/should exist (but aren\'t documented)

```
+-------------------------------------------------------------------------------------+
|       ?      WMI_GET_APPIE_CMD  ;aka GET_APP_IE            ;\not implemented in DSi 
|       ?      WMI_AP_MODE_STAT_CMD  ;has reply?             ;/                       |
+-------------------------------------------------------------------------------------+
```

Events/Responses that have REPLY structs defined (but CMDs don\'t send reply?)

```
+-------------------------------------------------------------------------------------+
|       ?      WMI_CRE_PRIORITY_STREAM_REPLY                 ;\                       
|       ?      WMI_DEL_PRIORITY_STREAM_REPLY                 ; not implemented in DSi |
|       ?      WMI_FRAME_RATES_REPLY                         ;/                       |
+-------------------------------------------------------------------------------------+
```

Events/Responses with special IDs

```
+-------------------------------------------------------------------------------------+
|       1001h  WMI_READY_EVENT                                                        |
|       1002h  WMI_CONNECT_EVENT                                                      |
|       1003h  WMI_DISCONNECT_EVENT                                                   |
|       1004h  WMI_BSSINFO_EVENT   ;aka WMI_BSS_INFO                                  |
|       1005h  WMI_CMDERROR_EVENT  ;aka WMI_CMD_ERROR_EVENT  ;for CMD 01h,11h,16h,26h |
|       1006h  WMI_REGDOMAIN_EVENT ;aka WMI_REG_DOMAIN_EVENT                          |
|       1007h  WMI_PSTREAM_TIMEOUT_EVENT                                              |
|       1008h  WMI_NEIGHBOR_REPORT_EVENT                                              |
|       1009h  WMI_TKIP_MICERR_EVENT                                                  |
|       100Ah  WMI_SCAN_COMPLETE_EVENT                                                |
|       100Bh  WMI_REPORT_STATISTICS_EVENT    ;related to CMD 0010h ?                 |
|       100Ch  WMI_RSSI_THRESHOLD_EVENT                                               |
|       100Dh  WMI_ERROR_REPORT_EVENT ;aka WMI_TARGET_ERROR_REPORT_EVENT              |
|       100Eh  WMI_OPT_RX_FRAME_EVENT ;aka WMI_OPT_RX_INFO                            |
|       100Fh  WMI_REPORT_ROAM_TBL_EVENT           ;related to CMD 002Ah ?            |
|       1010h  WMI_EXTENSION_EVENT   ;prefix for WMIX events...                       |
|       1010h:3001h  WMIX_DSETOPENREQ_EVENT ;request 2001h   ;\                       
|       1010h:3002h  WMIX_DSETCLOSE_EVENT   ;request close   ; not implemented in DSi |
|       1010h:3003h  WMIX_DSETDATAREQ_EVENT ;request 2002h   ;/                       |
|       1010h:3004h  WMIX_GPIO_INTR_EVENT         ;used (interrupt)                   |
|       1010h:3005h  WMIX_GPIO_DATA_EVENT         ;used (reply to 2004h and 2006h)    |
|       1010h:3006h  WMIX_GPIO_ACK_EVENT          ;used (reply to 2003h and 2005h)    |
|       1010h:3007h  WMIX_HB_CHALLENGE_RESP_EVENT ;used (reply to 2008h)              |
|       1010h:3008h  WMIX_DBGLOG_EVENT            ;used (probably related to 2009h)   |
|       1010h:3009h  WMIX_PROF_COUNT_EVENT                   ;-not implemented in DSi |
|       1011h  WMI_CAC_EVENT                                                          |
|       1012h  WMI_SNR_THRESHOLD_EVENT                                                |
|       1013h  WMI_LQ_THRESHOLD_EVENT                                                 |
|       1014h  WMI_TX_RETRY_ERR_EVENT                                                 |
|       1015h  WMI_REPORT_ROAM_DATA_EVENT ;related to 002Bh? ;\not implemented in DSi 
|       1016h  WMI_TEST_EVENT                                ;/                       |
|       1017h  WMI_APLIST_EVENT                                                       |
|       1018h  WMI_GET_WOW_LIST_EVENT              ;reply to CMD 0044h                |
|       1019h  WMI_GET_PMKID_LIST_EVENT            ;reply to CMD F006h                |
+-------------------------------------------------------------------------------------+
```

Below not in AR6kSDK.build_sw.18, however, \"101Ah\" is USED on DSi\...

```
+-----------------------------------------------------------------------+
|       101Ah  WMI_CHANNEL_CHANGE_EVENT            ;<-- used on DSi     |
+-----------------------------------------------------------------------+
```

Below some are spotted on 3DS (possibly inofficial stuff?)
(type4=3ds/internet?, macfilter=3ds/localmultiplay?)

```
+----------------------------------------------------------------------------------+
|       101Dh     type4, len=0                                                     |
|       101Fh     type4, len=N*4                                                   |
|       1020h     type4, len=8                                                     |
|       1021h     macfilter, len=10h+?      ;"succes"                              |
|       1022h     type4, len=0          ;reply to cmd 0057h ?                      |
|       1023h     macfilter, len=4+?    ;reply to cmd 0068h                        |
|       1024h     type4, len=0Eh                                                   |
|       1025h     type4, len=1   ;thrown by 3DS type4 variant (works when ignored) |
|       1026h     macfilter, len=0Ch    ;reply to cmd 006Dh                        |
|       1027h     macfilter, len=2+?    ;reply to cmd 0073h                        |
+----------------------------------------------------------------------------------+
```

Below (101Bh..9004h) not implemented in DSi\...

```
+------------------------------------------------------------------------------------+
|       101Bh  WMI_PEER_NODE_EVENT                                                   |
|       101Ch  WMI_PSPOLL_EVENT ;aka WMI_PS_POLL_EVENT  ;AP mode related?            |
|       101Dh  WMI_DTIMEXPIRY_EVENT                                                  |
|       101Eh  WMI_WLAN_VERSION_EVENT                                                |
|       101Fh  WMI_SET_PARAMS_REPLY_EVENT  ;reply to CMD F018h (reply to "SET" cmd!) |
|       1020h  WMI_ADDBA_REQ_EVENT                                                   |
|       1021h  WMI_ADDBA_RESP_EVENT                                                  |
|       1022h  WMI_DELBA_REQ_EVENT aka WMI_DELBA_EVENT                               |
|       1023h  WMI_TX_COMPLETE_EVENT                                                 |
|       1024h  WMI_HCI_EVENT_EVENT aka WMI_HCI_EVENT                                 |
|       1025h  WMI_ACL_DATA_EVENT                                                    |
|       1026h  WMI_REPORT_SLEEP_STATE_EVENT   ;formerly N/A                          |
|       1027h  WMI_WAPI_REKEY_EVENT           ;formerly N/A, or 1026h if WAPI_ENABLE |
|       1028h  WMI_REPORT_BTCOEX_STATS_EVENT  ;formerly 1026h/1027h  ;reply to F032h |
|       1029h  WMI_REPORT_BTCOEX_CONFIG_EVENT ;formerly 1027h/1028h  ;reply to F033h |
|       102Ah  WMI_GET_PMK_EVENT aka WMI_GET_PMK_REPLY                               |
|       102Bh  WMI_DFS_HOST_ATTACH_EVENT              ;\                             
|       102Ch  WMI_DFS_HOST_INIT_EVENT                ;                              |
|       102Dh  WMI_DFS_RESET_DELAYLINES_EVENT         ;                              |
|       102Eh  WMI_DFS_RESET_RADARQ_EVENT             ;                              |
|       102Fh  WMI_DFS_RESET_AR_EVENT                 ; DFS Events                   |
|       1030h  WMI_DFS_RESET_ARQ_EVENT                ;                              |
|       1031h  WMI_DFS_SET_DUR_MULTIPLIER_EVENT       ;                              |
|       1032h  WMI_DFS_SET_BANGRADAR_EVENT            ;                              |
|       1033h  WMI_DFS_SET_DEBUGLEVEL_EVENT           ;                              |
|       1034h  WMI_DFS_PHYERR_EVENT                   ;/                             |
|       1035h  WMI_CCX_RM_STATUS_EVENT                ;-CCX Evants  ;uh, EvAntS?     |
|       1036h  WMI_P2P_GO_NEG_RESULT_EVENT            ;-P2P Events  ;uh, EventS?     |
|       1037h  WMI_WAC_SCAN_DONE_EVENT                ;\                             
|       1038h  WMI_WAC_REPORT_BSS_EVENT               ; WAC                          |
|       1039h  WMI_WAC_START_WPS_EVENT                ;                              |
|       103Ah  WMI_WAC_CTRL_REQ_REPLY_EVENT           ;/                             |
|       103Bh  WMI_RFKILL_STATE_CHANGE_EVENT          ;\RFKILL Events                
|       103Ch  WMI_RFKILL_GET_MODE_CMD_EVENT          ;/                             |
|       103Dh  WMI_P2P_GO_NEG_REQ_EVENT               ;\                             
|       103Eh  WMI_P2P_INVITE_REQ_EVENT               ;                              |
|       103Fh  WMI_P2P_INVITE_RCVD_RESULT_EVENT       ;                              |
|       1040h  WMI_P2P_INVITE_SENT_RESULT_EVENT       ; More P2P Events              |
|       1041h  WMI_P2P_PROV_DISC_RESP_EVENT           ;                              |
|       1042h  WMI_P2P_PROV_DISC_REQ_EVENT            ;                              |
|       1043h  WMI_P2P_START_SDPD_EVENT               ;                              |
|       1044h  WMI_P2P_SDPD_RX_EVENT                  ;/                             |
|       1045h  WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENT  ;-avoid AR6003 crash     |
|       8000h  WMI_THIN_EVENTID_RESERVED_START        ;\                             
|       8001h  WMI_THIN_GET_MIB_EVENT                 ; THIN events (wmi_thin.h)     |
|       8002h  WMI_THIN_JOIN_EVENT                    ;                              |
|       8FFFh  WMI_THIN_EVENTID_RESERVED_END          ;/                             |
|       9000h  WMI_SET_CHANNEL_EVENT                            ;\                   
|       9001h  WMI_ASSOC_REQ_EVENT aka WMI_ASSOCREQ_EVENT       ; More events,       |
|       9002h  WMI_ACS_EVENT    ;generic ACS event              ; somehow located    |
|       9003h  WMI_REPORT_WMM_PARAMS_EVENT                      ; after THIN area    |
|       9004h  WMI_STORERECALL_STORE_EVENT                      ;/                   |
+------------------------------------------------------------------------------------+
```

code from 2012 has WMI_WAPI_REKEY_EVENT re-removed again, the two RFKILL Events moved around (placed into the P2P event area), and WMI_REPORT_WMM_PARAMS_EVENT moved to 10xxh, a new WMI_WAC_REJECT_WPS_EVENT at 10xxh, and WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENT removed, and WMI_STORERECALL_STORE_EVENT moved to 9003h, and adds more NEW stuff at 9004h-900Dh:

```
+-----------------------------------------------------------------------+
|       10xxh WMI_REPORT_WMM_PARAMS_EVENT     ;-moved to 10xxh or so    |
|       10xxh WMI_WAC_REJECT_WPS_EVENT        ;-NEW                     |
|       9003h WMI_STORERECALL_STORE_EVENT     ;-move to HERE            |
|       9004h WMI_WOW_EXT_WAKE_EVENT          ;\                        
|       9005h WMI_GTK_OFFLOAD_STATUS_EVENT    ;                         |
|       9006h WMI_NETWORK_LIST_OFFLOAD_EVENT  ;                         |
|       9007h WMI_REMAIN_ON_CHNL_EVENT        ; NEW                     |
|       9008h WMI_CANCEL_REMAIN_ON_CHNL_EVENT ;                         |
|       9009h WMI_TX_STATUS_EVENT             ;                         |
|       900Ah WMI_RX_PROBE_REQ_EVENT          ;                         |
|       900Bh WMI_P2P_CAPABILITIES_EVENT      ;                         |
|       900Ch WMI_RX_ACTION_EVENT             ;                         |
|       900Dh WMI_P2P_INFO_EVENT              ;/                        |
+-----------------------------------------------------------------------+
```




