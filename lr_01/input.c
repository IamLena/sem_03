#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define OK 0
#define IO_ERR 1
#define MEM_ERR 2

void instruction()
{
    printf("Введите последовательно два числа (по запросу программы).\n");
    printf("можно указывать или не указывать (если число положительно) знак мантисы числа и порядка,\n");
    printf("число может содержать только одну точку или запятую, обозначающую дробную часть числа,\n");
    printf("можете записать число в экспоненциальной форме, изпользуя \"e\" или \"Е\".\n" );
    printf("Для удобства отмечены границы 30 символов.\n");
    printf("При завершении ввода нажмите enter\n");
}

int input(char **str_array_beg, char **str_array_end)
{
    printf("Input number\n");
    printf("+/-|                              |\n    ");

    int length_of_array = 1;
    *str_array_beg = malloc(length_of_array);
    if (*str_array_beg)
    {
        int length_of_string = 0;
        char c;

        while (( c = getchar() ) != '\n' && c != EOF)
        {
            if (c =='+' || c == '-' || c =='.' || c == ',' || c == 'e' || c == 'E' || isdigit(c))
            {
                if (length_of_array == length_of_string)
                {
                    length_of_array ++;
                    *str_array_beg = realloc(*str_array_beg, length_of_array);
                }
                *(*str_array_beg + length_of_string) = c;
                length_of_string ++;
            }
            else
                return IO_ERR;
        }
        if(length_of_string == 0)
            return IO_ERR;
        *str_array_end = *str_array_beg + length_of_array;
        return OK;
    }
    else
        return MEM_ERR;
}

void print_int(int *b, int *e)
{
    printf("array: ");
    for (int *run = b; run < e; run ++)
        printf("%d ", *run);
    printf("\n");
}

void print_char(char *b, char *e)
{
    for (char *run = b; run < e; run ++)
        printf("%c ", *run);
    printf("\n");
}

void copy_array(int *ab, int *ae, int *bb, int *be)
{
    for (int i = 0; i < (ae - ab); i ++)
        *(bb + i) = *(ab + i);
}

void zeros (int **b, int **e)
{
    int n = *e - *b;
    int i = n - 1;
    while (i >= 2)
    {
        if (*(*b + i) != 0)
            break;
        i --;
    }
    i ++;
    *b = realloc(*b, i*sizeof(int));
    *e = *b + i;
}

void add_zero(int **ab, int **ae, int n)
{
    int m = *ae - *ab;
    *ab = realloc(*ab, (m + n)* sizeof(int));
    *ae = *ab + m + n;
    for (int i = m; i < m + n; i ++)
        *(*ab + i) = 0;
    *ae = *ab + m + n;
}

int make_array(char *str_beg, char *str_end, int **num_beg, int **num_end, int *power)
{
    assert((str_beg != NULL) && (str_end != NULL) && (str_beg < str_end) && (power != NULL));
    int len = str_end - str_beg;
    int index = 0;
    int flag = 0;
    int power_sign = 1;
    *power = 0;
    int i_e = 0;

    *num_beg = malloc(sizeof(int));

    if(*num_beg)
    {
        //значение знака храним в первом элементе массива 1 - положительный, 0 - отрицательный
        if (*str_beg == '+' || isdigit(*str_beg))
            *num_beg[index] = 1;// positive
        if (*str_beg  == '-')
            *num_beg[index] = -1;// negative


        //заполнение с конца, зеркально
        for (int i = len - 1; i >= 0; i --)
        {
            if (isdigit(*(str_beg + i)))
            {
                index ++;
                int length = (index + 1) * sizeof(int);
                *num_beg = realloc(*num_beg, length);
                if (!(*num_beg))
                    return MEM_ERR;
                *(*num_beg + index)= *(str_beg + i) - '0'; //char to int
                printf("%d ", *(*num_beg + index));
            }

            if (*(str_beg + i) == '.' || *(str_beg + i) == ',')
            {
                if (flag == 0)
                {
                    flag = 1;
                    *power += (i - len + 1 + i_e);
                }
                else
                    return IO_ERR;
            }

            if ((*(str_beg + i) == '-' || *(str_beg + i) == '+'))
            {
                if (i != 0)
                {
                    if (*(str_beg + i - 1) != 'e' && (*(str_beg + i - 1)) != 'E' )
                        return IO_ERR;
                    else
                        if (*(str_beg + i) == '-')
                            power_sign = -1;
                }
            }

            //при с талкновении с е бегунок по массиву идет в обратную сторону, создавая значение степени типа int
            if (*(str_beg + i) == 'e' || *(str_beg + i) == 'E')
            {
                if (index > 4)
                    printf("\n!!Переполнение порядка!!\n");
                if(index > 9)
                    return IO_ERR;
                i_e = (len - i);
                if (flag == 1)
                    return IO_ERR;
                else
                {
                    for (int j = index; j > 0; j --)
                    {
                        *power = *power * 10 + *(*num_beg + j);
                    }
                    *power *= power_sign;
                    *num_beg = realloc(*num_beg, 1 * sizeof(int));
                    index = 0;
                }
            }
        }
        *num_end = *num_beg + index + 1;
        if((*num_end - *num_beg) > 30)
            printf("\n!!Ваше число превышает 30 символов!!\n");
        zeros(num_beg, num_end);

        return OK;
    }
    else
        return MEM_ERR;
}

void sum(int **ab, int **ae, int **bb, int **be, int **sb, int **se)
{
    int n1 = *ae - *ab;
    int n2 = *be - *bb;
    int n;
    if (n1 < n2)
    {
        n = n2 + 1;
        add_zero(ab, ae, (n2 - n1 + 1));
        add_zero(bb, be, 1);
    }
    else
    {
        n = n1 + 1;
        add_zero(bb, be, (n1 - n2 + 1));
        add_zero(ab, ae, 1);
    }
    int r = 0;
    *sb = malloc(n*sizeof(int));
    **sb = 1;
    for (int i = 1; i < n; i ++)
    {
        *(*sb + i) = (*(*ab + i) + *(*bb + i)) % 10 + r;
        r = (*(*ab + i) + *(*bb + i)) / 10;
    }
    *se = *sb + n;
}

void mult(int **ab, int **ae, int p1, int **bb, int **be, int p2, int **mb, int **me, int *p)
{
    *p = p1 + p2;
    add_zero(bb, be, 1);
    int n1 = *ae - *ab;
    int n2 = *be - *bb;
    int n = n1 + n2 - 1;
    int *buf = NULL, *buf2 = NULL;
    int r = 0;
    buf2 = calloc(2, sizeof(int));
    int *buf2_end = buf2 + 2;

    for (int i = 1; i < n1; i ++)
    {
        r = 0;
        buf = calloc(n, sizeof(int));
        int *buf_end = buf + n;
        for (int j = 1; j < n2; j++)
        {
            *(buf + i + j -1) = (*(*ab + i) * *(*bb + j)) % 10 + r;
            r = (*(*ab + i) * *(*bb + j)) / 10;
        }
        sum(&buf, &buf_end, &buf2, &buf2_end, mb, me);
        free(buf);
        copy_array(*mb, *me, buf2, buf2_end);
    }
    **mb = (**ab == **bb);
    zeros(mb, me);
    free(buf2);
}

void norm_form(int *b, int *e, int p)
{
    if (*b == 0)
        printf("-");
    if(*b == 1)
        printf("+");
    for (int *run = e - 1; run > b; run --)
        printf("%d", *run);
    printf("e");
    printf("%d", p);
}


int main(void)
{
    setbuf(stdout, NULL);
    printf("типы и структуры данных\nлабораторная работа 1\nИУ7-31Б Лучина Елена\n\n");
    printf("\t\tУмножение больших чисел\n\n");
    instruction();

    int rc;//                               код возврата
    char *sb = NULL, *se = NULL;//          строка первого числа
    char *s2b = NULL, *s2e = NULL;//        строка второго числа
    int *nb = NULL, *ne = NULL;//           мантисса первого числа
    int power1;//                           степень первого числа
    int *n2b = NULL, *n2e = NULL; //        мантисса второго числа
    int power2;//                           степень второго числа

    rc = input(&sb, &se);
    if (rc == OK)
    {
        print_char(sb, se); //считанная строка
        rc = make_array(sb, se, &nb, &ne, &power1);
        if (rc == OK)
        {
            printf("power - %d\n", power1);//степень, при приведенном к стандарту числе
            print_int(nb, ne);
        }
        else if (rc == IO_ERR)
        {
            free(nb);
            free(sb);
            free(sb);
            printf("Некорректный ввод\n");
            printf("Обратите внимание на инструкцию к вводу.\n");
            return rc;
        }
        else
        {
            printf("Ошибка памяти\n");
            return rc;
        }
    }
    else if (rc == IO_ERR)
    {
        free(sb);
        printf("Некорректный ввод\n");
        printf("Обратите внимание на инструкцию к вводу.\n");
        return rc;
    }
    else
    {
        printf("Ошибка памяти\n");
        return rc;
    }

    rc = input(&s2b, &s2e);
    if (rc == OK)
    {
        print_char(s2b, s2e);
        rc = make_array(s2b, s2e, &n2b, &n2e, &power2);
        if (rc == OK)
        {
            printf("power - %d\n", power2);
            print_int(n2b, n2e);
        }
        else
        {
            free(n2b);
            free(s2b);
            printf("IO_ERR");
            return rc;
        }
    }
    else
    {
        free(s2b);
        printf("IO_ERR");
        return rc;
    }
    int *sumb = NULL, *sume = NULL;
    int power =0;
    mult(&nb, &ne, power1, &n2b, &n2e, power2, &sumb, &sume, &power);
    printf("power - %d\n", power);
    printf("result ");
    print_int(sumb, sume);
    norm_form(sumb, sume, power);
    free(sb);
    free(s2b);
    free(nb);
    free(n2b);
    return OK;
}
