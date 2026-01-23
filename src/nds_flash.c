#include <stm32f1xx_hal.h>
#include <string.h>

#include "nds_flash.h"
#include "gpios.h"

#define WREN 0x06 // Write Enable (No Parameters)
#define WRDI 0x04 // Write Disable (No Parameters)
#define RDID 0x9F // Read JEDEC Identification (Read 1..3 ID Bytes) (Manufacturer, Device Type, Capacity)
#define RDSR 0x05 // Read Status Register (Read Status Register, endless repeated)
#define READ 0x03 // Read Data Bytes (Write 3-Byte-Address, read endless data stream)
#define FAST 0x0B // Read Data Bytes at Higher Speed (Write 3-Byte-Address, write 1
#define PW   0x0A // Page Write (Write 3-Byte-Address, write 1..256 data bytes)
#define PP   0x02 // Page Program (Write 3-Byte-Address, write 1..256 data bytes)
#define PE   0xDB // Page Erase 100h bytes (Write 3-Byte-Address) (10ms typ, 20ms max)
#define SE   0xD8 // Sector Erase 10000h bytes (Write 3-Byte-Address) (1s typ, 5s max)
#define DP   0xB9 // Deep Power-down (No Parameters) (consumption 1uA typ, 10uA max)
#define RDP  0xAB // Release from Deep Power-down (No Parameters) (30us)

static void nds_flash_init(void);

__attribute__((always_inline)) inline void spi_dir_config(void) { GPIOC->CRL = 0x14111111; }

__attribute__((always_inline)) static inline void spi_bb_write_byte(uint8_t data, size_t cycles)
{
#define SEND_SPI_BIT(mask) \
        GPIOC_CLR_PIN(PIN_CLK); \
        (data & mask) ? GPIOC_SET_PIN(PIN_MOSI) : GPIOC_CLR_PIN(PIN_MOSI); \
        wait_cycles(cycles); \
        GPIOC_SET_PIN(PIN_CLK); \
        wait_cycles(cycles);

    SEND_SPI_BIT(0x80u);
    SEND_SPI_BIT(0x40u);
    SEND_SPI_BIT(0x20u);
    SEND_SPI_BIT(0x10u);
    SEND_SPI_BIT(0x08u);
    SEND_SPI_BIT(0x04u);
    SEND_SPI_BIT(0x02u);
    SEND_SPI_BIT(0x01u);

#undef SEND_SPI_BIT
    GPIOC_SET_PIN(PIN_MOSI);
    delay_us(5);
}

static __attribute__((always_inline)) inline void spi_bb_read_byte(uint8_t* data, size_t cycles)
{
    uint8_t rx = 0x00;
    *data = 0x00;

#define READ_SPI_BIT(i) \
        GPIOC_CLR_PIN(PIN_CLK); \
        wait_cycles(cycles); \
        rx = (GPIOC->IDR & PIN_MISO) ? 1 : 0; \
        GPIOC_SET_PIN(PIN_CLK); \
        *data |= (uint8_t)(rx << i); \
        wait_cycles(cycles);

    READ_SPI_BIT(7u);
    READ_SPI_BIT(6u);
    READ_SPI_BIT(5u);
    READ_SPI_BIT(4u);
    READ_SPI_BIT(3u);
    READ_SPI_BIT(2u);
    READ_SPI_BIT(1u);
    READ_SPI_BIT(0u);

#undef READ_SPI_BIT
    GPIOC_SET_PIN(PIN_MOSI);
    delay_us(3);
}

__attribute__((always_inline)) static inline void nds_flash_disable_infrared_core(void)
{
    spi_bb_write_byte(0x00, ONE_MHZ_IN_CYCLES);

    uint32_t timeout = 5000;
    do {
        timeout--;
        delay_us(1);
    } while (!(GPIOC->IDR & PIN_MISO) && timeout > 0);

    GPIOC_CLR_PIN(PIN_EEPROMCS);

    delay_us(40);
}

void nds_flash_init(void)
{
    spi_dir_config();

    GPIOC_SET_PIN(PIN_MOSI);
    GPIOC_SET_PIN(PIN_ROMCS);
    GPIOC_SET_PIN(PIN_EEPROMCS);
    HAL_Delay(5);

    // Reset must be high for flash communication enable */
    GPIOC_SET_PIN(PIN_RESET);
    HAL_Delay(10);

    nds_flash_disable_infrared_core();
}

uint32_t nds_flash_read_id(void)
{
    uint8_t data[4];

    nds_flash_init();

    spi_bb_write_byte(RDID, FOUR_MHZ_IN_CYCLES);
    spi_bb_read_byte(&data[0], FOUR_MHZ_IN_CYCLES);
    spi_bb_read_byte(&data[1], FOUR_MHZ_IN_CYCLES);
    spi_bb_read_byte(&data[2], FOUR_MHZ_IN_CYCLES);

    GPIOC_SET_PIN(PIN_EEPROMCS);
    HAL_Delay(1);

    return *((uint32_t*)data);
}

void nds_flash_read_bytes(uint32_t addr, uint8_t *data, size_t len)
{
    nds_flash_init();

    spi_bb_write_byte(READ, FOUR_MHZ_IN_CYCLES); // READ command
    spi_bb_write_byte((addr >> 16) & 0xFF, FOUR_MHZ_IN_CYCLES);
    spi_bb_write_byte((addr >> 8) & 0xFF, FOUR_MHZ_IN_CYCLES);
    spi_bb_write_byte(addr & 0xFF, FOUR_MHZ_IN_CYCLES);

    for(size_t i = 0; i < len; i++)
    {
        spi_bb_read_byte(&data[i], FOUR_MHZ_IN_CYCLES);
    }

    GPIOC_SET_PIN(PIN_EEPROMCS);
    HAL_Delay(1);
}
