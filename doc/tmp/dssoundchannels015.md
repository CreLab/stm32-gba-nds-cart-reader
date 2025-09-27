# DS Sound Channels 0..15


Each of the 16 sound channels occopies 16 bytes in the I/O region, starting with channel 0 at 4000400h..400040Fh, up to channel 15 at 40004F0h..40004FFh.

### 40004x0h - NDS7 - SOUNDxCNT - Sound Channel X Control Register (R/W)

```
+-------------------------------------------------------------------------------------+
|       Bit0-6    Volume Mul   (0..127=silent..loud)                                  |
|       Bit7      Not used     (always zero)                                          |
|       Bit8-9    Volume Div   (0=Normal, 1=Div2, 2=Div4, 3=Div16)                    |
|       Bit10-14  Not used     (always zero)                                          |
|       Bit15     Hold         (0=Normal, 1=Hold last sample after one-shot sound)    |
|       Bit16-22  Panning      (0..127=left..right) (64=half volume on both speakers) |
|       Bit23     Not used     (always zero)                                          |
|       Bit24-26  Wave Duty    (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)   |
|       Bit27-28  Repeat Mode  (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)  |
|       Bit29-30  Format       (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)            |
|       Bit31     Start/Status (0=Stop, 1=Start/Busy)                                 |
+-------------------------------------------------------------------------------------+
```

All channels support ADPCM/PCM formats, PSG rectangular wave can be used only on channels 8..13, and white noise only on channels 14..15.

### 40004x4h - NDS7 - SOUNDxSAD - Sound Channel X Data Source Register (W)

```
+------------------------------------------------------------------------------+
|       Bit0-26  Source Address (must be word aligned, bit0-1 are always zero) |
|       Bit27-31 Not used                                                      |
+------------------------------------------------------------------------------+
```


### 40004x8h - NDS7 - SOUNDxTMR - Sound Channel X Timer Register (W)

```
+-----------------------------------------------------------------------------+
|       Bit0-15  Timer Value, Sample frequency, timerval=-(33513982Hz/2)/freq |
+-----------------------------------------------------------------------------+
```

The PSG Duty Cycles are composed of eight \"samples\", and so, the frequency for Rectangular Wave is 1/8th of the selected sample frequency.
For PSG Noise, the noise frequency is equal to the sample frequency.

### 40004xAh - NDS7 - SOUNDxPNT - Sound Channel X Loopstart Register (W)

```
+-----------------------------------------------------------------------+
|       Bit0-15  Loop Start, Sample loop start position                 |
|                (counted in words, ie. N*4 bytes)                      |
+-----------------------------------------------------------------------+
```


### 40004xCh - NDS7 - SOUNDxLEN - Sound Channel X Length Register (W)
The number of samples for N words is 4\*N PCM8 samples, 2\*N PCM16 samples, or 8\*(N-1) ADPCM samples (the first word containing the ADPCM header). The Sound Length is not used in PSG mode.

```
+-----------------------------------------------------------------------+
|       Bit0-21  Sound length (counted in words, ie. N*4 bytes)         |
|       Bit22-31 Not used                                               |
+-----------------------------------------------------------------------+
```

Minimum length (the sum of PNT+LEN) is 4 words (16 bytes), smaller values (0..3 words) are causing hang-ups (busy bit remains set infinite, but no sound output occurs).

In One-shot mode, the sound length is the sum of (PNT+LEN).
In Looped mode, the length is (1\*PNT+Infinite\*LEN), ie. the first part (PNT) is played once, the second part (LEN) is repeated infinitely.



