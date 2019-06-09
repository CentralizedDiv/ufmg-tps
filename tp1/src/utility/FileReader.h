#ifndef FILEREADER_H
#define FILEREADER_H

#include "../models/Models.h"

/**
 *  Read the file passed as parameter and return a fullfiled
 * array of univerities
 */
University *getUniversitiesFromFile(char *fileName);

/**
 *  Read the file passed as parameter and return a fullfiled
 * array of applicants
 */
Applicant *getApplicantsFromFile(char *fileName);

/**
 * Read the first number of a file, wich contains the number of
 * applicants/universities
 */
int getQuantity(char *fileName);

#endif