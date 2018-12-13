#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "define.h"
#include "queue.h"

line_arr *create_arr()
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
int add_el_arr(line_arr *queue, order element)
{
    if (queue == NULL)
        queue = create();
    if (queue == NULL)
        return MEM_ERR;
    if (queue->len == MAX_LEN)
        return FULL;
    *(queue->pin) = element;
    queue->len++;
    queue->pin++;
    if (queue->pin == queue->line + MAX_LEN)
        queue->pin = queue->line;
    return OK;
}
int del_el_arr(line_arr *queue, order *element)
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
    for (int i = 0; i < queue.len; i++)
        printf("%lf ", queue.line[i]);
    printf("\n");

    for (int i = 0; i < queue.len; i++)
    {
        printf("%lf ", *(queue.pout));
        queue.pout++;
        if (queue.pout == queue.line + MAX_LEN)
            queue.pout = queue.line;
    }
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

line_list *create_list()
{
    line_list *new_queue = malloc(sizeof(line_list));
    if (new_queue)
    {
        new_queue->len = 0;
        new_queue->head = NULL;
        new_queue->pin = NULL;
        new_queue->pout = NULL;
    }
    return new_queue;
}
int add_el_list(line_list *queue, order element)
{
    if (queue == NULL)
        queue = create_list();
    if (queue == NULL)
        return MEM_ERR;
    if (queue->len == MAX_LEN)
        return FULL;
    node_p new_el = malloc(sizeof(struct node));
    if (new_el)
    {
        new_el->next = NULL;
        new_el->value = element;
        queue->pin->next = new_el;
        queue->len++;
    }
    return MEM_ERR;
}
int del_el_list(line_list *queue, order *element)
{
    assert(queue);
    assert(element);
    if (queue->len == 0)
        return EMPTY;
    *element = queue->pout->value;
    node_p next = queue->pout->next;
    free(queue->pout);
    queue->pout = next;
    queue->len--;
    return OK;
}
void print_list(line_list queue)
{
    for (int i = 0; i < queue.len; i++)
    {
        printf("%lf ", queue.pout->value);
        queue.pout = queue.pout->next;
    }
    printf("\n");
}
void destroy_list(line_list *queue)
{
    while(queue->head)
    {
        node_p next = queue->head->next;
        free(queue->head);
        queue->head = next;
    }
    queue->head = NULL;
    queue->pin = NULL;
    queue->pout = NULL;
    queue->len = 0;
}
