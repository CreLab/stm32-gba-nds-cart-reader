# ARM CPU Reference


**General ARM7TDMI Information**
- [ARM CPU Overview](./tmp/armcpuoverview.md)
- [ARM CPU Register Set](./tmp/armcpuregisterset.md)
- [ARM CPU Flags & Condition Field(./armcpuflagsconditionfieldcond.md)
- [ARM CPU 26bit Memory Interface](./tmp/armcpu26bitmemoryinterface.md)
- [ARM CPU Exceptions](./tmp/armcpuexceptions.md)
- [ARM CPU Memory Alignments](./tmp/armcpumemoryalignments.md)

**ARM 32bit Instruction Set (ARM Code)**
- [ARM Instruction Summary](./tmp/arminstructionsummary.md)
- [ARM Opcodes: Branch and Branch with Link (B, BL, BX, BLX, SWI,BKPT)](./tmp/armopcodesbranchandbranchwithlinkbblbxblxswibkpt.md)
- [ARM Opcodes: Data Processing (./armopcodesdataprocessingalu.md)
- [ARM Opcodes: Multiply and Multiply-Accumulate (MUL,MLA)](./tmp/armopcodesmultiplyandmultiplyaccumulatemulmla.md)
- [ARM Opcodes: Special ARM9 Instructions (CLZ,QADD/QSUB)](./tmp/armopcodesspecialarm9instructionsclzqaddqsub.md)
- [ARM Opcodes: Special ARM11 Instructions(./armopcodesspecialarm11instructionsmisc.md)
- [ARM Opcodes: Special ARM11 Instructions(./armopcodesspecialarm11instructionssimd.md)
- [ARM Opcodes: PSR Transfer (./armopcodespsrtransfermrsmsr.md)
- [ARM Opcodes: Memory: Single Data Transfer (LDR, STR,PLD)](./tmp/armopcodesmemorysingledatatransferldrstrpld.md)
- [ARM Opcodes: Memory: Halfword, Doubleword, and Signed DataTransfer](./tmp/armopcodesmemoryhalfworddoublewordandsigneddatatransfer.md)
- [ARM Opcodes: Memory: Block Data Transfer (LDM,STM)](./tmp/armopcodesmemoryblockdatatransferldmstm.md)
- [ARM Opcodes: Memory: Single Data Swap(./armopcodesmemorysingledataswapswp.md)
- [ARM Opcodes: Coprocessor Instructions (MRC/MCR, LDC/STC, CDP,MCRR/MRRC)](./tmp/armopcodescoprocessorinstructionsmrcmcrldcstccdpmcrrmrrc.md)

**ARM 16bit Instruction Set (THUMB Code)**
When operating in THUMB state, cut-down 16bit opcodes are used.
THUMB is supported on T-variants of ARMv4 and up, ie. ARMv4T, ARMv5T,
etc.
- [THUMB Instruction Summary](./tmp/thumbinstructionsummary.md)
- [THUMB Opcodes: Register Operations (ALU,BX)](./tmp/thumbopcodesregisteroperationsalubx.md)
- [THUMB Opcodes: Memory Load/Store(./thumbopcodesmemoryloadstoreldrstr.md)
- [THUMB Opcodes: Memory Addressing (ADDPC/SP)](./tmp/thumbopcodesmemoryaddressingaddpcsp.md)
- [THUMB Opcodes: Memory Multiple Load/Store (PUSH/POP andLDM/STM)](./tmp/thumbopcodesmemorymultipleloadstorepushpopandldmstm.md)
- [THUMB Opcodes: Jumps and Calls](./tmp/thumbopcodesjumpsandcalls.md)
- [THUMB Opcodes: New THUMB Opcodes inARM11](./tmp/thumbopcodesnewthumbopcodesinarm11.md)

**Note**
Switching between ARM and THUMB state can be done by using the Branch
and Exchange (BX) instruction.

**Further Information**
- [ARM Classic vs UAL Syntax (Unified AssemblerLanguage)](./tmp/armclassicvsualsyntaxunifiedassemblerlanguage.md)
- [ARM Pseudo Instructions andDirectives](./tmp/armpseudoinstructionsanddirectives.md)
- [ARM CP15 System Control Coprocessor](./tmp/armcp15systemcontrolcoprocessor.md)
- [ARM Vector Floating-point Unit (./armvectorfloatingpointunitvfp.md)
- [ARM CPU Instruction Cycle Times](./tmp/armcpuinstructioncycletimes.md)
- [ARM CPU Versions](./tmp/armcpuversions.md)
- [ARM CPU Data Sheet](./tmp/armcpudatasheet.md)



