#pragma once

#include "sym_field.hpp"
#include "sym_group.hpp"

typedef symZp *symZpVec;
typedef symG *symGVec;

namespace sym {
    symZpVec vector_zp_from_int(const int *int_vec, int size, symPoint modular);

    symZpVec vector_zp_rand(int size, symPoint modular);

    symZpVec vector_merge(symZpVec a, symZpVec b, int size_a, int size_b);

    symZpVec vector_add(symZpVec a, symZpVec b, int size);

    symGVec vector_raise(symG base, symZpVec x, int size);

    void inner_product(symGt r, symGVec a, symGVec b, int size);
}
