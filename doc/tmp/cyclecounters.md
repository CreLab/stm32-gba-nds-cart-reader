# Cycle Counters


### Execution Time value in Statusbar
No\$gba displays the clock cycles difference between start and stop time in status bar when the emulation gets stopped. For example, hitting F3-key to execute a \"BL draw_frame\" opcode would display the execution time of the \"draw_frame\" procedure.
Note: That would also include any interrupts or DMAs which may have been occurred while executing that procedure.

### User Counter
The user counter (located in Timers page of I/O map window) is incremented during emulation execution and tracing, the counter can be easily reset to zero by pushing the reset button which is displayed next to it.

### Debug Message Counters
The Debug Message feature includes some special operands (%totalclks%, %lastclks%) which allow to write cycle counts to debug message window (or into log file). See Debug Messages chapter for details.

### CPU Load Indicator
The \"Power Gauge\" (the red-green bar in debug window) displays the used CPU time (assuming that the unused CPU time is properly spent in Halt or IntrWait state, which reduces battery power consumption on real hardware). The higher it gets, the more CPU time is used.
By default, CPU load is re-calculated once per frame (60Hz), this rate can be changed in \"Other\" setup options (useful to prevent flickering with game engines that update the picture only once every two or three frames).
Note: The same information is also displayed as decimal value, in steps of 0.1%, in the Timers page of the I/O map window.

NB. Cycle counters are 32bit values and will overflow (restart at zero) after 4G cycles (256 seconds), which is probably more than enough in most cases.



