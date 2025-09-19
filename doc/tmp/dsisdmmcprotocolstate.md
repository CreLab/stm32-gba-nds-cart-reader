# DSi SD/MMC Protocol: State


### SD/MMC State
The \"state\" is an important SD/MMC feature to deal with - most commands can be send only in certain states:
For normal operation, the card should be in \"tran\" state (and it may then temporarily switch to \"data/rcv/prg\" states during read/write/erase commands).
For initialization, the card should be first forced to \"idle\" state, and the init commands should then go through \"ready/ident/stby\" states, until finally reaching \"tran\" state.
Less important states are \"dis/ina\", and, on MMC only, \"btst/slp/irq\" and \"pre-idle\".
Both SD and MMC specs are leaving state undocumented for SPI mode (meaning that SPI specific commands like CMD58/CMD59 are supported only in \"unknown\" state).

### SD Card State Transition Table

```
+-------------------------------------------------------------------------------------+
|       Command       old state --> idle readyidentstby tran data rcv  prg  dis  ina  |
|       DONE  Operation Complete    ---- ---- ---- ---- ---- tran ---- tran stby ---- |
|       class 0                                                                       |
|       CMD0  GO_IDLE_STATE         ok   idle idle idle idle idle idle idle idle ---- |
|       CMD2  ALL_SEND_CID          ---- ident---- ---- ---- ---- ---- ---- ---- ---- |
|       CMD3  SEND_RELATIVE_ADDR    ---- ---- stby ok   ---- ---- ---- ---- ---- ---- |
|       CMD4  SET_DSR               ---- ---- ---- ok   ---- ---- ---- ---- ---- ---- |
|       CMD7  SELECT_DESELECT_CARD                                                    |
|             card is addressed     ---- ---- ---- tran ---- ---- ---- ---- prg  ---- |
|             card is not addr.     ---- ---- ---- ok   stby stby ---- dis  ---- ---- |
|       CMD8  SEND_IF_COND          ok   ---- ---- ---- ---- ---- ---- ---- ---- ---- |
|       CMD9  SEND_CSD              ---- ---- ---- ok   ---- ---- ---- ---- ---- ---- |
|       CMD10 SEND_CID              ---- ---- ---- ok   ---- ---- ---- ---- ---- ---- |
|       CMD11 VOLTAGE_SWITCH        ---- ok   ---- ---- ---- ---- ---- ---- ---- ---- |
|       CMD12 STOP_TRANSMISSION     ---- ---- ---- ---- ---- tran prg  ---- ---- ---- |
|       CMD13 SEND_STATUS           ---- ---- ---- ok   ok   ok   ok   ok   ok   ---- |
|       CMD15 GO_INACTIVE_STATE     ---- ---- ---- ina  ina  ina  ina  ina  ina  ---- |
|       class 2                                                                       |
|       CMD16 SET_BLOCKLEN          ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       CMD17 READ_SINGLE_BLOCK     ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD18 READ_MULTIPLE_BLOCK   ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD19 SEND_TUNING_BLOCK     ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD20 SPEED_CLASS_CONTROL   ---- ---- ---- ---- prg  ---- ---- ---- ---- ---- |
|       CMD23                       ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       class 4                                                                       |
|       CMD16 SET_BLOCKLEN       (2)---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       CMD20 SPEED_CLASS_CONTROL(2)---- ---- ---- ---- prg  ---- ---- ---- ---- ---- |
|       CMD23 SET_BLOCK_COUNT       ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       CMD24 WRITE_BLOCK           ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       CMD25 WRITE_MULTIPLE_BLOCK  ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       CMD27 PROGRAM_CSD           ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       class 6                                                                       |
|       CMD28 SET_WRITE_PROT        ---- ---- ---- ---- prg  ---- ---- ---- ---- ---- |
|       CMD29 CLR_WRITE_PROT        ---- ---- ---- ---- prg  ---- ---- ---- ---- ---- |
|       CMD30 SEND_WRITE_PROT       ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       class 5                                                                       |
|       CMD32 ERASE_WR_BLK_START    ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       CMD33 ERASE_WR_BLK_END      ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       CMD38 ERASE                 ---- ---- ---- ---- prg  ---- ---- ---- ---- ---- |
|       class 7                                                                       |
|       CMD40 Read Block (DPS Spec) ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD42 LOCK_UNLOCK           ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       class 8                                                                       |
|       CMD55 APP_CMD               ok   ---- ---- ok   ok   ok   ok   ok   ok   ---- |
|       CMD56 GEN_CMD, RD/WR=0      ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|             GEN_CMD, RD/WR=1      ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       ACMD6  SET_BUS_WIDTH        ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       ACMD13 SD_STATUS            ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       ACMD22 SEND_NUM_WR_BLOCKS   ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       ACMD23 SET_WR_BLK_ERASE_CO. ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       ACMD41 SD_SEND_OP_COND                                                        |
|            OCR check is OK                                                          |
|            and card is not busy   ready---- ---- ---- ---- ---- ---- ---- ---- ---- |
|            OCR check is OK                                                          |
|            and card is busy(2)    ok   ---- ---- ---- ---- ---- ---- ---- ---- ---- |
|            OCR check fails                                                          |
|            query mode             ina  ---- ---- ---- ---- ---- ---- ---- ---- ---- |
|       ACMD42 SET_CLR_CARD_DETECT  ---- ---- ---- ---- ok   ---- ---- ---- ---- ---- |
|       ACMD51 SEND_SCR             ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       class 9                                                                       |
|       class 10 (1)                                                                  |
|       CMD6  SWITCH_FUNC           ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       class 11                                                                      |
|       CMD48 READ_EXTR_SINGLE      ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD49 WRITE_EXTR_SINGLE     ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       CMD58 READ_EXTR_MULTI       ---- ---- ---- ---- data ---- ---- ---- ---- ---- |
|       CMD59 WRITE_EXTR_MULTI      ---- ---- ---- ---- rcv  ---- ---- ---- ---- ---- |
|       ACMD14-16               Refer to DPS Specification (class 8)                  |
|       ACMD28                  Refer to DPS Specification (class 8)                  |
|       ACMD18,25,26,38,                                                              |
|       43,44,45,46,47,48,49    Refer to the "Part3 Security Specification" for       |
|                               information about the SD Security Features (class 8)  |
|       CMD52-CMD54             Refer to the "SDIO Card Specification" (class 9)      |
|       CMD21                   Refer to DPS Specification (class 11)                 |
|       CMD34-37,50,57          Refer to each command system specification (class 10) |
|       CMD41,CMD43-47          reserved (class 11)                                   |
|       CMD60...CMD63           reserved for manufacturer (class 11)                  |
|       SPI Mode                                                                      |
|       CMD1 SEND_OP_COND       SPI-only                                              |
|       CMD58 READ_OCR          SPI-only                                              |
|       CMD59 CRC_ON_OFF        SPI-only                                              |
+-------------------------------------------------------------------------------------+
```

Note (1): Class 10 commands were defined in Version 1.10.
Note (2): Card returns busy in case of following:

```
+-----------------------------------------------------------------------+
|       - Card executes internal initialization process                 |
|       - When HCS in the argument is set to 0 to SDHC or SDXC Card.    |
+-----------------------------------------------------------------------+
```

The state transitions of the SD Memory Card application-specific commands are given under Class 8, above.

```
+-----------------------------------------------------------------------+
|       ----  command is treated as illegal command                     |
|       ok    command is accepted, and card stays in SAME state         |
|       xxx   command is accepted, and card switches to "xxx" state     |
+-----------------------------------------------------------------------+
```


### MMC Card State Transition Table (JEDEC)

```
+-------------------------------------------------------------------------------------+
|       Command     old state --> idl rdy idt stb trn dta tst rcv prg dis ina slp irq |
|       Class Independent                                                             |
|       ERR  CRC error            --- --- --- --- --- --- --- --- --- --- --- --- stb |
|       ERR  command not supported--- --- --- --- --- --- --- --- --- --- --- --- stb |
|       Class 0                                                                       |
|       CMD0  (arg=00000000h)     ok  idl idl idl idl idl idl idl idl idl --- idl stb |
|             GO_IDLE_STATE                                                           |
|       CMD0  (arg=F0F0F0F0h)     pre pre pre pre pre pre pre pre pre pre --- pre stb |
|             GO_PRE_IDLE_STATE                                                       |
|       CMD0  (arg=FFFFFFFAh)     initiate alternative boot operation                 |
|             BOOT_INITIATION                                                         |
|       CMD1  SEND_OP_COND                                                            |
|             card VDD range ok   rdy --- --- --- --- --- --- --- --- --- --- --- stb |
|             card is busy        ok  --- --- --- --- --- --- --- --- --- --- --- stb |
|             card VDD range bad  ina --- --- --- --- --- --- --- --- --- --- --- stb |
|       CMD2  ALL_SEND_CID                                                            |
|              card wins bus      --- idt --- --- --- --- --- --- --- --- --- --- stb |
|              card loses bus     --- ok  --- --- --- --- --- --- --- --- --- --- stb |
|       CMD3  SET_RELATIVE_ADDR   --- --- stb --- --- --- --- --- --- --- --- --- stb |
|       CMD4  SET_DSR             --- --- --- ok  --- --- --- --- --- --- --- --- stb |
|       CMD5  SLEEP_AWAKE         --- --- --- slp -?- -?- -?- -?- -?- -?- -?- stb stb |
|       CMD6  SWITCH              --- --- --- --- prg --- --- --- --- --- --- --- stb |
|       CMD7  SELECT_DESELECT_CARD                                                    |
|             card is addressed   --- --- --- trn --- --- --- --- --- prg --- --- stb |
|             card is not addr.   --- --- --- --- stb stb --- --- dis --- --- --- stb |
|       CMD8  SEND_EXT_CSD        --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       CMD9  SEND_CSD            --- --- --- ok  --- --- --- --- --- --- --- --- stb |
|       CMD10 SEND_CID            --- --- --- ok  --- --- --- --- --- --- --- --- stb |
|       CMD12 STOP_TRANSMISSION   --- --- --- --- --- trn --- prg --- --- --- --- stb |
|       CMD13 SEND_STATUS         --- --- --- ok  ok  ok  ok  ok  ok  ok  --- --- stb |
|       CMD14 BUSTEST_R           --- --- --- --- --- --- trn --- --- --- --- --- stb |
|       CMD15 GO_INACTIVE_STATE   --- --- --- ina ina ina ina ina ina ina --- --- stb |
|       CMD19 BUSTEST_W           --- --- --- --- tst --- --- --- --- --- --- --- stb |
|       Class 1                                                                       |
|       CMD11 READ_DAT_UNTIL_STOP --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       Class 2                                                                       |
|       CMD16 SET_BLOCKLEN        --- --- --- --- ok  --- --- --- --- --- --- --- stb |
|       CMD17 READ_SINGLE_BLOCK   --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       CMD18 READ_MULTIPLE_BLOCK --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       CMD23 SET_BLOCK_COUNT     --- --- --- --- ok  --- --- --- --- --- --- --- stb |
|       Class 3                                                                       |
|       CMD20 WRITE_DAT_UNTIL_STOP--- --- --- --- rcv --- --- --- --- --- --- --- stb |
|       Class 4                                                                       |
|       CMD16 SET_BLOCKLEN        see class 2                                         |
|       CMD23 SET_BLOCK_COUNT     see class 2                                         |
|       CMD24 WRITE_BLOCK         --- --- --- --- rcv --- --- --- rcv1--- --- --- stb |
|       CMD25 WRITE_MULTIPLE_BL.  --- --- --- --- rcv --- --- --- rcv2--- --- --- stb |
|       CMD26 PROGRAM_CID         --- --- --- --- rcv --- --- --- --- --- --- --- stb |
|       CMD27 PROGRAM_CSD         --- --- --- --- rcv --- --- --- --- --- --- --- stb |
|       Class 6                                                                       |
|       CMD28 SET_WRITE_PROT      --- --- --- --- prg --- --- --- --- --- --- --- stb |
|       CMD29 CLR_WRITE_PROT      --- --- --- --- prg --- --- --- --- --- --- --- stb |
|       CMD30 SEND_WRITE_PROT     --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       CMD31 SEND_WRITE_PROT_TYPE--- --- --- --- dta --- --- --- --- --- --- --- stb |
|       Class 5                                                                       |
|       CMD35 ERASE_GROUP_START   --- --- --- --- ok  --- --- --- --- --- --- --- stb |
|       CMD36 ERASE_GROUP_END     --- --- --- --- ok  --- --- --- --- --- --- --- stb |
|       CMD38 ERASE               --- --- --- --- prg --- --- --- --- --- --- --- stb |
|       Class 7                                                                       |
|       CMD16 SET_BLOCKLEN        see class 2                                         |
|       CMD42 LOCK_UNLOCK         --- --- --- --- rcv --- --- --- --- --- --- --- stb |
|       Class 8                                                                       |
|       CMD55 APP_CMD             --- --- --- ok  ok  ok  ok  ok  ok  ok  --- --- ok  |
|       CMD56 GEN_CMD, RD/WR=0    --- --- --- --- rcv --- --- --- --- --- --- --- stb |
|             GEN_CMD, RD/WR=1    --- --- --- --- dta --- --- --- --- --- --- --- stb |
|       Class 9                                                                       |
|       CMD39 FAST_IO             --- --- --- ok  --- --- --- --- --- --- --- --- stb |
|       CMD40 GO_IRQ_STATE        --- --- --- irq --- --- --- --- --- --- --- --- stb |
|       Class 10-11                                                                   |
|       CMD41, CMD43..CMD54       Reserved                                            |
|       CMD57..CMD59              Reserved                                            |
|       CMD60..CMD63              Reserved for Manufacturer                           |
|       SPI Mode                                                                      |
|       CMD58 READ_OCR            SPI-only                                            |
|       CMD59 CRC_ON_OFF          SPI-only                                            |
+-------------------------------------------------------------------------------------+
```

NOTE 1. Due to legacy considerations, a card may treat CMD24/25 during a prg state_while busy is active_as a legal or an illegal command. A card that treats CMD24/25 during a prg-state_while busy is active_as an illegal command will not change its state to the rcv state. A host should not send CMD24/25 while the card is in prg state and busy is active.
NOTE 2. Due to legacy considerations, a card may treat CMD24/25 during a prg state_while busy is active_as a legal or an illegal command. A card that treats CMD24/25 during a prg state_while busy is active_as an illegal command will not change its state to the rcv state. A host should not send CMD24/25 while the card is in prg state and busy is active.
NOTE 3. As there is no way to obtain state information in boot mode, boot-mode states are not shown in this table.

```
+-----------------------------------------------------------------------+
|       pre  Pre-idle                                                   |
|       idl  idle                                                       |
|       rdy  ready                                                      |
|       idt  ident                                                      |
|       stb  stby                                                       |
|       trn  tran                                                       |
|       dta  data                                                       |
|       tst  btst                                                       |
+-----------------------------------------------------------------------+
```




