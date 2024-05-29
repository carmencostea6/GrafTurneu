#include "graf.h"
#define MAX_TEAMS 32
#define MAX_NAME 100
//exercitiul 1
//initializez graful,aloc memorie+matricea de adiacenta initializata cu 0
Graph *initGraph(int nrechipe)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        printf("alocare dinamică eșuată");
        exit(1);
    }
    graph->V = nrechipe;
    graph->E = 0;
    graph->teams = (team *)malloc(nrechipe * sizeof(team));
    if (graph->teams == NULL)
    {
        printf("alocare dinamică eșuată");
        exit(1);
    }
    graph->a = (int **)malloc(nrechipe * sizeof(int *));
    for (int i = 0; i < nrechipe; i++)
        graph->a[i] = (int *)calloc(nrechipe, sizeof(int));
    return graph;
}
//citesc datele din fisier
void citeste(FILE *fin, Graph *graph)
{
    char name[MAX_NAME];
    float points;
    int index = 0;
    while (index < graph->V)
    {
        fscanf(fin, "%f", &points);
        graph->teams[index].points = points;
        graph->teams[index].position = index + 1;
        fgets(name, MAX_NAME, fin);
         name[strlen(name) - 1] = '\0';//sterg newline
        graph->teams[index].name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        if (graph->teams[index].name == NULL)
        {
            printf("alocare dinamică esuata");
            exit(1);
        }
        strcpy(graph->teams[index].name, name);
        index++;
    }
}
// functie pentru desfasurarea unui meci si determinarea castigatorului
void meci(team *t1, team *t2, Graph **graph, int drum[])
{
    int winner, loser;
    if (t1->points > t2->points || (t1->points == t2->points && strcmp(t1->name, t2->name) < 0))
    {
        winner = t1->position - 1;
        loser = t2->position - 1;
    }
    else
    {
        winner = t2->position - 1;
        loser = t1->position - 1;
    }
    drum[winner] = 1;
    (*graph)->a[winner][loser] = 1;
    (*graph)->E++;
}
// functie pentru desfășurarea unui turneu
void turneu(Graph *graph,int victorie[])
{
    int nrechipe = graph->V;
    int *drum = (int *)malloc(nrechipe * sizeof(int));
    while (nrechipe > 1)
    {
        for (int k = 0; k < nrechipe; k++)
           { drum[k] = 0;
           victorie[k]=0;
           }
        for (int i = 0; i < nrechipe; i += 2)
            meci(&graph->teams[i], &graph->teams[i + 1], &graph, drum);
        int nr = 0;
        for (int j = 0; j < nrechipe; j++)
            if (drum[j]==1)
               {
                graph->teams[nr] = graph->teams[j];
                victorie[graph->teams[j].position - 1]++;//numar victoriile pentru fiecare echipa
                nr++;
               }
        nrechipe = nr;
    }
    free(drum);
}
// functie pt scrierea matricei de adiacenta in fisier
void scrie(FILE *fg, Graph *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        for (int j = 0; j < graph->V; j++)
            fprintf(fg, "%d ", graph->a[i][j]);
        fprintf(fg, "\n");
    }
}
//exercitiul 2
void Prestigiu(int nrechipe, int victorie[], float prestigiu[], float q,int l) //calculeaza prestigiul fiecarei echipe
{
    int r;
    for (int i = 0; i < nrechipe; i++)
     {
        r = victorie[i];
        float r1 = pow(2-q,r);
        float r2=pow(2,l);
        float r3=pow(2-q,l);
        prestigiu[i] = (q*r1)/(r2+r3*(q-1));
    }
}
void afisare(FILE *fs, Graph *graph, float prestigiu[]) 
{
    for (int i = 0; i < graph->V-1; i++) 
      for(int j=i+1;j<graph->V;j++)
      if(prestigiu[j]>prestigiu[i])
        fprintf(fs, "%.4f %s\n", prestigiu[i], graph->teams[i].name);
}
// functie pentru eliberarea memoriei alocate grafului
void freeGraph(Graph *graph)
{
    for (int i = 0; i < graph->E; i++)
    {
        free(graph->teams[i].name);
        free(graph->a[i]);
    }
    free(graph->teams);
    free(graph->a);
    free(graph);
}