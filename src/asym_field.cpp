#include "asym_field.hpp"

asymZp asym::rand_zp(asymPoint modular) {
    asymZp result;
    bn_rand_mod(result.point, modular);
    bn_copy(result.modular, modular);
    return result;
}

asymZp asym::zp_zero(asymPoint modular) {
    asymZp result;
    bn_set_dig(result.point, 0);
    bn_copy(result.modular, modular);
    return result;
}

asymZp asym::zp_one(asymPoint modular) {
    asymZp result;
    bn_set_dig(result.point, 1);
    bn_copy(result.modular, modular);
    return result;
}

asymZp asym::zp_copy(asymZp x) {
    asymZp result;
    bn_copy(result.point, x.point);
    bn_copy(result.modular, x.modular);
    return result;
}

asymZp asym::zp_from_int(int x, asymPoint modular) {
    asymZp result;
    bn_set_dig(result.point, x);
    bn_copy(result.modular, modular);
    return result;
}

asymZp asym::zp_add(asymZp x, asymZp y) {
    asymZp result;
    bn_add(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

asymZp asym::zp_neg(asymZp x) {
    asymZp result;
    bn_neg(result.point, x.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

asymZp asym::zp_mul(asymZp x, asymZp y) {
    asymZp result;
    bn_mul(result.point, x.point, y.point);
    bn_mod(result.point, result.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

asymZp asym::zp_inv(asymZp x) {
    asymZp result;
    bn_mod_inv(result.point, x.point, x.modular);
    bn_copy(result.modular, x.modular);
    return result;
}

int asym::zp_cmp(asymZp x, asymZp y) {
    return bn_cmp(x.point, y.point) == RLC_EQ;
}

int asym::zp_cmp_int(asymZp x, int y) {
    return bn_cmp_dig(x.point, y) == RLC_EQ;
}