# 3DS Files - Archive arcless


**arcless Format**
This is a very simple archive format, found in some LZ-compressed files,
eg. in 3DS Sound and 3DS Camera (RomFS:\\lyt\\C.LZ an
RomFS:\\shaders\\shaders.LZ), 3DS Picture Picke
(RomFS:\\sound\\csnd.LZ), and also in uncompressed form, eg. 3DS Soun
(RomFS:\\res\\S.pack).

```
+-----------------------------------------------------------------------+
|       00                                                              |
| 0h+N*40h 38h     Filename (ASCII, zeropadded)                      ;\ 
|       0                                                               |
| 38h*N*40h 4       File Offset (always 80h-aligned)                  ; |
|       03Ch*N*4                                                        |
| 0h 4       File Size                                         ; header |
|       .                                                               |
| .         1       Zero (indicates end of directory)                 ; |
|       ..                                                              |
|          ..      Zeropadding to 80h-byte boundary                  ;/ |
|       xxx*80                                                          |
| h    ..      File data (at above offsets)                      ;\data 
|       ..                                                              |
|          ..      Zeropadding to 80h-byte boundary, after each file ;/ |
+-----------------------------------------------------------------------+
```

The header doesn\'t contain any ID (like \"NARC\", \"SARC\", or \"darc\
or so). However, one can more or less reliably detect it by checking for
valid ASCII characters, zeropaddings, 1st Offset being located after the
directory, further Offsets being located at Offset+Size+Alignment from
previous entry, and with Offset+Size not exceeding the archive size.



