# DSi Atheros Wifi SDIO Interface


**AR6002 SDIO Registers**
- [DSi Atheros Wifi SDIO Function 0 RegisterSummary](./dsiatheroswifisdiofunction0registersummary.md)
- [DSi Atheros Wifi SDIO Function 1 RegisterSummary](./dsiatheroswifisdiofunction1registersummary.md)
- [DSi Atheros Wifi - SDIO Function 1 I/O -mbox_wlan_host_reg](./dsiatheroswifisdiofunction1iomboxwlanhostreg.md)
- [DSi Atheros Wifi Misc](./dsiatheroswifimisc.md)
For general info about SDIO protocol and I/O ports, and SDIO Function 0,
see
- [DSi SD/MMC Protocol and I/O Ports](./dsisdmmcprotocolandioports.md)

**Transfer Protocol (Commands/Events)**
- [DSi Atheros Wifi - Command Summary](./dsiatheroswificommandsummary.md)
- [DSi Atheros Wifi - Response Summary](./dsiatheroswifiresponsesummary.md)
- [DSi Atheros Wifi - Host Interest Area inRAM](./dsiatheroswifihostinterestareainram.md)
- [DSi Atheros Wifi - BMI BootloaderCommands](./dsiatheroswifibmibootloadercommands.md)
- [DSi Atheros Wifi - MBOX TransferHeaders](./dsiatheroswifimboxtransferheaders.md)
- [DSi Atheros Wifi - WMI Misc Commands](./dsiatheroswifiwmimisccommands.md)
- [DSi Atheros Wifi - WMI Misc Events](./dsiatheroswifiwmimiscevents.md)
- [DSi Atheros Wifi - WMI ConnectFunctions](./dsiatheroswifiwmiconnectfunctions.md)
- [DSi Atheros Wifi - WMI Channel and CipherFunctions](./dsiatheroswifiwmichannelandcipherfunctions.md)
- [DSi Atheros Wifi - WMI ScanFunctions](./dsiatheroswifiwmiscanfunctions.md)
- [DSi Atheros Wifi - WMI Bit RateFunctions](./dsiatheroswifiwmibitratefunctions.md)
- [DSi Atheros Wifi - WMI ThresholdFunctions](./dsiatheroswifiwmithresholdfunctions.md)
- [DSi Atheros Wifi - WMI Error, Retry and DebugFunctions](./dsiatheroswifiwmierrorretryanddebugfunctions.md)
- [DSi Atheros Wifi - WMI Priority StreamFunctions](./dsiatheroswifiwmiprioritystreamfunctions.md)
- [DSi Atheros Wifi - WMI RoamFunctions](./dsiatheroswifiwmiroamfunctions.md)
- [DSi Atheros Wifi - WMI PowerFunctions](./dsiatheroswifiwmipowerfunctions.md)
- [DSi Atheros Wifi - WMI StatisticsFunction](./dsiatheroswifiwmistatisticsfunction.md)
- [DSi Atheros Wifi - WMI Bluetooth Coexistence (olderAR6002)](./dsiatheroswifiwmibluetoothcoexistenceolderar6002.md)
- [DSi Atheros Wifi - WMI Wake on Wireless (WOW)Functions](./dsiatheroswifiwmiwakeonwirelesswowfunctions.md)
- [DSi Atheros Wifi - WMI General Purpose I/O (GPIO)Functions](./dsiatheroswifiwmigeneralpurposeiogpiofunctions.md)
Additional WMI Functions (NOT implemented in DSi with AR6002, but maybe
exist in DSi/3DS with AR6013/AR6014):
- [DSi Atheros Wifi - Unimplemented WMI MiscFunctions](./dsiatheroswifiunimplementedwmimiscfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence (newerAR6002)](./dsiatheroswifiunimplementedwmibluetoothcoexistencenewerar6002.md)
- [DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence(./dsiatheroswifiunimplementedwmibluetoothcoexistencear6003.md)
- [DSi Atheros Wifi - Unimplemented WMI DataSetFunctions](./dsiatheroswifiunimplementedwmidatasetfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI AP Mode Functions (exists on3DS)](./dsiatheroswifiunimplementedwmiapmodefunctionsexistson3ds.md)
- [DSi Atheros Wifi - Unimplemented WMI DFSFunctions](./dsiatheroswifiunimplementedwmidfsfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI P2PFunctions](./dsiatheroswifiunimplementedwmip2pfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI WACFunctions](./dsiatheroswifiunimplementedwmiwacfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI RF Kill and Store/RecallFunctions](./dsiatheroswifiunimplementedwmirfkillandstorerecallfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI THINFunctions](./dsiatheroswifiunimplementedwmithinfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI PyxisFunctions](./dsiatheroswifiunimplementedwmipyxisfunctions.md)
Aside from WMI Commands/Events, it should be obviously also possible to
transfer actual data packets, but unknown to do that\... maybe it\'
done through MBOX0 too, and maybe related to WMI_DATA_HDR,
WMI_TX_META_V0..3, WMI_RX_META_V0..2 in \"wmi.h\" and/or to stuff i
\"htc.h\".

- [DSi Atheros Wifi I2C EEPROM](./dsiatheroswifii2ceeprom.md)



