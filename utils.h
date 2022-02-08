#ifndef _UTILS_H_
#define _UTILS_H_

//Definire structurilor necesare pentru graful orientat
typedef struct node
{
    int v;
    struct node *next;
} TNode, *ATNode;

typedef struct
{
    int nn;
    ATNode *adl;
} TGraphL;

TGraphL *create_graph();
void alloc_list(TGraphL *G, int n);
void destroy_graf(TGraphL *G);
void insert_adiacency(TGraphL *G, int v1, int v2);
int find_index(char **nodes, char *node_name, int n);
void afisare_lista_adiacenta(TGraphL *G, FILE *outputFile, char **nodes);
int DFS(TGraphL *G, int start, int *visit);
//Modificari ulterioare
void visit(TGraphL *G, int k, int *visited, FILE *outputFile, char **nodes);

#endif