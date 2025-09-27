# DSi Atheros Wifi - WMI Priority Stream Functions


### WMIcmd(0005h) - WMI_CREATE_PSTREAM_CMD ;aka WMI_CRE_PRIORITY_STREAM
Parameters (3Fh bytes in DSi, but other variants exist, too):

```
+--------------------------------------------------------------------------------+
|       old 3Fh 40h  <---- total size (on DSi it's 3Fh, ie. middle column)       |
|       0Bh 00h 00h  A_UINT32 4  minServiceInt      ;in msec (14h=20)            |
|       0Fh 04h 04h  A_UINT32 4  maxServiceInt      ;in msec (14h=20)            |
|       13h 08h 08h  A_UINT32 4  inactivityInt      ;in msec (98967Fh=9999999)   |
|       17h 0Ch 0Ch  A_UINT32 4  suspensionInt      ;in msec (-1)                |
|       1Bh 10h 10h  A_UINT32 4  serviceStartTime            (0)                 |
|       1Fh 14h 14h  A_UINT32 4  minDataRate        ;in bps  (14500h=83200)      |
|       23h 18h 18h  A_UINT32 4  meanDataRate       ;in bps  (14500h=83200)      |
|       27h 1Ch 1Ch  A_UINT32 4  peakDataRate       ;in bps  (14500h=83200)      |
|       2Bh 20h 20h  A_UINT32 4  maxBurstSize                (0)                 |
|       2Fh 24h 24h  A_UINT32 4  delayBound                  (0)                 |
|       33h 28h 28h  A_UINT32 4  minPhyRate         ;in bps  (5B8D80h=6000000)   |
|       37h 2Ch 2Ch  A_UINT32 4  sba                         (2000h=8192)        |
|       3Bh 30h 30h  A_UINT32 4  mediumTime                  (0)                 |
|       07h 34h 34h  A_UINT16 2  nominalMSDU        ;in octeCts   (80D0h=?)      |
|       09h 36h 36h  A_UINT16 2  maxMSDU            ;in octeCts   (00D0h=?)      |
|       00h 38h 38h  A_UINT8  1  trafficClass                     (00h)          |
|       01h 39h 39h  A_UINT8  1  trafficDirection   ;DIR_TYPE     (02h=Bidir)    |
|       02h 3Ah 3Ah  A_UINT8  1  rxQueueNum                       (FFh)          |
|       03h 3Bh 3Bh  A_UINT8  1  trafficType        ;TRAFFIC_TYPE (01h=Periodic) |
|       04h 3Ch 3Ch  A_UINT8  1  voicePSCapability  ;VOICEPS_CAP_TYPE      (00h) |
|       05h 3Dh 3Dh  A_UINT8  1  tsid                                      (05h) |
|       06h 3Eh 3Eh  A_UINT8  1  userPriority       ;802.1D user priority  (00h) |
|       -   -   3Fh  A_UINT8  1  nominalPHY         ;nominal phy rate            |
+--------------------------------------------------------------------------------+
```

Old wmi.h source code from 2006 used 8bit/16bit/32bit parameter ordering, later source code reversed that to 32bit/16bit/8bit and added an extra \"nominalPHY\" entry. DSi uses the new ordering, but without the extra entry.
DIR_TYPE values:

```
+-----------------------------------------------------------------------+
|       UPLINK_TRAFFIC         = 0                                      |
|       DNLINK_TRAFFIC         = 1                                      |
|       BIDIR_TRAFFIC          = 2                                      |
+-----------------------------------------------------------------------+
```

TRAFFIC_TYPE values:

```
+-----------------------------------------------------------------------+
|       TRAFFIC_TYPE_APERIODIC = 0                                      |
|       TRAFFIC_TYPE_PERIODIC  = 1                                      |
+-----------------------------------------------------------------------+
```

VOICEPS_CAP_TYPE values:

```
+-----------------------------------------------------------------------+
|       DISABLE_FOR_THIS_AC    = 0                                      |
|       ENABLE_FOR_THIS_AC     = 1                                      |
|       ENABLE_FOR_ALL_AC      = 2                                      |
+-----------------------------------------------------------------------+
```

XXX see WMI_CRE_PRIORITY_STREAM_REPLY ????

### WMIcmd(0006h) - WMI_DELETE_PSTREAM_CMD ;aka WMI_DEL_PRIORITY_STREAM
Parameters (05h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   txQueueNumber                                 |
|       01h  A_UINT8  1   rxQueueNumber                                 |
|       02h  A_UINT8  1   trafficDirection                              |
|       03h  A_UINT8  1   trafficClass                                  |
|       04h  A_UINT8  1   tsid                                          |
+-----------------------------------------------------------------------+
```

XXX see WMI_DEL_PRIORITY_STREAM_REPLY ????

### WMIevent(1007h) - WMI_PSTREAM_TIMEOUT_EVENT
Event Data (04h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  txQueueNumber                                  |
|       01h  A_UINT8  1  rxQueueNumber                                  |
|       02h  A_UINT8  1  trafficDirection                               |
|       03h  A_UINT8  1  trafficClass                                   |
+-----------------------------------------------------------------------+
```




