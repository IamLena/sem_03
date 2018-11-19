#ifndef FILE_H
#define FILE_H

int get_file(FILE **f);
int read_matrix_lines(FILE *f, double ***pmtr, int *pn, int *pm);
double **read_matrix_coord(FILE *f, int *n, int *m, int *rc);

double *read_vector_coord(FILE *f, int *n, int *rc);
int read_vector_lines(FILE *f, double **pvector, int *pn);

#endif // FILE_H
