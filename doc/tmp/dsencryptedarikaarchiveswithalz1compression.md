# DS Encrypted Arika Archives with ALZ1 compression


Used in Arika\'s DSi Dr. Mario and reportedly also in other Arika titles.

```
+-----------------------------------------------------------------------------------+
|       rom:\INFO.DAT - contains encrypted directory                                
|       rom:\GAME.DAT - contains ALZ1 compressed files, and some uncompressed files 
+-----------------------------------------------------------------------------------+
```


### Arika INFO.DAT header

```
+-------------------------------------------------------------------------------+
|       000h 10h   Title (eg. "*Dr.Mario-DSi!!!" used as decryption key)        |
|       010h 14h   Zerofilled                                     ;\            
|       024h 4     Sector size (100h) (if zero: default to 800h)  ;             |
|       028h 4     Unknown, maybe version (1)                     ; encrypted   |
|       02Ch 4     Number of used Directory entries (eg. 288h)    ;             |
|       030h N*30h Directory entries (see below)                  ;/            |
|       ...  ..    Ununsed Directory entries (40h-filled)         ;-unencrypted |
+-------------------------------------------------------------------------------+
```

Arika Directory Entry format:

```
+------------------------------------------------------------------------------------+
|       000h 20h   Filename (ASCII, max 31 chars, plus zeropadding)                  |
|       020h 4     File Size in bytes                                                |
|       024h 4     File Offset in sector units (in GAME.DAT file)                    |
|       028h 4     File Size in sector units                                         |
|       02Ch 4     Decompressed File Size in bytes (same as [20h] when uncompressed) |
+------------------------------------------------------------------------------------+
```

The file names must contain lowercase \"a..z\" in first character (the software is generating a not-so-fast \"quick lookup table\" based on the 1st char, and produces memory corruption if it\'s outside of the \"a..z\" range).
Arika archives contain only files, not folders. However, the filenames do usually contain slashes (eg. \"com/chr/e_eff_vy01.dat\"), so software could split those names into folder+filename, if desired.

### Arika INFO.DAT decryption

```
+-------------------------------------------------------------------------------+
|       if buf[0]=00h then exit ;unencrypted                                    |
|       for i=10h to filesize-1, buf[i]=((buf[i] ror 4) xor FFh)-buf[i AND 0Fh] |
+-------------------------------------------------------------------------------+
```

The strength of the 10h-byte key pattern is that people will have a hard time to realize that the file is encrypted at all; otherwise they could easily decrypt it by just gazing at it in a hex editor.

### Arika ALZ1 compression
ALZ1 is almost identical to LZss, with some useless changes:
The 4-byte fileheader contains \"ALZ1\", without any info about the decompressed size (which must be taken from INFO.DAT instead).
The compression flags are inverted (0=compressed), and processed backwards (LSB first).
The dictionary is stored in separate 1000h-byte ringbuffer (which is initially zerofilled, so the files can directly start with compressed 00h bytes).
The 16bit compression codes are byte-swapped (1st byte is dict.lsb, 2nd byte is dict.msb\*10h+(len-3)), with dict being the dictionary\'s read index.
The dictionary\'s initial write index is FEEh, all compressed/uncompressed data written to dest is also written to the dictionary.

```
+-------------------------------------------------------------------------------------+
|        for i=0 to FFFh, ringbuf[i]=00h, next i   ;required for DSiware titles       |
|        p=0FEEh                           ;initial ringbuf write pointer             |
|       @@collect_more:                                                               |
|        flagbits=[src]+100h, src=src+1    ;8bit flags                                |
|       @@decompress_lop:                                                             |
|        if dst>=dst.end then goto @@decompress_done                                  |
|        flagbits=flagbits SHR 1                                                      |
|        if zero then goto @@collect_more                                             |
|        if carry=1 then                                                              |
|          dta=[src], [dst]=dta, ringbuf[p AND FFFh]=dta, dst=dst+1, p=p+1, src=src+1 |
|        else                                                                         |
|          q=[src]+((src+1]/10h)*100h), len=([src+1] AND 0Fh)+3, src=src+2            |
|          for i=1 to len   ;read from ringbuf[q] (instead of from relative [dst-q])  |
|            dta=ringbuf[q AND FFFh], [dst]=dta, ringbuf[p AND FFFh]=dta              |
|            dst=dst+1, p=p+1, q=q+1                                                  |
|          next i                                                                     |
|        endif                                                                        |
|        goto @@decompress_lop                                                        |
|       @@decompress_done:                                                            |
|        ret                                                                          |
+-------------------------------------------------------------------------------------+
```

ALZ1 compression is also used in PSX Power Spike (in BIZ archives inside of the main IDX/HUG archive). There are two small differences: The DSi version does have the compressed data prefixed by ID \"ALZ1\" (the PSX version doesn\'t have that prefix). The DSi version requires the ringbuffer to be initially zerofilled (the PSX version uses an uncompressed 00h byte before using compressed zeroes).

### Arika ALZ1+LZrev double compression
The file \"com/m2dres_narc.blz\" is double compressed (LZrev inside of ALZ1, which can actually reduce the size because LZrev or ALZ1 alone are having rather poor compression ratios) (whereas, LZrev can be only detected via the \".blz\" extension, so make sure not to forget the extension after handling the first compression layer).
Other files like \"lng/eur/fr/man/man_narc.blz\" are only LZrev compressed.

### Note
ALZ1 seems to be identical to LArc\'s lz5 compression method (except that ALZ1 does initially zerofill the ringbuf; whilst lz5 is using different initial byte patterns).



