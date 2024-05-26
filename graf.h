#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_TEAMS 32
#define MAX_NAME_LENGTH 100
typedef struct
{
    char *name;
    float points;
    int position;
} team;
typedef struct
{
    int E;
    team *teams;
    int **a;
} Graph;
Graph *initGraph(int nrechipe);
void citeste(FILE *fin, Graph *graph);
void meci(team *t1, team *t2, Graph *graph, int *roundWinners);
void turneu(Graph *graph);
void scrie(FILE *fg, Graph *graph);
//void freeGraph(Graph *graph);