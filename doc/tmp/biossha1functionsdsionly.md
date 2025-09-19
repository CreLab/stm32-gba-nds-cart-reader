# BIOS SHA1 Functions (DSi only)


SHA1_Init(struct)
SHA1_Update(struct,src,srclen)
SHA1_Finish(dst,struct)
SHA1_Init_Update_Finish(dst,src,srclen)
SHA1_Init_Update_Finish_Mess(dst,dstlen,src,srclen)
SHA1_Compare_20_Bytes(src1,src2)
SHA1_Default_Callback(struct,src,len)

### SWI 24h (DSi9/DSi7) - SHA1_Init(struct)
Initializes a 64h-byte structure for SHA1 calculations:

```
+----------------------------------------------------------------------------------+
|       [struct+00h] = 67452301h      ;\                                           
|       [struct+04h] = EFCDAB89h      ;                                            |
|       [struct+08h] = 98BADCFEh      ; initial SHA1 checksum value                |
|       [struct+0Ch] = 10325476h      ;                                            |
|       [struct+10h] = C3D2E1F0h      ;/                                           |
|       [struct+14h] = 00000000h ;lsw ;\total len in bits, initially zero          
|       [struct+18h] = 00000000h ;msw ;/                                           |
|       [struct+1Ch] = uninitialzed   ;-buffer for incomplete fragment (40h bytes) |
|       [struct+5Ch] = 00000000h      ;-incomplete fragment size                   |
|       if [struct+60h] = 00000000h then [struct+60h] = SHA1_Default_Callback      |
+----------------------------------------------------------------------------------+
```

Observe that the incoming \[struct+60h\] value should be 00000000h, otherwise the default callback isn\'t installed (using a different callback doesn\'t make too much sense, and it\'s probably not done by any DSi programs) (the callback feature might be intended to mount hardware accelleration, or to hook, customize, encrypt, or replace the SHA1 functionality).

### SWI 25h (DSi9/DSi7) - SHA1_Update(struct,src,srclen)
This function should be placed between Init and Finish. The Update function can be called multiple times if the source data is split into separate blocks. There\'s no alignment requirement (though the function works faster if src is 4-byte aligned).

```
+------------------------------------------------------------------------------------+
|       [struct+14h]=[struct+14h]+len*8  ;64bit value ;-raise total len in bits      |
|       if [struct+5Ch]<>0 and [struct+5Ch]+len>=40h  ;\                             
|         for i=[struct+5Ch] to 3Fh                   ; merge old incomplete chunk   |
|           [struct+1Ch+i]=[src], src=src+1, len=len-1; with new data and process it |
|         SHA1_Callback(struct,struct+1Ch,40h)        ; (if it gives a full chunk)   |
|         [struct+5Ch]=0                              ;/                             |
|       if len>=40h then                              ;\process full 40h-byte chunks 
|         SHA1_Callback(struct,src,len AND NOT 3Fh)   ; (if src isn't 4-byte aligned |
|         src=src+(len AND NOT 3Fh)                   ; then the DSi BIOS internally |
|         len=len AND 3Fh                             ;/copies all chunks to struct) |
|       if len>0 then                                 ;\                             
|         for i=[struct+5Ch] to [struct+5Ch]+len-1    ; memorize remaining bytes     |
|           [struct+1Ch+i]=[src], src=src+1, len=len-1; as incomplete chunk          |
|           [struct+5Ch]=[struct+5Ch]+1               ;/                             |
+------------------------------------------------------------------------------------+
```


### SWI 26h (DSi9/DSi7) - SHA1_Finish(dst,struct)

```
+-------------------------------------------------------------------------------------+
|       [total_len]=bswap8byte([struct+14h]) ;get total len in bits in big-endian     |
|       SHA1_Update(struct,value_80h,1)                            ;append end byte   |
|       while [struct+5Ch]<>38h do SHA1_Update(struct,value_00h,1) ;append padding    |
|       SHA1_Update(struct,total_len,8)                            ;append 64bit len  |
|       [struct+14h]=bswap8byte([total_len]) ;restore total len, exclude above update |
|       [dst+00h]=bswap([struct+00h]  ;msw   ;\                                       
|       [dst+04h]=bswap([struct+04h]         ; store SHA1 result at dst               |
|       [dst+08h]=bswap([struct+08h]         ; (in big-endian)                        |
|       [dst+0Ch]=bswap([struct+0Ch]         ;                                        |
|       [dst+10h]=bswap([struct+10h]  ;lsw   ;/                                       |
+-------------------------------------------------------------------------------------+
```


### SHA1_Default_Callback(struct,src,len)

```
+-------------------------------------------------------------------------------------+
|       for j=1 to len/40h                                                            |
|         a=[struct+0], b=[struct+4], c=[struct+8], d=[struct+0Ch], e=[struct+10h]    |
|         for i=0 to 79                                                               |
|           if i=0..15  then w[i] = bswap([src]), src=src+4                           |
|           if i=16..79 then w[i] = (w[i-3] xor w[i-8] xor w[i-14] xor w[i-16]) rol 1 |
|           if i=0..19  then f=5A827999h + e + (d xor (b and (c xor d)))              |
|           if i=20..39 then f=6ED9EBA1h + e + (b xor c xor d)                        |
|           if i=40..59 then f=8F1BBCDCh + e + ((b and c) or (d and (b or c)))        |
|           if i=60..79 then f=CA62C1D6h + e + (b xor c xor d)                        |
|           e=d, d=c, c=(b ror 2), b=a, a=f + (a rol 5) + w[i]                        |
|         [struct+0]=[struct+0]+a, [struct+4]=[struct+4]+b, [struct+8]=[struct+8]+c   |
|         [struct+0Ch]=[struct+0Ch]+d, [struct+10h]=[struct+10h]+e                    |
+-------------------------------------------------------------------------------------+
```


### SWI 27h (DSi9/DSi7) - SHA1_Init_Update_Finish(dst,src,srclen)

```
+-------------------------------------------------------------------------------+
|       [struct+60h]=00000000h  ;want Init to install the default SHA1 callback |
|       SHA1_Init(struct)                                                       |
|       SHA1_Update(struct,src,srclen)                                          |
|       SHA1_Finish(dst,struct)                                                 |
+-------------------------------------------------------------------------------+
```

Always returns r0=1.

### SWI 29h (DSi9/DSi7) - SHA1_Init_Update_Finish_Mess(dst,dstlen,src,srclen)

```
+------------------------------------------------------------------------------------+
|       if dst=0 then exit(r0=1)  ;uh, that's same return value as when okay         |
|       if src=0 and srclen<>0 then exit(r0=0)                                       |
|       [struct+60h]=00000000h                ;\                                     
|       SHA1_Init(struct)                     ; first compute normal SHA1            |
|       SHA1_Update(struct,src,srclen)        ; (same as SHA1_Init_Update_Finish)    |
|       SHA1_Finish(first_sha1,struct)        ;/                                     |
|      @@lop1:                                                                       |
|       i=13h  ;start with LSB of big-endian 20-byte value  ;\increment SHA1 value   
|      @@lop2:                                              ; by one (with somewhat  |
|       [first_sha1+i]=[first_sha1+i]+1, i=i-1              ; uncommon/bugged carry- |
|       if i>=0 and [first_sha1+i+1]=01h then goto @@lop2   ;/out to higher bytes)   |
|       SHA1_Update(struct,first_sha1,14h)    ;\compute 2nd SHA1 across 1st SHA1,    
|       SHA1_Finish(second_sha1,struct)       ;/done without re-initializing struct  |
|       for i=0 to min(14h,dstlen)-1, [dst]=[second_sha1+i], dst=dst+1               |
|       dstlen=dstlen-min(14h,dstlen)                                                |
|       if dstlen<>0 then goto @@lop1 else exit(r0=1)                                |
+------------------------------------------------------------------------------------+
```


### SHA1_Init_Update_Finish_HMAC(dst,key,src,srclen)

```
+-------------------------------------------------------------------------------------+
|       if len(key)>40h then key=SHA1(key) ;convert LONG keys to 14h-bytes length     |
|       if len(key)<40h then zero-pad key to 40h-bytes length                         |
|       for i=0 to 3Fh, [inner_key+i]=[key+i] xor 36h ;\                              
|       [struct+60h]=00000000h                        ;                               |
|       SHA1_Init(struct)                             ; compute 1st SHA1              |
|       SHA1_Update(struct,inner_key,40h)             ; across inner key and data     |
|       SHA1_Update(struct,src,srclen)                ;                               |
|       SHA1_Finish(first_sha1,struct)                ;/                              |
|       for i=0 to 3Fh, [outer_key+i]=[key+i] xor 5Ch ;\                              
|       [struct+60h]=00000000h                        ;                               |
|       SHA1_Init(struct)                             ; compute final SHA1            |
|       SHA1_Update(struct,outer_key,40h)             ; across outer key and 1st SHA1 |
|       SHA1_Update(struct,first_sha1,14h)            ;                               |
|       SHA1_Finish(dst,struct)                       ;/                              |
+-------------------------------------------------------------------------------------+
```


### SWI 28h (DSi9/DSi7) - SHA1_Compare_20_Bytes(src1,src2)
Out: r0=1=match, r0=0=mismatch/error (error occurs if src1=0 or src2=0).



