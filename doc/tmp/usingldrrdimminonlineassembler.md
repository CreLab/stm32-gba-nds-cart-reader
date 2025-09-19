# Using LDR Rd,=Imm in Online Assembler


LDR{cond} Rd,=Imm is a pseudo opcode, consisting of a LDR Rd,\[PC,disp\] opcode, and a 32bit immediate at \[PC+disp\] in the literal pool. The pool is normally generated when assembling the source code, however, additional pool values can be eventually squeezed into the final binary:

1) If the cursor points to an existing LDR=IMM, then it can be overwritten it by a new LDR=IMM, with changed {cond}, changed Rd, or changed Imm. In the latter case, if the immediates pool entry is shared with other LDR=IMMs, then the value of those opcodes will get changed as well - if you wish to suppress that behaviour: First overwrite the old LDR=IMM by NOP, then overwrite it again by new LDR=IMM, which will then (try to) use below mechanisms\...

2) If the cursor does NOT point to an existing LDR=IMM, then no\$gba will search nearby memory for usable addresses - A) a 32bit value that matches the desired immediate, B) a word-aligned 32bit value containing ascii letters \"fREE\", which you may want to insert here and there in your code, or C) a presumably unused blank memory area of at least 256 bytes which is 00h- or FFh-filled.

3) If the debugged program was written in C or C++ then you can probably replace some of the meaningless opcodes by hand. For example, to load a 16bit immediate with ARM code: MOV Rd,LSB, ADD Rd,MSB.



