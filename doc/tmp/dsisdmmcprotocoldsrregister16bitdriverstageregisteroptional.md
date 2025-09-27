# DSi SD/MMC Protocol: DSR Register (16bit Driver Stage Register) (Optional)


### CMD4 - SD/MMC - SET_DSR (type=bc)
Parameter bits:

```
+-----------------------------------------------------------------------+
|       31-16 DSR                                                       |
|       15-0  stuff bits                                                |
+-----------------------------------------------------------------------+
```

Response: N/A
Programs the DSR of all cards.

### DSR register (Optional)
The 16-bit driver stage register is described in detail in Chapter 0 (uh, where?). It can be optionally used to improve the bus performance for extended operating conditions (depending on parameters like bus length, transfer rate or number of cards). The CSD register carries the information about the DSR register usage. The default value of the DSR register is 0404h.



