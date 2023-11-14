#include "sym_group.h"

int test_generator() {
    g_sym x;
    gen(x);
    return g1_is_valid(x);
}

int test_all(bn_st *N) {
    // Set integers.
    ZP_SYM m = zp_from_int(5, N);
    ZP_SYM n = zp_from_int(25, N);

    // Declare variables.
    g_sym a, b;
    gt_sym x, y, z;

    // Get generator g_sym and find g_sym^5.
    gen(a);
    g_mul(b, a, m);

    // Get e(g_sym, g_sym) and e(g_sym^5, g_sym^5).
    bp_map(a, a, x);
    bp_map(b, b, y);

    // Get e(g_sym, g_sym)^25.
    gt_raise(z, x, n);

    // Compare e(g_sym^5, g_sym^5) with e(g_sym, g_sym)^25.
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