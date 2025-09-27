# DSi SD/MMC I/O Ports: Unknown/Unused Registers


Below registers don\'t seem to be used by existing software\...

### 40048F2h/4004AF2h - Can be 0003h

```
+-------------------------------------------------------------------------------------+
|       15-2   Always zero                                                            |
|       1-0    Unknown (0..3)                                                   (R/W) |
+-------------------------------------------------------------------------------------+
```


### 40048F4h/4004AF4h - Can be 0770h

```
+-------------------------------------------------------------------------------------+
|       15-11  Always zero                                                            |
|       10-8   Unknown (0..7)                                                   (R/W) |
|       7      Always zero                                                            |
|       6-4    Unknown (0..7)                                                   (R/W) |
|       3-0    Always zero                                                            |
+-------------------------------------------------------------------------------------+
```


### Unused Registers with Fixed value (all bits read-only, or write-only)

```
+-------------------------------------------------------------------------------------+
|       400482Ah/4004A2Ah 2    Fixed always zero?                                     |
|       4004832h/4004A32h 2    Fixed always zero?   ;(TC6371AF:BUF1 Data MSBs?)       |
|       400483Ah/4004A3Ah 2    Fixed always zero?   ;(SDCTL_SDIO_HOST_INFORMATION)    |
|       400483Ch/4004A3Ch 2    Fixed always zero?   ;(SDCTL_ERROR_CONTROL)            |
|       400483Eh/4004A3Eh 2    Fixed always zero?   ;(TC6387XB: LED_CONTROL)          |
|       4004840h/4004A40h 2    Fixed always 003Fh?                                    |
|       4004842h/4004A42h 2    Fixed always 002Ah?                                    |
|       4004844h/4004A44h 6Eh  Fixed always zerofilled?                               |
|       40048B2h/4004AB2h 2    Fixed always FFFFh?                                    |
|       40048B4h/4004AB4h 6    Fixed always zerofilled?                               |
|       40048BAh/4004ABAh 2    Fixed always 0200h?                                    |
|       40048BCh/4004ABCh 1Ch  Fixed always zerofilled?                               |
|       40048DAh/4004ADAh 6    Fixed always zerofilled?                               |
|       40048E2h/4004AE2h 2    Fixed always 0009h?  ;(RESERVED2/9, TC6371AF:CORE_REV) |
|       40048E4h/4004AE4h 2    Fixed always zero?                                     |
|       40048E6h/4004AE6h 2    Fixed always zero?   ;(RESERVED3, TC6371AF:BUF_ADR)    |
|       40048E8h/4004AE8h 2    Fixed always zero?   ;(TC6371AF:Resp_Header)           |
|       40048EAh/4004AEAh 6    Fixed always zerofilled?                               |
|       40048F0h/4004AF0h 2    Fixed always zero?   ;(RESERVED10)                     |
|       4004902h/4004B02h 2    Fixed always zero?                                     |
|       4004906h/4004B06h 2    Fixed always zero?                                     |
|       400490Ah/4004B0Ah 2    Fixed always zero?                                     |
|       4004910h/4004B10h F0h  Fixed always zerofilled?                               |
+-------------------------------------------------------------------------------------+
```




