#include "vector.h"

zp_vec vector_zp_from_int(int *int_vec, int size) {
    zp_vec x;
    x = (zp_vec) malloc(sizeof(zp) * size);
    for (int i = 0; i < size; i++) zp_from_int(x[i], int_vec[i]);
    return x;
}

zp_vec vector_zp_rand(int size) {
    zp_vec x;
    x = (zp_vec) malloc(sizeof(zp) * size);
    for (int i = 0; i < size; i++) rand_zp(x[i]);
    return x;
}

zp_vec vector_merge(zp_vec a, zp_vec b, int size_a, int size_b) {
    zp_vec r;
    r = (zp_vec) malloc(sizeof(zp) * (size_a + size_b));
    for (int i = 0; i < size_a; i++) zp_copy(r[i], a[i]);
    for (int i = 0; i < size_b; i++) zp_copy(r[i + size_a], b[i]);
    return r;
}

zp_vec vector_add(zp_vec a, zp_vec b, int size) {
    zp_vec r;
    r = (zp_vec) malloc(sizeof(zp) * size);
    for (int i = 0; i < size; i++) zp_add(r[i], a[i], b[i]);
    return r;
}

g_vec vector_raise(g base, zp_vec x, int size) {
    g_vec r;
    r = (g_vec) malloc(sizeof(g) * size);
    for (int i = 0; i < size; i++) multiply(r[i], base, x[i]);
    return r;
}

void inner_product(gt r, g_vec a, g_vec b, int size) {
    pc_map_sim(r, a, b, size);
}






