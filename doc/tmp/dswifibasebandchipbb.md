# DS Wifi Baseband Chip (BB)


BB-Chip Mitsumi MM3155 (DS), or BB/RF-Chip Mitsumi MM3218 (DS-Lite)

### 4808158h - W_BB_CNT - Baseband serial transfer control (W)

```
+-------------------------------------------------------------------------------+
|       0-7   Index     (00h-68h)                                               |
|       8-11  Not used  (should be zero)                                        |
|       12-15 Direction (5=Write BB_WRITE to Chip, 6=Read from Chip to BB_READ) |
+-------------------------------------------------------------------------------+
```

Transfer is started after writing to this register.

### 480815Ah - W_BB_WRITE - Baseband serial write data (W)

```
+-----------------------------------------------------------------------+
|       0-7   Data to be sent to chip (by following W_BB_CNT transfer)  |
|       8-15  Not used (should be zero)                                 |
+-----------------------------------------------------------------------+
```


### 480815Ch - W_BB_READ - Baseband serial read data (R)

```
+-----------------------------------------------------------------------+
|       0-7   Data received from chip (from previous W_BB_CNT transfer) |
|       8-15  Not used (always zero)                                    |
+-----------------------------------------------------------------------+
```


### 480815Eh - W_BB_BUSY - Baseband serial busy flag (R)

```
+-----------------------------------------------------------------------+
|       0     Transfer Busy (0=Ready, 1=Busy)                           |
|       1-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Used to sense transfer completion after writes to W_BB_CNT.
Not sure if I am doing something wrong\... but the busy flag doesn\'t seem to get set immediately after W_BB_CNT writes, and works only after waiting a good number of clock cycles?

### 4808160h - W_BB_MODE (R/W)

```
+-----------------------------------------------------------------------+
|       0-7   Always zero                                               |
|       8     Unknown (usually 1) (no effect no matter what setting?)   |
|       9-13  Always zero                                               |
|       14    Unknown (usually 0) (W_BB_READ gets unstable when set)    |
|       15    Always zero                                               |
+-----------------------------------------------------------------------+
```

This register is initialized by firmware bootcode - don\'t change.

### 4808168h - W_BB_POWER (R/W)

```
+-----------------------------------------------------------------------+
|       0-3   Disable whatever   (usually 0Dh=disable)                  |
|       4-14  Always zero                                               |
|       15    Disable W_BB_ports (usually 1=Disable)                    |
+-----------------------------------------------------------------------+
```

Must be set to 0000h before accessing BB registers.

### Read-Write-Ability of the BB-Chip Mitsumi MM3155 registers (DS)

```
+-----------------------------------------------------------------------+
|       Index    Num Dir Expl.                                          |
|       00h        1 R   always 6Dh (R) (Chip ID)                       |
|       01h..0Ch  12 R/W 8bit R/W                                       |
|       0Dh..12h   6 -   always 00h                                     |
|       13h..15h   3 R/W 8bit R/W                                       |
|       16h..1Ah   5 -   always 00h                                     |
|       1Bh..26h  12 R/W 8bit R/W                                       |
|       27h        1 -   always 00h                                     |
|       28h..4Ch     R/W 8bit R/W                                       |
|       4Dh        1 R   always 00h or BFh (depending on other regs)    |
|       4Eh..5Ch     R/W 8bit R/W                                       |
|       5Dh        1 R   always 01h (R)                                 |
|       5Eh..61h     -   always 00h                                     |
|       62h..63h   2 R/W 8bit R/W                                       |
|       64h        1 R   always FFh or 3Fh (depending on other regs)    |
|       65h        1 R/W 8bit R/W                                       |
|       66h        1 -   always 00h                                     |
|       67h..68h   2 R/W 8bit R/W                                       |
|       69h..FFh     -   always 00h                                     |
+-----------------------------------------------------------------------+
```


### Read-Write-Ability of the BB/RF-Chip Mitsumi MM3218 (DS-Lite)
Same as above. Except that reading always seems to return \[5Dh\]=00h. And, for whatever reason, Nintendo initializes DS-Lite registers by writing \[00h\]=03h and \[66h\]=12h. Nethertheless, the registers always read as \[00h\]=6Dh and \[66h\]=00h, ie. same as on original DS.

### Important BB Registers
Registers 0..68h are initialized by firmware bootcode, and (most) of these settings do not need to be changed by other programs, except for:

```
+----------------------------------------------------------------------------------+
|       Addr Initial Meaning                                                       |
|       01h 0x9E    [unsetting/resetting bit 7 initializes/resets the system?]     |
|       02h         unknown (firmware is messing with this register)               |
|       06h         unknown (firmware is messing with this register, too)          |
|       13h 0x00    CCA operation - criteria for receiving                         |
|                         0=only use Carrier Sense (CS)                            |
|                         1=only use Energy Detection (ED)                         |
|                         2=receive if CS OR ED                                    |
|                         3=receive only if CS AND ED                              |
|       1Eh 0xBB    see change channels flowchart (Ext. Gain when RF[09h].bit16=0) |
|       35h 0x1F    Energy Detection (ED) criteria                                 |
|                   value 0..61 (representing energy levels of -60dBm to -80dBm)   |
+----------------------------------------------------------------------------------+
```




