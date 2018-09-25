#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define OK 0
#define IO_ERR 1

int input(char **str_array_beg, char **str_array_end)
{
    printf("Input number\n");
    int length_of_array = 1;
    *str_array_beg = malloc(length_of_array);

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

    *str_array_end = *str_array_beg + length_of_array;
    return OK;
}

//void print(void *b, void *e, char c)
//{
//    size_t size;
//    if (c == 'c')
//        size = 1;


//    if (c == 'i')
//        size = 4;

//    for (void *run = b; run < e - size; run += size)
//        if (c == 'i')
//            printf("%d ", *run);
//        if (c == 'c')
//            printf("%c ", *run);
//    printf("\n");
//}

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

int make_array(char *str_beg, char *str_end, int **num_beg, int **num_end, int *power)
{
    char *s = str_beg;
    int len = str_end - str_beg;
    int index = 0;
    int flag = 0;
    int power_sign = 1;
    *power = 0;
    int i_e = 0;

    *num_beg = malloc(sizeof(int));

    if (*s == '+' || isdigit(*s))
        *num_beg[index] = 1;// positive
    if (*s == '-')
        *num_beg[index] = -1;// negative


    for (int i = len - 1; i >= 0; i --)
    {
        if (isdigit(*(str_beg + i)))
        {
            index ++;
            int length = (index + 1) * sizeof(int);
            *num_beg = realloc(*num_beg, length);
            *(*num_beg + index)= *(str_beg + i) - '0';
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

        if (*(str_beg + i) == 'e' || *(str_beg + i) == 'E')
        {
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
    zeros(num_beg, num_end);

    return OK;
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

void copy_array(int *ab, int *ae, int *bb, int *be)
{
    for (int i = 0; i < (ae - ab); i ++)
        *(bb + i) = *(ab + i);
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
            printf("r = %d\n", r);
            *(buf + i + j -1) = (*(*ab + i) * *(*bb + j)) % 10 + r;
            printf("el = %d\n", *(buf + i + j -1));
            r = (*(*ab + i) * *(*bb + j)) / 10;
        }
        printf("buf ");
        print_int(buf, buf_end);
        sum(&buf, &buf_end, &buf2, &buf2_end, mb, me);// error
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
    int rc;
    char *sb = NULL, *se = NULL;
    char *s2b = NULL, *s2e = NULL;
    int *nb = NULL, *ne = NULL;
    int power1;
    int *n2b = NULL, *n2e = NULL;
    int power2;

    rc = input(&sb, &se);
    if (rc == OK)
    {
        print_char(sb, se);
        rc = make_array(sb, se, &nb, &ne, &power1);
        if (rc == OK)
        {
            printf("power - %d\n", power1);
            print_int(nb, ne);
        }
        else
        {
            free(nb);
            free(sb);
            printf("IO_ERR");
            return rc;
        }
    }
    else
    {
        free(sb);
        printf("IO_ERR");
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
