#include "sym_vector.hpp"

int test_zp_from_int(bn_st *N) {
    int int_vec[4] = {1, 2, 3, 4};
    symZpVec x = sym::vector_zp_from_int(int_vec, 4, N);
    return sym::zp_cmp_int(x[3], 4);
}

int test_merge_vector(bn_st *N) {
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {11, 22, 33};
    symZpVec x = sym::vector_zp_from_int(int_vec_x, 3, N);
    symZpVec y = sym::vector_zp_from_int(int_vec_y, 3, N);
    symZpVec z = sym::vector_merge(x, y, 3, 3);
    return sym::zp_cmp_int(z[5], 33);
}

int test_add_vector(bn_st *N) {
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {11, 22, 33};
    symZpVec x = sym::vector_zp_from_int(int_vec_x, 3, N);
    symZpVec y = sym::vector_zp_from_int(int_vec_y, 3, N);
    symZpVec z = sym::vector_add(x, y, 3);
    return sym::zp_cmp_int(z[2], 36);
}

int test_inner_product(bn_st *N) {
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {4, 5, 6};
    symZpVec x = sym::vector_zp_from_int(int_vec_x, 3, N);
    symZpVec y = sym::vector_zp_from_int(int_vec_y, 3, N);

    symG base;
    symGVec gx, gy;
    sym::g_gen(base);
    gx = sym::vector_raise(base, x, 3);
    gy = sym::vector_raise(base, y, 3);

    symGt b, r;
    sym::inner_product(r, gx, gy, 3);
    sym::bp_map(base, base, b);
    gt_exp_dig(b, b, 32);

    return gt_cmp(b, r);
}

int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

    // Get order.
    bn_t N;
    pc_get_ord(N);

    // Perform tests.
    if (test_zp_from_int(N) != 1) return 1;
    if (test_merge_vector(N) != 1) return 1;
    if (test_add_vector(N) != 1) return 1;
    if (test_inner_product(N) != RLC_EQ) return 1;

    return 0;
}