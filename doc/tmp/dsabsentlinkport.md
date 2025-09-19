# DS Absent Link Port


The DS doesn\'t have a Serial Link Port Socket, however, internally, the NDS7 contains the complete set of Serial I/O Ports, as contained in the GBA:
- [GBA Communication Ports](./gbacommunicationports.md)

In GBA mode, the ports are working as on real GBA (as when no cable is connected). In NDS mode, the ports are even containing some additional bits:

### NDS7 SIO Bits (according to an early I/O map from Nintendo)

```
+------------------------------------------------------------------------------------+
|       NDS7 4000128h SIOCNT   Bit15 "CKUP"  New Bit in NORMAL/MULTI/UART mode (R/W) |
|       NDS7 4000128h SIOCNT   Bit14 "N/A"   Removed IRQ Bit in UART mode (?)        |
|       NDS7 400012Ah SIOCNT_H Bit14 "TFEMP" New Bit (R/W)                           |
|       NDS7 400012Ah SIOCNT_H Bit15 "RFFUL" New Bit (always zero?)                  |
|       NDS7 400012Ch SIOSEL   Bit0  "SEL"   New Bit (always zero?)                  |
|       NDS7 4000140h JOYCNT   Bit7  "MOD"   New Bit (R/W)                           |
+------------------------------------------------------------------------------------+
```

The \"CKUP\" bit duplicates the internal clock transfer rate (selected in SIOCNT.1) (tested in normal mode) (probably works also in multi/uart mode?).

### NDS7 DS-Lite 4001080h (W) (?)
DS-Lite Firmware writes FFFFh to this address (prior to accessing SIOCNT), so it\'s probably SIO or debugging related (might be as well a bug or so). Reading from the port always returns 0000h on both DS and DS-Lite.

### NDS9 SIO Bits (according to an early I/O map from Nintendo)

```
+-----------------------------------------------------------------------+
|       NDS9 4000120h SIODATA32 Bit0-31 Data            (always zero?)  |
|       NDS9 4000128h SIOCNT    Bit2    "TRECV" New Bit (always zero?)  |
|       NDS9 4000128h SIOCNT    Bit3    "TSEND" New Bit (always zero?)  |
|       NDS9 400012Ch SIOSEL    Bit0    "SEL"   New Bit (always zero?)  |
+-----------------------------------------------------------------------+
```

Not sure if these ports really exist in the release-version, or if it\'s been prototype stuff?

### RCNT
RCNT (4000134h) should be set to 80xxh (general purpose mode) before accessing EXTKEYIN (4000136h) or RTC (4000138h). No idea why (except when using RTC/SI-interrupt).

### DS Serial Port
The SI line is labeled \"INT\" on the NDS mainboard, it is connected to Pin 1 of the RTC chip (ie. the /INT interrupt pin).
I have no idea where to find SO, SC, and SD. I\'ve written a test proggy that pulsed all four RCNT bits - but all I could find was the SI signal. However, the BIOS contains some code that uses SIO normal mode transfers (for the debug version), so at least SI, SO, SC should exist\...?
MAYBE that three signals are somehow replaced by EXTKEYIN bit0,1,3?



