# AUX Xboo Burst Boot Backdoor


When writing Xboo compatible programs, always include a burst boot \"backdoor\", this will allow yourself (and other people) to upload programs much faster as when using the normal GBA BIOS multiboot function. Aside from the improved transmission speed, there\'s no need to reset the GBA each time (eventually manually if you do not have reset connect), without having to press Start+Select (if cartridge inserted), and, most important, the time-consuming nintendo-logo intro is bypassed.

### The Burst Boot Protocol
In your programs IRQ handler, add some code that watches out for burst boot IRQ requests. When sensing a burst boot request, download the actual boot procedure, and pass control to that procedure.

```
+--------------------------------------------------------------------------------+
|       Send (PC)    Reply (GBA)                                                 |
|       "BRST"       "BOOT"        ;request burst, and reply <prepared> for boot |
|       <wait 1/16s> <process IRQ> ;long delay, allow slave to enter IRQ handler |
|       llllllll     "OKAY"        ;send length in bytes, reply <ready> to boot  |
|       dddddddd     --------      ;send data in 32bit units, reply don't care   |
|       cccccccc     cccccccc      ;exchange crc (all data units added together) |
+--------------------------------------------------------------------------------+
```

Use normal mode, 32bit, external clock for all transfers. The received highspeed loader (currently approx. 180h bytes) is to be loaded to and started at 3000000h, which will then handle the actual download operation.

Below is an example program which works with multiboot, burstboot, and as normal rom/flashcard. The source can be assembled with a22i (the no\$gba built-in assembler, see no\$gba utility menu). When using other/mainstream assemblers, you\'ll eventually have to change some directives, convert numbers from NNNh into 0xNNN format, and define the origin somewhere in linker/makefile instead of in source code.


```
+-------------------------------------------------------------------------------------+
|      .arm            ;select 32bit ARM instruction set                              |
|      .gba            ;indicate that it's a gameboy advance program                  |
|      .fix            ;automatically fix the cartridge header checksum               |
|      org 2000000h    ;origin in RAM for multiboot-cable/no$gba-cutdown programs     |
|      ;------------------                                                            |
|      ;cartridge header/multiboot header                                             |
|       b     rom_start                ;-rom entry point                              |
|       dcb   ...insert logo here...   ;-nintento logo (156 bytes)                    |
|       dcb   'XBOO SAMPLE '           ;-title (12 bytes)                             |
|       dcb   0,0,0,0,  0,0            ;-game code (4 bytes), maker code (2 bytes)    |
|       dcb   96h,0,0                  ;-fixed value 96h, main unit code, device type |
|       dcb   0,0,0,0,0,0,0            ;-reserved (7 bytes)                           |
|       dcb   0                        ;-software version number                      |
|       dcb   0                        ;-header checksum (set by .fix)                |
|       dcb   0,0                      ;-reserved (2 bytes)                           |
|       b     ram_start                ;-multiboot ram entry point                    |
|       dcb   0,0                      ;-multiboot reserved bytes (destroyed by BIOS) |
|       dcb   0,0                      ;-blank padded (32bit alignment)               |
|      ;------------------                                                            |
|      irq_handler:  ;interrupt handler (note: r0-r3 are pushed by BIOS)              |
|       mov    r1,4000000h             ;\get I/O base address,                        
|       ldr    r0,[r1,200h] ;IE/IF     ; read IE and IF,                              |
|       and    r0,r0,r0,lsr 16         ; isolate occurred AND enabled irqs,           |
|       add    r3,r1,200h   ;IF        ; and acknowledge these in IF                  |
|       strh   r0,[r3,2]               ;/                                             |
|       ldrh   r3,[r1,-8]              ;\mix up with BIOS irq flags at 3007FF8h,      
|       orr    r3,r3,r0                ; aka mirrored at 3FFFFF8h, this is required   |
|       strh   r3,[r1,-8]              ;/when using the (VBlank-)IntrWait functions   |
|       and    r3,r0,80h ;IE/IF.7 SIO  ;\                                             
|       cmp    r3,80h                  ; check if it's a burst boot interrupt         |
|       ldreq  r2,[r1,120h] ;SIODATA32 ; (if interrupt caused by serial transfer,     |
|       ldreq  r3,[msg_brst]           ; and if received data is "BRST",              |
|       cmpeq  r2,r3                   ; then jump to burst boot)                     |
|       beq    burst_boot              ;/                                             |
|       ;... insert your own interrupt handler code here ...                          |
|       bx     lr                      ;-return to the BIOS interrupt handler         |
|      ;------------------                                                            |
|      burst_boot:     ;requires incoming r1=4000000h                                 |
|       ;... if your program uses DMA, disable any active DMA transfers here ...      |
|       ldr   r4,[msg_okay]            ;\                                             
|       bl    sio_transfer             ; receive transfer length/bytes & reply "OKAY" |
|       mov   r2,r0 ;len               ;/                                             |
|       mov   r3,3000000h   ;dst       ;\                                             
|       mov   r4,0  ;crc               ;                                              |
|      @@lop:                          ;                                              |
|       bl    sio_transfer             ; download burst loader to 3000000h and up     |
|       stmia [r3]!,r0      ;dst       ;                                              |
|       add   r4,r4,r0      ;crc       ;                                              |
|       subs  r2,r2,4       ;len       ;                                              |
|       bhi   @@lop                    ;/                                             |
|       bl    sio_transfer             ;-send crc value to master                     |
|       b     3000000h  ;ARM state!    ;-launch actual transfer / start the loader    |
|      ;------------------                                                            |
|      sio_transfer:  ;serial transfer subroutine, 32bit normal mode, external clock  |
|       str   r4,[r1,120h]  ;siodata32 ;-set reply/send data                          |
|       ldr   r0,[r1,128h]  ;siocnt    ;\                                             
|       orr   r0,r0,80h                ; activate slave transfer                      |
|       str   r0,[r1,128h]  ;siocnt    ;/                                             |
|      @@wait:                         ;\                                             
|       ldr   r0,[r1,128h]  ;siocnt    ; wait until transfer completed                |
|       tst   r0,80h                   ;                                              |
|       bne   @@wait                   ;/                                             |
|       ldr   r0,[r1,120h]  ;siodata32 ;-get received data                            |
|       bx    lr                                                                      |
|      ;---                                                                           |
|      msg_boot dcb 'BOOT'     ;\                                                     
|      msg_okay dcb "OKAY"     ; ID codes for the burstboot protocol                  |
|      msg_brst dcb "BRST"     ;/                                                     |
|      ;------------------                                                            |
|      download_rom_to_ram:                                                           |
|       mov  r0,8000000h  ;src/rom     ;\                                             
|       mov  r1,2000000h  ;dst/ram     ;                                              |
|       mov  r2,40000h/16 ;length      ; transfer the ROM content                     |
|      @@lop:                          ; into RAM (done in units of 4 words/16 bytes) |
|       ldmia [r0]!,r4,r5,r6,r7        ; currently fills whole 256K of RAM,           |
|       stmia [r1]!,r4,r5,r6,r7        ; even though the proggy is smaller            |
|       subs  r2,r2,1                  ;                                              |
|       bne   @@lop                    ;/                                             |
|       sub   r15,lr,8000000h-2000000h ;-return (retadr rom/8000XXXh -> ram/2000XXXh) |
|      ;------------------                                                            |
|      init_interrupts:                                                               |
|       mov  r4,4000000h               ;-base address for below I/O registers         |
|       ldr  r0,=irq_handler           ;\install IRQ handler address                  
|       str  r0,[r4,-4]   ;IRQ HANDLER ;/at 3FFFFFC aka 3007FFC                       |
|       mov  r0,0008h                  ;\enable generating vblank irqs                
|       strh r0,[r4,4h]   ;DISPSTAT    ;/                                             |
|       mrs  r0,cpsr                   ;\                                             
|       bic  r0,r0,80h                 ; cpu interrupt enable (clear i-flag)          |
|       msr  cpsr,r0                   ;/                                             |
|       mov  r0,0                      ;\                                             
|       str  r0,[r4,134h] ;RCNT        ; init SIO normal mode, external clock,        |
|       ldr  r0,=5080h                 ; 32bit, IRQ enable, transfer started          |
|       str  r0,[r4,128h] ;SIOCNT      ; output "BOOT" (indicate burst boot prepared) |
|       ldr  r0,[msg_boot]             ;                                              |
|       str  r0,[r4,120h] ;SIODATA32   ;/                                             |
|       mov  r0,1                      ;\interrupt master enable                      
|       str  r0,[r4,208h] ;IME=1       ;/                                             |
|       mov  r0,81h                    ;\enable execution of vblank IRQs,             
|       str  r0,[r4,200h] ;IE=81h      ;/and of SIO IRQs (burst boot)                 |
|       bx   lr                                                                       |
|      ;------------------                                                            |
|      rom_start:   ;entry point when booted from flashcart/rom                       |
|       bl   download_rom_to_ram       ;-download ROM to RAM (returns to ram_start)   |
|      ram_start:   ;entry point for multiboot/burstboot                              |
|       mov  r0,0feh                   ;\reset all registers, and clear all memory    
|       swi  10000h ;RegisterRamReset  ;/(except program code in wram at 2000000h)    |
|       bl   init_interrupts           ;-install burst boot irq handler               |
|       mov  r4,4000000h               ;\enable video,                                
|       strh r4,[r4,000h] ;DISPCNT     ;/by clearing the forced blank bit             |
|      @@mainloop:                                                                    |
|       swi  50000h ;VBlankIntrWait    ;-wait one frame (cpu in low power mode)       |
|       mov  r5,5000000h               ;\increment the backdrop palette color         
|       str  r8,[r5]                   ; (ie. display a blinking screen)              |
|       add  r8,r8,1                   ;/                                             |
|       b    @@mainloop                                                               |
|      ;------------------                                                            |
|      .pool                                                                          |
|      end                                                                            |
+-------------------------------------------------------------------------------------+
```




