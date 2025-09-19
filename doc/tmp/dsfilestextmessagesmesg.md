# DS Files - Text Messages (MESG)


MESG files contain localized strings (like \"Okay\" and \"Cancel\" and longer text messages). Different languages are stored separate message files, usually with .bmg extension. MESG files are used in NDS/DSi titles (in little endian), and also on Wii (in big endian).
DSi titles are: DSi Shop, Launcher, System Settings, and DSi Camera (however, the DSi-to-3DS Transfer Tool uses the newer MsgPrjBn/MsgStdBn format; despite of being a DSi program).

### MESG Header

```
+----------------------------------------------------------------------------+
|       000h 8     ID "MESGbmg1"         ;or "GSEM1gmb" in Super Mario 64 DS |
|       008h 4     Total Filesize        ;or Filesize+1 in Super Mario 64 DS |
|       00Ch 4     Number of Chunks (2=INF1+DAT1, 3=INF1+DAT1+MID1)          |
|       010h 1     Encoding (1=CP1252, 2=UTF-16, 3=Shift-JIS, 4=UTF-8)       |
|       011h 15    Padding (0)                                               |
+----------------------------------------------------------------------------+
```

Encoding UTF-16 appears to be most common (Super Mario 64 DS uses Shift-JIS).

### INF1 Chunk (Message Info)
It comes just after the BMG header. It contains information (like pointers) about the messages.

```
+-----------------------------------------------------------------------------------+
|       000h 4     Chunk ID "INF1"       ;or "1FNI" in Super Mario 64 DS            |
|       004h 4     Chunk Size                                                       |
|       008h 2     Number of messages (N)                                           |
|       00Ah 2     Size of each INF data in bytes  ;or in BITs in Super Mario 64 DS |
|       00Ch 4     "BMG file ID = ID for this BMG file (usually 0)"                 |
|       010h N*siz Message Info (32bit offset from DAT1+8, and optional attributes) |
+-----------------------------------------------------------------------------------+
```

For each message, there is a INF data about it. At Wii Fit, there is just the message offset. At Wii Fit Plus, there is two another fields.

```
+-------------------------------------------------------------------------+
|       000h 4     Offset to the message (after DAT1+8 section header)    |
|       004h siz-4 Attributes/flags (if entrysize is bigger than 4 bytes) |
+-------------------------------------------------------------------------+
```

The optional Attribute bits could be used to select different font types or window styles.

### DAT1 Chunk (Message Strings)

```
+------------------------------------------------------------------------------------+
|       000h 4     Chunk ID "DAT1"       ;or "1TAD" in Super Mario 64 DS             |
|       004h 4     Chunk Size            ;or Size+1 in Super Mario 64 DS             |
|       008h ..    Message strings (usually UTF-16, depending on Encoding in header) |
+------------------------------------------------------------------------------------+
```

The DSi Camera uses both char 001Ah and 0025h for escape codes.
UTF-16 string characters:

```
+-------------------------------------------------------------------------------------+
|       0000                           End of String (except inside Escape sequences) |
|       000A                           Linebreak                                      |
|       001A,nn,command,parameters     Escape Sequences (nn=length in bytes)          |
|       001A,08,00,0000,00xx           Set font size (64h=100%=Normal Size)           |
|       001A,08,00,0001,00xx           Set text color to xx                           |
|       001A,08,01,0000,24xx           Draw Unicode char U+2460..246E ;"(1)"..("15)"  |
|       001A,08,01,0000,xxxx           Draw Unicode char U+E068..F12B ;custom?        |
|       001A,06,02,0000                Draw Name of current player                    |
|       001A,0A,02,0010,000x,000w      Draw Integer from index x with w digits        |
|       001A,08,02,0011,00xx           Unknown (with xx=0..8)                         |
|       001A,08,02,0012,0000           Draw Name of a player                          |
|       001A,08,02,0013,0000           Unknown                                        |
|       001A,08,02,0014,0000           Unknown                                        |
|       001A,08,02,0015,0000           Unknown                                        |
|       001A,0A,02,0016,0000,0000      Unknown                                        |
|       001A,08,02,0017,0000           Unknown                                        |
|       001A,08,02,0020,0000           Draw Name of a Wii friend                      |
|       001A,08,03,0010,0000           Unknown                                        |
|       001A,0C,04,0000,000x,yyyy,zzzz Unknown (x=0..1, y=0524..14A4, and z=y+1)      |
|       0025,00xx,00yy,00zz            Escape codes in form of "%xyz" (or similar)    |
|       00xx                           ASCII Characters 20h..7Eh                      |
|       E0xx                           Custom button symbols (eg. in DSi Launcher)    |
+-------------------------------------------------------------------------------------+
```

Shift-JIS (or whatever) strings in Super Mario 64 DS:

```
+--------------------------------------------------------------------------------+
|       0D       Linebreak?                                                      |
|       10..1F   Escape codes?                                                   |
|       xx,xx    Unknown (doesn't really look like english Shift-JIS characters) |
|       FF       End of String                                                   |
+--------------------------------------------------------------------------------+
```


### MID1 Chunk (Message IDs) (if any)

```
+-----------------------------------------------------------------------+
|       000h 4     Chunk ID "MID1"                                      |
|       004h 4     Chunk Size                                           |
|       008h 2     Number of messages (same as in INF1 block)           |
|       00Ah 2     Unknown (usually 1000h)                              |
|       00Ch 4     Padding (0)                                          |
|       010h 4*N   Message IDs                                          |
+-----------------------------------------------------------------------+
```

Messages can be repeated in the different files (such like menu and ingame), if so, all messages with the same message ID of the same language are always having the same text, no differences between the text files can be found.
\"Elements with the same table index are attributes (not IDs?) for the same string.\"

### FLW1 and FLT1 Chunks (if any)
Some games are reportedly having additional \"FLW1\" and \"FLT1\" chunks. Unknown which games, and unknown what for, and unknown if such chunks exist in any DS games (or only in Wii games or whatever).

Thanks to <http://wiki.tockdom.com/wiki/BMG>



