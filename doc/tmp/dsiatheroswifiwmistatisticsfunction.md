# DSi Atheros Wifi - WMI Statistics Function


### WMIcmd(0010h) - WMI_GET_STATISTICS_CMD ;reply WMI_REPORT_STATISTICS
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIevent(100Bh) - WMI_REPORT_STATISTICS_EVENT ;related to CMD 0010h
Event Data (D5h bytes on DSi, although other sources claim A9h or EDh bytes):

```
+------------------------------------------------------------------------------------+
|       A9h D5h EDh  <---- total size (on DSi it's D5h, ie. middle column)           |
|       --  00h 00h A_UINT32 4  lqVal                    ;-  <-- newer version only  |
|       --  04h 04h A_INT32  4  noise_floor_calibation   ;-  <-- newer version only  |
|       --  08h 08h A_UINT32 4  power_save_failure_cnt   ;\pm_stats_t (new)          
|       --  --  0Ch A_UINT16 2  stop_tx_failure_cnt      ;   <-- NEWEST version only |
|       --  --  0Eh A_UINT16 2  atim_tx_failure_cnt      ;   <-- NEWEST version only |
|       --  --  10h A_UINT16 2  atim_rx_failure_cnt      ;   <-- NEWEST version only |
|       --  --  12h A_UINT16 2  bcn_rx_failure_cnt       ;/  <-- NEWEST version only |
|       00h 0Ch 14h A_UINT32 4  tx_packets               ;\                          
|       04h 10h 18h A_UINT32 4  tx_bytes                 ;                           |
|       08h 14h 1Ch A_UINT32 4  tx_unicast_pkts          ;                           |
|       0Ch 18h 20h A_UINT32 4  tx_unicast_bytes         ; tx_stats_t                |
|       10h 1Ch 24h A_UINT32 4  tx_multicast_pkts        ;                           |
|       14h 20h 28h A_UINT32 4  tx_multicast_bytes       ;                           |
|       18h 24h 2Ch A_UINT32 4  tx_broadcast_pkts        ;                           |
|       1Ch 28h 30h A_UINT32 4  tx_broadcast_bytes       ;                           |
|       20h 2Ch 34h A_UINT32 4  tx_rts_success_cnt       ;                           |
|       24h 30h 38h A_UINT32 16 tx_packet_per_ac[4]      ;                           |
|       --  40h 48h A_UINT32 16 tx_errors_per_ac[4]      ;   <-- newer version only  |
|       34h 50h 58h A_UINT32 4  tx_errors                ;                           |
|       38h 54h 5Ch A_UINT32 4  tx_failed_cnt            ;                           |
|       3Ch 58h 60h A_UINT32 4  tx_retry_cnt             ;                           |
|       --  --  64h A_UINT32 4  tx_mult_retry_cnt        ;   <-- NEWEST version only |
|       40h 5Ch 68h A_UINT32 4  tx_rts_fail_cnt          ;                           |
|       --  60h 6Ch A_INT32  4  tx_unicast_rate          ;/  <-- newer version only  |
|       44h 64h 70h A_UINT32 4  rx_packets               ;\                          
|       48h 68h 74h A_UINT32 4  rx_bytes                 ;                           |
|       4Ch 6Ch 78h A_UINT32 4  rx_unicast_pkts          ;                           |
|       50h 70h 7Ch A_UINT32 4  rx_unicast_bytes         ;                           |
|       54h 74h 80h A_UINT32 4  rx_multicast_pkts        ; rx_stats_t                |
|       58h 78h 84h A_UINT32 4  rx_multicast_bytes       ;                           |
|       5Ch 7Ch 88h A_UINT32 4  rx_broadcast_pkts        ;                           |
|       60h 80h 8Ch A_UINT32 4  rx_broadcast_bytes       ;                           |
|       64h 84h 90h A_UINT32 4  rx_fragment_pkt          ;                           |
|       68h 88h 94h A_UINT32 4  rx_errors                ;                           |
|       6Ch 8Ch 98h A_UINT32 4  rx_crcerr                ;                           |
|       70h 90h 9Ch A_UINT32 4  rx_key_cache_miss        ;                           |
|       74h 94h A0h A_UINT32 4  rx_decrypt_err           ;                           |
|       78h 98h A4h A_UINT32 4  rx_duplicate_frames      ;                           |
|       --  9Ch A8h A_INT32  4  rx_unicast_rate          ;/  <-- newer version only  |
|       7Ch A0h ACh A_UINT32 4  tkip_local_mic_failure         ;\                    
|       80h A4h B0h A_UINT32 4  tkip_counter_measures_invoked  ;                     |
|       84h A8h B4h A_UINT32 4  tkip_replays                   ; tkip_ccmp_stats_t   |
|       88h ACh B8h A_UINT32 4  tkip_format_errors             ;                     |
|       8Ch B0h BCh A_UINT32 4  ccmp_format_errors             ;                     |
|       90h B4h C0h A_UINT32 4  ccmp_replays                   ;/                    |
|       --  B8h C4h A_UINT32 4  wow_num_pkts_dropped           ;\                    
|       --  BCh C8h A_UINT16 2  wow_num_events_discarded       ; wlan_wow_stats_t    |
|       --  BEh CAh A_UINT8  1  wow_num_host_pkt_wakeups       ;                     |
|       --  BFh CBh A_UINT8  1  wow_num_host_event_wakeups     ;/                    |
|       --  --  CCh A_UINT32 4  arp_received                   ;\                    
|       --  --  D0h A_UINT32 4  arp_matched                    ; arp_stats_t         |
|       --  --  D4h A_UINT32 4  arp_replied                    ;/                    |
|       94h C0h D8h A_UINT32 4  cs_bmiss_cnt             ;\                          
|       98h C4h DCh A_UINT32 4  cs_lowRssi_cnt           ;                           |
|       9Ch C8h E0h A_UINT16 2  cs_connect_cnt           ; cserv_stats_t             |
|       9Eh CAh E2h A_UINT16 2  cs_disconnect_cnt        ;                           |
|       A0h CCh E4h A_INT16  2  cs_aveBeacon_rssi        ;                           |
|       --  CEh E6h A_UINT16 2  cs_roam_count            ;   <-- newer version only  |
|       --  D0h E8h A_INT16  2  cs_rssi                  ;   <-- newer version only  |
|       --  D2h EAh A_UINT8  1  cs_snr                   ;   <-- newer version only  |
|       --  D3h EBh A_UINT8  1  cs_aveBeacon_snr         ;   <-- newer version only  |
|       A2h D4h ECh A_UINT8  1  cs_lastRoam_msec         ;/                          |
|       A3h --  --  A_UINT32 4  power_save_failure_cnt   ;-pm_stats_t (old)          |
|       A7h --  --  A_INT16  2  noise_floor_calibation   ;-old version only          |
+------------------------------------------------------------------------------------+
```

The D5h-byte structure was found in AR6kSDK.build_sw.18 from 2006.
The A9h-byte structure was found in older (AR6001?) source from 2006.
The EDh-byte structure was found in newer source from 2008 and up.
Names: WMI_GET_STATISTICS aka WMI_REPORT_STATISTICS aka WMI_TARGET_STATS



