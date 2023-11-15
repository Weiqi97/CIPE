#pragma once

#include "sym_field.hpp"

typedef symZp *symZpMat;

namespace sym {
    symZpMat matrix_zp_from_int(const int *int_mat, int row, int col, symPoint modular);

    symZpMat matrix_zp_rand(int row, int col, symPoint modular);

    symZpMat matrix_identity(int size, symPoint modular);

    int matrix_is_identity(symZpMat x, int size);

    symZpMat matrix_transpose(symZpMat x, int row, int col);

    symZpMat matrix_merge(symZpMat x, symZpMat y, int row, int col_x, int col_y);

    symZpMat matrix_multiply(symZpMat x, symZpMat y, int row_x, int row_y, int col_y, symPoint modular);

    symZpMat matrix_inverse(symZpMat x, int size, symPoint modular);
}
