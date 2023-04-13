#include "helper.h"

float *fvecs_read(const char *file_path, size_t *d_out, size_t *n_out) {
    // Open up the file.
    FILE *file = fopen(file_path, "r");

    // Get the dimension.
    int d;
    fread(&d, 1, sizeof(int), file);

    // Get the number of vectors.
    fseek(file, 0, SEEK_SET);
    struct stat st{};
    fstat(fileno(file), &st);

    // Compute number of vectors.
    size_t sz = st.st_size;
    size_t n = sz / ((d + 1) * 4);

    // Update parameters.
    *d_out = d;
    *n_out = n;

    // Save the data.
    auto *x = new float[n * (d + 1)];
    fread(x, sizeof(float), n * (d + 1), file);

    // shift array to remove row headers
    for (size_t i = 0; i < n; i++) memmove(x + i * d, x + 1 + i * (d + 1), d * sizeof(*x));

    // Close file.
    fclose(file);

    return x;
}

int *ivecs_read(const char *file_path, size_t *d_out, size_t *n_out) {
    // Cast the float results to integers.
    return (int *) fvecs_read(file_path, d_out, n_out);
}