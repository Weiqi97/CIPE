#include "sym_group.hpp"

void sym::g_gen(symG x) {
    g1_get_gen(x);
}

void sym::g_mul(symG r, symG x, symZp y) {
    g1_mul(r, x, y.point);
}

void sym::gt_raise(symGt r, symGt x, symZp y) {
    gt_exp(r, x, y.point);
}

void sym::bp_map(symGt r, symG a, symG b) {
    pc_map(r, a, b);
}