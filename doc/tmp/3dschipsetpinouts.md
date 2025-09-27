# 3DS Chipset Pinouts


### New Gyroscope (ITG-1010) (used in New 3DS XL)

```
+-------------------------------------------------------------------------------+
|       1    VDDIO    Digital I/O supply voltage                                |
|       2    SCL/SCLK I2C serial clock (SCL); SPI serial clock (SCLK)           |
|       3    SDA/SDI  I2C serial data (SDA); SPI serial data input (SDI)        |
|       4    AD0/SDO  I2C Slave Address LSB (AD0); SPI serial data output (SDO) |
|       5    /CS      SPI chip select (Low=SPI mode, High=I2C mode)             |
|       6    RESV     Reserved. Connect to Ground                               |
|       7    INT      Interrupt digital output (totem pole or open-drain)       |
|       8    FSYNC    Frame synchronization digital input (or GND=unused)       |
|       9-12 NC       Not connected (may be used for PCB trace routing)         |
|       13   GND      Power supply ground                                       |
|       14   REGOUT   Regulator filter capacitor connection                     |
|       15   RESV-G   Reserved. Connect to Ground                               |
|       16   VDD      Power supply voltage                                      |
+-------------------------------------------------------------------------------+
```


### Old Gyroscope (ITG-3270) (used in Old 3DS)

```
+-------------------------------------------------------------------------------------+
|       1     CLKIN   Optional external ref clock input (or GND=unused)   GND         |
|       2-5   NC      Not connected (may be used for PCB trace routing)   -           |
|       6-7   RESV    Reserved. Do not connect                            -           |
|       8     VLOGIC  Digital IO voltage (must be <= VDD at all times)    TP254=?     |
|       9     AD0     I2C Slave Address LSB                               GND         |
|       10    REGOUT  Regulator filter capacitor connection               C71         |
|       11    RESV-G  Reserved - Connect to ground                        GND         |
|       12    INT     Interrupt digital output (totem pole or open-drain) TP158=IRQ   |
|       13    VDD     Power supply voltage                                TP3=VDD3.3V |
|       14-17 NC      Not (connected, may be used for PCB trace routing)  -           |
|       18    GND     Power supply ground                                 GND         |
|       19    RESV    Reserved. Do not connect                            -           |
|       20    CPOUT   Charge pump capacitor connection                    C73         |
|       21-22 RESV    Reserved. Do not connect                            -           |
|       23    SCL     I2C serial clock                                    TP144=SCL   |
|       24    SDA     I2C serial data                                     TP146=SDA   |
+-------------------------------------------------------------------------------------+
```

Note: Pinout is from ITG-3200 datasheet (which seems same as ITG-3270) (the right column shows GND/TP wiring in Old3DS).

### Accelerometer (LIS331DLH)

```
+------------------------------------------------------------------------------------+
|       1  VDD_IO      Power supply for I/O pins                          TP240=1.8V |
|       2  NC          Not connected                                      -          |
|       3  NC          Not connected                                      -          |
|       4  SCL,SPC     I2C.clock (or SPI.clock)                           TP34=SCL   |
|       5  GND         0V supply                                          GND        |
|       6  SDA,SDI,SDO I2C.data (or SPI.data.in, or 3-wire.data.out)      TP33=SDA   |
|       7  SA0,SDO     I2C.device.id (or SPI.data.out)                    CL1=GNDed  |
|       8  CS          Mode (high=I2C, low=SPI)                           TP240=1.8V |
|       9  INT2        Inertial interrupt 2                               TP54       |
|       10 Reserved    Connect to GND                                     GND        |
|       11 INT1        Inertial interrupt 1                               TP53       |
|       12 GND         0V supply                                          GND        |
|       13 GND         0V supply                                          GND        |
|       14 VDD         Power supply                                       D7-to-TP3  |
|       15 Reserved    Connect to VDD                                     D7-to-TP3  |
|       16 GND         0V supply                                          GND        |
+------------------------------------------------------------------------------------+
```


### Hall-Effect Switch (magnet sensor for sensing shell closed)
Texas Instruments DRV5032 (or the like). The sensor is near A/B buttons, triggered by right speaker.

```
+-----------------------------------------------------------------------+
|       1  VCC         Supply         (TP5 Supply 1.8V in 3DS)          |
|       2  VOUT        Signal Output  (TP126 in 3DS)                    |
|       3  GND         Ground                                           |
+-----------------------------------------------------------------------+
```


### IrDA Chip (NXP SC16IS750, 24pin HVQFN24 package)

```
+-----------------------------------------------------------------------+
|       1  I  /RESET     Reset (not used in 3DS, wired to VDD)          |
|       2  I  XTAL1      Crystal input, or external clock input         |
|       3  O  XTAL2      Crystal output, or clock output                |
|       4  -  VDD        Supply                                         |
|       5  I  I2C,/SPI   Interface mode select                          |
|       6  I  /CS,A0     SPI chip select, or I2C device id              |
|       7  I  SI,A1      SPI data in, or I2C device id                  |
|       8  O  SO         SPI data out                                   |
|       9  I  SCL,SCLK   SPI clk, or I2C clk                            |
|       10 IO SDA        I2C data                                       |
|       11 O  /IRQ       Interrupt                                      |
|       12 IO GPIO0      I/O (in 3DS: wired to transceiver PWDOWN pin)  |
|       13 IO GPIO1      I/O                                            |
|       14 IO GPIO2      I/O                                            |
|       15 IO GPIO3      I/O                                            |
|       16 -  Vss        GND                                            |
|       17 IO GPIO4,/DSR I/O, or modem data set ready                   |
|       18 IO GPIO5,/DTR I/O, or modem data terminal ready              |
|       19 IO GPIO6,/CD  I/O, or modem carrier detect                   |
|       20 IO GPIO7,/RI  I/O, or modem ring indicator                   |
|       21 O  /RTS       UART request to send                           |
|       22 I  /CTS       UART clear to send                             |
|       23 O  TX         UART data out (aka IrDA transmit signal)       |
|       24 I  RX         UART data in  (aka IrDA receive signal)        |
+-----------------------------------------------------------------------+
```


### IrDA Transceiver \"841\" (seems to be RPM841-H16 or similar)

```
+-----------------------------------------------------------------------------------+
|       1     LEDA   Transmit supply, can be always on, can be VCC or other supply  |
|       2     TX-RC  Remote Control Transmit, more strength than TXD   (high=light) |
|       3  I  TXD    IrDA Transmit, with less strength than TX-RC      (high=light) |
|       4  O  RXD    IrDA Receive, can be also polled manually         (low=light)  |
|       5     PWDOWN Power down, affects only RXD receive        (high=disable RXD) |
|       6     VCC    Digital supply, for logic gates and receive                    |
|       7     GND    Ground                                                         |
|       SHLD  GND    Shield (intended to reduce EMI noise)                          |
+-----------------------------------------------------------------------------------+
```


### NFC (Broadcom BCM2079x)
Caution: below is for 34pin BCM20793S (which is NOT used in New3DS)
Caution: actual New3DS uses 32pin BCM20791 (maybe similar, but has only 32pin)
The pinout difference might be as simple as omitting the two N/C pins, or some of the four EEPROM/VDD_EE pins\...?

```
+-------------------------------------------------------------------------------------+
|       1  VDDSWP_IN     Platform UICC supply in                                      |
|       2  VDDSWP_OUT0   UICC supply out                                              |
|       3  SWPIO_0       SWP I/O 0                                                    |
|       4  SWPIO_1       SWP I/O 1                                                    |
|       5  VDDSWP_OUT1   Supply to embedded secure element                            |
|       6  VDD_ADC       Decoupling, need linking to VDDC_CAP via target PCB          |
|       7  NFC_WAKE      Signal from host to the BCM20793S                            |
|       8  TM2           ATE test mode (grounded for normal operation)                |
|       9  VDD_EEPROM_IN 1.8V power input to the co-packaged EEPROM (get from VDD_EE) |
|       10 HOST_WAKE     Interrupt signal from the BCM20793S to host                  |
|       11 CLK_REQ       Clock request                                                |
|       12 UART_TXD      UART transmit       ;or BSC/I2C_SDA, or SPI_MOSI             |
|       13 VDDIO         I/O supply; externally regulated                             |
|       14 UART_RTS_N    UART ready to send  ;or BSC/I2C_SCL, or SPI_MISO             |
|       15 SPI_INT       Host interface select (Low=UART, High=BSC/I2C, NC=SPI+IRQ)   |
|       16 UART_CTS_N    UART clear to send  ;or BSC/I2C_REQ(?), or SPI_CS            |
|       17 UART_RXD      UART receive        ;or SPI_CLK                              |
|       18 N/C           No connect                                                   |
|       19 XTAL_XON      Crystal N                                                    |
|       20 XTAL_XOP      Crystal P/clock reference input                              |
|       21 VDD_XTAL      Decoupling, need linking to VDDC_CAP via target PCB          |
|       22 LPO           Frequency selection, strap high or low (see page 45)         |
|       23 VDD_VCO       Decoupling, need linking to VDDC_CAP via target PCB          |
|       24 VDDC_CAP      Decoupling, links VDDADC, VDD_XTAL, VDD_VCO via target PCB   |
|       25 REG_PU        Regulator power control from host                            |
|       26 VBAT          Battery supply                                               |
|       27 VDDA_CAP      Analog LDO supply decoupling (1.88V/2.5V)                    |
|       28 TX2           Coil output 2                                                |
|       29 TX1           Coil output 1                                                |
|       30 VDD_ANT       Rectifier output, external cap                               |
|       31 N/C           Do not connect                                               |
|       32 VDD_EE        Output 1.8V supply voltage (to be linked to VDD_SE_IN)       |
|       33 SDA (eeprom)  BSC/I2C data internally connected to co-packaged EEPROM      |
|       34 SCL (eeprom)  BSC/I2C clock internally connected to co-packaged EEPROM     |
+-------------------------------------------------------------------------------------+
```

EEPROM: CAT24C64 EEPROM Die
Unknown if the EEPROM exists in New3DS, it might require REG_PU wake or so? Or the EEPROM is accessed INTERNALLY by the NFC chip (and the two EXTERNAL I2C/BSC EEPROM pins or meant to be used only optionally, for factory/init/test or so?) (that way the NFC could be also accessed via SPI/UART whilst internally talking to the I2C/BSC EEPROM).

### MAX17040 Fuel Gauge (used in Old3DS)

```
+-----------------------------------------------------------------------+
|       1 CTG   Connect to GND                ;Old3DS: GND              |
|       2 CELL  Battery Voltage Input         ;Old3DS: TP38             |
|       3 VDD   Power Supply                  ;Old3DS: TP39             |
|       4 GND   Ground                        ;Old3DS: GND              |
|       5 SEO   External 32kHz clock enable   ;Old3DS: GND              |
|       6 EO    External 32kHz clock          ;Old3DS: GND              |
|       7 SCL   I2C Clock                     ;Old3DS: TP34             |
|       8 SDA   I2C Data                      ;Old3DS: TP33             |
+-----------------------------------------------------------------------+
```


### MAX17048 Fuel Gauge (this, or something similar(?) is used in New3DS)

```
+-----------------------------------------------------------------------+
|        ______________________                                         |
|       |o                     |                                        |
|       |  CTG  CELL VDD  GND  |                                        |
|       |  SDA  SCL  QRST /ALRT|                                        |
|       |______________________|                                        |
+-----------------------------------------------------------------------+
```


### BQ24072 Charging IC (should match the \"CKP\" chip in Old3DS and New3DS XL)

```
+-------------------------------------------------------------------------------------+
|       1  TS     I   External NTC Thermistor (3DS: dummy R2 resistor?);10K-to-GND    |
|       2  BAT    I/O Battery (charge output, and battery sense input) ;TP259/F2/TP22 |
|       3  BAT    I/O Battery (charge output, and battery sense input) ;TP259/F2/TP22 |
|       4  /CE    I   Charge Enable                                    ;TP11          |
|       5  EN2    I                                                    ;10K-to-TP8    |
|       6  EN1    I                                                    ;GNDed         |
|       7  /PGOOD O   External Supply Power Good (open drain)          ;TP7           |
|       8  GND    -   Ground                                           ;GND           |
|       9  /CHG   O   Charging (open drain)                            ;TP10          |
|       10 OUT    O   Supply Output  ;\from BAT or IN to system        ;TP8           
|       11 OUT    O   Supply Output  ;/                                ;TP8           |
|       12 ILIM   I   Current Limit adjust (wire 1100..8000ohm to GND) ;1.96K-to-GND  |
|       13 IN     I   External Supply Input (4.35V..6.6V)              ;EM1/F1/TP4    |
|       14 TMR    I                                                    ;56K-to-GND    |
|       15 TD     I                                                    ;GNDed         |
|       16 ISET   I   Fast Charge Current (wire 590..8900ohm to GND)   ;1.5K-to-GND   |
+-------------------------------------------------------------------------------------+
```


### Whatever \"EPB\" (Maybe power on/off main cpu power supplies?) (Old3DS U12)
Voltage Supervisor with Reset? Voltage Regulator with adjust/enable?

```
+-----------------------------------------------------------------------+
|              .-----.                                                  |
|       TP5   -|1   6|- TP3        ;TP3=Supply +3.3V, TP5=Supply 1.8V   |
|       GND   -|2   5|- GND                                             |
|       TP245 -|3   4|- TP246      ;TP246=low 0V, and TP245=high 1.7V   |
|              '-----'                                                  |
+-----------------------------------------------------------------------+
```

Note: Upon Power on, TP246 carries a \"variable frequency clock signal\" for a moment, and then goes low.

### Microchip \"/\\\\ N5, 120\" - Audio voltage regulator (Old3DS U13)

```
+-----------------------------------------------------------------------+
|              .-----.                                                  |
|       TP12  -|1   6|- TP12      ;TP12 = 4.18V                         |
|       ?     -|2   5|- GND                                             |
|       TP258 -|3   4|- ?         ;TP258 = Speaker/Audio Supply 3.5V    |
|              '-----'                                                  |
+-----------------------------------------------------------------------+
```




