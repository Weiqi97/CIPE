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
     * Multiply an element in G1 with a Zp element.
     * @param r - the resulting element in G1.
     * @param x - the input element in G1.
     * @param y - the Zp element to multiply with.
     */
    void g1_mul(g1 r, g1 x, Zp y);

    /**
     * Multiply an element in G2 with a Zp element.
     * @param r - the resulting element in G2.
     * @param x - the input element in G2.
     * @param y - the Zp element to multiply with.
     */
    void g2_mul(g2 r, g2 x, Zp y);

    /**
     * Raise an element in Gt with a Zp element.
     * @param r - the resulting element in Gt.
     * @param x - the input element in Gt.
     * @param y - the Zp element to raise to.
     */
    void gt_raise(gt r, gt x, Zp y);

    /**
     * Compute the bilinear pairing of element g1 and g2.
     * @param r - the resulting element in Gt.
     * @param x - the input element in G1.
     * @param y - the input element in G2.
     */
    void bp_map(gt r, g1 x, g2 y);
}