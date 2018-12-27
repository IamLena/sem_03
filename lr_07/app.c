#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define OK 0
#define PARAM_ERR 1
#define READ_ERR 2
#define MEM_ERR 3

unsigned long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

// в файле количество вершин и ребра в виде (v1, v2)
int read_graph(FILE *f, int **graph, int *n)
{
    if (graph == NULL || n == NULL)
    {
        printf("param err in read\n");
        return PARAM_ERR;
    }
    if (fscanf(f, "%d", n) != 1)
    {
        printf("invalid number of vertex\n");
        return READ_ERR;
    }
    if (*n <= 0)
    {
        printf("invalid number of vertex\n");
        return READ_ERR;
    }
    *graph = calloc((*n) * (*n), sizeof(int));
    if (!graph)
    {
        printf("mem_err in read\n");
        return MEM_ERR;
    }

    int v1, v2;
    while (fscanf(f, "%d%d", &v1, &v2) == 2)
    {
        if (v1 <= 0 || v1 > *n || v2 <= 0 || v2 > *n)
        {
            free(*graph);
            printf("invalid edges\n");
            return READ_ERR;
        }
        *(*graph + (*n) * (v1 -1) + (v2 - 1)) = 1;
        *(*graph + (*n) * (v2 -1) + (v1 - 1)) = 1;
    }
    return OK;
}

void print_matrix(int *matr, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", matr[n * i + j]);
        printf("\n");
    }
}

// запись отношений между вершинами графа в файл для графического представления
void to_dot(FILE *f, int *matr, int n)
{
    fprintf(f, "graph %s {\n", "pic");
    for (int i = 0; i < n; i++)
    {
        if (matr[i * n + i] == 1)
        {
            fprintf(f, "%d -- %d;\n", i + 1, i + 1);
        }
        for (int j = i + 1; j < n; j++)
        {
            if (matr[i * n + j] == 1)
            {
                fprintf(f, "%d -- %d;\n", i + 1, j + 1);
            }
        }
    }
    fprintf(f, "}\n");
}

// поиск в глубину для проверки на связность
void dfs(int v, int *matr, int *arr, int n)
{
    arr[v] = 1;

    for (int i = 0; i < n; i++)
    {
        if (matr[v * n + i] == 1 && arr[i] == 0)
            dfs(i, matr, arr, n);
    }
}

// проверка на дерево
int istree(int *matr, int n, int del)
{
  int edges = 0;
  int flag = 0;
  for (int i = 0; i < n; i++)
  {
      if (matr[i * n + i] == 1)
      {
          //петля
          flag = 1;
      }
      //подсчет ребер графа (если не равен
      for (int j = i + 1; j < n; j++)
      {
          if (matr[i * n + j] == 1)
          {
              edges++;
          }
      }
  }
  if (flag)
      return 0;
  if (edges != n - 2)
  {
      return 0;
  }
  int arr[n];
  memset(arr, 0, sizeof(arr));
  arr[del] = 1;
  dfs(0, matr, arr, n);
  for (int i = 0; i < n; i++)
  {
      if (!arr[i])
      {
          return 0;
      }
  }
  return 1;
}

// решение поставленной задачи
int process(int *matr, int n, int **tree)
{
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        //удаление одной вершины соответствующие столбец и строка = -1
        for (int j = 0; j < n; j++)
        {
            if (matr[i * n + j] == 1)
                matr[i * n + j] = matr[j * n + i] = -1;
        }
        if (istree(matr, n, i))
        {
            *tree = calloc(n * n, sizeof(int));
            assert(tree);
            for (int i = 0; i < n * n; i++)
                if (matr[i] == 1)
                    (*tree)[i] = 1;
            flag = 1;
        }

        for (int j = 0; j < n; j++)
        {
            if (matr[i * n + j] == -1)
                matr[i * n + j] = matr[j * n + i] = 1;
        }
        if (flag)
            return i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned long t1, t2;
    if (argc != 2)
    {
        printf("app.exe in.txt");
        return PARAM_ERR;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f)
    {
        printf("Can not open the file");
        return PARAM_ERR;
    }

    // матрица смежности графа
    t1 = tick();
    int *graph;
    int n;
    int rc = read_graph(f, &graph, &n);
    if (rc == OK)
    {
        printf("your graph:\n");
        print_matrix(graph, n);
        printf("\n");

        FILE *graph_file = fopen("graph.gv", "w");
        to_dot(graph_file, graph, n);
        printf("the graph is drawn in graph.gv\n");
        fclose(graph_file);

        int *tree = NULL;
        int v = process(graph, n, &tree);
        if (v)
        {
            printf("\nGraph CAN be transformed to the tree by deleting the %d vertex with its edges.\n\n", v + 1);
            FILE *tree_file = fopen("tree.gv", "w");
            to_dot(tree_file, tree, n);
            printf("the tree is drawn in tree.gv\n");
            fclose(tree_file);
            free(tree);
         }
         else
            printf("\nGraph CAN'T be transformed to the tree by deleting some vertex with its edges.\n\n");
     }
    free(graph);
    fclose(f);
    t2 = tick();
    printf("\ntime of working = %lu\n", t2 - t1);
    printf("memory: graph = %d",4 * n * n);
    return OK;
}
