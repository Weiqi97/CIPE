#include "sym_ipre.hpp"

Key setup(int size) {
    Key key{};
    pc_get_ord(key.modular);
    sym::g_gen(key.base);
    sym::bp_map(key.t_base, key.base, key.base);
    key.A = sym::matrix_zp_rand(2, size, key.modular);
    key.B = sym::matrix_zp_rand(B_SIZE, B_SIZE, key.modular);
    key.Bi = sym::matrix_transpose(sym::matrix_inverse(key.B, B_SIZE, key.modular), B_SIZE, B_SIZE);
    return key;
}

Ct enc(Key key, const int *message, int size) {
    // Declare the returned ciphertext and convert message to asymZp.
    Ct ct{};
    symZpVec x = sym::vector_zp_from_int(message, size, key.modular);

    // Helper values.
    int one[] = {1}, zero[] = {0};
    symZpVec one_vec = sym::vector_zp_from_int(one, 1, key.modular);
    symZpVec zero_vec = sym::vector_zp_from_int(zero, 1, key.modular);

    // We generate s and compute sA + x.
    symZpVec s = sym::vector_zp_rand(2, key.modular);
    symZpVec sA = sym::matrix_multiply(s, key.A, 1, 2, size, key.modular);
    symZpVec sAx = sym::vector_add(sA, x, size);
    ct.ctx = sym::vector_raise(key.base, sAx, size);

    // We compute the function hiding inner product encryption Key.
    symZpMat AT = sym::matrix_transpose(key.A, 2, size);
    symZpVec xAT = sym::matrix_multiply(x, AT, 1, size, 2, key.modular);
    symZpVec xATs = sym::vector_merge(xAT, s, 2, 2);
    symZpVec xATs0 = sym::vector_merge(xATs, zero_vec, 4, 1);
    symZpVec xATs01 = sym::vector_merge(xATs0, one_vec, 5, 1);
    symZpVec xATs01_B = sym::matrix_multiply(xATs01, key.B, 1, B_SIZE, B_SIZE, key.modular);
    ct.ctc = sym::vector_raise(key.base, xATs01_B, B_SIZE);

    // We compute the function hiding inner product encryption ciphertext.
    symZpVec sAAT = sym::matrix_multiply(sA, AT, 1, size, 2, key.modular);
    symZpVec xATsAAT = sym::vector_add(xAT, sAAT, 2);
    symZpVec sxATsAAT = sym::vector_merge(s, xATsAAT, 2, 2);
    symZpVec sxATsAAT1 = sym::vector_merge(sxATsAAT, one_vec, 4, 1);
    symZpVec sxATsAAT10 = sym::vector_merge(sxATsAAT1, zero_vec, 5, 1);
    symZpVec sxATsAAT10_Bi = sym::matrix_multiply(sxATsAAT10, key.Bi, 1, B_SIZE, B_SIZE, key.modular);
    ct.ctk = sym::vector_raise(key.base, sxATsAAT10_Bi, B_SIZE);

    return ct;
}

int eval(Key key, Ct x, Ct y, int size, int bound) {
    // Decrypt components.
    symGt xy, ct;
    sym::inner_product(xy, x.ctx, y.ctx, size);
    sym::inner_product(ct, x.ctc, y.ctk, B_SIZE);

    // Decrypt final result.
    gt_inv(ct, ct);
    gt_mul(xy, xy, ct);

    // Get a target group element holder.
    symGt output;

    // Iterate through a loop to find correct answer.
    for (int i = 1; i <= bound; i++) {
        gt_exp_dig(output, key.t_base, i);
        if (gt_cmp(output, xy) == RLC_EQ) return i;
    }

    // Otherwise return 0 as the output.
    return 0;
}