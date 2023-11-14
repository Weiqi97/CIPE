#include "sym_vector.h"

zp_vec vector_zp_from_int(const int *int_vec, int size, bn_st *modular) {
    zp_vec x;
    x = (zp_vec) malloc(sizeof(ZP_SYM) * size);
    for (int i = 0; i < size; i++) x[i] = zp_from_int(int_vec[i], modular);
    return x;
}

zp_vec vector_zp_rand(int size, bn_st *modular) {
    zp_vec x;
    x = (zp_vec) malloc(sizeof(ZP_SYM) * size);
    for (int i = 0; i < size; i++) x[i] = rand_zp(modular);
    return x;
}

zp_vec vector_merge(zp_vec a, zp_vec b, int size_a, int size_b) {
    zp_vec r;
    r = (zp_vec) malloc(sizeof(ZP_SYM) * (size_a + size_b));
    for (int i = 0; i < size_a; i++) r[i] = zp_copy(a[i]);
    for (int i = 0; i < size_b; i++) r[i + size_a] = zp_copy(b[i]);
    return r;
}

zp_vec vector_add(zp_vec a, zp_vec b, int size) {
    zp_vec r;
    r = (zp_vec) malloc(sizeof(ZP_SYM) * size);
    for (int i = 0; i < size; i++) r[i] = zp_add(a[i], b[i]);
    return r;
}

g_vec vector_raise(g_sym base, zp_vec x, int size) {
    g_vec r;
    r = (g_vec) malloc(sizeof(g_sym) * size);
    for (int i = 0; i < size; i++) g_mul(r[i], base, x[i]);
    return r;
}

void inner_product(gt_sym r, g_vec a, g_vec b, int size) {
    gt_sym temp;
    gt_set_unity(r);
    for (int i = 0; i < size; i++) { pc_map(temp, a[i], b[i]);
        gt_mul(r, r, temp);
    }
}