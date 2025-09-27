# DSi SD/MMC Protocol: OCR Register (32bit Operation Conditions Register)


CMD1 (MMC) and ACMD41 (SD) are intended to exchange OCR information. That is, the OCR parameter bits should indicate the host conditions (eg. for DSi: 40100000h, ie. bit20=3.3V supply, and bit30=HCS support for High Capacity carts with more than 2GBytes). The OCR response may then return something like 007f8000h when busy, and 807f8000h when ready (bit20 indicating the voltage being actually supported, bit30 indicating if it\'s High Capacity card, and bit31 indicating if the card is ready & switched from \"idle\" to \"ready\" state).
Cards do usually send at least one response with bit31=0 (busy), one should repeat sending CMD1/ACMD51 until bit31=1 (ready).
Note: All card(s) on the bus will respond to CMD1/ACMD51: with the response bits ANDed together (thus returning nonsense in bit30=HCS when actually sharing the same bus for multiple cards).
Note: The card switches to \"ina\" state if the voltage in param bits isn\'t supported.

### CMD1 - SD/MMC (For SD Cards: SPI-only) - SPI - SEND_OP_COND
Parameter For MMC Cards (supported in SPI and Non-SPI mode):

```
+----------------------------------------------------------------------------+
|       31-0  OCR without busy (ie. without the power-up busy flag in bit31) |
+----------------------------------------------------------------------------+
```

Parameter For SD Cards (supported in SPI mode only, not in Non-SPI mode):

```
+-------------------------------------------------------------------------------+
|       31    Reserved (0)                            ;\special case (applies   
|       30    HCS (Host Capacity Support information) ; to SD-cards in SPI-mode |
|       29-0  Reserved (0)                            ;/only)                   |
+-------------------------------------------------------------------------------+
```

SD Response: R1
MMC Response: R3 (same/similar as SD Mode\'s ACMD41 response, see below)
Sends host capacity support information and activates the card\'s initialization process. HCS is effective when card receives SET_IF_COND command.

### ACMD41 - SD - SPI - SD_SEND_OP_COND (type=bcr)

```
+------------------------------------------------------------------------------------+
|       31     reserved bit                                                          |
|       30     HCS(OCR[30]) (Host Capacity Support information)                      |
|       29     reserved for eSD                 ;\                                   
|       28     XPC Max Power Consumption (watts); SPI Mode: Reserved                 |
|       27-25  reserved bits                    ; (ie. only bit30 is used for SPI)   |
|       24     S18R                             ; (ie. ACMD41 is SAME as SPI CMD1 ?) |
|       23-0   VDD Voltage Window(OCR[23-0])    ;/                                   |
+------------------------------------------------------------------------------------+
```

SD Mode Response: R3:

```
+----------------------------------------------------------------------------+
|       47     Start Bit (0)                                 ;\              
|       46     Transmission To Host (0)                      ; 1st byte      |
|       45-40  Reserved (111111) (instead of Command value)  ;/              |
|       39-8   OCR (32bit)                                   ;-2nd..5th byte |
|       7-1    Reserved (111111) (instead of CRC7)           ;\6th byte      
|       0      End Bit (1)                                   ;/              |
+----------------------------------------------------------------------------+
```

SPI Mode Response: R1 (without extra Data transfer? use READ_OCR instead?)
Sends host capacity support information (HCS) and asks the accessed card to send its operating condition register (OCR) content in the response on the CMD line. HCS is effective when card receives SET_IF_COND command (uh, but IF_COND should be set BEFORE setting OP_COND?).
Sends request to switch to 1.8V signaling (S18R).
Reserved bit shall be set to \'0\'. CCS bit is assigned to OCR\[30\].
XPC controls the maximum power in the default speed mode of SDXC card.

```
+------------------------------------------------------------------------------------+
|       XPC=0: 0.36W (100mA at 3.6V on VDD1) (max) but speed class is not supported. |
|       XPC=1: 0.54W (150mA at 3.6V on VDD1) (max) and speed class is supported.     |
+------------------------------------------------------------------------------------+
```


### CMD58 - SD/MMC - SPI-ONLY (not Non-SPI Mode) - READ_OCR
Supported on SD Cards in SPI Mode only (in Non-SPI mode, CMD58 would be: MMC=Reserved, SD=READ_EXTR_MULTI)!
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

SPI Mode Response: R3:

```
+-----------------------------------------------------------------------------+
|       39-32  R1 (8bit Card Status, same as in normal SPI command responses) |
|       31-0   OCR (32bit)                                                    |
+-----------------------------------------------------------------------------+
```


### OCR register
The 32-bit operation conditions register stores the VDD voltage profile of the non UHS-II card and VDD1 voltage profile of the UHS-II card. Additionally, this register includes status information bits. One status bit is set if the card power up procedure has been finished. This register includes another status bit indicating the card capacity status after set power up status bit. The OCR register shall be implemented by the cards.
The 32-bit operation conditions register stores the VDD voltage profile of the card.
Bit 7 of OCR is newly defined for Dual Voltage Card and set to 0 in default. If a Dual Voltage Card does not receive CMD8, OCR bit 7 in the response indicates 0, and the Dual Voltage Card which received CMD8, sets this bit to 1.

```
+-------------------------------------------------------------------------------------+
|       31     Card power up status bit (0=Busy, 1=Ready)                             |
|       30     Card Capacity Status (CCS) (valid only if above Bit31 indicates Ready) |
|               CCS=0   SDSC Card      (addressed in 1-byte units)   ;MMC max 2GB     |
|               CCS=1   SDHC/SDXC card (addressed in 512-byte units) ;MMC > 2GB       |
|       29     UHS-II Card Status                                                     |
|       28-25  Reserved                                                               |
|       24     Switching to 1.8V Accepted (S18A) (Only UHS-I card supports this bit)  |
|       23     3.5-3.6                        ;\                                      
|       22     3.4-3.5                        ;                                       |
|       21     3.3-3.4                        ;                                       |
|       20     3.2-3.3 ;<-- this used by DSi  ;                                       |
|       19     3.1-3.2                        ; VDD Voltage Window                    |
|       18     3.0-3.1                        ;                                       |
|       17     2.9-3.0                        ;                                       |
|       16     2.8-2.9                        ;                                       |
|       15     2.7-2.8                        ;                                       |
|       14-8   Reserved (MMC: 2.0V .. 2.6V)   ;  ;<-- uh, probably in opposite order? |
|       7      Reserved for Low Voltage Range ;                                       |
|       6-4    Reserved                       ;                                       |
|       3-0    Reserved                       ;/                                      |
+-------------------------------------------------------------------------------------+
```

The supported voltage range is coded as shown in Table 5-1. A voltage range is not supported if the corresponding bit value is set to LOW. As long as the card is busy, the corresponding bit (31) is set to LOW.
VDD Voltage Window of OCR indicates VDD1 voltage range in case of UHS-II Card.
UHS-II Card Status bit is added in Bit 29 to indicate whether the card supports UHS-II Interface. Non UHS-II Card sets Bit 29 to 0 and UHS-II Card sets Bit 29 to 1. This bit is not affected by whether VDD2 is supplied or not.



