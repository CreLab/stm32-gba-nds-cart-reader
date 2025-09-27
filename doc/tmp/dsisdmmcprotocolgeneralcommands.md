# DSi SD/MMC Protocol: General Commands


### CMD0 - SD/MMC - SPI - GO_IDLE_STATE (type=bc)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

SD Mode Response: N/A
SPI Mode Response: R1
Resets all cards to idle state, it\'s usually sent to (re-)invoke card detection and initialization. The command does also seem to reset many further registers (for example, TRAN_SPEED is said to be reset to 25MHz, and, although not officially specified, the DSi\'s eMMC chip appears to get forced back to 1bit data bus mode).
Observe that card detection/initialization should be done at lower CLK rate than usually (MMC specifies max 400kHz - this is actually required - the DSi\'s onboard Samsung KMAPF0000M-S998 eMMC chip won\'t respond to ALL_GET_CID when trying to use 16MHz CLK), higher CLK can be used once when detecting max speed (TRAN_SPEED in CSD register).
The command is also used to enter SPI mode (in SPI mode, the /CS pin is held low, while in 1bit/4bit mode that pin would be DAT3=floating/high), SPI commands can be sent without CRCs, however, at time when entering SPI mode, memory cards may still insist on checksums, CMD0 should be thus always sent with CRC7.

### CMD8 - SD (SD v2.00 and up) - SPI - SET_IF_COND (type=bcr)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-12 reserved bits                                             |
|       11-8  supply voltage (VHS)                                      |
|       7-0   check pattern                                             |
+-----------------------------------------------------------------------+
```

SD Mode Response: R7:

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-20   Reserved (zero filled)           (20bit)      ;\2nd..4th byte 
|       19-16   Voltage accepted (see below)     (4bit)       ;/              |
|       23-8    Echo-back of check pattern       (8bit)       ;-5th byte      |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```

SPI Mode Response: R7:

```
+-----------------------------------------------------------------------------+
|       39-32  R1 (8bit Card Status, same as in normal SPI command responses) |
|       31-28  Command version (???)         (4bit)                           |
|       27-12  Reserved (0)                  (16bit)                          |
|       11-8   Voltage Accepted (see below)  (4bit)                           |
|       7-0    Echo-back of check pattern    (8bit)                           |
+-----------------------------------------------------------------------------+
```

Sends SD Memory Card interface condition, which includes host supply voltage information and asks the card whether card supports voltage.
Voltage Accepted values:

```
+-----------------------------------------------------------------------+
|       0001b  = 2.7-3.6V                                               |
|       0010b  = Reserved for Low Voltage Range                         |
|       0100b  = Reserved                                               |
|       1000b  = Reserved                                               |
|       Others = Not Defined                                            |
+-----------------------------------------------------------------------+
```

The card supported voltage information of 3.3V range power pin is sent by the response of CMD8. Bits 19-16 indicate the voltage range that the card supports. The card that accepted the supplied voltage returns R7 response. In the response, the card echoes back both the voltage range and check pattern set in the argument.

### CMD11 - SD - VOLTAGE_SWITCH (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  reserved bits (0)                                         |
+-----------------------------------------------------------------------+
```

Response: R1
Switch to 1.8V bus signaling level.

### CMD12 - SD/MMC - SPI - STOP_TRANSMISSION (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1b
Additional Data Transfer (from card): Busy signal for \"R1b\" response
Forces the card to stop transmission (SPI: in Multiple Block Read Operation).
Note: Toshiba SD/MMC controllers are sending STOP_TRANSMISSION automatically.

### CMD15 - SD/MMC - GO_INACTIVE_STATE (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA                                                       |
|       15-0  reserved bits (0)                                         |
+-----------------------------------------------------------------------+
```

Response: N/A
Sends an addressed card into the Inactive State. This command is used when the host explicitly wants to deactivate a card once and forever (and won\'t even react to GO_IDLE_STATE) until next power-up (aka until ejecting/reinserting the card).

### CMD59 - SD/MMC - SPI-ONLY (not Non-SPI Mode) - CRC_ON_OFF
Supported in SPI Mode only (in Non-SPI mode, CMD59 would be: MMC=Reserved, SD=WRITE_EXTR_MULTI)!
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-1  stuff bits                                                |
|       0     CRC option (0=off, 1=on)                                  |
+-----------------------------------------------------------------------+
```

SPI Mode Response: R1
Default on power up is unknown. Also unknown if this does completely prevent transmission of both CRC7 and CRC-CCITT values (especially in case of CID/CSD registers that have the CRC7 \"inside\" of the \"128bit\" register). Also unknown if CID/CSD are having \"double\" checksums (CRC7 plus CRC-CCITT) when transferring them as DATA packet (instead of as normal command/response).

### ACMD6 - SD - SET_BUS_WIDTH (type=ac)

```
+--------------------------------------------------------------------------+
|       31-2  stuff bits                                                   |
|       1-0   Bus width for Data transfers (0=1bit, 2=4bit, 1/3=reserved). |
+--------------------------------------------------------------------------+
```

Response: R1
The supported widths can be found in SCR register. The current width is stored in SSR register. Default width is 1bit on power up.
Note: MMC uses a different mechanism to change the bus-width (via EXT_CSD).

### ACMD42 - SD - SPI - SET_CLR_CARD_DETECT (type=ac)

```
+-----------------------------------------------------------------------+
|       31-1  stuff bits                                                |
|       0     set_cd (0=Disconnect, 1=Connect)                          |
+-----------------------------------------------------------------------+
```

Response: R1
Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 pin of the card.
The pull-up might be intended for card detection (other than by using the slot\'s card detect switch), and/or for sensing SPI mode (which would drag that pin to LOW level when asserting /CS chip select).
During operation, disabling the pull-up might improve 4bit mode data transfers (unless for card controllers which do rely on the card pull-up to be present). The TC6387XB datasheet recommends external 100K pull-ups on DAT0-2, and only 47K on DAT3 (not quite sure why, unless Toshiba believed the parallel 50K+47K pull-ups to sum up to 100K, rather than to 25K).

### CMD55 - SD/MMC (MMC: only in SPI-mode?) - SPI - APP_CMD (type=ac)

```
+-----------------------------------------------------------------------+
|       31-16  RCA (SPI Mode: stuff bits)                               |
|       15-0   stuff bits                                               |
+-----------------------------------------------------------------------+
```

Response: R1
Used as prefix for application specific commands, ie. the next command will be treated as \"ACMDnn\" rather than as normal \"CMDnn\".
As the name says, this was originally intended for \"application specific\" extensions, however, in the SD Card protocol, it\'s also used for some ACMD\'s that are part of the SD protocol.

### CMD56 - SD/MMC (MMC: only in SPI-mode?) - SPI - GEN_CMD (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-1  stuff bits                                                |
|       0     RD/WR Direction (0=Write to Card, 1=Read from Card)       |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to/from card, depending on above R/W bit):

```
+-----------------------------------------------------------------------+
|       General purpose data                                            |
|       For SDSC, block length is set via SET_BLOCKLEN command.         |
|       For SDHC/SDXC, block length is fixed to 512 bytes.              |
+-----------------------------------------------------------------------+
```

Used to transfer a data block to/from the card for general purpose/application specific commands.

### CMD14 - MMC - BUSTEST_R (type=adtc) (MMC only, Reserved on SD)
### CMD19 - MMC - BUSTEST_W (type=adtc) (MMC only, SET_TUNING_BLOCK on SD)

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to/from card):

```
+-------------------------------------------------------------------------+
|       test pattern (2bit per DATA line? eg. 8bit pattern in 4bit-mode?) |
+-------------------------------------------------------------------------+
```

MMC only. And, that, in Non-SPI mode only.
BUSTEST_W: Host sends the \"bus TEST Data pattern\" to card.
BUSTEST_R: Host reads the \"REVERSED bus TESTING data pattern\" from card.
The reversing is said to change a 2bit value of \"01\" into \"10\", unknown if that means that the bit-order is reversed, or that the bits are inverted.



