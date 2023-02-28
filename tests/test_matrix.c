//#include "matrix.h"
//
//int test_zp_from_int() {
//    zp_mat x;
//    int int_mat[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    x = matrix_zp_from_int(int_mat, 3, 3);
//    return zp_is_int(x[8], 9);
//}
//
//int test_transpose() {
//    int row = 3, col = 3;
//    zp_mat x, xt;
//    x = matrix_zp_rand(row, col);
//    xt = matrix_transpose(x, row, col);
//    return fp_cmp(xt[col - 1], x[2 * row]);
//}
//
//int test_identity() {
//    int size = 100;
//    zp_mat x;
//    x = matrix_identity(size);
//    return matrix_is_identity(x, size);
//}
//
//int test_merge() {
//    int size = 10;
//    zp_mat xy, x, y;
//    x = matrix_zp_rand(size, size);
//    y = matrix_identity(size);
//    xy = matrix_merge(x, y, size, size, size);
//    return fp_cmp(x[2 * size + 1], xy[4 * size + 1]);
//}
//
//int test_multiply_vector() {
//    int mat_x[5] = {1, 2, 3, 4, 5};
//    int mat_y[15] = {10, 20, 30,
//                     10, 20, 30,
//                     10, 20, 30,
//                     10, 20, 30,
//                     10, 20, 30};
//
//    zp_mat x, y, xy;
//    x = matrix_zp_from_int(mat_x, 1, 5);
//    y = matrix_zp_from_int(mat_y, 5, 3);
//    xy = matrix_multiply(x, y, 1, 5, 3);
//
//    return fp_cmp_dig(xy[1], 300);
//}
//
//int test_inverse() {
//    int size = 100;
//    // Allocate space.
//    zp_mat x, xi, r;
//    x = matrix_zp_rand(size, size);
//    xi = matrix_inverse(x, size);
//    r = matrix_multiply(xi, x, size, size, size);
//    return matrix_is_identity(r, size);
//}
//
//int main() {
//    // Init core and setup.
//    core_init();
//    pc_param_set_any();

//// Get order.
//bn_t N;
//pc_get_ord(N);
//
//    // Perform tests.
//    if (test_zp_from_int() != 1) return 1;
//    if (test_transpose() != RLC_EQ) return 1;
//    if (test_identity() != 1) return 1;
//    if (test_merge() != RLC_EQ) return 1;
//    if (test_multiply_vector() != RLC_EQ) return 1;
//    if (test_inverse() != 1) return 1;
//
//    return 0;
//}