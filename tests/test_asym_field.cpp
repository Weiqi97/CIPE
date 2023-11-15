#include "asym_field.hpp"

int test_zp_zero(asymPoint N) {
    asymZp x = asym::zp_zero(N);
    return asym::zp_cmp_int(x, 0);
}

int test_zp_one(asymPoint N) {
    asymZp x = asym::zp_one(N);
    return asym::zp_cmp_int(x, 1);
}

int test_zp_copy(asymPoint N) {
    asymZp x = asym::zp_from_int(10, N);
    asymZp y = asym::zp_copy(x);
    return asym::zp_cmp(x, y);
}

int test_zp_from_int(asymPoint N) {
    asymZp x = asym::zp_from_int(3, N);
    return asym::zp_cmp_int(x, 3);
}

int test_zp_add(asymPoint N) {
    asymZp x = asym::zp_from_int(10, N);
    asymZp y = asym::zp_from_int(20, N);
    asymZp z = asym::zp_add(x, y);
    return asym::zp_cmp_int(z, 30);
}

int test_zp_neg(asymPoint N) {
    asymZp x = asym::rand_zp(N);
    asymZp y = asym::zp_neg(x);
    asymZp z = asym::zp_add(x, y);
    return asym::zp_cmp_int(z, 0);
}

int test_zp_mul(asymPoint N) {
    asymZp x = asym::zp_from_int(10, N);
    asymZp y = asym::zp_from_int(20, N);
    asymZp z = asym::zp_mul(x, y);
    return asym::zp_cmp_int(z, 200);
}

int test_zp_inv(asymPoint N) {
    asymZp x = asym::rand_zp(N);
    asymZp y = asym::zp_inv(x);
    asymZp z = asym::zp_mul(x, y);
    return asym::zp_cmp_int(z, 1);
}

int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

    // Get order.
    bn_t N;
    pc_get_ord(N);

    // Perform tests.
    if (test_zp_zero(N) != 1) return 1;
    if (test_zp_one(N) != 1) return 1;
    if (test_zp_copy(N) != 1) return 1;
    if (test_zp_from_int(N) != 1) return 1;
    if (test_zp_add(N) != 1) return 1;
    if (test_zp_neg(N) != 1) return 1;
    if (test_zp_mul(N) != 1) return 1;
    if (test_zp_inv(N) != 1) return 1;

    return 0;
}