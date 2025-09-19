# DSi Teak MMIO\[8140h\] - Code Replacement Unit (CRU)


The CRU is intended to fix bugs in ROM-based programs (rather useless
for RAM-based DSi code).

- **MMIO\[8140h+(0..15)\*4\] - CRU Entry 0..15 Offset, bit0-15 (R/W)**
- **MMIO\[8142h+(0..15)\*4\] - CRU Entry 0..15 Offset, bit16-31 (R/W)**

```
+-----------------------------------------------------------------------+
|       0-17   P                                                        |
| rogram Address                           (0..3FFFFh)            (R/W) |
|       18-21  P                                                        |
| rogram Page (usually 0)                  (0..Fh)                (R/W) |
|       22-30  Unused (0) (except bit25-30 in entry 15)                 |
|       25-28                                                           |
|  Entry 15: Match entry number              (0..15=Entry 0..15)    (R) |
|       29                                                              |
|  Entry 15: Match flag (cleared after read) (0=None, 1=Yes/match)  (R) |
|       30     E                                                        |
| ntry 15: Master enable for all entries   (0=Disable, 1=Enable)  (R/W) |
|       31     E                                                        |
| nable Entry                              (0=Disable, 1=Enable)  (R/W) |
+-----------------------------------------------------------------------+
```

There are sixteen identical entries, resembling OCEM program breaks,
with some extra control/status bits in last entry.
The feature is working in so far that the read-only status bits get set
upon matches, but the match should reportedly insert \"a branc
instruction\" or trigger a \"trap\" exception, which doesn\'t happen.
Unknown if there are further config/mode/enable bits elsewhere for
activating that behaviour. To bypass ROM code, it might redirect to data
RAM, or external AHBM memory?



