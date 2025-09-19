# BIOS 3DS Exception Vectors


### Exception Vectors
The 3DS bootroms do mostly contain bootcode, unlike GBA/NDS without any public functions, apart from some small stubs for redirecting the exception vectors to RAM locations:

```
+-------------------------------------------------------------------------------------+
|       08000000h 8  arm9_irq                ldr r15,[$+4] // dd vector  ;\           
|       08000008h 8  arm9_fiq                ldr r15,[$+4] // dd vector  ;            |
|       08000010h 8  arm9_svc                ldr r15,[$+4] // dd vector  ; ARM9       |
|       08000018h 8  arm9_undef              ldr r15,[$+4] // dd vector  ; exceptions |
|       08000020h 8  arm9_prefetch_abort     ldr r15,[$+4] // dd vector  ;            |
|       08000028h 8  arm9_data_abort         ldr r15,[$+4] // dd vector  ;/           |
|       1FFFFFA0h 8  arm11_irq               ldr r15,[$+4] // dd vector  ;\           
|       1FFFFFA8h 8  arm11_fiq               ldr r15,[$+4] // dd vector  ;            |
|       1FFFFFB0h 8  arm11_svc               ldr r15,[$+4] // dd vector  ; ARM11      |
|       1FFFFFB8h 8  arm11_undef             ldr r15,[$+4] // dd vector  ; exceptions |
|       1FFFFFC0h 8  arm11_prefetch_abort    ldr r15,[$+4] // dd vector  ;            |
|       1FFFFFC8h 8  arm11_data_abort        ldr r15,[$+4] // dd vector  ;/           |
|       1FFFFFDCh 4  arm11_core1_entrypoint  dd vector                   ;-CPU1 entry |
|       (OVERLAY) 4  arm11_core23_entry      dd vector                   ;-CPU2/3     |
+-------------------------------------------------------------------------------------+
```

The ARM11 exception vectors are shared for all CPU cores (so one must manually redirect them to core specific handlers).
Alternately, instead of using the above RAM vectors, one could use ARM11 virtual memory or ARM9 ITCM for custom vectors.
Moreover, the CFG11_BOOTROM_OVERLAY_CNT/VAL feature allows to redirect ARM11 vectors on New3DS (mainly intended for booting CPU2/CPU3 cores).

### SWI/SVC Functions
There aren\'t any built-in functions in the bootroms, however, SVC opcodes can be used to obtain entrypoints to OS functions. That is, once when the OS is booted (FIRM files are started without any OS functions, but .code files can use OS functions).
Note: ARM has renamed SWI opcodes to SVC opcodes.



