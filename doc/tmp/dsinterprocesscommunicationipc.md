# DS Inter Process Communication (IPC)


Allows to exchange status information between ARM7 and ARM9 CPUs.
The register can be accessed simultaneously by both CPUs (without violating access permissions, and without generating waitstates at either side).

### 4000180h - NDS9/NDS7 - IPCSYNC - IPC Synchronize Register (R/W)

```
+---------------------------------------------------------------------------+
|       Bit   Dir  Expl.                                                    |
|       0-3   R    Data input from IPCSYNC Bit8-11 of remote CPU (00h..0Fh) |
|       4-7   -    Not used                                                 |
|       8-11  R/W  Data output to IPCSYNC Bit0-3 of remote CPU   (00h..0Fh) |
|       12    -    Not used                                                 |
|       13    W    Send IRQ to remote CPU      (0=None, 1=Send IRQ)         |
|       14    R/W  Enable IRQ from remote CPU  (0=Disable, 1=Enable)        |
|       15-31 -    Not used                                                 |
+---------------------------------------------------------------------------+
```


### 4000184h - NDS9/NDS7 - IPCFIFOCNT - IPC Fifo Control Register (R/W)

```
+--------------------------------------------------------------------------------+
|       Bit   Dir  Expl.                                                         |
|       0     R    Send Fifo Empty Status      (0=Not Empty, 1=Empty)            |
|       1     R    Send Fifo Full Status       (0=Not Full, 1=Full)              |
|       2     R/W  Send Fifo Empty IRQ         (0=Disable, 1=Enable)             |
|       3     W    Send Fifo Clear             (0=Nothing, 1=Flush Send Fifo)    |
|       4-7   -    Not used                                                      |
|       8     R    Receive Fifo Empty          (0=Not Empty, 1=Empty)            |
|       9     R    Receive Fifo Full           (0=Not Full, 1=Full)              |
|       10    R/W  Receive Fifo Not Empty IRQ  (0=Disable, 1=Enable)             |
|       11-13 -    Not used                                                      |
|       14    R/W  Error, Read Empty/Send Full (0=No Error, 1=Error/Acknowledge) |
|       15    R/W  Enable Send/Receive Fifo    (0=Disable, 1=Enable)             |
|       16-31 -    Not used                                                      |
+--------------------------------------------------------------------------------+
```


### 4000188h - NDS9/NDS7 - IPCFIFOSEND - IPC Send Fifo (W)

```
+-----------------------------------------------------------------------+
|       Bit0-31  Send Fifo Data (max 16 words; 64bytes)                 |
+-----------------------------------------------------------------------+
```


### 4100000h - NDS9/NDS7 - IPCFIFORECV - IPC Receive Fifo (R)

```
+-----------------------------------------------------------------------+
|       Bit0-31  Receive Fifo Data (max 16 words; 64bytes)              |
+-----------------------------------------------------------------------+
```


### IPCFIFO Notes
When IPCFIFOCNT.15 is disabled: Writes to IPCFIFOSEND are ignored (no data is stored in the FIFO, the error bit doesn\'t get set though), and reads from IPCFIFORECV return the oldest FIFO word (as usually) (but without removing the word from the FIFO).
When the Receive FIFO is empty: Reading from IPCFIFORECV returns the most recently received word (if any), or ZERO (if there was no data, or if the FIFO was cleared via IPCFIFOCNT.3), and, in either case the error bit gets set.
The Fifo-IRQs are edge triggered, IF.17 gets set when the condition \"(IPCFIFOCNT.2 AND IPCFIFOCNT.0)\" changes from 0-to-1, and IF.18 gets set when \"(IPCFIFOCNT.10 AND NOT IPCFIFOCNT.8)\" changes from 0-to-1. The IRQ flags can be acknowledged even while that conditions are true.



