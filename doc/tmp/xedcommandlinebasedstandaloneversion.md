# XED Commandline based standalone version


**Standalone 16bit DOS version**
This version is written in turbo pascal, nevertheless fast enough to
work on computer with less than 10MHz. It uses 16bit 8086 code, and
works with all 80x86 compatible CPUs, including very old XTs.
The downside is that it is restricted to Conventional DOS Memory, so
that the maximum filesize is 640K (actually less, because the program
and operating system need to use some of that memory).

**Using the 32bit debugger-built-in version as 32bit standalone
editor**
I haven\'t yet compiled a 32bit standalone version, however, any of th
no\$xxx 32bit debuggers can be used for that purpose. By commandlin
input:

+-----------------------------------------------------------------------+
```
|       no$xxx /x <filename>   Edit text file in standalone mode        |
|                                                                       |
|    no$xxx /b <filename>   Edit binary file in standalone hexedit mode |
```
+-----------------------------------------------------------------------+


**Standalone Commandline Syntax**
- Syntax: XED \<filename\> \[/l:\<line number\>\] \| /?

+-----------------------------------------------------------------------+
```
|       <name>    Filename, optionally d:\path\name.ext                 
|       /?        Displays commandline help                             |
|       /l:<nnn>  Moves to line number nnn after loading                |
```
+-----------------------------------------------------------------------+

The filename does not require to include an extension, the program
automatically loads the first existing file with any of following
extensions appended: XED, ASM, ASC, INC, BAT, TXT, HTM, DOC, A22, PAS.

**Standalone DOS Return Value**
XED returns a three-byte return value after closing the program. This
data is used when calling XED as external editor from inside of nocash
DOS debuggers, but it might be also useful for other purposes.
Because normal DOS return values are limited to 8bits only, the three
bytes are written into video RAM at rightmost three character locations
in first line:

+-----------------------------------------------------------------------+
```
|       VSEG:77*2  Exit code   (00h=Exit normal, F9h=Exit by F9-key)    |
|       VSEG:78*2  Line number (Lower 8bits, 1..65536 in total)         |
|       VSEG:79*2  Line number (Upper 8bits)                            |
```
+-----------------------------------------------------------------------+

The color attribute for these characters is set to zero (invisible,
black on black). Use INT 10h/AH=0Fh to determine the current video mode
(AL AND 7Fh), if it is monochrome (07h) then use VSEG=B000h, otherwise
VSEG=B800h.




