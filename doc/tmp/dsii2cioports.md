# DSi I2C I/O Ports


### 4004500h - DSi7 - I2C_DATA (R/W)

```
+-----------------------------------------------------------------------+
|       0-7  Data (or Device, or Register)                              |
+-----------------------------------------------------------------------+
```

When sending data, I2C_DATA should be written \<before\> setting I2C_CNT.bit7.
When reading data, I2C_DATA should be read \<after\> I2C_CNT.bit7 goes off.
Alongsides with the 8bit data, an additional 1bit \"Ack\" flag is transferred as response to the data (ie. in opposite direction of data direction), the Ack is located in I2C_CNT.Bit4, and it\'s usually indicating errors (or in some cases it appears to be also used to indicate that no further data is to be transferred).

### 4004501h - DSi7 - I2C_CNT (R/W)

```
+-------------------------------------------------------------------------------------+
|       0    Stop     (0=No, 1=Stop signal, after last byte)                          |
|       1    Start    (0=No, 1=Start signal, before first byte)                       |
|       2    Error    (0=No, 1=Pause/Flush? after Error, used with/after Stop)        |
|                     (1=Transfer only selected Start/Stop signal(s), without data?)  |
|                     (Nintendo seems to use bit2+bit0 to (try to) overcome problems  |
|                     with the BPTWL chip's quirky Stop handling)                     |
|       3    Unknown/unused (0)                                                       |
|       4    Ack (0=High=Error/LastRead, 1=Low=Okay) ;For DataRead:W, for DataWrite:R |
|       5    Data Direction   (0=Write, 1=Read) (note: Ack uses opposite direction)   |
|       6    Interrupt Enable (0=Disable, 1=Enable)                                   |
|       7    Start/busy       (0=Ready, 1=Start/busy)                                 |
+-------------------------------------------------------------------------------------+
```


### I2C Transfer Flowchart
The first byte (with the \"Start\" condition) contains the device number, which consists of a 7bit chip ID and a direction flag in bit0 (0=Write or 1=Read). The direction flag applies to all following bytes (until last byte with \"Stop\" condition), that rule means that \"Write Index & Write Data\" can be done in a single step, whilst \"Write Index & Read Data\" must be split into two separate steps (each with own \"Start/Stop\" conditions):

```
+-------------------------------------------------------------------------------------+
|      For Writing:                                                                   |
|       Write Device+0 (with Start condition)                 ;\                      
|       Write Index byte(s)                                   ; write index + data    |
|       Write Data byte(s) (last byte with Stop condition)    ;/                      |
|      For Reading:                                                                   |
|       Write Device+0 (with Start condition)                 ;\1st step: write index 
|       Write Index byte(s)                                   ;/                      |
|       Write Device+1 (with Start condition)                 ;\2nd step: read data   
|       Read Data byte(s) (last byte with ACK=0 and Stop)     ;/                      |
+-------------------------------------------------------------------------------------+
```

The index is usually a single byte (except for Aptina cameras, which do use 16bit indices transferred in two bytes; ordered MSB, LSB).
Per-byte transfer completion is indicated by the Start/busy flag, which should also indicate if the I2C chip is ready for next byte (I2C devices can hold the clock line low if they aren\'t ready), however, the BPTWL chip somehow doesn\'t support that, and it should be accessed with an extra delay:

```
+-----------------------------------------------------------------------+
|       Invoke byte-transfer                                            |
|       Do WaitByLoop (needed for the BPTWL device only)                |
|       Wait for start/busy flag to get zero                            |
+-----------------------------------------------------------------------+
```

Note: The DSi firmware is doing eight retries per I2C command (in case of receiving wrong ACK bytes), unknown if that\'s really required, a stable system should never need to do retries.



