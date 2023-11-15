#include "sym_field.hpp"

int test_zp_zero(symPoint N) {
    symZp x = sym::zp_zero(N);
    return sym::zp_cmp_int(x, 0);
}

int test_zp_one(symPoint N) {
    symZp x = sym::zp_one(N);
    return sym::zp_cmp_int(x, 1);
}

int test_zp_copy(symPoint N) {
    symZp x = sym::zp_from_int(10, N);
    symZp y = sym::zp_copy(x);
    return sym::zp_cmp(x, y);
}

int test_zp_from_int(symPoint N) {
    symZp x = sym::zp_from_int(3, N);
    return sym::zp_cmp_int(x, 3);
}

int test_zp_add(symPoint N) {
    symZp x = sym::zp_from_int(10, N);
    symZp y = sym::zp_from_int(20, N);
    symZp z = sym::zp_add(x, y);
    return sym::zp_cmp_int(z, 30);
}

int test_zp_neg(symPoint N) {
    symZp x = sym::zp_rand(N);
    symZp y = sym::zp_neg(x);
    symZp z = sym::zp_add(x, y);
    return sym::zp_cmp_int(z, 0);
}

int test_zp_mul(symPoint N) {
    symZp x = sym::zp_from_int(10, N);
    symZp y = sym::zp_from_int(20, N);
    symZp z = sym::zp_mul(x, y);
    return sym::zp_cmp_int(z, 200);
}

int test_zp_inv(symPoint N) {
    symZp x = sym::zp_rand(N);
    symZp y = sym::zp_inv(x);
    symZp z = sym::zp_mul(x, y);
    return sym::zp_cmp_int(z, 1);
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