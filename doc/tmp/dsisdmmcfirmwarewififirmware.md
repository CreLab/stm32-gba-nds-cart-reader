# DSi SD/MMC Firmware Wifi Firmware


### FAT16:\\title\\0003000f\\484e4341\\content\\000000vv.app (aka Wifi Firmware)
WLFIRM aka WLANFIRM (compressed, non-executable datafile, for all regions, v0:13B80h bytes, v1:13BA0h bytes, v2:17E60h bytes). This file contains Wifi Firmwares for the Xtensa CPU in the Atheros AR60xxG chips on the DWM-W0xx Wifi Daughterboards.

```
+-----------------------------------------------------------------------------------+
|       DSi Firmware 1.0            --> Wifi Firmware v0 (supports AR6002)          |
|       DSi Firmware 1.1 thru 1.2   --> Unknown (presumably v0 or v1)               |
|       DSi Firmware 1.3            --> Wifi Firmware v1 (supports AR6002)          |
|       DSi Firmware 1.4 thru 1.4.5 --> Wifi Firmware v2 (supports AR6002+AR6013)   |
|       Note: The AR6002 part is exact same in v1 and v2 (with same SHA1 in Part 1) |
|       However, part 1.c was slightly smaller in v0, apparently some small bugfix. |
+-----------------------------------------------------------------------------------+
```

The BIOS ROM in the AR60xxG chips can be extended/upgraded by uploading the firmware into RAM (the RAM isn\'t nonvolatile, so this must be done each time after power-up, that is done by the System Menu (launcher), so DSi games won\'t need to upload the firmware themselves.

```
+-------------------------------------------------------------------------------------+
|       00000h 80h    RSA-SHA1    (on [00080h..0009Fh]) (via RSA key from BIOS) ;\    
|       00080h 14h    Header SHA1 (on [000A0h..000FFh])                         ; SHA |
|       00094h 4      Header Size (00000060h, for entries 000A0h..000FFh)       ;     |
|       00098h 8      Zerofilled                                                ;/    |
|       000A0h 2      Version (0000h,0001h,0002h for v0,v1,v2)          ;\            
|       000A2h 1      Number of parts (01h..02h)   ;(02h in v2 only)    ; Header      |
|       000A3h 1      Unknown/zero?    (00h)                            ;             |
|       000A4h 4      Part 1 Start (00000100h) ;(in v1: E0h)  ;\Part 1  ; with IDs    
|       000A8h 4      Part 1 Size  (00013AC0h)                ; DWM-W015; as in wifi  |
|       000ACh 4      Part 1 ID    (00000001h) (=DWM-W015)    ; AR6002G ; flash[1FDh] |
|       000B0h 14h    Part 1 SHA1  (on [00100h..13BBFh])      ;/        ;             |
|       000C4h 4      Part 2 Start (00013BC0h)                ;\Part 2  ; ;\          
|       000C8h 4      Part 2 Size  (000042A0h)                ; DWM-W024; ; not in    |
|       000CCh 4      Part 2 ID    (00000002h) (=DWM-W024)    ; AR6013G ; ; version 1 |
|       000D0h 14h    Part 2 SHA1  (on [13BC0h..17E5Fh])      ;/        ; ;/          |
|       000E4h 1Ch    Zerofilled (padding to 20h-byte boundary)         ;/            |
|       00100h 1      Part 1 num subheader's    (04h) (a/b/c/d)                    ;\ 
|       00101h 1      Part 1 num ChipID's       (02h)                              ;  |
|       00102h 2      Part 1 offset to ChipID's (0044h)                            ;  |
|       00104h 10h    Part 1.a firm/main (00000080h,00013458h,80000001h,00502400h) ;  |
|       00114h 10h    Part 1.b database  (000134E0h,000002BCh,00000002h,0052D944h) ;  |
|       00124h 10h    Part 1.c stub/code (000137A0h,000002DEh,00000004h,00515000h) ;  |
|       00134h 10h    Part 1.d stub/data (00013A80h,00000030h,00000005h,00502400h) ;  |
|       00144h 8      Part 1 ChipID 1 ;alternate IDs ?       (02010001h,20000188h) ;  |
|       0014Ch 8      Part 1 ChipID 2 ;CHIP_ID, ROM_VERSION  (02000001h,20000188h) ;  |
|       00154h 4      Part 1 Firmware Version: 2.1.0.123               (2100007Bh) ;  |
|       00158h 0Ch    Part 1 RAM vars/base/size    (00500400h,00500000h,0002E000h) ;  |
|       00164h 1Ch    Zerofilled                                                   ;  |
|       00180h 13460h Part 1.a data (13458h compressed bytes, +8 bytes zeropadding);  |
|       135E0h 2C0h   Part 1.b data (2BCh bytes, +04h bytes zeropadding) ;database ;  |
|       138A0h 2E0h   Part 1.c data (2DEh bytes, +02h bytes zeropadding) ;stubcode ;  |
|       13B80h 40h    Part 1.d data (30h bytes, +10h bytes zeropadding)  ;stubdata ;/ |
|       13BC0h 1      Part 2 num subheader's    (04h)                              ;\ 
|       13BC1h 1      Part 2 num ChipID's       (02h)                              ;  |
|       13BC2h 2      Part 2 offset to ChipID's (0044h)                            ;  |
|       13BC4h 10h    Part 2.a firm/main (00000080h,00002EECh,80000001h,00524C00h) ;  |
|       13BD4h 10h    Part 2.b database  (00002F80h,00000FC0h,00000002h,0053F040h) ;  |
|       13BE4h 10h    Part 2.c stub/code (00003F40h,00000312h,00000004h,00527000h) ;  |
|       13BF4h 10h    Part 2.d stub/data (00004260h,00000038h,00000005h,00524C00h) ;  |
|       13C04h 8      Part 2 ChipID 1 ;CHIP_ID, ROM_VERSION  (0D000000h,23000024h) ;  |
|       13C0Ch 8      Part 2 ChipID 2 ;alternate IDs?        (0D000001h,23000024h) ;  |
|       13C14h 4      Part 2 Firmware Version: 2.3.0.108               (2300006Ch) ;  |
|       13C18h 0Ch    Part 2 RAM vars/base/size    (00520000h,00520000h,00020000h) ;  |
|       13C24h 1Ch    Zerofilled                                                   ;  |
|       13C40h 2F00h  Part 2.a data (2EECh compressed bytes,+14h bytes zeropadding);  |
|       16B40h FC0h   Part 2.b data (FC0h bytes, +00h bytes zeropadding)           ;  |
|       17B00h 320h   Part 2.c data (312h bytes, +0Eh bytes zeropadding)           ;  |
|       17E20h 40h    Part 2.d data (38h bytes, +08h bytes zeropadding)            ;/ |
+-------------------------------------------------------------------------------------+
```

The a/b/c/d subheaders consist of File Source Offset (relative to Start of Part 1/2 accordingly), Length, ID/Flags, and RAM Destination Address.
The stub/code and stub/data parts are loaded and executed first (the stub is reading calibration data from I2C bus EEPROM; this is decoupled from the main firmware because hardware implementations could use different calibration sources like I2C chips or SPI chips or mass-storage devices).
Thereafter, firm/main and database are loaded and executed. The \"LZ\" compressed firm/main part is automatically decompressed on the Xtensa side, the \"LZ\" stuff is some kind of \"tag,len,disp\" format:

```
+-----------------------------------------------------------------------+
|       Part 1.a data: 9F,FF,FF,FF,FF,FF,FF,00,00,00,00,9F,04,04,..     |
|       Part 2.a data: 5E,00,00,00,00,5E,04,04,5E,08,08,41,5F,49,..     |
+-----------------------------------------------------------------------+
```

The first byte identifies the \"tag\" value (this should be the value used least often in the uncompressed data). The following bytes are plain uncompressed data, mixed with \"tag,len,disp\" values (which will copy \"len\" bytes from \"dest-disp\" to \"dest\"). A special case is \"tag,00h\", which will store the \"tag\" value at dest. The len and disp values can consist of one or more byte(s) each (the LSB aka last byte is indicated by bit7=0; for example, \"84h,86h,0Fh\" would mean 01030Fh). For some odd reason, the values are always \"len\<=disp\" (even for zerofilled regions where \"len\>disp\" would be useful).



