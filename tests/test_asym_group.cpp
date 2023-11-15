#include "asym_group.hpp"

int test_g1_generator() {
    asymG1 x;
    asym::g1_gen(x);
    // Specifically this line goes wrong... I don't know how to further debug it.
    return g1_is_valid(x);
}

int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

    // Print the param used.
    pc_param_print();

    // Get order.
    bn_t N;
    pc_get_ord(N);

    // Perform tests.
    if (test_g1_generator() != 1) return 1;

    return 0;
}