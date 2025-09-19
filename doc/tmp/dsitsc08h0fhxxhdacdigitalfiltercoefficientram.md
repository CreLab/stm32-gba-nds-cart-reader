# DSi TSC\[08h..0Fh:xxh\], DAC Digital Filter Coefficient RAM


Default values shown for this page only become valid 100us following a hardware or software reset.

### TSC\[08h:01h\] - DAC Coefficient RAM Control (00h)

```
+-------------------------------------------------------------------------------------+
|       7-4   Reserved. Write only the reset value.                                   |
|       3     DAC miniDSP generated flag for toggling MSB of coefficient RAM address  |
|             (only used in non-adaptive mode)                                (R)     |
|       2     DAC Adaptive Filtering in DAC miniDSP (0=Disabled, 1=Enabled)   (R/W)   |
|       1     DAC Adaptive Filter Buffer Control Flag                         (R)     |
|               aka DAC Coefficient Buffers in adaptive filter mode                   |
|                  0: miniDSP accesses Buffer A,                                      |
|                       external control interface (=the user?) accesses Buffer B     |
|                  1: miniDSP accesses Buffer B,                                      |
|                       external control interface (=the user?) accesses Buffer A     |
|       0     DAC Adaptive Filter Buffer Switch Control                       (R/W)   |
|              0: DAC coefficient buffers will not be switched at next frame boundary |
|              1: DAC coefficient buffers will     be switched at next frame boundary |
|                 (only if adaptive filtering mode is enabled)                        |
|                 This bit will self-clear on switching.                              |
+-------------------------------------------------------------------------------------+
```


### TSC\[08h..0Bh:xxh\] - DAC Coefficient RAM, DAC Buffer A (252 x 16bit)
Coefficients are signed 16bit (-32,768..+32,767), each occupying 2 bytes (MSB,LSB).
The MSB should always be written first, immediately followed by the LSB (even if only the MSB or LSB portion of the coefficient changes, both registers should be written in this sequence).

```
+-------------------------------------------------------------------------------------+
|                        DAC miniDSP    Special                                       |
|                       (DAC Buffer A)  DAC-programmable                              |
|                        Coefficient    Coefficient                                   |
|       TSC[8:00h]       Page Select    -                                             |
|       TSC[8:01h]       Control        - (see above)                                 |
|       TSC[8:02h..0Bh]  C1..C5         N0,N1,N2,D1,D2 for Left Biquad A  ;N0=7FFFh   |
|       TSC[8:0Ch..15h]  C6..C10        N0,N1,N2,D1,D2 for Left Biquad B  ;N1,N2,D1,  |
|       TSC[8:16h..1Fh]  C11..C15       N0,N1,N2,D1,D2 for Left Biquad C  ;     D2=0  |
|       TSC[8:20h..29h]  C16..C20       N0,N1,N2,D1,D2 for Left Biquad D              |
|       TSC[8:2Ah..33h]  C21..C25       N0,N1,N2,D1,D2 for Left Biquad E              |
|       TSC[8:34h..3Dh]  C26..C30       N0,N1,N2,D1,D2 for Left Biquad F              |
|       TSC[8:3Eh..3Fh]  C31            -                                             |
|       TSC[8:40h..41h]  C32            for 3D PGA for PRB_P23, PRB_P24 and PRB_P25   |
|       TSC[8:42h..4Bh]  C33..C37       N0,N1,N2,D1,D2 for Right Biquad A             |
|       TSC[8:4Ch..55h]  C38..C42       N0,N1,N2,D1,D2 for Right Biquad B             |
|       TSC[8:56h..5Fh]  C43..C47       N0,N1,N2,D1,D2 for Right Biquad C             |
|       TSC[8:60h..69h]  C48..C52       N0,N1,N2,D1,D2 for Right Biquad D             |
|       TSC[8:6Ah..73h]  C53..C57       N0,N1,N2,D1,D2 for Right Biquad E             |
|       TSC[8:74h..7Dh]  C58..C62       N0,N1,N2,D1,D2 for Right Biquad F             |
|       TSC[8:7Eh..7Fh]  C63            -                                             |
|       TSC[9:00h]       Page Select    -                                             |
|       TSC[9:01h]       Reserved       - (do not write to this register)             |
|       TSC[9:02h..07h]  C65..C67       N0,N1,D1 for Left first-order IIR             |
|       TSC[9:08h..0Dh]  C68..C70       N0,N1,D1 for Right first-order IIR            |
|       TSC[9:0Eh..13h]  C71..C73       N0,N1,D1 for DRC first-order high-pass filter |
|       TSC[9:14h..19h]  C74..C76       N0,N1,D1 for DRC first-order low-pass filter  |
|       TSC[9:1Ah..7Fh]  C77..C127      -                                             |
|       TSC[A:00h]       Page Select    -                                             |
|       TSC[A:01h]       Reserved       - (do not write to this register)             |
|       TSC[A:02h..7Fh]  C129..C191     -                                             |
|       TSC[B:00h]       Page Select    -                                             |
|       TSC[B:01h]       Reserved       - (do not write to this register)             |
|       TSC[B:02h..7Fh]  C193..C255     -                                             |
+-------------------------------------------------------------------------------------+
```


### TSC\[0Ch..0Fh:xxh\] - DAC Coefficient RAM, DAC Buffer B (252 x 16bit)
This is essentially same as above Buffer A. But it\'s unclear if Buffer B is having the same special Biquad/3DPGA/IIR/DRC functions (the official datasheet doesn\'t mention them, but it does specify the initial reset values same as for Buffer A, ie. with value 7FFFh for the locations that correspond to \"N0\" coefficients, which is suggesting that those special functions are present in Buffer B, too).

```
+----------------------------------------------------------------------------+
|                        DAC miniDSP    Special                              |
|                       (DAC Buffer A)  DAC-programmable                     |
|                        Coefficient    Coefficient                          |
|       TSC[C:02h..0Bh]  C1..C5         Unknown  ;\                          
|       TSC[C:0Ch..15h]  C6..C10        Unknown  ;                           |
|       TSC[C:16h..1Fh]  C11..C15       Unknown  ; maybe Left Biquad A..F    |
|       TSC[C:20h..29h]  C16..C20       Unknown  ; as for Buffer A           |
|       TSC[C:2Ah..33h]  C21..C25       Unknown  ;                           |
|       TSC[C:34h..3Dh]  C26..C30       Unknown  ;/                          |
|       TSC[C:3Eh..3Fh]  C31            -                                    |
|       TSC[C:40h..41h]  C32            Unknown maybe 3D PGA as for Buffer A |
|       TSC[C:42h..4Bh]  C33..C37       Unknown  ;\                          
|       TSC[C:4Ch..55h]  C38..C42       Unknown  ;                           |
|       TSC[C:56h..5Fh]  C43..C47       Unknown  ; maybe Right Biquad A..F   |
|       TSC[C:60h..69h]  C48..C52       Unknown  ; as for Buffer A           |
|       TSC[C:6Ah..73h]  C53..C57       Unknown  ;                           |
|       TSC[C:74h..7Dh]  C58..C62       Unknown  ;/                          |
|       TSC[C:7Eh..7Fh]  C63            -                                    |
|       TSC[D:00h]       Page Select    -                                    |
|       TSC[D:01h]       Reserved       - (do not write to this register)    |
|       TSC[D:02h..07h]  C65..C67       Unknown  ;\                          
|       TSC[D:08h..0Dh]  C68..C70       Unknown  ; maybe IIR and DRC         |
|       TSC[D:0Eh..13h]  C71..C73       Unknown  ; as for Buffer A           |
|       TSC[D:14h..19h]  C74..C76       Unknown  ;/                          |
|       TSC[D:1Ah..7Fh]  C77..C127      -                                    |
|       TSC[E:00h]       Page Select    -                                    |
|       TSC[E:01h]       Reserved       - (do not write to this register)    |
|       TSC[E:02h..7Fh]  C129..C191     -                                    |
|       TSC[F:00h]       Page Select    -                                    |
|       TSC[F:01h]       Reserved       - (do not write to this register)    |
|       TSC[F:02h..7Fh]  C193..C255     -                                    |
+----------------------------------------------------------------------------+
```




