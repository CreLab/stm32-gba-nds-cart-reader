# DSi SD/MMC Protocol: Signals


XXX\...

### SD Mode 1-bit data transfer mode

```
+-------------------------------------------------------------------------------------+
|               __ start bit                             __ checksum bits (CRC-CCITT) |
|              |                                        |                             |
|              |  <------------data bits------------->  |   __ stop bit               |
|              |                                        |  |                          |
|       DAT0   0  1st 2nd 3rd 4th 5th 6th 7th ... last crc 1                          |
+-------------------------------------------------------------------------------------+
```


### SD Mode 4-bit data transfer mode

```
+-----------------------------------------------------------------------+
|               __ start bit         __ checksum bits (CRC-CCITT)       |
|              |                    |                                   |
|              |  <--data bits-->   |   __ stop bit                     |
|              |                    |  |                                |
|       DAT3   0  1st 5th ... ...  crc 1                                |
|       DAT2   0  2nd 6th ... ...  crc 1                                |
|       DAT1   0  3rd 7th ... ...  crc 1                                |
|       DAT0   0  4th 8th ... last crc 1                                |
+-----------------------------------------------------------------------+
```




