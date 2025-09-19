# Profiler Compatibility


The no\$gba profiling mechanism allows the parent routines to include/exclude cycles being spent in sub-routines, and other useful effects like the tree tab which would be impossible with other less advanced profiling mechanisms.

### How it works\...
During emulation, the no\$gba profiler keeps track of the program flow by watching any opcodes which change the program counter. It relies on identifying \"call\" and \"return\" opcodes used to enter/leave each procedure, and to ignore other \"jump\" opcodes used loop/skip inside of a procedure.
Sounds simple, but has been relative difficult to implement because the ARM CPU doesn\'t actually have clearly defined \"call/return/jump\" opcodes. Instead, it uses various branch (and load, pop, add, mov) opcodes to do various kinds of jumps to - or from - or inside of procedures (for example, the BX opcode is used for all three purposes).

### Flexibility and possible problems
The profiler should be meanwhile quite flexible and should work with most programs. If it doesn\'t work, then it is probably only because of a few procedures which use unconvential program code. In that case it should be no big deal to solve the problem, either by changing that procedures, or by supporting it in no\$gba. Either way, please let me know of \<any\> problems, and of which opcodes you are using to enter/leave the procedures, and if can solve it yourself by changing the code, or if you need the code to be supported in next no\$gba update!

### Re-synchronization
The profiler may shortly lose track of the program flow if it has overseen a return opcode from a child procedure to its parent. It will then assume that it is still executing the child (and any further cycles and sub-routines will be incorrectly counted to the child).
However, the profiler will re-synchronize itself to program flow once when it locates a return opcode which jumps to a higher parent procedure, the child routine which didn\'t have a return opcode will be then shown with a \"(?)\" question mark in the tree/list tabs.

Below is a summary of currently supported call/ret opcodes and opcode-combinations, useful to identify and report problems, or eventually to solve the problem by making your code compatible with it.

### Calls - Entering a sub-routine
Sub-routines are most conventionally entered by a \"bl addr\" opcode. Calls with thumb/arm mode switches & indirect calls can be implemented by groups of two opcodes. In ARM mode, that\'d be a \"mov lr,pc\" or a \"add lr,=retadr\" opcode, followed by a \"bx rd\" or \"ldr pc,\[jumplist\]\" opcode. Also, in ARM and THUMB mode, it can be implemented by a \"bl addr\" opcode which is pointing to a \"bx rd\" opcode. And, of course, IRQs and SWIs are as well supported.

### Returns - Leaving a sub-routine
Standard returns would be \"bx lr\" or \"mov pc,lr\" or \"pop pc\" opcodes (aka \"ldmfd \[r13\]!,pc\" aka \"ldr pc,\[sp\],4\"). Also, any \"bx rd\" may be used for returns with thumb/arm mode switch (eg. after a thumb \"pop rd\"), or if the return address was moved to rd register (instead of saving it on stack). Note: The profiler identifies \"bx rd\" as return opcode if the current procedure (or any parent procdures) have been called with the same return address as the value in \"rd\". Finally, IRQs and SWIs may return by \"subs/movs pc\".

### Jumps - Inside of procedures
All other jump opcodes are normally treated as normal jumps without affecting the profiler (unless a return address has been previously written into LR).
CAUTION: Because the normal thumb mode \"b\" opcode (branch) has relative short range, some programs may use the \"bl\" opcode (branch long with link) to produce long jumps (with the link register value being ignored/destroyed). The profiler currently treats all \"bl\" opcodes to be used to enter a sub-routine, not as long jump! Please let me know if that is a problem with your code!

### LR - Link Register (R14)
Please always have the return address stored in LR when calling a procedure. And please avoid to use LR (R14) for other purposes, ie. if possible, use only R0-R12 as general purpose data registers.

### Multitasking
The profiler memory is organized similar as a stack, and it should be actually running synchronous to the return addresses on the CPU stack. That means that it\'d be currently not working with any \'multitasking\' programs, ie. programs that switch between different threads, each with a separate stack.
Please let me know if you are doing any such things! I\'d love to support it - if anybody wants it. The feature would probably work automatically (without you having anything much more to do than to say \"hello, I use multitasking, what I am doing is\...\"), and it would nicely display each thread as separate root entry in the tree tab, allowing to determine time being spent in each thread (and its sub-routines) very easily\...



