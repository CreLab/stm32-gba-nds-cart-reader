# 3DS Files - Client Cert/Key (ClCertA)


ClCertA (title id: 0004001b00010002) contains the following encrypted files:

```
+-----------------------------------------------------------------------+
|       RomFS:ctr-common-1-cert.bin   ;default SSL client cert          |
|       RomFS:ctr-common-1-key.bin    ;default SSL client private key   |
+-----------------------------------------------------------------------+
```

The .bin files are AES-CBC encrypted using keyslot 0Dh (as set by bootrom): 000h 10h IV value for AES-CBC ;-IV value for decrypt

```
+---------------------------------------------------------------------------------+
|       010h LEN  DER file (LEN=filesize-20h-PAD)             ;\                  
|       xxxh PAD  Padding to 10h-byte boundary (zerofilled)   ; AES-CBC encrypted |
|       xx0h 1    Size of above padding (PAD)                 ; (keyslot 0Dh)     |
|       xx1h 0Fh  Padding to 10h-byte boundary (zerofilled)   ;/                  |
+---------------------------------------------------------------------------------+
```

The decrypted files are in .der format:
- [DSi SD/MMC Firmware Certificate/Keys (DER)](./dsisdmmcfirmwarecertificatekeysder.md)
The files are used by SSL module, the retail cert name is \"CTR Common Prod 1\".

The following servers require usage of ClCertA to connect:

```
+-----------------------------------------------------------------------------------+
|       https://account.nintendo.net/          ;Account/OAuth2 related              |
|       https://ccif.ctr.shop.nintendo.net/    ;CreditCardInfo/transaction? related |
|       https://ecs.c.shop.nintendowifi.net/   ;ECommerce SOAP, ticket-related      |
|       https://cas.c.shop.nintendowifi.net/   ;Cataloging SOAP                     |
|       https://ninja.ctr.shop.nintendo.net/   ;eShop-related                       |
|       https://nus.c.shop.nintendowifi.net/   ;NetUpdate SOAP, used by NIM module  |
+-----------------------------------------------------------------------------------+
```




