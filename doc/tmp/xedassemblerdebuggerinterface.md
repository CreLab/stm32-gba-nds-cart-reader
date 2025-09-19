# XED Assembler/Debugger Interface


### Nocash Debuggers
The XED editor provides simple but very useful interaction with the various nocash debuggers/emulators (no\$gba, no\$gmb, no\$cpc, no\$msx, no\$c64, no\$2k6, no\$zx, no\$nes, no\$sns, no\$x51).
The editor can be launched from inside of the debugger (by Alt+E hotkey, by retaining the recently edited line number when re-launching the editor).
And, when editing assembler source code files, F9-key can used to launch the assembler from inside of XED. That is, the file is saved to disk, the A22i assembler is started (built-in in all debuggers), and, in case of successful assembly, the program is loaded & started in the emulator. Otherwise, the assembler displays a list of errors, and the editor is moved directly to the source code line number in which the first error has occured.

### 16bit DOS debuggers
The XED editor is included built-in in all nocash windows debuggers, and in the no\$gba 32bit DOS version only.
For use with other nocash 16bit DOS debuggers the XED editor must be downloaded separately at <http://problemkaputt.de/xed.htm,> and must be installed in a directory which is included in your PATH statement.



