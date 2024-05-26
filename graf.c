#include "graf.h"
#define MAX_TEAMS 32
#define MAX_NAME 100
Graph *initGraph(int nrechipe)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        printf("Alocare dinamică eșuată");
        exit(1);
    }
    graph->E = nrechipe;
    graph->teams = (team *)malloc(nrechipe * sizeof(team));
    if (graph->teams == NULL)
    {
        printf("Alocare dinamică eșuată");
        exit(1);
    }
    graph->a = (int **)malloc(nrechipe * sizeof(int *));
    for (int i = 0; i < nrechipe; i++)
        graph->a[i] = (int *)calloc(nrechipe, sizeof(int));
    return graph;
}
void citeste(FILE *fin, Graph *graph)
{
    char name[MAX_NAME];
    float points;
    int index = 0;

    while (fscanf(fin, "%f %[^\n]s", &points, name) != EOF && index < graph->E)
    {
        graph->teams[index].position = index + 1;
        graph->teams[index].name = strdup(name);
        graph->teams[index].points = points;
        index++;
    }
}
// Funcția pentru desfășurarea unui meci și determinarea câștigătorului
void meci(team *t1, team *t2, Graph *graph, int *roundWinners)
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
    roundWinners[winner] = 1;
    graph->a[winner][loser] = 1;
}
// Funcția pentru desfășurarea unui turneu
void turneu(Graph *graph)
{
    int nrechipe = graph->E;
    int *roundWinners = (int *)calloc(nrechipe, sizeof(int));
    while (nrechipe > 1)
    {
        for (int i = 0; i < nrechipe; i += 2)
            meci(&graph->teams[i], &graph->teams[i + 1], graph, roundWinners);
        int newNumTeams = 0;
        for (int i = 0; i < graph->E; i++)
            if (roundWinners[i])
                graph->teams[newNumTeams++] = graph->teams[i];
        memset(roundWinners, 0, graph->E * sizeof(int));
        nrechipe = newNumTeams;
    }

    free(roundWinners);
}
// Funcția pentru scrierea matricei de adiacență într-un fișier
void scrie(FILE *fg, Graph *graph)
{

    for (int i = 0; i < graph->E; i++)
    {
        for (int j = 0; j < graph->E; j++)
            fprintf(fg, "%d ", graph->a[i][j]);
        fprintf(fg, "\n");
    }
}
/*// Funcția pentru eliberarea memoriei alocate grafului
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
}*/