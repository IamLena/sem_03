#include "error.h"
#include "get.h"
#include "io.h"
#include "mult.h"
#include "matrix_mem.h"

int main(void)
{
    int rc;
    double **matrix;
    int n, m;
    double *vector;
    double *result;
    unsigned long t1, t2, time1, time2;

    rc = get_matrix(&matrix, &n, &m);
    if (rc == OK)
    {
        if (n <= 10 && m <= 10)
            print_matrix(matrix, n, m);
        rc = get_vector(&vector, &m);
        if (rc == OK)
        {
            if (m <= 10)
                print_array(vector, m);

            t1 = tick();
            multiply_usual(matrix, vector, n, m, &result);
            t2 = tick();
            time1 = t2 - t1;

            s_matrix a;
            s_vector b;
            s_vector res;
            make_sparse_vector(vector, m, &b);
            make_sparse_matrix(matrix, n, m, &a);
            t1 = tick();
            res = mult_sparse(a, b);
            t2 = tick();
            time2 = t2 - t1;

            printf("RESULT\n");
            print_array(result, m);
            printf("sparse\n");
            print_array(res.bn, res.k);
            print_int_array(res.bi, res.k);

            printf("________________TIME_________________\n");
            printf("|usual multiply time  - %13lu|\n", time1);
            printf("|sparse multiply time - %13lu|\n", time2);
            printf("|____________________________________|\n");
        }
    }
    if (rc == IO_ERR)
        printf("Input error\n");
    if (rc == MEM_ERR)
        printf("Memory error\n");
    if (rc == FILE_ERR)
        printf("File name error\n");
    if (rc == CONT_ERR)
        printf("Content error\n");
    printf("Exiting the program");
    return rc;
}
