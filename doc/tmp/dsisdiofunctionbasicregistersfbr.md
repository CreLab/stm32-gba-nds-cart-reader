# DSi SDIO Function Basic Registers (FBR)


### 0:00n00h - FBR(n): Interface Type

```
+-------------------------------------------------------------------------------------+
|       0-3   Standard SDIO Function Interface Code                             (R)   |
|       4-5   Reserved for Future                                               (-)   |
|       6     Code Storage Area (CSA) Supported                   (0=No, 1=Yes) (R)   |
|       7     Code Storage Area (CSA) Enable   (0=Block reads/writes, 1=Enable) (R/W) |
|       8-15  Extended standard SDIO Function interface code  (when bit0-3=0Fh) (R)   |
+-------------------------------------------------------------------------------------+
```

The interface type is merged of bit0-3 and bit8-15:

```
+---------------------------------------------------------------------------------+
|       0h:00h = No SDIO standard interface (eg. Atheros Wifi in DSi)             |
|       1h:00h = SDIO Standard UART                                               |
|       2h:00h = SDIO Bluetooth Type-A standard interface                         |
|       3h:00h = SDIO Bluetooth Type-B standard interface                         |
|       4h:00h = SDIO GPS standard interface                                      |
|       5h:00h = SDIO Camera standard interface                                   |
|       6h:00h = SDIO PHS standard interface                                      |
|       7h:00h = SDIO WLAN interface                                              |
|       8h:00h = Embedded SDIO-ATA standard interface                             |
|       9h:00h = SDIO Bluetooth Type-A Alternate MAC PHY (AMP) standard interface |
|       Ah:00h = Reserved for Future                                              |
|       Bh:00h = Reserved for Future                                              |
|       Ch:00h = Reserved for Future                                              |
|       Dh:00h = Reserved for Future                                              |
|       Eh:00h = Reserved for Future                                              |
|       Fh:00h..FFh = Reserved for Future                                         |
+---------------------------------------------------------------------------------+
```


### 0:00n02h - FBR(n): Power

```
+-------------------------------------------------------------------------------------+
|       0     Support Power Selection                             (0=No, 1=Yes) (R)   |
|       1     Enable Power Selection        (0=Normal Current, 1=Lower Current) (R/W) |
|       2-3   Reserved for Future                                               (-)   |
|       4-7   Power State                                                       (R/W) |
+-------------------------------------------------------------------------------------+
```


### 0:00n09h-00n0Bh - FBR(n): Pointer to Card Information Structure (CIS)

```
+-----------------------------------------------------------------------------------+
|       0-16  Pointer to Function(n)'s Card Information Structure (Function CIS)(R) |
|       17-23 Unspecified (probably reserved)                                   (-) |
+-----------------------------------------------------------------------------------+
```

Should point to \"End-of-Chain Tuple\" for unsupported functions?

### 0:00n0Ch-00n0Eh - FBR(n): Code Storage Area (CSA) Address (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-23  Pointer to CSA memory (incremented after CSA data read/write)     (R/W) |
+-------------------------------------------------------------------------------------+
```


### 0:00n0Fh - FBR(n): Code Storage Area (CSA) Data \"Window\" (R or R/W)

```
+-------------------------------------------------------------------------------------+
|       0-7   Data (to/from auto-incrementing CSA Address) (R for ROM, R/W otherwise) |
+-------------------------------------------------------------------------------------+
```


### 0:00n10h-00n11h - FBR(n): CMD53 Block Size (R/W)

```
+-------------------------------------------------------------------------------------+
|       0-15  CMD53 Block size for Function(n)          (0001h..0800h) (0=None) (R/W) |
+-------------------------------------------------------------------------------------+
```




