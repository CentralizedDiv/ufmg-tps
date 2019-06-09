#ifndef GRAPH_UTILITIES
#define GRAPH_UTILITIES

#include "../models/Models.h"

// Cria o grafo, com V nós
Graph *createGraph(int V);

// Cria o grafo, com V nós
void printGraph(Graph *graph);

// Remove a aresta em ambas direções
void removeEdge(Graph *graph, int src, int dest);

// Monta o grafo, lendo do arquivo e populando a estrutura
Graph *getGraphFromFile(char *fileName);

#endif