#pragma once

#include <gmp.h>

extern "C" {
#include "relic_sym/relic.h"
}

// Set specific sym data types.
typedef bn_t symPoint;
struct symZp {
    symPoint point{};
    symPoint modular{};
};

namespace sym {
    symZp zp_rand(symPoint modular);

    symZp zp_zero(symPoint modular);

    symZp zp_one(symPoint modular);

    symZp zp_copy(symZp x);

    symZp zp_from_int(int x, symPoint modular);

    symZp zp_add(symZp x, symZp y);

    symZp zp_neg(symZp x);

    symZp zp_mul(symZp x, symZp y);

    symZp zp_inv(symZp x);

    int zp_cmp(symZp x, symZp y);

    int zp_cmp_int(symZp x, int y);
}
