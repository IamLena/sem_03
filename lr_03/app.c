#include "error.h"
#include "get.h"
#include "io.h"

int main(void)
{
    int rc;
    double **matrix;
    int n, m;
    double *vector;
    //double *result;

    rc = get_matrix(&matrix, &n, &m);
    if (rc == OK)
    {
        print_matrix(matrix, n, m);
        rc = get_vector(&vector, m);
        if (rc == OK)
        {
            print_array(vector, m);
            //result = mult(matrix, vector, n, m);
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
