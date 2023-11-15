#include "asym_group.hpp"

void asym::g1_gen(asymG1 x) {
    g1_get_gen(x);
}

void asym::g2_gen(asymG2 x) {
    g2_get_gen(x);
}

void asym::g1_mul(asymG1 r, asymG1 x, asymZp y) {
    g1_mul(r, x, y.point);
}

void asym::g2_mul(asymG2 r, asymG2 x, asymZp y) {
    g2_mul(r, x, y.point);
}

void asym::gt_raise(asymGt r, asymGt x, asymZp y) {
    gt_exp(r, x, y.point);
}

void asym::bp_map(asymGt r, asymG1 x, asymG2 y) {
    pc_map(r, x, y);
}

