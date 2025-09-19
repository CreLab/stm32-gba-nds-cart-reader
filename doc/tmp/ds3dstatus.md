# DS 3D Status


**4000600h - GXSTAT - Geometry Engine Status Register (R and R/W)**
Bit 30-31 are R/W. Writing \"1\" to Bit15 does reset the Error Fla
(Bit15), and additionally resets the Projection Stack Pointer (Bit13),
and probably (?) also the Texture Stack Pointer. All other GXSTAT bits
are read-only.

```
+-----------------------------------------------------------------------+
|       0     BoxTest,PositionTest,VectorTest Busy (0=Ready, 1=Busy)    |
|       1                                                               |
|    BoxTest Result  (0=All Outside View, 1=Parts or Fully Inside View) |
|       2-7   Not used                                                  |
|       8-12  Po                                                        |
| sition & Vector Matrix Stack Level (0..31) (lower 5bit of 6bit value) |
|       13    Projection Matrix Stack Level        (0..1)               |
|       14    Ma                                                        |
| trix Stack Busy (0=No, 1=Yes; Currently executing a Push/Pop command) |
|       15    Ma                                                        |
| trix Stack Overflow/Underflow Error (0=No, 1=Error/Acknowledge/Reset) |
|       16-24 Number of 40bit-entries in Command FIFO  (0..256)         |
|      (24)   Command FIFO Full (MSB of above)  (0=No, 1=Yes; Full)     |
|       25                                                              |
|  Command FIFO Less Than Half Full  (0=No, 1=Yes; Less than Half-full) |
|       26    Command FIFO Empty                (0=No, 1=Yes; Empty)    |
|       2                                                               |
| 7    Geometry Engine Busy (0=No, 1=Yes; Busy; Commands are executing) |
|       28-29 Not used                                                  |
|       30-31 C                                                         |
| ommand FIFO IRQ (0=Never, 1=Less than half full, 2=Empty, 3=Reserved) |
+-----------------------------------------------------------------------+
```

When GXFIFO IRQ is enabled (setting 1 or 2), the IRQ flag (IF.Bit21) is
set while and as long as the IRQ condition is true (and attempts to
acknowledge the IRQ by writing to IF.Bit21 have no effect). So that, the
IRQ handler must either fill the FIFO, or disable the IRQ (setting 0),
BEFORE trying to acknowledge the IRQ.

**4000604h - RAM_COUNT - Polygon List & Vertex RAM Count Register (R)**

```
+-----------------------------------------------------------------------+
|       0-1                                                             |
| 1   Number of Polygons currently stored in Polygon List RAM (0..2048) |
|       12-15  Not used                                                 |
|       16-                                                             |
| 28  Number of Vertices currently stored in Vertex RAM       (0..6144) |
|       13-15  Not used                                                 |
+-----------------------------------------------------------------------+
```

If a SwapBuffers command has been sent, then the counters are reset 10
cycles (at 33.51MHz clock) after next VBlank.

**4000320h - RDLINES_COUNT - Rendered Line Count Register (R)**
Rendering starts in scanline 214, the rendered lines are stored in a
buffer that can hold up to 48 scanlines. The actual screen output begins
after scanline 262, the lines are then read from the buffer and sent to
the display. Simultaneously, the rendering engine keeps writing new
lines to the buffer (ideally at the same speed than display output, so
the buffer would always contain 48 pre-calculated lines).

```
+-----------------------------------------------------------------------+
|       0-5                                                             |
|  Minimum Number (minus 2) of buffered lines in previous frame (0..46) |
|       6-31   Not used                                                 |
+-----------------------------------------------------------------------+
```

If rendering becomes slower than the display output, then the number of
buffered lines decreases. Smaller values in RDLINES indicate that
additional load to the rendering engine may cause buffer underflows in
further frames, if so, the program should reduce the number of polygons
to avoid display glitches.
Even if RDLINES becomes zero, it doesn\'t indicate whether actual buffe
underflows have occured or not (underflows are indicated in DISP3DCNT
Bit12).



