# DSi Teak MMIO\[8020h\] - Timers (TMR)


### MMIO\[8020h/8030h\] - Timer 0/1 Control (R/W)

```
+--------------------------------------------------------------------------------+
|       0-1   Time prescaler (0=Div1, 1=Div2, 2=Div4, 3=Div16)                   |
|       2-4   Count mode                                                         |
|              0h: single count     Stop at zero                                 |
|              1h: auto restart     Wrap from zero to Reload value               |
|              2h: free running     Wrap from zero to FFFFFFFFh                  |
|              3h: event count      Decrement manually, and stop at zero         |
|              4h: watchdog mode 1  Trigger Teak Reset at zero                   |
|              5h: watchdog mode 2  Trigger Teak NMI at zero                     |
|              6h: watchdog mode 3  Trigger Unacknowledgeable-Timer-IRQ at zero? |
|              7h: reserved         Same as mode 0 (stop at zero)                |
|       5     Unused (0)                                                         |
|       6     Output signal polarity                (0=Normal, 1=Invert/Buggy?)  |
|       7     Clear output signal; when bit14-15=0  (0=No change, 1=Clear)   (W) |
|       8     Pause the counter                     (0=Unpause, 1=Pause)         |
|       9     Freeze COUNTER_L/H register value     (0=Freeze, 1=Update)         |
|              Note: Bit8/Bit9 can be forced to always 1 via other Timer's Bit13 |
|       10    Restart/Reload the counter            (0=No change, 1=Restart) (W) |
|       11    Breakpoint requests enable   (0=Disable, 1=Enable) (DANGER/TRAP)   |
|       12    Clock source (0=InternalClk=134MHz/107MHz, 1=ExternalClk=None)     |
|       13    General Purpose (somehow interact between Timer 0 and 1)           |
|              Timer0: Force Timer1.Control.Bit9=1  (0=No, 1=Yes/ForceUpdate)    |
|              Timer1: Force Timer0.Control.Bit8=1  (0=No, 1=Yes/ForcePause)     |
|       14-15 Clear output signal automatically (0=No, 1/2/3=After 2/4/8 cycles) |
+--------------------------------------------------------------------------------+
```

The InternalClk is different for Timer 0 and 1, and depends on GLUE setting:

```
+----------------------------------------------------------------------------------+
|       For Timer 0 (no "waitstates")   --> 134.055928MHz                          |
|       For Timer 1 (with "waitstates") --> 107.244742MHz (aka 134.055928MHz/1.25) |
|       For Timer 1 (if GLUE_CFG0.bit0) --> Timer0_TOUT (bugs if Timer0_Reload<3)  |
|       Unknown what "waitstates" refers to, probably not the Z0/Z1/Z2/Z3 waits?   |
+----------------------------------------------------------------------------------+
```

Bit10 is automatically cleared after writing - however, when using prescaler other than Div1, it may take a few cycles until bit10 gets cleared (and perhaps also takes time until it is processed??? if so, one shouldn\'t clear bit10 in that timeslot).
Bit7 is usually cleared after writing - but not always, still unknown what/when that happens?

### MMIO\[8022h/8032h\] - Timer 0/1 Trigger Event/Watchdog (W)

```
+-------------------------------------------------------------------------+
|       0     In Event Mode: Decrement Counter (0=No change, 1=Decrement) |
|             In Watchdog Mode: Reload Counter (0=No change, 1=Reload)    |
|       1-15  Unused (0)                                                  |
+-------------------------------------------------------------------------+
```


### MMIO\[8024h/8034h\] - Timer 0/1 Reload value, bit0-15 (R/W)
### MMIO\[8026h/8036h\] - Timer 0/1 Reload value, bit16-31 (R/W)

```
+-----------------------------------------------------------------------+
|       0-31  Start/Reload value for decrementing counter               |
+-----------------------------------------------------------------------+
```

Used as start/reload value; copied to counter when setting Control.bit10, or after reaching 0 in auto-restart mode, or when writting trigger bit in watchdog mode.
Not used in free-run mode (which starts at current counter value, and wraps from 0 to FFFFFFFFh).

### MMIO\[8028h/8038h\] - Timer 0/1 Counter value, bit0-15 (R)
### MMIO\[802Ah/803Ah\] - Timer 0/1 Counter value, bit16-31 (R)

```
+-----------------------------------------------------------------------+
|       0-31  Current (or frozen) decrementing counter value            |
+-----------------------------------------------------------------------+
```

When using freeze, counter keeps decreasing in background, but reading the counter register returns the frozen value (latched when changing Control.bit9 from 1-to-0).

### MMIO\[802Ch/803Ch\] - Timer 0/1 PWM Reload value, bit0-15 (R/W)
### MMIO\[802Eh/803Eh\] - Timer 0/1 PWM Reload value, bit16-31 (R/W)

```
+-----------------------------------------------------------------------+
|       0-31  Restart value for PWM counter (uh, maybe PWM duty?)       |
+-----------------------------------------------------------------------+
```

Unknown if/when/how this is used (maybe just goes to an unimplemented PWM output pin).



