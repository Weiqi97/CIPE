#include "vector.h"

int test_zp_from_int() {
    zp_vec x;
    int int_vec[4] = {1, 2, 3, 4};
    x = vector_zp_from_int(int_vec, 4);
    return zp_is_int(x[3], 4);
}

int test_merge_vector() {
    zp_vec x, y, z;
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {11, 22, 33};
    x = vector_zp_from_int(int_vec_x, 3);
    y = vector_zp_from_int(int_vec_y, 3);
    z = vector_merge(x, y, 3, 3);
    return zp_is_int(z[5], 33);
}

int test_add_vector() {
    zp_vec x, y, z;
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {11, 22, 33};
    x = vector_zp_from_int(int_vec_x, 3);
    y = vector_zp_from_int(int_vec_y, 3);
    z = vector_add(x, y, 3);
    return zp_is_int(z[2], 36);
}

int test_inner_product() {
    zp_vec x, y;
    int int_vec_x[3] = {1, 2, 3};
    int int_vec_y[3] = {4, 5, 6};
    x = vector_zp_from_int(int_vec_x, 3);
    y = vector_zp_from_int(int_vec_y, 3);

    g base;
    g_vec gx, gy;
    generator(base);
    gx = vector_raise(base, x, 3);
    gy = vector_raise(base, y, 3);

    gt b, r;
    inner_product(r, gx, gy, 3);
    map(base, base, b);
    gt_exp_dig(b, b, 32);

    return gt_cmp(b, r);
}


int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

    // Perform tests.
    if (test_zp_from_int() != 1) return 1;
    if (test_merge_vector() != 1) return 1;
    if (test_add_vector() != 1) return 1;
    if (test_inner_product() != RLC_EQ) return 1;

    return 0;
}