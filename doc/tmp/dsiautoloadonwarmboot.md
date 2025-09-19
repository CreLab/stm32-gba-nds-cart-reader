# DSi Autoload on Warmboot


### Overview
Launcher (and unlaunch) can be commanded to autoload a different title.

```
+-----------------------------------------------------------------------------------+
|       2000000h  Autoload Parameters for newly loaded title  ;<-- optional extra   |
|       2000300h  Autoload via numeric Title ID               ;<-- official method  |
|       2000800h  Autoload via string "device:\path\filename" ;<-- alternate method 
|       2FFD800h  Title List (jump-able titles for use at 2000300h)                 |
|       BPTWL[70h].bit0  Warmboot flag                        ;<-- required flag    |
|       BPTWL[11h].bit0  Trigger reset                        ;<-- trigger reset    |
+-----------------------------------------------------------------------------------+
```

Moreover, autoload can occur on warmboot & coldboot: Launcher autoloads any ROM cartridge with carthdr\[01Fh\].Bit2. Unlaunch defaults to autoload any file named \"sdmc:\\bootcode.dsi\".

### Examples
DSi Browser settings screen allows to autoload System Settings (via 2000300h), and automatically enter the Internet options page (via 2000000h).
Nintendo Zone, if started with Wireless Communications disabled, allows to reboot itself (via specifying it\'s own Title ID in 2000300h).
Homebrew frontends for unlaunch could start themselves (via bootcode.dsi) and then command unlaunch to load another title (via 2000800h or 2000300h).

### 2000000h - Optional Auto-load parameters (passed on to new title)

```
+----------------------------------------------------------------------------------+
|       2000000h 8    AutoParam Old Title ID (former title)    ;carthdr[230h]      |
|       2000008h 1    AutoParam Unknown/Unused                                     |
|       2000009h 1    AutoParam Flags (03h=Stuff is used?)                         |
|       200000Ah 2    AutoParam Old Maker code                 ;carthdr[010h]      |
|       200000Ch 2    AutoParam Unknown (02ECh) ;\counter/length/indices/whatever? 
|       200000Eh 2    AutoParam Unknown (0000h) ;/                                 |
|       2000010h 2    AutoParam CRC16 on [000h..2FFh], initial=FFFFh, [010h]=0000h |
|       2000012h 2    AutoParam Unknown/Unused (000Fh = want Internet Settings?)   |
|       2000014h 2ECh AutoParam Unknown... some buffer... string maybe?            |
+----------------------------------------------------------------------------------+
```

Above is the overall skeleton as intended by Nintendo, the purpose/format of the 2ECh bytes is unknown (there seems to be some relation to entries \[0Ch\] and \[0Eh\], but theoretically, each title could use that bytes as pleased).

### 2000300h - Nintendo Auto-load feature (via numeric Title ID)

```
+-------------------------------------------------------------------------------------+
|       2000300h 4    AutoLoad ID ("TLNC")                                            |
|       2000304h 1    AutoLoad Unknown/unused (usually 01h)                           |
|       2000305h 1    AutoLoad Length of data at 2000308h (01h..18h,for CRC,18h=norm) |
|       2000306h 2    AutoLoad CRC16 of data at 2000308h (with initial value FFFFh)   |
|       2000308h 8    AutoLoad Old Title ID (former title) (can be 0=anonymous)       |
|       2000310h 8    AutoLoad New Title ID (new title to be started,0=none/launcher) |
|       2000318h 4    AutoLoad Flags (bit0, 1-3, 4, 5,6,7) ;usually 16bit, once 32bit |
|       200031Ch 4    AutoLoad Unused (but part of checksummed area when CRC len=18h) |
|       2000320h E0h  AutoLoad Unused (but zerofilled upon erasing autoload area)     |
+-------------------------------------------------------------------------------------+
```

Flags (usually 13h or 17h):

```
+------------------------------------------------------------------------------------+
|       0     IsValid (somehow enables/disables HealthSafety when TitleID is wrong?) |
|       1-3   Boottype (01h=Cartridge, 02h=Landing, 03h=DSiware) (see below)         |
|       4     Unknown                                                                |
|       5     Unknown                                                                |
|       6     LoadCompl (causes some error when set) (loading completed flag?)       |
|       7     Unknown                                                                |
|       8-15  Unused                                                                 |
|       16-31 Unused (usually not accessed at all, with normal 16bit reads)          |
+------------------------------------------------------------------------------------+
```

Boottypes (in Flags.bit1-3):

```
+-------------------------------------------------------------------------------------+
|       01h = Cartridge (with NewTitleID)    (with RSA signed header, or Whitelisted) |
|       02h = Landing ("nand:/tmp/jump.app") (with RSA signed DownloadPlay footer)    |
|       03h = DSiware (with NewTitleID)      (with RSA signed header)                 |
+-------------------------------------------------------------------------------------+
```

TitleID.LSW should match DSi cart header (or be reverse of NDS gamecode?)
TitleID.MSW should match DSi cart header (or be zero for NDS titles?)
Note: Many titles do create the above structure even when not requesting to boot a new file: with NewTitleID=0=none & flags=13h=cartridge (in that case flags should be ignored, and NewTitleID=0=none has priority).

### 2000800h - Unlaunch Auto-load feature (via \"device:/Path/Filename.ext\")

```
+-------------------------------------------------------------------------------------+
|       2000800h 12   Unlaunch Auto-load ID ("AutoLoadInfo")                          |
|       200080Ch 2    Unlaunch Length for CRC16 (fixed, must be 3F0h)                 |
|       200080Eh 2    Unlaunch CRC16 (across 2000810h..2000BFFh, initial value FFFFh) |
|       2000810h 4    Unlaunch Flags                                                  |
|       2000814h 2    Unlaunch Upper screen BG color (0..7FFFh)                       |
|       2000816h 2    Unlaunch Lower screen BG color (0..7FFFh)                       |
|       2000818h 20h  Unlaunch Reserved (zero)                                        |
|       2000838h 208h Unlaunch Device:/Path/Filename.ext (16bit Unicode,end by 0000h) |
|       2000A40h 1C0h Unlaunch Reserved (zero)                                        |
+-------------------------------------------------------------------------------------+
```

Unlaunch Flags (usually 01h):

```
+----------------------------------------------------------------------------------+
|       0    Load the title at 2000838h                                            |
|       1    Use colors 2000814h (use if loaded title is KNOWN to use such colors) |
|       2-31 Reserved (zero)                                                       |
+----------------------------------------------------------------------------------+
```

The name can use slashes or backslashes for folders, and it can use both long or short filenames (LFN or 8.3). The total length should not exceed 260 characters including EOL (alike windows MAX_PATH, although WinNT seems to allow up to 32K characters, which isn\'t supported here).

```
+------------------------------------------------------------------------------+
|       "nand:/path/name.ext",0000h   File on 1st partition of internal eMMC   |
|       "sdmc:/path/name.ext",0000h   File on 1st partition of external SD/MMC |
|       "cart:",0000h      ROM cartridge (in NDS cartridge slot)               |
|       "menu:",0000h      Force starting unlaunch filemenu                    |
|       "sett:",0000h      Force starting unlaunch options menu                |
|       "wifi:",0000h      Force starting unlaunch wifiboot overlay            |
+------------------------------------------------------------------------------+
```

Case-sensitivity: device, path and file can use upper/lower case A-Z (not case-sensititive), however currently any other letters are case-sensitive (eg. umlaut\'s or accented letters) (that is, they must be uppercase for short names, or have matching case for long names).
For black colors, you should also disable backlights before issuing reset (else screen will flash white for a short moment during initial forced blank; before unlaunch gets started).

### 2FFD800h - Title List
Before autoloading a title, one should make sure that the title is actually installed (and which region code it is having, ie. one should use wildcards that ignore the lower 8bit of the Title ID when searching the title).
The offical way is to look up the Title List in RAM, this is faster than manually crawling the directory tree. However, there are some restrictions: The Title List contains only titles from the same Maker (as the currently loaded title), plus some special \"jumpable\" system titles.

```
+---------------------------------------------------------------------------------+
|       2FFD800h 1     Titles: Number of titles in below lists (max 76h)          |
|       2FFD801h 0Fh   Titles: Zerofilled                                         |
|       2FFD810h 10h   Titles: Pub Flags (1bit each) ;same maker plus public.sav  |
|       2FFD820h 10h   Titles: Prv Flags (1bit each) ;same maker plus private.sav |
|       2FFD830h 10h   Titles: Jmp Flags (1bit each) ;jumpable or current-title   |
|       2FFD840h 10h   Titles: Mkr Flags (1bit each) ;same maker                  |
|       2FFD850h 3B0h  Titles: Title IDs (8 bytes each)                           |
+---------------------------------------------------------------------------------+
```

Related carthdr entries are:

```
+------------------------------------------------------------------------+
|       [010h].bit0-15  Maker (must match current title for Mkr Flags)   |
|       [01Dh].bir0     Jump (must be set for Jmp Flags)                 |
|       [230h].bit0-63  Title ID (must be nonzero for being listed)      |
|       [238h].bit0-31  Public.sav size (must be nonzero for Pub Flags)  |
|       [23Ch].bit0-31  Private.sav size (must be nonzero for Prv Flags) |
+------------------------------------------------------------------------+
```

The list can contain the hidden Nintendo Zone utility, and DSi ROM cartridges (both provided that Maker does match up with current title).
The jumpable titles with \[01Dh\].bit0 that are always in the list are:

```
+-----------------------------------------------------------------------+
|       00030015484E42xxh  ;System Settings                             |
|       00030005484E4441h  ;DS Download Play                            |
|       00030005484E4541h  ;Pictochat                                   |
|       00030004484E47xxh  ;Nintendo DSi Browser (if installed)         |
+-----------------------------------------------------------------------+
```

The list does NOT contain the Launcher itself, nor files from System Data folder (WifiFirmware, Whitelist, VersionData), nor NDS ROM cartridges, nor anything where Jmp+Mkr flags would be both zero.
If started via 2000300h, then the New Title (from 2000310h) does also receive the Old Title ID (from 2000308h) with Jmp flag being set; ie. permitting to return to the Old Title (to know which title was the old title, one should probably look at 2000000h, or at 2000308h if that\'s still intact in memory?).
Also, the Jmp flag is always set for the current title; ie. permitting the title to reboot itself.



