# AUX Mainboard


Other possibly useful signals on the mainboard\...

### FIQ Signal
The FIQ (Fast Interrupt) signal (labeled FIQ on the mainboard) could be used as external interrupt (or debugging break) signal.
Caution: By default, the FIQ input is directly shortcut to VDD35 (+3V or +5V power supply voltage), this can be healed by scratching off the CL1 connection located close to the FIQ pin (FIQ still appears to have an internal pull-up, so that an external resistor is not required).
The GBA BIOS rejects FIQs if using normal ROM cartridge headers (or when no cartridge is inserted). When using a FIQ-compatible ROM header, Fast Interrupts can be then requested by pulling FIQ to ground, either by a push button, or by remote controlled signals.

### RESET Signal
The RESET signal (found on the mainboard) could be used to reset the GBA by pulling the signal to ground for a few microseconds (or longer). The signal can be directly used (it is not shortcut to VDD35, unlike FIQ).
Note: A reset always launches Nintendo\'s time-consuming and annoying boot/logo procedure, so that it\'d be recommend to avoid this \"feature\" when possible.

### Joypad Signals
The 10 direction/button signals are each directly shortcut to ground when pressed, and pulled up high otherwise (unlike 8bit gameboys which used a 2x4 keyboard matrix), it\'d be thus easy to connect a remote keyboard, keypad, joypad, or read-only 12bit parallel port.



