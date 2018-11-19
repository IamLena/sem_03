#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define OK 0
#define IO_ERR 1
#define MEM_ERR 2
#define FILE_ERR 3
#define CONT_ERR 4

struct sparse_matrix
{
    int n;
    int m;
    double *an;
    int *aj;
    int h;
    int *ai;
    int k;
};

struct sparse_vector
{
    int k;
    int n;
    double *bn;
    int *bi;
};

typedef struct sparse_vector s_vector;
typedef struct sparse_matrix s_matrix;

#endif // ERROR_H
