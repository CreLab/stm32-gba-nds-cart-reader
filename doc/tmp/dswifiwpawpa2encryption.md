# DS Wifi WPA/WPA2 Encryption


### Summary of Encryption/Decryption functions

```
+-------------------------------------------------------------------------------+
|       Encrypt/Decrypt WPA/WEP packets     --> RC4 (Rivest Cipher 4 aka ARC4)  |
|       Encrypt/Decrypt WPA EAPOL key data  --> RC4 (Rivest Cipher 4 aka ARC4)  |
|       Encrypt/Decrypt WPA2 EAPOL key data --> AES-Key-Wrap/Unwrap             |
|       Encrypt/Decrypt WPA2 packets        --> AES-CCMP (AES-CTR-with-CBC-MAC) |
+-------------------------------------------------------------------------------+
```


### RC4 (Rivest Cipher 4 aka ARC4) (WEP/WPA)
Both NDS-Wifi and DSi-Wifi have RC4 hardware support for encrypting and decrypting WEP/WPA packets, however, that\'s working only for full packets (not for the Key Data field in WPA EAPOL packets, so both NDS and DSi will require a RC4 software implementation for the EAPOL part).

```
+------------------------------------------------------------------------------------+
|       RC4(src,dst,len,preskip,key,keylen):                                         |
|       for i=0 to FFh, sbox[i]=i, next i             ;-clear sbox                   |
|       j=0                                           ;\                             
|       for i=0 to FFh                                ;                              |
|         j=(j+sbox[i]+key[i mod keylen]) and FFh     ; apply key                    |
|         swap(sbox[i],sbox[j]                        ;                              |
|       next i                                        ;/                             |
|       i=0, j=0                                                                     |
|       for k=1 to preskip+len                                                       |
|         i=(i+1) and FFh, j=(j+sbox[i]) and FFh, swap(sbox[i],sbox[j])              |
|         if preskip>0 then preskip=preskip-1                                        |
|         else [dst]=[src] xor sbox[(sbox[i]+sbox[j]) and FFh], dst=dst+1, src=src+1 |
|       next k                                                                       |
|       parameters for WEP/WPA packets (done by hardware):                           |
|       key=iv(3)+password(5/13), keylen=3+5/13           ;WEP Key=WEP.IV+Password   |
|       key=iv(3)+from PTK???,    keylen=3+???            ;WPA Key=WEP.IV+???        |
|       src=data(n)+icv(4), srclen=n+4                    ;src, for WEP              |
|       src=data(n)+mic(8)+icv(4), srclen=n+8+4           ;src, for WPA              |
|       preskip=0                                                                    |
|       parameters for WPA EAPOL key data (requires software implementation):        |
|       key=EAPOL[31h..40h]+KEK[00h..0Fh], keylen=10h+10h ;Key = EAPOL Key IV + KEK  |
|       src=EAPOL+63h, srclen=bigendian(EAPOL[61h])       ;src, for WPA              |
|       preskip=100h                                                                 |
|       parameters for 70h-byte block in Nintendo Zone beacons (by software):        |
|       key="!SDW"+LastFourBytesOf(BSSID), keylen=8                                  |
|       src=BeaconTagDDh[18h..87h], srclen=70h                                       |
|       preskip=0                                                                    |
+------------------------------------------------------------------------------------+
```


### AES (Advanced Encryption Standard) (WPA2, DSi only)
NDS-Wifi doesn\'t have any AES hardware support at all, and a software implementation doesn\'t work because NDS-Wifi automatically applies WEP encryption (and adds/removes the WEP.IV field) when seeing the encryption flag in the frame header (and trying to disable the WEP hardware seems to cause encrypted packets not to be received at all).
DSi-Wifi has hardware support for AES-CCMP encrypted packets, however, AES-Key-Unwrap for Key Data in WPA2 EAPOL packets isn\'t supported by hardware, and does thus require a software implementation (the ARM7 AES hardware doesn\'t help because it supports AES-CTR and AES-CCM only).

```
+-------------------------------------------------------------------------------------+
|       AES-Key-Wrap/Unwrap(src,dst,len,key,keylen,mode) (for WPA2 EAPOL Key Data)    |
|       if (len and 7)<>0 then error  ;must be multiple of 8             ;-verify len |
|       aes_setkey(mode,key,keylen)                                      ;-init key   |
|       if mode=ENCRYPT and [src+00h..07h]<>A6A6A6A6A6A6A6A6h then error ;-verify IV  |
|       if mode=ENCRYPT then org=dst+8, count=1                   ;-for wrap          |
|       if mode=DECRYPT then org=dst+len-8, count=((len-8)/8)*6   ;-for unwrap        |
|       [dst+0..len-1] = [src+0..len-1]                  ;copy IV+DATA to dst         |
|       [tmp+00h..07h] = [dst+00h..07h]                  ;read IV from dst+0          |
|       for i=1 to 6                                                                  |
|         ptr=org                                                                     |
|         for j=1 to (len-8)/8                                                        |
|           [tmp+08h..0Fh] = [ptr+00h..07h]              ;read DATA from dst+index    |
|           if mode=ENCRYPT then aes_crypt_block(ENCRYPT,tmp,tmp)  ;encrypt tmp       |
|           [tmp+07h]=[tmp+07h] xor count                ;adjust byte[7]              |
|           if mode=DECRYPT then aes_crypt_block(DECRYPT,tmp,tmp)  ;decrypt tmp       |
|           [ptr+00h..07h] = [tmp+08h..0Fh]              ;writeback DATA to dst+index |
|           if mode=ENCRYPT then ptr=ptr+8, count=count+1                             |
|           if mode=DECRYPT then ptr=ptr-8, count=count-1                             |
|         next j                                                                      |
|       next i                                                                        |
|       [dst+00h..07h] = [tmp+00h..07h]                  ;writeback IV to dst+0       |
|       if mode=DECRYPT and [dst+00h..07h]<>A6A6A6A6A6A6A6A6h then error ;-verify IV  |
|       Parameters for Wrap/Unwrap:                                                   |
|       mode=ENCRYPT  ;<-- for Wrap (encrypt, used by access points)                  |
|       mode=DECRYPT  ;<-- for Unwrap (decrypt, used by clients)                      |
|       key=KEK, keylen=10h bytes (128bit)                                            |
|       src=EAPOL+63h, srclen=bigendian(EAPOL[61h])                                   |
+-------------------------------------------------------------------------------------+
```

The \"aes_setkey\" and \"aes_crypt_block\" functions are same as the BIG-ENDIAN implementations described in DSi AES chapter:
- [DSi Advanced Encryption Standard (AES)](./dsiadvancedencryptionstandardaes.md)

### Access Points / Keys
Keys for different access points are stored in Wifi-FLASH. Access Point 1-3 can be configured as Open/WEP only, and Access Point 4-6 can be Open/WEP/WPA/WPA2 (these extra entries exist on DSi only, the standard NDS firmware doesn\'t have free memory for storing access point 4-6).
- [DS Firmware Wifi Internet Access Points](./dsfirmwarewifiinternetaccesspoints.md)

### WPA/TKIP Encrypted Packets

```
+-----------------------------------------------------------------------------------+
|       .. MAC Header         ;-Normal Header                                       |
|       1  TSC1               ;\                   WEPSeed[1]=(TSC1 OR 20h) AND 7Fh 
|       1  WEPSeed[1]         ; WEP IV and Flags                                    |
|       1  TSC0 (LSB)         ; (Flags: bit0-4=Rsvd, bit5=ExtIV, bit6-7=KeyID)      |
|       1  Flags              ;/    (bit5: 0=No/WEP, 1=Yes/TKIP)                    |
|       1  TSC2               ;\                                                    
|       1  TSC3               ; WPA Extended IV                                     |
|       1  TSC4               ;                                                     |
|       1  TSC5 (MSB)         ;/                                                    |
|       .. Data               ;-Normal Data           ;\                            
|       8  MIC                ;-WPA MIC "Michael"     ; encrypted area              |
|       4  ICV                ;-WEP ICV               ;/                            |
|       4  FCS                ;-Normal FCS                                          |
+-----------------------------------------------------------------------------------+
```


### WPA2/AES-CCMP Encrypted Packets

```
+------------------------------------------------------------------------------+
|       .. MAC Header         ;-Normal Header                                  |
|       1  PN0 (LSB)          ;\                                               
|       1  PN1                ; CCMP Header (IV and Flags)                     |
|       1  Rsvd               ; (Flags: bit0-4=Rsvd, bit5=ExtIV, bit6-7=KeyID) |
|       1  Flags              ;     (bit5: 0=No/WEP, 1=Yes/TKIP)               |
|       1  PN2                ;                                                |
|       1  PN3                ;                                                |
|       1  PN4                ;                                                |
|       1  PN5 (MSB)          ;/                                               |
|       .. Data               ;-Normal Data           ;\encrypted area         
|       8  MIC                ;-CCMP MIC "AES MAC?"   ;/                       |
|       4  FCS                ;-Normal FCS                                     |
+------------------------------------------------------------------------------+
```

CCMP related: A2 (MPDU address 2), AAD, PN, Priority field of MPDU.

### TKIP MIC

```
+-----------------------------------------------------------------------+
|       6  DA                                                           |
|       6  SA                                                           |
|       1  Priority (0) (reserved for future)                           |
|       3  Zero (0) (also reserved for future)                          |
|       .. Data                                                         |
|       8  MIC (M0..M7) (aka L0..L3, R0..R3)                            |
+-----------------------------------------------------------------------+
```


TKIP mixing

```
+-----------------------------------------------------------------------+
|       TTAK     = Phase1 (TK, TA, TSC)                                 |
|       WEP seed = Phase2 (TTAK, TK, TSC)                               |
+-----------------------------------------------------------------------+
```




