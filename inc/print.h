#ifndef PRINT_H
#define PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nds_cart.h"
#include "util.h"

GLOBAL_STATUS print_chip_id(const s_nds_chip_id *id);
GLOBAL_STATUS print_keybuf(const char *pMsg, s_blowfish_t *pKeyBuf);

#endif // PRINT_H
