#pragma once

#include "asym_field.hpp"

typedef g1_t asymG1;
typedef g2_t asymG2;
typedef gt_t asymGt;

namespace asym {
    void g1_gen(asymG1 x);

    void g2_gen(asymG2 x);

    void g1_mul(asymG1 r, asymG1 x, asymZp y);

    void g2_mul(asymG2 r, asymG2 x, asymZp y);

    void gt_raise(asymGt r, asymGt x, asymZp y);

    void bp_map(asymGt r, asymG1 x, asymG2 y);
}
