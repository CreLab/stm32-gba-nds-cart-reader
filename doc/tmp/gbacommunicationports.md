# GBA Communication Ports


The GBAs Serial Port may be used in various different communication modes. Normal mode may exchange data between two GBAs (or to transfer data from master GBA to several slave GBAs in one-way direction).
Multi-player mode may exchange data between up to four GBAs. UART mode works much like a RS232 interface. JOY Bus mode uses a standardized Nintendo protocol. And General Purpose mode allows to mis-use the \'serial\' port as bi-directional 4bit parallel port.
Note: The Nintendo DS does not include a Serial Port.

- [SIO Normal Mode](./sionormalmode.md)
- [SIO Multi-Player Mode](./siomultiplayermode.md)
- [SIO UART Mode](./siouartmode.md)
- [SIO JOY BUS Mode](./siojoybusmode.md)
- [SIO General-Purpose Mode](./siogeneralpurposemode.md)
- [SIO Control Registers Summary](./siocontrolregisterssummary.md)

### Wireless Adapter
- [GBA Wireless Adapter](./gbawirelessadapter.md)

### Infrared Communication Adapters
Even though early GBA prototypes have been intended to support IR communication, this feature has been removed.
However, Nintendo is apparently considering to provide an external IR adapter (to be connected to the SIO connector, being accessed in General Purpose mode).
Also, it\'d be theoretically possible to include IR ports built-in in game cartridges (as done for some older 8bit/monochrome Hudson games).



