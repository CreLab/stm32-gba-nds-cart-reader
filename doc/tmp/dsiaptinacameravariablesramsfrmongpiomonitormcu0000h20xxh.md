# DSi Aptina Camera Variables: RAM/SFR/MON (GPIO/Monitor) (MCU:0000h-20xxh)


### Internal RAM (MCU:0000h..0xxxh)
Internal RAM is reserved for whatever internal purposes (probably including for storing the \'logical variables\' at MCU:2xxxh at some physical memory locations at MCU:0xxxh). However, some of those undocumented reserved RAM cells are manipulated by DSi games:

```
+-----------------------------------------------------------------------+
|       02F0h   2  UNDOC_RAM_02F0   (set to 0000h by DSi games)         |
|       02F2h   2  UNDOC_RAM_02F2   (set to 0210h by DSi games)         |
|       02F4h   2  UNDOC_RAM_02F4   (set to 001Ah by DSi games)         |
+-----------------------------------------------------------------------+
```

Exact RAM Size is unknown (around 2Kbyte or so)? Some Aptina chips do also contain some sort of User RAM (at 0800h or so) for unknown purpose (just general purpose storage maybe). Unknown if the DSi chips are having any such User RAM.

### Special Function Registers SFR (MCU:1040h..10FEh)

```
+---------------------------------------------------------------------------------+
|       1040h  ..  RESERVED_SFR_1040-1050    Reserved                             |
|       1060h  ..  RESERVED_SFR_1060-1066    Reserved (REV3)                      |
|       1070h   2  GPIO_DATA                 GPIO Data  (0..1E00h)                |
|                    0-8   Unused (0)                                             |
|                    9-12  gpio_3_0_data                                          |
|                    13-15 Unused (0)                                             |
|       1072h   2  RESERVED_SFR_1072         Reserved                             |
|       1074h   2  GPIO_OUTPUT_SET           GPIO Set   (0..0C00h/1E00h?) (W)     |
|                    0-8   Unused (0)                                             |
|                    9-12  gpio_3_0_output_toggle (uh, toggle or set?)            |
|                    13-15 Unused (0)                                             |
|       1076h   2  GPIO_OUTPUT_CLEAR         GPIO Clear (0..0C00h/1E00h?) (W)     |
|                    0-8   Unused (0)                                             |
|                    9-12  gpio_3_0_output_clear                                  |
|                    13-15 Unused (0)                                             |
|       1078h   2  GPIO_DIR                  GPIO Direction (0..1E00h, def=1E00h) |
|                    0-8   Unused (0)                                             |
|                    9     gpio_0_dir (0=Output, 1=Input) ;(LSB0 of 10bit Output) |
|                    10    gpio_1_dir (0=Output, 1=Input) ;(LSB1 of 10bit Output) |
|                    11    gpio_2_dir (0=Output, 1=Input) ;(Flash/Shutter Pulse)  |
|                    12    gpio_3_dir (0=Output, 1=Input) ;(OE_BAR for Databus)   |
|                    13-15 Unused (0)                                             |
|       107Ah  ..  RESERVED_SFR_107A-10FD    Reserved                             |
+---------------------------------------------------------------------------------+
```


### Monitor Variables MON (MCU:2000h..2025h)

```
+----------------------------------------------------------------------------------+
|       2000h   5  RESERVED_MON_00-04        Reserved                              |
|       2005h   1  MON_CMD                   Monitor Command (0..FFh)              |
|       2006h   2  MON_ARG1                  Monitor First Argument (0..FFFFh)     |
|       2008h  ..  RESERVED_MON_08-22        Reserved                              |
|       2024h   2  MON_PATCH_ID_0            Monitor First Patch (0..FFFFh) (REV1) |
|                    0-7   mon_patch_0_version (00h-0Fh)                           |
|                            The version number of the first patch (R)             |
|                    8-15  mon_patch_0_number  (00h-0Fh)                           |
|                            Identifies which patch the first patch is (R)         |
|       2024h   1  MON_PATCH_ID_0            (mask=FFh) (R) ;\unlike above  (REV3) 
|       2025h   1  MON_PATCH_ID_1            (0..FF)        ;/REV1 specs    (REV3) |
|       2026h   1  MON_PATCH_ID_2            (0..FF)                        (REV3) |
|       2027h   1  RESERVED_MON_27           Reserved                       (REV3) |
+----------------------------------------------------------------------------------+
```




