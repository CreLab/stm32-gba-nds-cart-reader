# DSi Teak CPU Registers


### 36bit/40bit Accumulators: a0,a1,b0,b1

```
+------------------------------------------------------------------------+
|       a0e:a0h:a0l (4:16:16 bits) = a0 (36bit)    ;TL2: 40bit (8:16:16) |
|       a1e:a1h:a1l (4:16:16 bits) = a1 (36bit)    ;TL2: 40bit (8:16:16) |
|       b0e:b0h:b0l (4:16:16 bits) = b0 (36bit)    ;TL2: 40bit (8:16:16) |
|       b1e:b1h:b1l (4:16:16 bits) = b1 (36bit)    ;TL2: 40bit (8:16:16) |
+------------------------------------------------------------------------+
```

4bit snippets (bit32-35) of a0/a1 can be found in status registers (st0,st1). On TL2, the whole upper 8bit (bit32-39) of a0/a1/b0/b1 can be additionally accessed via push/pop (a0e,a1e,b0e,b1e).

### Teak General Registers: r0,r1,r2,r3,r4,r5,r6,r7

```
+---------------------------------------------------------------------------+
|       r0     ;TL  ;16bit  ;\                                              
|       r1     ;TL  ;16bit  ;                                               |
|       r2     ;TL  ;16bit  ; old TL1 registers                             |
|       r3     ;TL  ;16bit  ;                                               |
|       r4     ;TL  ;16bit  ;                                               |
|       r5     ;TL  ;16bit  ;/                                              |
|       r6     ;TL2 ;16bit  ;<-- new TL2 register                           |
|       r7     ;TL  ;16bit  ;<-- aka rb (with optional immediate, MemR7Imm) |
+---------------------------------------------------------------------------+
```


### 32bit Multiply Result and 16bit Muliply Parameters: p0,p1, and x0,y0,x1,y1

```
+------------------------------------------------------------------------------------+
|       x0     ;TL  ;16bit  ;-                                                       |
|       y0     ;TL  ;16bit  ;-                                                       |
|       x1     ;TL2 ;16bit  ;-                                                       |
|       y1     ;TL2 ;16bit  ;-                                                       |
|       p0     ;TL  ;33bit! ;\Px   ;TL2: 33bit p0e:p0 ?  ;TL1: 32bit?                
|       p1     ;TL2 ;33bit! ;/     ;TL2: 33bit p1e:p1 ?  ;TL1: N/A                   |
|       p0h    ;TL  ;16bit  ; ;<-- aka ph ;<-- called "p0" (aka "p") in "RegisterP0" |
+------------------------------------------------------------------------------------+
```

The \"load ps\" and \"load ps01\" opcodes allow to specify a multiply shifter, this is useful when dealing with signed/unsigned parameters:

```
+-----------------------------------------------------------------------+
|       Unsigned = Unsigned * Unsigned       ;use shift 0               |
|       Unsigned = Unsigned * Signed         ;use shift +1              |
|       Unsigned = Signed * Signed           ;use shift +2              |
|       Signed = Unsigned * Unsigned         ;use shift -1              |
|       Signed = Unsigned * Signed           ;use shift 0               |
|       Signed = Signed * Signed             ;use shift +1              |
+-----------------------------------------------------------------------+
```


### TeakLite Misc

```
+-------------------------------------------------------------------------------------+
|       pc     ;TL  ;18bit! ;-program counter (TL2: 18bit, TL1: 16bit)                |
|       sp     ;TL  ;16bit  ;-stack pointer (decreasing on push/call)                 |
|       sv     ;TL  ;16bit  ;-shift value (negative=right) (for shift-by-register)    |
|       mixp   ;TL  ;16bit  ;-related to min/max/mind/maxd                            |
|       lc     ;TL  ;16bit  ;-Loop Counter (of block repeat)                          |
|       repc   ;TL  ;16bit  ;-Repeat Counter (for "rep" opcode)                       |
|       dvm    ;TL  ;16bit  ;-Data Value Match (OCEM data breakpoints) (and for trap) |
+-------------------------------------------------------------------------------------+
```


### TeakLiteII Misc: vtr0,vtr1,prpage

```
+---------------------------------------------------------------------------+
|       vtr0   ;TL2 16bit   ;\related to vtrshr,vtrmov,vtrclr               
|       vtr1   ;TL2 16bit   ;/(saved C/C1 carry flags for Viterby decoding) |
|       prpage ;TL2 4bit    ;-??? (bit0-3 used/dangerous, bit4-15 always 0) |
+---------------------------------------------------------------------------+
```

vtr0,vtr1 are related to vtrshr,vtrmov,vtrclr opcodes (and multi-function opcodes with \"vtrshr\" suffix).
prpage isn\'t used by existing DSi code, setting the four write-able bits to nonzero seems to screw-up opcode fetching, causing code to crash (unless one of the next 1-2 prefetched opcodes restores prpage=0, which causes opcode fetching to recover; after skipping some following prefetched opcodes, until prpage=0 is applied). Maybe it\'s related to code access rights or waitstates\... it doesn\'t seem to be related to upper 2bit of the 18bit program counter (prpage is zero even when executing code above address 0FFFFh).

### Old Control/Status registers (TeakLite): st0,st1,st2,icr
### New Control/Status registers (TeakLiteII): stt0,stt1,stt2,mod0,mod1,mod2,mod3
- [DSi Teak CPU Control/Status Registers](./dsiteakcpucontrolstatusregisters.md)

### Address Config (TeakLiteII): ar0,ar1,arp0,arp1,arp2,arp3
### Address Step/Modulo: cfgi,cfgj (and TL2 stepi0,stepj0)
- [DSi Teak CPU Address Config/Step/Modulo](./dsiteakcpuaddressconfigstepmodulo.md)

### User-defined registers (optional off-core): ext0,ext1,ext2,ext3
The four ext registers are intended for custom hardware extensions (where they could be used as I/O ports, with faster & more direct access than memory mapped I/O).

```
+-----------------------------------------------------------------------+
|       ext0   ;TL  ;16bit                                              |
|       ext1   ;TL  ;16bit                                              |
|       ext2   ;TL  ;16bit                                              |
|       ext3   ;TL  ;16bit                                              |
+-----------------------------------------------------------------------+
```

In the DSi, the four register do exist (they are fully read/write-able), but unknown if they do have any special functions - or if they are just general-purpose data registers (existing DSi software isn\'t using the ext registers, and hardware is solely accessed via memory mapped I/O).

### Bitfields for Control/Status registers and cfgi/cfgj registers

```
+-----------------------------------------------------------------------------------+
|       page   ;TL  ;8bit "load" st1.bit0-7   (page for MemImm8)    ;aka "lpg"      |
|       ps     ;TL  ;2bit "load" st1.bit10-11 (product shifter for multiply?)       |
|       ps01   ;TL2 ;4bit "load" mod0...?     (maybe separate "ps" for p0 and p1 ?) |
|       movpd  ;TL2 ;2bit "load" stt2.bit6-7  (page for reading DATA from ProgMem)  |
|       modi   ;TL  ;9bit "load" cfgi.bit7-15 =imm9                                 |
|       modj   ;TL  ;9bit "load" cfgj.bit7-15 =imm9                                 |
|       stepi  ;TL  ;7bit "load" cfgi.bit0-6  =imm7                                 |
|       stepj  ;TL  ;7bit "load" cfgj.bit0-6  =imm7                                 |
+-----------------------------------------------------------------------------------+
```


### Shadow Registers
Some registers (or in case of st0-st2: fractions thereof) exist as \"shadows\"\... related to \"cntx\", \"swap\", \"banke\" (and maybe \"bankr\"?) opcodes, and \"reti/retid\" opcodes with \"context\" suffix, and interrupts with context switching enabled.

```
+---------------------------------------------------------------------------+
|       st0  bit0,2-11                        ;\control/status (cntx)       
|       st1  bit10-11 (and "swap": bit0-7)    ; (TL2: probably also SttMod) |
|       st2  bit0-7                           ;/                            |
|       a0 <--> b0    manualswap only?        ;\accumulators (swap)         
|       a1 <--> b1    autoswapped?            ;/                            |
|       r0 <--> r0b                           ;\                            
|       r1 <--> r1b                           ;                             |
|       r4 <--> r4b                           ; BankFlags (banke)           |
|       r7 <--> r7b     ;TL2                  ;                             |
|       cfgi <--> cfgib                       ;                             |
|       cfgj <--> cfgjb ;TL2                  ;/                            |
|       Ar,Arp <--> ?   ;TL2                  ;-? (bankr and/or cntx)       |
+---------------------------------------------------------------------------+
```

Registers b0/b1 can be used as normal opcode operands, the other shadow registers are used only when doing bank/cntx stuff.

### Suffix codes: dmod,dmodi,dmodj,dmodij,context,eu,dbrv,ebrv,s,r
Non-register assembler keywords.

```
+---------------------------------------------------------------------------------+
|       dmod   ;TL  ;suffix ;\                                                    
|       dmodi  ;TL2 ;suffix ;                                                     |
|       dmodj  ;TL2 ;suffix ;                                                     |
|       dmodij ;TL2 ;suffix ;/                                                    |
|       context;TL  ;suffix ;<-- (related to "cntx")                              |
|       eu     ;TL  ;suffix ;<-- (aka "Axheu", now "Axh,eu")                      |
|       dbrv   ;TL2 ;suffix ;\for "bitrev"                                        
|       ebrv   ;TL2 ;suffix ;/                                                    |
|       s      ;TL  ;suffix ;\param for "cntx" opcode  ;"s" also for opcode 88D1h 
|       r      ;TL  ;suffix ;/                                                    |
+---------------------------------------------------------------------------------+
```


### Condition codes: true,eq,neq,gt,ge,lt,le,nn,c,v,e,l,nr,niu0,iu0,iu1
The 16 condition codes can be used for all opcodes with \"Cond\" operand, whereas \"true\" can be omitted (as it means always/non-conditional), the four conditions \"gt,ge,lt,le\" can be also used with \"min/max/maxd/cbs\" opcodes.

### Old pre-TeakLiteII keyword names (renamed in TeakLiteII)

```
+-----------------------------------------------------------------------+
|       TL:   x    y    p    ph   rb   lpg   a0heu   a1heu              |
|       TL2:  x0   y0   p0   p0h  r7   page  a0h,eu  a1h,eu             |
+-----------------------------------------------------------------------+
```




