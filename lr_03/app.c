#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "io.h"
#include "mult.h"
#include "file.h"
#include "matrix_mem.h"

int main(void)
{
    int rc = OK;

/* должно быть не тут
    //size
    int n, m;
    if ((input_int(&n, 5, "Input the quantity of rows:(0, 9999) ") != OK)
            || (input_int(&m, 5, "Input the quantity of columns:(0, 9999) ") != OK))
    {
        printf("Exiting the program");
        return IO_ERR;
    }
    printf("%d %d\n", n, m);*/

    char mode;
    mode_matrix:
    if (input_string(&mode, 2, "--------------------------\nInput or create the matrix\n1-file\n2-manual\n"
                     "3-auto(%)\nInput the mode of creation: ") != OK)
    {
        printf("Exiting the program");
        return IO_ERR;
    }
    if (mode - '0' == 1)
    {
        printf("working with file\n");
        FILE *f_matrix = NULL;
        if (get_file(&f_matrix) == FILE_ERR)
        {
            printf("Exiting the program");
            return FILE_ERR;
        }
        int code = coord_usual();
        int n, m, ok;
        double **matrix;
        if (code == 1)
        {
            printf("coordinats\n");
            matrix = read_matrix_coord(f_matrix, &n, &m, &ok);
            printf("ok - %d\n", ok);
            print_matrix(matrix, n, m);
        }
        else if (code == 2)
        {
            printf("usual matrix\n");
            ok = read_matrix_lines(f_matrix, &matrix, &n, &m);
            printf("ok - %d\n", ok);
            print_matrix(matrix, n, m);
        }
        else
        {
            printf("Exiting the program");
            fclose(f_matrix);
            return IO_ERR;
        }
        fclose(f_matrix);

    }
    else if (mode - '0' == 2)
    {
        printf("manual input\n");
    }
    else if (mode - '0' == 3)
    {
        printf("auto percentage");
    }
    else
    {
        printf("Invalid input\n");
        int again = IO_ERR;
        bool yn;
        while (again != OK)
            again = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            goto mode_matrix;
        if (yn == false)
        {
            printf("Exiting the program");
            return IO_ERR;
        }
    }
    mode_vector:
    if (input_string(&mode, 2, "--------------------------\nInput or create the vector\n1-file\n2-manual\n"
                 "3-auto(%)\nInput the mode of creation: ") != OK)
    {
        printf("Exiting the program");
        return IO_ERR;
    }
    if (mode - '0' == 1)
    {
        printf("working with file\n");
        FILE *f_vector = NULL;
        if (get_file(&f_vector) == FILE_ERR)
        {
            printf("Exiting the program");
            return FILE_ERR;
        }
        printf("ready\n");
        fclose(f_vector);
    }
    else if (mode - '0' == 2)
    {
        printf("manual input\n");
    }
    else if (mode - '0' == 3)
    {
        printf("auto percentage");
    }
    else
    {
        printf("Invalid input\n");
        int again = IO_ERR;
        bool yn;
        while (again != OK)
            again = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            goto mode_vector;
        if (yn == false)
        {
            printf("Exiting the program");
            return IO_ERR;
        }
    }


    return rc;
}
