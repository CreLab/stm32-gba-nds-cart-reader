# DSi Advanced Encryption Standard (AES)


### AES I/O Ports
- [DSi AES I/O Ports](./dsiaesioports.md)

### AES Pseudo Code
Little Endian Code (as used in DSi hardware):
- [DSi AES Little-Endian High Level Functions](./dsiaeslittleendianhighlevelfunctions.md)
- [DSi AES Little-Endian Core Function and Key Schedule](./dsiaeslittleendiancorefunctionandkeyschedule.md)
- [DSi AES Little-Endian Tables and Test Values](./dsiaeslittleendiantablesandtestvalues.md)
Big Endian Code (as used more commonly, in non-DSi implementations):
- [DSi AES Big-Endian High Level Functions](./dsiaesbigendianhighlevelfunctions.md)
- [DSi AES Big-Endian Core Function and Key Schedule](./dsiaesbigendiancorefunctionandkeyschedule.md)
- [DSi AES Big-Endian Tables and Test Values](./dsiaesbigendiantablesandtestvalues.md)
Most AES values are endian-free byte-strings, so different \"endianness\" does just mean to reverse the byte order of the 16/24/32-byte KEYs, the 16-byte data chunks, and the 16-byte CTR/CFB/CBC/MAC registers (in some of the latter cases it\'s also referring to actual endiannes, eg. for CTR increments).

### AES Usage in DSi
AES-CCM is used for several SD/MMC files (using a custom Nintendo-specific CCM variant; consisting of 128K-byte data blocks with 32-byte footers):
- [DSi ES Block Encryption](./dsiesblockencryption.md)
AES-CTR is used for the Modcrypt areas defined in Cartridge Header, and for eMMC Boot Sectors and for eMMC MBR/Partitions.

### AES Usage in DSi-Wifi
DSi Wifi is also supporting AES (and TKIP and WEP) encryption, the Wifi unit contains additional AES hardware for data packet encryption (however, Wifi EAPOL handshakes do require AES key unwrap implemented in software).

### AES Usage in DSi-Shop
DSi Shop downloads (and system updates) are using big-endian AES-CBC, this does require an AES software implementation because the DSi\'s AES hardware couldn\'t decrypt that AES variant.



