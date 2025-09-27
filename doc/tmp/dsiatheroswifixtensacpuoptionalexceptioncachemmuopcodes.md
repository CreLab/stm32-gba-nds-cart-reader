# DSi Atheros Wifi - Xtensa CPU Optional Exception/Cache/MMU Opcodes


### Interrupt Option

```
+-----------------------------------------------------------------------------------+
|       006it0h  RSIL  at,level       xchg  at,ps,intlevel i  Read/Set IntLevel     |
|       007i00h  WAITI level          waiti ps,intlevel i     Set IntLevel and Wait |
+-----------------------------------------------------------------------------------+
```


### High-Priority Interrupt Option

```
+------------------------------------------------------------------------------+
|       003i10h  RFI   level          ret_i level             RetFromHiPrioInt |
+------------------------------------------------------------------------------+
```


### Exception Option

```
+-----------------------------------------------------------------------------------+
|       000000h  ILL                  ill                     Illegal Instruction   |
|       002080h  EXCW                 xceptwait               Exception Wait        |
|       003000h  RFE                  ret_e                   RetFromException      |
|       003100h  RFUE                 ret_ue                  RetFromUserModeExcept |
|       003200h  RFDE                 ret_de                  RetFromDoubleExcept   |
|       005000h  SYSCALL              syscall                 System Call           |
+-----------------------------------------------------------------------------------+
```


### Debug Option

```
+----------------------------------------------------------------------------------+
|       004xy0h  BREAK imm4,imm4      break  imm8             Breakpoint           |
|       F1E000h  RFDO                 ret_do                  RetFromDebugOperat.  |
|       F1Es10h  RFDD    ;s=???       rer_dd imm1             RetFromDebugDispatch |
+----------------------------------------------------------------------------------+
```


### MemECC/Parity Option

```
+-----------------------------------------------------------------------------+
|       003020h  RFME                 ret_me                  RetFromMemError |
+-----------------------------------------------------------------------------+
```


### No Option

```
+--------------------------------------------------------------------------------+
|       E3rii0h  RUR ar,imm8          mov    ar,user[imm8]    Read User Register |
|       F3iit0h  WUR at,imm8          mov    user[imm8],at    WriteUserRegister  |
+--------------------------------------------------------------------------------+
```


### Region/MMU Option

```
+-----------------------------------------------------------------------------------+
|       503st0h  RITLB0 at,as         mov    at,itlb0[as]     Read InstTLB Virtual  |
|       507st0h  RITLB1 at,as         mov    at,itlb1[as]     Read InstTLB Translat |
|       50Bst0h  RDTLB0 at,as         mov    at,dtlb0[as]     Read DataTLB Virtual  |
|       50Fst0h  RDTLB1 at,as         mov    at,dtlb1[as]     Read DataTLB Translat |
|       504s00h  IITLB  as            inv    itlb[as]         Invalidate InstTLB    |
|       50Cs00h  IDTLB  as            inv    dtlb[as]         Invalidate DataTLB    |
|       505st0h  PITLB  at,as         probe  at,itlb[as]      Probe InstTLB         |
|       50Dst0h  PDTLB  at,as         probe  at,dtlb[as]      Probe DataTLB         |
|       506st0h  WITLB  at,as         mov    itlb[as],at      Write InstTLB Entry   |
|       50Est0h  WDTLB  at,as         mov    dtlb[as],at      Write DataTLB Entry   |
+-----------------------------------------------------------------------------------+
```


### Multiprocessor Option

```
+---------------------------------------------------------------------------------+
|       iiBst2h  L32AI at,as,i*4      mov_m at,[as+imm8*4]    Load 32bit Acquire  |
|       iiFst2h  S32RI at,as,imm*4    mov_m [as+imm8*4],at    Store 32bit Release |
+---------------------------------------------------------------------------------+
```


### Multiprocessor Conditional Store Option

```
+-------------------------------------------------------------------------+
|       iiEst2h  S32C1I at,as,imm*4   s32c1i at,[as+imm8*4]   CompareCond |
+-------------------------------------------------------------------------+
```


### Data Cache Option

```
+-------------------------------------------------------------------------------+
|       i07s82h  DPFL  as,imm4*16     cach_dpfl  [as+imm4*16] PrefetchAndLock * |
|       i27s82h  DHU   as,imm4*16     cach_dhu   [as+imm4*16] HitUnlock         |
|       i37s82h  DIU   as,imm4*16     cach_diu   [as+imm4*16] Index Unlock      |
|       i47s82h  DIWB  as,imm4*16     cach_diwb  [as+imm4*16] Index Writeback   |
|       i57s82h  DIWBI as,imm4*16     cach_diwbi [as+imm4*16] Index WbInvali.   |
|       ii7s02h  DPFR  as,imm8*4      cach_dpfr  [as+imm8*4]  PrefetchForRead   |
|       ii7s12h  DPFW  as,imm8*4      cach_dpfw  [as+imm8*4]  PrefetchForWrite  |
|       ii7s22h  DPFRO as,imm8*4      cach_dpfro [as+imm8*4]  PrefetchForRdOnce |
|       ii7s32h  DPFWO as,imm8*4      cach_dpfwo [as+imm8*4]  PrefetchForWrOnce |
|       ii7s42h  DHWB  as,imm8*4      cach_dhwb  [as+imm8*4]  HitWriteback      |
|       ii7s52h  DHWBI as,imm8*4      cach_dhwbi [as+imm8*4]  HitWritebackInv.  |
|       ii7s62h  DHI   as,imm8*4      cach_dhi   [as+imm8*4]  HitInvalidate     |
|       ii7s72h  DII   as,imm8*4      cach_dii   [as+imm8*4]  Index Invalidate  |
+-------------------------------------------------------------------------------+
```


### Instruction Cache Option

```
+-------------------------------------------------------------------------------+
|       i07sD2h  IPFL as,imm4*16      cach_ipfl  [as+imm4*16] PrefetchAndLock * |
|       i27sD2h  IHU  as,imm4*16      cach_ihu   [as+imm4*16] Hit Unlock        |
|       i37sD2h  IIU  as,imm4*16      cach_iiu   [as+imm4*16] Index Unlock      |
|       ii7sC2h  IPF  as,imm8*4       cach_ipf   [as+imm8*4]  Prefetch          |
|       ii7sE2h  IHI  as,imm8*4       cach_ihi   [as+imm8*4]  Hit Invalidate    |
|       ii7sF2h  III  as,imm8*4       cach_iii   [as+imm8*4]  Index Invalidate  |
+-------------------------------------------------------------------------------+
```


### Data/Instruction Cache Test Options

```
+----------------------------------------------------------------------------------+
|       F18st0h  LDCT  at,as          cach_mov at,dCachTag[as]  LoadDataCacheTag   |
|       F10st0h  LICT  at,as          cach_mov at,iCachTag[as]  LoadInstCacheTag   |
|       F12st0h  LICW  at,as          cach_mov at,iCachDta[as]  LoadInstCacheWord  |
|       F19st0h  SDCT  at,as          cach_mov dCachTag[as],at  StoreDataCacheTag  |
|       F11st0h  SICT  at,as          cach_mov iCachTag[as],at  StoreInstCacheTag  |
|       F13st0h  SICW  at,as          cach_mov iCachDta[as],at  StoreInstCacheWord |
+----------------------------------------------------------------------------------+
```


### Unknown

```
+---------------------------------------------------------------------------------+
|       71xxx0h  ACCER ...            accer ...               Unknown/Unspecified |
+---------------------------------------------------------------------------------+
```


### Custom Designer-Defined Opcode Option

```
+------------------------------------------------------------------------------------+
|       x6xxx0h  CUST ...             cust ...                DesignerDefinedOpcodes |
+------------------------------------------------------------------------------------+
```


### Simcall Option

```
+-----------------------------------------------------------------------------------+
|       005100h  SIMCALL              simcall                 Non-HW Simulator-Call |
+-----------------------------------------------------------------------------------+
```




