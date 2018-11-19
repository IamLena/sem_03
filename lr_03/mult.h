#ifndef MULT_H
#define MULT_H

#include "error.h"

unsigned long tick(void);
void multiply_usual(double **mtr, double *column, int n, int m, double **res);
double mult_spare_arrays(s_vector a, s_vector b);
s_vector mult_sparse(s_matrix mtr, s_vector vtr);

#endif // MULT_H
