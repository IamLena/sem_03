#include <stdio.h>
#include "define.h"
#include "queue.h"
#include "func.h"

int main(void)
{
    //array
    {
        printf("\narray\n");
        /*
        line_arr *queue1 = create_arr();
        order element;
        push_arr(&queue1, element);
        printf("line pusehed\n");
        print_arr(*queue1);
        pop_arr(queue1, &element);
        printf("line poped\n");
        print_arr(*queue1);
        printf("an element\n");
        print_order(element);
        */
        generate_line_arr();

    }

    //list
    {
        printf("\nlist\n");
        line_list *queue2 = create_list();
        order element;
        push_list(&queue2, element);
        printf("line pusehed\n");
        print_list(*queue2);
        pop_list(queue2, &element);
        printf("line poped\n");
        print_list(*queue2);
        printf("an element\n");
        print_order(element);
    }

    return 0;
}
