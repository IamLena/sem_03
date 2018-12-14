#ifndef FUNC_H
#define FUNC_H

#include "queue.h"


order *next_pointer(line_arr *queue, order *pointer);

order *prev_pointer(line_arr *queue, order *pointer);
int insert_sorted_array(line_arr *queue, order element);

line_arr *generate_line_arr(void);
line_list *generate_line_list(void);

void OA_arr(line_arr *queue);
void  OA_list(line_list **queue);

#endif //FUNC_H
