# DSi SD/MMC Bootloader


### Stages

```
+---------------------------------------------------------------------------+
|       Stage 1: Load Stage 2 from NAND Boot Sectors (via code in BIOS ROM) |
|       Stage 2: Load Stage 3 from NAND Filesystem                          |
|       Stage 3: Contains GUI and allows to boot Cartridges or NAND files   |
+---------------------------------------------------------------------------+
```


### Stage 1
The first stage of the DSi\'s bootloader lives in ROM, presumably on the CPU die. It loads further encrypted (and probably signed) stages from NAND flash, starting with a (partially unencrypted) offset table in the sector at 0x200.
Not much is known about this bootloader yet, but it presumably knows how to:

```
+-------------------------------------------------------------------------------------+
|       Initialize the encryption hardware                                            |
|       Read the contents of NVRAM                                                    |
|       Initialize both LCDs                                                          |
|       Read blocks (but not files) from the NAND flash                               |
|       Perform some variety of integrity check on all data it reads(signature,CRC,?) |
|       Display basic hexadecimal error codes                                         |
|       Possibly factory-programming the NAND flash?                                  |
|       Might also do basic power-on self test of peripherals                         |
+-------------------------------------------------------------------------------------+
```

When the Stage 1 bootloader (in ROM) fails, it displays a 32-bit hexadecimal number on the top screen, known Stage 1 error codes are:

```
+----------------------------------------------------------------------------------+
|       Error Code Description                                                     |
|       0000FE00   Error communicating NAND chip (It's missing, CLK shorted, etc.) |
|       0000FEFC   Integrity error in first block of Stage 2 (address at 220h)     |
|       0000FEFD   Integrity error in second block of Stage 2 (address at 230h)    |
|       0000FEFE   Boot sector integrity error (Sector 200h not valid), or error   |
|                    in NVRAM contents.                                            |
+----------------------------------------------------------------------------------+
```


### Stage 2
Unlike the stage1 bootloader, which must be small enough to fit in ROM (probably several kilobytes), the stage2 bootloader has about a megabyte of NAND flash reserved for it. The stage2 bootloader understands partitions and filesystems, and it is capable of loading the DSi menu. It also must understand the encryption used on filesystem blocks in the NAND, and it must understand how to load and validate title metadata.
The Stage 2 loader was not modified by the System Menu 1.4 update. This is still earlier in the boot process than the \"Health and Safety\" warning.
The first stage bootloader reads sector 0x200 in order to find a table of offsets to the Stage 2 bootloader:

```
+-------------------------------------------------------------------------------------+
|       00000220  00 08 00 00 10 64 02 00  00 80 7b 03 00 66 02 00 |.....d....{..f..| |
|       00000230  00 6e 02 00 88 75 02 00  00 80 7b 03 00 76 02 00 |.n...u....{..v..| |
|       00000240  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00 |................| |
+-------------------------------------------------------------------------------------+
```

This appears to be describing two chunks of the stage2 loader, one 0x26410 bytes in length at address 0x800, and one 0x27588 bytes at address 0x26e00.
Note that this sector (and two similar ones at 0x400 and 0x600) appear to be the only unencrypted blocks on the NAND flash.
It is unclear why there are two pieces which are nearly but not quite the same size. Passive traces of the boot sequence confirm that the 0x26e00 chunk is slightly larger, and it\'s loaded first. The 0x800 chunk is read immediately after the 0x26e00 chunk.
Whereas the filesystem data in NAND is encrypted using a unique key for every DSi, the stage2 bootloader is identical on every DSi tested so far. This probably means that it is encrypted using a fixed key included in stage1.

### After Stage 2 is loaded:

```
+-----------------------------------------------------------------------------------+
|       1. The NAND flash is partially re-initialized                               |
|       2. Sector 0 is read from the NAND. Appears to be (encrypted) DOS-style MBR. |
|       3. The MBR signature and the type of the first partition are verified.      |
|       4. Filesystem metadata is read from sectors starting around 0x100000. The   |
|            metadata appears to be in FAT format with long filenames.              |
|       5. Multiple files are loaded from the filesystem. The exact read addresses  |
|            will vary depending on your DSi's firmware version and the state of    |
|            its filesystem when you performed the last firmware update. On a brand |
|            new DSi, it appears that the DSi Menu itself is loaded from 0xb20000   |
|            after two small metadata files are read from 0xb1c000 and 0x7a0000.    |
+-----------------------------------------------------------------------------------+
```


All Stage 2 errors show before the health and safety screen. It appears that Stage 2 errors from a cold power-on always cause the DSi to hang at a black screen, whereas Stage 2 errors after reset (pressing but not holding the power button) will give an error message screen. Known Stage 2 errors:

```
+---------------------------------------------------------------------------+
|       Text                    Description                                 |
|       "Error: 1-2435-8325"    Invalid signature or partition type in MBR, |
|                                 invalid starting LBA.                     |
|       "Error: 2-2435-8325"    Error reading fat/sectors from eMMC         |
|       "Error: 3-2435-8325"    DSi Menu integrity checks failed            |
+---------------------------------------------------------------------------+
```


### Boot Sectors in DSi Debug version
Debug version bootsectors are almost same as in retail version: There\'s an extra RSA key inserted at ARM9:37CEADCh, and lots of B/BL/BLX/LDR addresses have changed due to the inserted bytes, but, apart from that changes, only 5 opcodes are really different, ARM9:37C07A0h, ARM9:37C0864h, ARM7:37B9110h, ARM7:37B9200h do trigger errors when SCFG_DEBUG bit0-1 are zero (opposite of retail version), and ARM9:37B8BA4h uses the extra RSA key at 37CEADCh for Debug Launcher (instead of the retail key at 1FFC400h).



