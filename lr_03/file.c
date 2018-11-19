#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "error.h"
#include "io.h"
#include "matrix_mem.h"

int get_file(FILE **f)
{
    char filename[20];
    if (input_string(filename, 20, "Input the file name: ") == IO_ERR)
    {
        printf("can not open the file\n");
        return FILE_ERR;
    }
    *f = fopen(filename, "r");
    if (*f)
    {
        printf("opened\n");
        return OK;
    }
    printf("Can not open the file\n");
    int rc = FILE_ERR;
    bool yn;
    while (rc != OK)
        rc = input_bool(&yn, "Want to try again? ");
    if (yn == true)
        rc = get_file(f);
    if (yn == false)
        rc = FILE_ERR;
    return rc;
    return OK;
}

/**
 * @brief read_matrix - читает матрицу из файла
 * @param filename - имя файла
 * @param n - количество строк
 * @param m - количество столбцов
 * @return - возвращает указать на матрицу, или null если не получилось ее задать
 * открывает файл, проверяет успешность, при ошибке выходит из функции
 * считывает первые три числа - n, m и количество ненулевых элементов
 * если они не удовлетворяют логическим условиям, возвращает null
 * считывает в цикле определенное количество строк - индексы и значения элементов, заполняет матрицу значениями
 * при ошибке выходит из функции
 * возврашает указатель н матрицу при удачном считывании
 */
double **read_matrix_coord(FILE *f, int *n, int *m, int *rc)
{
    if (!f)
        printf("file\n");
    assert((n != NULL) && (m != NULL));
    *rc = OK;
    double **new_matrix = NULL;

    int elements;
    if (fscanf(f, "%d %d %d", n, m, &elements) == 3)
    {
        if (*n > 0 && *m > 0 && elements > 0 && elements <= (*n) * (*m))
        {
            new_matrix = allocate_matrix(*n, *m);
            if (new_matrix)
            {
                int i, j;
                double el;
                int line = 0;
                int i_prev = 0, j_prev = 0;
                while (line < elements)
                {
                    if (fscanf(f, "%d %d %lf", &i, &j, &el) == 3)
                    {
                        float eps = 0.00000000001;
                        if (i <= *n && j <= *m && i > 0 && j > 0 && fabs(el - 0) > eps)
                        {
                            if (!(i == i_prev && j == j_prev))
                            {
                                //ошибка если повторяющиес не подряд
                                i_prev = i;
                                j_prev = j;
                                i--;
                                j--;
                                new_matrix[i][j] = el;
                                line++;
                            }
                            else
                            {
                                *rc = CONT_ERR;
                                break;
                            }
                        }
                        else
                        {
                            *rc = CONT_ERR;
                            break;
                        }
                    }
                    else
                    {
                        *rc = CONT_ERR;
                        break;
                    }
                }
                if (line != elements)
                    *rc = CONT_ERR;
                if (*rc == CONT_ERR)
                {
                    free_matrix(new_matrix, *n);
                    new_matrix = NULL;
                }
            }
            else
                *rc = MEM_ERR;
        }
        else
            *rc = CONT_ERR;
    }
    else
        *rc = CONT_ERR;

    return new_matrix;
}

// чтение матрицы
int read_matrix_lines(FILE *f, double ***pmtr, int *pn, int *pm)
{
    assert ((f != NULL) && (pmtr != NULL) && (pn != NULL) && (pm != NULL));
    int rc = OK;
    if (fscanf(f, "%d %d", pn, pm) == 2 && *pn > 0 && *pm > 0)
    {
        double **tmp = allocate_matrix(*pn, *pm);
        if (!tmp)
            rc = MEM_ERR;
        else
        {
            for (int i = 0; i < *pn; i++)
            {
                for (int j = 0; j < *pm; j++)
                {
                    if (fscanf(f, "%lf", &tmp[i][j]) != 1)
                    {
                        rc = CONT_ERR;
                        break;
                    }
                }
            }
        }
        char c;
        if (fscanf(f, "%c", &c) == 1 && c != '\n')
            rc = CONT_ERR;
        if (rc == OK)
            *pmtr = tmp;
        else
            free_matrix(tmp, *pn);
    }
    else
        rc = CONT_ERR;
    return rc;
}

double *read_vector_coord(FILE *f, int *n, int *rc)
{
    if (!f)
        printf("file\n");
    assert(f != NULL && n != NULL);
    *rc = OK;
    double *new_vector = NULL;

    int elements;
    if (fscanf(f, "%d %d", n, &elements) == 2)
    {
        printf("size - %d; nonzero - %d\n", *n, elements);
        if (*n > 0 && elements > 0 && elements <= *n)
        {
            new_vector = calloc(*n, sizeof(double));
            if (new_vector)
            {
                int i;
                double el;
                int line = 0;
                while (line < elements)
                {
                    if (fscanf(f, "%d %lf", &i, &el) == 2)
                    {
                        printf("%d: %lf\n", i, el);
                        float eps = 0.00000000001;
                        if (i <= *n && i > 0 && fabs(el - 0) > eps)
                        {
                                //i--;
                                new_vector[i] = el;
                                line++;
                        }
                        else
                        {
                            *rc = CONT_ERR;
                            break;
                        }
                    }
                    else
                    {
                        *rc = CONT_ERR;
                        break;
                    }
                }
                if (line != elements)
                    *rc = CONT_ERR;
                if (*rc == CONT_ERR)
                {
                    free(new_vector);
                    new_vector = NULL;
                }
            }
            else
                *rc = MEM_ERR;
        }
        else
            *rc = CONT_ERR;
    }
    else
        *rc = CONT_ERR;

    return new_vector;
}

// чтение матрицы
int read_vector_lines(FILE *f, double **pvector, int *pn)
{
    assert ((f != NULL) && (pvector != NULL) && (pn != NULL));
    int rc = OK;
    if (fscanf(f, "%d", pn) == 1 && *pn > 0)
    {
        double *tmp = calloc(*pn, sizeof(double));
        if (!tmp)
            rc = MEM_ERR;
        else
        {
            for (int i = 0; i < *pn; i++)
            {
                    if (fscanf(f, "%lf", &tmp[i]) != 1)
                    {
                        rc = CONT_ERR;
                        break;
                    }
            }
        }
        char c;
        if (fscanf(f, "%c", &c) == 1 && c != '\n')
            rc = CONT_ERR;
        if (rc == OK)
            *pvector = tmp;
        else
            free(tmp);
    }
    else
        rc = CONT_ERR;
    return rc;
}
