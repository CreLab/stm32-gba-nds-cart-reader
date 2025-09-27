# DS Cart Cheat Codebreaker DS


This is Pelican\'s entry into the DS cheat-device industry. It supports swapping out the cartridges, and alternately, also gives the user the option of connecting another gamecard onto it. For updating, the user may either manually enter codes, or use Wifi to connect to the Codebreaker update site (that updating will overwrite all manually entered codes though).

### Codebreaker DS Codes

```
+-------------------------------------------------------------------------------------+
|       ---Initialization---                                                          |
|       0000CR16 GAMECODE                    Specify Game ID, use Encrypted codes     |
|       8000CR16 GAMECODE                    Specify Game ID, use Unencrypted codes   |
|       BEEFC0DE XXXXXXXX                    Change Encryption Keys                   |
|       A0XXXXXX YYYYYYYY                    Bootup-Hook 1, X=Address, Y=Value        |
|       A8XXXXXX YYYYYYYY                    Bootup-Hook 2, X=Address, Y=Value        |
|       F0XXXXXX TYYYYYYY         Code-Hook 1 (T=Type,Y=CheatEngineAddr,X=HookAddr)   |
|       F8XXXXXX TPPPPPPP         Code-Hook 2 (T=Type,X=CheatEngineHookAddr,P=Params) |
|       ---General codes---                                                           |
|       00XXXXXX 000000YY                    [X]=YY                                   |
|       10XXXXXX 0000YYYY                    [X]=YYYY                                 |
|       20XXXXXX YYYYYYYY                    [X]=YYYYYYYY                             |
|       60XXXXXX 000000YY ZZZZZZZZ 00000000  [[X]+Z]=YY                               |
|       60XXXXXX 0000YYYY ZZZZZZZZ 10000000  [[X]+Z]=YYYY                             |
|       60XXXXXX YYYYYYYY ZZZZZZZZ 20000000  [[X]+Z]=YYYYYYYY                         |
|       30XXXXXX 000000YY                    [X]=[X] + YY                             |
|       30XXXXXX 0001YYYY                    [X]=[X] + YYYY                           |
|       38XXXXXX YYYYYYYY                    [X]=[X] + YYYYYYYY                       |
|       70XXXXXX 000000YY                    [X]=[X] OR  YY                           |
|       70XXXXXX 001000YY                    [X]=[X] AND YY                           |
|       70XXXXXX 002000YY                    [X]=[X] XOR YY                           |
|       70XXXXXX 0001YYYY                    [X]=[X] OR  YYYY                         |
|       70XXXXXX 0011YYYY                    [X]=[X] AND YYYY                         |
|       70XXXXXX 0021YYYY                    [X]=[X] XOR YYYY                         |
|       ---Memory fill/copy---                                                        |
|       40XXXXXX 2NUMSTEP 000000YY 000000ZZ  byte[X+(0..NUM-1)*STEP*1]=Y+(0..NUM-1)*Z |
|       40XXXXXX 1NUMSTEP 0000YYYY 0000ZZZZ  half[X+(0..NUM-1)*STEP*2]=Y+(0..NUM-1)*Z |
|       40XXXXXX 0NUMSTEP YYYYYYYY ZZZZZZZZ  word[X+(0..NUM-1)*STEP*4]=Y+(0..NUM-1)*Z |
|       50XXXXXX YYYYYYYY ZZZZZZZZ 00000000  copy Y bytes from [X] to [Z]             |
|       ---Conditional codes (bugged)---                                              |
|       60XXXXXX 000000YY ZZZZZZZZ 01c100VV  IF [[X]+Z] .. VV   THEN [[X]+Z]=YY       |
|       60XXXXXX 000000YY ZZZZZZZZ 01c0VVVV  IF [[X]+Z] .. VVVV THEN [[X]+Z]=YY       |
|       60XXXXXX 0000YYYY ZZZZZZZZ 11c100VV  IF [[X]+Z] .. VV   THEN [[X]+Z]=YYYY     |
|       60XXXXXX 0000YYYY ZZZZZZZZ 11c0VVVV  IF [[X]+Z] .. VVVV THEN [[X]+Z]=YYYY     |
|       60XXXXXX YYYYYYYY ZZZZZZZZ 21c100VV  IF [[X]+Z] .. VV   THEN [[X]+Z]=YYYYYYYY |
|       60XXXXXX YYYYYYYY ZZZZZZZZ 21c0VVVV  IF [[X]+Z] .. VVVV THEN [[X]+Z]=YYYYYYYY |
|       ---Conditional codes (working)---                                             |
|       D0XXXXXX NNc100YY                    IF [X] .. YY   THEN exec max(1,NN) lines |
|       D0XXXXXX NNc0YYYY                    IF [X] .. YYYY THEN exec max(1,NN) lines |
+-------------------------------------------------------------------------------------+
```

The condition digits (c=0..7), have the following functions:

```
+------------------------------------------------------------------------------------+
|       0 IF [mem] =  imm THEN ...              4 IF ([mem] AND imm) =  0   THEN ... |
|       1 IF [mem] <> imm THEN ...              5 IF ([mem] AND imm) <> 0   THEN ... |
|       2 IF [mem] <  imm THEN ... (unsigned)   6 IF ([mem] AND imm) =  imm THEN ... |
|       3 IF [mem] >  imm THEN ... (unsigned)   7 IF ([mem] AND imm) <> imm THEN ... |
+------------------------------------------------------------------------------------+
```

Notes

```
+------------------------------------------------------------------------------------+
|       GAMECODE  Cartridge Header[00Ch] (32bit in reversed byte-order)              |
|       CR16      Cartridge Header[15Eh] (16bit in normal byte-order)                |
|       XXXXXX    27bit addr (actually 7 digits, XXXXXXX, overlaps 5bit code number) |
+------------------------------------------------------------------------------------+
```

The \"bugged\" conditional codes (60XXXXXX) are accidently skipping NN lines when the condition is false, where NN is taken from the upper 8bit of the code\'s last 32bit values (ie. exactly as for the D0XXXXXX codes). For byte-writes, that would be NN=01h, which can be eventually dealt with, although there may be compatibility problems which future versions that might fix that bug. For halfword/word writes, NN would be 11h or 21h, so that codes are about totally unusable.

### Codebreaker DS / Encrypted Codes
The overall \"address value\" decryption works like so:

```
+-----------------------------------------------------------------------+
|       for i=4Fh to 00h                                                |
|         y=77628ECFh                                                   |
|         if i>13h then y=59E5DC8Ah                                     |
|         if i>27h then y=054A7818h                                     |
|         if i>3Bh then y=B1BF0855h                                     |
|         address = (Key0-value) xor address                            |
|         value   = value - Key1 - (address ror 1Bh)                    |
|         address = (address xor (value + y)) ror 13h                   |
|         if (i>13h) then                                               |
|           if (i<=27h) or (i>3Bh) then x=Key2 xor Key1 xor Key0        |
|           else x=((Key2 xor Key1) and Key0) xor (Key1 and Key2)       |
|           value=value xor (x+y+address)                               |
|           x = Secure[((i*4+00h) and FCh)+000h]                        |
|           x = Secure[((i*4+34h) and FCh)+100h] xor x                  |
|           x = Secure[((i*4+20h) and FCh)+200h] xor x                  |
|           x = Secure[((i*4+08h) and FCh)+300h] xor x                  |
|           address = address - (x ror 19h)                             |
|       next i                                                          |
+-----------------------------------------------------------------------+
```

Upon startup, the initial key settings are:

```
+-------------------------------------------------------------------------------------+
|       Secure[0..7FFh] = Copy of the ENCRYPTED 1st 2Kbytes of the game's Secure Area |
|       Key0 = 0C2EAB3Eh, Key1 = E2AE295Dh, Key2 = E1ACC3FFh, Key3 = 70D3AF46h        |
|       scramble_keys                                                                 |
+-------------------------------------------------------------------------------------+
```

Upon BEEFC0DE XXXXXXXX, the keys get changed like so:

```
+-----------------------------------------------------------------------+
|       Key0 = Key0 + (XXXXXXXX ror 1Dh)                                |
|       Key1 = Key1 - (XXXXXXXX ror 05h)                                |
|       Key2 = Key2 xor (Key3 xor Key0)                                 |
|       Key3 = Key3 xor (Key2  -  Key1)                                 |
|       scramble_keys                                                   |
+-----------------------------------------------------------------------+
```

The above scramble_keys function works like so:

```
+----------------------------------------------------------------------------------+
|       for i=0 to FFh                                                             |
|         y = byte(xlat_table[i])                                                  |
|         Secure[i*4+000h] = (Secure[i*4+000h] xor Secure[y*4]) + Secure[y*4+100h] |
|         Secure[i*4+400h] = (Secure[i*4+400h] xor Secure[y*4]) - Secure[y*4+200h] |
|       next i                                                                     |
|       for i=0 to 63h                                                             |
|         Key0 = Key0 xor (Secure[i*4] + Secure[i*4+190h])                         |
|         Key1 = Key1 xor (Secure[i*4] + Secure[i*4+320h])                         |
|         Key2 = Key2 xor (Secure[i*4] + Secure[i*4+4B0h])                         |
|         Key3 = Key3 xor (Secure[i*4] + Secure[i*4+640h])                         |
|       next i                                                                     |
|       Key0 = Key0  -  Secure[7D0h]                                               |
|       Key1 = Key1 xor Secure[7E0h]                                               |
|       Key2 = Key2  +  Secure[7F0h]                                               |
|       Key3 = Key3 xor Secure[7D0h] xor Secure[7F0h]                              |
+----------------------------------------------------------------------------------+
```

the xlat_table consists of 256 fixed 8bit values:

```
+-----------------------------------------------------------------------+
|       34h,59h,00h,32h,7Bh,D3h,32h,C9h,9Bh,77h,75h,44h,E0h,73h,46h,06h |
|       0Bh,88h,B3h,3Eh,ACh,F2h,BAh,FBh,2Bh,56h,FEh,7Ah,90h,F7h,8Dh,BCh |
|       8Bh,86h,9Ch,89h,00h,19h,CDh,4Ch,54h,30h,01h,93h,30h,01h,FCh,36h |
|       4Dh,9Fh,FDh,D7h,32h,94h,AEh,BCh,2Bh,61h,DFh,B3h,44h,EAh,8Bh,A3h |
|       2Bh,53h,33h,54h,42h,27h,21h,DFh,A9h,DDh,C0h,35h,58h,EFh,8Bh,33h |
|       B4h,D3h,1Bh,C7h,93h,AEh,32h,30h,F1h,CDh,A8h,8Ah,47h,8Ch,70h,0Ch |
|       17h,4Eh,0Eh,A2h,85h,0Dh,6Eh,37h,4Ch,39h,1Fh,44h,98h,26h,D8h,A1h |
|       B6h,54h,F3h,AFh,98h,83h,74h,0Eh,13h,6Eh,F4h,F7h,86h,80h,ECh,8Eh |
|       EEh,4Ah,05h,A1h,F1h,EAh,B4h,D6h,B8h,65h,8Ah,39h,B3h,59h,11h,20h |
|       B6h,BBh,4Dh,88h,68h,24h,12h,9Bh,59h,38h,06h,FAh,15h,1Dh,40h,F0h |
|       01h,77h,57h,F5h,5Dh,76h,E5h,F1h,51h,7Dh,B4h,FAh,7Eh,D6h,32h,4Fh |
|       0Eh,C8h,61h,C1h,EEh,FBh,2Ah,FCh,ABh,EAh,97h,D5h,5Dh,E8h,FAh,2Ch |
|       06h,CCh,86h,D2h,8Ch,10h,D7h,4Ah,CEh,8Fh,EBh,03h,16h,ADh,84h,98h |
|       F5h,88h,2Ah,18h,ACh,7Fh,F6h,94h,FBh,3Fh,00h,B6h,32h,A2h,ABh,28h |
|       64h,5Ch,0Fh,C6h,23h,12h,0Ch,D2h,BAh,4Dh,A3h,F2h,C9h,86h,31h,57h |
|       0Eh,F8h,ECh,E1h,A0h,9Ah,3Ch,65h,17h,18h,A0h,81h,D0h,DBh,D5h,AEh |
+-----------------------------------------------------------------------+
```

all used operations are unsigned 32bit integer.

### Thanks
To Kenobi and Dualscreenman from Kodewerx for above CBDS cheat info.



