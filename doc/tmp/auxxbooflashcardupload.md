# AUX Xboo Flashcard Upload


### Flashcard Upload
Allows to write data to flashcards which are plugged into GBA cartridge slot, cartridge is automatically started after writing. On initial power-up, hold down START+SELECT to prevent the GBA from booting the old program in the flashcard.
The Upload function in Utility menu uses flashcard mode for files bigger than 256KB (otherwise uses multiboot mode automatically). Also, there\'s a separate Upload to Flashcard function in Remote Access submenu, allowing to write files of 256KB or less to flashcard if that should be desired.

### Supported Flashcards
Function currently tested with Visoly Flash Advance (FA) 256Mbit (32MB) Turbo cartridge. Should also work with older FA versions. Please let me know if you are using other flashcards which aren\'t yet supported.

### Flashcard Performance
Writing to flashcards may become potentially slow because of chip erase/write times, cable transmission time, and the sheer size of larger ROM-images. However, developers whom are testing different builts of their project usually won\'t need to rewrite the complete flashcard, Xboo uses a highspeed checksum mechanism (16MB/sec) to determine which flashcard sector(s) have changed, and does then re-write only these sector(s).
To eliminate transmission time, data transfer takes place in the erase phases. Erase/write time depends on the flashcard type, should be circa 1-2 seconds per 256KB sector. Because the cartridge is programmed directly in the GBA there\'s no need to remove it from the GBA when writing to it.

### Developers Advice
Locate your program fragments at fixed addresses, for example, code and data blocks each aligned to 64K memory boundaries, so that data remains at the same location even when the size of code changes. Fill any blank spaces by value FFh for faster write time. Reduce the size of your ROM-image by efficient memory use (except for above alignment trick). Include the burst boot backdoor in your program, allowing to re-write the flashcard directly without resetting the GBA.

### Lamers Advice
Xboo Flashcard support does not mean to get lame & to drop normal multiboot support, if your program fits into 256KB then make it \<both\> flashcard \<and\> multiboot compatible - multiboot reduces upload time, increases your flashcard lifetime, and will also work for people whom don\'t own flashcards.



