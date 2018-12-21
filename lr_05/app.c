#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "define.h"
#include "queue.h"
#include "func.h"

int main(void)
{
    srand(time(NULL));

    //input intervals
    int t_interval1 = 0;
    int t_interval2 = 6;
    int t_processing1 = 0;
    int t_processing2 = 1;
    printf("input the interval time of orders\n");
    input_int(&t_interval1, 2, "from: ");
    input_int(&t_interval1, 2, "to: ");
    printf("input the time of processing orders\n");
    input_int(&t_interval1, 2, "from: ");
    input_int(&t_interval1, 2, "to: ");
    if (t_interval1 >= t_interval2)
    {
        t_interval1 = 0;
        t_interval2 = 6;
    }
    if (t_processing1 >= t_processing2)
    {
        t_processing1 = 0;
        t_processing2 = 1;
    }
//    t_interval1 = t_interval2 = 3;
//    t_processing1 = t_processing2 = 0.5;
    printf("input result: t1 = (%d, %d); t2 = (%d, %d)\n", t_interval1, t_interval2, t_processing1, t_processing2);

    //array
    {
        printf("\n--------------------ARRAY---------------\n\n");
        line_arr *queue = generate_line_arr(t_interval1, t_interval2, t_processing1, t_processing2);
        if (queue->len <= 15)
        {
            printf("generated\n");
            print_arr(*queue);
        }
        OA_arr(queue);
        destroy_arr(queue);
    }

    //list
    {
        printf("\n--------------------LIST---------------\n\n");
        line_list *queue = generate_line_list(t_interval1, t_interval2, t_processing1, t_processing2);
        if (queue->len <= 15)
        {
            printf("generated\n");
            //print_list(*queue);
        }
        OA_list(&queue);
        destroy_list(queue);
    }
    return 0;
}
