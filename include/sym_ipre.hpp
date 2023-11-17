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

    Pp ppgen(int size, int bound);

    Sk setup(Pp pp);

    Ct enc(Pp pp, Sk sk, const int *message);

    int eval(Pp pp, Ct x, Ct y);
}