# DSi Atheros Wifi SDIO Interface


### AR6002 SDIO Registers
- [DSi Atheros Wifi SDIO Function 0 Register Summary](./dsiatheroswifisdiofunction0registersummary.md)
- [DSi Atheros Wifi SDIO Function 1 Register Summary](./dsiatheroswifisdiofunction1registersummary.md)
- [DSi Atheros Wifi - SDIO Function 1 I/O - mbox_wlan_host_reg](./dsiatheroswifisdiofunction1iomboxwlanhostreg.md)
- [DSi Atheros Wifi Misc](./dsiatheroswifimisc.md)
For general info about SDIO protocol and I/O ports, and SDIO Function 0, see
- [DSi SD/MMC Protocol and I/O Ports](./dsisdmmcprotocolandioports.md)

### Transfer Protocol (Commands/Events)
- [DSi Atheros Wifi - Command Summary](./dsiatheroswificommandsummary.md)
- [DSi Atheros Wifi - Response Summary](./dsiatheroswifiresponsesummary.md)
- [DSi Atheros Wifi - Host Interest Area in RAM](./dsiatheroswifihostinterestareainram.md)
- [DSi Atheros Wifi - BMI Bootloader Commands](./dsiatheroswifibmibootloadercommands.md)
- [DSi Atheros Wifi - MBOX Transfer Headers](./dsiatheroswifimboxtransferheaders.md)
- [DSi Atheros Wifi - WMI Misc Commands](./dsiatheroswifiwmimisccommands.md)
- [DSi Atheros Wifi - WMI Misc Events](./dsiatheroswifiwmimiscevents.md)
- [DSi Atheros Wifi - WMI Connect Functions](./dsiatheroswifiwmiconnectfunctions.md)
- [DSi Atheros Wifi - WMI Channel and Cipher Functions](./dsiatheroswifiwmichannelandcipherfunctions.md)
- [DSi Atheros Wifi - WMI Scan Functions](./dsiatheroswifiwmiscanfunctions.md)
- [DSi Atheros Wifi - WMI Bit Rate Functions](./dsiatheroswifiwmibitratefunctions.md)
- [DSi Atheros Wifi - WMI Threshold Functions](./dsiatheroswifiwmithresholdfunctions.md)
- [DSi Atheros Wifi - WMI Error, Retry and Debug Functions](./dsiatheroswifiwmierrorretryanddebugfunctions.md)
- [DSi Atheros Wifi - WMI Priority Stream Functions](./dsiatheroswifiwmiprioritystreamfunctions.md)
- [DSi Atheros Wifi - WMI Roam Functions](./dsiatheroswifiwmiroamfunctions.md)
- [DSi Atheros Wifi - WMI Power Functions](./dsiatheroswifiwmipowerfunctions.md)
- [DSi Atheros Wifi - WMI Statistics Function](./dsiatheroswifiwmistatisticsfunction.md)
- [DSi Atheros Wifi - WMI Bluetooth Coexistence (older AR6002)](./dsiatheroswifiwmibluetoothcoexistenceolderar6002.md)
- [DSi Atheros Wifi - WMI Wake on Wireless (WOW) Functions](./dsiatheroswifiwmiwakeonwirelesswowfunctions.md)
- [DSi Atheros Wifi - WMI General Purpose I/O (GPIO) Functions](./dsiatheroswifiwmigeneralpurposeiogpiofunctions.md)
Additional WMI Functions (NOT implemented in DSi with AR6002, but maybe exist in DSi/3DS with AR6013/AR6014):
- [DSi Atheros Wifi - Unimplemented WMI Misc Functions](./dsiatheroswifiunimplementedwmimiscfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence (newer AR6002)](./dsiatheroswifiunimplementedwmibluetoothcoexistencenewerar6002.md)
- [DSi Atheros Wifi - Unimplemented WMI Bluetooth Coexistence (AR6003)](./dsiatheroswifiunimplementedwmibluetoothcoexistencear6003.md)
- [DSi Atheros Wifi - Unimplemented WMI DataSet Functions](./dsiatheroswifiunimplementedwmidatasetfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI AP Mode Functions (exists on 3DS)](./dsiatheroswifiunimplementedwmiapmodefunctionsexistson3ds.md)
- [DSi Atheros Wifi - Unimplemented WMI DFS Functions](./dsiatheroswifiunimplementedwmidfsfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI P2P Functions](./dsiatheroswifiunimplementedwmip2pfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI WAC Functions](./dsiatheroswifiunimplementedwmiwacfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI RF Kill and Store/Recall Functions](./dsiatheroswifiunimplementedwmirfkillandstorerecallfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI THIN Functions](./dsiatheroswifiunimplementedwmithinfunctions.md)
- [DSi Atheros Wifi - Unimplemented WMI Pyxis Functions](./dsiatheroswifiunimplementedwmipyxisfunctions.md)
Aside from WMI Commands/Events, it should be obviously also possible to transfer actual data packets, but unknown to do that\... maybe it\'s done through MBOX0 too, and maybe related to WMI_DATA_HDR, WMI_TX_META_V0..3, WMI_RX_META_V0..2 in \"wmi.h\" and/or to stuff in \"htc.h\".

- [DSi Atheros Wifi I2C EEPROM](./dsiatheroswifii2ceeprom.md)



