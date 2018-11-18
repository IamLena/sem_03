#include "error.h"
#include "get.h"
#include "io.h"
#include "mult.h"

int main(void)
{
    int rc;
    double **matrix;
    int n, m;
    double *vector;
    double *result;

    rc = get_matrix(&matrix, &n, &m);
    if (rc == OK)
    {
        print_matrix(matrix, n, m);
        rc = get_vector(&vector, m);
        if (rc == OK)
        {
            print_array(vector, m);
            printf("\n");
            multiply_usual(matrix, vector, n, m, &result);
            printf("mult here");
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
