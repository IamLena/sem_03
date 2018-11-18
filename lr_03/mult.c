#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"
#include "io.h"
#include "mult.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void multiply_usual(double **mtr, double *column, int n, int m, double **res)
{
    printf("n - %d, m - %d\n", n, m);
    printf("mult\n");
    assert(n > 0 && m > 0 && mtr != NULL && column != NULL && res != NULL);
    double *tmp = calloc(n, sizeof(double));
    for (int i = 0; i < n; i++)
        res[i] = 0;
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j ++)
            tmp[i] += mtr[i][j] * column[j];
        printf("%d - %f\n", i, tmp[i]);
    }
    *res = tmp;
    print_array(*res, n);
}
