#ifndef PPANN_ASYM_FIELD_H
#define PPANN_ASYM_FIELD_H

#include <gmp.h>

extern "C" {
#include "relic_asym/relic.h"
}

struct ZP_ASYM {
    bn_t point{};
    bn_t modular{};
};

ZP_ASYM rand_zp(bn_t modular);

ZP_ASYM zp_zero(bn_t modular);

ZP_ASYM zp_one(bn_t modular);

ZP_ASYM zp_copy(ZP_ASYM x);

ZP_ASYM zp_from_int(int x, bn_t modular);

ZP_ASYM zp_add(ZP_ASYM x, ZP_ASYM y);

ZP_ASYM zp_neg(ZP_ASYM x);

ZP_ASYM zp_mul(ZP_ASYM x, ZP_ASYM y);

ZP_ASYM zp_inv(ZP_ASYM x);

int zp_cmp(ZP_ASYM x, ZP_ASYM y);

int zp_cmp_int(ZP_ASYM x, int y);

#endif //PPANN_ASYM_FIELD_H
