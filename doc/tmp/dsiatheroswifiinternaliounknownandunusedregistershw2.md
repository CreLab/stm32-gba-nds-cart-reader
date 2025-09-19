# DSi Atheros Wifi - Internal I/O - Unknown and Unused Registers (hw2)


### hw4.0 would have the following extra registers

```
+----------------------------------------------------------------------------------+
|       00D000h - DBG_UART Registers   ;\don't exist in hw2.0 ?                    
|       00E000h - UMBOX Registers      ;/                                          |
|       020000h - WMAC DMA and IRQ     ;\                                          
|       020800h - WMAC QCU Queue       ; these MIGHT EXIST in hw2.0, too ?         |
|       021000h - WMAC DCU             ; (not defined in hw2.0 source code though) |
|       029800h - BB/LC Registers      ;/                                          |
|       030100h - RDMA Registers       ;\don't exist in hw2.0 ?                    
|       031000h - EFUSE Registers      ;/                                          |
+----------------------------------------------------------------------------------+
```


### some partial hw2.0 memory dump\...

```
+------------------------------------------------------------------------------------+
|       000000 Deadc0de                                                              |
|       004000 sth (01 00 00 00, 00 00 00 00)                        ;"RTC"          |
|       005000 Deadc0de                                                              |
|       008000 sth (00 00 00 00, 00 00 00 00)                        ;"VMC?"         |
|       009000 Deadc0de           ;should contain UART etc. (maybe disabled?)        |
|       014000 sth (00 00 00 00, 00 00 00 00) (--crash-- at 0140cx)  ;"GPIO?"        |
|       015000 Deadc0de                                                              |
|       018000 sth (00 01 0E 00, 00 01 0E 00)                        ;\MBOX          
|       019000 sth (00 01 0E 00, 00 01 0E 00)                        ;/              |
|       01A000 sth (00 01 0E 00, 00 01 0E 00)                        ;\MBOX:HOST_IF? 
|       01B000 sth (--crash-- at 01B00x)                             ;/              |
|       01C000 sth (00 00 14 00, D8 48 45 0E)                        ;-ANALOG?       |
|       01D000 Deadc0de                                                              |
|       020000 sth (00's)                                            ;\DMA?          
|       021000 sth (01 00 00 00, 02 00 00 00)                        ;/              |
|       022000 sth (00's)                                            ;\   ;\same as  
|       023000 sth (01 00 00 00, 02 00 00 00)                        ;    ;/DMA?     |
|       024000 sth (00's)                                            ; ??            |
|       025000 sth (00's)                                            ;               |
|       026000 sth (00's)                                            ;               |
|       027000 sth (00's)                                            ;/              |
|       028000 sth (<--- mac addr ---> 86 38)            ;\MAC_PCU?     mac_pcu.h ?  
|       029000 sth (14 E1 38 8A, 80 73 00 00)            ;/          ;\              
|       02A000 sth (00's)                                            ; BB at 29800h? |
|       02B000 sth (00's)                                            ;/              |
|       02C000 sth (00's)                                            ;-              |
|       02D000 sth (00's)                                            ;-              |
|       02E000 sth (00's)                                            ;-              |
|       02F000 sth (00's)                                            ;-              |
|       030000 Deadc0de              ;RDMA?? and (not?) EFUSE??                      |
|       040000 Deadbeef        ;\                                                    
|       050000 Deadbeef        ;                                                     |
|       060000 Deadbeef        ;                                                     |
|       070000 Deadbeef        ;/                                                    |
|       080000 004F1B74        ;\                                                    
|       090000 004F1B74        ;                                                     |
|       0A0000 004F1B74        ; mirror of ROM word at [0F3FF8] (second-last-word)   |
|       0B0000 004F1B74        ;                                                     |
|       0C0000 004F1B74        ;                                                     |
|       0D0000 004F1B74        ;/                                                    |
|       0E0000 sth (06 10 00 00, 21 22 22 22)   ;\80K ROM (14000h bytes)             
|       0F0000 sth (00 00 05 60, FF DF FF FF)   ;/                                   |
|       0F4000 004F1B74        ;-mirror of ROM word at [0F3FF8] (second-last-word)   |
|       100000 sth (48 0F 8E 00, 70 14 50 00)   ;\                                   
|       110000 sth                              ; 184K RAM (2E000h bytes)            |
|       120000 sth                              ;/                                   |
|       12E000 98A8A2AA        ;\                                                    
|       ...                    ;                                                     |
|       1FF000 98A8A2AA        ;/                                                    |
|       200000 Deadbeef        ;\                                                    
|       300000 Deadbeef        ;/                                                    |
|       00400000 looks like mirror of 000000                                         |
|       0041B000 looks like mirror of 01B000 --crash--                               |
|       ...      probably more mirrors...                                            |
|       FFC00000 looks like mirror of 000000                                         |
|       FFC1B000 looks like mirror of 01B000 --crash--                               |
|       ...      probably more mirrors till FFFFFFFF                                 |
+------------------------------------------------------------------------------------+
```


### some partial hw4.0 memory dump\...

```
+---------------------------------------------------------------------------+
|       000000 zerofilled                                                   |
|       004000 sth (01 00 00 00, 00 00 00 00)                        ;"RTC" |
|       005000 zerofilled                                                   |
|       040000 Deadbeef                                                     |
|       080000 zerofilled                                                   |
|       0E0000 06 10 00 00 21 22 22 22 00 00 00 E0 83 00 8E 00 ...   ;ROM?  |
|       109DC0 zerofilled                                            ;ROM?  |
|       10C000 14 19 52 00 ...                                       ;ROM?  |
|       114000 zerofilled                                            ;ROM?  |
|       120000 A0 B2 52 00     ;=52B2A0h (app_defined_area)   ;RAM          |
|       140000 zerofilled                                                   |
|       200000 Deadbeef                                                     |
|       400000..FFFFFFFF not checked (probably mirrors of above?)           |
+---------------------------------------------------------------------------+
```




