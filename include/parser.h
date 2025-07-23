#ifndef PARSER_H
#define PARSER_H

#define PARSE_OK 0
#define PARSE_ERR 1
#define MAX_ARGC 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_input(char *input, char **argv, int *count);

#endif