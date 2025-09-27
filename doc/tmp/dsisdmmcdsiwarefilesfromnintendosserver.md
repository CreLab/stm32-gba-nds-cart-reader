# DSi SD/MMC DSiware Files from Nintendo\'s Server


### <http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/000000vv>
The \"000000vv\" file contains the \".app\" file (in encrypted form).

```
+-----------------------------------------------------------------------+
|       Server:  "000000vv"      (AES-CBC encrypted, raw)               |
|       eMMC:    "000000vv.app"  (decrypted, raw)                       |
|       SD Card: "GGGGGGGG.bin"  (ES-block encrypted, with extra data)  |
+-----------------------------------------------------------------------+
```

First, the encrypted Title Key must be decrypted (via AES-CBC):

```
+---------------------------------------------------------------------------------+
|       KEY[00h..0Fh] = Common Key (AF,1B,F5,16,...)        ;from ARM7BIOS        |
|       IV[00h..07h]  = Title ID (00,03,00,tt,gg,gg,gg,gg)  ;from tik/cetk[1DCh]  |
|       IV[08h..0Fh]  = Zerofilled                          ;padding              |
|       Input: Encrypted Title Key                          ;from tik/cetk[1BFh]  |
|       Output: Decrypted Title Key                         ;for use in next step |
+---------------------------------------------------------------------------------+
```

Then, the actual executable/file can be decrypted (also via AES-CBC):

```
+-----------------------------------------------------------------------------------+
|       KEY[00h..0Fh] = Decrypted Title Key                 ;from above step        |
|       IV[00h..01h]  = Usually Zero (or "Index" from tmd?) ;from tmd[1E8h+N*24h] ? |
|       IV[02h..0Fh]  = Zerofilled                          ;padding                |
|       Input: Encrypted file "000000vv"                    ;from http download     |
|       Output: Decrypted file "000000vv.app"               ;saved on eMMC          |
+-----------------------------------------------------------------------------------+
```

The above decryption steps do require a big-endian AES-CBC software implementation (the DSi hardware supports only little-endian, and it supports only AES-CTR and AES-CCM, and, especially, it supports only the \"encrypt\" key schedule, whilst AES-CBC would require a different \"decrypt\" key schedule).

### <http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/cetk>
### <http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/tmd>
### <http://nus.cdn.t.shop.nintendowifi.net/ccs/download/000300tt4ggggggg/tmd.nn>
These files do contain tickets (\"cetk\"), and title metadata (\"tmd\" for newest version, plus \"tmd.nn\" for older versions; with nn=0,1,256,257,512 and the like).
- [DSi SD/MMC DSiware Tickets and Title metadata](./dsisdmmcdsiwareticketsandtitlemetadata.md)
The \"cetk\" file is available only for free system updates (not for titles sold commercially in DSi Shop).

### Downloading
The files can be downloaded with normal web browsers. The homebrew \"NUS Downloader\" utility is also allowing to download those files (and to decrypt them, provided that the \"cetk\" is available).
For free system updates, tickets can be downloaded as \"cetk\" files. For titles sold commercially in DSi ship, tickets must be purchased somehow differently.
For example, the updates for DSi System Settings (EUR) can be downloaded from:

```
+-------------------------------------------------------------------------------------+
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/00030015484e4250/tmd      |
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/00030015484e4250/cetk     |
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/00030015484e4250/00000002 |
|       http://nus.cdn.t.shop.nintendowifi.net/ccs/download/00030015484e4250/00000003 |
+-------------------------------------------------------------------------------------+
```

The tmd and cetk files are unencrypted. The 00000002 and 00000003 files are encrypted executables (containing System Settings v2 and v3).

### Older Versions
Nintendo is usually keeping older \"000000vv\" files on their server, so one could still download those older versions.
The oldest/original version would be usually \"00000000\", however, in case of system files that are pre-installed on all consoles, only later versions are available as updates (ie. starting with \"00000001\", or for some reason, with \"00000002\", in case of system settings).
The tmd/cetk files are available only for the newest version (meaning that some cosmetic values like title size & title version are adjusted for the newest version; the cetk\'s AES-CBC key usually doesn\'t change for updates, so older versions can be still decrypted with newer cetk\'s).
Older versions are usually deleted on internal eMMC storage, so only the \"000000vv.app\" file exists.



