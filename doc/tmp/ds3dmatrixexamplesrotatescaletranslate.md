# DS 3D Matrix Examples (Rotate/Scale/Translate)


### Identity Matrix
The MTX_IDENTITY command can be used to initialize the Position Matrix before doing any Translation/Scaling/Rotation, for example:

```
+-------------------------------------------------------------------------------------+
|       Load(Identity)                           ;no rotation/scaling used            |
|       Load(Identity), Mul(Rotate), Mul(Scale)  ;rotation/scaling (not so efficient) |
|       Load(Rotate), Mul(Scale)                 ;rotation/scaling (more efficient)   |
+-------------------------------------------------------------------------------------+
```


### Rotation Matrices
Rotation can be performed with MTX_MULT_3x3 command, simple examples are:

```
+-------------------------------------------------------------------------+
|       Around X-Axis          Around Y-Axis          Around Z-Axis       |
|       | 1.0  0     0   |     | cos   0    sin |     | cos   sin   0   | |
|       | 0    cos   sin |     | 0     1.0  0   |     | -sin  cos   0   | |
|       | 0    -sin  cos |     | -sin  0    cos |     | 0     0     1.0 | |
+-------------------------------------------------------------------------+
```


### Scale Matrix
The MTX_SCALE command allows to adjust the size of the polygon. The x,y,z parameters should be normally all having the same value, x=y=z (unless if you want to change only the height of the object, for example). Identical results can be obtained with MTX_MULT commands, however, when using lighting (MTX_MODE=2), then scaling should be done ONLY with MTX_SCALE (which keeps the length of the light\'s directional vector intact).

### Translation Matrix
The MTX_TRANS command allows to move polygons to the desired position. The polygon VTX commands are spanning only a small range of coordinates (near zero-coordinate), so translation is required to move the polygons to other locations in the world coordinates. Aside from that, translation is useful for moved objects (at variable coordinates), and for re-using an object at various locations (eg. you can create a forest by translating a tree to different coordinates).

### Matrix Multiply Order
The Matrix must be set up BEFORE sending the Vertices (which are then automatically multiplied by the matrix). When using multiple matrices multiplied with each other: Mind that, for matrix maths A\*B is NOT the same as B\*A. For example, if you combine Rotate and Translate Matrices, the object will be either rotated around it\'s own zero-coordinate, or around world-space zero-coordinate, depending on the multiply order.



