# DSi TSC\[20h..2Bh:xxh\], TSC\[40h..5Fh:xxh\] ADC/DAC Instruction RAM


### TSC\[20h..2Bh:xxh\] - ADC DSP Engine Instruction RAM (384 x 24bit)
ADC miniDSP Instructions are 20bit, each occupying 3 bytes (MSB,MID,LSB) (with dummy padding in upper 4bit of MSB).

```
+-----------------------------------------------------------------------+
|       TSC[20h..2Bh:00h]       Page Select                             |
|       TSC[20h..2Bh:01h]       Reserved                                |
|       TSC[20h:02h...61h]      ADC Instructions 0...31                 |
|       TSC[21h:02h...61h]      ADC Instructions 32...63                |
|       TSC[22h:02h...61h]      ADC Instructions 64...95                |
|       TSC[23h:02h...61h]      ADC Instructions 96...127               |
|       TSC[24h:02h...61h]      ADC Instructions 128...159              |
|       TSC[25h:02h...61h]      ADC Instructions 160...191              |
|       TSC[26h:02h...61h]      ADC Instructions 192...223              |
|       TSC[27h:02h...61h]      ADC Instructions 224...255              |
|       TSC[28h:02h...61h]      ADC Instructions 256...287              |
|       TSC[29h:02h...61h]      ADC Instructions 288...319              |
|       TSC[2Ah:02h...61h]      ADC Instructions 320...351              |
|       TSC[2Bh:02h...61h]      ADC Instructions 352...383              |
|       TSC[20h..2Bh:62h..7Fh]  Reserved                                |
+-----------------------------------------------------------------------+
```


### TSC\[40h..5Fh:xxh\] - DAC DSP Engine Instruction RAM (1024 x 24bit)
DAC miniDSP Instructions are 24bit (uh, unlike 20bit ADC ones?), each occupying 3 bytes (MSB,MID,LSB).

```
+-----------------------------------------------------------------------+
|       TSC[40h..5Fh:00h]       Page Select                             |
|       TSC[40h..5Fh:01h]       Reserved                                |
|       TSC[40h:02h...61h]      DAC Instructions 0...31                 |
|       TSC[41h:02h...61h]      DAC Instructions 32...63                |
|       TSC[42h:02h...61h]      DAC Instructions 64...95                |
|       TSC[43h:02h...61h]      DAC Instructions 96...127               |
|       TSC[44h:02h...61h]      DAC Instructions 128...159              |
|       TSC[45h:02h...61h]      DAC Instructions 160...191              |
|       TSC[46h:02h...61h]      DAC Instructions 192...223              |
|       TSC[47h:02h...61h]      DAC Instructions 224...255              |
|       TSC[48h:02h...61h]      DAC Instructions 256...287              |
|       TSC[49h:02h...61h]      DAC Instructions 288...319              |
|       TSC[4Ah:02h...61h]      DAC Instructions 320...351              |
|       TSC[4Bh:02h...61h]      DAC Instructions 352...383              |
|       TSC[4Ch:02h...61h]      DAC Instructions 384...415              |
|       TSC[4Dh:02h...61h]      DAC Instructions 416...447              |
|       TSC[4Eh:02h...61h]      DAC Instructions 448...479              |
|       TSC[4Fh:02h...61h]      DAC Instructions 480...511              |
|       TSC[50h:02h...61h]      DAC Instructions 512...543              |
|       TSC[51h:02h...61h]      DAC Instructions 544...575              |
|       TSC[52h:02h...61h]      DAC Instructions 576...607              |
|       TSC[53h:02h...61h]      DAC Instructions 608...639              |
|       TSC[54h:02h...61h]      DAC Instructions 640...671              |
|       TSC[55h:02h...61h]      DAC Instructions 672...703              |
|       TSC[56h:02h...61h]      DAC Instructions 704...735              |
|       TSC[57h:02h...61h]      DAC Instructions 736...767              |
|       TSC[58h:02h...61h]      DAC Instructions 768...799              |
|       TSC[59h:02h...61h]      DAC Instructions 800...831              |
|       TSC[5Ah:02h...61h]      DAC Instructions 832...863              |
|       TSC[5Bh:02h...61h]      DAC Instructions 864...895              |
|       TSC[5Ch:02h...61h]      DAC Instructions 896...927              |
|       TSC[5Dh:02h...61h]      DAC Instructions 928...959              |
|       TSC[5Eh:02h...61h]      DAC Instructions 960...991              |
|       TSC[5Fh:02h...61h]      DAC Instructions 992...1023             |
|       TSC[40h..5Fh:62h..7Fh]  Reserved                                |
+-----------------------------------------------------------------------+
```


Unknown if the Instruction RAM is implemented, the datasheets says that the RAM is R/W, but it seems to be always zero on DSi/3DS.
The miniDSP instruction set isn\'t officially documented anywhere. Texas Instruments has released a tool called AIC PurePath Studio, the tool supports graphical drag-and-drop prgrammaning, and it\'s said to be also supporting assembly code (perhaps also including opcode specs\... it isn\'t quite clear how to download that tool though).



