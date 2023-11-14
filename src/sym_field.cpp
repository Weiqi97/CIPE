#include "sym_field.h"

ZP_SYM rand_zp(bn_st *modular) {
    ZP_SYM result;
    bn_rand_mod(result.point, modular);
    bn_copy(result.modular, modular);
    return result;
}

ZP_SYM zp_zero(bn_st *modular) {
    ZP_SYM result;
    bn_set_dig(result.point, 0);
    bn_copy(result.modular, modular);
    return result;
}

ZP_SYM zp_one(bn_st *modular) {
    ZP_SYM result;
    bn_set_dig(result.point, 1);
    bn_copy(result.modular, modular);
    return result;
}

ZP_SYM zp_copy(ZP_SYM x) {
    ZP_SYM result;
    bn_copy(result.point, x.point);
    bn_copy(result.modular, x.modular);
    return result;
}

ZP_SYM zp_from_int(int x, bn_st *modular) {
    ZP_SYM result;
    bn_set_dig(result.point, x);
    bn_copy(result.modular, modular);
    return result;
}

ZP_SYM zp_add(ZP_SYM x, ZP_SYM y) {
    ZP_SYM result;
    bn_add(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

ZP_SYM zp_neg(ZP_SYM x) {
    ZP_SYM result;
    bn_neg(result.point, x.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

ZP_SYM zp_mul(ZP_SYM x, ZP_SYM y) {
    ZP_SYM result;
    bn_mul(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

ZP_SYM zp_inv(ZP_SYM x) {
    ZP_SYM result;
    bn_mod_inv(result.point, x.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

int zp_cmp(ZP_SYM x, ZP_SYM y) {
    return bn_cmp(x.point, y.point) == RLC_EQ;
}

int zp_cmp_int(ZP_SYM x, int y) {
    return bn_cmp_dig(x.point, y) == RLC_EQ;
}