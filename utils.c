#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

//Functia de alocare memorie pentru o structura de tip graf
TGraphL *create_graph()
{
    TGraphL *G;
    G = malloc(sizeof(TGraphL));
    return G;
}

//Alocam memorie pentru lista de adiacenta a grafului si setam numarul de noduri ale acestuia la n
void alloc_list(TGraphL *G, int n)
{
    int i;
    G->nn = n;
    G->adl = malloc(n * sizeof(ATNode)); //Alocam memorie pentru n campuri
    for (i = 0; i < n; i++)
        G->adl[i] = NULL; //Fiecare camp(inceput de lista de adiacenta) va puncta la NULL
}

void destroy_graf(TGraphL *G)
{
    ATNode parcurgere;
    for (int i = 0; i < G->nn; i++) //Trecem prin fiecare nod
    {
        parcurgere = G->adl[i]; //Parcurgem lista de adiacenta pentru fiecare nod in parte si eliberam memoria ocupata de aceasta
        while (parcurgere != NULL)
        {
            ATNode temp = parcurgere;      //Retinem un pointer la celula la care ne aflam acum
            parcurgere = parcurgere->next; //Avansam in lista
            free(temp);                    //Eliberam memoria
        }
        G->adl[i] = NULL; //Facem ca fiecare cap de lista sa puncteze la NULL la final
    }
    G->nn = 0;    //Numarul de noduri va fi al grafului va fi 0
    free(G->adl); //Eliberam pointerul adl
    free(G);      //Eliberam pointerul la intregul graf
}

//Functie cu ajutorul careia introducem nodul v2 in lista de adiacenta a nodului v1
void insert_adiacency(TGraphL *G, int v1, int v2)
{
    //Introducem valoarea v2 in lista de adiacenta a lui v1
    TNode *t;
    t = malloc(sizeof(TNode)); //Alocam memorie pentru noul nod pe care il vom atasa la lista de adiacenta a nodului v1
    t->v = v2;                 //Ii introducem valoarea v2
    //Realizam legaturile corespunzatoare in lista
    t->next = G->adl[v1];
    G->adl[v1] = t;
}

//Functie cu ajutorul careia aflam index-ul unui nod dupa numele acestuia folosindu-ne de matricea cu numele nodurilor definita in programul principal
int find_index(char **nodes, char *node_name, int n)
{
    //Cautam prin matricea de cuvinte numele nodului primit ca parametru
    for (int i = 0; i < n; i++)
    {
        if (strcmp(nodes[i], node_name) == 0) //Atunci cand gasim numele cuvantului intoarcem index-ul la care l-am localizat in matrice
            return i;
    }
}

//Functie auxiliara pe care am folosit-o la debug(sa vad daca graful se creeaza cum trebuie si daca listele de adiacenta sunt create cu valorile corecte)
void afisare_lista_adiacenta(TGraphL *G, FILE *outputFile, char **nodes)
{
    for (int i = 0; i < G->nn; i++)
    {
        ATNode parcurgere = G->adl[i];
        fprintf(outputFile, "Noduri adiacente nodului %s:", nodes[parcurgere->v]);
        while (parcurgere != NULL)
        {
            fprintf(outputFile, "%s ", nodes[parcurgere->v]);
            parcurgere = parcurgere->next;
        }
        fprintf(outputFile, "\n");
    }
}

//Parcurgerea de tip DFS pe care am folosit-o pentru a verifica daca graful este aciclic
int DFS(TGraphL *G, int start, int *visit)
{
    visit[start] = -1; //Valoarea -1 semnifica faptul ca nodul nu a fost descoperit
    ATNode aux;
    for (aux = G->adl[start]; aux != NULL; aux = aux->next) //Parcurgem lista de adiacenta pentru nod nostru curent
    {
        if (visit[aux->v] == 0) //Valoarea 0 semnifica faptul ca nodul a fost descoperit dar nu a fost parcurs in totalitate(nu toate nodurile adiacente la el au fost si ele parcurse)
        {
            if (DFS(G, aux->v, visit) == 0) //Inseamna ca am descoperit un ciclu in celelalte apeluri recursive ale functiei
                return 0;
        }
        else if (visit[aux->v] == -1) //Din moment ce nu am ajuns in el deloc inseamna ca exista un ciclu
            return 0;
    }
    visit[start] = 1; //Marcam prin valoarea 1 faptul ca nodul a fost descoperit in totalitate(am trecut prin toate nodurile adiacente lui)
    return 1;         //Daca se ajunge aici inseamna ca nu s-au descoperit cicluri in cadrul grafului deci acesta este aciclic
}

//Modificari ulterioare
void visit(TGraphL *G, int k, int *visited, FILE *outputFile, char **nodes)
{
    ATNode t;
    visited[k] = 1;
    for (t = G->adl[k]; t != NULL; t = t->next)
    {
        if (visited[t->v] == 0)
            visit(G, t->v, visited, outputFile, nodes);
    }
    fprintf(outputFile, "%s ", nodes[k]);
}
