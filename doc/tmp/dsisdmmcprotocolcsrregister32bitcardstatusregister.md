# DSi SD/MMC Protocol: CSR Register (32bit Card Status Register)


### CMD13 - SD/MMC - SPI - GET_STATUS (type=ac)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 RCA (SPI Mode: stuff bits)                                |
|       15-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

SD Mode Response: R1 (32bit Card Status):

```
+-----------------------------------------------------------------------------+
|       47      Start Bit (0)                                 ;\              
|       46      Transmission To Host (0)                      ; 1st byte      |
|       45-40   Command (the 6bit CMD being responded to)     ;/              |
|       39-8    CSR Card Status Register (32bit) (see below)  ;-2nd..5th byte |
|       7-1     CRC7                                          ;\6th byte      
|       0       End Bit (1)                                   ;/              |
+-----------------------------------------------------------------------------+
```

SPI Mode Response: R2 (16bit Card Status):

```
+-----------------------------------------------------------------------------+
|       15-0    CSR Card Status Register (16bit) (see below)  ;-1st..2nd byte |
+-----------------------------------------------------------------------------+
```

Addressed card sends its status register.

### CMDxx/ACMDxx - Other Commands
Most other commands are also returning the Card Status in their responses:
SD Mode Response: R1 (32bit Card Status)
SPI Mode Response: R1 (8bit Card Status; most SPI commands return only 8bit)
SPI Mode Response: R2 (16bit Card Status; SPI commands CMD13/ACMD return 16bit)

### CMDxx/ACMDxx - Other Commands with R1b Response
R1b is identical to R1, with an optional busy signal transmitted on the DATA line (R1b occurs for CMD7, CMD12, CMD20, CMD28, CMD29, CMD38) (and for MMC: also for CMD5, CMD6). The card may become busy after receiving these commands based on its state prior to the command reception. The Host shall check for busy at the response.
In SD Mode, the busy signal is sent on DAT0 line (DAT1-3 aren\'t used, even if the card is in 4bit mode). The busy signal does consist of BITs? (not bytes?), and has a \"start bit\"?, followed by what-value-when-busy? and what-final-value-when-ready?
In SPI Mode, the busy signal is sent as BYTEs (00h=Busy, xxh=Nonzero=Ready).

### CSR Card Status Register (full 32bit, as returned in SD Mode Response: R1)

```
+------------------------------------------------------------------------------------+
|       Bit  Typ Clr Identifier         Meaning                                      |
|       31   ERX  C  OUT_OF_RANGE       (1=Command's argument was out of range)      |
|       30   ERX  C  ADDRESS_ERROR      (1=Misaligned address/block len mismatch)    |
|       29   ERX  C  BLOCK_LEN_ERROR    (1=Wrong block length, bytelen mismatch)     |
|       28   ER   C  ERASE_SEQ_ERROR    (1=Error in erase command sequence)          |
|       27   ERX  C  ERASE_PARAM        (1=Wrong erease selection of write-blocks)   |
|       26   ERX  C  WP_VIOLATION       (1=Write failed due to write-protection)     |
|       25   SX   A  CARD_IS_LOCKED     (1=Card is locked by the host)               |
|       24   ERX  C  LOCK_UNLOCK_FAILED (1=Lock/unlock sequence or password error)   |
|       23   ER   B  COM_CRC_ERROR      (1=CRC check of previous command failed)     |
|       22   ER   B  ILLEGAL_COMMAND    (1=Command not legal for the card state)     |
|       21   ERX  C  CARD_ECC_FAILED    (1=Internal error correction failed)         |
|       20   ERX  C  CC_ERROR           (1=Internal card controller error)           |
|       19   ERX  C  ERROR              (1=General error, or Unknown error)          |
|       18   -    -  Reserved (eMMC: UNDERRUN)                                       |
|       17   -    -  Reserved (eMMC: OVERRUN) (eSD: DEFERRED_RESPONSE)               |
|       16   ERX  C  CSD_OVERWRITE      (1=read-only CSD section doesn't match card  |
|                                       content, or attempted to reverse the         |
|                                       Copy/WP bits)                                |
|       15   ERX  C  WP_ERASE_SKIP      (1=partial erase error due to write-protect) |
|       14   SX   A  CARD_ECC_DISABLED  (1=Internal error correction wasn't used)    |
|       13   SR   C  ERASE_RESET        (1=Erase sequence was aborted)               |
|       12-9 SX   B  CURRENT_STATE      (00h..0Fh=state, see below)                  |
|       8    SX   A  READY_FOR_DATA     (1=Ready/buffer is empty)                    |
|       7    EX   C  SWITCH_ERROR       (1=SWITCH command refused, MMC only)         |
|       6    -    -  Reserved/Unspecified (description is left blank)                |
|       5    SR   C  APP_CMD            (1=Card will expect ACMD)                    |
|       4    -    -  Reserved for SD I/O Card                                        |
|       3    ER   C  AKE_SEQ_ERROR      (1=Authentication Sequence Error)            |
|       2    -    -  Reserved for application specific commands                      |
|       1-0  -    -  Reserved for manufacturer test mode                             |
+------------------------------------------------------------------------------------+
```

Values for CURRENT_STATE (bit12-9):

```
+------------------------------------------------------------------------------------+
|       These bits indicate the OLD state of card when receiving the command,        |
|       (ie. if the command does change the state, then the NEW state won't be       |
|       seen until the NEXT command returns the new updated status bits)             |
|       00h     = idle                                                               |
|       01h     = ready                                                              |
|       02h     = ident                                                              |
|       03h     = stby                                                               |
|       04h     = tran    ;<-- normal state (when waiting for read/write commands)   |
|       05h     = data    ;data read  (CMD8,CMD11,CMD17,CMD18,CMD30,CMD56/R)         |
|       06h     = rcv     ;data write (CMD20?,CMD24,CMD25,CMD26,CMD27,CMD42,CMD56/W) |
|       07h     = prg     ;erase/wprot (CMD6,CMD28,CMD29,CMD38)                      |
|       08h     = dis                                                                |
|       09h     = btst    ;bus test write (CMD19, MMC only)                          |
|       0Ah     = slp     ;sleep (CMD5, MMC only)                                    |
|       0Bh-0Eh = reserved                                                           |
|       0Fh     = reserved for I/O mode (SDIO-only devices, without SD-memory)       |
|       N/A     = ina     ;inactive (CMD15) (card is killed, and can't send status)  |
|       N/A     = irq     ;interrupt mode (CMD40, MMC only)                          |
|       N/A     = pre     ;pre-idle (MMC only)                                       |
+------------------------------------------------------------------------------------+
```

Type aka Typ column (in above table):

```
+------------------------------------------------------------------------------+
|       E: Error bit.                                                          |
|       S: Status bit.                                                         |
|       R: Flag may get set within response of current command.                |
|       X: Flag may get set within response of NEXT command (with R1 response) |
+------------------------------------------------------------------------------+
```

Clear Condition aka Clr column (in above table):

```
+-------------------------------------------------------------------------------+
|       A: According to the card current state.                                 |
|       B: Always related to the previous command. Reception of a valid command |
|          will clear it (with a delay of one command).                         |
|       C: Clear by read.                                                       |
+-------------------------------------------------------------------------------+
```


### SPI Responses (8bit \"R1\" Responses, and 16bit \"R2\" Responses)

```
+-------------------------------------------------------------------------------------+
|      FIRST BYTE of all SPI Responses:                                               |
|       7  always 0                          ;\                                       
|       6  parameter error                   ; These 8bit are returned in ALL normal  |
|       5  address error                     ; SPI commands (with 8bit "R1" response) |
|       4  erase sequence error              ; and,                                   |
|       3  com crc error                     ; the same 8bits are also returned       |
|       2  illegal command                   ; as FIRST BYTE in SPI commands with     |
|       1  erase reset                       ; longer responses                       |
|       0  in idle state                     ;/                                       |
|      SECOND BYTE of SPI "R2" Response:                                              |
|       7  out of range, or csd overwrite           ;\                                
|       6  erase param                              ;                                 |
|       5  wp violation                             ; These extra 8bits are returned  |
|       4  card ecc failed                          ; as SECOND BYTE in SPI commands  |
|       3  CC error                                 ; with 16bit "R2" status response |
|       2  error                                    ; (ie. in CMD13 and ACMD13)       |
|       1  wp erase skip, or lock/unlock cmd failed ;                                 |
|       0  Card is locked                           ;/                                |
+-------------------------------------------------------------------------------------+
```


### Card Status Field/Command - Cross Reference
For each command responded by R1 response, following table defines the affected bits in the status field. An \'x\' means the error/status bit may be set in the response to the respective command.

```
+-----------------------------------------------------------------------------------+
|       Bits     31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12-9 8 5  |
|       CMD3                             x  x        x                    x         |
|       CMD6     x                 x     x  x  x  x  x                    x         |
|       CMD7                 x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD11                      x     x  x        x                    x         |
|       CMD12    x  x           x  x     x  x  x  x  x              x     x         |
|       CMD13    x  x        x  x  x  x  x  x  x  x  x        x  x  x     x    x    |
|       CMD16          x     x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD17    x  x        x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD18    x  x        x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD19    x  x        x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD20    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD23    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD24    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD25    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD26                x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD27                x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD28    x           x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD29    x           x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD30    x           x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD32    x        x  x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD33    x        x  x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD38             x  x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD42                x  x  x  x  x  x  x  x  x        x  x  x  x  x         |
|       CMD48    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD49    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD55                x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       CMD56                x  x  x  x  x  x  x  x  x        x  x  x  x  x    x  x |
|       CMD58    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       CMD59    x  x  x     x  x  x  x  x  x  x  x  x        x  x  x  x  x    x    |
|       ACMD6    x           x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       ACMD13               x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       ACMD22               x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       ACMD23               x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       ACMD42               x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
|       ACMD51               x  x  x  x  x  x  x  x  x        x  x  x  x  x       x |
+-----------------------------------------------------------------------------------+
```

Note: The response to CMD3 is R6 that includes only bits 23, 22, 19 and 12:9 out of the Card Status.



