# DS Wifi Unused Registers


### Wifi WS0 and WS1 Regions in NDS7 I/O Space
Wifi hardware occupies two 32K slots, but most of it is filled with unused or duplicated regions. The timings (waitstates) for WS0 and WS1 are initialized in WIFIWAITCNT (by firmware).

```
+--------------------------------------------------------------------------------+
|       4800000h-4807FFFh Wifi WS0 Region (32K)  ;used for RAM at 4804000h       |
|       4808000h-4808000h Wifi WS1 Region (32K)  ;used for registers at 4808000h |
|       4810000h-4FFFFFFh Not used (00h-filled)                                  |
+--------------------------------------------------------------------------------+
```

Structure of the 32K Wifi Regions (WS0 and WS1)

```
+-----------------------------------------------------------------------+
|       Wifi-WS0-Region    Wifi-WS1-Region    Content                   |
|       4800000h-4800FFFh  4808000h-4808FFFh  Registers                 |
|       4801000h-4801FFFh  4809000h-4809FFFh  Registers (mirror)        |
|       4802000h-4803FFFh  480A000h-480BFFFh  Unused                    |
|       4804000h-4805FFFh  480C000h-480DFFFh  Wifi RAM  (8K)            |
|       4806000h-4806FFFh  480E000h-480EFFFh  Registers (mirror)        |
|       4807000h-4807FFFh  480F000h-480FFFFh  Registers (mirror)        |
+-----------------------------------------------------------------------+
```

Wifi Registers (recommended 4808000h-4808FFFh) appear more stable in WS1?
Wifi RAM (recommended 4804000h-4805FFFh) appears more stable in WS0?

### Unused Ports (Original NDS)
Aside from those ports listed in the Wifi I/O Map, all other ports in range 4808000h..4808FFFh are unused. On the original DS, reading from these ports returns FFFFh.

### Unused Ports (NDS-Lite)
Reading from unused I/O ports acts as PASSIVE mirror of W_RXBUF_RD_DATA. Exceptions are: Ports 4808188h, and 48082D8h..48082E6h; which always return 0000h.

### Unused Memory (Original NDS)
Unused Wifi Memory is at 2000h..3FFFh. On the original DS, reading from that region returns FFFFh.

### Unused Memory (NDS-Lite)
Reading from unused memory acts as PASSIVE mirror of WifiRAM (ie. reading from it returns the value being most recently read from 4000h..5FFFh) (that not affected by indirect WifiRAM reads via W_RXBUF_RD_DATA) (and, that not affected by writes to wifi memory, including writes that do overwrite the most recent read value) (and, that only if WifiRAM is properly enabled, ie. Port 4808220h.Bits0-1 should be 0).
Moreover, certain addresses are additionally ORed with mirrored I/O Ports. That addresses are:

```
+-----------------------------------------------------------------------------+
|       2030h, 2044h, 2056h, 2080h, 2090h, 2094h, 2098h, 209Ch, 20A0h, 20A4h, |
|       20A8h, 20AAh, 20B0h, 20B6h, 20BAh, 21C0h, 2208h, 2210h, 2244h, 31D0h, |
|       31D2h, 31D4h, 31D6h, 31D8h, 31DAh, 31DCh, 31DEh.                      |
+-----------------------------------------------------------------------------+
```

For example, 2044h is a PASSIVE mirror of WifiRAM, ORed with an ACTIVE mirror of W_RANDOM (Port 044h). Note that some mirrors are at 2000h-2FFFh, and some at 3000h-3FFFh. The W_CMD_STAT mirrors are PASSIVE (that, in unused memory region only) (in normal port-mirror regions like 1000h-1FFF, W_CMD_STAT mirrors are ACTIVE).

### Known (W) Mirrors (when reading from Write-only ports)

```
+----------------------------------------------------------------------------+
|       Read from (W)           Mirrors to (NDS)       Or to (NDS-Lite)      |
|       070h W_TXBUF_WR_DATA    060h W_RXBUF_RD_DATA   074h W_TXBUF_GAP      |
|       078h W_INTERNAL         068h W_TXBUF_WR_ADDR   074h W_TXBUF_GAP      |
|       0ACh W_TXREQ_RESET      09Ch W_INTERNAL        ? (zero)              |
|       0AEh W_TXREQ_SET        09Ch W_INTERNAL        ? (zero)              |
|       0B4h W_TXBUF_RESET      0B6h W_TXBUSY          ? (zero)              |
|       158h W_BB_CNT           15Ch W_BB_READ         ? (zero)              |
|       15Ah W_BB_WRITE         ? (zero)               ? (zero)              |
|       178h W_INTERNAL         17Ch W_RF_DATA2        ? (zero)              |
|       20Ch W_INTERNAL         09Ch W_INTERNAL        ? (zero)              |
|       21Ch W_IF_SET           010h W_IF              010h-OR-05Ch-OR-more? |
|       228h W_X_228h           ? (zero)               ? (zero)              |
|       298h W_INTERNAL         084h W_TXBUF_TIM       084h W_TXBUF_TIM      |
|       2A8h W_INTERNAL         238h W_INTERNAL        238h W_INTERNAL       |
|       2B0h W_INTERNAL         084h W_TXBUF_TIM       084h W_TXBUF_TIM      |
+----------------------------------------------------------------------------+
```

Notes: The mirror to W_RXBUF_RD_DATA is a passive mirror.
The DS-Lite mirror at 21Ch consists of several ports ORed with each other (known components are Ports 010h and 05Ch, but there seem to be even more values ORed with it).

### Port Mirror Regions
The Wifi Port region at 000h..FFFh is mirrored to 1000h..1FFFh, 6000h..6FFFh, and 7000h..7FFFh. Many of that mirrored ports are PASSIVE mirrors. Eg. reading from 1060h (mirror of Port 060h, W_RXBUF_RD_DATA) returns the old W_RXBUF_RD_DATA value (but without loading a new value from Wifi RAM, and without incrementing W_RXBUF_RD_ADDR). However, other registers, like W_RANDOM do have ACTIVE mirrors.



