#ifndef PPANN_SYM_FIELD_H
#define PPANN_SYM_FIELD_H

#include <gmp.h>

extern "C" {
#include "relic_sym/relic.h"
}

struct ZP_SYM {
    bn_t point{};
    bn_t modular{};
};

ZP_SYM rand_zp(bn_t modular);

ZP_SYM zp_zero(bn_t modular);

ZP_SYM zp_one(bn_t modular);

ZP_SYM zp_copy(ZP_SYM x);

ZP_SYM zp_from_int(int x, bn_t modular);

ZP_SYM zp_add(ZP_SYM x, ZP_SYM y);

ZP_SYM zp_neg(ZP_SYM x);

ZP_SYM zp_mul(ZP_SYM x, ZP_SYM y);

ZP_SYM zp_inv(ZP_SYM x);

int zp_cmp(ZP_SYM x, ZP_SYM y);

int zp_cmp_int(ZP_SYM x, int y);

#endif //PPANN_SYM_FIELD_H