# LZ Decompression Functions


### LZSS, Yaz0, LZ11 - Decompression for BIOS/SWI and ZFTR Font Files
LZSS/Yaz0/LZ11 are very similar formats, with small differences in the header and compression codes, which could be summarized as so:

```
+----------------------------------------------------------------------------------+
|       10,ss,ss,Ss   ;ID(10h), Size(Ssssss)          ;-LZSS header                |
|       11,ss,ss,Ss   ;ID(11h), Size(Ssssss)          ;-LZ11 header                |
|       "Yaz0",Ss,ss,ss,ss,0,0,0,0,0,0,0,0            ;-Yaz0 header                |
|       Ff            ;Flags(Ff), each 8 entries      ;-Flags (bit7=first)         |
|       1N,nn,nP,pp   ;Disp(Ppp)+1, Len(Nnnn)+111h    ;\                           
|       0N,nP,pp      ;Disp(Ppp)+1, Len(Nn)+11h       ; LZ11, when flag=1          |
|       NP,pp         ;Disp(Ppp)+1, Len(N)+1          ;/                           |
|       0P,pp,Nn      ;Disp(Ppp)+1, Len(Nn)+12h       ;\Yaz0, when flag=0          
|       NP,pp         ;Disp(Ppp)+1, Len(N)+2          ;/                           |
|       NP,pp         ;Disp(Ppp)+1, Len(N)+3          ;-LZSS, when flag=1          |
|       Dd            ;Databyte(Dd)                   ;-When flag other than above |
+----------------------------------------------------------------------------------+
```

Below function can decompress LZSS data (as used by BIOS SWIs), and the LZ11 variant (with 11h in the header; as used by ZFTR font files, but not being compatible with the BIOS SWI functions on neither GBA nor NDS nor DSi).

```
+-------------------------------------------------------------------------------------+
|       if src has "LZ77" or "CMPR" prefix then src=src+4    ;skip prefix (if any)    |
|       typ=byte[src]                                                                 |
|       if typ=59h                            ;YAZ0                                   |
|         errif (bytes[src+0..3]<>"Yaz0") OR (bytes[src+8..15]<>0)                    |
|         fin=dst+BigEndian(word[src+04h]), src=src+16                                |
|       else                                  ;LZSS/LZ11                              |
|         fin=dst+(word[src]/100h), src=src+4                                         |
|       endif                                                                         |
|      @@collect_more:                                                                |
|       flagbits=[src], src=src+1, numflags=8                                         |
|       if typ=59h then flagbits=flagbits XOR 0FFh    ;-invert for YAZ0               |
|      @@decompress_lop:                                                              |
|       if dst>=fin then goto @@decompress_done                                       |
|       if numflags=0 then goto @@collect_more                                        |
|       numflags=numflags-1, flagbits=flagbits*2                                      |
|       if (flagbits AND 100h)=0 then                                                 |
|         [dst]=[src], dst=dst+1, src=src+1                                           |
|       else                                                                          |
|         if typ=10h        ;LZ10 aka LZSS (BIOS SWI compatible)                      |
|           len=3                                                                     |
|           len=len+[src]/10h, disp=001h+([src] AND 0Fh)*100h+[src+1], src=src+2      |
|         elseif typ=11h    ;LZ11 (special extended format)                           |
|           if [src]/10h>1 then len=001h                                              |
|           if [src]/10h<1 then len=011h+([src] AND 0Fh)*10h, src=src+1               |
|           if [src]/10h=1 then len=111h+([src] AND 0Fh)*1000h+[src+1]*10h, src=src+2 |
|           len=len+[src]/10h, disp=001h+([src] AND 0Fh)*100h+[src+1], src=src+2      |
|         elseif typ=59h    ;YAZ0 (special extended format)                           |
|           len=[src]/10h, disp=001h+([src] AND 0Fh)*100h+[src+1], src=src+2          |
|           if len=0 then len=[src]+12h, src=src+1, else len=len+02h                  |
|         endif                                                                       |
|         for i=1 to len, [dst]=[dst-disp], dst=dst+1, next i                         |
|       endif                                                                         |
|       goto @@decompress_lop                                                         |
|      @@decompress_done:                                                             |
|       ret                                                                           |
+-------------------------------------------------------------------------------------+
```

The LZSS variant is implemented in GBA/NDS/DSi BIOS SWI functions:
- [BIOS Decompression Functions](./biosdecompressionfunctions.md)
LZSS and LS11 are used with many NDS/DSi/3DS files. LZSS/LZ11 can be detected by checking for 10h/11h in first byte, and additionally checking for:

```
+-------------------------------------------------------------------------------+
|       Extension is ".lz", ".lz77", ".LZ", or extension is preceeded by "_LZ." |
|       Less common extensions are ".l", ".lex", ".cmp" (and various others)    |
|       Bytes[5..10] (after header+flags) contain IDs alike "NARC",FFFEh etc.   |
|       File starts with "LZ77",10h or "CMPR",10h (both rather uncommon)        |
+-------------------------------------------------------------------------------+
```

Prefix strings exist in a few LZSS files (\"LZ77\" in Super Mario 64 DS, or \"CMPR\" in Nanostray), then followed by normal LZSS data starting with type=10h.
Yaz0 files can be detected by checking for \"Yaz0\" in first 4 bytes. Yaz0 is used by a few titles only (eg. used by DSi Sound, rom:\\texture.szs). Yaz0 is widely believed to use RLE compression (don\'t ask why).

### LZrev - Reverse Decompression

```
+-------------------------------------------------------------------------------------+
|       Used for DSi Font (within TWLFontTable.dat)                                   |
|       Used for 3DS .code files (within NCCH ExeFS filesystems)                      |
|       Used for files with .blz extension (eg. in DSi Flipnote, DSi Paper Plane)     |
|       Used for ALZ1+LZrev double compression with .blz extension (eg. DSi Dr Mario) |
+-------------------------------------------------------------------------------------+
```

This function resembles LZSS, but with src/dst processed in reversed order (starting at highest memory location). Further differences are that the header is replaced by a footer, and, weirdly, data is copied from \"disp+3\" instead of \"disp+1\". The decompression is intended to use a single buffer for src/dst (so the source data will be overwritten during decompression) (in order to avoid overwriting still unprocessed data, some bytes near start of file are usually left uncompressed, eg. for the font files, decompression usually ends somewhere at fin=buf+15h rather than at fin=buf+0).

```
+----------------------------------------------------------------------------------+
|       dest_size=src_size+[src+src_size-4]   ;when dest_size is unknown (for 3DS) |
|       allocate buf(dest_size), copy "src_size" bytes from file to buf            |
|       src=buf+src_size                      ;origin = pointing after footer      |
|       dst=src+(word[src-4])-1               ;dst = src plus extra len            |
|       fin=src-(word[src-8] AND 00FFFFFFh)   ;fin = src minus compressed_len      |
|       src=src-(byte[src-5])-1               ;src = src minus footer_len          |
|      @@collect_more:                                                             |
|       flagbits=[src], src=src-1, numflags=8                                      |
|      @@decompress_lop:                                                           |
|       if src<=fin then goto @@decompress_done                                    |
|       if numflags=0 then goto @@collect_more                                     |
|       numflags=numflags-1, flagbits=flagbits*2                                   |
|       if (flagbits AND 100h)=0 then                                              |
|         [dst]=[src], dst=dst-1, src=src-1                                        |
|       else                                                                       |
|         len=([src]/10h)+3, disp=([src] AND 0Fh)*100h+([src-1])+3, src=src-2      |
|         for i=1 to len, [dst]=[dst+disp], dst=dst-1, next i                      |
|       endif                                                                      |
|       goto @@decompress_lop                                                      |
|      @@decompress_done:                                                          |
|       ret                                                                        |
+----------------------------------------------------------------------------------+
```

Note: The footer_len at \[src-5\] is usually 08h+0..3 (with 0..3 padding bytes to make the footer entries & file size word aligned).

### LZ/Huffman
Apart from the above chubby functions, there are at least two compression schemes trying to implement real serious compression:
- [GBA Cart e-Reader VPK Decompression](./gbacartereadervpkdecompression.md)
- [LZ Decompression Functions ASH0](./lzdecompressionfunctionsash0.md)
Some titles contain regular .zip files (with Stored and Deflated files):

```
+------------------------------------------------------------------------------------+
|       DSi Browser (rom:\skin\std_skin.zip) -- corrupted .zip (with 0D,0A appended) 
|       DSi Shop    (rom:\skin\std_skin.zip) -- intact .zip (unlike above)           
|       3DS Browser applet (RomFS:\browser\page\..\*.zip)                            
+------------------------------------------------------------------------------------+
```

- [ZIP Decompression](./zipdecompression.md)

### Others
Arika has brewed up a obscure compression+archive+encryption format:
- [DS Encrypted Arika Archives with ALZ1 compression](./dsencryptedarikaarchiveswithalz1compression.md)
- [DS Files - Vicarious Vision GFC/GOB Archives with ZLIB compression](./dsfilesvicariousvisiongfcgobarchiveswithzlibcompression.md)



