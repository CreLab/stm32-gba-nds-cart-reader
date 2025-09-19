# DS Cart Infrared Cartridge Memory Map


### IR Cartridge SFR Usage

```
+----------------------------------------------------------------------------------+
|       [0FFD6h].0  Port 3 Data bit0 OUT  IrDA PWDOWN (1=disable IrDA RX)          |
|       [0FFD6h].1  Port 3 Data bit1 IN   IrDA RXD  ;\via serial IrDA registers    
|       [0FFD6h].2  Port 3 Data bit2 OUT  IrDA TXD  ;/                             |
|       [0FFDBh].3  Port 8 Data bit3 OUT  Savedata chipselect (0=select) (cmd 00h) |
|       [0FFDBh].2  Port 8 Data bit2 OUT  LED color    ;\used in UNUSED functions, 
|       [0FFDBh].3  Port 8 Data bit3 OUT  LED color    ; in OLD ROM only, and      |
|       [0FFDEh].0  Port B Data bit0 IN   Button input ;/conflicting with Savedata |
|       IrDA  IR Transfers                                                         |
|       SPI   NDS Console (and cmd 00h forwarding to Savedata)                     |
+----------------------------------------------------------------------------------+
```


### IR Cartridge (OLD Version)

```
+-------------------------------------------------------------------------------------+
|       FB80h 200h  undocumented and unused RAM, is R/W in my 38600R (!)              |
|       FD80h 2     unused           ;-unused                                         |
|       FD82h 2     ir_callback      ;\main callbacks for ir/spi polling              
|       FD84h 2     spi_callback     ;/                                               |
|       FD86h 2     ir_timestamp     ;-last ir access (for timeout)?                  |
|       FD88h 2     spi_timestamp    ;-last spi access (for debug or so)?             |
|       FD8Ah 1     initial_blah     ;-initial state of Port 8.bit3 (not really used) |
|       FD8Bh 1     ir_rxbuf_wrptr   ;-ir_rxbuf_wrptr (for incoming IR data)?         |
|       FD8Ch 1     ir_rxbuf_rdptr   ;-ir_rxbuf_rdptr (for forwarding to spi)?        |
|       FD8Dh 84h   spi_rx_buf       ;-spi_rx_buf  ;(also ir TX buf)                  |
|       FE11h 84h   infrared_rx_buf  ;-infrared_rx_buf                                |
|       FE95h 1     spi_index        ;-spi_index                                      |
|       FE96h 1     ir_tx_index      ;-ir_tx_index   (from spi buf to TX infrared)    |
|       FE97h 1     ir_timeout_flag  ;-ir_timeout_flag   (or packet end or so?)       |
|       FE98h 2     button_num_changes   ;\                                           
|       FE9Ah 2     button_num_pushes    ; used only in                               |
|       FE9Ch 1     button_new_state     ; UNUSED functions                           |
|       FE9Dh 1     button_old_state     ;                                            |
|       FE9Eh 1     button_newly_pushed  ;                                            |
|       FE9Fh 1     button_offhold       ;/                                           |
|       FEA0h E0h   stack_area (stacktop at FF80h)                                    |
+-------------------------------------------------------------------------------------+
```


### IR Cartridge (NEW Version)

```
+-------------------------------------------------------------------------------------+
|       FB80h 200h  undocumented and unused RAM, is R/W in my 38600R (!)              |
|       FD80h 2     unused           ;-unused                                         |
|       FD82h 2     ir_callback      ;\main callbacks for ir/spi polling              
|       FD84h 2     spi_callback     ;/                                               |
|       FD86h 2     ir_timestamp     ;-last ir access (for timeout)?                  |
|       FD88h 1     ir_rxbuf_wrptr   ;-ir_rxbuf_wrptr (for incoming IR data)?         |
|       FD89h 1     ir_rxbuf_rdptr   ;-blah, always set to 0, never used              |
|       FD8Ah 1     spi_index        ;-spi_index                                      |
|       FD8Bh 1     ir_tx_index      ;-ir_tx_index   (from spi buf to TX infrared)    |
|       FD8Ch B8h   spi_rx_buf       ;-spi_rx_buf  ;(also ir TX buf)                  |
|       FE44h B8h+1 infrared_rx_buf  ;-infrared_rx_buf (plus space for appending 00h) |
|       FEFDh 1     ir_timeout_flag  ;-ir_timeout_flag   (or packet end or so?)       |
|       FEFEh 82h   stack_area (stacktop at FF80h)                                    |
+-------------------------------------------------------------------------------------+
```





