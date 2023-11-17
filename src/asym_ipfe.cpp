#include "asym_ipfe.hpp"

// A global value for this specific scheme only.
const static int B_SIZE = 4;

asym::ipfe::Pp asym::ipfe::ppgen(int size, int bound) {
    asym::ipfe::Pp pp{};
    pp.size = size;
    pp.bound = bound;
    asym::init_get_order(pp.mod);
    asym::g1_gen(pp.g1_base);
    asym::g2_gen(pp.g2_base);
    asym::bp_map(pp.gt_base, pp.g1_base, pp.g2_base);
    return pp;
}

asym::ipfe::Sk asym::ipfe::setup(asym::ipfe::Pp pp) {
    Sk sk{};
    sk.A = matrix_zp_rand(2, pp.size, pp.mod);
    sk.B = matrix_zp_rand(B_SIZE, B_SIZE, pp.mod);
    sk.Bi = matrix_transpose(matrix_inverse(sk.B, B_SIZE, pp.mod), B_SIZE, B_SIZE);
    return sk;
}

asym::ipfe::Key asym::ipfe::keyGen(asym::ipfe::Pp pp, asym::ipfe::Sk sk, const int *function) {
    // Declare the returned key and convert message to Zp.
    Key key{};
    zpVec y = vector_zp_from_int(function, pp.size, pp.mod);

    // We generate s and compute sA + x.
    zpVec s = vector_zp_rand(2, pp.mod);
    zpVec sA = matrix_multiply(s, sk.A, 1, 2, pp.size, pp.mod);
    zpVec sAx = vector_add(sA, y, pp.size);
    key.ctx = vector_raise_g1(pp.g1_base, sAx, pp.size);

    // We compute the function hiding inner product encryption derived key.
    zpMat AT = matrix_transpose(sk.A, 2, pp.size);
    zpVec xAT = matrix_multiply(y, AT, 1, pp.size, 2, pp.mod);
    zpVec sAAT = matrix_multiply(sA, AT, 1, pp.size, 2, pp.mod);
    zpVec xATsAAT = vector_add(xAT, sAAT, 2);
    zpVec sxATsAAT = vector_join(s, xATsAAT, 2, 2);
    zpVec sxATsAATBi = matrix_multiply(sxATsAAT, sk.Bi, 1, B_SIZE, B_SIZE, pp.mod);
    key.ctk = vector_raise_g1(pp.g1_base, sxATsAATBi, B_SIZE);

    return key;
}

asym::ipfe::Ct asym::ipfe::enc(asym::ipfe::Pp pp, asym::ipfe::Sk sk, const int *message) {
    // Declare the returned ciphertext and convert message to Zp.
    Ct ct{};
    zpVec x = vector_zp_from_int(message, pp.size, pp.mod);

    // We generate s and compute sA + x.
    zpVec s = vector_zp_rand(2, pp.mod);
    zpVec sA = matrix_multiply(s, sk.A, 1, 2, pp.size, pp.mod);
    zpVec sAx = vector_add(sA, x, pp.size);
    ct.ctx = vector_raise_g2(pp.g2_base, sAx, pp.size);

    // We compute the function hiding inner product encryption ciphertext.
    zpMat AT = matrix_transpose(sk.A, 2, pp.size);
    zpVec xAT = matrix_multiply(x, AT, 1, pp.size, 2, pp.mod);
    zpVec xATs = vector_join(xAT, s, 2, 2);
    zpVec xATsB = matrix_multiply(xATs, sk.B, 1, B_SIZE, B_SIZE, pp.mod);
    ct.ctc = vector_raise_g2(pp.g2_base, xATsB, B_SIZE);

    return ct;
}

int asym::ipfe::dec(Pp pp, Key y, Ct x) {
    // Decrypt components.
    gt xy, ct;
    inner_product(xy, y.ctx, x.ctx, pp.size);
    inner_product(ct, y.ctk, x.ctc, B_SIZE);

    // Decrypt final result.
    gt_inv(ct, ct);
    gt_mul(xy, xy, ct);

    // Get a target group element holder.
    gt output;

    // Iterate through a loop to find correct answer.
    for (int i = 1; i <= pp.bound; i++) {
        gt_exp_dig(output, pp.gt_base, i);
        if (gt_cmp(output, xy) == RLC_EQ) return i;
    }

    // Otherwise return 0 as the output.
    return 0;
}

