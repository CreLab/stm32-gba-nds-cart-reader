# DSi Aptina Camera Variables: FD (Anti-Flicker) (MCU:24xxh)


### Anti-Flicker Variables FD (MCU:2400h..247Bh)

```
+-------------------------------------------------------------------------------------+
|       2400h  ..  RESERVED_FD_00            Reserved                                 |
|       2402h   1  FD_WINDOW_POSH            Window Pos H (0..FFh, def=1Dh)           |
|                    0-3  Width (in units of 1/16th of frame width, minus 1) (0..0Fh) |
|                    4-7  X0 (=position/origin or so?) (0..0Fh)                       |
|       2403h   1  FD_WINDOW_HEIGHT          FlickerMeasurementWindowHeight (def=04h) |
|                    0-5  Flicker measurement window height in rows (0..3Fh)          |
|                    6-7  Unspecified                                                 |
|       2404h   1  FD_MODE                   Flicked Detection switches/indicators    |
|                    0-3  Reserved      (0..0Fh) (R)                                  |
|                    4    Debug_mode    (0=Disable, 1=Enable single period mode)      |
|                    5    Curr Flicker State (0=60Hz, 1=50Hz) (R)                     |
|                    6    Curr Settings (0=60Hz, 1=50Hz)                              |
|                    7    Manual Mode   (0=Disable, 1=Enable)                         |
|       2405h  ..  RESERVED_FD_05-07         Reserved                                 |
|       2408h   1  FD_SEARCH_F1_50           Search F1 50Hz  (0..FFh, def=33h)        |
|       2409h   1  FD_SEARCH_F2_50           Search F2 50Hz  (0..FFh, def=35h)        |
|       240Ah   1  FD_SEARCH_F1_60           Search F1 60Hz  (0..FFh, def=29h)        |
|       240Bh   1  FD_SEARCH_F2_60           Search F2 60Hz  (0..FFh, def=2Bh)        |
|       240Ch   1  UNDOC_FD_0C               (0..FFh)                                 |
|       240Dh   1  FD_STAT_MIN               Stat Min (0..FFh, def=03h)               |
|       240Eh   1  FD_STAT_MAX               Stat Max (0..FFh, def=05h)               |
|       240Fh  ..  RESERVED_FD_0F            Reserved                                 |
|       2410h   1  FD_MIN_AMPLITUDE          Ignore Signals below Min (0..FFh, def=5) |
|       2411h   2  FD_R9_STEP_F60_A          60HzA (def=0D4h) ;\Minimal Shutter Width 
|       2413h   2  FD_R9_STEP_F50_A          50HzA (def=103h) ; Steps for 60Hz/50H AC |
|       2415h   2  FD_R9_STEP_F60_B          60HzB (def=09Dh) ; in Context A/B        |
|       2417h   2  FD_R9_STEP_F50_B          50HzB (def=0B8h) ;/(0..FFFFh)            |
|       2419h  ..  RESERVED_FD_19-7B         Reserved                                 |
+-------------------------------------------------------------------------------------+
```




