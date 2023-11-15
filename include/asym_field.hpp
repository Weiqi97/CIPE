#pragma once

#include <gmp.h>

extern "C" {
#include "relic_asym/relic.h"
}

// Set specific asym data types.
typedef bn_t asymPoint;
struct asymZp {
    asymPoint point{};
    asymPoint modular{};
};

namespace asym {
    asymZp rand_zp(asymPoint modular);

    asymZp zp_zero(asymPoint modular);

    asymZp zp_one(asymPoint modular);

    asymZp zp_copy(asymZp x);

    asymZp zp_from_int(int x, asymPoint modular);

    asymZp zp_add(asymZp x, asymZp y);

    asymZp zp_neg(asymZp x);

    asymZp zp_mul(asymZp x, asymZp y);

    asymZp zp_inv(asymZp x);

    int zp_cmp(asymZp x, asymZp y);

    int zp_cmp_int(asymZp x, int y);
}
