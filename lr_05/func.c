#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "define.h"
#include "func.h"
#include "queue.h"

double randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

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

    print_arr(*queue);
    return queue;

}


line_list *generate_line_list(void);

void OA_arr(line_arr *queue);
void  OA_list(line_list *queue);
