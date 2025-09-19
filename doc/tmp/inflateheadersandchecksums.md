# Inflate - Headers and Checksums


### tinf_gzip_uncompress(dst, destLen, src, sourceLen)

```
+------------------------------------------------------------------------------------+
|      src_start=src, dst_start=dst                 ;memorize start addresses        |
|      if (src[0]<>1fh or src[1]<>8Bh) then ERROR   ;check id bytes                  |
|      if (src[2]<>08h) then ERROR                  ;check method is deflate         |
|      flg=src[3]                                   ;get flag byte                   |
|      if (flg AND 0E0h) then ERROR                 ;verify reserved bits            |
|      src=src+10                                                 ;skip base header  |
|      if (flg AND 04h) then src=src+2+LittleEndian16bit[src]     ;skip extra data   |
|      if (flg AND 08h) then repeat, src=src+1, until [src-1]=00h ;skip file name    |
|      if (flg AND 10h) then repeat, src=src+1, until [src-1]=00h ;skip file comment |
|      hcrc=(tinf_crc32(src_start, src-src_start) & 0000ffffh))   ;calc header crc   |
|      if (flg AND 02h) then x=LittleEndian16bit[src], src=src+2  ;get header crc    |
|      if (flg AND 02h) then if x<>hcrc then ERROR                ;verify header     |
|      tinf_uncompress(dst, destLen, src, src_start+sourceLen-src-8)  ;----> inflate |
|      crc32=LittleEndian32bit[src], src=src+4   ;get crc32 of decompressed data     |
|      dlen=LittleEndian32bit[src], src=src+4    ;get decompressed length            |
|      if (dlen<>destLen) then ERROR                              ;verify dest len   |
|      if (crc32<>tinf_crc32(dst_start,dlen)) then ERROR          ;verify crc32      |
|      ret                                                                           |
+------------------------------------------------------------------------------------+
```


### tinf_quasijarus_uncompress(dst, destLen, src, sourceLen)

```
+----------------------------------------------------------------------------------+
|      src_start=src, dst_start=dst                 ;memorize start addresses      |
|      if (src[0]<>1fh or src[1]<>A1h) then ERROR   ;check id bytes                |
|      src=src+2                                    ;skip header                   |
|      tinf_uncompress(dst, destLen, src, sourceLen-0Ah)          ;----> inflate   |
|      crc32=LittleEndian32bit[src], src=src+4   ;get crc32 of decompressed data   |
|      dlen=LittleEndian32bit[src], src=src+4    ;get decompressed length          |
|      if (dlen<>destLen) then ERROR                              ;verify dest len |
|      if (crc32<>tinf_crc32(dst_start,dlen)) then ERROR          ;verify crc32    |
|      ret                                                                         |
+----------------------------------------------------------------------------------+
```


### tinf_zlib_uncompress(dst, destLen, src, sourceLen)

```
+---------------------------------------------------------------------------------+
|      src_start=src, dst_start=dst         ;memorize start addresses             |
|      hdr=BigEndian16bit[src], src=src+2   ;get header                           |
|      if (hdr MOD 31)<>0 then ERROR        ;check header checksum (modulo)       |
|      if (hdr AND 20h)>0 then ERROR        ;check there is no preset dictionary  |
|      if (hdr AND 0F00h)<>0800h then ERROR ;check method is deflate              |
|      if (had AND 0F000h)>7000h then ERROR ;check window size is valid           |
|      tinf_uncompress(dst, destLen, src, sourceLen-6)      ;------> inflate      |
|      chk=BigEndian32bit[src], src=src+4                   ;get data checksum    |
|      if src-src_start<>sourceLen then ERROR               ;verify src len       |
|      if dst-dst_start<>destLen then ERROR                 ;verify dst len       |
|      if a32<>tinf_adler32(dst_start,destLen)) then ERROR  ;verify data checksum |
|      ret                                                                        |
+---------------------------------------------------------------------------------+
```


### tinf_adler32(src, length)

```
+--------------------------------------------------------------------------------+
|      s1=1, s2=0                                                                |
|      while (length>0)                                                          |
|       k=max(length,5552)    ;max length for avoiding 32bit overflow before mod |
|       for i=0 to k-1, s1=s1+[src], s2=s2+s1, src=src+1, next i                 |
|       s1=s1 mod 65521, s2=s2 mod 65521, length=length-k                        |
|      return (s2*10000h+s1)                                                     |
+--------------------------------------------------------------------------------+
```





