#pragma once

#include "asym_field.hpp"

namespace asym {
    using zpMat = Zp *;

    zpMat matrix_zp_from_int(const int *int_mat, int row, int col, point mod);

    zpMat matrix_zp_rand(int row, int col, point mod);

    zpMat matrix_identity(int size, point mod);

    int matrix_is_identity(zpMat x, int size);

    zpMat matrix_transpose(zpMat x, int row, int col);

    zpMat matrix_merge(zpMat x, zpMat y, int row, int col_x, int col_y);

    zpMat matrix_multiply(zpMat x, zpMat y, int row_x, int row_y, int col_y, point mod);

    zpMat matrix_inverse(zpMat x, int size, point mod);

    zpMat matrix_inverse_with_det(zpMat x, Zp &det, int size, point mod);
}