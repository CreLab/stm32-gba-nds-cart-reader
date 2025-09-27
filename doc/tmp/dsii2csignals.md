# DSi I2C Signals


Below is some pseudo code for the I2C signal transmission. The DSi hardware is doing most of that stuff automatically. The pseudo code may be useful for understanding the purpose of the start/stop/ack flags in the control register.


```
+------------------------------------------------------------------------------------+
|            START D7  D6  D5  D4  D3  D2  D1  D0 ACK  D7  D6/ .. /D1  D0 ACK STOP   |
|           __    ___ ___ ___ ___ ___ ___ ___ ___     ___ __/    /___ ___        ___ |
|       SDA   |__|___|___|___|___|___|___|___|___|___|___|_/ .. /|___|___|______|    |
|           ____   _   _   _   _   _   _   _   _   _   _  /    /   _   _   _   _____ |
|       SCL     |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |/ .. / |_| |_| |_| |_|      |
|                                                      /    /                        |
|            <--><------------------------------><--><--------------------><--><-->  |
|            Start    Device/Direction Byte      Ack   Index/Data Byte(s)  Ack Stop  |
+------------------------------------------------------------------------------------+
```


SDA should be changed at/after falling SCL edge (except for Start/Stop conditions, which are output during SCL=High).
The Device/Direction Byte is sent by master (the byte contains a 7bit device address in bit7-1, and a direction flag in bit0). The direction of the follwing index/data byte(s) depends on that direction flag (0=Write, 1=Read). The ACK bit responses are sent in opposite direction as the preceeding byte.
The SCL line is driven by master, however, when the master changes SCL from Low to HighZ, then the slave may keep SCL held Low to signalize that it isn\'t yet ready for the next bit.

### i2c_write_byte(send_start,send_stop,databyte):

```
+---------------------------------------------------------------------------------+
|       if (send_start) then i2c_start_cond()                     ;-start (if so) |
|       for i=7 downto 0, i2c_write_bit(databyte.bit(i)), next i  ;-write 8bit    |
|       nack = i2c_read_bit()                                     ;-read nack     |
|       if (send_stop) then i2c_stop_cond()                       ;-stop (if so)  |
|       return nack        ;return 0 if ack by the slave.         ;-return nack   |
+---------------------------------------------------------------------------------+
```


### i2c_read_byte(send_stop):

```
+-----------------------------------------------------------------------------------+
|       for i=7 downto 0, databyte.bit(i)=i2c_read_bit(), next i  ;-read 8bit       |
|       i2c_write_bit(nack)                                       ;-write nack      |
|       if (send_stop) then                                       ;\                
|         i2c_write_bit(1)    ;NACK (ack=high=Last byte)          ; nack (finish)   |
|         i2c_stop_cond()     ;STOP                               ;/                |
|       else                                                      ;\ack (want more) 
|         i2c_write_bit(0)    ;ACK (ack=low=More bytes)           ;/                |
|       return databyte                                           ;-return databyte |
+-----------------------------------------------------------------------------------+
```


### i2c_write_bit(bit):

```
+------------------------------------------------------------------------------------+
|       if (bit) then SDA=HighZ else SDA=Low          ;-                             |
|       I2C_delay()                                   ;-                             |
|       SCL=HighZ                                                                    |
|       wait until SCL=High (or timeout)              ;-wait (for clock stretching)  |
|       if (bit=1 and SDA=Low) then arbitration_lost();-errif other HW pulls SDA=low |
|       I2C_delay()                                   ;-                             |
|       SCL=Low                                       ;-                             |
+------------------------------------------------------------------------------------+
```


### i2c_read_bit():

```
+-----------------------------------------------------------------------------------+
|       SDA=HighZ                                     ;-let the slave drive data    |
|       I2C_delay()                                   ;-delay (one half clk)        |
|       SCL=HighZ                                                                   |
|       wait until SCL=High (or timeout)              ;-wait (for clock stretching) |
|       bit = SDA                     ;-                                            |
|       I2C_delay()                   ;-delay (one half clk)                        |
|       SCL=Low                       ;-                                            |
|       return bit                    ;-                                            |
+-----------------------------------------------------------------------------------+
```


### i2c_start_cond():

```
+--------------------------------------------------------------------------------+
|       if (started) then            ;if started, do a restart cond              |
|         SDA=HighZ                   ;-set SDA to 1                             |
|         I2C_delay()                                                            |
|         SCL=HighZ                                                              |
|         wait until SCL=High (or timeout)         ;-wait (for clock stretching) |
|         I2C_delay()         ;Repeated start setup time, minimum 4.7us          |
|       if (SDA=Low) then arbitration_lost()                                     |
|       SDA=Low                       ;-                                         |
|       I2C_delay()                                                              |
|       SCL=Low                                                                  |
|       started = true                                                           |
+--------------------------------------------------------------------------------+
```


### i2c_stop_cond():

```
+---------------------------------------------------------------------------+
|       SDA=Low                               ;-                            |
|       I2C_delay()                           ;-                            |
|       SCL=HighZ                             ;-                            |
|       wait until SCL=High (or timeout)      ;-wait (for clock stretching) |
|       I2C_delay()   ;Stop bit setup time, minimum 4us                     |
|       if (SDA=Low) then arbitration_lost()                                |
|       I2C_delay()                                                         |
|       started = false                                                     |
+---------------------------------------------------------------------------+
```


### I2C ACK/NACK Notes
There are five conditions that lead to the generation of a NACK:

```
+-----------------------------------------------------------------------------------+
|       1. No receiver is present on the bus with the transmitted address so there  |
|          is no device to respond with an acknowledge.                             |
|       2. The receiver is unable to receive or transmit because it is performing   |
|          some real-time function and is not ready to start communication with the |
|          master.                                                                  |
|       3. During the transfer, the receiver gets data or commands that it does not |
|          understand.                                                              |
|       4. During the transfer, the receiver cannot receive any more data bytes.    |
|       5. A master-receiver must signal the end of the transfer to the slave       |
|          transmitter.                                                             |
+-----------------------------------------------------------------------------------+
```

Sending the I2C Stop condition is done by sending a \"corrupted\" databit (instead of sending the first databit of the next byte) on the SDA output pin.
However, in receive mode, SDA would be in input direction (for receiving the first databit of next byte). So the master simply cannot output the Stop condition in that state (unless when using the ACK bit to notify the slave that the transfer will be stopped now).



