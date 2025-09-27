# DSi Atheros Wifi - SDIO Function 1 I/O - mbox_wlan_host_reg


Differences between hw2 versus hw4/hw6 (hw4 and hw6 are exactly same):

```
+-----------------------------------------------------------------------+
|       added several new "GMBOX" registers (hw4/hw6)                   |
|       added new CPU_DBG registers (hw4/hw6)                           |
|       added three new "UART_HCI_FRAMER_xxx" error bits (hw4/hw6)      |
|       renamed "DRAGON_INT" (hw2) to "INT" (hw4/hw6)                   |
|       renamed "SPI_xxx" (hw2) to "HOST_CTRL_SPI_xxx" (hw4/hw6)        |
+-----------------------------------------------------------------------+
```


### 1:00000h..000FFh - Mbox0 (100h bytes)
### 1:00100h..001FFh - Mbox1 (100h bytes)
### 1:00200h..002FFh - Mbox2 (100h bytes)
### 1:00300h..003FFh - Mbox3 (100h bytes)
### 1:00800h..00FFFh - Mbox0 Alias (bigger 800h bytes alias)
### 1:01000h..017FFh - Mbox1 Alias (bigger 800h bytes alias)
### 1:01800h..01FFFh - Mbox2 Alias (bigger 800h bytes alias)
### 1:02000h..027FFh - Mbox3 Alias (bigger 800h bytes alias)
### 1:02800h..03FFFh - Extra Mbox0 Alias \"for future usage\" (1800h bytes)
The MBOXes are some sort of FIFOs for transferring data blocks to/from wifi controller. Transfer end seems to be indicated by reading/writing the LAST byte (eg. when sending 4 bytes via Mbox0, data would be usually written to increasing addresses at 1:000FCh..000FFh, or 1:00FFCh..00FFFh when using the bigger Mbox alias) (technically, those addresses are just mirrors of each other, so one could as well write all bytes to the same address, or to random addresses at 1:00000h..000FFh and/or 1:00800h..00FFFh in no specific order; the only special case is that the last byte at 1:000FFh/1:00FFFh seems to be triggering something\... like maybe throwing an IRQ at remote side or so).
In total, there appear to be eight MBOXes for SDIO: Four TXFIFOs (from SDIO to Xtensa side), plus four RXFIFOs (from Xtensa to SDIO side). The capacity of the FIFOs is unknown; the 800h-byte spaces would suggest 800h bytes, but the firmware uploader seems to use only max 200h bytes for whatever reason. Hardware tests suggest only 80h bytes MBOX1-3 TXFIFOs, and 8Ah or 3CD0h bytes for MBOX0 TXFIFO (8Ah when writing LAST bytes, 3CD0h otherwise); that results may be disturbed by the firmware trying to process incoming data.
Reading from EMPTY FIFO keeps returning the most recently read value (the last byte before the FIFO got empty).
Writes to FULL FIFO\... results are unknown\... maybe ignored, and/or producing TIMEOUTs?

### 1:00400h - HOST_INT_STATUS (R)
### 1:00418h - (HOST\_)INT_STATUS_ENABLE (R/W)
Status.read: 0=No IRQ, 1=IRQ
Enable.read/write: 0=Disable, 1=Enable

```
+--------------------------------------------------------------------------------+
|       0-3    MBOX_DATA  MBOX0..3 Data pending (RX FIFO not empty)              |
|       4      COUNTER    Secondary IRQ from COUNTER_INT_STATUS                  |
|       5      INT        Copy of internal CPU's interrupt line (aka DRAGON_INT) |
|       6      CPU        Secondary IRQ from CPU_INT_STATUS                      |
|       7      ERROR      Secondary IRQ from ERROR_INT_STATUS                    |
+--------------------------------------------------------------------------------+
```

The status register is read-only (to reset the status bits: read/reset the corresponding MBOXes, or acknowledge the corresponding Secondary IRQ sources).

### 1:00401h - CPU_INT_STATUS (R/W)
### 1:00419h - CPU_INT_STATUS_ENABLE (R/W)
Status.read: 0=No IRQ, 1=IRQ
Status.write: 0=No change, 1=Acknowledge
Enable.read/write: 0=Disable, 1=Enable

```
+-----------------------------------------------------------------------+
|       0-7    BIT        Interrupt 0..7 from internal CPU              |
+-----------------------------------------------------------------------+
```

These bits are eight general purpose IRQ signals from the internal CPU (the meaning of the bits depends on software/firmware) (see WLAN_INT_HOST).

### 1:00402h - ERROR_INT_STATUS (R/W)
### 1:0041Ah - ERROR\_(INT\_)STATUS_ENABLE (R/W)
Status.read: 0=No IRQ, 1=IRQ
Status.write: 0=No change, 1=Acknowledge (except bit3)
Enable.read/write: 0=Disable, 1=Enable (except bit3)

```
+----------------------------------------------------------------------------+
|       0      TX_OVERFLOW  (host tried to write to a full MBOX)             |
|       1      RX_UNDERFLOW (host tried to read from an empty MBOX)          |
|       2      WAKEUP (client has entered ON-state)                          |
|       3      SPI Error Interrupt   ;STATUS only (not STATUS_ENABLE)  (R)   |
|       4      hw4/hw6: UART_HCI_FRAMER_UNDERFLOW             ;\             
|       5      hw4/hw6: UART_HCI_FRAMER_OVERFLOW              ; hw4/hw6 only |
|       6      hw4/hw6: UART_HCI_FRAMER_SYNC_ERROR            ;/             |
|       7      -                                                             |
+----------------------------------------------------------------------------+
```

Bit3 can be acknowledged or disabled only via SPI-specific registers from SPI host (that is, probably referring to the HOST_CTRL_SPI_CONFIG and HOST_CTRL_SPI_STATUS registers).

### 1:00403h - COUNTER_INT_STATUS (R)
### 1:0041Bh - COUNTER_INT_STATUS_ENABLE (R/W)
Status.read: 0=No IRQ, 1=IRQ
Enable.read/write: 0=Disable, 1=Enable

```
+-----------------------------------------------------------------------+
|       0-7    COUNT[0..7] is nonzero                                   |
+-----------------------------------------------------------------------+
```

The status register is read-only (to reset the status bits: decrease the COUNT values via COUNT_DEC\[0..7\]) (unknown if directly writing to COUNT\[0..7\] does also affect the interrupt bits; probably it does, although official specs suggests that only 00h \<\--\> 01h transitions affect IRQ bits).

### 1:00406h - HOST_INT_STATUS2 - hw4/hw6 only
### 1:00488h - (HOST\_)INT_STATUS2_ENABLE (R/W) - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0      hw4/hw6: GMBOX_DATA                            ;\             
|       1      hw4/hw6: GMBOX_TX_OVERFLOW                     ; hw4/hw6 only |
|       2      hw4/hw6: GMBOX_RX_UNDERFLOW                    ;/             |
|       3-7    -                                                             |
+----------------------------------------------------------------------------+
```


### 1:00404h - MBOX_FRAME (R)

```
+---------------------------------------------------------------------------------+
|       0-3    MBOX0..3 contains a SOM (start of message) byte in RX FIFO (1=Yes) |
|       4-7    MBOX0..3 contains a EOM (end of message) byte in RX FIFO   (1=Yes) |
+---------------------------------------------------------------------------------+
```

Note: A SOM byte always follows an EOM byte from the previous message.

### 1:00405h - RX_LOOKAHEAD_VALID (R)

```
+-----------------------------------------------------------------------+
|       0-3    MBOX0..3 contains at least 4 bytes in RX FIFO (1=Yes)    |
|       4-7    -                                                        |
+-----------------------------------------------------------------------+
```


### 1:00407h - GMBOX_RX_AVAIL - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0-6    hw4/hw6: BYTE                                  ;-hw4/hw6 only |
|       7      -                                                             |
+----------------------------------------------------------------------------+
```

uh, a \"7bit-byte\"? \... or maybe \"number of bytes\"?

### 1:00408h..0040Bh - RX_LOOKAHEAD0\[0..3\] (R)
### 1:0040Ch..0040Fh - RX_LOOKAHEAD1\[0..3\] (R)
### 1:00410h..00413h - RX_LOOKAHEAD2\[0..3\] (R)
### 1:00414h..00417h - RX_LOOKAHEAD3\[0..3\] (R)

```
+-----------------------------------------------------------------------+
|       0-7    MBOX RX FIFO Head-3 byte   ;\what is that?               
|       8-15   MBOX RX FIFO Head-2 byte   ; head "minus" N, or maybe    |
|       16-23  MBOX RX FIFO Head-1 byte   ;/head "plus index" N?        |
|       24-31  MBOX RX FIFO Head byte                                   |
+-----------------------------------------------------------------------+
```

Allows to preview the first 1..4 byte(s) from MBOX0..3, without removing the data from the FIFO. The first byte is valid when HOST_INT_STATUS indicates FIFO not empty. The first four bytes are valid when RX_LOOKAHEAD_VALID indicates at least 4 bytes in FIFO.

### 1:00420h..00427h - COUNT\[0..7\] (R/W)
This are eight 8bit counter registers for communicating with internal CPU (see LOCAL_COUNT and COUNT_INC in internal I/O map).

```
+-----------------------------------------------------------------------+
|       0-7    Credit Counter Value                                     |
+-----------------------------------------------------------------------+
```


### 1:00440h..0045Fh - COUNT_DEC\[0..7\] (R, or Write=any)
This are eight 32bit registers. Reading or writing the LSB of the 32bit values does decrement the correspondig COUNT register by one. The written value is ignored, reading returns the old COUNT value (before decrement). The decrement doesn\'t occur if the COUNT is already zero. The corresponding IRQ bit is cleared when COUNT becomes zero.

```
+-----------------------------------------------------------------------+
|       0-7    Credit Counter Value                                     |
|       8-31   Zero? (dummy padding for 32bit access)                   |
+-----------------------------------------------------------------------+
```


### 1:00460h..00467h - SCRATCH\[0..7\] (R/W)
This are eight 8bit general-purpose registers for communicating with internal CPU (see LOCAL_SCRATCH in internal I/O map).

```
+-----------------------------------------------------------------------+
|       0-7    General Purpose Value                                    |
+-----------------------------------------------------------------------+
```


### 1:00468h - FIFO_TIMEOUT (R/W)
Timeout (SDIO Wait duration) for cases when reading from empty MBOXes or writing to full MBOXes. On AR6001, timeout is counted in 1ms units (when CORE_CLK=40MHz) or 0.5ms units (when CORE_CLK=80MHz). Timings for AR6002 are probably same/similar?

```
+-----------------------------------------------------------------------+
|       0-7    Timeout (01h..FFh) (00h=Reserved/don't use)              |
+-----------------------------------------------------------------------+
```


### 1:00469h - FIFO_TIMEOUT_ENABLE (R/W)

```
+-----------------------------------------------------------------------+
|       0      Enable FIFO Timeouts (0=Disable, 1=Enable)               |
|       1-7    -                                                        |
+-----------------------------------------------------------------------+
```


### 1:0046Ah - DISABLE_SLEEP (R/W)

```
+-----------------------------------------------------------------------------------+
|       0      Prevent Sleep                       (0=Allow Sleep, 1=Prevent Sleep) |
|       1      Prevent Sleep when Host IRQ pending (0=Allow Sleep, 1=Prevent Sleep) |
|       2-7    -                                                                    |
+-----------------------------------------------------------------------------------+
```


### 1:0046Eh - LOCAL_BUS_ENDIAN (R/W) (AR6001 only, not hw2/hw4/hw6)

```
+-------------------------------------------------------------------------------+
|       0      AR6001 only: (0=Little Endian, 1=Big Endian)   ;-not hw2/hw4/hw6 |
|       1-7    -                                                                |
+-------------------------------------------------------------------------------+
```


### 1:00470h - LOCAL_BUS (R and R/W)

```
+-------------------------------------------------------------------------------+
|       0-1    Current Chip State (0=Shutdown, 1=On, 2=Sleep, 3=Wakeup) (R)     |
|       2      AR6001 only: KEEP_AWAKE (R/W)                  ;\                
|       3      AR6001 only: IO_ENABLE  (R/W)                  ; not hw2/hw4/hw6 |
|       4      AR6001 only: SOFT_RESET (R/W)                  ;/                |
|       5-7    -                                                                |
+-------------------------------------------------------------------------------+
```


### 1:00472h - INT_WLAN (R/W)

```
+-----------------------------------------------------------------------+
|       0-7    "VECTOR" or interrupt 0..7 ?  (0=No change, 1=Set)       |
+-----------------------------------------------------------------------+
```

Sends IRQs to internal CPU (see WLAN_MBOX_INT_STATUS bit0-7).

### 1:00474h..00477h - WINDOW_DATA

```
+-----------------------------------------------------------------------+
|       0-31   DATA                                                     |
+-----------------------------------------------------------------------+
```

Used to access the internal Xtensa memory space. The actual memory access occurs when writing the WINDOW_xxx_ADDR registers (see below).

### 1:00478h..0047Bh - WINDOW_WRITE_ADDR (W) (read: crashes hardware?)
### 1:0047Ch..0047Fh - WINDOW_READ_ADDR (W) (read: crashes hardware?)

```
+-----------------------------------------------------------------------+
|       0-1    Ignored                                                  |
|       2-27   ADDR (in 4-byte steps)                                   |
|       28-31  ?                                                        |
+-----------------------------------------------------------------------+
```

Writing an address to these registers causes 32bit data to be transferred to/from WINDOW_DATA register.

```
+---------------------------------------------------------------------------------+
|       For a memory write: First write WINDOW_DATA, then write WINDOW_WRITE_ADDR |
|       For a memory read: First write WINDOW_READ_ADDR, then read WINDOW_DATA    |
+---------------------------------------------------------------------------------+
```

The memory transfers seem to occur on writing address LSB (ie. one must first write the upper three ADDR bytes, then write the lower ADDR byte; that requires sending two separate SDIO commands, except, for accesses within the same 100h-byte block, one may get away with a single SDIO command for changing the LSB only, and leaving the MSBs unchanged).
Caution: Trying to read the ADDR registers seems to be somehow crashing the SDIO hardware (causing errors when trying to send any further SDIO commands).

### 1:00480h - HOST_CTRL_SPI_CONFIG (R/W)
This register can be accessed only via SPI interface.

```
+-------------------------------------------------------------------------------------+
|       0-1    DATA_SIZE (0=8bit, 1=16bit, 2=32bit, 3=Reserved) (addr = always 16bit) |
|       2      TEST_MODE (0=Normal, 1=Loopback/Echo)                                  |
|       3      INTERRUPT_ENABLE (0=Disable, 1=Enable)                                 |
|       4      SPI_RESET (0=Normal Operation, 1=Reset SPI core)                       |
|       5      AR6001 only, not AR6002? - SPI_CLK_OFFSET (R)                          |
|       6      -                                                                      |
|       7      AR6001 only, not AR6002? - ENDIAN (R/W)                                |
+-------------------------------------------------------------------------------------+
```


### 1:00481h - HOST_CTRL_SPI_STATUS (R/W)
This register is automatically output on SPI bus after completion of SPI data transfers.

```
+-------------------------------------------------------------------------------------+
|       0      READY    (0=Command Pending, 1=Completed/Ready)                (R)     |
|       1      WR_ERR   (0=Okay, 1=Write-Error)  (write: 0=No change, 1=Ack)  (R/ack) |
|       2      RD_ERR   (0=Okay, 1=Read-Error)   (write: 0=No change, 1=Ack)  (R/ack) |
|       3      ADDR_ERR (0=Okay, 1=Addr-Error)   (write: 0=No change?, 1=Ack?)        |
|       4      AR6001 only, not AR6002? - IFF_ERR                                     |
|       5      AR6001 only, not AR6002? - DMA_OVER                                    |
|       6-7    -                                                                      |
+-------------------------------------------------------------------------------------+
```


### 1:00482h - NON_ASSOC_SLEEP_EN ;hw2/hw4/hw6 (but didn\'t exist on AR6001)

```
+-----------------------------------------------------------------------+
|       0      BIT                                                      |
|       1-7    -                                                        |
+-----------------------------------------------------------------------+
```


### 1:00483h - CPU_DBG_SEL - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0-5    BIT                                            ;-hw4/hw6 only |
|       6-7    -                                                             |
+----------------------------------------------------------------------------+
```


### 1:00484h..00487h - CPU_DBG\[0..3\] - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0-7    DATA                                           ;-hw4/hw6 only |
+----------------------------------------------------------------------------+
```


### 1:00490h..00497h - GMBOX_RX_LOOKAHEAD\[0..7\] - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0-7    DATA                                           ;-hw4/hw6 only |
+----------------------------------------------------------------------------+
```


### 1:00498h - GMBOX_RX_LOOKAHEAD_MUX - hw4/hw6 only

```
+----------------------------------------------------------------------------+
|       0      SEL                                            ;-hw4/hw6 only |
|       1-7    -                                                             |
+----------------------------------------------------------------------------+
```


### 1:00600h..007FFh - CIS_WINDOW\[0..511\] (R/W?!)

```
+-----------------------------------------------------------------------+
|       0-7    DATA                                                     |
+-----------------------------------------------------------------------+
```




