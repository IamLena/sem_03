#ifndef INPUT_H
#define INPUT_H

void clean_stdin(void);
int input_bool(bool *value, char *key);
int input_action(void);
int input_string(char *str, int n, char *key);
int input_float(float *num, int n, char *key);
int input_si(short int* num, int n, char *key);
int input_int(int *num, int n, char *key);
int add_line(struct flat_t*flats, int length);

#endif // INPUT_H
