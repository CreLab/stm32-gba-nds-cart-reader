# 78K/0 Memory Map and SFRs


### 78K0 References

```
+-----------------------------------------------------------------------+
|       78K0/Kx2 User's Manual: Hardware       ;info on I/O Ports       |
|       78K0/Kx2 Flash Memory Self Programming ;info on 8100h function  |
|       78K0/Kx2 Flash Memory Programming      ;info on UART/SPI cable  |
|       78K/0 Series Instructions              ;info on opcodes         |
|       78K0/KB2 One-sheet Manual              ;quick reference poster  |
+-----------------------------------------------------------------------+
```


### 78K/0 Memory Map

```
+-------------------------------------------------------------------------------------+
|       0000h..003Fh  FLASH ROM Exception Vectors (16bit each)                        |
|       0040h..007Fh  FLASH ROM CALLT Vectors (16bit each)                            |
|       0080h..0084h  FLASH ROM Option Byte Area (5 bytes)                            |
|       0085h..008Eh  FLASH ROM Debug Security Area (10 bytes, if any)                |
|       008Fh..07FFh  FLASH ROM                                                       |
|       0800h..0FFFh  FLASH ROM (accessible via CALLF opcodes)                        |
|       1000h..1FFFh  FLASH ROM (can be swapped with 0000h..0FFFh)                    |
|       2000h..xFFFh  FLASH ROM (if any, in larger chips)                             |
|       8000h..BFFFh  FLASH ROM (if any, in larger chips) (bank-switched via BANK)    |
|       8000h..9FFFh  System ROM area (when mapped, with function handler at 8100h)   |
|       A000h..BFFFh  System ROM mirror (same as 8000h..9FFFh)                        |
|       C000h..       System ROM empty           (mostly FFh-filled, some FEh-bytes)  |
|       E000h..F7FFh  Extra RAM (max 6K, if any) (mostly FFh-filled, some F0h-bytes)  |
|       F800h..F8FFh  Undoc SFR's                                                     |
|       F900h..FAFFh  Zerofilled                                                      |
|       FB00h..FBFFh  Unknown (filled with random values) (more RAM?) (unused in DSi) |
|                     (FB00h is ONLY mapped when ROM enabled, otherwise FFh-filled)   |
|       FC00h..FF1Fh  RAM (officially/used area)                                      |
|       FE20h..FEDFh  RAM (accessible via short "saddr" opcodes)                      |
|       FEE0h..FEE7h  Register Bank 3 (X,A,C,B,E,D,L,H aka AX,BC,DE,HL)               |
|       FEE8h..FEEFh  Register Bank 2 (X,A,C,B,E,D,L,H aka AX,BC,DE,HL)               |
|       FEF0h..FEF7h  Register Bank 1 (X,A,C,B,E,D,L,H aka AX,BC,DE,HL)               |
|       FEF8h..FEFFh  Register Bank 0 (X,A,C,B,E,D,L,H aka AX,BC,DE,HL)               |
|       FF00h..FFFFh  Special Function Registers (SFR's)                              |
+-------------------------------------------------------------------------------------+
```

FLASH banks are 1Kbyte tall (aka erase block size?).

### 78K/0 Vectors

```
+-----------------------------------------------------------------------+
|       0000h RESET input, POC, LVI, WDT                                |
|       0002h -                                                         |
|       0004h INTLVI                                                    |
|       0006h INTP0                                                     |
|       0008h INTP1                                                     |
|       000Ah INTP2                                                     |
|       000Ch INTP3                                                     |
|       000Eh INTP4                                                     |
|       0010h INTP5                                                     |
|       0012h INTSRE6                                                   |
|       0014h INTSR6                                                    |
|       0016h INTST6                                                    |
|       0018h INTCSI10/INTST0                                           |
|       001Ah INTTMH1                                                   |
|       001Ch INTTMH0                                                   |
|       001Eh INTTM50                                                   |
|       0020h INTTM000                                                  |
|       0022h INTTM010                                                  |
|       0024h INTAD                                                     |
|       0026h INTSR0                                                    |
|       0028h INTWTI                                                    |
|       002Ah INTTM51                                                   |
|       002Ch INTKR                                                     |
|       002Eh INTWT                                                     |
|       0030h INTP6                                                     |
|       0032h INTP7                                                     |
|       0034h INTIIC0/NTDMU                                             |
|       0036h INTCSI11                                                  |
|       0038h INTTM001                                                  |
|       003Ah INTTM011                                                  |
|       003Ch INTACSI                                                   |
|       003Eh BRK                                                       |
+-----------------------------------------------------------------------+
```


### 78K/0 Option Bytes / Debug Security

```
+-----------------------------------------------------------------------+
|       0080h db   07Eh   ;Option Byte: Watchdog Mode                   |
|       0081h db   000h   ;Option Byte: POC Mode (0=1.59V, 1=2.7V)      |
|       0082h db   000h   ;Option Byte: Reserved (00h)                  |
|       0083h db   000h   ;Option Byte: Reserved (00h)                  |
|       0084h db   000h   ;Option Byte: On-chip Debug Control (0=Off)   |
|            ;---                                                       |
|       0085h db   0CCh   ;On-chip debug security ID (0Ah bytes) ...    |
|       0086h db   023h                                                 |
|       0087h db   0BAh                                                 |
|       0088h db   0C3h                                                 |
|       0089h db   07Dh                                                 |
|       008Ah db   094h                                                 |
|       008Bh db   0FEh                                                 |
|       008Ch db   073h                                                 |
|       008Dh db   0A5h                                                 |
|       008Eh db   0E6h                                                 |
+-----------------------------------------------------------------------+
```


### 78K/0 Program Status Word (PSW) aka \[FF1Eh\]

```
+-----------------------------------------------------------------------+
|       7  IE     ;Interrupt Enable                                     |
|       6  Z      ;Zero Flag                                            |
|       5  RBS1   ;Register Bank Select bit1                            |
|       4  AC     ;Aux Carry Flag                                       |
|       3  RBS0   ;Register Bank Select bit0                            |
|       2  0                                                            |
|       1  ISP    ;In-Service Priority Flag                             |
|       0  CY     ;Carry Flag                                           |
+-----------------------------------------------------------------------+
```


### 78K/0 Special Function Registers (SFR\'s)

```
+-------------------------------------------------------------------------------------+
|       Addr  Symbol R/W 1BW Reset BCDEF Special Function Register (SFR)              |
|       FF00h P0     R/W 1B- 00h   BCDEF Port 0                                       |
|       FF01h P1     R/W 1B- 00h   BCDEF Port 1                                       |
|       FF02h P2     R/W 1B- 00h   BCDEF Port 2                                       |
|       FF03h P3     R/W 1B- 00h   BCDEF Port 3                                       |
|       FF04h P4     R/W 1B- 00h   -CDEF Port 4                                       |
|       FF05h P5     R/W 1B- 00h   ---EF Port 5                                       |
|       FF06h P6     R/W 1B- 00h   BCDEF Port 6                                       |
|       FF07h P7     R/W 1B- 00h   -CDEF Port 7                                       |
|       FF08h ADCR   R   --W 0000h BCDEF 10-bit A/D conversion result                 |
|       FF09h ADCRH  R   -B- 00h   BCDEF 8-bit A/D conversion result                  |
|       FF0Ah RXB6   R   -B- FFh   BCDEF Receive buffer 6                             |
|       FF0Bh TXB6   R/W -B- FFh   BCDEF Transmit buffer 6                            |
|       FF0Ch P12    R/W 1B- 00h   BCDEF Port 12                                      |
|       FF0Dh P13    R/W 1B- 00h   -cDEF Port 13 (KC2: 48pin only)                    |
|       FF0Eh P14    R/W 1B- 00h   -cDEF Port 14 (KC2: 48pin only)                    |
|       FF0Fh SIO10  R   -B- 00h   BCDEF Serial I/O shift 10                          |
|       FF10h TM00   R   --W 0000h BCDEF 16-bit timer counter 00                      |
|       FF12h CR000  R/W --W 0000h BCDEF 16-bit timer capture/compare 000             |
|       FF14h CR010  R/W --W 0000h BCDEF 16-bit timer capture/compare 010             |
|       FF16h TM50   R   -B- 00h   BCDEF 8-bit timer counter 50                       |
|       FF17h CR50   R/W -B- 00h   BCDEF 8-bit timer compare 50                       |
|       FF18h CMP00  R/W -B- 00h   BCDEF 8-bit timer H compare 00                     |
|       FF19h CMP10  R/W -B- 00h   BCDEF 8-bit timer H compare 10                     |
|       FF1Ah CMP01  R/W -B- 00h   BCDEF 8-bit timer H compare 01                     |
|       FF1Bh CMP11  R/W -B- 00h   BCDEF 8-bit timer H compare 11                     |
|       FF1Ch SP     R/W --W xxxxh BCDEF CPU Stack Pointer      ;\undocumented, used  
|       FF1Eh PSW    R/W 1B- xxh   BCDEF CPU Program Status Word;/in pseudo opcodes   |
|       FF1Fh TM51   R   -B- 00h   BCDEF 8-bit timer counter 51                       |
|       FF20h PM0    R/W 1B- FFh   BCDEF Port mode 0                                  |
|       FF21h PM1    R/W 1B- FFh   BCDEF Port mode 1                                  |
|       FF22h PM2    R/W 1B- FFh   BCDEF Port mode 2                                  |
|       FF23h PM3    R/W 1B- FFh   BCDEF Port mode 3                                  |
|       FF24h PM4    R/W 1B- FFh   -CDEF Port mode 4                                  |
|       FF25h PM5    R/W 1B- FFh   ---EF Port mode 5                                  |
|       FF26h PM6    R/W 1B- FFh   BCDEF Port mode 6                                  |
|       FF27h PM7    R/W 1B- FFh   -CDEF Port mode 7                                  |
|       FF28h ADM    R/W 1B- 00h   BCDEF A/D converter mode                           |
|       FF29h ADS    R/W 1B- 00h   BCDEF Analog input channel specification           |
|       FF2Ch PM12   R/W 1B- FFh   BCDEF Port mode 12                                 |
|       FF2Eh PM14   R/W 1B- FFh   -cDEF Port mode 14 (KC2: 48pin only)               |
|       FF2Fh ADPC   R/W 1B- 00h   BCDEF A/D port configuration                       |
|       FF30h PU0    R/W 1B- 00h   BCDEF Pull-up resistor option 0                    |
|       FF31h PU1    R/W 1B- 00h   BCDEF Pull-up resistor option 1                    |
|       FF33h PU3    R/W 1B- 00h   BCDEF Pull-up resistor option 3                    |
|       FF34h PU4    R/W 1B- 00h   -CDEF Pull-up resistor option 4                    |
|       FF35h PU5    R/W 1B- 00h   ---EF Pull-up resistor option 5                    |
|       FF36h PU6    R/W 1B- 00h   ----F Pull-up resistor option 6                    |
|       FF37h PU7    R/W 1B- 00h   -CDEF Pull-up resistor option 7                    |
|       FF3Ch PU12   R/W 1B- 00h   BCDEF Pull-up resistor option 12                   |
|       FF3Eh PU14   R/W 1B- 00h   -cDEF Pull-up resistor option 14 (KC2: 48pin only) |
|       FF40h CKS    R/W 1B- 00h   -cDEF Clock output selection     (KC2: 48pin only) |
|       FF41h CR51   R/W -B- 00h   BCDEF 8-bit timer compare 51                       |
|       FF43h TMC51  R/W 1B- 00h   BCDEF 8-bit timer mode control 51                  |
|       FF48h EGP    R/W 1B- 00h   BCDEF External interrupt rising edge enable        |
|       FF49h EGN    R/W 1B- 00h   BCDEF External interrupt falling edge enable       |
|       FF4Ah SIO11  R   -B- 00h   ---eF Serial I/O shift 11 (KE2: 48KB only)         |
|       FF4Ch SOTB11 R/W -B- 00h   ---eF Transmit buffer 11  (KE2: 48KB only)         |
|       FF4Fh ISC    R/W 1B- 00h   BCDEF Input switch control                         |
|       FF50h ASIM6  R/W 1B- 01h   BCDEF Async serial interface operation mode 6      |
|       FF53h ASIS6  R   -B- 00h   BCDEF Async serial interface reception err/stat 6  |
|       FF55h ASIF6  R   -B- 00h   BCDEF Async serial interface transmission status 6 |
|       FF56h CKSR6  R/W -B- 00h   BCDEF Clock selection 6                            |
|       FF57h BRGC6  R/W -B- FFh   BCDEF Baud rate generator control 6                |
|       FF58h ASICL6 R/W 1B- 16h   BCDEF Async serial interface control 6             |
|       FF60h SDR0   R   -BW 0000h -cdeF Remainder data 0 bit0..         ;\           
|       FF61h SDR0H  R   -B- 00h   -cdeF Remainder data 0 bit8..         ;            |
|       FF62h MDA0L  R/W -BW 0000h -cdeF Multiply/divide data A0 bit0..  ; KC2-KE2:   |
|       FF63h MDA0LH R/W -B- 00h   -cdeF Multiply/divide data A0 bit8..  ; 48KB only  |
|       FF64h MDA0H  R/W -BW 0000h -cdeF Multiply/divide data A0 bit16.. ;            |
|       FF65h MDA0HH R/W -B- 00h   -cdeF Multiply/divide data A0 bit24.. ;            |
|       FF66h MDB0   R/W -BW 0000h -cdeF Multiply/divide data B0 bit0..  ;            |
|       FF67h MDB0H  R/W -B- 00h   -cdeF Multiply/divide data B0 bit8..  ;            |
|       FF68h DMUC0  R/W 1B- 00h   -cdeF Multiply/divide control 0       ;/           |
|       FF69h TMHMD0 R/W 1B- 00h   BCDEF 8-bit timer H mode 0                         |
|       FF6Ah TCL50  R/W 1B- 00h   BCDEF Timer clock selection 50                     |
|       FF6Bh TMC50  R/W 1B- 00h   BCDEF 8-bit timer mode control 50                  |
|       FF6Ch TMHMD1 R/W 1B- 00h   BCDEF 8-bit timer H mode 1                         |
|       FF6Dh TMCYC1 R/W 1B- 00h   BCDEF 8-bit timer H carrier control 1              |
|       FF6Eh KRM    R/W 1B- 00h   -CDEF Key return mode                              |
|       FF6Fh WTM    R/W 1B- 00h   -CDEF Watch timer operation mode                   |
|       FF70h ASIM0  R/W 1B- 01h   BCDEF Async serial interface operation mode 0      |
|       FF71h BRGC0  R/W -B- 1Fh   BCDEF Baud rate generator control 0                |
|       FF72h RXB0   R   -B- FFh   BCDEF Receive buffer 0                             |
|       FF73h ASIS0  R   -B- 00h   BCDEF Async serial interface reception err/stat 0  |
|       FF74h TXS0   W   -B- FFh   BCDEF Transmit shift 0                             |
|       FF80h CSIM10 R/W 1B- 00h   BCDEF Serial operation mode 10                     |
|       FF81h CSIC10 R/W 1B- 00h   BCDEF Serial clock selection 10                    |
|       FF84h SOTB10 R/W -B- 00h   BCDEF Transmit buffer 10                           |
|       FF88h CSIM11 R/W 1B- 00h   ---eF Serial operation mode 11  (KE2: 48KB only)   |
|       FF89h CSIC11 R/W 1B- 00h   ---eF Serial clock selection 11 (KE2: 48KB only)   |
|       FF8Ch TCL51  R/W 1B- 00h   BCDEF Timer clock selection 51                     |
|       FF90h CSIMA0 R/W 1B- 00h   ----F Serial operation mode specification 0        |
|       FF91h CSIS0  R/W 1B- 00h   ----F Serial status 0                              |
|       FF92h CSIT0  R/W 1B- 00h   ----F Serial trigger 0                             |
|       FF93h BRGCA0 R/W -B- 03h   ----F Division value selection 0                   |
|       FF94h ADTP0  R/W -B- 00h   ----F Automatic data transfer address point spec 0 |
|       FF95h ADTI0  R/W -B- 00h   ----F Automatic data transfer interval spec 0      |
|       FF96h SIOA0  R/W -B- 00h   ----F Serial I/O shift 0                           |
|       FF97h ADTC0  R   -B- 00h   ----F Automatic data transfer address count 0      |
|       FF99h WDTE   R/W -B- xAh   BCDEF Watchdog timer enable (initial=1Ah/9Ah)      |
|       FF9Fh OSCCTL R/W 1B- 00h   BCDEF Clock operation mode select                  |
|       FFA0h RCM    R/W 1B- x0h   BCDEF Internal oscillation mode                    |
|       FFA1h MCM    R/W 1B- 00h   BCDEF Main clock mode                              |
|       FFA2h MOC    R/W 1B- 80h   BCDEF Main OSC control                             |
|       FFA3h OSTC   R   1B- 00h   BCDEF Oscillation stabilization time counter stat  |
|       FFA4h OSTS   R/W -B- 05h   BCDEF Oscillation stabilization time select        |
|       FFA5h IIC0   R/W -B- 00h   BCDEF IIC shift 0                                  |
|       FFA6h IICC0  R/W 1B- 00h   BCDEF IIC control 0                                |
|       FFA7h SVA0   R/W -B- 00h   BCDEF Slave address 0                              |
|       FFA8h IICCL0 R/W 1B- 00h   BCDEF IIC clock selection 0                        |
|       FFA9h IICX0  R/W 1B- 00h   BCDEF IIC function expansion 0                     |
|       FFAAh IICS0  R   1B- 00h   BCDEF IIC status 0                                 |
|       FFABh IICF0  R/W 1B- 00h   BCDEF IIC flag 0                                   |
|       FFACh RESF   R   -B- xxh   BCDEF Reset control flag                           |
|       FFB0h TM01   R   --W 0000h ---eF 16-bit timer counter 01           ;\         
|       FFB2h CR001  R/W --W 0000h ---eF 16-bit timer capture/compare 001  ;          |
|       FFB4h CR011  R/W --W 0000h ---eF 16-bit timer capture/compare 011  ; KE2:     |
|       FFB6h TMC01  R/W 1B- 00h   ---eF 16-bit timer mode control 01      ; 48KB     |
|       FFB7h PRM01  R/W 1B- 00h   ---eF Prescaler mode 01                 ; only)    |
|       FFB8h CRC01  R/W 1B- 00h   ---eF Capture/compare control 01        ;          |
|       FFB9h TOC01  R/W 1B- 00h   ---eF 16-bit timer output control 01    ;/         |
|       FFBAh TMC00  R/W 1B- 00h   BCDEF 16-bit timer mode control 00                 |
|       FFBBh PRM00  R/W 1B- 00h   BCDEF Prescaler mode 00                            |
|       FFBCh CRC00  R/W 1B- 00h   BCDEF Capture/compare control 00                   |
|       FFBDh TOC00  R/W 1B- 00h   BCDEF 16-bit timer output control 00               |
|       FFBEh LVIM   R/W 1B- xxh   BCDEF Low-voltage detection                        |
|       FFBFh LVIS   R/W 1B- xxh   BCDEF Low-voltage detection level selection        |
|       FFC0h PFCMD  W?  ?B? ?     ?  Undoc: Flash Protect Command (write A5h)        |
|       FFC1h -      R/W 1B- ?     ?  Undoc: Flash ... FFC1h ... bits/pulses   FSSQ ? |
|       FFC2h PFS    R       ?     ?  Undoc: Flash Protect Status                     |
|       FFC4h FLPMC  R/W 1B? ?     ?  Undoc: Flash Programming Mode Ctl ;triple write |
|       FFC5h -      W   1?- ?     ?  Undoc: Flash ... 0FFC5h ... bits/mode   ?       |
|       FFC6h FLAPH  W   1B- ?     ?  Undoc: Flash addr ptr upper 8bit (bit1=flag)    |
|       FFC7h -      R/W 1?- ?     ?  Undoc: Flash ... 0FFC7h ... flag bits           |
|       FFC8h FLAPL  W   1BW ?     ?  Undoc: Flash addr ptr lower 16bit (bit0,1=flag) |
|       FFCAh -      R/W ?B? ?     ?  Undoc: Flash ... 0FFCAh ...       ;triple write |
|       FFCBh FLWE   W   ?B- ?     ?  Undoc: Flash write data ECC error correction?   |
|       FFCCh FLWH   W   -BW ?     ?  Undoc: Flash write data upper 16bit  ;\4-byte   
|       FFCEh FLWL   W   -BW ?     ?  Undoc: Flash write data lower 16bit  ;/         |
|       FFE0h IF0L   R/W 1BW 00h   BCDEF Interrupt request flag 0L      ;\IF0         
|       FFE1h IF0H   R/W 1BW 00h   BCDEF Interrupt request flag 0H      ;/            |
|       FFE2h IF1L   R/W 1BW 00h   BCDEF Interrupt request flag 1L      ;\IF1         
|       FFE3h IF1H   R/W 1BW 00h   BCDEF Interrupt request flag 1H      ;/            |
|       FFE4h MK0L   R/W 1BW FFh   BCDEF Interrupt mask flag 0L         ;\MK0         
|       FFE5h MK0H   R/W 1BW FFh   BCDEF Interrupt mask flag 0H         ;/            |
|       FFE6h MK1L   R/W 1BW FFh   BCDEF Interrupt mask flag 1L         ;\MK1         
|       FFE7h MK1H   R/W 1BW FFh   BCDEF Interrupt mask flag 1H         ;/            |
|       FFE8h PR0L   R/W 1BW FFh   BCDEF Priority specification flag 0L ;\PR0         
|       FFE9h PR0H   R/W 1BW FFh   BCDEF Priority specification flag 0H ;/            |
|       FFEAh PR1L   R/W 1BW FFh   BCDEF Priority specification flag 1L ;\PR1         
|       FFEBh PR1H   R/W 1BW FFh   BCDEF Priority specification flag 1H ;/            |
|       FFF0h IMS    R/W -B- CFh   BCDEF Internal memory size switching               |
|       FFF3h BANK   R/W -B- 00h   --def Memory bank select  (KD2-KF2: min 96KB only) |
|       FFF4h IXS    R/W -B- 0Ch   bcdeF Internal expansion RAM size switching        |
|       FFF5h -      R   ?B- ?     ?  Undoc: chip_id (package type and memory size)   |
|       FFFBh PCC    R/W 1B- 01h   BCDEF Processor clock control                      |
+-------------------------------------------------------------------------------------+
```

And, more undoc/secret registers:

```
+----------------------------------------------------------------------------------+
|       F800h..F0h   -   --- ?     ?  Undoc: unknown values, unused by software    |
|       F8F1h FLrE   R   -B- ?     ?  Undoc: Flash read data ECC error correction? |
|       F8F2h FLrH   R   -BW ?     ?  Undoc: Flash read data upper 16bit  ;\4-byte 
|       F8F4h FLrL   R   -BW ?     ?  Undoc: Flash read data lower 16bit  ;/total  |
|       F8F6h ???    R/W --W ?     ?  Undoc: Flash ...0F8F6h_word     ;-16bit      |
|       F8F8h -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8F9h ???    R/W -B- ?     ?  Undoc: Flash ...0F8F9h          ;-           |
|       F8FAh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8FBh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8FCh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8FDh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8FEh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
|       F8FFh -      -   --- ?     ?  Undoc:   ;(unused by software)               |
+----------------------------------------------------------------------------------+
```


Whereas,

```
+-----------------------------------------------------------------------+
|       1BT   = supports Bit/Byte/Word access (1bit/8bit/16bit)         |
|       BCDEF = supported on KB2/KC2/KD2/KE2/KF2 chip versions          |
+-----------------------------------------------------------------------+
```

For IMS/IXS: Regardless of the internal memory capacity, the initial values of the internal memory size switching register (IMS) and internal expansion RAM size switching register (IXS) of all products in the 78K0/Kx2 microcontrollers are fixed (IMS = CFH, IXS = 0CH). Therefore, set the value corresponding to each product as indicated in Tables 3-1 and 3-2.
For IMS/IXS: The ROM and RAM capacities of the products with the on-chip debug function can be debugged by setting IMS and IXS, according to the debug target products. Set IMS and IXS according to the debug target products.
For IXS on KB2-KE2: Set IXS only in products with internal expansion RAM.
The reset values of RES, LVIM and LVIS vary depending on the reset source.
The reset value of WDTE is determined by setting of option byte.
The reset value of RCM is 00h immediately after a reset release but automatically changes to 80h after oscillation accuracy stabilization of high-speed internal oscillator has been waited.



