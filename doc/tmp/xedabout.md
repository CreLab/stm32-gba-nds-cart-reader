# XED About


### About XED
XED is a text editor, the executable is fast and small, and it includes comfortable editing functions. It is both intended for standard .TXT files (or any other ASCII files, such like .ASM for assembler source code). Also, the line-wrapping support (.XED files) can be used for authoring stories, specifications, etc. Most of the features are much the same as for other text editors, some special functions are pointed out below:

### Block Selection
XED supports good old quality block mechanisms, allowing to copy/move the selection directly to cursor position by Ctrl+K,C/V hotkeys (without needing to use paste). For data exchange with other programs or text files, the block can be directly written to (or loaded from) file by Ctrl+K,R/W. And, mainstream copy/cut/paste functions are supported as well, by Ctrl+Ins, Shift+Del, Shift+Ins.
Note: The block remains selected even when typing text, and it won\'t get deleted when touching Del-key.

### Condensed Display Mode
Condensed mode is activated by \"F6,C\" key combination. In this mode, only lines beginning with colon \":\", or (for assembler source code files) with semicolon-colon \";:\", for example:

```
+-----------------------------------------------------------------------+
|       :Chapter IV                                                     |
|       ;:---Sound Engine---                                            |
+-----------------------------------------------------------------------+
```

Normal block functions can be used in this mode to Move, Copy, or Delete whole \'chapter(s)\'. Cursor keys can be used to move the cursor to a specific chapter. Pushing Enter or Escape terminates condensed mode.

### Column Block Mode
Column mode is activated by \"Ctrl+K,N\" key combination. In this mode, the block selection appears as a rectangular area, allowing to deal with tables & columns in text files by using copy/delete, indent/unindent block functions.
Typing \"Ctrl+K,N\" again will return to normal block mode (in which any lines between begin/end of the block will be selected at full length).

### Blank Space
Unlike most other editors, XED allows to move the cursor to any screen location, including at horizontal positions after the end of the current line. Entering space characters at such locations advances the cursor position, but does not actually store space characters in the file.
When typing text, spaces are automatically inserted between line-end and cursor position. Respectively, ending spaces are automatically deleted (eg. assume that the line contains \"Hello !\", deleting \"!\" will also remove the space character, internally).
That is of course all happening behind your back, you won\'t have to care about it - but you can be sure that there\'ll be no hidden spaces filling up disk space.

### Tabulation Marks / TAB-Key
The TAB Key advances the cursor to the next higher tabulation location (usually in steps of eight columns, counted from leftmost screen border), and the appropriate number of spaces is inserted into the file if necessary.
In overwrite mode (de-/activated by INS Key), the TAB Key simply advances the cursor without actually inserting spaces (and without overwriting existing text by spaces).

### Tabulation Marks / CHR(9)
When enabled in setup (default), TAB marks are automatically expanded into appropriate number of spaces (ie. towards next \"8-column\" position) when loading a file.
The file is normally saved by using raw SPC characters, without any TABs. Optionally, it can be saved by using \"best-fill\" SPCs and TABs (disabled by default), that feature may conflict with third party tools (assemblers, compilers, etc). In order to reduce the risk of such problems, best-fill is suppressed in quoted lines (by using \' or \" or \<\> quotation marks, eg. db \'Hello !\').

### Line Wrapping
Line wrapping is enabled/disabled by \"F5+W\" key combination. Wrapping is automatically enabled when loading a file with extension \".XED\".
In the file, wrapped lines are using CR characters as soft linebreaks, paragraphs are terminated by normal CR,LF characters.
Note: It\'d be recommended to convert .XED files into \'standard\' formats such like .TXT or .HTM before releasing them, but preferably NOT into disliked bloated file formats such like .PDF or .DOC.

### Word Processing
Aside from the above line-wrapping support, no other \'word processing\' features are included, the program provides normal \'type writer\' functions, not more, not less. In particular, any overload such like bold or colored text, big and small fonts, bitmaps and different fonts are disliked.



