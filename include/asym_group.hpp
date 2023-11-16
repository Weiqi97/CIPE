#pragma once

#include "asym_field.hpp"

namespace asym {
    using g1 = g1_t;
    using g2 = g2_t;
    using gt = gt_t;

    /**
     * Get a generator for the G1 group.
     * @param x - a holder for g1 element.
     */
    void g1_gen(g1 x);

    /**
     * Get a generator for the G2 group.
     * @param x - a holder for g2 element.
     */
    void g2_gen(g2 x);

    /**
     *
     * @param r
     * @param x
     * @param y
     */
    void g1_mul(g1 r, g1 x, Zp y);

    /**
     *
     * @param r
     * @param x
     * @param y
     */
    void g2_mul(g2 r, g2 x, Zp y);

    /**
     *
     * @param r
     * @param x
     * @param y
     */
    void gt_raise(gt r, gt x, Zp y);

    /**
     *
     * @param r
     * @param x
     * @param y
     */
    void bp_map(gt r, g1 x, g2 y);
}