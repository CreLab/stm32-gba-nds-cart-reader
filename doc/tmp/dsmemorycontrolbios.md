# DS Memory Control - BIOS


### 4000308h - NDS7 - BIOSPROT - Bios-data-read-protection address
Used to double-protect the first some KBytes of the NDS7 BIOS. The BIOS is split into two protection regions, one always active, one controlled by the BIOSPROT register. The overall idea is that only the BIOS can read from itself, any other attempts to read from that regions return FFh-bytes.

```
+-------------------------------------------------------------------------------------+
|       Opcodes at...      Can read from      Expl.                                   |
|       0..[BIOSPROT]-1    0..3FFFh           Double-protected (when BIOSPROT is set) |
|       [BIOSPROT]..3FFFh  [BIOSPROT]..3FFFh  Normal-protected (always active)        |
+-------------------------------------------------------------------------------------+
```

The initial BIOSPROT setting on power-up is zero (disabled). Before starting the cartridge, the BIOS boot code sets the register to 1204h (actually 1205h, but the mis-aligned low-bit is ignored). Once when initialized, further writes to the register are ignored.

The double-protected region contains the exception vectors, some bytes of code, and the cartridge KEY1 encryption seed (about 4KBytes). As far as I know, it is impossible to unlock the memory once when it is locked, however, with some trickery, it is possible execute code before it gets locked. Also, the two THUMB opcodes at 05ECh can be used to read all memory at 0..3FFFh,

```
+-----------------------------------------------------------------------------------+
|       05ECh  ldrb r3,[r3,12h]      ;requires incoming r3=src-12h                  |
|       05EEh  pop  r2,r4,r6,r7,r15  ;requires dummy values & THUMB retadr on stack |
+-----------------------------------------------------------------------------------+
```

Additionally most BIOS functions (eg. CpuSet), include a software-based protection which rejects source addresses in the BIOS area (the only exception is GetCRC16, though it still cannot bypass the BIOSPROT setting).

### Note
The NDS9 BIOS doesn\'t include any software or hardware based read protection.



