#ifndef PPANN_HELPER_H
#define PPANN_HELPER_H

#include <cstdio>
#include <cstring>
#include <sys/stat.h>

float *fvecs_read(const char *file_path, size_t *d_out, size_t *n_out);

int *ivecs_read(const char *file_path, size_t *d_out, size_t *n_out);

#endif //PPANN_HELPER_H