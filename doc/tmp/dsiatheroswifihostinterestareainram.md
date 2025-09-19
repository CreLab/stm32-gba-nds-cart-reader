# DSi Atheros Wifi - Host Interest Area in RAM


### Host Interest Area (aka Target Addresses)
Apart from sending BMI and WMI commands via MBOX0, some communication is also done by directly accessing the 100h-byte \"Host Interest\" area in RAM, this can be done via WINDOW_DATA register (or via BMI commands).
The format of this memory area (defined in \"targaddrs.h\") is held to be same on all AR60xx chips, however, its BASE ADDRESS may vary on different chips:

```
+-----------------------------------------------------------------------+
|       AR6002_HOST_INTEREST_ADDRESS   = 00500400h  ;older DSi          |
|       AR6013_HOST_INTEREST_ADDRESS   = 00520000h  ;newer DSi          |
|       AR6014_HOST_INTEREST_ADDRESS   = 00520000h  ;3DS and New3DS     |
|       AR6003_HOST_INTEREST_ADDRESS   = 00540600h                      |
|       MCKINLEY_HOST_INTEREST_ADDRESS = 00400600h                      |
+-----------------------------------------------------------------------+
```

That base address can be also found in the DSi\'s \"Wifi Firmware\" fileheader.
Aside from the 100h bytes in RAM, there\'s also another host interest byte in the LOCAL_SCRATCH\[0\] register; the CHIP_ID register could be also considered as interesting to the host.

### Host Interest Entries in RAM (\"host_interest_s\" structure, 64 words)

```
+-------------------------------------------------------------------------------------+
|       00h  hi_app_host_interest ;-Pointer to application-defined area, if any.      |
|                                 ; (set by Target application during startup)        |
|       04h  hi_failure_state ;-Pointer to register dump area after Target crash      |
|       08h  hi_dbglog_hdr    ;-Pointer to debug logging header                       |
|       0Ch  hi_flash_is_present ;Indicates whether or not flash is present on Target |
|              ;NB: flash_is_present indicator is here not just because it might be   |
|              ;of interest to the Host; but also because it's set early on by        |
|              ;Target's startup asm code and we need it to have a special RAM        |
|              ;address so that it doesn't get reinitialized with the rest of data.   |
|       10h  hi_option_flag     ;-Various flags (see below)                           |
|       14h  hi_serial_enable   ;-Boolean whether to output (additional) TTY messages |
|       18h  hi_dset_list_head  ;-Start address of DataSet index, if any              |
|       1Ch  hi_app_start       ;-Override BMI_DONE Target application start address  |
|       20h  hi_skip_clock_init          ;\                                           
|       24h  hi_core_clock_setting       ;                                            |
|       28h  hi_cpu_clock_setting        ; Clock and voltage tuning                   |
|       2Ch  hi_system_sleep_setting     ;                                            |
|       30h  hi_xtal_control_setting     ;                                            |
|       34h  hi_pll_ctrl_setting_24ghz   ;                                            |
|       38h  hi_pll_ctrl_setting_5ghz    ;                                            |
|       3Ch  hi_ref_voltage_trim_setting ;                                            |
|       40h  hi_clock_info               ;/                                           |
|       44h  hi_bank0_addr_value         ;\Flash configuration overrides, used only   
|       48h  hi_bank0_read_value         ; when firmware is not executing from flash  |
|       4Ch  hi_bank0_write_value        ; (when using flash, modify the global       |
|       50h  hi_bank0_config_value       ;/variables with equivalent names)           |
|       54h  hi_board_data               ;\Pointer to Board Data (eg. from I2C        
|       58h  hi_board_data_initialized   ;/EEPROM) and data present/init flag         |
|       5Ch  hi_dset_RAM_index_table     ;-                                           |
|       60h  hi_desired_baud_rate        ;\ ;<-- for TTY/UART (default=9600 decimal)  
|       64h  hi_dbglog_config            ;                                            |
|       68h  hi_end_RAM_reserve_sz       ;                                            |
|       6Ch  hi_mbox_io_block_sz         ;/                                           |
|       70h  hi_num_bpatch_streams       ;-Unused (supposedly was used before 2010)   |
|       74h  hi_mbox_isr_yield_limit     ;-                                           |
|       78h  hi_refclk_hz                ;-OSC  ;NN,000,000 decimal (26MHz/40MHz)     |
|      Below seems to be newer stuff... not implemented in DSi... (?)                 |
|       7Ch  hi_ext_clk_detected         ;\                                           
|       80h  hi_dbg_uart_txpin           ;                                            |
|       84h  hi_dbg_uart_rxpin           ;                                            |
|       88h  hi_hci_uart_baud            ;     <-- used in 3DS WMI_READY_EVENT ?      |
|       8Ch  hi_hci_uart_pin_assignments ;/ ;<-- byte[0]=tx, [1]=rx, [2]=rts, [3]=cts |
|       90h  hi_hci_uart_baud_scale_val  ;\                                           
|       94h  hi_hci_uart_baud_step_val   ;/                                           |
|       98h  hi_allocram_start           ;\                                           
|       9Ch  hi_allocram_sz              ;/                                           |
|       A0h  hi_hci_bridge_flags         ;\                                           
|       A4h  hi_hci_uart_support_pins    ;/                                           |
|              ;NOTE: byte[0]=RESET pin (bit7 is polarity), byte[1..3]=for future use |
|       A8h  hi_hci_uart_pwr_mgmt_params ;-                                           |
|              ;Bit[1]:     0=UART FC active low, 1=UART FC active high               |
|              ;Bit[16-31]: wakeup timeout in ms                                      |
|       ACh  hi_board_ext_data           ;\Pointer to extended board Data, and        
|       B0h  hi_board_ext_data_config    ;/Config/flags (bit0=valid, bit16-31=size)   |
|       B4h  hi_reset_flag               ;\warmboot flags, valid when [B8h]=12345678h 
|       B8h  hi_reset_flag_valid         ;/                                           |
|       BCh  hi_hci_uart_pwr_mgmt_params_ext  ;-bit[0-31]: idle timeout in ms         |
|       C0h  hi_acs_flags                     ;-ACS flags                             |
|       C4h  hi_console_flags         ;                                               |
|       C8h  hi_nvram_state           ;                                               |
|       CCh  hi_option_flag2          ;                                               |
|       D0h  hi_sw_version_override   ;\If non-zero, override values sent to Host     
|       D4h  hi_abi_version_override  ;/in WMI_READY event                            |
|       D8h  hi_test_apps_related     ;-test applications flags                       |
|       DCh  hi_ota_testscript        ;-location of test script                       |
|       E0h  hi_cal_data              ;-location of CAL data                          |
|       E4h..FFh      ;reserved                                                       |
|       FCh  reserved, but 3DS sets this to 00000003h along hi_board_data_initialized |
+-------------------------------------------------------------------------------------+
```


### LOCAL_SCRATCH\[0\] - AR6K option bits, to enable/disable various features
By default, all option bits are 0.

```
+-----------------------------------------------------------------------------------+
|       AR6K_OPTION_BMI_DISABLE   = 01h  ;bit0 Disable BMI comm with Host           |
|       AR6K_OPTION_SERIAL_ENABLE = 02h  ;bit1 Enable UART serial port TTY messages |
|       AR6K_OPTION_WDT_DISABLE   = 04h  ;bit2 WatchDog Timer override              |
|       AR6K_OPTION_SLEEP_DISABLE = 08h  ;bit3 Disable system sleep                 |
|       AR6K_OPTION_STOP_BOOT     = 10h  ;bit4 Stop boot processes (for ATE)        |
|       AR6K_OPTION_ENABLE_NOANI  = 20h  ;bit5 Operate without ANI                  |
|       AR6K_OPTION_DSET_DISABLE  = 40h  ;bit6 Ignore DataSets                      |
|       AR6K_OPTION_IGNORE_FLASH  = 80h  ;bit7 Ignore flash during bootup           |
+-----------------------------------------------------------------------------------+
```


### targaddr\[10h\] - hi_option_flag

```
+------------------------------------------------------------------------------------+
|       0     HI_OPTION_TIMER_WAR         ;Enable timer workaround                   |
|       1     HI_OPTION_BMI_CRED_LIMIT    ;Limit BMI command credits                 |
|       2     HI_OPTION_RELAY_DOT11_HDR   ;Relay Dot11 hdr to/from host              |
|       3     HI_OPTION_MAC_ADDR_METHOD   ;MAC addr method 0=locally administred     |
|                                         ;                1=globally unique addrs   |
|       4     HI_OPTION_ENABLE_RFKILL     ;RF Kill Enable Feature                    |
|       5     HI_OPTION_ENABLE_PROFILE    ;Enable CPU profiling                      |
|       6     HI_OPTION_DISABLE_DBGLOG    ;Disable debug logging                     |
|       7     HI_OPTION_SKIP_ERA_TRACKING ;Skip Era Tracking                         |
|       8     HI_OPTION_PAPRD_DISABLE     ;Disable PAPRD (debug)                     |
|       9-11  HI_OPTION_NUM_DEV           ;num dev (3bit)                            |
|       12-27 HI_OPTION_DEV_MODE          ;dev mode (16bit) (aka 4xMODE, 4xSUBMODE?) |
|       28    HI_OPTION_NO_LFT_STBL       ;Disable LowFreq LF Timer Stabilization    |
|       29    HI_OPTION_SKIP_REG_SCAN     ;Skip regulatory scan                      |
|       30    HI_OPTION_INIT_REG_SCAN     ;Do regulatory scan during init before     |
|                                         ; sending WMI ready event to host          |
|       31    HI_OPTION_FW_BRIDGE         ;Firmware bridging                         |
+------------------------------------------------------------------------------------+
```

Two bits of hi_option_flag are used to represent 3 (three?) modes

```
+-----------------------------------------------------------------------+
|       HI_OPTION_FW_MODE_IBSS         = 00h   ;IBSS Mode               |
|       HI_OPTION_FW_MODE_BSS_STA      = 01h   ;STA Mode                |
|       HI_OPTION_FW_MODE_AP           = 02h   ;AP Mode                 |
|       HI_OPTION_FW_MODE_BT30AMP      = 03h   ;BT30 AMP Mode           |
+-----------------------------------------------------------------------+
```

Two bits of hi_option flag are used to represent 4 submodes (aka DEV_MODE?)

```
+-----------------------------------------------------------------------+
|       HI_OPTION_FW_SUBMODE_NONE      = 00h   ;Normal mode             |
|       HI_OPTION_FW_SUBMODE_P2PDEV    = 01h   ;p2p device mode         |
|       HI_OPTION_FW_SUBMODE_P2PCLIENT = 02h   ;p2p client mode         |
|       HI_OPTION_FW_SUBMODE_P2PGO     = 03h   ;p2p go mode             |
+-----------------------------------------------------------------------+
```

Fw Mode/SubMode Mask

```
+------------------------------------------------------------------------------------+
|       .--------.-------.-------.-------.-------.-------.-------.-------.           |
|       |  SUB   |  SUB  |  SUB  | SUB   |       |       |       |       |           |
|       |MODE[3] |MODE[2]|MODE[1]|MODE[0]|MODE[3]|MODE[2]|MODE[1]|MODE[0]|           |
|       |  (2)   |  (2)  |  (2)  |  (2)  |  (2)  |  (2)  |  (2)  |  (2)  |           |
|       '--------'-------'-------'-------'-------'-------'-------'-------'           |
|       HI_OPTION_FW_MODE_BITS         0x2                                    ;\     
|       HI_OPTION_FW_MODE_MASK         0x3                                    ; MODE |
|       HI_OPTION_FW_MODE_SHIFT        0xC    ;bit12-13 (2bit) per device?    ;      |
|       HI_OPTION_ALL_FW_MODE_MASK     0xFF   ;bit12-19 (8bit) per 4 devices? ;/     |
|       HI_OPTION_FW_SUBMODE_BITS      0x2                                    ;\     
|       HI_OPTION_FW_SUBMODE_MASK      0x3                                    ; SUB- |
|       HI_OPTION_FW_SUBMODE_SHIFT     0x14   ;bit20-21 (2bit) per device?    ; MODE |
|       HI_OPTION_ALL_FW_SUBMODE_MASK  0xFF00 ;bit20-27 (8bit) per 4 devices? ;      |
|       HI_OPTION_ALL_FW_SUBMODE_SHIFT 0x8                                    ;/     |
+------------------------------------------------------------------------------------+
```


### targaddr\[CCh\] - hi_option_flag2

```
+-------------------------------------------------------------------------------------+
|       0     HI_OPTION_OFFLOAD_AMSDU  ;aka OFFLAOD                                   |
|       1     HI_OPTION_DFS_SUPPORT              ;-only in newer code from 2011 or so |
|       2     HI_OPTION_ENABLE_RFKILL            ;\                                   
|       3     HI_OPTION_RADIO_RETENTION_DISABLE  ;                                    |
|       4     HI_OPTION_EARLY_CFG_DONE           ; only in newer code from 2015 or so |
|       5     HI_OPTION_DISABLE_CDC_MAX_PERF_WAR ;                                    |
|       6     HI_OPTION_USE_EXT_LDO              ;                                    |
|       7     HI_OPTION_DBUART_SUPPORT           ;                                    |
|       8     Reserved?                          ;                                    |
|       9     HT_OPTION_GPIO_WAKEUP_SUPPORT ;HT? ;/                                   |
|       10-31 Reserved                                                                |
+-------------------------------------------------------------------------------------+
```


### targaddr\[B4h\] - hi_reset_flag (warmboot flags, valid when \[B8h\]=12345678h)
hi_reset_flag is used to do some stuff when target reset. such as restore app_start after warm reset or preserve host Interest area, or preserve ROM data, literals, etc.

```
+-------------------------------------------------------------------------------------+
|       0     HI_RESET_FLAG_PRESERVE_APP_START     ;preserve App Start address        |
|       1     HI_RESET_FLAG_PRESERVE_HOST_INTEREST ;preserve Host Interest            |
|       2     HI_RESET_FLAG_PRESERVE_ROMDATA       ;preserve ROM data                 |
|       3     HI_RESET_FLAG_PRESERVE_NVRAM_STATE                                      |
|       4     HI_RESET_FLAG_PRESERVE_BOOT_INFO   ;\only in newer code from 2015 or so 
|       5     HI_RESET_FLAG_WARM_RESET           ;/                                   |
|       6-31  Reserved                                                                |
+-------------------------------------------------------------------------------------+
```


### targaddr\[C0h\] - hi_acs_flags

```
+-----------------------------------------------------------------------+
|       0     HI_ACS_FLAGS_ENABLED            ;ACS is enabled           |
|       1     HI_ACS_FLAGS_USE_WWAN           ;Use physical WWAN device |
|       2     HI_ACS_FLAGS_TEST_VAP           ;Use test VAP             |
|       3-31  Reserved                                                  |
+-----------------------------------------------------------------------+
```


### targaddr\[C4h\] - hi_console_flags

```
+-----------------------------------------------------------------------------+
|       0-2   HI_CONSOLE_FLAGS_UART           ;UART ID     (0=Default)        |
|       3     HI_CONSOLE_FLAGS_BAUD_SELECT    ;Baud Select (0=9600, 1=115200) |
|       4-30  Reserved                                                        |
|       31    HI_CONSOLE_FLAGS_ENABLE         ;Enable Console                 |
+-----------------------------------------------------------------------------+
```


### targaddr\[D8h\] - Bitmap for hi_test_apps_related

```
+-----------------------------------------------------------------------+
|       0     HI_TEST_APPS_TESTSCRIPT_LOADED                            |
|       1     HI_TEST_APPS_CAL_DATA_AVAIL                               |
|       2-31  Reserved                                                  |
+-----------------------------------------------------------------------+
```


Convert a Target virtual address into a Target physical address

```
+------------------------------------------------------------------------------------+
|       AR6002_VTOP(vaddr)   = ((vaddr) & 0x001fffff)  ;\uh, 2Mbyte space?           
|       AR6003_VTOP(vaddr)   = ((vaddr) & 0x001fffff)  ;/(shouldn't that be 4Mbyte?) |
|       MCKINLEY_VTOP(vaddr) = ((vaddr))   ;whatever, maybe uses a different CPU/HW  |
+------------------------------------------------------------------------------------+
```


Override REV2 ROM\'s app start address (whatever crap, doesn\'t apply to DSi)

```
+-----------------------------------------------------------------------+
|       AR6002_REV2_APP_START_OVERRIDE      0x911A00  ;\                
|       AR6002_REV2_DATASET_PATCH_ADDRESS   0x52D8B0  ; AR6002          |
|       AR6002_REV2_APP_LOAD_ADDRESS        0x502070  ;/                |
|       AR6003_REV2_APP_START_OVERRIDE      0x944C00  ;\                
|       AR6003_REV2_APP_LOAD_ADDRESS        0x543180  ;                 |
|       AR6003_REV2_BOARD_EXT_DATA_ADDRESS  0x57E500  ; AR6003 REV2     |
|       AR6003_REV2_DATASET_PATCH_ADDRESS   0x57E884  ;                 |
|       AR6003_REV2_RAM_RESERVE_SIZE        6912      ;/                |
|       AR6003_REV3_APP_START_OVERRIDE      0x945D20  ;\                
|       AR6003_REV3_APP_LOAD_ADDRESS        0x545000  ;                 |
|       AR6003_REV3_BOARD_EXT_DATA_ADDRESS  0x542330  ; AR6003 REV3     |
|       AR6003_REV3_DATASET_PATCH_ADDRESS   0x57FEC8  ;                 |
|       AR6003_REV3_RAM_RESERVE_SIZE        512       ;                 |
|       AR6003_REV3_RAM_RESERVE_SIZE_TCMD   4352      ;/                |
+-----------------------------------------------------------------------+
```




