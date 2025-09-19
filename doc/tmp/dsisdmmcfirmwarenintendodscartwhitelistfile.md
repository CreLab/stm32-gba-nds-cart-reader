# DSi SD/MMC Firmware Nintendo DS Cart Whitelist File


### FAT16:\\title\\0003000f\\484e4841\\content\\00000001.app (aka NDS Cart Whitelist)
The NDS Cart Whitelist contains checksums of all officially released licensed NDS cartridges (newer NDS Carts that aren\'t included in the list must contain extended NDS Cart Headers with RSA signatures).
That means, unlike the original NDS, the DSi refuses to boot any unlicensed/homebrew NDS software (though some \"DSi compatible\" FLASH carts are bypassing that restriction via exploits in licensed NDS games).
Below Whitelist example is from firmware v1.4E:

```
+-------------------------------------------------------------------------------------+
|      Part 1 ("NDHT") is same in v1.0 through v1.4.5:                                |
|       00000h 4          ID "NDHT"                                                ;\ 
|       00004h 80h        RSA-SHA1 on [00084h..286A7h]                             ;  |
|       00084h 4          Number of titles (00000D76h) (=3446)                     ;  |
|       00088h D76h*30h   Titles (30h bytes each, with two SHA1s)                  ;/ |
|      Part 2 ("NDHX") is same in v1.4 through v1.4.5 (doesn't exist in v1.3):        |
|       286A8h 4          ID "NDHX"                                                ;\ 
|       286ACh 80h        RSA-SHA1 on [2872Ch..4AFBFh]                             ;  |
|       2872Ch 4          Number of titles (000013BCh) (=5052)                     ;  |
|       28730h 13BCh*1Ch  Titles (1Ch bytes each, only one SHA1)                   ;/ |
|      Part 3 ("NDHI") differs in v1.4 versus v1.4.5 (doesn't exist in v1.3):         |
|       4AFC0h 4          ID "NDHI"                                                ;\ 
|       4AFC4h 80h        RSA-SHA1 on [4B044h..4B1B7h]                             ;  |
|       4B044h 4          Number of titles (04h in v1.4E)    ;60h in v1.4.5E       ;  |
|       4B048h 4*5Ch      Specials for A3TE,A6WE,YF7E,YOUF   ;210h on New3DS       ;/ |
|      Footer:                                                                        |
|       4B1B8h 13         Version String ("2832",0Dh,0Ah,"10619",0Dh,0Ah in v1.4E) ;\ 
|       4B1C5h 11         Random garbage (padding to 10h-byte boundary)            ;/ |
+-------------------------------------------------------------------------------------+
```

The Version String at the end can be:

```
+------------------------------------------------------------------------------------+
|       00000000.app v1.0J   (at 286A8h) "2435",0Ah,"8325",0Ah          ;with LF's   |
|       00000000.app v1.3U   (at 286A8h) "2435",0Ah,"8325",0Ah          ;with LF's   |
|       00000001.app v1.4E   (at 4B1B8h) "2832",0Dh,0Ah,"10619",0Dh,0Ah ;with CRLF's |
|       0000000x.app v...    (?)                                                     |
|       00000006.app v1.4.5E (at 4D2C8h) "3067",0Ah,"11437",0Ah         ;with LF's   |
|       0000000x.app v...    (?)                                                     |
|       0000000e.app New3DS  (at 56E08h) "3106",0Ah,"11437",0Ah         ;with LF's   |
+------------------------------------------------------------------------------------+
```

BUG: The Whitelist\'s RSA signatures are NOT checked in firmware v1.4E (whilst other older/newer firmwares like 1.3U, 1.4.2E, and 1.4.5E are checking those signatures).

NDHT Title Structure (30h bytes each):

```
+-------------------------------------------------------------------------------------+
|      This contains all NDS titles released prior to DSi firmware v1.0.              |
|       Start Length  Description                                                     |
|       000h  4   Title ID (Gamecode)                                                 |
|       004h  4   Title version                                                       |
|       008h  20  Phase 1 SHA1-HMAC on 160h-byte cartheader and ARM9+ARM7 areas (?)   |
|       01Ch  20  Phase 2 SHA1-HMAC on ARM9 Overlay and NitroFAT (zero if no overlay) |
+-------------------------------------------------------------------------------------+
```

NDHX Title Structure (1Ch bytes each):

```
+------------------------------------------------------------------------+
|      This contains all NDS titles released prior to DSi firmware v1.4. |
|       000h  4   Title ID (Gamecode)                                    |
|       004h  4   Title version                                          |
|       008h  20  Phase 3 SHA1-HMAC on Icon/Title                        |
+------------------------------------------------------------------------+
```

NDHI Title Structure (5Ch bytes each):

```
+----------------------------------------------------------------------------+
|      This contains extra checks for detecting hacked/exploited NDS titles. |
|       000h  4   Title ID (Gamecode)                                        |
|       004h  4   Title version                                              |
|       008h  8*8 Offset+Length for up to 8 regions (or 0,0=None)            |
|       048h  20  Phase 4 SHA1-HMAC on above region(s)                       |
+----------------------------------------------------------------------------+
```

The 40h-byte SHA1-HMAC keys are contained in Launcher (61h,BDh,DDh,72h,\... for Phase 1+2, and 85h,29h,48h,F3h,\... for Phase 3+4). The RSA key is also contained in Launcher (C7h,F4h,1Dh,27h,\... for all Phases; though the RSA key is missing in firmwares where Nintendo forgot to implement the RSA check, eg. in v1.4E).

Example values for Metroid Demo (\"AMFE\"):

```
+--------------------------------------------------------------------------+
|       41 4D 46 45 00 00 00 00                                     ;\     
|       95 9A B3 09 B7 4E AF 29 2E 97 61 B9 DC E9 5F FE 86 5C 91 4E ; NDHT |
|       D3 94 43 02 64 3A AF C5 D1 E1 3B C0 47 4A A2 98 AB 5D 71 8F ;/     |
|       41 4D 46 45 00 00 00 00                                     ;\NDHX 
|       51 24 FE EF D4 3C 22 42 CC 17 13 0A 72 F8 FA 3B 4D 83 2A B1 ;/     |
+--------------------------------------------------------------------------+
```

Specials related to games:

```
+-----------------------------------------------------------------------+
|       NTR-A3TE-USA = Tak: The Great Juju Challenge                    |
|       NTR-A6WE-USA = FIFA World Cup 2006                              |
|       NTR-YF7E-USA = Fish Tycoon                                      |
|       NTR-YOUF-FRA = Samantha Oups!                                   |
+-----------------------------------------------------------------------+
```


### Newer NDS Carts with RSA
NDS games released after DSi firmware v1.0 have RSA headers without Icon SHA1
NDS games released after DSi firmware v1.4 have RSA headers with Icon SHA1
Accordingly, NDS games released between DSi firmware v1.0 and v1.4 do have whitelist NDHX entries (for the icon), but don\'t need NDHT entries (since that\'s already covered by the RSA header).
Related carthdr flags are:

```
+----------------------------------------------------------------------------+
|       cart[1BFh].bit6 = Cart Header RSA Signature exists                   |
|       cart[1BFh].bit5 = Cart Header has Icon SHA1 at [33Ch]                |
|       cart[378h]      = SHA1 (same as whitelist Phase 1)                   |
|       cart[38Ch]      = SHA1 (same as whitelist Phase 2)                   |
|       cart[33Ch]      = SHA1 (same as whitelist Phase 3) (if above bit5=1) |
+----------------------------------------------------------------------------+
```




