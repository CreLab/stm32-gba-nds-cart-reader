# DS Cartridge Unknown Commands


The Main Data transfer mode is normally using only two commands (B7h/B8h), however most cartridges do support one or more undocumented commands (as opposed to invalid commands, which will cause the cart to stop responding).

```
+----------------------------------------------------------------------------------+
|       Title                    Chip ID   Commands...                             |
|       Metroid First Hunt       00000FC2  B7 B8 D8                                |
|       Meine Tierarztpraxis     00000FAE  B7 B8 D8                                |
|       Meine Tierpension        00000FC2  B7 B8 D8                                |
|       Nanostray                00000FC2  B7 B8 D8                                |
|       Over the Hedge           00001FC2  B7 B8 D8                                |
|       Tony Hawk's Skateland    00003FC2  B7 B8                                   |
|       Tony Hawk's Downhill Jam 00003FC2  B7 B8                                   |
|       Ultimate Spiderman       00003FC2  B7 B8                                   |
|       System Flaw (DSi)        40001FC2  B7 B8 F1                                |
|       Biggest Loser (DSi)      40001FC2  B7 B8 F1                                |
|       Cooking Coach (DSi)      C0007FC2  58..5F 60..68 B7 B8                     |
|       Walk with Me             E0013F80  69..6C B5 B7 B8 D6                      |
|       Face Training (DSI NAND) E8007FEC  0x 5x 6x 8x 94 Bx D6 (see NAND chapter) |
+----------------------------------------------------------------------------------+
```

The presence of those commands was tested on DSi (where one can reset the cart by software to recover from invalid commands), with all parameter bits set to zero.
That testing is more difficult on NAND carts because the commands do only work when transferring the correct number of data bytes (0, 4, 200h, or 800h bytes), and only when being in the correct mode (ROM or RW mode; whereof, on DSi carts, the RW mode works ONLY in DSi mode).


```
+-------------------------------------------------------------------------------------+
|      ______________________________ Command 58h..68h ______________________________ |
+-------------------------------------------------------------------------------------+
```


### 5800000000000000h-5F00000000000000h (..) - Get HighZ
Unknown purpose, returns HighZ.

### 6000000000000000h-6800000000000000h (..) - Get Zeroes
Unknown purpose, returns at least 4000h encrypted 00h bytes.


```
+-------------------------------------------------------------------------------------+
|      ______________________________ Command 69h..6Ch ______________________________ |
+-------------------------------------------------------------------------------------+
```


### 6900000000000000h-6C00000000000000h (..) - Get Zeroes
Unknown purpose, returns at least 4000h encrypted 00h bytes.


```
+-------------------------------------------------------------------------------------+
|      ______________________________ Command B5h/D6h _______________________________ |
+-------------------------------------------------------------------------------------+
```


### B500000000000000h (0) - Start/Stop/Reset/Ack something?
Unknown. Returns only HighZ.

### D600000000000000h (4) - Get Status Byte (also used on NAND carts)
Returns a status byte (repeated in first four bytes, then followed by HighZ bytes).

Command B5h/D6h are supported in carts that have bit5 set in 4th byte of Chip ID (eg. in Walk with Me). Command D6h (and maybe also B5h) works both on power up (before secure area), and in main data phase (after secure area). The DSi Launcher contains following code to deal with such carts:

```
+----------------------------------------------------------------------------+
|      if chip_id AND 20000000h                                              |
|        get_nand_status(cmd_D6h)                                            |
|        if (nand_status AND 0Ch)<>0                    ;whatever bits       |
|          whatever(cmd_B5h)                            ;whatever command    |
|         loop:                                                              |
|          get_nand_status(cmd_D6h)                                          |
|          if (nand_status AND 20h)=0 then goto loop    ;wait for ready flag |
+----------------------------------------------------------------------------+
```



```
+-------------------------------------------------------------------------------------+
|      ________________________________ Command D8h _________________________________ |
+-------------------------------------------------------------------------------------+
```


### D800000000000000h (..) - Get Zeroes
Unknown purpose, returns at least 4000h encrypted 00h bytes.


```
+-------------------------------------------------------------------------------------+
|      ________________________________ Command F1h _________________________________ |
+-------------------------------------------------------------------------------------+
```


### F100000000000000h (1000h) - Get Serial/Manufacturer Info or so
Returns 1000h bytes of data (repeated each 1000h bytes), the data is mostly FFh-filled, with some kind of Serial Number or Manufacturer Info at offset E00h. Unknown what those values are good for, and if they contain unique IDs.
This command works in main data phase only (returns only FFh/HighZ on power up before secure area loading).
System Flaw cmd F1 response:

```
+-----------------------------------------------------------------------+
|       0000..0DFF  FF-filled                                           |
|       0E00        1E 40 05 5A FF FF 0D 01  32 68 38 7A 23 3F FF FF    |
|       0E10        03 0B 00 00 03 09 FF FF  FF FF FF FF FF FF FF FF    |
|       0E20        1E 40 05 03 0B 00 00 03  09 00 00 FF FF FF FF FF    |
|       0E30        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E40        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E50        FF FF FF FF FF 5A FF 5E  FF FF FF FF FF FF 5A FF    |
|       0E60        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E70        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E80..0FFF  FF-filled                                           |
|       1000..3FFF  mirrors of 0000-0FFF                                |
+-----------------------------------------------------------------------+
```

Biggest Loser cmd F1 response:

```
+-----------------------------------------------------------------------+
|       0000..0DFF  FF-filled                                           |
|       0E00        11 16 08 5A FF FF 0D 0B  39 7C 40 8E 2A 53 FF FF    |
|       0E10        03 0A 07 05 05 04 00 00  07 00 7F FF 00 FF FF FF    |
|       0E20        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E30        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E40        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E50        FF FF FF FF FF 5A FF 5E  FF FF FF FF FF FF 5A FF    |
|       0E60        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E70        FF FF FF FF FF FF FF FF  FF FF FF FF FF FF FF FF    |
|       0E80..0FFF  FF-filled                                           |
|       1000..3FFF  mirrors of 0000-0FFF                                |
+-----------------------------------------------------------------------+
```




