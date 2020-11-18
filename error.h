/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: error.h
 *
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

/**
 * Prints err message to the stderr
 * @param msg Message
 * @return Returns 1
 */
int errorMsg(char *msg);

#endif //ERROR_H