# DSi Atheros Wifi - BMI Bootloader Commands


The BMI commands are used to upload the Wifi Firmware to RAM. Doing that is required because the ROM functions themselves aren\'t fully functional, and the chip can process only BMI commands or WMI commands (not both at once):

```
+-----------------------------------------------------------------------+
|       BMI Commands --> After RESET                                    |
|       WMI Commands --> After uploading and sending BMI_DONE           |
+-----------------------------------------------------------------------+
```

The AR6002 ROM contains about 40-50% of the program code needed to operate the chip (and most of that ROM code is left unused, until it is getting initialized by the firmware; so the firmware isn\'t just an \"update\", it\'s absolutely required to get the chip working).

### DSi Wifi Firmware
On the DSi, the Wifi Firmware is stored in a eMMC file, and it\'s automatically uploaded by the DSi System Menu (Launcher), so DSi games should be always started with Firmware already installed, and don\'t need to deal with BMI commands.
- [DSi SD/MMC Firmware Wifi Firmware](./dsisdmmcfirmwarewififirmware.md)
If desired, one could force the chip back to BMI state by issuing a reset, eg. via RESET_CONTROL.Bit8; there might be further ways to issue resets, like SDIO CCCR maybe).
Note: The BMI uploader in DSi is reffering to BMI as \"PRE-AUTH\" phase, the system menu will be shown even in case of BMI failure, but any such failure will later cause a \"WLFIRM 2\" error (in sysmenu.log) at time when trying to start a title from within system menu.

### BMI Transfer
Before each BMI command, wait for LOCAL_COUNT\[4\] to become nonzero. Then, write the command and parameters to MBOX0. Then read the response (if any) from MBOX0 (ideally with checking MBOX empty flag before reading response bytes; DSi code doesn\'t seem to do that though - maybe the SDIO controller is automatically waiting while MBOX empty?).


```
+----------------------------------------------------------------------------------+
|      ____________________________ Execute Functions ____________________________ |
+----------------------------------------------------------------------------------+
```


### BMI_CMD(01h) - BMI_DONE - Launch Firmware

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000001h)                                  |
+-----------------------------------------------------------------------+
```

Starts the firmware by calling its entrypoint. The default entry is 915000h for AR6002G (or 927000h for AR6013G and AR6014G), alternately a custom entrypoint can be set via BMI_CMD(05h).

### BMI_CMD(04h) - BMI_EXECUTE - Execute

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000004h)                                  |
|       Send 32bit Entrypoint                                           |
|       Send 32bit Argument                                             |
|       Receive 32bit Return Value                                      |
+-----------------------------------------------------------------------+
```

Calls a function on Xtensa CPU. On DSi, this is used to execute the boot stub (for reading the I2C EEPROM data). The main firmware should be started via BMI_DONE, not via BMI_EXECUTE.

### BMI_CMD(05h) - BMI_SET_APP_START - Set App Start

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000005h)                                  |
|       Send 32bit Entrypoint                                           |
+-----------------------------------------------------------------------+
```

Changes the default entrypoint for BMI_DONE. The DSi doesn\'t use this feature (and uses the default entrypoint).


```
+-----------------------------------------------------------------------------------+
|      ___________________________ Read/Write Functions ___________________________ |
+-----------------------------------------------------------------------------------+
```


### BMI_CMD(02h) - BMI_READ_MEMORY - Read Memory

```
+--------------------------------------------------------------------------------+
|       Send 32bit Command (00000002h)                                           |
|       Send 32bit Address                                                       |
|       Send 32bit Length (should be max 80h or 200h or so (?) due to MBOX size) |
|       Receive LEN bytes, read from [address and up]                            |
+--------------------------------------------------------------------------------+
```

Allows to read Xtensa RAM or ROM in byte-units (I/O ports should be read in 32bit units, via BMI_READ_SOC_REGISTER).

### BMI_CMD(03h) - BMI_WRITE_MEMORY - Write Memory

```
+------------------------------------------------------------------------------+
|       Send 32bit Command (00000003h)                                         |
|       Send 32bit Address (or special value for "Segmented Write", see below) |
|       Send 32bit Length (should be max 1F4h due to MBOX size)                |
|       Send LEN bytes, written to [address and up]                            |
+------------------------------------------------------------------------------+
```

Allows to write Xtensa RAM. Used to upload the stub and data parts of the firmware (the main part of the firmware is uploaded via BMI_LZ_xxx functions).

### BMI_CMD(06h) - BMI_READ_SOC_REGISTER - Read Register

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000006h)                                  |
|       Send 32bit Address                                              |
|       Receive 32bit Word from [address]                               |
+-----------------------------------------------------------------------+
```

Allows to read Xtensa I/O Ports (or RAM or ROM) in 32bit-units. The same effect can be gained via WINDOW_DATA register (which is also working when the Xtensa CPU isn\'t in BMI bootloader state).

### BMI_CMD(07h) - BMI_WRITE_SOC_REGISTER - Write Register

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000007h)                                  |
|       Send 32bit Address                                              |
|       Send 32bit Word to [address]                                    |
+-----------------------------------------------------------------------+
```

Allows to write Xtensa I/O Ports (or RAM) in 32bit-units.

### BMI_CMD(0Dh) - BMI_LZ_STREAM_START - LZ Uncompress Stream Start

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (0000000Dh)                                  |
|       Send 32bit Destination Start Address for BMI_CMD(0Eh)           |
+-----------------------------------------------------------------------+
```

Sets the destination start address for following BMI_LZ_DATA command(s). Also resets the decompressor to expect the \"tag\" value in first byte.

### BMI_CMD(0Eh) - BMI_LZ_DATA - LZ Data Input

```
+-----------------------------------------------------------------------------------+
|       Send 32bit Command (0000000Eh)                                              |
|       Send 32bit Length (should be max 1F8h due to MBOX size)                     |
|       Send LEN compressed bytes, decompressed to incrementing destination address |
+-----------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|      ___________________________ ROM Patch Functions ___________________________ |
+----------------------------------------------------------------------------------+
```


ROM Patches using the hardware\'s TCAM/BCAM registers (implemented in hardware, but not actually used by DSi firmware).

### BMI_CMD(09h) - BMI_ROMPATCH_INSTALL - TCAM/BCAM_xxxxx

```
+--------------------------------------------------------------------------------+
|       Send 32bit Command (00000009h)                                           |
|       Send 32bit Target ROM Address                                            |
|       Send 32bit Target RAM Address or Value (depending on Target Type)        |
|       Send 32bit Size (in bytes)                                               |
|       Send 32bit Activate (0=Install without activate, 1=Install and activate) |
|       Receive 32bit PatchID                                                    |
+--------------------------------------------------------------------------------+
```

The DSi/3DS do contain TCAM hardware. The TCAM hardware\'s eight size settings are probably 20h,40h,80h,100h,200h,400h,800h,1000h. For the BCAM hardware, the size must be probably always set to 04h.

### BMI_CMD(0Ah) - BMI_ROMPATCH_UNINSTALL - TCAM/BCAM_Clr_index_and_xxx
Uninstall (and deactivate) a previously-installed ROM Patch.

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (0000000Ah)                                  |
|       Send 32bit PatchID (to be uninstalled & deactivated)            |
+-----------------------------------------------------------------------+
```


### BMI_CMD(0Bh) - BMI_ROMPATCH_ACTIVATE - TCAM/BCAM_Set_indices
### BMI_CMD(0Ch) - BMI_ROMPATCH_DEACTIVATE - TCAM/BCAM_Clr_indices
Activate/Deactivate a list of previously-installed ROM Patches.

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (0000000Bh/0000000Ch)                        |
|       Send 32bit Number of patches (N)                                |
|       Send Nx32bit List of PatchID's (to be activated/deactivated)    |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      ______________________________ Misc Functions ______________________________ |
+-----------------------------------------------------------------------------------+
```


### BMI_CMD(08h) - BMI_GET_TARGET_ID aka BMI_GET_TARGET_INFO - Get Version

```
+-------------------------------------------------------------------------+
|       Send 32bit Command (00000008h)                                    |
|       Receive 32bit Value (FFFFFFFFh) ;ROM version (or FFFFFFFFh)       |
|      If above value is FFFFFFFFh then following extra data is appended: |
|       Receive 32bit Value (0000000Ch) ;total size of extra data         |
|       Receive 32bit Value (20000188h) ;ROM version                      |
|       Receive 32bit Value (00000002h) ;TARGET_TYPE (2=AR6002)           |
+-------------------------------------------------------------------------+
```


### BMI_CMD(0Fh) - BMI_NVRAM_PROCESS ;not implemented in DSi, Invalid (ignored)
Unknown purpose, said to \"process or execute\" something in \"NVRAM\" with a name in \"LE format\":
\"Cause Target to search NVRAM (if any) for a segment with the specified name and process it according to NVRAM metadata.\"

```
+---------------------------------------------------------------------------------+
|       Send 32bit Command (0000000Fh)                                            |
|       Send 16x8bit Name (16 characters, in "LE format", uh?)                    |
|       Receive 32bit Value returned from last executed NVRAM segment (or 0=None) |
+---------------------------------------------------------------------------------+
```


### BMI_CMD(00h) - BMI_NO_COMMAND - Invalid (ignored)
### BMI_CMD(0Fh..FFFFFFFFh) - N/A - Invalid (ignored)

```
+-----------------------------------------------------------------------+
|       Send 32bit Command (00000000h, or 0000000Fh..FFFFFFFFh)         |
+-----------------------------------------------------------------------+
```


### Segmented Write
The Segmented Write feature is implemented only in newer ROMs (not in DSi with AR6002). It is invoked via BMI_CMD(03h) with destination address set to special value 00001234h.

```
+----------------------------------------------------------------------------+
|       Send 32bit Command (00000003h) <-- same as Write Memory command      |
|       Send 32bit Address (00001234h) <-- special value for Segmented Write |
|       Send 32bit Length (should be max 1F4h due to MBOX size)              |
|       Send LEN bytes, as described below...                                |
+----------------------------------------------------------------------------+
```

The transferred data should contain a file header:

```
+-----------------------------------------------------------------------+
|       00h 4    File ID (544D4753h) ("SGMT")                           |
|       04h 4    File Flags (0=Raw, 1=BMI_SGMTFILE_FLAG_COMPRESS)       |
+-----------------------------------------------------------------------+
```

Followed by one or more segments:

```
+--------------------------------------------------------------------------------+
|       00h 4    Destination Address (the actual address, no special value here) |
|       04h 4    Segment Length (N) (or special value FFFFFFFxh)                 |
|       08h N    Data (N bytes)     (no data when N=FFFFFFFxh)                   |
+--------------------------------------------------------------------------------+
```

Special values for \"Segment Length\" (all with bit31=1):

```
+------------------------------------------------------------------------------------+
|       FFFFFFFFh ;End of segmented data file (should occur as last segment)         |
|       FFFFFFFEh ;Board Data (write "hi_board_data+Address", instead raw "Address") |
|       FFFFFFFDh ;Set App Start=Addresss; like BMI_CMD(05h)                         |
|       FFFFFFFCh ;Call Address; like BMI_CMD(04h), but without param/return value   |
+------------------------------------------------------------------------------------+
```

Compressed Segmented data is said to work in two ways (?):

```
+-----------------------------------------------------------------------------------+
|       1) Use BMI_LZ_STREAM_START with Addr=00001234h, followed by BMI_LZ_DATA, or |
|       2) Use BMI_WRITE_MEMORY with Addr=00001234h and file header Flags=1.        |
+-----------------------------------------------------------------------------------+
```

Atheros has invented that weird feature for \"backwards compatibility & darn convenience\", which is both sad and funny because Atheros is definitely unable to \<maintain\> backwards compatibility (such as keeping the same WMI command/event numbering in firmware revisions), but as it seems, Atheros is believing that \"backwards compatibility\" is something that can be \<invented\> by adding obscure features.



