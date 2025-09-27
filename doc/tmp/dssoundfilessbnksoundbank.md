# DS Sound Files - SBNK (Sound Bank)


This seems to assign ADSR patterns to each note of each SWAV instrument\...?

\"A bank is linked to up to 4 SWAR files which contain the samples. It defines the instruments which a SSEQ sequence can use. You may imagine SSEQ + SBNK + SWAR are similar to module music created by trackers.\" uh?

### SBNK Header

```
+---------------------------------------------------------------------------+
|       000h 4   ID "SBNK"                                    ;\            
|       004h 2   Byte Order    (FEFFh)                        ;             |
|       006h 2   Version       (0100h)                        ; Main header |
|       008h 4   Total Filesize                               ;             |
|       00Ch 2   Header Size (usually 10h)                    ;             |
|       00Eh 2   Number of Blocks (usually 1 = DATA)          ;/            |
|       010h 4   ID "DATA"                                    ;\            
|       014h 4   Total Filesize, minus 10h                    ;             |
|       018h 20h Reserved (0) (for use at runtime)            ; Sub header  |
|       038h 4   Number of Instruments (SWAV's)               ;             |
|       03Ch N*4 Instrument Records (1+2+1 bytes per instr.)  ;/            |
|       ...  ..  Instrument Data (depending of above records) ;-            |
+---------------------------------------------------------------------------+
```


### Instrument Record

```
+-----------------------------------------------------------------------------------+
|       000h 1   fRecord     ;can be either 0, 1..4, 16 or 17                       |
|       001h 2   nOffset     ;absolute offset of the data in file  ;uh, misaligned? |
|       003h 1   Reserved (0)                                                       |
+-----------------------------------------------------------------------------------+
```


### fRecord = 0, it is empty (unknown purpose, dummy? or maybe disable ADSR?)
nOffset will also = 0.

### fRecord \< 16, the record is a note/wave definition
\"I have seen values 1, 2 and 3. But it seems the value does not affect the wave/note definition that follows. Instrument record size is 10 bytes.\"

```
+------------------------------------------------------------------------+
|       00h 10    SWAV, SWAR, Note, Attack, Decay, Sustain, Release, Pan |
+------------------------------------------------------------------------+
```


### fRecord = 16, the record is a range of note/wave definitions

```
+---------------------------------------------------------------------------+
|       00h      1   Lower note (0..127)          ;eg. 10 ;\notes 10..20    
|       01h      1   Upper note (0..127)          ;eg. 20 ;/                |
|       02h+N*12 2   Unknown (usually 0001h)                                |
|       04h+N*12 10  SWAV, SWAR, Note, Attack, Decay, Sustain, Release, Pan |
+---------------------------------------------------------------------------+
```


### fRecord = 17, the record is a regional wave/note definition

```
+---------------------------------------------------------------------------+
|       00h      1   End of 1st region (0..127)   ;eg. 25  = notes 0..25    |
|       01h      1   End of 2nd region (0..127)   ;eg. 35  = notes 26..35   |
|       02h      1   End of 3rd region (0..127)   ;eg. 45  = notes 36..45   |
|       03h      1   End of 4th region (0..127)   ;eg. 55  = notes 46..55   |
|       04h      1   End of 5th region (0..127)   ;eg. 65  = notes 56..65   |
|       05h      1   End of 6th region (0..127)   ;eg. 127 = notes 66..last |
|       06h      1   End of 7th region (0..127)   ;eg. 0   = none           |
|       07h      1   End of 8th region (0..127)   ;eg. 0   = none           |
|       08h+N*12 2   Unknown (usually 0001h)                                |
|       08h+N*12 10  SWAV, SWAR, Note, Attack, Decay, Sustain, Release, Pan |
+---------------------------------------------------------------------------+
```

REMARKS: Unknown bytes before wave/defnition definition = 5, not 1 in stage_04_bank.sbnk, stage_04.sdat, Rom No.1156, uh?

### SWAV, SWAR, Note, Attack, Decay, Sustain, Release, Pan

```
+---------------------------------------------------------------------------------+
|       00h 2  SWAV Number   the swav used                                        |
|       02h 2  SWAR Mumber   the swar used (see Info Block --> "BANK Info Entry") |
|       04h 1  Note Number   (0..127)                                             |
|       05h 1  Attack Rate   (0..127, 127=fast)                                   |
|       06h 1  Decay Rate    (0..127, 127=fast)                                   |
|       07h 1  Sustain Level (0..127, 127=stay at max, no decay)                  |
|       08h 1  Release Rate  (0..127, 127=fast)                                   |
|       09h 1  Pan           (0..127, 64=middle) (uh, what=left, what=right?)     |
+---------------------------------------------------------------------------------+
```


### Articulation Data

```
+-----------------------------------------------------------------------+
|                  .                   <-- max level (127)              |
|                 / \                                                   
|                /   \                                                  
|               /     '---------.      <-- sustain level (0..127)       |
|              /                 \                                      
|             /                   \                                     
|       -----'---------------------'-- <-- min level (0)                |
|           Attack Decay Sustain Release                                |
+-----------------------------------------------------------------------+
```



```
+---------------------------------------------------------------------------------+
|       "The SEQ Player treats 0 as the 100% amplitude value and -92544 (723*128) |
|       as the 0% amplitude value. The starting ampltitude is 0% (-92544)." uh?   |
+---------------------------------------------------------------------------------+
```



```
+-----------------------------------------------------------------------------------+
|       "During the attack phase, in each cycle, the SSEQ Player calculates the new |
|       amplitude value: amplitude value = attack rate * amplitude value / 255. The |
|       attack phase stops when amplitude reaches 0." THAT IS... NON-LINEAR attack? |
+-----------------------------------------------------------------------------------+
```



```
+----------------------------------------------------------------------------------+
|       "During the decay phase, in each cycle, the SSEQ Player calculates the new |
|       amplitude value: amplitude value = amplitude value - decay rate.           |
|       Note the starting amplitude value is 0. The decay phase stops when         |
|       amplitude reaches sustain level." THAT IS... LINEAR decay/release?         |
+----------------------------------------------------------------------------------+
```




