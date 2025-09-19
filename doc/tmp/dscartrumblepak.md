# DS Cart Rumble Pak


### DS Rumble Option Pak
The Rumble Pak comes bundled with Metroid Prime Pinball. It contains a small actuator made by ALPS to make it rumble. The original device (NTR-008) is sized like a normal GBA cartridge, and there\'s also shorter variant for the DS-Lite (USG-006).
The rumble pak is pretty simple internally, it only wires up to a few pins on the GBA Cartridge Port:

```
+-----------------------------------------------------------------------+
|       VCC, GND, /WR, AD1, and IRQ (grounded)                          |
+-----------------------------------------------------------------------+
```

AD1 runs into a little 8 pin chip, which is probably just a latch on the rising edge of /WR. A line runs from this chip to a transistor that is directly connected to the actuator. The only other chip on the board is a 5 pin jobber, probably a power component.
For detection, AD1 seems to be pulled low when reading from it, the other AD lines are open bus (containing the halfword address), so one can do:

```
+-----------------------------------------------------------------------------+
|       for i=0 to 0FFFh                                                      |
|         if halfword[8000000h+i*2]<>(i and FFFDh) then <not_a_ds_rumble_pak> |
|       next i                                                                |
+-----------------------------------------------------------------------------+
```

The actuator doesn\'t have an on/off setting like a motor, it rumbles when you switch it between the two settings. Switch frequently for a fast rumble, and fairly slowly for more of a \'tick\' effect. That should be done via timer irq:

```
+-----------------------------------------------------------------------+
|       rumble_state = rumble_state xor 0002h                           |
|       halfword[8000000h]=rumble_state                                 |
+-----------------------------------------------------------------------+
```

Unknown if one of the two states has higher power-consumption than the other, ie. if it\'s a \"pull/release\" mechanism, if so, then disabling rumble should be done by using the \"release\" state, which would be AD1=0, or AD1=1\...?
Note: The v3 firmware can detect the Rumble Pak as an option pak, but it does not provide an enable/disable rumble option in the alarm menu.

### Other DS Rumble device
There\'s also another DS add-on with rumble. That device uses AD8 (instead AD1) to control rumble, and, it\'s using a classic motor (ie. it\'s rumbling while and as long as the latched AD8 value is \"1\").
- [DS Cart Slider with Rumble](./dscartsliderwithrumble.md)

### GBA Rumble Carts
There are also a few GBA games that contain built-in Rumble, and which could be used by NDS games as well. To be user friendly, best support both types.
- [GBA Cart Rumble](./gbacartrumble.md)



