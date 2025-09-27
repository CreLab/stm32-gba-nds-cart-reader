# DS Wifi WPA/WPA2 Handshake Messages (EAPOL)


### 4-Way Handshake and Group Key Handshake messages
For WPA, the Group Key Handshake occurs immediately after the 4-way Handshake (effecitively making it a 6-way handshake). For WPA2, the Group Key is contained in the 4-way Handshake, so the Group Key Handshake isn\'t needed.
For both WPA and WPA2, the access point may change the Group Key every once and then, and invoke a new Group Key Handshake for the new key.

### EAPOL Key Frame
This is preceeded by a LLC/SNAP header (AAh,AAh,03h,00h,00h,00h,88h,8Eh), the 888Eh in last two bytes indicates that following bytes to contain an EAPOL Key Frame:

```
+-----------------------------------------------------------------------------------+
|       00h  2    Version/Type (or Type/Version?) (01 03)                           |
|       02h  2    Length of [04h..end] (005Fh+LEN)                      ;BIG-ENDIAN |
|       04h  1    Descriptor Type (FEh=WPA, 02h=WPA2)                               |
|       05h  2    Key Information (flags, see below)                    ;BIG-ENDIAN |
|       07h  2    Key Length (0=None, 20h=TKIP, 10h=CCMP, 05h/0Dh=WEP)  ;BIG-ENDIAN |
|       09h  8    Key Replay Counter (usually 0 or 1 in first message)  ;BIG-ENDIAN |
|       11h  32   Key Nonce (ANonce/SNonce)                                         |
|       31h  16   Key Data IV (RC4 uses IV+KEK) (not used for AES-Key-Wrap)         |
|       41h  8    Key RSC (TSC/PN) (whatever, for GTK)               ;LITTLE-ENDIAN |
|       49h  8    Reserved (zerofilled)                                             |
|       51h  16   Key MIC on [00h..end] (with MIC initially zerofilled)       ;HMAC |
|       61h  2    Key Data Length (LEN) (00 nn)                         ;BIG-ENDIAN |
|       63h  LEN  Key Data (can be encrypted in certain messages)                   |
+-----------------------------------------------------------------------------------+
```


### Key Information flags

```
+------------------------------------------------------------------------------------+
|       0-2   Key Descriptor Version (1=WPA/MD5/RC4, 2=WPA2/SHA1/AESkeywrap)         |
|       3     Key Type (0=Group, 1=Pairwise)                                         |
|       4-5   Reserved (0) or WPA Group Key Index (1 or 2) (zero for WPA2)           |
|       6     Install  (0=No, 1=Yes, configure temporal key)                         |
|       7     Key Ack  (0=No, 1=Yes, AP wants a reply; with same Key Replay Counter) |
|       8     Key MIC  (0=No, 1=Yes, key frame contains MIC)                         |
|       9     Secure   (0=No, 1=Yes, initial key-exchange complete)                  |
|       10    Error    (0=No, 1=Yes, MIC failure and Request=1)                      |
|       11    Request  (0=No, 1=Yes, request AP to invoke a new handshake)           |
|       12    Encrypted(0=No, 1=Yes, Key Data is encrypted; via RC4 or AESkeywrap)   |
|       13-15 Reserved (0)                                                           |
+------------------------------------------------------------------------------------+
```


### Key Data
Key Data does usually consist of element(s) in following form:

```
+------------------------------------------------------------------------------+
|       00h 1   Element ID (for WPA: DDh=RSNIE - for WPA2: 30h=RSNIE, DDh=KDE) |
|       01h 1   Element Length of [02h..end]                                   |
|       02h ..  Element Data (OUI's etc.)                                      |
+------------------------------------------------------------------------------+
```

WPA and WPA2 assign different meanings to Element ID value DDh. The 3-byte maker prefix in OUI values does also differ for WPA/WPA2. And, the meaning of the OUI\'s varies depending on WHERE they are used (eg. 00-0F-AC-02 could be a Cipher Suite entry, or an Authentication entry):

```
+-------------------------------------------------------------------------------------+
|       EAPOL Descriptor Type values                                                  |
|       WPA          WPA2         Meaning                                             |
|       FEh          02h          Indicates if ElementIDs and OUIs are WPA or WPA2    |
|       EAPOL Key Information flags/values                                            |
|       0089h        008Ah        Handshake #1  ;\                                    
|       0109h        010Ah        Handshake #2  ; 4-way Handshake                     |
|       01C9h        13CAh        Handshake #3  ;                                     |
|       0109h(again) 030Ah        Handshake #4  ;/                                    |
|       0391h/03A1h  1382h        Handshake #5  ;\Group Key Handshake                 
|       0311h/0321h  0302h        Handshake #6  ;/                                    |
|       EAPOL Key Data Element IDs                                                    |
|       DDh          30h          Element ID for RSNIE (Robust Network Security info) |
|       -            DDh          Element ID for KDE (Key Data Encapsulation)         |
|       -            DDh          Element ID for padding (followed by 00h-bytes)      |
|       RSNIE Prefix OUI's (WPA only):                                                |
|       00-50-F2-01  -            Element Vendor OUI for RSNIE                        |
|       RSNIE Group Cipher suite selector OUI's (aka Multicast):                      |
|       00-50-F2-01  00-0F-AC-01  RSNIE Group Cipher WEP-40  (default for US/NSA)     |
|       00-50-F2-02  00-0F-AC-02  RSNIE Group Cipher TKIP    (default for WPA)        |
|       00-50-F2-04  00-0F-AC-04  RSNIE Group Cipher CCMP    (default for WPA2)       |
|       00-50-F2-05  00-0F-AC-05  RSNIE Group Cipher WEP-104 (default for WEP)        |
|       RSNIE Pairwise Cipher suite selector OUI's (aka Unicast):                     |
|       00-50-F2-00  00-0F-AC-00  RSNIE Pairwise Cipher None (WEP, Group Cipher only) |
|       00-50-F2-02  00-0F-AC-02  RSNIE Pairwise Cipher TKIP (default for WPA)        |
|       00-50-F2-04  00-0F-AC-04  RSNIE Pairwise Cipher CCMP (default for WPA2)       |
|       RSNIE Authentication AKM suite selector OUI's :                               |
|       00-50-F2-01  00-0F-AC-01  RSNIE Authentication over IEEE 802.1X (radius?)     |
|       00-50-F2-02  00-0F-AC-02  RSNIE Authentication over PSK (default/home use)    |
|       KDE Key Data Encapsulation OUI's (WPA2 only):                                 |
|       -            00-0F-AC-01  KDE GTK         (followed by 2+N bytes)             |
|       -            00-0F-AC-02  KDE STAKey      (followed by 2+6+N bytes)           |
|       -            00-0F-AC-03  KDE MAC address (followed by 6 bytes)               |
|       -            00-0F-AC-04  KDE PMKID       (followed by 16 bytes)              |
+-------------------------------------------------------------------------------------+
```


### RSNIE (Robust Network Security Information Element)
RSNIE allows to exchange information about the desired/supported encryption methods. RSNIE is found in handshake message 2/3 (and also in Beacons). In most cases one could just ignore the RSNIE stuff (eg. if Wifi FLASH is already configured to use a specific cipher type). A special case might be networks that use a weaker Group Cipher (for older devices) combined with offering stronger Pairwise Ciphers (for devices that support them).

```
+------------------------------------------------------------------------------------+
|       WPA2 RSNIE (Robust Network Security Information Element):                    |
|       00h  1  Element ID (30h=RSNIE for WPA2)                                      |
|       01h  1  Element Len of [02h..end] (usually 14h)                              |
|       02h  2  RSNIE Version 1                        (01 00)     ;WHATEVER-ENDIAN? |
|       04h  4  RSNIE Group Cipher Suite OUI (CCMP)    (00 0F AC 04)                 |
|       08h  2  RSNIE Pairwise Cipher Suite Count (1)  (01 00)      ;LITTLE-ENDIAN   |
|       0Ah  4  RSNIE Pairwise Cipher Suite OUI (CCMP) (00 0F AC 04)                 |
|       0Eh  2  RSNIE Authentication Count (1)         (01 00)      ;LITTLE-ENDIAN   |
|       10h  4  RSNIE Authentication OUI (PSK)         (00 0F AC 02)                 |
|       14h  2  RSNIE Capabilities                     (00 00)      ;LITTLE-ENDIAN?  |
|       16h (2) RSNIE Optional PMKID Count  ;\usually none such     ;LITTLE-ENDIAN   
|       18h (16)RSNIE Optional PMKID's      ;/                                       |
|       WPA RSNIE (Robust Network Security Information Element):                     |
|       00h  1  Element ID (DDh=Vendor/RSNIE for WPA)                                |
|       01h  1  Element Len of [02h..end] (usually 16h or 18h)                       |
|       02h  4  Element Vendor OUI for RSNIE  (00 50 F2 01)       ;<-- WPA only      |
|       06h  2  RSNIE Version value? (1)      (01 00)              ;WHATEVER-ENDIAN? |
|       08h  4  RSNIE Mcast OUI (TKIP)        (00 50 F2 02)                          |
|       0Ch  2  RSNIE Ucast Count (1)         (01 00)               ;LITTLE-ENDIAN   |
|       0Eh  4  RSNIE Ucast OUI (TKIP)        (00 50 F2 02)                          |
|       12h  2  RSNIE Auth AKM Count (1)      (01 00)               ;LITTLE-ENDIAN   |
|       14h  4  RSNIE Auth AKM OUI (PSK)      (00 50 F2 02)                          |
|       18h (2) RSNIE Capabilities maybe?     (00 00)               ;LITTLE-ENDIAN?  |
|       RSN Capabilities flags (usually 0000h) (also spotted: 0C 00):                |
|       0   RSN Pre-Auth capabilities                                                |
|       1   RSN No Pairwise capabilities                                             |
|       2-3 RSN PTKSA Replay Counters (0..3 = 1,2,4,16 replay counters)              |
|       4-5 RSN GTKSA Replay Counters (0..3 = 1,2,4,16 replay counters)              |
|       6   Managment Frame Protection Required                                      |
|       7   Managment Frame Protection Capable                                       |
|       8   Joint Multi-band RSNA                                                    |
|       9   PeerKey Enabled                                                          |
|       10  SPP A-MSDU Capable                                                       |
|       11  SPP A-MSDU Required                                                      |
|       12  PBAC                                                                     |
|       13  Ext Key ID for Unicast                                                   |
|       14-15 Reserved (0)                                                           |
+------------------------------------------------------------------------------------+
```


### KDE Key Data Encapsulation (or raw data for WPA)
KDE (or WPA\'s raw data) is mainly useful for transferring the GTK group key. Note that Key Data in WPA2 message 3 contains both RSNIE and KDE GTK (and KDE padding). Whilst the raw data in WPA cannot be mixed RSNIE.

```
+------------------------------------------------------------------------------------+
|       WPA2 KDE GTK (Key Data Encapsulation for Group Key, in encrypted Key Data):  |
|       00h  1   Element ID (DDh=KDE for WPA2)                                       |
|       01h  1   Element Len (16h)                                                   |
|       02h  4   KDE OUI GTK (00-0F-AC-01) (occurs in message 3/5)                   |
|       06h  1   KDE GTK Key ID (01h or 02h)      ;bit2: Tx ?                        |
|       07h  1   KDE GTK Reserved (00h)                                              |
|       08h  16  KDE GTK Key GTK (for Key ID from above byte [06h])                  |
|       WPA2 KDE PKMID (Key Data Encapsulation for PKMID) (optional, not needed):    |
|       00h  1   Element ID (DDh=KDE for WPA2)                                       |
|       01h  1   Element Len (14h)                                                   |
|       02h  4   KDE OUI PMKID (00-0F-AC-04) (optionally occurs in message 1)        |
|       06h  16  KDE PMKID (useless checksum on PMK, sometimes exposed in message 1) |
|       WPA2 KDE Padding (for padding Key Data to Nx8 bytes for AES-Key-wrap):       |
|       00h  1   Element ID (DDh=KDE for WPA2)                                       |
|       01h  0-6 Padding (00h) (aka Element Len=00h)                                 |
|       WPA GTK (raw Group Key; without Element ID or KDE-style encapsulation):      |
|       00h  16  Key GTK (for Key ID from Key Information bit4-5) (in message 5)     |
+------------------------------------------------------------------------------------+
```




