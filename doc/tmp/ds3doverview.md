# DS 3D Overview


The NDS 3D hardware consists of a Geometry Engine, and a Rendering Engine.

### Geometry Engine (Precalculate coordinates & assign polygon attributes)
Geometry commands can be sent via Ports 4000440h and up (or alternately, written directly to Port 4000400h).
The commands include matrix and vector multiplications, the purpose is to rotate/scale/translate coordinates (vertices), the resulting coordinates are stored in Vertex RAM.
Moreover, it allows to assign attributes to the polygons and vertices, that includes vertex colors (or automatically calculated light colors), texture attributes, number of vertices per polygon (three or four), and a number of flags, these attributes are stored in Polygon RAM. Polygon RAM also contains pointers to the corresponding vertices in Vertex RAM.

### Swap Buffers (Pass data from the Geometry Engine to the Rendering Engine)
The hardware includes two sets of Vertex/Polygon RAM, one used by the Geometry Engine, one by the Rendering Engine. The SwapBuffers command simply exchanges these buffers (so the new Geometry Data is passed to the Rendering Engine) (and the old buffer is emptied, so the Geometry engine can write new data to it). Additionally, the two parameter bits from the \<previous\> SwapBuffers command are copied to the Geometry Engine.
Data that is NOT swapped: SwapBuffers obviously can\'t swap Texture memory (so software must take care that Texture memory is kept mapped throughout rendering). Moreover, the rendering control registers (ports 4000060h, and 4000330h..40003BFh) are not swapped (so that values must be kept intact during rendering, too).

### Rendering Engine (Display Output)
The Rendering Engine draws the various Polygons, and outputs them as BG0 layer to the 2D Video controller (which may then output them to the screen, or to the video capture unit). The Rendering part is done automatically by hardware, so the software has little influence on it.
Rendering is done scanline-by-scanline, so there\'s only a limited number of clock cycles per scanline, which is limiting the maximum number of polygons per scanline. However, due to the 48-line cache (see below), some scanlines are allowed to exceed that maximum.
Rendering starts 48 lines in advance (while still in the Vblank period) (and does then continue throughout the whole display period), the rendered data is written to a small cache that can hold up to 48 scanlines.

### Scanline Cache vs Framebuffer
Note: There\'s only the 48-line cache (not a full 192-line framebuffer to store the whole rendered image). That is perfectly reasonable since animated data is normally drawn only once (so there would be no need to store it). That, assuming that the Geometry Engine presents new data every frame (otherwise, if the Geometry software is too slow, or if the image isn\'t animated, then the hardware is automatically rendering the same image again, and again).



