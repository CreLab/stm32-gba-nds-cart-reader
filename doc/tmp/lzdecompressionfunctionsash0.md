# LZ Decompression Functions ASH0


ASH0 is used by several games on different consoles (eg. DSi Flipnote, rom:\\SampleData.Eu\\\*.ash).

### ash_decompress(source,dest)

```
+------------------------------------------------------------------------------------+
|       collected[0]=80000000h          ;stream 0 initially empty (endflag in bit31) |
|       collected[1]=80000000h          ;stream 1 initially empty (endflag in bit31) |
|       src[0]=source+0                 ;stream 0 start                              |
|       for i=0 to 3, id[i]=read_bits(0,8), next i, if id[0..3]<>'ASH0' then error   |
|       dest_end=dest+read_bits(0,32)   ;size of decompressed data                   |
|       src[1]=source+read_bits(0,32)   ;stream 1 start                              |
|       load_huffman_tree(0,9)          ;load stream 0 tree (9bit len/data values)   |
|       load_huffman_tree(1,11)         ;load stream 1 tree (11bit disp values)      |
|      decompress_loop:                                                              |
|       temp=0, while temp<8000h do temp=tree[0][temp+read_bits(0,1)]                |
|       if temp<8100h then                                                           |
|         [dest]=temp AND FFh, dest=dest+1      ;store one uncompressed data byte    |
|       else                                                                         |
|         disp=0, while disp<8000h do disp=tree[1][disp+read_bits(1,1)]              |
|         len=temp+3-8100h, disp=disp+1-8000h                                        |
|         for j=1 to len, [dest]=[dest-disp], dest=dest+1, next j                    |
|       if dest<dest_end then decompress_loop                                        |
|       ret                                                                          |
+------------------------------------------------------------------------------------+
```


### read_bits(s,num)

```
+-------------------------------------------------------------------------------------+
|       data=0                                                                        |
|       for i=1 to num                                                                |
|        shl collected[s],1    ;move next bit to carry, or set zeroflag if empty      |
|        if zeroflag                                                                  |
|         collected[s]=[src[s]]*1000000h+[src[s]+1]*10000h+[src[s]+2]*100h+[src[s]+3] |
|         src[s]=src[s]+4      ;read data in 32bit units, in reversed byte-order      |
|         carryflag=1          ;endbit                                                |
|         rcl collected[s],1   ;move bit31 to carry (and endbit to bit0)              |
|        rcl data,1            ;move carry to data                                    |
|       next i                                                                        |
|       ret(data)                                                                     |
+-------------------------------------------------------------------------------------+
```


### load_huffman_tree(s,width)

```
+-----------------------------------------------------------------------------------+
|       stacktop=sp                                                                 |
|       tree_index=0                                                                |
|      load_lop:                                                                    |
|       if getbits(0,1)=1                                                           |
|        push tree_index+1   ;right (bit0=right)      ;\                            
|        push tree_index     ;left                    ; memorize left/right indices |
|        tree_index=tree_index+2                      ; and load more               |
|        goto load_lop                                ;/                            |
|       dta=getbits(0,width)+8000h           ;get data (bit15=data)                 |
|      resolve_lop:                                                                 |
|       pop idx                              ;parent index                          |
|       tree[s][idx]=dta                     ;store data (or child_index)           |
|       if (idx AND 1)=0 then goto load_lop  ;load more (if it was left node)       |
|       dta=idx-1   ;child_index (to be stored at next parent_index)                |
|       if stacktop<>sp then goto resolve_lop                                       |
|       ret                                                                         |
+-----------------------------------------------------------------------------------+
```

Note: The official max tree sizes appear to be:

```
+-----------------------------------------------------------------------+
|       tree[0] = about 200h*6 halfwords                                |
|       tree[1] = about 800h*6 halfwords                                |
+-----------------------------------------------------------------------+
```




