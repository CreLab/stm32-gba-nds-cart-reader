# DSi SD/MMC Filesystem


### DSi Partition Table and FAT Filesystems
- [DSi SD/MMC Partition Table (aka Master Boot Record aka MBR)](./dsisdmmcpartitiontableakamasterbootrecordakambr.md)
- [DSi SD/MMC Filesystem (FAT)](./dsisdmmcfilesystemfat.md)
System Tools and DSiware games are having regular \"ROM Cartridge\" headers, with NitroROM filesystem defined in that headers (ie. the \".app\" files are internally containing a 2nd filesystem inside of the FAT filesystem; eventually there can be also NARC files as 3rd filesystem inside of the NitroROM filesystem).
- [DSi Cartridge Header](./dsicartridgeheader.md)
- [DS Cartridge NitroROM and NitroARC File Systems](./dscartridgenitroromandnitroarcfilesystems.md)
Savedata for DSiWare games is usually stored in \"public.sav\" or \"private.sav\" files. That .sav files are usually containing a FAT12 with its own VBR, FAT, and Directories (so they use some virtual FAT12 inside of the real FAT16).

### DSi Filesystem Overview
- [DSi SD/MMC Internal NAND Layout](./dsisdmmcinternalnandlayout.md)
- [DSi SD/MMC Bootloader](./dsisdmmcbootloader.md)
- [DSi SD/MMC Device List](./dsisdmmcdevicelist.md)
- [DSi SD/MMC Complete List of SD/MMC Files/Folders](./dsisdmmccompletelistofsdmmcfilesfolders.md)
- [DSi SD/MMC Summary of SD/MMC Files/Folders](./dsisdmmcsummaryofsdmmcfilesfolders.md)
- [DSi SD/MMC Images](./dsisdmmcimages.md)
- [DSi Autoload on Warmboot](./dsiautoloadonwarmboot.md)

### DSi Files
- [DSi SD/MMC DSiware Files on Internal eMMC Storage](./dsisdmmcdsiwarefilesoninternalemmcstorage.md)
- [DSi SD/MMC DSiware Files on External SD Card (.bin aka Tad Files)](./dsisdmmcdsiwarefilesonexternalsdcardbinakatadfiles.md)
- [DSi SD/MMC DSiware Files from Nintendo\'s Server](./dsisdmmcdsiwarefilesfromnintendosserver.md)
- [DSi SD/MMC DSiware Tickets and Title metadata](./dsisdmmcdsiwareticketsandtitlemetadata.md)
- [DSi SD/MMC Firmware dev.kp and cert.sys Certificate Files](./dsisdmmcfirmwaredevkpandcertsyscertificatefiles.md)
- [DSi SD/MMC Firmware Certificate/Keys (DER)](./dsisdmmcfirmwarecertificatekeysder.md)
- [DSi SD/MMC Firmware Font File](./dsisdmmcfirmwarefontfile.md)
- [DSi SD/MMC Firmware Log Files](./dsisdmmcfirmwarelogfiles.md)
- [DSi SD/MMC Firmware Misc Files](./dsisdmmcfirmwaremiscfiles.md)
- [DSi SD/MMC Firmware Wifi Firmware](./dsisdmmcfirmwarewififirmware.md)
- [DSi SD/MMC Firmware System Settings Data Files](./dsisdmmcfirmwaresystemsettingsdatafiles.md)
- [DSi SD/MMC Firmware Version Data File](./dsisdmmcfirmwareversiondatafile.md)
- [DSi SD/MMC Firmware Nintendo DS Cart Whitelist File](./dsisdmmcfirmwarenintendodscartwhitelistfile.md)
- [DSi SD/MMC Camera Files - Overview](./dsisdmmccamerafilesoverview.md)
- [DSi SD/MMC Camera Files - JPEG\'s](./dsisdmmccamerafilesjpegs.md)
- [DSi SD/MMC Camera Files - pit.bin](./dsisdmmccamerafilespitbin.md)
- [DSi SD/MMC Flipnote Files](./dsisdmmcflipnotefiles.md)
- [DS File Formats](./dsfileformats.md)



