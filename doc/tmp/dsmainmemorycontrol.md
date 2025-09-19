# DS Main Memory Control


### Main Memory
The DS Main Memory is 2Mx16bit (4MByte), 1.8V Pseudo SRAM (PSRAM); all Dynamic RAM refresh is handled internally, the chip doesn\'t require any external refresh signals, and alltogether behaves like Static RAM. Non-sequential access time is 70ns, sequential (burst) access time is 12ns.

### Main Memory Control
The memory chips contain built-in Control functions, which can be accessed via Port 27FFFFEh and/or by EXMEMCNT Bit 14. Nintendo is using at least two different types of memory chips in DS consoles, Fujitsu 82DBS02163C-70L, and ST M69AB048BL70ZA8, both appear to have different control mechanisms, other chips (with 8MB size) are used in the semi-professional DS hardware debuggers, and further chips may be used in future, so using the memory control functions may lead into compatibitly problems.

### Power Consumption / Power Control
Power Consumption during operation (read/write access) is somewhat 30mA, in standby mode (no read/write access) consumption is reduced to 100uA.
Furthermore, a number of power-down modes are supported: In \"Deep\" Power Down mode the refresh is fully disabled, consumption is 10uA (and all data will be lost), in \"Partial\" Power Down modes only fragment of memory is refreshed, for smallest fragments, consumption goes to down to circa 50uA. The chip cannot be accessed while it is in Deep or Partial Power Down mode.

### Fujitsu 82DBS02163C-70L
The Configuration Register (CR) can be written to by the following sequence:

```
+-----------------------------------------------------------------------------+
|       LDRH R0,[27FFFFEh]      ;read one value                               |
|       STRH R0,[27FFFFEh]      ;write should be same value as above          |
|       STRH R0,[27FFFFEh]      ;write should be same value as above          |
|       STRH R0,[27FFFFEh]      ;write any value                              |
|       STRH R0,[27FFFFEh]      ;write any value                              |
|       LDRH R0,[2400000h+CR*2] ;read, address-bits are defining new CR value |
+-----------------------------------------------------------------------------+
```

Do not access any other Main Memory addresses during above sequence (ie. disable interrupts, and do not execute the sequence by code located in Main Memory). The CR value is write-only. The CR bits are:

```
+-------------------------------------------------------------------------------------+
|       Bit    Expl.                                                                  |
|       0-6    Reserved         (Must be 7Fh)                                         |
|       7      Write Control                                                          |
|                0=WE Single Clock Pulse Control without Write Suspend Function       |
|                1=WE Level Control with Write Suspend Function)                      |
|               Burst Read/Single Write is not supported at WE Single Clock Mode.     |
|       8      Reserved         (Must be 1)                                           |
|       9      Valid Clock Edge (0=Falling Edge, 1=Rising Edge)                       |
|       10     Single Write     (0=Burst Read/Burst Write, 1=Burst Read/Single Write) |
|       11     Burst Sequence   (0=Reserved, 1=Sequential)                            |
|       12-14  Read Latency     (1=3 clocks, 2=4 clocks, 3=5 clocks, other=Reserved)  |
|       15     Mode                                                                   |
|                0=Synchronous:  Burst Read, Burst Write                              |
|                1=Asynchronous: Page Read, Normal Write                              |
|               In Mode 1 (Async), only the Partial Size bits are used,               |
|               all other bits, CR bits 0..18, must be "1".                           |
|       16-18  Burst Length     (2=8 Words, 3=16Words, 7=Continous, other=Reserved)   |
|       19-20  Partial Size     (0=1MB, 1=512KB, 2=Reserved, 3=Deep/0 bytes)          |
+-------------------------------------------------------------------------------------+
```

The Power Down mode is entered by setting CE2=LOW, this can be probably done by setting EXMEMCNT Bit14 to zero.

### ST Microelectronics M69AB048BL70ZA8
The chip name decodes as PSRAM (M96), Asynchronous (A), 1.8V Burst (B), 2Mx16 (048), Two Chip Enables (B), Low Leakage (L), 70ns (70), Package (ZA), -30..+85\'C (8).
There are three data sheets for different PSRAM chips available at www.st.com (unfortunately none for M69AB048BL70ZA8), each using different memory control mechanisms.

### NDS9 BIOS
The NDS9 BIOS contains the following Main Memory initialization code, that method doesn\'t match up with any ST (nor Fujitsu) data sheets that I\'ve seen. At its best, it looks like a strange (and presumably non-functional) mix-up of different ST control methods.

```
+-----------------------------------------------------------------------+
|       STRH 2000h,[4000204h]    ;EXMEMCNT, enable RAM, async mode      |
|       LDRH R0,[27FFFFEh]                                              |
|       STRH R0,[27FFFFEh]                                              |
|       STRH R0,[27FFFFEh]                                              |
|       STRH FFDFh,[27FFFFEh]                                           |
|       STRH E732h,[27FFFFEh]                                           |
|       LDRH R0,[27E57FEh]                                              |
|       STRH 6000h,[4000204h]    ;EXMEMCNT, enable RAM, normal mode     |
+-----------------------------------------------------------------------+
```




