# DS Firmware Header


### Firmware Memory Map

```
+------------------------------------------------------------------------------------+
|       00000h-00029h  Firmware Header                                               |
|       0002Ah-001FFh  Wifi Settings                                                 |
|       00200h-3F9FFh  Firmware Code/Data                       ;-NDS only (not DSi) |
|       00200h-002FEh  00h-filled                               ;\                   
|       002FFh         80h                                      ;                    |
|       00300h-1F2FFh  FFh-filled (not write-able on 4K chips)  ; DSi only (not NDS) |
|       1F300h-1F3FEh  FFh-filled (write-able)                  ;                    |
|       1F3FFh         Whatever Debug/Bootflags                 ;                    |
|       1F400h-1F5FFh  Wifi Access Point 4  ;\with WPA/WPA2     ;                    
|       1F600h-1F7FFh  Wifi Access Point 5  ; support           ;                    |
|       1F800h-1F9FFh  Wifi Access Point 6  ;/                  ;/                   |
|       3FA00h-3FAFFh  Wifi Access Point 1  ;\                                       
|       3FB00h-3FBFFh  Wifi Access Point 2  ; Open/WEP only                          |
|       3FC00h-3FCFFh  Wifi Access Point 3  ;/                                       |
|       3FD00h-3FDFFh  Not used                                                      |
|       3FE00h-3FEFFh  User Settings Area 1                                          |
|       3FF00h-3FFFFh  User Settings Area 2                                          |
+------------------------------------------------------------------------------------+
```

On iQue DS (with 512K flash memory), user settings are moved to 7FE00h and up, and, there seems to be some unknown stuff at 200h..27Fh.

### Firmware Header (00000h-001FFh)

```
+------------------------------------------------------------------------------------+
|       Addr Size Expl.                                                              |
|       000h 2    part3 romaddr/8 (arm9 gui code) (LZ/huffman compression)           |
|       002h 2    part4 romaddr/8 (arm7 wifi code) (LZ/huffman compression)          |
|       004h 2    part3/4 CRC16 arm9/7 gui/wifi code                                 |
|       006h 2    part1/2 CRC16 arm9/7 boot code                                     |
|       008h 4    firmware identifier (usually nintendo "MAC",nn) (or nocash "XBOO") |
|                 the 4th byte (nn) occassionally changes in different versions      |
|       00Ch 2    part1 arm9 boot code romaddr/2^(2+shift1) (LZSS compressed)        |
|       00Eh 2    part1 arm9 boot code 2800000h-ramaddr/2^(2+shift2)                 |
|       010h 2    part2 arm7 boot code romaddr/2^(2+shift3) (LZSS compressed)        |
|       012h 2    part2 arm7 boot code 3810000h-ramaddr/2^(2+shift4)                 |
|       014h 2    shift amounts, bit0-2=shift1, bit3-5=shift2, bit6-8=shift3,        |
|                 bit9-11=shift4, bit12-15=firmware_chipsize/128K                    |
|       016h 2    part5 data/gfx romaddr/8 (LZ/huffman compression)                  |
|       018h 8    Optional KEY1-encrypted "enPngOFF"=Cartridge KEY2 Disable          |
|                 (feature isn't used in any consoles, instead contains timestamp)   |
|       018h 5    Firmware version built timestamp (BCD minute,hour,day,month,year)  |
|       01Dh 1    Console type                                                       |
|                   FFh=Nintendo DS                                                  |
|                   20h=Nintendo DS-lite                                             |
|                   57h=Nintendo DSi (also iQueDSi)                                  |
|                   43h=iQueDS                                                       |
|                   63h=iQueDS-lite                                                  |
|                 The entry was unused (FFh) in older NDS, ie. replace FFh by 00h)   |
|                   Bit0   seems to be DSi/iQue related                              |
|                   Bit1   seems to be DSi/iQue related                              |
|                   Bit2   seems to be DSi related                                   |
|                   Bit3   zero                                                      |
|                   Bit4   seems to be DSi related                                   |
|                   Bit5   seems to be DS-Lite related                               |
|                   Bit6   indicates presence of "extended" user settings (DSi/iQue) |
|                   Bit7   zero                                                      |
|       01Eh 2    Unused (FFh-filled)                                                |
|       020h 2    User Settings Offset (div8) (usually last 200h flash bytes)        |
|       022h 2    Unknown (7EC0h or 0B51h)                                           |
|       024h 2    Unknown (7E40h or 0DB3h)                                           |
|       026h 2    part5 CRC16 data/gfx                                               |
|       028h 2    unused (FFh-filled)                                                |
|       02Ah-1FFh Wifi Calibration Data (see next chapter)                           |
+------------------------------------------------------------------------------------+
```


### DSi

```
+-----------------------------------------------------------------------------------+
|       000h 1Dh   Zerofilled (bootcode is in new eMMC chip, not on old FLASH chip) |
|       01Dh 6     Same as on DS (header: Console Type and User Settings Offset)    |
|       022h 6     Zerofilled (bootcode is in new eMMC chip, not on old FLASH chip) |
|       028h..1FCh Same as on DS (wifi calibration)                                 |
|       1FDh 1     Wifi Board (01h=DWM-W015, 02h=W024, 03h=W028)   ;\this was       
|       1FEh 1     Wifi Flash (20h=With access point 4/5/6)        ; FFh-filled     |
|       1FFh 1     Same as on DS (FFh)                             ;/on DS          |
|       200h FFh   Zerofilled                                      ;\               
|       2FFh 1     Unknown (80h)                                   ; this was       |
|       300h   1F000h FFh's (not write-able on 4K chips)           ; bootcode       |
|       1F300h FFh    FFh's (write-able) ;twl-debugger: 00h's      ; on DS          |
|       1F3FFh 1      FFh                ;twl-debugger: 40h        ;/               |
+-----------------------------------------------------------------------------------+
```

The bytes \[000h..027h\] cannot be changed on DSi because they are part of the RSA signature in DSi\'s Boot Info Block (at eMMC offset 200h..3FFh).



