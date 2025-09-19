# DSi Atheros Wifi Internal Hardware


Below describes the internal Atheros hardware. The hardware registers
can be accessed via WINDOW_DATA, or by uploading custom code to the
Xtensa CPU via BMI Bootloader commands.
Anyways, normally, the Wifi unit should be accessed via WMI commands, so
one won\'t need to deal with internal hardware (except cases lik
reading the CHIP_ID, or for better understanding of the inner workings
of the hardware).

**Internal Xtensa CPU**
- [DSi Atheros Wifi - Xtensa CPURegisters](./dsiatheroswifixtensacpuregisters.md)
- [DSi Atheros Wifi - Xtensa CPU CoreOpcodes](./dsiatheroswifixtensacpucoreopcodes.md)
- [DSi Atheros Wifi - Xtensa CPU Optional GeneralOpcodes](./dsiatheroswifixtensacpuoptionalgeneralopcodes.md)
- [DSi Atheros Wifi - Xtensa CPU Optional Exception/Cache/MMUOpcodes](./dsiatheroswifixtensacpuoptionalexceptioncachemmuopcodes.md)
- [DSi Atheros Wifi - Xtensa CPU Optional Floating-PointOpcodes](./dsiatheroswifixtensacpuoptionalfloatingpointopcodes.md)
- [DSi Atheros Wifi - Xtensa CPU Optional MAC16Opcodes](./dsiatheroswifixtensacpuoptionalmac16opcodes.md)
- [DSi Atheros Wifi - Xtensa CPU Opcode EncodingTables](./dsiatheroswifixtensacpuopcodeencodingtables.md)

**Internal Memory and I/O Maps**
- [DSi Atheros Wifi - Internal MemoryMap](./dsiatheroswifiinternalmemorymap.md)
- [DSi Atheros Wifi - Internal I/O Map Summary(./dsiatheroswifiinternaliomapsummaryhw2.md)
- [DSi Atheros Wifi - Internal I/O Map Summary(./dsiatheroswifiinternaliomapsummaryhw4.md)
- [DSi Atheros Wifi - Internal I/O Map Summary(./dsiatheroswifiinternaliomapsummaryhw6.md)
Note: All DSi/3DS boards are using hw2 (though with minor changes
between AR6002 and AR6013/AR6014 on the GPIO I2C pin wiring, and
external oscillator). The hw4/hw6 variants are shown here only for
curiosity, they aren\'t used anywhere in DSi/3DS).

**AR60XX Internal Registers**
- [DSi Atheros Wifi - Internal I/O - Unknown and Unused Registers(./dsiatheroswifiinternaliounknownandunusedregistershw2.md)
- [DSi Atheros Wifi - Internal I/O - 004000h - RTC/Clock SOC(./dsiatheroswifiinternalio004000hrtcclocksochw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 00x000h - RTC/Clock WLAN(./dsiatheroswifiinternalio00x000hrtcclockwlanhw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 0xx240h - RTC/Clock SYNC(./dsiatheroswifiinternalio0xx240hrtcclocksynchw6.md)
- [DSi Atheros Wifi - Internal I/O - 006000h - WLAN Coex (MCI)(./dsiatheroswifiinternalio006000hwlancoexmcihw6.md)
- [DSi Atheros Wifi - Internal I/O - 00x000h - Bluetooth Coex(./dsiatheroswifiinternalio00x000hbluetoothcoexhw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 00x000h - Memory Control(./dsiatheroswifiinternalio00x000hmemorycontrolhw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 00C000h - Serial UART(./dsiatheroswifiinternalio00c000hserialuarthw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 00E000h - UMBOX Registers(./dsiatheroswifiinternalio00e000humboxregistershw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 010000h - Serial I2C/SPI(./dsiatheroswifiinternalio010000hseriali2cspihw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 014000h - GPIO 18/26/57 pin(./dsiatheroswifiinternalio014000hgpio182657pinhw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 018000h - MBOX Registers(./dsiatheroswifiinternalio018000hmboxregistershw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 01C000h - Analog Intf(./dsiatheroswifiinternalio01c000hanalogintfhw2.md)
- [DSi Atheros Wifi - Internal I/O - 01C000h - Analog Intf(./dsiatheroswifiinternalio01c000hanalogintfhw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 020000h - WMAC DMA(./dsiatheroswifiinternalio020000hwmacdmahw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 020080h - WMAC IRQ Interrupt(./dsiatheroswifiinternalio020080hwmacirqinterrupthw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 020800h - WMAC QCU Queue(./dsiatheroswifiinternalio020800hwmacqcuqueuehw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 021000h - WMAC DCU(./dsiatheroswifiinternalio021000hwmacdcuhw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 028000h - WMAC PCU(./dsiatheroswifiinternalio028000hwmacpcuhw2hw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 029800h - BB Baseband(./dsiatheroswifiinternalio029800hbbbasebandhw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 0xxx00h - RDMA Registers(./dsiatheroswifiinternalio0xxx00hrdmaregistershw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 03x000h - EFUSE Registers(./dsiatheroswifiinternalio03x000hefuseregistershw4hw6.md)
- [DSi Atheros Wifi - Internal I/O - 034000h - More Stuff(./dsiatheroswifiinternalio034000hmorestuffhw6.md)



