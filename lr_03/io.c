#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "error.h"
#include "io.h"
#include "mult.h"

/**
 * @brief clean_stdin
 * очищает поток ввода путем считывания всего в локальную переменную
 */
void clean_stdin(void)
{
    char c = 'a';
    while (c != '\n' && c != EOF)
        c = getchar();
}

/**
 * @brief input_bool обрабатывает ответ да/нет на логический вопрос
 * @param value где хранить переменную
 * @param key строка-пояснение, сам вопрос
 * @return код возврата - ОК если ответ корректен (да/нет), IO_ERR (если некорректен)
 *
 * считывает первый символ, если не перевод строки и не конец файла, считывает второй символ
 * если строкой символ не перевод строки, очищаем поток ввода и возращаем ошибку. Иначе проверяем что первый символ y/Y (yes) или n/N (no).
 * Если это действительно так возвращаем это значение через параметр, а из самой функции возращаем код успешности. Иначе возвращаем Ошибку ввода.
 */
int input_bool(bool *value, char *key)
{
    printf("%s ", key);
    printf("y/n: ");
    char c = getchar();
    if (c != EOF && c != '\n')
    {
        char c2 = getchar();
        if (c2 == '\n')
        {
            if (c == 'y' || c == 'Y')
            {
                *value = true;
                return OK;
            }
            if (c == 'n' || c == 'N')
            {
                *value = false;
                return OK;
            }
            return IO_ERR;
        }
        clean_stdin();
        return IO_ERR;
    }
    return IO_ERR;
}

/**
 * @brief input_string ввод строки
 * @param str строка, полученная в результате чтения
 * @param n длина строки
 * @param key выражение, пояснение к вводу
 * @return код ошибки
 *
 * считывание посимвольно до конца ввода, увеличивается переменная индекса,
 * если индекс в результате равен нулю или больше длины - сообщаем пользователю,
 * что ввод пустой или превышает допустимое количество символов.
 * Спрашиваем у пользователя хочет ли он попробовать еще, до тех пор пока он не ответить да или нет
 * если да - вызываем функцию ввода еще раз
 * если нет - возвращаем код ошибки ввода
 *
 * считает n-1 и добавит в конец ноль
 */
int input_string(char *str, int n, char *key)
{
    printf("%s", key);
    char c;
    int rc = OK;
    int i = 0;
    bool yn;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (i < n - 1)
            str[i] = c;
        i++;
    }
    str[i] = '\0';
    if (i > n || i == 0)
    {
        //printf("Empty input or reached the maximum size of holder\n");
        printf("Invalid Input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_string(str, n, key);
        if (yn == false)
            rc = IO_ERR;
    }
    return rc;
}

/**
 * @brief input_int - считывает ввод целого числа
 * @param num - переменная где будет храниться значение
 * @param n - длина строки, представляющая число
 * @param key - строка-пояснение к вводу
 * @return код успешности
 *
 * Считывает строку ввода (Узнаем что ввод не пустой и не превышает некоторого значения, ограниченного количеством символов)
 * Если считанно удачно, идем по символам в этой строке. Если это цифра, преобразуем ее в число и прибавим к результату,
 * предварительно умноженному на 10 (если эта цифра не первая в числе).
 * Если встречается не цифра, сообщаем пользователю что ввод не корректен и спрашиваем, хочет ли он попробовать еще раз.
 * Если да, то снова запускаем функцию. Если нет то возвращаем код ошибки ввода.
 * Если считывание прошло успешно, возвращаем значение через параметр и код успешности.
 */
int input_int(int *num, int n, char *key)
{
    char buf[n];
    int a = 0;
    int rc = OK;
    bool yn;
    if (input_string(buf, n + 1, key) != OK)
        return IO_ERR;
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (isdigit(buf[i]))
        {
            if (a != 0)
                a *= 10;
            a += buf[i] - '0';
        }
        else
        {
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_int(num, n, key);
            if (yn == false)
                rc = IO_ERR;
            return rc;
        }
    }
    *num = a;
    return rc;
}

/**
 * @brief input_double считывает вещественное число
 * @param num - переменная где храниться результирующее значение
 * @param n - длина строки, представляющая число
 * @param key - строка-пояснение к вводу
 * @return код успешности
 *
 * Считывает строку ввода (Узнаем что ввод не пустой и не превышает некоторого значения, ограниченного количеством символов)
 * Если считанно удачно, идем по символам в этой строке.  Если это точка, изменяем флаг, если он уже изменен то возвращаем ошибку.
 * Если это цифра, преобразуем ее в число и прибавим к результату, предварительно умноженному на 10 (если эта цифра не первая в числе),
 * если флаг изменен и это дробная часть то увеличиваем делитель.
 * Если встречается не цифра, сообщаем пользователю что ввод не корректен и спрашиваем, хочет ли он попробовать еще раз.
 * Если да, то снова запускаем функцию. Если нет то возвращаем код ошибки ввода.
 * Если считывание прошло успешно, возвращаем значение, деленное на делитель, через параметр и код успешности.
 */
int input_double(double *num, int n, char *key)
{
    char buf[n];
    double a = 0, dot = 1;
    int flag = 0;
    int flag_minus = 0;
    int rc = OK;
    bool yn;
    if (input_string(buf, n, key) != OK)
        return IO_ERR;
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (isdigit(buf[i]) || buf[i] == '.' || buf[i] == '-')
        {
            if (buf[i] == '-')
            {
                if (flag_minus == 0 && i == 0)
                {
                    dot = -1;
                    flag_minus = 1;
                }
                else
                {
                    printf("Invalid input\n");
                    rc = IO_ERR;
                    while (rc != OK)
                        rc = input_bool(&yn, "Want to try again? ");
                    if (yn == true)
                        rc = input_double(num, n, key);
                    if (yn == false)
                        rc = IO_ERR;
                    return rc;
                }

            }
            else if (buf[i] == '.')
            {
                if (flag == 1)
                {
                    printf("Invalid input\n");
                    rc = IO_ERR;
                    while (rc != OK)
                        rc = input_bool(&yn, "Want to try again? ");
                    if (yn == true)
                        rc = input_double(num, n, key);
                    if (yn == false)
                        rc = IO_ERR;
                    return rc;
                }
                else
                    flag = 1;
            }
            else
            {
                if (a != 0)
                    a *= 10;
                a += buf[i] - '0';
                if (flag == 1)
                    dot *= 10;
                if (dot == 100000)
                {
                    printf("Invalid input power\n");
                    rc = IO_ERR;
                    while (rc != OK)
                        rc = input_bool(&yn, "Want to try again? ");
                    if (yn == true)
                        rc = input_double(num, n, key);
                    if (yn == false)
                        rc = IO_ERR;
                    return rc;
                }
            }
        }
        else
        {
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_double(num, n, key);
            if (yn == false)
                rc = IO_ERR;
            return rc;
        }
    }
    a /= dot;
    *num = a;
    return rc;
}

////координатный или в виде матрицы
int coord_usual()
{
    printf("--------------\n1-coordinate\n2-by lines\nChoose the mode: ");
    char c1 = getchar();
    if (c1 == '\n' || c1 == EOF)
    {
        printf("Invalid input\n");

    }
    else
    {
        char c2 = getchar();
        if (c2 == '\n')
        {
            if (c1 == '1' && c2 == '\n')
                return 1;
            else if (c1 == '2' && c2 == '\n')
                return 2;
            else
                printf("Invalid input\n");
        }
        else
        {
            printf("Invalid Input\n");
            clean_stdin();
        }
    }
    return -1;
}

//печать матрицы
void print_matrix(double **mtr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%f ", mtr[i][j]);
        printf("\n");
    }
}

void print_array(double *vector, int m)
{
    for (int i = 0; i < m; i++)
        printf("%lf ", vector[i]);
}
