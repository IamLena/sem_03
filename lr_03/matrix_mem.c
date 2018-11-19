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

int make_sparse_matrix(double **mtr, int n, int m, s_matrix *matrix)
{
    print_matrix(mtr, n, m);
    printf("\n-------------\n");
    double *data;
    int *data_j, *data_i;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mtr[i][j] != 0)
                count++;
        }
    }
    printf("count - %d\n", count);
    data = malloc(count * sizeof(double));
    if (!data)
        return MEM_ERR;
    data_j = malloc(count * sizeof(int));
    if (!data_j)
        return MEM_ERR;
    data_i = malloc((n + 1) * sizeof(int));
    if (!data_i)
        return MEM_ERR;
    count = 0;
    for (int i = 0; i < n; i++)
    {
        data_i[i] = count;
        for (int j = 0; j < m; j++)
            if (mtr[i][j] != 0)
            {
                data[count] = mtr[i][j];
                data_j[count] = j;
                count++;
            }
    }
    data_i[n] = count;
    printf("AN: ");
    print_array(data, count);
    printf("AJ: ");
    print_int_array(data_j, count);
    printf("AI: ");
    print_int_array(data_i, n + 1);
    matrix->an = data;
    matrix->aj = data_j;
    matrix->ai = data_i;
    matrix->n = n;
    matrix->m = m;
    matrix->k = n + 1;
    matrix->h = count;
    printf("\n");
    return OK;
}

int make_sparse_vector(double *vector, int n, s_vector *b)
{
    printf("\n-------------\n");
    print_array(vector, n);
    double *data;
    int *data_i;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (vector[i] != 0)
                count++;
    }
    printf("count - %d\n", count);
    data = malloc(count * sizeof(double));
    if (!data)
        return MEM_ERR;
    data_i = malloc(count * sizeof(int));
    if (!data_i)
        return MEM_ERR;
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (vector[i] != 0)
        {
            data[count] = vector[i];
            data_i[count] = i;
            count++;
        }
    }
    printf("AN: ");
    print_array(data, count);
    printf("AI: ");
    print_int_array(data_i, count);
    b->bn = data;
    b->bi = data_i;
    b->n = n;
    b->k = count;
    printf("\n");
    return OK;
}
