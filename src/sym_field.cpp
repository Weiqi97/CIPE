#include "sym_field.hpp"

symZp sym::zp_rand(symPoint modular) {
    symZp result;
    bn_rand_mod(result.point, modular);
    bn_copy(result.modular, modular);
    return result;
}

symZp sym::zp_zero(symPoint modular) {
    symZp result;
    bn_set_dig(result.point, 0);
    bn_copy(result.modular, modular);
    return result;
}

symZp sym::zp_one(symPoint modular) {
    symZp result;
    bn_set_dig(result.point, 1);
    bn_copy(result.modular, modular);
    return result;
}

symZp sym::zp_copy(symZp x) {
    symZp result;
    bn_copy(result.point, x.point);
    bn_copy(result.modular, x.modular);
    return result;
}

symZp sym::zp_from_int(int x, symPoint modular) {
    symZp result;
    bn_set_dig(result.point, x);
    bn_copy(result.modular, modular);
    return result;
}

symZp sym::zp_add(symZp x, symZp y) {
    symZp result;
    bn_add(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

symZp sym::zp_neg(symZp x) {
    symZp result;
    bn_neg(result.point, x.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

symZp sym::zp_mul(symZp x, symZp y) {
    symZp result;
    bn_mul(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

symZp sym::zp_inv(symZp x) {
    symZp result;
    bn_mod_inv(result.point, x.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

int sym::zp_cmp(symZp x, symZp y) {
    return bn_cmp(x.point, y.point) == RLC_EQ;
}

int sym::zp_cmp_int(symZp x, int y) {
    return bn_cmp_dig(x.point, y) == RLC_EQ;
}