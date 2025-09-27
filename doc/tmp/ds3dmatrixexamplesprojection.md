# DS 3D Matrix Examples (Projection)


The most important matrix is the Projection Matrix (to be initialized with MTX_MODE=0 via MTX_LOAD_4x4 command). It does specify the dimensions of the view volume.

With Perspective Projections more distant objects will appear smaller, with Orthogonal Projects the size of the objects is always same regardless of their distance.


```
+-----------------------------------------------------------------------+
|       Perspective Projection     Orthogonal Projection                |
|                        __                  __________                 |
|            top __..--''  |            top |          |                |
|               |   view   |                |   view   |                |
|       Eye ----|--------->|        Eye ----|--------->|                |
|               |__volume  |                |  volume  |                |
|          bottom  ''--..__|          bottom|__________|                |
|             near        far             near        far               |
+-----------------------------------------------------------------------+
```


Correctly initializing the projection matrix (as shown in the examples below) can be quite difficult (mind that fixed point multiply/divide requires to adjust the fixed-point width before/after calculation). For beginners, it may be recommended to start with a simple Identity Matrix (MTX_IDENTITY command) used as Projection Matrix (ie. Ortho with t,b,l,r set to +/-1).

### Orthogonal Projections (Ortho)

```
+-----------------------------------------------------------------------+
|       | (2.0)/(r-l)       0             0            0     |          |
|       |      0       (2.0)/(t-b)        0            0     |          |
|       |      0            0        (2.0)/(n-f)       0     |          |
|       | (l+r)/(l-r)  (b+t)/(b-t)   (n+f)/(n-f)      1.0    |          |
+-----------------------------------------------------------------------+
```

n,f specify the distance from eye to near and far clip planes. t,b,l,r are the coordinates of near clip plane (top,bottom,left,right). For a symmetrical view (ie. the straight-ahead view line centered in the middle of viewport) t,b,l,r should be usually t=+ysiz/2, b=-ysiz/2, r=+xsiz/2, l=-xsiz/2; the (xsiz/ysiz) ratio should be usually equal to the viewport\'s (width/heigh) ratio. Examples for a asymmetrical view would be b=0 (frog\'s view), or t=0 (bird\'s view).

### Left-Right Asymmetrical Perspective Projections (Frustum)

```
+-----------------------------------------------------------------------+
|       | (2*n)/(r-l)       0             0            0     |          |
|       |      0       (2*n)/(t-b)        0            0     |          |
|       | (r+l)/(r-l)  (t+b)/(t-b)   (n+f)/(n-f)     -1.0    |          |
|       |      0            0       (2*n*f)/(n-f)      0     |          |
+-----------------------------------------------------------------------+
```

n,f,t,b,l,r have same meanings as above (Ortho), the difference is that more distant objects will appear smaller with Perspective Projection (unlike Orthogonal Projection where the size isn\'t affected by the distance).

### Left-Right Symmetrical Perspective Projections (Perspective)

```
+-----------------------------------------------------------------------+
|       | cos/(asp*sin)     0             0            0     |          |
|       |      0         cos/sin          0            0     |          |
|       |      0            0        (n+f)/(n-f)     -1.0    |          |
|       |      0            0       (2*n*f)/(n-f)      0     |          |
+-----------------------------------------------------------------------+
```

Quite the same as above (Frustum), but with symmetrical t,b values (which are in this case obtained from a vertical view range specified in degrees), and l,r are matched to the aspect ratio of the viewport (asp=height/width).

### Moving the Camera
After initializing the Projection Matrix, you may multiply it with Rotate and/or Translation Matrices to change camera\'s position and view direction.



