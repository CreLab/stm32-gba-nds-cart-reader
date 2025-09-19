# The A22i Assembler


### Online Assembler
In the debuggers code window, you can directly enter assembler instructions and modify the program code. The assembler input box shows up automatically when typing the first character of the new instruction.
The most basic purpose would be to overwrite an opcode by typing \"NOP\", but you could also enter any other instruction, such like \"ADD R0,R0,4\" when having debug info (.sym file) loaded, you may also use labels as parameters, eg. \"B mainloop\". The pseudo opcode \"LDR Rd,=Imm\" can be used only under certain circumstances:
- [Using LDR Rd,=Imm in Online Assembler](./usingldrrdimminonlineassembler.md)
Note: Aside from translating machine code instructions, the assembler input box can be also used to change the value of CPU registers, by typing \"r0=12345678\", or \"sp=3007FF0\" for example. For curiosity, it also parses simple commands such like: run, reload, help, exit, date, etc.

### Source Code Assembler
The assembler can be also used to assemble source code files, by using the Assemble File function in Utility menu. This function has been mostly implemented for my own pleasure, and because I didn\'t wanted to install thirdparty tools on my computer. It\'s having some nice features, but it\'s also lacking some possibly important functions (see below).

### A22i Advantages
It\'s easy to use, very fast, produces ready-for-use debug info .sym files, it understands official ARM syntax, as well as more reasonable cleaned-up syntax, and also different assembler dialects, directives, and numeric formats, it can be used directly from inside of the debugger (and from inside of the editor), and vice-versa: it\'s able call the editor in case of assembly errors.

### A22i Disadvantages
The main disadvantage is that A22i isn\'t supporting macros (yet).

### A22i is a Matter of Taste
If you want to use linkers, make files, project files, header files, command files, resource files, script files, libraries, high level languages, strip commands, object files, and cathode ray tube (crt) files - forget about it!
A22i translates a source code file into a binary file, not more, not less.

For more info about instruction set and directives, see:
- [ARM CPU Reference](./armcpureference.md)
- [ARM Pseudo Instructions and Directives](./armpseudoinstructionsanddirectives.md)

### Sample Code
For a source code example, have a look at the Magic Floor game at the no\$gba webpage, the package includes the binary, source code, with comments, and .sym debug info file.
<http://problemkaputt.de/magicflr.htm>



