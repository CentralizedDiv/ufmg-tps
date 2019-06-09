#include "./src/tp2.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  char *citiesFile;
  clock_t start, end;
  double cpu_time_used;

  start = clock();

  // argc != 5 -> debug VSCODE
  if (argc != 2 && argc != 5) {
    printf("Por favor insira o argumento, no formato \"./main "
           "{PATH_TO_FOLDER}/cidades.txt\"\n");
    printf("OBS: Se estiver usando make run, passe os argumentos no "
           "formato:\"make run citiesFile=\"{PATH_TO_FOLDER}/cidades.txt\"\n");
  } else {
    citiesFile = argv[1];
    startTP2(citiesFile);
  }
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Time elapsed %f", cpu_time_used);
  return 0;
}