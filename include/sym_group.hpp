#pragma once

#include "sym_field.hpp"

typedef g1_t symG;
typedef gt_t symGt;

namespace sym {
    void g_gen(symG x);

    void g_mul(symG r, symG x, symZp y);

    void gt_raise(symGt r, symGt x, symZp y);

    void bp_map(symG a, symG b, symGt r);
}

