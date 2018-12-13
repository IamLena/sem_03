#include <stdio.h>
#include "define.h"
#include "queue.h"
#include "func.h"

int main(void)
{
    //array
    {
        printf("\narray\n");

        /*line_arr *queue1 = create_arr();
        order element;
        while (queue1->len != MAX_LEN)
        {
            push_arr(&queue1, element);
            printf("line pusehed\n");
            print_arr(*queue1);
        }
        while (queue1->len != 0)
        {
            pop_arr(queue1, &element);
            printf("line poped\n");
            print_arr(*queue1);
            printf("an element\n");
            print_order(element);
        }*/
        //order el;
        line_arr *queue = generate_line_arr();
        /*pop_arr(queue, &el);
        printf("here\n");
        print_arr(*queue);
        printf("there\n");


        order element;
        element.time_arrive = 4;
        print_order(element);
        printf("\n______________\n");
        insert_sorted_array(queue, element);*/
        print_arr(*queue);
        OA_arr(queue);

    }

    //list
    {
        printf("\nlist\n");
        /*line_list *queue2 = create_list();
        order element;
        push_list(&queue2, element);
        printf("line pusehed\n");
        print_list(*queue2);
        pop_list(queue2, &element);
        printf("line poped\n");
        print_list(*queue2);
        printf("an element\n");
        print_order(element);*/
        //generate_line_list();
    }

    return 0;
}
