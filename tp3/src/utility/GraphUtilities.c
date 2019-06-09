#include "GraphUtilities.h"
#include <stdio.h>
#include <stdlib.h>

void removeEdgeDirected(Graph *graph, Edge *auxEdge, int vertexToCompare, int vertexToChange) {
  while (auxEdge) {
    if (auxEdge->dest == vertexToCompare) {
      if (auxEdge->prev != NULL) {
        auxEdge->prev->next = auxEdge->next;
      } else {
        (&graph->vertexes[vertexToChange])->edges = auxEdge->next;
      }
      auxEdge = NULL;
    } else {
      auxEdge = auxEdge->next;
    }
  }
}

void removeEdge(Graph *graph, int src, int dest) {
  int index;
  Edge *auxEdge = graph->vertexes[src].edges;
  removeEdgeDirected(graph, auxEdge, dest, src);

  auxEdge = graph->vertexes[dest].edges;
  removeEdgeDirected(graph, auxEdge, src, dest);
}

void printGraph(Graph *graph) {
  int v;
  for (v = 0; v < graph->V; ++v) {
    Edge *edge = graph->vertexes[v].edges;
    printf("\n Graph Adjacency List \n%d ", graph->vertexes[v].id);
    while (edge) {
      printf(" - [%d -> %d]", edge->src, edge->dest);
      edge = edge->next;
    }
    printf("\n");
  }
}

Edge *newEdge(int src, int dest) {
  Edge *edge = (Edge *)malloc(sizeof(Edge));
  edge->src = src;
  edge->dest = dest;
  return edge;
}

void addEdge(Graph *graph, int src, int dest) {
  Edge *edge = newEdge(src, dest);
  edge->prev = NULL;
  edge->next = graph->vertexes[src].edges;

  if (graph->vertexes[src].edges != NULL)
    graph->vertexes[src].edges->prev = edge;

  graph->vertexes[src].edges = edge;

  edge = newEdge(dest, src);
  edge->prev = NULL;
  edge->next = graph->vertexes[dest].edges;

  if (graph->vertexes[dest].edges != NULL)
    graph->vertexes[dest].edges->prev = edge;

  graph->vertexes[dest].edges = edge;
}

Graph *createGraph(int V) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->V = V;
  graph->vertexes = (Vertex *)malloc(V * sizeof(Vertex));

  int i;
  for (i = 0; i < V; ++i) {
    graph->vertexes[i].id = i;
    graph->vertexes[i].visited = false;
    graph->vertexes[i].flagged = false;
    graph->vertexes[i].edges = NULL;
  }

  return graph;
}

Graph *getGraphFromFile(char *fileName) {
  FILE *uFile = fopen(fileName, "r");

  if (uFile) {
    int numberOfVertexes, numberOfEdges, index, currentSrc, currentDest;

    // Pega, da primeira linha o número de vértices e de arestas
    fscanf(uFile, "%d", &numberOfVertexes);
    fscanf(uFile, "%d", &numberOfEdges);

    Graph *graph = createGraph(numberOfVertexes);

    // Percorre as próximas linhas, criando as arestas
    for (index = 0; index < numberOfEdges; index++) {
      fscanf(uFile, "%d", &currentSrc);
      fscanf(uFile, "%d", &currentDest);
      addEdge(graph, currentSrc, currentDest);
    }

    fclose(uFile);
    return graph;
  } else {
    printf("\nArquivo nao encontrado!\n");
  }
}