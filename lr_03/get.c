#include "error.h"
#include "io.h"
#include "file.h"
#include "matrix_mem.h"

int matrix_mode1(double ***matrix, int *n, int *m)
{
    printf("working with file\n");
    FILE *f_matrix = NULL;
    if (get_file(&f_matrix) == FILE_ERR)
    {
        return FILE_ERR;
    }
    int code = get_mode("123", "-------------------\n1-coordinates\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    int ok;
    if (code == 1)
    {
        printf("coordinats\n");
        *matrix = read_matrix_coord(f_matrix, n, m, &ok);
        if (ok == OK)
                print_matrix(*matrix, *n, *m);
        fclose(f_matrix);
        return ok;
    }
    if (code == 2)
    {
        printf("usual matrix\n");
        ok = read_matrix_lines(f_matrix, matrix, n, m);
        if (ok == OK)
                print_matrix(*matrix, *n, *m);
        fclose(f_matrix);
        return ok;
    }

    fclose(f_matrix);
    return IO_ERR;
}

int matrix_mode2(double ***matrix, int *n, int *m)
{
    printf("manual\n");
    if ((input_int(n, 5, "Input the quantity of rows:(0, 9999) ") != OK)
            || (input_int(m, 5, "Input the quantity of columns:(0, 9999) ") != OK))
        return IO_ERR;
    printf("%d %d\n", *n, *m);
    *matrix = allocate_matrix(*n, *m);
    if (*matrix == NULL)
        return MEM_ERR;
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
        {
            if (input_double(&(*matrix)[i][j], 10, "input an element: ") == IO_ERR)
                return IO_ERR;
            printf("%f\n", (*matrix)[i][j]);
        }
    return OK;
}

void randomize(double **matrix, int n, int m)
{
    //srand(time(NULL));
    int i = rand() % n;
    printf("i - %d ", i);
    int j = rand() % m;
    printf("j - %d\n", j);
    while (matrix[i][j] != 0)
    {
        int i = rand() % n;
        printf("i - %d ", i);
        int j = rand() % m;
        printf("j - %d\n", j);
    }
    double div = RAND_MAX / 100;
    double el = - 50 + (rand() / div);
    printf("%d %d %f\n", i, j, el);
    matrix[i][j] = el;
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
    printf("auto\n");
    if ((input_int(n, 5, "Input the quantity of rows:(0, 9999) ") != OK)
            || (input_int(m, 5, "Input the quantity of columns:(0, 9999) ") != OK))
        return IO_ERR;
    printf("%d %d\n", *n, *m);
    if (input_int(&prc, 4, "Input the % of filling: ") == OK)
        if (prc > 100)
            return IO_ERR;
    printf("%d\n", prc);
    *matrix = allocate_matrix(*n, *m);
    if (!(*matrix))
        return MEM_ERR;
    int nonzero = (int)(*n * *m * prc/ 100);
    printf("nonzero els - %d\n", nonzero);
    printf("rows - %d\n", nonzero/(*m));
    printf("last row - %d\n", nonzero%(*m));
    for (int i = 0; i < nonzero/(*m); i++)
    {
        for (int j = 0; j < *m; j++)
        {
            (*matrix)[i][j] = rand_double();
            printf("%d %d %f\n", i, j, (*matrix)[i][j]);
        }
    }
    int i = nonzero/(*m);
    printf("i = %d\n", i);
    for (int j = 0; j < nonzero%(*m); j++)
    {
        (*matrix)[i][j] = rand_double();
        printf("%d %d %f\n", i, j, (*matrix)[i][j]);
    }
    return OK;
}

int vector_mode1(double **vector, int *n)
{
    printf("file\n");
    FILE *f_vector = NULL;
    if (get_file(&f_vector) == FILE_ERR)
    {
        return FILE_ERR;
    }
    int code = get_mode("123", "-------------------\n1-coordinates\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    int ok;
    if (code == 1)
    {
        printf("coordinats\n");
        *vector = read_vector_coord(f_vector, n, &ok);
        if (ok == OK)
                print_array(*vector, *n);
        fclose(f_vector);
        return ok;
    }
    if (code == 2)
    {
        printf("usual matrix\n");
        ok = read_vector_lines(f_vector, vector, n);
        if (ok == OK)
                print_array(*vector, *n);
        fclose(f_vector);
        return ok;
    }

    fclose(f_vector);
    return IO_ERR;
}

int vector_mode2(double **vector, int n)
{
    printf("manual\n");
    double *tmp = calloc(n, sizeof(double));
    if (!tmp)
        return MEM_ERR;
    int code = get_mode("123", "-------------------\n1-coordinates"
                               "\n2-by elements\n3-exit\nInput the mode or 3 for exit: ");
    if (code == 1)
    {//предоставить возможность выхода
        int els_number;
        input_int(&els_number, 4, "input the number of elemnets of nonzero value: ");
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
    return IO_ERR;
}

int vector_mode3(double **vector, int n)
{
    printf("auto\n");
    int prc;
    if (input_int(&prc, 4, "Input the % of filling: ") == OK)
        if (prc > 100)
            return IO_ERR;
    printf("%d\n", prc);
    *vector = calloc(n, sizeof(double));
    if (!(*vector))
        return MEM_ERR;
    int nonzero = (int)(n * prc/ 100);
    printf("nonzero els - %d\n", nonzero);
    for (int j = 0; j < nonzero; j++)
    {
        (*vector)[j] = rand_double();
        printf("%d %f\n", j, (*vector)[j]);
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
    if (mode == 1)
        return vector_mode1(vector, n);
    if (mode == 2)
        return vector_mode2(vector, *n);
    if (mode == 3)
        return vector_mode3(vector, *n);
    if (mode == 4)
        return IO_ERR;
    return get_vector(vector, n);
}
