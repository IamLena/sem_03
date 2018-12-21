#ifndef FUNC_H
#define FUNC_H

#include "queue.h"
#include <stdbool.h>


order *next_pointer(line_arr *queue, order *pointer);

order *prev_pointer(line_arr *queue, order *pointer);
int insert_sorted_array(line_arr *queue, order element);
int insert_sorted_array2(line_arr *queue, order element);

line_arr *generate_line_arr(int t1_ot, int t1_do, int t2_ot, int t2_do);
line_list *generate_line_list(int t1_ot, int t1_do, int t2_ot, int t2_do);

void OA_arr(line_arr *queue);
void  OA_list(line_list **queue);

void clean_stdin(void);
int input_bool(bool *value, char *key);
int input_string(char *str, int n, char *key);
int input_int(int *num, int n, char *key);

#endif //FUNC_H
