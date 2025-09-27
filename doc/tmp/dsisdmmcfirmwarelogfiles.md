# DSi SD/MMC Firmware Log Files


### FAT16:\\sys\\log\\shop.log (32 bytes)

```
+-----------------------------------------------------------------------+
|       0000h 20h   Zerofilled                                          |
+-----------------------------------------------------------------------+
```

Unknown if this file can contain anything else.

### FAT16:\\sys\\log\\product.log (573 bytes)
Contains some ASCII text with version, date (YY/MM/DD), and time (HH:SS) info (using 0Ah as CRLF):

```
+-------------------------------------------------------------------------------------+
|       0,BOARD,START,1.5,09/01/14,14:52,000055, ,                                    |
|       0,BOARD,OK,1.5,09/01/14,14:53,000055, ,                                       |
|       0,TP_CAL,OK,2.0, , , ,(647 811)-(3478 3245),                                  |
|       0,AGING,OK,1.0, , , ,Time=60:20(m:s)                                          |
|       Count=32,                                                                     |
|       0,FINAL,START,1.5,09/01/15,09:52,000084,TWL Ver.2.0,                          |
|       0,FINAL,OK,1.5,09/01/15,09:52,000084,TWL Ver.2.0,                             |
|       0,MIC,OK,2.1, , , ,All Test Passed,                                           |
|       0,CAMERA,OK,2.1, , , , ,                                                      |
|       0,WRFU,START,0.60,09/01/15,10:03,000143,P000063 G000143 717cfde74f5ef6763473, |
|       0,WRFU,OK,0.60,09/01/15,10:04,000143,PCVer:1.7f                               |
|       R-53 -55 E0.00 0.00,                                                          |
|       0,IMPORT,START,1.0, , , , ,                                                   |
|       0,IMPORT,OK,1.0, , , ,Region=EUR,                                             |
|       0,NCHECK,OK,1.0, , , , ,                                                      |
+-------------------------------------------------------------------------------------+
```


### FAT16:\\sys\\log\\sysmenu.log (16Kbytes)
Contains several groups of three text lines. Each \"#FFT\" group begins with two 0Ah characters, and is followed by space padding for 256-byte alignment of the next group).
Below is some example (with blank space removed, original 40-digit hash strings abbreviated to \"xxxx..xx\", and some lines are replaced by \"\...\").

```
+-----------------------------------------------------------------------------------+
|       #FFT 13-08-18[SUN] 12:37:10                                                 |
|       title: HNAP                                                                 |
|       DHT_PAHSE1_FAILED (sub info): hash1     - 8dfc..59                          |
|       #FFT 13-08-18[SUN] 12:37:10                                                 |
|       title: HNAP                                                                 |
|       DHT_PAHSE1_FAILED (sub info): calc_hash - 7eca..f5                          |
|       #FFT 13-08-18[SUN] 12:37:11                                                 |
|       title: HNAP                                                                 |
|       menuRedIplManager.cpp [l.514] RED FATAL 0000000010000000 (0000000041575445) |
|       #FFT 13-08-18[SUN] 12:37:11                                                 |
|       title: HNAP                                                                 |
|       menuResetCallback.cpp [l.50] type 0                                         |
|       #FFT 13-08-18[SUN] 13:44:16                                                 |
|       title: HNAP                                                                 |
|       DHT_PAHSE1_FAILED (sub info): hash1Addr-02799e38                            |
|       #FFT 13-08-18[SUN] 13:44:16                                                 |
|       title: HNAP                                                                 |
|       DHT_PAHSE1_FAILED (sub info): hash1     - 8dfc..59                          |
|       ...                                                                         |
|       ...                                                                         |
|       #FFT 13-09-10[TUE] 22:07:39                                                 |
|       title: HNAP                                                                 |
|       menuResetCallback.cpp [l.50] type 0                                         |
|       #FFT 13-09-14[SAT] 14:59:16                                                 |
|       title: HNAP                                                                 |
|       SYSMi_LoadTitleThreadFunc: some error has occurred.                         |
|       #FFT 13-09-14[SAT] 14:59:16                                                 |
|       title: HNAP                                                                 |
|       SYSMi_AuthenticateTitleThreadFunc: loaded 1 times.                          |
|       #FFT 13-09-14[SAT] 14:59:17                                                 |
|       title: HNAP                                                                 |
|       menuRedIplManager.cpp [l.514] RED FATAL 0000800000002100 (0003000049524544) |
|       #FFT 13-09-14[SAT] 14:59:17                                                 |
|       title: HNAP                                                                 |
|       menuResetCallback.cpp [l.50] type 0                                         |
|       #FFT 00-01-03[MON] 20:50:18                                                 |
|       title: HNAP                                                                 |
|       WHITELIST_NOTFOUND (sub info): no entry for phase 1/2.                      |
|       #FFT 00-01-03[MON] 20:50:18                                                 |
|       title: HNAP                                                                 |
|       WHITELIST_NOTFOUND (sub info): no entry for phase 3.                        |
|       #FFT 00-01-03[MON] 20:50:18                                                 |
|       title: HNAP                                                                 |
|       SYSMi_LoadTitleThreadFunc: some error has occurred.                         |
|       #FFT 00-01-03[MON] 20:50:18                                                 |
|       title: HNAP                                                                 |
|       SYSMi_AuthenticateTitleThreadFunc: loaded 1 times.                          |
|       #FFT 00-01-03[MON] 20:50:19                                                 |
|       title: HNAP                                                                 |
|       menuRedIplManager.cpp [l.514] RED FATAL 0000800008000100 (000000004143454b) |
|       #FFT 00-01-03[MON] 20:50:19                                                 |
|       title: HNAP                                                                 |
|       menuResetCallback.cpp [l.50] type 0                                         |
|       #FFT 00-01-05[WED] 01:03:16                                                 |
|       title: HNAP                                                                 |
|       WHITELIST_NOTFOUND (sub info): no entry for phase 1/2.                      |
|       ...                                                                         |
|       ...                                                                         |
|       #FFT 00-01-01[SAT] 00:02:37                                                 |
|       title: HNAP                                                                 |
|       SYSMi_AuthenticateTitleThreadFunc: loaded 1 times.                          |
|       #FFT 00-01-01[SAT] 00:02:38                                                 |
|       title: HNAP                                                                 |
|       menuRedIplManager.cpp [l.514] RED FATAL 0002004000000100 (00000000414e5045) |
|       #FFT 00-01-01[SAT] 00:02:38                                                 |
|       title: HNAP                                                                 |
|       menuResetCallback.cpp [l.50] type 0                                         |
+-----------------------------------------------------------------------------------+
```




