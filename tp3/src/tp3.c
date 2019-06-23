#include "./models/Models.h"
#include "./utility/GraphUtilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
  if (a < b)
    return a;

  return b;
}

int optimalVertexCover(Graph *graph, int currentVertex, bool isFlagged, int isFlaggedMap[][2], int parentMap[]) {
  // Se o vértice não tiver arestas
  if (graph->vertexes[currentVertex].edges == NULL) {
    return isFlagged;
  } else if (isFlaggedMap[currentVertex][isFlagged] != -1) { // Se já tivermos o valor para este vértice
    return isFlaggedMap[currentVertex][isFlagged];
  }

  // Inicializa a soma
  int sum = 0, index;
  Edge *currentEdge = graph->vertexes[currentVertex].edges;

  // Percorre as arestas deste vértice
  while (currentEdge != NULL) {
    // Se o próximo vértice não for o pai do atual
    if (currentEdge->dest != parentMap[currentEdge->src]) {
      // Salva o pai
      parentMap[currentEdge->dest] = currentVertex;

      // Se o vértice atual não tem bandeira, o próximo deve ter
      if (!isFlagged) {
        sum += optimalVertexCover(graph, currentEdge->dest, true, isFlaggedMap, parentMap);
      } else { // Se tem, devemos verificar as duas opções para o próximo
        sum += min(optimalVertexCover(graph, currentEdge->dest, true, isFlaggedMap, parentMap), optimalVertexCover(graph, currentEdge->dest, false, isFlaggedMap, parentMap));
      }
    }

    // Vai para a próxima aresta
    currentEdge = currentEdge->next;
  }

  // Guarda o resultado no map
  isFlaggedMap[currentVertex][isFlagged] = sum + isFlagged;
  return isFlaggedMap[currentVertex][isFlagged];
}

void task1(Graph *graph) {
  int index;

  // Mappers usados para programação dinâmica
  // Salva, para cada vértice, o resultado quando o mesmo está, ou não marcado
  int isFlaggedMap[graph->V][2];
  // Salva o pai de cada vértice.
  int parentMap[graph->V];

  // Preenche os mappers com um valor inicial de -1
  for (index = 0; index < graph->V; index++) {
    isFlaggedMap[index][0] = -1;
    isFlaggedMap[index][1] = -1;
    parentMap[index] = -1;
  }

  // Calcula o valor sem a raíz(vértice 0)
  int withoutRoot = optimalVertexCover(graph, 0, false, isFlaggedMap, parentMap);

  // Calcula o valor com a raíz(vértice 0)
  int withRoot = optimalVertexCover(graph, 0, true, isFlaggedMap, parentMap);

  // Printa o resultado ótimo
  printf("%d\n", min(withoutRoot, withRoot));
}

void task2(Graph *graph) {
  int index, currentSrc, currentDest, sum = 0;

  // Para cada vértice, percorre todas suas arestas
  for (index = 0; index < graph->V; index++) {

    // Pega a primeira aresta
    Edge *currentEdge = graph->vertexes[index].edges;
    while (currentEdge) {
      // Se o vértice atual não tem bandeira, põe a bandeira nos dois vértices desta aresta
      if (!graph->vertexes[currentEdge->src].flagged) {
        graph->vertexes[currentEdge->src].flagged = true;
        graph->vertexes[currentEdge->dest].flagged = true;
        sum += 2;
      }
      currentSrc = currentEdge->src;
      currentDest = currentEdge->dest;

      currentEdge = currentEdge->next;

      // Remove esta aresta, nos dois sentidos
      removeEdge(graph, currentSrc, currentDest);
    }
  }

  printf("%d\n", sum);
}

void startTP3(char *graphFile, char *task) {

  // Monta o grafo
  Graph *graph = getGraphFromFile(graphFile);

  if (graph) {
    if (strncmp(task, "tarefa1", 10) == 0) {
      task1(graph);
    } else if (strncmp(task, "tarefa2", 10) == 0) {
      task2(graph);
    } else {
      printf("\n Insira uma das duas tarefas validas: 'tarefa1' ou 'tarefa2'");
    }
  }
}