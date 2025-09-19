# BIOS RSA Pseudo Code


### rsa_mpi_pow_mod(dst,src,pubkey,exp,num_exp_bits) ;\[dst\]=\[src\]\^\[exp\] mod \[key\]

```
+-------------------------------------------------------------------------------------+
|       base(rsa__number_size), bigbuf(rsa_number_size*2)                             |
|       [base]=[src], [dst]=1, pow8bit=01h                ;-init base, result, powbit |
|       for i=1 to num_exp_bits                                                       |
|         if [exp] AND pow8bit then rsa_mpi_mul_mod(dst,base)   ;-mul result          |
|         rsa_mpi_mul_mod(base,base)                            ;-square base         |
|         pow8bit=pow8bit ROL 1, exp=exp+carry                  ;-next exp bit        |
|       next i                                                                        |
|       return                                                                        |
+-------------------------------------------------------------------------------------+
```

This is the RSA main function. The exponent is applied by squaring the \"src\" several times, and, if the corresponding exponent bit is set, multiplying the result by the squared value. To avoid the numbers to become incredible large, the modulus is applied after each multiplication (rather than applying it only on the final result).

```
+-----------------------------------------------------------------------------------+
|       For the Private Key formula: Use exp=prvkey, num_exp_bits=rsa_number_size*8 |
|       For the Public Key formula:  Use exp=ptr_to_10001h, num_exp_bits=17         |
+-----------------------------------------------------------------------------------+
```

The parameters and result for \"rsa_mpi_pow_mod\" must be in little-endian. Ie. for DSi, reverse the byte order of the incoming/outgoing values. And, on DSi, use rsa_number_size=80h (aka 128 bytes, aka for 1024bit RSA).

### rsa_mpi_mul_mod(dst,src):

```
+-----------------------------------------------------------------------+
|       rsa_mpi_mul(bigbuf,dst,src)           ;-multiply                |
|       rsa_mpi_mod(bigbuf,pubkey)            ;-modulus                 |
|       [dst]=[bigbuf+0..rsa_number_size-1]   ;-copy to dst             |
|       return                                                          |
+-----------------------------------------------------------------------+
```


### rsa_mpi_mul(dst,src1,src2): ;\[dst\]=\[src1\]\*\[src2\]

```
+---------------------------------------------------------------------------+
|       [dst+0]=0, oldmsw=0                   ;-init first word and oldmsw  |
|       for i=0 to rsa_number_size-4 step 4   ;\                            
|         call @@inner_loop                   ; compute LSWs of destination |
|         src2=src2+4                         ;                             |
|       next i                                ;/                            |
|       src2=src2-4                                                         |
|       for i=rsa_number_size-8 to 0 step -4  ;\                            
|         src1=src1+4                         ; compute MSWs of destination |
|         call @@inner_loop                   ;                             |
|       next i                                ;/                            |
|       return                                                              |
|      ;---                                                                 |
|      @@inner_loop:                                                        |
|       [dst+4]=oldmsw, oldmsw=0                                            |
|       for j=0 to i step 4                                                 |
|         msw:lsw = [src1+j]*[src2-j]                                       |
|         [dst+0]=[dst+0]+lsw                                               |
|         [dst+4]=[dst+4]+msw+cy                                            |
|         oldmsw=oldmsw+cy                                                  |
|       next j                                                              |
|       dst=dst+4                                                           |
|       ret                                                                 |
+---------------------------------------------------------------------------+
```


### rsa_mpi_mod(dst,src): ;\[dst\]=\[dst\] mod \[src\] ;aka division remainder
;Double/Single -\> Single modulo division (mpi/mpi)
;Divisor\'s MSW must be \>= 80000000h

```
+-------------------------------------------------------------------------------------+
|       ebx=rsa_number_size, dst=dst+ebx, i=ebx+4                                     |
|      @@type0_lop:                                                           ;\      
|       if [dst+ebx-4]=0 then goto @@type0_next                               ;       |
|       rsa_mpi_cmp(dst,src), if borrow then goto @@type1_next                ; type0 |
|       rsa_mpi_sub(dst,src), if [dst+ebx-4]<>0 then goto @@type1_next        ; loop  |
|      @@type0_next:                                                          ;       |
|       dst=dst-4, i=i-4, if i>0 then goto @@type0_lop                        ;/      |
|       goto @@done                                                                   |
|      ;--- --- ---                                                                   |
|      @@type1_lop:                                                           ;\      
|       lsw=[dst+ebx-4], msw=[dst+ebx-0]                                      ;       |
|       if msw>=[src+ebx-4] then fac=FFFFFFFFh else fac=msw:lsw / [src+ebx-4] ;       |
|       rsa_mpi_mulsub(dst,src,fac), if carry=0 then goto @@skip_add          ; type1 |
|      @@add_more:                                                            ; loop  |
|       rsa_mpi_add(dst,src)                                                  ;       |
|       [dst+ebx]=[dst+ebx]+carry, if carry=0 then goto @@add_more            ;       |
|      @@skip_add:                                                            ;       |
|       if [dst+ebx-4]=0 then goto @@type0_next                               ;       |
|      @@type1_next:                                                          ;       |
|       dst=dst-4, i=i-4, if i>0 then goto @@type1_lop                        ;/      |
|      @@done:                                                                        |
|       return                                                                        |
+-------------------------------------------------------------------------------------+
```


### rsa_mpi_mulsub(dst,src,fac): ;\[dst\]=\[dst\]-\[src\]\*fac

```
+-------------------------------------------------------------------------------------+
|       oldborrow=0, oldmsw=0                                       ;\                
|       for i=0 to rsa_number_size-4 step 4                         ; process         |
|         msw:lsw = [src+i]*fac, lsw=lsw+oldmsw, oldmsw=msw+carry   ; rsa_number_size |
|         [dst+i]=[dst+i]-lsw-oldborrow, oldborrow=borrow           ; bytes, plus...  |
|       next i                                                      ;/                |
|       [dst+rsa_number_size]=[dst+rsa_number_size]-oldmsw-oldborrow ;-one extra word |
|       return borrow   ;(unlike "rsa_embedded" which returns INVERTED borrow)        |
+-------------------------------------------------------------------------------------+
```


### rsa_mpi_add(dst,src): ;out: \[dst\]=\[dst\]+\[src\], carry

```
+-----------------------------------------------------------------------+
|       carry = 0                                                       |
|       for i=0 to rsa_number_size-4 step 4                             |
|         [dst+i]=[dst+i]+[src+i]+carry                                 |
|       next i                                                          |
|       return carry                                                    |
+-----------------------------------------------------------------------+
```


### rsa_mpi_sub(dst,src): ;out: \[dst\]=\[dst\]-\[src\], borrow/unused

```
+-----------------------------------------------------------------------+
|       borrow = 0                                                      |
|       for i=0 to rsa_number_size-4 step 4                             |
|         [dst+i]=[dst+i]-[src+i]-borrow                                |
|       next i                                                          |
|       return borrow                                                   |
+-----------------------------------------------------------------------+
```


### rsa_mpi_cmp\[dst,src\]: ;compare \[dst\]-\[src\], out: borrow

```
+-----------------------------------------------------------------------+
|       for i=rsa_number_size-4 to 0 step -4                            |
|         temp=[dst+i]-[src+i], if not equal then return borrow         |
|       next i                                                          |
|       return borrow                                                   |
+-----------------------------------------------------------------------+
```

This is about same as \"sub\", but faster (because it can abort the loop upon first difference).



