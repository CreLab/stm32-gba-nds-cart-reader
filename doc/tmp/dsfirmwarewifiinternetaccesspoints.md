# DS Firmware Wifi Internet Access Points


### Connection data 1 at WifiFlash\[00020h\]\*8-400h (eg. 01FA00h/03FA00h/07FA00h)
### Connection data 2 at WifiFlash\[00020h\]\*8-300h (eg. 01FB00h/03FB00h/07FB00h)
### Connection data 3 at WifiFlash\[00020h\]\*8-200h (eg. 01FC00h/03FC00h/07FC00h)
These three 100h byte regions are used to memorize known internet access points. The NDS firmware doesn\'t use these regions, but games that support internet are allowed to read (and configure/write) them. The DSi firmware also supports configuring these entries.

```
+-------------------------------------------------------------------------------------+
|       Addr Siz Expl.                                                                |
|       000h 64  Unknown (usually 00h-filled) (no Proxy supported on NDS)             |
|       040h 32  SSID (ASCII name of the access point) (padded with 00h's)            |
|       060h 32  SSID for WEP64 on AOSS router (each security level has its own SSID) |
|       080h 16  WEP Key 1 (for type/size, see entry E6h)                             |
|       090h 16  WEP Key 2  ;\                                                        
|       0A0h 16  WEP Key 3  ; (usually 00h-filled)                                    |
|       0B0h 16  WEP Key 4  ;/                                                        |
|       0C0h 4   IP Address           (0=Auto/DHCP)                                   |
|       0C4h 4   Gateway              (0=Auto/DHCP)                                   |
|       0C8h 4   Primary DNS Server   (0=Auto/DHCP)                                   |
|       0CCh 4   Secondary DNS Server (0=Auto/DHCP)                                   |
|       0D0h 1   Subnet Mask (0=Auto/DHCP, 1..1Ch=Leading Ones) (eg. 6 = FC.00.00.00) |
|       0D1h ..  Unknown (usually 00h-filled)                                         |
|       0E6h 1   WEP Mode (0=None, 1/2/3=5/13/16 byte hex, 5/6/7=5/13/16 byte ascii)  |
|       0E7h 1   Status (00h=Normal, 01h=AOSS, FFh=connection not configured/deleted) |
|       0E8h 1   Zero (not SSID Length, ie. unlike as entry 4,5,6 on DSi)             |
|       0E9h 1   Unknown (usually 00h)                                                |
|       0EAh 2   DSi only: MTU (Max transmission unit) (576..1500, usually 1400)      |
|       0ECh 3   Unknown (usually 00h-filled)                                         |
|       0EFh 1   bit0/1/2 - connection 1/2/3 (1=Configured, 0=Not configured)         |
|       0F0h 6   Nintendo Wifi Connection (WFC) 43bit User ID                         |
|                (ID=([F0h] AND 07FFFFFFFFFFh)*1000, shown as decimal string          |
|                NNNN-NNNN-NNNN-N000) (the upper 5bit of the last byte are            |
|                containing additional/unknown nonzero data)                          |
|       0F6h 8   Unknown (nonzero stuff !?!)                                          |
|       0FEh 2   CRC16 for Entries 000h..0FDh (with initial value 0000h)              |
+-------------------------------------------------------------------------------------+
```

For connection 3: entries \[0EFh..0FDh\] - always zero-filled?
The location of the first data block is at the User Settings address minus 400h, ie. Firmware Header \[00020h\]\*8-400h.

### Connection data 4 at WifiFlash\[00020h\]\*8-A00h (eg. 01F400h) (DSi only)
### Connection data 5 at WifiFlash\[00020h\]\*8-800h (eg. 01F600h) (DSi only)
### Connection data 6 at WifiFlash\[00020h\]\*8-600h (eg. 01F800h) (DSi only)
The DSi has three extra 200h-byte regions (for use DSi games, with the new WPA/WPA2 encryption support, and with additional proxy support), these extra regions are found under \"Advanced Setup\" in the DSi firmware\'s \"Internet\" configuration menu.

```
+-------------------------------------------------------------------------------------+
|       Addr Siz Expl.                                                                |
|       000h 32  Proxy Authentication Username (ASCII string, padded with 00's)       |
|       000h 32  Proxy Authentication Password (ASCII string, padded with 00's)       |
|       040h 32  SSID (ASCII string, padded with 00's) (see [0E8h] for length)        |
|       060h ..  Maybe same as NDS                                                    |
|       080h 16  WEP Key (zerofilled for WPA)                                         |
|       0xxh ..  Maybe same as NDS                                                    |
|       0C0h 4   IP Address           (0=Auto/DHCP)                                   |
|       0C4h 4   Gateway              (0=Auto/DHCP)                                   |
|       0C8h 4   Primary DNS Server   (0=Auto/DHCP)                                   |
|       0CCh 4   Secondary DNS Server (0=Auto/DHCP)                                   |
|       0D0h 1   Subnet Mask (0=Auto/DHCP, 1..1Ch=Leading Ones) (eg. 6 = FC.00.00.00) |
|       0D1h ..  Unknown (zerofilled)                                                 |
|       0E6h 1   WEP (00h=None/WPA/WPA2, 01h/02h/03h/05h/06h/07h=WEP, same as NDS)    |
|       0E7h 1   WPA (00h=Normal, 10h=WPA/WPA2, 13h=WPS+WPA/WPA2, FFh=unused/deleted) |
|       0E8h 1   SSID Length in characters (01h..20h, or 00h=unused)                  |
|       0E9h 1   Unknown (usually 00h)                                                |
|       0EAh 2   MTU Value (Max transmission unit) (576..1500, usually 1400)          |
|       0ECh 3   Unknown (usually 00h-filled)                                         |
|       0EFh 1   bit0/1/2 - connection 4/5/6 (1=Configured, 0=Not configured)         |
|       0F0h 14  Zerofilled (or maybe ID as on NDS, if any such ID exists for DSi?)   |
|       0FEh 2   CRC16 for Entries 000h..0FDh (with initial value 0000h)              |
|       100h 32  Precomputed PSK (based on WPA/WPA2 password and SSID) ;\all zero     
|       120h 64  WPA/WPA2 password (ASCII string, padded with 00's)    ;/for WEP      |
|       160h 33  Zerofilled                                                           |
|       181h 1   WPA (0=None/WEP, 4=WPA-TKIP, 5=WPA2-TKIP, 6=WPA-AES, 7=WPA2-AES)     |
|       182h 1   Proxy Enable         (00h=None, 01h=Yes)                             |
|       183h 1   Proxy Authentication (00h=None, 01h=Yes)                             |
|       184h 48  Proxy Name (ASCII string, max 47 chars, padded with 00's)            |
|       1B4h 52  Zerofilled                                                           |
|       1E8h 2   Proxy Port (16bit)                                                   |
|       1EAh 20  Zerofilled                                                           |
|       1FEh 2   CRC16 for Entries 100h..1FDh (with initial value 0000h) (0=deleted)  |
+-------------------------------------------------------------------------------------+
```

The location of the first data block (aka settings number 4) is at the User Settings address minus A00h, ie. Firmware Header \[00020h\]\*8-A00h.
Observe that NDS consoles do have NDS Firmware bootcode/data in that area, so those new regions can exist on DSi only (or on homebrew NDS firmwares). Presence of the new regions is indicated in Firmware Header \[001FEh\], that byte is usually FFh=NDS or 20h=DSi, the DSi browser does internally replace FFh by 10h, and does then check if byte\>=20h (ie. the new areas exist if the byte is 20h..FEh).
Note that the Proxy feature can be used to redirect internet access (when using a custom proxy server, one could redirect commercial games to homebrew servers; as done by the <http://pbsds.net/> project) (actually the same should be possible with the DNS server entry, possibly with less traffic).

### Note
The location of the user settings & connection data varies (eg. 01Fxxxh=DSi, 03Fxxxh=NDS, 07Fxxxh=iQueDS).

### Nintendo Zone Beacons
DSi games and DSi browser can reportedly also connect to Nintendo\'s public access points (those that are announced via Nintendo Zone Beacons).

### Hidden Connection data at WifiFlash\[00020h\]\*8-100h (eg. xxFD00h)
This seems to hold an extra 100h-byte region (same as Connection data 1-3), some (or all) NDS/DSi games seem to be capable of using it (although it isn\'t shown in config menues). One theory is that it might be used for the Nintendo Wi-Fi USB Connector?



