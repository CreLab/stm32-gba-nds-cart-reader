# DS Wifi WPA/WPA2 Keys and MICs


### Summary of WPA/WPA2 Keys

```
+-------------------------------------------------------------------------------------+
|       PSK  Preshared Key (based on password and SSID)                               |
|       PMK  Pairwise Master Key (same as PSK)                                        |
|       PTK  Pairwise Transient Key (based on PMK, AA, SPA, ANonce, SNonce)           |
|       KCK  EAPOL Key Confirmation Key (PTK.bit0..127)    ;for handshake MIC's       |
|       KEK  EAPOL Key Encryption Key   (PTK.bit128..255)  ;for handshake Key Data    |
|       TK   Temporal Key (TKIP:PTK.bit256..511, CCMP:PTK.bit256..383)                |
|       GMK  Group Master Key (don't care, used only internally by the access point)  |
|       GTK  Group Transient Key (for multicast/broadcast) (based on GMK, AA, GNonce) |
+-------------------------------------------------------------------------------------+
```


### Summary of WPA/WPA2 Seeds

```
+-------------------------------------------------------------------------------+
|       password  ASCII password for the Wifi network                           |
|       SSID      ASCII name of access point                                    |
|       AA        MAC address of access point (BSSID)                           |
|       SPA       MAC address of DSi console                                    |
|       Anonce    Random number from access point (handshake message #1 and #3) |
|       Snonce    Random number from console      (handshake message #2)        |
|       Gnonce    Random number internally used by access point (don't care)    |
+-------------------------------------------------------------------------------+
```


### Summary of WPA/WPA2 Checksums

```
+----------------------------------------------------------------------------+
|       MIC       Message Integrity Code, checksum on EAPOL messages         |
|       PMKID     PMK ID, checksum on PMK and AA, SPA (optional, don't care) |
+----------------------------------------------------------------------------+
```


### PRF(key,keylen, src,srclen, dst,dstlen, numrounds) ;Pseudo-Random Function

```
+------------------------------------------------------------------------------------+
|       for i=0 to (dstlen-1)/14                                                     |
|         call SHA1HMAC(src,srclen, key,keylen, tmpdst)                              |
|         tmpsum[0..13] = tmpdst[0..13]                                              |
|         for j=1 to numrounds-1                        ;only if numrounds>1         |
|           tmpsrc[0..13] = tmpdst[0..13], tmpsrclen=14                              |
|           call SHA1HMAC(tmpsrc,tmpsrclen, key,keylen, tmpdst)                      |
|           tmpsum[0..13] = tmpsum[0..13] XOR tmpdst[0..13]                          |
|         next j                                                                     |
|         src[srclen-1] = src[srclen-1] + 01h           ;increase last byte of src   |
|         len=min(14,(dstlen-i*14))                                                  |
|         dst[i*14+(0..(len-1))] = tmpsum[0..(len-1)]                                |
|       next i                                                                       |
|       src[srclen-1] = src[srclen-1] - (dstlen+13)/14  ;undo increments, if desired |
+------------------------------------------------------------------------------------+
```

Note: This is using SHA1HMAC for both WPA and WPA2 (unlike the MIC, which is computed via MD5HMAC for WPA, and SHA1HMAC for WPA2).

### PSK (Preshared Key) aka PMK (Pairwise Master Key)

```
+----------------------------------------------------------------------------------+
|       key = password,                      keylen = len(password)  ;ASCII string |
|       src = ssid + bytes(00h,00h,00h,01h), srclen = len(ssid)+4    ;ASCII string |
|       dst = PSK,                           dstlen = 32, numrounds=4096           |
|       call PRF(key,keylen, src,srclen, dst,dstlen, numrounds)                    |
|       PMK=PSK                                                                    |
+----------------------------------------------------------------------------------+
```

Computing the PSK/PMK requires 2x4096 SHA1HMAC calculations, which can be quite slow. The speed could be doubled by pre-computing the SHA1 states for \"key XOR 36h\'s\" and \"key XOR 5Ch\'s\". And, the PSK/PMK needs to be calculated only when changing the password/ssid (the DSi stores the PSK in Wifi-FLASH).

### PTK (Pairwise Transient Key) and KCK/KEK/TK

```
+-----------------------------------------------------------------------------------+
|       src[0..21]  = "Pairwise key expansion"                                      |
|       src[22]     = byte(00h)                                                     |
|       src[23..28] = min(AA,SPA)         ;\MAC addresses (AA=BSSID, SPA=console)   
|       src[29..34] = max(AA,SPA)         ;/                                        |
|       src[35..66] = min(ANonce,SNonce)  ;\nonces from 4-way handshake message 1+2 
|       src[67..98] = max(ANonce,SNonce)  ;/                                        |
|       src[99]     = byte(00h)                                                     |
|       srclen = 22+1+6+6+32+32+1 = 100                                             |
|       key=PSK, keylen=32, numrounds=1                                             |
|       dst=PTK, dstlen=64  ;WPA needs dstlen=64 (WPA2 would also work with len=48) |
|       call PRF(key,keylen, src,srclen, dst,dstlen, numrounds)                     |
|       KCK    = PTK[00h..0Fh]   ;-for EAPOL handshake MIC checksums                |
|       KEK    = PTK[10h..1Fh]   ;-for EAPOL handshake Key Data decryption          |
|       TK.key = PTK[20h..2Fh]   ;-for data packets                                 |
|       TX.tx  = PTK[30h..37h]   ;\needed for WPA/TKIP only (not WPA2/AES)          
|       TX.rx  = PTK[38h..3Fh]   ;/                                                 |
|       TK.keyindex = 0                                                             |
+-----------------------------------------------------------------------------------+
```


### GTK (Group Transient Key)

```
+--------------------------------------------------------------------------+
|       GTK.key = GTK[00h..0Fh]  ;-for data packets                        |
|       GTX.tx  = GTK[10h..17h]  ;\needed for WPA/TKIP only (not WPA2/AES) 
|       GTX.rx  = GTK[18h..1Fh]  ;/                                        |
|       GTK.keyindex = 1 or 2      ;WPA: from EAPOL Key Information bit4-5 |
|       GTK.keyindex = 1 or 2      ;WPA2: from EAPOL Key Data KDE entry    |
+--------------------------------------------------------------------------+
```


### MIC (Message Integrity Code)

```
+-------------------------------------------------------------------------------------+
|       oldmic = EAPOL[51h..60h]                                                      |
|       EAPOL[51h..60h] = zerofill                                                    |
|       src=EAPOL, srclen=EAPOL[02h]*100h+EAPOL[03h]                                  |
|       key=KCK, keylen=16                                                            |
|       if (EAPOL[06h] AND 07h)=1 then call MD5HMAC(src,srclen, key,keylen, dst)      |
|       if (EAPOL[06h] AND 07h)=2 then call SHA1HMAC(src,srclen, key,keylen, dst)     |
|       newmic = dst[0..0Fh]      ;16-byte MD5 result, or first 16byte of SHA1 result |
|       EAPOL[51h..60h] = newmic                                                      |
|       if newmic <> oldmic then error  ;when verifying MIC                           |
+-------------------------------------------------------------------------------------+
```


### PMKID (whatever ID, optional/useless, don\'t care)

```
+-----------------------------------------------------------------------+
|       key=PMK, keylen=32                                              |
|       src[0..7]   = "PMK Name"                                        |
|       src[8..13]  = AA   ;aka MAC address of access point (BSSID)     |
|       src[14..19] = SPA  ;aka MAC address of console                  |
|       srclen = 8+6+6 = 20                                             |
|       call SHA1HMAC(src,srclen, key,keylen, dst)                      |
|       PMKID = dst[0..0Fh]   ;first 16byte of SHA1 result              |
+-----------------------------------------------------------------------+
```

Note: SHA1HMAC is used for WPA2. Unknown if WPA uses SHA1HMAC, or MD5HMAC, or if WPA does have PMKIDs at all.

### Deriving GTK (done internally by access point, don\'t care)

```
+-----------------------------------------------------------------------+
|       src[0..18]  = "Group key expansion"                             |
|       src[19]     = byte(00h)                                         |
|       src[20..25] = AA                 ;MAC address (AA=BSSID)        |
|       src[26..57] = GNonce             ;whaever random/timer/index    |
|       src[58]     = byte(00h)                                         |
|       srclen = 19+1+6+32+1 = 59                                       |
|       key=GMK, keylen=32, numrounds=1  ;whatever random key           |
|       dst=GTK, dstlen=32                                              |
|       call PRF(key,keylen, src,srclen, dst,dstlen, numrounds)         |
+-----------------------------------------------------------------------+
```

This is the recommended way for creating the GTK, anyways, this is done internally by the access point, and everybody else doesn\'t need to worry about how the GTK was generated (ie. one just uses the GTK received in EAPOL messages).



