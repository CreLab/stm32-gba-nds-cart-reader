# DSi Atheros Wifi - Internal I/O - 018000h - MBOX Registers (hw2/hw4/hw6)


These registers are same in hw2/hw4/hw6, except that:

```
+-----------------------------------------------------------------------+
|       GMBOX registers exist in hw4/hw6 only                           |
|       STE_MODE register exists in hw6 only                            |
|       WLAN_MBOX_INT_xxx bit18,19 exist in hw6 only                    |
+-----------------------------------------------------------------------+
```

And, register names didn\'t have had the \"WLAN\_\" prefix in hw2.


```
+-----------------------------------------------------------------------------------+
|      ___________________________ Manual MBOX Transfer ___________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:018000h..01800Ch - WLAN_MBOX_FIFO\[0..3\]

```
+----------------------------------------------------------------------------+
|       0-7    DATA: DATABYTE                                                |
|       8-11   DATA: zero?                                                   |
|       12-15  DATA: zero? maybe copy of MBOX_FIFO_STATUS bit12-15 ? (FULL)  |
|       16-19  DATA: looks like copy of MBOX_FIFO_STATUS bit16-19 ?  (EMPTY) |
|       20-31  -                                                             |
+----------------------------------------------------------------------------+
```

READ: Allows to read incoming MBOX data; before reading this register, the data MUST be manually copied to this register via WLAN_MBOX_TXFIFO_POP\[n\], then read this register, and check the EMPTY flag; this requires \"double indexing\" as so: for MBOX(n), test \"WLAN_MBOX_FIFO\[n\].bit(16+n)\", if the bit is zero, then bit0-7 contains valid data.
WRITE: Allows to send outgoing MBOX data (write the databyte, with zeroes in bit8-31); before doing so, one SHOULD check if the FIFO is full via WLAN_MBOX_FIFO_STATUS.

### ATH:0180F0h..0180FCh - WLAN_MBOX_TXFIFO_POP\[0..3\]

```
+-----------------------------------------------------------------------+
|       0      DATA  ... uh 4x1bit ?   for MBOX0..3 ?                   |
|       1-31   -                                                        |
+-----------------------------------------------------------------------+
```

Writing 0 to WLAN_MBOX_TXFIFO_POP\[n\] does remove the oldest \"TXFIFO\" entry (the data transmitted from SDIO side to xtensa side via MBOXn), and stores that value (and a copy of the WLAN_MBOX_FIFO_STATUS bits) in WLAN_MBOX_FIFO\[n\].

### ATH:018100h..01810Ch - WLAN_MBOX_RXFIFO_POP\[0..3\]

```
+-----------------------------------------------------------------------+
|       0      DATA  ... uh 4x1bit ?   for MBOX0..3 ?                   |
|       1-31   -                                                        |
+-----------------------------------------------------------------------+
```

Probably similar as above, but for opposite direction (ie. allowing to read data that was \"sent-to-the-host\"; normally such data should be read by the host, so one would use this feature only if one wants to screw up the normal transfer flow).


```
+----------------------------------------------------------------------------------+
|      ____________________________ DMA MBOX Transfer ____________________________ |
+----------------------------------------------------------------------------------+
```


### ATH:018014h - WLAN_MBOX_DMA_POLICY

```
+-----------------------------------------------------------------------+
|       0      RX_ORDER                                                 |
|       1      RX_QUANTUM                                               |
|       2      TX_ORDER                                                 |
|       3      TX_QUANTUM                                               |
|       4-31   -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:018018h - WLAN_MBOX0_DMA_RX_DESCRIPTOR_BASE
### ATH:018020h - WLAN_MBOX0_DMA_TX_DESCRIPTOR_BASE
### ATH:018028h - WLAN_MBOX1_DMA_RX_DESCRIPTOR_BASE
### ATH:018030h - WLAN_MBOX1_DMA_TX_DESCRIPTOR_BASE
### ATH:018038h - WLAN_MBOX2_DMA_RX_DESCRIPTOR_BASE
### ATH:018040h - WLAN_MBOX2_DMA_TX_DESCRIPTOR_BASE
### ATH:018048h - WLAN_MBOX3_DMA_RX_DESCRIPTOR_BASE
### ATH:018050h - WLAN_MBOX3_DMA_TX_DESCRIPTOR_BASE
### ATH:018114h - WLAN_GMBOX0_DMA_RX_DESCRIPTOR_BASE - hw4/hw6 only
### ATH:01811Ch - WLAN_GMBOX0_DMA_TX_DESCRIPTOR_BASE - hw4/hw6 only

```
+-----------------------------------------------------------------------+
|       0-1    -                                                        |
|       2-27   ADDRESS                                                  |
|       28-31  -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:01801Ch - WLAN_MBOX0_DMA_RX_CONTROL
### ATH:018024h - WLAN_MBOX0_DMA_TX_CONTROL
### ATH:01802Ch - WLAN_MBOX1_DMA_RX_CONTROL
### ATH:018034h - WLAN_MBOX1_DMA_TX_CONTROL
### ATH:01803Ch - WLAN_MBOX2_DMA_RX_CONTROL
### ATH:018044h - WLAN_MBOX2_DMA_TX_CONTROL
### ATH:01804Ch - WLAN_MBOX3_DMA_RX_CONTROL
### ATH:018054h - WLAN_MBOX3_DMA_TX_CONTROL
### ATH:018118h - WLAN_GMBOX0_DMA_RX_CONTROL - hw4/hw6 only
### ATH:018120h - WLAN_GMBOX0_DMA_TX_CONTROL - hw4/hw6 only

```
+-----------------------------------------------------------------------+
|       0      STOP                                                     |
|       1      START                                                    |
|       2      RESUME                                                   |
|       3-31   -                                                        |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      __________________________________ Status __________________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:018010h - WLAN_MBOX_FIFO_STATUS

```
+-----------------------------------------------------------------------+
|       0-11   -                                                        |
|       12-15  FULL flags for MBOX 0..3                                 |
|       16-19  EMPTY flags for MBOX 0..3                                |
|       20-31  -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:018058h - WLAN_MBOX_INT_STATUS
### ATH:01805Ch - WLAN_MBOX_INT_ENABLE

```
+------------------------------------------------------------------------------------+
|       0-7    HOST           Interrupt 0..7 from Host        ;SDIO 1:00472h.bit0..7 |
|       8-11   RX_NOT_FULL    MBOX0..3 RX FIFO Not Full                              |
|       12-15  TX_NOT_EMPTY   MBOX0..3 TX FIFO Not Empty                             |
|       16     RX_UNDERFLOW   MBOX RX Underflow (tried to read from empty fifo)      |
|       17     TX_OVERFLOW    MBOX TX Overflow (tried to write to full fifo)         |
|       18     hw6: FRAME_DONE                            ;\hw6.0 only               
|       19     hw6: NO_RX_MBOX_DATA_AVA                   ;/                         |
|       20-23  TX_DMA_COMPLETE      MBOX0..3 TX DMA Complete                         |
|       24-27  TX_DMA_EOM_COMPLETE  MBOX0..3 TX DMA Complete .. End of message?      |
|       28-31  RX_DMA_COMPLETE      MBOX0..3 RX DMA Complete                         |
+------------------------------------------------------------------------------------+
```


### ATH:018124h - WLAN_GMBOX_INT_STATUS - hw4/hw6 only
### ATH:018128h - WLAN_GMBOX_INT_ENABLE - hw4/hw6 only

```
+-----------------------------------------------------------------------+
|       0      RX_NOT_FULL                                              |
|       1      TX_NOT_EMPTY                                             |
|       2      TX_DMA_COMPLETE                                          |
|       3      TX_DMA_EOM_COMPLETE                                      |
|       4      RX_DMA_COMPLETE                                          |
|       5      RX_UNDERFLOW                                             |
|       6      TX_OVERFLOW                                              |
|       7-31   -                                                        |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ______________________________ SDIO Handshake ______________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:018060h - WLAN_INT_HOST

```
+------------------------------------------------------------------------------------+
|       0-7    VECTOR   Interrupt 0..7 to Host                ;SDIO 1:00401h.bit0..7 |
|       8-31   -                                                                     |
+------------------------------------------------------------------------------------+
```


### ATH:018080h..01809Ch - WLAN_LOCAL_COUNT\[0..7\]
### ATH:0180A0h..0180BCh - WLAN_COUNT_INC\[0..7\]

```
+------------------------------------------------------------------------------------+
|       0-7    VALUE (credit counter)                         ;SDIO 1:00420h..00427h |
|       8-31   -                                                                     |
+------------------------------------------------------------------------------------+
```

See COUNT and COUNT_DEC.

### ATH:0180C0h..0180DCh - WLAN_LOCAL_SCRATCH\[0..7\]

```
+------------------------------------------------------------------------------------+
|       0-7    VALUE (scratch)                                ;SDIO 1:00460h..00467h |
|       8-31   -                                                                     |
+------------------------------------------------------------------------------------+
```


### ATH:0180E0h - WLAN_USE_LOCAL_BUS

```
+---------------------------------------------------------------------------+
|       0      PIN_INIT       ;whatever, maybe PCI bus related (non-SDIO) ? |
|       1-31   -                                                            |
+---------------------------------------------------------------------------+
```


### ATH:0180E4h - WLAN_SDIO_CONFIG

```
+---------------------------------------------------------------------------------+
|       0      CCCR_IOR1       ;SDIO Func I/O Ready bit1 ?    ;SDIO 0:00002h.bit1 |
|       1-31   -                                                                  |
+---------------------------------------------------------------------------------+
```


### ATH:01A000h..01BFFCh - WLAN_HOST_IF_WINDOW\[0..2047\]

```
+------------------------------------------------------------------------------------+
|       0-7    DATA                                           ;SDIO 1:00000h..007FFh |
|       8-31   -                                                                     |
+------------------------------------------------------------------------------------+
```

Allows to access the SDIO Host registers via Internal registers, should be done only for testing purposes.


```
+-----------------------------------------------------------------------------------+
|      ___________________________________ Misc ___________________________________ |
+-----------------------------------------------------------------------------------+
```


### ATH:0180E8h - WLAN_MBOX_DEBUG

```
+-----------------------------------------------------------------------+
|       0-2    SEL                                                      |
|       3-31   -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:0180ECh - WLAN_MBOX_FIFO_RESET

```
+-----------------------------------------------------------------------+
|       0      INIT                                                     |
|       1-31   -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:018110h - WLAN_SDIO_DEBUG

```
+-----------------------------------------------------------------------+
|       0-3    SEL                                                      |
|       4-31   -                                                        |
+-----------------------------------------------------------------------+
```


### ATH:01812Ch - STE_MODE - hw6.0 only

```
+-----------------------------------------------------------------------+
|       0      SEL                                                      |
|       1-2    PHA_POL                                                  |
|       3      SEL_16BIT                                                |
|       4      SWAP                                                     |
|       5      RST                                                      |
|       6      SPI_CTRL_EN                                              |
+-----------------------------------------------------------------------+
```




