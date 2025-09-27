# DSi Atheros Wifi - WMI Channel and Cipher Functions


### WMIcmd(000Eh) - WMI_GET_CHANNEL_LIST_CMD ;reply 000Eh ;aka WMI_CHANNEL_LIST
Parameters:

```
+-----------------------------------------------------------------------+
|       None                                                            |
+-----------------------------------------------------------------------+
```

WMI_GET_CHANNEL_LIST_CMD reply ;aka WMI_CHANNEL_LIST_REPLY

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT8  1    reserved1          ;whatever (zero)                  |
|       01h  A_UINT8  1    numChannels        ;number of channels in reply (N)  |
|       02h  A_UINT16 N*2  channelList[1]     ;channels in MHz                  |
|       02h+N*2       2    Zero (0000h)       ;undocumented (end of list or so) |
+-------------------------------------------------------------------------------+
```

Reply size is 1Ah bytes on DSi (2+(11\*2)+2 bytes, for 11 channels, plus ending 0000h; that ending halfward isn\'t officially mentioned to exist).

### WMIcmd(0011h) - WMI_SET_CHANNEL_PARAMS_CMD ;aka WMI_CHANNEL_PARAMS_CMD
Parameters (04h+N\*2 bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   reserved1           ;whatever (?)             |
|       01h  A_UINT8  1   scanParam           ;set if enable scan       |
|       02h  A_UINT8  1   phyMode             ;see WMI_PHY_MODE         |
|       03h  A_UINT8  1   numChannels         ;how many channels follow |
|       04h  A_UINT16 N*2 channelList[1]      ;channels in MHz          |
+-----------------------------------------------------------------------+
```

WMI_PHY_MODE values:

```
+-----------------------------------------------------------------------+
|       WMI_11A_MODE     = 01h                                          |
|       WMI_11G_MODE     = 02h                                          |
|       WMI_11AG_MODE    = 03h                                          |
|       WMI_11B_MODE     = 04h                                          |
|       WMI_11GONLY_MODE = 05h                                          |
+-----------------------------------------------------------------------+
```

#define WMI_MAX_CHANNELS = 32
Some (or all?) DSi\'s have only channel 1-11 enabled, and throw WMI_CMDERROR_EVENT when trying to set channel 12,13,14. Unknown what defines which channels are enabled (probably something in EEPROM).
The enabled channels can be obtained via WMI_GET_CHANNEL_LIST_CMD (which is probably related to the country reported in WMI_REGDOMAIN_EVENT).

### WMIevent(101Ah) - WMI_CHANNEL_CHANGE_EVENT ;\<\-- used on DSi ?
Event Data (06h bytes):

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT16  2  oldChannel;   ;\uh, old is 16bit, new is misaligned 32bit? 
|       02h  A_UINT32  4  newChannel;   ;/(DSi does really send 6 bytes)             |
+------------------------------------------------------------------------------------+
```

This event is not defined in \"AR6kSDK.build_sw.18\", however, \"101Ah\" is USED on DSi.

### WMIcmd(0016h) - WMI_ADD_CIPHER_KEY_CMD
Parameters (2Dh bytes on DSi?, but other sources claim 2Ch or 33h bytes):

```
+-----------------------------------------------------------------------------------+
|       2Ch 2Dh 33h   <---- total size (on DSi it's 2Dh, ie. middle column)         |
|       00h 00h 00h  A_UINT8  1   keyIndex ;aka WMI_MAX_KEY_INDEX ?                 |
|       01h 01h 01h  A_UINT8  1   keyType  ;aka CRYPTO_TYPE                         |
|       02h 02h 02h  A_UINT8  1   keyUsage      ;KEY_USAGE                          |
|       03h 03h 03h  A_UINT8  1   keyLength                                         |
|       04h 04h 04h  A_UINT8  8   keyRSC[8]     ;key replay sequence counter        |
|       0Ch 0Ch 0Ch  A_UINT8  32  key[WMI_MAX_KEY_LEN]    ;aka password             |
|       --  2Ch 2Ch  A_UINT8  1   key_op_ctrl   ;Additional Key Control information |
|       --  --  2Dh  A_UINT8  6   key_macaddr[ATH_MAC_LEN]                          |
+-----------------------------------------------------------------------------------+
```

KEY_USAGE values:

```
+-------------------------------------------------------------------------------------+
|       PAIRWISE_USAGE     = 00h ;<-- DSi browser uses THIS for WPA/WPA2 key 0        |
|       GROUP_USAGE        = 01h ;<-- DSi browser uses THIS for WEP/WPA/WPA2 key 1..3 |
|       TX_USAGE           = 02h ;<-- reportedly "default Tx Key - Static WEP only"   |
|       Undoc (or 01h+02h) = 03h ;<-- DSi browser uses THIS for WEP key 0             |
+-------------------------------------------------------------------------------------+
```

Bit Flag. (aka key_op_ctrl values?):

```
+------------------------------------------------------------------------------------+
|       Bit 0 - Initialise TSC - default is Initialize                               |
|       KEY_OP_INIT_TSC    = 01h                                                     |
|       KEY_OP_INIT_RSC    = 02h                                                     |
|       KEY_OP_INIT_WAPIPN = 10h (only if "WAPI_ENABLE")                             |
|       KEY_OP_INIT_VAL    = 03h  ;<-- Default Initialise the TSC & RSC ;used by DSi |
|       KEY_OP_VALID_MASK  = 03h                                                     |
+------------------------------------------------------------------------------------+
```

More constants:

```
+------------------------------------------------------------------------------------+
|       WMI_MIN_KEY_INDEX = 0                                                        |
|       WMI_MAX_KEY_INDEX = 3  ;<-- when not "WAPI_ENABLE"                           |
|       WMI_MAX_KEY_INDEX = 7  ;<-- when "WAPI_ENABLE" (wapi grpKey 0-3, prwKey 4-7) |
|       WMI_MAX_KEY_LEN   = 32                                                       |
+------------------------------------------------------------------------------------+
```

### WEP Cipher Keys
All four keys (with KeyIndex=0..3) must be set before WMI_CONNECT_CMD. The NDS/DSi user interface allows to define only one WEP key 0, but one must add dummy keys for key 1..3, else connect will fail.
### WPA/WPA2 Cipher Keys
For WPA/WPA2, WMI_CONNECT_CMD isn\'t working fully automated: After WMI_CONNECT_EVENT, one must manually receive & reply EAPOL handshake messages, and then add the cipher keys based on the message contents. The used keys are key 0 (for pairwise cipher), and key 1 or 2 (for the current group cipher key).
- [DS Wifi WPA/WPA2 Handshake Messages (EAPOL)](./dswifiwpawpa2handshakemessageseapol.md)
- [DS Wifi WPA/WPA2 Keys and MICs](./dswifiwpawpa2keysandmics.md)
- [DS Wifi WPA/WPA2 Encryption](./dswifiwpawpa2encryption.md)
- [DS Firmware Wifi Calibration Data](./dsfirmwarewificalibrationdata.md)
- [DS Firmware Wifi Internet Access Points](./dsfirmwarewifiinternetaccesspoints.md)
Moreover, the access point may throw further EAPOL messages for assigning new group keys every once and then, and one must also manually apply that new key via ADD_CIPHER (the group key index switches between 1 and 2 on each update).

```
+----------------------------------------------------------------------------------+
|       KeyIndex=0,   key=PTK[20h..2Fh]+PTK[38h..3Fh]+PTK[30h..37h], RSC=0         |
|       KeyIndex=1/2, key=GTK[00h..0Fh]+PTK[18h..1Fh]+PTK[10h..17h], RSC=EAPOL RSC |
+----------------------------------------------------------------------------------+
```

### WAPI Cipher Keys
Some atheros firmwares have \"WAPI_ENABLE\" with eight key indices (grpKey=0..3, prwKey=4..7). The DSi firmware probably doesn\'t have that WAPI stuff.

### WMIcmd(0017h) - WMI_DELETE_CIPHER_KEY_CMD ;ignored dummy command on DSi
Parameters (01h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1   keyIndex                                      |
+-----------------------------------------------------------------------+
```


### WMIcmd(0018h) - WMI_ADD_KRK_CMD ;ignored dummy command on DSi
Parameters (10h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  16  krk[WMI_KRK_LEN]                              |
+-----------------------------------------------------------------------+
```

#define WMI_KRK_LEN = 16
KRK maybe means \"Key Registration with Knowledge\"?

### WMIcmd(0019h) - WMI_DELETE_KRK_CMD ;ignored dummy command on DSi
Parameters:

```
+----------------------------------------------------------------------------------+
|       Unknown (none?) (or maybe same as for ADD_KRK ?) (seems to be NONE on DSi) |
+----------------------------------------------------------------------------------+
```


### WMIcmd(0020h) - WMI_SET_TKIP_COUNTERMEASURES_CMD
Parameters (01h bytes):

```
+------------------------------------------------------------------------+
|       00h  A_UINT8  1  cm_en                      ;WMI_TKIP_CM_CONTROL |
+------------------------------------------------------------------------+
```

WMI_TKIP_CM_CONTROL values:

```
+-----------------------------------------------------------------------+
|       WMI_TKIP_CM_DISABLE = 00h                                       |
|       WMI_TKIP_CM_ENABLE  = 01h                                       |
+-----------------------------------------------------------------------+
```

Note: There are also \"CM_CONNECT_TYPE\" values in \"cnxmgmt.h\", is THAT related?

### WMIevent(1009h) - WMI_TKIP_MICERR_EVENT
Event Data (02h bytes):

```
+-----------------------------------------------------------------------+
|       00h  A_UINT8  1  keyid                                          |
|       01h  A_UINT8  1  ismcast                                        |
+-----------------------------------------------------------------------+
```

TKIP MIC Error Event



