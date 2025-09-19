# DSi AES Big-Endian Tables and Test Values



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
|         FT[i]=(FSb[i]*01010100h) xor (x*01000001h)                               |
|         w=00000000h, x=RSb[i]                                                    |
|         if x<>00h then   ;ie. not at i=63h                                       |
|           w=w+pow[(log[x]+log[0Eh]) mod 00FFh]*1h                                |
|           w=w+pow[(log[x]+log[09h]) mod 00FFh]*100h                              |
|           w=w+pow[(log[x]+log[0Dh]) mod 00FFh]*10000h                            |
|           w=w+pow[(log[x]+log[0Bh]) mod 00FFh]*1000000h                          |
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
|       FT[00h..FFh] = A56363C6,847C7CF8,..,3A16162C    ;Forward Table             |
|       RT[00h..FFh] = 50A7F451,5365417E,..,4257B8D0    ;Reverse Table             |
+----------------------------------------------------------------------------------+
```



```
+------------------------------------------------------------------------------------+
|      aes_setkey_results:                                                           |
|       key = "AES-Test-Key-Str-1234567-Abcdefg"  ;use only 1st bytes for 128/192bit |
|       128bit ENCRYPT --> RK[0..9..30..43] = 2D534541..ED0DC6FA..43DAC81C..0F5026BB |
|       192bit ENCRYPT --> RK[0..9..30..51] = 2D534541..4AAB3D82..29CA38D2..CA4DFE3B |
|       256bit ENCRYPT --> RK[0..9..30..59] = 2D534541..1AA51359..CCB886C8..88956C9C |
|       128bit DECRYPT --> RK[0..9..30..43] = F653079B..47DD8A1C..1C2070A7..7274532D |
|       192bit DECRYPT --> RK[0..9..30..51] = 3CEC6AFF..C4F96B6F..AE36B4AE..7274532D |
|       256bit DECRYPT --> RK[0..9..30..59] = DE7ADCD9..8C559ADD..067A387E..7274532D |
+------------------------------------------------------------------------------------+
```



```
+---------------------------------------------------------------------------------+
|      aes_crypt_results:                                                         |
|       [key+0..15]    = "AES-Test-Key-Str-1234567-Abcdefg"                       |
|       [iv+0..15]     = "Nonce/InitVector"                                       |
|       [xtra+0..20]   = "Extra-Associated-Data"  ;\for CCM                       
|       iv_len=12, mac_len=16, xtra_len=21        ;/                              |
|       Unencrypted:   [dta+0..113Fh] = "Unencrypted-Data", 190h x "TestPadding"  |
|       AES-ECB:       [dta+0..113Fh] = 5F,BD,04,DB,..,E4,07,F4,B6  ;\            
|       AES-CBC:       [dta+0..113Fh] = 0B,BB,53,FA,..,DD,28,6D,AE  ;             |
|       AES-CFB128:    [dta+0..113Fh] = F4,75,4F,0E,..,73,B5,D7,E7  ; keysize=128 |
|       AES-CFB8:      [dta+0..113Fh] = F4,10,6A,83,..,BF,1B,16,3E  ;             |
|       AES-CTR:       [dta+0..113Fh] = F4,75,4F,0E,..,04,DF,EB,BA  ;             |
|       AES-CCM:       [dta+0..113Fh] = FD,1A,6D,98,..,EE,FD,68,F6  ;             |
|       AES-CCM (ori): [mac+0..0Fh]   = FD,F9,FE,85,..,4F,50,3C,AF  ;             |
|       AES-CCM (DSi): [mac+0..0Fh]   = xx,xx,xx,xx,..,xx,xx,xx,xx  ;/            |
|       AES-ECB:       [dta+0..113Fh] = 0E,69,F5,1A,..,9A,5F,7A,9A  ;-keysize=192 |
|       AES-ECB:       [dta+0..113Fh] = C6,FB,68,C1,..,14,89,6C,E0  ;-keysize=256 |
+---------------------------------------------------------------------------------+
```




