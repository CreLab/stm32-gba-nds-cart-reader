# DS Video Capture and Main Memory Display Mode


### 4000064h - NDS9 - DISPCAPCNT - 32bit - Display Capture Control Register (R/W)
Capture is supported for Display Engine A only.

```
+-----------------------------------------------------------------------------------+
|       0-4   EVA               (0..16 = Blending Factor for Source A)              |
|       5-7   Not used                                                              |
|       8-12  EVB               (0..16 = Blending Factor for Source B)              |
|       13-15 Not used                                                              |
|       16-17 VRAM Write Block  (0..3 = VRAM A..D) (VRAM must be allocated to LCDC) |
|       18-19 VRAM Write Offset (0=00000h, 0=08000h, 0=10000h, 0=18000h)            |
|       20-21 Capture Size      (0=128x128, 1=256x64, 2=256x128, 3=256x192 dots)    |
|       22-23 Not used                                                              |
|       24    Source A          (0=Graphics Screen BG+3D+OBJ, 1=3D Screen)          |
|       25    Source B          (0=VRAM, 1=Main Memory Display FIFO)                |
|       26-27 VRAM Read Offset  (0=00000h, 0=08000h, 0=10000h, 0=18000h)            |
|       28    Not used                                                              |
|       29-30 Capture Source    (0=Source A, 1=Source B, 2/3=Sources A+B blended)   |
|       31    Capture Enable    (0=Disable/Ready, 1=Enable/Busy)                    |
+-----------------------------------------------------------------------------------+
```

Notes:
VRAM Read Block (VRAM A..D) is selected in DISPCNT Bits 18-19.
VRAM Read Block can be (or must be ?) allocated to LCDC (MST=0).
VRAM Read Offset is ignored (zero) in VRAM Display Mode (DISPCNT.16-17).
VRAM Read/Write Offsets wrap to 00000h when exceeding 1FFFFh (max 128K).
Capture Sizes less than 256x192 capture the upper-left portion of the screen.
Blending factors EVA and EVB are used only if \"Source A+B blended\" selected.
After setting the Capture Enable bit, capture starts at next line 0, and the capture enable/busy bit is then automatically cleared (in line 192, regardless of the capture size).

Capture data is 15bit color depth (even when capturing 18bit 3D-images).
Capture A: Dest_Intensity = SrcA_Intensitity ; Dest_Alpha=SrcA_Alpha.
Capture B: Dest_Intensity = SrcB_Intensitity ; Dest_Alpha=SrcB_Alpha.
Capture A+B (blending):

```
+-----------------------------------------------------------------------+
|      Dest_Intensity = (  (SrcA_Intensitity * SrcA_Alpha * EVA)        |
|                        + (SrcB_Intensitity * SrcB_Alpha * EVB) ) / 16 |
|      Dest_Alpha = (SrcA_Alpha AND (EVA>0)) OR (SrcB_Alpha AND EVB>0)) |
+-----------------------------------------------------------------------+
```


Capture provides a couple of interesting effects.
For example, 3D Engine output can be captured via source A (to LCDC-allocated VRAM), in the next frame, either Graphics Engine A or B can display the captured 3D image in VRAM image as BG2, BG3, or OBJ (from BG/OBJ-allocated VRAM); this method requires to switch between LCDC- and BG/OBJ-allocation.
Another example would be to capture Engine A output, the captured image can be displayed (via VRAM Display mode) in the following frames, simultaneously the new Engine A output can be captured, blended with the old captured image; in that mode moved objects will leave traces on the screen; this method works with a single LCDC-allocated VRAM block.
- [DS Video Display System Block Diagram](./dsvideodisplaysystemblockdiagram.md)

### 4000068h - NDS9 - DISP_MMEM_FIFO - 32bit - Main Memory Display FIFO (R?/W)
Intended to send 256x192 pixel 32K color bitmaps by DMA directly

```
+------------------------------------------------------------------------------+
|      - to Screen A             (set DISPCNT to Main Memory Display mode), or |
|      - to Display Capture unit (set DISPCAPCNT to Main Memory Source).       |
+------------------------------------------------------------------------------+
```

The FIFO can receive 4 words (8 pixels) at a time, each pixel is a 15bit RGB value (the upper bit, bit15, is unused).
Set DMA to Main Memory mode, 32bit transfer width, word count set to 4, destination address to DISP_MMEM_FIFO, source address must be in Main Memory.
Transfer starts at next frame.
Main Memory Display/Capture is supported for Display Engine A only.



