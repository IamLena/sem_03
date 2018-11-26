#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"
#include "io.h"
#include "mult.h"
#include "matrix_mem.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void multiply_usual(double **mtr, double *column, int n, int m, double **res)
{
    assert(n > 0 && m > 0 && mtr != NULL && column != NULL && res != NULL);
    double *tmp = calloc(n, sizeof(double));
    if (!tmp)
    {
        *res = NULL;
        return;
    }
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < m; j ++)
            tmp[i] += mtr[i][j] * column[j];
    }
    *res = tmp;
}

int count_intersection(int *arr1, int *arr2, int m, int n)
{
    int count = 0;
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        if (arr1[i] < arr2[j])
            i++;
        else if (arr2[j] < arr1[i])
            j++;
        else /* if arr1[i] == arr2[j] */
        {
            i++;
            count++;
        }
    }
    return count;
}

void intersection(int *arr1, int *arr2, int m, int n, int *res, int *res_len)
{
   int  count = 0, i = 0, j = 0;
    while (i < m && j < n)
    {
        if (arr1[i] < arr2[j])
            i++;
        else if (arr2[j] < arr1[i])
            j++;
        else /* if arr1[i] == arr2[j] */
        {
            res[count] = arr2[j++];
            //printf(" %d ", arr2[j++]);
            i++;
            count++;
        }
    }
    *res_len = count;
}

size_t find_index( int *a, size_t size, int value )
{
    size_t index = 0;
    while ( index < size && a[index] != value ) ++index;
    return ( index == size ? -1 : index );
}

double mult_spare_arrays(s_vector a, s_vector b)
{
    double res = 0;
    assert(a.n == b.n);
//    int len = a.n;

//    int p[len];
//    for (int i = 0; i < len; i++)
//        p[i] = 0;
//    int k = 0;
//    for (int i = 0; i < a.k; i++)
//    {
//        printf("i = %d, %d\n", i, a.bi[i]);
//        while (a.bi[i] != k)
//        {
//            printf("k = %d\n", k);
//            k++;
//        }
//        p[k] = i + 1;
//        k++;
//    }
//    printf("PI: ");
//    print_int_array(p, len);
//    for (int i = 0; i < b.k; i++)
//    {
//        if (p[b.bi[i]] != 0)
//        {
//            res += a.bn[i] * b.bn[i];
//            printf("mult\n");
//            //mult
//        }
//    }
//    printf("res - %f\n", res);


    int res_len = count_intersection(a.bi, b.bi, a.k, b.k);
    int result[res_len];
    intersection(a.bi, b.bi, a.k, b.k, result, &res_len);
    for (int k = 0; k < res_len; k++)
    {
        res += a.bn[find_index(a.bi, a.k, result[k])] * b.bn[find_index(b.bi, b.k, result[k])];
    }
    return res;
}

s_vector mult_sparse(s_matrix mtr, s_vector vtr)
{
    double result[mtr.n];
    for (int i = 0; i < mtr.n; i++)
    {
        s_vector row;
        row.n = mtr.m;
        row.k = mtr.ai[i + 1] - mtr.ai[i];
        row.bi = malloc(row.k * sizeof(int));
        row.bn = malloc(row.k * sizeof(int));
        int k = 0;
        for (int j = mtr.ai[i]; j < mtr.ai[i + 1]; j++)
        {
            row.bi[k] = mtr.aj[j];
            row.bn[k] = mtr.an[j];
            k++;
        }
        result[i] = mult_spare_arrays(row, vtr);
        free(row.bi);
        free(row.bn);
    }
    s_vector sparse_result;
    make_sparse_vector(result, mtr.n, &sparse_result);
    return sparse_result;
}
