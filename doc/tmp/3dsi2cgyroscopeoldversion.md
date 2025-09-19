# 3DS I2C Gyroscope (old version)


I2C Device 2:D0h

**GYRO Register Map - InvenSense ITG-3270 gyroscope (used in Old 3DS)**

```
+-----------------------------------------------------------------------+
|       Hex     Register Name R/W                                       |
|       00h     WHO_AM_I      R/W Device ID (aka Who Am I)              |
|       15h     SMPLRT_DIV    R/W Sample Rate Divider (reset=00h)       |
|       16h                                                             |
|   DLPF_FS       R/W Low Pass Filter and Full Scale Config (reset=00h) |
|       17h     INT_CFG       R/W Interrupt Configuration (reset=00h)   |
|       1Ah     INT_STATUS    R   Interrupt Status (reset=00h)          |
|       1Bh/1Ch TEMP_OUT_H/L  R   signed 16bit Temperature data (R)     |
|       1Dh/1Eh GYRO_XOUT_H/L R   signed 16bit Gyro X output data (R)   |
|       1Fh/20h GYRO_YOUT_H/L R   signed 16bit Gyro Y output data (R)   |
|       21h/22h GYRO_ZOUT_H/L R   signed 16bit Gyro Y output data (R)   |
|       3Eh     PWR_MGM       R/W Power Management (reset=00h)          |
|       xxh-FFh Undocumented (unknown)                                  |
+-----------------------------------------------------------------------+
```

Note: The 16bit H/L values are in BIG-ENDIAN format.

**Register Description**
The register space allows single-byte reads and writes, as well as burst
reads and writes. When performing burst reads or writes, the memory
pointer will increment until reading or writing is terminated by the
master, or until the memory pointer reaches \"certain reserved register
between 21h and 3Ch\" (uh, that would include GYRO_ZOUT at 21h and/o
22h?).
Note that any bit that is not defined should be set to zero.

- **GYRO\[00h\] - WHO_AM_I - Device ID (R/W)**

```
+-----------------------------------------------------------------------+
|       0    R                                                          |
| eserved ("may be 0 or 1") (maybe ID.bit1, maybe R/W, or what?)    (?) |
|       1-6  I2C                                                        |
|  Device ID bit2-7 (initially 34h on power-up, aka D0h/4)        (R/W) |
|       7    R                                                          |
| eserved ("should be 0")                                           (?) |
+-----------------------------------------------------------------------+
```

Contains the upper 6bit of the 8bit I2C Device ID, can be used for
detection, the value is also write-able and can be changed after
power-on.

- **GYRO\[15h\] - SMPLRT_DIV - Sample Rate Divider (R/W)**

```
+-----------------------------------------------------------------------+
|                                                                       |
| 0-7  Sample Rate Divider (00h..FFh=Divide by 1..100h) (initially 00h) |
+-----------------------------------------------------------------------+
```

The gyros outputs are sampled internally at either 1kHz or 8kHz,
determined by the DLPF_CFG setting (see register 22). This sampling is
then filtered digitally and delivered into the sensor registers after
the number of cycles determined by this register. The sample rate is
given by the following formula:

```
+-----------------------------------------------------------------------+
|       Fsampl                                                          |
| e = Finternal / (divider+1)   ;where Finternal is either 1kHz or 8kHz |
+-----------------------------------------------------------------------+
```

As an example, if the internal sampling is at 1kHz, then setting this
register to 7 would give the following:

```
+-----------------------------------------------------------------------+
|       Fsample = 1kHz / (7 + 1) = 125Hz, or 8ms per sample             |
+-----------------------------------------------------------------------+
```


- **GYRO\[16h\] - DLPF_FS - Low Pass Filter and Full Scale Config (R/W)**

```
+-----------------------------------------------------------------------+
|       0-                                                              |
| 2  DLPF_CFG  Digital low pass filter bandwidth & internal sample rate |
|       3-4  FS_SEL    Full scale selection for gyro sensor data        |
|       5-7  Reserved (should be 0)                                     |
+-----------------------------------------------------------------------+
```

FS_SEL Gyro Full-Scale Range:

      0 Reserved (despite of being power-up default)
      1 Reserved
      2 Reserved
      3 +/-2000
