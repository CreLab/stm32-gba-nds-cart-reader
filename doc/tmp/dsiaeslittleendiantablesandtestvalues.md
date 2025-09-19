# DSi AES Little-Endian Tables and Test Values



```
+----------------------------------------------------------------------------------+
|      aes_generate_tables:                                                        |
|       for i=0 to 0FFh               ;compute pow and log tables...               |
|         if i=0 then x=01h, else x=x xor x*2, if x>0FFh then x=x xor 11Bh         |
|         pow[i]=x, log[x]=i                                                       |
|       for i=0 to 0FFh               ;generate the forward and reverse S-boxes... |
|         x=pow[0FFh-log[i]]                                                       |
|         x=x xor (x rol 1) xor (x rol 2) xor (x rol 3) xor (x rol 4) xor 63h      |
|         if i=0 then x=63h                                                        |
|         FSb[i]=x, RSb[x]=i                                                       |
|       for i=0 to 0FFh               ;generate the forward and reverse tables...  |
|         x=FSb[i]*2, if x>0FFh then x=x xor 11Bh                                  |
|         FT[i]=(FSb[i]*00010101h) xor (x*01000001h)                               |
|         w=00000000h, x=RSb[i]                                                    |
|         if x<>00h then   ;ie. not at i=63h                                       |
|           w=w+pow[(log[x]+log[0Eh]) mod 00FFh]*1000000h                          |
|           w=w+pow[(log[x]+log[09h]) mod 00FFh]*10000h                            |
|           w=w+pow[(log[x]+log[0Dh]) mod 00FFh]*100h                              |
|           w=w+pow[(log[x]+log[0Bh]) mod 00FFh]*1h                                |
|         RT[i]=w                                                                  |
+----------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      aes_generate_tables_results:                                                |
|       pow[00h..FFh] = 01,03,05,0F,11,..,C7,52,F6,01   ;pow  ;\needed temporarily 
|       log[00h..FFh] = 00,FF,19,01,32,..,C0,F7,70,07   ;log  ;/for table creation |
|       FSb[00h..FFh] = 63,7C,77,7B,F2,..,B0,54,BB,16   ;Forward S-box             |
|       RSb[00h..FFh] = 52,09,6A,D5,30,..,55,21,0C,7D   ;Reverse S-box             |
|       FT[00h..FFh] = C66363A5,F87C7C84,..,2C16163A    ;Forward Table             |
|       RT[00h..FFh] = 51F4A750,7E416553,..,D0B85742    ;Reverse Table             |
+----------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      aes_setkey_results:                                                           |
|       key = "AES-Test-Key-Str-1234567-Abcdefg"  ;use only 1st bytes for 128/192bit |
|       128bit ENCRYPT --> RK[0..9..30..43] = 2D534541..2783080F..93AF7DF0..827EE10D |
|       192bit ENCRYPT --> RK[0..9..30..51] = 79654B2D..9708FA95..2529372B..C66C19FA |
|       256bit ENCRYPT --> RK[0..9..30..59] = 3332312D..DF5C92A5..74174E2E..3C8ADAE6 |
|       128bit DECRYPT --> RK[0..9..30..43] = AEABCD4D..ECD33F19..8C87B246..7274532D |
|       192bit DECRYPT --> RK[0..9..30..51] = AFA9796F..72A3EFE5..455646C7..37363534 |
|       256bit DECRYPT --> RK[0..9..30..59] = 0ED52830..4601F929..415A7D65..67666564 |
+------------------------------------------------------------------------------------+
```



```
+---------------------------------------------------------------------------------+
|      aes_crypt_results:                                                         |
|       [key+0..15]    = "AES-Test-Key-Str-1234567-Abcdefg"                       |
|       [iv+0..15]     = "Nonce/InitVector"                                       |
|       [xtra+0..20]   = "Extra-Associated-Data"  ;\for CCM                       
|       iv_len=12, mac_len=16, xtra_len=xx        ;/                              |
|       Unencrypted:   [dta+0..113Fh] = "Unencrypted-Data", 190h x "TestPadding"  |
|       AES-ECB:       [dta+0..113Fh] = 20,24,73,88,..,44,A8,D6,A8  ;\            
|       AES-CBC:       [dta+0..113Fh] = A4,6F,7A,F2,..,58,C9,02,B4  ;             |
|       AES-CFB128:    [dta+0..113Fh] = 20,C6,DB,35,..,9A,83,7F,DB  ; keysize=128 |
|       AES-CFB8:      [dta+0..113Fh] = 55,C7,75,1C,..,24,6E,A6,D1  ;             |
|       AES-CTR:       [dta+0..113Fh] = 20,C6,DB,35,..,AB,09,0C,75  ;             |
|       AES-CCM:       [dta+0..113Fh] = C8,37,D7,F1,..,7B,EF,FC,12  ;             |
|       AES-CCM (ori): [mac+0..0Fh]   = xx,xx,xx,xx,..,xx,xx,xx,xx  ;             |
|       AES-CCM (DSi): [mac+0..0Fh]   = xx,xx,xx,xx,..,xx,xx,xx,xx  ;/            |
|       AES-ECB:       [dta+0..113Fh] = CC,B6,4D,17,..,D3,56,3E,64  ;-keysize=192 |
|       AES-ECB:       [dta+0..113Fh] = A9,A9,9B,3E,..,8A,C6,13,A1  ;-keysize=256 |
+---------------------------------------------------------------------------------+
```




