#ifndef INPUT_H
#define INPUT_H

#define MAX_INPUT_SIZE 1024
#define PATH_MAX 4096

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_input(char *buffer, size_t size);
void get_last_two_dirs(char *buf);

#endif