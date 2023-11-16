#pragma once

#include "sym_vector.hpp"
#include "sym_matrix.hpp"

const int B_SIZE = 6;

struct Key {
    symZpMat A;
    symZpMat B;
    symZpMat Bi;
    symG base;
    symGt t_base;
    bn_t modular;
};

struct Ct {
    symGVec ctx;
    symGVec ctk;
    symGVec ctc;
};

Key setup(int size);

Ct enc(Key key, const int *message, int size);

int eval(Key key, Ct x, Ct y, int size, int bound);