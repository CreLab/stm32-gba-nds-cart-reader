# DS Cartridge Secure Area


The Secure Area is located in ROM at 4000h..7FFFh, it can contain normal program code and data, however, it can be used only for ARM9 boot code, it cannot be used for ARM7 boot code, icon/title, filesystem, or other data.

### Secure Area Size
The Secure Area exists if the ARM9 boot code ROM source address (src) is located within 4000h..7FFFh, if so, it will be loaded (by BIOS via KEY1 encrypted commands) in 4K portions, starting at src, aligned by 1000h, up to address 7FFFh. The secure area size if thus 8000h-src, regardless of the ARM9 boot code size entry in header.
Note: The BIOS silently skips any NDS9 bootcode at src\<4000h.
Cartridges with src\>=8000h do not have a secure area.

### Secure Area ID
The first 8 bytes of the secure area are containing the Secure Area ID, the ID is required (verified by BIOS boot code), the ID value changes during boot process:

```
+---------------------------------------------------------------------------------+
|       Value                Expl.                                                |
|       "encryObj"           raw ID before encryption (raw ROM-image)             |
|       (encrypted)          encrypted ID after encryption (encrypted ROM-image)  |
|       "encryObj"           raw ID after decryption (verified by BIOS boot code) |
|       E7FFDEFFh,E7FFDEFFh  destroyed ID (overwritten by BIOS after verify)      |
+---------------------------------------------------------------------------------+
```

If the decrypted ID does match, then the BIOS overwrites the first 8 bytes by E7FFDEFFh-values (ie. only the ID is destroyed). If the ID doesn\'t match, then the first 800h bytes (2K) are overwritten by E7FFDEFFh-values.

### Secure Area First 2K Encryption/Content
The first 2K of the Secure Area (if it exists) are KEY1 encrypted. In official games, this 2K region contains data like so (in decrypted form):

```
+--------------------------------------------------------------------------+
|       000h..007h  Secure Area ID (see above)                             |
|       008h..00Dh  Fixed (FFh,DEh,FFh,E7h,FFh,DEh)                        |
|       00Eh..00Fh  CRC16 across following 7E0h bytes, ie. [010h..7FFh]    |
|       010h..7FDh  Unknown/random values, mixed with some THUMB SWI calls |
|       7FEh..7FFh  Fixed (00h,00h)                                        |
+--------------------------------------------------------------------------+
```

Of which, only the ID in the first 8 bytes is verified. Neither BIOS nor (current) firmare versions are verifying the data at 008h..7FFh, so the 7F8h bytes may be also used for normal program code/data.

### Avoiding Secure Area Encryption
WLAN files are reportedly same format as cartridges, but without Secure Area, so games with Secure Area cannot be booted via WLAN. No\$gba can encrypt and decrypt Secure Areas only if the NDS BIOS-images are present. And, Nintendo\'s devkit doesn\'t seem to support Secure Area encryption of unreleased games.
So, unencrypted cartridges are more flexible in use. Ways to avoid encryption (which still work on real hardware) are:
1) Set NDS9 ROM offset to 4000h, and leave the first 800h bytes of the Secure Area 00h-filled, which can be (and will be) safely destroyed during loading; due to the missing \"encryObj\" ID; that method is used by Nintendo\'s devkit.
2) Set NDS9 ROM offset to 8000h or higher (cartridge has no Secure Area at all).
3) Set NDS9 ROM offset, RAM address, and size to zero, set NDS7 ROM offset to 200h, and point both NDS9 and NDS7 entrypoints to the loaded NDS7 region. That method avoids waste of unused memory at 200h..3FFFh, and it should be compatible with the NDS console, however, it is not comaptible with commercial cartridges - which do silently redirect address below 4000h to \"addr=8000h+(addr AND 1FFh)\". Still, it should work with inofficial flashcards, which do not do that redirection. No\$gba emulates the redirection for regular official cartridges, but it disables redirection for homebrew carts if NDS7 rom offset\<8000h, and NDS7 size\>0.
\[One possible problem: Newer \"anti-passme\" firmware versions reportedly check that the entrypoint isn\'t set to 80000C0h, that firmwares might also reject NDS9 entrypoints within the NDS7 bootcode region?\]



