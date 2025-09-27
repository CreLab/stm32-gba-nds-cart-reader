# DSi Atheros Wifi - Internal I/O - 010000h - Serial I2C/SPI (hw2/hw4/hw6)


These registers are providing a general purpose I2C/SPI serial bus. The SI_xxx registers are exactly same in hw2/hw4/hw6.
In the DSi, they are used in I2C mode - for reading wifi calibration data:
- [DSi Atheros Wifi I2C EEPROM](./dsiatheroswifii2ceeprom.md)

### ATH:010000h - SI_CONFIG

```
+------------------------------------------------------------------------------+
|       0-3    DIVIDER            (probably transfer rate, should be 6 on DSi) |
|       4      INACTIVE_CLK       (whatever, should be 1 for I2C)              |
|       5      INACTIVE_DATA      (whatever, should be 1 for I2C)              |
|       6      POS_DRIVE          (whatever, should be zero for I2C)           |
|       7      POS_SAMPLE         (whatever, should be 1 for I2C)              |
|       8-15   -                                                               |
|       16     I2C                (0=SPI, 1=I2C)                               |
|       17     -                                                               |
|       18     BIDIR_OD_DATA      (whatever, should be 1 for I2C)              |
|       19     ERR_INT            (whatever, enable or status?)                |
+------------------------------------------------------------------------------+
```

On DSi, this is register is set to 500B6h.

### ATH:010004h - SI_CS

```
+----------------------------------------------------------------------------------+
|       0-3    TX_CNT    Number of TX bytes (0..8) (should be 1..8 for I2C device) |
|       4-7    RX_CNT    Number of RX bytes (0..8)                                 |
|       8      START     Write 1 to start transfer                                 |
|       9      DONE_INT  Status (0=Busy, 1=Done/Okay)                              |
|       10     DONE_ERR  Status (1=Error)                                          |
|       11-13  BIT_CNT_IN_LAST_BYTE (0=Normal/8bit, 1..7=whatever)                 |
+----------------------------------------------------------------------------------+
```

For I2C with TX_CNT and RX_CNT both nonzero: TX data is transferred first.
Unknown when the DONE flags are cleared (possibly when writing 0 to bit9,10, or when writing 1 to bit8, or maybe automatically after reading).

### ATH:010008h..01000Ch - SI_TX_DATA0/SI_TX_DATA1

```
+-----------------------------------------------------------------------+
|       0-7    DATA0  1st TX byte (device number in case of I2C mode)   |
|       8-15   DATA1  2nd TX byte (if any)                              |
|       16-23  DATA2  ...                                               |
|       24-31  DATA3  ..                                                |
|       32-39  DATA4                                                    |
|       40-47  DATA5                                                    |
|       48-55  DATA6                                                    |
|       56-63  DATA7                                                    |
+-----------------------------------------------------------------------+
```


### ATH:010010h..010014h - SI_RX_DATA0/SI_RX_DATA1

```
+-----------------------------------------------------------------------+
|       0-7    DATA0  1st RX byte (if any)                              |
|       8-15   DATA1  2nd RX byte (if any)                              |
|       16-23  DATA2  ...                                               |
|       24-31  DATA3  ..                                                |
|       32-39  DATA4                                                    |
|       40-47  DATA5                                                    |
|       48-55  DATA6                                                    |
|       56-63  DATA7                                                    |
+-----------------------------------------------------------------------+
```




