# DS 3D Matrix Examples (Maths Basics)


Below is a crash-course on matrix maths. Most of it is carried out automatically by the hardware. So this chapter is relevant only if you are interested in details about what happens inside of the 3D engine.

### Matrix-by-Matrix Multiplication
Matrix multiplication, C = A \* B, is possible only if the number of columns in A is equal to the number of rows in B, so it works fine with the 4x4 matrices which are used in the NDS. For the multiplication, assume matrix C to consist of elements cyx, and respecitively, matrix A and B to consist of elements ayx and byx. So that C = A \* B looks like:

```
+---------------------------------------------------------------------------+
|       | c11 c12 c13 c14 |     | a11 a12 a13 a14 |     | b11 b12 b13 b14 | |
|       | c21 c22 c23 c24 |  =  | a21 a22 a23 a24 |  *  | b21 b22 b23 b24 | |
|       | c31 c32 c33 c34 |     | a31 a32 a33 a34 |     | b31 b32 b33 b34 | |
|       | c41 c42 c43 c44 |     | a41 a42 a43 a44 |     | b41 b42 b43 b44 | |
+---------------------------------------------------------------------------+
```

Each element in C is calculated by multiplying the elements from one row in A by the elements from the corresponding column in B, and then taking the sum of the products, ie.

```
+-----------------------------------------------------------------------+
|       cyx = ay1*b1x + ay2*b2x + ay3*b3x + ay4*b4x                     |
+-----------------------------------------------------------------------+
```

In total, that requires 64 multiplications (four multiplications for each of the 16 cyx elements), and 48 additions (three per cyx element), the hardware carries out that operation at a relative decent speed of 30..35 clock cycles, possibly by performing several multiplications simultaneously with separate multiply units.
Observe that for matrix multiplication, A\*B is NOT the same as B\*A.

### Matrix-by-Vector & Vector-by-Matrix Multiplication
Vectors are Matrices with only one row, or only one column. Multiplication works as for normal matrices; the number of rows/columns must match up, repectively, row-vectors can be multiplied by matrices; and matrices can be multiplied by column-vectors (but not vice-versa). Eg. C = A \* B:

```
+---------------------------------------------------------------------------+
|                                                       | b11 b12 b13 b14 | |
|       | c11 c12 c13 c14 |  =  | a11 a12 a13 a14 |  *  | b21 b22 b23 b24 | |
|                                                       | b31 b32 b33 b34 | |
|                                                       | b41 b42 b43 b44 | |
+---------------------------------------------------------------------------+
```

The formula for calculating the separate elements is same as above,

```
+-----------------------------------------------------------------------+
|       cyx = ay1*b1x + ay2*b2x + ay3*b3x + ay4*b4x                     |
+-----------------------------------------------------------------------+
```

Of which, C and A have only one y-index, so one may replace \"cyx and ayx\" by \"c1x and a1x\", or completely leave out the y-index, ie. \"cx and ax\".

### Matrix-by-Number Multiplication
Simply multiply all elements of the Matrix by the number, C = A \* n:

```
+-----------------------------------------------------------------------+
|       cyx = ayx*n                                                     |
+-----------------------------------------------------------------------+
```

Of course, works also with vectors (matrices with only one row/column).

### Matrix-to-Matrix Addition/Subtraction
Both matrices must have the same number of rows & columns, add/subtract all elements with corresponding elements in other matrix, C = A +/- B:

```
+-----------------------------------------------------------------------+
|       cyx = ayx +/- byx                                               |
+-----------------------------------------------------------------------+
```

Of course, works also with vectors (two matrices with only one row/column).

### Vectors
A vector, for example (x,y,z), consists of offsets along x-,y-, and z-axis. The line from origin to origin-plus-offset is having two characteristics: A direction, and a length.
The length (aka magnitude) can be calculated as L=sqrt(x\^2+y\^2+z\^2).

### Vector-by-Vector Multiplication
This can be processed as LineVector\*RowVector, so the result is a number (aka scalar) (aka a matrix with only 1x1 elements). Multiplying two (normalized) vectors results in: \"cos(angle)=vec1\*vec2\", ie. the cosine of the angle between the two vectors (eg. used for light vectors). Multiplying a vector with itself, and taking the square root of the result obtains its length, ie. \"length=sqrt(vec\^2)\".
That stuff should be done with 3-dimensional vectors (not 4-dimensionals).

### Normalized Vectors
Normalized Vectors (aka Unit Vectors) are vectors with length=1.0. To normalize a vector, divide its coordinates by its length, ie. x=x/L, y=y/L, z=z/L, the direction remains the same, but the length is now 1.0.
On the NDS, normalized vectors should have a length of something less than 1.0 (eg. something like 0.99) because several NDS registers are limited to 1bit sign, 0bit integer, Nbit fractional part (so vectors that are parallel to the x,y,z axes, or that become parallel to them after rotation, cannot have a length of 1.0).

### Fixed-Point Numbers
The NDS uses fixed-point numbers (rather than floating point numbers). Addition and Subtraction works as with normal integers, provided that the fractional part is the same for both numbers. If it is not the same: Shift-left the value with the smaller fractional part.
For multiplication, the fractional part of result is the sum of the fractional parts (eg. 12bit fraction \* 12bit fraction = 24bit fraction; shift-right the result by 12 to convert it 12bit fraction). The NDS matrix multiply unit is maintaining the full 24bit fraction when processing the

```
+-----------------------------------------------------------------------+
|       cyx = ay1*b1x + ay2*b2x + ay3*b3x + ay4*b4x                     |
+-----------------------------------------------------------------------+
```

formula, ie. the three additions are using full 24bit fractions (with carry-outs to upper bits), the final result of the additions is then shifted-right by 12.
For division, it\'s vice versa, the fractions of the operands are substracted, 24bit fraction / 12bit fraction = 12bit fraction. When dividing two 12bit numbers, shift-left the first number by 12 before division to get a result with 12bit fractional part.

### Four-Dimensional Matrices
The NDS uses four-dimensional matrices and vectors, ie. matrices with 4x4 elements, and vectors with 4 elements. The first three elements are associated with the X,Y,Z-axes of the three-dimensional space. The fourth element is somewhat a \"W-axis\".
With 4-dimensional matrices, the Translate matrix can be used to move an object to another position. Ie. once when you\'ve setup a matrix (which may consists of pre-multiplied scaling, rotation, translation matrices), then that matrix can be used on vertices to perform the rotation, scaling, translation all-at-once; by a single Vector\*Matrix operation.
With 3-dimensional matrices, translation would require a separate addition, additionally to the multiply operation.



