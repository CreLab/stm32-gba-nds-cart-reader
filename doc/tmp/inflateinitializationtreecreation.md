# Inflate - Initialization & Tree Creation


### tinf_init()

```
+-----------------------------------------------------------------------+
|      tinf_build_bits_base(length_bits, length_base, 4, 3)             |
|      length_bits[28]=0, length_base[28]=258                           |
|      tinf_build_bits_base(dist_bits, dist_base, 2, 1)                 |
|      ret                                                              |
+-----------------------------------------------------------------------+
```


### tinf_build_bits_base(bits,base,delta,base_val)

```
+-----------------------------------------------------------------------+
|      for i=0 to 29                                                    |
|       bits[i]=min(0,i-delta)/delta                                    |
|       base[i]=base_val                                                |
|       base_val=base_val+(1 shl bits[i])                               |
|      ret                                                              |
+-----------------------------------------------------------------------+
```


### tinf_build_fixed_trees()

```
+-------------------------------------------------------------------------------------+
|      for i=0 to 6, tinf_len_tree.table[i]=0, next i       ;[0..6]=0   ;len tree...  |
|      tinf_len_tree.table[7,8,9]=24,152,112                ;[7..9]=24,152,112        |
|      for i=0 to 23,  tinf_len_tree.trans[i+0]  =i+256, next i  ;[0..23]   =256..279 |
|      for i=0 to 143, tinf_len_tree.trans[i+24] =i+0,   next i  ;[24..167] =0..143   |
|      for i=0 to 7,   tinf_len_tree.trans[i+168]=i+280, next i  ;[168..175]=280..287 |
|      for i=0 to 111, tinf_len_tree.trans[i+176]=i+144, next i  ;[176..287]=144..255 |
|      for i=0 to 4, tinf_dist_tree.table[i]=0, next i   ;[0..4]=0,0,0,0,0 ;\dist     
|      tinf_dist_tree.table[5]=32                        ;[5]=32           ; tree     |
|      for i=0 to 31, tinf_dist_tree.trans[i]=i, next i  ;[0..31]=0..31    ;/         |
|      ret                                                                            |
+-------------------------------------------------------------------------------------+
```


### tinf_decode_dynamic_trees()

```
+-------------------------------------------------------------------------------------+
|      hlit  = tinf_read_bits(5)+257           ;get 5 bits HLIT (257-286)             |
|      hdist = tinf_read_bits(5)+1             ;get 5 bits HDIST (1-32)               |
|      hclen = tinf_read_bits(4)+4             ;get 4 bits HCLEN (4-19)               |
|      for i=0 to 18, lengths[i]=0, next i                                            |
|      for i=0 to hclen-1                      ;read lengths for code length alphabet |
|       lengths[clcidx[i]]=tinf_read_bits(3)   ;get 3 bits code length (0-7)          |
|      tinf_build_tree(code_tree, lengths, 19) ;build code length tree                |
|      for num=0 to hlit+hdist-1               ;decode code lengths for dynamic trees |
|       sym = tinf_decode_symbol(code_tree)                                           |
|       len=1, val=sym                         ;default (for sym=0..15)               |
|       if sym=16 then len=tinf_read_bits(2)+3, val=lengths[num-1] ;3..6 previous     |
|       if sym=17 then len=tinf_read_bits(3)+3, val=0              ;3..10 zeroes      |
|       if sym=18 then len=tinf_read_bits(7)+11, val=0             ;11..138 zeroes    |
|       for i=1 to len, lengths[num]=val, num=num+1, next i                           |
|      tinf_build_tree(tinf_len_tree,  0,      hlit)    ;\build trees                 
|      tinf_build_tree(tinf_dist_tree, 0+hlit, hdist)   ;/                            |
|      ret                                                                            |
+-------------------------------------------------------------------------------------+
```


### tinf_build_tree(tree, first, num)

```
+-----------------------------------------------------------------------------------+
|      for i=0 to 15, tree.table[i]=0, next i     ;clear code length count table    |
|      ;scan symbol lengths, and sum code length counts...                          |
|      for i=0 to num-1, x=lengths[i+first], tree.table[x]=tree.table[x]+1, next i  |
|      tree.table[0]=0                                                              |
|      sum=0          ;compute offset table for distribution sort                   |
|      for i=0 to 15, offs[i]=sum, sum=sum+tree.table[i], next i                    |
|      for i=0 to num-1  ;create code to symbol xlat table (symbols sorted by code) |
|       x=lengths[i+first], if x<>0 then tree.trans[offs[x]]=i, offs[x]=offs[x]+1   |
|      next i                                                                       |
|      ret                                                                          |
+-----------------------------------------------------------------------------------+
```


### tinf_data

```
+----------------------------------------------------------------------------------+
|      clcidx[0..18] = 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15   ;constants |
+----------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      typedef struct TINF_TREE:                                        |
|        unsigned short table[16]     ;table of code length counts      |
|        unsigned short trans[288]    ;code to symbol translation table |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|      TINF_TREE tinf_len_tree   ;length/symbol tree                                |
|      TINF_TREE tinf_dist_tree  ;distance tree                                     |
|      TINF_TREE code_tree       ;temporary tree (for generating the dynamic trees) |
|      unsigned char lengths[288+32]   ;temporary 288+32 x 8bit ;\for dynamic tree  
|      unsigned short offs[16]         ;temporary 16 x 16bit    ;/creation          |
+-----------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|      unsigned char  length_bits[30]                                   |
|      unsigned short length_base[30]                                   |
|      unsigned char  dist_bits[30]                                     |
|      unsigned short dist_base[30]                                     |
+-----------------------------------------------------------------------+
```




