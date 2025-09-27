# DS Cart DLDI Driver - Guessed Address-Adjustments


The DLDI installer uses some guessing method for address-adjustments (the FIX_xxx flags are supposed to patch addresses, but not opcodes or other data).

### Unaligned-Word patching and over-shooting bug
The central mistake in the official DLDI installer is that it is patching all words at \[start..end-1\], using 1-byte address increments instead of 4-byte increments. This includes patching words at non-word aligned locations, or patching words whose lower bytes were already patched, and over-shooting to words at \[end-1..end+2\].

### ddmem Base BF800000h
Most or all .dldi files are using ddmem base BF800000h (defined in dldi.ld). That value was chosen because it won\'t conflict with opcodes (as NDS BIOS doesn\'t use SWI function 80h, BF80xxxxh would be an invalid SWI function in ARM; and BF80h would be an invalid opcode in THUMB).
So far, this would have worked well, but it doesn\'t work with unaligned-word patching bug (eg. THUMB opcodes 8000h,BF00h, or ARM opcodes xxBF80xxh or the like). And, even if it would have worked for opcodes - it might still fail for data values.

### FIX_GOT
GOT does usually contain BF80xxxxh address pointers (plus some 00000000h words). The guessing works quite stable (the maximum for 32K files is xxxxh=7FFFh, so there\'s no risk to encounter xxxx=BF80h) (one could encounter xxxxh=xxBFh, but the previously patched word is usually in RAM area, eg. 02xxxxxxh, so this would form BF02h, without risk to be seen as BF80h).
BUG: The GOT table is usually located at the end of the .dldi file, meaning that the over-shooting bug will see three uninitialized bytes at \[got_end+0..2\], and may go amok if they are BF80xxh or xxBF80h. The value of those bytes depends on left-over from previously installed .dldi driver(s) and on the ddmem base used in the .nds file, so the bug may take place randomly depending on several factors.

### FIX_GLUE
GLUE does usually contain a handful of opcodes and .pool values for switching between ARM and THUMB code. The intention is to patch the addresses in the .pool, and to leave the opcodes intact. This can be potentially stable, assuming that the used opcodes in the GLUE (and the next three bytes after glue_end) usually won\'t contain BF80h).

### FIX_ALL
This is the mother of all bugs. Fortunately there aren\'t any .dldi drivers with FIX_ALL flag - and one should never make drivers that do use it.
ALL is covering the whole dldi space, including the 80h-byte DLDI header, the code area, including GLUE area, and GOT area, and probably also the yet uninitialized BSS area, and the next three bytes after end_all.
Patching the whole code area means an increased risk to hit opcodes or data values that contain BF80h. The over-shooting bug may even destroy the next three bytes after the 32Kbyte area.
Patching the DLDI header could destroy the header itself, the header in the .dldi file usually won\'t contain BF80h at unintended locations, however, the pointers in that header are adjusted before applying FIX_ALL, for example, RAM base 0200BF00h (in .nds file) combined with a function at BF800080h (in .dldi file) would result in 0200BF80h. The nasty thing is that the problem won\'t occur with other RAM base values (in other .nds files).

### Avoiding the bugs
When making .dldi drivers: Never use FIX_ALL. And preferably avoid FIX_GOT and FIX_GLUE as well (ARM CPU can do relative jumps and relative addressing, eg. via ADR and ADRL pseudo opcodes, so there\'s no point in needing address adjustments). Or otherwise append padding after GOT area, and try to avoid using opcodes/data with BF80h in/after GLUE area.
When making dldi installers: Best patch only word-aligned words (ARM CPU can\'t access unaligned data, so there\'s little chance that DLDI drivers would ever contain unaligned words). Or, when maintaining unaligned patching: At the very least skip the 80h-byte header on FIX_ALL, and after patching a word at other locations, skip the next three bytes, and don\'t do the over-shooting at end.
When making .nds files: There isn\'t too much that could be done here. One could set ddmem to 64Kbyte aligned addresses (so functions won\'t end up at xxxxBF80h). Or one could even set ddmem to BF800000h (so patching will leave everything unchanged & intact - so one could then do the address adjustments manually, and hopefully more reliable than other DLDI installers).



