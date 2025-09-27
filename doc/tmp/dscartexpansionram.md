# DS Cart Expansion RAM


### DS Memory Expansions
There are several RAM expansions for the NDS. The RAM cartridge connects to the GBA slot; can can be then accessed from cartridges in the DS slot.

```
+--------------------------------------------------------------------------+
|       Opera         (8MB RAM) (official RAM expansion for Opera browser) |
|       EZ3/4/3-in-1  (8-16MB RAM, plus FLASH, plus rumble)                |
|       Supercard     (32MB)                                               |
|       M3            (32MB)                                               |
|       G6            (32MB)                                               |
+--------------------------------------------------------------------------+
```

The recommended access time (waitstates) for all memory types is unknown. Unknown which programs do use these expansions for which purposes (aside from the Opera browser).
Thanks to Rick \"Lick\" Wong for info on detection and unlocking.

### Opera / DS Memory Expansion Pak (NTR-011 or USG-007)

```
+-----------------------------------------------------------------------+
|       base=9000000h, size=800000h (8MB)                               |
|       unlock=1, lock=0                                                |
|       STRH [8240000h],lock/unlock                                     |
+-----------------------------------------------------------------------+
```


### EZ

```
+-----------------------------------------------------------------------+
|       base=8400000h, size=VAR (8MB..16MB)                             |
|       locking/unlocking/detection see below                           |
+-----------------------------------------------------------------------+
```


### Supercard

```
+-----------------------------------------------------------------------+
|       base=8000000h, size=1FFFFFEh (32MB minus last two bytes?)       |
|       unlock=5 (RAM_RW), lock=3 (MEDIA)                               |
|       STRH [9FFFFFEh],A55Ah                                           |
|       STRH [9FFFFFEh],A55Ah                                           |
|       STRH [9FFFFFEh],lock/unlock                                     |
|       STRH [9FFFFFEh],lock/unlock                                     |
+-----------------------------------------------------------------------+
```


### M3

```
+-----------------------------------------------------------------------+
|       base=8000000h, size=2000000h (32MB)                             |
|       unlock=00400006h, lock=00400003h                                |
|       LDRH Rd,[8E00002h]                                              |
|       LDRH Rd,[800000Eh]                                              |
|       LDRH Rd,[8801FFCh]                                              |
|       LDRH Rd,[800104Ah]                                              |
|       LDRH Rd,[8800612h]                                              |
|       LDRH Rd,[8000000h]                                              |
|       LDRH Rd,[8801B66h]                                              |
|       LDRH Rd,[8000000h+(lock/unlock)*2]                              |
|       LDRH Rd,[800080Eh]                                              |
|       LDRH Rd,[8000000h]                                              |
|       LDRH Rd,[80001E4h]                                              |
|       LDRH Rd,[80001E4h]                                              |
|       LDRH Rd,[8000188h]                                              |
|       LDRH Rd,[8000188h]                                              |
+-----------------------------------------------------------------------+
```


### G6

```
+-----------------------------------------------------------------------+
|       base=8000000h, size=2000000h (32MB)                             |
|       unlock=6, lock=3                                                |
|       LDRH Rd,[9000000h]                                              |
|       LDRH Rd,[9FFFFE0h]                                              |
|       LDRH Rd,[9FFFFECh]                                              |
|       LDRH Rd,[9FFFFECh]                                              |
|       LDRH Rd,[9FFFFECh]                                              |
|       LDRH Rd,[9FFFFFCh]                                              |
|       LDRH Rd,[9FFFFFCh]                                              |
|       LDRH Rd,[9FFFFFCh]                                              |
|       LDRH Rd,[9FFFF4Ah]                                              |
|       LDRH Rd,[9FFFF4Ah]                                              |
|       LDRH Rd,[9FFFF4Ah]                                              |
|       LDRH Rd,[9200000h+(lock/unlock)*2]                              |
|       LDRH Rd,[9FFFFF0h]                                              |
|       LDRH Rd,[9FFFFE8h]                                              |
+-----------------------------------------------------------------------+
```


### Detection
For EZ, detection works as so:

```
+-----------------------------------------------------------------------+
|      ez_ram_test:   ;Based on DSLinux Amadeus' detection              |
|       ez_subfunc(9880000h,8000h) ;-SetRompage (OS mode)               |
|       ez_subfunc(9C40000h,1500h) ;-OpenNorWrite                       |
|       [08400000h]=1234h          ;\                                   
|       if [08400000h]=1234h       ; test writability at 8400000h       |
|         [8000000h]=4321h         ; and non-writability at 8000000h    |
|         if [8000000h]<>4321h     ;                                    |
|           return true            ;/                                   |
|       ez_subfunc(9C40000h,D200h) ;CloseNorWrite                       |
|       ez_subfunc(9880000h,0160h) ;SetRompage (0160h)                  |
|       ez_subfunc(9C40000h,1500h) ;OpenNorWrite                        |
|       [8400000h]=1234h           ;\                                   
|       if [8400000h]=1234h        ; test writability at 8400000h       |
|         return true              ;/                                   |
|       return false               ;-failed                             |
|      ez_subfunc(addr,data):                                           |
|       STRH [9FE0000h],D200h                                           |
|       STRH [8000000h],1500h                                           |
|       STRH [8020000h],D200h                                           |
|       STRH [8040000h],1500h                                           |
|       STRH [addr],data                                                |
|       STRH [9FC0000h],1500h                                           |
+-----------------------------------------------------------------------+
```

For all other types (everything except EZ), simply verify that you can write (when unlocked), and that you can\'t (when locked).



