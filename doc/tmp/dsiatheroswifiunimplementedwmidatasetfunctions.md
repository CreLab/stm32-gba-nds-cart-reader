# DSi Atheros Wifi - Unimplemented WMI DataSet Functions


Not implemented in DSi.

The \"DataSet\" feature allows the firmware to read external data from host memory for whatever purpose (maybe intended for cases where the wifi board doesn\'t contain an EEPROM, or for cases where Xtensa RAM/ROM is too small to hold the whole firmware, or just to make it easier to modify data for testing/debugging).
For the \"DataSet\" stuff, the normal Command/Response flow is reversed: the firmware does send an EVENT to request data, and the host must respond by a REPLY_CMD (except for the CLOSE_EVENT, which requires no reply).

### WMIevent(1010h:3001h) - WMIX_DSETOPENREQ_EVENT

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT32 4   dset_id          ;-ID of requested DataSet (see "dsetid.h") |
|       04h  A_UINT32 4   targ_dset_handle ;\to be echo'ed in REPLY_CMD               
|       08h  A_UINT32 4   targ_reply_fn    ; (host doesn't need to deal with this)    |
|       0Ch  A_UINT32 4   targ_reply_arg   ;/                                         |
+-------------------------------------------------------------------------------------+
```

DataSet Open Request Event. The host should open the DataSet and send a WMIX_DSETOPEN_REPLY_CMD.

### WMIevent(1010h:3003h) - WMIX_DSETDATAREQ_EVENT

```
+-------------------------------------------------------------------------------------+
|       00h  A_UINT32 4   access_cookie    ;-some kind of "filehandle" on host side   |
|       04h  A_UINT32 4   offset           ;\source offset & length of requested data 
|       08h  A_UINT32 4   length           ;/                                         |
|       0Ch  A_UINT32 4   targ_buf         ;\to be echo'ed in REPLY_CMD               
|       10h  A_UINT32 4   targ_reply_fn    ; (host doesn't need to deal with this)    |
|       14h  A_UINT32 4   targ_reply_arg   ;/                                         |
+-------------------------------------------------------------------------------------+
```

DataSet Data Request Event. The host should send the requested data via WMIX_DSETDATA_REPLY_CMD.

### WMIevent(1010h:3002h) - WMIX_DSETCLOSE_EVENT

```
+--------------------------------------------------------------------------------------+
|       00h  A_UINT32 4   access_cookie       ;-some kind of "filehandle" on host side |
+--------------------------------------------------------------------------------------+
```

DataSet Close Event. The host should close the DataSet (and doesn\'t need to send any REPLY_CMD).

### WMIcmd(002Eh:2001h) - WMIX_DSETOPEN_REPLY_CMD

```
+------------------------------------------------------------------------------------+
|       00h  A_UINT32 4   status            ;-what status ?                          |
|       04h  A_UINT32 4   targ_dset_handle  ;\                                       
|       08h  A_UINT32 4   targ_reply_fn     ; to be echo'ed from open EVENT          |
|       0Ch  A_UINT32 4   targ_reply_arg    ;/                                       |
|       10h  A_UINT32 4   access_cookie     ;-some kind of "filehandle" on host side |
|       14h  A_UINT32 4   size              ;-what size ?                            |
|       18h  A_UINT32 4   version           ;-what version ?                         |
+------------------------------------------------------------------------------------+
```

This REPLY_CMD should be send in response to WMIX_DSETOPENREQ_EVENTs.

### WMIcmd(002Eh:2002h) - WMIX_DSETDATA_REPLY_CMD

```
+---------------------------------------------------------------------------+
|       00h  A_UINT32 4   status            ;-what status ?                 |
|       04h  A_UINT32 4   targ_buf          ;\                              
|       08h  A_UINT32 4   targ_reply_fn     ; to be echo'ed from data EVENT |
|       0Ch  A_UINT32 4   targ_reply_arg    ;/                              |
|       10h  A_UINT32 4   length            ;\requested data                
|       14h  A_UINT8  LEN buf[length]       ;/                              |
+---------------------------------------------------------------------------+
```

This REPLY_CMD should be send in response to WMIX_DSETDATAREQ_EVENTs.



