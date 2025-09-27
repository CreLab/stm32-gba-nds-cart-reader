# DS Wifi Configuration Ports


### 4808120h - W_CONFIG_120h (R/W) ;init from firmware\[04Ch\] ;81ff 0048-\>SAME
### 4808122h - W_CONFIG_122h (R/W) ;init from firmware\[04Eh\] ;ffff 4840-\>SAME
### 4808124h - W_CONFIG_124h (R/W) ;init from firmware\[05Eh\] ;ffff 0000-\>0032
### 4808128h - W_CONFIG_128h (R/W) ;init from firmware\[060h\] ;ffff 0000-\>01F4
### 4808130h - W_CONFIG_130h (R/W) ;init from firmware\[054h\] ;0fff 0142-\>0140
### 4808132h - W_CONFIG_132h (R/W) ;init from firmware\[056h\] ;8fff 8064-\>SAME
### 4808140h - W_CONFIG_140h (R/W) ;init from firmware\[058h\] ;ffff 0000-\>E0E0
### 4808142h - W_CONFIG_142h (R/W) ;init from firmware\[05Ah\] ;ffff 2443-\>SAME
### 4808144h - W_CONFIG_144h (R/W) ;init from firmware\[052h\] ;00ff 0042-\>SAME
### 4808146h - W_CONFIG_146h (R/W) ;init from firmware\[044h\] ;00ff 0016-\>0002
### 4808148h - W_CONFIG_148h (R/W) ;init from firmware\[046h\] ;00ff 0016-\>0017
### 480814Ah - W_CONFIG_14Ah (R/W) ;init from firmware\[048h\] ;00ff 0016-\>0026
### 480814Ch - W_CONFIG_14Ch (R/W) ;init from firmware\[04Ah\] ;ffff 162C-\>1818
### 4808150h - W_CONFIG_150h (R/W) ;init from firmware\[062h\] ;ff3f 0204-\>0101
### 4808154h - W_CONFIG_154h (R/W) ;init from firmware\[050h\] ;7a7f 0058-\>SAME
These ports are to be initialized from firmware settings.
Above comments show the R/W bits (eg. 81FFh means bit15 and bit8-0 are R/W, bit14-9 are always zero), followed by the initial value on Reset (eg. 0048h), followed by new value after initialization from firmware settings (eg. 0032h, or SAME if the Firmware value is equal to the Reset value; these values seem to be identical in all currently existing consoles).
Note: Firmware part4 changes W_CONFIG_124h to C8h, and W_CONFIG_128h to 7D0h, and W_CONFIG_150h to 202h, and W_CONFIG_140h depending on tx rate and preamble:

```
+-------------------------------------------------------------------------------------+
|       W_CONFIG_140h = firmware[058h]+0202h             ;1Mbit/s                     |
|       W_CONFIG_140h = firmware[058h]+0202h-6161h       ;2Mbit/s with long preamble  |
|       W_CONFIG_140h = firmware[058h]+0202h-6161h-6060h ;2Mbit/s with short preamble |
+-------------------------------------------------------------------------------------+
```


### 48080ECh - W_CONFIG_0ECh (R/W) ;firmware writes 3F03h (same as on power-up)
### 48080D4h - W_CONFIG_0D4h (R/W) ;firmware writes 0003h (affectd by W_MODE_RST)
### 48080D8h - W_CONFIG_0D8h (R/W) ;firmware writes 0004h (same as on power-up)
### 4808254h - W_CONFIG_254h (?) ;firmware writes 0000h (read: EEEEh on DS-Lite)
Firmware just initializes these ports with fixed values, without further using them after initialization.

### 48080DAh - W_RX_LEN_CROP (R/W) ;firmware writes 0602h (same as on power-up)

```
+-------------------------------------------------------------------------------+
|       0-7   Decrease RX Length by N halfwords for Non-WEP packets (usually 2) |
|       8-15  Decrease RX Length by N halfwords for WEP packets     (usually 6) |
+-------------------------------------------------------------------------------+
```

Used to exclude the FCS (and WEP IV+ICV) from the length entry in the Hardware RX Header.



