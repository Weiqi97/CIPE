#include "sym_vector.hpp"

symZpVec sym::vector_zp_from_int(const int *int_vec, int size, symPoint modular) {
    symZpVec x;
    x = (symZpVec) malloc(sizeof(symZp) * size);
    for (int i = 0; i < size; i++) x[i] = sym::zp_from_int(int_vec[i], modular);
    return x;
}

symZpVec sym::vector_zp_rand(int size, symPoint modular) {
    symZpVec x;
    x = (symZpVec) malloc(sizeof(symZp) * size);
    for (int i = 0; i < size; i++) x[i] = sym::zp_rand(modular);
    return x;
}

symZpVec sym::vector_merge(symZpVec a, symZpVec b, int size_a, int size_b) {
    symZpVec r;
    r = (symZpVec) malloc(sizeof(symZp) * (size_a + size_b));
    for (int i = 0; i < size_a; i++) r[i] = sym::zp_copy(a[i]);
    for (int i = 0; i < size_b; i++) r[i + size_a] = sym::zp_copy(b[i]);
    return r;
}

symZpVec sym::vector_add(symZpVec a, symZpVec b, int size) {
    symZpVec r;
    r = (symZpVec) malloc(sizeof(symZp) * size);
    for (int i = 0; i < size; i++) r[i] = sym::zp_add(a[i], b[i]);
    return r;
}

symGVec sym::vector_raise(symG base, symZpVec x, int size) {
    symGVec r;
    r = (symGVec) malloc(sizeof(symG) * size);
    for (int i = 0; i < size; i++) sym::g_mul(r[i], base, x[i]);
    return r;
}

void sym::inner_product(symGt r, symGVec a, symGVec b, int size) {
    symGt temp;
    gt_set_unity(r);
    for (int i = 0; i < size; i++) {
        pc_map(temp, a[i], b[i]);
        gt_mul(r, r, temp);
    }
}