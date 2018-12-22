#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "define.h"
#include "queue.h"
#include "func.h"

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

int get_mode(char *valid, char *key)
{
    printf("%s ", key);
    char c1 = getchar();
    if (c1 == '\n' || c1 == EOF)
    {
        printf("Invalid input\n");

    }
    else
    {
        char c2 = getchar();
        if (c2 == '\n')
        {
            if (strchr(valid, c1) != NULL)
                return (c1 - '0');
            else
                printf("Invalid input\n");
        }
        else
        {
            printf("Invalid Input\n");
            clean_stdin();
        }
    }
    return get_mode(valid, key);
}

int menu(void)
{
    printf("_________________________________________________________________________________\n");
    printf("\t\t\t\tMENU\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("1) change interval and processing time ranges of orders\n");
    printf("2) change quantity of out orders and frequency of showing information about length\n");
    printf("3) 100%% precision results of modeling\n");
    printf("4) modeling #1, array\n");
    printf("5) nodeling #2, list\n");
    printf("6) exit\n");
    printf("_________________________________________________________________________________\n");
    //printf("input the option: \n");
    int mode = get_mode("123456", "input the option");
    return mode;
}

double estimate(double t_interval1, double t_interval2, double t_processing1, double t_processing2, int n)
{
    double t1 = (t_interval1 + t_interval2)/2;
    double t2 = (t_processing1 + t_processing2)/2;
    line_arr *queue = generate_line_arr(t1, t1, t2, t2);
    double estimated = OA_arr(queue, n, 10 * n);
    destroy_arr(queue);
    return estimated;
}

int main(void)
{
    int option = 7;

    double t_interval1 = 0;
    double t_interval2 = 6;
    double t_processing1 = 0;
    double t_processing2 = 1;
    int n = 1000;
    int every = 100;

    double estimated = -1;
    double time;
    unsigned long t1, t2;

    while (option != 6)
    {
        printf("\n _____________VALUES___________\n");
        printf("|time_interval (%.2f, %.2f)    |\n|time_processing (%.2f, %.2f)  |\n", t_interval1, t_interval2, t_processing1, t_processing2);
        printf("|%d out orders\t       |\n|every %d of actions show info|\n", n, every);
        printf("|______________________________|\n");
        option = menu();

        if (option == 1)
        {
            printf("input the interval time of orders\n");
            input_double(&t_interval1, 2, "from: ");
            input_double(&t_interval2, 2, "to: ");
            printf("input the time of processing orders\n");
            input_double(&t_processing1, 2, "from: ");
            input_double(&t_processing2, 2, "to: ");
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
            estimated = -1;
        }
        else if (option == 2)
        {
            input_int(&n, 4, "input the number of out orders: ");
            input_int(&every, 4, "input frequency of showing information about length: ");

            if (n <= 0 || every <= 0)
            {
                n = 1000;
                every = 100;
            }
            estimated = -1;
        }
        else if (option == 3)
        {
            estimated = estimate(t_interval1, t_interval2, t_processing1, t_processing2, n);
        }
        else if (option == 4)
        {
            if (estimated == -1)
                estimated = estimate(t_interval1, t_interval2, t_processing1, t_processing2, n);
            printf("\n--------------------ARRAY---------------\n");
            line_arr *queue = generate_line_arr(t_interval1, t_interval2, t_processing1, t_processing2);
            t1 = tick();
            time = OA_arr(queue, n, every);
            t2 = tick();
            printf("precision - %f%%\n", abs(estimated - time)/estimated * 100);
            printf("time ticks = %lu\n", t2 - t1);
            destroy_arr(queue);
        }
        else if (option == 5)
        {
            if (estimated == -1)
                estimated = estimate(t_interval1, t_interval2, t_processing1, t_processing2, n);
            printf("\n--------------------LIST---------------\n");
            line_list *queue = generate_line_list(t_interval1, t_interval2, t_processing1, t_processing2);
            t1 = tick();
            time = OA_list(&queue, n, every);
            t2 = tick();
            printf("precision - %f%%\n", abs(estimated - time)/estimated * 100);
            printf("time ticks = %lu\n", t2 - t1);
            destroy_list(queue);
        }
    }

    printf("exiting the programm\n");
    return 0;
}
