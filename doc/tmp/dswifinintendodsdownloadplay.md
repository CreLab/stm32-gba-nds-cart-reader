# DS Wifi Nintendo DS Download Play


DS Download Play allows to download small games from other NDS/DSi consoles. This is also known as Wireless Multiboot (WMB), or Single Gamecart Multiplay.

Before downloading: Receive beacons, display Icon/Title, prompt user whether to download that title, and, if so, connect to host (via authentication and association requests). See previous chapter for details.

### Download process (after authentication/association)

```
+-----------------------------------------------------------------------------+
|       Host sends NameRequests, client(s) send UsernameReply                 |
|       Host sends RSA frame, client(s) send RsaReply                         |
|       Host sends Data (Header/ARM9/ARM7 binaries), client(s) send DataReply |
|       Host sends Data, if it's the last packet, client(s) send GotAllReply  |
|       Host sends Final message, client(s) send FinalReply                   |
|       Client(s) send Deauthentication with Reason=3 and jump to entrypoints |
+-----------------------------------------------------------------------------+
```

The whole transfer is done at 2MBit/s, without any WEP/WPA encryption, and without ARM9 Secure Area encryption.

### CMD DATA, Host-to-client packets (with DA = 03:09:BF:00:00:00)
Sent via 4808090h/W_TXBUF_CMD (multiplayer master)

```
+------------------------------------------------------------------------------------+
|       00h 2   Value for W_CMD_REPLYTIME (0106h)                                    |
|       02h 2   Slave Flags, bit1..15 for slave 1..15 (1=connected) (eg. 0002h)      |
|       04h 1   Size in halfwords of Command+Data (ie. [06h..end, excluding footer]) |
|       05h 1   Flags   (11h=Normal, 01h=Footerless/Can be ignored, 00h=Deauth'ed?)  |
|       06h 1   Command (01h=NameRequest, 03h=RSA, 04h=DataPacket, 05h=Done)         |
|      For Command 00h (Dummy, NameDone/RsaDone/DataDone):                 ;\        
|       07h 5   Unused (zerofilled)                                        ;         |
|      For Command 01h (NameRequest):                                      ;         |
|       07h 5   Unused (zerofilled)                                        ;         |
|      For Command 02h (Error: Wrong Game Serial):                         ;         |
|       07h 5   Unused (zerofilled)                                        ; Data    |
|      For Command 03h (RSA):                                              ;         |
|       07h E4h RSA Signature Frame (see below)                            ;         |
|       EBh 5   Unused (zerofilled)                                        ;         |
|      For Command 04h (Data Packet):                                      ;         |
|       07h 2   Unknown (zero)                                             ;         |
|       09h 2   Packet Number (0=Header, 1..N=ARM9, N+1..Last=ARM7)        ;         |
|       0Bh ..  Data (1F8h bytes, or less for Header, or end of ARM7/ARM9) ;         |
|       xxh 1   Unused (zero)                                              ;         |
|      For Command 05h (Final):                                            ;         |
|       07h 5   Unused (garbage, same as last data command)                ;         |
|      For Command 06h (Unknown): ;normally not used, but ds download play ;         |
|       07h ..  Unknown           ;supports cmd 02h,03h,06h after username ;/        |
|      Extra Footer (usually present, unless Flags [05h].bit4=0):          ;\        
|       xxh 2   Slave Flags, again? (0002h)  ;or 0000h ?                   ; Footer  |
|       Note: The footer is usually present in most or all packets         ;         |
|       (Super Mario 64 DS has some dummy packets without footer)          ;/        |
+------------------------------------------------------------------------------------+
```

The packet number (and info from RSA frame) allow to compute the packet destination address. That max packet size is 1F8h bytes (at least so when using default Tag=DDh \[14h\]=1FEh).
The transfer is usually done with increasing packet numbers. However, there may be lost or duplicated packets. And the uploader tends to do weird things like starting with packet 0001h instead of 0000h, and once or then inserting packet 0000h (or other unrequested packets) during transfer.
Essentially, the downloader should maintain a flag array to know which packets were already received, and which ones still need to be requested in Data Replys. The uploader should ignore slightly outdated replies (keep sending the next packet if the wanted packet number is same as most recently transferred one).

### REPLY, Client to Host Replies (with DA = 03:09:BF:00:00:10)
Sent via 4808094h/W_TXBUF_REPLY1 (multiplayer slave).

```
+-----------------------------------------------------------------------------------+
|       00h 1  Size in halfwords (of [02h..end])?  (00h=Short, or 04h=Normal)       |
|       01h 1  Flags?                              (00h, 01h, 81h, or 80h)          |
|      Short Dummy Reply:                                                           |
|       02h -  Nothing (can occur once or then during username or data transfer)    |
|      Normal Dummy Reply:                                                          |
|       02h 1  Reply Type (00h=Dummy) (can occur before username transfer)          |
|       03h 7  Unused (zerofilled)                                                  |
|      Username Reply:                                                              |
|       02h 1  Reply Type (07h=Username)                                            |
|       03h 1  Username snippet number (00h..04h=Snippet #0..4)                     |
|       04h 6  Snippet 0: Game ID (0040xxxxh), Favorite Color, UsernameLength(0-10) |
|       04h 6  Snippet 1: Username Char[0,1,2]                                      |
|       04h 6  Snippet 2: Username Char[3,4,5]                                      |
|       04h 6  Snippet 3: Username Char[6,7,8]                                      |
|       04h 6  Snippet 4: Username Char[9], 0001h/0002h, C500h/0000h                |
|       (There can be more (smaller) snippets if Tag=DDh [16h] is smaller than 8)   |
|      Rsa Reply:                                                                   |
|       02h 1  Reply Type (08h=RsaReply)                                            |
|       03h 7  Unused (garbage, usually same as Username Snippet #2)                |
|      Data Reply:                                                                  |
|       02h 1  Reply Type (09h=DataReply)                                           |
|       03h 2  Next wanted packet number (smallest missing packet number)           |
|       05h 2  Number of different packets received (0001h..Total-1)                |
|       07h 3  Unused (zerofilled)                                                  |
|      Got All Reply:                                                               |
|       02h 1  Reply Type (0Ah=GotAllReply, no further packets needed)              |
|       03h 7  Garbage (old values from last Data Reply)                            |
|      Final Reply:                                                                 |
|       02h 1  Reply Type (0Bh=FinalReply, confirms the FinalCommand)               |
|       03h 7  Garbage (old values from last Data Reply)                            |
+-----------------------------------------------------------------------------------+
```

Ideally, software should update the reply immediately after receiving the command (within a few hundred clock cycles) (when failing to write W_TXBUF_REPLY1 in time, the hardware does reportedly generate a completely Empty Dummy Reply with 0-byte data, and FC=0158h).

### CMD ACK, Host to client acknowledgements (with DA = 03:09:BF:00:00:03)
Generated automatically by hardware (after sending W_TXBUF_CMD and after receiving Replies) (DA seems to be fully hardcoded in hardware, the other IEEE header fields might be derived from preceeding RX/TX packets and/or from hardware registers).

```
+---------------------------------------------------------------------------------+
|       00h 2  Unknown/random? (eg. 0046h or 001Bh)                               |
|       02h 2  Error Flags (bit1-15=No reply from Slave 1-15, eg. when AID_LOW=0) |
+---------------------------------------------------------------------------------+
```

Note: The SEQNO value in the IEEE header of CMD ACK must be reportedly one higher than in the corresponding CMD packet (the NDS hardware is doing that automatically, but one may need to take care of it on non-NDS hardware).

### RSA signature frame payload (Command 03h)
\"Notably: the RSA frame itself is not included as part of the data being signed, bringing up various security issues and making Nintendo\'s firmware engineers look amateurish at best.\"

```
+---------------------------------------------------------------------------------+
|       00h 4   ARM9 Entrypoint             (usually 20008xxh)                    |
|       04h 4   ARM7 Entrypoint             (usually 2380000h) (or WRAM?)         |
|       08h 4   Zerofilled                                                        |
|       0Ch 4   Header Destination (temp)   (usually 27FFE00h)                    |
|       10h 4   Header Destination (actual) (usually 27FFE00h)                    |
|       14h 4   Header Size (160h)                                                |
|       18h 4   Zerofilled                                                        |
|       1Ch 4   ARM9 Destination (temp)     (usually 2000000h)                    |
|       20h 4   ARM9 Destination (actual)   (usually 2000000h)                    |
|       24h 4   ARM9 Size                                                         |
|       28h 4   Zerofilled                                                        |
|       2Ch 4   ARM7 Destination (temp)     (usually 22C0000h in Main RAM)        |
|       30h 4   ARM7 Destination (actual)   (usually 2380000h) (or WRAM?)         |
|       34h 4   ARM7 Size                                                         |
|       38h 4   Unknown (00000001h)                                               |
|       3Ch 4   Signature ID   (61h,63h,01h,00h) (aka "ac", or backwards "ca") ;\ 
|       40h 80h Signature RSA  (RSA signature in OpenPGP SHA1 format)          ;  |
|       C0h 4   Signature Seed (same as value used to create RSA signature)    ;/ |
|                              (Nanostray:22AA9FC2h, Hedge:24272349h)             |
|                              (Eragon:2512EE7Ah, TableHockey:02704DF6h)          |
|       C4h 20h Zerofilled (stored together with above in E4h-byte array)         |
+---------------------------------------------------------------------------------+
```

The temp/actual destination addresses are usually identical, except for ARM7 which is loaded to a separate temp address in Main RAM (needed there for computing its SHA1 on ARM9 side).
The RSA signature is as so: First compute SHA1\'s on Header and ARM9 and ARM7 areas, and store them in a 40h-byte array:

```
+-----------------------------------------------------------------------+
|       00h 14h SHA1 on Header                                          |
|       14h 14h SHA1 on ARM9 bootcode                                   |
|       28h 14h SHA1 on ARM7 bootcode                                   |
|       3Ch 4   Signature Seed (same as the four bytes from [C0h])      |
+-----------------------------------------------------------------------+
```

Then compute a SHA1 on that 40h-byte array, that SHA1 value is then used in the RSA signature (in OpenPGP SHA1 format, ie. same as SWI 23h in DSi BIOS). The RSA private key is unknown, the RSA public key (9Eh,C1h,CCh,C0h,\...) can be found in the NDS Firmware and in the DSi\'s DS Download Play utility.
Unknown if the 4-byte Seed value is having any special meaning (eg. it might be some checksum, or it might be just some random, timestamp, or dummy expiredate?).
The 4+80h+4 signature bytes at \[3Ch..C3h\] are conventionally stored at the \"end\" of the binary, ie. at the offset specified in cartheader\[080h\].

### 160h-byte Header
Some Download Play titles have faulty header entries (eg. Table Hockey Tech Demo, with nonsense Icon offset etc). In such cases, dumps are conventionally having a manually repaired header & an extra copy of the original header:

```
+------------------------------------------------------------------------------------+
|       0000h 160h  Repaired Header (address/size/entrypoint for ARM9,ARM7,Icon,RSA) |
|       0160h A0h   Zerofilled                                                       |
|       0200h 10h   ID "DS DOWNLOAD PLAY" (8bit characters)                          |
|       0210h 10h   ID "----------------" (8bit characters)                          |
|       0220h 160h  Original Header (to be uploaded for RSA check)                   |
|       0380h 10h   ID "----------------" (8bit characters)                          |
|       0390h 10h   ID "Nintendo"         (16bit characters)                         |
|       03A0h 10h   ID Zerofilled                                                    |
|       03B0h 10h   ID "----------------" (8bit characters)                          |
|       03C0h ..    Zerofilled                                                       |
+------------------------------------------------------------------------------------+
```

The 160h-byte Header itself is about same as in ROM-images. The Icon/Title entry contains the information that is broadcast in Beacons. The Total Size entry points to the 88h-byte RSA Signature. The File/Overlay entries contain unused/dummy values.

### Beacons
Beacons should be kept sent during transfer, however, the DS Download tool throws a Deauth message when receiving more than 15 beacons with data traffic (ie. one must pause uploading at least each 16th beacon).
Also, the download should try to sync itself to the LCD Video Sync value in the Beacon (supposedly interpreted relative to the IEEE Beacon Timestamp) (with small uploads, there\'s probably not enough time to complete the synchronization, so the uploaded executable may still have to finish the synchronization by itself).

### Entrypoint/Memory
The Entrypoints are supposedly taken from the RSA frame (not from the 160h-byte header)? There is some error checking on the RSA frame addresses (eg. ARM7 area must exist and must apparently point to RAM or WRAM). Additionally, there is some special info in RAM:

```
+------------------------------------------------------------------------------------+
|       27FFC40h 2   Boot Indicator (2=Booted from DS Download Play via Wifi)        |
|       27FFC42h 2   Beacon Size (0060h, based on Tag=DDh size: "(88h-08h+41h)/2")   |
|       27FFC44h 2   Looks like RSSI Signal Strength AND FEh (eg. 12h=Low, 82h=High) |
|       27FFC46h 6   BSSID (master's MAC address)                                    |
|       27FFC4Ch 2   SSID Size? (0020h)                                              |
|       27FFC4Eh 4   SSID Game Serial ID (0040xxxxh)                                 |
|       27FFC52h 2   SSID Random Stream ID (xxxxh)                                   |
|       27FFC54h 1Ah SSID Padding? (zerofilled)                                      |
|       27FFC6Eh 2   Beacon Capabilities (0021h)                                     |
|       27FFC70h 2   Beacon Rates (bit0/1 = 1/2Mbit/s) (0003h)                       |
|       27FFC72h 2   Beacon Rates (same as above)      (0003h)                       |
|       27FFC74h 2   Beacon Interval (00Cxh..00Dxh)                                  |
|       27FFC76h 2   Beacon TIM ListenInt (0002h)                                    |
|       27FFC78h 2   Beacon Channel (1, 7, or 13)                                    |
|       27FFC7Ah 04h Unknown (zerofilled)                                            |
|       27FFC7Eh 2   Unused? (zero) (not part of 3Ch-bytes at 27FFC42h)              |
+------------------------------------------------------------------------------------+
```

Multiplayer games can use that info for communicating with each other after the upload. The player number (needed for more than 2 players) doesn\'t seem to be included in that structure, it might be still in W_AID_LOW though?

### List of DS Download Play Games
Games with DS Download Play Support (single-cart multiplayer):

```
+---------------------------------------------------------------------------+
|       Game ID   Players  Title                                            |
|       00400136h 2        Over the Hedge (download contains a 2D minigame) |
|       00400052h 2        Nanostray                                        |
|       00400011h 1-4      Super Mario 64 DS                                |
|       etc. (unknown if/which games support more than 4 players)           |
+---------------------------------------------------------------------------+
```

Demos available from DS Download Stations (or was that pre-Download Station?):

```
+-----------------------------------------------------------------------+
|       Eragon                                                          |
|       Lara Croft Tomb Raider Legend                                   |
|       Magnetica                                                       |
|       Metroid Prime Hunters Demo                                      |
|       Submarine Tech Demo                                             |
|       (and many trailers with non-playable movie clips)               |
+-----------------------------------------------------------------------+
```

Download Station (in shops):

```
+------------------------------------------------------------------------------+
|       Allows to download some bootmenu, offering downloading demos/trailers? |
+------------------------------------------------------------------------------+
```


### Exploits (not sure what they do)

```
+-----------------------------------------------------------------------------------+
|       WifiMe - downloader patch for NDS firmware without RSA check?               |
|       Unlaunch.dsi v2.1 - can patch RSA check in DSi's DS Download Play           |
|       HaxxStation - uploader patch for Download Station to upload homebrew/hacks? |
+-----------------------------------------------------------------------------------+
```

Unknown if unchecked entries in RSA frame can be also used to crash/boot?
Unknown if public RSA key can be found in gigaleak or so?

### NDS/DSi Games with DS Download Play support

```
+-----------------------------------------------------------------------+
|      100 Classic Books                                                |
|      Absolute Chess (Nintendo DSiWare)                                |
|      Absolute Reversi (Nintendo DSiWare)                              |
|      Advance Wars: Dual Strike                                        |
|      Age Of Empires: Mythologies                                      |
|      America's Test Kitchen: Let's Get Cooking                        |
|      Animaniacs: Lights, Camera, Action!                              |
|      Arkanoid DS                                                      |
|      Art Academy                                                      |
|      Atari Greatest Hits Volume 1                                     |
|      Atari Greatest Hits Volume 2                                     |
|      Avatar, The Last Airbender: Into The Inferno                     |
|      Bakugan: Defenders Of The Core                                   |
|      Battle Of Giants: Dinosaurs                                      |
|      Battle Of Giants: Dragons                                        |
|      Battle Of Giants: Mutant Insects                                 |
|      Beyblade: Metal Fusion                                           |
|      Big Bang Mini                                                    |
|      Big Brain Academy                                                |
|      Bleach: Blade Of Fate, The                                       |
|      Bleach: Dark Souls                                               |
|      Boing! Docomodake DS                                             |
|      Bomberman                                                        |
|      Bomberman Land Touch!                                            |
|      Bomberman Land Touch! 2                                          |
|      Boogie                                                           |
|      Bookworm (retail version)                                        |
|      Brain Age: Train Your Brain In Minutes A Day!                    |
|      Brain Age 2: More Training In Minutes A Day!                     |
|      Brain Assist                                                     |
|      Brain Voyage                                                     |
|      Bratz: Forever Diamondz                                          |
|      Break 'Em All                                                    |
|      Burnout Legends                                                  |
|      Bust-A-Move DS                                                   |
|      Call Of Duty 4: Modern Warfare                                   |
|      Candace Kane's Candy Factory                                     |
|      Carnival Games                                                   |
|      Cars 2                                                           |
|      Cars Mater-National                                              |
|      Cars Race-O-Rama                                                 |
|      Cartoon Network Racing                                           |
|      Chameleon                                                        |
|      Cheetah Girls, The: Passport To Stardom                          |
|      Chessmaster: The Art Of Learning                                 |
|      Classic Word Games                                               |
|      Club Penguin: Elite Penguin Force                                |
|      Club Penguin: Elite Penguin Force - Herbert's Revenge            |
|      Clubhouse Games                                                  |
|      Clubhouse Games Express: Card Classics (Nintendo DSiWare)        |
|      Clubhouse Games Express: Family Favorites (Nintendo DSiWare)     |
|      Clubhouse Games Express: Strategy Pack (Nintendo DSiWare)        |
|      Cookie & Cream                                                   |
|      Cooking Mama                                                     |
|      Cooking Mama 2: Dinner With Friends                              |
|      Cooking Mama 3: Shop & Chop                                      |
|      C.O.R.E.                                                         |
|      Corvette Evolution GT                                            |
|      Cosmo Fighters (Nintendo DSiWare)                                |
|      Crafting Mama                                                    |
|      Crash Boom Bang!                                                 |
|      Custom Robo Arena                                                |
|      Dairojo! Samurai Defenders (Nintendo DSiWare)                    |
|      Deca Sports DS                                                   |
|      Diary Girl                                                       |
|      Diddy Kong Racing DS                                             |
|      Dino Master: Dig, Discover, Duel                                 |
|      DiRT 2                                                           |
|      Disney Fairies: Tinker Bell                                      |
|      DK Jungle Climber                                                |
|      Dokapon Journey                                                  |
|      Draglade                                                         |
|      Dragon Ball Z: Harukanaru Densetsu                               |
|      Dragon Booster                                                   |
|      Dragon Quest Heroes: Rocket Slime                                |
|      Dreamer: Pop Star                                                |
|      Dropcast                                                         |
|      Eco-Creatures: Save The Forrest                                  |
|      Elite Beat Agents                                                |
|      Everyday Soccer (Nintendo DSiWare)                               |
|      Ferrari Challenge: Trofeo Pirelli                                |
|      FIFA Soccer 06                                                   |
|      FIFA Soccer 08                                                   |
|      FIFA Soccer 09                                                   |
|      FIFA Soccer 10                                                   |
|      FIFA Street 3                                                    |
|      FIFA World Cup 06                                                |
|      Final Fantasy Fables: Chocobo Tales                              |
|      Flash Focus: Vision Training In Minutes A Day                    |
|      Foto Frenzy                                                      |
|      Freedom Wings                                                    |
|      Fritz Chess                                                      |
|      Frogger: Helmet Chaos                                            |
|      Gardening Mama                                                   |
|      Gauntlet                                                         |
|      Geometry Wars: Galaxies                                          |
|      Godzilla: Unleashed Double Smash                                 |
|      Golden Compass, The                                              |
|      GoldenEye: Rogue Agent                                           |
|      Grease                                                           |
|      GRID                                                             |
|      Gunpey DS                                                        |
|      Harry Potter And The Deathly Hallows, Part 1                     |
|      Harry Potter And The Deathly Hallows, Part 2                     |
|      Harry Potter And The Order Of The Phoenix                        |
|      Harvest Moon: Frantic Farming                                    |
|      Hasbro Family Game Night                                         |
|      Hearts Spades Euchre (Nintendo DSiWare)                          |
|      Heavy Armor Brigade                                              |
|      High School Musical 2: Work This Out!                            |
|      Homie Rollerz                                                    |
|      Igor: The Game                                                   |
|      Imagine Babysitters                                              |
|      Imagine Ballet Star                                              |
|      Imagine Ice Champions                                            |
|      Imagine Rock Star                                                |
|      Imagine Teacher                                                  |
|      Intellivision Lives!                                             |
|      Ivy The Kiwi? (retail version)                                   |
|      Jeopardy                                                         |
|      Jewel Quest Expeditions                                          |
|      Jumble Madness                                                   |
|      Kirby: Squeak Squad                                              |
|      Kirby Super Star Ultra                                           |
|      Konami Classics Series: Arcade Hits                              |
|      Labyrinth                                                        |
|      Learn Science                                                    |
|      Left Brain Right Brain                                           |
|      Left Brain Right Brain 2                                         |
|      Legend Of Zelda, The: Phantom Hourglass                          |
|      Legend Of Zelda, The: Spirit Tracks                              |
|      Legendary Starfy, The                                            |
|      LEGO Star Wars II: The Original Trilogy                          |
|      Little League World Series Baseball 2009                         |
|      L.O.L.                                                           |
|      Lost In Blue 2                                                   |
|      Lost In Blue 3                                                   |
|      Lunar Knights                                                    |
|      Madagascar                                                       |
|      Madagascar: Escape 2 Africa                                      |
|      Madden NFL 08                                                    |
|      Madden NFL 09                                                    |
|      Magnetica                                                        |
|      Mario & Sonic At The Olympic Games                               |
|      Mario & Sonic At The Olympic Winter Games                        |
|      Mario Hoops 3-On-3                                               |
|      Mario Kart DS                                                    |
|      Mario Party DS                                                   |
|      Mario Vs. Donkey Kong 2: March Of The Minis                      |
|      Marvel Super Hero Squad                                          |
|      Math Play                                                        |
|      Mega Man ZX Advent                                               |
|      Meteos                                                           |
|      Meteos: Disney Magic                                             |
|      Metroid Prime Hunters                                            |
|      Metroid Prime Pinball                                            |
|      Might & Magic: Clash Of Heroes                                   |
|      Mini Ninjas                                                      |
|      MLB Power Pros 2008                                              |
|      Monopoly/Boggle/Yahtzee/Battleship                               |
|      Monster Band                                                     |
|      Monster Bomber                                                   |
|      Monster Racers                                                   |
|      Monsters Vs Aliens                                               |
|      MX Vs ATV Reflex                                                 |
|      My DoItAll                                                       |
|      My Frogger Toy Trials                                            |
|      My Word Coach                                                    |
|      MySims                                                           |
|      MySims Agents                                                    |
|      MySims Kingdom                                                   |
|      MySims Party                                                     |
|      MySims Racing                                                    |
|      MySims SkyHeroes                                                 |
|      Nacho Libre                                                      |
|      Namco Museum DS                                                  |
|      Nanostray                                                        |
|      Nanostray 2                                                      |
|      Need For Speed Carbon: Own The City                              |
|      Need For Speed: Nitro                                            |
|      Need For Speed: ProStreet                                        |
|      Need For Speed: Undercover                                       |
|      Nervous Brickdown                                                |
|      NEVES                                                            |
|      New Carnival Games                                               |
|      New International Track & Field                                  |
|      New Super Mario Bros.                                            |
|      New York Times Crosswords, The                                   |
|      Nicktoons: Attack Of The ToyBots                                 |
|      Nicktoons: Battle For Volcano Island                             |
|      Ninjatown                                                        |
|      Over The Hedge                                                   |
|      PDC World Championship Darts                                     |
|      Peggle Dual Shot                                                 |
|      Personal Trainer: Math                                           |
|      Petz Dogz 2                                                      |
|      Petz Dogz Fashion                                                |
|      Phineas And Ferb Ride Again                                      |
|      Phineas And Ferb: Across The 2nd Dimension                       |
|      Picross 3D                                                       |
|      Picross DS                                                       |
|      PICTOIMAGE                                                       |
|      Ping Pals                                                        |
|      Pirates: Duels On The High Seas                                  |
|      Pirates Of The Caribbean: At World's End                         |
|      Planet 51: The Game                                              |
|      Planet Puzzle League                                             |
|      Plants Vs. Zombies                                               |
|      Playmobil Knights                                                |
|      Playmobil Pirates                                                |
|      Pogo Island                                                      |
|      Point Blank DS                                                   |
|      Pokemon Mystery Dungeon: Explorers Of Sky                        |
|      Pokemon Trozei!                                                  |
|      Polar Bowler                                                     |
|      Polarium                                                         |
|      Pony Friends                                                     |
|      Pony Friends: Mini-Breeds Edition                                |
|      Pony Friends 2                                                   |
|      Pop Island (Nintendo DSiWare)                                    |
|      Pop Island - Paperfield (Nintendo DSiWare)                       |
|      Power Play Pool                                                  |
|      Prey The Stars                                                   |
|      Princess And The Frog, The                                       |
|      Princess In Love                                                 |
|      Prism: Light The Way                                             |
|      Pro Evolution Soccer 2008                                        |
|      Professional Fisherman's Tour: Northern Hemisphere               |
|      Puchi Puchi Virus                                                |
|      Puyo POP FEVER                                                   |
|      Puzzle De Harvest Moon                                           |
|      Quest Trio, The                                                  |
|      QuickSpot                                                        |
|      Rabbids Go Home                                                  |
|      Race Driver: Create & Race                                       |
|      Rafa Nadal Tennis                                                |
|      Ratatouille                                                      |
|      Rayman Raving Rabbids 2                                          |
|      Rayman Raving Rabbids TV Party                                   |
|      Ridge Racer DS                                                   |
|      Ringling Bros. and Barnum & Bailey Circus                        |
|      Rio                                                              |
|      Rock Revolution                                                  |
|      Rollin' Rascals                                                  |
|      RooGoo Attack!                                                   |
|      Rub Rabbits                                                      |
|      Rubik's World                                                    |
|      SBK: Snowboard Kids                                              |
|      Scrabble                                                         |
|      Sega Casino                                                      |
|      Sega Superstars Tennis                                           |
|      Shaun White Snowboarding                                         |
|      Shining Stars: Super Starcade                                    |
|      Shrek The Third                                                  |
|      Simpsons Game, The                                               |
|      Skate It                                                         |
|      Solitaire Overload                                               |
|      Sonic Colors                                                     |
|      Sonic Rush                                                       |
|      Sonic Rush Adventure                                             |
|      Space Bust-A-Move                                                |
|      Space Invaders Extreme                                           |
|      Space Invaders Extreme 2                                         |
|      SpongeBob's Boating Bash                                         |
|      Squishy Tank                                                     |
|      Star Fox Command                                                 |
|      Stitch Jam                                                       |
|      Style Lab: Makeover                                              |
|      Super Black Bass Fishing                                         |
|      Super Dodgeball Brawlers                                         |
|      Super Mario 64 DS                                                |
|      Super Monkey Ball: Touch & Roll                                  |
|      Super Speed Machines                                             |
|      Superman Returns: The Videogame                                  |
|      Suzuki Super-Bikes II: Riding Challenge                          |
|      Tamagotchi Connection: Corner Shop                               |
|      Tamagotchi Connection: Corner Shop 2                             |
|      Tamagotchi Connection: Corner Shop 3                             |
|      Tank Beat                                                        |
|      Tetris DS                                                        |
|      Tetris Party Deluxe                                              |
|      ThinkSmart Kids 8+                                               |
|      Thrillville: Off The Rails                                       |
|      Tiger Woods PGA Tour 08                                          |
|      Tinker Bell And The Great Fairy Rescue                           |
|      Toon-Doku                                                        |
|      Top Gun                                                          |
|      Totally Spies! 2: Undercover                                     |
|      Touch Darts                                                      |
|      Touchmaster 2                                                    |
|      Touchmaster 3                                                    |
|      Touchmaster: Connect                                             |
|      TrackMania DS                                                    |
|      TrackMania Turbo                                                 |
|      Trioncube                                                        |
|      Tropix DS                                                        |
|      True Swing Golf                                                  |
|      Ultimate Mortal Kombat                                           |
|      Ultimate Puzzle Games: Sudoku Edition                            |
|      USA Today Puzzle Craze                                           |
|      Warhammer 40,000: Squad Command                                  |
|      Whac-A-Mole                                                      |
|      Wild West, The                                                   |
|      Windy X Windham                                                  |
|      Winning Eleven: Pro Evolution Soccer 2007                        |
|      WireWay                                                          |
|      Wizards Of Waverly Place                                         |
|      Wordfish                                                         |
|      WordJong                                                         |
|      World Championship Games                                         |
|      World Championship Poker: Deluxe Series                          |
|      World Cup Of Pool                                                |
|      World Of Zoo                                                     |
|      Worms: Open Warfare                                              |
|      Worms: Open Warfare 2                                            |
|      Xiaolin Showdown                                                 |
|      Yoshi Touch & Go                                                 |
|      Zendoku                                                          |
|      Zoo Keeper                                                       |
+-----------------------------------------------------------------------+
```




