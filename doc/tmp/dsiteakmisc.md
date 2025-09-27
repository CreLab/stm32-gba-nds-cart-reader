# DSi Teak Misc


### Teak Instruction Set References
There aren\'t any official references for the Teak instruction set. However, there\'s one document that has leaked into internet (plus some docs for older Oak instruction set):

```
+---------------------------------------------------------------------------+
|       TeakLite Architecture Specification Revision 4.41 (DSP Group Inc.)  |
|       OakDSPCore Technical Manuals for CWDSP1640 or CWDSP167x (LSI Logic) |
|       OakDSPCore DSP Subsystem AT75C (Atmel)                              |
+---------------------------------------------------------------------------+
```

TeakLite II supports lots of additional opcodes, the only available info has leaked in form of .DLLs which were (apparently by mistake) bundled with a specific RVDS release version:

```
+-------------------------------------------------------------------------------+
|       TeakLite II disassembler dll in RVDS (RealView Developer Suite) 4.0 Pro |
+-------------------------------------------------------------------------------+
```

There\'s no known way to use the RVDS disassembler GUI to decipher Teak binaries. However, Normmatt found a way to get the .DLLs to disassemble code manually (via LoadLibrary and GetProcAddr), which in turn allowed to disassemble all possible 65536 combinations for all opcodes.
BUG: That RVDS tool disassembles \"R0425\" operands to \"r6\" (instead of \"r5\"), that\'s definetely wrong for the old \"movr\" opcode (TeakLite I didn\'t support any \"r6\" register at all), and, when looking at disassembled code, it does also look wrong for newer TL2 opcodes.
Actually, the registers CAN be redefined via ar0/ar1/arp0/arp1/arp2/arp3, so it isn\'t actually a bug.

### Teak MMIO Registers
There aren\'t official docs, but wwylele has discovered a debugger at that contains definitions for most of the MMIO bits:

```
+---------------------------------------------------------------------------------+
|       searching for "teak" in the "search for chip" box on "www.lauterbach.com" |
|       should lead to this file: trace32_ceva-teak_r_2019_02_000108303_win64.zip |
+---------------------------------------------------------------------------------+
```

The zip contains a \"perxteak.per\" file that contains the MMIO bit definitions (in txt format). The definitions for OCEM do accidentally refer to an older version (without 18bit addresses). Definitions for GLUE, ICU, APBP, DMA, CRU, GPIO, and BTDMP are missing (whereof a similar/older ICU variant is defined in \"peroak.per\" in the same zip).

### Teak COFF Files
The DSi Sound utility contains a COFF file called \"aac.a\" (inside of its nitro filesystem), and aside from the binary, the file is also including a COFF symbol table with labels in ASCII format.

### Teak Undefined Opcodes
There are several \"Undefined\" opcodes: Any opcodes that have no instruction assigned in the opcode encoding table (or that are excplicitely assigned as \"undefined\" in the table). Opcodes with invalid parameters (eg. ArArp set to 6..7).
Some opcodes are also having \"Unused\" operand bits; these bits should be usually zero (nonzero would supposedly mirror to the same instruction, but one shouldn\'t do that).
Moreover, there are various special cases saying that certain opcodes may not be used with certain registers, eg. \"addh\" shall not be used with operands Ax,Bx,p (with unknown results when violating that rule).

### Teak Memory
Memory is addressed in 16bit WORD units (not in bytes) with separate Instruction and Data busses. Before starting the Teak, store the Teak program code in New Shared WRAM, and then map that memory to Teak side via MBK registers:
- [DSi New Shared WRAM (for ARM7, ARM9, DSP)](./dsinewsharedwramforarm7arm9dsp.md)
At Teak side, 16bit is the smallest addressable unit (so there\'s no \"byte-order\" on Teak side - however, 16bit values should be stored in little endian format on ARM side).
Confusingly, the \"movpdw\" opcode is doing a 32bit read with two 16bit words ordered in big-endian (and, on ARM side, byte-fractions ordered in little-endian). There are a few more opcodes that can read/write 32bits, with optional address increment/decrement for the 2nd word, so endianness is selectable in that cases; it\'s also common to use the SAME address for both words (probably intended for scaling a 16bit memory value to 32bits).

### Teak Code Memory
TeakLite II supports 18bit program memory addressing (unlike Teak/Oak which supported only 16bit addresses). The 18bits allow to address max 256Kwords (=512Kbytes) of code, whereas, the DSi can map only half that much memory to the DSP (ie. max 256Kbytes code).
Call/Ret are always pushing/popping 32bit return addresses (even when doing \"near\" calls within the same 16bit page).

### Teak Data Memory (RAM and Memory Mapped I/O)
Teak Data Memory is addressed via 16bit address bus (via registers r0..r7), allowing to access max 64Kwords (2Kwords of MMIO, plus 62Kwords of RAM). The memory is divided into three sections (X/Z/Y-spaces), the size/location of that sections can be changed via Port 8114h (in 1Kword units), and alongsides, the MMIO base can be adjusted via Port 811Eh. The default areas are:

```
+----------------------------------------------------------------------------------+
|       0000h..7FFFh  X Space (for RAM, with 1-stage write-buffer)     ;min zero   |
|       8000h..87FFh  Z Space (for Memory-mapped I/O, no write-buffer) ;min zero   |
|       8800h..FFFFh  Y Space (for RAM, with 1-stage write-buffer))    ;min 1Kword |
+----------------------------------------------------------------------------------+
```

Confusingly, the DSi Sound utility is mapping 128Kwords of RAM as Teak Data memory, but it\'s unknown how to access all of that memory. The CPU opcodes, CPU registers, and MMIO registers don\'t seem to allow to access more than 64Kwords of Data. Maybe the extra memory is accessible via DMA, and maybe the CPU\'s \[r7+imm16\] operands might allow to exceed the 64Kbyte range (though they might as well wrap within 64Kbyte range, actually that\'s more likely, especially for \"signed\" immediates).

### Teak Call Conventions (as done in \"aac.a\" from DSi Sound)
Functions are called with up to four parameters in a0,a1,b0,b1 (or a0l, a1l, b0l, b1l when needing only 16bits). Any further parameters are pushed on stack before the function call (and are deallocated via \"rets Imm8\" opcode upon return). Register r7 is often used as stack frame (for accessing pushed incoming parameters & locally allocated variables).
Functions may smash a0, a1, b0, b1. A return value (if any) is stored in a0 (or a0l). All other registers like r0..r7, sv, etc. should be left unchanged (or pushed/popped when needed).

### Teak Speed
Cycles per opcode are defined in the TeakLite document (not covering TeakLite II opcodes though). Most instructions (even Multiply opcodes) can complete in a single clock cycle. The main bottleneck appear to be memory access cycles: Code and Data memory can be accessed in parallel, so the overall rule would be:

```
+-----------------------------------------------------------------------+
|       NumCycles = max(NumberOfOpcodeWords, NumberOfDataReadsWrites)   |
+-----------------------------------------------------------------------+
```

Some exceptions with extra cycles are opcodes that are changing PC, or that do read/write program memory (movd and movp). Opcodes exp, max, maxd, min are having restrictions saying that the result may not be used by the \"following instruction\".
The overall clock speed in the DSi is unknown; some years ago somebody seems to have claimed it to be around 130MHz, but it\'s unclear where that info came from.

```
+------------------------------------------------------------------------------------+
|       Teak actual CPU clock(s) are...                                              |
|       134.055928MHz (aka 134MHz)       <-- for Timer 0, SIO, DMA (no "waitstates") |
|       107.244742MHz (aka 134MHz/1.25)  <-- for Timer 1, CPU    (with "waitstates") |
+------------------------------------------------------------------------------------+
```

The ARM9 can access WRAM at 33MHz, whilst Teak seems to be capable of fetching 16bit opcodes and 16bit data at 107MHz from the same WRAM (apparently without even using a cache).



