# 3DS Files - Video Banner (CBMD)


CBMD - CTR Banner Model Data (archive for CGFX/CWAV files)
These are stored in CXI ExeFS:/banner and optionally in extdata exbanner.
This is used for banners of titles you see in the home menu.
BNR used for the app banners in the CXI/exbanner is the same as CBMD with CWAV at the end (uh, who is \"BNR\", and is that CWAV always supported in all cases, or only for that \"BNR\" thing?).

### CBMD Header

```
+-------------------------------------------------------------------------------------+
|       000h 4     ID "CBMD"                                                          |
|       004h 4     Zero                                                               |
|       008h 4     CGFX Offset for Default (88h)  ;-main CGFX file (for all regions)  |
|       00Ch 4     CGFX Offset for EUR-English    ;\                                  
|       010h 4     CGFX Offset for EUR-French     ; region-specific CGFX files        |
|       014h 4     CGFX Offset for EUR-German     ; (or 0=None)                       |
|       018h 4     CGFX Offset for EUR-Italian    ; (these are smaller CGFX files,    |
|       01Ch 4     CGFX Offset for EUR-Spanish    ; usually with one or two custom    |
|       020h 4     CGFX Offset for EUR-Dutch      ; Textures) (3DS Activity Log has   |
|       024h 4     CGFX Offset for EUR-Portuguese ; more custom entries though)       |
|       028h 4     CGFX Offset for EUR-Russian    ; (Nintendo Network ID Settings     |
|       02Ch 4     CGFX Offset for JPN-Japanese   ; doesn't have any custom CGFX's)   |
|       030h 4     CGFX Offset for USA-English    ;                                   |
|       034h 4     CGFX Offset for USA-French     ;    (unknown if CHN/KOR/TWN are    |
|       038h 4     CGFX Offset for USA-Spanish    ;    also supported?)               |
|       03Ch 4     CGFX Offset for USA-Portuguese ;/                                  |
|       040h 44h   Padding (0)                    ;<-- XXX probably CHN/KOR/TWN here? |
|       084h 4     CWAV Offset for Sound wave data                                    |
|       088h ..    CFGX/CWAV data area...                                             |
+-------------------------------------------------------------------------------------+
```


\"The common CGFX is used if the CGFX offset for the system region/language is zero. Those optional offsets can be used in extdata exbanner, but separate CBMD banner files for each region/language can be used as well.\"

### Entry Size
The header contains only offsets. To compute the size, search the next bigger offset (or use the filesize as max offset), and then subtract the current offset from that value. Note: The list does usually contain increasing offsets (but it may be a bad idea to rely on that, eg. EUR-Spanish and USA-Spanish might use the same offsets).

### CGFX Graphics
- [3DS Files - Video Archive (CGFX)](./3dsfilesvideoarchivecgfx.md)
Banner CGFX files are LZ11-compressed, the decompressed CGFX size shouldn\'t exceed 80000h bytes for banners.

### CWAV Sound
- [3DS Files - Sound Wave Data (CWAV Format)](./3dsfilessoundwavedatacwavformat.md)
Banner CWAV total channels must be 2, and the length of the audio must be 3 seconds or less (uh, is that regardless of sample rate/sample size?), otherwise the sound will play incorrectly (beeping/clicking) or the model may fail to load.



