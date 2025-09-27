# DS Cartridge PassMe/PassThrough


PassMe is an adapter connected between the DS and an original NDS cartridge, used to boot unencrypted code from a flash cartridge in the GBA slot, it replaces the following entries in the original NDS cartridge header:

```
+----------------------------------------------------------------------------------+
|       Addr  Siz Patch                                                            |
|       004h  4   E59FF018h  ;opcode LDR PC,[027FFE24h] at 27FFE04h                |
|       01Fh  1   04h        ;set autostart bit                                    |
|       022h  1   01h        ;set ARM9 rom offset to nn01nnnnh (above secure area) |
|       024h  4   027FFE04h  ;patch ARM9 entry address to endless loop             |
|       034h  4   080000C0h  ;patch ARM7 entry address in GBA slot                 |
|       15Eh  2   nnnnh      ;adjust header crc16                                  |
+----------------------------------------------------------------------------------+
```

After having verified the encrypted chip IDs (from the original cartridge), the console thinks that it has successfully loaded a NDS cartridge, and then jumps to the (patched) entrypoints.

### GBA Flashcard Format
Although the original PassMe requires only the entrypoint, PassMe programs should additionally contain one (or both) of the ID values below, allowing firmware patches to identify & start PassMe games without real PassMe hardware.

```
+-----------------------------------------------------------------------+
|       0A0h  GBA-style Title    ("DSBooter")                           |
|       0ACh  GBA-style Gamecode ("PASS")                               |
|       0C0h  ARM7 Entrypoint    (32bit ARM code)                       |
+-----------------------------------------------------------------------+
```

Of course, that applies only to early homebrew programs, newer games should use normal NDS cartridge headers.

### ARM9 Entrypoint
The GBA-slot access rights in the EXMEMCNT register are initially assigned to the ARM7 CPU, so the ARM9 cannot boot from the flashcard, instead it is switched into an endless loop in Main RAM (which contains a copy of the cartridge header at 27FFE00h and up). The ARM7 must thus copy ARM9 code to Main RAM, and then set the ARM9 entry address by writing to \[027FFE24h\].



