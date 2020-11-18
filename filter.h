/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: filter.h
 *
 */

#ifndef FILTER_H
#define FILTER_H

#include <stdio.h>
#include <string.h>

/**
 * Reads the file line by line and checks if the domain is not permited
 * @param filename File name
 * @return 0 if it's allowed, 1 if some error occured, -1 if permited domain
 */
int filter_domain(char * filename, char * domain);

#endif //FILTER_H