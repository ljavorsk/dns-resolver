/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: filter.c
 *
 */

#include "filter.h"
#include "error.h"
#include <stdlib.h>
int filter_domain(char * filename, char * domain){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) return errorMsg("File cannot be opened");
    
    char chunk[128];

    // 0 if the domain is not permited, 1 if permited
    int result = 0;
    
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        // Clear the newline characters
        chunk[strcspn(chunk, "\r\n")] = 0;

        if(result == 1) break;
        // Skip comment lines
        if(chunk[0] == '#') continue;

        // Compare every line of the file to the output
        result = (strcmp(chunk, domain)) ? 0 : 1;
    }
    fclose(fp);
    return result;
}