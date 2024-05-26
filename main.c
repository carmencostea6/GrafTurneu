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
        printf("fisierul de citire nu a putut fi deschis");
        exit(1);
    }
    FILE *fs;
    fs = fopen(argv[3], "wt");
    if (fs == NULL)
    {
        printf("fisierul de citire nu a putut fi deschis");
        exit(1);
    }
    int nrechipe = 32;
    Graph *graph = initGraph(nrechipe);
    citeste(fin, graph);
    turneu(graph);
    scrie(fg, graph);
    //freeGraph(graph);
    fclose(fin);
    fclose(fg);
    fclose(fs);
    return 0;
}
