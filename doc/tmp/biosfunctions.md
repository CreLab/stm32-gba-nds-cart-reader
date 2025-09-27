# BIOS Functions


The BIOS includes several System Call Functions which can be accessed by SWI instructions. Incoming parameters are usually passed through registers R0,R1,R2,R3. Outgoing registers R0,R1,R3 are typically containing either garbage, or return value(s). All other registers (R2,R4-R14) are kept unchanged.

### Caution
When invoking SWIs from inside of ARM state specify SWI NN\*10000h, instead of SWI NN as in THUMB state.

### Overview
- [BIOS Function Summary](./biosfunctionsummary.md)
- [BIOS Differences between GBA and NDS functions](./biosdifferencesbetweengbaandndsfunctions.md)

### All Functions Described
- [BIOS Arithmetic Functions](./biosarithmeticfunctions.md)
- [BIOS Rotation/Scaling Functions](./biosrotationscalingfunctions.md)
- [BIOS Decompression Functions](./biosdecompressionfunctions.md)
- [BIOS Memory Copy](./biosmemorycopy.md)
- [BIOS Halt Functions](./bioshaltfunctions.md)
- [BIOS Reset Functions](./biosresetfunctions.md)
- [BIOS Misc Functions](./biosmiscfunctions.md)
- [BIOS Multi Boot (Single Game Pak)](./biosmultibootsinglegamepak.md)
- [BIOS Sound Functions](./biossoundfunctions.md)
- [BIOS SHA1 Functions (DSi only)](./biossha1functionsdsionly.md)
- [BIOS RSA Functions (DSi only)](./biosrsafunctionsdsionly.md)

### 3DS bootroms
- [BIOS 3DS Exception Vectors](./bios3dsexceptionvectors.md)

### RAM Usage, BIOS Dumps
- [BIOS RAM Usage](./biosramusage.md)
- [BIOS Dumping](./biosdumping.md)

### How BIOS Processes SWIs
SWIs can be called from both within THUMB and ARM mode. In ARM mode, only the upper 8bit of the 24bit comment field are interpreted.
Each time when calling a BIOS function 4 words (SPSR, R11, R12, R14) are saved on Supervisor stack (\_svc). Once it has saved that data, the SWI handler switches into System mode, so that all further stack operations are using user stack.
In some cases the BIOS may allow interrupts to be executed from inside of the SWI procedure. If so, and if the interrupt handler calls further SWIs, then care should be taken that the Supervisor Stack does not overflow.



