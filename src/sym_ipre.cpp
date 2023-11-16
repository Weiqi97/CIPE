#include "sym_ipre.hpp"

sym::ipre::Key sym::ipre::setup(point secpar, int size) {
    Key key{};
    bn_copy(key.mod, secpar);
    g_gen(key.base);
    bp_map(key.t_base, key.base, key.base);
    key.A = matrix_zp_rand(2, size, key.mod);
    key.B = matrix_zp_rand(B_SIZE, B_SIZE, key.mod);
    key.Bi = matrix_transpose(matrix_inverse(key.B, B_SIZE, key.mod), B_SIZE, B_SIZE);
    return key;
}

sym::ipre::Ct sym::ipre::enc(Key key, const int *message, int size) {
    // Declare the returned ciphertext and convert message to Zp.
    Ct ct{};
    zpVec x = vector_zp_from_int(message, size, key.mod);

    // We generate s and compute sA + x.
    zpVec s = vector_zp_rand(2, key.mod);
    zpVec sA = matrix_multiply(s, key.A, 1, 2, size, key.mod);
    zpVec sAx = vector_add(sA, x, size);
    ct.ctx = vector_raise(key.base, sAx, size);

    // We compute the function hiding inner product encryption Key.
    zpMat AT = matrix_transpose(key.A, 2, size);
    zpVec xAT = matrix_multiply(x, AT, 1, size, 2, key.mod);
    zpVec xATs = vector_merge(xAT, s, 2, 2);
    zpVec xATsB = matrix_multiply(xATs, key.B, 1, B_SIZE, B_SIZE, key.mod);
    ct.ctc = vector_raise(key.base, xATsB, B_SIZE);

    // We compute the function hiding inner product encryption ciphertext.
    zpVec sAAT = matrix_multiply(sA, AT, 1, size, 2, key.mod);
    zpVec xATsAAT = vector_add(xAT, sAAT, 2);
    zpVec sxATsAAT = vector_merge(s, xATsAAT, 2, 2);
    zpVec sxATsAATBi = matrix_multiply(sxATsAAT, key.Bi, 1, B_SIZE, B_SIZE, key.mod);
    ct.ctk = vector_raise(key.base, sxATsAATBi, B_SIZE);

    return ct;
}

int sym::ipre::eval(Key key, Ct x, Ct y, int size, int bound) {
    // Decrypt components.
    gt xy, ct;
    inner_product(xy, x.ctx, y.ctx, size);
    inner_product(ct, x.ctc, y.ctk, B_SIZE);

    // Decrypt final result.
    gt_inv(ct, ct);
    gt_mul(xy, xy, ct);

    // Get a target group element holder.
    gt output;

    // Iterate through a loop to find correct answer.
    for (int i = 1; i <= bound; i++) {
        gt_exp_dig(output, key.t_base, i);
        if (gt_cmp(output, xy) == RLC_EQ) return i;
    }

    // Otherwise return 0 as the output.
    return 0;
}