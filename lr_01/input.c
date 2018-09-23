#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define OK 0
#define IO_ERR 1

int input(char **str_array_beg, char **str_array_end)
{
    printf("Input a long string\n");
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

int main()
{
    char *sb = NULL, *se = NULL;

    if (input(&sb, &se) == IO_ERR)
        printf("IO_ERR");
    else
    {
        print_char(sb, se);
        int *nb = NULL, *ne = NULL;
        int power;
        if (make_array(sb, se, &nb, &ne, &power) == OK)
        {
            printf("power - %d\n", power);
            print_int(nb, ne);
            free(nb);
        }
        else
            printf("IO_ERR");
    }
    free(sb);

    return OK;
}
