# Inflate - Core Functions


### tinf_uncompress(dst,src)

```
+------------------------------------------------------------------------------------+
|      tinf_init()                    ;init constants (needed to be done only once)  |
|      tinf_align_src_to_byte_boundary()                                             |
|      repeat                                                                        |
|       bfinal=tinf_getbit()          ;read final block flag (1 bit)                 |
|       btype=tinf_read_bits(2)       ;read block type (2 bits)                      |
|       if btype=0 then tinf_inflate_uncompressed_block()                            |
|       if btype=1 then tinf_build_fixed_trees(), tinf_inflate_compressed_block()    |
|       if btype=2 then tinf_decode_dynamic_trees(), tinf_inflate_compressed_block() |
|       if btype=3 then ERROR         ;reserved                                      |
|      until bfinal=1                                                                |
|      tinf_align_src_to_byte_boundary()                                             |
|      ret                                                                           |
+------------------------------------------------------------------------------------+
```


### tinf_inflate_uncompressed_block()

```
+-----------------------------------------------------------------------------------+
|      tinf_align_src_to_byte_boundary()                                            |
|      len=LittleEndian16bit[src+0]                             ;get len            |
|      if LittleEndian16bit[src+2]<>(len XOR FFFFh) then ERROR  ;verify inverse len |
|      src=src+4                                                ;skip len values    |
|      for i=0 to len-1, [dst]=[src], dst=dst+1, src=src+1, next i    ;copy block   |
|      ret                                                                          |
+-----------------------------------------------------------------------------------+
```


### tinf_inflate_compressed_block()

```
+---------------------------------------------------------------------------+
|      repeat                                                               |
|       sym1=tinf_decode_symbol(tinf_len_tree)                              |
|       if sym1<256                                                         |
|        [dst]=sym1, dst=dst+1                                              |
|       if sym1>256                                                         |
|        len  = tinf_read_bits(length_bits[sym1-257])+length_base[sym1-257] |
|        sym2 = tinf_decode_symbol(tinf_dist_tree)                          |
|        dist = tinf_read_bits(dist_bits[sym2])+dist_base[sym2]             |
|        for i=0 to len-1, [dst]=[dst-dist], dst=dst+1, next i              |
|      until sym1=256                                                       |
|      ret                                                                  |
+---------------------------------------------------------------------------+
```


### tinf_decode_symbol(tree)

```
+----------------------------------------------------------------------------------+
|      sum=0, cur=0, len=0                                                         |
|      repeat                         ;get more bits while code value is above sum |
|       cur=cur*2 + tinf_getbit()                                                  |
|       len=len+1                                                                  |
|       sum=sum+tree.table[len]                                                    |
|       cur=cur-tree.table[len]                                                    |
|      until cur<0                                                                 |
|      return tree.trans[sum+cur]                                                  |
+----------------------------------------------------------------------------------+
```


### tinf_read_bits(num) ;get N bits from source stream

```
+-----------------------------------------------------------------------+
|      val=0                                                            |
|      for i=0 to num-1, val=val+(tinf_getbit() shl i), next i          |
|      return val                                                       |
+-----------------------------------------------------------------------+
```


### tinf_getbit() ;get one bit from source stream

```
+---------------------------------------------------------------------------+
|      bit=tag AND 01h, tag=tag/2                                           |
|      if tag=00h then tag=[src], src=src+1, bit=tag AND 01h, tag=tag/2+80h |
|      return bit                                                           |
+---------------------------------------------------------------------------+
```


### tinf_align_src_to_byte_boundary()

```
+------------------------------------------------------------------------------+
|      tag=01h   ;empty/end-bit (discard any bits, align src to byte-boundary) |
|      ret                                                                     |
+------------------------------------------------------------------------------+
```




