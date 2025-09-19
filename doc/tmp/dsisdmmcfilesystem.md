# DSi SD/MMC Filesystem


**DSi Partition Table and FAT Filesystems**
- [DSi SD/MMC Partition Table (aka Master Boot Record akaMBR)](./dsisdmmcpartitiontableakamasterbootrecordakambr.md)
- [DSi SD/MMC Filesystem (./dsisdmmcfilesystemfat.md)
System Tools and DSiware games are having regular \"ROM Cartridge\
headers, with NitroROM filesystem defined in that headers (ie. the
\".app\" files are internally containing a 2nd filesystem inside of th
FAT filesystem; eventually there can be also NARC files as 3rd
filesystem inside of the NitroROM filesystem).
- [DSi Cartridge Header](./dsicartridgeheader.md)
- [DS Cartridge NitroROM and NitroARC FileSystems](./dscartridgenitroromandnitroarcfilesystems.md)
Savedata for DSiWare games is usually stored in \"public.sav\" o
\"private.sav\" files. That .sav files are usually containing a FAT1
with its own VBR, FAT, and Directories (so they use some virtual FAT12
inside of the real FAT16).

**DSi Filesystem Overview**
- [DSi SD/MMC Internal NAND Layout](./dsisdmmcinternalnandlayout.md)
- [DSi SD/MMC Bootloader](./dsisdmmcbootloader.md)
- [DSi SD/MMC Device List](./dsisdmmcdevicelist.md)
- [DSi SD/MMC Complete List of SD/MMCFiles/Folders](./dsisdmmccompletelistofsdmmcfilesfolders.md)
- [DSi SD/MMC Summary of SD/MMCFiles/Folders](./dsisdmmcsummaryofsdmmcfilesfolders.md)
- [DSi SD/MMC Images](./dsisdmmcimages.md)
- [DSi Autoload on Warmboot](./dsiautoloadonwarmboot.md)

**DSi Files**
- [DSi SD/MMC DSiware Files on Internal eMMCStorage](./dsisdmmcdsiwarefilesoninternalemmcstorage.md)
- [DSi SD/MMC DSiware Files on External SD Card (.bin aka TadFiles)](./dsisdmmcdsiwarefilesonexternalsdcardbinakatadfiles.md)
- [DSi SD/MMC DSiware Files from Nintendo\'Server](./dsisdmmcdsiwarefilesfromnintendosserver.md)
- [DSi SD/MMC DSiware Tickets and Titlemetadata](./dsisdmmcdsiwareticketsandtitlemetadata.md)
- [DSi SD/MMC Firmware dev.kp and cert.sys CertificateFiles](./dsisdmmcfirmwaredevkpandcertsyscertificatefiles.md)
- [DSi SD/MMC Firmware Certificate/Keys(./dsisdmmcfirmwarecertificatekeysder.md)
- [DSi SD/MMC Firmware Font File](./dsisdmmcfirmwarefontfile.md)
- [DSi SD/MMC Firmware Log Files](./dsisdmmcfirmwarelogfiles.md)
- [DSi SD/MMC Firmware Misc Files](./dsisdmmcfirmwaremiscfiles.md)
- [DSi SD/MMC Firmware Wifi Firmware](./dsisdmmcfirmwarewififirmware.md)
- [DSi SD/MMC Firmware System Settings DataFiles](./dsisdmmcfirmwaresystemsettingsdatafiles.md)
- [DSi SD/MMC Firmware Version DataFile](./dsisdmmcfirmwareversiondatafile.md)
- [DSi SD/MMC Firmware Nintendo DS Cart WhitelistFile](./dsisdmmcfirmwarenintendodscartwhitelistfile.md)
- [DSi SD/MMC Camera Files - Overview](./dsisdmmccamerafilesoverview.md)
- [DSi SD/MMC Camera Files - JPEG\'s](./dsisdmmccamerafilesjpegs.md)
- [DSi SD/MMC Camera Files - pit.bin](./dsisdmmccamerafilespitbin.md)
- [DSi SD/MMC Flipnote Files](./dsisdmmcflipnotefiles.md)
- [DS File Formats](./dsfileformats.md)



