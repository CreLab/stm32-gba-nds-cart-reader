# DSi Touchscreen Access


The Touch Screen Controller (for lower LCD screen) is accessed via SPI bus,
- [DS Serial Peripheral Interface Bus (SPI)](./dsserialperipheralinterfacebusspi.md)
so far, it\'s same as on NDS, but the SPI touchscreen commands are having an entirely different format in DSi mode:
The DSi touchscreen registers are selected via a combination of a PAGE byte and an INDEX byte. The PAGE byte is located at INDEX=00h, and it does somewhat \'bankswitch\' the contents of INDEX=01h..7Fh. And INDEX can be incremented manually, or automatically (but, confusingly, the manual increment doesn\'t work for reading Y coordinates).
SPI clock should be set to 4MHz for DSi Mode touchscreen access (unlike NDS, which used 2MHz). The PENIRQ bit in port 4000136h is always zero in DSi mode.
When reading data: Write dummy 00h-bytes in output direction.

AIC3000D

### DSi Touchscreen PAGE:INDEX values
The INDEX/Direction byte is written as first byte after SPI chip select:

```
+-------------------------------------------------------------------------+
|       0     Direction for following data bytes (0=Write, 1=Read)        |
|       1-7   INDEX (00h..7Fh) for following data bytes (auto-increasing) |
+-------------------------------------------------------------------------+
```

However, the chip has more than 128 registers, stored in multiple pages.

```
+-----------------------------------------------------------------------+
|       TSC[00h]=PAGE         ;<-- change page (at INDEX=0)             |
|       TSC[PAGE:INDEX]       ;<-- access registers in select page      |
+-----------------------------------------------------------------------+
```


### Pen Down Testing

```
+----------------------------------------------------------------------------------+
|       if (TSC[3:09h] AND 40h)<>0 then return(not_pressed)   ;ADC Ready Flag      |
|       if (TSC[3:0Eh] AND 03h)<>0 then return(not_pressed)   ;Undocumented Flags? |
|       return(pressed)                                                            |
+----------------------------------------------------------------------------------+
```

Note: On NDS, this would be done by reading port 4000136h.bit6, which isn\'t supported in DSi mode.

### X/Y Coordinate Reading

```
+-----------------------------------------------------------------------------+
|       touchdata[0..19] = TSC[FCh:01h..14h]     ;read page FCh, index(1..20) |
|       rawx=0, rawy=0                                                        |
|       for i=0 to 8 step 2                                                   |
|         x = touchdata[i+0]*100h+touchdata[i+1]                              |
|         y = touchdata[i+10]*100h+touchdata[i+11]                            |
|         if (x or y) and F000h then return(not_pressed)                      |
|         rawx=rawx+x, rawy=rawy+y                                            |
|       return(rawx/5, rawy/5)                                                |
+-----------------------------------------------------------------------------+
```

The resulting 12bit coordinates are same as on NDS (ie. they need to be further processed using the Calibration Points from User Settings).
Reading TSC\[FCh:01h..14h\] must be done in a single SPI transfer (reading them separatedly as TSC\[FCh:01h\], TSC\[FCh:02h\], etc. doesn\'t work).

### Touchscreen X/Y Coordinates

```
+---------------------------------------------------------------------------------+
|       0-11   Coordinate (0..FFFh) (usually 000h when not pressed)               |
|       12-14  State (0=Pressed, 7=Released) (or sometimes also 1 or 3=Released)  |
|       15     State Changed (0=No, 1=Newly pressed/released; cleared after read) |
+---------------------------------------------------------------------------------+
```

Bit12-14 are usually set to 7 when releasing the screen (though sometimes they become 1 or 3 when releasing the screen, and do stay so until newly pressing it).
Bit15 is cleared after reading (so it will be usually seen only in the first MSB, ie. at INDEX=01h) (though maybe it can also occur elsewhere if it becomes newly set during the SPI transfer).

### Microphone
The microphone input was part of the TSC on NDS. In DSi mode it is reportedly somehow changed, using a new \"CODEC\" (aka the DSi\'s newer TSC touchscreen/sound controller).

### NDS Backwards Compatibility Mode
The DSi hardware can emulate the NDS-style touchscreen protocol (with X/Y/MIC channels and with additional PENIRQ flag; but without Pressure or Temperature channels).
- [DS Touch Screen Controller (TSC)](./dstouchscreencontrollertsc.md)
DSi enhanced games should implement both modes, and use the new mode on DSi consoles, and the old mode on NDS consoles (alternately, CartHdr\[1BFh\].bit0=0 will activate the old mode for both NDS+DSi).
If the backwards compatibility mode isn\'t enabled, then trying to read the touchscreen in NDS fashion will return nothing but zeroes for all TSC channels (and also zero for the PENIRQ bit).



