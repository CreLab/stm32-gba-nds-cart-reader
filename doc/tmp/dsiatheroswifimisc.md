# DSi Atheros Wifi Misc


### Atheros chip References
Related Atheros chips:

```
+------------------------------------------------------------------------------+
|       AR6001  with MIPS CPU, 18x18 pin BGA package      ;not used in DSi/3DS |
|       AR6002  with Xtensa CPU, 13x13 pin BGA package    ;used in early DSi   |
|       AR6013  as AR6002, with built-in NDS-mode MM3218  ;used in later DSi   |
|       AR6014  as AR6013, with new 3DS-multiplay mode    ;used in 3DS/New3DS  |
+------------------------------------------------------------------------------+
```

There are some datasheets & source code:

```
+-------------------------------------------------------------------------------------+
|       http://www.datasheetspdf.com/PDF/AR6002/705769/6  ;AR6002 datasheet 56 pages  |
|       http://www.datasheetspdf.com/PDF/AR6001X/900300/1 ;AR6001 datasheet 148 pages |
|       http://svn.openmoko.org/developers/nbd/ar6k/      ;AR6K source code           |
+-------------------------------------------------------------------------------------+
```

The overall hardware registers appear to be same for all AR60xx chips (no matter if they contain MIPS or Xtensa CPUs). The AR6002 datasheet doesn\'t contain ANY details about hardware registers. The AR6001 datasheet describes SOME hardware registers. And, the AR6K source code contains details about MORE undocumented hardware registers (in some cases listing DIFFERENT addresses as in the datasheet).
The AR6013/AR6014 chips are probably custom designs with some extra MM3218 emulation for NDS games (and possible with some unknown extra hardware features).

### BPTWL
Apart from SDIO bus, some wifi functions are also controlled by the BPTWL chip (accessed via I2C bus). The wifi related BPTWL signals are:

```
+--------------------------------------------------------------------------------+
|       ATH_TX_H              ;\maybe some/all of these do just indicate traffic 
|       WL_RXPE               ; (for blinking the wifi LED, if it is enabled)    |
|       WL_TXPE               ;/                                                 |
|       /WIFI_RST             ;-Reset or so                                      |
+--------------------------------------------------------------------------------+
```

That signals seem to be used with BPTWL register 30h, which is allowing to disable the Wifi LED, and might also allow to do things like restting the Wifi hardware, and/or switching between NDS and DSi wifi-modes.



