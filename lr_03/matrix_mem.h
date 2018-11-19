#ifndef MATRIX_MEM_H
#define MATRIX_MEM_H
#include "error.h"

void free_matrix(double **p, int n);
double **allocate_matrix(int n, int m);
int memory_size(double **mtr, int n, int m);
int make_sparse_matrix(double **mtr, int n, int m, s_matrix *matrix);
int make_sparse_vector(double *vector, int n, s_vector *b);

#endif // MATRIX_MEM_H
