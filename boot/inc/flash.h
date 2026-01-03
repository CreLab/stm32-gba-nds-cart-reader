
// Flashing routines //

#define FLASH_CR_OPTWRE (uint32_t)(1 << 9)
#define FLASH_CR_LOCK   (uint32_t)(1 << 7)
#define FLASH_CR_STRT   (uint32_t)(1 << 6)
#define FLASH_CR_OPTER  (uint32_t)(1 << 5)
#define FLASH_CR_OPTPG  (uint32_t)(1 << 4)
#define FLASH_CR_PER    (uint32_t)(1 << 1)
#define FLASH_CR_PG     (uint32_t)(1 << 0)
#define FLASH_SR_BSY    (uint32_t)(1 << 0)
#define FLASH_SR_PGERR  (uint32_t)(1 << 2)
#define FLASH_SR_WPERR  (uint32_t)(1 << 4)
#define FLASH_KEYR      (*(volatile uint32_t*)0x40022004U)
#define FLASH_OPTKEYR   (*(volatile uint32_t*)0x40022008U)
#define FLASH_SR        (*(volatile uint32_t*)0x4002200CU)
#define FLASH_CR        (*(volatile uint32_t*)0x40022010U)
#define FLASH_AR        (*(volatile uint32_t*)0x40022014U)

static void _flash_lock() {
	// Clear the unlock state.
	FLASH_CR |= FLASH_CR_LOCK;
}

static void _flash_unlock() {
	// Only if locked!
	if (FLASH_CR & FLASH_CR_LOCK) {
		// Authorize the FPEC access.
		FLASH_KEYR = 0x45670123U;
		FLASH_KEYR = 0xcdef89abU;
	}
}

#define _flash_wait_for_last_operation() \
	/* 1 cycle wait, see STM32 errata */ \
	do {                                 \
		__asm__ volatile("nop");         \
	} while (FLASH_SR & FLASH_SR_BSY);

static void _flash_erase_page(uint32_t page_address) {
	_flash_wait_for_last_operation();

	FLASH_CR |= FLASH_CR_PER;
	FLASH_AR = page_address;
	FLASH_CR |= FLASH_CR_STRT;

	_flash_wait_for_last_operation();

	FLASH_CR &= ~FLASH_CR_PER;
}

static int _flash_page_is_erased(uint32_t addr) {
	volatile uint32_t *_ptr32 = (uint32_t*)addr;
	for (unsigned i = 0; i < 1024/sizeof(uint32_t); i++)
		if (_ptr32[i] != 0xffffffffU)
			return 0;
	return 1;
}

static void _flash_program_buffer(uint32_t address, uint16_t *data, unsigned len) {
	_flash_wait_for_last_operation();

	// Enable programming
	FLASH_CR |= FLASH_CR_PG;

	volatile uint16_t *addr_ptr = (uint16_t*)address;
	for (unsigned i = 0; i < len/2; i++) {
		addr_ptr[i] = data[i];
		_flash_wait_for_last_operation();
	}

	// Disable programming
	FLASH_CR &= ~FLASH_CR_PG;
}

static void _flash_erase_option_bytes() {
	_flash_wait_for_last_operation();

	FLASH_CR |= FLASH_CR_OPTER;
	FLASH_CR |= FLASH_CR_STRT;

	_flash_wait_for_last_operation();

	FLASH_CR &= ~FLASH_CR_OPTER;
}

static void _flash_program_option_bytes(uint32_t address, uint16_t data) {
	_flash_wait_for_last_operation();

	FLASH_CR |= FLASH_CR_OPTPG;  // Enable option byte programming.
	volatile uint16_t *addr_ptr = (uint16_t*)address;
	*addr_ptr = data;
	_flash_wait_for_last_operation();
	FLASH_CR &= ~FLASH_CR_OPTPG;  // Disable option byte programming.
}

static void _optbytes_unlock() {
	if (!(FLASH_CR & FLASH_CR_OPTWRE)) {
		// F1 uses same keys for flash and option
		FLASH_OPTKEYR = 0x45670123U;
		FLASH_OPTKEYR = 0xcdef89abU;
	}
}
