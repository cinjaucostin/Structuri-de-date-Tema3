#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    int n, m;
    FILE *inputFile, *outputFile;
    inputFile = fopen("bnet.in", "r");
    outputFile = fopen("bnet.out", "w");
    //Citim numarul de noduri si numarul de arce ale grafului
    fscanf(inputFile, "%d %d\n", &n, &m);
    if (strcmp(argv[1], "-c1") == 0) //Verificam daca programul a primit ca argument string-ul "-c1"
    {
        //Declaram si alocam memorie pentru "matricea de cuvinte" in care vom salva numele nodurilor
        char **nodes;
        nodes = malloc(100 * sizeof(char *));
        for (int i = 0; i < 100; i++)
            nodes[i] = malloc(30 * sizeof(char));
        //Citirea celei de-a doua linii(cea care contine numele tuturor nodurilor)
        for (int i = 0; i < n; i++)
        {
            fscanf(inputFile, "%s ", nodes[i]); //Introduceam in matricea de cuvinte nodes pe pozitia i cuvantul din input de pe pozitia i
            //Practic faceam o asociere intre ordinea in care am primit nodurile in input si index-ul fiecaruia
            //Spre exemplu daca in input primeam in aceasta ordinea urmatoarele noduri:Cristi Alexandru Dragos
            //Lui Cristi ii corespunde index-ul 0, lui Alexandru index-ul 1 si lui Dragos index-ul 2
        }
        fscanf(inputFile, "\n");

        TGraphL *graf = create_graph(); //Apelam functia create_graph care aloca memorie pentru structura de tip graf si intoarce un pointer la ea.
        alloc_list(graf, n);            //Alocam memorie pentru lista de adiacenta a grafului

        char **read1;
        read1 = malloc(100 * sizeof(char *));
        for (int i = 0; i < 100; i++)
            read1[i] = malloc(30 * sizeof(char));
        char **read2;
        read2 = malloc(100 * sizeof(char *));
        for (int i = 0; i < 100; i++)
            read2[i] = malloc(30 * sizeof(char));

        for (int i = 0; i < m; i++)
        {
            fscanf(inputFile, "%s %s\n", read1[i], read2[i]); //Citim linia cu numele nodurilor adiacente
            //Apelam functia find_index pentru a afla index-ul nodului in functie de numele acestuia
            int v1 = find_index(nodes, read1[i], n);
            int v2 = find_index(nodes, read2[i], n);
            //Odata ce am calculat index-ul ambelor noduri vom apela functia insert_adiacency pentru a-l adauga pe v2 la lista de adiacenta a lui v1
            insert_adiacency(graf, v1, v2);
        }

        int *visited = calloc(n, sizeof(int)); //Alocam memorie pentru vectorul de vizitari
        int cycle = 1;                         //Pornim cu ideea ca
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == 0) //Apelam functia DFS pentru fiecare nod nevizitat
                cycle = DFS(graf, i, visited);
        }
        if (cycle) //Inseamna ca graful nu  are cicluri
        {
            fprintf(outputFile, "corect\n");
        }
        else //Inseamna ca graful are cicluri
            fprintf(outputFile, "imposibil\n");

        for (int i = 0; i < n; i++)
            visited[i] = 0;

        for (int i = 0; i < graf->nn; i++)
        {
            if (visited[i] == 0)
            {
                visit(graf, i, visited, outputFile, nodes);
            }
        }

        //Eliberarea memoriei ocupate

        destroy_graf(graf); //Eliberam memoria ocupata de graf
        //Eliberam memoria pointerilor de care ne-am folosit la citire
        for (int i = 0; i < 100; i++)
        {
            free(read1[i]);
            free(read2[i]);
        }
        for (int i = 0; i < 100; i++)
            free(nodes[i]);
        free(read1);
        free(read2);
        free(nodes);
        free(visited);
    }
    //Inchidem cele doua fisiere
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
