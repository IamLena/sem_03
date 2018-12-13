#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

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

int insert_sorted_array(line_arr *queue, order element)
{
    if (queue->len == MAX_LEN)
        return FULL;
    order *run = prev_pointer(queue, queue->pout);
    order *next = queue->pout;
    queue->pout -= 1;

    while(run != queue->pout && next->time_arrive <= element.time_arrive)
    {
        //printf("%lf vs %lf\n",  next->time_arrive, element.time_arrive);
        //print_order(*next);
        *run = *next;
        run = next_pointer(queue, run);
        next = next_pointer(queue, next);
    }
    *run = element;
    queue->len += 1;
    return OK;
}

//int insert_sorted_list()
//{

//}

line_arr *generate_line_arr(void)
{
    double time = 0;
    line_arr *queue = create_arr();
    order new_order;

    while (queue->len != MAX_LEN)
    {
        new_order.loop = 0;
        new_order.time_interval = randfrom(0, 6);
        time += new_order.time_interval;
        new_order.time_processing = randfrom(0, 1);
        new_order.time_arrive = time;
        push_arr(&queue, new_order);
    }
    return queue;
}


line_list *generate_line_list(void)
{
    double time = 0;
    line_list *queue = create_list();
    order new_order;

    while (queue->len != MAX_LEN)
    {
        new_order.loop = 0;
        new_order.time_interval = randfrom(0, 6);
        time += new_order.time_interval;
        new_order.time_processing = randfrom(0, 1);
        new_order.time_arrive = time;
        push_list(&queue, new_order);
    }
    return queue;
}

void OA_arr(line_arr *queue)
{
    double time = 0;
    double time_prostoy = 0;

    int order_out = 0;
    int input = 0;
    order el;

    while(order_out != N)
    {
//        if (order_out == EVERY)
//        {
//            printf("line:\n");
//            print_arr(*queue);
//            printf("time of working = %lf\n", time);
//            printf("time prostoy = %lf\n", time_prostoy);
//        }
        if (pop_arr(queue, &el) != OK)
        {
            printf("empty\n");
            return;
        }
        printf("popped\n");
        print_arr(*queue);
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
            printf("pushing this one:\n");
            print_order(el);
            insert_sorted_array(queue, el);
        }
        printf("__________________\n");
        print_arr(*queue);
        printf("time of working = %lf\n", time);
        printf("time prostoy = %lf\n", time_prostoy);
        printf("input orders = %d\n", input);
        printf("out = %d\n", order_out);
    }

    printf("__________RESULT___________\n");
    printf("time of working = %lf\n", time);
    printf("time prostoy = %lf\n", time_prostoy);
    printf("input orders = %d\n", input);
}

void  OA_list(line_list *queue);
