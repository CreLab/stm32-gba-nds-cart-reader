/*
*****************************************************************************
**

**  File        : LinkerScript.ld
**
**  Abstract    : Linker script for STM32F103RCTx Device with
**                256KByte FLASH, 48KByte RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
**  (c)Copyright Ac6.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Ac6 permit registered System Workbench for MCU users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the System Workbench for MCU toolchain.
**
*****************************************************************************
*/

/* Enforce emission of the vector table. */
EXTERN (Vector_Table)

/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
/* Reserve the last 8 bytes of RAM to save info across reboots */
RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 49152 - 8
FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 4K
}

/* Define output sections */
SECTIONS
{
	.text : {
		*(.vectors)	/* Vector table */
		*(.text*)	/* ProgRAM code */
		. = ALIGN(4);
		*(.rodata*)	/* Read-only data */
		. = ALIGN(4);
	} >FLASH

	_etext = .;

	.data : {
		_data = .;
		*(.data*)	/* Read-write initialized data */
		. = ALIGN(4);
		_edata = .;
	} >RAM AT >FLASH
	_data_loadaddr = LOADADDR(.data);

	.bss : {
		*(.bss*)	/* Read-write zero initialized data */
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	} >RAM

	/*
	 * The .eh_fRAMe section appears to be used for C++ exception handling.
	 * You may need to fix this if you're using C++.
	 */
	/DISCARD/ : { *(.eh_fRAMe) }

	. = ALIGN(4);
	end = .;
}

PROVIDE(_stack = ORIGIN(RAM) + LENGTH(RAM));
