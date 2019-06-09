#include <stdio.h>
#include <stdlib.h>
#include "./models/Models.h"
#include "./utility/FileReader.h"

/**
 * Search an unmatched applicant in the matching, and set it to the pointer.
 *  The number of applications must be greater than 0, otherwise this is an unallocated applicant.
 *  If dont find anyone, returns false, otherwise returns true 
 */
bool getUnmatchedApplicant(Applicant* currentUnmatched, Applicant* applicants, Match* matching, int numberOfApplicants, int numberOfMatches) {
  int index, indexMatching;
  bool alreadyMatched, found = false;
  Applicant currentApplicant;
  Match currentMatch;

  // Loop through all applicants
  for(index = 0; index < numberOfApplicants; index++) {
    currentApplicant = applicants[index];

    // If this applicant did not applicate to all his list
    if(currentApplicant.numberOfApplications > 0) {
      alreadyMatched = false;

      // Loop through the current matching 
      for(indexMatching = 0; indexMatching < numberOfMatches; indexMatching++) {
        currentMatch = matching[indexMatching];
        if(currentMatch.applicant.id == currentApplicant.id) {
          alreadyMatched = true;
        }
      }

      // If this applicant wasn't found at the current matching, select it
      if(!alreadyMatched) {
        *currentUnmatched = currentApplicant; 
        found = true;
        break;
      }
    }
  }

  // If some unmatched was found  
  if(found) {
    return true;
  } else {
    return false;
  }
}

/**
 * Return the first university in currentUnmatched priorityList and remove it from his lit=st
 */
University getFirstUniversityInPriorityList(Applicant* currentUnmatched, University* universities, int numberOfUniversities, Applicant* applicants, int numberOfApplicants) {
  University currentUniversity;
  Applicant currentApplicant;

  // Get first univeristy
  int firstUniversityId = currentUnmatched->priorityList[0], index;  
  
  // Flag this position
  currentUnmatched->priorityList[0] = -1;
  
  // Shift priorityList array to right
  // If this wasn't the last univeristy in priorityList, move the next one to the first position
  currentUnmatched->numberOfApplications = currentUnmatched->numberOfApplications - 1;
  if(currentUnmatched->numberOfApplications > 0) {
    currentUnmatched->priorityList = &currentUnmatched->priorityList[1];
  }

  // Persist data into applicants array
  for(index = 0; index < numberOfApplicants; index++) {
    currentApplicant = applicants[index];
    if(currentApplicant.id == currentUnmatched->id) {
      applicants[index] = *currentUnmatched;
    }
  }

  for(index = 0; index < numberOfUniversities; index++) {
    currentUniversity = universities[index];
    if(currentUniversity.id == firstUniversityId) {
     return currentUniversity;
    }
  }
}

/**
 *  Search the worst score matched to an university in the matching,
 * return -1 if the university has an empty place
 */
int getCurrentWorstScore(University priorityUniverity, Match* matching, int numberOfMatches) {
  int index, worstScore = -1, matchesFound = 0;

  // Loop through current matching
  for(index = 0; index < numberOfMatches; index++) {
    Match currentMatch = matching[index];

    // If we find a matching with the univeristy, sets it worst score
    if(currentMatch.university.id == priorityUniverity.id) {
      matchesFound++;
      if(worstScore == -1 || currentMatch.applicant.score < worstScore) {
        worstScore = currentMatch.applicant.score;
      } 
    }
  }

  // If we found less matches than the university offers 
  if(matchesFound < priorityUniverity.numberOfPlaces) {
    return -1;
  } 
  return worstScore;
}

/**
 * Remove an id from an applicant priorityList
 */
void checkPriorityList(Applicant currentUnmatched, Applicant** unallocated, int* numberOfUnallocated) {
  if(currentUnmatched.priorityList[0] == -1) {
    *unallocated = realloc(*unallocated, (*numberOfUnallocated + 1) * sizeof(Applicant));
    (*unallocated)[*numberOfUnallocated] = currentUnmatched;
    *numberOfUnallocated += 1;
  }
}

/**
 * Insert an university and an applicant in the matching
 */
void match(University priorityUniverity, Applicant currentUnmatched, Match** matching, int* numberOfMatches, Applicant** unallocated, int* numberOfUnallocated, int replace) {
  int index;
  // If this university was already matched, change the applicant, otherwise, create a new match
  if(replace != -1) {
    for(index = 0; index < *numberOfMatches; index++) {
      if((*matching)[index].university.id == priorityUniverity.id && 
          (*matching)[index].applicant.score == replace) {
        
        checkPriorityList((*matching)[index].applicant, unallocated, numberOfUnallocated);
        (*matching)[index].applicant = currentUnmatched;  
      }  
    }
  } else {
    *matching = realloc(*matching, (*numberOfMatches + 1) * sizeof(Match));
    (*matching)[*numberOfMatches].applicant = currentUnmatched;
    (*matching)[*numberOfMatches].university = priorityUniverity;
    *numberOfMatches += 1;
  }
}

// Sorting Functions to use with qsort, they compare applicnats by their id
int compareApplicants(const void* a, const void* b) {
  const Applicant* applicantA = (const Applicant*)a;
  const Applicant* applicantB = (const Applicant*)b;
  return ( applicantA->id - applicantB->id ); 
}

int compareMatchs(const void* a, const void* b) {
  const Match* matchA = (const Match*)a;
  const Match* matchB = (const Match*)b;
  return compareApplicants(&matchA->applicant, &matchB->applicant); 
}

void startTP1(char* universitiesFile, char* applicantsFile) {
  int index;
  int currentWorstScore;
  int numberOfUniversities = getQuantity(universitiesFile);
  int numberOfApplicants = getQuantity(applicantsFile);
  int numberOfMatches = 0;
  int numberOfUnallocated = 0;

  University* universities = getUniversitiesFromFile(universitiesFile);
  Applicant* applicants = getApplicantsFromFile(applicantsFile);

  // Placeholder
  Applicant* unallocated = (Applicant*)calloc(0, sizeof(Applicant));
  Match* matching = (Match*)calloc(0, sizeof(Match));

  Applicant currentUnmatched;
  while(getUnmatchedApplicant(&currentUnmatched, applicants, matching, numberOfApplicants, numberOfMatches)) {
    University priorityUniverity = getFirstUniversityInPriorityList(&currentUnmatched, universities, numberOfUniversities, applicants, numberOfApplicants);  
    if(currentUnmatched.score >= priorityUniverity.minimumScore) {
      currentWorstScore = getCurrentWorstScore(priorityUniverity, matching, numberOfMatches);
      if(currentWorstScore < currentUnmatched.score) {
        match(priorityUniverity, currentUnmatched, &matching, &numberOfMatches, &unallocated, &numberOfUnallocated, currentWorstScore);  
      } else {
        checkPriorityList(currentUnmatched, &unallocated, &numberOfUnallocated);
      }
    } else {
      checkPriorityList(currentUnmatched, &unallocated, &numberOfUnallocated);
    }
  }

  //Sorting
  qsort(unallocated, numberOfUnallocated, sizeof(Applicant), compareApplicants);
  qsort(matching, numberOfMatches, sizeof(Match), compareMatchs);
  
  //Printing
  printf("Grupos com alocacao\n");
  for(index = 0; index < numberOfMatches; index++) {
    printf("%d %d\n", matching[index].applicant.id,  matching[index].university.id);
  }
  printf("Candidatos nao alocados\n");
  for(index = 0; index < numberOfUnallocated; index++) {
    printf("%d\n", unallocated[index].id); 
  }

  // Deallocating
  for(index = 0; index < numberOfApplicants; index++) {
    free(applicants[index].priorityList);
  }
  free(universities);
  free(applicants);
}