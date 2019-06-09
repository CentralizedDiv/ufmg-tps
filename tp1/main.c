#include <stdio.h>
#include "./src/tp1.h"

int main(int argc, char *argv[]) {
  char *universitiesFile;
  char *applicantsFile;

  if(argc != 3) {
    printf("Por favor insira os dois argumentos, no formato \"./main {PATH_TO_FOLDER}/universidades.txt {PATH_TO_FOLDER}/candidatos.txt\"\n");
    printf("OBS: Se estiver usando make run, passe os argumentos no formato: \"make run universitiesFile=\"{PATH_TO_FOLDER}/universidades.txt\" applicantsFile=\"{PATH_TO_FOLDER}/candidatos.txt\"\n");
  } else {
    universitiesFile = argv[1];
    applicantsFile = argv[2]; 
    startTP1(universitiesFile, applicantsFile);
  }
  return 0;
}