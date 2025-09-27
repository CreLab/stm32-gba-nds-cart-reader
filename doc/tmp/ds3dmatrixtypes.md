# DS 3D Matrix Types


Essentially, all matrices in the NDS are 4x4 Matrices, consisting of 16 values, m\[0..15\]. Each element is a signed fixed-point 32bit number, with a fractional part in the lower 12bits.
The other Matrix Types are used to reduce the number of parameters being transferred, for example, 3x3 Matrix requires only nine parameters, the other seven elements are automatically set to 0 or 1.0 (whereas \"1.0\" means \"1 SHL 12\" in 12bit fixed-point notation).


```
+-----------------------------------------------------------------------+
|        _      4x4 Matrix       _        _    Identity Matrix    _     |
|       | m[0]  m[1]  m[2]  m[3]  |      |  1.0   0     0     0    |    |
|       | m[4]  m[5]  m[6]  m[7]  |      |  0     1.0   0     0    |    |
|       | m[8]  m[9]  m[10] m[11] |      |  0     0     1.0   0    |    |
|       |_m[12] m[13] m[14] m[15]_|      |_ 0     0     0     1.0 _|    |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|        _      4x3 Matrix       _        _  Translation Matrix   _     |
|       | m[0]  m[1]  m[2]   0    |      |  1.0   0     0     0    |    |
|       | m[3]  m[4]  m[5]   0    |      |  0     1.0   0     0    |    |
|       | m[6]  m[7]  m[8]   0    |      |  0     0     1.0   0    |    |
|       |_m[9]  m[10] m[11]  1.0 _|      |_m[0]  m[1]  m[2]   1.0 _|    |
+-----------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------+
|        _      3x3 Matrix       _        _     Scale Matrix      _     |
|       | m[0]  m[1]  m[2]   0    |      | m[0]   0     0     0    |    |
|       | m[3]  m[4]  m[5]   0    |      |  0    m[1]   0     0    |    |
|       | m[6]  m[7]  m[8]   0    |      |  0     0    m[2]   0    |    |
|       |_ 0     0     0     1.0 _|      |_ 0     0     0     1.0 _|    |
+-----------------------------------------------------------------------+
```




