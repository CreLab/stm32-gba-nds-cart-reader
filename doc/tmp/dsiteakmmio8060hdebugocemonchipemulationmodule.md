# DSi Teak MMIO\[8060h\] - Debug (OCEM, On-chip Emulation Module)


### MMIO\[8060h\] - OCEM Program Flow Trace Buffer (PFT), bit0-15 (R)
### MMIO\[8061h\] - OCEM Program Flow Trace Buffer (PFT), bit16-31 (R)
This buffer contains addresses of the 16 most recent jump opcodes, reading returns the oldest of those 16 addresses (or 16 random address/page values if read after reset). One can disable buffer updating via MMIO\[8070h\] (eg. to avoid jumps inside of a debug handler to be written to the buffer). There is \"buffer full\" condition that gets set 16 jumps after reset, and that can trap an optional buffer full exception.

```
+-----------------------------------------------------------------------+
|       0-17   Program Flow Trace Address                               |
|       18-23  Unused (0)                                               |
|       24-27  Program Flow Trace Page                                  |
|       28-31  Unused (0)                                               |
+-----------------------------------------------------------------------+
```

Unknown if there is any way to \"make the buffer empty\", either by clearing the buffer, or by removing entries until it gets empty. Also, there is no known way to read the next buffer entry, except for one trick: temporarily re-enable buffer updates via MMIO\[8070h\] and issue a dummy jump; this will add a new entry, and reading will then return the next oldest entry; by that, the buffer won\'t get empty (but, when ignoring the address of the dummy jump, one can extract the actual non-dummy data from the buffer).

### MMIO\[8062h/8064h/8066h\] - OCEM Program Break Address 1/2/3, bit0-15 (R/W)
### MMIO\[8063h/8065h/8067h\] - OCEM Program Break Address 1/2/3, bit16-31 (R/W)

```
+-----------------------------------------------------------------------+
|       0-17   Program Break Address                                    |
|       18-23  Unused (0)                                               |
|       24-27  Program Break Page (should be usually 00h)               |
|       28-31  Unused (0)                                               |
+-----------------------------------------------------------------------+
```


### MMIO\[8068h/8069h/806Ah\] - OCEM Program Break Counter 1/2/3 (R/W)

```
+----------------------------------------------------------------------------+
|       0-7    Program Address Break Counter (decrements upon PC=break.addr) |
|       8-15   Unused (0)                                                    |
+----------------------------------------------------------------------------+
```

Break triggers upon count zero. Writing count=NNh will trap after program counter had hit the break address NNh times (writing count=00h will trigger immediately, without even hitting the break address).

### MMIO\[806Bh\] - OCEM Data Break Mask (R/W)
### MMIO\[806Ch\] - OCEM Data Break Address (R/W)

```
+-----------------------------------------------------------------------+
|       0-15   Mask/Address                                             |
+-----------------------------------------------------------------------+
```


### MMIO\[806Dh\] - OCEM Breakpoint Enable Flags DANGER (0=Disable, 1=Enable/Trap)

```
+-------------------------------------------------------------------------------+
|       0      Data value break point on data write transaction                 |
|       1      Data value break point on data read transaction                  |
|       2      Data address break point as a result on data write transaction   |
|       3      Data address break point as a result on data read transaction    |
|       4      Simultaneous data address and data value match                   |
|       5      External register write transaction  ;\(aka ext0/1/2/3?)         
|       6      External register read transaction   ;/                          |
|       7      Program Address break 1 count zero                               |
|       8      Program Address break 2 count zero                               |
|       9      Program Address break 3 count zero                               |
|       10     Break on any program jumps instead of executing the next address |
|       11     Break on detection of interrupt service routine                  |
|       12     Break as a result of program flow trace buffer full              |
|       13     Break when returning to the beginning of block repeat loop       |
|       14     Break on illegal condition (uh, are that... illegal opcodes?)    |
|       15     Single Step                                                      |
+-------------------------------------------------------------------------------+
```

Note: Data value refers to the \"dvm\" CPU-core register. Data write matches can occur on things like \"mov r0,1234h\" or \"addv r0,1\" (when r0 becomes equal to dvm).

### MMIO\[806Eh\] - OCEM Mode/Indication? (R/W)

```
+-----------------------------------------------------------------------------------+
|       0      Program Flow Trace Buffer full (0=Not full/OldestIsGarbage, 1=Full)  |
|       1-11   Unknown (R/W)                                                        |
|       12     MOVD instruction detected (uh, usually 1, even when not using movd?) |
|       13     User reset activated while in break point service routine            |
|       14     Boot mode   (0=No, 1=Yes)                                            |
|       15     Debug mode  (0=No, 1=Yes)                                            |
+-----------------------------------------------------------------------------------+
```

Unknown if this is a mode or status register, or mixup thereof?

### MMIO\[806Fh\] - OCEM Breakpoint Status Flags (R/W)

```
+----------------------------------------------------------------------------------+
|       0      Break caused by Data value match                                    |
|       1      Break caused by Data address match                                  |
|       2      Break caused by Data value and data address match                   |
|       3      Break caused by User defined register transaction (aka ext0/1/2/3?) |
|       4      Break caused by an external event (aka what?)                       |
|       5      Break caused by Program address break 1 count zero                  |
|       6      Break caused by Program address break 2 count zero                  |
|       7      Break caused by Program address break 3 count zero                  |
|       8-10   Unknown (R/W)                                                       |
|       11     Break caused by Branch break point                                  |
|       12     Break caused by Interrupt break point                               |
|       13     Break caused by Program Flow Trace Buffer full                      |
|       14     Break caused by Illegal break point                                 |
|       15     Break caused by Software trap                                       |
+----------------------------------------------------------------------------------+
```

Uh, R/W mask is BFFFh, ie. bit14 is always 0, that doesn\'t match up with above description?

### MMIO\[8070h\] - OCEM Program Flow Trace Update Disable (R/W)

```
+-------------------------------------------------------------------------+
|       0      Disable Program Flow Buffer Updating (0=Enable, 1=Disable) |
|       1-15   Unused (0)                                                 |
+-------------------------------------------------------------------------+
```


### MMIO\[8072h\] - Unknown 16bit? (R/W)

```
+-----------------------------------------------------------------------+
|       0-15   Unknown (R/W)                                            |
+-----------------------------------------------------------------------+
```

Maybe be \"programming model signature\" mentioned in perxteak.per (though that is claimed to use only upper 8bit)? That signature might be some general purpose value to notify the debugger what kind of code is executed?

### MMIO\[8074h\] - OCEM Boot/Debug Mode (R)

```
+-----------------------------------------------------------------------+
|       0-13   Unused? (0)                                              |
|       14     Boot mode   (0=No, 1=Yes)                                |
|       15     Debug mode  (0=No, 1=Yes)                                |
+-----------------------------------------------------------------------+
```

Usually contains the same mode bits as written to MMIO\[806Eh\].bit14/bit15 (maybe one of the registers contains the OLD mode bits; when entering a debug handler or so).



