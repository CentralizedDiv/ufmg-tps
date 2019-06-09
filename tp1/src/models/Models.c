#include "Models.h"

struct University {
  int id;
  int numberOfPlaces;
  int minimumScore;
};

struct Applicant {
  int id;
  int score;
  int* priorityList;
};

struct Match {
  University university;
  Applicant applicant;
};