# DS Cartridge Protocol


Communication with Cartridge ROM relies on sending 8 byte commands to
the cartridge, after the sending the command, a data stream can be
received from the cartridge (the length of the data stream isn\'t fixed
below descriptions show the default length in brackets, but one may
receive more, or less bytes, if desired).

**Cartridge Memory Map**

```
+-----------------------------------------------------------------------+
|       0000000h-0000FFFh Header (unencrypted)                          |
|       0001000h-0003FFFh Not read-able (zero filled in ROM-images)     |
|       0004000h                                                        |
| -0007FFFh Secure Area, 16KBytes (first 2Kbytes with extra encryption) |
|       0008000h-...      Main Data Area                                |
+-----------------------------------------------------------------------+
```

DSi cartridges are split into a NDS area (as above), and a new DSi
area:

```
+-----------------------------------------------------------------------+
|       XX00000                                                         |
| h XX02FFFh DSi Not read-able (XX00000h=first megabyte after NDS area) |
|       XX030                                                           |
| 00h-XX06FFFh DSi ARM9i Secure Area (usually with modcrypt encryption) |
|       XX07000h-...      DSi Main Data Area                            |
+-----------------------------------------------------------------------+
```

Cartridge memory must be copied to RAM (the CPU cannot execute code in
ROM).

**Command Summary, Cmd/Reply-Encryption Type, Default Length**

```
+-----------------------------------------------------------------------+
|                                                                       |
|    Command/Params    Expl.                             Cmd  Reply Len |
|       -- Unencrypted Load --                                          |
|                                                                       |
|  9F00000000000000h Dummy (read HIGH-Z bytes)         RAW  RAW   2000h |
|       00000000                                                        |
| 00000000h Get Cartridge Header              RAW  RAW   200h DSi:1000h |
|                                                                       |
|   00aaaaaaaa000000h Get Cartridge Header (1T-ROM,NAND)RAW  RAW   200h |
|                                                                       |
|      9000000000000000h 1st Get ROM Chip ID               RAW  RAW   4 |
|                                                                       |
|      A000000000000000h Get 3DS encryption type (3DS)     RAW  RAW   4 |
|                                                                       |
|   00aaaaaaaa000000h Unencrypted Data (debug ver only) RAW  RAW   200h |
|                                                                       |
|      3Ciiijjjxkkkkkxxh Activate KEY1 Encryption (NDS)    RAW  RAW   0 |
|                                                                       |
|      3Diiijjjxkkkkkxxh Activate KEY1 Encryption (DSi)    RAW  RAW   0 |
|                                                                       |
|      3E00000000000000h Activate 16-byte commands (3DS)   RAW  RAW   0 |
|       -- Secure Area Load --                                          |
|                                                                       |
| 4llllmmmnnnkkkkkh Activate KEY2 Encryption Mode     KEY1 FIX   910h+0 |
|                                                                       |
| 1lllliiijjjkkkkkh 2nd Get ROM Chip ID               KEY1 KEY2  910h+4 |
|       xx                                                              |
| xxxxxxxxxxxxxxh Invalid - Get KEY2 Stream XOR 00h KEY1 KEY2  910h+... |
|       2bbb                                                            |
| biiijjjkkkkkh Get Secure Area Block (4Kbytes)   KEY1 KEY2  910h+10A8h |
|                                                                       |
| 6lllliiijjjkkkkkh Optional KEY2 Disable             KEY1 KEY2  910h+? |
|                                                                       |
| Alllliiijjjkkkkkh Enter Main Data Mode              KEY1 KEY2  910h+0 |
|       -- Main Data Load --                                            |
|                                                                       |
|   B7aaaaaaaa000000h Encrypted Data Read               KEY2 KEY2  200h |
|                                                                       |
|      B800000000000000h 3rd Get ROM Chip ID               KEY2 KEY2  4 |
|                                                                       |
|    xxxxxxxxxxxxxxxxh Invalid - Get KEY2 Stream XOR 00h KEY2 KEY2  ... |
|                                                                       |
|      B500000000000000h Whatever NAND related? (DSi?)     KEY2 KEY2  0 |
|                                                                       |
|      D600000000000000h Whatever NAND related? (DSi?)     KEY2 KEY2  4 |
+-----------------------------------------------------------------------+
```

The parameter digits contained in above commands are:

```
+-----------------------------------------------------------------------+
|       aaa                                                             |
| aaaaa     32bit ROM address (command B7 can access only 8000h and up) |
|       bbbb                                                            |
|         Secure Area Block number (0004h..0007h for addr 4000h..7000h) |
|                                                                       |
|  x,xx         Random, not used in further commands (DSi: always zero) |
|       iii,jjj,llll Random, must be SAME value in further commands     |
|       kkkkk        Random, must be INCREMENTED after FURTHER commands |
|       mmm,nnn      Random, used as KEY2-encryption seed               |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      _________                                                        |
| ___ Unencrypted Commands (First Part of Boot Procedure) _____________ |
+-----------------------------------------------------------------------+
```


**Cartridge Reset**
The /RES Pin switches the cartridge into unencrypted mode. After reset,
the first two commands (9Fh and 00h) are transferred at 4MB/s CLK rate.

**9F00000000000000h (2000h) - Dummy**
Dummy command send after reset, returns endless stream of HIGH-Z bytes
(ie. usually receiving FFh, immediately after sending the command, the
first 1-2 received bytes may be equal to the last command byte).

**0000000000000000h (200h) (DSi:1000h) - Get Header (from address
00000000h)**
**00aaaaaaaa000000h (200h) - DSi Get Header Snippet (from address
aaaaaaaah)**
Returns RAW unencrypted cartridge header, usually repeated every 1000h
bytes. Some carts allow to read the header with a single 200h-byte or
1000h-byte read, others require eight separate 200h-byte reads.

```
+-----------------------------------------------------------------------+
|       NDS/MROM   --> Read 200h bytes from address 000h                |
|       NDS/1T-ROM --> Read 200h bytes from address 000h                |
|       NDS/NAND   --> Read 200h bytes from address 000h                |
|       DSi/MROM   --> Read 1000h bytes from address 000h               |
|                                                                       |
|  DSi/1T-ROM --> Read 8x200h bytes from address 000h,200h,400h,..,E00h |
|                                                                       |
|  DSi/NAND   --> Read 8x200h bytes from address 000h,200h,400h,..,E00h |
+-----------------------------------------------------------------------+
```

Note: DSi/1T-ROM usually allows to read 1000h bytes or 8x200h, but
DSi/NAND works only when reading 8x200h bytes.
The Gamecode header entry is used later on to initialize the encryption.
Also, the ROM Control entries define the length of the KEY1 dummy
periods (typically 910h clocks), and the CLK transfer rate for further
commands (typically faster than the initial 4MB/s after power up).

**9000000000000000h (4) - 1st Get ROM Chip ID**
Returns RAW unencrypted Chip ID (eg. C2h,0Fh,00h,00h), repeated every 4
bytes.

```
+-----------------------------------------------------------------------+
|       1s                                                              |
| t byte - Manufacturer (eg. C2h=Macronix) (roughly based on JEDEC IDs) |
|       2nd by                                                          |
| te - Chip size (00h..7Fh: (N+1)Mbytes, F0h..FFh: (100h-N)*256Mbytes?) |
|       3rd byte - Flags (see below)                                    |
|       4th byte - Flags (see below)                                    |
+-----------------------------------------------------------------------+
```

The Flag Bits in 3th byte can be

```
+-----------------------------------------------------------------------+
|       0   U                                                           |
| ses Infrared (but via SPI, unrelated to ROM) (also Jam with the Band) |
|       1   Unknown (set in some 3DS carts)                             |
|       2-6 Zero                                                        |
|       7   Unknown (set in Kingdom Hearts - Re-Coded)                  |
+-----------------------------------------------------------------------+
```

The Flag Bits in 4th byte can be

```
+-----------------------------------------------------------------------+
|       0-2 Zero                                                        |
|       3   NAND flag (0=ROM, 1=NAND)                                   |
|       4   3DS Flag  (0=NDS/DSi, 1=3DS)                                |
|       5   Unknown   (0=Normal, 1=Support cmd B5h/D6h)                 |
|                                                                       |
|   6   DSi flag  (0=NDS/3DS, 1=DSi) (but also set in NDS Walk with Me) |
|       7   Ca                                                          |
| rt Protocol Variant (0=old/smaller MROM, 1=new/bigger 1T-ROM or NAND) |
+-----------------------------------------------------------------------+
```

Existing/known ROM IDs are:

```
+-----------------------------------------------------------------------+
|       C2h                                                             |
| ,07h,00h,00h NDS Macronix 8MB ROM  (eg. DS Vision, with microSD slot) |
|                                                                       |
|      AEh,0Fh,00h,00h NDS Noname   16MB ROM (eg. Meine Tierarztpraxis) |
|       C2h,0Fh,00h,00h NDS Macronix 16MB ROM (eg. Metroid Demo)        |
|       C2h,1Fh,00h,00h NDS Macronix 32MB ROM (eg. Over the Hedge)      |
|       C2h,1Fh,                                                        |
| 00h,40h DSi Macronix 32MB ROM (eg. Art Academy, TWL-VAAV, SystemFlaw) |
|       80h,3F                                                          |
| h,01h,E0h NDS SanDisk  64MB ROM+Infrared (eg. Walk with Me, NTR-IMWP) |
|       AEh,3Fh,00h,E0h DSi Noname   64MB ROM (eg. de Blob 2, TWL-VD2V) |
|       C2h,3Fh,00h,00h NDS Macronix 64MB ROM (eg. Ultimate Spiderman)  |
|       C2h,3Fh,00h,40h DSi Macronix 64MB ROM (eg. Crime Lab, NTR-VAOP) |
|       80h,7Fh,00h,80h NDS SanDisk  128MB ROM (DS Zelda, NTR-AZEP-0)   |
|       80h,7F                                                          |
| h,01h,E0h ?   SanDisk? 128MB ROM+Infrared (P-letter SoulSilver, IPGE) |
|                                                                       |
|  C2h,7Fh,00h,80h NDS Macronix 128MB ROM (eg. Spirit Tracks, NTR-BKIP) |
|                                                                       |
|  C2h,7Fh,00h,C0h DSi Macronix 128MB ROM (eg. Cooking Coach, TWL-VCKE) |
|       ECh                                                             |
| ,7Fh,00h,88h NDS Samsung  128MB NAND (eg. Warioware D.I.Y., NTR-UORE) |
|       ECh,                                                            |
| 7Fh,01h,88h NDS Samsung  128MB NAND (eg. Jam with the Band, NTR-UXBP) |
|                                                                       |
| ECh,7Fh,00h,E8h DSi Samsung  128MB NAND (eg. Face Training, TWL-USKV) |
|       80h,FFh                                                         |
| ,80h,E0h NDS SanDisk? 256MB ROM (Kingdom Hearts - Re-Coded, NTR-BK9P) |
|                                                                       |
|  C2h,FFh,01h,C0h DSi Macronix 256MB ROM+Infrared (eg. P-Letter White) |
|                                                                       |
|      C2h,FFh,00h,80h NDS Macronix 256MB ROM (eg. Band Hero, NTR-BGHP) |
|       C                                                               |
| 2h,FEh,01h,C0h DSi Macronix 512MB ROM+Infrared (eg. P-Letter White 2) |
|       C2h,FEh,00h,90h 3DS Macronix probably 512MB? ROM (eg. Sims 3)   |
|       45h,FAh,00h,90h 3DS SanDisk? maybe... 1GB?   ROM (eg. Starfox)  |
|                                                                       |
|     C2h,F8h,00h,90h 3DS Macronix maybe... 2GB?   ROM (eg. Kid Icarus) |
|                                                                       |
|   C2h,7Fh,00h,90h 3DS Macronix 128MB ROM CTR-P-AENJ MMinna no Ennichi |
|       C2h,                                                            |
| FFh,00h,90h 3DS Macronix 256MB ROM CTR-P-AFSJ Pro Yakyuu Famista 2011 |
|       C2h,FEh                                                         |
| ,00h,90h 3DS Macronix 512MB ROM CTR-P-AFAJ Real 3D Bass FishingFishOn |
|       C2h,FAh                                                         |
| ,00h,90h 3DS Macronix 1GB ROM CTR-P-ASUJ Hana to Ikimono Rittai Zukan |
|       C2h,                                                            |
| FAh,02h,90h 3DS Macronix 1GB ROM CTR-P-AGGW Luigis Mansion 2 ASiA CHT |
|       C2h,F8h,                                                        |
| 00h,90h 3DS Macronix 2GB ROM CTR-P-ACFJ Castlevania - Lords of Shadow |
|                                                                       |
|      C2h,F8h,02h,90h 3DS Macronix 2GB ROM CTR-P-AH4J Monster Hunter 4 |
|                                                                       |
|     AEh,FAh,00h,90h 3DS Noname?  1GB ROM CTR-P-AGKJ Gyakuten Saiban 5 |
|       AEh,F                                                           |
| Ah,00h,98h 3DS Noname?  1GB NAND CTR-P-EGDJ Tobidase Doubutsu no Mori |
|       45h,FAh,00h,90h 3DS SanDisk? 1GB ROM CTR-P-AFLJ Fantasy Life    |
|       45h,F8                                                          |
| h,00h,90h 3DS SanDisk? 2GB ROM CTR-P-AVHJ Senran Kagura Burst - Guren |
|                                                                       |
| C2h,F0h,00h,90h 3DS Macronix 4GB ROM CTR-P-ABRJ Biohazard Revelations |
|                                                                       |
|      ?,?,?,?         NDS ?        ? (eg. Japanese TV Tuner, NTR-UNSJ) |
|       00h,00h                                                         |
| ,00h,00h Cart Reset Busy (Face Training needs 20ms delay after reset) |
|       FFh,FFh,FFh,FFh None (no cartridge inserted)                    |
+-----------------------------------------------------------------------+
```

The official JEDEC ID for Samsung would be \"CEh\", but for some reason
Samsung\'s NDS chip does spit out \"ECh\" as Maker ID. SanDisk has tw
IDs (80h on NDS/DSi, and 45h on 3DS).

**3Ciiijjjxkkkkkxxh (0) - Activate KEY1 Encryption Mode**
The 3Ch command returns endless stream of HIGH-Z bytes, all following
commands, and their return values, are encrypted. The random parameters
iii,jjj,kkkkk must be re-used in further commands; the 20bit kkkkk value
is to be incremented by one after each \<further\> command (it i
\<not\> incremented after the 3Ch command).

**3Diiijjjxkkkkkxxh (0) - Activate KEY1 Encryption Mode and Unlock DSi
Mode**
Same as command 3Ch (but with different initial 1048h-byte encryption
values), and works only on DSi carts. Command 3Dh is unlocking two
features on DSi carts:

```
+-----------------------------------------------------------------------+
|       1) Com                                                          |
| mand 2bbbbiiijjjkkkkkh loads ARM9i secure area (instead of ARM9 area) |
|       2)                                                              |
|  Command B7aaaaaaaa000000h allows to read the 'whole' cartridge space |
+-----------------------------------------------------------------------+
```

Without command 3Dh, DSi carts will allow to read only the first some
megabytes (for example, the first 11 Mbyte of the System Flaw
cartridge), and the remaining memory returns mirrors of
\"addr=8000h+(addr AND 1FFh)\").
Note: After reset, the cartridge protocol allows to send only either one
of the 3Ch/3Dh commands (DSi consoles can control the cartridge reset
pin, so they can first send 3Ch and read the normal secure area, then
issue a reset and 3Dh and read the DSi secure area) (on a NDS one could
do the same by ejecting/inserting the cartridge instead of toggling the
reset pin).


```
+-----------------------------------------------------------------------+
|      _________                                                        |
| ___ KEY1 Encrypted Commands (2nd Part of Boot procedure) ____________ |
+-----------------------------------------------------------------------+
```


**4llllmmmnnnkkkkkh (910h) - Activate KEY2 Encryption Mode**
KEY1 encrypted command, parameter mmmnnn is used to initialize the KEY2
encryption stream. Returns 910h dummy bytes (which are still subject to
old KEY2 settings; at pre-initialization time, this is fixed: HIGH-Z,
C5h, 3Ah, 81h, etc.). The new KEY2 seeds are then applied, and the first
KEY2 byte is then precomputed. The 910h dummy stream is followed by that
precomputed byte value endless repeated (this is the same value as that
\"underneath\" of the first HIGH-Z dummy-byte of the next command).
Secure1000h: Returns repeated FFh bytes (instead of the leading C5h,
3Ah, 81h, etc. stuff).
Secure1000h: Returns repeated FFh bytes (instead of the repeated
precomputed value).

**1lllliiijjjkkkkkh (914h) - 2nd Get ROM Chip ID / Get KEY2 Stream**
KEY1 encrypted command. Returns 910h dummy bytes, followed by KEY2
encrypted Chip ID repeated every 4 bytes, which must be identical as for
the 1st Get ID command. The BIOS randomly executes this command once or
twice. Changing the first command byte to any other value returns an
endless KEY2 encrypted stream of 00h bytes, that is the easiest way to
retrieve encryption values and to bypass the copyprotection.

**2bbbbiiijjjkkkkkh (19B8h) - Get Secure Area Block**
KEY1 encrypted command. Used to read a secure area block (bbbb in range
0004h..0007h for addr 4000h..7000h) (or, after sending command 3Dh on a
DSi: bbbb in range 0004h..0007h for addr XX03000h..XX06000h).
Each block is 4K, so it requires four Get Secure Area commands to
receive the whole Secure Area (ROM locations 4000h-7FFFh), the BIOS is
reading these blocks in random order.
Normally (if the upper bit of the Chip ID is set): Returns 910h dummy
bytes, followed by 200h KEY2 encrypted Secure Area bytes, followed by
18h KEY2 encrypted 00h bytes, then the next 200h KEY2 encrypted Secure
Area bytes, again followed by 18h KEY2 encrypted 00h bytes, and so on.
That stream is repeated every 10C0h bytes (8x200h data bytes, plus 8x18h
zero bytes).
Alternately (if the upper bit of the Chip ID is zero): Returns 910h
dummy bytes, followed by 1000h KEY2 encrypted Secure Area bytes,
presumably followed by 18h bytes, too.
Aside from above KEY2 encryption (which is done by hardware), the first
2K of the NDS Secure Area is additionally KEY1 encrypted; which must be
resolved after transfer by software (and the DSi Secure Area is usually
modcrypted, as specified in the cartridge header).

**6lllliiijjjkkkkkh (0) - Optional KEY2 Disable**
KEY1 encrypted command. Returns 910h dummy bytes (which are still KEY2
affected), followed by endless stream of RAW 00h bytes. KEY2 encryption
is disabled for all following commands.
- This command is send only if firmware\[18h\] matches encrypted strin
\"enPngOFF\", and ONLY if firmware get_crypt_keys had completed BEFOR
completion of secure area loading, this timing issue may cause unstable
results.

**Alllliiijjjkkkkkh (910h) - Enter Main Data Mode**
KEY1 encrypted command. Returns 910h dummy bytes, followed by endless
KEY2 encrypted stream of 00h bytes. All following commands are KEY2
encrypted.


```
+-----------------------------------------------------------------------+
|      _________                                                        |
| _______ KEY2 Encrypted Commands (Main Data Transfer) ________________ |
+-----------------------------------------------------------------------+
```


**B7aaaaaaaa000000h (200h) - Get Data**
KEY2 encrypted command. The desired ROM address is specifed, MSB first,
in parameter bytes (a). Returned data is KEY2 encrypted.
There is no alignment restriction for the address. However, the
datastream wraps to the begin of the current 4K block when
address+length crosses a 4K boundary (1000h bytes). Special case:
SanDisk ROMs are forcefully 200h-byte aligned, and can merely read max
200h bytes (padded with unencrypted FFh bytes when trying to read more
data).
The command can be used only for addresses 8000h and up. Addresses
0..7FFFh are silently redirected to address \"8000h+(addr AND 1FFh)\"
DSi cartridges will also reject XX00000h..XX06FFFh in the same fashion
(and also XX07000h and up if the DSi cartridge isn\'t unlocked vi
command 3Dh).
Addresses that do exceed the ROM size do mirror to the valid address
range (that includes mirroring non-loadable regions like 0..7FFFh to
\"8000h+(addr AND 1FFh)\"; some newer games are using this behaviour fo
some kind of anti-piracy checks).

**B800000000000000h (4) - 3rd Get ROM Chip ID**
KEY2 encrypted command. Returns KEY2 encrypted Chip ID repeated every 4
bytes.

**xxxxxxxxxxxxxxxxh - Invalid Command**
Any other command (anything else than above B7h and B8h) in KEY2 command
mode causes communcation failures. The invalid command returns an
endless KEY2 encrypted stream of 00h bytes. After the invalid command,
the KEY2 stream is NOT advanced for further command bytes, further
commands seems to return KEY2 encrypted 00h bytes, of which, the first
returned byte appears to be HIGH-Z.
Ie. the cartridge seems to have switched back to a state similar to the
KEY1-phase, although it doesn\'t seem to be possible to send KEY
commands.


```
+-----------------------------------------------------------------------+
|      ________                                                         |
| ___________________________ Notes ___________________________________ |
+-----------------------------------------------------------------------+
```


**KEY1 Command Encryption / 910h Dummy Bytes**
All KEY1 encrypted commands are followed by 910h dummy byte transfers,
these 910h clock cycles are probably used to decrypt the command at the
cartridge side; communication will fail when transferring less than 910h
bytes.
The return values for the dummy transfer are: A single HIGH-Z byte,
followed by 90Fh KEY2-encrypted 00h bytes. The KEY2 encryption stream is
advanced for all 910h bytes, including for the HIGH-Z byte.
Note: Current cartridges are using 910h bytes, however, other carts
might use other amounts of dummy bytes, the 910h value can be calculated
based on ROM Control entries in cartridge header. For the KEY1 formulas,
see:
- [DS Encryption by Gamecode/Idcode(./dsencryptionbygamecodeidcodekey1.md)

**KEY2 Command/Data Encryption**
- [DS Encryption by Random Seed (./dsencryptionbyrandomseedkey2.md)

**Cart Protocol Variants (Chip ID.Bit31)**
There are two protocol variants for NDS carts, indicated by Bit31 of the
ROM Chip ID (aka bit7 of the 4th ID byte):

```
+-----------------------------------------------------------------------+
|                                                                       |
|   1) Chip ID.Bit31=0  Used by older/smaller carts with up to 64MB ROM |
|                                                                       |
|  2) Chip ID.Bit31=1  Used by newer/bigger carts with 64MB or more ROM |
+-----------------------------------------------------------------------+
```

The first variant (for older carts) is described above. The second
second variant includes some differences for KEY1 encrypted commands:
GAPS: The commands have the same 910h-cycle gaps, but without outputting
CLK pulses during those gaps (ie. used with ROMCTRL.Bit28=0) (the
absence of the CLKs implies that there is no dummy data transferred
during gaps, and accordingly, that the KEY2 stream isn\'t advance
during the 910h gap cycles).
REPEATED COMMANDS and SECURE AREA DELAY: All KEY1 encrypted commands
must be sent TWICE (or even NINE times). First, send the command with
0-byte Data transfer length. Second, issue the Secure Area Delay
- (required; use the delay specified in cart header\[06Eh\]).
Third, send the command once again with 0-byte or 4-byte data transfer
length (usually 0 bytes, or 4-bytes for Chip ID command), or sent it
eight times with 200h-byte data transfer length (for the 1000h-byte
secure area load command).
For those repeats, always resend exactly the same command (namely, kkkkk
is NOT incremented during repeats, and there is no extra index needed to
select 200h-byte portions within 1000h-byte blocks; the cartridge is
automatically outputting the eight portions one after another).



