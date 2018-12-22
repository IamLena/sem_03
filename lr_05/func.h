#ifndef FUNC_H
#define FUNC_H

#include "queue.h"
#include <stdbool.h>


order *next_pointer(line_arr *queue, order *pointer);

order *prev_pointer(line_arr *queue, order *pointer);
int insert_sorted_array(line_arr *queue, order element);
int insert_sorted_array2(line_arr *queue, order element);

line_arr *generate_line_arr(double t1_ot, double t1_do, double t2_ot, double t2_do);
line_list *generate_line_list(double t1_ot, double t1_do, double t2_ot, double t2_do);

double OA_arr(line_arr *queue, int n, int every);
double  OA_list(line_list **queue, int n, int every);

void clean_stdin(void);
int input_bool(bool *value, char *key);
int input_string(char *str, int n, char *key);
int input_int(int *num, int n, char *key);
int input_double(double *num, int n, char *key);

#endif //FUNC_H
