#include "helper.h"

#include "iostream"
using namespace std;

int test_read_fvecs() {
    // Set dimensions holders and get the data.
    size_t d, n;
    float *xd = fvecs_read("sift_query.fvecs", &d, &n);

    // Check for whether the data is correct.
    if (d != 128) return 0;
    if (n != 10000) return 0;
    if (xd[1] != 3) return 0;
    if (xd[1279872] != 23) return 0;

    // If everything passes, return 1.
    return 1;
}

int test_read_ivecs() {
    // Set dimensions holders and get the data.
    size_t d, n;
    int *gt = ivecs_read("sift_groundtruth.ivecs", &d, &n);

    // Check for whether the data is correct.
    if (d != 100) return 0;
    if (n != 10000) return 0;
    if (gt[1] != 934876) return 0;
    if (gt[999900] != 874343) return 0;

    // If everything passes, return 1.
    return 1;
}

int test_encrypt() {
    // Set dimensions holders and get the data.
    size_t d, n;
    float *xd = fvecs_read("sift_query.fvecs", &d, &n);

    cout << static_cast<int>(xd[1]) << endl;
    //
    int d_int, n_int;
    d_int = static_cast<int>(d);
    n_int = static_cast<int>(n);

    //
//    Key key = setup(d_int);
//    Ct *encrypted_data = encrypt_data(gt, key, d_int, 1);
    return 1;
}

int main() {
    // Init core and setup.
    core_init();
    pc_param_set_any();

//    if (test_read_fvecs() != 1) return 1;
//    if (test_read_ivecs() != 1) return 1;
    if (test_encrypt() != 1) return 1;
    return 0;
}