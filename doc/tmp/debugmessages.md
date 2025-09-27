# Debug Messages


Debug Messages can be defined in source code. When the emulator \'executes\' a message opcode, the message text will be output to the debug message window and to file DEBUGMSG.TXT. Debug Messages will not disturb execution on real hardware (the branch opcode just skips the data definition, wastes a few clock cycles though).

### User Defined Messages
The message definition format (in THUMB or ARM mode) is as follows:

```
+--------------------------------------------------------------------------------+
|        mov  r12,r12          ;first ID                                         |
|        b    @@continue       ;branch opcode that skips the message data        |
|        dcw  6464h            ;second ID (ascii 'dd')                           |
|        dcw  0                ;reserved for flags                               |
|        dcb  'Hello'          ;user defined ascii data (max length 120 bytes)   |
|        dcb  0                ;ending zero (normally not required, see below)   |
|       .align 4               ;align following code (use align 2 in thumb mode) |
|       @@continue:                                                              |
+--------------------------------------------------------------------------------+
```

The text field is terminated by a zero byte or by the branch destination. The zero byte must be separately defined ONLY if your assembler doesn\'t zero-pad alignment space.

The ascii string may contain parameters, defined as %param%.

```
+-------------------------------------------------------------------------------------+
|       r0,r1,r2,...,r15  show register content (displayed as 32bit Hex number)       |
|       sp,lr,pc          alias for r13,r14,r15                                       |
|       scanline          show current scanline number                                |
|       frame             show total number of frames since coldboot                  |
|       totalclks         show total number of clock cycles since coldboot            |
|       lastclks          show number of cycles since previous lastclks (or zeroclks) |
|       zeroclks          resets the 'lastclks' counter                               |
+-------------------------------------------------------------------------------------+
```


In the no\$gba built-in A22i assembler, messages may be defined as:

```
+-----------------------------------------------------------------------+
|       .msg 'Hello'                                                    |
|       .msg 'Source Addr = %r0% ; Dest Addr = %r1% ; Length = %r2%'    |
|       .msg 'Stack Pointer = %SP%'                                     |
|       .msg 'Decompression time: %lastclks% cycles'                    |
+-----------------------------------------------------------------------+
```

Messages could be defined as macros when using other assemblers. The %parameters% are stored in ascii format as-is. The assembler/macro does NOT need to interprete and/or adjust the parameters!

### See also
Aside from use \"mov r12,r12\", debug messages can be also output via pseudo I/O ports:
- [DS Debug Registers (Emulator/Devkits)](./dsdebugregistersemulatordevkits.md)

### 3D Log and Wifi Log
Additionally to the User messages, no\$gba can also log 3D commands and Wifi packets in the debug message window. The separate message types can be enabled/disabled by checkboxes in the menubar of the window.



