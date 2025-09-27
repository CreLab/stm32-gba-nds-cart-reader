# DSi Atheros Wifi I2C EEPROM


The I2C EEPROM is read via the wifi firmware\'s bootstub (prior to executing the main firmware) via the SI_xxx registers. The DSi wifi boards are usually containing a HN58X2408F chip (1Kx8, with 8bit index). However, the bootstub contains code for also supporting HN58X24xx chips with bigger capacity (including such with 16bit index) (although actually using only 300h bytes regardless of the capacity). The I2C device number is A0h, or, in case of EEPROMs with 8bit index, the device number is misused to contain the upper address bits as so:

```
+------------------------------------------------------------------------------------+
|       device = A0h + direction_flag + (addr/100h)*2  ;for devices with 8bit index  |
|       device = A0h + direction_flag                  ;for devices with 16bit index |
+------------------------------------------------------------------------------------+
```


### I2C EEPROM Content for AR6002G

```
+--------------------------------------------------------------------------------+
|       000h 4     Maybe Size, ID, or Version? (00000300h)                       |
|       004h 2     Checksum (all halfwords at [0..2FFh] XORed shall give FFFFh)  |
|       006h 2     Unknown                                                       |
|       008h 2     Country+8000h  ;eg. 8000h+188h=JP, 8000h+348h=US (REG_DOMAIN) |
|       00Ah 6     MAC Address (must be same as in SPI FLASH)                    |
|       010h 4     Type/version? (MSB must be 60h, verified by ARM7)             |
|       014h 4     Zerofilled                                                    |
|       018h 5     Unknown                                                       |
|       01Dh 1Fh   Zerofilled                                                    |
|       03Ch 70h   FFh-filled                                                    |
|       0ACh 8     Zerofilled                                                    |
|       0B4h 12    Unknown                                                       |
|       0C0h 20    Unknown                                                       |
|       0D4h 18h   Zerofilled                                                    |
|       0ECh 4     Unknown                                                       |
|       0F0h 4     Unknown, overwritten by [0ECh] after loading                  |
|       0F4h 12    Unknown, similar to data at 0B4h ?                            |
|       100h 20    Unknown, similar to data at 0C0h ?                            |
|       114h 2Ch   Zerofilled                                                    |
|       140h 8     FFh-filled                                                    |
|       148h 4     Unknown                                                       |
|       14Ch 88h   Zerofilled                                                    |
|       1D4h 3x18  Unknown                                                       |
|       212h 18    Zerofilled                                                    |
|       224h 4x4   Unknown       ;\                                              
|       234h 2x4   Unknown       ;                                               |
|       23Ch 3x4   Unknown       ; together 15x4 maybe ?                         |
|       248h 12    Unknown       ;                                               |
|       254h 3x4   Unknown       ;/                                              |
|       260h 60h   Unknown                                                       |
|       2C0h 40h   Zerofilled                                                    |
|       300h 100h  Not used (not loaded to RAM)                                  |
+--------------------------------------------------------------------------------+
```


The presence of the I2C EEPROM appears to be some mis-conception. It might make sense to store the wifi calibration data on the daughterboard (rather than in eMMC storage on mainboard), however, it could be as well stored in the SPI FLASH chip, but Nintendo apparently didn\'t knew how to do that.



