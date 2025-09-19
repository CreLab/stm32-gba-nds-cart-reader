# Profiler Window


The Profiler Window (Alt+P key in debug mode) displays execution time and number of calls of all executed procedures. The window is split into Tree, Path, and List tabs. Double-clicking an item in a tab moves the debuggers code window to the selected procedure.

### Profiler Tree Tab
Displays all executed procedures with number of calls and execution time, presented as tree view; sub-routines show up as child branches. Useful to find out which procedures have been called how long and at which location(s).

### Profiler Path Tab
Displays the current branch of the profiler tree - including any (nested) interrupt branch(es), the currently executed procedure shows up at the bottom. The path is similar to all return addresses on the various isr/irq/svc stacks (and in the LR register) being merged into a single \"stack\".

### Profiler List Tab
Displays all executed procedures, the number of calls, and execution time in separate columns. The table can be sorted by clicking on the column headers.

### Clock Cycle Values
The clock cycles can be optionally shown as total number of cycles (since the game was started, or the profiler list has been cleared), or as medium number of cycles per call, or as medium number of cycles per second (the GBA runs at 16,777,216 cycles per second).
Also, clock cycles can be either shown with or without cycles being spent in sub-routines (optionally including or excluding cycles in Halt/IntrWait sub-routines).

### IRQs and DMAs
By default, IRQs and sound/video DMAs are shown as root entries in tree. If desired, the setup allows to change the profiler mode to count all IRQs/DMAs as \"sub-routines\". IRQs/DMAs which will then show up everywhere in the tree where they have occurred. Also, IRQs/DMAs clock cycles are then counted as normal sub-routine time to the interrupted \"parent\" procedures.
Note: DMAs that are directly started by the CPU (by start immediately timing) are always shown as local \"sub-routines\".

For more information on how to use the profiler, and how to avoid possible problems, please also read the next chapter,
- [Profiler Compatibility](./profilercompatibility.md)



