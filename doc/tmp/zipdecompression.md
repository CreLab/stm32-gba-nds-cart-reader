# ZIP Decompression


### Overall ZIP structure

```
+-----------------------------------------------------------------------+
|       Local file headers, with file data                              |
|       Central directory, with file headers, and optional signature    |
|       End of central directory record, with optional comment          |
+-----------------------------------------------------------------------+
```


### ZIP Local file header

```
+-------------------------------------------------------------------------------------+
|       000h 4    local file header signature (04034B50h) ("PK",3,4)                  |
|       004h 2    version needed to extract (os*256+major*10+minor) (common=14h=v2.0) |
|       006h 2    general purpose bit flag  (common=0)                                |
|       008h 2    compression method (0=stored, 8=deflated, other=rare?)              |
|       00Ah 2    last mod file time                                                  |
|       00Ch 2    last mod file date                                                  |
|       00Eh 4    crc32 of uncompressed file data (zero when size=0)                  |
|       012h 4    compressed size                                                     |
|       016h 4    uncompressed size                                                   |
|       01Ah 2    file name length                                                    |
|       01Ch 2    extra field length                                                  |
|       01Eh ..   file name (or "folder/file" name)                                   |
|       ...  ..   extra field                                                         |
|       ...  ..   compressed file data                                                |
+-------------------------------------------------------------------------------------+
```


### ZIP Central directory structure
Central directory entries:

```
+--------------------------------------------------------------------------------+
|       000h 4    central file header signature (02014B50h) ("PK",1,2)           |
|       004h 2    version made by                                                |
|       006h 2    version needed to extract                                      |
|       008h 2    general purpose bit flag                                       |
|       00Ah 2    compression method (0=stored, 8=deflated, other=rare?)         |
|       00Ch 2    last mod file time                                             |
|       00Eh 2    last mod file date                                             |
|       010h 4    crc32 of uncompressed file data                                |
|       014h 4    compressed size                                                |
|       018h 4    uncompressed size                                              |
|       01Ch 2    file name length                                               |
|       01Eh 2    extra field length                                             |
|       020h 2    file comment length                                            |
|       022h 2    disk number start                                              |
|       024h 2    internal file attributes                                       |
|       026h 4    external file attributes                                       |
|       02Ah 4    offset of local file header (from begin of disk number [022h]) |
|       02Eh ..   file name (or "folder/file" name)                              |
|       ...  ..   extra field                                                    |
|       ...  ..   file comment (usually ASCII text, if any)                      |
+--------------------------------------------------------------------------------+
```

Central directory signature (optional, after last directory entry)

```
+-----------------------------------------------------------------------+
|       000h 4    header signature (05054B50h) ("PK",5,5)               |
|       004h 2    size of data                                          |
|       006h ..   signature data (variable size, whatever crap)         |
+-----------------------------------------------------------------------+
```


### ZIP End of central directory record

```
+-------------------------------------------------------------------------------------+
|       000h 4    end of central dir signature (06054B50h) ("PK",5,6)                 |
|       004h 2    number of this disk (usually 0000h)                                 |
|       006h 2    number of disk with the start of central directory                  |
|       008h 2    total number of entries in the central directory on this disk       |
|       00Ah 2    total number of entries in the central directory                    |
|       00Ch 4    size of the central directory                                       |
|       010h 4    offset of start of central directory, on disk number [006h]         |
|       014h 2    .ZIP file comment length (can be zero even if comment/junk follows) |
|       016h ..   .ZIP file comment (usually ASCII text, if any)                      |
+-------------------------------------------------------------------------------------+
```


### Official specs
The official ZIP specs can be reportedly found on pkware.com (but it\'s unknown which browsers are capable of viewing that webpage):

```
+-----------------------------------------------------------------------+
|       http://support.pkware.com/home/pkzip/developer-tools/appnote    |
+-----------------------------------------------------------------------+
```

Alternately, the currently latest specs can be found here:

```
+--------------------------------------------------------------------------------+
|       http://pkware.cachefly.net/webdocs/APPNOTE/APPNOTE-6.3.9.TXT  ;July 2020 |
+--------------------------------------------------------------------------------+
```

That specs include info on rarely used things (including other compression methods, encryption, compressed directory entries, and support for 64bit offset/size values).

### Inflate/Deflate
Inflate/Deflate is a common (de-)compression algorithm, used in ZIP files since 1991. And also used by ZLIB, GZIP, PNG. The DSi Browsers GET command includes the string \"Accept-Encoding: deflate, gzip, x-gzip, identity\", so it\'s apparently also used for internet transfers. In the PSX world, it\'s also used by the .CDZ cdrom-image format.
- [Inflate - Core Functions](./inflatecorefunctions.md)
- [Inflate - Initialization & Tree Creation](./inflateinitializationtreecreation.md)
- [Inflate - Headers and Checksums](./inflateheadersandchecksums.md)
Note: Very old ZIP versions from 1989/1990 did use Shrink and Implode instead of Deflate.



