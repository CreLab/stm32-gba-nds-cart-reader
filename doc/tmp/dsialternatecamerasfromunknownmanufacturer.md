# DSi Alternate Cameras from Unknown Manufacturer


Device A0h/E0h appear to be cameras from an alternate manufacturer. DSi games are supporting these devices, but as by now, there aren\'t any DSi consoles known to be actually fitted with these cameras.
The camera type & manufacturer are still unknown. Below initialization data is containing some characterstic info that should allow to identify them. For example, register 03h appears to be bank-switching the other registers.

### unknown_cam_get_chip_id:
Reading an 8bit value from index 00h (in any bank?) seems to return some Chip ID, at least the DSi is reading that register before initialization (despite of reading it, the DSi does appear to ignore that value though).
Note: On a DSi with Aptina cameras, trying to read anything from I2C devices A0h/E0h does just return FFh-bytes.

### Formatting Note
Below tables consist of \"Index,Length,Data\[Length\]\" entries.

### unknown_cam_type_code_list_init:

```
+-------------------------------------------------------------------------------------+
|       003h, 1,001h               ;<-- bank maybe?                                   |
|       009h, 3,0E2h,002h,002h                                                        |
|       004h, 1,010h                                                                  |
|       004h, 1,0A0h                                                                  |
|       004h, 2,090h,04Ch                                                             |
|       00Dh, 1,0FFh                                                                  |
|       016h, 1,053h                                                                  |
|       018h, 3,002h,001h,00Fh                                                        |
|       020h, 1,000h                                                                  |
|       023h, 2,000h,000h                                                             |
|       034h, 8,000h,003h,000h,003h,001h,002h,000h,0C2h                               |
|       03Dh, 4,050h,050h,000h,067h                                                   |
|       042h, 1,01Ch                                                                  |
|       04Ah, 2,043h,0F8h                                                             |
|       04Eh, 7,028h,0FCh,000h,024h,014h,008h,008h                                    |
|       056h,13,000h,018h,028h,034h,044h,056h,06Eh,080h,0A4h,0C2h,0D6h,0E8h,0F4h      |
|       065h,12,00Fh,038h,008h,000h,01Fh,01Fh,01Fh,01Fh,01Fh,01Fh,01Fh,01Fh           |
|       07Ah,17,039h,03Bh,03Ah,036h,03Ch,03Ch,03Ah,03Ch,03Ch,03Ch,03Ah,03Ch,038h      |
|               03Ah,031h,03Ah,082h                                                   |
|       08Dh,22,08Ah,090h,096h,09Ch,0A4h,0AAh,0B0h,0B6h,0BCh,0C4h,0CAh,0D0h,0D6h      |
|               0DCh,0E4h,0EAh,0F0h,0F2h,0F4h,0F6h,0F8h,0FAh                          |
|       0A9h, 1,02Bh                                                                  |
|       0ABh, 3,02Eh,000h,050h                                                        |
|       0AFh, 1,070h                                                                  |
|       0B2h, 4,03Ch,068h,049h,070h                                                   |
|       0B7h,21,032h,000h,00Eh,0F8h,00Ch,07Ah,040h,000h,000h,010h,044h,064h,052h      |
|               012h,001h,0D7h,004h,002h,024h,002h,024h                               |
|       0D4h, 5,004h,004h,008h,00Ah,010h                                              |
|       016h, 1,0F7h                                                                  |
|       0DEh, 2,002h,024h                                                             |
|       016h, 1,053h                                                                  |
|       0E1h, 1,034h                                                                  |
|       0FFh, 1,00Fh                                                                  |
|       003h, 1,002h               ;<-- bank maybe?                                   |
|       005h, 2,06Dh,004h                                                             |
|       011h, 4,004h,048h,004h,048h                                                   |
|       016h, 2,00Ch,0D8h                                                             |
|       019h, 2,00Ch,0D8h                                                             |
|       01Eh, 6,002h,024h,070h,000h,001h,06Eh                                         |
|       026h, 7,008h,00Fh,00Fh,006h,0FFh,0FFh,003h                                    |
|       02Eh,19,07Eh,088h,074h,07Eh,008h,010h,080h,008h,084h,078h,001h,003h,00Ah      |
|               025h,060h,0B0h,006h,000h,000h                                         |
|       042h, 7,080h,010h,010h,010h,040h,080h,0FFh                                    |
|       04Ah,30,000h,000h,001h,0E5h,001h,0E0h,000h,070h,002h,0F0h,000h,02Eh,001h      |
|               0F3h,000h,005h,000h,000h,001h,000h,000h,0C0h,000h,026h,000h,01Ch      |
|               000h,0B3h,000h,086h                                                   |
|       069h,36,000h,000h,006h,014h,014h,01Fh,000h,000h,000h,000h,000h,01Fh,000h      |
|               000h,010h,010h,010h,01Fh,000h,000h,004h,004h,004h,01Fh,000h,000h      |
|               000h,000h,000h,01Fh,000h,000h,010h,010h,010h,01Fh                     |
|       095h, 1,084h                                                                  |
|       097h,18,002h,000h,0FFh,0FFh,000h,0FFh,0FFh,000h,000h,0FFh,0FFh,000h,0FFh      |
|               0FFh,000h,0F8h,014h,010h                                              |
|       0AAh,13,044h,098h,08Ch,09Ch,048h,08Ch,08Ah,09Ch,046h,02Ah,080h,008h,026h      |
|       0B8h, 8,02Ah,084h,000h,026h,02Ah,080h,008h,020h                               |
|       0C1h,10,038h,020h,01Fh,01Dh,034h,020h,01Fh,01Dh,045h,05Dh                     |
|       0CCh, 2,020h,020h                                                             |
|       0D0h, 3,080h,000h,0FFh                                                        |
|       003h, 1,000h               ;<-- bank maybe?                                   |
|       013h, 2,000h,04Ch                                                             |
|       01Dh, 2,000h,04Ch                                                             |
|       015h, 2,001h,05Fh                                                             |
|       055h, 2,001h,05Eh                                                             |
|       031h, 6,006h,068h,00Ch,005h,004h,047h                                         |
|       047h, 2,000h,003h                                                             |
|       04Ah, 3,0A0h,000h,003h                                                        |
|       04Fh, 2,000h,003h                                                             |
|       059h, 2,000h,001h                                                             |
|       05Fh, 2,000h,001h                                                             |
|       066h, 1,09Eh                                                                  |
|       06Eh, 2,07Fh,003h                                                             |
|       075h, 1,050h                                                                  |
|       07Ah, 2,000h,001h                                                             |
|       07Eh, 1,020h                                                                  |
|       082h, 1,038h                                                                  |
|       084h,14,003h,040h,003h,040h,000h,000h,040h,003h,0FFh,002h,008h,020h,018h,006h |
|       093h,11,020h,040h,040h,01Fh,002h,000h,000h,000h,000h,000h,000h                |
|       003h, 1,001h               ;<-- bank maybe?                                   |
|       00Fh, 1,0C9h                    ;or, for Device E0h: 00Fh, 1,0C8h             |
|       052h, 3,004h,008h,008h          ;or, for Device E0h: N/A                      |
|       003h, 1,002h               ;<-- bank maybe?                                   |
|       026h, 1,008h                    ;or, for Device E0h: 026h, 1,000h             |
|       0CCh, 2,0C0h,0C0h               ;or, for Device E0h: N/A                      |
|       0B4h, 1,000h                    ;or, for Device E0h: N/A                      |
|       0B6h, 1,026h                    ;or, for Device E0h: N/A                      |
|       0B9h, 3,000h,008h,026h          ;or, for Device E0h: N/A                      |
|       0BDh, 1,000h                    ;or, for Device E0h: N/A                      |
|       026h, 1,008h                    ;or, for Device E0h: N/A                      |
|       003h, 1,001h               ;<-- bank maybe?                                   |
|       02Dh, 1,0FFh                                                                  |
|       004h, 1,020h                                                                  |
+-------------------------------------------------------------------------------------+
```


### unknown_cam_type_code_list_activate:

```
+-----------------------------------------------------------------------+
|       003h, 1,002h               ;<-- bank maybe?                     |
|       0A7h, 1,014h                                                    |
|       003h, 1,001h               ;<-- bank maybe?                     |
|       004h, 1,0A0h                                                    |
|       004h, 1,090h                                                    |
|       02Dh, 1,000h                                                    |
|       004h, 1,098h                                                    |
+-----------------------------------------------------------------------+
```


### Random Note
This info is probably not really helpful, but the DSi firmware contains code for setting Register C1h..C9h (within unknown bank) to one of the following twelve settings.

```
+-----------------------------------------------------------------------+
|       C1h, 8,038h,030h,01Fh,01Fh,02Ch,030h,01Fh,01Fh                  |
|       C1h, 8,038h,030h,01Fh,01Fh,038h,030h,01Fh,01Fh                  |
|       C1h, 8,02Ch,030h,01Fh,01Fh,02Ch,030h,01Fh,01Fh                  |
|       C1h, 8,02Ch,030h,01Fh,01Fh,02Ch,030h,01Fh,01Fh                  |
|       C1h, 8,02Ch,030h,01Fh,01Fh,02Ch,030h,01Fh,01Fh                  |
|       C1h, 8,02Ch,030h,01Fh,01Fh,02Ch,030h,01Fh,01Fh                  |
|       C1h, 8,030h,028h,018h,018h,034h,028h,008h,018h                  |
|       C1h, 8,030h,028h,018h,018h,030h,028h,008h,018h                  |
|       C1h, 8,028h,028h,018h,018h,028h,028h,008h,018h                  |
|       C1h, 8,028h,028h,018h,018h,028h,028h,008h,018h                  |
|       C1h, 8,028h,028h,018h,018h,028h,028h,008h,018h                  |
|       C1h, 8,028h,028h,018h,018h,028h,028h,008h,018h                  |
+-----------------------------------------------------------------------+
```




