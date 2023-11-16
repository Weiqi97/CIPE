#pragma once

#include "asym_ipfe.hpp"

namespace asym::ipfe::kim {
    Sk setup(point secpar, int size);

    Key keyGen(Sk key, const int *function, int size);

    Ct enc(Sk key, const int *message, int size);

    int dec(Sk key, Key x, Ct y, int size, int bound);
}