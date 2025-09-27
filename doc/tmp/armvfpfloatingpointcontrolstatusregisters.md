# ARM VFP Floating Point Control/Status Registers


### FPSID Register (Floating Point System ID) (R)

```
+-------------------------------------------------------------------------------------+
|       31-24  Implementor code (41h=ARM)                                             |
|       23     Hardware/software implementation (0=Hardware, 1=Software)              |
|       22-21  FSTMX/FLDMX format  (0=Format 1, Other=Reserved)                       |
|       20     Supported Precision (0=Single and Double, 1=Single only)               |
|       19-16  Architecture version number (0=VFPv1, 1=VFPv2, 2-15=Reserved)          |
|       15-8   Primary part number of VFP implementation (20h=VFP11) ;\Implementation 
|       7-4    Variant number                            (0Bh=MPCore); defined        |
|       3-0    Revision number of the part               (04h=Fourth);/               |
+-------------------------------------------------------------------------------------+
```

New3DS: 410120b4h = VFPv2 D variant (with single AND double precision).

### FPSCR Register (Floating Point Status/Control Register for user-level) (R/W)

```
+-------------------------------------------------------------------------------------+
|       31     N Flag (1=Comparision result is Less Than)                             |
|       30     Z Flag (1=Comparision result is Equal)                                 |
|       29     C Flag (1=Comparision result is Equal, Greater Than, or Unordered)     |
|       28     V Flag (1=Comparision result is Unordered)                             |
|              Note: Use FMSTAT opcode to transfer above flags to ARM CPSR flags      |
|       27-26  Unused (0)                                                             |
|       25     Default Nan mode   (XXX see page C2-16) (0=Disable, 1=Enable)          |
|       24     Flush-to-zero mode (XXX see page C2-14) (0=Disable, 1=Enable)          |
|       23-22  Rounding mode (0=To Nearest, 1=Up, 2=Down, 3=Towards Zero)             |
|       21-20  Vector Stride (0/3 = 1/2 Singles; or 0/3 = 1/2 Doubles) (1/2=Reserved) |
|       19     Unused (0)                                                             |
|       18-16  Vector Len    (0..7 = 1..8 Singles; or 0..3 = 1..4 Doubles)            |
|       15     Trap Enable Input Denormal (aka Subnormal)     ;\                      
|       14-13  Unused (0)                                     ;                       |
|       12     Trap Enable Inexact                            ; Trap Enable aka       |
|       11     Trap Enable Underflow                          ; Exception Enable      |
|       10     Trap Enable Overflow                           ;                       |
|       9      Trap Enable Division by Zero                   ;                       |
|       8      Trap Enable Invalid Operation                  ;/                      |
|       7      Cumulative Exception Input Denormal            ;\                      
|       6-5    RES                                            ;                       |
|       4      Cumulative Exception Inexact                   ; Cumulative what...?   |
|       3      Cumulative Exception Underflow                 ;                       |
|       2      Cumulative Exception Overflow                  ;                       |
|       1      Cumulative Exception Division by Zero          ;                       |
|       0      Cumulative Exception Invalid Operation         ;/                      |
+-------------------------------------------------------------------------------------+
```


### FPEXC Register (Floating Point Exception Register for system-level) (R/W)

```
+-------------------------------------------------------------------------------------+
|       31     Exception Flag ... long blurb replated to process swap code            |
|       30     Enable Floating Point Instructions (0=Disable, 1=Enable)               |
|       29-0   Sub-architecture defined (see below for mpcore)                        |
|      Extra mpcore bits:                                                             |
|       29     Unused (0)                                                             |
|       28     FPINST2 instruction valid flag                                         |
|       27-11  Unused (0)                                                             |
|       10-8   VECITR Number of remaining iterations after exception (0..6=1..7, 7=0) |
|       7      INV Input exception flag                                               |
|       6-4    Unused (0)                                                             |
|       3      UFC Potential Underflow Flag                                           |
|       2      OFC Potential Overflow Flag                                            |
|       1      Unused (0)                                                             |
|       0      IOC Potential invalid operation flag                                   |
+-------------------------------------------------------------------------------------+
```

The exception handler must clear bit31 and bit28.

### FPINST - Floating-Point Instruction Register, Privileged 0xEE000A00 (R/W)
Contains the opcode that has triggered the exception. The Cond field in bit28-31 is changed to 0Eh (Always), and the Fd:D, Fn:N, Fm:M are changed to indicated the fault-location within a vector (with FPEXC.bit8-10 indicating the remaining unprocessed elements of the vector).

### FPINST2 - Floating-Point Instruction Register 2, Privileged UNP (R/W)
If FPEXC.bit28=1, then this register contains another float opcode (that was prefetched, but not yet executed). The Cond field in bit28-31 is changed to 0Eh (Always). The exception handler should handle the failed FPINST opcode, then try to execute prefetched FPINST2 opcode, and then return from exception.

### MVFR0, Media and VFP Feature Register 0, Any 0x11111111 (R)

```
+-------------------------------------------------------------------------------------+
|       31-28  VFP hardware support level when user traps are disabled                |
|              (01h=In MPCore processors when Flush-to-Zero and Default_NaN and       |
|              Round-to-Nearest are all selected in FPSCR, the coprocessor does not   |
|              require support code. Otherwise floating-point support code is         |
|              required)                                                              |
|       27-24  Support for short vectors           (01h=Yes)                          |
|       23-20  Support for hardware square root    (01h=Yes)                          |
|       19-16  Support for hardware divide         (01h=Yes)                          |
|       15-12  Support for software/user traps     (01h=Yes/support code is required) |
|       11-8   Support for double precision VFP    (01h=Yes, v2)                      |
|       7-4    Support for single precision VFP    (01h=Yes, v2)                      |
|       3-0    Support for the media register bank (01h=Yes/support 16, 64bit regs)   |
+-------------------------------------------------------------------------------------+
```


### MVFR1 - Media and VFP Feature Register 1, Any 0x00000000 (R)

```
+------------------------------------------------------------------------------------+
|       31-28  Reserved                                                              |
|       11-8   Support for media extension, single precision floating-point (00h=No) |
|       7-4    Support for media extension, integer instructions            (00h=No) |
|       3-0    Support for media extension, load/store instructions         (00h=No) |
+------------------------------------------------------------------------------------+
```




