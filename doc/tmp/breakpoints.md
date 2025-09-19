# Breakpoints


### Normal Breaks (F2-key)
Normal breakpoints are set (or removed) by moving the code-window cursor onto the desired opcode, and then pushing the F2-key.

### Run-to-Cursor (F4-key)
Hitting F4-key directly starts emulation, and stops when reaching the code window cursor. The break address is not memorized, ie. it is used only once.

### Global Memory Read/Write Breaks
This break-family allows to capture reads/writes to specific memory addresses, or memory areas. Membreaks are defined by pressing Ctrl+B, and then entering a memory address or area in square brackets,

```
+-----------------------------------------------------------------------+
|       [3007ffc]            single address (eg. GBA IRQ vector)        |
|       [6000000..6003fff]   memory area    (eg. first 16K of VRAM)     |
+-----------------------------------------------------------------------+
```

followed by question and/or exclamation marks, indicating the type,

```
+-----------------------------------------------------------------------+
|       ?     break on any read (from specified address/area)           |
|       !?    break on any read or changed write                        |
|       !!?   break on any read or any write                            |
|       !     break on changed write                                    |
|       !!    break on any write                                        |
+-----------------------------------------------------------------------+
```

Question marks (\"?\") capture reads. Double exclamation marks (\"!!\") will capture ALL writes, single exclamation marks (\"!\") capture only writes that are changing the memory content (ie. the new data must be different than old data). The ordering (eg. \"!!?\" or \"!?!\" or \"?!!\") is don\'t care.

### Local Conditional Breakpoints
Press Ctrl-B and define the break by entering \"address, condition\". The emulator will stop when the program counter reaches the address, and when the condition is true. The \"\$\" symbol represents the current cursor address of code window. Examples:

```
+------------------------------------------------------------------------------------+
|       $, r0<>0           --> break at cursor position if r0 is non-zero            |
|       $, r0 & 2          --> break at cursor position if bit 1 of r0 is set        |
|       $, r0 !& 2         --> break at cursor position if bit 1 of r0 is zero       |
|       8001234, [r1]=r2   --> break at 8001234 if r1 points at a value equal to r2  |
|       wrchr              --> break at wrchr (always, no condition, same as F2-key) |
|       wrchr, r0=0d       --> break at wrchr if r0 contains 0dh                     |
|       $, [4000006] > 0A0 --> break at cursor if VCOUNT is greater than 0A0h        |
|       $, r4 <= r5        --> break at cursor if r4 is less or equal than r5        |
|       $, [r4] <> [r5]    --> break at cursor if r4 points at other value than r5   |
|       mainloop, ..5      --> break every 5th time that pc gets to mainloop (timer) |
+------------------------------------------------------------------------------------+
```

The conditions are verified BEFORE the instruction is executed.

```
+-----------------------------------------------------------------------+
|       Operators:              Operands:          Timer Identifier:    |
|       ==  =   <   >   &       n   [nn]  r        ..                   |
|       !=  <>  <=  >=  !&      nn  [rr]  rr                            |
+-----------------------------------------------------------------------+
```

Operators == and != are pseudonyms for = and \<\>

### Global Conditional Breakpoints
Global breaks are working exactly as above local breaks, except that the condition is verfied after \<each\> executed opcode. In the Ctrl+B window, enter a condition (without specifying a address). Examples:

```
+----------------------------------------------------------------------------+
|       r0 = 0            --> break whenever register r0 becomes zero        |
|       [4000006]>20      --> break whenever VCOUNT becomes greater than 20h |
+----------------------------------------------------------------------------+
```

The emulator stops only when a condition changes from false to true, ie. it does not permanently break after each opcode if the condition stays true for a while.

### The Break Window
The lower left window of the debug screen is shared for Data and Breakpoints, use TAB-key in this window to switch between Data and Break windows. The Break window lists all defined breakpoints, DEL-key can be used to delete a selected breakpoint. When pressing ENTER on a local breakpoint, the code window will be moved to the break address, this works also for bookmarks (that are non-functional \'dummy\' breaks, defined by Alt+B key in code window).

### Source Code Breakpoints
The opcode MOV R11,R11 may be used as source code breakpoint (in both THUMB and ARM state). These breaks are working much like normal F2-key breakpoints, except that they may be defined directly in source code by inserting the above opcode. Because the opcode is not changing any registers or flags there will be no conflicts when testing the binary on real hardware.
Note: Source breaks work only if you have enabled them in no\$gba setup. To remove a specific source break, move the code-window cursor onto it, and hit the DEL-key (or enter NOP in the online assembler).



