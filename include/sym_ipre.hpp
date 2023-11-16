#pragma once

#include "sym_vector.hpp"
#include "sym_matrix.hpp"

namespace sym::ipre {
    const int B_SIZE = 6;

    struct Key {
        sym::zpMat A;
        sym::zpMat B;
        sym::zpMat Bi;
        sym::g base;
        sym::gt t_base;
        sym::point mod;
    };

    struct Ct {
        sym::gVec ctx;
        sym::gVec ctk;
        sym::gVec ctc;
    };

    Key setup(point secpar, int size);

    Ct enc(Key key, const int *message, int size);

    int eval(Key key, Ct x, Ct y, int size, int bound);
}