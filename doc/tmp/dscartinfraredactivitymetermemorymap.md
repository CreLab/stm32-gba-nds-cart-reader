# DS Cart Infrared Activity Meter Memory Map


The most important RAM locations are FCE8h=Total steps, and FB9Ch=Unique ID (when using multiple Activity Meters), FCF0h=Daily Goal (to change LED color after N steps). Nintendo is reading/writing a few more RAM locations. And, there are ring buffers with steps per minute/hour/day in EEPROM.

### Activity Meter SFR Usage

```
+-------------------------------------------------------------------------------------+
|       [0FFD4h].0  Port 1 Data bit0 IN   Factory Test (0=Test, 1=Normal)             |
|       [0FFD4h].2  Port 1 Data bit2 OUT  Set for sum of eight A/D conversions        |
|       [0FFD6h].0  Port 3 Data bit0 OUT  IrDA PWDOWN (1=disable IrDA RX)             |
|       [0FFD6h].1  Port 3 Data bit1 IN   IrDA RXD  ;\via serial IrDA registers       
|       [0FFD6h].2  Port 3 Data bit2 OUT  IrDA TXD  ;/                                |
|       [0FFDBh].2  Port 8 Data bit2 OUT  LED color?                                  |
|       [0FFDBh].3  Port 8 Data bit3 OUT  LED color?                                  |
|       [0FFDCh].0  Port 9 Data bit0 OUT  SPI EEPROM chipselect (0=select)            |
|       [0FFDEh].0  Port B Data bit0 IN   Button input                                |
|       IrDA  IR Transfers                                                            |
|       SPI   SPI 8Kbyte EEPROM                                                       |
|       A/D   Used to read two single-axis sensors (for step counting)?               |
|       A/D   Also used to read sum of eight A/D conversions (for wakeup from sleep)? |
+-------------------------------------------------------------------------------------+
```

The SPI EEPROM uses same commands as NDS cart savedata:
- [DS Cartridge Backup](./dscartridgebackup.md)

### Activity Meter RAM (1Kbyte, FB80h-FF7Fh)

```
+-------------------------------------------------------------------------------------+
|       FB80h 1   Button flags (bit7=curr.state, bit6=newly.pressed, bit5=old.state)  |
|       FB81h 1   ... cleared if memread src was unique_id (and other cases)          |
|       FB82h 1   ... sys/power mode ?                                                |
|       FB83h 1   ... adc_mode, or power_saving?                                      |
|       FB84h 1   ... clock change request                                            |
|       FB85h 1   ... led_extra_mask (never CLEARED, except on boot, or maybe via IR) |
|       FB86h 1   adc_array_index (index in ADC array X/Y, wraps in range 00h..3Fh)   |
|       FB87h 1   ... entrysize of current data in ringbuf (per newest TAG) or so?    |
|       FB88h 1   SPI overrun error (probably nonsense, SPI clk can't outrun itself)  |
|       FB89h 1   Unused                                                              |
|       FB8Ah 1   num_steps_curr_minute (00h..FCh) (no conflict with tag FDh,FEh,FFh) |
|       FB8Bh 1   rtc_event_flags (bit0=minute, bit1=hour, bit2=day, bit3=also.hour)  |
|       FB8Ch 1   ... timing offhold for various stuff                                |
|       FB8Dh 1   some_shift_amount         ;READ via IR                              |
|       FB8Eh 1   Daily goal reached flag (aka LED color) (bit0=reached, bit1=???)    |
|       FB8Fh 1   ... timing for LED step pulses?                                     |
|       FB90h 1   ... timing for LED step pulses?                                     |
|       FB91h 1   ... flag for LED step pulse state?                                  |
|       FB92h 1   Hour when new day starts (BCD, usually/always 03h)   ;READ via IR   |
|       FB93h 1   ... some flag for inactivity low-power mode ?                       |
|       FB94h 1   LED animation number (1..5, or 0=none) (factory test result)        |
|       FB95h 1   Unused                                                              |
|       FB96h 1   New day flag                                                        |
|       FB97h 1   Fixed LED mask (this is a "fixed" setting from EEPROM)              |
|       FB98h 1   Compare_ctrl_0  ;\for "Compare Control" HW registers (89h,89h)      
|       FB99h 1   Compare_ctrl_1  ;/                                                  |
|       FB9Ah 1   New Goal flag (apply [FCF4h] as new goal, starting on next day?)    |
|       FB9Bh 1   Unused                                                              |
|       FB9Ch 28h Unique ID ;READ via IR (initally set by NDS via RAM+EEPROM writes?) |
|       FBC4h 2   adc_current_x                                                       |
|       FBC6h 2   adc_current_y                                                       |
|       FBC8h 80h adc_array_x (40h x 16bit)                                           |
|       FC48h 80h adc_array_y (40h x 16bit)                                           |
|       FCC8h 2   adc_scale_factor_x  ;\scale factors                                 
|       FCCAh 2   adc_scale_factor_y  ;/                                              |
|       FCCCh 2   adc_scale_unused_z  ;\semi-unused (written, but never read)         
|       FCCEh 2   adc_scale_unused_t  ;/                                              |
|       FCD0h 2   ringbuf_mm_index (0020h..16A0h)   ;READ via IR                      |
|       FCD2h 2   ringbuf_hh_index (16A1h..1C42h)   ;READ via IR                      |
|       FBD4h 2   Unused                                                              |
|       FCD6h 2   ringbuf_dd_index (1C43h..1CDEh)   ;READ via IR                      |
|       FCD8h 2   num_steps_curr_hour    (16bit step counter for current hour)        |
|       FCDAh 2   ringbuf_stepback_index (result from cmd_2Ah, to be read by cmd_0Ah) |
|       FCDCh 2   adc_inactivity_timer   (time since last pedometer step)             |
|       FCDEh 2   SPI overrun error counter (related to flag at FB88h)                |
|       FCE0h 2   Unused                                                              |
|       FCE2h 2   adc_current_sum (sum of eight A/D conversions)                      |
|       FCE4h 4   seconds_counter (seconds since 1st Jan 2001?, initially 0D2B0B80h)  |
|       FCE8h 4   num_steps_lifelong (lifelong TOTAL steps)                           |
|       FCECh 4   num_steps_today    (step counter, for current day)                  |
|       FCF0h 4   Daily_goal         (WRITTEN via IR, NDS cart default=3000 decimal)  |
|       FCF4h 4   new_goal_steps     (somewhat reload value for daily goal?)          |
|       FCF8h 18h Unused                                                              |
|       FD10h 2   main_callback (main_adc_button_callback, or ir_callback)            |
|       FD12h 40h ir_tx_data    (buffer for Memory & EEPROM reads)                    |
|       FD52h 2   clk_callback  (clk_whatever_callback, or 0=none)                    |
|       FD54h 2   ir_callback   (ir_active_callback, or ir_dummy_callback)            |
|       FD56h 2   ir_timestamp_last_byte (for sensing SHORT GAPs, aka end-of-packet)  |
|       FD58h 2   RX chksum from hdr[2..3]                                            |
|       FD5Ah 2   RX chksum from calculation                                          |
|       FD5Ch 2   ir_timestamp_last_xfer (for sensing LONG GAPs, aka sleep mode)      |
|       FD5Eh 1   Unused                                                              |
|       FD5Fh 1   ir_rx_len                                                           |
|       FD60h 1   ... semi-unused (set to 00h?) (but never read)                      |
|       FD61h 44h ir_rxtx_buf, hdr[4]+data[40h]                                       |
|       FDA5h 1   ir_tx_hdr_len    ;\memorized TX len+hdr[4]                          
|       FDA6h 4   ir_tx_hdr_copy   ;/(never actually used)                            |
|       FDAAh 1   bad_chksum_count, give up sending bad_chksum replies after 3 errors |
|       FDABh 1   bad_chksum_flag, request reply_FCh (bad_chksum)                     |
|       FDACh 80h ... array (40h x 16bit)          ;\                                 
|       FE2Ch 80h ... array (40h x 16bit)          ; analog sine/cosine               |
|       FEACh 4   ... dword                        ; stuff for converting             |
|       FEB0h 4   ... dword                        ; adc to step counter?             |
|       FEB4h 1   ... byte                         ;                                  |
|       FEB5h 1   ... byte                         ;/                                 |
|       FEB6h 2   Incremented in main_adc_button_callback (but not used elsewhere)    |
|       FEB8h 1   Unused                   ;\maybe meant to be 4-byte tx hdr,         
|       FEB9h 1   TX sequence number       ; but only hdr[1] used (as increasing      |
|       FEBAh 2   Unused                   ;/seq.no for memory read/write replies)    |
|       FEBCh 4   ... array (2 x 16bit)                                               |
|       FEC0h 4   ... array (2 x 16bit)                                               |
|       FEC4h 4   ... array (2 x 16bit)                                               |
|       FEC8h 4   ... array (2 x 16bit)                                               |
|       FECEh B2h CPU Stack area, initial SP=FF80h                                    |
+-------------------------------------------------------------------------------------+
```


### Activity Meter EEPROM (8Kbytes, serial SPI bus)

```
+------------------------------------------------------------------------------------+
|       EEPROM:0000h 9     ID "nintendo",00h (9 bytes)                               |
|       EEPROM:0009h 17h   Unused (FFh-filled)                                       |
|       EEPROM:0020h 1681h Ringbuf_mm ;steps per MINUTE for 4 days ;(24*60*4-1)*8bit |
|       EEPROM:16A1h 5A2h  Ringbuf_hh ;steps per HOUR for 30 days  ;(24*30+1)*16bit  |
|       EEPROM:1C43h 9Ch   Ringbuf_dd ;steps per DAY for 52 days   ;(52)*24bit       |
|       EEPROM:1CDFh 1     Unused (FFh) (padding ringbuf's to 20h-byte-boundary)     |
|       EEPROM:1CE0h 200h  Unused (FFh-filled)                                       |
|       EEPROM:1EE0h 8+1   ADC_scale_values (4x16bit) ;RAM:FCC8h ;\                  
|       EEPROM:1EE9h 2+1   ADC sum_limit              ;RAM:stack ; these EEPROM      |
|       EEPROM:1EECh 3     Unused                                ; settings          |
|       EEPROM:1EEFh 4+1   Num_steps_lifelong         ;RAM:FCE8h ; have 1-byte       |
|       EEPROM:1EF4h 1+1   Fixed LED Mask             ;RAM:FB97h ; checksums         |
|       EEPROM:1EF6h 2     Unused                                ; appended, and     |
|       EEPROM:1EF8h 1+1   Some_shift_amount          ;RAM:FB8Dh ; backups at        |
|       EEPROM:1EFAh 4+1   Daily_goal                 ;RAM:FCF0h ; 1F40h-1F9Fh       |
|       EEPROM:1EFFh 4+1   New_goal_steps             ;RAM:FCF4h ;                   |
|       EEPROM:1F04h 28h+1 Unique ID                  ;RAM:FB9Ch ;                   |
|       EEPROM:1F2Dh 13h   Unused (00h-filled)                   ;/                  |
|       EEPROM:1F40h 60h   Backup copies of above data at 1EE0h..1F3Fh ;-backups     |
|       EEPROM:1FA0h 2     Error code     (initially FFFFh)                          |
|       EEPROM:1FA2h 1     Reboot counter (initially 00h or 01h ?)                   |
|       EEPROM:1FA3h 5Dh   Unused (FFh-filled)                                       |
+------------------------------------------------------------------------------------+
```

The MM/HH/DD ring buffers are steps per minute/hour/day accordingly, mixed with special tags:

```
+-------------------------------------------------------------------------------------+
|       00xxh          Zero steps for N minutes (N=max FCh)       ;\in ringbuf_mm     
|       xxh            N steps per minute (N=01h..FCh)            ;/                  |
|       xxxxh          N steps per hour (N=0000h..FFFFh)          ;-in ringbuf_hh     |
|       xxxxxxh        N steps per day (N=000000h..FFFFFFh)       ;-in ringbuf_dd     |
|       FDxxxxxxxxxxh  Timestamp, reversed-BCD-digit-order, seconds since 2001 or so? |
|       FEh            Newest entry marker?                                           |
|       FFh            Unused entry marker?                                           |
+-------------------------------------------------------------------------------------+
```

The firmware contains code for searching tags FDh/FEh/FFh forwards and backwards, that works well with BCD values and 8bit counters, but unknown it can work with the 16bit/24bit counters. The BCD digits are stored backwards (eg. 12345 = FD5432100000h). Rinbuf pointers can be read from RAM locations FCD0h, FCD2h, FCD6h, and FCDAh).



