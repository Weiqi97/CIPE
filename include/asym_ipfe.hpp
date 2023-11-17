#pragma once

#include "asym_vector.hpp"
#include "asym_matrix.hpp"

namespace asym::ipfe {
    // Struct for secret key.
    struct Sk {
        zpMat A;
        zpMat B;
        zpMat Bi;
        g1 g1_base;
        g2 g2_base;
        gt gt_base;
        point mod;
    };

    // Struct for derived functional key.
    struct Key {
        g1Vec ctx;
        g1Vec ctk;
    };

    // Struct for ciphertext.
    struct Ct {
        g2Vec ctx;
        g2Vec ctc;
    };

    /**
     *
     * @param secpar
     * @param size
     * @return
     */
    Sk setup(point secpar, int size);

    /**
     *
     * @param key
     * @param function
     * @param size
     * @return
     */
    Key keyGen(Sk key, const int *function, int size);

    /**
     *
     * @param key
     * @param message
     * @param size
     * @return
     */
    Ct enc(Sk key, const int *message, int size);

    /**
     *
     * @param key
     * @param x
     * @param y
     * @param size
     * @param bound
     * @return
     */
    int dec(Sk key, Key x, Ct y, int size, int bound);
}