#ifndef MATRIX_MEM_H
#define MATRIX_MEM_H

void free_matrix(double **p, int n);
double **allocate_matrix(int n, int m);
int memory_size(double **mtr, int n, int m);
int make_sparse_matrix(double **mtr, int n, int m);
int make_sparse_vector(double *vector, int n);

#endif // MATRIX_MEM_H
