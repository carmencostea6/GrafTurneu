#include "graf.h"
int main(int argc, char *argv[])
{
    FILE *fin;
    fin = fopen(argv[1], "rt");
    if (fin == NULL)
    {
        printf("fisierul de citire nu a putut fi deschis");
        exit(1);
    }
    FILE *fg;
    fg = fopen(argv[2], "wt");
    if (fg == NULL)
    {
        printf("fisierul de scriere nu a putut fi deschis");
        exit(1);
    }
    FILE *fs;
    fs = fopen(argv[3], "wt");
    if (fs == NULL)
    {
        printf("fisierul de scriere nu a putut fi deschis");
        exit(1);
    }
    int nrechipe = 32;
    Graph *graph = initGraph(nrechipe);
    //printf("%d %d",graph->V,graph->E);
    citeste(fin, graph);
    int victorie[32];
    turneu(graph,victorie);
    scrie(fg, graph);
   // printf("%d %d",graph->V,graph->E);
    float prestigiu[32]={0};
    Prestigiu(nrechipe,victorie,prestigiu,0.15,5);
    afisare(fs,graph,prestigiu);
    freeGraph(graph);
    fclose(fin);
    fclose(fg);
    fclose(fs);
    return 0;
}
