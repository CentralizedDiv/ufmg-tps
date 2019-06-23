#include "./src/tp3.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  char *graphFile, *task;

  // argc != 6 -> debug VSCODE
  if (argc != 3 && argc != 6) {
    printf("Por favor insira o argumento, no formato \"./build/tp3 "
           "tarefa1 {PATH_TO_FOLDER}/trilha.txt\"\n");
    printf("OBS: Se estiver usando make run, passe os argumentos no "
           "formato:\"make run task=\"tarefa1\" graphFile=\"{PATH_TO_FOLDER}/cidades.txt\"\n");
  } else {
    task = argv[1];
    graphFile = argv[2];
    startTP3(graphFile, task);
  }
  return 0;
}