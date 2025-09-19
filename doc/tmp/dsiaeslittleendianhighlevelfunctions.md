# DSi AES Little-Endian High Level Functions


**AES-CTR (Counter)**
aes_crypt_ctr(src,dst,len,nc_off,iv)

```
+-----------------------------------------------------------------------+
|       aes_se                                                          |
| tkey(ENCRYPT,key,key_size]                                 ;-init key |
- |       [ctr+0                                                          |
- | ..15] = [iv+0..15]                                         ;-init ctr |
- |       n=[nc_off]                                                      |
|                                                                       |
|   while len>0   ;code is 100% same for ENCRYPT and DECRYPT         ;\ 
|         if                                                            |
| n=0                                                         ; encrypt |
|           aes_                                                        |
| crypt_block(ENCRYPT,ctr,tmp)                             ; or decrypt |
|           l                                                           |
| ittleendian(ctr)=littleendian(ctr)+1   ;increment counter   ; message |
|                                                                       |
- |      [dst] = [src] xor [tmp+n]                                      ; |
|                                                                       |
|     src=src+1, dst=dst+1, len=len-1, n=(n+1) and 0Fh               ;/ |
- |       [nc_off]=n                                                      |
+-----------------------------------------------------------------------+
```


**AES-CCM (Counter with CBC-MAC)**
aes_ccm_crypt(mode,src,dst,msg_len,iv,iv_len,xtra,xtra_len,mac,mac_len)

```
+-----------------------------------------------------------------------+
|       if m                                                            |
| ac_len<4 or mac_len>16 or (mac_len and 1)=1 then error       ;\limits 
|                                                                       |
|   if iv_len<7 or iv_len>13 then error                              ;/ |
|       aes_se                                                          |
| tkey(ENCRYPT,key,key_size]                                 ;-init key |
|                                                                       |
|   ctr_len = 15-iv_len                                              ;\ 
- |       [ctr+1                                                          |
| 5]=ctr_len-1          ;bit3..7=zero   ;1 byte (ctr_len)    ; init ctr |
|                                                                       |
- |    [ctr+(15-iv_len)..14] = [iv+0..(iv_len-1)]  ;7..13 bytes (iv)    ; |
|                                                                       |
- |   [ctr+0..(14-iv_len)]=littleendian(0)  ;8..2 bytes (counter=0)    ;/ |
|                                                                       |
- |   [cbc+0..15]=littleendian(msg_len)  ;-[(iv_len+1)..15]=msg_len    ;\ 
|                                                                       |
- |    if [cbc+15..15-iv_len]<>0 then error  ;msg_len overlaps iv/flags ; |
|                                                                       |
- |    [cbc+(15-iv_len)..14]=[iv+0..iv_len-1] ;-[1..iv_len]=iv/nonce    ; |
- |       [cbc+1                                                          |
| 5].bit7=0  ;reserved/zero   ;\                             ; init cbc 
|                                                                       |
- |    [cbc+15].bit6=(xtra_len>0)        ; [15]=flags                   ; |
|                                                                       |
- |    [cbc+15].bit5..3=(mac_len/2-1)    ;                              ; |
|                                                                       |
- |    [cbc+15].bit2..0=(ctr_len-1)      ;/                             ; |
|                                                                       |
|   aes_crypt_block(ENCRYPT,cbc,cbc)      ;UPDATE_CBC_MAC            ;/ |
|                                                                       |
|   if NintendoDSi then                                              ;\ 
|                                                                       |
|      a=0 ;the DSi hardware doesn't support xtra_len encoding at all ; |
|                                                                       |
|    elseif xtra_len<0FF00h then                                      ; |
- |         [                                                             |
- | cbc+14..15]=[cbc+14..15] xor littleendian(xtra_len), a=2      ; weird |
|       elseif                                                          |
|  xtra_len<100000000h then                                  ; encoding |
|                                                                       |
- |  [cbc+14..15]=[cbc+14..15] xor littleendian(FFFEh)              ; for |
- |         [cbc                                                          |
- | +10..13]=[cbc+10..13] xor littleendian(xtra_len), a=6      ; xtra_len |
|                                                                       |
|    else                                                             ; |
|                                                                       |
- |      [cbc+14..15]=[cbc+14..15] xor littleendian(FFFFh)              ; |
|                                                                       |
- |     [cbc+6..13] =[cbc+6..13]  xor littleendian(xtra_len), a=10     ;/ |
|       while                                                           |
|  xtra_len>0                                                 ;\scatter 
|         z=                                                            |
| min(xtra_len,16-a)                                           ; cbc by |
|                                                                       |
- | [cbc+16-a-z..(15-a)]=[cbc+16-a-z..(15-a)] xor [xtra+0..(z-1)]  ; xtra |
|         aes_                                                          |
| crypt_block(ENCRYPT,cbc,cbc)    ;UPDATE_CBC_MAC            ; (if any) |
|                                                                       |
|     xtra=xtra+z, xtra_len=xtra_len-z, a=0                          ;/ |
|                                                                       |
|   while msg_len>0                                                  ;\ 
|                                                                       |
|      littleendian(ctr)=littleendian(ctr)+1   ;increment counter     ; |
|                                                                       |
|      aes_crypt_block(ENCRYPT,ctr,tmp)    ;CTR_CRYPT                 ; |
|         z=m                                                           |
| in(msg_len,16)                                              ; encrypt |
|         if mod                                                        |
| e=ENCRYPT                                                ; or decrypt |
- |           [                                                           |
- | cbc+(16-z)..15] = [cbc+(16-z)..15] xor [src+0..(z-1)]       ; message |
|                                                                       |
- | [dst+0..(z-1)] = [src+0..(z-1)] xor [tmp+(16-z)..15]           ; body |
|                                                                       |
|      if mode=DECRYPT                                                ; |
|                                                                       |
- |        [cbc+(16-z)..15] = [cbc+(16-z)..15] xor [dst+0..(z-1)]       ; |
|                                                                       |
|      aes_crypt_block(ENCRYPT,cbc,cbc)    ;UPDATE_CBC_MAC            ; |
|                                                                       |
|     src=src+z, dst=dst+z, msg_len=msg_len-z                        ;/ |
|                                                                       |
- |   [ctr+0..(14-iv_len)]=littleendian(0)  ;reset counter=0           ;\ 
|       aes_c                                                           |
| rypt_block(ENCRYPT,ctr,tmp)      ;CTR_CRYPT                 ; message |
- |       [cbc+0.                                                         |
- | .15] = [cbc+0..15] xor [tmp+0..15]                        ; auth code |
|       z=m                                                             |
| ac_len                                                        ; (mac) |
|                                                                       |
- |    IF mode=ENCRYPT then [mac+0..(z-1)] = [cbc+(16-z)..15]           ; |
|                                                                       |
- |   IF mode=DECRYPT and [mac+0..(z-1)] <> [cbc+(16-z)..15] then error;/ |
+-----------------------------------------------------------------------+
```


**AES-Key-Wrap/Unwrap**
This is used for EAPOL Key Data in WPA2 Wifi packets, however, neither
DSi-ARM7 nor DSi-Wifi do support that by hardware, so the unwrap
(decrypt) must be implemented by software. For details see:
- [DS Wifi WPA/WPA2 Encryption](./dswifiwpawpa2encryption.md)

Below are some other AES variants (just for curiosity - those variants
aren\'t used in DSi):

**AES-CBC (Cipher-block chaining)**
aes_crypt_cbc(mode,src,dst,len,iv)

```
+-----------------------------------------------------------------------+
|       aes_se                                                          |
| tkey(mode,key,key_size]                                    ;-init key |
- |       [cbc+0                                                          |
- | ..15] = [iv+0..15]                                         ;-init cbc |
|       if (len AND 0Fh)>0 then error                                   |
|                                                                       |
|   while len>0                                                      ;\ 
|                                                                       |
|      if mode=ENCRYPT                                                ; |
|                                                                       |
- |        [dst+0..15] = [src+0..15] xor [cbc+0..15]                    ; |
|           a                                                           |
| es_crypt_block(mode,dst,dst)                                ; encrypt |
- |           [cbc                                                        |
- | +0..15] = [dst+0..15]                                    ; or decrypt |
|         if                                                            |
| mode=DECRYPT                                                ; message |
|                                                                       |
- |        [tmp+0..15] = [src+0..15]                                    ; |
|                                                                       |
|        aes_crypt_block(mode,src,dst)                                ; |
|                                                                       |
- |        [dst+0..15] = [dst+0..15] xor [cbc+0..15]                    ; |
|                                                                       |
- |        [cbc+0..15] = [tmp+0..15]                                    ; |
|                                                                       |
|     src=src+16, dst=dst+16, len=len-16                             ;/ |
+-----------------------------------------------------------------------+
```


**AES-CFB128 (Cipher feedback on 128bits, aka 16 bytes)**
aes_crypt_cfb128(mode,src,dst,len,iv_off,iv)

```
+-----------------------------------------------------------------------+
|       aes_se                                                          |
| tkey(ENCRYPT,key,key_size]                                 ;-init key |
- |       [cfb+0                                                          |
- | ..15] = [iv+0..15]                                         ;-init cfb |
- |       n=[iv_off]                                                      |
|                                                                       |
|   while len>0                                                      ;\ 
|         if                                                            |
| n=0 then aes_crypt_block(ENCRYPT,cfb,cfb)                   ; encrypt |
|         if mod                                                        |
- | e=DECRYPT then c=[src], [dst]=c xor [cfb+n], [cfb+n]=c   ; or decrypt |
|         if                                                            |
- | mode=ENCRYPT then c=[cfb+n] xor [src], [cfb+n]=c, [dst]=c   ; message |
|                                                                       |
|     src=src+1, dst=dst+1, len=len-1, n=(n+1) and 0Fh               ;/ |
- |       [iv_off]=n                                                      |
+-----------------------------------------------------------------------+
```


**AES-CFB8 (Cipher feedback on 8bits, aka 1 byte, very inefficient)**
aes_crypt_cfb8(mode,src,dst,len,iv)

```
+-----------------------------------------------------------------------+
|       aes_se                                                          |
| tkey(ENCRYPT,key,key_size]                                 ;-init key |
- |       [cfb+0                                                          |
- | ..15] = [iv+0..15]                                         ;-init cfb |
- |       n=[iv_off]                                                      |
|                                                                       |
|   while len>0                                                      ;\ 
|                                                                       |
|      aes_crypt_block(ENCRYPT,cfb,tmp)                               ; |
- |         [cf                                                           |
- | b+1..15] = [cfb+0..14]   ;shift with 8-bit step             ; encrypt |
|         if mod                                                        |
- | e=DECRYPT then [cfb+0] = [src+(n xor 0Fh)]               ; or decrypt |
- |         [ds                                                           |
- | t+(n xor 0Fh)] = [src+(n xor 0Fh)] xor [tmp+15]  ;shift-in  ; message |
|                                                                       |
- |      if mode=ENCRYPT then [cfb+0] = [dst+(n xor 0Fh)]               ; |
|                                                                       |
|     len=len-1, n=n+1                                               ;/ |
- |       [iv_off]=n                                                      |
+-----------------------------------------------------------------------+
```


**AES-ECB (Electronic codebook, very basic, very insecure)**
aes_crypt_ecb(mode,src,dst,len)

```
+-----------------------------------------------------------------------+
|       aes_se                                                          |
| tkey(mode,key,key_size]                                    ;-init key |
|       if (len AND 0Fh)>0 then error                                   |
|       while                                                           |
|  len>0                                                      ;\encrypt 
|         aes_cr                                                        |
| ypt_block(mode,src,dst)                                  ; or decrypt |
|         src                                                           |
| =src+16, dst=dst+16, len=len-16                             ;/message |
+-----------------------------------------------------------------------+
```




