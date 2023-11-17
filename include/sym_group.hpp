#pragma once

#include "sym_field.hpp"

namespace sym {
    using g = g1_t;
    using gt = gt_t;

    /**
     * Get a generator for the G group.
     * @param x - a holder for g element.
     */
    void g_gen(g x);

    /**
     * Multiply an element in G with a Zp element.
     * @param r - the resulting element in G.
     * @param x - an input element in G.
     * @param y - the Zp element to multiply with.
     */
    void g_mul(g r, g x, Zp y);

    /**
     * Raise an element in Gt with a Zp element.
     * @param r - the resulting element in Gt.
     * @param x - an input element in Gt.
     * @param y - the Zp element to raise to.
     */
    void gt_raise(gt r, gt x, Zp y);

    /**
     * Compute the bilinear pairing of element g1 and g2.
     * @param r - the resulting element in Gt.
     * @param x - an input element in G.
     * @param y - an input element in G.
     */
    void bp_map(gt r, g a, g b);
}