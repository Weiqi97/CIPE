#include "matrix.h"

zp_mat matrix_zp_from_int(int *int_mat, int row, int col) {
    zp_mat x;
    x = (zp_mat) malloc(sizeof(zp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            zp_from_int(x[i * col + j], int_mat[i * col + j]);
        }
    }
    return x;
}

zp_mat matrix_zp_rand(int row, int col) {
    zp_mat x;
    x = (zp_mat) malloc(sizeof(zp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            rand_zp(x[i * col + j]);
        }
    }
    return x;
}

zp_mat matrix_identity(int size) {
    zp_mat x;
    x = (zp_mat) malloc(sizeof(zp) * size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) zp_from_int(x[i * size + j], 1);
            else zp_zero(x[i * size + j]);
        }
    }
    return x;
}

int matrix_is_identity(zp_mat x, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j && fp_cmp_dig(x[i * size + j], 1) != RLC_EQ) return 0;
            if (i != j && fp_cmp_dig(x[i * size + j], 0) != RLC_EQ) return 0;
        }
    }
    return 1;
}

zp_mat matrix_transpose(zp_mat x, int row, int col) {
    zp_mat xt;
    xt = (zp_mat) malloc(sizeof(zp) * row * col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            zp_copy(xt[j * row + i], x[i * col + j]);
        }
    }
    return xt;
}

zp_mat matrix_merge(zp_mat x, zp_mat y, int row, int col_x, int col_y) {
    zp_mat xy;
    xy = (zp_mat) malloc(sizeof(zp) * row * (col_x + col_y));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col_x; j++) {
            zp_copy(xy[i * (col_x + col_y) + j], x[i * col_x + j]);
        }
        for (int j = 0; j < col_y; j++) {
            zp_copy(xy[i * (col_x + col_y) + col_x + j], y[i * col_y + j]);
        }
    }
    return xy;
}

zp_mat matrix_multiply(zp_mat x, zp_mat y, int row_x, int row_y, int col_y) {
    zp temp;
    zp_mat xy;
    xy = (zp_mat) malloc(sizeof(zp) * row_x * col_y);

    for (int i = 0; i < row_x; i++) {
        for (int j = 0; j < col_y; j++) {
            zp_zero(xy[i * row_y + j]);
            for (int k = 0; k < row_y; k++) {
                zp_multiply(temp, x[i * row_y + k], y[k * col_y + j]);
                zp_add(xy[i * col_y + j], xy[i * col_y + j], temp);
            }
        }
    }
    return xy;
}

zp_mat matrix_inverse(zp_mat x, int size) {
    // Declare the row echelon matrix and generate it.
    zp_mat identity, row_echelon;
    identity = matrix_identity(size);
    row_echelon = matrix_merge(x, identity, size, size, size);

    // Declare temp value.
    zp temp_multiplier, temp_neg;

    // Bottom left half to all zeros.
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j && !zp_is_int(row_echelon[i * 2 * size + j], 1)) {
                zp_inverse(temp_multiplier, row_echelon[i * 2 * size + i]);
                for (int k = i; k < size * 2; k++) {
                    zp_multiply(row_echelon[j * 2 * size + k], row_echelon[j * 2 * size + k], temp_multiplier);
                }
            }

            if (i == j && zp_is_int(row_echelon[i * 2 * size + j], 0)) break;

            if (i != j) {
                zp_copy(temp_multiplier, row_echelon[j * 2 * size + i]);
                for (int k = i; k < size * 2; k++) {
                    zp_multiply(temp_neg, temp_multiplier, row_echelon[i * 2 * size + k]);
                    zp_neg(temp_neg, temp_neg);
                    zp_add(row_echelon[j * 2 * size + k], row_echelon[j * 2 * size + k], temp_neg);
                }
            }
        }
    }

    // Top right half to all zeros.
    for (int i = size - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            zp_copy(temp_multiplier, row_echelon[j * 2 * size + i]);
            for (int k = i; k < size * 2; k++) {
                zp_multiply(temp_neg, temp_multiplier, row_echelon[i * 2 * size + k]);
                zp_neg(temp_neg, temp_neg);
                zp_add(row_echelon[j * 2 * size + k], row_echelon[j * 2 * size + k], temp_neg);
            }
        }
    }


    // Copy over the output.
    zp_mat xi;
    xi = (zp_mat) malloc(sizeof(zp) * size * size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            zp_copy(xi[i * size + j], row_echelon[i * 2 * size + size + j]);
        }
    }
    return xi;
}