#ifndef QUEUE_H
#define QUEUE_H

#include "define.h"
#include "queue.h"

typedef struct order_t order;
typedef struct line_arr_t line_arr;

typedef struct node_t* node_p;
typedef struct line_list_t line_list;

//array
struct order_t
{
    double time_interval;
    double time_arrive;
    double time_processing;
    int loop;
};

struct line_arr_t
{
    order line[MAX_LEN];
    order *pin;
    order *pout;
    int len;
};


struct node_t
{
    order value;
    struct node_t *next;
};

//list
struct line_list_t
{
    //node_p head;
    node_p pin;
    node_p pout;
    int len;
};

//array_funcs
line_arr *create_arr(void);
int push_arr(line_arr **queue, order element);
int pop_arr(line_arr *queue, order *element);
void print_arr(line_arr queue);
void destroy_arr(line_arr *queue);

//list_funcs
line_list *create_list(void);
int push_list(line_list **queue, order element);
int pop_list(line_list *queue, order *element);
void print_list(line_list queue);
void destroy_list(line_list *queue);

void print_order(order el);

#endif // QUEUE_H
