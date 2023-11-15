#include "sym_matrix.hpp"

symZpMat sym::matrix_zp_from_int(const int *int_mat, int row, int col, symPoint modular) {
    symZpMat x;
    x = (symZpMat) malloc(sizeof(symZp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            x[i * col + j] = sym::zp_from_int(int_mat[i * col + j], modular);
        }
    }
    return x;
}

symZpMat sym::matrix_zp_rand(int row, int col, symPoint modular) {
    symZpMat x;
    x = (symZpMat) malloc(sizeof(symZp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            x[i * col + j] = sym::zp_rand(modular);
        }
    }
    return x;
}

symZpMat sym::matrix_identity(int size, symPoint modular) {
    symZpMat x;
    x = (symZpMat) malloc(sizeof(symZp) * size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) x[i * size + j] = sym::zp_one(modular);
            else x[i * size + j] = sym::zp_zero(modular);
        }
    }
    return x;
}

int sym::matrix_is_identity(symZpMat x, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j && !sym::zp_cmp_int(x[i * size + j], 1)) return 0;
            if (i != j && !sym::zp_cmp_int(x[i * size + j], 0)) return 0;
        }
    }
    return 1;
}

symZpMat sym::matrix_transpose(symZpMat x, int row, int col) {
    symZpMat xt;
    xt = (symZpMat) malloc(sizeof(symZp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            xt[j * row + i] = sym::zp_copy(x[i * col + j]);
        }
    }
    return xt;
}

symZpMat sym::matrix_merge(symZpMat x, symZpMat y, int row, int col_x, int col_y) {
    symZpMat xy;
    xy = (symZpMat) malloc(sizeof(symZp) * row * (col_x + col_y));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col_x; j++) {
            xy[i * (col_x + col_y) + j] = sym::zp_copy(x[i * col_x + j]);
        }
        for (int j = 0; j < col_y; j++) {
            xy[i * (col_x + col_y) + col_x + j] = sym::zp_copy(y[i * col_y + j]);
        }
    }
    return xy;
}

symZpMat sym::matrix_multiply(symZpMat x, symZpMat y, int row_x, int row_y, int col_y, symPoint modular) {
    auto xy = (symZpMat) malloc(sizeof(symZp) * row_x * col_y);

    for (int i = 0; i < row_x; i++) {
        for (int j = 0; j < col_y; j++) {
            xy[i * row_y + j] = sym::zp_zero(modular);
            for (int k = 0; k < row_y; k++) {
                xy[i * col_y + j] = sym::zp_add(xy[i * col_y + j], sym::zp_mul(x[i * row_y + k], y[k * col_y + j]));
            }
        }
    }
    return xy;
}

symZpMat sym::matrix_inverse(symZpMat x, int size, symPoint modular) {
    // Declare the row echelon matrix and generate it.
    symZpMat identity = matrix_identity(size, modular);
    symZpMat row_echelon = matrix_merge(x, identity, size, size, size);

    // Declare temp value.
    symZp temp_multiplier;
    symZp temp_neg;

    // Bottom left half to all zeros.
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j && !sym::zp_cmp_int(row_echelon[i * 2 * size + j], 1)) {
                temp_multiplier = sym::zp_inv(row_echelon[i * 2 * size + i]);
                for (int k = i; k < size * 2; k++) {
                    row_echelon[j * 2 * size + k] = sym::zp_mul(row_echelon[j * 2 * size + k], temp_multiplier);
                }
            }

            if (i == j && sym::zp_cmp_int(row_echelon[i * 2 * size + j], 0)) break;

            if (i != j) {
                temp_multiplier = sym::zp_copy(row_echelon[j * 2 * size + i]);
                for (int k = i; k < size * 2; k++) {
                    temp_neg = sym::zp_mul(temp_multiplier, row_echelon[i * 2 * size + k]);
                    temp_neg = sym::zp_neg(temp_neg);
                    row_echelon[j * 2 * size + k] = sym::zp_add(row_echelon[j * 2 * size + k], temp_neg);
                }
            }
        }
    }

    // Top right half to all zeros.
    for (int i = size - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            temp_multiplier = sym::zp_copy(row_echelon[j * 2 * size + i]);
            for (int k = i; k < size * 2; k++) {
                temp_neg = sym::zp_mul(temp_multiplier, row_echelon[i * 2 * size + k]);
                temp_neg = sym::zp_neg(temp_neg);
                row_echelon[j * 2 * size + k] = sym::zp_add(row_echelon[j * 2 * size + k], temp_neg);
            }
        }
    }

    // Copy over the output.
    symZpMat xi;
    xi = (symZpMat) malloc(sizeof(symZp) * size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            xi[i * size + j] = sym::zp_copy(row_echelon[i * 2 * size + size + j]);
        }
    }
    return xi;
}