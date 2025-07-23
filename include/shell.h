#ifndef SHELL_H
#define SHELL_H

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define EXIT_SHELL 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int shell();
int execute_command(char **argv, int argc);

#endif