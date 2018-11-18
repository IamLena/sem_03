#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"
#include "io.h"
#include "mult.h"

void multiply_usual(double **mtr, double *column, int n, int m, double *res)
{
    printf("mult\n");
    assert(n > 0 && m > 0 && mtr != NULL && column != NULL && res != NULL);
    print_matrix(mtr, n, m);
    printf("on\n");
    print_array(column, m);
    for (int i = 0; i < n; i++)
        res[i] = 0;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j ++)
            res[i] += mtr[i][j] + column[j];
        printf("%d - %f\n", i, res[i]);
    }
    print_array(res, n);
}
