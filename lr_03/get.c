#include <stdbool.h>

#include "error.h"
#include "io.h"
#include "file.h"
#include "matrix_mem.h"

int matrix_mode1(double ***matrix, int *n, int *m)
{
    FILE *f_matrix = NULL;
    if (get_file(&f_matrix) == FILE_ERR)
    {
        return FILE_ERR;
    }
    int code = get_mode("123", "-------------------\n1-by coordinates\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    int ok;
    if (code == 1)
    {
        *matrix = read_matrix_coord(f_matrix, n, m, &ok);
        fclose(f_matrix);
        return ok;
    }
    if (code == 2)
    {
        ok = read_matrix_lines(f_matrix, matrix, n, m);
        fclose(f_matrix);
        return ok;
    }
    fclose(f_matrix);
    return EXIT;
}

int matrix_mode2(double ***matrix, int *n, int *m)
{
    int rc = OK;
    bool yn;
    if ((input_int(n, 5, "Input the quantity of rows:(0, 9999) (length < 5) ") != OK)
            || (input_int(m, 5, "Input the quantity of columns:(0, 9999) (length < 5) ") != OK))
        return IO_ERR;
    if (*n == 0)
    {
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_int(n, 5, "Input the quantity of rows:(0, 9999) (length < 5) ");
        if (yn == false)
            rc = IO_ERR;
        if (rc == IO_ERR) return IO_ERR;
    }
    if (*m == 0)
    {
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_int(m, 5, "Input the quantity of columns:(0, 9999) (length < 5) ");
        if (yn == false)
            rc = IO_ERR;
        if (rc == IO_ERR) return IO_ERR;
    }
    *matrix = allocate_matrix(*n, *m);    
    if (*matrix == NULL)
        return MEM_ERR;

    int code = get_mode("123", "-------------------\n1-by coordinates"
                               "\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    if (code == 1)
    {
        int els_number;
        input_int(&els_number, 4, "input the number of elements of nonzero value: ");
        printf("els num - %d\n",els_number);
        if (els_number > 0 && els_number <= *n * *m)
        {
            int el, d;
            int i, j;
            printf("press enter at the end of input of all elements\n");

            for (int k = 0; k < els_number; k++)
            {
                d = input_int(&i, 5, "input row index: ");
                if (d != OK || i > *n)
                    return IO_ERR;
                d = input_int(&j, 5, "input column index: ");
                if (d != OK || j > *m)
                    return IO_ERR;
                el = input_double(&((*matrix)[i][j]), 10, "input a value: ");
                if (el != OK)
                    return IO_ERR;
            }
            return OK;
        }
        else
            return IO_ERR;
    }
    if (code == 2)
    {
        for (int i = 0; i < *n; i++)
            for (int j = 0; j < *m; j++)
            {
                printf("[%d][%d] ",i, j);
                if (input_double(&(*matrix)[i][j], 10, "input an element: ") == IO_ERR)
                    return IO_ERR;
            }
        return OK;
    }
    return EXIT;
}

double rand_double(void)
{
    double div = RAND_MAX / 100;
    double el = - 50 + (rand() / div);
    return el;
}

int matrix_mode3(double ***matrix, int *n, int *m)
{
    int prc;
    if ((input_int(n, 5, "Input the quantity of rows:(0, 9999) (length < 5) ") != OK)
            || (input_int(m, 5, "Input the quantity of columns:(0, 9999) (length < 5) ") != OK))
        return IO_ERR;
    if (input_int(&prc, 4, "Input the % of filling: ") == OK)
        if (prc > 100)
            return IO_ERR;
    *matrix = allocate_matrix(*n, *m);
    if (!(*matrix))
        return MEM_ERR;
    int nonzero = (int)(*n * *m * prc/ 100);

    int k = 0, i, j;
    while (k < nonzero)
    {
        i = rand() % *n;
        j = rand() % *m;
        if ((*matrix)[i][j] == 0)
        {
            (*matrix)[i][j] = rand_double();
            k++;
        }
    }
    return OK;
}

int vector_mode1(double **vector, int *n)
{
    FILE *f_vector = NULL;
    if (get_file(&f_vector) == FILE_ERR)
    {
        return FILE_ERR;
    }
    int code = get_mode("123", "-------------------\n1-by coordinates\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    int ok;
    if (code == 1)
    {
        *vector = read_vector_coord(f_vector, n, &ok);
        fclose(f_vector);
        return ok;
    }
    if (code == 2)
    {
        ok = read_vector_lines(f_vector, vector, n);
        fclose(f_vector);
        return ok;
    }
    fclose(f_vector);
    return EXIT;
}

int vector_mode2(double **vector, int n)
{
    double *tmp = calloc(n, sizeof(double));
    if (!tmp)
        return MEM_ERR;
    int code = get_mode("123", "-------------------\n1-by coordinates"
                               "\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    if (code == 1)
    {
        int els_number;
        input_int(&els_number, 4, "input the number of elements of nonzero value: ");
        printf("els num - %d\n",els_number);
        if (els_number > 0 && els_number <= n)
        {
            int d, el;
            printf("press enter at the end of input of all elements\n");
            for (int i = 0; i < els_number; i++)
            {
                d = input_int(&i, 5, "input index:");
                if (d != OK || i > n)
                    return IO_ERR;
                el = input_double(&tmp[i], 10, "input a value: ");
                if (el != OK)
                    return IO_ERR;
            }
            clean_stdin();//может поправить как-то
            *vector = tmp;
            return OK;
        }
    }
    if (code == 2)
    {
        for (int i = 0; i < n; i++)
            if (input_double(&tmp[i], 10,"input an element: ") != OK)
                return IO_ERR;
        *vector = tmp;
        return OK;
    }
    return EXIT;
}

int vector_mode3(double **vector, int n)
{
    int prc;
    if (input_int(&prc, 4, "Input the % of filling: ") == OK)
        if (prc > 100)
            return IO_ERR;
    *vector = calloc(n, sizeof(double));
    if (!(*vector))
        return MEM_ERR;
    int nonzero = (int)(n * prc/ 100);
    int k = 0, i;
    while (k < nonzero)
    {
        i = rand() % n;
        if ((*vector)[i] == 0)
        {
            (*vector)[i] = rand_double();
            k++;
        }
    }
    return OK;
}

int get_matrix(double ***matrix, int *n, int *m)
{
    int mode = get_mode("1234", "--------------------------\nInput or create the matrix\n1-file"
                               "\n2-manual\n3-auto(%)\n4-exit\nInput the mode of creation or put 4 for exit: ");
    if (mode == 1)
        return matrix_mode1(matrix, n, m);
    if (mode == 2)
        return matrix_mode2(matrix, n, m);
    if (mode == 3)
        return matrix_mode3(matrix, n, m);
    if (mode == 4)
        return IO_ERR;
    return get_matrix(matrix, n, m);
}

int get_vector(double **vector, int *n)
{
    int mode = get_mode("1234", "--------------------------\nInput or create vector\n1-file\n2-manual\n3-auto(%)\n"
                               "4-exit\nInput the mode of creation or put 4 for exit: ");
    int file_n;
    if (mode == 1)
    {
        int rc = vector_mode1(vector, &file_n);
        printf("n = %d file_n = %d\n", file_n, *n);
        if (file_n != *n)
        {
            printf("incorrect size, can not multiply\n");
            rc = IO_ERR;
        }
        return rc;
    }
    if (mode == 2)
        return vector_mode2(vector, *n);
    if (mode == 3)
        return vector_mode3(vector, *n);
    if (mode == 4)
        return IO_ERR;
    return get_vector(vector, n);
}
