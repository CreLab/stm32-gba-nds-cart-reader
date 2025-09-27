# DS Encryption by Random Seed (KEY2)


### KEY2 39bit Seed Values
The pre-initialization settings at cartridge-side (after reset) are:

```
+-----------------------------------------------------------------------+
|       Seed0 = 58C56DE0E8h                                             |
|       Seed1 = 5C879B9B05h                                             |
+-----------------------------------------------------------------------+
```

The post-initialization settings (after sending command 4llllmmmnnnkkkkkh to the cartridge, and after writing the Seed values to Port 40001Bxh) are:

```
+-----------------------------------------------------------------------+
|       Seed0 = (mmmnnn SHL 15)+6000h+Seedbyte                          |
|       Seed1 = 5C879B9B05h                                             |
+-----------------------------------------------------------------------+
```

The seedbyte is selected by Cartridge Header \[013h\].Bit0-2, this index value should be usually in range 0..5, however, possible values for index 0..7 are: E8h,4Dh,5Ah,B1h,17h,8Fh,99h,D5h.
The 24bit random value (mmmnnn) is derived from the real time clock setting, and also scattered by KEY1 encryption, anyways, it\'s just random and doesn\'t really matter where it comes from.

### KEY2 Encryption
Relies on two 39bit registers (x and y), which are initialized as such:

```
+-------------------------------------------------------------------------------------+
|       x = reversed_bit_order(seed0)  ;ie. LSB(bit0) exchanged with MSB(bit38), etc. |
|       y = reversed_bit_order(seed1)                                                 |
+-------------------------------------------------------------------------------------+
```

During transfer, x, y, and transferred data are modified as such:

```
+-----------------------------------------------------------------------------------+
|       x = (((x shr 5)xor(x shr 17)xor(x shr 18)xor(x shr 31)) and 0FFh)+(x shl 8) |
|       y = (((y shr 5)xor(y shr 23)xor(y shr 18)xor(y shr 31)) and 0FFh)+(y shl 8) |
|       data = (data xor x xor y) and 0FFh                                          |
+-----------------------------------------------------------------------------------+
```




