# DSi SD/MMC Protocol: RCA Register (16bit Relative Card Address)


The RCA was intended for connecting multiple cards to the same host, possibly even sharing the same signal wires for multiple cards. The multi-card feature isn\'t used to often though.
Most hosts are having only a single card slot. And, hosts that \<do\> support multiple cards may use separate busses and even separate controllers for each card (eg. Nintendo DSi is doing so for onboard NAND and external SD slot).
However, even single-card systems will need to obtain a \"dummy\" RCA, and use that RCA value for selecting the card.
The only exception is SPI mode: SPI isn\'t using RCA, and doesn\'t support RCA commands at all - instead, in SPI mode, the cards are selected via /CS signal (which may include multiple /CS signals for multiple cards).

### CMD3 - SD - GET_RELATIVE_ADDR (type=bcr)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R6:

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-24   New published RCA of the card   ;-16bit       ;-2nd..3th byte |
|       23-22   CSR Card Status, bit 23-22      ;\            ;\              
|       21      CSR Card Status, bit 19         ; 16bit       ; 4nd..5th byte |
|       20-8    CSR Card Status, bit 12-0       ;/            ;/              |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```

Ask the card to publish a new relative address (RCA).
Dunno how this is intended to work with multiple cards. The goal should be to assign \<different\> RCAs to each card. The command should be probably repeatedly used until all cards respond with different RCAs. This would require the cards to contain some sort of analog random generator - or maybe to use the CID register as random seed (the CID seems to contain unique serial numbers per card)?

### CMD3 - MMC - SET_RELATIVE_ADDR (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA                                                       |
|       15-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1
Assigns an RCA value TO the card (ie. the opposite of CMD3 on SD Cards).
Dunno how this is intended to work with multiple cards. The goal should be to assign \<different\> RCAs to each card. But actually, the command appears to assign the \<same\> RCA to all cards?

### CMD7 - SD/MMC - SELECT_DESELECT_CARD (type=ac) ;actually: (type=bcr)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA                                                       |
|       15-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1b (only from the selected card)
Additional Data Transfer (from card): Busy signal for \"R1b\" response
Command toggles a card between the stand-by and transfer states or between the programming and disconnect states. In both cases, the card is selected by its own relative address and gets deselected by any other address; address 0 deselects all.
In the case that the RCA equals 0, then the host may do one of the following:
- Use other RCA number to perform card de-selection.
- Re-send CMD3 to change its RCA number to other than 0 and then use CMD7 with RCA=0 for card deselection.

### CMD5 - MMC - SLEEP_AWAKE (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA                                                       |
|       15    Sleep/Awake flag (0=Awake/stby, 1=Sleep/slp)              |
|       14-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1b

### RCA register
The writable 16-bit relative card address register carries the card address that is published by the card during the card identification. This address is used for the addressed host-card communication after the card identification procedure. The default value of the RCA register is 0000h. The value 0000h is reserved to set all cards into the Stand-by State with CMD7.
In UHS-II mode, Node ID is used as RCA. Refer to SD-TRAN Section of UHS-II Addendum for more details.

### Note
Commands GET_CSD, GET_CID, APP_CMD, GO_INACTIVE_STATE, and GET_STATUS allow/require to specify RCA in parameter field.
Other commands are either processed by all cards (broadcast commands), or processed only be cards that have been previously selected via CMD7 (most normal commands).

### Broadcast Commands

```
+-----------------------------------------------------------------------------------+
|       CMD0     sd/mmc spi GO_IDLE_STATE (type=bc)                                 |
|       CMD2     sd/mmc     ALL_GET_CID (type=bcr)                                  |
|       CMD3     sd         GET_RELATIVE_ADDR (type=bcr)                            |
|       CMD4     sd/mmc     SET_DSR (type=bc)                                       |
|       CMD7     sd/mmc     SELECT_DESELECT_CARD (type=ac) ;actually: (type=bcr)    |
|       CMD8     sd     spi SET_IF_COND (type=bcr)                                  |
|       ACMD41   sd     spi SD_SEND_OP_COND (type=bcr)  ;SPI: reduced functionality |
+-----------------------------------------------------------------------------------+
```

Some broadcast commands are sending responses.
SD specs are suggesting to use separate CMD lines for each card (so the host would broadcast the same command on all CMD lines, and would receive separate responses in parallel from each CMD line).
MMC cards are said to support open-collector CMD lines (so responses from separate cards would be logically ORed, though, dunno what that would be good for).



