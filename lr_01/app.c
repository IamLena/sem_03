#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include<time.h>

#define OK 0
#define IO_ERR 1
#define MEM_ERR 2

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void instruction()
{
    printf("ИНСТРУКЦИЯ К ВВОДУ\n");
    printf("Введите последовательно два числа (по запросу программы).\n");
    printf("Сначала программа запросит вещественное число, потом целое.\n");
    printf("Число вводите без пробелов.\n");
    printf("Укажите знак мантисы числа и порядка, при отсутсвии знака число будет считаться положительным,\n");
    printf("число может содержать только одну точку или запятую, обозначающую дробную часть числа,\n");
    printf("можете записать число в экспоненциальной форме, изпользуя \"e\" или \"Е\".\n" );
    printf("Разряд порядка должен не превышать 5.\n");
    printf("Разряд числа должен не превышать 30.\n");
    printf("Для удобства отмечены границы 30 символов.\n");
    printf("При завершении ввода нажмите enter.\n\n");
}

int input_int(char **str_array_beg, char **str_array_end)
{
    printf("Введите целое число:\n");
    printf("+/-|                              |\n    ");

    int length_of_array = 1;
    *str_array_beg = malloc(length_of_array);
    if (*str_array_beg)
    {
        int length_of_string = 0;
        char c;

        while (( c = getchar() ) != '\n' && c != EOF)
        {
            if (c =='+' || c == '-' || isdigit(c) || c == 'e' || c == 'E')
            {
                if (length_of_array == length_of_string)
                {
                    length_of_array ++;
                    char * tmp = realloc(*str_array_beg, length_of_array);
                    if(tmp)
                        *str_array_beg = tmp;
                    else
                        return MEM_ERR;
                }
                *(*str_array_beg + length_of_string) = c;
                length_of_string ++;
            }
            else
            {
                printf("\nСодержит неправильные символы.");
                return IO_ERR;
            }
        }
        if(length_of_string == 0)
        {
            printf("Пустой ввод.\n");
            return IO_ERR;
        }
        *str_array_end = *str_array_beg + length_of_array;
        return OK;
    }
    else
        return MEM_ERR;
}

int input_float(char **str_array_beg, char **str_array_end)
{
    printf("Введите вещественное число:\n");
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
                    char *tmp = realloc(*str_array_beg, length_of_array);
                    if(tmp)
                        *str_array_beg = tmp;
                    else
                        return MEM_ERR;
                }
                *(*str_array_beg + length_of_string) = c;
                length_of_string ++;
            }
            else
            {
                printf("\nСодержит неправильные символы.");
                return IO_ERR;
            }
        }
        if(length_of_string == 0)
        {
            printf("\nПустой ввод.");
            return IO_ERR;
        }
        *str_array_end = *str_array_beg + length_of_array;
        return OK;
    }
    else
        return MEM_ERR;
}

void print_int(const int *b, const int *e)
{
    assert(b != NULL && e != NULL && b < e);
    printf("array: ");
    for (const int *run = b; run < e; run ++)
        printf("%d ", *run);
    printf("\n");
}

void print_char(const char *b, const char *e)
{
    assert(b != NULL && e != NULL && b < e);
    for (const char *run = b; run < e; run ++)
        printf("%c ", *run);
    printf("\n");
}

void copy_array(const int *ab, const int *ae, int *bb, int *be)
{
    assert(ab != NULL && ae != NULL && bb != NULL && be != NULL);
    assert((ae - ab == be - bb) && (ab < ae));
    for (int i = 0; i < (ae - ab); i ++)
        *(bb + i) = *(ab + i);
}

int delete_useless_zeros (int **b, int **e)
{
    int n = *e - *b;
    int i = n - 1;
    while (i > 1)
    {
        if (*(*b + i) != 0)
            break;
        i --;
    }
    i ++;
    int *tmp = realloc(*b, i*sizeof(int));
    if(tmp)
        *b = tmp;
    else
        return MEM_ERR;
    *e = *b + i;
    return OK;
}

int add_zero(int **ab, int **ae, int n)
{
    int m = *ae - *ab;
    int *tmp = realloc(*ab, (m + n)* sizeof(int));
    if (tmp)
        *ab = tmp;
    else
        return MEM_ERR;
    *ae = *ab + m + n;
    for (int i = m; i < m + n; i ++)
        *(*ab + i) = 0;
    *ae = *ab + m + n;
    return OK;
}

int make_array(char *str_beg, char *str_end, int **num_beg, int **num_end, int *power)
{
    assert((str_beg != NULL) && (str_end != NULL) && (str_beg < str_end) && (power != NULL));
    int len = str_end - str_beg;
    int index = 0;
    int flag = 0;
    int flag_e = 0;
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
                int *tmp = realloc(*num_beg, length);
                if(tmp)
                    *num_beg = tmp;
                else
                    return MEM_ERR;
                *(*num_beg + index)= *(str_beg + i) - '0'; //char to int
            }

            if (*(str_beg + i) == '.' || *(str_beg + i) == ',')
            {
                if (flag == 0)
                {
                    flag = 1;
                    *power += (i - len + 1 + i_e);
                }
                else
                {
                    printf("\nСождержит более одной точки");
                    return IO_ERR;
                }
            }

            if ((*(str_beg + i) == '-' || *(str_beg + i) == '+'))
            {
                if (i != 0)
                {
                    if (i == len - 1)
                    {
                        printf("Пустой ввод\n");
                        return IO_ERR;
                    }
                    if (*(str_beg + i - 1) != 'e' && (*(str_beg + i - 1)) != 'E' )
                    {
                        printf("\nНеправильное место знака");
                        return IO_ERR;
                    }
                    else
                        if (*(str_beg + i) == '-')
                            power_sign = -1;
                }
                else
                    if(i == len - 1)
                    {
                        printf("Пустой ввод\n");
                        return IO_ERR;
                    }
            }

            //при с талкновении с е бегунок по массиву идет в обратную сторону, создавая значение степени типа int
            if ((*(str_beg + i) == 'e' || *(str_beg + i) == 'E'))
            {
                if (i == len - 1 || i == 0 || (i == 1 && (*str_beg == '+' || *str_beg == '-')))
                {
                    printf("Пустой ввод\n");
                    return IO_ERR;
                }
                if (flag_e == 1)
                {
                    printf("\nСодержит более одной е.");
                    return IO_ERR;
                }
                flag_e = 1;
                if (index > 5)
                {
                    printf("\n!!Переполнение порядка!!");
                    return IO_ERR;
                }
                i_e = (len - i);
                if (flag == 1)
                {
                    printf("\nНеправильное расположение точки");
                    return IO_ERR;
                }
                else
                {
                    for (int j = index; j > 0; j --)
                        *power = *power * 10 + *(*num_beg + j);
                    *power *= power_sign;
                    int *tmp = realloc(*num_beg, 1 * sizeof(int));
                    if(tmp)
                        *num_beg = tmp;
                    else
                        return MEM_ERR;
                    index = 0;
                }
            }
        }
        *num_end = *num_beg + index + 1;
        if((*num_end - *num_beg) > 31)
        {
            printf("\n!!Ваше число превышает 30 символов!!");
            return IO_ERR;
        }
        if (delete_useless_zeros(num_beg, num_end) == OK)
            return OK;
        else
            return MEM_ERR;
    }
    else
        return MEM_ERR;
}

int sum(int **ab, int **ae, int **bb, int **be, int **sb, int **se)
{
    int n1 = *ae - *ab;
    int n2 = *be - *bb;
    int n;
    int rc;
    if (n1 < n2)
    {
        n = n2 + 1;
        rc = add_zero(ab, ae, (n2 - n1 + 1));
        if(rc == MEM_ERR)
            return rc;
        rc = add_zero(bb, be, 1);
        if(rc == MEM_ERR)
            return rc;
    }
    else
    {
        n = n1 + 1;
        rc = add_zero(bb, be, (n1 - n2 + 1));
        if (rc == MEM_ERR)
            return rc;
        rc = add_zero(ab, ae, 1);
        if (rc == MEM_ERR)
            return rc;
    }
    int r = 0;
    *sb = malloc(n*sizeof(int));
    if (!(*sb))
        return MEM_ERR;
    **sb = 1;
    for (int i = 1; i < n; i ++)
    {
        *(*sb + i) = (*(*ab + i) + *(*bb + i)) % 10 + r;
        r = (*(*ab + i) + *(*bb + i)) / 10;
    }
    *se = *sb + n;
    return OK;
}

int mult(int **ab, int **ae, int p1, int **bb, int **be, int p2, int **mb, int **me, int *p)
{
    *p = p1 + p2;
    int rc = add_zero(bb, be, 1);
    if(rc == MEM_ERR)
        return rc;
    int n1 = *ae - *ab;
    int n2 = *be - *bb;
    int n = n1 + n2 - 1;
    int *buf = NULL, *buf2 = NULL;
    int r = 0;
    buf2 = calloc(2, sizeof(int));
    if(!buf2)
        return MEM_ERR;
    int *buf2_end = buf2 + 2;

    for (int i = 1; i < n1; i ++)
    {
        r = 0;
        buf = calloc(n, sizeof(int));
        if(!buf)
            return MEM_ERR;
        int *buf_end = buf + n;
        for (int j = 1; j < n2; j++)
        {
            *(buf + i + j -1) = (*(*ab + i) * *(*bb + j)) % 10 + r;
            r = (*(*ab + i) * *(*bb + j)) / 10;
        }
        if (sum(&buf, &buf_end, &buf2, &buf2_end, mb, me) == MEM_ERR)
        {
            free(buf);
            free(buf2);
            return MEM_ERR;
        }
        free(buf);
        copy_array(*mb, *me, buf2, buf2_end);
    }
    **mb = (**ab == **bb);
    delete_useless_zeros(mb, me);
    free(buf2);
    return OK;
}

int count_zeros(const int *b, const int *e)
{
    assert( b != NULL && e != NULL && b < e);
    int count = 0;
    for (int i = 1; i < (e - b); i ++)
    {
        if (*(b + i) == 0)
            count ++;
        else
            break;
    }
    return count;
}

void zeros(int **b, int **e, int *p)
{
    assert(p != NULL && b != NULL && e != NULL);
    int n = *e - *b;
    int m = count_zeros(*b, *e);
    memmove(*b + 1, *b + 1 + m, (n - m) * sizeof(int));
    *p += m;
    *b = realloc(*b, (n - m)*sizeof(int));
    *e = *b + (n - m);
}
void norm_form(int *b, int *e, int p)
{
    if (*b == 0)
        printf("-");
    if(*b == 1)
        printf("+");
    printf("0.");
    p += (int)(e - b - 1);
    for (int *run = e - 1; run > b; run --)
        printf("%d", *run);
    if (p != 0)
    {
        printf("e");
        printf("%d", p);
    }
}

void round_num (int **b, int **e)
{
    int n = *e - *b;
    assert(n > 30);
    int m = n - 30;
    for (int i = 1; i < m; i ++)
    {
        if (*(*b + i) >= 5)
            *(*b + i + 1) += 1;
        *(*b + i) = 0;
    }

    for (int i = m; i < n - 1; i ++)
    {
        if (*(*b + i) == 10)
        {
            *(*b + i) = 0;
            *(*b + i + 1) += 1;
        }
    }
    if (*(*e - 1) == 10)
    {
        int rc = add_zero(b, e, 1);
        if (rc == MEM_ERR)
            return;
        *(*e - 2) = 0;
        *(*e - 1) = 1;
    }
}

int main(void)
{
    unsigned long long t1, t2, t;
    setbuf(stdout, NULL);
    printf("типы и структуры данных\nлабораторная работа 1\nИУ7-31Б Лучина Елена вариант-20\n\n");
    printf("Умножение больших чисел (вещественное на целое)\n\n");
    instruction();

    int rc;//                               код возврата
    char *sb = NULL, *se = NULL;//          строка первого числа
    char *s2b = NULL, *s2e = NULL;//        строка второго числа
    int *nb = NULL, *ne = NULL;//           мантисса первого числа
    int power1;//                           степень первого числа
    int *n2b = NULL, *n2e = NULL;//        мантисса второго числа
    int power2;//                           степень второго числа

    rc = input_float(&sb, &se);
    if (rc == OK)
    {
        rc = make_array(sb, se, &nb, &ne, &power1);
        if (rc == IO_ERR)
        {
            free(nb);
            free(sb);
            printf("\nНекорректный ввод. ");
            printf("Обратите внимание на инструкцию к вводу.\n");
            return rc;
        }
        if(rc == MEM_ERR)
        {
            printf("\nОшибка памяти\n");
            free(sb);
            return rc;
        }
    }
    else if (rc == IO_ERR)
    {
        free(sb);
        printf("\nНекорректный ввод. ");
        printf("Обратите внимание на инструкцию к вводу.\n");
        return rc;
    }
    else
    {
        printf("\nОшибка памяти\n");
        return rc;
    }

    rc = input_int(&s2b, &s2e);
    if (rc == OK)
    {
        rc = make_array(s2b, s2e, &n2b, &n2e, &power2);
        if (rc == IO_ERR)
        {
            free(nb);
            free(sb);
            free(n2b);
            free(s2b);
            printf("\nНекорректный ввод. ");
            printf("Обратите внимание на инструкцию к вводу.\n");
            return rc;
        }
        if(rc == MEM_ERR)
        {
            free(nb);
            free(sb);
            free(s2b);
            printf("\nОшибка памяти\n");
            return rc;
        }
    }
    else if (rc == IO_ERR)
    {
        free(nb);
        free(sb);
        free(s2b);
        printf("\nНекорректный ввод. ");
        printf("Обратите внимание на инструкцию к вводу.\n");
        return rc;
    }
    else
    {
        free(nb);
        free(sb);
        printf("\nОшибка памяти\n");
        return rc;
    }

    t1 = tick();
    int *multb = NULL, *multe = NULL;
    int power =0;
    rc = mult(&nb, &ne, power1, &n2b, &n2e, power2, &multb, &multe, &power);
    if(rc == OK)
    {
        if ((multe - multb) > 31)
            round_num(&multb, &multe);
        zeros(&multb, &multe, &power);
        norm_form(multb, multe, power);
    }
    else
        printf("\nОшибка памяти");
    free(sb);
    free(s2b);
    free(nb);
    free(n2b);
    t2 = tick();
    t = t2 - t1;
    printf("\ntime - %lu tick", (unsigned long)t);
    t /= 2400000000;//2.40Ггц - тактовая частота процессора
    printf("\ntime - %lusec", (unsigned long)t);// 2133437267sec
    return rc;
}
