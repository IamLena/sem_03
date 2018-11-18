#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"
#include "io.h"
#include "mult.h"
#include "file.h"
#include "matrix_mem.h"
#include "get.h"

int main(void)
{
    int rc = OK;
    int n, m;
    double **matrix;
    double *vector, *result;

//    rc = get_matrix(&matrix, &n, &m);
//    if (rc == OK)
//    {
//        print_matrix(matrix, n, m);
//    }
    get_matrix(&matrix, &n, &m);
    printf("next\n");
    char mode;
    mode_matrix:
    if (input_string(&mode, 2, "--------------------------\nInput or create the matrix\n1-file\n2-manual\n"
                     "3-auto(%)\nInput the mode of creation: ") != OK)
    {
        rc = IO_ERR;
        goto end;
    }
    if (mode - '0' == 1)
    {
        printf("working with file\n");
        FILE *f_matrix = NULL;
        if (get_file(&f_matrix) == FILE_ERR)
        {
            rc = FILE_ERR;
            goto end;
        }
        int code = coord_usual();
        int ok;
        if (code == 1)
        {
            printf("coordinats\n");
            matrix = read_matrix_coord(f_matrix, &n, &m, &ok);
            if (ok == MEM_ERR || ok == CONT_ERR)
            {
                rc = ok;
                goto end;
            }
            printf("ok - %d\n", ok);
            print_matrix(matrix, n, m);
            printf("double* - %d, double - %d\n", (int)sizeof(double*), (int)sizeof(double));
            printf("mem size - %d", memory_size(matrix, n, m));
        }
        else if (code == 2)
        {
            printf("usual matrix\n");
            ok = read_matrix_lines(f_matrix, &matrix, &n, &m);
            if (ok == MEM_ERR || ok == CONT_ERR)
            {
                rc = ok;
                goto end;
            }
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
    printf("\n");
    print_matrix(matrix, n, m);
    //double vector[m];
    vector = calloc(m, sizeof(double));
    if (!vector)
    {
        rc = MEM_ERR;
        goto end;
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

        //double vector[m];
        int code = coord_usual();
        if (code == 2)
        {
            for (int i = 0; i < m; i++)
                if (input_double(&vector[i], 10,"input an element: ") != OK)
                {
                    rc = IO_ERR;
                    goto end;
                }
            printf("prints\n");
            print_array(vector, m);
            print_matrix(matrix, n, m);
        }
        else if (code == 1)
        {
            int els_number;
            input_int(&els_number, 4, "input the number of elemnets of nonzero value: ");
            if (els_number == 0)
                for (int i = 0; i < m; i++)
                    vector[i] = 0;
            else if (els_number > 0 && els_number <= m)
            {
                int d, el;
                printf("press enter at the end of input of all elements\n");
                for (int i = 0; i < els_number; i++)
                {
                    d = input_int(&i, 2, "input index:");
                    if (d != OK)
                    {
                        rc = IO_ERR;
                        goto end;
                    }
                    if (i < 0 || i >= m)
                    {
                        rc = IO_ERR;
                        goto end;
                    }
                    el = input_double(&vector[i], 10, "input a value: ");
                    if (el != OK)
                    {
                        rc = IO_ERR;
                        goto end;
                    }
                }
                clean_stdin();

            }
        }
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
    printf("MULTIPLY");
    print_array(vector, m);
    print_matrix(matrix, n, m);//error
    //double result[n];
    result = malloc(n * sizeof (double));
    if (!result)
    {
        rc = MEM_ERR;
        goto end;
    }
    multiply_usual(matrix, vector, n, m, result);
    print_array(result, n);


    end:
    //free
    if (rc == MEM_ERR)
        printf("Memory error\n");
    if (rc == IO_ERR)
        printf("Input error\n");
    if (rc == CONT_ERR)
        printf("Content error\n");
    if (rc == FILE_ERR)
        printf("File name error\n");
    printf("Exiting the program\n");
    return rc;
}
