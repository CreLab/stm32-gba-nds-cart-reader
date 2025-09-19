# DSi Atheros Wifi - WMI Wake on Wireless (WOW) Functions


### WMIcmd(0042h) - WMI_SET_HOST_SLEEP_MODE_CMD
Parameters (08h bytes on DSi?, so, a BOOL must be 4 bytes?):

```
+-----------------------------------------------------------------------+
|       00h  A_BOOL   4  awake;                                         |
|       04h  A_BOOL   4  asleep;                                        |
+-----------------------------------------------------------------------+
```

See also: WMI_SET_HOST_SLEEP_MODE_CMD_PROCESSED_EVENT

### WMIcmd(0043h) - WMI_SET_WOW_MODE_CMD
Event Data (04h bytes on DSi?, but other sources claim MORE bytes?):

```
+-------------------------------------------------------------------------------------+
|       04h ??h   <---- total size (on DSi it's 04h, ie. left column)                 |
|       00h 00h  A_BOOL         4   enable_wow                                        |
|       --  04h  WMI_WOW_FILTER ..  filter ;UINTx or so? with "WMI_WOW_FILTER" value? |
|       --  ..   A_UINT16       2   hostReqDelay                                      |
+-------------------------------------------------------------------------------------+
```

WMI_WOW_FILTER values (only one defined):

```
+-----------------------------------------------------------------------+
|       WOW_FILTER_SSID = 01h                                           |
+-----------------------------------------------------------------------+
```


### WMIcmd(0044h) - WMI_GET_WOW_LIST_CMD ;reply 1018h (!)
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   filter_list_id;                               |
+-----------------------------------------------------------------------+
```

Reply (88h bytes on DSi): WMI_GET_WOW_LIST_EVENT:

```
+---------------------------------------------------------------------------------+
|       00h  A_UINT8    1      num_filters     /* number of patterns in reply     |
|       01h  A_UINT8    1      this_filter_num /* filter # x of total num_filters |
|       02h  A_UINT8    1      wow_mode                                           |
|       03h  A_UINT8    1      host_mode                                          |
|       04h  WOW_FILTER N*84h  wow_filters[1]                                     |
+---------------------------------------------------------------------------------+
```

WOW_FILTER structure:

```
+-----------------------------------------------------------------------+
|         A_UINT8 1    wow_valid_filter;                                |
|         A_UINT8 1    wow_filter_id;                                   |
|         A_UINT8 1    wow_filter_size;                                 |
|         A_UINT8 1    wow_filter_offset;                               |
|         A_UINT8 40h  wow_filter_mask[WOW_MASK_SIZE];                  |
|         A_UINT8 40h  wow_filter_pattern[WOW_PATTERN_SIZE];            |
+-----------------------------------------------------------------------+
```

There\'s also a \"WOW_FILTER_LIST\" structure (unknown purpose):

```
+-----------------------------------------------------------------------+
|         A_UINT8    1      wow_valid_list;                             |
|         A_UINT8    1      wow_list_id;                                |
|         A_UINT8    1      wow_num_filters;                            |
|         A_UINT8    1      wow_total_list_size;                        |
|         WOW_FILTER 4*84h  list[WOW_MAX_FILTERS_PER_LIST];             |
|      #define WOW_MAX_FILTER_LISTS     = 1     /*  4  */               |
|      #define WOW_MAX_FILTERS_PER_LIST = 4                             |
|      #define WOW_PATTERN_SIZE         = 64                            |
|      #define WOW_MASK_SIZE            = 64                            |
+-----------------------------------------------------------------------+
```


### WMIcmd(0045h) - WMI_ADD_WOW_PATTERN_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   filter_list_id;                               |
|       01h  A_UINT8  1   filter_size;                                  |
|       02h  A_UINT8  1   filter_offset;                                |
|       03h  A_UINT8  ..  filter[1];                                    |
+-----------------------------------------------------------------------+
```


### WMIcmd(0046h) - WMI_DEL_WOW_PATTERN_CMD
Parameters (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT16 2   filter_list_id;                               |
|       02h  A_UINT16 2   filter_id;                                    |
+-----------------------------------------------------------------------+
```


### WMIevent(1018h) - WMI_GET_WOW_LIST_EVENT ;reply to CMD 0044h
See WMI_GET_WOW_LIST_CMD for response details.



