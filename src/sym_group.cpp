#include "sym_group.hpp"

void sym::g_gen(symG x) {
    g1_get_gen(x);
}

void sym::g_mul(ep_st *r, ep_st *x, symZp y) {
    g1_mul(r, x, y.point);
}

void sym::gt_raise(fp_t *r, fp_t *x, symZp y) {
    gt_exp(r, x, y.point);
}

void sym::bp_map(ep_st *a, ep_st *b, fp_t *r) {
    pc_map(r, a, b);
}