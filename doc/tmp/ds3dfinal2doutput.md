# DS 3D Final 2D Output


The final 3D image (consisting of polygons and rear-plane) is passed to 2D Engine A as BG0 layer (provided that DISPCNT is configured to use 3D as BG0).

### Scrolling
The BG0HOFS register (4000010h) can be used the scroll the 3D layer horizontally, the scroll region is 512 pixels, consisting of 256 pixels for the 3D image, followed by 256 transparent pixels, and then wrapped to the 3D image again. Vertical scrolling (and rotation/scaling) cannot be used on the 3D layer.

### BG Priority Order
The lower 2bit of the BG0CNT register (4000008h) control the priority relative to other BGs and OBJs, so the 3D layer can be in front of or behind 2D layers. All other bits in BG0CNT have no effect on 3D, namely, mosaic cannot be used on the 3D layer.

### Special Effects
Special Effects Registers (4000050h..54h) can be used as such:

```
+------------------------------------------------------------------------------+
|       Brightness up/down with BG0 as 1st Target via EVY   (as for 2D)        |
|       Blending with BG0 as 2nd Target via EVA/EVB         (as for 2D)        |
|       Blending with BG0 as 1st Target via 3D Alpha-values (unlike as for 2D) |
+------------------------------------------------------------------------------+
```

The latter method probably (?) uses per-pixel 3D alpha values as such: EVA=A/2, and EVB=16-A/2, without using the EVA/EVB settings in 4000052h.

### Window Feature
Window Feature (4000040h..4Bh) can be used as for 2D.
\"If the 3D screen has highest priority, then alpha-blending is always enabled, regardless of the Window Control register\'s color effect enable flag \[ie. regardless of Bit5 of WIN0IN, WIN1IN, WINOBJ, WINOUT registers\]\"\... not sure if that is true, and if it superseedes the effect selection in Port 4000050h\...?



