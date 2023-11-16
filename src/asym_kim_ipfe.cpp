#include "asym_kim_ipfe.hpp"

asym::ipfe::Sk asym::ipfe::kim::setup(asym_bn_st *secpar, int size) {
    return asym::ipfe::Sk();
}

asym::ipfe::Key asym::ipfe::kim::keyGen(asym::ipfe::Sk key, const int *function, int size) {
    return asym::ipfe::Key();
}

asym::ipfe::Ct asym::ipfe::kim::enc(asym::ipfe::Sk key, const int *message, int size) {
    return asym::ipfe::Ct();
}

int asym::ipfe::kim::dec(asym::ipfe::Sk key, asym::ipfe::Key x, asym::ipfe::Ct y, int size, int bound) {
    return 0;
}
