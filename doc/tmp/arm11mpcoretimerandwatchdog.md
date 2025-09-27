# ARM11 MPCore - Timer and Watchdog


### Timer and Watchdog
Below registers are for the LOCAL CPU core (the other CPU cores have their own registers, mapped at the same address).

### 17E00600h - MPCore Timer0 Reload Value (R/W)
### 17E00620h - MPCore Timer1/Watchdog Reload Value (R/W)

```
+-----------------------------------------------------------------------+
|       0-31  Reload Value                                              |
+-----------------------------------------------------------------------+
```

The Reload value is copied to the Counter in two situations:
1) When the Counter decrements to zero (with Auto-reload enabled).
2) When writing to the Reload register (in watchdog mode this is the only way to refresh the watchdog, and to prevent it from resetting the CPU).

### 17E00604h - MPCore Timer0 Counter Value (R/W)
### 17E00624h - MPCore Timer1/Watchdog Counter Value (R/W, R in watchdog mode)

```
+-----------------------------------------------------------------------+
|       0-31  Counter Value (decrementing)                              |
+-----------------------------------------------------------------------+
```

If the MP11 CPU belonging to the timer is in debug state, the counter does not decrement until the MP11 CPU returns to non debug state.

### 17E00608h - MPCore Timer0 Control Register (R/W)
### 17E00628h - MPCore Timer1/Watchdog Control Register (R/W, R in watchdog mode)

```
+----------------------------------------------------------------------------------+
|       0     Timer Enable     (0=Stop, 1=Enable/Decrement)                        |
|       1     Auto-reload      (0=One-shot, stop at zero, 1=Auto-reload at zero)   |
|       2     Interrupt Enable (0=Disable, 1=Trigger Interrupt ID 1Dh/1Eh at zero) |
|       3     Timer0: Reserved      (0=Timer, fixed, always 0)                     |
|       3     Timer1: Watchdog mode (0=Timer, 1=Watchdog)                          |
|               Note: Bit3 can be cleared via 17E00634h only                       |
|       4-7   Reserved (0)                                                         |
|       8-15  Prescaler (0..255 = CPU_CLK/2 divided by 1..256)                     |
|       16-31 Reserved (0)                                                         |
+----------------------------------------------------------------------------------+
```


### 17E0060Ch - MPCore Timer0 Interrupt Status (R/ack)
### 17E0062Ch - MPCore Timer1/Watchdog Interrupt Status (R/ack)

```
+-----------------------------------------------------------------------------------+
|       0     Event flag (counter reached zero)  (0=No, 1=Event)  ;write 1 to clear |
|       1-31  Reserved                                                              |
+-----------------------------------------------------------------------------------+
```

If the timer interrupt is enabled, Interrupt ID 1Dh/1Eh is set as Pending in the Interrupt Distributor after the event flag is set.

### 17E00630h - MPCore Timer1/Watchdog Reset Sent Register (R/ack)

```
+-----------------------------------------------------------------------------------+
|       0     Reset flag  (0=Normal, 1=Reset caused by Watchdog)  ;write 1 to clear |
|       1-31  Reserved                                                              |
+-----------------------------------------------------------------------------------+
```


### 17E00634h - W - MPCore Timer1/Watchdog Disable Register

```
+-----------------------------------------------------------------------------+
|       0-31  Key (write 12345678h, then write 87654321h to disable watchdog) |
+-----------------------------------------------------------------------------+
```

Switches the watchdog back to Timer mode (ie. clears bit3 in Control Register, and thereby re-enables writing to 17E00624h/17E00628h).

### Calculating timer intervals

```
+----------------------------------------------------------------------------------+
|      The timer interval is calculated using the following equation:              |
|        (PRESCALER_value+1)*(Reload_value+1)*2 / CPU_CLK_frequency                |
|      This equation can be used to calculate the period between two events out of |
|      the timers and the watchdog time-out time.                                  |
+----------------------------------------------------------------------------------+
```

Uh, doesn\'t that mean that reload occurs on UNDERFLOW (not on ZERO)\...?



