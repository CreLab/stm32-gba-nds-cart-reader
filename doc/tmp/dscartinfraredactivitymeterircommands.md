# DS Cart Infrared Activity Meter IR Commands


### Packet Encryption/Checksumming
Nintendo wants all IR packet bytes to be \"encrypted\" (XORed by AAh), that encryption/decryption must be done on ARM side. The checksums are calculated as so (on decrypted packets):

```
+---------------------------------------------------------------------------------+
|       sum=0, packet[2,3]=00h,00h                    ;-initial chksum            |
|       for i=0 to size-1                                                         |
|         if (i and 1)=0 then sum=sum+packet[i]*100h  ;\add in big-endian fashion 
|         if (i and 1)=1 then sum=sum+packet[i]       ;/                          |
|       sum=(sum/10000h)+(sum AND FFFFh)              ;\final adjust              
|       sum=(sum/10000h)+(sum)                        ;/                          |
|       packet[2,3]=sum,sum/100h                      ;-store in little-endian    |
+---------------------------------------------------------------------------------+
```

The packets are transferred at 115200 baud, 8n1. End of Packet is indicated by a pause in the IR transmission (that does also indicate the packet size).
Before sending a command packet, one should always wait for incoming data from the Activity Meter (ie. for the FCh byte, or for Reply/ChecksumError responses for previous command).

### Activity Meter IR commands (from NDS):

```
+------------------------------------------------------------------------------------+
|       08,xx,cc,cc,msb,lsb,data[..]  CPU Memory Write    (len=3Eh max)  ;Reply=08   |
|       0A,xx,cc,cc,msb,lsb,len       CPU Memory Read     (len=40h max)  ;Reply=0A   |
|       0A,xx,cc,cc,FB,9C,len         CPU Memory Read FB9Ch with ClrFlag ;Reply=0A   |
|       20,xx,cc,cc,msb,lsb,data[..]  Serial EEPROM Write (len=3Eh max)  ;Reply=20   |
|       22,xx,cc,cc,msb,lsb,len       Serial EEPROM Read  (len=40h max)  ;Reply=22   |
|       24,00,cc,cc,ss,ss,ss,ss       Update Ringbuf_mm    ;\            ;Reply=24   
|       24,01,cc,cc,ss,ss,ss,ss       Update Ringbuf_hh    ; and set     ;Reply=24   |
|       24,02,cc,cc,ss,ss,ss,ss       Update Ringbuf_dd    ; 32bit       ;Reply=24   |
|       24,03,cc,cc,ss,mm,hh          Set RTC hh:mm:ss     ; seconds     ;Reply=24   |
|       24,04,cc,cc,ss,ss,ss,ss       Raw Set ssssssss ?   ;/            ;Reply=24   |
|       24,xx,cc,cc,ss,ss,ss,ss       Invalid (same as 24,04)            ;Reply=24   |
|       26,xx,cc,cc                   Deadlock   ;\both same (maybe      ;Reply=26   
|       28,xx,cc,cc                   Deadlock   ;/Watchdog/reboot?)     ;Reply=26   |
|       2A,xx,cc,cc,00,nn             Stepback Ringbuf_hh  ;\go back nn  ;Reply=2A   
|       2A,xx,cc,cc,01,nn             Stepback Ringbuf_mm  ; entries,    ;Reply=2A   |
|       2A,xx,cc,cc,02,nn             Stepback Ringbuf_dd  ;/see [FCDAh] ;Reply=2A   |
|       2A,xx,cc,cc,xx,..             Invalid                            ;Reply=2A   |
|       2C,cs,cc,cc                   Toggle one LED on/off              ;Reply=2C   |
|       F4,xx,cc,cc                   Disconnect                         ;Reply=None |
|       F6,xx,cc,cc                   Force "Bad Chksum" reply           ;Reply=FC   |
|       FA,xx,cc,cc                   Connect                            ;Reply=F8   |
|       FE,...                        Noise      ;\ignored, noise        ;Reply=None 
|       FF,...                        Noise      ;/                      ;Reply=None |
|       xx,xx,cc,cc                   Invalid    ;-ignored, invalid cmd  ;Reply=None |
|       xx,xx,xx,xx                   Bad Chksum                         ;Reply=FC   |
+------------------------------------------------------------------------------------+
```


### Activity Meter IR replies (to NDS):

```
+-----------------------------------------------------------------------------------+
|       08,sq,cc,cc           Reply to Cmd 08 (CPU Memory Write reply)              |
|       0A,sq,cc,cc,data[..]  Reply to Cmd 0A (CPU Memory Read reply)               |
|       20,sq,cc,cc           Reply to Cmd 20 (Serial EEPROM Write reply)           |
|       22,sq,cc,cc,data[..]  Reply to Cmd 22 (Serial EEPROM Read reply)            |
|       26,xx,cc,cc           Reply to Cmd 26 and 28 (Deadlock reply)               |
|       24,xx,cc,cc           Reply to Cmd 24 (Update, or Set RTC time)             |
|       2A,xx,cc,cc           Reply to Cmd 2A (Stepback, with result at [FCDAh])    |
|       2C,cs,cc,cc           Reply to Cmd 2C (LED reply)                           |
|       80,FF,cc,cc           Factory Reset and Hardware Test completed (or failed) |
|       F8,00,cc,cc           Reply to Cmd FA (Connect reply)                       |
|       FC,xx,cc,cc           Reply to Cmd's with Bad Chksum (and Cmd F6)           |
|       FC                    Advertising Msg (after pressing button) (single byte) |
+-----------------------------------------------------------------------------------+
```


### Notes

```
+----------------------------------------------------------------------------------+
|       cc,cc        Checksum (LITTLE-ENDIAN)                                      |
|       msb,lsb      Memory Address (big-endian)                                   |
|       ss,ss,ss,ss  Seconds since 2001 (big-endian)                               |
|       ss,mm,hh     RTC time HH:MM:SS (BCD) (caution: smashes seconds since 2001) |
|       sq           Increasing sequence number in Memory Access replies           |
|       cs           LED color/state (c=color red/green, s=state on/off)           |
|       xx           Whatever (don't care?)                                        |
+----------------------------------------------------------------------------------+
```

There aren\'t any specific commands for reading things like step counters, one must instead use the Memory Read/Write commands with hardcoded RAM or EEPROM address, see:
- [DS Cart Infrared Activity Meter Memory Map](./dscartinfraredactivitymetermemorymap.md)
The command/reply are intended to be transferred from/to NDS accordingly, but things could go wrong if there are multiple consoles or activity meters (all trying to process the same message, or even mistreating replies as commands).
The infrared range (distance/angle) is unknown. Dumping the whole 64K CPU memory space worked without checksum errors at about 5-10cm distance (and that worked without even using the Connect command).



