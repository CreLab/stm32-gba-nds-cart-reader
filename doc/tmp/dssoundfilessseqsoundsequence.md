# DS Sound Files - SSEQ (Sound Sequence)


It is a converted MIDI sequence. Linked to a BANK for instruments.
SSEQ is usually found inside of SDAT files (but also exists as standalone file, eg. 3DS Circle Pad Pro test/calib, RomFS:\\extrapad_bcwav_LZ.bin\\\*.sseq, and 3DS Picture Picker, RomFS:\\sound\\csnd.LZ\\\*).

### SSEQ Header

```
+---------------------------------------------------------------------------+
|       000h 4     ID "SSEQ"                                  ;\            
|       004h 2     Byte Order    (FEFFh)                      ;             |
|       006h 2     Version       (0100h)                      ; Main header |
|       008h 4     Total Filesize                             ;             |
|       00Ch 2     Header Size (usually 10h)                  ;             |
|       00Eh 2     Number of Blocks (usually 1 = DATA)        ;/            |
|       010h 4     ID "DATA"                                  ;\            
|       014h 4     Total Filesize, minus 10h                  ; Sub header  |
|       018h 4     Offset to data (from SSEQ+0) (1Ch)         ;/            |
|       01Ch ..    Arrays of sequence data..                  ;-            |
+---------------------------------------------------------------------------+
```


NB. For the details of the SSEQ file, please refer to loveemu\'s sseq2mid

### Description
A SSEQ can have at maximum 16 tracks, notes in the range of 0..127 (middle C is 60). Each quartet note has a fixed tick length of 48. Tempo in the range of 1..240 BPM (default is 120). The SSEQ will not be played correctly if tempo higher than 240.

The SEQ player uses ARM7\'s Timer1 for timing. The ARM7\'s 4 Timers runs at 33MHz (approximately 2\^25). The SEQ player sets Timer1 reload value to 2728, prescaler to F/64. So on about every 0.0052 sec (64\*2728/33MHz) the SEQ Player will be notified (1 cycle). As a quartet note has fixed tick value of 48, the highest tempo that SEQ Player can handle is 240 BPM (60/(0.0052\*48)).

During each cycle, the SEQ player adds the tempo value to a variable. Then it checks if the value exceeds 240. If it does, the SEQ player subtracts 240 from the variable, and process the SSEQ file. Using this method, the playback is not very precise but the difference is too small to be noticed.

Take an example with tempo = 160 BPM, the SSEQ file is processed twice in 3 notifications.

```
+-----------------------------------------------------------------------+
|       cycle  variable action                                          |
|       1       0       Add 160                                         |
|       2       160     Add 160                                         |
|       3       320     Subtract 240, process once, add 160             |
|       4       240     Subtract 240, process once, add 160             |
|       5       160     Add 160                                         |
|       6       320     Subtract 240, process once, add 160             |
|       7       240     Subtract 240, process once, add 160             |
|       8       160     Add 160                                         |
+-----------------------------------------------------------------------+
```


### Events

```
+------------------------------------------------------------------------------------+
|       ID      Parameter             Description                                    |
|       00h-7Fh Velocity: 1 byte [0..127]                                            |
|               Duration: Variable Length                                            |
|                                     NOTE-ON. Duration is expressed in tick.        |
|                                     48 for quartet note.                           |
|                                     Usually it is NOT a multiple of 3.             |
|       80h     Duration: Variable Length                                            |
|                                     REST. It tells the SSEQ-sequencer to wait for  |
|                                     a certain tick. Usually it is a multiple of 3. |
|       81h     Bank & Program Number:                                               |
|               Variable Length                                                      |
|                                     bits[0..7] is the program number,              |
|                                     bits[8..14] is the bank number.                |
|                                     Bank change is seldomly found,                 |
|                                     so usually bank 0 is used.                     |
|       FEh     2 bytes Indicates which tracks are used.                             |
|               Bit0 for track 0, ... Bit15 for track 15.                            |
|               If the bit is set, the corresponding track is used.                  |
|                                     Indication begin of multitrack. Must be in the |
|                                     beginning of the first track to work. A series |
|                                     of event 0x93 follows.                         |
|       93h     4 bytes 1st byte is track number [0..15]                             |
|               The other 3 bytes are the relative adress of track data.             |
|               Add nDataOffset (usually 0x1C) to find out the absolute address.     |
|                                     SSEQ is similar to MIDI in that track data are |
|                                     stored one after one track. Unlike mod music.  |
|       94h     JUMP Address: 3 bytes                                                |
|               (Add nDataOffset (usually 0x1C) to find out the absolute address.)   |
|                                     JUMP. A jump must be backward. So that the     |
|                                     song will loop forever.                        |
|       95h     CALL Address: 3 bytes                                                |
|               (Add nDataOffset (usually 0x1C) to find out the absolute address.)   |
|       A0h-BFh See loveemu's sseq2mid for more details.                             |
|                                     Some arithmetic operations / comparions.       |
|                                     Affect how SSEQ is to be played.               |
|       C0h     1 byte  PAN                (0..127, middle is 64, uh?)               |
|       C1h     1 byte  VOLUME             (0..127)                                  |
|       C2h     1 byte  MASTER VOLUME      (0..127)                                  |
|       C3h     1 byte  TRANSPOSE (Channel Coarse Tuning) (0..64 = 64..128 in MIDI)  |
|       C4h     1 byte  PITCH BEND                                                   |
|       C5h     1 byte  PITCH BEND RANGE                                             |
|       C6h     1 byte  TRACK PRIORITY                                               |
|       C7h     1 byte  MONO/POLY          (0=Poly, 1=Mono)                          |
|       C8h     1 byte  TIE (unknown)      (0=Off, 1=On)                             |
|       C9h     1 byte  PORTAMENTO CONTROL                                           |
|       CAh     1 byte  MODULATION DEPTH   (0=Off, 1=On)                             |
|       CBh     1 byte  MODULATION SPEED                                             |
|       CCh     1 byte  MODULATION TYPE    (0=Pitch, 1=Volume, 2=Pan)                |
|       CDh     1 byte  MODULATION RANGE                                             |
|       CEh     1 byte  PORTAMENTO ON/OFF                                            |
|       CFh     1 byte  PORTAMENTO TIME                                              |
|       D0h     1 byte  ATTACK RATE                                                  |
|       D1h     1 byte  DECAY RATE                                                   |
|       D2h     1 byte  SUSTAIN RATE                                                 |
|       D3h     1 byte  RELEASE RATE                                                 |
|       D4h     1 byte  LOOP START         (how many times to be looped)             |
|       D5h     1 byte  EXPRESSION                                                   |
|       D6h     1 byte  PRINT VARIABLE     (unknown)                                 |
|       E0h     2 byte  MODULATION DELAY                                             |
|       E1h     2 byte  TEMPO                                                        |
|       E3h     2 byte  SWEEP PITCH                                                  |
|       FCh     -       LOOP END           (for LOOP START)                          |
|       FDh     -       RETURN from CALL command                                     |
|       FFh     -       EOT: End Of Track                                            |
+------------------------------------------------------------------------------------+
```




