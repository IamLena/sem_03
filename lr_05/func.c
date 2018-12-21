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

order *next_pointer(line_arr *queue, order *pointer)
{
    if (pointer == queue->line + MAX_LEN)
        return queue->line;
    return pointer + 1;
}

order *prev_pointer(line_arr *queue, order *pointer)
{
    if (pointer == queue->line)
        return queue->line + MAX_LEN - 1;
    return pointer - 1;
}

//исправить в принципе реализвацию.
// так долго, много операций.
int insert_sorted_array(line_arr *queue, order element)
{
    if (queue->len == MAX_LEN)
        return FULL;
    if (queue->len == 0)
    {
        *(queue->pin) = element;
        queue->len++;
        queue->pout = queue->pin;
        queue->pin = next_pointer(queue, queue->pin);
        return OK;
    }
    order *run = prev_pointer(queue, queue->pout);
    order *next = queue->pout;
    queue->pout -= 1;

    while(run != queue->pout && next->time_arrive <= element.time_arrive)
    {
        printf("%lf vs %lf\n",  next->time_arrive, element.time_arrive);
        print_order(*next);
        *run = *next;
        run = next_pointer(queue, run);
        next = next_pointer(queue, next);
    }
    *run = element;
    queue->len += 1;
    return OK;
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

line_arr *generate_line_arr(int t1_ot, int t1_do, int t2_ot, int t2_do)
{
    double time = 0;
    line_arr *queue = create_arr();
    order new_order;

    while (queue->len != MAX_LEN)
    {
        new_order.loop = 0;
        new_order.time_interval = randfrom(t1_ot, t1_do);
        time += new_order.time_interval;
        new_order.time_processing = randfrom(t2_ot, t2_do);
        new_order.time_arrive = time;
        push_arr(&queue, new_order);
    }
    return queue;
}


line_list *generate_line_list(int t1_ot, int t1_do, int t2_ot, int t2_do)
{
    double time = 0;
    line_list *queue = create_list();
    if (queue)
    {
        order new_order;

        while (queue->len != MAX_LEN)
        {
            new_order.loop = 0;
            new_order.time_interval = randfrom(t1_ot, t1_do);
            time += new_order.time_interval;
            new_order.time_processing = randfrom(t2_ot, t2_do);
            new_order.time_arrive = time;
            push_list(&queue, new_order);
        }
    }
    return queue;
}

void OA_arr(line_arr *queue)
{
    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    int counter = 0;
    int sum_len = 0;
    int code;
    order el;

    while(order_out != N)
    {
        if (pop_arr(queue, &el) != OK)
        {
            printf("empty\n");
            return;
        }
        if (el.time_arrive - time > 0)
            time_prostoy += el.time_arrive - time;

        if (el.loop == 0)
            input++;

        time += el.time_interval;
        time += el.time_processing;
        el.loop++;
        el.time_arrive = time;
        el.time_interval = 0;
//        el.time_arrive = time + el.time_interval;

        if (el.loop == 5)
        {
            order_out++;
            memmove(queue->line, queue->pout, queue->len * sizeof(order));
            queue->pout -= 1;
            queue->pin = queue->pout + queue->len;
            //printf("\nout\n");
            //print_arr(*queue);

        }
        else
        {
            //int code = insert_sorted_array(queue, el);
            code = insert_sorted_array2(queue, el);
            //print_arr(*queue);
            if (code == FULL)
            {
                printf("full\n");
                return;
            }
            else
                sum_len += code;
        }
        //sum_len += queue->len;
        counter++;
        if (counter != 0 && counter % EVERY == 0)
        {
            printf("%d orders are processed\n", counter);
            printf("line length = %d\n", code);
            printf("average line length = %f\n", sum_len / (double)counter);
            printf("_____________________________\n");
            //print_arr(*queue);
        }
    }

    printf("\n__________RESULTS_______________\n");
    printf("|                               |\n");
    printf("|time of working = %lf\t|\n", time);
    printf("|time prostoy    = %lf\t|\n", time_prostoy);
    printf("|input orders    = %-8d\t|\n", input);
    printf("|output orders   = %-8d\t|\n", order_out);
    printf("|actions         = %-8d\t|\n", counter);
    printf("|time / average  = %-8f\t|\n", (time / 3.0));
    printf("|_______________________________|\n");
}

void  OA_list(line_list **queue)
{
    int cur_len;

    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    int counter = 0;
    int sum_len = 0;
    order el;

    while(order_out != N)
    {
        if (pop_list(*queue, &el) != OK)
        {
            printf("empty\n");
            return;
        }
        if (el.time_arrive - time > 0)
            time_prostoy += el.time_arrive - time;

        if (el.loop == 0)
            input++;

        time += el.time_interval;
        time += el.time_processing;
        el.loop++;
        el.time_arrive = time;
        el.time_interval = 0;

        if (el.loop == 5)
            order_out++;
        else
        {
            cur_len = insert_sorted_list(queue, el);
        }
        sum_len += cur_len;
        counter++;
        if (counter != 0 && counter % EVERY == 0)
        {
            printf("%d orders are processed\n", counter);
            printf("line length = %d\n", cur_len);
            printf("average line length = %f\n", sum_len / (double)counter);
            printf("_____________________________\n");
        }
    }

    printf("\n__________RESULTS_______________\n");
    printf("|                               |\n");
    printf("|time of working = %lf\t|\n", time);
    printf("|time prostoy    = %lf\t|\n", time_prostoy);
    printf("|input orders    = %-8d\t|\n", input);
    printf("|output orders   = %-8d\t|\n", order_out);
    printf("|actions         = %-8d\t|\n", counter);
    printf("|time / average  = %-8f\t|\n", (time / 3.0));
    printf("|_______________________________|\n");
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

void OA_arr2(void)
{
    line_arr *queue = create_arr();

    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    int counter = 0;
    int sum_len = 0;
    int code;
    order el;

    while(order_out != N)
    {
        if (pop_arr(queue, &el) != OK)
        {
            printf("empty\n");
            return;
        }
        if (el.time_arrive - time > 0)
            time_prostoy += el.time_arrive - time;

        if (el.loop == 0)
            input++;

        time += el.time_interval;
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
            //printf("\nout\n");
            //print_arr(*queue);

        }
        else
        {
            //int code = insert_sorted_array(queue, el);
            code = insert_sorted_array2(queue, el);
            //print_arr(*queue);
            if (code == FULL)
            {
                printf("full\n");
                return;
            }
            else
                sum_len += code;
        }
        //sum_len += queue->len;
        counter++;
        if (counter != 0 && counter % EVERY == 0)
        {
            //print_arr(*queue);
            printf("%d orders are processed\n", counter);
            printf("line length = %d\n", code);
            printf("average line length = %f\n", sum_len / (double)counter);
        }
    }

    printf("\n__________RESULTS_______________\n");
    printf("|                               |\n");
    printf("|time of working = %lf\t|\n", time);
    printf("|time prostoy    = %lf\t|\n", time_prostoy);
    printf("|input orders    = %-8d\t|\n", input);
    printf("|output orders   = %-8d\t|\n", order_out);
    printf("|actions         = %-8d\t|\n", counter);
    printf("|_______________________________|\n");
}
