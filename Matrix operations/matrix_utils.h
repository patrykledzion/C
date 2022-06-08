//
// Created by patry on 06.09.2021.
//

#ifndef DANTE_MATRIX_UTILS_H
#define DANTE_MATRIX_UTILS_H

struct matrix_t{
    int **ptr;
    int width;
    int height;
};


int matrix_create(struct matrix_t *m, int width, int height);
int matrix_read(struct matrix_t *m);
void matrix_display(const struct matrix_t *m);
void matrix_destroy(struct matrix_t *m);

struct matrix_t* matrix_create_struct(int width, int height);
void matrix_destroy_struct(struct matrix_t **m);
struct matrix_t* matrix_copy(struct matrix_t *m);
struct matrix_t* matrix_load_b(const char *filename, int *err_code);
struct matrix_t* matrix_load_t(const char *filename, int *err_code);
struct matrix_t* matrix_add(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_subtract(const struct matrix_t *m1, const struct matrix_t *m2);
struct matrix_t* matrix_multiply(const struct matrix_t *m1, const struct matrix_t *m2);
int type_of_file(char *filename);

#endif //DANTE_MATRIX_UTILS_H
