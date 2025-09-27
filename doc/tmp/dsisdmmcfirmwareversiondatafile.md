# DSi SD/MMC Firmware Version Data File


verdata (00030005-HNLx) is a bundle of data which corresponds to a release of the \"System Menu\" \-- every time Nintendo announces a new version of the system menu, they will update one or more other titles and then update this title. The verdata filesize is constant for all versions/regions (1B50h bytes). Existing verdata downloads on Nintendo\'s server are:

```
+-----------------------------------------------------------------------+
|       00000001..00000009  jpn         (9 versions)                    |
|       00000003..00000009  usa/eur/aus (7 versions)                    |
|       00000001..00000006  chn         (6 versions)                    |
|       00000002..00000006  kor         (5 versions)                    |
+-----------------------------------------------------------------------+
```

Apart from those downloads/updates, each region did probably originally have an older version pre-installed. The japanese 1.0J firmware did oddly have 00000000.app files for BOTH japan and usa?/aus? installed (whereof the latter contained 0.1A instead of 1.0A as version string).

### FAT16:\\title\\0003000f\\484e4cgg\\content\\000000vv.app (aka Version Data)

```
+-----------------------------------------------------------------------+
|       0000h 80h  RSA-SHA1 on entries [0080h..end of file]             |
|       0080h ...  NARC (Nitro Archive) ...                             |
+-----------------------------------------------------------------------+
```

The NARC is a nintendo-specific virtual filesystem. For details, see:
- [DS Cartridge NitroROM and NitroARC File Systems](./dscartridgenitroromandnitroarcfilesystems.md)
The NARC archive contains the following files:

```
+-------------------------------------------------------------------------------------+
|      .twl-nup-cert.der    - server cert for software update server                  |
|      .twl-nup-prvkey.der  - client-side private key for software update server      |
|      .twl-shop-cert.der   - server cert for Shopping Channel server                 |
|      .twl-shop-prvkey.der - client-side private key for Shopping Channel server     |
|      NintendoCA-G2.der    - Certificate Authority cert, used to sign other certs    |
|      eula_url.bin         - URL to the EULA text for this system update,            |
|                             generally https://cfh.t.app.nintendowifi.net/eula/      |
|      nup_host.bin         - server to query for the next system update,             |
|                             generally nus.t.shop.nintendowifi.net:443               |
|      time_stamp.bin       - build date for this version, eg. 00281108 (28 Nov 2008) |
|      user_area_size.bin   - eg. 08000000h (signed) (=128Mbyte? aka 1024 "blocks"?)  |
|      version.bin          - firmware version (and version/region string)            |
+-------------------------------------------------------------------------------------+
```

The NARC is usually mounted as \"verdata:\" device (eg. \"verdata:/version.bin\").
The four \".twl-\*.der\" files are encrypted with ES Block Encryption (using a fixed key):

```
+-----------------------------------------------------------------------+
|       KEY[00h..0Fh] = Constant (08,2F,61,38,...)  ;from ARM7BIOS      |
+-----------------------------------------------------------------------+
```

- [DSi ES Block Encryption](./dsiesblockencryption.md)
For the decrypted .der files (and unecrypted NintendoCA-G2.der file), see
- [DSi SD/MMC Firmware Certificate/Keys (DER)](./dsisdmmcfirmwarecertificatekeysder.md)
The version.bin file contains the firmare version:

```
+----------------------------------------------------------------------------+
|       000h 2    Major Version (0001h)                       (eg. 1)        |
|       002h 2    Minor Version (0000h..0004h)                (eg. 4)        |
|       004h 1Ch  Version/Region string in UTF-16, zeropadded (eg. "1.4.5E") |
+----------------------------------------------------------------------------+
```

The Version/Region string is displayed in System Settings. The region suffix is \"J\"=JAP, \"U\"=USA, \"E\"=EUR, \"A\"=AUS, \"C\"=CHN, \"K\"=KOR, or \"ALL\"=3DS/New3DS.

### DSi Firmware Versions

```
+-------------------------------------------------------------------------------------+
|       0.1    31 Jul 2008  Pre-release v0.1A (accidentally included in v1.0J)        |
|       1.0    09 Sep 2008  Pre-installed v1.0J version (the actual file in v1.0J)    |
|       1.0?   22 Oct 2008? First Update(??) to Japanese Region DSi System Menu       |
|       1.1?   ?            dsibrew:NoneSuch?, wikipedia:Preinstalled1stJpnVersion??  |
|       1.2    18 Dec 2008  Second Update to Japanese Region DSi System Menu          |
|       1.3    03 Apr 2009  Launch Day (USA, EUR, AUS), new "start DSi Camera" button |
|       1.4    29 Jul 2009  Blocks NDS flashcarts, Facebook support to share photos   |
|       1.4.1  07 Sep 2010  Blocks more NDS flashcarts                                |
|       1.4.2  10 May 2011  Blocks DSiWare exploits on SD card (sudokuhax etc.)       |
|       1.4.3  29 Jun 2011  Blocks more NDS flashcarts (only whitelist was updated)   |
|       1.4.4  21 Mar 2012  Blocks DSi cart exploits (CookingCoach/ClassicWordGames)  |
|       1.4.5  11 Dec 2012  Blocks more NDS flashcards                                |
+-------------------------------------------------------------------------------------+
```

JAP region launched first (unknown if there was any pre-installed version prior to the v1.0 update (or if v1.0 was really released as \"update\" at all), unknown if v1.1 did also exist).
USA/EUR/AUS regions launched on 03 Apr 2009 (so only v1.3 and up exist as update?; but they had an older version pre-installed: v1.2U is known to exist).
CHN region launched on 11 Sep 2010 with firmware v1.4.2C (or more probably with v1.4.1C pre-installed?).
KOR region launched at unknown date (probably near chinese launch date) (korean v1.4.1K is known to exist).
CHN and KOR do have version numbers one step higher than normal regions (ie. v1.4 through v1.4.5 are called v1.4.1 through v1.4.6 in china/korea).
3DS and New3DS identify themselves as DSi version v1.4.2ALL.



