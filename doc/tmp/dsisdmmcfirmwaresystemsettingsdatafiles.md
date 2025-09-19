# DSi SD/MMC Firmware System Settings Data Files


The DSi stores System Settings (and Title ID of most recent System Menu index) on eMMC in two identical files: TWLCFG0.dat and TWLCFG1.dat.
If both files are intact then the newer file is taken (as indicated by the update counter; for some weird reason, the DSi System Menu is always updating BOTH files, so they are usually both \"newer\").
For NDS compatibility, some of the data is additionally stored on Wifi FLASH:
- [DS Firmware User Settings](./dsfirmwareusersettings.md)
The TWL data and the NDS-style data are also copied to RAM:

```
+----------------------------------------------------------------------------+
|       2000400h 128h   TWLCFGn.dat bytes [088h..1AFh]                       |
|       2FFFC80h 70h    Wifi FLASH User Settings (fmw[newest_user_settings]) |
|       2FFFDFCh 4      Pointer to 2000400h                                  |
+----------------------------------------------------------------------------+
```

For some reason, most DSi games are containing some initialization code for repairing or initializing the above pointer, as so:

```
+-----------------------------------------------------------------------+
|       if [2FFFDFCh]=0 then [2FFFDFCh]=2000400h                        |
+-----------------------------------------------------------------------+
```

The RAM data at 2000400h isn\'t actually used by too many games though (one program that is using it is Flipnote).
Some games are attempting to adopt the System Setting\'s language selection as game language, games should do that only if they do support that language (a bad example is the german version of Magic Made Fun: Deep Psyche, which defaults to French when using English as system language).

### FAT16:\\shared1\\TWLCFG0.dat (16Kbytes) (System Settings Data)
### FAT16:\\shared1\\TWLCFG1.dat (16Kbytes) (System Settings Data)

```
+-------------------------------------------------------------------------------------+
|       File RAM  Siz   Description                                                   |
|       000h -    14h   SHA1 on entries [088h..1AFh]                                  |
|       014h -    6Ch   Zerofilled                                                    |
|       080h -    1     Version or so (01h)                                           |
|       081h -    1     Update Counter (0..7Fh, wraps after 7bit)     ;fmw_user[070h] |
|       082h -    2     Zero (0000h)                                                  |
|       084h -    4     Size of below RAM area (00000128h)                            |
|       088h 000h 4     Config Flags (usually 0000000Fh)                              |
|                        bit0     Unknown      (usually 1)                            |
|                        bit1     Unknown      (usually 1)                            |
|                        bit2     LanguageSet? (usually 1)                            |
|                        bit3     Wifi Enable  (0=Disable, 1=Enable)                  |
|                        bit4     Unknown      (usually 0)                            |
|                        bit5-23  Zero                                                |
|                        bit24    EULA Flag    (0=No/CountryChanged, 1=Agreed)        |
|                        bit25-31 Zero                                                |
|       08Ch 004h 1     Zero                                                          |
|       08Dh 005h 1     Country code, same as Wii country codes (eg. 46h=Bulgaria)    |
|       08Eh 006h 1     Selected Language (eg. 1=English)        ;fmw_user[064h,075h] |
|       08Fh 007h 1     RTC Year (last date change) (max 63h=2099)    ;fmw_user[066h] |
|       090h 008h 4     RTC Offset (difference in seconds on change)  ;fmw_user[068h] |
|       094h 00Ch 4     Zerofilled (or FFh-filled) (=MSBs of above?)            06Ch? |
|       098h 010h 1     EULA Version (0=None/CountryChanged, 1=v1)        ;cart[20Eh] |
|       099h 011h 9     Zerofilled                                                    |
|       0A2h 01Ah 1     Alarm Hour   (0..17h)                         ;fmw_user[052h] |
|       0A3h 01Bh 1     Alarm Minute (0..3Bh)                         ;fmw_user[053h] |
|       0A4h 01Ch 2     Zerofilled                                                    |
|       0A6h 01Eh 1     Alarm Enable (0=Off, 1=On)                    ;fmw_user[056h] |
|       0A7h 01Fh 1     Zerofilled                                                    |
|       0A8h 020h 1     Zerofilled                                     ;\             
|       0A9h 021h 1     System Menu number of used Title Slots (0..39) ; zerofilled   |
|       0AAh 022h 1     System Menu number of free Title Slots (39..0) ; when copied  |
|       0ABh 023h 1     Unknown (0)                                    ; to RAM       |
|       0ACh 024h 1     Unknown (02h or 03h)                           ;              |
|       0ADh 025h 3     Zerofilled                                     ;              |
|       0B0h 028h 8     System Menu most recently selected Title ID    ;/ ;cart[230h] |
|       0B8h 030h 2x2   TSC calib (adc.x1,y1) 12bit ADC-position      ;fmw_user[058h] |
|       0BCh 034h 2x1   TSC calib (scr.x1,y1) 8bit pixel-position     ;fmw_user[05Ch] |
|       0BEh 036h 2x2   TSC calib (adc.x2,y2) 12bit ADC-position      ;fmw_user[05Eh] |
|       0C2h 03Ah 2x1   TSC calib (scr.x2,y2) 8bit pixel-position     ;fmw_user[062h] |
|       0C4h 03Ch 4     Unknown (9C 20 01 02)                                         |
|       0C8h 040h 4     Zerofilled                                                    |
|       0CCh 044h 1     Favorite color (also Sysmenu Cursor Color)    ;fmw_user[002h] |
|       0CDh 045h 1     Zero                                                          |
|       0CEh 046h 2     Birthday (month, day)                   ;fmw_user[003h..004h] |
|       0D0h 048h 14h+2 Nickname (UCS-2), max 10 chars+EOL      ;fmw_user[006h..019h] |
|       0E6h 05Eh 34h+2 Message (UCS-2), max 26 chars+EOL       ;fmw_user[01Ch..04Fh] |
|       11Ch 094h 1     Parental Controls Flags (bit0=Parental, bit1-6=Pictochat,etc) |
|       11Dh 095h 6     Zero                                                          |
|       123h 09Bh 1     Parental Controls Region (0=Off, 3=German/USK, 4=French?)     |
|       124h 09Ch 1     Parental Controls Years of Age Rating (00h..14h)  ;cart[2F0h] |
|       125h 09Dh 1     Parental Controls Secret Question (00h..05h)                  |
|       126h 09Eh 1     Parental Controls Unknown (can be 00h, 06h, or 07h)           |
|       127h 09Fh 2     Zero                                                          |
|       129h 0A1h 4+1   Parental Controls PIN (ASCII digits) 4 digits+EOL             |
|       12Eh 0A6h 80h+2 Parental Controls Secret Answer (UCS-2), max 64 chars+EOL     |
|       1B0h -    3E50h Unused (FFh-filled)                                           |
+-------------------------------------------------------------------------------------+
```

Additionally, there\'s some stuff in RAM (maybe current Wifi Firmware version):

```
+-------------------------------------------------------------------------------------+
|       -    128h B8h   Unused                                                        |
|       -    1E0h 1     WlFirm Type (1=DWM-W015, 2=W024, 3=W028)    ;wifi_flash[1FDh] |
|       -    1E1h 1     WlFirm Unknown (zero)                                         |
|       -    1E2h 2     WlFirm CRC16 with initial value FFFFh on [1E4h..1EFh]         |
|       -    1E4h 4     WlFirm RAM vars (500400h)  ;\                                 
|       -    1E8h 4     WlFirm RAM base (500000h)  ; as from "Wifi Firmware" file     |
|       -    1ECh 4     WlFirm RAM size (02E000h)  ;/                                 |
|       -    1F0h 10h   WlFirm Unknown (zero)                                         |
|       -    200h 14h   Hexvalues from HWINFO_N.dat                                   |
|       -    214h 0Ch   Unused/padding? (zero)                                        |
+-------------------------------------------------------------------------------------+
```


Parental controls fields are all zero when not in use.

The Wifi Enable flag is\... a surreal fake Wireless-Disable option; which does only disable the Wifi LED, the actual Wifi transmission does still work.



