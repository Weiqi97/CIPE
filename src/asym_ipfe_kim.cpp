#include "asym_ipfe_kim.hpp"

asym::ipfe::Pp asym::ipfe::kim::ppgen(int size, int bound) {
    return asym::ipfe::ppgen(size, bound);
}

asym::ipfe::kim::Sk asym::ipfe::kim::setup(asym::ipfe::kim::Pp pp) {
    Sk sk{};
    sk.B = matrix_zp_rand(pp.size, pp.size, pp.mod);
    sk.Bi = matrix_transpose(matrix_inverse_with_det(sk.B, sk.det, pp.size, pp.mod), pp.size, pp.size);
    return sk;
}

asym::ipfe::Key asym::ipfe::kim::keyGen(asym::ipfe::kim::Pp pp, asym::ipfe::kim::Sk sk, const int *function) {
    return asym::ipfe::kim::Key();
}

asym::ipfe::Ct asym::ipfe::kim::enc(asym::ipfe::kim::Pp pp, asym::ipfe::kim::Sk sk, const int *message) {
    return asym::ipfe::kim::Ct();
}

int asym::ipfe::kim::dec(asym::ipfe::kim::Pp pp, asym::ipfe::kim::Key y, asym::ipfe::kim::Ct x) {
    return 0;
}

