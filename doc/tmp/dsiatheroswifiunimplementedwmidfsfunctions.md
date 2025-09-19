# DSi Atheros Wifi - Unimplemented WMI DFS Functions


### WMIcmd(F034h) - WMI_SET_DFS_ENABLE_CMD ;aka WMI_SET_DFS_CMD maybe ?
### WMIcmd(F035h) - WMI_SET_DFS_MINRSSITHRESH_CMD ;aka WMI_SET_DFS_CMD too ??
### WMIcmd(F036h) - WMI_SET_DFS_MAXPULSEDUR_CMD ;aka WMI_SET_DFS_CMD too ??
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (maybe WMI_SET_DFS_CMD structure?)                      |
+-----------------------------------------------------------------------+
```

There is a \"WMI_SET_DFS_CMD\" structure defined:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   enable;                                       |
+-----------------------------------------------------------------------+
```

Maybe that structure is meant to be used with one of the WMI_SET_DFS_xxx_CMD commands, or maybe it\'s even meant to be used with ALL of that THREE commands.

```
+-----------------------------------------------------------------------+
|       XXX see file "dfs_common.h"                                     |
+-----------------------------------------------------------------------+
```


### WMIcmd(F037h) - WMI_DFS_RADAR_DETECTED_CMD ;aka WMI_RADAR_DETECTED_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2  chan_index;                                    |
|       02h  A_INT8   1  bang_radar;                                    |
+-----------------------------------------------------------------------+
```


### WMIevent(102Bh) - WMI_DFS_HOST_ATTACH_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT64 8  ext_chan_busy_ts;                              |
|       08h  A_UINT8  1  enable_ar;                                     |
|       09h  A_UINT8  1  enable_radar;                                  |
+-----------------------------------------------------------------------+
```


### WMIevent(102Ch) - WMI_DFS_HOST_INIT_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32 4  dfs_domain;                                    |
+-----------------------------------------------------------------------+
```


### WMIevent(102Dh) - WMI_DFS_RESET_DELAYLINES_EVENT
### WMIevent(102Eh) - WMI_DFS_RESET_RADARQ_EVENT
### WMIevent(102Fh) - WMI_DFS_RESET_AR_EVENT
### WMIevent(1030h) - WMI_DFS_RESET_ARQ_EVENT
### WMIevent(1031h) - WMI_DFS_SET_DUR_MULTIPLIER_EVENT
### WMIevent(1032h) - WMI_DFS_SET_BANGRADAR_EVENT
### WMIevent(1033h) - WMI_DFS_SET_DEBUGLEVEL_EVENT
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (if any) (not defined in file "dfs_common.h")           |
+-----------------------------------------------------------------------+
```


### WMIevent(1034h) - WMI_DFS_PHYERR_EVENT
Event Data:

```
+--------------------------------------------------------------------------+
|       00h  A_UINT8         1     num_events;                             |
|       01h  dfs_event_info  ..    ev_info[WMI_DFS_EVENT_MAX_BUFFER_SIZE]; |
+--------------------------------------------------------------------------+
```

WMI_DFS_EVENT_MAX_BUFFER_SIZE = ((255)/sizeof(struct dfs_event_info))
Format of the above \"dfs_event_info\" structure:

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT64 8  full_ts;       /* 64-bit full timestamp from interrupt time |
|       08h  A_UINT32 4  ts;            /* Original 15 bit recv timestamp            |
|       0Ch  A_UINT32 4  ext_chan_busy; /* Ext chan busy %                           |
|       10h  A_UINT8  1  rssi;          /* rssi of radar event                       |
|       11h  A_UINT8  1  dur;           /* duration of radar pulse                   |
|       12h  A_UINT8  1  chanindex;     /* Channel of event                          |
|       13h  A_UINT8  1  flags;                                                      |
+------------------------------------------------------------------------------------+
```

Values for \"flags\":

```
+-----------------------------------------------------------------------+
|       PRIMARY_CH = 0  ;\flags.bit0                                    
|       EXT_CH     = 1  ;/                                              |
|       AR_EVENT   = 0  ;\flags.bit1                                    
|       DFS_EVENT  = 2  ;/                                              |
+-----------------------------------------------------------------------+
```

Some more DFS related constants (unknown purpose):

```
+-----------------------------------------------------------------------------------+
|       DFS_UNINIT_DOMAIN = 0     ;Uninitialized dfs domain                         |
|       DFS_FCC_DOMAIN    = 1     ;FCC3 dfs domain                                  |
|       DFS_ETSI_DOMAIN   = 2     ;ETSI dfs domain                                  |
|       DFS_MKK4_DOMAIN   = 3     ;Japan dfs domain                                 |
|       MAX_BIN5_DUR      = 131   ;rounded from 131.25=(105*1.25)   ;DFS related    |
|       TRAFFIC_DETECTED = 1      ;whatever                         ;DFS related    |
|       ATH_DEBUG_DFS  = 00000100h  ;Minimal DFS debug        ;\                    
|       ATH_DEBUG_DFS1 = 00000200h  ;Normal DFS debug         ; should match the    |
|       ATH_DEBUG_DFS2 = 00000400h  ;Maximal DFS debug        ; table from if_ath.c |
|       ATH_DEBUG_DFS3 = 00000800h  ;matched filterID display ;/                    |
+-----------------------------------------------------------------------------------+
```




