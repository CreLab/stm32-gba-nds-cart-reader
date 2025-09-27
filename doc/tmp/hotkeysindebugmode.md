# Hotkeys in Debug Mode


Most debug functions are available via hotkeys and via mouse accessible popup boxes. The popup boxes generally also show the corresponding hotkey.


```
+-------------------------------------------------------------------------------------+
|      Cursor             (*) Move around                                             |
|      Cursor Right           Follow (in codewin: map window to jump/call dest adr)   |
|      Cursor Right           Follow (in stckwin: map codewin to return adr)          |
|      Cursor Left            Undo follow (if nothing to undo: goto program counter)  |
|      Page Up/Down       (*) Move around                                             |
|      Home               (*) Goto Start or to 0000                                   |
|      End                (*) Goto End or to IO-Area (FF40 codewin, FF10 datawin)     |
|      Ret                (*) Center/Uncenter current line in code window             |
|      Shift+Cursor           Change Active Window (Code,Data,Stck,Regs)              |
|      Shift+Cursor       (*) Toggle between Hex- and Ascii-input in data window      |
|      Tab                (*) Toggle Standard and Symbolic Display in code window     |
|      Tab                (*) Toggle Lower Window (Data or Break/Watch)               |
|      Ctrl-B                 Enter Breakpoint Address, Condition                     |
|      Ctrl-N                 Find Next Breakpoint                                    |
|      Ctrl-G                 Goto Address (prompts for address) (does not affect pc) |
|      Ctrl-E             (*) Toggle Warnings on/off                                  |
|      Ctrl-O                 OS Shell (calls DOS, type 'exit' to come back)          |
|      Ctrl-I                 Inspect (Define Watchpoint address)                     |
|      Ctrl-R                 Reload Cartridge                                        |
|      Ctrl-S                 Search (see below! this works a bit strange)            |
|      Ctrl-C                 Continue Search                                         |
|      Ctrl-D                 Toggle Datazone (see below)                             |
|      Ctrl-A/T/X         (*) Add/Toggle/Remove Machine (up to 12 gameboys at 1 time) |
|      Ctrl-L/W               Load/Save Snapshot (RAM, CPU-state and ROM-cartname)    |
|      Ctrl-Left/Right    (*) Decrease/Increase start address of window by one byte   |
|      <..>                   Assemble into Memory (input box appears on 1st char)    |
|      F1                     Help                                                    |
|      F2                     Toggle Breakpoint at cursor                             |
|      F3                     Trace with calls executed                               |
|      F4                     Run to Cursor                                           |
|      F5                     VRAM Viewer (last accessed screen, TAB toggles)         |
|      F6                     Jump to Cursor (sets programcounter (pc) and rombank)   |
|      F7                     Trace (Execute one instruction)                         |
|      F8                     Run until current sub-routine returns                   |
|      F9                     Run (until breakpoint or user break)                    |
|      F10                    Hardware Info Screen (splits in 50 lines DOS mode)      |
|      F11                    Setup Screen (last accessed setup window)               |
|      F12                    Cartridge Menu (last accessed, filename or files.lst)   |
|      Scroll Lock            Toggle Datacur follows Codecur (or 16bit reg) on/off    |
|      Keypad "/"             Run one Frame                                           |
|      Keypad "*"             Reset and Run                                           |
|      Keypad "-"         (*) Continue Run (same as F9)                               |
|      ESC                (*) Popup File Menu or close current window/menu            |
|      Alt+<..>           (*) Popup Menus (eg. Alt+F for File Menu)                   |
|      Alt+A                  Animate (Repeated trace until key pressed)              |
|      Alt+B                  Place Bookmark                                          |
|      Alt+E                  Edit File                                               |
|      Alt+P                  Profiler Window                                         |
|      Alt+X                  Exit No$gba                                             |
|      Right Mouse Button (*) DOS: Continue Run (same as F9), Windows: Context Menu   |
|      Left Mouse Button  (*) Select Window, Place Cursor, Toggle Breakpoint or       |
|                              CPU-flag, Open Popup Menu, Click Option, etc.          |
+-------------------------------------------------------------------------------------+
```


The functions that are marked by (\*) are not shown in the popup menues of the menu bar. Vice versa, not all functions can be accessed through hotkeys, so to be able to access all functions you must use both hotkeys and menu bars.

See also:
- [Hotkeys in Emulation Mode](./hotkeysinemulationmode.md)



