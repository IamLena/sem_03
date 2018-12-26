#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "define.h"
#include "func.h"
#include "queue.h"

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int insert_sorted_array2(line_arr *queue, order element)
{
    int current_length = 1;
    if (queue->len == MAX_LEN)
        return FULL;

    order *cur = queue->pout - 1;
    while((cur + 1) != queue->pin && (cur + 1)->time_arrive <= element.time_arrive)
    {
        current_length++;
        *cur = *(cur + 1);
        cur++;
    }
    *(cur) = element;
    queue->pout -= 1;
    queue->len += 1;
    return current_length;
}

int insert_sorted_list(line_list **queue, order element)
{
    int current_length = 1;
    if ((*queue)->len == MAX_LEN)
        return FULL;
    node_p new = malloc(sizeof(struct node_t));
    if (!new)
        return MEM_ERR;
    new->value = element;

    node_p run = (*queue)->pout;
    node_p prev;
    while (run && (run->value.time_arrive < element.time_arrive))
    {
        current_length++;
        prev = run;
        run = run->next;
    }
    if (run == (*queue)->pout)
    {
        (*queue)->pout = new;
        new->next = run;
    }
    else
    {
        prev->next = new;
        new->next = run;
    }
    (*queue)->len += 1;
    return current_length;
}

line_arr *generate_line_arr(double t1_ot, double t1_do, double t2_ot, double t2_do)
{
    double time = 0;
    line_arr *queue = create_arr();
    order new_order;

    while (queue->len != MAX_LEN)
    {
        new_order.loop = 0;
        if (t1_ot == t1_do)
            new_order.time_interval = t1_ot;
        else
            new_order.time_interval = randfrom(t1_ot, t1_do);
        time += new_order.time_interval;
        if (t2_ot == t2_do)
            new_order.time_processing = t2_ot;
        else
            new_order.time_processing = randfrom(t2_ot, t2_do);
        new_order.time_arrive = time;
        push_arr(&queue, new_order);
    }

    return queue;
}


line_list *generate_line_list(double t1_ot, double t1_do, double t2_ot, double t2_do)
{
    double time = 0;
    line_list *queue = create_list();
    if (queue)
    {
        order new_order;

        while (queue->len != MAX_LEN)
        {
            new_order.loop = 0;
            if (t1_ot == t1_do)
                new_order.time_interval = t1_ot;
            else
                new_order.time_interval = randfrom(t1_ot, t1_do);
            time += new_order.time_interval;
            if (t2_ot == t2_do)
                new_order.time_processing = t2_ot;
            else
                new_order.time_processing = randfrom(t2_ot, t2_do);
            new_order.time_arrive = time;
            push_list(&queue, new_order);
        }
    }
    return queue;
}

double OA_arr(line_arr *queue, int n, int every)
{

    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    int counter = 0;
    int sum_len = 0;
    int code = 0;
    order el;

    while(order_out != n)
    {
        if (pop_arr(queue, &el) != OK)
        {
            printf("empty\n");
            return time;
        }

        if (el.time_arrive - time > 0)
            time_prostoy += el.time_arrive - time;

        if (el.loop == 0)
            input++;

        if (el.time_arrive - time > 0)
            time = el.time_arrive;
        time += el.time_processing;
        el.loop++;
        el.time_arrive = time;
        el.time_interval = 0;

        if (el.loop == 5)
        {
            order_out++;
            memmove(queue->line, queue->pout, queue->len * sizeof(order));
            queue->pout -= 1;
            queue->pin = queue->pout + queue->len;
            if (counter != 0 && order_out % every == 0)
            {
                if (code <= 10)
                {
                    printf("%.2f : %d : OA |%d| : ", time, order_out, el.loop);
                    print_loops_arr(*queue, time);
                }
                printf("%d orders are processed\n", counter);
                printf("line length = %d\n", code);
                printf("average line length = %f\n", sum_len / (double)counter);
                printf("_____________________________\n");

            }
        }
        else
        {
            code = insert_sorted_array2(queue, el);
            if (code == FULL)
            {
                printf("full\n");
                return time;
            }
            else
                sum_len += code;
        }
        counter++;
    }

    while (queue->pout->time_arrive <= time)
    {
        if (queue->pout->loop == 0)
            input++;
        queue->pout++;
    }
    printf("\n__________RESULTS_______________\n");
    printf("|                               |\n");
    printf("|time of working = %lf\t|\n", time);
    printf("|time idle       = %lf\t|\n", time_prostoy);
    printf("|input orders    = %-8d\t|\n", input);
    printf("|output orders   = %-8d\t|\n", order_out);
    printf("|actions         = %-8d\t|\n", counter);
    printf("|_______________________________|\n");

    return time;
}

double OA_list(line_list **queue, int n, int every)
{
    int cur_len = 0;

    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    int counter = 0;
    int sum_len = 0;
    order el;

    while(order_out != n)
    {
        if (pop_list(*queue, &el) != OK)
        {
            printf("empty\n");
            return time;
        }
        if (el.time_arrive - time > 0)
            time_prostoy += el.time_arrive - time;

        if (el.loop == 0)
            input++;

        if (el.time_arrive - time > 0)
            time = el.time_arrive;
        time += el.time_processing;
        el.loop++;
        el.time_arrive = time;
        el.time_interval = 0;

        if (el.loop == 5)
        {
            order_out++;
            if (order_out != 0 && order_out % every == 0)
            {
                if (cur_len <= 10)
                {
                    printf("%.2f : %d : OA |%d| : ", time, order_out, el.loop);
                    print_loops_list(**queue, time);
                }
                printf("%d\n", order_out);
                printf("%d orders are processed\n", counter);
                printf("line length = %d\n", cur_len);
                printf("average line length = %f\n", sum_len / (double)counter);
                printf("_____________________________\n");

            }

        }
        else
        {
            cur_len = insert_sorted_list(queue, el);
            if (cur_len == FULL)
            {
                printf("full\n");
                return time;
            }
            else if (cur_len == MEM_ERR)
            {
                printf("mem_err\n");
                return time;
            }
        }
        sum_len += cur_len;
        counter++;
    }

    while ((*queue)->pout->value.time_arrive <= time)
    {
        if ((*queue)->pout->value.loop == 0)
            input++;
        (*queue)->pout = (*queue)->pout->next;
    }

    printf("\n__________RESULTS_______________\n");
    printf("|                               |\n");
    printf("|time of working = %lf\t|\n", time);
    printf("|time idle       = %lf\t|\n", time_prostoy);
    printf("|input orders    = %-8d\t|\n", input);
    printf("|output orders   = %-8d\t|\n", order_out);
    printf("|actions         = %-8d\t|\n", counter);
    printf("|_______________________________|\n");

    return time;
}


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
    if (i == 0)
        return 5;
    if (i > n)
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
    int res = input_string(buf, n + 1, key);
    if (res == 5)
    {
        printf("default\n");
        return 5;
    }
    else if (res == IO_ERR)
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

int input_double(double *num, int n, char *key)
{
    char buf[n];
    double a = 0, dot = 1;
    int flag = 0;
    int rc = OK;
    bool yn;
    if (input_string(buf, n, key) != OK)
        return IO_ERR;
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (isdigit(buf[i]) || buf[i] == '.' || buf[i] == '-' || buf[i] == '+')
        {
            if (buf[i] == '-')
            {
                if (i == 0)
                    dot = -1;
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
            else if (buf[i] == '+')
            {
                if (i == 0)
                    dot = 1;
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
                if (dot == 10000000)
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
