/**
 * VUT FIT Brno
 * 28.10.2020
 *
 * Authors:
 * Lukas Javorsky (xjavor20)
 * 
 * File: error.c
 *
 */

#include "error.h"

int errorMsg(char *msg)
{
    fprintf(stderr, RED"%s\n"RESET, msg);
    return EXIT_FAILURE;
}