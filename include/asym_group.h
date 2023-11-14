#ifndef PPANN_ASYM_GROUP_H
#define PPANN_ASYM_GROUP_H

#include "asym_field.h"

typedef g1_t g1_asym;
typedef g2_t g2_asym;
typedef gt_t gt_asym;

void g1_gen(g1_asym x);

void g2_gen(g2_asym x);

void g1_mul(g1_asym r, g1_asym x, ZP_ASYM y);

void g2_mul(g2_asym r, g2_asym x, ZP_ASYM y);

void gt_raise(gt_asym r, gt_asym x, ZP_ASYM y);

void bp_map(gt_asym r, g1_asym x, g2_asym y);

#endif //PPANN_ASYM_GROUP_H