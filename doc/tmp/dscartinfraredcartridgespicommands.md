# DS Cart Infrared Cartridge SPI Commands


There are two NDS cart firmware versions with minor differences:

```
+-----------------------------------------------------------------------+
|       OLD was used in Walk with Me (maybe also Active Health?)        |
|       NEW was used in the P-Letter game series                        |
+-----------------------------------------------------------------------+
```

The IR-port is accessed via SPI bus commands; that bus is also shared for accessing FLASH/EEPROM memory (via 00h-prefix).

### Infrared NDS cartridge SPI command summary

```
+-------------------------------------------------------------------------------------+
|       04h,04h                  Initial dummy in walk with me (bugged read or wrdi?) |
|       00h,cmd,params[...]      Savedata access                                      |
|       01h,00h,00h              Infrared RX (none, len=0, plus dummy data=0)         |
|       01h,len,data[len]        Infrared RX (OLD: max 84h bytes, NEW: max B8h bytes) |
|       02h,data[...]            Infrared TX (OLD: max 84h bytes, NEW: max B8h bytes) |
|       02h,F2h,data[...]        OLD: ignored (refuses to TX data starting with F2h)  |
|       03h,msb,lsb,data         Memory Write 8bit   ;\MOV.B                          
|       04h,msb,lsb,data         Memory Read 8bit    ;/                               |
|       05h,msb,lsb,data,data    Memory Write 16bit  ;\MOV.W (fails on 8bit SFRs?)    
|       06h,msb,lsb,data,data    Memory Read 16bit   ;/                               |
|       07h,00h,num,num,num,...  Blah, returns num params from previous spi command   |
|       08h..FFh                 OLD: Ignored (keeps awaiting a SPI command byte)     |
|       08h,ver                  NEW: Returns version (ver=AAh)                       |
|       09h..FFh                 OLD: Ignored (returns zeropadding)                   |
+-------------------------------------------------------------------------------------+
```


### SPI Transfers
The SPI transfers are working at max 1MHz transfer clock, and they do require a delay after each byte:
Waiting 800h clks at 33MHz seems to work okay (eg. MOV r0,200h // SWI 03h on ARM7). The NEW ROM version disables IR polling when doing the SPI transfers for RX/TX data blocks (so it may work with shorter delays between the data\[\...\] bytes).
The savedata access is directly passed to the FLASH/EEPROM chip and does work at 4MHz without delays (except, the leading 00h prefix must be transferred at 1MHz plus delay, and another delay is needed when releasing chipselect after last byte).
Note: The NDS cart slot IRQ pin is GNDed in Walk with Me (ie. there is no IRQ for SPI/IR status).
SPI access does require cart power on and reset (via DSi SCFG registers), but doesn\'t require any ROM commands like secure area loading. Confusingly, the ROM Chip ID seems to have an IR flag in bit0 of 3rd byte (although the ROM chip isn\'t wired to IR hardware at all).

### IR Transfers
The IR transfers are using a fixed baudrate: 115200 baud, 8n1, one-directional (RX gets disabled during TX). The RX/TX commands are transferring \"packets\" (with each \"packet\" being terminated by a \"pause\" in the IR transmission; that \"packet+pause\" mechanism is making it impossible to use streaming for transferring larger blocks that exceed the buffer size of max 84h or B8h bytes).
The RX command will return empty data with len=00h until a WHOLE packet has been received via IR.
The TX command won\'t start the IR transfer until the WHOLE packet has been written via SPI, with packet end indicated by releasing chip select.
There is no way to detect TX transfer end (other than computing the expected tranfer time and using an ARM timer).
However, Nintendo is sending a Reply for most TX commands, so one can simply wait for RX packets to determine TX completion (if neither Reply nor Checksum Error are received then one will still need timeout handling).

### Memory Read/Write
These commands are normally not used. The memory commands do forcefully abort IR transfers, so they can\'t be used for polling IR transfer status.
However, they can be used for dumping the firmware ROM, and they could be used to upload/execute custom code in RAM, which may allow to overcome some of the above IR transfer restrictions (other baudrates, fewer delays, better streaming, not ignoring byte F2h, etc).

### IR Cart Detection
NDS/DSi Carts with IR support are having special game code with \"I\" in first letter (NTR-Ixxx or TWL-Ixxx). There are reportedly pirate/bootleg versions of the P-Letter games without IR hardware, unknown if they do nethertheless have the \"I\" in the gamecode.
Emulators can detect the leading 00h prefix for Savedata access, although that detection may go wrong if preceeded by IR access. Emulators can additionally detect the slow 1MHz SPI clock used for IR access (and for 00h prefix).



