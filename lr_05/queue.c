#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "define.h"
#include "queue.h"

void print_order(order el)
{
    printf("loop - %d\n", el.loop);
    printf("interval - %lf\n", el.time_interval);
    printf("arrived - %lf\n", el.time_arrive);
    printf("processing - %lf\n", el.time_processing);
}

line_arr *create_arr(void)
{
    line_arr *new_queue = malloc(sizeof(line_arr));
    if (new_queue)
    {
        new_queue->len = 0;
        new_queue->pin = new_queue->line;
        new_queue->pout = new_queue->line;
    }
    return new_queue;
}
int push_arr(line_arr **queue, order element)
{
    //print_order(element);
    if (*queue == NULL)
        *queue = create_arr();
    if (*queue == NULL)
        return MEM_ERR;
    if ((*queue)->len == MAX_LEN)
        return FULL;
    *((*queue)->pin) = element;
    (*queue)->len++;
    (*queue)->pin++;
    if ((*queue)->pin == (*queue)->line + MAX_LEN)
        (*queue)->pin = (*queue)->line;
    return OK;
}
int pop_arr(line_arr *queue, order *element)
{
    assert(queue);
    assert(element);
    if (queue->len == 0)
        return EMPTY;
    *element = *(queue->pout);
    queue->len--;
    queue->pout++;
    if (queue->pout == queue->line + MAX_LEN)
        queue->pout = queue->line;
    return OK;
}
void print_arr(line_arr queue)
{
    /*for (int i = 0; i < MAX_LEN; i++)
        print_order(queue.line[i]);
        //printf("%lf ", queue.line[i]);
    printf("\n");*/

    for (int i = 0; i < queue.len; i++)
    {
        print_order(*(queue.pout));
        //printf("%lf ", *(queue.pout));
        queue.pout++;
        if (queue.pout == queue.line + MAX_LEN)
            queue.pout = queue.line;
    }
    printf("\n----------------------------\n");
}

void print_loops_arr(line_arr queue, double time)
{
    int count = 0;
    int count_zeros = 0;
    float sum = 0;
    float sum_todo = 0;

    int count_ones = 0;
    int count_twos = 0;
    int count_threes = 0;
    int count_fours = 0;

    while (queue.pout->time_arrive <= time)
    //while(queue.pout->time_arrive <= time && queue.pout->loop < 4)
    {

        sum_todo += ((5 - queue.pout->loop) * 0.5);
         if (queue.pout->loop == 0)
             count_zeros += 1;
         else if (queue.pout->loop == 1)
             count_ones += 1;
         else if (queue.pout->loop == 2)
             count_twos += 1;
         else if (queue.pout->loop == 3)
             count_threes += 1;
         else if (queue.pout->loop == 4)
             count_fours += 1;
         sum += queue.pout->loop * 0.5;
         count++;
         printf("%d ", queue.pout->loop);

        queue.pout++;
//        if (queue.pout == queue.line + MAX_LEN)
//            queue.pout = queue.line;
    }
    printf(":%d", count);
//    printf("| %d ", count_zeros);
//    printf("| %d ", count_ones);
//    printf("| %d ", count_twos);
//    printf("| %d ", count_threes);
//    printf("| %d ", count_fours);
//    printf("| %.1f ", sum);
//    printf("| %.1f ", sum_todo);
//    printf("| %.1f ", sum_todo / sum);
    printf("\n");
}

void destroy_arr(line_arr *queue)
{
    queue->len = 0;
    queue->pin = NULL;
    queue->pout = NULL;
    free(queue);
    queue = NULL;
}

line_list *create_list(void)
{
    line_list *new_queue = malloc(sizeof(line_list));
    if (new_queue)
    {
        new_queue->len = 0;
        //new_queue->head = NULL;
        new_queue->pin = NULL;
        new_queue->pout = NULL;
    }
    return new_queue;
}
int push_list(line_list **queue, order element)
{
    if (*queue == NULL)
        *queue = create_list();
    if (*queue == NULL)
        return MEM_ERR;
    if ((*queue)->len == MAX_LEN)
        return FULL;
    node_p new_el = malloc(sizeof(struct node_t));
    if (new_el)
    {
        new_el->next = NULL;
        new_el->value = element;
        if ((*queue)->pin == NULL)
        {
            //(*queue)->head = new_el;
            (*queue)->pin = new_el;
            (*queue)->pout = new_el;
        }
        else
        {
            (*queue)->pin->next = new_el;
            (*queue)->pin = (*queue)->pin->next;
        }
        (*queue)->len++;
    }
    return MEM_ERR;
}
int pop_list (line_list *queue, order *element)
{
    assert(queue);
    assert(element);
    if (queue->len == 0)
        return EMPTY;
    *element = queue->pout->value;
    node_p next = queue->pout->next;
    free(queue->pout);//memory error
    queue->pout = next;
    queue->len--;
    return OK;
}
void print_list(line_list queue)
{
    for (int i = 0; i < queue.len; i++)
    {
        print_order(queue.pout->value);
        //printf("%lf ", queue.pout->value);
        queue.pout = queue.pout->next;
    }
    printf("\n_______________________\n");
}

void print_loops_list(line_list queue, double time)
{
    while (queue.pout->value.time_arrive <= time)
    {
        printf ("%d ", queue.pout->value.loop);
        queue.pout = queue.pout->next;
    }
    printf("\n");
}

void destroy_list(line_list *queue)
{
    while(queue->pout)
    {
        node_p next = queue->pout->next;
        free(queue->pout);
        queue->pout = next;
    }
    //queue->head = NULL;
    queue->pin = NULL;
    queue->pout = NULL;
    queue->len = 0;
    free(queue);
}
