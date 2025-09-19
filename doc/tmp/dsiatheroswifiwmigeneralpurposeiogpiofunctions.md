# DSi Atheros Wifi - WMI General Purpose I/O (GPIO) Functions


### WMIcmd(002Eh:2003h) - WMIX_GPIO_OUTPUT_SET_CMD ;reply=3006h
Parameters:

```
+-------------------------------------------------------------------------------+
|       00h  A_UINT32  4     set_mask;             /* pins to set               |
|       04h  A_UINT32  4     clear_mask;           /* pins to clear             |
|       08h  A_UINT32  4     enable_mask;          /* pins to enable for output |
|       0Ch  A_UINT32  4     disable_mask;         /* pins to disable/tristate  |
+-------------------------------------------------------------------------------+
```

Set GPIO pin output state.
In order for output to be driven, a pin must be enabled for output.
This can be done during initialization through the GPIO Configuration DataSet, or during operation with the enable_mask.
If a request is made to simultaneously set/clear or set/disable or clear/disable or disable/enable, results are undefined.
NB: Some of the WMIX APIs use a 32-bit mask. On Targets that support more than 32 GPIO pins, those APIs only support the first 32 GPIO pins.

### WMIcmd(002Eh:2004h) - WMIX_GPIO_INPUT_GET_CMD ;reply=3005h
Parameters:

```
+-----------------------------------------------------------------------+
|       Unknown (none?)                                                 |
+-----------------------------------------------------------------------+
```


### WMIcmd(002Eh:2005h) - WMIX_GPIO_REGISTER_SET_CMD ;reply=3006h, too
Parameters:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4    gpioreg_id;           /* GPIO register ID   |
|       04h  A_UINT32  4    value;                /* value to write     |
+-----------------------------------------------------------------------+
```

Set a GPIO register. For debug/exceptional cases.
Values for gpioreg_id are GPIO_ID\_\*, defined in a platform-dependent header, gpio.h.

### WMIcmd(002Eh:2006h) - WMIX_GPIO_REGISTER_GET_CMD ;reply=3005h, too
Parameters:

```
+--------------------------------------------------------------------------+
|       00h  A_UINT32  4    gpioreg_id;           /* GPIO register to read |
+--------------------------------------------------------------------------+
```

Get a GPIO register. For debug/exceptional cases.

### WMIcmd(002Eh:2007h) - WMIX_GPIO_INTR_ACK_CMD
Parameters:

```
+----------------------------------------------------------------------------------+
|         A_UINT32              ack_mask;             /* interrupts to acknowledge |
+----------------------------------------------------------------------------------+
```

Host acknowledges and re-arms GPIO interrupts. A single message should be used to acknowledge all interrupts that were delivered in an earlier WMIX_GPIO_INTR_EVENT message.

### WMIevent(1010h:3004h) - WMIX_GPIO_INTR_EVENT ;used (interrupt)
Event Data:

```
+----------------------------------------------------------------------------+
|       00h  A_UINT32  4   intr_mask;            /* pending GPIO interrupts  |
|       04h  A_UINT32  4   input_values;         /* recent GPIO input values |
+----------------------------------------------------------------------------+
```

Target informs Host of GPIO interrupts that have ocurred since the last WMIX_GIPO_INTR_ACK_CMD was received. Additional information \-- the current GPIO input values is provided \-- in order to support use of a GPIO interrupt as a Data Valid signal for other GPIO pins.

### WMIevent(1010h:3005h) - WMIX_GPIO_DATA_EVENT ;used (reply to 2004h and 2006h)
Event Data:

```
+-----------------------------------------------------------------------+
|       00h  A_UINT32  4   value;                                       |
|       04h  A_UINT32  4   reg_id;                                      |
+-----------------------------------------------------------------------+
```

Target responds to Host\'s earlier WMIX_GPIO_INPUT_GET_CMD request using a GPIO_DATA_EVENT with value set to the mask of GPIO pin inputs and reg_id set to GPIO_ID_NONE.
Target responds to Hosts\'s earlier WMIX_GPIO_REGISTER_GET_CMD request using a GPIO_DATA_EVENT with value set to the value of the requested register and reg_id identifying the register (reflects the original request).
NB: reg_id supports the future possibility of unsolicited WMIX_GPIO_DATA_EVENTs (for polling GPIO input), and it may simplify Host GPIO support.

### WMIevent(1010h:3006h) - WMIX_GPIO_ACK_EVENT ;used (reply to 2003h and 2005h)
Event Data:

```
+-----------------------------------------------------------------------+
|       Unknown (none?) (confirms GPIO_xxx_SET commands)                |
+-----------------------------------------------------------------------+
```


### GPIO Constants

```
+----------------------------------------------------------------------------+
|       AR6001_GPIO_PIN_COUNT   = 18                                         |
|       AR6002_GPIO_PIN_COUNT   = 18  ;aka hw2.0                             |
|       AR6003_GPIO_PIN_COUNT   = 28  ;aka hw4.0 ;XXX shouldn't that be 26 ? |
|       MCKINLEY_GPIO_PIN_COUNT = 57  ;aka hw6.0                             |
+----------------------------------------------------------------------------+
```

Values of gpioreg_id in the WMIX_GPIO_REGISTER_SET_CMDID and WMIX_GPIO_REGISTER_GET_CMDID commands come in two flavors. If the upper bit of gpioreg_id is CLEAR, then the remainder is interpreted as one of these values. This provides platform-independent access to GPIO registers. If the upper bit (GPIO_ID_OFFSET_FLAG) of gpioreg_id is SET, then the remainder is interpreted as a platform-specific GPIO register offset.

```
+---------------------------------------------------------------------------+
|       GPIO_ID_OUT         = 00000000h                                     |
|       GPIO_ID_OUT_W1TS    = 00000001h                                     |
|       GPIO_ID_OUT_W1TC    = 00000002h                                     |
|       GPIO_ID_ENABLE      = 00000003h                                     |
|       GPIO_ID_ENABLE_W1TS = 00000004h                                     |
|       GPIO_ID_ENABLE_W1TC = 00000005h                                     |
|       GPIO_ID_IN          = 00000006h                                     |
|       GPIO_ID_STATUS      = 00000007h                                     |
|       GPIO_ID_STATUS_W1TS = 00000008h                                     |
|       GPIO_ID_STATUS_W1TC = 00000009h                                     |
|       GPIO_ID_PIN0        = 0000000Ah                                     |
|       GPIO_ID_PIN(n)      = (GPIO_ID_PIN0+(n))  ;=0000000Ah and up        |
|       GPIO_ID_NONE        = FFFFFFFFh                                     |
|       GPIO_ID_OFFSET_FLAG       = 80000000h                               |
|       GPIO_ID_REG_MASK          = 7fffffffh                               |
|       GPIO_ID_IS_OFFSET(reg_id) = (((reg_id) & GPIO_ID_OFFSET_FLAG) != 0) |
+---------------------------------------------------------------------------+
```




