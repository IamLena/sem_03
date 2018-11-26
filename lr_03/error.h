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
#define EXIT 10
#define IO_ERR 1
#define MEM_ERR 2
#define FILE_ERR 3
#define CONT_ERR 4

struct sparse_matrix
{
    int n;//количество строк матрицы
    int m;//количество столбцов матрицы
    double *an;//масси элементов
    int *aj;//массив индексов столбцов
    int h;//количество ненулевых элементов
    int *ai;//массив начал строк
    int k;//длина массива ai
};

struct sparse_vector
{
    int k;//количество ненулевых элементов
    int n;//длина столбца
    double *bn;//массив ненулевых элементов
    int *bi;//массив индексов
};

typedef struct sparse_vector s_vector;
typedef struct sparse_matrix s_matrix;

#endif // ERROR_H
