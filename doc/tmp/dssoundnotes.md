# DS Sound Notes


### Sound delayed Start/Restart (timing glitch)
A sound will be started/restarted when changing its start bit from 0 to 1, however, the sound won\'t start immediately: PSG/Noise starts after 1 sample, PCM starts after 3 samples, and ADPCM starts after 11 samples (3 dummy samples as for PCM, plus 8 dummy samples for the ADPCM header).

### Sound Stop (timing note)
In one-shot mode, the Busy bit gets cleared automatically at the BEGIN of the last sample period, nethertheless (despite of the cleared Busy bit) the last sample is kept output until the END of the last sample period (or, if the Hold flag is set, then the last sample is kept output infinitely, that is, until Hold gets cleared, or until the sound gets restarted).

### Hold Flag (appears useless/bugged)
The Hold flag allows to keep the last sample being output infinitely after the end of one-shot sounds. This feature is probably intended to allow to play two continous one-shot sound blocks (without producing any scratch noise upon small delays between both blocks, which would occur if the output level would drop to zero).
However, the feature doesn\'t work as intended. As described above, PCM8/PCM16 sound starts are delayed by 3 samples. With Hold flag set, old output level is acually kept intact during the 1st sample, but the output level drops to zero during 2nd-3rd sample, before starting the new sound in 4th sample.

### 7bit Volume and Panning Values

```
+-----------------------------------------------------------------------+
|       data.vol   = data*N/128                                         |
|       pan.left   = data*(128-N)/128                                   |
|       pan.right  = data*N/128                                         |
|       master.vol = data*N/128/64                                      |
+-----------------------------------------------------------------------+
```

Register settings of 0..126,127 are interpreted as N=0..126,128.

### Max Output Levels
When configured to max volume (and left-most or right-most panning), each channel can span the full 10bit output range (-200h..1FFh) on one speaker, as well as the full 16bit input range (-8000h..7FFFh) on one capture unit.
(It needs 2 channels to span the whole range on BOTH speakers/capture units.)
Together, all sixteen channels could thus reach levels up to -1E00h..21F0h (with default BIAS=200h) on one speaker, and -80000h..+7FFF0h on one capture unit. However, to avoid overflows, speaker outputs are clipped to MinMax(0,3FFh), and capture inputs to MinMax(-8000h..+7FFFh).

### Channel/Mixer Bit-Widths

```
+-----------------------------------------------------------------------+
|       Step                           Bits  Min        Max             |
|       0 Incoming PCM16 Data          16.0  -8000h     +7FFFh          |
|       1 Volume Divider (div 1..16)   16.4  -8000h     +7FFFh          |
|       2 Volume Factor (mul N/128)    16.11 -8000h     +7FFFh          |
|       3 Panning (mul N/128)          16.18 -8000h     +7FFFh          |
|       4 Rounding Down (strip 10bit)  16.8  -8000h     +7FFFh          |
|       5 Mixer (add channel 0..15)    20.8  -80000h    +7FFF0h         |
|       6 Master Volume (mul N/128/64) 14.21 -2000h     +1FF0h          |
|       7 Strip fraction               14.0  -2000h     +1FF0h          |
|       8 Add Bias (0..3FFh, def=200h) 15.0  -2000h+0   +1FF0h+3FFh     |
|       9 Clip (min/max 0h..3FFh)      10.0  0          +3FFh           |
+-----------------------------------------------------------------------+
```

Table shows integer.fractional bits, and min/max values (without fraction).

### Capture Clipping/Rounding
Incoming ch(a) is NOT clipped, ch(a)+ch(b) may overflow (see Capture Bugs).
Incoming mixer data (20.8bits) is clipped to 16.8bits (MinMax -8000h..7FFFh).
For PCM8 capture format, the 16.8 bits are divided by 100h (=8.16 bits).
If the MSB of the fractional part is set, then data is rounded towards zero.
(Positive values are rounded down, negative values are rounded up.)
The fractional part is then discarded, and plain integer data is captured.

### PSG Sound
The output volume equals to PCM16 values +7FFFh (HIGH) and -7FFFh (LOW).
PSG sound is always Infinite (the SOUNDxLEN Register, and the SOUNDxCNT Repeat Mode bits have no effect). The PSG hardware doesn\'t support sound length, sweep, or volume envelopes, however, these effects can be produced by software with little overload (or, more typically, with enormous overload, depending on the programming language used).

### PSG Wave Duty (channel 8..13 in PSG mode)
Each duty cycle consists of eight HIGH or LOW samples, so the sound frequency is 1/8th of the selected sample rate. The duty cycle always starts at the begin of the LOW period when the sound gets (re-)started.

```
+-----------------------------------------------------------------------+
|       0  12.5% "_______-_______-_______-"                             |
|       1  25.0% "______--______--______--"                             |
|       2  37.5% "_____---_____---_____---"                             |
|       3  50.0% "____----____----____----"                             |
|       4  62.5% "___-----___-----___-----"                             |
|       5  75.0% "__------__------__------"                             |
|       6  87.5% "_-------_-------_-------"                             |
|       7   0.0% "________________________"                             |
+-----------------------------------------------------------------------+
```

The Wave Duty bits exist and are read/write-able on all channels (although they are actually used only in PSG mode on channels 8-13).

### PSG Noise (channel 14..15 in PSG mode)
Noise randomly switches between HIGH and LOW samples, the output levels are calculated, at the selected sample rate, as such:

```
+-----------------------------------------------------------------------+
|       X=X SHR 1, IF carry THEN Out=LOW, X=X XOR 6000h ELSE Out=HIGH   |
+-----------------------------------------------------------------------+
```

The initial value when (re-)starting the sound is X=7FFFh. The formula is more or less same as \"15bit polynomial counter\" used on 8bit Gameboy and GBA.

### PCM8 and PCM16
Signed samples in range -80h..+7Fh (PCM8), or -8000h..+7FFFh (PCM16).
The output volume of PCM8=NNh is equal to PCM16=NN00h.

### IMA-ADPCM Format
IMA-ADPCM is a Adaptive Differential Pulse Code Modulation (ADPCM) variant, designed by International Multimedia Association (IMA), the format is used, among others, in IMA-ADPCM compressed Windows .WAV files.
The NDS data consist of a 32bit header, followed by 4bit values (so each byte contains two values, the first value in the lower 4bits, the second in upper 4 bits). The 32bit header contains initial values:

```
+-----------------------------------------------------------------------------+
|       Bit0-15   Initial PCM16 Value (Pcm16bit = -7FFFh..+7FFF) (not -8000h) |
|       Bit16-22  Initial Table Index Value (Index = 0..88)                   |
|       Bit23-31  Not used (zero)                                             |
+-----------------------------------------------------------------------------+
```

In theory, the 4bit values are decoded into PCM16 values, as such:

```
+----------------------------------------------------------------------------------+
|       Diff = ((Data4bit AND 7)*2+1)*AdpcmTable[Index]/8      ;see rounding-error |
|       IF (Data4bit AND 8)=0 THEN Pcm16bit = Max(Pcm16bit+Diff,+7FFFh)            |
|       IF (Data4bit AND 8)=8 THEN Pcm16bit = Min(Pcm16bit-Diff,-7FFFh)            |
|       Index = MinMax (Index+IndexTable[Data4bit AND 7],0,88)                     |
+----------------------------------------------------------------------------------+
```

In practice, the first line works like so (with rounding-error):

```
+-----------------------------------------------------------------------+
|       Diff = AdpcmTable[Index]/8                                      |
|       IF (data4bit AND 1) THEN Diff = Diff + AdpcmTable[Index]/4      |
|       IF (data4bit AND 2) THEN Diff = Diff + AdpcmTable[Index]/2      |
|       IF (data4bit AND 4) THEN Diff = Diff + AdpcmTable[Index]/1      |
+-----------------------------------------------------------------------+
```

And, a note on the second/third lines (with clipping-error):

```
+------------------------------------------------------------------------------------+
|       Max(+7FFFh) leaves -8000h unclipped (can happen if initial PCM16 was -8000h) |
|       Min(-7FFFh) clips -8000h to -7FFFh (possibly unlike windows .WAV files?)     |
+------------------------------------------------------------------------------------+
```

Whereas, IndexTable\[0..7\] = -1,-1,-1,-1,2,4,6,8. And AdpcmTable \[0..88\] =

```
+-------------------------------------------------------------------------------+
|       0007h,0008h,0009h,000Ah,000Bh,000Ch,000Dh,000Eh,0010h,0011h,0013h,0015h |
|       0017h,0019h,001Ch,001Fh,0022h,0025h,0029h,002Dh,0032h,0037h,003Ch,0042h |
|       0049h,0050h,0058h,0061h,006Bh,0076h,0082h,008Fh,009Dh,00ADh,00BEh,00D1h |
|       00E6h,00FDh,0117h,0133h,0151h,0173h,0198h,01C1h,01EEh,0220h,0256h,0292h |
|       02D4h,031Ch,036Ch,03C3h,0424h,048Eh,0502h,0583h,0610h,06ABh,0756h,0812h |
|       08E0h,09C3h,0ABDh,0BD0h,0CFFh,0E4Ch,0FBAh,114Ch,1307h,14EEh,1706h,1954h |
|       1BDCh,1EA5h,21B6h,2515h,28CAh,2CDFh,315Bh,364Bh,3BB9h,41B2h,4844h,4F7Eh |
|       5771h,602Fh,69CEh,7462h,7FFFh                                           |
+-------------------------------------------------------------------------------+
```

The closest way to reproduce the AdpcmTable with 32bit integer maths appears:

```
+-----------------------------------------------------------------------------+
|       X=000776d2h, FOR I=0 TO 88, Table[I]=X SHR 16, X=X+(X/10), NEXT I     |
|       Table[3]=000Ah, Table[4]=000Bh, Table[88]=7FFFh, Table[89..127]=0000h |
+-----------------------------------------------------------------------------+
```

When using ADPCM and loops, set the loopstart position to the data part, rather than the header. At the loop end, the SAD value is reloaded to the loop start location, additionally index and pcm16 values are reloaded to the values that have originally appeared at that location. Do not change the ADPCM loop start position during playback.

### Microphone Input
For Microphone (and Touchscreen) inputs, see
- [DS Touch Screen Controller (TSC)](./dstouchscreencontrollertsc.md)



