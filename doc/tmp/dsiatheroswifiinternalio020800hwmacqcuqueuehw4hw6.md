# DSi Atheros Wifi - Internal I/O - 020800h - WMAC QCU Queue (hw4/hw6)


### ATH:020800h..020824h - MAC_QCU_TXDP\[0..9\] aka MAC_DMA_Q(0..9)\_TXDP

```
+---------------------------------------------------------------------------------+
|       0-31   DATA  ...   unspecified     ;MAC Transmit Queue descriptor pointer |
+---------------------------------------------------------------------------------+
```


### ATH:020840h - MAC_QCU_TXE aka MAC_DMA_Q_TXE - MAC Transmit Queue enable (R)
### ATH:020880h - MAC_QCU_TXD aka MAC_DMA_Q_TXD - MAC Transmit Queue disable

```
+-----------------------------------------------------------------------+
|       0-9    DATA                                                     |
+-----------------------------------------------------------------------+
```


### ATH:0208C0h..0208E4h - MAC_QCU_CBR\[0..9\] aka MAC_DMA_Q(0..9)\_CBRCFG

```
+-----------------------------------------------------------------------------+
|       0-23  CBR interval (us)      (INTERVAL)       ;\MAC CBR configuration 
|       24-31 CBR overflow threshold (OVF_THRESH)     ;/                      |
+-----------------------------------------------------------------------------+
```


### ATH:020900h..020924h - MAC_QCU_RDYTIME\[0..9\] aka MAC_DMA_Q(0..9)\_RDYTIMECFG

```
+-----------------------------------------------------------------------------------+
|       0-23  CBR interval (us)      (DURATION)       ;\MAC ReadyTime configuration 
|       24    CBR enable             (EN)             ;/                            |
+-----------------------------------------------------------------------------------+
```


### ATH:020940h - MAC_QCU_ONESHOT_ARM_SC aka MAC_DMA_Q_ONESHOTMAC_DMAM_SC - Set
### ATH:020980h - MAC_QCU_ONESHOT_ARM_CC aka MAC_DMA_Q_ONESHOTMAC_DMAM_CC - Clr
MAC OneShotArm set/clear control

```
+-----------------------------------------------------------------------+
|       0-9    SET/CLEAR                                                |
+-----------------------------------------------------------------------+
```


### ATH:0209C0h..0209E4h - MAC_QCU_MISC\[0..9\] aka MAC_DMA_Q(0..9)\_MISC
MAC Miscellaneous QCU settings

```
+----------------------------------------------------------------------------------+
|       0-3   Frame Scheduling Policy mask (FSP):                                  |
|               0=ASAP                    ;\                                       
|               1=CBR                     ; defined as so for                      |
|               2=DMA Beacon Alert gated  ; hw4 (maybe same                        |
|               3=TIM gated               ; for hw6)                               |
|               4=Beacon-sent-gated       ;/                                       |
|       4     OneShot enable (ONESHOT_EN)                                          |
|       5     CBR expired counter disable incr (NOFR, empty q)                     |
|       6     CBR expired counter disable incr (NOBCNFR, empty beacon q)           |
|       7     Beacon use indication (IS_BCN)                                       |
|       8     CBR expired counter limit enable (CBR_EXP_INC_LIMIT)                 |
|       9     Enable TXE cleared on ReadyTime expired or VEOL (TXE_CLR_ON_CBR_END) |
|       10    CBR expired counter reset (MMR_CBR_EXP_CNT_CLR_EN)                   |
|       11    FR_ABORT_REQ_EN         DCU frame early termination request control  |
+----------------------------------------------------------------------------------+
```


### ATH:020A00h..020A24h - MAC_QCU_CNT\[0..9\] aka MAC_DMA_Q(0..9)\_STS

```
+------------------------------------------------------------------------------------+
|       0-1    FR_PEND: Pending Frame Count (R)        ;\MAC Misc QCU status/counter 
|       8-15   CBR_EXP: CBR expired counter (R)        ;/                            |
+------------------------------------------------------------------------------------+
```


### ATH:020A40h - MAC_QCU_RDYTIME_SHDN aka MAC_DMA_Q_RDYTIMESHDN

```
+---------------------------------------------------------------------------+
|       0-9    SHUTDOWN: MAC ReadyTimeShutdown status (flags for QCU 0-9 ?) |
+---------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      _____________ below in hw6 only _____________                    |
+-----------------------------------------------------------------------+
```


### ATH:020830h - MAC_QCU_STATUS_RING_START ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   ADDR                                                     |
+-----------------------------------------------------------------------+
```


### ATH:020834h - MAC_QCU_STATUS_RING_END ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   ADDR                                                     |
+-----------------------------------------------------------------------+
```


### ATH:020838h - MAC_QCU_STATUS_RING_CURRENT (R) ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-31   ADDRESS                        (R)                       |
+-----------------------------------------------------------------------+
```


### ATH:020A44h - MAC_QCU_DESC_CRC_CHK ;hw6 only

```
+-----------------------------------------------------------------------+
|       0      EN                                                       |
+-----------------------------------------------------------------------+
```


### ATH:020A48h - MAC_QCU_EOL ;hw6 only

```
+-----------------------------------------------------------------------+
|       0-9    DUR_CAL_EN                                               |
+-----------------------------------------------------------------------+
```




