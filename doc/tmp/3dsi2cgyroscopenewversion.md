# 3DS I2C Gyroscope (new version)


I2C Device 2:D2h

**NEW_GYRO Register Map - InvenSense ITG-1010**

```
+-----------------------------------------------------------------------+
|       04h/05h XG_OFFS_TC_H/L R/W Temperature Compensation X (10bit)   |
|       07h/08h YG_OFFS_TC_H/L R/W Temperature Compensation Y (10bit)   |
|       0Ah/0Bh ZG_OFFS_TC_H/L R/W Temperature Compensation Z (10bit)   |
|       13h/14h XG_OFFS_USRH/L R/W User DC Bias Compensation X (16bit)  |
|       15h/16h YG_OFFS_USRH/L R/W User DC Bias Compensation Y (16bit)  |
|       17h/18h ZG_OFFS_USRH/L R/W User DC Bias Compensation Z (16bit)  |
|       19h     SMPLRT_DIV     R/W Sample Rate Divider                  |
|       1Ah     CONFIG         R/W Configuration                        |
|       1Bh     GYRO_CONFIG    R/W Gyroscope Configuration              |
|       23h     FIFO_EN        R/W FIFO Channel Enable                  |
|                                                                       |
|      37h     INT_PIN_CFG    R/W INT Pin / Bypass Enable Configuration |
|       38h     INT_ENABLE     R/W Interrupt Enable                     |
|       3Ah     INT_STATUS     R   Interrupt Status                     |
|                                                                       |
| 41h/42h TEMP_OUT_H/L   R   Temperature Measurement  TEMP_OUT  (16bit) |
|                                                                       |
| 43h/44h GYRO_XOUT_H/L  R   Gyroscope Measurements X GYRO_XOUT (16bit) |
|                                                                       |
| 45h/46h GYRO_YOUT_H/L  R   Gyroscope Measurements Y GYRO_YOUT (16bit) |
|                                                                       |
| 47h/48h GYRO_ZOUT_H/L  R   Gyroscope Measurements Z GYRO_ZOUT (16bit) |
|       6Ah     USER_CTRL      R/W User Control                         |
|       6Bh     PWR_MGMT_1     R/W Power Management 1                   |
|       6Ch     PWR_MGMT_2     R/W Power Management 2                   |
|       72h/73h FIFO_COUNTH/L  R/W FIFO Count Register (10bit)          |
|       74h     FIFO_R_W       R/W FIFO Read/Write Data                 |
- |       75h     WHO_AM_I       R   Device ID       - WHO_AM_I[6:1] -    |
|       80h-FFh Undocumented (in New3DSXL these are same as 00h-7Fh)    |
+-----------------------------------------------------------------------+
```

Note: The 16bit H/L values are in BIG-ENDIAN format.

- **NEW_GYRO\[04h/05h\] - XG_OFFS_TC_H/L - Temperature Compensation 
(10bit, R/W)**
- **NEW_GYRO\[07h/08h\] - YG_OFFS_TC_H/L - Temperature Compensation 
(10bit, R/W)**
- **NEW_GYRO\[0Ah/0Bh\] - ZG_OFFS_TC_H/L - Temperature Compensation 
(10bit, R/W)**
Unknown if these registers are implemented in 3DS (register 00h..0Bh
contain \"garbage\" that rather doesn\'t look like 10bit values).

```
+-----------------------------------------------------------------------+
|                                                                       |
| 0-9   Signed 10bit, in 2.52 mdps/C steps (default=factory programmed) |
|       10-15 Unused (should be 0)                                      |
+-----------------------------------------------------------------------+
```

Writing 0000h disables temperature compensation (this doesn\'t affec
the factory values, which will be restored upon reset/power-up).

- **NEW_GYRO\[13h/14h\] - XG_OFFS_USRH/L - User DC Bias Compensation 
(16bit, R/W)**
- **NEW_GYRO\[15h/16h\] - YG_OFFS_USRH/L - User DC Bias Compensation 
(16bit, R/W)**
- **NEW_GYRO\[17h/18h\] - ZG_OFFS_USRH/L - User DC Bias Compensation 
(16bit, R/W)**

```
+-----------------------------------------------------------------------+
|       0-15  Signed 16bit, subtracted from the sensor values           |
+-----------------------------------------------------------------------+
```


- **NEW_GYRO\[19h\] - SMPLRT_DIV - Sample Rate Divider (R/W)**

```
+-----------------------------------------------------------------------+
|                                                                       |
| 0-7  Sample Rate Divider (00h..FFh=Divide by 1..100h) (initially 00h) |
+-----------------------------------------------------------------------+
```

This register specifies the divider from the gyroscope output rate that
can be used to generate a reduced Sample Rate.

```
+-----------------------------------------------------------------------+
|                                                                       |
|  When FCHOICE_B=0 and DLPF_CFG=1..6   --> Sample Rate Divider IS USED |
|       When                                                            |
|  FCHOICE_B=0 and DLPF_CFG=0 or 7 --> Sample Rate is fixed at 8kHz ??? |
|       W                                                               |
| hen FCHOICE_B=1..3                  --> Sample Rate is fixed at 32kHz |
+-----------------------------------------------------------------------+
```

The sensor register output and FIFO output are both based on the Sample
Rate.
When this register is effective under the FCOICE_B and DLPF_CFG
settings, the reduced Sample Rate is generated by the formula below:

```
+-----------------------------------------------------------------------+
|       Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)          |
+-----------------------------------------------------------------------+
```

where Gyroscope Output Rate = 1kHz.

- **NEW_GYRO\[1Ah\] - CONFIG - Configuration (R/W)**

```
+-----------------------------------------------------------------------+
|                                                                       |
| 0-2 DLPF_CFG      Configures the Digital Low Pass Filter DLPF setting |
|       3-5 EXT_SYNC_SET  Configures the Frame Sync FSYNC pin sampling  |
|       6                                                               |
|   FIFO_MODE     FIFO Mode (0=Overwrite oldest data, 1=Stop when full) |
|       7   -             Reserved                                      |
+-----------------------------------------------------------------------+
```

Please note that the DLPF can only be used when FCHOICE_B=0 (Register
27).
An external signal connected to the FSYNC pin can be sampled by
configuring EXT_SYNC_SET.
Signal changes to the FSYNC pin are latched so that short strobes may be
captured. The latched FSYNC signal will be sampled at the Sampling Rate,
as defined in register 25. After sampling, the latch will reset to the
current FSYNC signal state.
The sampled value will be reported in place of the least significant bit
in a sensor data register determined by the value of EXT_SYNC_SET
according to the following table.

```
+-----------------------------------------------------------------------+
|       EXT_SYNC_SET  FSYNC Bit Location                                |
|       0             Input disabled                                    |
|       1             TEMP_OUT_L.bit0                                   |
|       2             GYRO_XOUT_L.bit0                                  |
|       3             GYRO_YOUT_L.bit0                                  |
|       4             GYRO_ZOUT_L.bit0                                  |
+-----------------------------------------------------------------------+
```

The DLPF is configured by DLPF_CFG, when FCHOICE_B=0. The gyroscope and
temperature sensor are filtered according to the value of DLPF_CFG and
FCHOICE_B as shown in the table below.

```
+-----------------------------------------------------------------------+
|       F                                                               |
| CHOICE_B  DLPF_CFG   <---Gyroscope------->   <--Temperature Sensor--> |
|       <1> <0>               Bandwidth Delay   Fs    Bandwidth  Delay  |
|       0   0      0          250Hz     0.97ms  8kHz  4000Hz     0.04ms |
|       0   0      1          184Hz     2.9ms   1kHz  188Hz      1.9ms  |
|       0   0      2          92Hz      3.9ms   1kHz  98Hz       2.8ms  |
|       0   0      3          41Hz      5.9ms   1kHz  42Hz       4.8ms  |
|       0   0      4          20Hz      9.9ms   1kHz  20Hz       8.3ms  |
|       0   0      5          10Hz      17.85ms 1kHz  10Hz       13.4ms |
|       0   0      6          5Hz       33.48ms 1kHz  5Hz        18.6ms |
|       0   0      7          3600Hz    0.17ms  8kHz  4000Hz     0.04ms |
|       -   1      -          8800Hz    0.064ms 32kHz 4000Hz     0.04ms |
|       1   0      -          3600Hz    0.11ms  32kHz 4000Hz     0.04ms |
+-----------------------------------------------------------------------+
```


- **NEW_GYRO\[1Bh\] - GYRO_CONFIG - Gyroscope Configuration (R/W)**

```
+-----------------------------------------------------------------------+
|       0-1 FCHOICE_B Choose the gyroscope output setting               |
|       2   -         Reserved                                          |
|       3-4 FS_SEL    Gyroscope Full Scale range select                 |
|       5   ZG_ST     Gyroscope X self test (0=Normal, 1=Perform test)  |
|       6   YG_ST     Gyroscope Y self test (0=Normal, 1=Perform test)  |
|       7   XG_ST     Gyroscope Z self test (0=Normal, 1=Perform test)  |
+-----------------------------------------------------------------------+
```

The electro/mechanical self test bits will move the sensor\'s proo
- masses, the result can be then seen in sensor registers \[43h..48h\].

```
+-----------------------------------------------------------------------+
|       FS_SEL Full Scale Range                                         |
|       0      +/-250 ø/s                                               |
|       1      +/-500 ø/s                                               |
|       2      +/-1000 ø/s                                              |
|       3      +/-2000 ø/s                                              |
+-----------------------------------------------------------------------+
```

FCHOICE_B, in conjunction with DLPF_CFG (Register 1Ah), is used to
choose the gyroscope output setting. For further information regarding
the operation of FCHOICE_B, please refer to Section 4.2.

- **NEW_GYRO\[23h\] - FIFO_EN - R/W FIFO Channel Enable (R/W)**

```
+-----------------------------------------------------------------------+
|       0-3 -            Reserved                                       |
|       4   ZG_FIFO_EN   Output Gyroscope Z to FIFO (0=No, 1=Yes)       |
|       5   YG_FIFO_EN   Output Gyroscope Y to FIFO (0=No, 1=Yes)       |
|       6   XG_FIFO_EN   Output Gyroscope X to FIFO (0=No, 1=Yes)       |
|       7   TEMP_FIFO_EN Output Temperature to FIFO (0=No, 1=Yes)       |
+-----------------------------------------------------------------------+
```


- **NEW_GYRO\[37h\] - INT_PIN_CFG - INT Pin / Bypass Enable Configuratio
(R/W)**

```
+-----------------------------------------------------------------------+
|       0-1 -                 Reserved                                  |
|       2                                                               |
|   FSYNC_INT_MODE_EN FSYNC Pin Enable  (0=Disable, 1=Enable FSYNC IRQ) |
|                                                                       |
| 3   FSYNC_INT_LEVEL   FSYNC Pin Act Low (0=Active High, 1=Active Low) |
|       4   INT_                                                        |
| RD_CLEAR     Interrupt Clear (0=Upon IntStatus read, 1=Upon Any read) |
|       5                                                               |
|  LATCH_INT_EN     INT Pin Hold       (0=50us pulse, 1=Hold until ack) |
|                                                                       |
|   6   INT_OPEN         INT Pin Open Drain (0=Push-pull, 1=Open drain) |
|                                                                       |
| 7   INT_LEVEL        INT Pin Active Low (0=Active High, 1=Active Low) |
+-----------------------------------------------------------------------+
```

FSYNC_INT_MODE_EN: When bit2 is equal to 1, the FSYNC pin will trigger
an interrupt when it transitions to the level specified by
FSYNC_INT_LEVEL. When a FSYNC interrupt is triggered, the FSYNC_INT bit
in Register 58 will be set to 1. An interrupt is sent to the host
processor if the FSYNC interrupt is enabled by the FSYNC_INT_EN bit in
Register 56.

- **NEW_GYRO\[38h\] - INT_ENABLE - Interrupt Enable (R/W)**

```
+-----------------------------------------------------------------------+
|       0   DATA                                                        |
| _RDY_EN   Enable Data Ready interrupt           (0=Disable, 1=Enable) |
|       1-2 -             Reserved                                      |
|       3   FSY                                                         |
| NC_INT_EN  Enable FSYNC pin interrupt (0=Disable, 1=Use FSYNC as IRQ) |
|       4   FIFO                                                        |
| _OFLOW_EN Enable FIFO buffer overflow interrupt (0=Disable, 1=Enable) |
|       5-7 -             Reserved                                      |
+-----------------------------------------------------------------------+
```

The Data Ready interrupt is triggered when all the sensor registers have
been written with the latest gyro sensor data.

- **NEW_GYRO\[3Ah\] - INT_STATUS - Interrupt Status (R)**

```
+-----------------------------------------------------------------------+
|       0                                                               |
|   DATA_RDY_INT   Data Ready (sample rate) interrupt (0=No, 1=Yes/IRQ) |
|       1-2 -              Reserved                                     |
|       3                                                               |
|   FSYNC_INT      FSYNC Frame Sync interrupt         (0=No, 1=Yes/IRQ) |
|       4                                                               |
|   FIFO_OFLOW_INT FIFO Overrun interrupt             (0=No, 1=Yes/IRQ) |
|       5-7 -              Reserved                                     |
+-----------------------------------------------------------------------+
```

Each bit will clear after the register is read.

- **NEW_GYRO\[41h/42h\] - TEMP_OUT_H/L - Temperature Measurement (R
16bit)**
- **NEW_GYRO\[43h/44h\] - GYRO_XOUT_H/L - Gyroscope Measurements X (R
16bit)**
- **NEW_GYRO\[45h/46h\] - GYRO_YOUT_H/L - Gyroscope Measurements Y (R
16bit)**
- **NEW_GYRO\[47h/48h\] - GYRO_ZOUT_H/L - Gyroscope Measurements Z (R
16bit)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|  0-15  Most recent sensor value, signed 16bit, updated at sample rate |
+-----------------------------------------------------------------------+
```

- These sensor registers \[41h..48h\], are composed of two sets o
registers: an internal register set and a user-facing read register
set.

```
+-----------------------------------------------------------------------+
|      The internal register set is always updated at the Sample Rate.  |
|      The                                                              |
|  user-facing read register set duplicates the internal register set's |
|      data                                                             |
|  values whenever the serial interface is idle. This guarantees that a |
|      burst r                                                          |
| ead of sensor registers will read measurements from the same sampling |
|      instant.                                                         |
+-----------------------------------------------------------------------+
```

Note that if burst reads are not used, the user is responsible for
ensuring a set of single byte reads correspond to a single sampling
instant by checking the Data Ready interrupt.
Temperature: The scale factor and offset for the temperature sensor are
found in the Electrical Specifications table in Product Specification
document.

- **NEW_GYRO\[6Ah\] - USER_CTRL - User Control (R/W)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|   0   Reset Gyro/Temp sensor signal paths (0=No/ready, 1=Reset/busy?) |
|       1   Reserved                                                    |
|                                                                       |
|   2   FIFO Reset (clear fifo)             (0=No/ready, 1=Reset/busy?) |
|       3   Reserved                                                    |
|       5   Reserved                                                    |
|                                                                       |
| 4   Primary Interface select            (0=I2C/normal, 1=SPI/instead) |
|       6   FIFO Read Enable                    (0=Disable, 1=Enable)   |
|       7   Reserved                                                    |
+-----------------------------------------------------------------------+
```

It is \"recommended\" to have FIFO Read disabled when doing FIFO Reset.

- **NEW_GYRO\[6Bh\] - PWR_MGMT_1 - Power Management 1 (R/W)**

```
+-----------------------------------------------------------------------+
|       0-2 CLKSEL       Clock source select (see below)                |
|                                                                       |
|   3   TEMP_DIS     Temperature sensor disable   (0=Normal, 1=Disable) |
|       4-5 -            Reserved                                       |
|                                                                       |
|     6   SLEEP        Sleep Mode                   (0=Normal, 1=Sleep) |
|       7                                                               |
| DEVICE_RESET Reset all internal registers (0=No/ready, 1=Reset/busy?) |
+-----------------------------------------------------------------------+
```

CLKSEL Clock Source

```
+-----------------------------------------------------------------------+
|       00h = Internal 20MHz oscillator                                 |
|       01h = PLL  ;\                                                   
|       02h = PLL  ; gyroscope based clock (PLL)                        |
|       03h = PLL  ;                                                    |
|       04h = PLL  ;                                                    |
|       05h = PLL  ;/                                                   |
|       06h = Internal 20MHz oscillator                                 |
|       07h = Reserved                                                  |
+-----------------------------------------------------------------------+
```

The PLL is the default clock source upon power up (uh, but all registers
except WHO_AM_I are said to be zero on power-up). In order for the
gyroscope to perform to spec, the PLL must be selected as the clock
source.
When the internal 20MHz oscillator is chosen as the clock source, the
device can operate while having the gyroscopes disabled. However, this
is only recommended if the user wishes to use the internal temperature
sensor in this mode.
For further information regarding the device clock source, please refer
to the relevant \"Product Specification document\" (uh, but thi
sentence comes from the Product Specification) and the Power Mode
Transition Descriptions section in the Appendix (uh, but there is no
Appendix).
Reset: The default values for each register can be found in \"Sectio
3\", uh?

- **NEW_GYRO\[6Ch\] - PWR_MGMT_2 - Power Management 2 (R/W)**

```
+-----------------------------------------------------------------------+
|       0   STBY_ZG Gyro Z standby mode  (0=Normal, 1=Standby)          |
|       1   STBY_YG Gyro Y standby mode  (0=Normal, 1=Standby)          |
|       2   STBY_XG Gyro X standby mode  (0=Normal, 1=Standby)          |
|       3-5 -       Reserved bit(s)                                     |
|       6-7 -       Reserved bit-pair?                                  |
+-----------------------------------------------------------------------+
```

To activate any gyro axis again, all three gyro axes must first be put
into standby mode, and then be turned on simultaneously.
If the user wishes to put all three gyro axes into standby mode, the
internal oscillator must be selected as the clock source.
If all three gyro axes are put into standby mode while the clock source
of the device is set to the PLL (with the gyro drive generating the
reference clock), the chip will hang due to an absence of a clock.
As long as one gyro axis is enabled, the drive circuit will remain
active and the PLL will provide a clock.

- **NEW_GYRO\[72h/73h\] - FIFO_COUNTH/L - FIFO Count Register (10bit
(R/W)**

```
+-----------------------------------------------------------------------+
|       0-9   Number of bytes stored in the FIFO buffer (max=?)         |
|       10-15 Reserved                                                  |
+-----------------------------------------------------------------------+
```

The count value is latched when reading the High byte (ie. one can read
H-then-L without risking carry-outs from L to H during reading).

- **NEW_GYRO\[74h\] - FIFO_R_W - FIFO Read/Write Data (R/W)**

```
+-----------------------------------------------------------------------+
|       0-7   FIFO Data                                                 |
+-----------------------------------------------------------------------+
```

This register is used to read and write(?) data from the FIFO buffer.
Data is written to the FIFO in order of register number, (from lowest to
highest). If all the FIFO enable flags (see below) are enabled, the
- contents of NEW_GYRO\[41h..48h\] will be written in order.

- **NEW_GYRO\[75h\] - WHO_AM_I - Device ID (always 68h) (R)**

```
+-----------------------------------------------------------------------+
|                                                                       |
|    0   Reserved ("Hard coded to 0")                               (R) |
|                                                                       |
|    1-6 I2C Device ID bit2-7 (always 34h, aka D0h/4 or D2h/4)      (R) |
|                                                                       |
|    7   Reserved ("Hard coded to 0")                               (R) |
+-----------------------------------------------------------------------+
```

The device address D0h or D2h can be selected via AD0 pin (the AD0 pin
is not reflected in this register). This register is read-only (unlike
as OLD_GYRO).

- **NEW_GYRO\[00h..0Dh\] - Reserved/Undocumented**
Reading these fourteen registers returns following weird values:

```
+-----------------------------------------------------------------------+
|       BD DB D1 29 9C 1D 20 67 F4 1A 8C 08 B1 71                       |
+-----------------------------------------------------------------------+
```

There should be 10bit temperature calibration values, but
9C1Dh,67F4h,8C08h exceed 10bit range.
The first two bytes (BDh,DBh) seem to resemble the 1st/2nd bytes of
older RS232 gyroscope protocols.



