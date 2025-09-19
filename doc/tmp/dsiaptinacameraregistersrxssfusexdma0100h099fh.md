# DSi Aptina Camera Registers: RX_SS, FUSE, XDMA (0100h-099Fh)


### RX_SS (0100h-0117h)

```
+-----------------------------------------------------------------------------------+
|       0100h  ..  RESERVED_RX_SS_100     Reserved                                  |
|       0102h   2  TEST_PXL_RED           Test Pixel Red    ;\Default value is 1FFh 
|       0104h   2  TEST_PXL_G1            Test Pixel Green1 ; for Gray Flat Field   |
|       0106h   2  TEST_PXL_G2            Test Pixel Green2 ; (0..03FFh, def=01FFh) |
|       0108h   2  TEST_PXL_BLUE          Test Pixel Blue   ;/                      |
|       010Ah  ..  RESERVED_RX_SS_10A-116 Reserved                                  |
+-----------------------------------------------------------------------------------+
```


### FUSE_ROM (0800h-081Fh)
Reserved, unknown purpose, all zero in DSi.

```
+-----------------------------------------------------------------------+
|       0800h  ..  RESERVED_FUSE_ROM_800-81E  Reserved                  |
+-----------------------------------------------------------------------+
```


### XDMA (0982h-099Fh)
Access to internal LOGICAL \"driver\" variables.

```
+------------------------------------------------------------------------------------+
|       0982h  ..  RESERVED_XDMA_982      Reserved                                   |
|       098Ch   2  MCU_ADDRESS            MCU Address (0000h..FFFFh)                 |
|                    0-7   driver_variable (0..FFh)                                  |
|                    8-12  driver_id       (0..1Fh) (eg. 3=AWB, 7=MODE, etc.)        |
|                    13-14 address space   (0=Physical/RAM/SFR, 1=Logical/Variables) |
|                    15    access_8_bit    (0=16bit, 1=8bit; converted to 16bit)     |
|       0990h 8x2  MCU_DATA_0-7           MCU Data 0..7 (8 x 16bit)                  |
+------------------------------------------------------------------------------------+
```

For reading, it\'s best to use \"16bit\" mode, no matter if reading an 8bit BYTE, or a 16bit MSB,LSB value. The \"8bit\" mode is converting bytes to 16bit values (MSB=00h, LSB=BYTE), which is a rather contraproductive idiotism; intended for I2C functions that implement only 16bit data transfers, but no 8bit transfers.
Unknown what exactly is mapped at MCU_DATA_0-7 (probably the 16 bytes at MCU_ADDRESS+0..15, probably with direct mapping / ie. without latching a copy of that memory).
MCU_ADDRESS doesn\'t seem to increment after reading data, however, the i2c index does increase, so one can probably read up to 16 bytes from MCU_DATA_0-7.



