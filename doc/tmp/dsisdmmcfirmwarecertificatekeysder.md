# DSi SD/MMC Firmware Certificate/Keys (DER)


### .der files (ASN.1)

```
+-------------------------------------------------------------------------------------+
|       DSi Version Data, narc:\NintendoCA-G2.der           (unencrypted)             
|       DSi Version Data, narc:\.twl-*.der                  (ES Block encrypted)      
|       DSi Browser, rom:\ca\*.ca                           (unencrypted)             
|       DSi is-twl-update, *.der (dev unit public keys)     (unencrypted, stringless) |
|       DSi Dokodemi, rom:key\pubkey.der (only 162 bytes)   (unencrypted, stringless) 
|       3DS browser applet, RomFS:\browser\rootca.pem       (ASCII BASE64 .der's)     
|       3DS System Data Archives 1, offline... cave.pem     (ASCII BASE64 .der)       |
|       3DS Shared Data Archives, Non-Nintendo TLS, *.der   (unencrypted)             |
|       3DS System Data Archives 1, ClCertA, RomFS:*.bin    (AES-CBC encrypted)       |
|       3DS Nintendo Zone, RomFS:\certs\*.der               (unencrypted)             
|       3DS Nintendo Zone, RomFS:\certs\dev.pem             (ASCII BASE64 .der)       
|       3DS Nintendo Zone, RomFS:\certs\client.key          (ASCII BASE64 .der)       
|       3DS Miiverse olv applet, RomFS:\browser\cave.pem    (ASCII BASE64 .der)       
|       3DS Miiverse olv applet, RomFS:\browser\*.p12       (nested der-inside-der?)  
+-------------------------------------------------------------------------------------+
```

For the BASE64 .pem variant, see:
- [3DS Files - BASE64 Encoding](./3dsfilesbase64encoding.md)

There are two types of .der files:
Public keys with Certificates (these do usually contain lots of entries with many OIDs and name strings for certificate, company, country, email, etc).
Private keys (these do usually contain only a few entries, often without any OIDs at all, apart from the private key, they do usually also contain the public key & original prime numbers).


```
+-------------------------------------------------------------------------------------+
|      _________________________ Tag,Length,Value Encoding __________________________ |
+-------------------------------------------------------------------------------------+
```


The files consist of several Tag-Length-Value (TLV) triplets. All data is in BIG-ENDIAN.

### Tag

```
+--------------------------------------------------------------------------------+
|       bit6-7 class  (0=Universal, 1=Application, 2=Context-defined, 3=Private) |
|       bit5   form   (0=Primitive, 1=Constructed)                               |
|       bit4-0 number (0..1Fh)                                                   |
+--------------------------------------------------------------------------------+
```

Common are:

```
+-------------------------------------------------------------------------------------+
|       BOOLEAN           UNIVERSAL  Primitive    00000001 (01h)                      |
|       INTEGER           UNIVERSAL  Primitive    00000010 (02h)                      |
|       BIT STRING        UNIVERSAL  Primitive    00000011 (03h)                      |
|       OCTET STRING      UNIVERSAL  Primitive    00000100 (04h)                      |
|       NULL              UNIVERSAL  Primitive    00000101 (05h)                      |
|       OBJECT IDENTIFIER UNIVERSAL  Primitive    00000110 (06h)                      |
|       UTF8String        UNIVERSAL  Primitive    00001100 (0Ch)                      |
|       PrintableString   UNIVERSAL  Primitive    00010011 (13h)                      |
|       TeletexString     UNIVERSAL  Primitive    00010100 (14h)                      |
|       IA5String         UNIVERSAL  Primitive    00010110 (16h)                      |
|       Time String                                        (17h)  in dsi version data |
|       BMPString         UNIVERSAL  Primitive    00011110 (1Eh)                      |
|       SEQUENCE          UNIVERSAL  Constructed  00110000 (30h)                      |
|       SEQUENCE OF       UNIVERSAL  Constructed  00110000 (30h)                      |
|       SET               UNIVERSAL  Constructed  00110001 (31h)                      |
|       SET OF            UNIVERSAL  Constructed  00110001 (31h)                      |
|       -unknown-         CONTEXT    Primitive             (80h) ;3ds miiverse .p12   |
|       -unknown-         CONTEXT    Constructed           (A0h) ;dsi version (small) |
|       -unknown-         CONTEXT    Constructed           (A3h) ;dsi browser (big)   |
+-------------------------------------------------------------------------------------+
```


### Length
The length encoding depends on bit7 of the first byte:

```
+-----------------------------------------------------------------------+
|       when bit7=0 --> bit6-0 contain length (0..127 bytes)            |
|       when bit7=1 --> bit6-0 contain number of following length bytes |
+-----------------------------------------------------------------------+
```

The length does rarely exceed 16bits, the most common lengths are:

```
+-----------------------------------------------------------------------+
|       len          = Length 0..127 bytes     (with len<80h)           |
|       81h,len      = Length 128..255 bytes   (with len>7Fh)           |
|       82h,msb,lsb  = Length 256..65535 bytes (with msb:len>00FFh)     |
+-----------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ___________________________________ Tag's ____________________________________ |
+-------------------------------------------------------------------------------------+
```


### 01h,Len,Value - BOOLEAN
Allows to define a boolean flag. Len is always 1, and value must be:

```
+-----------------------------------------------------------------------+
|       value[0] = flag (00h=False, or FFh=True)                        |
+-----------------------------------------------------------------------+
```


### 02h,Len,Value - INTEGER
Allows to define integer, including \"large\" values like RSA keys. Bit7 of the first byte is treated as sign bit, when storing unsigned values one must insert a leading 00h byte if the high bit is set.

```
+-----------------------------------------------------------------------------------+
|       value[0..(len-1)] = data   ;(len)*8 bits (with sign bit in MSB of 1st byte) |
+-----------------------------------------------------------------------------------+
```


### 03h,Len,Value - BIT STRING
Allows to define data that isn\'t a multiple of 8 bits. Or multiples of 8 bits are also working (when first byte is 00h), this sometimes used to store RSA keys as unsigned integers, or, more weirdly, it can also contain further Tag,Len,Value items (eg. SEQUENCE tags with separate RSA key and RSA exponent enclosed in the BIT string) (\... somewhat as if the BIT string contains a child .der file?).

```
+-----------------------------------------------------------------------+
|       value[0] = number of unused bits in LSB of last byte (0..7)     |
|       value[1..(len-1)] = data   ;(len-1)*8-unused bits               |
+-----------------------------------------------------------------------+
```


### 04h,Len,Value - OCTET STRING
Allows to define data that is a multiple of 8 bits. This can contain general purpose stuff, including mixup\'s of flags, integers, arrays, text strings.

```
+-----------------------------------------------------------------------+
|       value[1..(len-1)] = data   ;(len-1)*8 bits                      |
+-----------------------------------------------------------------------+
```


### 05h,Len - NULL
Allows to define empty/zero data, Len must be 00h, and accordingly, value is 0-byte tall.

### 06h,Len,Value - OBJECT IDENTIFIER (OID)
OIDs can be used as prefix for other tags (eg. to indicate that the following tag(s) contain a username or email address). The OIDs are usually expressed as a series of decimal numbers separated by dots. In binary form, these are stored as follows:

```
+-----------------------------------------------------------------------+
|       value[0] = 2nd+(1st*40)       ;\                                
|       value[1] = 3rd                ; basic encoding for 7bit values  |
|       value[2] = 4th                ;                                 |
|       etc.                          ;/                                |
+-----------------------------------------------------------------------+
```

There are some special cases: The 1st number must be 0..2. The 2nd number must be 0..39 when 1st=0..1 (there is no such limit when 1st=2).
Values bigger than 7bit are split into two or more 7bit fragments (with bit7=1 in the leading fragments, and bit7=0 in the last fragment), that variable-length encoding is used whenever \"2nd+(1st\*40)\" or \"3rd,4th,etc.\" are exceeding 7bits. For example,

```
+-----------------------------------------------------------------------+
|       1.2.3.4.255        --> 2Ah, 03h, 04h, 81h,7Fh                   |
|       2.999.1234.1.2.3.4 --> 88h,37h, 89h,52h, 01h, 02h, 03h, 04h     |
+-----------------------------------------------------------------------+
```

There are millions of OID values (assigned by thousands of organizations), the OID\'s can be deciphered with online databases, for example,

```
+-----------------------------------------------------------------------+
|       http://oidref.com/                                              |
+-----------------------------------------------------------------------+
```

However, DER certificates are usually containing only a few standard OID values. See the \"OID Values\" list below for the OID\'s found in DSi/3DS certificates.

### 0Ch,Len,Value - UTF8 String (Unicode byte & multibyte chars)
### 13h,Len,Value - Printable String (some ASCII A-Z,a-z,0-9,space,\'()+,-./:=?)
### 14h,Len,Value - T61 Teletext String (ITU T.61) (extended 8bit ASCII)
### 16h,Len,Value - IA5 String (aka ISO 646, full 7bit ASCII with @&{}\[\] etc.)
### 17h,Len,Value - Time String (numeric chars \"0-9\" and timezone suffix)
### 1Eh,Len,Value - BMP String (aka UTF-16 Unicode) (two-byte chars)
Allows to define things like company/address/country strings, using various extended or restriceted variants of the ASCII character set. The most common type is Printable String (Tag=13h) for basic english, or IA5 String(Tag=16h) for email addresses with \"@\" characters.

```
+-----------------------------------------------------------------------+
|       value[0..(len-1)] = text string                                 |
+-----------------------------------------------------------------------+
```

The Time String (Tag=17h) can contain UTC (GMT) time in different variants (without seconds, with seconds, or with seconds+century; and optional seconds fraction; terminated by a \"Z\" character, or by +/-HHMM timezone info):

```
+---------------------------------------------------------------------------------+
|       "YYMMDDHHMMZ"           ;\                                                
|       "YYMMDDHHMM+HHMM"       ; UTC Time without seconds, and optional timezone |
|       "YYMMDDHHMM-HHMM"       ;/                                                |
|       "YYMMDDHHMMSSZ"         ;\                                                
|       "YYMMDDHHMMSS+HHMM"     ; UTC Time with seconds, and optional timezone    |
|       "YYMMDDHHMMSS-HHMM"     ;/                                                |
|       "YYYYMMDDHHMMSSZ"       ;\Generalized Time with seconds and century, and  
|       "YYYYMMDDHHMMSS.SSSSZ"  ;/optional seconds fraction (no trailing zeroes)  |
+---------------------------------------------------------------------------------+
```


### 30h,Len,Value - Sequence (or Sequence of)
### 31h,Len,Value - Set (or Set of)
### A0h,Len,Value - Undoc_A0h
### A3h,Len,Value - Undoc_A3h

```
+-----------------------------------------------------------------------+
|       value[0..(len-1)] = contains further Tag,Length,Data values     |
+-----------------------------------------------------------------------+
```

XXX


```
+-------------------------------------------------------------------------------------+
|      _________________________________ OID Values _________________________________ |
+-------------------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|       0.9.2342.19200300.100.1.*  /itu-t/data/pss/ucl/pilot/pilotAttributeType/..    |
|       0.9.2342.19200300.100.1.1  ../userid                 ;unused                  |
|       0.9.2342.19200300.100.1.25 ../domainComponent        ;unused                  |
|       1.2.840.113533.7.65.*  /iso/member-body/us/nortelnetworks/entrust/nsn-ce/..   |
|       1.2.840.113533.7.65.0  ../0                    ;dsi browser equifax_s_ca.ca   |
|       1.2.840.113549.1.1.*   /iso/member-body/us/rsadsi/pkcs/pkcs-1/..              |
|       1.2.840.113549.1.1.1   ../rsaEncryption                                       |
|       1.2.840.113549.1.1.2   ../rsaEncryptionWithMD2       ;dsi browser rsa.ca      |
|       1.2.840.113549.1.1.3   ../rsaEncryptionWithMD4       ;unused                  |
|       1.2.840.113549.1.1.4   ../rsaEncryptionWithMD5       ;dsi browser thawte.ca   |
|       1.2.840.113549.1.1.5   ../rsaEncryptionWithSHA1                               |
|       1.2.840.113549.1.1.11  ../rsaEncryptionWithSHA256                             |
|       1.2.840.113549.1.1.12  ../rsaEncryptionWithSHA384    ;unused                  |
|       1.2.840.113549.1.1.13  ../rsaEncryptionWithSHA512    ;unused                  |
|       1.2.840.113549.1.1.14  ../rsaEncryptionWithSHA224    ;unused                  |
|       1.2.840.113549.1.7.*   /iso/member-body/us/rsadsi/pkcs/pkcs-7/..              |
|       1.2.840.113549.1.7.1   ../data   ;for nested .der?   ;3ds miiverse olv applet |
|       1.2.840.113549.1.7.6   ../encryptedData              ;"inside" pkcs-7         |
|       1.2.840.113549.1.9.*   /iso/member-body/us/rsadsi/pkcs/pkcs-9/..              |
|       1.2.840.113549.1.9.1   ../emailAddress                                        |
|       1.2.840.113549.1.9.21  ../localKeyID                 ;"inside" pkcs-7         |
|       1.2.840.113549.1.12.1.*  /iso/member-body/us/rsadsi/pkcs/pkcs-12/PbeIds/..    |
|       1.2.840.113549.1.12.1.3  ../pbeWithSHAAnd3-KeyTripleDES-CBC ;\inside pkcs-7   
|       1.2.840.113549.1.12.1.6  ../pbeWithSHAAnd40BitRC2-CBC       ;/                |
|       1.2.840.113549.1.12.10.* /iso/member-body/us/rsadsi/pkcs/pkcs-12/Version1/.   |
|       1.2.840.113549.1.12.10.1.2 ../BagIds/ShroudedKeyBag         ;-inside pkcs-7   |
|       1.3.6.1.4.1.311.*      /iso/org/dod/internet/prv/enterprise/microsoft/..      |
|       1.3.6.1.4.1.311.20.2   ../20/2/?  ;incomplete blurp? ;3ds browser securetrust |
|       1.3.6.1.4.1.311.21.1   ../21.1    ;unknown blurp?    ;3ds browser securetrust |
|       1.3.6.1.5.5.7.1.*      /iso/org/dod/internet/security/mechanisms/pkix/pe/..   |
|       1.3.6.1.5.5.7.1.12     ../id-pe-logotype     ;3ds shared data TLS, CA_8.der   |
|       1.3.14.3.2.*           /iso/org/oiw/secsig/algorithms/..                      |
|       1.3.14.3.2.26          ../hashAlgorithmIdentifier    ;3ds miiverse olv applet |
|       2.5.4.*                /joint/ds/attributeType/..                             |
|       2.5.4.3                ../commonName                                          |
|       2.5.4.4                ../surname                                             |
|       2.5.4.5                ../serialNumber                                        |
|       2.5.4.6                ../countryName                                         |
|       2.5.4.7                ../localityName                                        |
|       2.5.4.8                ../stateOrProvinceName                                 |
|       2.5.4.9                ../streetAddress                                       |
|       2.5.4.10               ../organizationName                                    |
|       2.5.4.11               ../organizationalUnit                                  |
|       2.5.4.12               ../title                                               |
|       2.5.4.42               ../givenName                                           |
|       2.5.29.*               /joint/ds/certificateExtension/..                      |
|       2.5.29.14              ../subjectKeyIdentifier                                |
|       2.5.29.15              ../keyUsage                                            |
|       2.5.29.16              ../privateKeyUsagePeriod  ;dsi browser equifax_s_ca.ca |
|       2.5.29.17              ../subjectAltName             ;3ds browser japnese gov |
|       2.5.29.18              ../issuerAltName              ;unused                  |
|       2.5.29.19              ../basicConstraints                                    |
|       2.5.29.20              ../cRLNumber                  ;unused                  |
|       2.5.29.21              ../reasonCode                 ;unused                  |
|       2.5.29.22              ../expirationDate             ;unused                  |
|       2.5.29.23              ../instructionCode            ;unused                  |
|       2.5.29.24              ../invalidityDate             ;unused                  |
|       2.5.29.25              ../cRLDistributionPoints      ;unused                  |
|       2.5.29.26              ../issuingDistributionPoint   ;unused                  |
|       2.5.29.27              ../deltaCRLIndicator          ;unused                  |
|       2.5.29.28              ../issuingDistributionPoint   ;unused                  |
|       2.5.29.29              ../certificateIssuer          ;unused                  |
|       2.5.29.30              ../nameConstraints            ;unused                  |
|       2.5.29.31              ../cRLDistributionPoints                               |
|       2.5.29.32              ../certificatePolicies        ;dsi browser swiss_g2.ca |
|       2.5.29.33              ../policyMappings             ;unused                  |
|       2.5.29.34              ../policyConstraints          ;unused                  |
|       2.5.29.35              ../authorityKeyIdentifier                              |
|       2.5.29.36              ../policyConstraints          ;unused                  |
|       2.5.29.37              ../extKeyUsage                ;3ds browser usertrust   |
|       2.16.840.1.113730.1.*  /joint/country/us/organization/netscape/cert-ext/..    |
|       2.16.840.1.113730.1.1  ../cert-type               ;dsi browser tc_c2_ca.ca    |
|       2.16.840.1.113730.1.8  ../ca-policy-url           ;dsi browser tc_c2_ca.ca    |
|       2.16.840.1.113730.1.13 ../comment                                             |
+-------------------------------------------------------------------------------------+
```




