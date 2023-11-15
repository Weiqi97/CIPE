#include "sym_group.hpp"

int test_generator() {
    symG x;
    sym::g_gen(x);
    return g1_is_valid(x);
}

int test_all(bn_st *N) {
    // Set integers.
    symZp m = sym::zp_from_int(5, N);
    symZp n = sym::zp_from_int(25, N);

    // Declare variables.
    symG a, b;
    symGt x, y, z;

    // Get generator symG and find symG^5.
    sym::g_gen(a);
    sym::g_mul(b, a, m);

    // Get e(symG, symG) and e(symG^5, symG^5).
    sym::bp_map(a, a, x);
    sym::bp_map(b, b, y);

    // Get e(symG, symG)^25.
    sym::gt_raise(z, x, n);

    // Compare e(symG^5, symG^5) with e(symG, symG)^25.
    return gt_cmp(y, z);
}

int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

    // Get order.
    bn_t N;
    pc_get_ord(N);

    // Perform tests.
    if (test_generator() != 1) return 1;
    if (test_all(N) != RLC_EQ) return 1;

    return 0;
}