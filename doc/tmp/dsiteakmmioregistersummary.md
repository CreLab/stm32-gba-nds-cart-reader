# DSi Teak MMIO - Register Summary


I/O ports are mapped in \"data memory\" at 8000h-87FFh (2Kwords). All ports are 16bit wide, located at even word addresses (words at odd addresses seem to be always 0000h, except, there ARE some odd ports used at 806xh).

### 8000h Mirrors

```
+-----------------------------------------------------------------------+
|       8000h..8002h 3300 3300 3300 R   Mirror of Port 80D6h            |
+-----------------------------------------------------------------------+
```

### 8004h JAM

```
+-----------------------------------------------------------------------------------+
|       8004h        0000 0000 87FF R/W JAM Unknown                                 |
|       8006h        ?    ?    ?    ??  JAM Unknown/Crash, DANGER (crashes on read) |
|       8008h..800Eh 3300 3300 3300 R   Mirror of Port 80D6h                        |
+-----------------------------------------------------------------------------------+
```

### 8010h GLUE

```
+-----------------------------------------------------------------------------------+
|       8010h        0000 0000 0003 R/W GLUE CFG0                                   |
|       8012h        0000 0000 0003 R/W GLUE Unknown 2bit                           |
|       8014h        0000 0000 FFFF R/W GLUE Unknown 16bit                          |
|       8016h        0000 0000 0000 R   GLUE Unknown (DSi=0000h, New3DS=00BAh)      |
|       8018h        0000 0000 BDEF R/W GLUE Whatever Parity/Shuffle                |
|       801Ah        C902 C902 C902 R   GLUE Chip config ID (for xpert_offsets_tbl) |
|       801Ch..801Eh 0003 0003 0003 R   Mirror of port 8010h                        |
+-----------------------------------------------------------------------------------+
```

### 8020h Timers

```
+-------------------------------------------------------------------------------------+
|       8020h        0000 0000 7xDF R/W Timer 0 Control (bit11=DANGER)      ;\        
|       8022h        0000 0000 0000 W   Timer 0 Trigger Event/Watchdog      ;         |
|       8024h        0000 0000 FFFF R/W Timer 0 Reload value, bit0-15       ; Timer 0 |
|       8026h        0000 0000 FFFF R/W Timer 0 Reload value, bit16-31      ;         |
|       8028h        0000 0000 0000 R   Timer 0 Counter value, bit0-15      ;         |
|       802Ah        0000 0000 0000 R   Timer 0 Counter value, bit16-31     ;         |
|       802Ch        0000 0000 FFFF R/W Timer 0 PWM Reload value, bit0-15   ;         |
|       802Eh        0000 0000 FFFF R/W Timer 0 PWM Reload value, bit16-31  ;/        |
|       8030h        0200 0200 7xDF R/W Timer 1 Control (bit11=DANGER)      ;\        
|       8032h        0000 0000 0000 W   Timer 1 Trigger Event/Watchdog      ;         |
|       8034h        0000 0000 FFFF R/W Timer 1 Reload value, bit0-15       ; Timer 1 |
|       8036h        0000 0000 FFFF R/W Timer 1 Reload value, bit16-31      ;         |
|       8038h        0000 0000 0000 R   Timer 1 Counter value, bit0-15      ;         |
|       803Ah        0000 0000 0000 R   Timer 1 Counter value, bit16-31     ;         |
|       803Ch        0000 0000 FFFF R/W Timer 1 PWM Reload value, bit0-15   ;         |
|       803Eh        0000 0000 FFFF R/W Timer 1 PWM Reload value, bit16-31  ;/        |
|       8040h..804Eh 3300 3300 3300 R   Mirror of Port 80D6h                          |
+-------------------------------------------------------------------------------------+
```

### 8050h Serial Port (SIO)

```
+-----------------------------------------------------------------------+
|       8050h        7000 0000 F03F R/W SIO Control                     |
|       8052h        0000 0000 7F7F R/W SIO Clock Divider               |
|       8054h        0000 0000 0000 R+W SIO Data (R) and (W)            |
|       8056h        0000 0000 0001 R/W SIO Enable                      |
|       8058h        0000 0000 0000 R   SIO Status                      |
|       805Ah..805Eh F03F F03F F03F R   Mirror of port 8050h            |
+-----------------------------------------------------------------------+
```

### 8060h Debug (OCEM, On-chip Emulation Module)

```
+--------------------------------------------------------------------------------+
|       8060h        0105 0105 0105 R   OCEM Program Flow Trace Buffer, bit0-15  |
|       8061h        0000 0000 0000 R   OCEM Program Flow Trace Buffer, bit16-31 |
|       8062h        FFFF 0000 FFFF R/W OCEM Program Break Address 1, bit0-15    |
|       8063h        0F03 0000 0F03 R/W OCEM Program Break Address 1, bit16-31   |
|       8064h        FFFF 0000 FFFF R/W OCEM Program Break Address 2, bit0-15    |
|       8065h        0F03 0000 0F03 R/W OCEM Program Break Address 2, bit16-31   |
|       8066h        FFFF 0000 FFFF R/W OCEM Program Break Address 3, bit0-15    |
|       8067h        0F03 0000 0F03 R/W OCEM Program Break Address 3, bit16-31   |
|       8068h        00FF 0000 00FF R/W OCEM Program Break Counter 1             |
|       8069h        00FF 0000 00FF R/W OCEM Program Break Counter 2             |
|       806Ah        00FF 0000 00FF R/W OCEM Program Break Counter 3             |
|       806Bh        FFFF 0000 FFFF R/W OCEM Data Break Mask                     |
|       806Ch        FFFF 0000 FFFF R/W OCEM Data Break Address                  |
|       806Dh        0000 0000      R/W OCEM Breakpoint Enable Flags (DANGER)    |
|       806Eh        3001 0000 FFFF R/W OCEM Mode/Indication?                    |
|       806Fh        0000 0000 BFFF R/W OCEM Breakpoint Status Flags             |
|       8070h        0000 0000 0001 R/W OCEM Program Flow Trace Update Disable   |
|       8072h        0000 0000 FFFF R/W Unknown 16bit?                           |
|       8074h        C000 C000 C000 R   OCEM Boot/Debug Mode                     |
|       8076h..807Eh 0105 0105 0105 R   Mirror of port 8060h                     |
+--------------------------------------------------------------------------------+
```

### 8080h PLL and Power (PMU, Power Management Unit)

```
+-------------------------------------------------------------------------------------+
|       8080h        C00E 0000 FFFF R/W PMU PLL Multiplier                            |
|       8082h        0001 0000 0001 R/W PMU PLL Power-on config                       |
|       8084h        8000           R/W PMU PLL Divider/Bypass (DANGER)               |
|       8086h        0000           R/W PMU Wake/Shutdown Module(s)                   |
|       8088h        0000 0000 07BF R/W PMU Recover Module(s) on interrupt 0          |
|       808Ah        0000 0000 07BF R/W PMU Recover Module(s) on interrupt 1          |
|       808Ch        0000 0000 07BF R/W PMU Recover Module(s) on interrupt 2          |
|       808Eh        0000 0000 07BF R/W PMU Recover Module(s) on vectored interrupt   |
|       8090h        0000 0000 06BF R/W PMU Recover Module(s) on Timer 0 (no bit8)    |
|       8092h        0000 0000 05BF R/W PMU Recover Module(s) on Timer 1 (no bit9)    |
|       8094h        0000 0000 07BF R/W PMU Recover Module(s) on NMI                  |
|       8096h        0000 0000 0002 R/W PMU Recover DMA on external signal (bit1)     |
|       8098h        0000 0000 0302 R/W PMU Breakpoint mask module(s) (bit1,8,9 only) |
|       809Ah        0000 0000 0003 R/W PMU Wake/Shutdown BTDMP(s)                    |
|       809Ch        0000 0000 0003 R/W PMU Recover BTDMP(s) on interrupt 0           |
|       809Eh        0000 0000 0003 R/W PMU Recover BTDMP(s) on interrupt 1           |
|       80A0h        0000 0000 0003 R/W PMU Recover BTDMP(s) on interrupt 2           |
|       80A2h        0000 0000 0003 R/W PMU Recover BTDMP(s) on vectored interrupt    |
|       80A4h        0000 0000 0003 R/W PMU Recover BTDMP(s) on Timer 0               |
|       80A6h        0000 0000 0003 R/W PMU Recover BTDMP(s) on Timer 1               |
|       80A8h        0000 0000 0003 R/W PMU Recover BTDMP(s) on NMI (undoc?)          |
|       80AAh        0000 0000 FFFF R/W Unknown 16bit                                 |
|       80ACh        0000 0000 FFFF R/W Unknown 16bit                                 |
|       80AEh        0000 0000 FFFF R/W Unknown 16bit                                 |
|       80B0h..80BEh FFFF FFFF FFFF R   Mirror of port 8080h                          |
+-------------------------------------------------------------------------------------+
```

### 80C0h APBP (aka HPI Host Port Interface)

```
+---------------------------------------------------------------------------------+
|       80C0h        xxxx xxxx xxxx R/W APBP DSP-to-ARM Reply 0                   |
|       80C2h        4300 4300 4300 R   APBP ARM-to-DSP Command 0                 |
|       80C4h        0000 0000 FFFF R/W APBP DSP-to-ARM Reply 1                   |
|       80C6h        3123 3123 3123 R   APBP ARM-to-DSP Command 1                 |
|       80C8h        0000 0000 FFFF R/W APBP DSP-to-ARM Reply 2                   |
|       80CAh        3223 3223 3223 R   APBP ARM-to-DSP Command 2                 |
|       80CCh        0000 0000 FFFF R/W APBP DSP-to-ARM Semaphore Set Flags       |
|       80CEh        0000           R/W APBP ARM-to-DSP Semaphore Interrupt Mask  |
|       80D0h        0000           W?  APBP ARM-to-DSP Semaphore Ack Flags       |
|       80D2h        AFFE AFFE AFFE R   APBP ARM-to-DSP Semaphore Get Flags       |
|       80D4h        0000           R/W APBP Control (DANGER: can crash cpu)      |
|       80D6h        03C0 03C0 03C0 R   APBP DSP-side Status                      |
|       80D8h        3B00 3B00 3B00 R   APBP ARM-side Status (mirror of 400430Ch) |
|       80DAh..80DEh 0000 0000 0000 R   Fixed 0000h                               |
+---------------------------------------------------------------------------------+
```

### 80E0h Bus Config for DMA to external ARM-bus (AHBM)

```
+----------------------------------------------------------------------------------+
|       80E0h        0000 0000 0000 R   AHBM Status                                |
|       80E2h+N*6    0000 0000 0FBF R/W AHBM Channel 0..2 Configure Burst/Data     |
|       80E4h+N*6    0000 0000 03FF R/W AHBM Channel 0..2 Configure Whatever       |
|       80E6h+N*6    0000 0000 00FF R/W AHBM Channel 0..2 Configure DMA            |
|       80F4h        0000 0000 FC00 R/W Unknown 6bit? bit10-15 are used            |
|       80F6h        0000 0000 0000 R?  AHBM Internal FIFO (R) and maybe also (W?) |
|       80F8h        0000 0000 0000 R?  Unknown always zero?                       |
|       80FAh        0000 0000 FFFF R/W Read/write-able(!) mirror of MMIO[80FCh]   |
|       80FCh        FFFF 0000 FFFF R/W Unknown 16bit?                             |
|       80FEh        0000 0000 FFFF R/W Unknown 16bit?                             |
+----------------------------------------------------------------------------------+
```

### 8100h MIU (memory limits for X-,Y-,Z-Space, and Memory Mapped I/O base)

```
+-------------------------------------------------------------------------------------+
|       8100h        FFFF 0000 FFFF R/W MIU Waitstate Settings, bit0-15               |
|       8102h        0FFF 0000 0FFF R/W MIU Waitstate Settings, bit16-31              |
|       8104h        0000 0000 FFFF R/W MIU Waitstate Area Z0                         |
|       8106h        0000 0000 FFFF R/W MIU Waitstate Area Z1                         |
|       8108h        0000 0000 FFFF R/W MIU Waitstate Area Z2                         |
|       810Ah        0000 0000 FFFF R/W MIU Waitstate Area Z3                         |
|       810Ch        0014 0014 0014 R   Mirror of port 811Ah                          |
|       810Eh        0000 0000 FFFF R/W MIU X Page (16bit) (or unused)                |
|       8110h        0000 0000 00FF R/W MIU Y Page (8bit)  (or unused)                |
|       8112h        0000           R/W MIU Z Page (16bit) (or absolute page)(DANGER) |
|       8114h        1E20           R/W MIU X/Y Page Size for Page 0 (or all pages)   |
|       8116h        1E20 0100 403F R/W MIU X/Y Page Size for Page 1 (or unused)      |
|       8118h        1E20 0100 403F R/W MIU X/Y Page Size for Off-chip (or unused)    |
|       811Ah        0014 00x4      R/W MIU Config for Misc stuff (DANGER)            |
|       811Ch        0004 0000 007F R/W MIU Config for Program Page and Download Mem  |
|       811Eh        8000           R/W MIU Base Address for MMIO Registers (DANGER)  |
|       8120h        0000 0000 000F R/W MIU Observability Mode                        |
|       8122h        0000 0000 007F R/W MIU Pin Config?                               |
|       8124h..813Eh 0014 0014 0014 R   Mirror of port 811Ah                          |
+-------------------------------------------------------------------------------------+
```

### 8140h Patch (CRU, Code Replacement Unit)

```
+------------------------------------------------------------------------------------+
|       8140h+N*4    0000 0000 FFFF R/W CRU Entry 0..14 Offset, bit0-15              |
|       8142h+N*4    0000 0000 803F R/W CRU Entry 0..14 Offset, bit16-31             |
|       817Ch        0000 0000 FFFF R/W CRU Entry 15 Offset, bit0-15  ;\with control 
|       817Eh        0000 0000 C03F R/W CRU Entry 15 Offset, bit16-31 ;/status bits  |
+------------------------------------------------------------------------------------+
```

### 8180h DMA (eight channels, port 81C0h..81Exh are bank-switched via 81BEh)

```
+-----------------------------------------------------------------------------------+
|       8180h        0000 0000 0000 R   DMA Internal: Channel Size0 Busy or so?     |
|       8182h        0000 0000 0000 R   DMA Internal: Channel Size1 Busy or so?     |
|       8184h        0001 0000 00FF R/W DMA Channel Start Flags (1=Start/Busy)      |
|       8186h        0000 0000 00FF R/W DMA Channel Pause Flags (1=Pause)           |
|       8188h        0000 0000 0000 R   DMA Channel End Flags for Size0             |
|       818Ah        0000 0000 0000 R   DMA Channel End Flags for Size1             |
|       818Ch        0000 0000 0000 R   DMA Channel End Flags for Size2 (all done)  |
|       818Eh        3210 0000 7777 R/W DMA Whatever Slot Config, bit0-15           |
|       8190h        7654 0000 7777 R/W DMA Whatever Slot Config, bit16-31          |
|       8192h        0000 0000 7C03 R/W Unknown, R/W mask 7C03h                     |
|       8194h        0000 0000 0000 R   DMA Internal: contains SRC_ADDR_L after DMA |
|       8196h        0000 0000 0000 R   DMA Internal: contains DST_ADDR_L after DMA |
|       8198h..81B4h 0000 0000 0000 R   Fixed 0000h                                 |
|       81B6h        0000 0000 FFFF R/W Unknown, 16bit                              |
|       81B8h        0000 0000 FFFF R/W Unknown, 16bit                              |
|       81BAh        0000 0000 FFFF R/W Unknown, 16bit                              |
|       81BCh        0000 0000 FFFF R/W Unknown, 16bit                              |
|       81BEh        0000 0000 0007 R/W DMA Select Channel (bank for 81C0h-81Exh)   |
|       81C0h:0..7   0000 0000 FFFF R/W DMA Channel: Source Address, bit0-15        |
|       81C2h:0..7   0000 0000 FFFF R/W DMA Channel: Source Address, bit16-31       |
|       81C4h:0..7   0000 0000 FFFF R/W DMA Channel: Destination Address, bit0-15   |
|       81C6h:0..7   0000 0000 FFFF R/W DMA Channel: Destination Address, bit16-31  |
|       81C8h:0..7   FFFF 0001 FFFF R/W DMA Channel: Size0 (usually total len)      |
|       81CAh:0..7   0001 0001 FFFF R/W DMA Channel: Size1 (usually 1)              |
|       81CCh:0..7   0001 0001 FFFF R/W DMA Channel: Size2 (usually 1)              |
|       81CEh:0..7   0001 0000 FFFF R/W DMA Channel: Source Step0      ;-2,4,2,1    |
|       81D0h:0..7   0001 0000 FFFF R/W DMA Channel: Source Step1      ;-4,2,2,1    |
|       81D2h:0..7   0001 0000 FFFF R/W DMA Channel: Source Step2      ;-2,4,0,1    |
|       81D4h:0..7   0001 0000 FFFF R/W DMA Channel: Destination Step0 ;-4,2,0,1    |
|       81D6h:0..7   0001 0000 FFFF R/W DMA Channel: Destination Step1 ;-0,0,0,1    |
|       81D8h:0..7   0001 0000 FFFF R/W DMA Channel: Destination Step2 ;-0,0,0,1    |
|       81DAh:0..7   F200 0000 F7FF R/W DMA Channel: Memory Area Config             |
|       81DCh:0..7   0000 0000 1FF7 R/W DMA Channel: Unknown, usually set to 0300h? |
|       81DEh:0..7   0000 0000 00FF R/W DMA Channel: Start/Stop/Control             |
|       81E0h:0..7   0000 0000 0000 R   DMA Internal: contains SRC_ADDR_L after DMA |
|       81E2h:0..7   0000 0000 0000 R   DMA Internal: contains DST_ADDR_L after DMA |
|       81E4h:0..7   0000 0000 0000 R   DMA Internal: contains SRC_ADDR_H after DMA |
|       81E6h:0..7   0000 0000 0000 R   DMA Internal: contains DST_ADDR_H after DMA |
|       81E8h..81FEh 0000 0000 0000 R   Fixed 0000h                                 |
+-----------------------------------------------------------------------------------+
```

### 8200h ICU (interrupts)

```
+------------------------------------------------------------------------------------+
|       8200h        4020 4020 4020 R   ICU Interrupt Pending Flags  (1=Pending)     |
|       8202h        0000 0000 0000 W   ICU Interrupt Acknowledge    (1=Clear)       |
|       8204h        0000 0000 FFFF R/W ICU Interrupt Manual Trigger (1=Set)         |
|       8206h        0000 0000 FFFF R/W ICU Enable Interrupt as int0 (1=Enable)      |
|       8208h        0000 0000 FFFF R/W ICU Enable Interrupt as int1 (1=Enable)      |
|       820Ah        0000 0000 FFFF R/W ICU Enable Interrupt as int2 (1=Enable)      |
|       820Ch        0000 0000 FFFF R/W ICU Enable Interrupt as vint (1=Enable)      |
|       820Eh        2000 0000 FFFF R/W ICU Interrupt Trigger mode (0=Level, 1=Edge) |
|       8210h        2000 0000 FFFF R/W ICU Interrupt Polarity (0=Normal, 1=Invert)  |
|       8212h+N*4    0003 0000 8003 R/W ICU Vectored Interrupt 0..15 Addr, bit16-31  |
|       8214h+N*4    FC00 0000 FFFF R/W ICU Vectored Interrupt 0..15 Addr, bit0-15   |
|       8252h        0000 0000 FFFF R/W ICU Interrupt Master Disable (1=Off/undoc)   |
|       8254h        0000 0000 5555 R/W Unknown, R/W mask 5555h                      |
|       8256h        0000 0000 5555 R/W Unknown, R/W mask 5555h                      |
|       8258h..827Eh 0000 0000 0000 R   Mirror of Port 8200h                         |
+------------------------------------------------------------------------------------+
```

### 8280h BTDMP Audio (two channels N=0..1, each with speaker out and mic in)

```
+------------------------------------------------------------------------------------+
|       8280h+N*80h  0005 0000 FFFF R/W BTDMP Receive Control         ;\             
|       8282h+N*80h  0000 0000 7FE7 R/W BTDMP Receive Period          ;              |
|       8284h+N*80h  0000 0000 0FE7 R/W BTDMP Receive Usually 0004h   ;              |
|       8286h+N*80h  0000 0000 0003 R/W BTDMP Receive Usually 0021h   ; RX           |
|       8288h+N*80h  1FFF 0000 1FFF R/W BTDMP Receive Usually 0000h   ; (microphone) |
|       828Ah+N*80h  0000 0000 0FFF R/W BTDMP Receive Usually 0000h   ;              |
|       828Ch+N*80h  0000 0000 3FFF R/W BTDMP Receive Usually 0000h   ;              |
|       828Eh+N*80h  0000 0000 FFFF R/W BTDMP Receive Usually unused  ;              |
|       8290h+N*80h  0000 0000 FFFF R/W BTDMP Receive Usually unused  ;              |
|       8292h+...    0000 0000 0000 R   Fixed 0000h                   ;              |
|       829Eh+N*80h  0000 0000 8000 R/W BTDMP Receive Enable          ;/             |
|       82A0h+N*80h  0005 0000 FFFF R/W BTDMP Transmit Control        ;\             
|       82A2h+N*80h  0000 0000 7FE7 R/W BTDMP Transmit Period         ;              |
|       82A4h+N*80h  0000 0000 0FE7 R/W BTDMP Transmit Usually 0004h  ;              |
|       82A6h+N*80h  0000 0000 0003 R/W BTDMP Transmit Usually 0021h  ; TX           |
|       82A8h+N*80h  1FFF 0000 1FFF R/W BTDMP Transmit Usually 0000h  ; (audio out)  |
|       82AAh+N*80h  0000 0000 0FFF R/W BTDMP Transmit Usually 0000h  ;              |
|       82ACh+N*80h  0000 0000 3FFF R/W BTDMP Transmit Usually 0000h  ;              |
|       82AEh+N*80h  0000 0000 FFFF R/W BTDMP Transmit Usually unused ;              |
|       82B0h+N*80h  0000 0000 FFFF R/W BTDMP Transmit Usually unused ;              |
|       82B2h+...    0000 0000 0000 R   Fixed 0000h                   ;              |
|       82BEh+N*80h  0000 0000 8000 R/W BTDMP Transmit Enable         ;/             |
|       82C0h+N*80h  001x 001F 001F R   BTDMP Receive FIFO Status     ;\             
|       82C2h+N*80h  0057 005x 0057 R   BTDMP Transmit FIFO Status    ;              |
|       82C4h+N*80h  E0A1 FFFF E0A1 R   BTDMP Receive FIFO Data       ; RX/TX        |
|       82C6h+N*80h  0000 0000 0000 W   BTDMP Transmit FIFO Data      ;              |
|       82C8h+N*80h  0000 0000 0003 R/W BTDMP Receive FIFO Control    ;              |
|       82CAh+N*80h  0000 0000 0003 R/W BTDMP Transmit FIFO Control   ;/             |
|       82CCh+...    0000 0000 0000 R   Fixed 0000h                                  |
|       8380h..867Eh 03C0 03C0 03C0 R   Mirror of Port 80D6h                         |
+------------------------------------------------------------------------------------+
```

### 8680h ? (listed in \"xpert_offsets_tbl\", but there are just mirrors)

```
+-----------------------------------------------------------------------+
|       8680h..87FEh 03C0 03C0 03C0 R   Mirror of Port 80D6h            |
+-----------------------------------------------------------------------+
```

### 8800h ? (listed in \"perxteak.per\", but seems to be always 0) (dbg aka H2C)

```
+-----------------------------------------------------------------------------------+
|       (this is called "Host-to-Core JAM protocol" and consists of 11bit values)   |
|       (not sure if that are MMIO registers, or some 11bit data transfer protocol) |
|       8800h..8807h 0000 0000 0000 R?  Fixed 0 (reportedly H2C aka dbg stuff?)     |
+-----------------------------------------------------------------------------------+
```


### xpert_offsets_tbl: (with baseIO=8000h)
The DSi\'s aac.a file contains a \"xpert_offsets_tbl\" with three sets of I/O regions, which are apparently related to different hardware versions:

```
+-------------------------------------------------------------------------------------+
|          ?    JAM  GLUE TMR  SIO  OCEM PMU  APBP AHBM MIU  CRU  DMA  ICU AUDIO ?    |
|       #0 3333 0000 0010 0020 0050 0060 0080 00A0 3333 00C0 3333 0100 0180 0200 3333 |
|       #1 0000 0004 0010 0020 0050 0060 0080 00C0 00E0 0100 0140 0180 0200 0280 0680 |
|       #2 3333 0004 0010 3333 3333 0020 0040 3333 3333 0060 3333 3333 0120 3333 3333 |
+-------------------------------------------------------------------------------------+
```

All addresses are relative to the MMIO base (usually 8000h), 3333h is apparently some dummy value for unsupported I/O areas.
The DSi does use set #1. The other two sets are probably relicts for older Teak hardware that was never used in DSi consoles (for example, set #2 doesn\'t event support the APBP region for cmd/reply/semaphore).



