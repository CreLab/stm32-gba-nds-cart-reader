# DS Cart Infrared P-Walker Ports LCD Controller


### LCD Command Table
Commands are 1 or 2 bytes long (with D/C=Low, and, unlike normal SPI, one can release /CS after each byte, even when sending 2-byte commands).

```
+-------------------------------------------------------------------------------------+
|       1st Byte     2nd Byte  Description                                            |
|       00h+(0..Fh)  -       Set Column Address bit0-3   ;\VRAM xloc in 1-pixel units 
|       10h+(0..7)   -       Set Column Address bit4-6   ;/                           |
|       18h+(0..7)   -       Reserved                                                 |
|       20h+(0..7)   -       Set Internal Regulator Resistor Ratio                    |
|                              (0..7 = 2.3, 3.0, 3.7, 4.4, 5.1, 5.8, 6.5, 7.2)        |
|       28h+(0..7)   -       Set Power Control Register                               |
|                              bit2: Internal Voltage Booster (0=Off, 1=On)           |
|                              bit1: Internal Regulator       (0=Off, 1=On)           |
|                              bit0: Output Op-amp Buffer     (0=Off, 1=On)           |
|       30h+(0..0Fh) -       Reserved                                                 |
|       40h          00h-xxh Set Display Start Line (0..127?) (ROW) ("scroll yloc")   |
|       41h+(0..2)   00h-xxh Same as above?                                           |
|       44h          00h-xxh Set Display Offset (0..63) (COM0=ROW0..63) (pinout?)     |
|       45h+(0..2)   00h-xxh Same as above?                                           |
|       48h          00h-xxh Set Multiplex Ratio (num lines, duty 1/((16..64)+icon))  |
|       49h+(0..2)   00h-xxh Same as above?                                           |
|       4Ch          00h-3Fh Set N-line Inversion (0=Off, 1..31=Reduce crosstalk?)    |
|       4Ch          20h-FFh Same as above?                                           |
|       4Dh+(0..2)   00h-FFh Same as above?                                           |
|       50h+(0..7)   -       Set LCD Bias (0..5=1/(4..9), 6=1/9, too)                 |
|       57h+(0..0Ch) -       Reserved                                                 |
|       64h+(0..3)   -       Set DC-DC Converter Factor (0=2x/3x, 1=4x, 2/3=5x)       |
|       68h+(0..18h) -       Reserved                                                 |
|       81h          00h-3Fh Set Contrast (0..3Fh, 3Fh=Darkest)                       |
|       82h          OTP     Set VL6 voltage (00h..0Fh = original+Signed4bit(N))      |
|       83h          OTP     OTP Programming?                                         |
|       84h+(0..7)   -       Reserved                                                 |
|       88h          00h-FFh Set White Mode      (bit0-3=FrameA, bit4-7=FrameB)       |
|       89h          00h-FFh Set White Mode      (bit0-3=FrameC, bit4-7=FrameD)       |
|       8Ah          00h-FFh Set Light Gray Mode (bit0-3=FrameA, bit4-7=FrameB)       |
|       8Bh          00h-FFh Set Light Gray Mode (bit0-3=FrameC, bit4-7=FrameD)       |
|       8Ch          00h-FFh Set Dark Gray Mode  (bit0-3=FrameA, bit4-7=FrameB)       |
|       8Dh          00h-FFh Set Dark Gray Mode  (bit0-3=FrameC, bit4-7=FrameD)       |
|       8Eh          00h-FFh Set Black Mode      (bit0-3=FrameA, bit4-7=FrameB)       |
|       8Fh          00h-FFh Set Black Mode      (bit0-3=FrameC, bit4-7=FrameD)       |
|                              Above defines the grayscale palette for color 0-3,     |
|                              normally all frames should use the same setting.       |
|                              Color 0 is usually white (set to zero), color 3 is     |
|                              usually black (set to number of levels selected via    |
|                              cmd 90h). Color 1 and 2 are usually light/dark gray,   |
|                              set to desired contrast, which may depend on the LCD.  |
|       90h+(0..7)   -       Set PWM and FRC for gray-scale operation                 |
|                              bit0-1: Levels (0/1=Nine, 2=Twelve, 3=Fifteen Levels)  |
|                              bit2:   Frames (0=Four, 1=Three Frames)                |
|                              Note: Nintendo uses "9 levels" ranging from "0 to 9"   |
|                              (maybe level 0 is treated as off, thus not counted)    |
|       98h+(0..7)   -       Reserved                                                 |
|       A0h+(0..1)   -       Set Segment Remap (0=Col00h is SEG0, 1=Col7Fh is SEG0)   |
|                              Aka xflip mirror?                                      |
|       A2h+(0..1)   -       Set Icon Enable (0=Disable, 1=Enable)                    |
|       A4h+(0..1)   -       Set Entire Display On/Off (0=Show RAM, 1=All Pixels On)  |
|       A6h+(0..1)   -       Set Inverse Display (0=Normal, 1=Inverse On/Off Pixels)  |
|       A8h+(0..1)   -       Set Power Save Mode (0=Standby, 1=Sleep)                 |
|       AAh          -       Reserved                                                 |
|       ABh          -       Start Internal Oscillator (needed after reset)           |
|       ACh+(0..1)   ?       Reserved                                                 |
|       AEh+(0..1)   -       Set Display On/Off (0=Off, 1=On)                         |
|       B0h+(0..0Fh) -       Set Page Address (00h..0Fh)  ;VRAM yloc in 8-pixel units |
|       C0h+(0,8)    -       Set COM Output Scan Direction (0=Normal, 8=Remapped)     |
|                              Remapped: COM[0..(N-1)] becomes COM[(N-1)..0])         |
|                              Aka yflip mirror?                                      |
|       C1h+(0..6)   -       Same as above (Normal)                                   |
|       C9h+(0..6)   -       Same as above (Remapped)                                 |
|       D0h+(0..10h) -       Reserved                                                 |
|       E1h          -       Exit Power-save Mode (return from Sleep/Standby modes)   |
|       E2h          -       Software Reset (initialize some internal registers)      |
|       E3h          -       Reserved                                                 |
|       E4h          -       Exit N-line Inversion mode                               |
|       E5h+(0..2)   -       Reserved                                                 |
|       E8h          LEN+DTA Transfer VRAM Display Data (for 3-wire SPI mode only)    |
|                              (LEN=00h-FFh, followed by LEN+1 data bytes)            |
|       E9h+(0..6)   -       Reserved                                                 |
|       F0h+(0..0Fh) ..      Test mode commands and Extended features                 |
|       F0h          00h-03h Ext. Set VL6 Noise reduction (0=Enable, 3=Disable)       |
|       F1h          08h-0Fh Ext. Set TC Value per 'C (0=-0.05%, 1=-0.07%, 2..7=?)    |
|       F2h          00h-07h Ext. Oscillator Adjustment                               |
|                              (0..7 = -9%, -6%, -3%, +0%, +3%, +6%, +9%, +12%)       |
|       F7h          00h-01h Ext. Oscillator Source (0=Internal, 1=External, 2=UNDOC) |
|       F6h          00h-1Fh Ext. Frame Frequency Adjust                              |
|                              bit0-2: FrameFQ (0..7 = 0..7)                          |
|                              bit3-4: Fosc    (0-3 = 59kHz, 75kHz, 94kHz, 113kHz)    |
|       FBh          X2h,X6h Ext. Lock/Unlock Interface (bit2: 0=Unlock, 1=Lock)      |
+-------------------------------------------------------------------------------------+
```


### VRAM Writing
First set the VRAM address using three commands with D/C=Low:

```
+----------------------------------------------------------------------------+
|       00h+(xloc) AND 0Fh     ;Set Column Address bit0-3                    |
|       10h+(xloc/10h)         ;Set Column Address bit4-6                    |
|       B0h+(yloc/8)           ;Set Page Address (00h..0Ah, other=reserved?) |
+----------------------------------------------------------------------------+
```

For the actual data transfer, set D/C=High and write data (each two bytes contain vertical 8-pixel columns, with bit0=top, bit7=bottom):

```
+-----------------------------------------------------------------------------------+
|       1st byte = bitplane 1   ;\color 0..3 are usually white, lgray, dgray, black 
|       2nd byte = bitplane 0   ;/(palette can be changed via cmd 88h-8Fh though)   |
+-----------------------------------------------------------------------------------+
```

Note: Column Address (xloc) is auto-incremented after each byte pair, the Page Address (yloc) is NOT incremented when wrapping from x=7Fh to x=00h.
The last page is the \"icon\", this has only 1 pixel per xloc, maybe intended to enable special symbols instead of pixels (on displays to combine symbols and pixels).

### VRAM Reading and Status Byte (both supported in parallel Non-SPI mode only)
The controller supports four modes (Nintendo uses the 4-wire SPI mode):

```
+-----------------------------------------------------------------------------------+
|       3-wire SPI Serial write-only (/CS, CLK, MOSI, with cmd E8h instead D/C pin) |
|       4-wire SPI Serial write-only (/CS, CLK, MOSI, D/C=Data/Cmd)                 |
|       12-wire 8080 Parallel read/write (/CS, D0-D7, D/C, /RD, /WR)                |
|       12-wire 6800 Parallel read/write (/CS, D0-D7, D/C, E, R/W)                  |
+-----------------------------------------------------------------------------------+
```

VRAM can be read setting the VRAM address as usually, and then reading with D/C=High. And, an 8bit status byte can be read with D/C=Low:

```
+-----------------------------------------------------------------------+
|       7    BUSY    Chip is executing instruction (0=Ready, 1=Busy)    |
|       6    ON      Display is On/Off             (0=Off, 1=On)        |
|       5    RES     Chip is executing reset       (0=Ready, 1=Busy)    |
|       4-0  -       Fixed Chip ID                 (08h=SSD1850)        |
+-----------------------------------------------------------------------+
```


### Note
Nintendo uses a 96x64 pixel grayscale LCD screen with 2bpp, without backlight or frontlight. VRAM is double buffered (VRAM size is at least 96x128 pixels).
The display controller seems to be a Solomon System SSD1850 chip\... or similar, there are a number of datasheets that are more or less matching the LCD commands used in the firmware:

```
+-----------------------------------------------------------------------------------+
|       SSD0852  128x128 would allow double-buffer, but extended commands are wrong |
|       SSD0858  104x65  close, but extended commands are wrong                     |
|       SSD0859  128x81  could be correct (almost same as SSD1850)                  |
|       SSD1820  128x65  wrong, lacks palette (command 88h-8Fh)                     |
|       SSD1820A 128x65  wrong, lacks palette (command 88h-8Fh)                     |
|       SSD1821  128x81  wrong, lacks palette (command 88h-8Fh)                     |
|       SSD1850  128x65  could be correct (ysiz is good, but no double-buffering)   |
|       SSD1851  128x81  as above, but more lines than needed                       |
|       SSD1852  128x128 would allow double-buffer, but extended commands are wrong |
|       SSD1854  128x160 wrong, uses 2-byte command B0h,YYh lacks extended commands |
|                        (also cmd 18h,20h,4xh,50h,60h-63h,64h,82h,83h,etc. differ) |
|       SSD1858  104x65  close, but lacks many extended commands                    |
|       SSD1859  128x81  could be correct (almost same as SSD1850)                  |
+-----------------------------------------------------------------------------------+
```

But, Nintendo\'s firmware contains extended command F7h,02h (which isn\'t mentioned in any of the above datasheets).
And, the firmware seems to use two 64-line framebuffers at DisplayStart=0 and DisplayStart=64, ie. needing 128 lines in total, which leaves no space for the \"icon\" scanline (at least not addressable via cmd B0h+y).



