# ARM VFP Floating Point Registers


### Floating point Registers
Registers S0-S31 can contain Single-precision float values, or 32bit Integers (for conversion to/from float format), or a pair of two Single-precision registers can contain one Double-precision float value.

```
+-------------------------------------------------------------------------------+
|       Scalar Bank       Vector bank 1       Vector bank 2       Vector bank 3 |
|       S1:S0    D0       S9:S8    D4         S17:S16  D8         S25:S24  D12  |
|       S2:S3    D1       S11:S10  D5         S19:S18  D9         S27:S26  D13  |
|       S5:S4    D2       S13:S12  D6         S21:S20  D10        S29:S28  D14  |
|       S7:S6    D3       S15:S14  D7         S23:S22  D11        S31:S30  D15  |
+-------------------------------------------------------------------------------+
```

The VFP supports \"Scalar\" and \"Vector\" modes (and a mixed \"Vector/Scalar\" mode).
The \"Vector\" mode can perform simultaneous operations on up to 8 singles, or up to 4 doubles (via Vector LEN and STRIDE selected in FPSCR register).
The registers are organized in \"banks\", and vectors cannot cross banks (eg. using operand S23 with LEN=3, STRIDE=2 would use registers S23,S17,S19).

### Scalar Mode, Fd=Fm \<op\> Fn
The \"Scalar\" mode performs operations on 1 single or double. This done in any of the following situations:

```
+------------------------------------------------------------------------------------+
|      - When FPSCR register is set to Vector LEN=1 (and STRIDE=1), or               |
|      - When Destination is S0..S7 or D0..D3 (scalar bank), or                      |
|      - When using FCMP comparision opcodes, or                                     |
|      - When using FCVT or FxxTOxx conversion opcodes, or                           |
|      - When using FMxxRxx register transfer opcodes, or                            |
|      - When using FLDxx/FSTxx load/store (whereof, FLDM/FSTM can transfer multiple |
|        registers in vector-like fashion; regardless of LEN/STRIDE settings)        |
+------------------------------------------------------------------------------------+
```


### Vector Mode, Fd\[LEN\]=Fm\[LEN\] \<op\> Fn\[LEN\]
The vector mode does merely perform the selected operation on all array elements, this is correct for cases like Vector+Vector addition, but incorrect for Vector\*Vector multiplication (to get the final result one must manually compute the sum of the results).

```
+--------------------------------------------------------------------------------+
|      - When FPSCR register is set to Vector LEN=2..8 (and STRIDE=1..2), and    |
|      - When Source and Destination are S8..S31 or D4..D15 (vector banks), and  |
|      - When using FADD, FSUB, FDIV, FCPY, FABS, FNEG, FSQRT, or FxMxx multiply |
+--------------------------------------------------------------------------------+
```


### Mixed Mode, Fd\[LEN\]=Fm \<op\> Fn\[LEN\]
This allows to add/multiply/etc. all elements of a vector by a scalar value. This is done when combining vectors operands with the following:

```
+-----------------------------------------------------------------------+
|      - When Source operand Fm is S0..S7 or D0..D3 (scalar bank), and  |
|      - othersise same conditions as for Vector mode                   |
+-----------------------------------------------------------------------+
```


### Integer Format (S0..S31 aka I0..I31)

```
+------------------------------------------------------------------------+
|       31-0   Integer (signed or unsigned, depending on FxxTOxx opcode) |
+------------------------------------------------------------------------+
```

The VFP can\'t do integer maths, however, one can load/store integer values in S0..S31, and then use the FxxTOxx opcodes to convert integers to/from float format. The integers are always 32bit (no matter if converting Single/Double precision float values).

### Single Precision Registers (float1.8.23) (S0..S31)

```
+--------------------------------------------------------------------------+
|       31     1bit  Sign (0=Positive, 1=Negative)                         |
|       30-23  8bit  Exponent (01h..FEh=for 2^(N-7Fh), or 00h/FFh=Special) |
|       22-0   23bit Fraction (0..7FFFFFh)                                 |
+--------------------------------------------------------------------------+
```


### Double Precision Registers (float1.11.52) (D0..D15)

```
+-------------------------------------------------------------------------------+
|       63     1bit  Sign (0=Positive, 1=Negative)                              |
|       62-52  11bit Exponent (001h..7FEh=for 2^(N-3FFh), or 000h/7FFh=Special) |
|       51-0   52bit Fraction (0..FFFFFFFFFFFFFh)                               |
+-------------------------------------------------------------------------------+
```


### Exponent 01h..FEh (Single) or 001h..7FEh (Double):

```
+-----------------------------------------------------------------------+
|       Sign * 2^(exponent-7Fh) * (1.fraction)    ;Single               |
|       Sign * 2^(exponent-3FFh) * (1.fraction)   ;Double               |
+-----------------------------------------------------------------------+
```

### Exponent 00h (Single) or 000h (Double), aka Small Numbers and Zero:

```
+---------------------------------------------------------------------------------+
|       Sign * 2^(-7Eh) * (0.fraction)            ;Single                         |
|       Sign * 2^(-3FEh) * (0.fraction)           ;Double                         |
|       The above includes 0 being encoded as fraction=0, the sign bit is ignored |
|       for cases like "compare +/-0", but the sign is used for "divide by +/-0". |
|       Small numbers in 0.fraction format may require extra clock cycles for     |
|       counting leading zeroes; unknown if that problem does actually exist on   |
|       ARM hardware, however, the "flush to zero" feature (see FPSCR.bit24) can  |
|       be used to avoid that issue; 0.fraction will be then replaced by 0.000.   |
+---------------------------------------------------------------------------------+
```

### Exponent FFh (Single) or 7FFh (Double), aka NaN\'s and Infinite:

```
+-------------------------------------------------------------------------------------+
|       fraction=000000h          or 0000000000000h                 +/-Infinite       |
|       fraction=000001h..3FFFFFh or 0000000000001h..7FFFFFFFFFFFFh +/-Signaling NaNs |
|       fraction=400000h          or 8000000000000h                 +/-Default NaN    |
|       fraction=400000h..7FFFFFh or 8000000000000h..FFFFFFFFFFFFFh +/-Quite NaNs     |
|       NaNs (Not a Number) can be used for abstract non-numeric expressions; this    |
|       isn't useful for normal maths, but may be useful if a database contains       |
|       entries like "Weight=UNKNOWN". If so, one may handle the NaN before passing   |
|       it to the floating point unit, or otherwise the hardware will either trigger  |
|       an exception (Signaling NaNs) or leave the NaN unchanged (Quite NaNs),        |
|       eg. "UNKNOWN*2+3 = UNKNOWN", or replace it by Default NaN (if FPSCR.bit25=1). |
|       Different NaNs can be compared using integer comparisons, float comparisions  |
|       of NaNs have "unordered" results (even when comparing a NaN with itself).     |
+-------------------------------------------------------------------------------------+
```


### Multiply Note
When multiplying vector\*vector, the hardware does merely multiply the components (without computing the sum of the multiply results). To get sum, one could use FMUL and several FADD\'s with different strides. Or better, for multiple vector\*vector multiplications, use FMUL and several FMAC\'s with source data rearranged as so:

```
+-----------------------------------------------------------------------+
|       FMUL (X,X,X,X,X,X,X,X)*(X,X,X,X,X,X,X,X)                        |
|       FMAC (Y,Y,Y,Y,Y,Y,Y,Y)*(Y,Y,Y,Y,Y,Y,Y,Y)                        |
|       FMAC (Z,Z,Z,Z,Z,Z,Z,Z)*(Z,Z,Z,Z,Z,Z,Z,Z)                        |
|       FMAC (W,W,W,W,W,W,W,W)*(W,W,W,W,W,W,W,W)                        |
+-----------------------------------------------------------------------+
```

Ie. in that case, the 1st \"vector\" contains the X components from up to eight (X,Y,Z,W) vectors.



