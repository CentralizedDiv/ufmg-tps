#ifndef MODELS_H
#define MODELS_H

/**
 * University Model
 * 
 * int: id -> University indicator.
 * int: minimumScore -> Minimum score to enter this university.
 * int: numberOfPlaces -> Maximum places at this univerity.  
 * 
 */
typedef struct {
  int id;
  int numberOfPlaces;
  int minimumScore;
} University;

/**
 * Applicant Model
 * 
 * int: id -> Applicant indicator.
 * int: score -> Applicant's score.
 * int*: priorityList -> Array of universities sorted by applicant's interest.  
 * int: numberOfApplications -> Amount of universities that this applicant put in his priorityList
 */
typedef struct {
  int id;
  int score;
  int numberOfApplications;
  int* priorityList;
} Applicant;

/**
 * Match Model
 * 
 * Applicant: applicant
 * University: university 
 */
typedef struct {
  University university;
  Applicant applicant;
} Match;

/**
 * Boolean type
 */
typedef int bool;
#define true 1
#define false 0

#endif