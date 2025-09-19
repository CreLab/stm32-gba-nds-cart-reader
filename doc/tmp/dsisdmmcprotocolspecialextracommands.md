# DSi SD/MMC Protocol: Special Extra Commands



```
+------------------------------------------------------------------------------------+
|      _________________________ Write PROTECTION Commands _________________________ |
+------------------------------------------------------------------------------------+
```


### CMD28 - SDSC/MMC (not SDHC/SDXC) - SPI - SET_WRITE_PROT (type=ac)
### CMD29 - SDSC/MMC (not SDHC/SDXC) - SPI - CLR_WRITE_PROT (type=ac)

```
+--------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: Unsupported) |
+--------------------------------------------------------------------------+
```

Response: R1b
Additional Data Transfer (from card): Busy signal for \"R1b\" response
Write protection support is indicated in CSD(WP_GRP_ENABLE), and additionally \"class 6\" should be flagged in CSD(CCC). The group size is indicated in CSD(WP_GRP_SIZE), observe that that field is 5bit/7bit wide for SD/MMC accordingly.

### CMD30 - SDSC/MMC (not SDHC/SDXC) - SPI - GET_WRITE_PROT (type=adtc)

```
+--------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: Unsupported) |
+--------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+------------------------------------------------------------------------------------+
|       31-0  Flags (1=write-protected) (bit0=addressed group, bit1..31=next groups) |
+------------------------------------------------------------------------------------+
```

If the card provides write protection features, this command asks the card to send the status of the write protection bits: 32 write protection bits (representing 32 write protect groups starting at the specified address) followed by 16 CRC bits are transferred in a payload format via the DATA line. The last (least significant) bit of the protection bits corresponds to the first addressed group. If the addresses of the last groups are outside the valid range, then the corresponding write protection bits shall be set to 0.

### CMD31 - MMC - GET_WRITE_PROT_TYPE (type=adtc)

```
+--------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: Unsupported) |
+--------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-------------------------------------------------------------------------------+
|       63-0  Flags (1=write-protected) (bit0-1=addressed group, bit2..63=next) |
+-------------------------------------------------------------------------------+
```

Returns thirty-two 2bit values (0=not protected, 1=temporary write protection, 2=power-on write protection, 3=permanent write protection).

### Further Write-Protection Mechanisms
The whole card can be write-protected via PERM_WRITE_PROTECT and TMP_WRITE_PROTECT bits in CSD register (supported for MMC and SDSC/SDHC/SDXC).
SD Cards (and SD Card adaptors for miniSD and microSD cards) are additionally having a mechanical \"LOCK\" write protection tab (MMC cards don\'t have that feature).
The PWD feature provides Read/Write-protection (when not knowing the password).


```
+-------------------------------------------------------------------------------------+
|      _______________________________ Erase Commands _______________________________ |
+-------------------------------------------------------------------------------------+
```


### CMD32 - SD - SPI - ERASE_WR_BLK_START (type=ac)
### CMD33 - SD - SPI - ERASE_WR_BLK_END (type=ac)

```
+--------------------------------------------------------------------------------+
|       31-0  data address (SDSC: in 1-byte units, SDHC/SDXC: in 512-byte units) |
+--------------------------------------------------------------------------------+
```

Response: R1
Sets the address of the first/last write block of the continuous range to be erased.

### CMD35 - MMC - SPI - ERASE_GROUP_START (type=ac)
### CMD36 - MMC - SPI - ERASE_GROUP_END (type=ac)

```
+-----------------------------------------------------------------------+
|       31-0  data address (MMC: in WHAT units?)                        |
+-----------------------------------------------------------------------+
```

Response: R1
MMC only. Unknown, maybe similar to above SD commands?

### CMD32-34,37 - SPI - MMC - Reserved for compatibility with older MMC cards
MMC only. Unknown, maybe also Erase related?

### CMD38 - SD/MMC - SPI - ERASE (type=ac)

```
+-----------------------------------------------------------------------+
|       31-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: R1b
Additional Data Transfer (from card): Busy signal for \"R1b\" response
Erases all previously selected write blocks.

### Further Erase Commands
Sectors are automatically erased on-the-fly when writing data blocks, so manually using above erase commands isn\'t really necessary; it may be useful for shreddering private data though, and it might also speed up subsequent writes since the writes can omit the on-the-fly erasing step.
The SET_WR_BLK_ERASE_COUNT (ACMD23) can be used to notify the card that it may pre-erase multiple sectors upon write commands (eg. to speed-up cluster writes that are spanning across multiple sectors).
The password lock feature includes a Forced Erase function, which will reset the password, and ERASE THE WHOLE CARD, this may be useful if the user has forgot the password, but will destroy data (possibly including the pre-formatted filesystem headers; which would be bad, because that headers should contain cluster sizes somewhat matched to the physical sector sizes).


```
+-------------------------------------------------------------------------------------+
|      ________________________________ I/O Commands ________________________________ |
+-------------------------------------------------------------------------------------+
```


### CMD5 - SD - SPI - Reserved for I/O cards
### CMD52-54 - SD - SPI - Commands for SDIO

```
+-----------------------------------------------------------------------+
|       CMD5  SDIO: IO_SEND_OP_COND                                     |
|       CMD52 SDIO: IO_RW_DIRECT                                        |
|       CMD53 SDIO: IO_RW_EXTENDED                                      |
+-----------------------------------------------------------------------+
```

Refer to the \"SDIO Card Specification\". SDIO is an extension to the SD protocol that allows to access non-memory-card hardware (such like cameras or network adaptors).


```
+-------------------------------------------------------------------------------------+
|      __________________________ Switch Function Commands __________________________ |
+-------------------------------------------------------------------------------------+
```


### CMD6 - SD (SD v1.10 and up) - SPI - SWITCH_FUNC (type=adtc)

```
+-------------------------------------------------------------------------------+
|       31     Mode (0=Check function, 1=Switch function)                       |
|       30-24  reserved (All '0')                                               |
|       23-20  function group 6: Reserved (0h or Fh)                            |
|       19-16  function group 5: Reserved (0h or Fh)                            |
|       15-12  function group 4: Power Limit     ;SPI Mode: Reserved (0h or Fh) |
|       11-8   function group 3: Drive Strength  ;SPI Mode: Reserved (0h or Fh) |
|       7-4    function group 2: Command System                                 |
|       3-0    function group 1: Access Mode                                    |
+-------------------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to/from whatever):

```
+-----------------------------------------------------------------------+
|       unknown                                                         |
+-----------------------------------------------------------------------+
```

Checks switch-able function (mode 0) and switch card function (mode 1). See Chapter 4.3.10.

### CMD34-35 - SD - Reserved
Reserved for each command system set by switch function command (CMD6).
Detailed definition is referred to each command system specification.
Maybe related to above \"function group 5..6\"?

### CMD36,37 - SD - Undoc (description field is held blank)
### CMD50,57 - SD - Undoc (description field is held blank)
Undoc. Maybe related to above \"function group 1..4\"?

### SPI: CMD34-37 - SD - SPI - Reserved for Command Systems from CMD6
### SPI: CMD50,57 - SD - SPI - Reserved for Command Systems from CMD6
Described as so for SPI Mode. Maybe related to above \"function group 1..6\"?


```
+------------------------------------------------------------------------------------+
|      ________________________ Function Extension Commands ________________________ |
+------------------------------------------------------------------------------------+
```


### CMD21 - SD - Reserved for DPS Specification (Data Protection System)
Reserved.

### CMD48 - SD (optional, see SCR.Bit34) - READ_EXTR_SINGLE (type=adtc)

```
+-----------------------------------------------------------------------+
|       31     MIO (0=Memory, 1=I/O)                                    |
|       30-27  FNO                                                      |
|       26     Reserved (0)                                             |
|       25-9   ADDR                                                     |
|       8-0    LEN                                                      |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       whatever                                                        |
+-----------------------------------------------------------------------+
```

Single block read type. Refer to Section 5.7.2.1.

### CMD49 - SD (optional, see SCR.Bit34) - WRITE_EXTR_SINGLE (type=adtc)

```
+-----------------------------------------------------------------------+
|       31     MIO (0=Memory, 1=I/O)                                    |
|       30-27  FNO                                                      |
|       26     MW                                                       |
|       25-9   ADDR                                                     |
|       8-0    LEN/MASK                                                 |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to card):

```
+-----------------------------------------------------------------------+
|       whatever                                                        |
+-----------------------------------------------------------------------+
```

Single block write type. Refer to Section 5.7.2.2.

### CMD58 - SD (optional, see SCR.Bit35) - READ_EXTR_MULTI (type=adtc)

```
+-----------------------------------------------------------------------+
|       31     MIO (0=Memory, 1=I/O)                                    |
|       30-27  FNO                                                      |
|       26     BUS (0=512B, 1=32KB)                                     |
|       25-9   ADDR                                                     |
|       8-0    BUC                                                      |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (from card):

```
+-----------------------------------------------------------------------+
|       whatever                                                        |
+-----------------------------------------------------------------------+
```

Multi-block read type. Refer to Section 5.7.2.4.

### CMD59 - SD (optional, see SCR.Bit35) - WRITE_EXTR_MULTI (type=adtc)

```
+-----------------------------------------------------------------------+
|       31     MIO (0=Memory, 1=I/O)                                    |
|       30-27  FNO                                                      |
|       26     BUS (0=512B, 1=32KB)                                     |
|       25-9   ADDR                                                     |
|       8-0    BUC                                                      |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to card):

```
+-----------------------------------------------------------------------+
|       whatever                                                        |
+-----------------------------------------------------------------------+
```

Multi-block write type. Refer to Section 5.7.2.5.

Note: CCC bit 11 is set to 1 when any command of class 11 is supported. Supporting of these commands is indicated in SCR register.



