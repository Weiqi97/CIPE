#include "vector.h"
#include "matrix.h"


const int B_SIZE = 6;

struct key {
    zp_mat A;
    zp_mat B;
    zp_mat Bi;
    g base;
    gt t_base;
};

struct ct {
    g_vec ctx;
    g_vec ctk;
    g_vec ctc;
};

void initialize_relic() {
    core_init();
    pc_param_set_any();

}

struct key setup(int size) {
    struct key key;
    key.A = matrix_zp_rand(2, size);
    key.B = matrix_zp_rand(B_SIZE, B_SIZE);
    key.Bi = matrix_inverse(key.B, B_SIZE);
    key.Bi = matrix_transpose(key.Bi, B_SIZE, B_SIZE);
    generator(key.base);
    map(key.base, key.base, key.t_base);
    return key;
}

struct ct enc(struct key key, int *message, int size) {
    // Declare the returned ciphertext and convert message to zp.
    struct ct ct;
    zp_vec x = vector_zp_from_int(message, size);

    // Helper values.
    int one[] = {1}, zero[] = {0};
    zp_vec one_vec = vector_zp_from_int(one, 1);
    zp_vec zero_vec = vector_zp_from_int(zero, 1);

    // We generate s and compute sA + x.
    zp_vec s = vector_zp_rand(2);
    zp_vec sA = matrix_multiply(s, key.A, 1, 2, size);
    zp_vec sAx = vector_add(sA, x, size);
    ct.ctx = vector_raise(key.base, sAx, size);

    // We compute the function hiding inner product encryption key.
    zp_mat AT = matrix_transpose(key.A, 2, size);
    zp_vec xAT = matrix_multiply(x, AT, 1, size, 2);
    zp_vec xATs = vector_merge(xAT, s, 2, 2);
    zp_vec xATs0 = vector_merge(xATs, zero_vec, 4, 1);
    zp_vec xATs01 = vector_merge(xATs0, zero_vec, 5, 1);
    zp_vec xATs01_B = matrix_multiply(xATs01, key.B, 1, B_SIZE, B_SIZE);
    ct.ctc = vector_raise(key.base, xATs01_B, B_SIZE);

    // We compute the function hiding inner product encryption ciphertext.
    zp_vec sAAT = matrix_multiply(sA, AT, 1, size, 2);
    zp_vec xATsAAT = vector_add(xAT, sAAT, 2);
    zp_vec sxATsAAT = vector_merge(s, xATsAAT, 2, 2);
    zp_vec sxATsAAT1 = vector_merge(sxATsAAT, zero_vec, 4, 1);
    zp_vec sxATsAAT10 = vector_merge(sxATsAAT1, zero_vec, 5, 1);
    zp_vec sxATsAAT10_Bi = matrix_multiply(sxATsAAT10, key.Bi, 1, B_SIZE, B_SIZE);
    ct.ctk = vector_raise(key.base, sxATsAAT10_Bi, B_SIZE);

    return ct;
}

void eval(struct key key, struct ct x, struct ct y, int size) {
    //
    gt z, xy, ct;
    inner_product(xy, x.ctx, y.ctx, size);
    inner_product(ct, x.ctc, y.ctk, B_SIZE);

    // Decrypt.
    gt_inv(ct, ct);
    gt_mul(z, xy, ct);

    // Check correctness.
    gt desired_output;
    gt_exp_dig(desired_output, key.t_base, 10);

    if (gt_cmp(desired_output, z) == RLC_EQ) printf("Magic happened.");
    else printf("Fuck my life.");
}

int main() {
    initialize_relic();

//    int x[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    struct key key = setup(10);
//    struct ct ct_x = enc(key, x, 10);
//    eval(key, ct_x, ct_x, 10);

    bn_t a, b, c, n;
    pc_get_ord(n);

    bn_rand_mod(a, n);
    bn_rand_mod(b, n);
    bn_mul(c, a, a);
    bn_mod(c, c, n);

    g g1, g2;
    g1_mul(g1, key.base, a);
    g1_mul(g2, key.base, b);

    gt gt1, gt2;pc_map(gt1, g1, g2);
    gt_exp(gt2, key.t_base, c);

    printf("Works if 1: %i", gt_cmp(gt1, gt2) == RLC_EQ);
    return 0;
}
