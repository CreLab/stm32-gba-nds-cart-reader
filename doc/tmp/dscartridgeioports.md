# DS Cartridge I/O Ports


The Gamecard bus registers can be mapped to NDS7 or NDS9 via EXMEMCNT, see
- [DS Memory Control](./dsmemorycontrol.md)

### 40001A0h - NDS7/NDS9 - AUXSPICNT - Gamecard ROM and SPI Control (R/W)

```
+---------------------------------------------------------------------------------+
|       0-1   SPI Baudrate        (0=4MHz/Default, 1=2MHz, 2=1MHz, 3=512KHz)      |
|       2-5   Not used            (always zero)                                   |
|       6     SPI Hold Chipselect (0=Deselect after transfer, 1=Keep selected)    |
|       7     SPI Busy            (0=Ready, 1=Busy) (presumably Read-only)        |
|       8-12  Not used            (always zero)                                   |
|       13    NDS Slot Mode       (0=Parallel/ROM, 1=Serial/SPI-Backup)           |
|       14    Transfer Ready IRQ  (0=Disable, 1=Enable) (for ROM, not for AUXSPI) |
|       15    NDS Slot Enable     (0=Disable, 1=Enable) (for both ROM and AUXSPI) |
+---------------------------------------------------------------------------------+
```

The \"Hold\" flag should be cleared BEFORE transferring the LAST data unit, the chipselect will be then automatically cleared after the transfer, the program should issue a WaitByLoop(12) on NDS7 (or longer on NDS9) manually AFTER the LAST transfer.

### 40001A2h - NDS7/NDS9 - AUXSPIDATA - Gamecard SPI Bus Data/Strobe (R/W)
The SPI transfer is started on writing to this register, so one must \<write\> a dummy value (should be zero) even when intending to \<read\> from SPI bus.

```
+-----------------------------------------------------------------------+
|       0-7  Data                                                       |
|       8-15 Not used (always zero)                                     |
+-----------------------------------------------------------------------+
```

During transfer, the Busy flag in AUXSPICNT is set, and the written DATA value is transferred to the device (via output line), simultaneously data is received (via input line). Upon transfer completion, the Busy flag goes off, and the received value can be then read from AUXSPIDATA, if desired.

### 40001A4h - NDS7/NDS9 - ROMCTRL - Gamecard Bus ROMCTRL (R/W)

```
+------------------------------------------------------------------------------------+
|       0-12  KEY1 gap1 length  (0-1FFFh) (forced min 08F8h by BIOS) (leading gap)   |
|       13    KEY2 encrypt data (0=Disable, 1=Enable KEY2 Encryption for Data)       |
|       14     "SE" Unknown? (usually same as Bit13) (does NOT affect timing?)       |
|       15    KEY2 Apply Seed   (0=No change, 1=Apply Encryption Seed) (Write only)  |
|       16-21 KEY1 gap2 length  (0-3Fh)   (forced min 18h by BIOS) (200h-byte gap)   |
|       22    KEY2 encrypt cmd  (0=Disable, 1=Enable KEY2 Encryption for Commands)   |
|       23    Data-Word Status  (0=Busy, 1=Ready/DRQ) (Read-only)                    |
|       24-26 Data Block size   (0=None, 1..6=100h SHL (1..6) bytes, 7=4 bytes)      |
|       27    Transfer CLK rate (0=6.7MHz=33.51MHz/5, 1=4.2MHz=33.51MHz/8)           |
|       28    KEY1 Gap CLKs (0=Hold CLK High during gaps, 1=Output Dummy CLK Pulses) |
|       29    RESB Release Reset  (0=Reset, 1=Release) (cannot be cleared once set)  |
|       30    Data Direction "WR" (0=Normal/read, 1=Write, for FLASH/NAND carts)     |
|       31    Block Start/Status  (0=Ready, 1=Start/Busy) (IRQ See 40001A0h/Bit14)   |
+------------------------------------------------------------------------------------+
```

The cartridge header is booted at 4.2MHz CLK rate, and following transfers are then using ROMCTRL settings specified in cartridge header entries \[060h\] and \[064h\], which are usually using 6.7MHz CLK rate for the main data transfer phase (whereof, older MROM carts can actually transfer 6.7Mbyte/s, but newer 1T-ROM carts default to reading 200h-byte blocks with gap1=657h, thus reaching only 1.6Mbyte/s).
Transfer length of null, four, and 200h..4000h bytes are supported by the console, however, retail cartridges cannot cross 1000h-byte boundaries (and, SanDisk ROM chips and Samsung NAND chips cannot transfer more than 200h bytes).
### Default cart header entries

```
+-----------------------------------------------------------------------+
|       hdr[60h]   hdr[64h]   hdr[6Eh]                                  |
|       00586000h  001808F8h  051Eh     ;older/faster MROM              |
|       00416657h  081808F8h  0D7Eh     ;newer/slower 1T-ROM            |
|       00416657h  081808F8h  0D7Eh     ;newer/slower NAND              |
+-----------------------------------------------------------------------+
```

### Older/Faster MROM
The romctrl values in cartheader\[60h,64h\] are okay, but the secure delay in \[6Eh\] is nonsense (should be zero).
### Misdeclared MROM
Some carts like SystemFlaw and BiggestLoser are actually containing MROM chips despite of having 1T-ROM values in cart header (gap1=657h is making loading insane slow, gap2=01h causes errors on 1000h-byte blocks, and secure.clk=4.2MHz is slowing down secure area loading, combined with even slower secure area delay despite of not needing any delay for MROM).
As the cart header entries are wrong, some other detection is needed: This can be probably done by checking ChipID.bit31 (or otherwise by testing if 1000h-block reading works with gap1=01h, if so, then it\'s 1T-ROM).
### Newer/Slower 1T-ROM
Actual 1T-ROM carts can be very slow, especially when using the insane cart header values and default firmware blocksize of 200h bytes which drops loading speed from 6.7Mbytes/s to 1.6Mbyte/s (as workaround, use gap1=180h, blocksize=1000h, also secure area delay should be 400h, not D7Eh) (tested/working for CookingCoach, unknown if that timings work for all other carts).
### Superslow Writeable NAND
This is having the same official insane delays as 1T-ROM, but with less tolerance for faster timings (fastest working values are gap1=380h, blocksize=200h, secure delay 400h, plus 20ms delay after releasing reset).
### Cart Reset
Reset flag in bit29 can be set once only (to release reset), the only way to clear the bit is power-off. However, there are some ways to issue resets:
1) On NDS: Manually eject/insert the cart (that won\'t affect bit29, but the cart will reset itself anyways upon power loss) (eject on DSi will power-off the cart slot).
2) If one of the two ROMCTRL registers (on ARM7 and ARM9) is still zero: Temporarily toggle ARM7/ARM9 cart access via EXMEMCNT on ARM9 side.
3) On DSi: If the 2nd cart slot ROMCTRL register (40021A4h) is still zero: Temporarily swap 1ns/2nd cart slot via SCFG_MC.bit15 on ARM7 side.
4) On DSi: Use SCFG_MC to toggle cart power off/on; this will actually reset bit29, the DSi firmware is actually using that method, but it\'s very slow (takes about 300ms, for the power-off wait, plus (unneccassary) hardcoded power-on delays).

### 40001A8h - NDS7/NDS9 - Gamecard bus 8-byte Command Out
The separate commands are described in the Cartridge Protocol chapter, however, once when the BIOS boot procedure has completed, one would usually only need command \"B7aaaaaaaa000000h\", for reading data (usually 200h bytes) from address aaaaaaaah (which should be usually aligned by 200h).

```
+------------------------------------------------------------------------------------+
|       0-7   1st Command Byte (at 40001A8h) (eg. B7h) (MSB)                         |
|       8-15  2nd Command Byte (at 40001A9h) (eg. addr bit 24-31)                    |
|       16-23 3rd Command Byte (at 40001AAh) (eg. addr bit 16-23)                    |
|       24-31 4th Command Byte (at 40001ABh) (eg. addr bit 8-15) (when aligned=even) |
|       32-39 5th Command Byte (at 40001ACh) (eg. addr bit 0-7)  (when aligned=00h)  |
|       40-47 6th Command Byte (at 40001ADh) (eg. 00h)                               |
|       48-57 7th Command Byte (at 40001AEh) (eg. 00h)                               |
|       56-63 8th Command Byte (at 40001AFh) (eg. 00h) (LSB)                         |
+------------------------------------------------------------------------------------+
```

Observe that the command/parameter MSB is located at the smallest memory location (40001A8h), ie. compared with the CPU, the byte-order is reversed.

### 4100010h - NDS7/NDS9 - Gamecard bus 4-byte Data In (R) (or W)

```
+-----------------------------------------------------------------------+
|       0-7   1st received Data Byte (at 4100010h)                      |
|       8-15  2nd received Data Byte (at 4100011h)                      |
|       16-23 3rd received Data Byte (at 4100012h)                      |
|       24-31 4th received Data Byte (at 4100013h)                      |
+-----------------------------------------------------------------------+
```

After sending a command, data can be read from this register manually (when the DRQ bit is set), or by DMA (with DMASAD=4100010h, Fixed Source Address, Length=1, Size=32bit, Repeat=On, Mode=DS Gamecard).

### 40001B0h - 32bit - NDS7/NDS9 - Encryption Seed 0 Lower 32bit (W)
### 40001B4h - 32bit - NDS7/NDS9 - Encryption Seed 1 Lower 32bit (W)
### 40001B8h - 16bit - NDS7/NDS9 - Encryption Seed 0 Upper 7bit (bit7-15 unused)
### 40001BAh - 16bit - NDS7/NDS9 - Encryption Seed 1 Upper 7bit (bit7-15 unused)
These registers are used by the NDS7 BIOS to initialize KEY2 encryption (and there\'s normally no need to change that initial settings). Writes to the Seed registers do not have direct effect on the internal encryption registers, until the Seed gets applied by writing \"1\" to ROMCTRL.Bit15.

```
+-----------------------------------------------------------------------+
|      For more info:                                                   |
+-----------------------------------------------------------------------+
```

- [DS Encryption by Random Seed (KEY2)](./dsencryptionbyrandomseedkey2.md)
Note: There are \<separate\> Seed registers for both NDS7 and NDS9, which can be applied by ROMCTRL on NDS7 and NDS9 respectively (however, once when applied to the internal registers, the new internal setting is used for \<both\> CPUs).



