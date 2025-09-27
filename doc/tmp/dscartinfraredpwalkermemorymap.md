# DS Cart Infrared P-Walker Memory Map


### P-Walker SFR Usage

```
+-----------------------------------------------------------------------------------+
|       [0FFD4h].0  Port 1 Data bit0 OUT  SPI LCD chipselect (0=select)             |
|       [0FFD4h].1  Port 1 Data bit1 OUT  SPI LCD access mode (0=Cmd, 1=Data)       |
|       [0FFD4h].2  Port 1 Data bit2 OUT  SPI EEPROM chipselect (0=select)          |
|       [0FFD6h].0  Port 3 Data bit0 OUT  IrDA PWDOWN (1=disable IrDA RX)           |
|       [0FFD6h].1  Port 3 Data bit1 IN   IrDA RXD  ;\via serial IrDA registers     
|       [0FFD6h].2  Port 3 Data bit2 OUT  IrDA TXD  ;/                              |
|       [0FFDBh].2  Port 8 Data bit2      ?                                         |
|       [0FFDBh].3  Port 8 Data bit3      ?                                         |
|       [0FFDBh].4  Port 8 Data bit4 OUT  A/D related ... whatfor LCD? accel? batt? |
|       [0FFDCh].0  Port 9 Data bit0 OUT  SPI Accelerometer chipselect (0=select)   |
|       [0FFDEh].0  Port B Data bit0 IN   ?  ;\                                     
|       [0FFDEh].2  Port B Data bit2 IN   ?  ; maybe buttons                        |
|       [0FFDEh].4  Port B Data bit4 IN   ?  ;/                                     |
|       [0FFDEh].5  Port B Data bit5 OUT  ?                                         |
|       Timer W General A/B/C  Audio Frequency/Volume                               |
|       IrDA                   IR Transfers                                         |
|       SPI                    SPI 64Kbyte EEPROM, LCD Cmd/Data, Accelerometer      |
|       A/D                    whatfor LCD? accel? batt?                            |
+-----------------------------------------------------------------------------------+
```

The SPI EEPROM uses same commands as NDS cart savedata:
- [DS Cartridge Backup](./dscartridgebackup.md)
For the other two SPI-like devices, see:
- [DS Cart Infrared P-Walker Ports LCD Controller](./dscartinfraredpwalkerportslcdcontroller.md)
- [DS Cart Infrared P-Walker Ports Accelerometer BMA150](./dscartinfraredpwalkerportsaccelerometerbma150.md)
Note: SPI LCD chipselect is also used for outputting factory test results via SPI bus (requires special hardware attached instead of the LCD screen).

### RAM Map (2Kbytes, F780h..FF7Fh)

```
+-----------------------------------------------------------------------+
|       F780h 60h      Misc variables                                   |
|       F7E0h 2        main_callback                          ;<--      |
|       F7E2h ECh      Misc variables                                   |
|       F8CEh 8+80h    Infrared RX/TX buffer hdr+data (also misc/heap)  |
|       F956h 62Ah     Temp buffer, free RAM, and stack       ;<--      |
|       FF80h -        Stacktop (end of RAM)                            |
+-----------------------------------------------------------------------+
```


### ROM Map
For some quick hacks, Dmitry recommends these ROM addresses (which won\'t work when reflashing the firmware).

```
+----------------------------------------------------------------------------------+
|       0772h          Send IR packet (F8D6h=src, r0l=len, r0h=hdr[0], r1l=hdr[1]) |
|       08D6h          Default callback (when in IR transfer mode)                 |
|       259Eh          Watchdog refresh                                            |
+----------------------------------------------------------------------------------+
```


### EEPROM Map
The EEPROM contains some important basic data, plus GUI related bitmaps (mostly text strings pre-rendered as bitmaps for the local user name & game language) (and maybe(?) also game specific customizations).

```
+-------------------------------------------------------------------------------------+
|       0000h 8        ID "nintendo" (set after initial power-up eeprom init)         |
|       0008h 8        ID whatever   (set via Cmd F0h and FEh) (never read)           |
|       0010h 62h      ???                                                            |
|       0072h 1        Number of watchdog resets                                      |
|       0073h 0Dh      ???                                                            |
|       0080h 02h+1    ADC calibration (factory-provided)               ;\            
|       0083h 28h+1    Unique ID      (set via Cmd F0h)                 ; with 1-byte |
|       00ACh 40h+1    LCD ConfigCmds (set via Cmd F0h)                 ; checksums   |
|       00EDh 68h+1    Identity Data ("provisioned" at walk start time) ; and backup  |
|       0156h 18h+1    Health Data   ("provisioned" at walk start time) ; copies at   |
|       016Fh 01h+1    Copy Flag (00h=Normal, A5h=copy was interrupted) ; 0180h-027Fh |
|       0171h 0Fh      Unused                                           ;/            |
|       0180h 100h     Backup copies of entries at 0080h-0017Fh                       |
|       0280h ...      Various Bitmaps                                                |
|       8C70h ...      Various Garbage, Bitmaps, Items, Team, Route                   |
|       CE8Ah 2        current watts written to eeprom by cmd 20h before replying     |
|                        (likely so remote can read them directly). u16 BE            |
|       CE8Ch ...      Various stuff                                                  |
|       CEF0h 1Ch      Historic step count per day. u32 each, BE,                     |
|                        [0] is yesterday, [1] is day before, etc...                  |
|       CF0Ch ...      Various stuff                                                  |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      __________________ Data Structures (in EEPROM and Packets) ___________________ |
+-------------------------------------------------------------------------------------+
```


### Unique ID (28h bytes)

```
+---------------------------------------------------------------------------+
|       00h 28h Generated by the DS game at pairing time, unique per walker |
+---------------------------------------------------------------------------+
```


### Identity Data (68h bytes) //stored reliably at 0x00ED/0x01ED
All multi-byte values LE, unless otherwise specified

```
+-----------------------------------------------------------------------------------+
|       00h 4   Unknown (LE, always 1?) ;\written from game packet at walk start    
|       04h 4   Unknown (LE, always 1?) ;  ;<-- 0 at walk end  ;copied from [0]     |
|       08h 2   Unknown (LE, always 7?) ;                                           |
|       0Ah 2   Unknown (LE, always 7?) ;/ ;<-- 0 at walk end  ;copied from [8?]    |
|       0Ch 2   TrainerTID                                                          |
|       0Eh 2   TrainerSID                                                          |
|       10h 28h Unique ID                                                           |
|       38h 10h EventBitmap (aka bitfield with 128 event flags?)                    |
|       48h 10h Trainer Name (8 chars, using a custom 16bit charset, non-unicode)   |
|       58h 1   Unknown                                                             |
|       59h 1   Unknown                                                             |
|       5Ah 1   Unknown                                                             |
|       5Bh 1   Flags (bit0=PairedToGame, bit1=HasPoke, bit2=PokeJoinedOnAWalk)     |
|       5Ch 1   ProtoVer (02h)    (written by DS, refuse peer's with other values)  |
|       5Dh 1   Unknown                                                             |
|       5Eh 1   ProtoSubver (00h) (written by DS, refuse peer's with other values)  |
|       5Fh 1   Unknown (02h)     (written by DS at walk start)                     |
|       60h 4   LastSyncTime ;Big Endian  ;in WHAT... maybe seconds since WHEN?     |
|       64h 4   StepCount    ;Big Endian  ;since WHEN... today? lifetime? lastsync? |
+-----------------------------------------------------------------------------------+
```


### Peer Play Data (38h bytes) //aka \"PEER PLAY DATA\"
All multi-byte values LE, unless otherwise specified

```
+----------------------------------------------------------------------------+
|       00h 4   curStepCount  (since WHEN?)                                  |
|       04h 2   curWatts                                                     |
|       06h 2   Unused                                                       |
|       08h 4   Unknown, copied from IdentityData[00h]                       |
|       0Ch 2   Unknown, copied from IdentityData[08h]                       |
|       0Eh 2   Species                                                      |
|       10h 16h P-Nickname   (11 chars)  ;\the actual names in bitmap format 
|       26h 10h Trainer Name (8 chars)   ;/are stored elsewhere in EEPROM?   |
|       36h 1   GenderForm                                                   |
|       37h 1   HasSpecialForms (spinda, arceus, unown, etc.)                |
+----------------------------------------------------------------------------+
```


### LcdConfigCmds (40h bytes)
Stored reliably at 00ACh/01ACh.

```
+------------------------------------------------------------------------------------+
|       00h 1   u8 contrastAndFlags (if 00h/FFh? commands at ROM:BEB8h will be used) |
|       01h 3Fh u8 commands[3fh] (Commands, or FDh,NNh=Delay(NNh), FEh=End of list)  |
+------------------------------------------------------------------------------------+
```


### Enroll Data (71h bytes)

```
+---------------------------------------------------------------------------------+
|       00h 28h Unique ID             ;always written                             |
|       28h 40h LCD Config Data       ;written or verified depending on byte[70h] |
|       68h 8   Whatever ID           ;always written to EEPROM:0008h             |
|       70h 1   LCD Action (00h=WriteA, 01h=Compare, 03h=WriteB, 02h/04h-FFh=Nop) |
+---------------------------------------------------------------------------------+
```


### HealthData (18h bytes)
Stored reliably at 0156h/0256h. Cached in RAM at F780h.
Big Endian unless otherwise noted.

```
+----------------------------------------------------------------------------------+
|       00h 4  u32 lifetimeTotalSteps                                              |
|       04h 4  u32 todaySteps           //zeroed at midnight                       |
|       08h 4  u32 lastSyncTime                                                    |
|       0Ch 2  u16 totalDays                                                       |
|       0Eh 2  u16 curWatts                                                        |
|       10h 2  u16 unk_0                                                           |
|       12h 1  u8 unk_1                                                            |
|       13h 1  u8 unk_2                                                            |
|       14h 3  u8 padding[3]                                                       |
|       17h 1  u8 settings (bit0=isOnSpecialRoute, bit1-2=Volume, bit3-6=Contrast) |
+----------------------------------------------------------------------------------+
```


See Dmitry\'s webpage for more \"game-specifc\" data structures and memory addresses.



