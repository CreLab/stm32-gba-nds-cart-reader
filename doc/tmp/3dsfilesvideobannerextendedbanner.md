# 3DS Files - Video Banner (Extended Banner)


### Overview
The Extended Banner is used to add text (and optionally an extra texture) to a given banner. It can also (optionally) be used to set an expiration date for a banner.

See \"\\user\\ExBanner\\\" for how the extended-banners are loaded from extdata. The Home Menu extended-banner loading function will immediately return without loading anything if the programID is for System Settings.

### System titles using extended banners

```
+-----------------------------------------------------------------------+
|       Mii Maker                                                       |
|       Face Raiders                                                    |
+-----------------------------------------------------------------------+
```


### Format - Extension: .BIN (\...stored somewhere as extdata on SD card?)

```
+------------------------------------------------------------------------------------+
|       000h 2    Texture width (if texture is used)                                 |
|       002h 2    Texture height (if texture is used)                                |
|       004h 2    Texture colour format (if texture is used)                         |
|       008h 4    Expire Date, Year    ;\                                            
|       00Ch 2    Expire Date, Month   ; what is that, ASCII? or 32bit year???       |
|       010h 2    Expire Date, Day     ;/                                            |
|       014h 15h  Name of texture (if texture is used) ;uh, 15h may mean 16 decimal? |
|       024h 200h Plain text comment (255 character max) to be displayed in the      |
|                   banner on the HOME Menu (UTF-16 or so?)                          |
|       224h 80h  unknown/unspecified                                                |
|       2A4h ..   Texture data (if any)                                              |
+------------------------------------------------------------------------------------+
```

The date used for never-expiring exbanners varies, on retail like with Mii Maker this is 31 Dec 2099 (year=833h, month=0Ch, day=1Fh). The expiration-timestamp is only used for SpotPass exbanners, not extdata-exbanners.

### Texture Colour Formats

```
+-----------------------------------------------------------------------+
|       00h = RGBA8                                                     |
|       01h = RGB8                                                      |
|       02h = RGBA5551                                                  |
|       03h = RGBA565                                                   |
|       04h = RGBA4                                                     |
|       05h = LA8                                                       |
|       06h = HILO8                                                     |
|       07h = L8                                                        |
|       08h = A8                                                        |
|       09h = LA4                                                       |
|       0Ah = L4                                                        |
|       0Bh = A4                                                        |
|       0Ch = ETC1                                                      |
|       0Dh = ETC1A4                                                    |
+-----------------------------------------------------------------------+
```

- [3DS GPU Texture Formats](./3dsgputextureformats.md)

### SpotPass
When Home Menu loads extended-banners, it also attempts to load a \"CBMD\" banner via SpotPass service commands. Normally this CBMD banner doesn\'t exist in extended-banner extdata. This is broken with New3DS titles since Home Menu uses these BOSS commands with the New3DS bitmask in the programID set. The common and language-specific (when offset is non-zero) \"CGFX\" specified by the CBMD are decompressed and processed.

The \"CGFX\" sections in this CBMD are actually the exact same exbanners loaded from normal extdata. The exbanner data from SpotPass is stored to the same state as the extdata-exbanners. No CWAV is loaded from SpotPass data.

The exbanners from SpotPass must have a timestamp less than current_datetime, otherwise they won\'t be parsed. The timestamp for the banner is calculated with: nintimestamp_mktime(out, exbanner-\>year, exbanner-\>month, exbanner-\>day, \<hour=23\>, \<minute = 59\>, \<second = 59\>, \<millisecond = 999\>);



