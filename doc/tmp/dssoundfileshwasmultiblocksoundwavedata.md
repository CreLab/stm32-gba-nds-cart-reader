# DS Sound Files - HWAS (Multiblock Sound Wave Data)


Used in NDS Over the Hedge, rom:\\vvobj\\generated\\gob\\main.gfc and main.gob
Used in NDS Downhill Jam, rom:\\vvobj\\generated\\gob\\main.gfc and main.gob
(the Hedge/Downhill archives contain both .hwas and .swav files, plus other stuff).
Reportedly, Guitar Heroes On Tour series does also use .hwas files.

```
+-------------------------------------------------------------------------------------+
|       000h 4    ID "sawh" (aka "hwas" spelled backwards)                            |
|       004h 4    Blocksize (2000h in Over the Hedge, 8000h in Guitar Heroes)         |
|       008h 4    Samplerate in Hertz (always 19996)                                  |
|       00Ch 4    Number of Channels (always 1=mono)                                  |
|       010h 4    Loop Start Sample (always 0, offset from start of data section)     |
|       014h 4    Filesize minus 200h (ie. excluding 200h-byte header)                |
|       018h 4    Loop End Sample (end of music, offset from start of data section)   |
|       01Ch 1E4h Zerofilled                                                          |
|      Data Section:                                                                  |
|       200h ..   1st data block (adpcm_header[4], plus adpcm_data[blocksize])        |
|       ...  ..   2nd data block (adpcm_header[4], plus adpcm_data[blocksize])        |
|       ...  ..   etc.                                                                |
|       ...  ..   Last data block (adpcm_header[4], plus adpcm_data[remaining bytes]) |
|       ...  ..   Padding to 200h-byte boundary                                       |
+-------------------------------------------------------------------------------------+
```

The .hwas format contains more or less the same data as Nintendo\'s .swav format:
- [DS Sound Files - SWAV (Sound Wave Data)](./dssoundfilesswavsoundwavedata.md)
The main difference is that .swav has only one data block, and .hwas is split into several data blocks (each with their own 4-byte adpcm header).



