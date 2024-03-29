#include "sym_init.hpp"

void sym::init_get_order(sym::point N) {
    // Initiate relic.
    core_init();
    pc_param_set_any();

    // Get order.
    pc_get_ord(N);
}