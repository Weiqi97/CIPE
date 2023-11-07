#ifndef PPANN_GROUP_H
#define PPANN_GROUP_H

#include "field.h"

typedef g1_t g_sym;
typedef gt_t gt_sym;

void gen(g_sym x);

void g_mul(g_sym r, g_sym x, ZP y);

void gt_raise(gt_sym r, gt_sym x, ZP y);

void bp_map(g_sym a, g_sym b, gt_sym r);

#endif //PPANN_GROUP_H