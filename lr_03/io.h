#ifndef IO_H
#define IO_H

#include <stdbool.h>

void clean_stdin(void);
int input_bool(bool *value, char *key);
int input_string(char *str, int n, char *key);
int input_int(int *num, int n, char *key);
int input_double(double *num, int n, char *key);
void print_matrix(double **mtr, int n, int m);
void print_array(double *vector, int m);
int get_mode(char *valid, char *key);
void print_int_array(int *vector, int m);

#endif // IO_H
