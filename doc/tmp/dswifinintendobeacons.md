# DS Wifi Nintendo Beacons


Beacons are most commonly used to announce Wifi Internet Access Points. The special Nintendo Beacons are used to announce Local Network games (randomly broadcast on channel 1, 7, or 13).

### All beacon frames transmitted by a DS host have the following format

```
+------------------------------------------------------------------------------------+
|       TXHDR using 2MBit/s rate                                                     |
|       802.11 Management frame header                                               |
|       802.11 Beacon header (Timestamp, BeaconInterval=00xxh, Capability=0021h)     |
|       Supported rates      (Tag=01h, Len=02h, 82h,84h)       ;1Mbit/s and 2Mbit/s  |
|       Distribution Channel (Tag=03h, Len=01h, 0xh)           ;channel 1, 7, or 13  |
|       TIM vector           (Tag=05h, Len=05h, 00h,02h,0,0,0) ;adjusted by hardware |
|       Custom extension     (Tag=DDh, Len=18h+N, see below)                         |
+------------------------------------------------------------------------------------+
```


### Nintendo specific beacon info (information element Tag=DDh)

```
+-------------------------------------------------------------------------------------+
|       00h 4  Nintendo Beacon OUI (00h,09h,BFh,00h)                                  |
|       04h 2  Stepping Offset for 4808134h/W_POST_BEACON (always 000Ah)              |
|       06h 2  LCD Video Sync in 15.625Hz units (VCOUNT*7Fh-W_US_COUNT*2)/80h         |
|       08h 4  Fixed ID (00400001h)                                                   |
|       0Ch 4  Game ID  (0040xxxxh) (or 00000857h=Nintendo Zone)                      |
|       10h 2  Randomly generated Stream code (0000h..FFFFh?)                         |
|       12h 1  Number of bytes from entry 18h and up (70h for multiboot) (0 if Empty) |
|       13h 1  Beacon Type (1=Multicart/Pictochat, 9=Empty, 0Bh=Multiboot, ?=Zone)    |
|       14h 2  CMD data size   (01FEh = FFh halfwords) (or 0100h)                     |
|       16h 2  REPLY data size (0008h = 4 halfwords)                                  |
+-------------------------------------------------------------------------------------+
```

For Empty (length zero, may occur at very begin of multiboot)

```
+-----------------------------------------------------------------------+
|       18h -  Nothing, no data                                         |
+-----------------------------------------------------------------------+
```

For Multicart (variable length)

```
+------------------------------------------------------------------------------------+
|       18h .. Custom data, usually containing the host name, either in 8bit ascii,  |
|              or 16bit unicode format. Sometimes taken from Firmware User Settings, |
|              and sometimes from Cartridge Backup Memory.                           |
+------------------------------------------------------------------------------------+
```

For Pictochat (length 8)

```
+--------------------------------------------------------------------------+
|       18h 2  Fixed (always 2348h)                                        |
|       1Ah 2  Unknown xxxx                                                |
|       1Ch 1  Chatroom number (00h..03h for Chatroom A..D)                |
|       1Dh 1  Number of users already connected (1..16, including master) |
|       1Eh 2  Fixed (always 0004h)                                        |
+--------------------------------------------------------------------------+
```

For Multiboot (aka DS Download Play) (always 70h bytes)

```
+-------------------------------------------------------------------------------------+
|       18h 4  Game ID (0040xxxxh) (same as [0Ch]) (varies from game to game)         |
|       1Ch 1  Last Snippet flag (00h=Snippet #0..8, 02h=Snippet #9)                  |
|       1Dh 1  Session Number (00h=First) (increments when restarting a new upload)   |
|       1Eh 1  Number of slaves already connected (0..15, excluding master)           |
|                Uh, actually [1Eh] is always 01h, even for 2..3 slaves?              |
|       1Fh 1  Snippet number (0..9=Snippet #0..9)                                    |
|       20h 2  Checksum (on entries [22h..87h])                                       |
|               chksum=0, for i=22h to 86h step 2, chksum=chksum+halfword[i], next i, |
|               chksum=FFFFh AND NOT (chksum+chksum/10000h)                           |
|       22h 1  In Snippet #0..8: Snippet number (0..8, same as [1Fh])                 |
|              In Snippet #9: Number or players connected (0..16, may include master) |
|       23h 1  Highest Snippet number (09h=Snippet #9)                                |
|       24h 2  In Snippet #0..8: Snippet Size in bytes (62h for #0..7, 48h for #8)    |
|              In Snippet #9: Player Mask (eg. 000Fh=4-Players, including Master)     |
|       26h 62h Snippet Data (always 62h bytes, zeropadded if size<62h)               |
+-------------------------------------------------------------------------------------+
```

For Nintendo Zone (with Game ID=00000857h) (always 70h bytes):

```
+-----------------------------------------------------------------------+
|       18h 70h Encrypted Nintendo Zone Beacon Info (see below)         |
+-----------------------------------------------------------------------+
```


### Multiboot Advertisement Snippets
Snippet #0..8 are merged to form a larger datablock with following info:

```
+---------------------------------------------------------------------------------+
|       000h 32  Icon Palette (same as for ROM Cartridge Icon)                    |
|       020h 512 Icon Bitmap  (same as for ROM Cartridge Icon)                    |
|       220h 1   Favorite color (00h..0Fh)       ;\                               
|       221h 1   Username Length (0..10)         ; from firmware user settings    |
|       222h 20  Username (max 10 chars UCS-2)   ;/                               |
|       236h 1   Max number of players (1..16, may include master)                |
|       237h 1   Unknown (00h)                                                    |
|       238h 96  Game name (48 UCS-2)   (same as 1st line of ROM Cartridge Title) |
|       298h 192 Description (96 UCS-2) (same as further lines of ROM Cart Title) |
|       358h 26  Unused (padding 48h-byte Snippet #8 to 62h-byte size)            |
+---------------------------------------------------------------------------------+
```

Snippet #9 contains slave names:

```
+------------------------------------------------------------------------------------+
|       000h 2   Slave Mask (eg. 000Eh for three slaves) (initially 0000h, see note) |
|       002h 1   Slave 1 Number*10h+Color (10h+color)     ;\                         
|       003h 1   Slave 1 Username Length (0..10)          ; Slave 1 (if any)         |
|       004h 14h Slave 1 Username (max 10 chars UCS-2)    ;/                         |
|       018h 1   Slave 2 Number*10h+Color (20h+color)     ;\                         
|       019h 1   Slave 2 Username Length (0..10)          ; Slave 2 (if any)         |
|       01Ah 14h Slave 2 Username (max 10 chars UCS-2)    ;/                         |
|       01Eh 1   Slave 3 Number*10h+Color (30h+color)     ;\                         
|       01Fh 1   Slave 3 Username Length (0..10)          ; Slave 3 (if any)         |
|       020h 14h Slave 3 Username (max 10 chars UCS-2)    ;/                         |
|       ...                                                                          |
+------------------------------------------------------------------------------------+
```

Note: The slave Mask is initially 0000h, and isn\'t updated until AFTER having transferred the first some Data packets.
Unknown if there can be more 62h-byte snippets appended (if any games support 5 or more slaves).

### Authentication/Association process
Connecting to a Host console is done via standard 802.11 managment frames. The Auth/Assoc Requests must be sent during the listen interval (ie. shortly after having received beacons).

```
+-----------------------------------------------------------------------------+
|       Host sends beacon(s)                                                  |
|       Client sends an Authentication Request (AuthSeq=1)            ;\Auth  
|       Host sends an Authentication Response (AuthSeq=2)             ;/      |
|       Host sends beacon(s)                                                  |
|       Client sends an Association Request (with special SSID)       ;\Assoc 
|       Host sends an Association Response                            ;/      |
|       Host sends beacon(s) and begins sending CMD/Data packets              |
+-----------------------------------------------------------------------------+
```

The Nintendo Beacons are transferred without public SSID (without Tag=00h). However, the Association Request must contain a SSID, which is derived from the custom Tag=DDh area.

```
+-----------------------------------------------------------------------+
|      SSID for multiboot (20h-byte binary, non-ASCII):                 |
|       00h 4   Game ID (0040xxxxh) (from Beacon Tag=DDh, entry 0Ch)    |
|       04h 2   Stream code         (from Beacon Tag=DDh, entry 10h)    |
|       06h 1Ah Zerofilled                                              |
+-----------------------------------------------------------------------+
```

Multicart games or Pictochat may use whatever SSID\'s they want (unknown if there is standard for that).

### Encrypted Nintendo Zone Beacon Info (with Game ID=00000857h)
Nintendo Zone beacons are broadcast by DS consoles with special \"Beacon Cartridges\" (that console is merely sending beacons, it doesn\'t act as an Access Point itself. Instead, the beacon contains the SSID/password for the actual Access Point in the Shop/Restaurant, or for your own home network).
The SSID/Password in the Zone Beacons can be also used by DSi games and DSi browser (depending on the Flags at \[66h\]).

```
+------------------------------------------------------------------------------------+
|       00h 32  Access Point SSID (ASCII, zeropadded if shorter than 32 chars)       |
|       20h 10  Server ApNum (ASCII, ten digits/chars...?)                           |
|       2Ah 2   Unknown (0001h)                                                      |
|       2Ch 24  Server? Retailer ID string? (eg. "ShopName Country") (purpose=?)     |
|       44h 32  Access Point WEP key (0/5/13/16 bytes) or WPA/WPA2 password          |
|       64h 1   Unknown (00h for DSi, other values for 3DS)                          |
|       65h 1   Access Point WEP mode (0=Open, 1/2/3=5/13/16 bytes)                  |
|               (only on 3DS?: 4=WPA-TKIP, 5=WPA2-TKIP, 6=WPA-AES, 7=WPA2-AES)       |
|       66h 2   Flags (0003h)                                                        |
|                 Bit0: Enable Nintendo Zone content on DS(i)                        |
|                 Bit1: Enable Online Gaming and Friend list                         |
|                 Bit4: Enable Nintendo Zone Viewer on 3DS                           |
|                 Bit7: Block Nintendo eShop                                         |
|                 Bit8: Block Internet Browser                                       |
|       68h 4   Unknown (uh, maybe zero?)                                            |
|       6Ch 2   Unknown (0428h)                                                      |
|       6Eh 2   CRC16 with initial value 0 across [00h..6Dh] (or optionally 0=NoCrc) |
+------------------------------------------------------------------------------------+
```

The above 70h-bytes are RC4 encrypted (the WEP encryption algorithm) with an 8-byte key:

```
+-----------------------------------------------------------------------+
|       Key[0..3] = "!SDW" (aka "WDS!" backwards)                       |
|       Key[4..7] = Last 4 bytes of the 6-byte BSSID from Beacon header |
+-----------------------------------------------------------------------+
```

When receiving the Nintendo Zone beacon, DSi Launcher will add some animation to the Nintendo Zone icon. The Nintendo Zone tool will occassionally show a green signal strength symbol in upper right (if the SSID and WEP password match for your Access Point). Moreover, the tool should then connect to the server (supposedly using the ApNum entry), but that step seems to fail, probably because Nintendo has shut down the Zone servers someday in 2016-2018.
ApNum:
\"Authentication parameter, required for connecting to the server. server uses this to determine which third-party content to link to on the index page. First ASCII number char in this param is region, this is also used to determine which server to connect to. Regions: 0=JP, 1=USA, 2/3=EUR, 4=KOR, 5=China, ?=TWN.\" Uh, unknown if those \"digits\" are letters or digits? There is a screenshot showing \"1BBUSMN000\" for Bestbuy. The 3DS has a hotspot.conf file with numeric ApNums, eg. \"2013300000\". Unknown if the region digit is required to match the console region.



