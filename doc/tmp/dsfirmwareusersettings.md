# DS Firmware User Settings


### Current Settings (RAM 27FFC80h-27FFCEFh, DSi: 2FFFC80h-2FFFCEFh)
### User Settings 0 (Firmware 3FE00h-3FEFFh) ;(DSi & iQue use different address,
### User Settings 1 (Firmware 3FF00h-3FFFFh) ;see Firmware Header \[020h\])

```
+-----------------------------------------------------------------------------------+
|       Addr Size Expl.                                                             |
|       000h  2   Version (5) (Always 5, for all NDS/DSi Firmware versions)         |
|       002h  1   Favorite color (0..15) (0=Gray, 1=Brown, etc.)                    |
|       003h  1   Birthday month (1..12) (Binary, non-BCD)                          |
|       004h  1   Birthday day   (1..31) (Binary, non-BCD)                          |
|       005h  1   Not used (zero)                                                   |
|       006h  20  Nickname string in UTF-16 format                                  |
|       01Ah  2   Nickname length in characters    (0..10)                          |
|       01Ch  52  Message string in UTF-16 format                                   |
|       050h  2   Message length in characters     (0..26)                          |
|       052h  1   Alarm hour     (0..23) (Binary, non-BCD)                          |
|       053h  1   Alarm minute   (0..59) (Binary, non-BCD)                          |
|       054h  2                                                                     |
|       056h  1   80h=enable alarm (huh?), bit 0..6=enable?                         |
|       057h  1   Zero (1 byte)                                                     |
|       058h  2x2 Touch-screen calibration point (adc.x1,y1) 12bit ADC-position     |
|       05Ch  2x1 Touch-screen calibration point (scr.x1,y1) 8bit pixel-position    |
|       05Eh  2x2 Touch-screen calibration point (adc.x2,y2) 12bit ADC-position     |
|       062h  2x1 Touch-screen calibration point (scr.x2,y2) 8bit pixel-position    |
|       064h  2   Language and Flags (see below)                                    |
|       066h  1   Year (2000..2255) (when having entered date in the boot menu)     |
|       067h  1   Unknown (usually 00h...08h or 78h..7Fh or so)                     |
|       068h  4   RTC Offset (difference in seconds when RTC time/date was changed) |
|       06Ch  4   Not used (FFh-filled, sometimes 00h-filled) (=MSBs of above?)     |
+-----------------------------------------------------------------------------------+
```

Below not stored in RAM (found only in FLASH memory)\...

```
+------------------------------------------------------------------------------+
|       070h  2   Update counter (used to check latest) (must be 0000h..007Fh) |
|       072h  2   CRC16 of entries 00h..6Fh (70h bytes)                        |
|       074h  8Ch Not used (FFh-filled) (or extended data, see below)          |
+------------------------------------------------------------------------------+
```

Below extended data was invented for iQue DS (for adding the chinese language setting), and is also included in Nintendo DSi models. Presence of extended data is indicated in Firmware Header entry \[1Dh\].Bit6.

```
+-------------------------------------------------------------------------------------+
|       074h  1   Unknown (01h) (maybe version?)                                      |
|       075h  1   Extended Language (0..5=Same as Entry 064h, plus 6=Chinese)         |
|                 (for language 6, entry 064h defaults to english; for compatibility) |
|                 (for language 0..5, both entries 064h and 075h have same value)     |
|       076h  2   Bitmask for Supported Languages (Bit0..6)                           |
|                 (007Eh for iQue DS, ie. with chinese, but without japanese)         |
|                 (0042h for iQue DSi, chinese (and english, but only for NDS mode))  |
|                 (003Eh for DSi/EUR, ie. without chinese, and without japanese)      |
|       078h  86h Not used (FFh-filled on iQue DS, 00h-filled on DSi)                 |
|       0FEh  2   CRC16 of entries 74h..FDh (8Ah bytes)                               |
+-------------------------------------------------------------------------------------+
```

Note: The DSi does store the user settings in eMMC files (TWLCFGn.dat), that files include NDS-style settings (username etc), plus additional DSi-specific settings (country, parental controls, etc). For backwards compatibilty, the DSi does also store a copy of those settings in NDS-style format in Wifi FLASH and Main RAM at 2FFFC80h.
- [DSi SD/MMC Firmware System Settings Data Files](./dsisdmmcfirmwaresystemsettingsdatafiles.md)
DSi Backlight level and DSi sound volume seem to be stored in the BPTWL chip (or possibly in its attached I2C potentiometer).

### Language and Flags (Entry 064h)

```
+----------------------------------------------------------------------------------+
|       0..2 Language (0=Japanese, 1=English, 2=French, 3=German,                  |
|            4=Italian, 5=Spanish, 6..7=Reserved) (for Chinese see Entry 075h)     |
|            (the language setting also implies time/data format)                  |
|       3    GBA mode screen selection (0=Upper, 1=Lower)                          |
|       4-5  Backlight Level    (0..3=Low,Med,High,Max) (DS-Lite only)             |
|       6    Bootmenu Disable   (0=Manual/bootmenu, 1=Autostart Cartridge)         |
|       7-8  ?                                                                     |
|       9    Settings Lost (1=Prompt for User Info, and Language, and Calibration) |
|       10   Settings Okay (0=Prompt for User Info)                                |
|       11   Settings Okay (0=Prompt for User Info) (Same as Bit10)                |
|       12   No function                                                           |
|       13   Settings Okay (0=Prompt for User Info, and Language)                  |
|       14   Settings Okay (0=Prompt for User Info) (Same as Bit10)                |
|       15   Settings Okay (0=Prompt for User Info) (Same as Bit10)                |
+----------------------------------------------------------------------------------+
```

The Health and Safety message is skipped if Bit9=1, or if one or more of the following bits is zero: Bits 10,11,13,14,15. However, as soon as entering the bootmenu, the Penalty-Prompt occurs.

Note: There are two User Settings areas in the firmware chip, at offset 3FE00h and 3FF00h, if both areas have valid CRCs, then the current/newest area is that whose Update Counter is one bigger than in the other/older area.

```
+------------------------------------------------------------------------+
|       IF count1=((count0+1) AND 7Fh) THEN area1=newer ELSE area0=newer |
+------------------------------------------------------------------------+
```

When changing settings, the older area is overwritten with new data (and incremented Update Counter). The two areas allow to recover previous settings in case of a write-error (eg. on a battery failure during write).

### Battery Removal
Even though the battery is required only for the RTC (not for the firmware flash memory), most of the firmware user settings are reset when removing the battery. This appears to be a strange bug-or-feature of the DS bios, at least, fortunately, it still keeps the rest of the firmware intact.



