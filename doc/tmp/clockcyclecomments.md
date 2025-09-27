# Clock Cycle Comments


The normal execution time for one GBA opcode ranges between 1 and 100 (!) clock cycles, or more. Unfortunately, opcode execution time depends on various of circumstances (bus widths, waitstates, etc.), which is making it rather difficult to count cycles by hand, or just to a get feeling for efficient GBA code.

The no\$gba Clock Cycle Comments feature displays the execution time for each opcode in disassembler window. Four different view modes (selectable in setup) are available:

### Short Formula, and Detailed Formula
Short Formula: Displays the Non-sequential, Sequential, and Internal cycles (eg. 2N+3S+1I). Detailed Formula: Splits the N and S cycles into code and data access (eg. 1N+1S+1ND+2SD+1I, N/S for code, ND/SD for data).

### Cycles, and Cycles & Sum
Cycles: Displays the number of clock cycles (by resolving the above formula - recursing operand size, opcode and data addresses, and current waitstate configuration). Cycles & Sum: Additionally displays the sum of all opcodes on screen in a second column (to use that feature, simply scroll the first line of interest to topmost screen position).

Even though these features are making it much easier to count cycles, there are still some restrictions which should be kept in mind:

### Data access (load/store opcodes) - Important
Cycles are resolved by current register settings. For example, the execution time for \"LDR Rd,\[Rb\]\" could be resolved correctly only if Rb is currently pointing to the same memory area as when executing that opcode (that is valid if the program counter points to the opcode, for stack accesses by r13 register it\'d be usually always valid).

### Prefetch
Game-Pak Prefetch isn\'t yet understood or supported. If it is enabled in WAITCNT register, access to cartridge ROM may take up less cycles as displayed in clock cycle comments.

### Conditional Opcodes
Conditional opcodes are always assumed to be true (unless if the program counter points to the opcode, in that case the actual execution time is displayed, ie. 1S if the condition is false).

### Sums
The Cycles & Sums features simply adds one execution time to another, useful for fragments of code, but of course not aware of loops or skips.

### Jumps
Execution time for branch opcodes is incorrectly displayed by using local waitstates for local code area (rather than target area). However, intersegment jumps (from one memory area to another) are typically consisting of a call-return combination (ie. the overall execution time would be correct, but the execution times of the call and return opcodes would be exchanged).

### VRAM Waitstates
VRAM Waitstates are not displayed (the real hardware would occasionally add 1 cycle for accesses to video memory).



