# DSi Atheros Wifi - WMI Scan Functions


### WMIcmd(0007h) - WMI_START_SCAN_CMD
Parameters (theoretically 12h+N\*2 bytes, but 14h bytes when N=0 ?):

```
+-------------------------------------------------------------------------------------+
|       00h  A_BOOL   4   forceFgScan                                                 |
|       04h  A_BOOL   4   isLegacy            For Legacy Cisco AP compatibility       |
|       08h  A_UINT32 4   homeDwellTime       Max duration in the home channel (msec) |
|       0Ch  A_UINT32 4   forceScanInterval   Time interval between scans (msec)      |
|       10h  A_UINT8  1   scanType            WMI_SCAN_TYPE                           |
|       11h  A_UINT8  1   numChannels         how many channels follow                |
|       12h  A_UINT16 N*2 channelList[1]      channels in MHz                         |
+-------------------------------------------------------------------------------------+
```

WMI_SCAN_TYPE values:

```
+-----------------------------------------------------------------------+
|       WMI_LONG_SCAN  = 0                                              |
|       WMI_SHORT_SCAN = 1                                              |
+-----------------------------------------------------------------------+
```

Old code from 2008 did (additionally) use value 0 and 1 as so:

```
+-----------------------------------------------------------------------+
|       WMI_PYXIS_PAS_DSCVR = 0                                         |
|       WMI_PYXIS_ACT_DSCVR = 1                                         |
+-----------------------------------------------------------------------+
```

The DSi Browser receives one or more WMI_BSSINFO_EVENT\'s (if there are any beacons on the current channel), and, once when the DwellTime (mul5?) has ellapsed, finally receives WMI_SCAN_COMPLETE_EVENT.

### WMIcmd(0008h) - WMI_SET_SCAN_PARAMS_CMD
Parameters (14h bytes):

```
+-----------------------------------------------------------------------------------+
|       00h  A_UINT16 2  fg_start_period         ;seconds                           |
|       02h  A_UINT16 2  fg_end_period           ;seconds                           |
|       04h  A_UINT16 2  bg_period               ;seconds                           |
|       06h  A_UINT16 2  maxact_chdwell_time     ;msec                              |
|       08h  A_UINT16 2  pas_chdwell_time        ;msec                              |
|       0Ah  A_UINT8  1  shortScanRatio          ;how many shorts scan for one long |
|       0Bh  A_UINT8  1  scanCtrlFlags                                              |
|       0Ch  A_UINT16 2  minact_chdwell_time     ;msec                              |
|       0Eh  A_UINT16 2  maxact_scan_per_ssid    ;max active scans per ssid         |
|       10h  A_UINT32 4  max_dfsch_act_time      ;msec                              |
+-----------------------------------------------------------------------------------+
```

#define WMI_SHORTSCANRATIO_DEFAULT = 3
Warning: ScanCtrlFlag value of FFh is used to disable all flags in WMI_SCAN_PARAMS_CMD
Do not add any more flags to WMI_SCAN_CTRL_FLAG_BITS
WMI_SCAN_CTRL_FLAGS_BITS:

```
+----------------------------------------------------------------------------------+
|       CONNECT_SCAN_CTRL_FLAGS   = 01h  ;set if can scan in the Connect cmd       |
|       SCAN_CONNECTED_CTRL_FLAGS = 02h  ;set if scan for the SSID it is           |
|                                        ;  already connected to                   |
|       ACTIVE_SCAN_CTRL_FLAGS    = 04h  ;set if enable active scan                |
|       ROAM_SCAN_CTRL_FLAGS      = 08h  ;set if enable roam scan when bmiss       |
|                                        ;  and lowrssi                            |
|       REPORT_BSSINFO_CTRL_FLAGS = 10h  ;set if follows customer BSSINFO          |
|                                        ;  reporting rule                         |
|       ENABLE_AUTO_CTRL_FLAGS    = 20h  ;if disabled, target doesn't              |
|                                        ;  scan after a disconnect event          |
|       ENABLE_SCAN_ABORT_EVENT   = 40h  ;Scan complete event with canceled status |
|                                        ;  will be generated when a scan is       |
|                                        ;  prempted before it gets completed      |
|      #define CAN_SCAN_IN_CONNECT(flags)      (flags & CONNECT_SCAN_CTRL_FLAGS)   |
|      #define CAN_SCAN_CONNECTED(flags)       (flags & SCAN_CONNECTED_CTRL_FLAGS) |
|      #define ENABLE_ACTIVE_SCAN(flags)       (flags & ACTIVE_SCAN_CTRL_FLAGS)    |
|      #define ENABLE_ROAM_SCAN(flags)         (flags & ROAM_SCAN_CTRL_FLAGS)      |
|      #define CONFIG_REPORT_BSSINFO(flags)    (flags & REPORT_BSSINFO_CTRL_FLAGS) |
|      #define IS_AUTO_SCAN_ENABLED(flags)     (flags & ENABLE_AUTO_CTRL_FLAGS)    |
|      #define SCAN_ABORT_EVENT_ENABLED(flags) (flags & ENABLE_SCAN_ABORT_EVENT)   |
+----------------------------------------------------------------------------------+
```


#define DEFAULT_SCAN_CTRL_FLAGS = (CONNECT_SCAN_CTRL_FLAGS \| SCAN_CONNECTED_CTRL_FLAGS \| ACTIVE_SCAN_CTRL_FLAGS \| ROAM_SCAN_CTRL_FLAGS \| ENABLE_AUTO_CTRL_FLAGS)

### WMIevent(100Ah) - WMI_SCAN_COMPLETE_EVENT
Event Data (old: None, or new: status, 04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_INT32  4  status;    ;aka "staus"                        |
+-----------------------------------------------------------------------+
```

(whatever, usually/always zero)
(can be 10h\... when already connected maybe?)

Note: There are several \"SCAN_xxx\" and \"xxx_SCPRI\" values defined in \"discovery.h\" - purpose is unknown (maybe that stuff is used only internally).



