#include "asym_group.h"

void g1_gen(asym_ep_st *x) {
    g1_get_gen(x);
}

void g2_gen(asym_ep2_st *x) {
    g2_get_gen(x);
}

void g1_mul(asym_ep_st *r, asym_ep_st *x, ZP_ASYM y) {
    g1_mul(r, x, y.point);
}

void g2_mul(asym_ep2_st *r, asym_ep2_st *x, ZP_ASYM y) {
    g2_mul(r, x, y.point);
}

void gt_raise(asym_fp6_t *r, asym_fp6_t *x, ZP_ASYM y) {
    gt_exp(r, x, y.point);
}

void bp_map(asym_fp6_t *r, asym_ep_st *x, asym_ep2_st *y) {
    pc_map(r, x, y);
}

