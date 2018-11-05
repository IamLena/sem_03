#ifndef OUTPUT_H
#define OUTPUT_H

void print_line(struct flat_t flat);
void print_head(void);
int print_table(struct flat_t *flats, int length);
void print_keys (k_el *table, int length);

#endif // OUTPUT_H
