# DS Wifi Power-Down Registers


### 4808036h - W_POWER_US (R/W)

```
+-----------------------------------------------------------------------+
|       0     Disable W_US_COUNT and W_BB_ports  (0=Enable, 1=Disable)  |
|       1     Unknown (usually 0)                                       |
|       2-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

Bit0=0 enables RFU by setting RFU.Pin11=HIGH, which activates the 22.000MHz oscillator on the RFU board, the 22MHz clock is then output to RFU.Pin26.

### 4808038h - W_POWER_TX (R/W)
transmit-related power save or sth
init from firmware\[05Ch\]

```
+----------------------------------------------------------------------------+
|       0     Auto Wakeup (1=Leave Idle Mode a while after Pre-Beacon IRQ15) |
|       1     Auto Sleep  (0=Enter Idle Mode on Post-Beacon IRQ13)           |
|       2     Unknown                                                        |
|       3     Unknown (Write-only) (used by firmware)                        |
|       4-15  Always zero                                                    |
+----------------------------------------------------------------------------+
```


### 480803Ch - W_POWERSTATE (R/W)/(R)

```
+-------------------------------------------------------------------------------+
|       0     Unknown (usually 0)                         (R/W)                 |
|       1     Request Power Enable (0=No, 1=Yes/queued)   (R/W, but not always) |
|       2-7   Always zero                                                       |
|       8     Indicates that Bit9 is about the be cleared (Read only)           |
|       9     Current power state (0=Enabled, 1=Disabled) (Read only)           |
|       10-15 Always zero                                                       |
+-------------------------------------------------------------------------------+
```

\[value =1: queue disable power state\] ;\<\-- seems to be incorrect
\[value =2: queue enable power state\] ;\<\-- seems to be correct
Enabling causes wakeup interrupt (IRQ11).
Note: That queue stuff seems to work only if W_POWER_US=0 and W_MODE_RST=1.

### 4808040h - W_POWERFORCE - Force Power State (R/W)

```
+-----------------------------------------------------------------------------------+
|       0     New value for W_POWERSTATE.Bit9  (0=Clear/Delayed, 1=Set/Immediately) |
|       1-14  Always zero                                                           |
|       15    Apply Bit0 to W_POWERSTATE.Bit9  (0=No, 1=Yes)                        |
+-----------------------------------------------------------------------------------+
```

Setting W_POWERFORCE=8001h whilst W_POWERSTATE.Bit9=0 acts immediately:

```
+----------------------------------------------------------------------------+
|       (Doing this is okay. Switches to power down mode. Similar to IRQ13.) |
|       [4808034h]=0002h ;W_INTERNAL                                         |
|       [480803Ch]=02xxh ;W_POWERSTATE                                       |
|       [48080B0h]=0000h ;W_TXREQ_READ                                       |
|       [480819Ch]=0046h ;W_RF_PINS                                          |
|       [4808214h]=0009h ;W_RF_STATUS (idle)                                 |
+----------------------------------------------------------------------------+
```

Setting W_POWERFORCE=8000h whilst W_POWERSTATE.Bit9=1 acts delayed:

```
+--------------------------------------------------------------------------------+
|       (Don't do this. After that sequence, the hardware seems to be messed up) |
|       W_POWERSTATE.Bit8 gets set to indicate the pending operation,            |
|       while pending, changes to W_POWERFORCE aren't applied to W_POWERSTATE,   |
|       while pending, W_POWERACK becomes Read/Write-able,                       |
|       writing 0000h to W_POWERACK does clear W_POWERSTATE.Bit8,                |
|       and does apply POWERFORCE.Bit0 to W_POWERSTATE.Bit9                      |
|       and does deactivate Port W_POWERACK again.                               |
+--------------------------------------------------------------------------------+
```


### 4808048h - W_POWER\_? (R/W)

```
+-----------------------------------------------------------------------+
|       0     Unknown                                                   |
|       1     Unknown                                                   |
|       2-15  Always zero                                               |
+-----------------------------------------------------------------------+
```

At whatever time (during transmit or so) it gets set to 0003h by hardware.

See also: POWCNT2, W_BB_POWER.



