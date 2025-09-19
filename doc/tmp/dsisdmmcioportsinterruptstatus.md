# DSi SD/MMC I/O Ports: Interrupt/Status


All SD/MMC IRQs are triggering IF2.8, CardIRQ does ADDITIONALLY trigger IF2.9
All SDIO IRQs are triggering IF2.10, CardIRQ does ADDITIONALLY trigger IF2.11?

### 400481Ch/4004A1Ch - SD_IRQ_STATUS0-1 - Interrupt Status (R/ack)
### 4004820h/4004A20h - SD_IRQ_MASK0-1 - Interrupt Mask (R/W)
The IRQ_STATUS registers contain acknowledge-able IRQ Flags (those bits that that are maskable in IRQ_MASK register), as well as static read-only status bits without IRQ function (eg. WRPROTECT).
IRQ Flags/Write (0=Acknowledge, 1=No change)
IRQ Flags/Read (0=No IRQ, 1=IRQ)
IRQ Mask (0=Enable, 1=Disable) (8B7F031Dh when all IRQs disabled)

```
+-------------------------------------------------------------------------------------+
|       Bit Stat  Mask  Function                                                      |
|       0   SREP  MREP  CMDRESPEND    (response end) (or R1b: busy end)               |
|       1   0     0     Unknown/unused (always 0)                                     |
|       2   SRWA  MRWA  DATAEND       (set after (last) data block end)               |
|       3   SCOT  MCOT  CARD_REMOVE (0=No event, 1=Is/was newly ejected)      ;\      
|       4   SCIN  MCIN  CARD_INSERT (0=No event, 1=Is/was newly inserted)     ; SD    |
|       5   undoc 0     SIGSTATE    (0=Ejected, 1=Inserted) (SDIO: always 1)  ; Slot  |
|       6   0     0     Unknown/unused (always 0)                             ; Sw's  |
|       7   undoc 0     WRPROTECT   (0=Locked/Ejected, 1=Unlocked/HalfEjected);/      |
|       8   undoc undoc CARD_REMOVE_A (0=No event, 1=High-to-Low occurred)    ;\SD    
|       9   undoc undoc CARD_INSERT_A (0=No event, 1=Low-to-High occurred)    ; Slot  |
|       10  undoc 0     SIGSTATE_A    (usually 1=High) ;also as so for SDIO   ;/Data3 |
|       11  0     0     Unknown/unused (always 0)                                     |
|       12  0     0     Unknown/unused (always 0)                                     |
|       13  0     0     Unknown/unused (always 0)                                     |
|       14  0     0     Unknown/unused (always 0)                                     |
|       15  0     0     Unknown/unused (always 0)                                     |
|       16  SCIX  MCIX  CMD_IDX_ERR   Bad CMD-index in response      (RCMDE,SCMDE)    |
|       17  SCRC  MCRC  CRCFAIL       CRC response error (WCRCE,RCRCE,SCRCE,CCRCE)    |
|       18  SEND  MEND  STOPBIT_ERR   End bit error      (WEBER,REBER,SEBER,CEBER)    |
|       19  SDTO  MDTO  DATATIMEOUT   Data Timeout                (NRCS,NWCS,KBSY)    |
|       20  SFOF  MFOF  RXOVERFLOW    HOST tried write full                           |
|       21  SFUF  MFUF  TXUNDERRUN    HOST tried read empty                           |
|       22  SCTO  MCTO  CMDTIMEOUT    Response start-bit timeout         (NRS,NSR)    |
|       23  undoc 0     DATA0_PIN (0=Low, 1=High) (of selected port: eMMC or SD Slot) |
|       24  SBRE  MBRE  RXRDY         (fifo not empty) (request data read)            |
|       25  SBWE  MBWE  TXRQ          (datafifoempty?) (request data write)           |
|       26  0     0     Unknown/unused (always 0)                                     |
|       27  undoc undoc Unknown/undoc  (bit27 is mask-able in IRQ_MASK)               |
|       28  0     0     Unknown/unused (always 0)                                     |
|       29  undoc 0     CMD_READY? (inverse of BUSY?) (unlike toshiba ILFSL/IFSMSK)   |
|       30  undoc 0     CMD_BUSY   (CMD_BUSY=0 shortly before CMD_READY=1?)           |
|       31  ILA   IMSK  Illegal Command Access (old CMD still busy, or wrong NTDT)    |
+-------------------------------------------------------------------------------------+
```

Normally, IRQs should be acknowledged by writing \"FLAGS=NOT X\", whilst the firmware is using an unstable \"FLAGS=FLAGS AND NOT X\" read-modify-write function (accidentally acknowledging any IRQs that have newly occurred during that operation).

### 4004836h/4004A36h - SD_CARD_IRQ_STAT (R/ack)
### 4004838h/4004A38h - SD_CARD_IRQ_MASK (R/W)
IRQ Flags/Write (0=Acknowledge, 1=No change)
IRQ Flags/Read (0=No IRQ, 1=IRQ)
IRQ Mask (0=Enable, 1=Disable) (C007h when all IRQs disabled)

```
+-------------------------------------------------------------------------------------+
|       Bit  Stat  Mask   Function                                                    |
|       15   undoc undoc  SomeIRQ (triggered SOMETIMES on forced CMDTIMEOUT?)         |
|       14   undoc undoc  SomeIRQ (triggered near DATAEND?)                           |
|       13-3 0     0      Always zero                                                 |
|       2    undoc undoc  SomeIRQ (triggered on forced TXUNDERRUN?)                   |
|       1    undoc undoc  SomeIRQ (triggered about once per datablock?)               |
|       0    CINT0 CIMSK0 CardIRQ (triggered by /IRQ aka Data1 pin; for SDIO devices) |
+-------------------------------------------------------------------------------------+
```

All stat bits (except bit1) are triggered only if enabled in SD_CARD_IRQ_CTL.
Bit0 is actually used (for SDIO hardware), the other bits aren\'t used by existing software (they don\'t seem to be useful; purpose might be error testing, or forcing commands to abort).

### 4004834h/4004A34h - SD_CARD_IRQ_CTL (R/W)
CardIRQ Enable works only when also writing SD_CARD_PORT_SELECT.bit10=0 and only with valid SD_CARD_CLK_CTL setting.

```
+-------------------------------------------------------------------------------------+
|       15-10  Always zero                                                            |
|       9      Enable setting SD_CARD_IRQ_STAT.bit14 and cause nothing special? (R/W) |
|       8      Enable setting SD_CARD_IRQ_STAT.bit15 and cause CMDTIMEOUT?      (R/W) |
|       7-3    Always zero                                                            |
|       2      Enable setting SD_CARD_IRQ_STAT.bit2 and cause TXUNDERRUN?       (R/W) |
|       1      Always zero                                                            |
|       0      Enable setting SD_CARD_IRQ_STAT.bit0 (CardIRQ upon Data1=LOW)    (R/W) |
+-------------------------------------------------------------------------------------+
```

Bit9 is autocleared at time when bit9 causes setting SD_CARD_IRQ_STAT.bit14.
Bit2 is autocleared shortly before bit8 causes CMDTIMEOUT.
SD_CARD_IRQ_STAT.bit15 is set only when setting bit8 AND bit2 DURING cmd/xfer.

### 40048F8h/40048FAh - SD_EXT_IRQ_STAT0-1 - Interrupt Status (R/ack)
### 40048FCh/40048FEh - SD_EXT_IRQ_MASK0-1 - Interrupt Mask (R/W)
The 3DS bootroom is using bit0-2 for eMMC insert/eject detection. DSi software isn\'t doing such stuff (though the registers seem to exist in DSi hardware, too). Either way, eMMC cannot be ejected on neither DSi nor 3DS, so the feature is kinda useless.

```
+-------------------------------------------------------------------------------------+
|       Bit   Stat  Mask  Function                                                    |
|       0     SCOT  MCOT  CARD_REMOVE (0=No event, 1=Is/was newly ejected)     ;\eMMC 
|       1     SCIN  MCIN  CARD_INSERT (0=No event, 1=Is/was newly inserted)    ; Slot |
|       2     undoc 1     SIGSTATE    (MMC: Always 1=Inserted) (SDIO: always 0);/Sw   |
|       3     0     RW    Unknown (stat always 0, but mask is R/W)   ;\maybe another  
|       4     0     RW    Unknown (stat always 0, but mask is R/W)   ; unimplemented  |
|       5     0     1     Unknown (stat always 0, and mask always 1) ;/device?        |
|       6     0     RW    Unknown (stat always 0, but mask is R/W)   ;\maybe yet one  
|       7     0     RW    Unknown (stat always 0, but mask is R/W)   ; more?          |
|       8-15  0     0     Unknown/unused (always 0)                  ;/               |
|       16    ??    RW    Unknown (stat can be 0/1)               (R/W? or rather R?) |
|       17    ??    RW    Unknown (stat can be 0/1)               (R/W? or rather R?) |
|       18    ??    1     Unknown (1=normal, 0=data/read from card to fifo busy?) (R) |
|       19    0     RW    Unknown (stat always 0, but mask is R/W)                    |
|       20    0     RW    Unknown (stat always 0, but mask is R/W)                    |
|       21    0     1     Unknown (stat always 0, and mask always 1)                  |
|       22    0     RW    Unknown (stat always 0, but mask is R/W)                    |
|       23    0     RW    Unknown (stat always 0, but mask is R/W)                    |
|       24-31 0     0     Unknown/unused (always 0)                                   |
+-------------------------------------------------------------------------------------+
```

Some of the unknown bits might be CD/Data3 or IRQ/Data1 pins for Device 1, in similar way as for Device 0 (maybe that is in bit16-18, which are observed to become nonzero in certain situations).
EXT_IRQ_STAT can be 00000000h..00070004h for MMC, or always 00000000h for SDIO (as there\'s only one device on SDIO bus). EXT_IRQ_MASK is R/W (can be 00240024h..00FF00FFh) for both SD/MMC and SDIO.

### 4004900h/4004B00h - SD_DATA32_IRQ

```
+------------------------------------------------------------------------------------+
|       15-13  Always zero                                                           |
|       12     TX32RQ IRQ Enable   (0=Disable, 1=Enable)                       (R/W) |
|       11     RX32RDY IRQ Enable  (0=Disable, 1=Enable)                       (R/W) |
|       10     Clear FIFO32        (0=No change, 1=Force FIFO32 Empty)         (W)   |
|       9      TX32RQ IRQ Flag     (0=IRQ, 1=No) (0=FIFO32 Empty)              (R)   |
|       8      RX32RDY IRQ Flag    (0=No, 1=IRQ) (1=FIFO32 Full)               (R)   |
|       7-2    Always zero                                                           |
|       1      Select 16bit/32bit Data Mode (0=DATA16, 1=DATA32, see 40048D8h) (R/W) |
|       0      Always zero                                                           |
+------------------------------------------------------------------------------------+
```

Bit8,9 are extra IRQ flags, the flags get set ONLY in DATA32 mode (not in DATA16 mode).
Bit8,9 are somewhat edge-triggered (setting the IF2 bit only on NoIRQ-to-IRQ transitions; whilst Disable-to-Enable transitions don\'t trigger IF2).
Bit8,9 don\'t need to be acknowledged, they are automatically switched to \"No IRQ\" by hardware (when reading/writing DATA32_FIFO, ie. when the FIFO is no longer empty/full).

### 400482Ch/4004A2Ch - SD_ERROR_DETAIL_STATUS0-1 - Error Detail Status (R)
This register contains extra info about the error bits in SD_IRQ_STATUS. The error bits (except bit13/always set) are automatically cleared when sending a new command by writing to SD_CMD.

```
+------------------------------------------------------------------------------------+
|       31-23 0      Always zero                                                     |
|       22    KBSY   Timeout for CRC status busy                          ;\STAT.19  
|       21    NWCS   Timeout for CRC status   (can occur for Data Write)  ; (SDTO)   |
|       20    NRCS   Timeout for Data start-bit, or for Post Data Busy    ;/         |
|       19-18 0      Always zero                                                     |
|       17    NRS    Response Timeout for auto-issued CMD12               ;\STAT.22  
|       16    NCR    Response Timeout for non-auto-issued CMD's           ;/(SCTO)   |
|       15-14 0      Always zero                                                     |
|       13    undoc  Unknown/undoc (always 1)                             ;-Always 1 |
|       12    0      Always zero                                                     |
|       11    WCRCE  CRC error for Write CRC status for a write command   ;\         
|       10    RCRCE  CRC error for Read Data                              ; STAT.17  |
|       9     SCRCE  CRC error for a Response for auto-issued CMD12       ; (SCRC)   |
|       8     CCRCE  CRC error for a Response for non-auto-issued CMD's   ;/         |
|       5     WEBER  End bit error for Write CRC status                   ;\         
|       4     REBER  End bit error for Read Data                          ; STAT.18  |
|       3     SEBER  End bit error for Response for auto-issued CMD12     ; (SEND)   |
|       2     CEBER  End bit error for Response for non-auto-issued CMD's ;/         |
|       1?    SCMDE  Bad CMD-index in Response of auto-issued CMD12       ;\STAT.16  
|       0     RCMDE  Bad CMD-index in Response of non-auto-issued CMD's   ;/(SCIX)   |
+------------------------------------------------------------------------------------+
```

Note: CMD12 is STOP_TRANSMISSION (automatically sent after BLK_COUNT blocks).
The four \"auto-issued CMD12\" bits exist for SD registers only (not for SDIO, going by old toshiba datasheets; which may be wrong).
SCMDE is probably in bit1 (though, official specs say bit0, which would be same as RCMDE).
Some error bits can be intentionally provoked: Bit8=1 when programming the controller to expect GET_STATUS to return a 136bit response. Bit16=1 when sending GET_CID in \"tran\" state. Bit20=1 when sending GET_STATUS configured to expect a data/read reply. Bit21=1 when sending GET_STATUS configured to expect a data/write block (and with actually sending a data block to it).

### 40048F6h/4004AF6h - SD_WRPROTECT_2 (RESERVED4) (R)

```
+-------------------------------------------------------------------------------------+
|       15-1   Always zero                                                            |
|       0      WRPROTECT_2 for onboard eMMC (usually/always 0=Unlocked)           (R) |
+-------------------------------------------------------------------------------------+
```

Bit0 is write-protect flag for onboard eMMC (equivalent to the SD/MMC slot\'s write-protect switch in 400481Ch.bit7, but in inverted form: 0=Unlocked for eMMC, instead of 0=Locked for SD/MMC). The firmware does check bit0 (and, if set, hangs shortly before starting games), unknown if the TWL CPU and DSi mainboard do actually have any solder pads for it.

### IRQ Edge-Triggering
One nasty \"feature\" for both IRQ_STATUS and DATA32_IRQ is that the interrupts are edge-triggered (IF2.bit8 gets set only on No-IRQ-to-IRQ transitions) (IF2 can be acknowledged even if IRQ(s) are still requested, which would mean that those IRQ(s) would get lost). Workaround would be:

```
+------------------------------------------------------------------------------+
|      - first acknowledge IF2.bit8 (must be done before next step)            |
|      - then check for pending IRQs in IRQ_STATUS and DATA32_IRQ, and process |
|        all of them                                                           |
+------------------------------------------------------------------------------+
```

Ie. if you would process only a single IRQ, then any other IRQs would get lost.
For IRQ_STATUS, one could also force unprocessed IRQs to re-trigger IF2 by temporarily disabling IRQ_MASK bits (disable-to-enable for pending IRQs is also edge-triggering IF2). That trick works for IRQ_STATUS only, not for DATA32_IRQ.



