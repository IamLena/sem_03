#include "derectives.h"
#include "input.h"

/**
 * @brief clean_stdin
 * очищает поток ввода
 */
void clean_stdin(void)
{
    //printf("clearing! ");
    char c = 'a';
    while (c != '\n' && c != EOF)
    {
        c = getchar();
        //printf("%c", c);
    }
    //printf("\n");
}

/**
 * @brief input_bool обрабатывает ввод логического значения
 * @param value логическая переменная, в которую сохранится ввод
 * @param key строка-выражение, пояснение к вводу
 * @return код ошибки
 * выводит на экран переданное сообщение, получает ввод
 * если строка равна "y" логическая переменная равно true
 * если строка равна "n" логическая переменная принимает значение false
 * иначе программа очищает поток ввода и возвращает код ошибки ввода
 */
int input_bool(bool *value, char *key)
{
    printf("%s ", key);
    printf("y/n: ");
    bool tmp;
    char c;
    int rc = OK;
    c = getchar();
    if (c != EOF && c != '\n')
    {
        if (c == 'y' || c == 'Y')
            tmp =  true;
        else if (c == 'n' || c == 'N')
            tmp = false;
        else
            rc = IO_ERR;

        if (((c = getchar()) == '\n'))
        {
            if (rc == OK)
                *value = tmp;
        }
        else
        {
            clean_stdin();
            rc =  IO_ERR;
        }
    }
    else
        rc = IO_ERR;
    return rc;
}

/**
 * @brief input_action Обрабатывает ввод пункта меню
 * @return код операции
 */
int input_action(void)
{
    int act;
    char c, c2, c3;
    printf("chose an action (input the number): ");
    c = getchar();
    if (c != EOF && c != '\n')
    {
        if (isdigit(c) && c != '0')
        {
            c2 = getchar();
            if (c == '1')
            {
                if (c2 == '\n')
                    act = ACTION_1;
                else
                {
                    c3 = getchar();
                    if (c2 == '0' && c3 == '\n')
                        act = ACTION_10;
                    else if (c2 == '1' && c3 == '\n')
                        act = ACTION_11;
                    else if (c2 == '2' && c3 == '\n')
                        act = ACTION_12;
                    else
                        if (c3 != '\n')
                            act = IO_ERR;
                }
            }
            else if (c == '2' && c2 == '\n')
                act = ACTION_2;
            else if (c == '3' && c2 == '\n')
                act = ACTION_3;
            else if (c == '4' && c2 == '\n')
                act = ACTION_4;
            else if (c == '5' && c2 == '\n')
                act = ACTION_5;
            else if (c == '6' && c2 == '\n')
                act = ACTION_6;
            else if (c == '7' && c2 == '\n')
                act = ACTION_7;
            else if (c == '8' && c2 == '\n')
                act = ACTION_8;
            else if (c == '9' && c2 == '\n')
                act = ACTION_9;
            else
                act = IO_ERR;
        }
        else
            act = IO_ERR;
        if (act == IO_ERR)
            clean_stdin();
    }
    else
        act = IO_ERR;
    return act;
}

/**
 * @brief input_string ввод строки
 * @param str строка, полученная в результате чтения
 * @param n длина строки
 * @param key выражение, пояснение к вводу
 * @return код ошибки
 * считывание посимвольно до конца ввода, увеличивается переменная индекса,
 * если индекс в результате равен нулю или больше длины - сообщаем пользователю,
 * что ввод пустой или превышает допустимое количество символов.
 * Спрашиваем у пользователя хочет ли он попробовать еще, до тех пор пока он не ответить да или нет
 * если да - вызываем функцию ввода еще раз
 * если нет - возвращаем код ошибки ввода
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
            str[i++] = c;
    }
    str[i] = '\0';
    if (i > n || i == 0)
    {
        printf("Empty input or reached the maximum size of holder\n");
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
 * @brief input_float ввод вещественного числа
 * @param size
 * @param key
 * @return
 */
int input_float(float *size, char *key)
{
    printf("%s", key);
    int rc = OK;
    float tmp;
    bool yn;
    if (scanf("%f", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_float(size, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if (tmp <= 0)
        {
            printf("<=0\n");
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_float(size, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *size = tmp;
            clean_stdin();
        }
    }
    return rc;
}

int input_si(short int *a, char *key)
{
    bool yn;
    printf("%s", key);
    int rc = OK;
    short int tmp;
    if (scanf("%hi", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_si(a, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if(!(0 < tmp && tmp <= 32767))
        {
            printf("<=0\n");
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_si(a, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *a = tmp;
            clean_stdin();
        }
    }
    return rc;
}

int input_int(int* a, char *key)
{
    bool yn;
    printf("%s", key);
    int rc = OK;
    int tmp;
    if (scanf("%d", &tmp) != 1)
    {
        clean_stdin();
        printf("Invalid input\n");
        rc = IO_ERR;
        while (rc != OK)
            rc = input_bool(&yn, "Want to try again? ");
        if (yn == true)
            rc = input_int(a, key);
        if (yn == false)
            rc = IO_ERR;
    }
    else
    {
        if (tmp < 0 || tmp > 4294967295)
        {
            clean_stdin();
            printf("Invalid input\n");
            rc = IO_ERR;
            while (rc != OK)
                rc = input_bool(&yn, "Want to try again? ");
            if (yn == true)
                rc = input_int(a, key);
            if (yn == false)
                rc = IO_ERR;
        }
        else
        {
            *a = tmp;
            clean_stdin();
        }
    }
    return rc;
}
