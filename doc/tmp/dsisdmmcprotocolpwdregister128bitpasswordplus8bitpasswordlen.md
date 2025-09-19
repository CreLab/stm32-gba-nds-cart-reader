# DSi SD/MMC Protocol: PWD Register (128bit Password plus 8bit Password len)


### CMD40 - SD - Defined by DPS Spec (Data Protection System) (type=adtc)

```
+-----------------------------------------------------------------------+
|       Defined by DPS Spec.                                            |
+-----------------------------------------------------------------------+
```

Response: R1
Additional Data Transfer (to/from whatever):

```
+-----------------------------------------------------------------------+
|       unknown                                                         |
+-----------------------------------------------------------------------+
```

Single block read type. Intended to read whatever \"public\" data, which is available even if the card is locked.

### CMD42 - SD/MMC (SD v2.00 and up) - SPI - LOCK_UNLOCK (type=adtc)

```
+-----------------------------------------------------------------------+
|       31-0  Reserved bits (0)                                         |
+-----------------------------------------------------------------------+
```

Response: R1 (MMC: R1b?)
MMC?: Additional Data Transfer (from card): Busy signal for \"R1b\" response
Additional Data Transfer (to card):

```
+-------------------------------------------------------------------------------------+
|       Note: Before using this command, the size of the following data block (ie.    |
|             "1st..Nth/Extra" byte) must be set via SET_BLOCKLEN command (CMD16).    |
|       1st byte: Flags                                                               |
|         Bit7-4 Reserved (0)                                                         |
|         Bit3   ERASE       Force Erase (1=Erase WHOLE CARD and clear password)      |
|         Bit1   LOCK_UNLOCK Lock card (0=Unlock, 1=Lock) (default on power up: Lock) |
|         Bit1   CLR_PWD     Clears password  (0=no, 1=yes)                           |
|         Bit0   SET_PWD     Set new password (0=no, 1=yes)                           |
|       2nd byte: PWDS_LEN   Length of the Password(s) in bytes ("3rd..Nth" byte)     |
|       3rd..Nth byte: Password (old password, if SET_PWD: followed by new password)  |
|       Extra byte: Alignment padding (only in DDR50 mode, if above is odd num bytes) |
+-------------------------------------------------------------------------------------+
```

Used to set/clear the password (=to change the password), or to lock/unlock the card (=to log out/log in). If the password exists, then the default state on power-up is Locked (user is logged out).
In locked state, the card will accept only \"Basic Commands\" (class 0), plus CMD16,40,42, plus ACMD41,42. Observe that this will prevent some initialization commands (for example, switching to 4bit bus via SET_BUS_WIDTH (ACMD6) isn\'t possible on locked cards).
The password is stored in a 128bit PWD register, so password can be max 16 bytes long. The PWDS_LEN value can be max 32 bytes (when sending old+new password). The length of the current/old password is stored in an 8bit PWD_LEN register (though due to the above limit, that \"8bit\" value can be in range 0..16 only; PWD_LEN=0 means that there is no password, which is somewhat equivalent to what happens when setting the CLR_PWD bit?).
PWD Notes:
Related CSR status bits are: CARD_IS_LOCKED and LOCK_UNLOCK_FAILED. Presence of the locking feature is indicated by the CCC \"class 7\" bit in CSD register.
Many SD cards are internally containing separate controller and memory chips, so it might be quite easy to bypass the locking by desoldering one of those chips.



