# DSi Atheros Wifi - Unimplemented WMI Pyxis Functions


### WMIcmd(F009h) - WMI_UNUSED1 or WMI_PYXIS_CONFIG_CMD
Parameters:

```
+-------------------------------------------------------------------------------------+
|      Config Header:                                                                 |
|       00h  A_UINT16 2  pyxisConfigType ;One of WMI_PYXIS_CONFIG_TYPE                |
|       02h  A_UINT16 2  pyxisConfigLen  ;Length in Bytes of Information that follows |
|      When pyxisConfigType=0=WMI_PYXIS_GEN_PARAMS                                    |
|       04h  A_UINT32 2  dataWindowSizeMin                                            |
|       08h  A_UINT32 2  dataWindowSizeMax                                            |
|       0Ch  A_UINT8  1  maxJoiners                                                   |
|      When pyxisConfigType=1=WMI_PYXIS_DSCVR_PARAMS                                  |
|       04h  A_UINT32 4  dscvrWindow                                                  |
|       08h  A_UINT32 4  dscvrInterval                                                |
|       0Ch  A_UINT32 4  dscvrLife                                                    |
|       10h  A_UINT32 4  probeInterval                                                |
|       14h  A_UINT32 4  probePeriod                                                  |
|       18h  A_UINT16 2  dscvrChannel                                                 |
|      When pyxisConfigType=2=WMI_PYXIS_SET_TX_MODE                                   |
|       04h  A_BOOL   4  mode                                                         |
+-------------------------------------------------------------------------------------+
```

Whatever \"Pyxis specific\".

### WMIcmd(F00Ah) - WMI_UNUSED2 or WMI_PYXIS_OPERATION_CMD
Parameters:

```
+------------------------------------------------------------------------------------+
|      Command Header:                                                               |
|       00h  A_UINT16 2  pyxisCmd                                                    |
|       02h  A_UINT16 2  pyxisCmdLen   ;Length following this header                 |
|      When pyxisCmd=0=WMI_PYXIS_DISC_PEER                                           |
|       04h  A_UINT8  6  peerMacAddr[ATH_MAC_LEN]                                    |
|      When pyxisCmd=1=WMI_PYXIS_JOIN_PEER                                           |
|       04h  A_UINT32 4  ctrl_flags (One of the Bits determines if it                |
|                         is Virt Adhoc/the device is to join a BSS)                 |
|       08h  A_UINT16 2  channel                  ;Data Channel                      |
|       0Ah  A_UINT8  1  networkType              ;network type                      |
|       0Bh  A_UINT8  1  dot11AuthMode            ;OPEN_AUTH                         |
|       0Ch  A_UINT8  1  authMode                 ;NONE_AUTH                         |
|       0Dh  A_UINT8  1  pairwiseCryptoType       ;One of NONE_CRYPT, AES_CRYPT      |
|       0Eh  A_UINT8  1  pairwiseCryptoLen        ;0 since ADD_KEY passes the length |
|       0Fh  A_UINT8  1  groupCryptoType          ;One of NONE_CRYPT, AES_CRYPT      |
|       10h  A_UINT8  1  groupCryptoLen           ;0 since ADD_KEY passes the length |
|       11h  A_UINT8  6  peerMacAddr[ATH_MAC_LEN] ;BSSID of peer network             |
|       17h  A_UINT8  6  nwBSSID[ATH_MAC_LEN]     ;BSSID of the Pyxis Adhoc Network  |
|      When pyxisCmd=?=WHAT? below is also "incompletely-defined" as pyxisCmd:       |
|       04h  A_BOOL   4  mode (what is this here? dupe of WMI_PYXIS_CONFIG_CMD?)     |
+------------------------------------------------------------------------------------+
```

Whatever \"Pyxis specific\".



