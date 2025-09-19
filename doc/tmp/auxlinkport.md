# AUX Link Port


### Serial Link Port Pin-Out (GBA:\"EXT\" - GBA SP:\"EXT.1\")

```
+-----------------------------------------------------------------------+
|       Pin  Name  Cable                                                |
|       1    VDD35 N/A       GBA Socket     GBA Plug   Old "8bit" Plug  |
|       2    SO    Red       ___________    _________    ___________    |
|       3    SI    Orange   |  2  4  6  |  / 2  4  6 \  |  2  4  6  |   
|       4    SD    Brown     \_1_ 3 _5_/   \_1_ 3 _5_/   \_1__3__5_/    
|       5    SC    Green         '-'           '-'                      |
|       6    GND   Blue      Socket Outside View / Plug Inside View     |
|       Shield     Shield                                               |
+-----------------------------------------------------------------------+
```

Note: The pin numbers and names are printed on the GBA mainboard, colors as used in Nintendo\'s AGB-005 and older 8bit cables.

### Serial Link/Power Supply Port (GBA-Micro: \"EXT.\")

```
+-----------------------------------------------------------------------+
|       1  In  DC (Supply 5.2VDC)  ___________________                  |
|       2  Out V3 (SIO 3.3VDC)    |  1 2 3 4 5 6 7 8  |                 |
|       3  I/O SO (SIO RCNT.3)    | ================= |                 |
|       4  I/O SI (SIO RCNT.2)     \_________________/                  
|       5  I/O SD (SIO RCNT.1)                                          |
|       6  I/O SC (SIO RCNT.0)                                          |
|       7  OUT DG (SIO GROUND)                                          |
|       8  In  DG (Supply GROUND)                                       |
|       -  -   -  (Shield not connected)                                |
+-----------------------------------------------------------------------+
```


### Cable Diagrams (Left: GBA Cable, Right: 8bit Gameboy Cable)

```
+-----------------------------------------------------------------------+
|       Big Plug  Middle Socket  Small Plug    Plug 1         Plug 2    |
|        SI _________________     ____ SI       SI ______  ______SI     |
|        SO ____________SO   |__ | ___ SO       SO ______><______SO     |
|        GND____________GND______|____GND       GND_____________GND     |
|        SD ____________SD____________ SD       SD               SD     |
|        SC ____________SC____________ SC       SC _____________ SC     |
|        Shield_______Shield_______Shield       Shield_______Shield     |
+-----------------------------------------------------------------------+
```


### Normal Connection
Just connect the plugs to the two GBAs and leave the Middle Socket disconnected, in this mode both GBAs may behave as master or slave, regardless of whether using big or small plugs.
The GBA is (NOT ???) able to communicate in Normal mode with MultiPlay cables which do not have crossed SI/SO lines.

### Multi-Play Connection
Connect two GBAs as normal, for each further GBAs connect an additional cable to the Middle socket of the first (or further) cable(s), up to four GBAs may be connected by using up to three cables.
The GBA which is connected to a Small Plug is master, the slaves are all connected to Large Plugs. (Only small plugs fit into the Middle Socket, so it\'s not possible to mess up something here).

### Multi-Boot Connection
MultiBoot (SingleGamepak) is typically using Multi-Play communication, in this case it is important that the Small plug is connected to the master/sender (ie. to the GBA that contains the cartridge).

### Non-GBA Mode Connection
First of all, it is not possible to link between 32bit GBA games and 8bit games, parts because of different cable protocol, and parts because of different signal voltages.
However, when a 8bit cartridge is inserted (the GBA is switched into 8bit compatibility mode) it may be connected to other 8bit games (monochrome gameboys, CGBs, or to other GBAs which are in 8bit mode also, but not to GBAs in 32bit mode).
When using 8bit link mode, an 8bit link cable must be used. The GBA link cables won\'t work, see below modification though.

### Using a GBA 32bit cable for 8bit communication
Open the middle socket, and disconnect Small Plugs SI from GND, and connect SI to Large Plugs SO instead. You may also want to install a switch that allows to switch between SO and GND, the GND signal should be required for MultiPlay communication only though.
Also, cut off the plastic ledge from the plugs so that they fit into 8bit gameboy sockets.

### Using a GBA 8bit cable for 32bit communication
The cable should theoretically work as is, as the grounded SI would be required for MultiPlay communication only. However, software that uses SD for Slave-Ready detection won\'t work unless when adding a SD-to-SD connection (the 8bit plugs probably do not even contain SD pins though).



