# DS Cart Infrared P-Walker IR Commands


Commands are usually send from NDS (or from other Walkers)

```
+-------------------------------------------------------------------------+
|       EEPROM Commands  (Cmd 02,04,0C,0E,82)     ;\From NDS or Walker    
|       Connect Commands (Cmd F8,FA,FC)           ;/                      |
|       Peer Commands    (Cmd 10...1C)            ;-From Walker           |
|       Unused Commands  (Cmd's with * marking)   ;-From Prototype tests? |
|       Other Commands   (Cmd's other than above) ;-From NDS              |
+-------------------------------------------------------------------------+
```


### Incoming Commands from NDS (or incoming commands/replies from another Walker)

```
+-------------------------------------------------------------------------------------+
|       00,hi,..,lzss(..)     EEPROM Write [hi00h..hi7Fh] Compressed   ;Reply=04      |
|       80,hi,..,lzss(..)     EEPROM Write [hi80h..hiFFh] Compressed   ;Reply=04      |
|       02,hi,..,data(..)     EEPROM Write [hi00h..hi7Fh] Raw          ;Reply=04      |
|       82,hi,..,data(..)     EEPROM Write [hi80h..hiFFh] Raw          ;Reply=04      |
|       04,xx,..              EEPROM Write Reply                     ;SendMoreCmd(s)  |
|       06,hi,..,lo,data(nn)* CPU Memory Write [hilo+(0..nn-1)]        ;Reply=06      |
|       0A,hi,..,lo,data(nn)* EEPROM Write Random Len [hilo+(0..nn-1)] ;Reply=04      |
|       0C,xx,..,hi,lo,nn     EEPROM Read Request [hilo+(0..nn-1)]     ;Reply=0E      |
|       0E,xx,..,data(nn)     EEPROM Read Reply                      ;SendMoreCmd(s)  |
|       10,xx,..,data(68h)    Peer Step 1 Request                      ;Reply=12      |
|       12,xx,..,data(68h)    Peer Step 1 Reply                      ;SendMoreCmd(s)  |
|       14,xx,..,data(38h)    Peer Step 2 Request                      ;Reply=16      |
|       16,xx,..              Peer Step 2 Reply                ;Reply=16 or None      |
|       1C,xx,..              Peer Refuse                      ;Reply=None+Disconnect |
|       20,xx,..              Identity Read Request                    ;Reply=22      |
|       24,xx,..            * Ping Request                             ;Reply=26      |
|       2A,xx,..,none?        Unique ID Read Request                   ;Reply=2A      |
|       2C,xx,..,none?      * Unique ID Read Request slightly other    ;Reply=2A      |
|       32,xx,..,data(28h?) * Identity Write Request 1                 ;Reply=34      |
|       36,xx,..            * Connection Error 1                       ;Reply=None    |
|       38,xx,..            * Walk Start Silent                        ;Reply=38      |
|       40,xx,..,data(28h?) * Identity Write Request 2                 ;Reply=42      |
|       44,xx,..            * Connection Error 2                       ;Reply=None    |
|       4E,xx,..              Walk End Request                         ;Reply=50      |
|       52,xx,..,data(28h?)?? Identity Write Request 3                 ;Reply=54      |
|       56,xx,..            * Connection Error 3                       ;Reply=None    |
|       5A,xx,..              Walk Start Nonsilent                     ;Reply=5A      |
|       60,xx,..,data(28h?) * Identity Write Request 4                 ;Reply=62      |
|       64,xx,..            * Connection Error 4                       ;Reply=None    |
|       66,xx,..            * Walk End Request OTHER                   ;Reply=68      |
|       9C,xx,..            * Error Whatever                   ;Reply=9C+Disconnect   |
|       9E,xx,..            * Error Weird Participate          ;Reply=9E+Disconnect   |
|       A0,xx,..            * Weird Participate 1                  ;Reply=A0 or 9E    |
|       A2,xx,..            * Weird Participate 2                  ;Reply=A2 or 9E    |
|       A4,xx,..            * Weird Participate 3                  ;Reply=A4 or 9E    |
|       A6,xx,..            * Weird Participate 4                  ;Reply=A6 or 9E    |
|       A8,xx,..            * Weird Participate 5                  ;Reply=A8 or 9E    |
|       AA,xx,..            * Weird Participate 6                  ;Reply=AA or 9E    |
|       AC,xx,..            * Weird Participate 7                  ;Reply=AC or 9E    |
|       AE,xx,..            * Weird Participate 8                  ;Reply=AE or 9E    |
|       B8,xx,..            * Award Stamp Heart                        ;Reply=D8      |
|       BA,xx,..            * Award Stamp Spade                        ;Reply=DA      |
|       BC,xx,..            * Award Stamp Diamond                      ;Reply=DC      |
|       BE,xx,..            * Award Stamp Club                         ;Reply=DE      |
|       C0,xx,..            * Award Special Map                        ;Reply=C0      |
|       C2,xx,..            * Award Event P-Letter                     ;Reply=C2      |
|       C4,xx,..            * Award Event Item                         ;Reply=C4      |
|       C6,xx,..            * Award Event Route                        ;Reply=C6      |
|       D0,xx,..            * Award All Stamps and Special Map         ;Reply=C0      |
|       D2,xx,..            * Award All Stamps and Event P-Letter      ;Reply=C2      |
|       D4,xx,..            * Award All Stamps and Event Item          ;Reply=C4      |
|       D6,xx,..            * Award All Stamps and Event Route         ;Reply=C6      |
|       D8,xx,..            * Connection Error 5                       ;Reply=None    |
|       F0,xx,..,data(71h) ?? Enroll Data (28h+40h+8+1 bytes)          ;Reply=F0      |
|       F4,xx,..            * Disconnect                       ;Reply=None+Disconnect |
|       F8,02,..              Connection Reply from Walker             ;SendCmd=1002  |
|       FA,01,..              Connection Request from NDS              ;Reply=F802    |
|       FA,02,..              Connection Request from Walker           ;Reply=F802    |
|       FA,xx,..              Connection Request invalid       ;Reply=None+Disconnect |
|       FC                    Connection Beacon from Walker            ;SendCmd=FA    |
|       FE,01,..,data(8)    * EEPROM Write [0008h..000Fh]              ;Reply=FE      |
|       xx                  * Ignored (single byte other than FC)      ;Reply=None    |
|       xx,xx,..            * Invalid Cmd                              ;Reply=None    |
|       xx,xx,xxxx          * Ignored (wrong 4-byte ID for Cmd 00-F7)  ;Reply=None    |
|       xx,xx,xxxx          * Bad Checksum (disconnect if too often)   ;Reply=None    |
+-------------------------------------------------------------------------------------+
```


### Outgoing Replies to NDS (or outgoing commands/replies to another Walker)

```
+-------------------------------------------------------------------------------------+
|       02,hi,..,data(nn)     EEPROM Write ...                         ;Cmd=Peer      |
|       82,hi,..,data(nn)     EEPROM Write ...                         ;Cmd=Peer      |
|       04,hi,..              EEPROM Write Reply                  ;Cmd=00/02/0A/80/82 |
|       06,hi,..            * CPU Memory Write Reply                   ;Cmd=06h       |
|       0C,02,..,hi,lo,nn     EEPROM Read Request  ;Peer, EEPROM Read  ;Cmd=0Eh       |
|       0E,02,..,data(nn)     EEPROM Read Reply                        ;Cmd=0Ch       |
|       10,02,..,data(68h)    Peer Step 1 Request (after Connect Reply);Cmd=F8h       |
|       12,02,..,data(68h)    Peer Step 1 Reply                        ;Cmd=10h       |
|       14,02,..,data(38h)    Peer Step 2 Request                      ;Cmd=0Eh       |
|       16,02,..              Peer Step 2 Reply                        ;Cmd=14h/16h   |
|       1C,02,..              Peer Refuse                              ;Cmd=10h/12h   |
|       22,02,..,data(68h)    Identitiy Read Reply                     ;Cmd=20h       |
|       26,02,..            * Ping Reply                               ;Cmd=24h       |
|       2A,02,..,data(28h)    Unique ID Reply                          ;Cmd=2Ah/2Ch   |
|       34,02,..            * Identitiy Write 1 Reply                  ;Cmd=32h       |
|       38,02,..            * Walk Start silent Reply                  ;Cmd=38h       |
|       42,02,..            * Identitiy Write 2 Reply                  ;Cmd=40h       |
|       50,02,..              Walk End Reply                           ;Cmd=4Eh       |
|       54,02,..           ?? Identitiy Write 3 Reply                  ;Cmd=52h       |
|       5A,02,..              Walk Start nonsilent Reply               ;Cmd=5Ah       |
|       62,02,..            * Identitiy Write 4 Reply                  ;Cmd=60h       |
|       68,02,..            * Walk End OTHER Reply                     ;Cmd=66h       |
|       9C,02,..            * Weird Whatever Reply-to-Reply?           ;Cmd=9Ch       |
|       9E,02,..,data(11h)  * Weird Participated Reply                 ;Cmd=A0h..AEh  |
|       9E,02,..            * Weird Participated Reply-to-Reply?       ;Cmd=9Eh       |
|       A0,02,..,data(11h)  * Weird Participated Reply 1               ;Cmd=A0h       |
|       A2,02,..,data(11h)  * Weird Participated Reply 2               ;Cmd=A2h       |
|       A4,02,..,data(11h)  * Weird Participated Reply 3               ;Cmd=A4h       |
|       A6,02,..,data(11h)  * Weird Participated Reply 4               ;Cmd=A6h       |
|       A8,02,..,data(11h)  * Weird Participated Reply 5               ;Cmd=A8h       |
|       AA,02,..,data(11h)  * Weird Participated Reply 6               ;Cmd=AAh       |
|       AC,02,..,data(11h)  * Weird Participated Reply 7               ;Cmd=ACh       |
|       AE,02,..,data(11h)  * Weird Participated Reply 8               ;Cmd=AEh       |
|       C0,02,..            * Award Special Map Reply                  ;Cmd=C0h/D0h   |
|       C2,02,..            * Award Event P-Letter Reply               ;Cmd=C2h/D2h   |
|       C4,02,..            * Award Event Item Reply                   ;Cmd=C4h/D4h   |
|       C6,02,..            * Award Event Route Reply                  ;Cmd=C6h/D6h   |
|       C8,02,..            * Award Stamp Heart Reply                  ;Cmd=B8h       |
|       CA,02,..            * Award Stamp Spade Reply                  ;Cmd=BAh       |
|       CC,02,..            * Award Stamp Diamond Reply                ;Cmd=BCh       |
|       CE,02,..            * Award Stamp Club Reply                   ;Cmd=BEh       |
|       F0,02,..,data(28h) ?? Enroll Reply                             ;Cmd=F0h       |
|       F8,02,..              Connect Reply                            ;Cmd=FAh       |
|       FA,02,..              Connect Request from walker              ;Cmd=FCh       |
|       FC                    Connection Beacon                        ;Button?       |
|       FE,02,..            * EEPROM Write [0008h..000Fh] Reply        ;Cmd=FEh       |
|       -?-                   Checksum Error... has no reply? or maybe sends Beacons? |
+-------------------------------------------------------------------------------------+
```


### Notes

```
+-------------------------------------------------------------------------------------+
|       ..    short for 16bit Checksum at hdr[2..3] and 32bit Session ID at hdr[4..7] |
|       xx    somewhat don't care (usually 01h=From NDS, or 02h=From Walker)          |
+-------------------------------------------------------------------------------------+
```

All 16bit checksum and the IR \"encryption\" (XOR by AAh), seem to be same as for Activity Meter (see there, except use initial sum=2, not sum=0).
The Connect Request & Reply commands are sending a \"random\" SessionID each, all following commands/replies (except F8h and up) must use

```
+-----------------------------------------------------------------------+
|       SessionID = ConnectRequestRandomID XOR ConnectReplyRandomID.    |
+-----------------------------------------------------------------------+
```

The Compressed EEPROM commands are writing decompressed 80h-bytes of data to EEPROM (ie. the compression is only used to speedup the IR transfer, not to save memory). The compression format is Nintendo\'s standard LZSS (including the header value 10h, and little-endian 24bit length; which should be always 80h). Special case: Compressed writes with exactly 80h bytes of incoming data are treated as uncompressed writes (to be used when compression ratio is worse than no compression).



