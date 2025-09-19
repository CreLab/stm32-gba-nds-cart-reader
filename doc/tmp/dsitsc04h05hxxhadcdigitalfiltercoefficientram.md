# DSi TSC\[04h..05h:xxh\], ADC Digital Filter Coefficient RAM


Default values shown for this page only become valid 100us following a hardware or software reset.

### TSC\[04h-05h:xxh\] - ADC Coefficient RAM (126 x 16bit)
Coefficients are signed 16bit (-32,768..+32,767), each occupying 2 bytes (MSB,LSB).
The MSB should always be written first, immediately followed by the LSB (even if only the MSB or LSB portion of the coefficient changes, both registers should be written in this sequence).

```
+-------------------------------------------------------------------------------------+
|                        ADC miniDSP   ADC FIR Filter Special                         |
|                        Coefficients  Coefficients   Coefficients                    |
|       TSC[4:00h]       Page Select   -              -                               |
|       TSC[4:01h]       Reserved      -              -                               |
|       TSC[4:02h..07h]  C1..C3        -              N0,N1,D1 for AGC LPF            |
|                                                       (first-order IIR, used        |
|                                                       as averager to detect level)  |
|       TSC[4:08h..0Dh]  C4..C6        -              N0,N1,D1 for ADC-programmable   |
|                                                       first-order IIR               |
|       TSC[4:0Eh..17h]  C7..C11       FIR0..FIR4     N0,N1,N2,D1,D2 for ADC Biquad A |
|       TSC[4:18h..21h]  C12..C16      FIR5..FIR9     N0,N1,N2,D1,D2 for ADC Biquad B |
|       TSC[4:22h..2Bh]  C17..C21      FIR10..FIR14   N0,N1,N2,D1,D2 for ADC Biquad C |
|       TSC[4:2Ch..35h]  C22..C26      FIR15..FIR19   N0,N1,N2,D1,D2 for ADC Biquad D |
|       TSC[4:36h..3Fh]  C27..C31      FIR20..FIR24   N0,N1,N2,D1,D2 for ADC Biquad E |
|       TSC[4:40h..7Fh]  C32..C63      -              -                               |
|       TSC[5:00h]       Page Select   -              -                               |
|       TSC[5:01h]       Reserved      -              -                               |
|       TSC[5:02h..7Fh]  C65..C127     -              -                               |
+-------------------------------------------------------------------------------------+
```


### Multi-order FIR Filter (Finite Impulse Response)

```
+-------------------------------------------------------------------------------+
|       input[n] ---o--MUL(F0)-->ADD-----------------> output[n]                |
|                   |             ^                                             |
|               input[n-1]        |                          ;\                 
|                   |             |                          ; first order FIR  |
|                   o--MUL(F1)-->ADD                         ;/                 |
|                   |             ^                                             |
|               input[n-2]        |                          ;\                 
|                   |             |                          ; second order FIR |
|                   o--MUL(F2)-->ADD                         ;/                 |
|                   :             ^                                             |
|                   :             :                          ;-further order's  |
+-------------------------------------------------------------------------------+
```


### First-order IIR Filter (Infinite Impulse Response)

```
+------------------------------------------------------------------------------+
|       input[n] ---o--MUL(N0)-->ADD-------------o---> output[n]               |
|                   |             ^              |                             |
|               input[n-1]        |          output[n-1]     ;\                
|                   |             |              |           ; first order IIR |
|                   o--MUL(N1)-->ADD<--MUL(-D1)--o           ;/                |
+------------------------------------------------------------------------------+
```


### Biquad Filter (IIR with 1st and 2nd order)

```
+-------------------------------------------------------------------------------+
|       input[n] ---o--MUL(N0)-->ADD-------------o---> output[n]                |
|                   |             ^              |                              |
|               input[n-1]        |          output[n-1]     ;\                 
|                   |             |              |           ; first order IIR  |
|                   o--MUL(N1)-->ADD<--MUL(-D1)--o           ;/                 |
|                   |             ^              |                              |
|               input[n-2]        |          output[n-2]     ;\                 
|                   |             |              |           ; second order IIR |
|                   o--MUL(N2)-->ADD<--MUL(-D2)--o           ;/                 |
+-------------------------------------------------------------------------------+
```





