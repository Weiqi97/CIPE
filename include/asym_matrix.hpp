#pragma once

#include "asym_field.hpp"

namespace asym {
    using zpMat = Zp *;

    /**
     * Convert a matrix of integers to a matrix of Zp elements.
     * @param int_mat - a matrix of integers.
     * @param row - number of rows of desired matrix.
     * @param col - number of columns of desired matrix.
     * @param mod - size of the field.
     * @return a matrix of Zp elements.
     */
    zpMat matrix_zp_from_int(const int *int_mat, int row, int col, point mod);

    /**
     * Generate a random matrix with Zp elements.
     * @param row - number of rows of desired matrix.
     * @param col - number of columns of desired matrix.
     * @param mod - size of the field.
     * @return a matrix of Zp elements.
     */
    zpMat matrix_zp_rand(int row, int col, point mod);

    /**
     * Generate an identity matrix.
     * @param size - size of the desired matrix.
     * @param mod - size of the field.
     * @return an identity matrix of Zp elements.
     */
    zpMat matrix_identity(int size, point mod);

    /**
     * Check if a matrix is an identity matrix.
     * @param x - a matrix of Zp elements.
     * @param size - side length of the input matrix.
     * @return 1 if the input matrix is an identity matrix and 0 otherwise.
     */
    int matrix_is_identity(zpMat x, int size);

    /**
     * Find the transpose of the input matrix.
     * @param x - a matrix of Zp elements.
     * @param row - number of rows of input matrix x.
     * @param col - number of columns of input matrix x.
     * @return the transposed matrix of x.
     */
    zpMat matrix_transpose(zpMat x, int row, int col);

    /**
     * Join two matrices with the same number of rows.
     * @param x - a matrix of Zp elements.
     * @param y - a matrix of Zp elements.
     * @param row - number of rows of both matrix x and matrix y.
     * @param col_x - number of columns of input matrix x.
     * @param col_y - number of columns of input matrix y.
     * @return the joined matrix of x and y.
     */
    zpMat matrix_join(zpMat x, zpMat y, int row, int col_x, int col_y);

    /**
     * Multiply two matrices.
     * @param x - a matrix of Zp elements.
     * @param y - a matrix of Zp elements.
     * @param row_x - number of rows of input matrix x.
     * @param row_y - number of rows of input matrix y, which is assumed to be the same as number of columns of x.
     * @param col_y - number of columns of input matrix y.
     * @param mod - size of the field.
     * @return the product of xy.
     */
    zpMat matrix_multiply(zpMat x, zpMat y, int row_x, int row_y, int col_y, point mod);

    /**
     * Compute inverse of a square matrix.
     * @param x - a matrix of Zp elements.
     * @param size - side length of the input matrix.
     * @param mod - size of the field.
     * @return the inverse of input matrix x.
     */
    zpMat matrix_inverse(zpMat x, int size, point mod);

    /**
     *
     * @param x
     * @param det
     * @param size
     * @param mod
     * @return
     */
    zpMat matrix_inverse_with_det(zpMat x, Zp &det, int size, point mod);
}