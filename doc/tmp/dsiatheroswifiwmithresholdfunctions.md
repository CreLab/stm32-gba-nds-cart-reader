# DSi Atheros Wifi - WMI Threshold Functions


Below commands allow to define thresholds for RSSI, SNR, LQ.

```
+-----------------------------------------------------------------------+
|       RSSI  Received Signal Strength Indicator                        |
|       SNR   Signal to Noise Ratio                                     |
|       LQ    Link Quality                                              |
+-----------------------------------------------------------------------+
```


### WMIcmd(0021h) - WMI_RSSI_THRESHOLD_PARAMS_CMD
Parameters (20h bytes):

```
+--------------------------------------------------------------------------------+
|       00h  A_UINT32 4  pollTime                ;Polling time as a factor of LI |
|       04h  A_INT16  2  thresholdAbove1_Val     ;lowest of upper                |
|       06h  A_INT16  2  thresholdAbove2_Val                                     |
|       08h  A_INT16  2  thresholdAbove3_Val                                     |
|       0Ah  A_INT16  2  thresholdAbove4_Val                                     |
|       0Ch  A_INT16  2  thresholdAbove5_Val                                     |
|       0Eh  A_INT16  2  thresholdAbove6_Val     ;highest of upper               |
|       10h  A_INT16  2  thresholdBelow1_Val     ;lowest of bellow               |
|       12h  A_INT16  2  thresholdBelow2_Val                                     |
|       14h  A_INT16  2  thresholdBelow3_Val                                     |
|       16h  A_INT16  2  thresholdBelow4_Val                                     |
|       18h  A_INT16  2  thresholdBelow5_Val                                     |
|       1Ah  A_INT16  2  thresholdBelow6_Val     ;highest of bellow              |
|       1Ch  A_UINT8  1  weight                  ;"alpha"                        |
|       1Dh  A_UINT8  3  reserved[3]                                             |
|      Setting the polltime to 0 would disable polling.                          |
|      Threshold values are in the ascending order, and should agree to:         |
|        (lowThreshold_lowerVal < lowThreshold_upperVal < highThreshold_lowerVal |
|          < highThreshold_upperVal)                                             |
+--------------------------------------------------------------------------------+
```

See also: WMI_RSSI_THRESHOLD_EVENT

### WMIcmd(002Fh) - WMI_SNR_THRESHOLD_PARAMS_CMD
Parameters (10h bytes):

```
+--------------------------------------------------------------------------------+
|       00h  A_UINT32 4  pollTime                ;Polling time as a factor of LI |
|       04h  A_UINT8  1  weight                  ;"alpha"                        |
|       05h  A_UINT8  1  thresholdAbove1_Val     ;lowest of uppper   ;uh, ppper? |
|       06h  A_UINT8  1  thresholdAbove2_Val                                     |
|       07h  A_UINT8  1  thresholdAbove3_Val                                     |
|       08h  A_UINT8  1  thresholdAbove4_Val     ;highest of upper               |
|       09h  A_UINT8  1  thresholdBelow1_Val     ;lowest of bellow   ;uh bell?   |
|       0Ah  A_UINT8  1  thresholdBelow2_Val                                     |
|       0Bh  A_UINT8  1  thresholdBelow3_Val                                     |
|       0Ch  A_UINT8  1  thresholdBelow4_Val     ;highest of bellow  ;uh bell?   |
|       0Dh  A_UINT8  3  reserved[3]                                             |
+--------------------------------------------------------------------------------+
```

Setting the polltime to 0 would disable polling.
See also: WMI_SNR_THRESHOLD_EVENT

### WMIcmd(0030h) - WMI_LQ_THRESHOLD_PARAMS_CMD
Parameters (0Ch bytes):

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT8  1  enable              ;<-- enable (unlike SNR command)        |
|       01h  A_UINT8  1  thresholdAbove1_Val   ;\these parameters seem to be same as 
|       02h  A_UINT8  1  thresholdAbove2_Val   ; for WMI_SNR_THRESHOLD_PARAMS_CMD    |
|       03h  A_UINT8  1  thresholdAbove3_Val   ;                                     |
|       04h  A_UINT8  1  thresholdAbove4_Val   ;                                     |
|       05h  A_UINT8  1  thresholdBelow1_Val   ;                                     |
|       06h  A_UINT8  1  thresholdBelow2_Val   ;                                     |
|       07h  A_UINT8  1  thresholdBelow3_Val   ;                                     |
|       08h  A_UINT8  1  thresholdBelow4_Val   ;                                     |
|       09h  A_UINT8  3  reserved[3]           ;/                                    |
+------------------------------------------------------------------------------------+
```

See also: WMI_LQ_THRESHOLD_EVENT

### WMIcmd(0033h) - WMI_CLR_RSSI_SNR_CMD
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Probably somehow related to RSSI_THRESHOLD and SNR_THRESHOLD.

### WMIevent(100Ch) - WMI_RSSI_THRESHOLD_EVENT
Event Data (03h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_INT16  2   rssi                                          |
|       02h  A_UINT8  1   range                                         |
+-----------------------------------------------------------------------+
```

WMI_RSSI_THRESHOLD_VAL values (which are probably meant to occurr in one of above fields, unclear which one though):

```
+-----------------------------------------------------------------------+
|       WMI_RSSI_THRESHOLD1_ABOVE = 0                                   |
|       WMI_RSSI_THRESHOLD2_ABOVE = 1                                   |
|       WMI_RSSI_THRESHOLD3_ABOVE = 2                                   |
|       WMI_RSSI_THRESHOLD4_ABOVE = 3                                   |
|       WMI_RSSI_THRESHOLD5_ABOVE = 4                                   |
|       WMI_RSSI_THRESHOLD6_ABOVE = 5                                   |
|       WMI_RSSI_THRESHOLD1_BELOW = 6                                   |
|       WMI_RSSI_THRESHOLD2_BELOW = 7                                   |
|       WMI_RSSI_THRESHOLD3_BELOW = 8                                   |
|       WMI_RSSI_THRESHOLD4_BELOW = 9                                   |
|       WMI_RSSI_THRESHOLD5_BELOW = 10                                  |
|       WMI_RSSI_THRESHOLD6_BELOW = 11                                  |
+-----------------------------------------------------------------------+
```

Indicate the RSSI events to host. Events are indicated when we breach a thresold value. (uh, how old do we breach?)

### WMIevent(1012h) - WMI_SNR_THRESHOLD_EVENT
Event Data (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  range        ;WMI_SNR_THRESHOLD_VAL            |
|       01h  A_UINT8  1  snr                                            |
+-----------------------------------------------------------------------+
```

WMI_SNR_THRESHOLD_VAL values:

```
+-----------------------------------------------------------------------+
|       WMI_SNR_THRESHOLD1_ABOVE = 1                                    |
|       WMI_SNR_THRESHOLD1_BELOW = 2                                    |
|       WMI_SNR_THRESHOLD2_ABOVE = 3                                    |
|       WMI_SNR_THRESHOLD2_BELOW = 4                                    |
|       WMI_SNR_THRESHOLD3_ABOVE = 5                                    |
|       WMI_SNR_THRESHOLD3_BELOW = 6                                    |
|       WMI_SNR_THRESHOLD4_ABOVE = 7                                    |
|       WMI_SNR_THRESHOLD4_BELOW = 8                                    |
+-----------------------------------------------------------------------+
```


### WMIevent(1013h) - WMI_LQ_THRESHOLD_EVENT
Event Data (05h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_INT32  4  lq                                             |
|       04h  A_UINT8  1  range        ;WMI_LQ_THRESHOLD_VAL             |
+-----------------------------------------------------------------------+
```

WMI_LQ_THRESHOLD_VAL values:

```
+-----------------------------------------------------------------------+
|       WMI_LQ_THRESHOLD1_ABOVE = 1                                     |
|       WMI_LQ_THRESHOLD1_BELOW = 2                                     |
|       WMI_LQ_THRESHOLD2_ABOVE = 3                                     |
|       WMI_LQ_THRESHOLD2_BELOW = 4                                     |
|       WMI_LQ_THRESHOLD3_ABOVE = 5                                     |
|       WMI_LQ_THRESHOLD3_BELOW = 6                                     |
|       WMI_LQ_THRESHOLD4_ABOVE = 7                                     |
|       WMI_LQ_THRESHOLD4_BELOW = 8                                     |
+-----------------------------------------------------------------------+
```




