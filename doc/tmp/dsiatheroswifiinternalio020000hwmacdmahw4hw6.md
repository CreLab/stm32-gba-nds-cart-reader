# DSi Atheros Wifi - Internal I/O - 020000h - WMAC DMA (hw4/hw6)


### ATH:020008h - MAC_DMA_CR - MAC Control Register

```
+-------------------------------------------------------------------------------+
|       0-1    -                                                                |
|       2      hw4: Receive enable (RXE)            (R)       ;\one bit in hw4, 
|       2      hw6: Receive LP enable (RXE_LP)      (R)       ; two bits in hw6 |
|       3      hw6: Receive HP enable (RXE_HP)      (R)       ;/                |
|       4      -                                                                |
|       5      Receive disable (RXD)                                            |
|       6      One-shot software interrupt (SWI)    (R)                         |
+-------------------------------------------------------------------------------+
```


### ATH:02000Ch - MAC_DMA_RXDP - MAC receive queue descriptor pointer ;hw4 only

```
+-----------------------------------------------------------------------+
|       ..     Pointer                           <------------ HW4 ONLY |
+-----------------------------------------------------------------------+
```


### ATH:020014h - MAC_DMA_CFG - MAC configuration and status register

```
+------------------------------------------------------------------------+
|       0      Byteswap TX descriptor words (BE_MODE_XMIT_DESC)          |
|       1      Byteswap TX data buffer words (BE_MODE_XMIT_DATA)         |
|       2      Byteswap RX descriptor words (BE_MODE_RCV_DESC)           |
|       3      Byteswap RX data buffer words (BE_MODE_RCV_DATA)          |
|       4      Byteswap register access data words (BE_MODE_MMR)         |
|       5      AP/adhoc indication (ADHOC) (0=AP, 1=Adhoc)               |
|       6-7    -                                                         |
|       8      PHY OK status (PHY_OK)                    (R)             |
|       9      hw6: EEPROM_BUSY                          (R)  ;-hw6 only |
|       10     Clock gating disable (CLKGATE_DIS)                        |
|       11     hw6: HALT_REQ                                  ;\         
|       12     hw6: HALT_ACK                             (R)  ;          |
|       13-16  -                                              ;          |
|       17-18  hw6: REQ_Q_FULL_THRESHOLD                      ; hw6 only |
|       19     hw6: MISSING_TX_INTR_FIX_ENABLE                ;          |
|       20     hw6: LEGACY_INT_MIT_MODE_ENABLE                ;          |
|       21     hw6: RESET_INT_MIT_CNTRS                       ;/         |
+------------------------------------------------------------------------+
```


### ATH:020018h - MAC_DMA_RXBUFPTR_THRESH ;hw6 only

```
+------------------------------------------------------------------------+
|       0-3    hw6: HP_DATA                                   ;\hw6 only 
|       8-14   hw6: LP_DATA                                   ;/         |
+------------------------------------------------------------------------+
```


### ATH:02001Ch - MAC_DMA_TXDPPTR_THRESH ;hw6 only

```
+------------------------------------------------------------------------+
|       0-3    DATA                                           ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:020020h - MAC_DMA_MIRT - Maximum rate threshold register

```
+-----------------------------------------------------------------------+
|       0-15   Threshold (RATE_THRESH)                                  |
+-----------------------------------------------------------------------+
```


### ATH:020024h - MAC_DMA_IER aka MAC_DMA_GLOBAL_IER - MAC Interrupt enable

```
+-----------------------------------------------------------------------+
|       0      Global interrupt enable (0=Disable, 1=Enable)            |
+-----------------------------------------------------------------------+
```


### ATH:020028h - MAC_DMA_TIMT_0 - Transmit Interrupt Mitigation Threshold
### ATH:02002Ch - MAC_DMA_RIMT - Receive Interrupt Mitigation Threshold

```
+-----------------------------------------------------------------------+
|       0-15   Last packet threshold (LAST_PKT_THRESH)                  |
|       16-31  First packet threshold (FIRST_PKT_THRESH)                |
+-----------------------------------------------------------------------+
```


### ATH:020030h - MAC_DMA_TXCFG - MAC Transmit DMA size config register
In hw4, most bits are left undefined, however, hw4 DOES refer to the register as \"MAC tx DMA size config\", so one may assume that at least the SIZE value in bit0-2 does exist in hw4, too.

```
+------------------------------------------------------------------------------+
|       0-2    hw6: DMA_SIZE (maybe as in RXCFG below?)       ;-hw6 only (???) |
|       3      -                                                               |
|       4-9    Frame trigger level (TRIGLVL)                                   |
|       10     hw6: JUMBO_EN                                  ;-hw6 only (??)  |
|       11     ADHOC_BEACON_ATIM_TX_POLICY (hw6name: BCN_PAST_ATIM_DIS)        |
|       12     hw6: ATIM_DEFER_DIS                            ;\               
|       13     -                                              ;                |
|       14     hw6: RTCI_DIS                                  ; hw6 only (?)   |
|       15-16  -                                              ;                |
|       17     hw6: DIS_RETRY_UNDERRUN                        ;                |
|       18     hw6: DIS_CW_INC_QUIET_COLL                     ;                |
|       19     hw6: RTS_FAIL_EXCESSIVE_RETRIES                ;/               |
+------------------------------------------------------------------------------+
```

Blurb\...

```
+-------------------------------------------------------------------------+
|       MAC_DMA_FTRIG_IMMED = 0x00000000 ;bytes in PCU TX FIFO before air |
|       MAC_DMA_FTRIG_64B   = 0x00000010 ;default                         |
|       MAC_DMA_FTRIG_128B  = 0x00000020                                  |
|       MAC_DMA_FTRIG_192B  = 0x00000030                                  |
|       MAC_DMA_FTRIG_256B  = 0x00000040 ;5 bits total                    |
+-------------------------------------------------------------------------+
```


### ATH:020034h - MAC_DMA_RXCFG - MAC rx DMA size config register

```
+------------------------------------------------------------------------------+
|       0-2    DMA Size (0..7 = 4,8,16,32,64,128,256,512 bytes)                |
|       3-4    hw6: ZERO_LEN_DMA_EN                           ;-hw6: two bits? |
|       4      hw4: Enable DMA of zero-length frame           ;-hw4: one bit?  |
|       5      hw6: JUMBO_EN                                  ;\               
|       6      hw6: JUMBO_WRAP_EN                             ; hw6 only (?)   |
|       7      hw6: SLEEP_RX_PEND_EN                          ;/               |
+------------------------------------------------------------------------------+
```

Blurb\...

```
+---------------------------------------------------------------------------------+
|       MAC_DMA_RXCFG_DMASIZE_4B   = 0x00000000 ;DMA size 4 bytes (TXCFG + RXCFG) |
|       MAC_DMA_RXCFG_DMASIZE_8B   = 0x00000001 ;DMA size 8 bytes                 |
|       MAC_DMA_RXCFG_DMASIZE_16B  = 0x00000002 ;DMA size 16 bytes                |
|       MAC_DMA_RXCFG_DMASIZE_32B  = 0x00000003 ;DMA size 32 bytes                |
|       MAC_DMA_RXCFG_DMASIZE_64B  = 0x00000004 ;DMA size 64 bytes                |
|       MAC_DMA_RXCFG_DMASIZE_128B = 0x00000005 ;DMA size 128 bytes               |
|       MAC_DMA_RXCFG_DMASIZE_256B = 0x00000006 ;DMA size 256 bytes               |
|       MAC_DMA_RXCFG_DMASIZE_512B = 0x00000007 ;DMA size 512 bytes               |
+---------------------------------------------------------------------------------+
```


### ATH:020038h - MAC_DMA_RXJLA (R) ;hw6 only

```
+------------------------------------------------------------------------+
|       31-2   DATA                                       (R) ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:020040h - MAC_DMA_MIBC - MAC MIB control register

```
+-----------------------------------------------------------------------+
|       0     counter overflow warning (WARNING)          (R)           |
|       1     freeze MIB counters (FREEZE)                              |
|       2     clear MIB counters (CLEAR)                                |
|       3     MIB counter strobe, increment all (STROBE)  (R)           |
+-----------------------------------------------------------------------+
```


### ATH:020044h - MAC_DMA_TOPS - MAC timeout prescale count

```
+-----------------------------------------------------------------------+
|       0-15  Timeout prescale (TIMEOUT)                                |
+-----------------------------------------------------------------------+
```


### ATH:020048h - MAC_DMA_RXNPTO - MAC no frame received timeout

```
+-----------------------------------------------------------------------+
|       0-9   No frame received timeout (TIMEOUT)                       |
+-----------------------------------------------------------------------+
```


### ATH:02004Ch - MAC_DMA_TXNPTO - MAC no frame trasmitted timeout

```
+-------------------------------------------------------------------------------+
|       0-9   No frame transmitted timeout (TIMEOUT)                            |
|       10-19 QCU Mask (QCU 0-9)  ;QCU's for which frame completions will cause |
|               a reset of the no frame xmit'd timeout                          |
+-------------------------------------------------------------------------------+
```


### ATH:020050h - MAC_DMA_RPGTO - MAC receive frame gap timeout

```
+-----------------------------------------------------------------------+
|       0-9   Receive frame gap timeout (TIMEOUT)                       |
+-----------------------------------------------------------------------+
```


### ATH:020054h - MAC_DMA_RPCNT - MAC receive frame count limit ;hw4 only

```
+------------------------------------------------------------------------+
|       0-4   Receive frame count limit                       ;-hw4 only |
+------------------------------------------------------------------------+
```


### ATH:020058h - MAC_DMA_MACMISC - MAC miscellaneous control/status register

```
+-----------------------------------------------------------------------------+
|       4      hw6: FORCE_PCI_EXT                             ;-hw6 only      |
|       5-8    DMA observation bus mux select (DMA_OBS_MUXSEL)                |
|       9-11   MISC observation bus mux select (MISC_OBS_MUXSEL)              |
|       12-14  MAC observation bus mux select (lsb) (MISC_F2_OBS_LOW_MUXSEL)  |
|       15-17  MAC observation bus mux select (msb) (MISC_F2_OBS_HIGH_MUXSEL) |
+-----------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      ____________ below in hw6 only ____________                      |
+-----------------------------------------------------------------------+
```


### ATH:02005Ch - MAC_DMA_INTER ;hw6 only

```
+-----------------------------------------------------------------------+
|       0      REQ                                                      |
|       1-2    MSI_RX_SRC                                               |
|       3-4    MSI_TX_SRC                                               |
+-----------------------------------------------------------------------+
```


### ATH:020060h - MAC_DMA_DATABUF ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-11   LEN                                                      |
+-----------------------------------------------------------------------+
```


### ATH:020064h - MAC_DMA_GTT ;hw6 only
### ATH:02006Ch - MAC_DMA_CST ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-15   COUNT                                                    |
|       16-31  LIMIT                                                    |
+-----------------------------------------------------------------------+
```


### ATH:020068h - MAC_DMA_GTTM ;hw6 only

```
+-----------------------------------------------------------------------+
|       0      USEC_STROBE                                              |
|       1      IGNORE_CHAN_IDLE                                         |
|       2      RESET_ON_CHAN_IDLE                                       |
|       3      CST_USEC_STROBE                                          |
|       4      DISABLE_QCU_FR_ACTIVE_GTT                                |
|       5      DISABLE_QCU_FR_ACTIVE_BT                                 |
+-----------------------------------------------------------------------+
```


### ATH:020070h - MAC_DMA_RXDP_SIZE ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-7    LP                             (R)                       |
|       8-12   HP                             (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:020074h - MAC_DMA_RX_QUEUE_HP_RXDP ;hw6 only
### ATH:020078h - MAC_DMA_RX_QUEUE_LP_RXDP ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   ADDR                                                     |
+-----------------------------------------------------------------------+
```


### ATH:0200E0h - MAC_DMA_DMADBG_0 (R) - hw6 only
### ATH:0200E4h - MAC_DMA_DMADBG_1 (R) - hw6 only
### ATH:0200E8h - MAC_DMA_DMADBG_2 (R) - hw6 only
### ATH:0200ECh - MAC_DMA_DMADBG_3 (R) - hw6 only
### ATH:0200F0h - MAC_DMA_DMADBG_4 (R) - hw6 only
### ATH:0200F4h - MAC_DMA_DMADBG_5 (R) - hw6 only
### ATH:0200F8h - MAC_DMA_DMADBG_6 (R) - hw6 only
### ATH:0200FCh - MAC_DMA_DMADBG_7 (R) - hw6 only

```
+------------------------------------------------------------------------+
|       0-31   DATA                                      (R)  ;-hw6 only |
+------------------------------------------------------------------------+
```


### ATH:020100h - MAC_DMA_QCU_TXDP_REMAINING_QCU_7_0 (R) ;hw6 only
### ATH:020104h - MAC_DMA_QCU_TXDP_REMAINING_QCU_9_8 (R) ;hw6 only

```
+------------------------------------------------------------------------+
|       0-39   For QCU 0-9 (4bits each)                  (R)  ;\hw6 only 
|       40-63  -                                              ;/         |
+------------------------------------------------------------------------+
```


### (see above) - MAC_DMA_TIMT_0 - hw4/hw6
### ATH:020108h - MAC_DMA_TIMT_1 - hw6 only
### ATH:02010Ch - MAC_DMA_TIMT_2 - hw6 only
### ATH:020110h - MAC_DMA_TIMT_3 - hw6 only
### ATH:020114h - MAC_DMA_TIMT_4 - hw6 only
### ATH:020118h - MAC_DMA_TIMT_5 - hw6 only
### ATH:02011Ch - MAC_DMA_TIMT_6 - hw6 only
### ATH:020120h - MAC_DMA_TIMT_7 - hw6 only
### ATH:020124h - MAC_DMA_TIMT_8 - hw6 only
### ATH:020128h - MAC_DMA_TIMT_9 - hw6 only

```
+-----------------------------------------------------------------------+
|       0-15   LAST_PKT_THRESH                                          |
|       16-31  FIRST_PKT_THRESH                                         |
+-----------------------------------------------------------------------+
```


### ATH:02012Ch - MAC_DMA_CHKACC - hw6 only

```
+-----------------------------------------------------------------------+
|       0      CHKSUM_SEL                                               |
+-----------------------------------------------------------------------+
```




