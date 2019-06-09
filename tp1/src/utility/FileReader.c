#include <stdio.h>
#include <stdlib.h>
#include "FileReader.h"

int getQuantity(char* fileName) {
  FILE* uFile = fopen(fileName, "r");
  int quantity;
  fscanf(uFile, "%d", &quantity);
  return quantity;
}

University* getUniversitiesFromFile(char* fileName) {
  FILE* uFile = fopen(fileName, "r");
  int numberOfUniversities, index;
  University* universities;
  University currentUniversity;

  // Get First line, wich contains the number of universities
  fscanf(uFile, "%d", &numberOfUniversities);

  // Malloc x universities
  universities = malloc(numberOfUniversities * sizeof(University));

  // Get next lines, wich contains other univeristy values
  for(index = 0; index < numberOfUniversities; index++) {
    currentUniversity.id = index + 1;
    fscanf(uFile, "%d", &currentUniversity.numberOfPlaces);
    fscanf(uFile, "%d", &currentUniversity.minimumScore);

    universities[index] = currentUniversity;
  }

  fclose(uFile);
  return universities;
}

Applicant* getApplicantsFromFile(char* fileName) {
  FILE* aFile = fopen(fileName, "r");
  int numberOfApplicants, numberOfApplications, index, anotherIndex;
  Applicant* applicants;
  Applicant currentApplicant;

  // Get First line, wich contains the number of applicants
  fscanf(aFile, "%d", &numberOfApplicants);

  // Malloc x applicants
  applicants = malloc(numberOfApplicants * sizeof(Applicant));

  // Get next lines, wich contains other univeristy values
  for(index = 0; index < numberOfApplicants; index++) {
    currentApplicant.id = index + 1;

    // Get First line, wich contains the number of applications and score
    fscanf(aFile, "%d", &currentApplicant.numberOfApplications);
    fscanf(aFile, "%d", &currentApplicant.score);

    // Malloc x ints, one for each application
    currentApplicant.priorityList = malloc(currentApplicant.numberOfApplications * sizeof(int));

    for(anotherIndex = 0; anotherIndex < currentApplicant.numberOfApplications; anotherIndex++) {
      fscanf(aFile, "%d", &currentApplicant.priorityList[anotherIndex]);
    }

    applicants[index] = currentApplicant;
  }

  fclose(aFile);
  return applicants;
}