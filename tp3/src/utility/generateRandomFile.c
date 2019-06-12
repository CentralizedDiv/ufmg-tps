#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ref = https://stackoverflow.com/questions/6127503/shuffle-array-in-c */
void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

int main(int argc, char *argv[]) {
  // Randomize the seed
  srand(time(NULL));

  // Init variables
  int isSpanningTree = 0,
      numberOfVertexes = 0,
      numberOfEdges = 0,
      numberOfCycleEdges = 0,
      auxVertexA = 0,
      auxVertexB = 0,
      index = 0,
      jindex = 0;

  char *filePath;

  // Check if all parameters was given
  if (argc != 4) {
    printf("Please provide the args in the following format: generateRandomFile {numberOfVertexes} {isSpanningTree}(1/0) {filePath}\n");
  } else {
    // Get Params
    numberOfVertexes = atoi(argv[1]);
    isSpanningTree = atoi(argv[2]);
    filePath = argv[3];

    // Init arrays
    int vertexes[numberOfVertexes],
        randomVertexes[numberOfVertexes],
        adjMatrix[numberOfVertexes][numberOfVertexes];

    // Create and shuffle our vertexes
    for (index = 0; index < numberOfVertexes; index++) {
      randomVertexes[index] = index;

      // Fill our adjMatrix
      for (jindex = 0; jindex < numberOfVertexes; jindex++) {
        adjMatrix[index][jindex] = 0;
      }
    }
    shuffle(randomVertexes, numberOfVertexes);

    // Fill the root of our tree
    vertexes[0] = randomVertexes[numberOfVertexes - 1];

    // Open the file, and fill the first line
    FILE *fp = fopen(filePath, "w");
    fprintf(fp, "%d %d\n", numberOfVertexes, numberOfVertexes - 1);

    // For each vertex, we create a random edge
    for (index = 0; index < numberOfVertexes - 1; index++) {

      // Get a random vertex of our tree
      auxVertexA = vertexes[rand() % (index + 1)];

      // Pop the suffled vertexes array
      auxVertexB = randomVertexes[numberOfVertexes - (index + 2)];

      // Write the edge in our file
      fprintf(fp, "%d %d\n", auxVertexA, auxVertexB);
      vertexes[index + 1] = auxVertexB;

      // Mark the edge
      adjMatrix[auxVertexA][auxVertexB] = 1;
      adjMatrix[auxVertexB][auxVertexA] = 1;

      numberOfEdges++;
    }

    // If we want cycles
    // WARN this works really bad with big entries
    if (!isSpanningTree) {
      // Go to file's beggining
      fseek(fp, 0, SEEK_SET);

      // Random number of cycles
      int maxEdges = (numberOfVertexes * (numberOfVertexes - 1)) / 2;
      numberOfCycleEdges = rand() % (maxEdges - numberOfEdges) + 1;
	
      // Replace the first line
      fprintf(fp, "%d %d\n", numberOfVertexes, numberOfEdges + numberOfCycleEdges);

      // Back to the end of the file
      fseek(fp, 0, SEEK_END);
      fseek(fp, 0, SEEK_END);
      for (index = 0; index < numberOfCycleEdges; index++) {
        // Search non existing edges
        int aindex, chosenA = -1, chosenB = -1;
        for (aindex = 0; aindex < numberOfVertexes; aindex++) {
          for (jindex = 0; jindex < numberOfVertexes; jindex++) {
            if (aindex != jindex && adjMatrix[aindex][jindex] == 0) {
              chosenA = aindex;
              chosenB = jindex;
            }
          }
        }

        // Write the cycle edge in our file
        fprintf(fp, "%d %d\n", chosenA, chosenB);

        // Mark the edges
        adjMatrix[chosenA][chosenB] = 1;
        adjMatrix[chosenB][chosenA] = 1;

        numberOfEdges++;
      }
    }

    printf("Graph with %d cycle(s) generated at: %s", numberOfCycleEdges, filePath);
    // Close our file
    fclose(fp);
  }
  return 0;
}