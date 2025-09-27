# Pocketstation Emulation


The Sony Pocketstation is a memory card with ARM processor and 32x32 pixel LCD screen for Sony Playstation consoles. As such, it doesn\'t have much to do with GBA/NDS.
Anyways, as I haven\'t got around to implement ARM emulation in no\$psx yet, the Pocketstation is currently emulated as part of the no\$gba project (eventually it might be moving from no\$gba to no\$psx someday in future).

### Pocketstation BIOS
For using a copy of the original 16Kbyte BIOS: store it as file POCKSTAT.ROM in no\$gba directory. If that file isn\'t present, then no\$gba will use it\'s own built-in BIOS clone.

### Pocketstation Specs
For tech info on memory map, I/O ports, bios, file formats, see:

```
+-----------------------------------------------------------------------+
|       http://problemkaputt.de/psx-spx.htm#pocketstation               |
+-----------------------------------------------------------------------+
```

For info on the ARM processor, see:
- [ARM CPU Reference](./armcpureference.md)



