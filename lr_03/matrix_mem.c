#include <stdlib.h>
#include <stdio.h>

#include "error.h"
#include "io.h"

/**
 * @brief free_matrix - освобождает матрицу
 * @param p - указатель на матрицу
 */
void free_matrix(double **p, int n)
{
    free(p[n]);
    free(p);
}

/**
 * @brief allocate_matrix - определяет в памяти матрицу
 * @param n - количество строк
 * @param m - количество столбцов
 * @return указатель на матрицу или null если выделить память не удалось
 */
double **allocate_matrix(int n, int m)
{
    double **ptrs = NULL, *data = NULL;
    ptrs = malloc((n + 1) * sizeof(double*));
    if (ptrs)
    {
        data = (double*)calloc((n) * (m), sizeof(double));
        if (data)
            for (int i = 0; i < n; i++)
                ptrs[i] = data + i * m;
        else
            free(ptrs);
    }
    ptrs[n] = data;
    return ptrs;
}

int memory_size(double **mtr, int n, int m)
{
    return (n * sizeof(double*) + n * m * sizeof(double));
}
