# DSi Atheros Wifi - WMI Bit Rate Functions


### WMIcmd(0034h) - WMI_SET_FIXRATES_CMD ;aka WMI_FIX_RATES_CMD
Parameters (02h bytes on DSi?, but other sources claim 08h bytes):

```
+---------------------------------------------------------------------------------+
|       02h 08h   <---- total size (on DSi it's 02h, ie. left column)             |
|       00h --  A_UINT16 2   fixRateMask     ;0..0FFFh          ;see WMI_BIT_RATE |
|       --  00h A_UINT32 4   fixRateMask(0)  ;0..0FFFFFFFh      ;see WMI_BIT_RATE |
|       --  04h A_UINT32 4   fixRateMask(1)  ;0..0FFFFFFFh      ;see WMI_BIT_RATE |
+---------------------------------------------------------------------------------+
```


### WMIcmd(0035h) - WMI_GET_FIXRATES_CMD ;reply 0035h
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply: WMI_GET_FIXRATES aka WMI_FIX_RATES_REPLY
Event Data (02h bytes on DSi?, but other sources claim 08h bytes):

```
+----------------------------------------------------------------------------------+
|       02h 08h   <---- total size (on DSi it's 02h, ie. left column)              |
|       00h --  A_UINT16 2   fixRateMask     ;0..0FFFh           ;see WMI_BIT_RATE |
|       --  00h A_UINT32 4   fixRateMask(0)  ;0..0FFFFFFFh       ;see WMI_BIT_RATE |
|       --  04h A_UINT32 4   fixRateMask(1)  ;0..0FFFFFFFh       ;see WMI_BIT_RATE |
+----------------------------------------------------------------------------------+
```

See \"FIX_RATE_xxx\" values.

### WMIcmd(0048h or 0047h) - WMI_SET_FRAMERATES_CMD ;aka WMI_FRAME_RATES_CMD
DSi uses command number 0048h for this (whilst most or all official Atheros code is using number 0047h).
Parameters (04h bytes, or 0Ch bytes on hardware with more rates):

```
+-------------------------------------------------------------------------------------+
|       04h 0Ch   <---- total size (on DSi it's 04h, ie. left column)                 |
|       00h 00h  A_UINT8  1   bEnableMask               (used: 01h) ;whatever?        |
|       01h 01h  A_UINT8  1   frameType  (D4h=special?) (used: A4h) ;type and subtype |
|       02h --   A_UINT16 2   frameRateMask ;0..0FFFh (used: FFF7h) ;see WMI_BIT_RATE |
|       --  02h  A_UINT8  2   reserved[2]                           ;for alignment    |
|       --  04h  A_UINT32 4   frameRateMask(0)  ;0..0FFFFFFFh       ;see WMI_BIT_RATE |
|       --  08h  A_UINT32 4   frameRateMask(1)  ;0..0FFFFFFFh       ;see WMI_BIT_RATE |
+-------------------------------------------------------------------------------------+
```

Note: FRAMERATE is apparently meant to be \"bitrate\" for certain \"packet types\" (frames). The type and subtype values are maybe meant to resemble those in Frame Control (FC) field, or the FTYPE_xxx constants in some atheros source code?
Reportedly there is a \"WMI_FRAME_RATES_REPLY\" with same Reply structure as above Parameter structure, the DSi doesn\'t support that feature (and it\'s rather unknown if/when/how that Reply would be sent if the feature were implemented\... maybe as event, or as reply to SET_FRAMERATES, or as reply to whatever other cmd).

### WMIcmd(F000h) - WMI_SET_BITRATE_CMD ;aka WMI_BIT_RATE_CMD
Parameters (03h bytes):

```
+------------------------------------------------------------------------+
|       00h  A_INT8  1   rateIndex      (FFh=Auto)     ;see WMI_BIT_RATE |
|       01h  A_INT8  1   mgmtRateIndex  (00h=1Mbit/s)                    |
|       02h  A_INT8  1   ctlRateIndex   (00h=1Mbit/s)                    |
+------------------------------------------------------------------------+
```

Note: This doesn\'t really work. Using rateIndex=FFh (or 0Bh) does currently reach only max 600Kbyte/s upload speed (which MIGHT be a bug in my software). However, using rateIndex=00h is slower, but still reaches more than 200Kbyte/s (which is outright wrong and impossible at 1Mbit/s).

### WMIcmd(F001h) - WMI_GET_BITRATE_CMD ;reply F001h
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```

Reply:

```
+-----------------------------------------------------------------------+
|       00h  A_INT8   1    rateIndex           ;see WMI_BIT_RATE        |
+-----------------------------------------------------------------------+
```


### WMI_BIT_RATE values

```
+-----------------------------------------------------------------------+
|       Mbit/s        = Index      Mbit/s            = Mask             |
|       RATE_AUTO     = -1         -                 = -                |
|       RATE_1Mb      = 0          FIX_RATE_1Mb      = 1h               |
|       RATE_2Mb      = 1          FIX_RATE_2Mb      = 2h               |
|       RATE_5_5Mb    = 2          FIX_RATE_5_5Mb    = 4h               |
|       RATE_11Mb     = 3          FIX_RATE_11Mb     = 8h               |
|       RATE_6Mb      = 4          FIX_RATE_6Mb      = 10h              |
|       RATE_9Mb      = 5          FIX_RATE_9Mb      = 20h              |
|       RATE_12Mb     = 6          FIX_RATE_12Mb     = 40h              |
|       RATE_18Mb     = 7          FIX_RATE_18Mb     = 80h              |
|       RATE_24Mb     = 8          FIX_RATE_24Mb     = 100h             |
|       RATE_36Mb     = 9          FIX_RATE_36Mb     = 200h             |
|       RATE_48Mb     = 10         FIX_RATE_48Mb     = 400h             |
|       RATE_54Mb     = 11         FIX_RATE_54Mb     = 800h             |
+-----------------------------------------------------------------------+
```

Below only for newer (non-DSi) revisions (with 32bit RATE_MASK values):

```
+-----------------------------------------------------------------------+
|       RATE_MCS_0_20 = 12         FIX_RATE_MCS_0_20 = 1000h            |
|       RATE_MCS_1_20 = 13         FIX_RATE_MCS_1_20 = 2000h            |
|       RATE_MCS_2_20 = 14         FIX_RATE_MCS_2_20 = 4000h            |
|       RATE_MCS_3_20 = 15         FIX_RATE_MCS_3_20 = 8000h            |
|       RATE_MCS_4_20 = 16         FIX_RATE_MCS_4_20 = 10000h           |
|       RATE_MCS_5_20 = 17         FIX_RATE_MCS_5_20 = 20000h           |
|       RATE_MCS_6_20 = 18         FIX_RATE_MCS_6_20 = 40000h           |
|       RATE_MCS_7_20 = 19         FIX_RATE_MCS_7_20 = 80000h           |
|       RATE_MCS_0_40 = 20         FIX_RATE_MCS_0_40 = 100000h          |
|       RATE_MCS_1_40 = 21         FIX_RATE_MCS_1_40 = 200000h          |
|       RATE_MCS_2_40 = 22         FIX_RATE_MCS_2_40 = 400000h          |
|       RATE_MCS_3_40 = 23         FIX_RATE_MCS_3_40 = 800000h          |
|       RATE_MCS_4_40 = 24         FIX_RATE_MCS_4_40 = 1000000h         |
|       RATE_MCS_5_40 = 25         FIX_RATE_MCS_5_40 = 2000000h         |
|       RATE_MCS_6_40 = 26         FIX_RATE_MCS_6_40 = 4000000h         |
|       RATE_MCS_7_40 = 27         FIX_RATE_MCS_7_40 = 8000000h         |
+-----------------------------------------------------------------------+
```

Get bit rate cmd uses same definition as set bit rate cmd



