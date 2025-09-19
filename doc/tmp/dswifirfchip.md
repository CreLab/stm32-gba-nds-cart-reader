# DS Wifi RF Chip


RF-Chip RF9008 (compatible to RF2958 from RF Micro Devices, Inc.) (Original DS)
BB/RF-Chip Mitsumi MM3218 (DS-Lite)

### 480817Ch - W_RF_DATA2 - RF chip serial data/transfer enable (R/W)
For Type2 (ie. firmware\[040h\]\<\>3):

```
+-----------------------------------------------------------------------+
|       0-1   Upper 2bit of 18bit data                                  |
|       2-6   Index   (00h..1Fh) (firmware uses only 00h..0Bh)          |
|       7     Command (0=Write data, 1=Read data)                       |
|       8-15  Should be zero (not used with 24bit transfer)             |
+-----------------------------------------------------------------------+
```

For Type3 (ie. firmware\[040h\]=3):

```
+-----------------------------------------------------------------------+
|       0-3   Command (5=Write data, 6=Read data)                       |
|       4-15  Should be zero (not used with 20bit transfer)             |
+-----------------------------------------------------------------------+
```

Writing to this register starts the transfer.

### 480817Eh - W_RF_DATA1 - RF chip serial data (R/W)
For Type2 (ie. firmware\[040h\]\<\>3):

```
+-----------------------------------------------------------------------+
|       0-15  Lower 16bit of 18bit data                                 |
+-----------------------------------------------------------------------+
```

For Type3 (ie. firmware\[040h\]=3):

```
+-------------------------------------------------------------------------------+
|       0-7   Data (to be written to chip) (or being received from chip)        |
|       8-15  Index (usually 00h..28h) (index 40h..FFh are mirrors of 00h..3Fh) |
+-------------------------------------------------------------------------------+
```

This value should be set before setting W_RF_DATA2.

### 4808180h - W_RF_BUSY - RF chip serial busy flag (R)

```
+-----------------------------------------------------------------------+
|       0     Transfer Busy (0=Ready, 1=Busy)                           |
|       1-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Used to sense transfer completion after writes to W_RF_DATA2.

### 4808184h - W_RF_CNT - RF chip serial control (R/W)

```
+-----------------------------------------------------------------------+
|       0-5   Transfer length (init from firmware[041h].Bit0-5)         |
|       6-7   Always zero                                               |
|       8     Unknown         (init from firmware[041h].Bit7)           |
|       9-13  Always zero                                               |
|       14    Unknown         (usually 0)                               |
|       15    Always zero                                               |
+-----------------------------------------------------------------------+
```

This register is initialized by firmware bootcode - don\'t change.
Usually, Type2 has length=24bit and flag=0. Type3 uses length=20bit and flag=1.

### Caution For Type2 (ie. firmware\[040h\]\<\>3)
Before accessing Type2 RF Registers, first BB\[01h\] must have been properly initialized (ie. BB\[01h\].Bit7 must have been toggled from 0-to-1).



