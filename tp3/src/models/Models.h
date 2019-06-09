#ifndef MODELS_H
#define MODELS_H

/**
 * Boolean type
 */
typedef int bool;
#define true 1
#define false 0

typedef struct Edge Edge;

struct Edge {
  int src;
  int dest;
  Edge *next;
  Edge *prev;
};

typedef struct {
  int id;
  bool visited;
  bool flagged;
  Edge *edges;
} Vertex;

typedef struct {
  int V;
  Vertex *vertexes;
} Graph;

#endif