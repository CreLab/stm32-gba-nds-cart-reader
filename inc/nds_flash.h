#ifndef NDS_FLASH_H
#define NDS_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "util.h"

uint32_t nds_flash_read_id(void);
void nds_flash_read_bytes(uint32_t addr, uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* NDS_FLASH_H */
