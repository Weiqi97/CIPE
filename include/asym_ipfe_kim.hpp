#pragma once

#include "asym_ipfe.hpp"

namespace asym::ipfe::kim {
    // These would be the same as in the other IPFE scheme.
    using Pp = asym::ipfe::Pp;
    using Ct = asym::ipfe::Ct;
    using Key = asym::ipfe::Key;

    // We define a new struct for the secret key to include determinant value.
    struct Sk {
        asym::Zp det;
        asym::zpMat B;
        asym::zpMat Bi;
    };

    /**
     * Generate public parameters which contains the following.
     *  - size: message length.
     *  - bound: inner product result bound.
     *  - g1_base: a generator in group G1.
     *  - g2_base: a generator in group G2.
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
     * Derive a functional key on the input.
     * @param pp - the public parameters.
     * @param sk - the secret key.
     * @param function - the input function vector.
     * @return the functional key.
     */
    Key keyGen(Pp pp, Sk sk, const int *function);

    /**
     * Encrypt a message vector.
     * @param pp - the public parameters.
     * @param sk - the secret key.
     * @param message - the input message vector.
     * @return the ciphertext.
     */
    Ct enc(Pp pp, Sk sk, const int *message);

    /**
     * Compute inner product between a functional key and a ciphertext.
     * @param pp - the public parameters.
     * @param y - a functional key.
     * @param x - a ciphertext.
     * @return the integer result of the inner product.
     */
    int dec(Pp pp, Key y, Ct x);
}