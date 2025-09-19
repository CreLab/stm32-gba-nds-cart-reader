# DSi Atheros Wifi - Internal I/O - 00C000h - Serial UART (hw2/hw4/hw6)


The UART_xxx registers are used to output TTY messages (ASCII strings) when enabled in the \"Host Interest\" area:

```
+-------------------------------------------------------------------------------------+
|       LOCAL_SCRATCH[0].bit1 AR6K_OPTION_SERIAL_ENABLE --> TTY master enable         |
|       targaddr[14h] hi_serial_enable --> enable additional TTY msg's during BMI     |
|       targaddr[60h] hi_desired_baud_rate --> for TTY/UART (default=9600 decimal)    |
|       targaddr[C4h] hi_console_flags - whatever, UART related, maybe newer firmware |
+-------------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      ______________________ hw2 UART Registers ______________________ |
+-----------------------------------------------------------------------+
```


### Texas Instruments TL16C550AN - Asynchronous Communications Element (ACE)
The hw2 UART is based on the TL16C550AN chip (which is also found in the SNES \"Exertainment Bicycle\" add-on).

### ATH:00C000h (when DLAB=0) - (WLAN_UART\_)RBR - RX Data FIFO (R) ;hw2
### ATH:00C020h (when DLAB=0) - (WLAN_UART\_)SRBR (mirror of RBR?) ;hw2

```
+-----------------------------------------------------------------------+
|       0-7  Data (with 16-byte FIFO)                                   |
+-----------------------------------------------------------------------+
```


### ATH:00C000h (when DLAB=0) - (WLAN_UART\_)THR - TX Data FIFO (W) ;hw2

```
+-----------------------------------------------------------------------+
|       0-7  Data (with 16-byte FIFO)                                   |
+-----------------------------------------------------------------------+
```


### ATH:00C004h (when DLAB=0) - (WLAN_UART\_)IER - Interrupt Control (R/W) ;hw2

```
+-------------------------------------------------------------------------------------+
|       0    ERBFI Received Data Available Interrupt            (0=Disable, 1=Enable) |
|       1    ETBEI Transmitter Holding Register Empty Interrupt (0=Disable, 1=Enable) |
|       2    ELSI  Receiver Line Status Interrupt               (0=Disable, 1=Enable) |
|       3    EDDSI Modem Status Interrupt                       (0=Disable, 1=Enable) |
|       4-7  -     Not used (always zero)                                             |
+-------------------------------------------------------------------------------------+
```


### ATH:00C000h (when DLAB=1) - (WLAN_UART\_)DLL - Baudrate Divisor LSB (R/W) ;hw2
### ATH:00C004h (when DLAB=1) - (WLAN_UART\_)DLH - Baudrate Divisor MSB (R/W) ;hw2

```
+------------------------------------------------------------------------------------+
|       0-7  Divisor Latch LSB/MSB, should be set to "divisor = XIN / (baudrate*16)" |
+------------------------------------------------------------------------------------+
```


### ATH:00C008h - (WLAN_UART\_)IIR - Interrupt Status (R) ;hw2
### ATH:00C028h - (WLAN_UART\_)SIIR (mirror or IIR?) ;hw2

```
+-----------------------------------------------------------------------------------+
|       0    Interrupt Pending Flag (0=Pending, 1=None)                       ;\IID 
|       1-3  Interrupt ID, 3bit     (0..7=see below) (always 00h when Bit0=1) ;/    |
|       4-5  Not used (always zero)                                                 |
|       6    FIFOs Enabled (always zero in TL16C450 mode) ;\these bits have same    
|       7    FIFOs Enabled (always zero in TL16C450 mode) ;/value as "FIFO Enable"  |
+-----------------------------------------------------------------------------------+
```

The 3bit Interrupt ID can have following values:

```
+------------------------------------------------------------------------------------+
|       ID Prio Expl.                                                                |
|       00h 4   Handshaking inputs CTS,DSR,RI,DCD have changed      (Ack: Read MSR)  |
|       01h 3   Transmitter Holding Register Empty     (Ack: Write THR or Read IIR)  |
|       02h 2   RX FIFO has reached selected trigger level          (Ack: Read RBR)  |
|       03h 1   RX Overrun/Parity/Framing Error, or Break Interrupt (Ack: Read LSR)  |
|       06h 2   RX FIFO non-empty & wasn't processed for longer time(Ack: Read RBRh) |
+------------------------------------------------------------------------------------+
```

Interrupt ID values 04h,05h,07h are not used.

### ATH:00C008h - (WLAN_UART\_)FCR - FIFO Control (W) ;hw2

```
+------------------------------------------------------------------------------------+
|       0    FIFO Enable (0=Disable, 1=Enable) (Enables access to FIFO related bits) |
|       1    Receiver FIFO Reset      (0=No Change, 1=Clear RX FIFO) (RCVR_FIFO_RST) |
|       2    Transmitter FIFO Reset   (0=No Change, 1=Clear TX FIFO) (XMIT_FIFO_RST) |
|       3    DMA Mode Select (Mode for /RXRDY and /TXRDY) (0=Mode 0, 1=Mode 1)       |
|       4-5  Not used (should be zero)                                               |
|       6-7  Receiver FIFO Trigger    (0..3 = 1,4,8,14 bytes) (RCVR_TRIG)            |
+------------------------------------------------------------------------------------+
```


### ATH:00C00Ch - (WLAN_UART\_)LCR - Character Format Control (R/W) ;hw2

```
+-------------------------------------------------------------------------------------+
|       0-1  Character Word Length    (0..3 = 5,6,7,8 bits) (CLS)                     |
|       2    Number of Stop Bits      (0=1bit, 1=2bit; for 5bit chars: only 1.5bit)   |
|       3    Parity Enable (PEN)      (0=None, 1=Enable Parity or 9th data bit)       |
|       4    Parity Type/9th Data bit (0=Odd, 1=Even) (EPS)                           |
|       5    Unused in hw2? ;for TL16C550AN: Bit4-5 can be 2=Set9thBit, 3=Clear9thBit |
|       6    Set Break                (0=Normal, 1=Break, Force SOUT to Low)          |
|       7    Divisor Latch Access     (0=Normal I/O, 1=Divisor Latch I/O) (DLAB)      |
+-------------------------------------------------------------------------------------+
```


### ATH:00C010h - (WLAN_UART\_)MCR - Handshaking Control (R/W) ;hw2

```
+----------------------------------------------------------------------------------+
|       0    DTR  Output Level for /DTR pin  (Data Terminal Ready) (0=High, 1=Low) |
|       1    RTS  Output Level for /RTS pin  (Request to Send)     (0=High, 1=Low) |
|       2    OUT1 Output Level for /OUT1 pin (General Purpose)     (0=High, 1=Low) |
|       3    OUT2 Output Level for /OUT2 pin (General Purpose)     (0=High, 1=Low) |
|       4/5? LOOP Loopback Mode (0=Normal, 1=Testmode, loopback TX to RX)          |
|       5-7  Not used (always zero)                                                |
+----------------------------------------------------------------------------------+
```

The Loopback bit should be Bit4 (according to TL16C550AN datasheet), but hw2 source code claims it to be in bit5.

### ATH:00C014h - (WLAN_UART\_)LSR - RX/TX Status (R) (W=don\'t do) ;hw2
### ATH:00C034h - (WLAN_UART\_)SLSR (mirror of LSR?) ;hw2

```
+-------------------------------------------------------------------------------------+
|       0    RX Data Ready (DR)       (0=RX FIFO Empty, 1=RX Data Available)          |
|       1    RX Overrun Error (OE)    (0=Okay, 1=Error) (RX when RX FIFO Full)        |
|       2    RX Parity Error (PE)     (0=Okay, 1=Error) (RX parity bad)               |
|       3    RX Framing Error (FE)    (0=Okay, 1=Error) (RX stop bit bad)             |
|       4    RX Break Interrupt (BI)  (0=Normal, 1=Break) (RX line LOW for long time) |
|       5    Transmitter Holding Register (THRE) (1=TX FIFO is empty)                 |
|       6    Transmitter Empty (TEMT) (0=No, 1=Yes, TX FIFO and TX Shift both empty)  |
|       7    At least one Overrun/Parity/Framing Error in RX FIFO (0=No, 1=Yes/Error) |
+-------------------------------------------------------------------------------------+
```

Bit7 is always zero in TL16C450 mode. Bit1-3 are automatically cleared after reading. In FIFO mode, bit2-3 reflect to status of the current (=oldest) character in the FIFO (unknown/unclear if bit2-3 are also auto-cleared when in FIFO mode).
Note: The AR6002 BIOS ROM is using \"SLSR\" (instead of \"LSR\") for testing bit0,5,6. And, before each read from SLSR register, the AR6002 BIOS BIOS does first write 0 to SLSR (for whatever unknown purpose).
Basically, \"SLSR\" (and other \"Sxxx\" registers) seems to be some sort of a mirror of \"LSR\" (and other \"xxx\" registers)? Maybe one of them omits automatic IRQ acknowledge or so?

### ATH:00C018h - (WLAN_UART\_)MSR - Handshaking Status (R) (W=don\'t do) ;hw2
### ATH:00C038h - (WLAN_UART\_)SMSR (mirror or MSR?) ;hw2

```
+-------------------------------------------------------------------------------------+
|       0    DCTS Change flag for /CTS pin ;ClearToSend       ;\change flags (0=none, 
|       1    DDSR Change flag for /DSR pin ;DataSetReady      ; 1=changed since last  |
|       2    TERI Change flag for /RI pin  ;RingIndicator     ; read) (automatically  |
|       3    DDCD Change flag for /DCD pin ;DataCarrierDetect ;/cleared after read)   |
|       4    CTS  Input Level on /CTS pin ;ClearToSend        ;\                      
|       5    DSR  Input Level on /DSR pin ;DataSetReady       ; current levels        |
|       6    RI   Input Level on /RI pin  ;RingIndicator      ; (inverted ?)          |
|       7    DCD  Input Level on /DCD pin ;DataCarrierDetect  ;/                      |
+-------------------------------------------------------------------------------------+
```


### ATH:00C01Ch - (WLAN_UART\_)SCR - Scratch (R/W) ;hw2

```
+----------------------------------------------------------------------------------+
|       0-7  General Purpose Storage (eg. read/write-able for UART chip detection) |
+----------------------------------------------------------------------------------+
```


### ATH:00C02Ch - (WLAN_UART\_?)MWR ;whatever \"M Write Register?\" ;hw2
### ATH:00C03Ch - (WLAN_UART\_?)MRR ;whatever \"M Read Register?\" ;hw2

```
+-------------------------------------------------------------------------------------+
|       0-31 whatever... 32bit wide (unlike other UART registers) (?) (UART related?) |
+-------------------------------------------------------------------------------------+
```



```
+---------------------------------------------------------------------------+
|      ______________________ hw4/hw6 UART Registers ______________________ |
+---------------------------------------------------------------------------+
```


### Multiple UARTs ;hw4/hw6
There appear to be multiple hw4/hw6 UARTs: one normal, one for debug, one for hw6:

```
+-----------------------------------------------------------------------+
|       WLAN_UART_BASE_ADDRESS     = 0000C000h ;hw4/hw6                 |
|       WLAN_DBG_UART_BASE_ADDRESS = 0000D000h ;hw4/hw6                 |
|       WLAN_UART2_BASE_ADDRESS    = 00054C00h ;hw6                     |
+-----------------------------------------------------------------------+
```

Maybe the UARTs are all using the same register format with differerent base?

### ATH:00C000h - UART_DATA ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-7    TXRX_DATA                                                |
|       8      RX_CSR                                                   |
|       9      TX_CSR                                                   |
+-----------------------------------------------------------------------+
```


### ATH:00C004h - UART_CONTROL ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      PARITY_EVEN                                              |
|       1      PARITY_ENABLE                                            |
|       2      IFC_DCE                                                  |
|       3      IFC_ENABLE                                               |
|       4      FLOW_INVERT                                              |
|       5      FLOW_ENABLE                                              |
|       6      DMA_ENABLE                                               |
|       7      RX_READY_ORIDE                                           |
|       8      TX_READY_ORIDE                                           |
|       9      SERIAL_TX_READY                                          |
|       10     RX_BREAK                                                 |
|       11     TX_BREAK                                                 |
|       12     HOST_INT                                                 |
|       13     HOST_INT_ENABLE                                          |
|       14     TX_BUSY                                                  |
|       15     RX_BUSY                                                  |
+-----------------------------------------------------------------------+
```


### ATH:00C008h - UART_CLKDIV ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0-15   CLK_STEP                                                 |
|       16-23  CLK_SCALE                                                |
+-----------------------------------------------------------------------+
```


### ATH:00C00Ch - UART_INT ;hw4/hw6
### ATH:00C010h - UART_INT_EN ;hw4/hw6

```
+-----------------------------------------------------------------------+
|       0      RX_VALID_INT                                             |
|       1      TX_READY_INT                                             |
|       2      RX_FRAMING_ERR_INT                                       |
|       3      RX_OFLOW_ERR_INT                                         |
|       4      TX_OFLOW_ERR_INT                                         |
|       5      RX_PARITY_ERR_INT                                        |
|       6      RX_BREAK_ON_INT                                          |
|       7      RX_BREAK_OFF_INT                                         |
|       8      RX_FULL_INT                                              |
|       9      TX_EMPTY_INT                                             |
+-----------------------------------------------------------------------+
```




