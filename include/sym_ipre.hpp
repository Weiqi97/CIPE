#pragma once

#include "sym_vector.hpp"
#include "sym_matrix.hpp"

namespace sym::ipre {
    // Struct for the public parameters.
    struct Pp {
        int size;
        int bound;
        g g_base;
        gt gt_base;
        point mod;
    };

    // Struct for the secret key.
    struct Sk {
        zpMat A;
        zpMat B;
        zpMat Bi;
    };

    // Struct for the ciphertext.
    struct Ct {
        gVec ctx;
        gVec ctk;
        gVec ctc;
    };

    /**
     * Generate public parameters which contains the following.
     *  - size: message length.
     *  - bound: inner product result bound.
     *  - g_base: a generator in group G.
     *  - gt_base: the result of e(g_base, g_base).
     *  - mod: the size of the field.
     * @param size - message length.
     * @param bound - inner product result bound.
     * @return the generated public parameters.
     */
    Pp ppgen(int size, int bound);

    /**
     * Generate the secret key for the scheme.
     * @param pp - the public parameters.
     * @return the generated secret key.
     */
    Sk setup(Pp pp);

    /**
     * Encrypt a message vector.
     * @param pp - the public parameters.
     * @param sk - the secret key.
     * @param message - the input message vector.
     * @return the ciphertext.
     */
    Ct enc(Pp pp, Sk sk, const int *message);

    /**
     * Compute inner product of two messages using their ciphertexts.
     * @param pp - the public parameters.
     * @param x - a ciphertext.
     * @param y - a ciphertext.
     * @return the integer result of the inner product.
     */
    int eval(Pp pp, Ct x, Ct y);
}