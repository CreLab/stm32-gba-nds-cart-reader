# DSi ES Block Encryption


ES Block Encryption, for lack of a better name, is a Nintendo DSi specific data encryption method. It\'s used for some SD/MMC files:

```
+-----------------------------------------------------------------------+
|       FAT16:\sys\dev.kp                                               
|       FAT16:\ticket\000300tt\4ggggggg.tik (tickets)                   
|       SD Card: .bin files (aka Tad Files) (contains multiple blocks)  |
|       .twl-*.der files (within the "verdata" NARC file)               |
+-----------------------------------------------------------------------+
```


### Block Layout

```
+------------------------------------------------------------------------------+
|       00000h      BLKLEN   Data Block      (AES-CCM encrypted)               |
|       BLKLEN+00h  10h      Data Checksum   (AES-CCM MAC value on above Data) |
|       BLKLEN+10h  1        Fixed 3Ah       (AES-CTR encrypted)               |
|       BLKLEN+11h  0Ch      Nonce           (unencrypted)                     |
|       BLKLEN+1Dh  1        BLKLEN.bit16-23 (AES-CTR encrypted)               |
|       BLKLEN+1Eh  1        BLKLEN.bit8-15  (AES-CTR encrypted)               |
|       BLKLEN+1Fh  1        BLKLEN.bit0-7   (AES-CTR encrypted)               |
+------------------------------------------------------------------------------+
```

BLKLEN can be max 20000h. If the Data is bigger than 128Kbytes, then it\'s split into multiple block(s) with BLKLEN=20000h (the last block can have smaller BLKLEN).

### Data Block Encryption/Decryption (AES-CCM)

```
+-----------------------------------------------------------------------+
|       IV[00h..0Bh]=[BLKLEN+11h..1Ch]  ;Nonce                          |
|       IV[0Ch..0Fh]=Don't care (not used for CCM)                      |
+-----------------------------------------------------------------------+
```

With that IV value, apply AES-CCM on the Data Block:

```
+-----------------------------------------------------------------------+
|       00000h      BLKLEN   Data Block      (AES-CCM)                  |
+-----------------------------------------------------------------------+
```

Observe that some DSi files have odd BLKLEN values, so you may need to append padding bytes to the Data Block (the DSi hardware requires full 16-byte chunks for encryption/decryption).
Alternately, one could use AES-CTR for decryption (this may be faster/easier, and allows random access, though without MAC verify), using this IV value:

```
+--------------------------------------------------------------------------------+
|       IV[00h..02h]=offset/10h + 1     ;CTR value for desired 16-byte block     |
|       IV[03h..0Eh]=[BLKLEN+11h..1Ch]  ;Nonce for CTR                           |
|       IV[0Fh]=02h                     ;Indicate 3-byte wide CTR (fixed on DSi) |
+--------------------------------------------------------------------------------+
```


### Data Block Padding (16-byte alignment)
For encryption, it\'s simple: Just append 00h byte(s) as padding value.
For decryption, it\'s more complicated: The padding values should be ENCRYPTED 00h-bytes (required to get the same MAC result as for encryption). If you don\'t want to verify the MAC, then you could append whatever dummy bytes. If you want to verify the MAC, then you could pre-calculate the padding values as so:

```
+--------------------------------------------------------------------------------+
|       IV[00h..02h]=BLKLEN/10h + 1     ;CTR value for last 16-byte block        |
|       IV[03h..0Eh]=[BLKLEN+11h..1Ch]  ;Nonce                                   |
|       IV[0Fh]=02h                     ;Indicate 3-byte wide CTR (fixed on DSi) |
+--------------------------------------------------------------------------------+
```

Then, use AES-CTR (not CCM) to encrypt sixteen 00h-bytes, the last byte(s) of the result can be then used as padding value(s). The padding values should be pre-calculated BEFORE starting the CCM decryption (the DSi hardware allows only one AES task at once, so they cannot be calculated via AES-CTR when AES-CCM decryption is in progress).

### Verifying the Footer values (AES-CTR)
This step is needed only for verification purposes (encryption tools should create these values, but decryption tools may or may not verify them).

```
+-----------------------------------------------------------------------+
|       IV[00h]=00h                     ;Zero                           |
|       IV[01h..0Ch]=[BLKLEN+11h..1Ch]  ;Nonce                          |
|       IV[0Dh..0Fh]=00h,00h,00h        ;Zero                           |
+-----------------------------------------------------------------------+
```

With that IV value (and same Key as for AES-CCM), apply AES-CTR on the last 16 bytes of the block:

```
+-----------------------------------------------------------------------+
|       BLKLEN+10h  1        Fixed 3Ah       (AES-CTR encrypted)        |
|       BLKLEN+11h  0Ch      Nonce           (unencrypted)              |
|       BLKLEN+1Dh  1        BLKLEN.bit16-23 (AES-CTR encrypted)        |
|       BLKLEN+1Eh  1        BLKLEN.bit8-15  (AES-CTR encrypted)        |
|       BLKLEN+1Fh  1        BLKLEN.bit0-7   (AES-CTR encrypted)        |
+-----------------------------------------------------------------------+
```

AES-CTR is XORing the data stream (encrypted bytes will turn into unencrypted bytes, and vice-versa), so the result would look as so:

```
+----------------------------------------------------------------------------------+
|       BLKLEN+10h  1        Fixed 3Ah       (unencrypted)       (to be verified)  |
|       BLKLEN+11h  0Ch      Nonce           (AES-CTR encrypted) (useless/garbage) |
|       BLKLEN+1Dh  1        BLKLEN.bit16-23 (unencrypted)       (to be verified)  |
|       BLKLEN+1Eh  1        BLKLEN.bit8-15  (unencrypted)       (to be verified)  |
|       BLKLEN+1Fh  1        BLKLEN.bit0-7   (unencrypted)       (to be verified)  |
+----------------------------------------------------------------------------------+
```

Mind that BLKLEN can be odd, so data at BLKLEN+00h..1Fh isn\'t necessarily located at 4-byte aligned addresses.



