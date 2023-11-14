#include "asym_group.h"

//int test_all(bn_st *N) {
//    // Set integers.
//    ZP_ASYM a = zp_from_int(5, N);
//    ZP_ASYM b = zp_from_int(6, N);
//    ZP_ASYM c = zp_from_int(30, N);
//
//    // Declare variables.
//    g1_asym j, k;
//    g2_asym m, n;
//    gt_asym x, y, z;
//
//    //
//    g1_gen(j);
//    g2_gen(m);
//
//    asym_bn_t test;
//    asym_bn_set_dig(test, 20);
//
//    g1_mul(k, j, test);
//
//
//    // Compare e(g_sym^5, g_sym^5) with e(g_sym, g_sym)^25.
//    return RLC_EQ;
//}

int main() {
    core_clean();

    // Init core and setup.
    core_init();
    pc_param_set_any();

    g1_asym p;
    g1_new(p);
    g1_get_gen(p);

    // Get order.
//    bn_t N;
//    pc_get_ord(N);

    // Perform tests.
//    if (test_all(N) != RLC_EQ) return 1;

    return 0;
}