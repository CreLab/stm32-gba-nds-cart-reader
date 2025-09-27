# DSi Aptina Camera Variables: AE (Auto Exposure) (MCU:22xxh)


### Auto Exposure Variables AE (MCU:2200h-2261h)

```
+-------------------------------------------------------------------------------------+
|       2200h  ..  RESERVED_AE_00            Reserved                                 |
|       2202h   1  AE_WINDOW_POS             AE Window Position Y0 and X0             |
|                    0-3  X0 (in units of 1/16th of frame width)  (0..0Fh)            |
|                    4-7  Y0 (in units of 1/16th of frame height) (0..0Fh)            |
|       2203h   1  AE_WINDOW_SIZE            AE Window Height and Width (def=FFh)     |
|                    0-3  Width  (units of 1/16th of frame width, minus 1)  (0..0Fh)  |
|                    4-7  Height (units of 1/16th of frame height, minus 1) (0..0Fh)  |
|       2204h  ..  RESERVED_AE_04            Reserved                                 |
|       2206h   1  AE_TARGET                 AE Target Brightness (0..FFh, def=32h)   |
|       2207h   1  AE_GATE                   AE Sensitivity       (0..FFh, def=04h)   |
|       2208h  ..  UNDOC_AE_08               (0..FFh, def=02h)                        |
|       2209h  ..  RESERVED_AE_09-0A         Reserved                                 |
|       220Bh   1  AE_MIN_INDEX              Min                      (0-FFh)         |
|       220Ch   1  AE_MAX_INDEX              Max allowed zone number  (0-FFh,def=18h) |
|       220Dh   1  AE_MIN_VIRTGAIN           Min allowed virtual gain (0-FFh,def=10h) |
|       220Eh   1  AE_MAX_VIRTGAIN           Max allowed virtual gain (0-FFh,def=80h) |
|       220Fh  ..  RESERVED_AE_0F-11         Reserved                                 |
|       2212h   2  AE_MAX_DGAIN_AE1          Max digital gain pre-LC  (def=8000h)     |
|       2214h  ..  RESERVED_AE_14-16         Reserved                                 |
|       2217h   1  AE_STATUS                 AE Status                                |
|                    0   AE_at_limit (1=AE reached limit)                             |
|                    1   R9_changed  (1=Need to skip frame)                           |
|                    2   Ready       (0=AE not ready, 1=AE ready)                     |
|                    3-7 Unused (0)                                                   |
|       2218h   1  AE_CURRENT_Y              Last measured luma   (0-FFh,def=4Bh) (R) |
|       2219h   2  AE_R12                    Curr shutter delay       (def=0279h) (R) |
|       221Bh   1  AE_INDEX                  Curr zone integration time (def=04h) (R) |
|       221Ch   1  AE_VIRTGAIN               Curr virtual gain    (0-FFh,def=10h) (R) |
|       221Dh  ..  RESERVED_AE_1D-1E         Reserved                                 |
|       221Fh   2  AE_DGAIN_AE1              Current digital gain pre-LC (def=0080h)  |
|       2221h  ..  RESERVED_AE_21            Reserved                                 |
|       2222h   2  AE_R9                     Current R9:0 value (0-FFFFh, def=0010h)  |
|       2224h  ..  RESERVED_AE_24-2C         Reserved                                 |
|       222Dh   2  AE_R9_STEP                Integration time per zone   (def=009Dh)  |
|       222Fh  ..  RESERVED_AE_2F-49         Reserved                                 |
|       224Ah   1  AE_TARGETMIN              Min value for target  (0..FFh, def=32h)  |
|       224Bh   1  AE_TARGETMAX              Max value for target  (0..FFh, def=96h)  |
|       224Ch   1  AE_TARGETBUFFERSPEED      Target Buffer Speed   (0..FFh, def=0Ch)  |
|       224Dh  ..  RESERVED_AE_4D            Reserved                                 |
|       224Fh   1  AE_BASETARGET             Target Base           (0..FFh, def=36h)  |
|       2250h  ..  RESERVED_AE_50-61         Reserved                                 |
|       2262h  ..  RESERVED_AE_62-64         Reserved (REV3)                          |
+-------------------------------------------------------------------------------------+
```




