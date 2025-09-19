# DSi AES Big-Endian Core Function and Key Schedule



```
+------------------------------------------------------------------------------------+
|      aes_crypt_block(mode,src,dst):                                                |
|       Y0 = RK[0] xor [src+00h]                                                     |
|       Y1 = RK[1] xor [src+04h]                                                     |
|       Y2 = RK[2] xor [src+08h]                                                     |
|       Y3 = RK[3] xor [src+0Ch]                                                     |
|       ;below code depending on mode:      <---ENCRYPT--->  -or-  <---DECRYPT--->   |
|       for i=1 to nr-1                                                              |
|         X0      = RK[i*4+0] xor scatter32(FT,Y0,Y1,Y2,Y3)  -or-  (RT,Y0,Y3,Y2,Y1)  |
|         X1      = RK[i*4+1] xor scatter32(FT,Y1,Y2,Y3,Y0)  -or-  (RT,Y1,Y0,Y3,Y2)  |
|         X2      = RK[i*4+2] xor scatter32(FT,Y2,Y3,Y0,Y1)  -or-  (RT,Y2,Y1,Y0,Y3)  |
|         X3      = RK[i*4+3] xor scatter32(FT,Y3,Y0,Y1,Y2)  -or-  (RT,Y3,Y2,Y1,Y0)  |
|         Y0=X0, Y1=X1, Y2=X2, Y3=X3                                                 |
|       [dst+00h] = RK[nr*4+0] xor scatter8(FSb,Y0,Y1,Y2,Y3) -or-  (RSb,Y0,Y3,Y2,Y1) |
|       [dst+04h] = RK[nr*4+1] xor scatter8(FSb,Y1,Y2,Y3,Y0) -or-  (RSb,Y1,Y0,Y3,Y2) |
|       [dst+08h] = RK[nr*4+2] xor scatter8(FSb,Y2,Y3,Y0,Y1) -or-  (RSb,Y2,Y1,Y0,Y3) |
|       [dst+0Ch] = RK[nr*4+3] xor scatter8(FSb,Y3,Y0,Y1,Y2) -or-  (RSb,Y3,Y2,Y1,Y0) |
+------------------------------------------------------------------------------------+
```



```
+---------------------------------------------------------------------------+
|      scatter32(TAB,a,b,c,d):              scatter8(TAB,a,b,c,d):          |
|       w=      (TAB[a.bit0..7])             w.bit0..7   = TAB[a.bit0..7]   |
|       w=w xor (TAB[b.bit8..15] rol 8)      w.bit8..15  = TAB[b.bit8..15]  |
|       w=w xor (TAB[c.bit16..23] rol 16)    w.bit16..23 = TAB[c.bit16..23] |
|       w=w xor (TAB[d.bit24..31] rol 24)    w.bit24..31 = TAB[d.bit24..31] |
|       return w                             return w                       |
+---------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      aes_setkey(mode,key,keysize):  ;out: RK[0..43/51/59], nr=10/12/14              |
|       aes_generate_tables   ;<-- unless tables are already initialized              |
|       if keysize<>128 and keysize<>192 and keysize<>256 then error  ;size in bits   |
|       rc=01h, j=0, jj=keysize/32, nr=jj+6   ;jj=4,6,8      ;\                       
|       for i=0 to (nr+1)*4-1                 ;nr=10,12,14   ; copy 16/24/32-byte key |
|         if i<jj then w=[key+i*4+0..3]                      ; to RK[0..3/5/7]        |
|         else w=w xor RK[i-jj]                              ; and, make              |
|         RK[i]=w, j=j+1                                     ; RK[4/6/8..43/51/59]    |
|         if j=jj then                                       ;                        |
|           w=scatter8(FSb,w,w,w,w)                          ;                        |
|           w=(w ror 8) xor (rc)                             ;                        |
|           j=0, rc=rc*2, if rc>0FFh then rc=rc xor 11Bh     ;                        |
|         if j=4 and jj=8 then w=scatter8(FSb,w,w,w,w)       ;/                       |
|       if mode=DECRYPT then                                                          |
|         for i=0 to nr/2-1     ;swap entries (except middle one)                     |
|           for j=0 to 3                                                              |
|             w=RK[i*4+j], v=RK[nr*4-i*4+j]                                           |
|             RK[i*4+j]=v, RK[nr*4-i*4+j]=w                                           |
|         for i=4 to nr*4-1     ;modify entries (except RK[0..3] and RK[nr*4+0..3])   |
|           w=RK[i], w=scatter8(FSb,w,w,w,w), RK[i]=scatter32(RT,w,w,w,w)             |
+-------------------------------------------------------------------------------------+
```




